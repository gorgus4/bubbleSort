#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <string>

using namespace std;

// ===================
// Sortowanie
// ===================

void bubbleSortStandard(vector<int>& arr, bool ascending) {
    
    int size = arr.size();
    if (size <= 1) return;
    
    for (int i = 0; i < size - 1; i++) {
        
        for (int j = 0; j < size - 1; j++) {
            
            if (ascending) {
                
                if (arr[j] > arr[j + 1]) {
                    
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            } 
            else {
                
                if (arr[j] < arr[j + 1]) {
                    
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void bubbleSortOptimized(vector<int>& arr, bool ascending) {
    
    int size = arr.size();
    if (size <= 1) return;

    bool swapped;
    int rangeCuts = 0; 

    do {
        swapped = false;
        
        for (int i = 0; i < size - 1 - rangeCuts; i++) {
            
            if (ascending) {
                
                if (arr[i] > arr[i + 1]) {
                    
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    
                    swapped = true; 
                }
            } 
            else {
                
                if (arr[i] < arr[i + 1]) {
                    
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    
                    swapped = true; 
                }
            }
        }
        rangeCuts++;
        
    } while (swapped && rangeCuts < size - 1);
}

// ===================
// Menu
// ===================

int getMenuOption() {
    
    int option = 0;
    
    cout << ">> SYSTEM SORTOWANIA BABELKOWEGO" << endl;
    cout << "1> Wlasna tablica" << endl;
    cout << "2> Wygenerowana tablica" << endl;
    cout << "?> Wybierz opcje: ";

    while (true) {
        
        if (cin >> option) {
            
            if (option == 1 || option == 2) {
                break;
            }
        } 
        else {
            
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        cout << "!> ERROR: Niepoprawny wybor!"; 
        cout << endl << "?> Sproboj ponownie: ";
    }
    return option;
}

// ===================
// Wlasna tablica
// ===================

bool getManualInput(vector<int>& arr) {
    
    cin.ignore();

    cout << endl << ">> Wypisz elementy po kolei: " << endl;
    
    string line;
    int index = 1;
    
    while (true) {
        
        cout << "?> Element " << index << ": ";
        
        if (!getline(cin, line) || line.empty()) {
            break;
        }
        
        try {
           
            size_t processedChars = 0;
            int value = stoi(line, &processedChars);
            
            while (processedChars < line.length() && isspace(line[processedChars])) {
                
                processedChars++;
            }
            
            if (processedChars < line.length()) {
                
                cout << "!> ERROR: Niewlasciwy format - podaj integer!" << endl;
                continue;
            }
            
            arr.push_back(value);
            index++;
        } 
        catch (...) {
            
            cout << "!> ERROR: Niewlasciwy znak - sproboj ponownie!" << endl;
        }
    }
    return true;
}

// ===================
// Wygenerowana tablica
// ===================

bool getRandomInput(vector<int>& arr) {
    
    int size = 0;
    
    cout << endl << "?> Podaj wielkosc tablicy: ";
    
    if (!(cin >> size)) {
        
        cin.clear();
        cin.ignore(10000, '\n');
        
        cout << "!> ERROR: Niewlasciwy format - podaj integer!" << endl;
        
        return false;
    }

    if (size < 0) {
        
        cout << "!> ERROR: Rozmiar tablicy nie moze byc ujemny!" << endl;
        
        return false;
    }

    if (size > 0) {
       
        int minValue, maxValue;
        
        cout << "?> Podaj dolna granice zakresu liczb: ";
        cin >> minValue;
        cout << "?> Podaj gorna granice zakresu liczb: ";
        cin >> maxValue;

        if (minValue > maxValue) {
            
            cout << "!> ERROR: Dolna granica nie moze byc wieksza od gornej!!" << endl;
            
            return false;
        }

        arr.resize(size);
        
        unsigned long long seed = time(nullptr);
        
        for (int i = 0; i < size; i++) {
            
            seed = (seed * 1103515245 + 12345) % 2147483648;
            
            arr[i] = minValue + (seed % (maxValue - minValue + 1));
        }
    }
    return true;
}

// ===================
// Rodzaj sortowania
// ===================

bool getSortOrder() {
    
    int sortOrder = 1;
    
    cout << endl << ">> Wybierz kierunek sortowania:" << endl;
    cout << "1> Rosnaco" << endl;
    cout << "2> Malejaco" << endl;
    cout << "?> Wybierz opcje: ";
    
    while (!(cin >> sortOrder) || (sortOrder != 1 && sortOrder != 2)) {
        
        cin.clear();
        cin.ignore(10000, '\n');
        
        cout << "!> ERROR: Niepoprawny wybor!" << endl << "?> Sproboj ponownie: ";
    }
    return (sortOrder == 1);
}

// ===================
// Wypisz tabilce
// ===================

void printArray(const vector<int>& arr) {
    
    for (int i = 0; i < (int)arr.size(); i++) {
        
        cout << arr[i] << " ";
    }
}

// ===================
// Uruchom sortowanie + czas
// ===================

void runSorting(vector<int>& standardArr, vector<int>& optimizedArr, bool ascending) {
    
    if (standardArr.empty()) {
        
        cout << endl << "!> ERROR: Pusta tablica." << endl;
        return;
    }

// Pomiar standarodowy:

    auto startStandard = chrono::high_resolution_clock::now();
    
    bubbleSortStandard(standardArr, ascending);
    
    auto endStandard = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> durationStandard = endStandard - startStandard;

// Pomiar zoptymalizowany:

    auto startOptimized = chrono::high_resolution_clock::now();
    
    bubbleSortOptimized(optimizedArr, ascending);
    
    auto endOptimized = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> durationOptimized = endOptimized - startOptimized;

    cout << endl << ">> Tablica po sortowaniu (" << (ascending ? "Rosnaco" : "Malejaco") << "):" << endl;
    
    printArray(optimizedArr);
    
    cout << endl << endl;

    cout << ">> Czas sortowania BEZ optymalizacji: " << durationStandard.count() << " ms" << endl;
    cout << ">> Czas sortowania Z optymalizacja:   " << durationOptimized.count() << " ms" << endl;
    
}

// ===================
// Złożoność
// ===================

void displayComplexity() {
    
    cout << ">> ANALIZA ZLOZONOSCI ALGORYTMU ZOPTYMALIZOWANEGO" << endl;
    cout << ">> CZASOWA:" << endl;
    cout << ">> Optymistyczna: O(n)" << endl;
    cout << ">> Srednia:       O(n^2)" << endl;
    cout << ">> Pesymistyczna: O(n^2)" << endl;
    cout << ">> PAMIECIOWA:" << endl;
    cout << ">> Algorytmu:     O(1)" << endl;
}

// ===================
// Main
// ===================

int main() {
    
    int option = getMenuOption();

    vector<int> vectorStandard; 
    vector<int> vectorOptimized; 

// Wybor tablicy (wlasna / wygenerowana)

    if (option == 1) {
        
        if (!getManualInput(vectorStandard)) {
            return 1;
        }

        vectorOptimized = vectorStandard; 
    } 
    else if (option == 2) {
        
        if (!getRandomInput(vectorStandard)) {
            return 1;
        }
        
        vectorOptimized = vectorStandard; 
    }

    if (vectorStandard.empty()) {
        
        cout << endl << "!> ERROR: Pusta tablica." << endl;
        
        return 0;
    }

    cout << endl << ">> Tablica przed sortowaniem:" << endl;
    
    printArray(vectorOptimized);
    
    cout << endl;

    bool ascending = getSortOrder();

    runSorting(vectorStandard, vectorOptimized, ascending);
    
    cout << endl;
    
    displayComplexity();

    return 0;
}