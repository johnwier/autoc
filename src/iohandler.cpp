#include <cstddef>
#include <iostream>
#include "iohandler.h"
#include <vector>

IoHandler* createIoHandler(handlerType_e type, string filename){
    switch(type){
        case STD:
            return new IoStd();
        case TEXT:
            return new IoTxt(filename);
        case BINARY:
            return new IoBinary(filename);
        default:
            return NULL;
    };
}

int IoHandler::read(vector<pair<string,int>>& dictionary){ return 0;}
int IoHandler::write(vector<pair<string,int>>& dictionary){ return 0;}


/**
 * IoStd
 */
IoStd::IoStd(){ }

int IoStd::read(vector<pair<string,int>>&dictionary){
    cout << "No file. Starting fresh" << endl;
    return 0;
}
int IoStd::write(vector<pair<string,int>>&dictionary){
    return dumpDictionary(dictionary);
}

int IoStd::dumpDictionary(vector<pair<string,int>>&dictionary){
    cout << endl << "String\tCount" << endl;
    for(const auto &entry : dictionary){
        cout << entry.first << '\t' << entry.second << endl;
    }
    return 0;
}


/**
 * IoTxt
 */
IoTxt::IoTxt(string filename){
    cout << "Open file " << filename << endl;
    this->filename = filename;
}

IoTxt::~IoTxt(){ }

int IoTxt::read(vector<pair<string,int>>&dictionary){
    string key;
    int weight;
    cout<<"Txt read"<<endl;
    ifstream fp(filename, ios::in);
    while(fp >> key >> weight){
        dictionary.push_back(make_pair(key, weight));
    }
    fp.close();
    return 0;
}

int IoTxt::write(vector<pair<string,int>>&dictionary){
    ofstream fp(filename, ios::out | ios::trunc);
    for(const auto& entry : dictionary){
        fp << entry.first << " " << entry.second << endl;
    }
    fp.close();
    return 0;
}

IoBinary::IoBinary(string filename){
    cout << "Open file " << filename << endl;
    this->filename = filename;
}

IoBinary::~IoBinary(){ }

int IoBinary::read(vector<pair<string,int>>&dictionary){
    ifstream fp;
    fp.open(filename, ios::in | ios::binary);
    string text;
    int weight;
    for(;;){
        getline(fp, text, '\0');
        if(!fp.good()) break;
        fp.read((char*)&weight, sizeof(weight));
        dictionary.push_back(make_pair(text, weight));
    }
    fp.close();
    return 0;
}

int IoBinary::write(vector<pair<string,int>>&dictionary){
    ofstream fp;
    fp.open(filename, ios::out | ios::binary | ios::trunc);
    for(const auto& entry : dictionary){
        fp.write(entry.first.c_str(), entry.first.length()+1);
        fp.write((char*)&entry.second, sizeof(entry.second));
    }
    fp.close();
    return 0;
}
