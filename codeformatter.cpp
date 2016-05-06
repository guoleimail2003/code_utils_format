#include <codeformatter.h>
#include <common_type.h>
#include <QStringList>

QString CodeFormatter::TAG = QString("CodeFormatter");

QString CodeFormatter::getTag() {
    return TAG;
}

CodeFormatter::CodeFormatter(QObject *parent) :
    QObject(parent)
{
    mSplit = ' ';
}

QString CodeFormatter::ascii_2_digital
(const int input_format, const int output_format, QString input)
{
    if (input_format <= INPUT_FORMAT_START || input_format >= INPUT_FORMAT_INVALID
            || output_format <= OUTPUT_FORMAT_START || output_format >= OUTPUT_FORMAT_INVALID
            || input.isNull() || input.isEmpty()
            || INPUT_FORMAT_ASCII != input_format) {
        qFatal("The parameter is invalid for this function!");
        if (INPUT_FORMAT_ASCII != input_format) {
            if (DEBUG_PRINT) qDebug("input_fomrat is invalid! input_format = %s\n",
                                    qPrintable(CommonType::getInputFormat(TAG, input_format)));
        }
    }

    if (DEBUG_PRINT) qDebug("Enter the function = %s,", "ascii_2_digital");

    //get split from the input
    QString ret;

    switch(output_format) {
    case OUTPUT_FORMAT_HEX:
        ret = ascii_2_hex(input);
        break;
    case OUTPUT_FORMAT_DECIMAL:
        ret = ascii_2_decimal(input);
        break;
    case OUTPUT_FORMAT_OCT:
        ret = ascii_2_oct(input);
        break;
    case OUTPUT_FORMAT_BINARY:
        ret = ascii_2_binary(input);
        break;
    default:
        if (DEBUG_PRINT) qDebug("Func name =%s , can not find the output_format function to handle the the request", "ascii_2_digital");
        ret = ascii_2_decimal(input);
        break;
    }
    if (DEBUG_PRINT) qDebug("exit func = %s\n", "ascii_2_digital");
    return ret;
}

/**
 * @brief CodeFormatter::digital_2_ascii
 * @param input_format
 * @param output_format
 * @param input
 * @return
 */
QString CodeFormatter::digital_2_ascii
(const int input_format, const int output_format, const QString input)
{
    if (input_format <= INPUT_FORMAT_START || input_format >= INPUT_FORMAT_INVALID
            || output_format <= OUTPUT_FORMAT_START || output_format >= OUTPUT_FORMAT_INVALID
            || input.isNull() || input.isEmpty()
            || OUTPUT_FORMAT_ASCII != output_format) {
        qFatal("The parameter is invalid for this function!");
        if (OUTPUT_FORMAT_ASCII != output_format) {
            if (DEBUG_PRINT) qDebug("output_format is invalid! output_format = %s\n",
                                    qPrintable(CommonType::getOutputFormat(TAG, output_format)));
        }
    }

    if (DEBUG_PRINT) qDebug("Enter the function = %s,", "digital_2_ascii");

    QString ret;
    switch (input_format) {
    case INPUT_FORMAT_HEX:
        ret = hex_2_ascii(input);
        break;
    case INPUT_FORMAT_DECIMAL:
        ret = decimal_2_ascii(input);
        break;
    case INPUT_FORMAT_OCT:
        ret = oct_2_ascii(input);
        break;
    case INPUT_FORMAT_BINARY:
        ret = binary_2_ascii(input);
        break;
    default:
        if (DEBUG_PRINT) qDebug("Func name =%s , can not find the output_format function to handle the the request", "digital_2_ascii");
        ret = decimal_2_ascii(input);
        break;
    }
    if (DEBUG_PRINT) qDebug("ret = %s \n", qPrintable(ret));
    if (DEBUG_PRINT) qDebug("exit func = %s\n", "digital_2_ascii");
    return ret;
}

/**
 * @brief CodeFormatter::digital_2_digital
 * @param input_format
 * @param output_format
 * @param input
 * @return
 */
