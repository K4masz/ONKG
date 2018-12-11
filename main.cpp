#include <iostream>
#include <stdio.h>
#include <vector>


void startCalculating(bool **pBoolean, bool *currentRegisterState);

void addToUsedRegisterValues(bool *currentRegisterState);

bool isAlreadyUsedState(bool *registerState);

bool isEveryRegisterStateUsed();

void calculateCycle(bool **conversionMatrix, bool *currentRegisterState);

void calculateState(bool **conversionMatrix, bool *currentRegisterState);

using namespace std;

bool *usedRegisterValues;
int flipFlopCount = 0;
bool maximalCycle = false; //2n-1

void setStartRegister(bool* &currentRegister) {
    currentRegister[0] = 1;
    for (int i = 1; i < flipFlopCount; i++) {
        currentRegister[i] = 0;
    }
}

bool calculateCell(bool* matrixRow, bool* currentRegister) {
    int result = 0;

    for (int i = 0; i < flipFlopCount; i++) {
        result = result + (matrixRow[i] * currentRegister[i]);
    }

    return (result % 2);
}

void calculateRegisterState(bool **matrix, bool *&currentRegister) {
    bool *nextRegister = new bool[flipFlopCount];

    for (int i = 0; i < flipFlopCount; i++) {
        nextRegister[i] = calculateCell(matrix[i], currentRegister);
    }

    currentRegister = nextRegister;
}

void fillMatrix(bool **fillingMatrix) {
    for (int i = 0; i < flipFlopCount; i++) {
        cout << "Podaj " << i + 1 << " wiersz: ";

        for (int j = 0; j < flipFlopCount; j++) {
            cin >> fillingMatrix[i][j];
        }
    }
}

void showMatrix(bool **matrix) {
    cout << endl << endl << endl;

    for (int i = 0; i < flipFlopCount; i++) {
        for (int j = 0; j < flipFlopCount; j++) {
            cout << matrix[i][j] << " ";
        }

        cout << "\n";
    }
}

//metoda parsująca
int parseRegisterState(bool *&currentRegisterState) {
    int result;
    for (int i = 0; i < flipFlopCount; i++)
        if (currentRegisterState[i])
            result += 2 ^ (currentRegisterState[i] * i);

    return result;
}


void addToUsedRegisterValues(bool *currentRegisterState) {
    usedRegisterValues[parseRegisterState(currentRegisterState)] = true;
}

//Początek wszystkich obliczeń
void startCalculating(bool **conversionMatrix, bool *currentRegisterState) {
    int cyclesNumber = 0;
    //początek liczenia jednego cyklu
    do {
        //obecny rejestr idzie do użytych rejestrów
        calculateCycle(conversionMatrix, currentRegisterState);

        //koniec pętli
        cyclesNumber++;


    } while (isEveryRegisterStateUsed());

    cout << "Finalna liczba cykli: " << cyclesNumber;

}

void calculateCycle(bool **conversionMatrix, bool *currentRegisterState) {
    //przemnożyć macierz przez rejestr - mamy rejestr wynikowy
    int statesNumber = 0;
    do {

        calculateState(conversionMatrix, currentRegisterState);
        statesNumber++;
    } while ((parseRegisterState(currentRegisterState) == 0) || isAlreadyUsedState(currentRegisterState));
    //sprawdzić czy rejestr przedstawia zero jeśli jest lub czy jest w użytych (parsowane na liczbe) - jesli tak koniec
    cout << "liczba stanów w cyklu: " << statesNumber;
    if(statesNumber == 2^flipFlopCount-1){
        cout<< "generuje cykl maksymalny";
    }

}

void calculateState(bool **conversionMatrix, bool *currentRegisterState) {
    addToUsedRegisterValues(currentRegisterState);
    calculateRegisterState(conversionMatrix, currentRegisterState);

}

bool isEveryRegisterStateUsed() {
    bool result = true;

    for (int i = 0; i < flipFlopCount; i++)
        if (usedRegisterValues[i] == false)
            result = false;

    return result;
}

bool isAlreadyUsedState(bool *registerState) {
    if (usedRegisterValues[parseRegisterState(registerState)] == true)
        return true;
    else
        return false;

}


int main() {

    bool **conversionMatrix;
    bool *currentRegisterState;

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

    fillMatrix(conversionMatrix);
    showMatrix(conversionMatrix);

    setStartRegister(currentRegisterState);
    startCalculating(conversionMatrix, currentRegisterState);

    return 0;
}

