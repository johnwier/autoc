#pragma once
#include <fstream>
#include <vector>
using namespace std;

typedef enum _handlerType_e{
    STD = 0,
    BINARY,
    TEXT
} handlerType_e;

class IoHandler{
    protected:
        string filename;
    public:
        virtual int read(vector<pair<string,int>>&);
        virtual int write(vector<pair<string,int>>&);
};

IoHandler* createIoHandler(handlerType_e type, string filename);

class IoStd : public IoHandler {
    public:
        IoStd();
        ~IoStd();
        int read(vector<pair<string,int>>&);
        int write(vector<pair<string,int>>&);
        static int dumpDictionary(vector<pair<string,int>>&);
};

class IoTxt : public IoHandler {
    public:
        IoTxt(string);
        ~IoTxt();
        int read(vector<pair<string,int>>&);
        int write(vector<pair<string,int>>&);
};

class IoBinary : public IoHandler {
    public:
        IoBinary(string);
        ~IoBinary();
        int read(vector<pair<string,int>>&);
        int write(vector<pair<string,int>>&);
};