QString CodeFormatter::digital_2_digital
(const int input_format, const int output_format, QString input)
{
    if (input_format <= INPUT_FORMAT_START || input_format >= INPUT_FORMAT_INVALID
            || output_format <= OUTPUT_FORMAT_START || output_format >= OUTPUT_FORMAT_INVALID
            || input.isNull() || input.isEmpty()
            || OUTPUT_FORMAT_ASCII == output_format
            || INPUT_FORMAT_ASCII == input_format)
    {
        qFatal("The parameter is invalid for this function!");
        if (OUTPUT_FORMAT_ASCII != output_format) {
            if (DEBUG_PRINT) qDebug("output_format is invalid! output_format = %s\n",
                                    qPrintable(CommonType::getOutputFormat(TAG, output_format)));
        }
    }

    if (DEBUG_PRINT) qDebug("Enter the function = %s,", "digital_2_digital");

    //get split from the input
    QChar split = getSplit(input);
    if (DEBUG_PRINT) qDebug("Func name = %s, split = %d\n", "digital_2_digital", split.toLatin1());

    QString ret;
    int func_mask = input_format << 8 | output_format;
    switch (func_mask) {
    case MASK_HEX_2_DECIMAIL:
        ret = hex_2_decimal(input);
        break;
    case MASK_HEX_2_OCT:
        ret = hex_2_oct(input);
        break;
    case MASK_HEX_2_BINARY:
        ret = hex_2_binary(input);
        break;
    case MASK_DECIMAL_2_HEX:
        ret = decimal_2_hex(input);
        break;
    case MASK_DECIMAL_2_OCT:
        ret = decimal_2_oct(input);
        break;
    case MASK_DECIMAL_2_BINARY:
        ret = decimal_2_binary(input);
        break;
    case MASK_OCT_2_HEX:
        ret = oct_2_hex(input);
        break;
    case MASK_OCT_2_DECIMAL:
        ret = oct_2_decimal(input);
        break;
    case MASK_OCT_2_BIANRY:
        ret = oct_2_binary(input);
        break;
    case MASK_BINARY_2_HEX:
        ret = binary_2_hex(input);
        break;
    case MASK_BINARY_2_DECIMAL:
        ret = binary_2_decimal(input);
        break;
    case MASK_BINARY_2_OCT:
        ret = binary_2_oct(input);
        break;
    default:
        if (DEBUG_PRINT) qDebug("Func name =%s , can not find the output_format function to handle the the request", "digital_2_digital");
        break;
    }
    if (DEBUG_PRINT) qDebug("ret = %s \n", qPrintable(ret));
    if (DEBUG_PRINT) qDebug("exit func = %s\n", "digital_2_digital");
    return ret;
}

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
        qFatal("parameter is null or empty, func = %s", "hex_2_str");
    }
    if (DEBUG_PRINT) {
        qDebug("Enter the hex_2_str function!");
        qDebug("input_format =%s, output_format=%s, hex_val=%s, split=%x\n",
               qPrintable(CommonType::getInputFormat(getTag(), input_format)),
               qPrintable(CommonType::getOutputFormat(getTag(), output_format)),
               qPrintable(hex_val),
               split.toLatin1());
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
        break;
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
               split.toLatin1());
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
        char c = val.at(i).toLatin1();
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

/**
 * @brief CodeFormatter::getSplit
 * @param input
 * @return
 */
QChar CodeFormatter::getSplit(const QString input)
{
    if (input.isNull() || input.isEmpty()) {
        qFatal("The parameter input is invalid!  input = %s\n", qPrintable(input));
    }
    QChar split;
    //check the split char, skip the 8 char
    if (input.indexOf(',', 8) >= 8) {
        split = ',';
    } else {
        split = ' ';
    }
    if (DEBUG_PRINT) qDebug("getSplit End, split = %c", split.toLatin1());
    return split;
}

/**
 * @brief CodeFormatter::ascii_2_hex
 * @param input
 * @return
 */
QString CodeFormatter::ascii_2_hex(const QString input)
{
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "ascii_2_hex", qPrintable(input));
        }
    }
    QString ret = str_2_hex(INPUT_FORMAT_ASCII, OUTPUT_FORMAT_HEX, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "ascii_2_hex", qPrintable(ret));
    return ret;
}

//From ascii to decimal
QString CodeFormatter::ascii_2_decimal(const QString input)
{
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "ascii_2_decimal", qPrintable(input));
        }
    }
    ret = str_2_hex(INPUT_FORMAT_ASCII, OUTPUT_FORMAT_DECIMAL, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "ascii_2_decimal", qPrintable(ret));
    return ret;
}

//From ascii to oct
QString CodeFormatter::ascii_2_oct(const QString input)
{
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "ascii_2_oct", qPrintable(input));
        }
    }
    ret = str_2_hex(INPUT_FORMAT_ASCII, OUTPUT_FORMAT_OCT, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "ascii_2_oct", qPrintable(ret));
    return ret;
}

