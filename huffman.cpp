#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
using namespace std;

//Класс ячеек дерева
class Node
{
public:
    Node()
        : left(nullptr), right(nullptr)
    {}
    Node(Node * LeftNode, Node * RightNode)
        : left(LeftNode), right(RightNode), number(LeftNode->number + RightNode->number)
    {}
public:
    int number;
    char value;
    Node * left, * right;
};
class huffman
{
public:
    huffman()
    {
        H_weight = new map<char, int>;
        H_nodeList = new list<Node *>;
        H_code = new vector <bool>;
        H_table = new map<char, vector<bool> >;
        H_resultBinCode = new vector<bool>;
    }
    ~huffman()
    {
        delete H_weight;
        delete H_nodeList;
        delete H_code;
        delete H_table;
        delete H_resultBinCode;
    }
public:
    void coding(ifstream &inFile)
    {
        createWeight(inFile);
        printWeight();
        createListNode();
        createTree();
        createTable(H_root);
    }
    int saveCodFile(ifstream &inFile, ofstream &outFile)
    {
        return saveCodingFile(inFile, outFile);
    }
    int decoding(ifstream &inFile_encoded, ofstream &outFile_decoded)
    {
        return decodingEncodeFile(inFile_encoded, outFile_decoded);
    }

private:
    //Получение количества встречаемых сомволов в файле
    void createWeight(ifstream &inFile)
    {
        char ch;
        inFile.read((char *) &ch, sizeof ch);
        while(!inFile.eof())
        {
            ++(*H_weight)[ch];
            cout << ch;
            inFile.read((char *) &ch, sizeof ch);
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
        for (itrWeight = H_weight->begin(); itrWeight != H_weight->end(); itrWeight++)
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
        if(Root->value)
            (*H_table)[Root->value] = (*H_code); //ПРОБЛЕМА ВЕРОЯТНЕЕ ТУТ!
        H_code->pop_back();
    }
    //Сохранение готового закодированного файла
    int saveCodingFile(ifstream &inFile, ofstream &newCodingFile)
    {
        vector<bool> * BufferBinCode = new vector<bool>;
        size_t count = 0;
        char ch, buf = 0;
        inFile.clear();
        inFile.seekg(0);
        inFile.read((char *) &ch, sizeof ch);
        while(!inFile.eof())
        {
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
            inFile.read((char *) &ch, sizeof ch);
        }
        delete BufferBinCode;
        return 1;
    }
private:
    //Декодирование зашифрованного файла
    int decodingEncodeFile(ifstream &inFile_encoded, ofstream &outFile_decoded)
    {

        Node * ptr = H_root;
        size_t count = 0;
        char byte;
        inFile_encoded.clear();
        inFile_encoded.seekg(0);
        inFile_encoded.read((char *) &byte, sizeof byte);
        while(!inFile_encoded.eof())
        {
            bool buf = byte & (1 << (7 - count));
            if(buf)
                ptr = ptr->right;
            else
                ptr = ptr->left;
            if(ptr->left == nullptr && ptr->right == nullptr)
            {
                outFile_decoded.write((char *) &ptr->value, sizeof ptr->value);
                ptr = H_root;
            }
            ++count;
            if(count == 8)
            {
                count = 0;
                inFile_encoded.read((char *) &byte, sizeof byte);
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
private:
    map<char, int> * H_weight;
    list <Node *> * H_nodeList;
    vector <bool> * H_code;
    map<char, vector<bool> > * H_table;
    vector<bool> * H_resultBinCode;
    Node * H_root;
};

//Управляющий класс алгоритмом и другими вещами
class crypto
{
public:
    crypto(char * nameFile)
        : nameFile(nameFile), Algorithm(nullptr), flagOpenFile(false), flagSaveFileCoding(false), flagSaveFileDecoding(false), flagCodingFile(false), flagDegodingFile(false)
    {
        openFile(nameFile);
        Algorithm = new huffman;
    }
    ~crypto()
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
    void saveKey()
    {

    }
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
    huffman * Algorithm;
    ifstream inFile;
    ofstream outFile;
};
int main(void)
{
    char nameFile[] = "E:/1.djvu";
    char CodeFile[] = "E:/2.djvu";
    char deCodeFile[] = "E:/3.djvu";
    cout << "Name file: " << nameFile << endl;
    crypto file(nameFile);
    file.codingFile();
    system("pause");
    file.saveCodingFile(CodeFile);
    file.closeInFile();
    system("pause");
    file.openFile(CodeFile);
    file.decodingFile(deCodeFile);
    file.closeInFile();
    return 0;
}
