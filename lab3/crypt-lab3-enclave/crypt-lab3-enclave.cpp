#include "crypt-lab3-enclave_t.h"
#include "sgx_trts.h"
#include <string.h>

const char* PersonalData[] = {
    "mysqld, also known as MySQL Server, is a single multithreaded program that does most of the work in a MySQL",
    "installation. It does not spawn additional processes. MySQL Server manages access to the MySQL data",
    "directory that contains databases and tables. The data directory is also the default location for other",
    "information such as log files and status files. Some installation packages contain a debugging version of",
    "the server named mysqld-debug. Invoke this version instead of mysqld for debugging support, memory",
    "allocation checking, and trace file support (see Section 7.9.1.2, “Creating Trace Files”).",
    "When MySQL server starts, it listens for network connections from client programs and manages access to",
    "databases on behalf of those clients. The mysqld program has many options that can be specified at startup.",
    "For a complete list of options, run this command: mysqld --verbose --help MySQL Server also has a set of",
    "system variables that affect its operation as it runs. System variables can be set at server startup, and",
    "many of them can be changed at runtime to effect dynamic server reconfiguration. MySQL Server also has a",
    "set of status variables that provide information about its operation. You can monitor these status",
    "variables to access runtime performance characteristics. For a full description of MySQL Server command",
    "options, system variables, and status variables, see Section 7.1, “The MySQL Server”. For information",
    "about installing MySQL and setting up the initial configuration, see Chapter 2, Installing MySQL."
};


void getPD(char* outbuffer, size_t len, int i) {
    size_t array_size = sizeof(PersonalData) / sizeof(char*);
    if (i < 0 || i >= array_size) {
        memcpy(outbuffer, "Wrong index!", len);
        return;
    }
    memcpy(outbuffer, PersonalData[i], len);
    return;
}