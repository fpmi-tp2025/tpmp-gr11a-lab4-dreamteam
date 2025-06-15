#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
    static bool connect(const std::string& dbPath);
    static sqlite3* getDB();
private:
    static sqlite3* db;
};

#endif
