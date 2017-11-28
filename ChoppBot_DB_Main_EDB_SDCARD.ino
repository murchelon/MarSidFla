/*
   EDB_SDCARD.pde
   Extended Database Library + External SD CARD storage demo

   Thanks to https://github.com/firebull/arduino-edb/ for the SD CARD example. 

   The Extended Database library project page is here:
   http://www.arduino.cc/playground/Code/ExtendedDatabaseLibrary

*/

#include "Arduino.h"


// Use the external SPI SD card as storage
#include <SPI.h>
#include <SD.h>

#define SD_PIN 10  // SD Card CS pin
#define TABLE_SIZE 8192

// The number of demo records that should be created.  This should be less
// than (TABLE_SIZE - sizeof(EDB_Header)) / sizeof(LogEvent).  If it is higher,
// operations will return EDB_OUT_OF_RANGE for all records outside the usable range.
#define RECORDS_TO_CREATE 10

char* db_name = "/db/users.db";

File dbFile;





// Arbitrary record definition for this table.
// This should be modified to reflect your record needs.
struct recUsuario {
    int id;
    int Nivel;
    String Nome;
    long Saldo;
}
recUsuario;

// The read and write handlers for using the SD Library
// Also blinks the led while writing/reading
inline void writer (unsigned long address, const byte* data, unsigned int recsize) {
    digitalWrite(13, HIGH);
    dbFile.seek(address);
    dbFile.write(data,recsize);
    dbFile.flush();
    digitalWrite(13, LOW);
}

inline void reader (unsigned long address, byte* data, unsigned int recsize) {
    digitalWrite(13, HIGH);
    dbFile.seek(address);
    dbFile.read(data,recsize);
    digitalWrite(13, LOW);
}




// Create an EDB object with the appropriate write and read handlers
EDB db(&writer, &reader);





void Init_Database()
{


    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);


    

    if (!SD.begin(SD_PIN)) 
    {
      LogTerm("Cartão SD não localizado");
      return;
    }
    else
    {
      LogTerm("Cartão SD inicializado com sucesso !");
    }


    randomSeed(analogRead(0));
    
    
    // Check dir for db files
    if (!SD.exists("/db")) {
        Serial.println("Dir for Db files does not exist, creating...");
        SD.mkdir("/db");
    }
    
    if (SD.exists(db_name)) {

        dbFile = SD.open(db_name, FILE_WRITE);

        // Sometimes it wont open at first attempt, espessialy after cold start
        // Let's try one more time
        if (!dbFile) {
            dbFile = SD.open(db_name, FILE_WRITE);
        }

        if (dbFile) {
            Serial.print("Openning current table... ");
            EDB_Status result = db.open(0);
            if (result == EDB_OK) {
                Serial.println("DONE");
            } else {
                Serial.println("ERROR");
                Serial.println("Did not find database in the file " + String(db_name));
                Serial.print("Creating new table... ");
                db.create(0, TABLE_SIZE, (unsigned int)sizeof(recUsuario));
                Serial.println("DONE");
                return;
            }
        } else {
            Serial.println("Could not open file " + String(db_name));
            return;
        }
    } else {
        Serial.print("Creating table... ");
        // create table at with starting address 0
        dbFile = SD.open(db_name, FILE_WRITE);
        db.create(0, TABLE_SIZE, (unsigned int)sizeof(recUsuario));
        Serial.println("DONE");
    }

    
    insertOneRecord(6, "Marcelo Rocha", 500, 1000);
    insertOneRecord(7, "Andre Costa", 500, 1000);
    
    
    //insertOneRecord(1);
    //insertOneRecord(1, "Joao");
    //insertOneRecord(2, "Antonio");

    LogTerm("registros inseridos");
    
    selectAll();

    dbFile.close();


}



// Run the demo
void ShowExample_DB()
{

  
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    Serial.begin(9600);
    Serial.println(" Extended Database Library + External SD CARD storage demo");
    Serial.println();

    randomSeed(analogRead(0));

    if (!SD.begin(SD_PIN)) {
        Serial.println("No SD-card.");
        return;
    }

    // Check dir for db files
    if (!SD.exists("/db")) {
        Serial.println("Dir for Db files does not exist, creating...");
        SD.mkdir("/db");
    }

    if (SD.exists(db_name)) {

        dbFile = SD.open(db_name, FILE_WRITE);

        // Sometimes it wont open at first attempt, espessialy after cold start
        // Let's try one more time
        if (!dbFile) {
            dbFile = SD.open(db_name, FILE_WRITE);
        }

        if (dbFile) {
            Serial.print("Openning current table... ");
            EDB_Status result = db.open(0);
            if (result == EDB_OK) {
                Serial.println("DONE");
            } else {
                Serial.println("ERROR");
                Serial.println("Did not find database in the file " + String(db_name));
                Serial.print("Creating new table... ");
                db.create(0, TABLE_SIZE, (unsigned int)sizeof(recUsuario));
                Serial.println("DONE");
                return;
            }
        } else {
            Serial.println("Could not open file " + String(db_name));
            return;
        }
    } else {
        Serial.print("Creating table... ");
        // create table at with starting address 0
        dbFile = SD.open(db_name, FILE_WRITE);
        db.create(0, TABLE_SIZE, (unsigned int)sizeof(recUsuario));
        Serial.println("DONE");
    }

    recordLimit();
    countRecords();
    createRecords(RECORDS_TO_CREATE);
    countRecords();
    selectAll();
    //deleteOneRecord(RECORDS_TO_CREATE / 2);
    //countRecords();
    //selectAll();
    //appendOneRecord(RECORDS_TO_CREATE + 1);
    //countRecords();
    //selectAll();
    //insertOneRecord(RECORDS_TO_CREATE / 2);
    //countRecords();
    //selectAll();
    //updateOneRecord(RECORDS_TO_CREATE);
    //selectAll();
    //countRecords();
    //deleteAll();
    //Serial.println("Use insertRec() and deleteRec() carefully, they can be slow");
    //countRecords();
    //for (int i = 1; i <= 20; i++) insertOneRecord(1);  // inserting from the beginning gets slower and slower
    //countRecords();
    //for (int i = 1; i <= 20; i++) deleteOneRecord(1);  // deleting records from the beginning is slower than from the end
    //countRecords();


    dbFile.close();
}







