/**
 * ============================================================================
 * Copyright (c) 2026 Калоян Ивелинов Милчев (Kaloyan Ivelinov Milchev)
 * Факултетен номер / Student ID: F118428
 * Нов български университет (New Bulgarian University)
 * ============================================================================
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * ============================================================================
 * Решение 1: Наивен подход (Naive Approach)
 * ============================================================================
 * 
 * АЛГОРИТЪМ:
 * ----------
 * За всяка станция (освен първата и последната), проверяваме дали съдържа
 * ключовия низ чрез ръчно сравнение символ по символ.
 * 
 * СЛОЖНОСТ:
 * ---------
 * - Време: O(T * N * M * L)
 *   където:
 *     T = брой запитвания
 *     N = брой станции
 *     M = средна дължина на име на станция
 *     L = дължина на ключовия низ
 * 
 * - Памет: O(N * M) за съхранение на имената
 * 
 * ЗАЩО Е НАИВЕН:
 * --------------
 * Ръчната имплементация на substring търсене има O(M * L) сложност
 * за всяка станция, вместо да използваме оптимизирани библиотечни функции.
 * 
 * ============================================================================
 */

bool containsSubstring(const string& str, const string& key) {
    int strLen = str.length();
    int keyLen = key.length();
    
    for (int i = 0; i <= strLen - keyLen; i++) {
        bool found = true;
        for (int j = 0; j < keyLen; j++) {
            if (str[i + j] != key[j]) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }
    return false;
}

int solve() {
    int n;
    cin >> n;
    
    string stations[n];
    for (int i = 0; i < n; i++) {
        cin >> stations[i];
    }
    
    string key;
    cin >> key;
    
    if (n == 1) return 1;
    
    int count = 2;
    for (int i = 1; i < n - 1; i++) {
        if (containsSubstring(stations[i], key)) {
            count++;
        }
    }
    
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        cout << solve() << "\n";
    }
    
    return 0;
}
