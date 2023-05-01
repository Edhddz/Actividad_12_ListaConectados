#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QString>
#include <fstream>
#include <QFileDialog>

#define NOMBRE_ARCHIVO "Neuronas.txt"
#define DELIMITADOR_CAMPO '|'
#define DELIMITADOR_REGISTRO '\n'

QString input;
AdministradoraNeurona admiNeurona;

struct datosNeurona
{
    int id = C_0;
    int posX = C_0;
    int posY = C_0;
    int r = C_0;
    int g = C_0;
    int b = C_0;
    float voltaje = C_0;
}dNeurona;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //enableDarkMode(); //Dark mode ;)
}

MainWindow::~MainWindow(){delete ui;}

//Métodos Clase Nerona
Neurona::Neurona(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red, int& green,
                 int& blue)
{
    if(id > C_0){this->setId(id);}
    if(voltaje > C_0){this->setVoltaje(voltaje);}
    this->setPosicionX(posicion_x);
    this->setPosicionY(posicion_y);
    if(red > C_0){this->setRed(red);}
    if(green > C_0){this->setGreen(green);}
    if(blue > C_0){this->setBlue(blue);}
}

Neurona::Neurona()
{
    this->id = C_0;
    this->voltaje = C_0;
    this->posicion_x = C_0;
    this->posicion_y = C_0;
    this->red = C_0;
    this->green = C_0;
    this->blue = C_0;
}

std::string Neurona::printNeurona()
{
    std::stringstream ss;
    ss << "ID: " << this->getId() <<std::endl
       << "Voltaje: " << this->getVoltaje() <<std::endl
       << "Posicion X: " << this->getPosicionX() <<std::endl
       << "Posicion Y: " << this->getPosicionY() <<std::endl
       << "Red: " << this->getRed() <<std::endl
       << "Green: " << this->getGreen() <<std::endl
       << "Blue: " << this->getBlue() <<std::endl <<std::endl;

    return ss.str();
}
std::string Neurona::getInfoNeurona()
{
    std::stringstream ss;

    ss << this->getId() << DELIMITADOR_CAMPO << this->getVoltaje() << DELIMITADOR_CAMPO
       << this->getPosicionX() << DELIMITADOR_CAMPO << this->getPosicionY() << DELIMITADOR_CAMPO
       << this->getRed() << DELIMITADOR_CAMPO << this->getGreen() << DELIMITADOR_CAMPO
       << this->getBlue() << DELIMITADOR_REGISTRO;

    return ss.str();
}

//Métodos Clase AdministradoraNeurona
void AdministradoraNeurona::agregarFinal(int& id, float& voltaje, int& posicion_x, int& posicion_y,
                                          int& red, int& green, int& blue)
{
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->neurona = new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue);
    nuevoNodo->siguiente = NULL;

    if(inicio == NULL){inicio = nuevoNodo;}
    else
    {
        Nodo* temp = inicio;
        while (temp->siguiente != NULL){temp = temp->siguiente;}
        temp->siguiente = nuevoNodo;
    }
    contadorNeuronas++;
}
int AdministradoraNeurona::calcularDistanciaEntrePuntos(int& x1, int& y1, int& x2, int& y2)
{
    int x3 = x2-x1;
    int y3 = y2-y1;

    return (int) sqrt(pow(x3, 2) + pow(y3, 2));
}

void AdministradoraNeurona::agregarInicio(int& id, float& voltaje, int& posicion_x, int& posicion_y,
                                         int& red, int& green, int& blue)
{
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->neurona = new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue);
    nuevoNodo->siguiente = NULL;

    if(inicio == NULL){inicio = nuevoNodo;}
    else
    {
        nuevoNodo->siguiente = inicio;
        inicio = nuevoNodo;
    }
    contadorNeuronas++;
}

int AdministradoraNeurona::searchNeurona(int neuronaABuscar)
{
    Nodo* nodoTemporal = inicio;

    for(int i = C_0; i<contadorNeuronas && nodoTemporal != NULL; i++)
    {
        if(nodoTemporal->neurona->getId() == neuronaABuscar){return i;}
        nodoTemporal = nodoTemporal->siguiente;
    }
    return -1;
}

