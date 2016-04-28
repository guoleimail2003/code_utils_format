#ifndef CODEFORMATTER_H
#define CODEFORMATTER_H

#include <QObject>
#include <QString>
#include <common_type.h>

class CodeFormatter : public QObject
{
    Q_OBJECT
private:
    static QString TAG;
public:
    explicit CodeFormatter(QObject *parent = 0);

    //get TAG
    static QString getTag();

    //From ascii to char  65 -> 'A'
    QString hex_2_str(const int input_format, const int output_format,
                      const QString hex_val, const QChar split);
    //From char to ascii  'A' -> 65
    QString str_2_hex(const int input_format, const int output_format,
                      const QString hex_val, const QChar split);
    //From decimal to hex
    QString digtal_in_2_out(const int input_format, const int output_format,
                          const QString hex_val, const QChar split);
signals:

public slots:

};

#endif // CODEFORMATTER_H
