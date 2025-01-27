# This file contains code for create C++ DrawTarget headers files piece by piece

from datetime import datetime
import json
import textwrap
from .EPaperDetails import EPaperDetails
from logging import Logger


def dict_to_wrapped_string(data, width=120, indent=2, prefix=" * "):
    # Convert dictionary to JSON string with proper indentation
    json_string = json.dumps(data, indent=indent)
    # Split the JSON string into lines
    lines = json_string.splitlines()
    # Wrap each line individually, with the specified width and prefix
    wrapped_lines = []
    for line in lines:
        wrapped_lines.extend(
            textwrap.wrap(line, width=width,
                          subsequent_indent=prefix, initial_indent=prefix)
        )
    # Join the wrapped lines into a single string
    return "\n".join(wrapped_lines)


class Param:
    def __init__(self, name: str, type: str, description: str):
        self.name = name
        self.type = type
        self.description = description


class Function:
    def __init__(self, name: str, content: str, description: str, override: bool = False, params: 'list[Param]' = []):
        self.name = name
        self.content = content
        self.description = description
        self.override = override
        self.params = params

    def Build(self) -> str:
        """
        Generate C++ code for function
        """
        # docstring
        docstring = f'/// @brief {self.description}\n'
        paramlist = ''

        for p in self.params:
            docstring += f'/// @param {p.name} {p.description}\n'
            paramlist += f'{p.type} {p.name}, '

        docstring = docstring.strip()
        paramlist = paramlist.strip(' ,')

        signature = f'void {self.name}({paramlist}) '
        if self.override:
            signature += 'override '
        signature += '{'

        return f'{docstring}\n{signature}\n{textwrap.indent(self.content, "    ")}\n}}'


class DrawTargetClassBuilder:
    """
    Used for constructing C++ headerfiles for DrawTargets
    """

    def __init__(self, det: EPaperDetails, classname: str, inherits: str, log: Logger):
        self.det: EPaperDetails = det
        self.classname = classname
        self.inherits = inherits
        self.DisplayFunctions: 'list[Function]' = []
        self.functions: 'list[Function]' = []
        self.ignoredFunctions: list[str] = []

    def ConstructRefreshFunction(self) -> Function:
        conditions = []
        idx = 0
        for i in self.DisplayFunctions:
            conditions.append(f'''case RefreshMode::{self.refreshModes[idx]}:
{i.name}();
break;
''')
            idx += 1
        joinedCond = "\n".join(conditions)
        content = f'''if (!IsOpen()) {{
    throw RefreshingClosedDevice(GetDeviceName());
}}

PreprocessBuffers();

switch (static_cast<RefreshMode>(mode)) {{
{joinedCond}

default:
    throw UnsupportedRefreshMode(mode, GetDeviceName());
}}
        '''

        return Function('Refresh',
                        content,
                        'Refresh the display with current buffer',
                        True,
                        [Param('mode', 'int', 'How to refresh the display')])

    def ConstructRefreshModeEnum(self) -> str:
        temp = []
        self.refreshModes = []
        for i in self.DisplayFunctions:
            e = i.name.replace('Display_', '')
            if e == '':
                e = 'Normal'

            temp.append(e)
            self.refreshModes.append(e)

        # sort refreshmodes

        # enforce Display, Partial, Base as first three modes
        order = {"Display": 0, "Partial": 1, "Base": 2}
        temp = sorted(
            temp, key=lambda x: order.get(x, 3))

        s = 'enum RefreshMode { '
        count = 0
        for i in temp:
            s += f'{i} = {count}, '
            count += 1

        s = s.strip(' ,') + ' };'

        return s

    def DocumentIgnoredFunctions(self) -> str:
        if len(self.ignoredFunctions) == 0:
            return ""
        else:
            s = "// The following functions were not created:\n\n"
            for i in self.ignoredFunctions:
                s += f'//  ! {i}\n'
            s += '\n'

            return s

    def ConstructFunctionDeclarations(self) -> str:
        r = ''

        for i in self.DisplayFunctions:
            self.functions.append(i)

        self.functions.append(self.ConstructRefreshFunction())
        for f in self.functions:
            r += f.Build() + '\n\n'
        return r.strip()

    def Build(self) -> str:
        return f'''/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: {self.det.fullName}
 * Shortname: {self.det.name}
 * Generated On: {datetime.now().strftime("%-d %B %Y @ %-I:%M %p")}
 * Supported Color Channels: {",".join(self.det.supportColorChannels)}
 * Type: {self.inherits}
 *
 * The following JSON data was used:
{dict_to_wrapped_string(self.det.raw)}
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {{

/// @brief Waveshare devices that you can draw to
namespace devices {{

/// @brief {self.det.fullName}
namespace {self.det.name} {{

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {{
extern "C" {{
#include "../epaper/e-Paper/{self.det.name}.h"
}}
}} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = {self.det.screenWidth};

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = {self.det.screenHeight};

{self.ConstructRefreshModeEnum()}

class {self.det.name}_DrawTarget : public {self.inherits} {{
  public:
    std::string GetDeviceName() const override {{ return "{self.det.fullName}"; }}
    int GetWidth() const override {{ return DEVICE_WIDTH; }}
    int GetHeight() const override {{ return DEVICE_HEIGHT; }}
    
{textwrap.indent(self.DocumentIgnoredFunctions(), '    ')}{textwrap.indent(self.ConstructFunctionDeclarations(), '    ')}

    {self.det.name}_DrawTarget() : {self.inherits}(GetWidth(), GetHeight()) {{}}
    ~{self.det.name}_DrawTarget() {{}}
}};

}} // namespace {self.det.name}

}} // namespace devices

}} // namespace epaperapi'''
