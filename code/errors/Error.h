#ifndef ERROR_H
#define ERROR_H

#include <execution>
#include <string>
#include <ctime>

using namespace std;

class BaseError : public exception
{
public:
    BaseError()=default;
    virtual ~BaseError() = default;
    BaseError(string file, string function, int line, const char *time, string message);
    virtual const char *what() const noexcept override;

protected:
    string error_message;
};

class FileError : public BaseError
{
public:
    FileError()=default;
    virtual ~FileError() override = default;
    explicit FileError(string file, string function, int line, const char *time, string message);
};

class BadModel : public BaseError
{
public:
    BadModel()=default;
    virtual ~BadModel() override = default;
    explicit BadModel(string file, string function, int line, const char *time, string message);
};

class CamExistError : public BaseError
{
public:
    CamExistError()=default;
    virtual ~CamExistError() override = default;
    explicit CamExistError(string file, string function, int line, const char *time, string message);
};

class RangeError : public BaseError
{
public:
    RangeError()=default;
    virtual ~RangeError() override = default;
    explicit RangeError(string file, string function, int line, const char *time, string message);
};


#endif
