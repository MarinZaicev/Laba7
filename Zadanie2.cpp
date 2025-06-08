#include <iostream>
#include <math.h>
using namespace std;

// Функция для нахождения k-го бита в строке Sn
char findKBit(int n, int k) {
    // S1 = "0"
    if (n == 1) {
        return '0';
    }

    // Вычисляем длину строки Sn = 2^n - 1
    int length = (int)pow(2, n) - 1;

    // Находим позицию центрального бита (всегда '1')
    int mid = (length + 1) / 2;

    // Если k указывает на центральный бит
    if (k == mid) {
        return '1';
    }
    // Если k находится в первой половине строки (Sn-1)
    else if (k < mid) {
        // Рекурсивно ищем k-й бит в Sn-1
        return findKBit(n - 1, k);
    }
    // Если k находится во второй половине строки (reverse(invert(Sn-1)))
    else {
        // Находим соответствующую позицию в Sₙ₋₁:
        // reverse делает последний бит первым, поэтому позиция = 2^n - k
        int posInSn1 = ((int)pow(2, n)) - k;

        // Получаем бит из Sn-1 на этой позиции
        char bit = findKBit(n - 1, posInSn1);

        // Инвертируем бит (0 -> 1, 1 -> 0)
        return (bit == '0') ? '1' : '0';
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n, k;
    cout << "Введите n и k: ";
    cin >> n >> k;

    // Проверяем корректность ввода (k должно быть в пределах длины строки)
    if (k < 1 || k >(1 << n) - 1) {
        cout << "Ошибка: k должно быть в диапазоне [1, " << ((1 << n) - 1) << "]" << endl;
        return 1;
    }

    cout << k << "-й бит в S_" << n << ": " << findKBit(n, k) << endl;
    return 0;
}
