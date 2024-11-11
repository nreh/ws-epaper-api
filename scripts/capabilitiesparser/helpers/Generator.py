from abc import ABC, abstractmethod

from .ClassBuilder import DrawTargetClassBuilder
from .EPaperDetails import EPaperDetails
import helpers.ClassBuilder as cb
from helpers.logging import Logger


def extract_function_suffix(s, type):
    # Find the position of "type" in the string
    type_index = s.find(type)
    # If "type" is found, return everything from "type" onward
    if type_index != -1:
        return s[type_index:]
    # If "type" is not found, return the original string
    return s.split('(', maxsplit=1)[0]


def count_args(function_call):
    content = function_call.split("(")[1].split(")")[0].strip()
    if not content or content == "void":  # Check for empty or 'void'
        return 0
    return len(content.split(","))


class Generator():
    """
    Generic class for generating C++ code for EPD displays
    """

    def __init__(self, builder: DrawTargetClassBuilder, det: EPaperDetails, log: Logger):
        builder: DrawTargetClassBuilder
        det: EPaperDetails
        log: Logger

        super().__init__()
        self.builder = builder
        self.det = det
        self.log = log

    def CreateFunctionFromSignature(self, functionSignature: str, category: str, functionName: str, docstring: str,
                                    first: bool = False, passedParameters: 'list[str]' = []):
        function_name = functionSignature.split("(")[0]
        num_args = count_args(functionSignature)

        if num_args > len(passedParameters):
            self.log.warning(
                f'Function \'{functionSignature}\' takes {num_args} arguments but we expected at most {len(passedParameters)} - skipping',
                f'{category} Loop')
            return None  # function takes too many arguments, Skip
        else:
            content = f'controller::{function_name}({", ".join(passedParameters[0:num_args])});'

            return cb.Function(
                functionName if first else extract_function_suffix(
                    function_name, functionName),
                content,
                docstring
            )

    def AddFunctionFromSignature(self, functionSignature: str, category: str, functionName: str, docstring: str,
                                 first: bool = False, passedParameters: 'list[str]' = []):
        """
        Parse function signature and add it to the headerfile
        """
        res = self.CreateFunctionFromSignature(
            functionSignature, category, functionName, docstring, first, passedParameters)

        if not res is None:
            self.builder.functions.append(res)

    def CreateInitializeFunctions(self):
        """
        Parse function signatures for all 'Initialize' functions and add them to the headerfile
        """

        first = True
        for i in sorted(self.det.functions['Initialize'], key=len):
            self.AddFunctionFromSignature(i, 'Initialize', 'Init',
                                          'Initialize the display', first)
            first = False

    def CreateClearFunctions(self):
        """
        Parse function signatures for all 'Clear' functions and add them to the headerfile
        """

        first = True
        for i in sorted(self.det.functions['Clear'], key=len):
            self.AddFunctionFromSignature(i, 'Clear', 'Clear',
                                          'Clear the display', first)
            first = False

    def CreateSleepFunctions(self):
        """
        Parse function signatures for all 'Sleep' functions and add them to the headerfile
        """

        first = True
        for i in sorted(self.det.functions['Sleep'], key=len):
            self.AddFunctionFromSignature(i, 'Sleep', 'Sleep',
                                          'Put the display to sleep', first)
            first = False

    def CreateDisplayFunctions(self):
        """
        Parse function signatures for all 'Display' functions and add them to the headerfile
        """

        first = True
        combined = self.det.functions['Display'] + self.det.functions['Display_Base'] + \
            self.det.functions['Display_Partial'] + \
            self.det.functions['Display_Fast'] + \
            self.det.functions['Display_Misc']

        for i in sorted(combined, key=len):
            # we want to add it to DisplayFunctions instead of Functions
            func = self.CreateFunctionFromSignature(i, 'Display', 'Display',
                                                    'Display pixels in buffers to display', first, [])
            self.builder.DisplayFunctions.append(func)
            first = False

    def BuildHeaderfile(self):
        self.CreateInitializeFunctions()
        self.CreateClearFunctions()
        self.CreateSleepFunctions()
        self.CreateDisplayFunctions()

        return self.builder.Build()
