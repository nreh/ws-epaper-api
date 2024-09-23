# This script goes through all header files and generates DrawTargets classes for each. It uses ChatGPT to determine
# capablities and other details because I'm too lazy to go through all of them manually :P

import os
import sys
from openai import OpenAI

print("Starting parsefiles.py script...")

OPENAI_API_KEY = os.environ.get('OPENAI_PERSONAL_API_KEY')
EPAPER_DIR = './epaper/e-Paper/'
INSTRUCTIONS = """In the C++ code I give identify the height and width preprocessor variables. Please put your response in a
simple format in the form: "width,height" (without the quotation marks). There are many files but they're all in the same
general format with differing prefixes and sometimes functions but nothing drastic. BUT, if you find a weird discrepancy or
some potential confusion (even slightly) indicate as such in the form: "WARNING: <your message>" (without the quotations).
"""

if OPENAI_API_KEY is None:
    raise RuntimeError(
        "No OPENAI_API_KEY in environment variables! This script uses ChatGPT so please supply the API key.")

# https://platform.openai.com/docs/assistants/quickstart

client = OpenAI(api_key=OPENAI_API_KEY)

assistant = client.beta.assistants.create(
    name="E-Paper API Assistant",
    instructions=INSTRUCTIONS,
    model='gpt-3.5-turbo'
)

thread = client.beta.threads.create()


class EPaperDetails:
    """
    Contains details parsed from the header files
    """

    def __init__(self):
        self.name = ""  # example: EPD_2in13_V4
        self.fullPath = ""  # example: epaper/e-Paper/EPD_2in13_V4.h
        self.fullName = ""  # example: 2.13inch e-paper V4
        self.screenWidth = 0  # example: 122
        self.screenHeight = 0  # example: 250
