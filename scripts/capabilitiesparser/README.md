# 🧠 Capabilities Parsing

Each Waveshare E-Paper display has different capabilities and ways to render images to the display, and there are at least 71
different displays (based on 71 header files in the `external/waveshare/epaper/e-Paper` folder). Because it'd be extremely
tedious to go through all those headerfiles manually and write C++ DrawTarget code for each, I'm taking advantage of ChatGPT
to do that for me instead.

This folder contains 2 scripts, one for parsing capabilities for an EPD device from waveshares own code and writing them into
JSON files. And one for generating **DrawTarget** headerfiles for use by the epaper API from those generated JSON files.

In addition to the header files in the `external/waveshare/epaper/e-Paper`, the parse script also requires the example files
taken from Waveshare's GitHub repo which contains useful information on the color scale, rotation, and bitmap functions used.

## 📂 Step 1: Create Folders

Create two folders, one for the headerfiles and one for the example code. (Alternatively, you can just use the existing
`external/waveshare/epaper/e-Paper` folder for the headerfiles).

You can obtain the example files from (though make sure to remove any extra files that aren't example files):
https://github.com/waveshareteam/e-Paper/tree/master/RaspberryPi_JetsonNano/c/examples

After that, create one more folder for where the outputted JSON files will be saved to.

In this example, we'll create the following folders:

```bash
./HeaderFiles/ # This folder will contain our EPD headerfiles
./ExampleFiles/ # This folder will contain our EPD example code from their github
./results # JSON files generated will be saved here
```

## 🔑 Step 2: Get API Key

Head over to https://platform.openai.com/api-keys and create an API key. Set the `OPENAI_PERSONAL_API_KEY` environment
variable to this API key.

## 📖 Step 3: Parse the Code

Now we can run the `Parse.py` script. Here's how it works.

```
usage: Parse.py [-h] [--single] [--model MODEL] [--prompt PROMPT] [--output OUTPUT] [--full] headerpath examplepath

Parses header and test files using ChatGPT and records functions, capabilities, and other information.


positional arguments:

  headerpath       Path to directory containing header files

  examplepath      Path to directory containing .c example files


optional arguments:

  -h, --help       show this help message and exit

  --single         When this flag is used, you can pass in a single file instead of a directory for headerpath and examplepath

  --model MODEL    ChatGPT model to use, default is 'gpt-4o'

  --prompt PROMPT  Path to file containing prompt given to ChatGPT. Default is 'prompt.txt'

  --output OUTPUT  Directory to output parsed results - default is './results'

  --full           By default files that have already been parsed will not be reparsed. If this flag is passed all files regardless of whether they have been parsed or not will be reparsed and have .json files regenerated.
```

For now, all optional arguments can be ignored, so for our example it would look something like this:

```
python3 Parse.py ./HeaderFiles ./ExampleFiles
```

The script will find all header files in the `HeaderFiles` folder and send them to ChatGPT for parsing. Then, it will attempt
to find a matching example file in the `ExampleFiles` folder and fill in any remaining information.

> [!NOTE] Due to OpenAI's rate limiting, you'll probably have to re-run the script multiple times to get all header files
> parsed. Don't worry, any header files that have already been processed will be skipped.

### Example JSON

Here's an example of the generated JSON from the **EPD_2in13_V4.h** headerfile:

```json
{
  "FullName": "2.13inch e-paper V4",
  "ScreenWidth": 122,
  "ScreenHeight": 250,
  "SupportedColorChannels": ["black"],
  "Functions": {
    "Initialize": ["EPD_2in13_V4_Init(void)", "EPD_2in13_V4_Init_Fast(void)", "EPD_2in13_V4_Init_GUI(void)"],
    "Clear": ["EPD_2in13_V4_Clear(void)", "EPD_2in13_V4_Clear_Black(void)"],
    "Display": ["EPD_2in13_V4_Display(UBYTE *Image)"],
    "Display_Base": ["EPD_2in13_V4_Display_Base(UBYTE *Image)"],
    "Display_Partial": ["EPD_2in13_V4_Display_Partial(UBYTE *Image)"],
    "Display_Fast": ["EPD_2in13_V4_Display_Fast(UBYTE *Image)"],
    "Display_Misc": [],
    "Sleep": ["EPD_2in13_V4_Sleep(void)"],
    "Misc": []
  },
  "Notes": "Only black is supported explicitly as all functions and clears reference 'black'. The function EPD_2in13_V4_Init_GUI doesn't indicate a specific display capability but is included for comprehensive initialization.",
  "PaintRotation": 90,
  "BitmapFunction": "GUI_ReadBmp"
}
```
