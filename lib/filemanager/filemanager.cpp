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
        if( file.substring(aux,aux+begin_param.length()) == begin_param ){
            n++;
        }
        if( n == i+1){
            file = file.substring(aux);
            break;
        }
    }

    return file.substring( file.indexOf(begin_param)+begin_param.length(),file.indexOf(end_param) );
};

bool writeFile(String filename, String toWrite){
    File myFile;
    String content = "";

    while(!SD.begin(SS));

    myFile = SD.open(filename,FILE_APPEND);

    if(myFile){                                 // Correct opening
        myFile.print(toWrite);
        myFile.close();
        return true;
    }else{                                      // Wrong opening
        myFile.close();
        return false;
    }
    
}

bool createBlankFile(String filename){
    File myFile;

    while(!SD.begin(SS));

    if( SD.exists(filename) ){
        SD.remove(filename);
        myFile = SD.open(filename,FILE_WRITE);
        if(myFile){                                 // Correct creation
            myFile.close();
            return true;
        }else{                                      // Wrong creation
            myFile.close();
            return false;
        }
    }
    else{
        myFile = SD.open(filename,FILE_WRITE);
        if(myFile){                                 // Correct creation
            myFile.close();
            return true;
        }else{                                      // Wrong creation
            myFile.close();
            return false;
        }
    }
}

// bool checkExistFile(String filename){
//     while(!SD.begin(SS));

//     if( SD.exists(filename) ){

//     }
// }