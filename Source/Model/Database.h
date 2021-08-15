#ifndef DATABASE_H
#define DATABASE_H

#include "Definition.h"

#include <string>
#include <vector>

using namespace std;

namespace Model {

struct DatabaseAttribute {
    UuidType total;
    UuidType blockTotal;
    string name;

    DatabaseAttribute() : total(0), blockTotal(0), name("") {}
    ~DatabaseAttribute() {}
};

struct DatabaseBlock {
    UuidType uuid;
    vector<string> data;

    DatabaseBlock() : uuid(0) {}
    DatabaseBlock(UuidType id, const vector<string> &v) : uuid(id), data(v) {}
    ~DatabaseBlock() {}

    void setUuid(int id) {
        uuid = id;
    }

    UuidType getUuid() {
        return uuid;
    }
};

class DatabaseController {
public:
    DatabaseController(string name = "");
    ~DatabaseController();

    void open(string name);
    void close();

    DatabaseAttribute getAttribute() const;
    DatabaseBlock getBlock(UuidType id) const;

    void setAttribute(DatabaseAttribute attr);
    void setBlock(UuidType id, DatabaseBlock block);
private:
    DatabaseAttribute attribute;

    string getFileName(string dir, string name, string prefix) const;
};

}

#endif