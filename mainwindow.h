#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QColor>
#include <QPainter>
#include <QGraphicsTextItem>

#define C_0 0

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ShowNPushButton_clicked();
    void on_InserPushButton_clicked();
    void on_CleanPushNutton_clicked();
    void on_SavePushButton_clicked();
    void on_LoadPushButton_clicked();
    void on_SearchPushButton_clicked();
    void on_DibujarNPushButton_clicked();
    void on_LimpiarPanPushButton_clicked();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    bool datosCorrectos();
    QGraphicsScene *escena = new QGraphicsScene();
    void enableDarkMode();
};
#endif // MAINWINDOW_H

class Neurona
{
    int id;
    float voltaje;
    int posicion_x;
    int posicion_y;
    int red;
    int green;
    int blue;

public:
    Neurona(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red, int& green,
            int& blue);
    Neurona();

    void setId(int id){this->id = id;}
    int getId(){return id;}

    void setVoltaje(float voltaje){this->voltaje = voltaje;}
    float getVoltaje(){return voltaje;}

    void setPosicionX(int posicion_x){this->posicion_x = posicion_x;}
    int getPosicionX(){return posicion_x;}

    void setPosicionY(int posicion_y){this->posicion_y = posicion_y;}
    int getPosicionY(){return posicion_y;}

    void setRed(int red){this->red = red;}
    int getRed(){return red;}

    void setGreen(int green){this->green = green;}
    int getGreen(){return green;}

    void setBlue(int blue){this->blue = blue;}
    int getBlue(){return blue;}

    std::string printNeurona();
    std::string getInfoNeurona();
};

class Nodo
{
public:
    Neurona* neurona;
    Nodo* siguiente;
    Nodo* conexionCercana;
};

class AdministradoraNeurona
{
    Nodo* inicio;
    int contadorNeuronas = 0;
    int calcularDistanciaEntrePuntos(int& x1, int& y1, int& x2, int& y2);

public:
    void agregarInicio(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red,
                       int& green, int& blue);
    void agregarFinal(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red,
                      int& green, int& blue);
    void recuperaNeurona(int& pos, int& id, float& voltaje, int& posX, int& posY, int& red, int& green, int& blue);
    void recuperaCoordenadaNeurona(int& pos, int& posX, int& posY);
    void setContadorNeuronas(int& contador);
    int getContadorNeuronas();
    int searchNeurona(int neuronaABuscar);
    QString guardarNeuronas();
    QString cargarNeuronas();
    void sortNeuronas(bool tipoOrdenamiento);
    void intercambiaDatosNeurona(Nodo* nodo1, Nodo* nodo2);
    int dibujarConexionesCercanas(int& pos, int& x1, int& y1, int& x2, int& y2);
    int getIdNeurona(int& pos);
    void conectar(int vertex, int edge);
    float getVoltaje(int& pos);
};
