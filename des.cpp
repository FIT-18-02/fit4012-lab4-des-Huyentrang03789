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

    // Expansion
    int expansion_table[48] = {
        32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,16,17,18,19,
        20,21,20,21,22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    };

    // Permutation P
    int permutation_tab[32] = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

    int sbox[8][4][16] = {
        {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
         {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
         {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
         {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

        {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
         {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
         {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
         {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},

        {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
         {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
         {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
         {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

        {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
         {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
         {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
         {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

        {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
         {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
         {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
         {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

        {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
         {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
         {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
         {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

        {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
         {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
         {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
         {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

        {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
         {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
         {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
         {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
    };

    for (int i = 0; i < 16; i++) {
        string right_expanded = "";
        for (int j = 0; j < 48; j++)
            right_expanded += right[expansion_table[j] - 1];

        string xored = xor_str(right_expanded, roundKeys[i]);

        string sbox_out = "";
        for (int j = 0; j < 8; j++) {
            string block = xored.substr(j * 6, 6);

            int row = (block[0] - '0') * 2 + (block[5] - '0');
            int col = stoi(block.substr(1, 4), nullptr, 2);

            int val = sbox[j][row][col];
            sbox_out += bitset<4>(val).to_string();
        }

        string perm2 = "";
        for (int j = 0; j < 32; j++)
            perm2 += sbox_out[permutation_tab[j] - 1];

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
