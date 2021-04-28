#include <stdio.h>
#include <inttypes.h>
#include <byteswap.h>
#include <unistd.h>

// Chekcing for Little Endian
const int _i = 1;
#define _is_lilend() ((*(char *)&_i) != 0)

// Words and Bytes
#define _BYTE uint8_t
#define _WORD uint64_t
#define _PF PRIx64

// Page 5 of the secure hash standard
#define _ROTR(_x, _n) (((_x) >> (_n)) | ((_x) << ((sizeof(_x) * 8) - (_n))))
#define _SHR(_x, _n) ((_x) >> (_n))

// Page 10 of the secure hash standard
#define _CH(_x, _y, _z) (((_x) & (_y)) ^ (~(_x) & (_z)))
#define _MAJ(_x, _y, _z) (((_x) & (_y)) ^ ((_x) & (_z)) ^ ((_y) & (_z)))

#define _BIGSIG0(_x) (_ROTR(_x, 28) ^ _ROTR(_x, 34) ^ _ROTR(_x, 39))
#define _BIGSIG1(_x) (_ROTR(_x, 14) ^ _ROTR(_x, 18) ^ _ROTR(_x, 41))
#define _SMALLSIG0(_x) (_ROTR(_x, 1) ^ _ROTR(_x, 8) ^ _SHR(_x, 7))
#define _SMALLSIG1(_x) (_ROTR(_x, 19) ^ _ROTR(_x, 61) ^ _SHR(_x, 6))

// Union stores all variables in the same memory
union _Block
{
    //SHA512 works on block sizes of 1024 bits.
    _BYTE _bytes[128];   // 8x128 = 1024 - dealing with blocks as _bytes
    _WORD _words[16];    // 64x16 = 1024 - dealing with blocks as _words
    uint64_t _sixf[16]; // 64x16 = 1024 - dealing with the last 128 bits of last block
};

// Enumeration to keep track of current state
enum _Status
{
    _READ,
    _PAD,
    _END
};

// Section 4.2.3 page 12 of the secure hash standard
// SHA-512 Constants
const _WORD _K[] = {
    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
    0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
    0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
    0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
    0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
    0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
    0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
    0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
    0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
    0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
    0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

// Function used to get blocks of data
int _next_block(FILE *F, union _Block *M, enum _Status *S, uint64_t *nobits)
{
    // Number of _bytes read
    size_t nobytes;
    if (*S == _END)
    {
        return 0; // Exit and finish program
    }
    else if (*S == _READ)
    {
        // Try to read-in 128 _bytes from the input file
        nobytes = fread(M->_bytes, 1, 128, F);
        // Calculate the total bits read so far
        *nobits = *nobits + (8 * nobytes);
        if (nobytes == 128)
        {
            // Reads in 128 _bytes perfectly, Do nothing...
            return 1;
        }
        else if (nobytes < 112)
        {
            // This happens when we have enough room for all the padding
            // Append a 1 bit (and seven 0 bits to make a full byte)
            M->_bytes[nobytes] = 0x80; // 10000000 in bits

            // Append enough 0 bits, leaving 128 at the end

            //
            //  Something amiss here!!!
            //

            for (nobytes++; nobytes < 128; nobytes++)
            {
                M->_bytes[nobytes] = 0x00; // 00000000 in bits
            }

            // Append the length of the original input and check for Endianess
            M->_sixf[15] = (_is_lilend() ? bswap_64(*nobits) : *nobits);
            // Switch state to _END
            *S = _END;
        }
        else
        {
            // At the end of the input messsage with no room for all the padding
            // Append a 1 bit (and seven 0 bits to make a full byte and check for Endianess)
            M->_bytes[nobytes] = 0x80; // 10000000 in bits

            // Append 0 bits
            for (nobytes++; nobytes < 128; nobytes++)
            {
                M->_bytes[nobytes] = 0x00; // 00000000 in bits
            }

            // Switch state to _PAD
            *S = _PAD;
        }
    }
    else if (*S == _PAD)
    {
        // Apend 0 bits
        for (nobytes = 0; nobytes < 112; nobytes++)
        {
            M->_bytes[nobytes] = 0x00; // 00000000 in bits
        }

        // Append nobits as an integer and check for Endianess
        M->_sixf[15] = (_is_lilend() ? bswap_64(*nobits) : *nobits);
        // Set state to _END
        *S = _END;
    }

    if (_is_lilend())
    {
        for (int i = 0; i < 16; i++)
        {
            M->_words[i] = bswap_64(M->_words[i]);
        }
    }

    return 1;
}

// Hash computation process Section 6.4 page 24-26
int _next_hash(union _Block *M, _WORD H[])
{
    _WORD W[128];
    // Iterator
    int t;

    // All Temporary Variables & Message schedule, Section 6.4.2
    _WORD a, b, c, d, e, f, g, h, T1, T2;

    // Section 6.4.2 Part 1
    for (t = 0; t < 16; t++)
    {
        W[t] = M->_words[t];
    }
    for (t = 16; t < 80; t++)
    {
        W[t] = _SMALLSIG1(W[t - 2]) + W[t - 7] + _SMALLSIG0(W[t - 15]) + W[t - 16];
    }

    // Section 6.4.2, Part 2
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    // Section 6.4.2, Part 3
    for (t = 0; t < 80; t++)
    {
        T1 = h + _BIGSIG1(e) + _CH(e, f, g) + _K[t] + W[t];
        T2 = _BIGSIG0(a) + _MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    // Section 6.4.2, Part 4
    H[0] = a + H[0];
    H[1] = b + H[1];
    H[2] = c + H[2];
    H[3] = d + H[3];
    H[4] = e + H[4];
    H[5] = f + H[5];
    H[6] = g + H[6];
    H[7] = h + H[7];

    return 0;
}

int SHA512(FILE *f)
{
    // Section 5.3.5 page 15 & 16 from the secure hash standard
    // SHA-512 Const
    _WORD H[] = {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 
        0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 
        0x1f83d9abfb41bd6b, 0x5be0cd19137e2179};

    // The function that performs the SHA-512 algorithm on message f.
    union _Block M;
    // Total number of bits read
    uint64_t nobits = 0;
    // Current _Status
    enum _Status S = _READ;

    // Loop through the (preprocessed) blocks
    while (_next_block(f, &M, &S, &nobits))
    {
        _next_hash(&M, H);
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%016" _PF, H[i]);
    }
    printf("\n");

    return 0;
}

/*
int main(int argc, char *argv[])
{
    FILE *f;
    // Open file from command line for reading
    f = fopen(argv[1], "r");

    // Calculate the SHA512 of input file f
    SHA512(f);

    // Close the file
    fclose(f);

    return 0;
}
*/