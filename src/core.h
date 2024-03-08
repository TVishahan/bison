#pragma once

#include <nlohmann/json.hpp>

enum {

};

struct stBatchFile {
    unsigned int uid;
    char** name;
    char** path;
    stBatchFile* header;
    stBatchFile* next;
    stBatchFile* footer;
    bool enabled;

    unsigned int flags;
};