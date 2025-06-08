#include <iostream>      
#include <vector>        
#include <string>        
#include <algorithm>     
#include <climits>       

using namespace std;     

// Функция для нахождения максимального перекрытия между концом строки a и началом строки b
int findOverlap(const string& a, const string& b) {
    // Вычисляем максимально возможную длину перекрытия 
    int maxLen = min(a.length(), b.length()) - 1;

    // Проверяем все возможные длины перекрытия от максимальной до 1
    for (int l = maxLen; l > 0; l--) {
        // Сравниваем конец строки a длиной l с началом строки b длиной l
        if (a.substr(a.size() - l) == b.substr(0, l)) {
            return l;  // Возвращаем найденную длину перекрытия
        }
    }
    return 0;  // Если перекрытие не найдено, возвращаем 0
}

// Рекурсивная функция для поиска оптимального порядка слов
void findBestOrder(const vector<string>& words,  // Все слова для кроссворда
    vector<bool>& used,           // Массив флагов использования слов
    vector<int>& currentOrder,    // Текущий порядок слов
    int currentLength,            // Текущая длина кроссворда
    int& minLength,               // Минимальная найденная длина (передаётся по ссылке)
    vector<int>& bestOrder) {     // Лучший найденный порядок слов

    // Базовый случай: если все слова использованы
    if (currentOrder.size() == words.size()) {
        // Если текущая длина меньше найденного минимума
        if (currentLength < minLength) {
            minLength = currentLength;  // Обновляем минимальную длину
            bestOrder = currentOrder;   // Сохраняем лучший порядок
        }
        return;
    }

    // Перебираем все слова
    for (int i = 0; i < words.size(); i++) {
        // Если слово ещё не использовано
        if (!used[i]) {
            int overlap = 0;  // Длина перекрытия с предыдущим словом

            // Если это не первое слово, вычисляем перекрытие
            if (!currentOrder.empty()) {
                overlap = findOverlap(words[currentOrder.back()], words[i]);
            }

            // Вычисляем новую длину кроссворда при добавлении текущего слова
            int newLength = currentLength + words[i].length() - overlap;

            // Если новая длина меньше текущего минимума
            if (newLength < minLength) {
                used[i] = true;              // Помечаем слово как использованное
                currentOrder.push_back(i);   // Добавляем индекс слова в текущий порядок

                // Рекурсивный вызов для следующего слова
                findBestOrder(words, used, currentOrder, newLength, minLength, bestOrder);

                // Возвращаем состояние (backtracking)
                currentOrder.pop_back();
                used[i] = false;
            }
        }
    }
}

// Функция построения кроссворда из найденного оптимального порядка слов
string buildCrossword(const vector<string>& words) {
    // Если список слов пуст, возвращаем пустую строку
    if (words.empty()) return "";

    vector<bool> used(words.size(), false);  // Флаги использования слов
    vector<int> currentOrder, bestOrder;     // Текущий и лучший порядок слов
    int minLength = INT_MAX;                 // Начальное значение минимальной длины

    // Запускаем рекурсивный поиск оптимального порядка
    findBestOrder(words, used, currentOrder, 0, minLength, bestOrder);

    // Если не найден ни один допустимый порядок
    if (bestOrder.empty()) return "";

    // Строим результирующую строку кроссворда
    string result = words[bestOrder[0]];  // Начинаем с первого слова

    // Добавляем остальные слова с учётом перекрытий
    for (int i = 1; i < bestOrder.size(); i++) {
        // Находим перекрытие между текущим и предыдущим словом
        int overlap = findOverlap(words[bestOrder[i - 1]], words[bestOrder[i]]);
        // Добавляем часть слова после перекрытия
        result += words[bestOrder[i]].substr(overlap);
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<string> words = { "матан", "прога", "амбассадор", "новосиб" };

    string crossword = buildCrossword(words);

    cout << "Линейный кроссворд: " << crossword << endl;
    cout << "Длина: " << crossword.length() << " букв" << endl;

    return 0;  // Завершаем программу
}
