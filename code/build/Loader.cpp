#include "Loader.h"

void TXTLoader::open(string file_name)
{
    try
    {
        stream.open(file_name, ios::in);
    }
    catch (ifstream::failure &e)
    {
        time_t t_time = time(NULL);
        throw FileError(__FILE__, __FUNCTION__ , __LINE__, ctime(&t_time), "Error while opening file");
    }
}

int TXTLoader::get_num()
{
    int num;
    try
    {
        stream >> num;
    }
    catch (ifstream::failure &e)
    {
        time_t t_time = time(NULL);
        throw FileError(__FILE__, __FUNCTION__ , __LINE__, ctime(&t_time), "Error while reading from file");
    }
    return num;
}

void TXTLoader::close()
{
    stream.close();
}
