#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H
#include <node.h>
using namespace std;

//Класс, характеризующий алгоритм
class HuffmanCoding
{
public:
    HuffmanCoding()
    {
        H_weight = new map<char, int>;
        H_nodeList = new list<Node *>;
        H_code = new vector <bool>;
        H_table = new map<char, vector<bool> >;
        H_DecodTable = new map<vector<bool>, char>;
        H_resultBinCode = new vector<bool>;
    }
    ~HuffmanCoding()
    {
        delete H_weight;
        delete H_nodeList;
        delete H_code;
        delete H_table;
        delete H_resultBinCode;
        delete H_DecodTable;
    }
public:
    //Кодирование файла
    void coding(ifstream &inFile)
    {
        createWeight(inFile);
//        printWeight();
        createListNode();
        createTree();
        createTable(H_root);
//        printTable();
    }
    //Сохранение кодированного файла
    int saveCodFile(ifstream &inFile, ofstream &outFile)
    {
        return saveCodingFile(inFile, outFile);
    }
    //Декодирование файла
    int decoding(ifstream &inFile_encoded, ofstream &outFile_decoded)
    {
        return decodingEncodeFile(inFile_encoded, outFile_decoded);
    }
    //Сохранение ключа
    void saveKeyFile(ofstream &Key)
    {
        _saveKeyFile(Key);
    }
    //Открытие ключа
    void openKeyFile(ifstream &Key)
    {
        _openKeyFile(Key);
    }
private:
    //Получение количества встречаемых сомволов в файле
    void createWeight(ifstream &inFile)
    {
        char ch;
        while(!inFile.eof())
        {
            inFile.read((char *) &ch, sizeof ch);
            ++(*H_weight)[ch];
        }
    }
    //Вывод весов
    void printWeight()
    {
        map<char, int>::iterator itrWeight;
        for(itrWeight = H_weight->begin(); itrWeight != H_weight->end(); itrWeight++)
            cout << itrWeight->second << " : " << itrWeight->first << endl;
    }
    //Создание листа ячеяк
    void createListNode()
    {
        map<char, int>::iterator itrWeight;
        for (itrWeight = H_weight->begin(); itrWeight != H_weight->end(); ++itrWeight)
        {
            //Создание новых узлов
            Node * newNode = new Node;
            newNode->value = itrWeight->first;
            newNode->number = itrWeight->second;
            H_nodeList->push_back(newNode);
        }
    }
    //Создание дерева
    void createTree()
    {
        while(H_nodeList->size() != 1)
        {
            //Сортировка
            H_nodeList->sort(compare());
            //удаление первых элементов списка
            Node * SonL = H_nodeList->front();
            H_nodeList->pop_front();
            Node * SonR = H_nodeList->front();
            H_nodeList->pop_front();
            //На основе удаленных создаю отца
            Node * Parent = new Node(SonL, SonR);
            H_nodeList->push_back(Parent);
        }
        //Корень дерева
        H_root = H_nodeList->front();
    }
    //Создание таблицы: символ - код
    void createTable(Node * Root)
    {
        if(Root->left != nullptr)
        {
            H_code->push_back(0);
            createTable(Root->left);
        }
        if(Root->right != nullptr)
        {
            H_code->push_back(1);
            createTable(Root->right);
        }
        if(Root->left == nullptr && Root->right == nullptr)
        {
            (*H_table)[Root->value] = (*H_code); //ПРОБЛЕМА ВЕРОЯТНЕЕ ТУТ!
        }
        H_code->pop_back();
    }
    //Вывод таблицы
    void printTable()
    {
        vector<bool> * BufferBinCode = new vector<bool>;
        map<char, vector<bool> >::iterator itr;
        for(itr = H_table->begin(); itr != H_table->end(); ++itr)
        {
            char ch = itr->first;
            if(ch == ' ') cout << "space";
            cout << itr->first << " : " ;
            (*BufferBinCode) = (*H_table)[ch];
            for(size_t n = 0; n < BufferBinCode->size(); ++n)
            {
                cout << (*BufferBinCode)[n];
            }
            cout << endl;
        }
        delete BufferBinCode;
    }
    //Сохранение готового закодированного файла
    int saveCodingFile(ifstream &inFile, ofstream &newCodingFile)
    {
        vector<bool> * BufferBinCode = new vector<bool>;
        size_t count = 0;
        char ch, buf = 0;
        inFile.clear();
        inFile.seekg(0);
        while(!inFile.eof())
        {
            inFile.read((char *) &ch, sizeof ch);
            (*BufferBinCode) = (*H_table)[ch];
            for(size_t n = 0; n < BufferBinCode->size(); ++n)
            {
                buf = buf | (*BufferBinCode)[n] << (7 - count);
                ++count;
                if(count == 8)
                {
                    count = 0;
                    newCodingFile.write((char *) &buf, sizeof buf);
                    buf = 0;
                }
            }
        }
        delete BufferBinCode;
        return 1;
    }
    //Сохранение ключа
    void _saveKeyFile(ofstream &Key) const
    {
        map<char, vector<bool> >::iterator itr;
        for(itr = H_table->begin(); itr != H_table->end(); ++itr)
        {
            structKey keyBuff;
            vector<bool> code = itr->second;
            char byte[2] = "";
            for(size_t i = 0; i < code.size(); ++i)
            {
                byte[0] = code[i] ? '1' : '0';
                strcat(keyBuff.code, byte);
            }
            keyBuff.ch = itr->first;
            Key.write((char *) &(keyBuff), sizeof(keyBuff));
            strcpy(keyBuff.code, "");
        }
    }
    //Открытие ключа
    void _openKeyFile(ifstream &Key)
    {
        structKey keyBuff;
        Key.read((char *) &(keyBuff), sizeof(structKey));
        while(!Key.eof())
        {
            vector<bool> codeBuff;
            for(size_t j = 0; j < strlen(keyBuff.code); j++)
            {
                bool byte;
                if((keyBuff.code)[j] == '1')
                    byte = true;
                else if((keyBuff.code)[j] == '0')
                    byte = false;
                codeBuff.push_back(byte);
            }
            char ch = keyBuff.ch;
            (*H_DecodTable)[codeBuff] = ch;
            Key.read((char *) &(keyBuff), sizeof(structKey));
        }
//        // Проверка, что ключ открылся корректно
//        map<vector<bool>, char>::iterator itr;
//        for(itr = H_DecodTable->begin(); itr != H_DecodTable->end(); ++itr)
//        {
//            cout << itr->second << " ";
//            for(size_t n = 0; n < (itr->first).size(); ++n)
//                cout << (itr->first)[n];
//            cout << endl;
//        }
    }
private:
    //Декодирование зашифрованного файла
    int decodingEncodeFile(ifstream &inFile_encoded, ofstream &outFile_decoded)
    {
        vector<bool> codeBuff;
        size_t count = 0;
        char byte = inFile_encoded.get();
        while(!inFile_encoded.eof())
        {
            bool buf = byte & (1 << (7 - count));
            codeBuff.push_back(buf);
            for(map<vector<bool>, char>::iterator itr = H_DecodTable->begin(); itr != H_DecodTable->end(); ++itr)
            {
                if((itr->first) == codeBuff)
                {
                    char valueChar = itr->second;
                    outFile_decoded.write((char *) &valueChar, sizeof(valueChar));
                    codeBuff.clear();
                }
            }
            ++count;
            if(count == 8)
            {
                count = 0;
                byte = inFile_encoded.get();
            }
        }
        return 1;
    }
private:
    //Структура для сравнения ячеек при сортировке
    struct compare
    {
        bool operator() (Node * left, Node * right) const
        {
            return left->number < right->number;
        }
    };
    //Структурка для записи чтения ключа из файла
    struct structKey
    {
        char ch;
        char code[100];
    };
private:
    map<char, int> * H_weight;
    list <Node *> * H_nodeList;
    vector <bool> * H_code;
    map<char, vector<bool> > * H_table;
    map<vector<bool>, char> * H_DecodTable;
    vector<bool> * H_resultBinCode;
    Node * H_root;
};

#endif // HUFFMANCODING_H
