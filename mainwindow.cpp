#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

QString MainWindow::TAG = QString("mainwindow");

QString MainWindow::getTag() {
    return TAG;
}

QClipboard* MainWindow::getClipboard() {
    if (!mClipboard) {
        if (DEBUG_PRINT) qDebug("get clipboard pointer!");
        mClipboard = QApplication::clipboard();
    }
    return QApplication::clipboard();
}

void MainWindow::initialControls() {
    //initialization the ui controls.
    mClearInputOutput = ui->clear_input_output;
    mInputEdit = ui->InputEdit;
    mOutputEdit = ui->OutputEdit;

    //input format
    mRadioButtion_Input_Hex = ui->rb_input_hex;
    mRadioButtion_Input_Decimal = ui->rb_input_decimal;
    mRadioButtion_Input_Ascii = ui->rb_input_ascii;
    mRadioButtion_Input_Oct = ui->rb_input_oct;
    mRadioButtion_Input_Binary = ui->rb_input_binary;


    //output format
    mRadioButtion_Output_Hex = ui->rb_output_hex;
    mRadioButtion_Output_Decimal = ui->rb_output_decimal;
    mRadioButtion_Output_Ascii = ui->rb_output_ascii;
    mRadioButtion_Output_Oct = ui->rb_output_oct;
    mRadioButtion_Output_Binary = ui->rb_output_binary;

    //initialization the controls
    mInputFormat = INPUT_FORMAT_HEX;
    mRadioButtion_Input_Hex->setChecked(true);
    mOutputFormat = OUTPUT_FORMAT_ASCII;
    mRadioButtion_Output_Ascii->setChecked(true);
    mRadioButtion_Output_Hex->setDisabled(true);
}

void MainWindow::disableAllRadioButtion() {
    //mRadioButtion_Input_Hex->setDisabled(true);
    //mRadioButtion_Input_Decimal->setDisabled(true);
    //mRadioButtion_Input_Ascii->setDisabled(true);
    //mRadioButtion_Input_Oct->setDisabled(true);
    //mRadioButtion_Input_Binary->setDisabled(true);
    mRadioButtion_Output_Hex->setDisabled(true);
    mRadioButtion_Output_Decimal->setDisabled(true);
    mRadioButtion_Output_Ascii->setDisabled(true);
    mRadioButtion_Output_Oct->setDisabled(true);
    mRadioButtion_Output_Binary->setDisabled(true);
}

