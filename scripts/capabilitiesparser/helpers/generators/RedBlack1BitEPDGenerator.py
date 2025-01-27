# This file contains code for generating C++ header files

from ..Generator import Generator
from ..ClassBuilder import DrawTargetClassBuilder
from ..EPaperDetails import EPaperDetails
from ..logging import Logger


class RedBlack1BitEPD_Generator(Generator):
    """
    Generate C++ code for a redblack 1 bit EPD display
    """

    def __init__(self, det: EPaperDetails, log: Logger):
        super().__init__(DrawTargetClassBuilder(
            det, det.name, 'RedBlack1BitEPD', log), det, log)

    # add packedBits argument
    def CreateDisplayFunctions(self):
        """
        Parse function signatures for all 'Display' functions and add them to the headerfile
        """

        first = True
        combined = self.det.functions['Display'] + self.det.functions['Display_Base'] + \
            self.det.functions['Display_Partial'] + \
            self.det.functions['Display_Fast'] + \
            self.det.functions['Display_Misc']

        def sorter(name):
            return len(name.split('(')[0])

        for i in sorted(combined, key=sorter):
            # we want to add it to DisplayFunctions instead of Functions
            func = self.CreateFunctionFromSignature(i, 'Display', 'Display',
                                                    'Display pixels in buffers to display', first,
                                                    ['packedBitsBlack', 'packedBitsRed'])

            if func is None:
                continue

            self.builder.DisplayFunctions.append(func)
            first = False
