#include "Error.h"

BaseError::BaseError(string file, string function, int line, const char *time, string message)
{
    error_message = "\n\nError";
    error_message += "\nFile: " + file;
    error_message += "\nFunction : " + function;
    error_message += "\nLine : " + to_string(line);
    error_message += "\nTime : " + string(time);
    error_message += "Info : " + message;
    error_message += "\n\n";
}

const char *BaseError::what() const noexcept
{
    return error_message.c_str();
}

FileError::FileError(string file, string function, int line, const char *time, string message) : BaseError(file,
                                                                                                           function,
                                                                                                           line, time,
                                                                                                           message)
{

}

BadModel::BadModel(string file, string function, int line, const char *time, string message) : BaseError(file, function,
                                                                                                         line, time,
                                                                                                         message)
{

}

CamExistError::CamExistError(string file, string function, int line, const char *time, string message) : BaseError(file,
                                                                                                                   function,
                                                                                                                   line,
                                                                                                                   time,
                                                                                                                   message)
{

}

RangeError::RangeError(string file, string function, int line, const char *time, string message) : BaseError(file,
                                                                                                             function,
                                                                                                             line, time,
                                                                                                             message)
{

}
