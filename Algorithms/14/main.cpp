#include <iostream>
#include <fstream>
#include <vector>
#include <list>

const int TABLE_SIZE = 20;

class HashTable
{
public:
    HashTable() : table(TABLE_SIZE) {}
//добавляет строку (слово) в хеш-таблицу.
    void insert(const std::string& word)
    {
        int index = hashFunction(word);
        table[index].push_back(word);
    }

    void writeToFile(const std::string& filename)
    {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open())
        {
            std::cerr << "Невозможно открыть выходной файл." << std::endl;
            return;
        }
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            for (const auto& word : table[i])
            {
                outputFile << i << ": " << word << std::endl;
            }
        }
        outputFile.close();
    }

private:
    int hashFunction(const std::string& word)
    {
        // Простейшая хеш-функция - сумма ASCII-кодов символов
        int sum = 0;
        for (char ch : word)
        {
            sum += ch;
        }
        return sum % TABLE_SIZE;
    }

    std::vector<std::list<std::string>> table;
};
int main()
{
    std::string inputFileName = "input.txt";
    std::string outputFileName = "output.txt";
    HashTable hashTable;
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Невозможно открыть входной файл." << std::endl;
        return 1;
    }
    std::string word;
    while (inputFile >> word)
    {
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end()); //удаляет знаки препинания из слова
        hashTable.insert(word);
    }
    inputFile.close();
    // Запись в файл
    hashTable.writeToFile(outputFileName);
    std::cout << "Хэш-таблица была записана в файл " << outputFileName << std::endl;
    return 0;
}