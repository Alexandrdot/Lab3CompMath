#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
#include "Methods.h"
#include "Charts.h"

using namespace std;
//вызываю методы, провожу расчет, вывожу графики через Charts

vector<float> Methods::MyDataForFourthDegree(){
    vector<float> koeff(5);
    
    for (int i = 0; i < 5; ++i) {
        printf("Введите коэффициент a%d: ", i);
        cin >> koeff[i];
    }
    return koeff;
}

void Methods::NewtonInterpolationPolynomial(vector<vector<float>> Dots){
    long N = Dots.size(); //количество точек
    Charts chart;
    vector<vector<float>> diff(N, vector<float>(N, 0.0f)); //разделенные разности n-го порядка
    
    //(0) = f(xi)
    for (int i = 0; i < N; ++i) {
            diff[0][i] = Dots[i][1];
    }
    //остальные (по формулам разделенных разностей, шаг разный)
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N - i; ++j) {
            diff[i][j] = (diff[i - 1][j + 1] - diff[i - 1][j]) / (Dots[j + i][0] - Dots[j][0]);
        }
    }
    //теперь есть все коеффиценты
    //далее вызываем "chart" => "сборщик" => view
    chart.PrintNewtonPolynom(diff, Dots);
}

void Methods::LagrangeInterpolationPolynomial(vector<vector<float>> Dots){
    long N = Dots.size(); //количество точек
    vector<float> C(N); //коэф (знаменатель) + умножил на yi для простоты
    Charts chart;
    
    for (int i = 0; i < N; i++){
        C[i] = Dots[i][1];
        for (int j = 0; j < N; j++){
            if (i != j){
                C[i] *= 1 / (Dots[i][0] - Dots[j][0]);
            }
        }
    }
    //собрали коэффициенты
    chart.PrintLagrangePolynom(C, Dots);
}

vector<vector<float>> Methods::BuildMatrixKoeff(vector<vector<float>> Koeff, int a, vector<vector<float>> Dots){
    //мнк, вычисление матрицы коэффицентов полинома a, b, c, ...
    for (int i = 0; i < Koeff.size(); i++){
        for (int j = 0; j < Koeff.size() + 1; j++){
            double summ_degree = 0;
            for (int k = 0; k < Dots.size(); k++){ //a
                if (j != Koeff.size())
                    summ_degree += pow(Dots[k][0], a - i - j);
                else
                    summ_degree += pow(Dots[k][0], a - i - j + 1) * Dots[k][1];
            }
            Koeff[i][j] = summ_degree;
        }
    }
    return Koeff;
}

void Methods::SmoothingPolynomials(vector<vector<float>> Dots, int a){
    vector<vector<float>> koeff(a+1, vector<float>(a+2));
    Methods methods;
    Charts chart;
    koeff = methods.BuildMatrixKoeff(koeff, a * 2, Dots);
    vector<float> x = GaussMethod(koeff);
    
    if (x.size() != 1){
        if (a == 1)
            chart.PrintFirstSmoothingPolynomials(x);
        else if (a == 2)
            chart.PrintSecondSmoothingPolynomials(x);
        else
            chart.PrintThirdSmoothingPolynomials(x);
    }
    else {
        cout << "Нулевой диагональный элемент, решение не возможно!" << endl;
        return;
    }
}

vector<float> Methods::GaussMethod(vector<vector<float>> matrix){
    //схема единственного деления
    long row = matrix.size(); //кол-во строк
    long column = row + 1; //кол-во столбцов
    vector<float> x(row);
    for (int n = 0; n < column - 2; n++) // N-2 - так как расширенная матрица
    {
        float max_element = -1000;
        int number_row = 0;
        vector<float> copy_row(column);
        for (int k = n; k < row; k++) //поиск макс элемента в столбце на каждом шаге в зависимости от номера столбца
        {
            if (abs(matrix[k][n]) > max_element)
            {
                max_element = abs(matrix[k][n]);
                number_row = k;
                for (int j = 0; j < column; j++)
                {
                    copy_row[j] = matrix[k][j];
                }
            }
        }

        for (int j = 0; j < column; j++)
        {
            matrix[number_row][j] = matrix[n][j];
            matrix[n][j] = copy_row[j];
        }

        if (matrix[n][n] == 0)
        {
            return vector<float>(0);
        }
        for (int i = n + 1; i < row; i++) //строки
        {
            //сейчас я на второй строке
            float koeff = matrix[i][n] / matrix[n][n];
            for (int j = 0; j < column; j++) //элементы
            {
                matrix[i][j] = matrix[i][j] - koeff * matrix[n][j];
            }
        }
    }
    for (int i = int(row) - 1; i >= 0; i--) // i - строки (с конца)
    {
       float sum = 0;
       for (int j = i + 1; j < row; j++)  // j - столбцы (учитываем уже найденные переменные)
       {
           sum += matrix[i][j] * x[j];
       }
       x[i] = (matrix[i] [column - 1] - sum) / matrix[i][i];
    }
    return x;
}

void Methods::FourDegreePolynomials(){
    Charts chart;
    vector<float> _koeff = MyDataForFourthDegree();
    chart.PrintFourDegreePolynom(_koeff);
}