void ApagaConteudoSD()
{

    
    File root;
    int DeletedCount = 0;
    int FolderDeleteCount = 0;
    int FailCount = 0;
    String rootpath = "/";    
    
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    
    LogTerm("ApagaConteudoSD - INICIO");
    
    
    if (!SD.begin(SD_PIN)) {
        Serial.println("No SD-card.");
        return;
    }

    
    root = SD.open("/");
    delay(2000);
    


    
    //rm(root, rootpath);    
    
    
    while (true) {

      File entry = root.openNextFile();

      
      String localPath;
    
      if (! entry) {
        // no more files
        break;
      }

      
      //Serial.print(entry.name());
      
      if (entry.isDirectory()) 
      {

        localPath = rootpath + entry.name() + rootpath + '\0';
        char folderBuf[localPath.length()];
        localPath.toCharArray(folderBuf, localPath.length() );
        
        //LogTerm(strcat("Removendo Diretorio ", entry.name()));

        if( SD.rmdir( folderBuf ) )
        {
          Serial.print("Deleted folder ");
          Serial.println(folderBuf);
          FolderDeleteCount++;
        } 
        else
        {
          Serial.print("Unable to delete folder ");
          Serial.println(folderBuf);
          FailCount++;
        }
        

      }
      else
      {
      
        localPath = rootpath + entry.name() + '\0';
        char charBuf[localPath.length()];
        localPath.toCharArray(charBuf, localPath.length() );

        if( SD.remove( charBuf ) )
        {
          Serial.print("Deleted ");
          Serial.println(localPath);
          DeletedCount++;
        } 
        else
        {
          Serial.print("Failed to delete ");
          Serial.println(localPath);
          FailCount++;
        }
  
        

        //LogTerm(strcat("Removendo Arquivo ", entry.name()));

      }
      
      entry.close();
      
      
    }
    
    LogTerm("ApagaConteudoSD - FIM");

    return;
}



// utility functions

void recordLimit()
{
    Serial.print("Record Limit: ");
    Serial.println(db.limit());
}

void deleteOneRecord(int recno)
{
    Serial.print("Deleting recno: ");
    Serial.println(recno);
    db.deleteRec(recno);
}

void deleteAll()
{
    Serial.print("Truncating table... ");
    db.clear();
    Serial.println("DONE");
}

void countRecords()
{
    Serial.print("Record Count: ");
    Serial.println(db.count());
}

void createRecords(int num_recs)
{
    Serial.print("Creating Records... ");
    for (int recno = 1; recno <= num_recs; recno++)
    {
        recUsuario.id = recno;
        recUsuario.Nivel = 100;
        recUsuario.Nome = "Marcelo Rocha";
        recUsuario.Saldo = 250.25;
        EDB_Status result = db.appendRec(EDB_REC recUsuario);
        if (result != EDB_OK) printError(result);
    }
    Serial.println("DONE");
}

void selectAll()
{
    for (int recno = 1; recno <= db.count(); recno++)
    {
        EDB_Status result = db.readRec(recno, EDB_REC recUsuario);
        if (result == EDB_OK)
        {
            Serial.print("Recno: ");
            Serial.print(recno);
            Serial.print(" ID: ");
            Serial.print(recUsuario.id);
            Serial.print(" Nome: ");
            Serial.println(recUsuario.Nome);
        }
        else printError(result);
    }
}

void updateOneRecord(int recno)
{
    Serial.print("Updating record at recno: ");
    Serial.print(recno);
    Serial.print("... ");
    recUsuario.id = 3;
    recUsuario.Nome = "Jose";
    EDB_Status result = db.updateRec(recno, EDB_REC recUsuario);
    if (result != EDB_OK) printError(result);
    Serial.println("DONE");
}

void insertOneRecord(int _recno, String _Nome, int _Nivel, long _Saldo)
{
    Serial.print("Inserting record at recno: ");
    Serial.print(_recno);
    Serial.print("... ");
    
    recUsuario.id = _recno;
    recUsuario.Nivel = _Nivel;
    recUsuario.Nome = _Nome;
    recUsuario.Saldo = _Saldo;
    //EDB_Status result = db.insertRec(_recno, EDB_REC recUsuario);
    EDB_Status result = db.appendRec(EDB_REC recUsuario);
    if (result != EDB_OK) printError(result);
    Serial.println("DONE");
}

void appendOneRecord(int id)
{
    Serial.print("Appending record... ");
    recUsuario.id = id;
    recUsuario.Nivel = 600;
    recUsuario.Nome = "Sidney 600";
    recUsuario.Saldo = 20.00;
    EDB_Status result = db.appendRec(EDB_REC recUsuario);
    if (result != EDB_OK) printError(result);
    Serial.println("DONE");
}

void printError(EDB_Status err)
{
    Serial.print("ERROR: ");
    switch (err)
    {
        case EDB_OUT_OF_RANGE:
            Serial.println("Recno out of range");
            break;
        case EDB_TABLE_FULL:
            Serial.println("Table full");
            break;
        case EDB_OK:
        default:
            Serial.println("OK");
            break;
    }
}