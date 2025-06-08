#include <GL/glut.h>  // Подключаем библиотеку GLUT
#include <cmath>       // Для математических функций (sqrt)

// Размеры окна
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RECURSION_DEPTH = 4;  // Фиксированная глубина рекурсии

// Функция построения кривой Коха
void drawKochCurve(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        // Базовый случай - рисуем отрезок
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    // Вычисляем разницу координат
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Точки, делящие отрезок на 3 равные части
    float xA = x1 + dx / 3;
    float yA = y1 + dy / 3;
    float xB = x1 + 2 * dx / 3;
    float yB = y1 + 2 * dy / 3;

    // Координаты вершины треугольника
    float xC = (x1 + x2) / 2 - dy * sqrt(3) / 6;
    float yC = (y1 + y2) / 2 + dx * sqrt(3) / 6;

    // Рекурсивно строим 4 новых отрезка
    drawKochCurve(x1, y1, xA, yA, depth - 1);
    drawKochCurve(xA, yA, xC, yC, depth - 1);
    drawKochCurve(xC, yC, xB, yB, depth - 1);
    drawKochCurve(xB, yB, x2, y2, depth - 1);
}

// Функция отрисовки
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Очищаем буфер цвета
    glColor3f(1.0, 1.0, 1.0);     // Устанавливаем белый цвет

    glBegin(GL_LINES);  // Начинаем рисовать линии
    // Рисуем кривую Коха между точками (-0.8, -0.2) и (0.8, -0.2)
    drawKochCurve(-0.8f, -0.2f, 0.8f, -0.2f, RECURSION_DEPTH);
    glEnd();  // Заканчиваем рисовать

    glutSwapBuffers();  // Обновляем экран
}

// Инициализация OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Черный фон
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Устанавливаем 2D-проекцию с координатами от -1 до 1
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Koch Curve");

    // Настройки и запуск
    init();
    glutDisplayFunc(display);  // Регистрируем функцию отрисовки

    glutMainLoop();  // Запускаем главный цикл
    return 0;
}
