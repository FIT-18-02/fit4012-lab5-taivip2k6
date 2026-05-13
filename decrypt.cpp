/* decrypt.cpp
 * Performs decryption using AES 128-bit
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "structures.h"

using namespace std;

void SubRoundKey(unsigned char * state, unsigned char * roundKey) {

    for (int i = 0; i < 16; i++) {
        state[i] ^= roundKey[i];
    }
}

void InverseMixColumns(unsigned char * state) {

    unsigned char tmp[16];

    tmp[0]  = (unsigned char)mul14[state[0]]  ^ mul11[state[1]]  ^ mul13[state[2]]  ^ mul9[state[3]];
    tmp[1]  = (unsigned char)mul9[state[0]]   ^ mul14[state[1]]  ^ mul11[state[2]]  ^ mul13[state[3]];
    tmp[2]  = (unsigned char)mul13[state[0]] ^ mul9[state[1]]   ^ mul14[state[2]]  ^ mul11[state[3]];
    tmp[3]  = (unsigned char)mul11[state[0]] ^ mul13[state[1]]  ^ mul9[state[2]]   ^ mul14[state[3]];

    tmp[4]  = (unsigned char)mul14[state[4]] ^ mul11[state[5]]  ^ mul13[state[6]]  ^ mul9[state[7]];
    tmp[5]  = (unsigned char)mul9[state[4]]  ^ mul14[state[5]]  ^ mul11[state[6]]  ^ mul13[state[7]];
    tmp[6]  = (unsigned char)mul13[state[4]] ^ mul9[state[5]]   ^ mul14[state[6]]  ^ mul11[state[7]];
    tmp[7]  = (unsigned char)mul11[state[4]] ^ mul13[state[5]]  ^ mul9[state[6]]   ^ mul14[state[7]];

    tmp[8]  = (unsigned char)mul14[state[8]] ^ mul11[state[9]]  ^ mul13[state[10]] ^ mul9[state[11]];
    tmp[9]  = (unsigned char)mul9[state[8]]  ^ mul14[state[9]]  ^ mul11[state[10]] ^ mul13[state[11]];
    tmp[10] = (unsigned char)mul13[state[8]] ^ mul9[state[9]]   ^ mul14[state[10]] ^ mul11[state[11]];
    tmp[11] = (unsigned char)mul11[state[8]] ^ mul13[state[9]]  ^ mul9[state[10]]  ^ mul14[state[11]];

    tmp[12] = (unsigned char)mul14[state[12]] ^ mul11[state[13]] ^ mul13[state[14]] ^ mul9[state[15]];
    tmp[13] = (unsigned char)mul9[state[12]]  ^ mul14[state[13]] ^ mul11[state[14]] ^ mul13[state[15]];
    tmp[14] = (unsigned char)mul13[state[12]] ^ mul9[state[13]]  ^ mul14[state[14]] ^ mul11[state[15]];
    tmp[15] = (unsigned char)mul11[state[12]] ^ mul13[state[13]] ^ mul9[state[14]]  ^ mul14[state[15]];

    for (int i = 0; i < 16; i++) {
        state[i] = tmp[i];
    }
}

void ShiftRows(unsigned char * state) {

    unsigned char tmp[16];

    tmp[0]  = state[0];
    tmp[1]  = state[13];
    tmp[2]  = state[10];
    tmp[3]  = state[7];

    tmp[4]  = state[4];
    tmp[5]  = state[1];
    tmp[6]  = state[14];
    tmp[7]  = state[11];

    tmp[8]  = state[8];
    tmp[9]  = state[5];
    tmp[10] = state[2];
    tmp[11] = state[15];

    tmp[12] = state[12];
    tmp[13] = state[9];
    tmp[14] = state[6];
    tmp[15] = state[3];

    for (int i = 0; i < 16; i++) {
        state[i] = tmp[i];
    }
}

void SubBytes(unsigned char * state) {

    for (int i = 0; i < 16; i++) {
        state[i] = inv_s[state[i]];
    }
}

void Round(unsigned char * state, unsigned char * key) {

    SubRoundKey(state, key);
    InverseMixColumns(state);
    ShiftRows(state);
    SubBytes(state);
}

void InitialRound(unsigned char * state, unsigned char * key) {

    SubRoundKey(state, key);
    ShiftRows(state);
    SubBytes(state);
}

void AESDecrypt(
    unsigned char * encryptedMessage,
    unsigned char * expandedKey,
    unsigned char * decryptedMessage
) {

    unsigned char state[16];

    for (int i = 0; i < 16; i++) {
        state[i] = encryptedMessage[i];
    }

    InitialRound(state, expandedKey + 160);

    for (int i = 8; i >= 0; i--) {
        Round(state, expandedKey + (16 * (i + 1)));
    }

    SubRoundKey(state, expandedKey);

    for (int i = 0; i < 16; i++) {
        decryptedMessage[i] = state[i];
    }
}

int main() {

    cout << "=============================" << endl;
    cout << " 128-bit AES Decryption Tool " << endl;
    cout << "=============================" << endl;

    ifstream infile("message.aes", ios::binary);

    if (!infile) {
        cout << "Unable to open message.aes" << endl;
        return 1;
    }

    vector<unsigned char> encryptedMessage(
        (istreambuf_iterator<char>(infile)),
        istreambuf_iterator<char>()
    );

    infile.close();

    cout << "Read encrypted message from message.aes" << endl;

    string keystr;

    ifstream keyfile("keyfile");

    if (!keyfile) {
        cout << "Unable to open keyfile" << endl;
        return 1;
    }

    getline(keyfile, keystr);

    keyfile.close();

    cout << "Read in the 128-bit key from keyfile" << endl;

    istringstream hex_chars_stream(keystr);

    unsigned char key[16];

    int i = 0;
    unsigned int c;

    while (hex_chars_stream >> hex >> c) {

        key[i] = c;
        i++;
    }

    unsigned char expandedKey[176];

    KeyExpansion(key, expandedKey);

    int messageLen = encryptedMessage.size();

    unsigned char * decryptedMessage =
        new unsigned char[messageLen];

    for (int i = 0; i < messageLen; i += 16) {

        AESDecrypt(
            encryptedMessage.data() + i,
            expandedKey,
            decryptedMessage + i
        );
    }

    cout << "Decrypted message in hex:" << endl;

    for (int i = 0; i < messageLen; i++) {

        cout << hex
             << setw(2)
             << setfill('0')
             << (int)decryptedMessage[i]
             << " ";
    }

    cout << endl;

    cout << "Decrypted message: ";

    for (int i = 0; i < messageLen; i++) {

        if (decryptedMessage[i] != 0x00) {
            cout << decryptedMessage[i];
        }
    }

    cout << endl;

    delete[] decryptedMessage;

    return 0;
}
