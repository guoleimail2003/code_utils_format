#include <codeformatter.h>
#include <common_type.h>
#include <QStringList>
#include <Qt>


QString CodeFormatter::TAG = QString("CodeFormatter");

QString CodeFormatter::getTag() {
    return TAG;
}

CodeFormatter::CodeFormatter(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief CodeFormatter::hex_2_str from hex to ascii
 * @param prefix
 * @param hex_val such as "0x41 0x42" --> "AB"
 * @return "AB"
 */
/**
 * @brief CodeFormatter::hex_2_str  from hex to ascii string
 * @param prefix  such as 0x41 --> the prefix is 0x etc.
 * @param input
 * @param output
 * @param hex_val such as 41 42 or 0x41 0x42
 * @param split  ' '
 * @return  "AB"
 */
QString CodeFormatter::hex_2_str(const int input_format, const int output_format,
                                 const QString hex_val, const QChar split)
{
    if (input_format <= INPUT_FORMAT_START || input_format >= INPUT_FORMAT_INVALID
            || output_format <= OUTPUT_FORMAT_START || output_format >= OUTPUT_FORMAT_INVALID
            || hex_val.isNull() || hex_val.isEmpty()
            || split.isNull() || !split.isSpace())
    {
        qFatal("parameter is not null and empty, func = %s", "hex_2_str");
    }
    if (DEBUG_PRINT) {
        qDebug("Enter the hex_2_str function!");
        qDebug("input_format =%s, output_format=%s, hex_val=%s, split=%x\n",
               qPrintable(CommonType::getInputFormat(getTag(), input_format)),
               qPrintable(CommonType::getOutputFormat(getTag(), output_format)),
               qPrintable(hex_val),
               split.toAscii());
    }
    int code_format = 10;
    switch (input_format) {
    case INPUT_FORMAT_DECIMAL:
        code_format = 10;
        break;
    case INPUT_FORMAT_HEX:
        code_format = 16;
        break;
    case INPUT_FORMAT_OCT:
        code_format = 8;
        break;
    case INPUT_FORMAT_BINARY:
        code_format = 2;
    default:
        code_format = 10;
        break;
    }

    QString ret, tmp, val;
    val = hex_val;
    QStringList list = val.split(split);
    char c;
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).trimmed();
        if (tmp.isEmpty()) {
            continue;
        }
        c = tmp.toInt(0, code_format);
        if (DEBUG_PRINT) qDebug("list[%d] = %d", i, c);
        ret.append(c);
    }
    if (DEBUG_PRINT) qDebug("ret = %s",qPrintable(ret));
    return ret;
}

/**
 * @brief CodeFormatter::str_2_hex
 * @param prefix   0x
 * @param input   hex oct binary
 * @param hex_val  "ABCD"
 * @param split    ' ' split with space
 * @return   "0x41 0x42 0x43 0x44"
 */
QString CodeFormatter::str_2_hex(const int input_format, const int output_format,
                                 const QString hex_val, const QChar split)
{
    if (input_format <= INPUT_FORMAT_START || input_format >= INPUT_FORMAT_INVALID
            || output_format <= OUTPUT_FORMAT_START || output_format >= OUTPUT_FORMAT_INVALID
            || hex_val.isNull() || hex_val.isEmpty()
            || split.isNull() || !split.isSpace())
    {
        qFatal("parameter is not null and empty, func = %s/n", "str_2_hex");
    }
    if (DEBUG_PRINT) {
        qDebug("Enter the str_2_hex function!");
        qDebug("input_format=%s, output_format=%s, hex_val=%s, split=%x\n",
               qPrintable(CommonType::getInputFormat(getTag(), input_format)),
               qPrintable(CommonType::getOutputFormat(getTag(), output_format)),
               qPrintable(hex_val),
               split.toAscii());
    }

    //output codec
    int code_format = 10;
    switch (output_format) {
    case OUTPUT_FORMAT_DECIMAL:
        code_format = 10;
        break;
    case OUTPUT_FORMAT_HEX:
        code_format = 16;
        break;
    case OUTPUT_FORMAT_OCT:
        code_format = 8;
        break;
    case OUTPUT_FORMAT_BINARY:
        code_format = 2;
        break;
    default:
        code_format = 10;
        break;
    }
    qDebug("code_format = %d\n", code_format);
    QString ret,tmp,val;
    QChar c;
    ret.clear();
    val = hex_val;
    val = val.trimmed();
    for (int i = 0; i < val.size(); i++) {
        char c = val.at(i).toAscii();
        if (c == ' ') {
            continue;
        }
        tmp.clear();
        if (output_format == OUTPUT_FORMAT_HEX) {
            tmp.append("0x");
        } else if (output_format == OUTPUT_FORMAT_OCT) {
            tmp.append("0");
        }
        tmp.append(QString::number(c, code_format).toUpper());
        if (i !=  (val.size() -1)) tmp.append(split);
        ret.append(tmp);
    }
    if (DEBUG_PRINT) qDebug("ret = %s\n", qPrintable(ret));
    return ret;
}
