#include "CFileOperation.h"
#include "CCopyOperation.h"
#include "CMoveOperation.h"

int main(int argc, char* argv[])
{
    // construct the helper text
    const std::string helpText =
        "Usage: recf operation \"patterns\" target_dir [source_dir]\n\n"
        "operations:\n"
        "\tc\tcopy the files matching the pattern\n"
        "\tm\tmove the files matching the pattern\n"
        "\th\tdisplay this text\n"
        "\n"
        "patterns:\n"
        "\ta comma separated list of matches to be used as a critera\n"
        "\ti.e. \"*.png,foo*.mkv\"\n"
        "\n"
        "target_dir:\n"
        "\twhere the files that match the criteria should be copied/moved to\n"
        "\n"
        "source_dir:\n"
        "\twhere the recursive walk should start from; defaults to the current working directory"
        "\n";

    std::vector<std::string> arguments; // the vector storing the incoming arguments
    std::string operation, patterns, target, source;
    CFileOperation* fileOp = nullptr;

    // store the arguments in a vector
    for (int i = 1; i < argc; i++) 
        arguments.push_back (argv[i]);

    // check if there are enough arguments
    if (arguments.size() < 3)
    {
        std::cout << "Not enough arguments specified.\n";
        std::cout << helpText;
        
        return error_code::NOT_ENOUGH_ARGUMENTS;
    }

    // get the operation
    operation = arguments[0];

    // check the operation
    if (operation.compare("m") && operation.compare("c") && operation.compare("h"))
    {
        std::cout << "Invalid operation specified.\n";
        std::cout << helpText;

        return error_code::INVALID_ARGUMENTS;
    }

    // if the user wanted the help, we're done here
    if (operation.compare ("h") == 0)
    {
        std::cout << helpText;

        return error_code::SUCCESS;
    }

    // get the patterns
    patterns = arguments[1];

    // get the target dir
    target = arguments[2];
    
    // get the source dir
    if (arguments.size() > 3)
        source = arguments[3];
    else
        source = ".";

    // make the operation
    if (operation.compare ("m") == 0)
        fileOp = new CMoveOperation (source, target, patterns);
    else if (operation.compare ("c") == 0)
        fileOp = new CCopyOperation (source, target, patterns);

    // do the chosen operation
    int result = fileOp->do_operation ();

    // delete the object
    delete fileOp;

    // return status
    return result;
}
