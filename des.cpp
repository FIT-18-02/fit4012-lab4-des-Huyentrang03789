#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

// HELPER
string xor_str(const string &a, const string &b) {
    string res = "";
    for (int i = 0; i < a.size(); i++) {
        res += (a[i] != b[i]) ? '1' : '0';
    }
    return res;
}

// PERMUTATION
string initial_permutation(const string &input) {
    int ip[64] = {
        58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
    };

    string out = "";
    for (int i = 0; i < 64; i++)
        out += input[ip[i] - 1];
    return out;
}

string inverse_initial_permutation(const string &input) {
    int ip_inv[64] = {
        40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
    };

    string out = "";
    for (int i = 0; i < 64; i++)
        out += input[ip_inv[i] - 1];
    return out;
}

// KEY GENERATOR 
class KeyGenerator {
private:
    string key;

public:
    KeyGenerator(string k) : key(k) {}

    vector<string> generate() {
        vector<string> roundKeys;

        int pc1[56] = {
            57,49,41,33,25,17,9,1,58,50,42,34,26,18,
            10,2,59,51,43,35,27,19,11,3,60,52,44,36,
            63,55,47,39,31,23,15,7,62,54,46,38,30,22,
            14,6,61,53,45,37,29,21,13,5,28,20,12,4
        };

        int pc2[48] = {
            14,17,11,24,1,5,3,28,15,6,21,10,
            23,19,12,4,26,8,16,7,27,20,13,2,
            41,52,31,37,47,55,30,40,51,45,33,48,
            44,49,39,56,34,53,46,42,50,36,29,32
        };

        int shift[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

        string perm = "";
        for (int i = 0; i < 56; i++)
            perm += key[pc1[i] - 1];

        string left = perm.substr(0, 28);
        string right = perm.substr(28, 28);

        for (int i = 0; i < 16; i++) {
            rotate(left.begin(), left.begin() + shift[i], left.end());
            rotate(right.begin(), right.begin() + shift[i], right.end());

            string combined = left + right;
            string roundKey = "";

            for (int j = 0; j < 48; j++)
                roundKey += combined[pc2[j] - 1];

            roundKeys.push_back(roundKey);
        }

        return roundKeys;
    }
};

// DES
class DES {
private:
    vector<string> keys;

public:
    DES(vector<string> k) : keys(k) {}

string process(string input, bool decrypt = false) {
    vector<string> roundKeys = keys;

    if (decrypt) reverse(roundKeys.begin(), roundKeys.end());

    string perm = initial_permutation(input);

    string left = perm.substr(0, 32);
    string right = perm.substr(32, 32);

    int expansion_table[48] = {
        32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,16,17,18,19,
        20,21,20,21,22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    };

    int permutation_tab[32] = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

    for (int i = 0; i < 16; i++) {
        // Expansion 32 -> 48
        string right_expanded = "";
        for (int j = 0; j < 48; j++)
            right_expanded += right[expansion_table[j] - 1];

        // XOR với round key
        string xored = xor_str(right_expanded, roundKeys[i]);

        string sbox = xored.substr(0, 32);

        // Permutation
        string perm2 = "";
        for (int j = 0; j < 32; j++)
            perm2 += sbox[permutation_tab[j] - 1];

        string new_right = xor_str(left, perm2);

        left = right;
        right = new_right;
    }

    string combined = right + left;
    return inverse_initial_permutation(combined);
}
};

// MAIN 
int main() {
    int mode;
    string input, key;

    cin >> mode;
    cin >> input;
    cin >> key;

    KeyGenerator kg(key);
    vector<string> keys = kg.generate();

    string result = "";

    // MODE 1: ENCRYPT
    if (mode == 1) {
        DES des(keys);

        for (int i = 0; i < input.size(); i += 64) {
            string block = input.substr(i, 64);

            // 🔥 BỔ SUNG: ZERO PADDING
            if (block.size() < 64)
                block.append(64 - block.size(), '0');

            result += des.process(block, false);
        }
    }

    // MODE 2: DECRYPT
    else if (mode == 2) {
        DES des(keys);

        for (int i = 0; i < input.size(); i += 64) {
            string block = input.substr(i, 64);

            if (block.size() < 64)
                block.append(64 - block.size(), '0');

            result += des.process(block, true);
        }
    }

    cout << result << endl;

    return 0;
}
