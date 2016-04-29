#ifndef CRYPTOALGORITHM_H
#define CRYPTOALGORITHM_H
#include "huffmancoding.h"
using namespace std;

//Управляющий класс алгоритмом и другими вещами
class CryptoAlgorithm
{
public:
    CryptoAlgorithm()
        : Algorithm(nullptr), flagOpenFile(false), flagSaveFileCoding(false), flagSaveFileDecoding(false), flagCodingFile(false), flagDegodingFile(false)
    {
        Algorithm = new HuffmanCoding;
    }

    CryptoAlgorithm(char * nameFile)
        : nameFile(nameFile), Algorithm(nullptr), flagOpenFile(false), flagSaveFileCoding(false), flagSaveFileDecoding(false), flagCodingFile(false), flagDegodingFile(false)
    {
        openFile(nameFile);
        Algorithm = new HuffmanCoding;
    }
    ~CryptoAlgorithm()
    {}
public:
    //Открытие файла
    void openFile(char * nameFileOpen)
    {
        if(flagOpenFile)
            return;
        inFile.open(nameFileOpen, ios::binary | ios::in);
        if(!inFile.is_open())
        {
            cout << "File open( " << nameFileOpen << " ): Error" << endl;
            return;
        }
        cout << "File open( " << nameFileOpen << " ): OK" << endl;
        flagOpenFile = true;
    }
    //Кодирование файла
    void codingFile()
    {
        if(!flagOpenFile)
        {
            cout << "File not open: EXIT" << endl;
            return;
        }
        Algorithm->coding(inFile);
        flagSaveFileCoding = true;
    }
   //Сохранение готового кодированного файла
    void saveCodingFile(const char * nameCodingFile)
    {
        if(!flagSaveFileCoding)
        {
            cout << "File not coding: ERROR " << endl;
            return;
        }
        outFile.open(nameCodingFile, ios::binary | ios::out);
        if(!outFile.is_open())
        {
            cout << "Error open file coding! " << endl;
            return;
        }
        if(Algorithm->saveCodFile(inFile, outFile))
        {
            outFile.close();
            flagSaveFileCoding = true;
            cout << "Save file coding: OK" << endl;
        }
    }
    //Сохранение уже готового сгенерированного ключа
    void saveKey(const char * NameFileKey)
    {
        if(!flagSaveFileCoding)
        {
            cout << "File is not encoded! "<< endl;
            return;
        }
        ofstream Key(NameFileKey, ios::out | ios::binary);
        if(!Key.is_open())
        {
            cout << "Key file is not open" << endl;
            return;
        }
        Algorithm->saveKeyFile(Key);
        cout << "Save key file..." << endl;
        Key.close();
    }
    //Откртие ключа
    void openKey(const char * NameFileKey)
    {
        if(!flagOpenFile)
        {
            cout << "Input File is not open! "<< endl;
            return;
        }
        ifstream Key(NameFileKey, ios::binary | ios::in);
        if(!Key.is_open())
        {
            cout << "Error opening key file!" << endl;
            return;
        }
        Algorithm->openKeyFile(Key);
        Key.close();
        cout << "Key file open" << endl;
    }
    //Декодирование файла
    void decodingFile(const char * nameDecodingFile)
    {
        if(!flagOpenFile)
        {
            cout << "File not open! ERROR!" << endl;
            return;
        }
        outFile.open(nameDecodingFile, ios::binary | ios::out);
        if(!outFile.is_open())
        {
            cout << "Error open file decoding! " << endl;
            return;
        }
        if(Algorithm->decoding(inFile, outFile));
        {
            outFile.close();
            flagDegodingFile = true;
            cout << "Save file decoding: OK" << endl;
        }
    }
    //Закрытие открытого файла
    void closeInFile()
    {
        if(!flagOpenFile)
        {
            cout << "Error close file. He is not open!" << endl;
            return;
        }
        inFile.close();
        flagOpenFile = false;
        cout << "Input Filse Close!" << endl;
    }

private:
    char * nameFile;
    bool flagOpenFile, flagSaveFileCoding, flagSaveFileDecoding, flagCodingFile, flagDegodingFile /* <- Под вопросом, нужна ли данная переменная */;
    HuffmanCoding * Algorithm;
    ifstream inFile;
    ofstream outFile;
};

#endif // CRYPTOALGORITHM_H