void AdministradoraNeurona::sortNeuronas(bool tipoOrdenamiento)
{
    Nodo* nodoTemporalL;
    Nodo* nodoTemporalR = NULL;
    int cambiado;

    do
    {
        cambiado = C_0;
        nodoTemporalL = inicio;

        if(tipoOrdenamiento)
        {
            while (nodoTemporalL->siguiente != nodoTemporalR) {
                if(nodoTemporalL->neurona->getId() > nodoTemporalL->siguiente->neurona->getId())
                {
                    intercambiaDatosNeurona(nodoTemporalL, nodoTemporalL->siguiente);
                    cambiado = 1;
                }
                nodoTemporalL = nodoTemporalL->siguiente;
            }
        }
        else
        {
            while (nodoTemporalL->siguiente != nodoTemporalR) {
                if(nodoTemporalL->neurona->getVoltaje() > nodoTemporalL->siguiente->neurona->getVoltaje())
                {
                    intercambiaDatosNeurona(nodoTemporalL, nodoTemporalL->siguiente);
                    cambiado = 1;
                }
                nodoTemporalL = nodoTemporalL->siguiente;
            }
        }
    }while(cambiado);
    nodoTemporalL = NULL;
}

void AdministradoraNeurona::intercambiaDatosNeurona(Nodo* nodo1, Nodo* nodo2)
{
    Neurona* temp = nodo1->neurona;
    nodo1->neurona = nodo2->neurona;
    nodo2->neurona = temp;
}

int AdministradoraNeurona::dibujarConexionesCercanas(int& pos, int& x1, int& y1, int& x2, int& y2)
{
    int indMenor = C_0;
    int arregloDistancias[contadorNeuronas];
    int i = C_0;
    int j = C_0;

    while (i < contadorNeuronas){arregloDistancias[i++] = C_0;}

    recuperaCoordenadaNeurona(pos, x1, y1);

    for(j = C_0; j < contadorNeuronas; j++)//Obtener distancia entre puntos
    {
        if(j == pos){continue;}
        else
        {
            recuperaCoordenadaNeurona(j, x2, y2);
            arregloDistancias[j] = calcularDistanciaEntrePuntos(x1, y1, x2, y2);
        }
    }

    for(i = C_0; i < contadorNeuronas; i++)//Encontrar indice menor
    {
        if(arregloDistancias[indMenor] == C_0)
        {
            indMenor++;
            i++;
            if(arregloDistancias[i] < arregloDistancias[indMenor])
            {
                indMenor = i;
            }
        }
        else if(arregloDistancias[i] == C_0 && i == contadorNeuronas-1)
        {
            continue;
        }
        else if(arregloDistancias[i] == C_0)
        {
            i++;
            if(arregloDistancias[i] < arregloDistancias[indMenor])
            {
                indMenor = i;
            }
        }
        else
        {
            if(arregloDistancias[i] < arregloDistancias[indMenor])
            {
                indMenor = i;
            }
        }
    }
    conectar(getIdNeurona(pos), getIdNeurona(indMenor));
    return indMenor;
}

void AdministradoraNeurona::recuperaCoordenadaNeurona(int& pos, int& posX, int& posY)
{
    Nodo* nodoTemporal = inicio;

    for(int i = C_0; i<contadorNeuronas && nodoTemporal != NULL; i++)
    {
        if(i == pos)
        {
            posX = nodoTemporal->neurona->getPosicionX();
            posY = nodoTemporal->neurona->getPosicionY();
        }
        nodoTemporal = nodoTemporal->siguiente;
    }
}

void AdministradoraNeurona::recuperaNeurona(int& pos, int& id, float& voltaje, int& posX, int& posY,
                                            int& red, int& green, int& blue)
{
    Nodo* nodoTemporal = inicio;

    for(int i = C_0; i<contadorNeuronas && nodoTemporal != NULL; i++)
    {
        if(i == pos)
        {
            id = nodoTemporal->neurona->getId();
            voltaje = nodoTemporal->neurona->getVoltaje();
            posX = nodoTemporal->neurona->getPosicionX();
            posY = nodoTemporal->neurona->getPosicionY();
            red = nodoTemporal->neurona->getRed();
            green = nodoTemporal->neurona->getGreen();
            blue = nodoTemporal->neurona->getBlue();
        }
        nodoTemporal = nodoTemporal->siguiente;
    }
}

