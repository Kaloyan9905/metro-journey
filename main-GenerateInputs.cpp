/**
 * ============================================================================
 * Copyright (c) 2026 Калоян Ивелинов Милчев (Kaloyan Ivelinov Milchev)
 * Факултетен номер / Student ID: F118428
 * Нов български университет (New Bulgarian University)
 * ============================================================================
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

/**
 * ============================================================================
 * Генератор на входни данни за задачата "Пътуване с Метро"
 * ============================================================================
 * 
 * ИЗПОЛЗВАНЕ:
 * -----------
 *   ./generator [брой_запитвания] [мин_станции] [макс_станции]
 * 
 * ПРИМЕРИ:
 *   ./generator              # 10 запитвания, 5-10000 станции (по подразбиране)
 *   ./generator 50           # 50 запитвания
 *   ./generator 100 10 500   # 100 запитвания с 10-500 станции всяко
 * 
 * ФОРМАТ НА ВХОДА:
 * ----------------
 *   T (брой запитвания)
 *   За всяко запитване:
 *     N (брой станции)
 *     N имена на станции
 *     Ключов низ
 * 
 * ГЕНЕРИРАНИ ФАЙЛОВЕ:
 * -------------------
 *   input/input.txt   - входни данни
 *   output/output.txt - очаквани отговори
 * 
 * ============================================================================
 */

const vector<string> prefixes = {
    "central", "north", "south", "east", "west",
    "new", "old", "upper", "lower", "grand",
    "park", "tech", "eco", "bio", "smart",
    "green", "blue", "red", "gold", "silver"
};

const vector<string> suffixes = {
    "station", "stop", "plaza", "square", "center",
    "park", "view", "side", "town", "city",
    "gate", "point", "cross", "bridge", "mall"
};

const vector<string> keys = {
    "eco", "park", "city", "tech", "green", "blue", "red", "gold", "silver"
};

const long long MAX_TOTAL_STATIONS = 1000000;  // Ограничение от условието

string generateRandomString(int length) {
    string result;
    for (int i = 0; i < length; i++) {
        result += 'a' + (rand() % 26);
    }
    return result;
}

bool containsSubstring(const string& str, const string& key) {
    return str.find(key) != string::npos;
}

string generateStationName(const string& key, bool shouldContainKey) {
    string name;
    
    if (shouldContainKey) {
        int variant = rand() % 3;
        if (variant == 0) {
            name = key + generateRandomString(rand() % 6 + 2);
        } else if (variant == 1) {
            name = generateRandomString(rand() % 6 + 2) + key;
        } else {
            name = generateRandomString(rand() % 4 + 1) + key + generateRandomString(rand() % 4 + 1);
        }
    } else {
        do {
            name = prefixes[rand() % prefixes.size()] + suffixes[rand() % suffixes.size()];
        } while (containsSubstring(name, key));
    }
    
    return name;
}

int calculateAnswer(const vector<string>& stations, const string& key) {
    int n = stations.size();
    if (n == 1) return 1;
    
    int count = 2; // start + end
    for (int i = 1; i < n - 1; i++) {
        if (containsSubstring(stations[i], key)) {
            count++;
        }
    }
    return count;
}

int randomInRange(int minVal, int maxVal) {
    return minVal + rand() % (maxVal - minVal + 1);
}

void printUsage(const char* programName) {
    cout << "Използване: " << programName << " [брой_запитвания] [мин_станции] [макс_станции]\n\n";
    cout << "Аргументи:\n";
    cout << "  брой_запитвания  Брой запитвания за генериране (по подразбиране: 10)\n";
    cout << "  мин_станции      Минимален брой станции на запитване (по подразбиране: 5)\n";
    cout << "  макс_станции     Максимален брой станции на запитване (по подразбиране: 10000)\n\n";
    cout << "Примери:\n";
    cout << "  " << programName << "              # 10 запитвания, 5-10000 станции\n";
    cout << "  " << programName << " 50           # 50 запитвания, 5-10000 станции\n";
    cout << "  " << programName << " 100 10 500   # 100 запитвания, 10-500 станции\n";
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    
    int numQueries = 10;
    int minStations = 5;
    int maxStations = 10000;
    
    if (argc >= 2) {
        if (string(argv[1]) == "-h" || string(argv[1]) == "--help") {
            printUsage(argv[0]);
            return 0;
        }
        numQueries = atoi(argv[1]);
    }
    if (argc >= 3) {
        minStations = atoi(argv[2]);
    }
    if (argc >= 4) {
        maxStations = atoi(argv[3]);
    }
    
    if (numQueries <= 0) {
        cerr << "Грешка: Броят запитвания трябва да е положително число.\n";
        return 1;
    }
    if (minStations <= 0 || maxStations <= 0 || minStations > maxStations) {
        cerr << "Грешка: Невалиден диапазон за станции.\n";
        return 1;
    }
    
    ofstream fin("input/input.txt");
    ofstream fout("output/output.txt");
    
    if (!fin || !fout) {
        cerr << "Грешка при създаване на файлове!" << endl;
        return 1;
    }
    
    fin << numQueries << "\n";
    
    cout << "=== Metro Journey Generator ===\n";
    cout << "Генериране на " << numQueries << " запитвания\n";
    cout << "Диапазон станции: " << minStations << " - " << maxStations << "\n\n";
    
    long long totalStations = 0;
    
    for (int t = 1; t <= numQueries; t++) {
        int n;
        
        // Edge case: първите няколко теста са специални случаи
        if (t == 1 && minStations <= 1) {
            n = 1;  // Edge case: N = 1
        } else {
            n = randomInRange(minStations, maxStations);
        }
        
        // Проверка за ограничението от 1,000,000 общо станции
        if (totalStations + n > MAX_TOTAL_STATIONS) {
            cout << "\n[ВНИМАНИЕ] Достигнато ограничение от " << MAX_TOTAL_STATIONS << " станции.\n";
            cout << "Генерирани " << (t - 1) << " запитвания вместо " << numQueries << ".\n";
            numQueries = t - 1;
            break;
        }
        
        totalStations += n;
        
        string key = keys[rand() % keys.size()];
        double keyProb = 0.1 + ((double)(rand() % 20) / 100.0);
        
        vector<string> stations;
        for (int i = 0; i < n; i++) {
            bool hasKey = ((double)rand() / RAND_MAX) < keyProb;
            stations.push_back(generateStationName(key, hasKey));
        }
        
        fin << n << "\n";
        for (int i = 0; i < n; i++) {
            fin << stations[i] << "\n";
        }
        fin << key << "\n";
        
        int answer = calculateAnswer(stations, key);
        fout << answer << "\n";
        
        if (numQueries <= 20 || t % (numQueries / 10) == 0 || t == numQueries) {
            cout << "Query " << t << "/" << numQueries 
                 << ": N=" << n << ", key=\"" << key << "\", answer=" << answer << "\n";
        }
    }
    
    fin.close();
    fout.close();
    
    cout << "\n=== Генерирането завърши ===\n";
    cout << "Общо станции: " << totalStations << "\n";
    cout << "Средно станции/запитване: " << (totalStations / numQueries) << "\n\n";
    cout << "Генерирани файлове:\n";
    cout << "  input/input.txt   - " << numQueries << " запитвания\n";
    cout << "  output/output.txt - " << numQueries << " очаквани отговора\n";
    
    return 0;
}
