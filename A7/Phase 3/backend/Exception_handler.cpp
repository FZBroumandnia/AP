#include "Exception_handler.hpp"
Exception_handler::Exception_handler(int _type)
{
    exception_type = _type;
};
string Exception_handler::error_message()
{
    if (exception_type == Not_found)
        return NF;
    if (exception_type == Bad_Req)
        return BAD_REQ;
    if (exception_type == Empty)
        return EMPTY;
    if (exception_type == Permission_denied)
        return PERMISSION_ERR;
    return " ";
}