int AdministradoraNeurona::getContadorNeuronas(){return contadorNeuronas;}

void AdministradoraNeurona::setContadorNeuronas(int& contador){contadorNeuronas = contador;}

int AdministradoraNeurona::getIdNeurona(int& pos)
{
    Nodo* nodoTemporal = inicio;

    for(int i = C_0; i<contadorNeuronas && nodoTemporal != NULL; i++)
    {
        if(i == pos)
        {
            return nodoTemporal->neurona->getId();
        }
        nodoTemporal = nodoTemporal->siguiente;
    }
    return -1;
}

QString AdministradoraNeurona::guardarNeuronas()
{
    std::ofstream archivoNeuronas;
    std::stringstream ss;

    if(contadorNeuronas > C_0)
    {
        archivoNeuronas.open(NOMBRE_ARCHIVO, std::ios::out);
        if(archivoNeuronas.is_open())
        {
            Nodo* nodoTemporal = inicio;
            ss << contadorNeuronas << DELIMITADOR_CAMPO;
            for(int i = C_0; i<contadorNeuronas && nodoTemporal != NULL; i++)
            {
                ss << nodoTemporal->neurona->getInfoNeurona();
                nodoTemporal = nodoTemporal->siguiente;
            }
            archivoNeuronas << ss.str();
            ss.str(std::string()); //Vacía el contenido del Stringstream
            ss << "Neuronas registradas en el archivo " << NOMBRE_ARCHIVO;

            return QString::fromStdString(ss.str());
        }
        else {ss.str(std::string()); ss << "No fue posible abrir el archivo...";}
        archivoNeuronas.close();
    }
    else{ss << "No hay neuronas registradas";}

    return QString::fromStdString(ss.str());
}

QString AdministradoraNeurona::cargarNeuronas()
{
    std::ifstream archivoNeuronas;
    int contadorNeuronas = C_0;
    int id, pos_X, pos_Y, red, green, blue, pos;
    float voltaje;
    char delimCampo;
    std::string cadena, subcadena;

    QString fName = QFileDialog::getOpenFileName();

    archivoNeuronas.open(fName.toStdString());
    if(archivoNeuronas)
    {
        archivoNeuronas >> contadorNeuronas;
        archivoNeuronas >> delimCampo;
        admiNeurona.setContadorNeuronas(contadorNeuronas);
        for(int i = C_0; i < contadorNeuronas; i++)
        {
            std::getline(archivoNeuronas, cadena);

            pos = cadena.find_first_of(DELIMITADOR_CAMPO, C_0);
            subcadena = cadena.substr(C_0, pos);
            id = std::stoi(subcadena);
            cadena = cadena.substr(pos+1);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO, C_0);
            subcadena = cadena.substr(C_0, pos);
            voltaje = std::stof(subcadena);
            cadena = cadena.substr(pos+1);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(C_0, pos);
            pos_X = std::stoi(subcadena);
            cadena = cadena.substr(pos+1);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(C_0, pos);
            pos_Y = std::stoi(subcadena);
            cadena = cadena.substr(pos+1);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(C_0, pos);
            red = std::stoi(subcadena);
            cadena = cadena.substr(pos+1);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(C_0, pos);
            green = std::stoi(subcadena);
            cadena = cadena.substr(pos+1);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(C_0, pos);
            blue = std::stoi(subcadena);

            admiNeurona.agregarFinal(id, voltaje, pos_X, pos_Y, red, green, blue);
        }
        setContadorNeuronas(contadorNeuronas);
        return "Se han cargado las neuronas desde el archivo";
    }
    else {
        return "No se abrio el archivo";
    }
}

