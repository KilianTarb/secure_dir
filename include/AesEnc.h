#include "indexfile.h"
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/aes.h>

class AesEnc {
    private:
        IndexFile *_i;
        AES_KEY _key;
    public:
        AesEnc(IndexFile *index, unsigned char *key, uint key_size);
        void StartEncryption(void *file_begin_encrypt_callback(FileKey *file), void *on_file_encrypted(FileKey *file));
};