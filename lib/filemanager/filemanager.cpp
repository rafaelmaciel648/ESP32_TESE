#include "filemanager.h"

String findParamInFile(const char* param, String filename){
    File myFile;
    String aux = "";

    while(!SD.begin(SS));

    myFile = SD.open(filename);
    
    if(myFile){
        while(myFile.available()){
            if(myFile.find(param)){
                aux = myFile.readStringUntil('<');
            }
        }
    }else{
        // FILE EMPTY
    }
    myFile.close();
    return aux;
};
