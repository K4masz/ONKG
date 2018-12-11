#include <iostream>
#include <stdio.h>
#include <vector>


using namespace std;


void setStartRegister(bool *&currentRegister, int size) {
    currentRegister[0] = true;
    for (int i = 1; i < size; i++) {
        currentRegister[i] = false;
    }
}

void fillMatrix(bool** fillingMatrix, int size) {
    for (int i= 0; i < size; i++) {
        cout << "Podaj " << i+1 << " wiersz: ";

        for (int j = 0; j < size; j++) {
            cin >> fillingMatrix[i][j];
        }
    }
}

void showMatrix(bool** matrix, int size) {
    cout << endl << endl << endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }

        cout << "\n";
    }
}



int main() {

    int flipFlopCount = 0;
    bool **conversionMatrix;
    bool *currentRegister;
    bool *usedRegisterValues;
    int cyclesCount = 0;
    string matrixStr;

    bool test = (true * false + 1) % 2;
    cout << test;

    cout << "Podaj wielkość macierzy: ";
    cin >> flipFlopCount;
    cout << endl << endl;

    //INITIALIZING MATRIX
    conversionMatrix = new bool *[flipFlopCount];
    for (int i = 0; i < flipFlopCount; i++) {
        conversionMatrix[i] = new bool[flipFlopCount];
    }
    //INITIALIZING MATRIX - END

    usedRegisterValues = new bool[2 ^ flipFlopCount - 1];

    fillMatrix(conversionMatrix, flipFlopCount);
    showMatrix(conversionMatrix, flipFlopCount);

    return 0;
}