void AdministradoraNeurona::conectar(int vertex, int edge)
{
    Nodo* tempLista = inicio;
    Nodo* tempConectado;
    Nodo* nuevoNodo = new Nodo();

    nuevoNodo->neurona = new Neurona();
    nuevoNodo->neurona->setId(edge);

    while(tempLista != nullptr)
    {
        if(tempLista->neurona->getId() == vertex){break;}
        tempLista = tempLista->siguiente;
    }

    tempConectado = tempLista;

    while(tempConectado != nullptr)
    {
        if(tempConectado->conexionCercana == nullptr){tempConectado->conexionCercana = nuevoNodo; std::cout << "Conectado" << tempConectado->neurona->getId() << " " << tempConectado->conexionCercana->neurona->getId() <<std::endl; break;}
        tempConectado = tempConectado->conexionCercana;
    }
    delete nuevoNodo;


}

void MainWindow::enableDarkMode()
{
    this->setStyleSheet("background-color: #434343;");// Set background color
    // Set's labels colors
    ui->IDLabel->setStyleSheet("color: white;");
    ui->VoltLabel->setStyleSheet("color: white;");
    ui->PosLabel->setStyleSheet("color: white;");
    ui->XLabel->setStyleSheet("color: white;");
    ui->YLabel->setStyleSheet("color: white;");
    ui->ColorLabel->setStyleSheet("color: white;");
    ui->RLabel->setStyleSheet("color: white;");
    ui->GLabel->setStyleSheet("color: white;");
    ui->BLabel->setStyleSheet("color: white;");
    ui->IDSearchLabel->setStyleSheet("color: white;");
    // Set's LineEdits colors
    ui->IDLineEdit->setStyleSheet("color: white;");
    ui->VoltLineEdit->setStyleSheet("color: white;");
    ui->PosXLineEdit->setStyleSheet("color: white;");
    ui->PosYLineEdit->setStyleSheet("color: white;");
    ui->ColorRLineEdit->setStyleSheet("color: white;");
    ui->ColorGLineEdit->setStyleSheet("color: white;");
    ui->ColorBLineEdit->setStyleSheet("color: white;");
    ui->IDSearchLineEdit->setStyleSheet("color: white;");
    // Set's PushButtons colors
    ui->BegginInsertPushButton->setStyleSheet("color: white;");
    ui->EndInsertPushButton->setStyleSheet("color: white;");
}

//Interacción con la interfaz
void MainWindow::on_InserPushButton_clicked() //Recupera la información de los LineTextEdit
{
    int id, posX, posY, r, g, b;
    float voltaje;
    bool dataError;

    ui->IDLineEdit->setInputMask(0000); //Establece un InputMask para aceptar números únicamente
    ui->VoltLineEdit->setInputMask(0000);
    ui->PosXLineEdit->setInputMask(0000);
    ui->PosYLineEdit->setInputMask(0000);
    ui->ColorRLineEdit->setInputMask(0000);
    ui->ColorGLineEdit->setInputMask(0000);
    ui->ColorBLineEdit->setInputMask(0000);

    if(datosCorrectos())
    {
        id = ui->IDLineEdit->text().toInt(); //ID
        voltaje = ui->VoltLineEdit->text().toFloat(); //Voltaje
        posX = ui->PosXLineEdit->text().toInt(); //Posicion X
        posY = ui->PosYLineEdit->text().toInt(); //Posicion Y
        r = ui->ColorRLineEdit->text().toInt(); //Color Rojo
        g = ui->ColorGLineEdit->text().toInt(); //Color Verde
        b = ui->ColorBLineEdit->text().toInt(); //Color Azul
        int i = C_0;

        if(ui->BegginInsertPushButton->isChecked())
        {
            admiNeurona.agregarInicio(id, voltaje, posX, posY, r, g, b);
            ui->InfoDisplay->insertPlainText("Neurona creada!\n");
        }
        else if(ui->EndInsertPushButton->isChecked())
        {
            admiNeurona.agregarFinal(id, voltaje, posX, posY, r, g, b);
            ui->InfoDisplay->insertPlainText("Neurona creada!\n");
        }
        else
        {
            ui->InfoDisplay->insertPlainText("Selecciona la ubicación en la que deseas guardar la "
                                               "neurona");
        }
        ui->IDLineEdit->clear();
        ui->VoltLineEdit->clear();
        ui->PosXLineEdit->clear();
        ui->PosYLineEdit->clear();
        ui->ColorRLineEdit->clear();
        ui->ColorGLineEdit->clear();
        ui->ColorBLineEdit->clear();
    }
    else {
        ui->InfoDisplay->setPlainText("Verifica la información, sólo se aceptan números...");
    }

}

