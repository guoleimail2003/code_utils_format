#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <common_type.h>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QRadioButton>
#include <QClipboard>
#include <codeformatter.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_clear_input_output_clicked();

    void on_translate_clicked();

    void on_rb_input_hex_clicked();

    void on_rb_input_decimal_clicked();

    void on_rb_input_ascii_clicked();

    void on_rb_input_oct_clicked();

    void on_rb_input_binary_clicked();

    void on_rb_output_decimal_clicked();

    void on_rb_output_hex_clicked();

    void on_rb_output_ascii_clicked();

    void on_rb_output_oct_clicked();

    void on_rb_output_binary_clicked();

    void on_copy_to_clipborad_clicked();

    void on_copy_from_clipborad_clicked();

private:
    Ui::MainWindow *ui;

    QLabel* mInputControl;
    QPushButton* mClearInputOutput;
    QPushButton* mTranslate;
    QTextEdit* mInputEdit;
    QTextEdit* mOutputEdit;

    //input format
    QRadioButton* mRadioButtion_Input_Hex;
    QRadioButton* mRadioButtion_Input_Decimal;
    QRadioButton* mRadioButtion_Input_Ascii;
    QRadioButton* mRadioButtion_Input_Oct;
    QRadioButton* mRadioButtion_Input_Binary;


    //output format
    QRadioButton* mRadioButtion_Output_Hex;
    QRadioButton* mRadioButtion_Output_Decimal;
    QRadioButton* mRadioButtion_Output_Ascii;
    QRadioButton* mRadioButtion_Output_Oct;
    QRadioButton* mRadioButtion_Output_Binary;

    //current status
    int mInputFormat;
    int mOutputFormat;
    static QString TAG;

    //code formatter
    CodeFormatter mCodeFormatter;
    CommonType mCommonType;

    //initial control
    void initialControls();
    //disable radiobutton control
    void disableAllRadioButtion();
    //enable all radio buttion control
    void enableAllRadioButtion();

protected:
    QClipboard* mClipboard;
    QClipboard* getClipboard();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //get TAG
    static QString getTag();

};

#endif // MAINWINDOW_H
