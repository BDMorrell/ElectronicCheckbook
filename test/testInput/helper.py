import sys, getopt, os.path

class generator:
    newline=None
    fileName=''
    def generate(openFile):
        raise NotImplementedError('helper.generator.generate() is an abstract method')

def generateFile(gen):
    outputPath = getOutputPathFromArgv(gen.fileName)
    with open(outputPath, 'w', newline=gen.newline) as file:
        gen.generate(file)

def getOutputPathFromArgv(filename):
    outputDirectory = 'hello'
    helpText = " [-h|--help] [-D <directory>|--directory=<directory>]"
    opts, extraArgs = None,None
    try:
        opts, extraArgs = getopt.getopt(sys.argv[1:],"hD:",["help","directory="])
    except getopt.error:
        print("Error: " + sys.argv[0] + helpText)
        sys.exit(1)
    for (opt, arg) in opts:
        if opt in ('-h', '--help'):
            print("usage: " + sys.argv[0] + helpText)
            sys.exit()
        elif opt in ('-D', '--directory'):
            outputDirectory = arg
        else:
            print("?")
    return os.path.realpath(os.path.join(outputDirectory, filename))
