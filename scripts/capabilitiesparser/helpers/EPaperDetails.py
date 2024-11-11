import json
import pathlib
import re
import time
from openai import OpenAI


client = None
assistant = None
thread = None


def SetUpOpenAI(OPENAI_API_KEY, prompt, model):
    global client
    global assistant
    global thread

    print("Setting up OpenAI API...", end='')

    # https://platform.openai.com/docs/assistants/quickstart

    client = OpenAI(api_key=OPENAI_API_KEY)

    assistant = client.beta.assistants.create(
        name="E-Paper API Assistant",
        instructions=prompt,
        model=model,
    )

    thread = client.beta.threads.create()


class EPaperDetails:
    """
    Contains details parsed from the header files
    """

    def __init__(self, filename):
        self.filename = filename  # name of the source file this information was extracted from
        self.name = pathlib.Path(self.filename).stem  # example: EPD_2in13_V4
        self.fullPath = ""  # example: epaper/e-Paper/EPD_2in13_V4.h
        self.fullName = ""  # example: 2.13inch e-paper V4
        self.screenWidth = 0  # example: 122
        self.screenHeight = 0  # example: 250
        self.supportColorChannels = []  # example, black, red, green, blue, yellow
        self.data = {
            "FullName": None,
            "ScreenWidth": None,
            "ScreenHeight": None,
            "SupportedColorChannels": [],
            "Functions": {
                "Initialize": [],
                "Clear": [],
                "Display": [],
                "Display_Base": [],
                "Display_Partial": [],
                "Display_Fast": [],
                "Display_Misc": [],
                "Sleep": [],
                "Misc": []
            },
            "Notes": None,
        }
        self.paintScale = None
        self.paintRotation = None
        self.bitmapFunction = None
        self.notes = None
        self.functions = {}

    def parseFromJson(self, json: dict):
        self.fullName = json['FullName']
        self.screenWidth = json['ScreenWidth']
        self.screenHeight = json['ScreenHeight']
        self.supportColorChannels = json['SupportedColorChannels']
        self.functions = json['Functions']
        self.notes = json['Notes']
        if 'PaintScale' in json.keys():
            self.paintScale = json['PaintScale']
        if 'PaintRotation' in json.keys():
            self.paintRotation = json['PaintRotation']
        if 'BitmapFunction' in json.keys():
            self.bitmapFunction = json['BitmapFunction']

    def toJson(self) -> dict:
        json = {
            'FullName': self.name,
            'ScreenWidth': int(self.screenWidth),
            'ScreenHeight': int(self.screenHeight),
            'SupportedColorChannels': self.supportColorChannels,
            'Functions': self.functions,
            'Notes': self.notes,
        }
        if self.paintScale is not None:
            json['PaintScale'] = self.paintScale
        if self.paintRotation is not None:
            json['PaintRotation'] = self.paintRotation
        if self.bitmapFunction is not None:
            json['BitmapFunction'] = self.bitmapFunction

        return json

    def ParseFromHeaderFile(self, file):
        f = open(file, 'r', encoding='utf-8', errors='replace')
        contents = f.read()
        f.close()

        message = client.beta.threads.messages.create(
            thread_id=thread.id,
            role="user",
            content=contents
        )

        run = client.beta.threads.runs.create_and_poll(
            thread_id=thread.id,
            assistant_id=assistant.id
        )

        while run.status == 'in_progress':
            time.sleep(0.25)

        if run.status == 'completed':
            result = client.beta.threads.messages.list(
                thread_id=thread.id).data[0].content[0].text.value
            r = open('ignore_log.txt', 'a')
            r.write(result + '\n\n')
            r.close()

            # parse as JSON
            self.data = json.loads(result)
            self.parseFromJson(self.data)

            return self.data
        else:
            raise Exception(f'Run did not complete, status={run.status}')

    def ParseExampleFile(self, file):
        f = open(file, 'r', encoding='utf-8', errors='replace')
        contents = f.read()
        f.close()

        # find certain functions or lines of code in the example file

        # Paint Scale

        match = re.search(r'Paint_SetScale\((\d+)\)', contents)
        if match:
            self.paintScale = int(match.group(1))

        # Paint Rotation

        match = re.search(
            r'Paint_NewImage\([^,]+, [^,]+, [^,]+, (\d+),', contents)
        if match:
            self.paintRotation = int(match.group(1))

        # Bitmap Function

        match = re.search(r'\b(GUI_ReadBmp(?:_[A-Za-z0-9]+)*)\b', contents)
        if match:
            self.bitmapFunction = match.group(1)

    def Save(self, outputDirectory: str):
        """
        Save details as a JSON to output directory
        """

        outputPath = pathlib.Path(outputDirectory)

        out = open(outputPath / (self.filename + '.json'),
                   'w', encoding='utf-8', errors='replace')
        json.dump(self.toJson(), out, indent=2)
        out.close()

    def HasExampleFile(self):
        """
        Returns true if there is some data parsed from an example file
        """
        return self.paintScale != None or self.paintRotation != None or self.bitmapFunction != None

    def DetermineMode(self):
        """
        Based on data features determine what mode of C++ header file to generate...
        """
        if self.HasExampleFile():
            if self.paintScale == 2 or self.paintScale == None:
                if self.bitmapFunction == 'GUI_ReadBmp':
                    if 'black' in self.supportColorChannels:
                        if len(self.supportColorChannels) == 1:
                            # 1 Bit monochrome mode
                            return 'Black1BitEPD'
                        else:
                            # Red/Black mode
                            return 'RedBlack1BitEPD'
                    else:
                        # must be some other unknown single channel color
                        return 'UnknownSingleChannel'

        return 'Unknown'
