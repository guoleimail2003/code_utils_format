#include <common_type.h>
#include <QString>

QString CommonType::getInputFormat(QString caller, const int input) {
    if (input <= INPUT_FORMAT_START || input >= INPUT_FORMAT_INVALID
            || caller.isNull() || caller.isEmpty()) {
        qFatal("The output format you input is invalid input = %d, caller=%s\n", input, qPrintable(caller));
    }
    if (DEBUG_PRINT) qDebug("caller=%s, input = %d\n", qPrintable(caller), input);
    QString ret;
    ret.clear();
    switch(input) {
    case INPUT_FORMAT_DECIMAL:
        ret = "INPUT_FORMAT_DECIMAL";
        break;
    case INPUT_FORMAT_HEX:
        ret = "INPUT_FORMAT_HEX";
        break;
    case INPUT_FORMAT_OCT:
        ret = "INPUT_FORMAT_OCT";
        break;
    case INPUT_FORMAT_BINARY:
        ret = "INPUT_FORMAT_BINARY";
        break;
    case INPUT_FORMAT_ASCII:
        ret = "INPUT_FORMAT_ASCII";
        break;
    default:
        if (DEBUG_PRINT) qDebug("NO string for this input format caller=%s, input = %d\n", qPrintable(caller), input);
        break;
    }
    return ret;
}

QString CommonType::getOutputFormat(QString caller, const int output) {
    if (output <= OUTPUT_FORMAT_START || output >= OUTPUT_FORMAT_INVALID
            || caller.isNull() || caller.isEmpty()) {
        qFatal("The output format you input is invalid output = %d, caller=%s\n", output, qPrintable(caller));
    }
    if (DEBUG_PRINT) qDebug("caller=%s, output = %d\n", qPrintable(caller), output);
    QString ret;
    switch (output) {
    case OUTPUT_FORMAT_DECIMAL:
        ret = "OUTPUT_FORMAT_DECIMAL";
        break;
    case OUTPUT_FORMAT_HEX:
        ret = "OUTPUT_FORMAT_HEX";
        break;
    case OUTPUT_FORMAT_OCT:
        ret = "OUTPUT_FORMAT_OCT";
        break;
    case OUTPUT_FORMAT_BINARY:
        ret = "OUTPUT_FORMAT_BINARY";
        break;
    case OUTPUT_FORMAT_ASCII:
        ret = "OUTPUT_FORMAT_ASCII";
        break;
    default:
        if (DEBUG_PRINT) qDebug("NO string for this output format caller=%s, output = %d\n", qPrintable(caller), output);
        break;
    }
    return ret;
}