//enable all radio buttion control
void MainWindow::enableAllRadioButtion() {
    //mRadioButtion_Input_Hex->setEnabled(true);
    //mRadioButtion_Input_Decimal->setEnabled(true);
    //mRadioButtion_Input_Ascii->setEnabled(true);
    //mRadioButtion_Input_Oct->setEnabled(true);
    //mRadioButtion_Input_Binary->setEnabled(true);
    mRadioButtion_Output_Hex->setEnabled(true);
    mRadioButtion_Output_Decimal->setEnabled(true);
    mRadioButtion_Output_Ascii->setEnabled(true);
    mRadioButtion_Output_Oct->setEnabled(true);
    mRadioButtion_Output_Binary->setEnabled(true);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialControls();

    //check the null pointer
    if (CHECK_NULL_POINTER(mClearInputOutput) || CHECK_NULL_POINTER(mInputEdit)
            || CHECK_NULL_POINTER(mOutputEdit)) {
        qFatal("null pointer detected in initialization");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rb_input_hex_clicked()
{
    mInputFormat = INPUT_FORMAT_HEX;

    //enable the control
    enableAllRadioButtion();
    mRadioButtion_Output_Hex->setDisabled(true);
    mRadioButtion_Output_Ascii->setChecked(true);
    mOutputFormat = OUTPUT_FORMAT_ASCII;
}

void MainWindow::on_rb_input_decimal_clicked()
{
    mInputFormat = INPUT_FORMAT_DECIMAL;
    enableAllRadioButtion();
    mRadioButtion_Output_Decimal->setDisabled(true);
    mRadioButtion_Output_Hex->setChecked(true);
    mOutputFormat = OUTPUT_FORMAT_HEX;
}

void MainWindow::on_rb_input_ascii_clicked()
{
    mInputFormat = INPUT_FORMAT_ASCII;
    enableAllRadioButtion();
    mRadioButtion_Output_Ascii->setDisabled(true);
    mRadioButtion_Output_Hex->setChecked(true);
    mOutputFormat = OUTPUT_FORMAT_HEX;
}

void MainWindow::on_rb_input_oct_clicked()
{
    mInputFormat = INPUT_FORMAT_OCT;
    enableAllRadioButtion();
    mRadioButtion_Output_Oct->setDisabled(true);
    mRadioButtion_Output_Hex->setChecked(true);
    mOutputFormat = OUTPUT_FORMAT_HEX;
}

void MainWindow::on_rb_input_binary_clicked()
{
    mInputFormat = INPUT_FORMAT_BINARY;
    enableAllRadioButtion();
    mRadioButtion_Output_Binary->setDisabled(true);
    mRadioButtion_Output_Hex->setChecked(true);
    mOutputFormat = OUTPUT_FORMAT_HEX;
}

void MainWindow::on_rb_output_decimal_clicked()
{
    mOutputFormat = OUTPUT_FORMAT_DECIMAL;
}

void MainWindow::on_rb_output_hex_clicked()
{
    mOutputFormat = OUTPUT_FORMAT_HEX;
}

void MainWindow::on_rb_output_ascii_clicked()
{
    mOutputFormat = OUTPUT_FORMAT_ASCII;
}

void MainWindow::on_rb_output_oct_clicked()
{
    mOutputFormat = OUTPUT_FORMAT_OCT;
}

void MainWindow::on_rb_output_binary_clicked()
{
    mOutputFormat = OUTPUT_FORMAT_BINARY;
}

void MainWindow::on_copy_to_clipborad_clicked()
{
    QString text;
    if (mOutputEdit) {
        text = mOutputEdit->toPlainText();
    } else {
        qDebug("mOutputEdit == null");
    }
    if (!text.isNull() || !text.isEmpty()) {
        if (DEBUG_PRINT) qDebug("copy text = %s to clipboard", qPrintable(text));
        getClipboard()->setText(text);
    }
}

void MainWindow::on_copy_from_clipborad_clicked()
{
    QString text = getClipboard()->text();
    if (!text.isNull() || !text.isEmpty()) {
        if (DEBUG_PRINT) qDebug("copy text = %s to mInputEdit", qPrintable(text));
        if (mInputEdit) {
            mInputEdit->setPlainText(text);
        } else {
            qDebug("mInputEdit == null");
        }
    }
}

void MainWindow::on_clear_input_output_clicked()
{
     mInputEdit->clear();
     mOutputEdit->clear();
}

void MainWindow::on_translate_clicked()
{
    QString input_text = mInputEdit->toPlainText();
    if (DEBUG_PRINT) {
        qDebug("mInputFormat = %s, mOutputFormat = %s",
               qPrintable(CommonType::getInputFormat(getTag(), mInputFormat)),
               qPrintable(CommonType::getOutputFormat(getTag(), mOutputFormat)));
    }
    QString output;
    if (OUTPUT_FORMAT_ASCII == mOutputFormat) {
        if (DEBUG_PRINT) qDebug("call hex_2_str");
        output = mCodeFormatter.hex_2_str(mInputFormat, mOutputFormat, input_text, QChar(' '));
    } else if (INPUT_FORMAT_ASCII == mInputFormat) {
        if (DEBUG_PRINT) qDebug("call str_2_hex");
        output = mCodeFormatter.str_2_hex(mInputFormat, mOutputFormat, input_text, QChar(' '));
    } else {
        if (DEBUG_PRINT) qDebug("Can not find the method to tranlate mInputFormat = %s mOutputFormat = %s",
                                qPrintable(CommonType::getInputFormat(getTag(), mInputFormat)),
                                qPrintable(CommonType::getOutputFormat(getTag(), mOutputFormat)));
    }
    if (!output.isNull() && !output.isEmpty()) {
        mOutputEdit->setText(output);
    }
}
