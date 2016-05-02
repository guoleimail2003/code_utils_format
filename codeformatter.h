#ifndef CODEFORMATTER_H
#define CODEFORMATTER_H

#include <QObject>
#include <QString>
#include <QChar>
#include <common_type.h>

class CodeFormatter : public QObject
{
    Q_OBJECT
private:
    static QString TAG;
    QChar mSplit;

    //From ascii to char  65 -> 'A'
    QString hex_2_str(const int input_format, const int output_format,
                      const QString hex_val, const QChar split);
    //From char to ascii  'A' -> 65
    QString str_2_hex(const int input_format, const int output_format,
                      const QString hex_val, const QChar split);

    //get split char from the input
    QChar getSplit(const QString input);
public:
    explicit CodeFormatter(QObject *parent = 0);

    //get TAG
    static QString getTag();

    QString ascii_2_digital(const int input_format, const int output_format, QString input);

    QString digital_2_ascii(const int input_format, const int output_format, QString input);

    QString digital_2_digital(const int input_format, const int output_format, QString input);

    //================ascii to digial =======================

    //From ascii to hex
    QString ascii_2_hex(const QString input);

    //From ascii to decimal
    QString ascii_2_decimal(const QString input);

    //From ascii to oct
    QString ascii_2_oct(const QString input);

    //From ascii to binary
    QString ascii_2_binary(const QString input);

    //================digital to ascii =======================

    //From hex to ascii
    QString hex_2_ascii(const QString input);

    //From decimal to ascii
    QString decimal_2_ascii(const QString input);

    //From oct to ascii
    QString oct_2_ascii(const QString input);

    //From binary to ascii
    QString binary_2_ascii(const QString input);

    //================digital to digital =======================
    //From hex to decimal
    QString hex_2_decimail(const QString input);

    //From hex to oct
    QString hex_2_oct(const QString input);

    //From hex to binary
    QString hex_2_binary(const QString input);

    //From decimal to hex
    QString decimal_2_hex(const QString input);

    //From decimal to oct
    QString decimal_2_oct(const QString input);

    //From decimal to binary
    QString decimal_2_binary(const QString input);

    //From oct to hex
    QString oct_2_hex(const QString input);

    //From oct to decimal
    QString oct_2_decimail(const QString input);

    //From oct to binary
    QString oct_2_binary(const QString input);

    //From binary to hex
    QString binary_2_hex(const QString input);

    //From binary to decimal
    QString binary_2_decimail(const QString input);

    //From binary to oct
    QString binary_2_oct(const QString input);


    QString digital_in_2_out(const int input_format, const int output_format,
                          const QString hex_val, const QChar split);
signals:

public slots:

};

#endif // CODEFORMATTER_H
