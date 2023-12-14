#include "bibl.h"


int main() {
    try {
        RedBlackTree<std::pair<int, int>, std::string> Tree;

        std::ifstream inputFile("input.txt");

        if (!inputFile.is_open()) {
            throw std::runtime_error("Ошибка при открытии файла ввода.");
        }

        // Считываем данные из файла
        std::string line;
        while (std::getline(inputFile, line)) {
            try {
                // Используем поток для разбора строки
                std::istringstream iss(line);

                // Считываем слово и значения x1 и x2
                std::string word;
                char openParenthesis, semicolon, closeParenthesis;
                int x1, x2;

                if (iss >> word >> std::ws >> std::ws >> openParenthesis >> x1 >> semicolon >> x2 >> closeParenthesis) {
                    if (openParenthesis == '(' && semicolon == ';' && closeParenthesis == ')') {
                        // Создаем std::pair и добавляем в дерево
                        Tree.insert(std::make_pair(x1, x2), word);
                    } else {
                        throw std::invalid_argument("Неверный формат в строке: " + line);
                    }
                } else {
                    throw std::invalid_argument("Ошибка при разборе строки: " + line);
                }
            } catch (const std::exception& e) {
                std::cerr << "Исключение при обработке строки: " << e.what() << std::endl;
            }
        }

        inputFile.close();

        std::cout << "Дерево:" << std::endl;
        Tree.printTree();

        std::cout << std::endl;
        std::cout << std::endl;

        int searchX1, searchX2;
        std::cout << "Введите координаты (x1 и x2) для поиска: ";
        if (!(std::cin >> searchX1 >> searchX2)) {
            throw std::invalid_argument("Ошибка при вводе координат для поиска.");
        }

        // Создаем ключ для поиска
        std::pair<int, int> searchKey = std::make_pair(searchX1, searchX2);

        // Поиск слова по координатам
        std::string result;
        if (Tree.search(searchKey, result)) {
            std::cout << "Слово для координат (" << searchX1 << ", " << searchX2 << "): " << result << std::endl;
        } else {
            std::cout << "Слово для координат (" << searchX1 << ", " << searchX2 << ") не найдено." << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::endl;

        std::string searchValue;
        std::cout << "Введите слово для поиска координаты: ";
        if (!(std::cin >> searchValue)) {
            throw std::invalid_argument("Ошибка при вводе слова для поиска координаты.");
        }
        std::pair<int, int> resultKey;

        if (Tree.searchByValue(searchValue, resultKey)) {
            std::cout << "Координата найдена: (" << resultKey.first << ", " << resultKey.second << ")" << std::endl;
        } else {
            std::cout << "Такого слова нет в дереве. " << std::endl;
        }

        int treeDepth = Tree.depth();
        std::cout << "Глубина дерева: " << treeDepth << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "Введите координаты (x1 и x2) начала диапазона: ";
        if (!(std::cin >> searchX1 >> searchX2)) {
            throw std::invalid_argument("Ошибка при вводе координат начала диапазона.");
        }
        std::pair<int, int> leftRange = std::make_pair(searchX1, searchX2);
        std::cout << "Введите координаты (x3 и x4) конца диапазона: ";
        if (!(std::cin >> searchX1 >> searchX2)) {
            throw std::invalid_argument("Ошибка при вводе координат конца диапазона.");
        }
        std::pair<int, int> rightRange = std::make_pair(searchX1, searchX2);

        std::pair<std::pair<int, int>, std::pair<int, int>> range = std::make_pair(leftRange, rightRange);

        Tree.searchInRange(range);

        std::cout << std::endl;
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Поймано исключение: " << e.what() << std::endl;
        return 1;
    }


    return 0;
}