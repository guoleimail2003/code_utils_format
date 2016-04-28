#ifndef COMMON_TYPE_H
#define COMMON_TYPE_H

#include <QString>


#define PREFIX_STR_0X "0x"
#define PREFIX_STR_NONE ""
#define DEBUG_PRINT true

#define CHECK_NULL_POINTER(p) ((NULL == p)?true:false)

typedef enum {
    INPUT_FORMAT_START = 10,
    INPUT_FORMAT_DECIMAL = 11,
    INPUT_FORMAT_HEX = 12,
    INPUT_FORMAT_OCT = 13,
    INPUT_FORMAT_BINARY = 14,
    INPUT_FORMAT_ASCII = 15,
    INPUT_FORMAT_INVALID
} INPUT_FORMAT;

typedef enum {
    OUTPUT_FORMAT_START = 20,
    OUTPUT_FORMAT_DECIMAL = 21,
    OUTPUT_FORMAT_HEX = 22,
    OUTPUT_FORMAT_OCT = 23,
    OUTPUT_FORMAT_BINARY = 24,
    OUTPUT_FORMAT_ASCII = 25,
    OUTPUT_FORMAT_INVALID
} OUTPUT_FORMAT;

class CommonType {
public:
    static QString getInputPrefix(QString caller, const int prefix);
    static QString getInputFormat(QString caller, const int input);
    static QString getOutputFormat(QString caller, const int output);
};

#endif // COMMON_TYPE_H
