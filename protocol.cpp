#include "protocol.h"

std::string domain2queryname(std::string source){
    std::string ret;
    ret.resize(source.size()+2, '0');

    int p = source.size() - 1;
    int length = 0;

    char* _source = (char*)source.c_str();
    char* _ret = (char*)ret.c_str();

    while (p >= 0) {
        if (_source[p] != '.') {
            length++;
            ret[p + 1] = _source[p];
        }else {
            ret[p + 1] = length;
            length = 0;
        }
        p--;
    }
    ret[0] = length;
    return std::move(ret);
}

std::string queryname2domain(std::string source){
    int source_size = source.size();
    std::string ret;
    ret.resize(source_size - 2, '0');
    
    char* _source = (char*)source.c_str() ;
    char* _ret = (char*)ret.c_str();
    memcpy(_ret, _source + 1, source_size - 1);

    int p = _source[0];
    while (p < source_size - 2) {
        int n = _ret[p];
        _ret[p] = '.';
        p += n + 1;
    }
    return std::move(ret);
}
