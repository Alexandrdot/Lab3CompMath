#define GL_SILENCE_DEPRECATION


#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include "Methods.h"
#include "Charts.h"
#include <GLUT/glut.h>

using namespace std;

bool Check(vector<vector<float>> Dots){
    for (int i = 0; i < Dots.size() - 1; i++){
        for (int j = i + 1; j < Dots.size(); j++){
            if (Dots[i][0] == Dots[j][0]){
                return false;
            }
        }
    }
    return true;
}

void MyMenu(){
    string path = "/Users/aleksandr/Desktop/files/4 семестр/Вычислительная математика/3 лабораторная/lab3.txt"; ///<-- путь к файлу
    
    float x, y;
    char choice;
    bool running = true;
    Methods methods;
    Charts chart;
    
    while(running) {
        cout << "\nМеню:" << endl;
        cout << "1. Интерполяционный многочлен Ньютона" << endl;
        cout << "2. Интерполяционный многочлен Лагранжа" << endl;
        cout << "3. Сглаживающие многочлены 1 степени" << endl;
        cout << "4. Сглаживающие многочлены 2 степени" << endl;
        cout << "5. Сглаживающие многочлены 3 степени" << endl;
        cout << "6. Построение графика полинома 4 степени" << endl;
        cout << "7. Убрать графики" << endl;
        cout << "ESC. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        vector<vector<float>> Dots; //точки
        ifstream myFile(path);  //файл
        while (myFile >> x >> y)
            Dots.push_back({x, y});
        myFile.close();
        
        sort(Dots.begin(), Dots.end()); //сортировка
        
        bool check = Check(Dots);
        if (!check){
            cout << "Обнаружено совпадение х. Измените таблицу значений!" << endl;
            continue;
        }
        
        switch (choice) {
            case '1':
                cout << "Выбран Интерполяционный многочлен Ньютона" << endl;
                methods.NewtonInterpolationPolynomial(Dots);
                break;
            case '2':
                cout << "Выбран Интерполяционный многочлен Лагранжа" << endl;
                methods.LagrangeInterpolationPolynomial(Dots);
                break;
            case '3':
                cout << "Выбраны Сглаживающие многочлены 1 степени" << endl;
                methods.SmoothingPolynomials(Dots, 1);
                break;
            case '4':
                cout << "Выбраны Сглаживающие многочлены 2 степени" << endl;
                methods.SmoothingPolynomials(Dots, 2);
                break;
            case '5':
                cout << "Выбраны Сглаживающие многочлены 3 степени" << endl;
                methods.SmoothingPolynomials(Dots, 3);
                break;
            case '6':
                cout << "Выбрано Построение графика полинома 4 степени" << endl;
                methods.FourDegreePolynomials();
                break;
            case '7':
                cout << "Выбрано Отчистка" << endl;
                chart.Clear();
                break;
            case 27:
                running = false;
                exit(0);
                break;
            default:
                cout << "Некорректный ввод. Пожалуйста, повторите." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }
}

void InitGlut(int argc, char** argv){
    Charts chart;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polynoms");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    chart.MyGlutDisplay();
    chart.MyGlutReshape();
}


int main(int argc, char** argv) {
    InitGlut(argc, argv);
    
    thread background(MyMenu); //второй поток
    background.detach();
    
    glutMainLoop();
    return 0;
}
