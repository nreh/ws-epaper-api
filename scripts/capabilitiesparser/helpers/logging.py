import textwrap


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    GRAY = '\033[90m'
    DIMYELLOW = '\033[2;33m'


class Logger:
    def __init__(self, verbose: bool, filename: str):
        self.verbose = verbose
        self.filename = filename

    def write(self, type: str, message: str, area: str, prefixColor=bcolors.GRAY, messageColor=''):
        type = type.upper()
        if type == 'INFO' and self.verbose == False:
            # don't log
            return
        else:
            if area != '':
                area = f' @ {area}'
            print(textwrap.indent(
                f'{message}{bcolors.ENDC}', f'{prefixColor}[{self.filename}]{area} |{bcolors.ENDC}{messageColor} '))

    def info(self, message, area=''):
        self.write('info', message, area)

    def error(self, message, area=''):
        self.write('error', message, area, bcolors.FAIL,
                   bcolors.BOLD + bcolors.FAIL)

    def warning(self, message, area=''):
        self.write('warning', message, area,
                   bcolors.GRAY, bcolors.WARNING)