//From ascii to binary
QString CodeFormatter::ascii_2_binary(const QString input)
{
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "ascii_2_binary", qPrintable(input));
        }
    }
    ret = str_2_hex(INPUT_FORMAT_ASCII, OUTPUT_FORMAT_BINARY, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "ascii_2_binary", qPrintable(ret));
    return ret;
}

QString CodeFormatter::hex_2_ascii(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "hex_2_ascii", qPrintable(input));
        }
    }
    ret = hex_2_str(INPUT_FORMAT_HEX, OUTPUT_FORMAT_ASCII, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "hex_2_ascii", qPrintable(ret));
    return ret;
}

QString CodeFormatter::decimal_2_ascii(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "decimal_2_ascii", qPrintable(input));
        }
    }
    ret = hex_2_str(INPUT_FORMAT_DECIMAL, OUTPUT_FORMAT_ASCII, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "decimal_2_ascii", qPrintable(ret));
    return ret;
}
QString CodeFormatter::oct_2_ascii(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "oct_2_ascii", qPrintable(input));
        }
    }
    ret = hex_2_str(INPUT_FORMAT_OCT, OUTPUT_FORMAT_ASCII, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "oct_2_ascii", qPrintable(ret));
    return ret;
}

QString CodeFormatter::binary_2_ascii(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "binary_2_ascii", qPrintable(input));
        }
    }
    ret = hex_2_str(INPUT_FORMAT_BINARY, OUTPUT_FORMAT_ASCII, input, getSplit(input));
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s \n", "binary_2_ascii", qPrintable(ret));
    return ret;
}

QString CodeFormatter::hex_2_decimal(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "hex_2_decimal", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,16);
        ret.append(QString::number(tmp, 10));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "hex_2_decimal", qPrintable(ret));
    return ret;
}

QString CodeFormatter::hex_2_oct(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "hex_2_oct", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,16);
        ret.append(QString::number(tmp, 8));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "hex_2_oct", qPrintable(ret));
    return ret;
}

QString CodeFormatter::hex_2_binary(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "hex_2_binary", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,16);
        ret.append(QString::number(tmp, 2));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "hex_2_binary", qPrintable(ret));
    return ret;
}

QString CodeFormatter::decimal_2_hex(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "decimal_2_hex", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,10);
        ret.append(QString::number(tmp, 16));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "decimal_2_hex", qPrintable(ret));
    return ret;
}

QString CodeFormatter::decimal_2_oct(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "decimal_2_oct", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,10);
        ret.append(QString::number(tmp, 8));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "decimal_2_oct", qPrintable(ret));
    return ret;
}

QString CodeFormatter::decimal_2_binary(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "decimal_2_binary", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,10);
        ret.append(QString::number(tmp, 2));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "decimal_2_binary", qPrintable(ret));
    return ret;
}

QString CodeFormatter::oct_2_hex(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "oct_2_hex", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,8);
        ret.append(QString::number(tmp, 16));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "oct_2_hex", qPrintable(ret));
    return ret;
}

QString CodeFormatter::oct_2_decimal(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "oct_2_decimal", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,8);
        ret.append(QString::number(tmp, 10));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "oct_2_decimal", qPrintable(ret));
    return ret;
}

QString CodeFormatter::oct_2_binary(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "oct_2_binary", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,8);
        ret.append(QString::number(tmp, 2));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "oct_2_binary", qPrintable(ret));
    return ret;
}

QString CodeFormatter::binary_2_hex(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "binary_2_hex", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,2);
        ret.append(QString::number(tmp, 16));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "decimal_2_hex", qPrintable(ret));
    return ret;
}

QString CodeFormatter::binary_2_decimal(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "binary_2_decimal", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,2);
        ret.append(QString::number(tmp, 10));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "binary_2_decimail", qPrintable(ret));
    return ret;
}

QString CodeFormatter::binary_2_oct(const QString input) {
    QString ret;
    if (input.isNull() || input.isEmpty()) {
        if (DEBUG_PRINT) {
            qFatal("invalid paramerters func = %s, input = %s\n", "binary_2_oct", qPrintable(input));
        }
    }
    QChar split = getSplit(input);
    QStringList list = input.split(split);
    int tmp = 0;
    ret.clear();
    for (int i = 0; i < list.size(); i++) {
        tmp = list.at(i).toInt(0,2);
        ret.append(QString::number(tmp, 8));
        if (i != (list.size() - 1)) {
            ret.append(' ');
        }
    }
    if (DEBUG_PRINT) qDebug("func = %s, ret = %s\n", "binary_2_oct", qPrintable(ret));
    return ret;
}
