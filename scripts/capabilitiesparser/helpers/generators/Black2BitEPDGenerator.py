# This file contains code for generating C++ header files

from ..Generator import Generator
from ..ClassBuilder import DrawTargetClassBuilder
from ..EPaperDetails import EPaperDetails
from ..logging import Logger


class Black2BitEPD_Generator(Generator):
    """
    Generate C++ code for a black 2 bit EPD display
    """

    def __init__(self, det: EPaperDetails, log: Logger):
        super().__init__(DrawTargetClassBuilder(
            det, det.name, 'Black2BitEPD', log), det, log)

    # add packedBits argument
    def CreateDisplayFunctions(self):
        """
        Parse function signatures for all 'Display' functions and add them to the headerfile
        """

        has4GrayFunction = False

        first = True
        combined = self.det.functions['Display'] + self.det.functions['Display_Base'] + \
            self.det.functions['Display_Partial'] + \
            self.det.functions['Display_Fast'] + \
            self.det.functions['Display_Misc']

        def sorter(name):
            return len(name.split('(')[0])

        # Even though the display is 2 bit (4 shades of gray), these functions actually render 1 bit of color :/
        # we determine whether a function accepts a 2bit or 1bit color array by if the name of the display
        # function contains '4Gray'

        # However, if no display function contains '4Gray' in its name, then all functions are assumed to
        # be 4Gray (2bit).

        for i in combined:
            i: str
            if '4gray' in i.lower():
                has4GrayFunction = True
                break

        _1bitDisplayFunctions: list[str] = []
        _2bitDisplayFunctions: list[str] = []

        if not has4GrayFunction:
            _2bitDisplayFunctions = combined
        else:
            for i in combined:
                if '4gray' in i.lower():
                    _2bitDisplayFunctions.append(i)
                else:
                    _1bitDisplayFunctions.append(i)

        for i in sorted(_1bitDisplayFunctions, key=sorter):
            # we want to add it to DisplayFunctions instead of Functions
            func = self.CreateFunctionFromSignature(i, 'Display', 'Display',
                                                    'Display pixels in 1 bit buffer to display', first,
                                                    ['packedBits_1bit'])

            if func is None:
                continue

            self.builder.DisplayFunctions.append(func)
            first = False

        for i in sorted(_2bitDisplayFunctions, key=sorter):
            func = self.CreateFunctionFromSignature(
                i, 'Display', f'{self.det.name}_', 'Display pixels in 2 bit buffer to display (4 shades of gray)',
                False,
                ['packedBits_2bit'])

            if func is None:
                continue

            self.builder.DisplayFunctions.append(func)