void MainWindow::on_ShowNPushButton_clicked() //Botón Mostrar Neuronas
{
    int contadorNeuronas = admiNeurona.getContadorNeuronas();

    if(contadorNeuronas > C_0)
    {
        ui->tableWidget->setEnabled(true);
        while(ui->tableWidget->rowCount() < contadorNeuronas){
            ui->tableWidget->insertRow(1);
        }

        for(int i = C_0; i < contadorNeuronas; i++)
        {
            int x;
            admiNeurona.recuperaNeurona(i, dNeurona.id, dNeurona.voltaje, x, dNeurona.posY,
                                        dNeurona.r, dNeurona.g, dNeurona.b);

            QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(dNeurona.id));
            QTableWidgetItem* voltItem = new QTableWidgetItem(QString::number(dNeurona.voltaje));
            QTableWidgetItem* posXItem = new QTableWidgetItem(QString::number(x));
            QTableWidgetItem* posYItem = new QTableWidgetItem(QString::number(dNeurona.posY));
            QTableWidgetItem* rItem = new QTableWidgetItem(QString::number(dNeurona.r));
            QTableWidgetItem* gItem = new QTableWidgetItem(QString::number(dNeurona.g));
            QTableWidgetItem* bItem = new QTableWidgetItem(QString::number(dNeurona.b));

            ui->tableWidget->setItem(i,C_0, idItem);
            ui->tableWidget->setItem(i,1, voltItem);
            ui->tableWidget->setItem(i,2, posXItem);
            ui->tableWidget->setItem(i,3, posYItem);
            ui->tableWidget->setItem(i,4, rItem);
            ui->tableWidget->setItem(i,5, gItem);
            ui->tableWidget->setItem(i,6, bItem);
        }
    }
    else
        ui->InfoDisplay->setPlainText("NO hay neuronas registradas");
}

void MainWindow::on_CleanPushNutton_clicked() //Borra el contenido de los campos LineTextEdit
{
    ui->IDLineEdit->clear();
    ui->VoltLineEdit->clear();
    ui->PosXLineEdit->clear();
    ui->PosYLineEdit->clear();
    ui->ColorRLineEdit->clear();
    ui->ColorGLineEdit->clear();
    ui->ColorBLineEdit->clear();
}

bool MainWindow::datosCorrectos() //Verifica que los valores ingresados sean todos válidos, numéricos en éste caso
{
    if(ui->IDLineEdit->hasAcceptableInput() && ui->VoltLineEdit->hasAcceptableInput() &&
       ui->PosXLineEdit->hasAcceptableInput() && ui->PosYLineEdit->hasAcceptableInput() &&
       ui->ColorRLineEdit->hasAcceptableInput() && ui->ColorGLineEdit->hasAcceptableInput() &&
       ui->ColorBLineEdit->hasAcceptableInput()) return true;
    else {return false;}
}

void MainWindow::on_SavePushButton_clicked() //Botón de Respaldar Neuronas
{
    ui->InfoDisplay->setPlainText(admiNeurona.guardarNeuronas());
}

void MainWindow::on_LoadPushButton_clicked() //Botón de Cargar Neuronas
{
    ui->InfoDisplay->setPlainText(admiNeurona.cargarNeuronas());
}

