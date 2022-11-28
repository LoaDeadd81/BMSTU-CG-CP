#include "Errors.h"

BaseError::BaseError(string file, string function, int line, string message)
{
    error_message = "\n\nError";
    error_message += "\nFile: " + file;
    error_message += "\nFunction : " + function;
    error_message += "\nLine : " + to_string(line);
    error_message += "Info : " + message;
    error_message += "\n\n";
}

const char *BaseError::what() const noexcept
{
    return error_message.c_str();
}

MemoryError::MemoryError(string file, string function, int line, string message)
        : BaseError(file, function, line, message)
{

}

DimensionError::DimensionError(string file, string function, int line, string message)
        : BaseError(file, function, line, message)
{
}

IndexError::IndexError(string file, string function, int line, string message)
        : BaseError(file, function, line, message)
{
}

IterIndexError::IterIndexError(string file, string function, int line, string message)
        : BaseError(file, function, line, message)
{
}

ZeroDivError::ZeroDivError(string file, string function, int line, string message)
        : BaseError(file, function, line, message)
{

}
