#include "datalogger.h"
#include "LinkedList.h"
#include "utils.h"
#include "filemanager.h"

extern LinkedList<DataItemList*> dataValues;

void logData(){
    if(dataValues.size() <= 0) return;

    DataItemList *aux;
    String log = "";
    while(dataValues.size() > 0){
        aux = dataValues.shift();
        // DEFINE STRING LOG TO PRINT
        log.concat("TIME_STAMP,");
        if(aux->param == 1){             // Temperature
            log.concat(" TEMP, ");
        }
        else if(aux->param == 2){        // PH
            log.concat(" PH, ");
        }
        else if(aux->param == 3){        // Dissolved Oxygen
            log.concat(" DO, ");    
        }
        else if(aux->param == 4){        // Conductivity
            log.concat(" COND, ");
        }
        log.concat(aux->value);
        log.concat("\n");
    }

    Serial.print(log);

    if( writeFile("/data/logger.txt", log) ){
    }else{
    
    }
}

bool newLogFile(String filename){
    if( createBlankFile(filename) ){
        return true;
    }
    else{
        return false;
    }
}
