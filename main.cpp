#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

//DEKLARACAJE FUNKCJI
void initMatrix();
void fillMatrix();
void showMatrix();
void initRegisterState();
void initUsedRegisterValues();
void startCalculations();
void calculateCycle();
void calculateState();
void addToUsedRegisterValues();
void calculateRegisterState();
bool calculateCell(bool* matrixRow);
bool isAlreadyUsedState();
bool isEveryRegisterStateUsed();
int parseRegisterState();
void convertToRegister(int decimalNumber);
//ZMIENNE GLOBALNE

bool **conversionMatrix;
bool *currentRegisterState;
bool *usedRegisterValues;
int flipFlopCount = 0;
bool maximalCycle = false; //2n-1




//FLAGI

bool isEveryRegisterStateUsed() {
    bool result = true;

    for (int i = 0; i < flipFlopCount; i++)
        if (usedRegisterValues[i] == false) {
            result = false;
            break;
        }

    return result;
}

bool isAlreadyUsedState() {
    return usedRegisterValues[parseRegisterState()];
}

//INIT

void initMatrix(){
cout << "Podaj wielkość macierzy: ";
    cin >> flipFlopCount;
    cout << endl << endl;

    //INITIALIZING MATRIX
    conversionMatrix = new bool *[flipFlopCount];
    for (int i = 0; i < flipFlopCount; i++) {
        conversionMatrix[i] = new bool[flipFlopCount];
    }
    //INITIALIZING MATRIX - END
}

void initUsedRegisterValues(){
    int n = pow(2, flipFlopCount) - 1;
    usedRegisterValues = new bool[n];

    usedRegisterValues[0] = 1;
    for (int  i = 1; i < n; i++) {
        usedRegisterValues[i] = 0;
    }
}
void initRegisterState() {
    currentRegisterState = new bool[flipFlopCount];
    //currentRegisterState[0] = 1;
    for (int i = 0; i < flipFlopCount; i++) {
        currentRegisterState[i] = 0;
    }
}

//MATRIX

void fillMatrix() {
    for (int i = 0; i < flipFlopCount; i++) {
        cout << "Podaj " << i + 1 << " wiersz: ";

        for (int j = 0; j < flipFlopCount; j++) {
            cin >> conversionMatrix[i][j];
        }
    }
}

void showMatrix() {
    cout << endl;

    for (int i = 0; i < flipFlopCount; i++) {
        for (int j = 0; j < flipFlopCount; j++) {
            cout << conversionMatrix[i][j] << " ";
        }

        cout << "\n";
    }
}

bool calculateCell(bool* matrixRow) {
    int result = 0;

    for (int i = 0; i < flipFlopCount; i++) {
        result = result + (matrixRow[i] * currentRegisterState[i]);
    }

    return (result % 2);
}

void calculateRegisterState() {
    bool *nextRegister = new bool[flipFlopCount];

    for (int i = 0; i < flipFlopCount; i++) {
        nextRegister[i] = calculateCell(conversionMatrix[i]);
    }

    currentRegisterState = nextRegister;
}

//LOGIKA

void calculateState() {
    addToUsedRegisterValues();
    calculateRegisterState();

}

void calculateCycle() {
    //przemnożyć macierz przez rejestr - mamy rejestr wynikowy
    int statesNumber = 0;
    do {
        statesNumber++;
        calculateState();

    } while ((parseRegisterState() != 0) && !isAlreadyUsedState());
    //sprawdzić czy rejestr przedstawia zero jeśli jest lub czy jest w użytych (parsowane na liczbe) - jesli tak koniec
    cout << "liczba stanów w cyklu: " << statesNumber;
    if(statesNumber == pow(2, flipFlopCount)-1) {
        cout<< "generuje cykl maksymalny";
    }

}

int parseRegisterState() { //metoda parsująca
    int result = 0;
    for (int i = 0; i < flipFlopCount; i++)
        if (currentRegisterState[i])
            result += pow(2, i);

    return result;
}

void addToUsedRegisterValues() {
    usedRegisterValues[parseRegisterState()] = true;
}

void findFirstAvailableState(){
    for(int i =1 ; i< flipFlopCount ; i++ ){
        if(!usedRegisterValues[i]){
            convertToRegister(i);
            break;
        }
    }
}

void convertToRegister(int decimalNumber){
    int i =0 ;
    do{
    currentRegisterState[i] = decimalNumber%2;
    decimalNumber /= 2;
    i++;
    }while(decimalNumber > 0);
}

void startCalculations() { //Początek wszystkich obliczeń
    int cyclesNumber = 0;
    //początek liczenia jednego cyklu
    do {
        //obecny rejestr idzie do użytych rejestrów
        findFirstAvailableState();
        calculateCycle();

        //koniec pętli
        cyclesNumber++;


    } while (!isEveryRegisterStateUsed());

    cout << "Finalna liczba cykli: " << cyclesNumber;

}



//MAIN

int main() {

    initMatrix();
    fillMatrix();
    showMatrix();

    initRegisterState();
    initUsedRegisterValues();

    startCalculations();

    return 0;
}

