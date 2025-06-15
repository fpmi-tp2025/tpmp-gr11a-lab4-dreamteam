#include "database.h"
#include <iostream>

sqlite3* Database::db = nullptr;

bool Database::connect(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    std::cout << "Connected to database." << std::endl;
    return true;
}

sqlite3* Database::getDB() {
    return db;
}
