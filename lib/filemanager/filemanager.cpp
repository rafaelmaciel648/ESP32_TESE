#include "filemanager.h"

String readFile(String filename){
    File myFile;
    String content = "";

    while(!SD.begin(SS));

    myFile = SD.open(filename);
    if(myFile){
        while(myFile.available()){
            content.concat(char(myFile.read()));
        }
    }else{
        // FILE EMPTY
    }
    myFile.close();
    return content;
}

String getParam(const char* param, String file){
    const String begin_param = String("<" + String(param) + ">");
    const String end_param = String("</" + String(param) + ">");

    return file.substring( file.indexOf(begin_param)+begin_param.length(),file.indexOf(end_param) );
};

String getParamInIndice(const char* param, String file, int i){
    const String begin_param = String("<" + String(param) + ">");
    const String end_param = String("</" + String(param) + ">");
    int n=0;

    for(int aux=0; aux<file.length(); aux++){
        if( file.substring(aux,aux+8) == begin_param ){
            n++;
        }
        if( n == i){
            file = file.substring(aux);
            break;
        }
    }

    return file.substring( file.indexOf(begin_param)+begin_param.length(),file.indexOf(end_param) );
};