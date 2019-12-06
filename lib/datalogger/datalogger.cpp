#include "datalogger.h"
#include "LinkedList.h"
#include "myutils.h"
#include "filemanager.h"
#include "rtcmodule.h"

extern LinkedList<DataItemList*> dataValues;

void logData(){
    if(dataValues.size() <= 0) return;

    DataItemList *aux;
    String log = "";
    String logTEMP = "";
    String logPH = "";
    String logDO = "";
    String logCOND = "";
    String str = "";
    
    while(dataValues.size() > 0){
        aux = dataValues.shift();
        // DEFINE STRING LOG TO PRINT
        switch(aux->param){
            case 1:
                str.concat(aux->timestamp);
                str.concat(" , TEMP , ");
                str.concat(aux->value);
                str.concat("\n");
                logTEMP.concat(str);
                break;
            case 2:
                str.concat(aux->timestamp);
                str.concat(" ,  PH  , ");
                str.concat(aux->value);
                str.concat("\n");
                logPH.concat(str);
                break;
            case 3:
                str.concat(aux->timestamp);
                str.concat(" ,  DO  , ");
                str.concat(aux->value);
                str.concat("\n");
                logDO.concat(str);
                break;
            case 4:
                str.concat(aux->timestamp);
                str.concat(" , COND , ");
                str.concat(aux->value);
                str.concat("\n");
                logCOND.concat(str);
                break;
        }

        log.concat(str);
        str = "";
    }

    Serial.print(log);

    if( logTEMP.length() > 0){
        if( !writeFile("/log/logTemp.txt", logTEMP) ){
            #ifdef DEBUG
            Serial.println("Error: printing logTemp.txt");
            #endif
        }
    }
    
    if(logPH.length() > 0){
        if( !writeFile("/log/logPh.txt", logPH) ){
            #ifdef DEBUG
            Serial.println("Error: printing logTemp.txt");
            #endif
        }
    }

    if(logDO.length() > 0){
        if( !writeFile("/log/logDo.txt", logDO) ){
            #ifdef DEBUG
            Serial.println("Error: printing logTemp.txt");
            #endif
        }
    }

    if(logCOND.length() > 0){
        if( !writeFile("/log/logCond.txt", logCOND) ){
            #ifdef DEBUG
            Serial.println("Error: printing logTemp.txt");
            #endif
        }
    }

    if( !writeFile("/log/datalogger.txt", log) ){
        #ifdef DEBUG
        Serial.println("Error: printing datalogger.txt");
        #endif
    }
    return;
}

bool newLogFile(String filename){
    if( createBlankFile(filename) ){
        return true;
    }
    else{
        return false;
    }
}

// bool checkExistFile(String filename){

// }


        // log.concat(aux->timestamp);
        // if(aux->param == 1){             // Temperature
        //     log.concat(" , TEMP , ");
        //     log.concat(aux->value);
        //     log.concat("\n");
        // }
        // else if(aux->param == 2){        // PH
        //     log.concat(" ,  PH  , ");
        //     log.concat(aux->value);
        //     log.concat("\n");
        // }
        // else if(aux->param == 3){        // Dissolved Oxygen
        //     log.concat(" ,  DO  , ");
        //     log.concat(aux->value);
        //     log.concat("\n");    
        // }
        // else if(aux->param == 4){        // Conductivity
        //     log.concat(" , COND , ");
        //     log.concat(aux->value);
        //     log.concat("\n");
        // }