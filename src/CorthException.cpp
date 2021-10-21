#include "CorthException.hpp"

CorthException::CorthException(int _errorCode, const std::string& _message) : message(_message), errorCode(_errorCode) { }

const char* CorthException::what() const {
    return message.c_str();
}

const std::string& CorthException::getMessage() {
    return message;
}
const int& CorthException::getErrorCode() {
    return errorCode;
}