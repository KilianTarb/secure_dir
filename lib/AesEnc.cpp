#include "AesEnc.h"

AesEnc::AesEnc(IndexFile *index, unsigned char *key, uint key_size) {
    _i = index;
    AES_set_encrypt_key(key, key_size, &_key);
}

void AesEnc::StartEncryption(
    void *file_begin_encrypt_callback(FileKey *file),
    void *file_encrypted_callback(FileKey *file)) {

    FileKeyCollection *file_collection = _i->GetFiles();

    for (FileKeyCollection::iterator it = file_collection->begin(); it != file_collection->end(); it++) {
        file_begin_encrypt_callback(it.base());

        FILE *source_file;
        source_file = fopen(it->filePath.c_str(), "r");

        FILE *dest_file;
        dest_file = fopen(it->EncyptedFileName.c_str(), "ab+");

        int current_read, total_read, byte_write;

        fseek(source_file, 0, SEEK_END);
        total_read = ftell(source_file);
        rewind(source_file);

        while (current_read < total_read) {
            unsigned char *in_block = (unsigned char *)malloc(AES_BLOCK_SIZE);
            unsigned char *out_block = (unsigned char *)malloc(AES_BLOCK_SIZE);

            current_read += fread(in_block, 1, AES_BLOCK_SIZE, source_file);

            AES_encrypt(in_block, out_block, &_key);

            byte_write = fwrite(out_block, 1, AES_BLOCK_SIZE, dest_file);
        }

        file_encrypted_callback(it.base());

        fclose(source_file);
        fclose(dest_file);
    }
}