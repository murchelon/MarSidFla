

#define SD_PIN 10  // SD Card CS pin
#define TABLE_SIZE 8192

// The number of demo records that should be created.  This should be less
// than (TABLE_SIZE - sizeof(EDB_Header)) / sizeof(LogEvent).  If it is higher,
// operations will return EDB_OUT_OF_RANGE for all records outside the usable range.
#define RECORDS_TO_CREATE 10

char* CB_db_name = "/db/ChoppBot_DB.db";
File CB_dbFile;


// Arbitrary record definition for this table.
// This should be modified to reflect your record needs.
struct CB_LogEvent {
    int id;
    int temperature;
}
CB_LogEvent;


// Create an EDB object with the appropriate write and read handlers
EDB CB_db(&writer, &reader);


void SD_Init()
{
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);


    LogTerm("Inicializando SD Card...");

    randomSeed(analogRead(0));

    if (!SD.begin(SD_PIN)) {
        Serial.println("Cartao nao inserido");
        return;
    }

    // Check dir for db files
    if (!SD.exists("/db")) {
        Serial.println("Diretorio do banco de dados nao criado. Criando direotorio...");
        SD.mkdir("/db");
    }



    CB_dbFile.close();

    LogTerm("Cartao SD inicializado.");

}