void MainWindow::on_SearchPushButton_clicked()
{
    int pos;
    ui->tableWidget->clear();
    while (ui->tableWidget->rowCount() != 1) {
        ui->tableWidget->removeRow(1);
    }

    pos = admiNeurona.searchNeurona(ui->IDSearchLineEdit->text().toInt());

    if(pos != -1)
    {
        ui->tableWidget->setEnabled(true);
        ui->InfoDisplay->setPlainText("Neurona ENCONTRADA...");
        admiNeurona.recuperaNeurona(pos, dNeurona.id, dNeurona.voltaje, dNeurona.posX, dNeurona.posY,
                                    dNeurona.r, dNeurona.g, dNeurona.b);
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(dNeurona.id));
        QTableWidgetItem* voltItem = new QTableWidgetItem(QString::number(dNeurona.voltaje));
        QTableWidgetItem* posXItem = new QTableWidgetItem(QString::number(dNeurona.posX));
        QTableWidgetItem* posYItem = new QTableWidgetItem(QString::number(dNeurona.posY));
        QTableWidgetItem* rItem = new QTableWidgetItem(QString::number(dNeurona.r));
        QTableWidgetItem* gItem = new QTableWidgetItem(QString::number(dNeurona.g));
        QTableWidgetItem* bItem = new QTableWidgetItem(QString::number(dNeurona.b));

        ui->tableWidget->setItem(C_0,C_0, idItem);
        ui->tableWidget->setItem(C_0,1, voltItem);
        ui->tableWidget->setItem(C_0,2, posXItem);
        ui->tableWidget->setItem(C_0,3, posYItem);
        ui->tableWidget->setItem(C_0,4, rItem);
        ui->tableWidget->setItem(C_0,5, gItem);
        ui->tableWidget->setItem(C_0,6, bItem);
    }
    else{ui->InfoDisplay->setPlainText("No se encontró la neurona..."); ui->tableWidget->setEnabled(false);}
}

void MainWindow::on_DibujarNPushButton_clicked()
{
    QPen pen;
    QColor colorNeurona;
    int contadorNeurona = admiNeurona.getContadorNeuronas();

    if(contadorNeurona > C_0)
    {
        for(int i = C_0; i < contadorNeurona; i++)
        {
            admiNeurona.recuperaNeurona(i, dNeurona.id, dNeurona.voltaje, dNeurona.posX,
                                        dNeurona.posY, dNeurona.r, dNeurona.g, dNeurona.b);
            colorNeurona.setRgb(dNeurona.r, dNeurona.g, dNeurona.b);
            escena->addEllipse(dNeurona.posX, dNeurona.posY, dNeurona.voltaje, dNeurona.voltaje,
                               pen, QBrush(QColor(colorNeurona)));
        }
        ui->graphicsView->setScene(escena);
    }
}

void MainWindow::on_LimpiarPanPushButton_clicked(){escena->clear();}

void MainWindow::on_pushButton_clicked()
{
    if(admiNeurona.getContadorNeuronas() > C_0){admiNeurona.sortNeuronas(true);}
    else{ui->InfoDisplay->setPlainText("No hay neuronas registradas..."); ui->tableWidget->setEnabled(false);}
}

void MainWindow::on_pushButton_2_clicked()
{
    if(admiNeurona.getContadorNeuronas() > C_0){admiNeurona.sortNeuronas(false);}
    else{ui->InfoDisplay->setPlainText("No hay neuronas registradas..."); ui->tableWidget->setEnabled(false);}
}

void MainWindow::on_pushButton_3_clicked()
{
    int x1, y1, x2, y2, pos;
    int contadorNeuronas = admiNeurona.getContadorNeuronas();

    if(admiNeurona.getContadorNeuronas() > C_0)
    {
        for(int i = C_0; i < contadorNeuronas; i++)
        {
            pos = admiNeurona.dibujarConexionesCercanas(i, x1, y1, x2, y2);

            QGraphicsTextItem* textItem = new QGraphicsTextItem(QString::number(admiNeurona.getIdNeurona(i)));
            textItem->setFont(QFont("Consolas", 12));
            textItem->setTextWidth(50);
            textItem->setPos(QPoint(x1,y1));
            admiNeurona.recuperaCoordenadaNeurona(pos, x2, y2);


            escena->addItem(textItem);
            escena->addLine(x1, y1, x2, y2);
        }
    }
    else {ui->InfoDisplay->setPlainText("No hay neuronas registradas...");}
}
