//================ Шифратор файлов реализованный на основе алгоритма Хаффмана ================
//================ Справка по методам ================
//1. Открытие выбранного файла(Кодированного / Декадированного):
//-->      inFile.openFile(char * nameFile);
//2. Кодирование файла:
//-->      inFile.codingFile();
//3. Сохранение ключа:
//-->      inFile.saveKey(char * nameKeyFile);
//4. Открытие ключа:
//-->      inFile.openKey(char * nameKeyFile);
//5. Декадирование файла:
//-->      inFile.decodingFile(char * nameDeCodeFile);
//6. Закрытие файла (inFile):
//-->      inFile.closeInFile();
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include "cryptoalgorithm.h"
void menu();
int main(void)
{
    char nameFile[] = "E:/testingHuffman/1.txt";
    char CodeFile[] = "E:/testingHuffman/2.txt";
    char deCodeFile[] = "E:/testingHuffman/3.txt";
    char nameKeyFile[] = "E:/testingHuffman/key.txt";
    cout << "Name file: " << nameFile << endl;
//    CryptoAlgorithm file(nameFile);
    CryptoAlgorithm file;
    file.openFile(nameFile);
    file.codingFile();
    system("pause");
    file.saveCodingFile(CodeFile);
    file.saveKey(nameKeyFile);
    file.closeInFile();
    system("pause");
    file.openFile(CodeFile);
    file.openKey(nameKeyFile);
    file.decodingFile(deCodeFile);
    file.closeInFile();
    return 0;
}
void menu()
{

}
