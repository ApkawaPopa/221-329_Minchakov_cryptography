#include "sgx_urts.h" // вместо #include <string.h>
#include "sgx_tseal.h"
#include "crypt-lab3-enclave_u.h" // !!! вписать свой
#define ENCLAVE_FILE L"crypt-lab3-enclave.signed.dll" // !!! вписать свой

#include <cstdio>

int main() {
    sgx_enclave_id_t eid;
    sgx_status_t ret = SGX_SUCCESS;
    sgx_launch_token_t token = { 0 };
    int updated = 0;

    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("App: error %#x, failed to create enclave.\n", ret);
        return -1;
    }

    int req_index = -1;
    char outbuffer[1024] = { 0 };
    printf_s("Input array index: ");
    int result = scanf_s("%d", &req_index);
    getPD(eid, outbuffer, 1024, req_index);
    printf_s("String[index]: %s\n", outbuffer);
    std:system("pause");

    if (SGX_SUCCESS != sgx_destroy_enclave(eid))
        return -1;

    return 0;
}