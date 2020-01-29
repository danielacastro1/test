//Daniela Castro
#include <QMessageBox>
#include <QStringBuilder>


#include "mainwindow.h"
#include "ui_mainwindow.h"


const double ROOM_PRICES[] = {284, 325, 290, 350};
const double PARKING_PRICE = 12.75;
const double TAX_RATE = 15;
const double RESORT_FEE = 15;

const QStringList CREDIT_CARD_MASKS = {
    "4999-9999-9999-9999",
    "5999-9999-9999-9999",
    "6999-9999-9999-9999",
    "3999-999999-99999",

};

//settin up mask constructors
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->creditCardLineEdit->setInputMask(CREDIT_CARD_MASKS.at(0));

    this->calculatePreviewPrice();

    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(365));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculatePreviewPrice()
{
    bool isQueen = this->ui->queenRadio->isChecked();
    bool isStandard = this->ui->standardRadio->isChecked();
    int index = 0;

    if(!isQueen)
        index = 2;
    if(!isStandard)
        index++;

    double price = ROOM_PRICES[index];
    bool hasParking = this->ui->parkingCheckBox->isChecked();

    if(hasParking)
        price = price + PARKING_PRICE;

    int nights = this->ui->nightsSpinBox->value();
    price = price * nights;

    QLocale* locale = new QLocale("en_US");

    this->ui->priceLabel->setText(locale->toString(price));
}

void MainWindow::on_queenRadio_toggled(bool checked)
{
    this->calculatePreviewPrice();
}

void MainWindow::on_standardRadio_toggled(bool checked)
{
    this->calculatePreviewPrice();
}

void MainWindow::on_nightsSpinBox_valueChanged(int arg1)
{
    this->calculatePreviewPrice();
}

void MainWindow::on_parkingCheckBox_stateChanged(int arg1)
{
    this->calculatePreviewPrice();
}

//page 1
void MainWindow::on_nextPushButton_clicked()
{
    QLocale* locale = new QLocale("en_US");

    if(ui->customerName->text().length() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Please include a name for your reservation.");
        msgBox.exec();

        return;
    }

    bool isQueen = this->ui->queenRadio->isChecked();
    bool isStandard = this->ui->standardRadio->isChecked();
    int index = 0;

    QString bedType = "2-Queen";
    QString viewType = "Standard";

    if(!isQueen) {

        index = 2;
        bedType = "1-King";
    }

    if(!isStandard) {
        index++;
        viewType = "Atrium";
    }

    double price = ROOM_PRICES[index];
    int nights = this->ui->nightsSpinBox->value();
    double roomPrice = price * nights;
    double tax = roomPrice * TAX_RATE/100;
    QString parkingString = "No";
    bool hasParking = this->ui->parkingCheckBox->isChecked();

    double parking = 0;
    if(hasParking) {
        parkingString = "Yes";
        parking = PARKING_PRICE * nights;
    }

    int adults = this->ui->adultBox->value();
    int children = this->ui->childrenBox->value();
    int totalGuests = adults + children;
    QString guests = locale->toString(adults);
    if(adults == 1)
        guests = guests % " Adult";
    else
        guests = guests % " Adults";
    if(children == 1)
        guests = guests % " " % locale->toString(children) % " Child";
    else if(children > 0)
        guests = guests % " " % locale->toString(children) % " Children";

    if(isQueen && totalGuests > 4) {
        QMessageBox msgBox;
        msgBox.setText("This room type accommodates no more than 4 guests. Please try again.");
        msgBox.exec();

        return;
    }

    if(!isQueen && totalGuests > 3) {
        QMessageBox msgBox;
        msgBox.setText("This room type accommodates no more than 3 guests. Please try again.");
        msgBox.exec();

        return;
    }






    double resort = RESORT_FEE * nights;

    double total = roomPrice + tax + parking + resort;

    QDate date = this->ui->dateEdit->date();

    this->ui->roomCostLabel->setText(locale->toString(roomPrice));
    this->ui->taxLabel->setText(locale->toString(tax));
    this->ui->parkingLabel->setText(locale->toString(parking));
    this->ui->resortLabel->setText(locale->toString(resort));
    this->ui->totalCostLabel->setText(locale->toString(total));

    this->ui->firstDayLabel->setText("");
    this->ui->numberOfNightsLabel->setText(locale->toString(nights));
    this->ui->roomTypeLabel->setText(bedType % " " % viewType);
    this->ui->parkingLabel_2->setText(parkingString);
    this->ui->guestsLabel->setText(guests);
    this->ui->totalCostLabel_2->setText(locale->toString(total));
    this->ui->firstDayLabel->setText(date.toString("MM/dd/yyyy"));







    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_backPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
//setting mask
void MainWindow::on_visaRadio_toggled(bool checked)
{
    if (!checked)
        return;
    ui->creditCardLineEdit->setInputMask(CREDIT_CARD_MASKS.at(0));
    ui->creditCardLineEdit->clear();


}

void MainWindow::on_masterCardRadio_toggled(bool checked)
{
    if (!checked)
        return;
    ui->creditCardLineEdit->setInputMask(CREDIT_CARD_MASKS.at(1));
    ui->creditCardLineEdit->clear();

}

void MainWindow::on_discoverRadio_toggled(bool checked)
{
    if (!checked)
        return;
    ui->creditCardLineEdit->setInputMask(CREDIT_CARD_MASKS.at(2));
    ui->creditCardLineEdit->clear();

}

void MainWindow::on_americaexpressRadio_toggled(bool checked)
{
    if (!checked)
        return;
    ui->creditCardLineEdit->setInputMask(CREDIT_CARD_MASKS.at(3));
    ui->creditCardLineEdit->clear();

}
//box message, confirming payment
void MainWindow::on_payPushButton_clicked()
{
    QMessageBox msgBox;
    int creditCardLength = 19;

    if(ui->americaexpressRadio->isChecked())
        creditCardLength = 17;
    if(ui->creditCardLineEdit->text().length() != creditCardLength){
        msgBox.setText("Please check your credit card number and try again.");
        msgBox.exec();

        return;
    }

    msgBox.setText("Your transaction has been successfully processed!");
    msgBox.exec();

    QString creditCard = ui->creditCardLineEdit->text();
    QString fourDigits = creditCard.right(4);

    ui->creditCardDigitsLabel->setText(fourDigits);
    ui->stackedWidget->setCurrentIndex(2);



}

//page 3
void MainWindow::on_confirmPushButton_clicked()
{
    QMessageBox thankYou;
    thankYou.setText("Thank you for your reservation. We hope you enjoy your stay!");
    thankYou.exec();
    QApplication::quit();
  }

//fin
