# Theory-of-Algorithms-Project
## Project Outine
This repository contains all work done for my 4th Year module Theory of Algorithms. The objective of the project is to create the SHA-512, *Standard-Hash Algorithm*. The program is written in the C programming language. The program will take the name or path of a file as a command line arguement and output the SHA-512 digest of it. This is to be coded from scratch using **ONLY** the standard C library.

## File Structure
- **Extras** : This folder contains all working extra text and c files. All rough work leading up to the sha512.c can be found here.
- **Makefile** : A standard c makefile that complies the sha512 program.
- **README.md** : A standard README file written in Markdown, which informs and instructions the reader on the programs design and how to use it. You are reading this right now!
- **sha512** : The Secure Hash Standard algorithm SHA 512. This program when run will take in a an additional file which will have the SHA 512 hashing function preformed on it.

## How to Run

## What is the SHA-512 and why is it important?

## Module Questions
The module requires answering 3 questions. Each question is related to the topics covered in the module Theory of Algorithm. These topics include the Secure Hash Standard, Standard-Hash Algorithms (SHA) 256 and 512, Turing Machines, and more. The questions are labeled 1-3 and answer up to 500 words each below.
### 1). Why can't we reverse the SHA-512 algorithm to retrience the original message from a hash digest?
We can't reverse the SHA-512 algorithm for a number of design reasons. Firstly, the SHA-512 is a cryptographic hash function, which is a mathematical algorithm that maps data of abbitrary size, known as the *message*, to a bit array of a fixed size, the *message digest* [1]. The hash algorithm is designed to ensure that each bit of the output is dependent upon every bit in the input. This form of **bit dependency** prevents malicious attempts to split-up the algorithm and attempt to reverse calculate the input. Furthermore, being bit dependent any change in a *single bit* in our input will result in the **Avalanche Effect** [2,3]. Any input change of the slightest kind (from 0 to 1 or vice-versa) will change the output significantly, this could be upto half or more of the entire message changing. Hash functions that do not exhibit the avalanche effect to a high degree are said to have poor randomness and are open to cryptanalyst to make predictions about the input, when given the output. <br/>
The SHA-512 algorithm is known in computer science as **one-way function**. This is a function that is considered easy to compute on every input, but hard to invert given the image *(the set of all output values the function may produce)* of a random input. It is infeasible to reverse the process that generated the given hash value. The only way to find a message that prodces a given hash would be to attempt a brute-force search of possible inputs to see if they match. This is both a tedious and time-consuming method that may never yield any tangible results and could theoretically take years to complete. <br/>
The SHA-512 algorithm contains non-linear operations which prevents malicious users from using linear algebra techniques to solve the input of a given output. Non-linear operations make it much harder to calculate the inverse than it is to calculate the hash. During the hash computation each message block from, M^1, ..., M^N is processed and compressed using non-linear operations and has its internal state updated. The next message block comes in and has its internal state processed, compressed and updated. This continues until no more message blocks remain at which point the updated message blocks are concatenated together to create the final hash value [5]. <br/>

### 2). Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
If we want to try and find a message that has a specific hash value we would used a *Preimage attack*. The most efficient way to compute a preimage is through the use of a brute-force attack, in which the user attempts to guess the correct answer. This has a time complexity of O(2^n), where n = 128bits, **2^128 = 2,480,000,000**, which is consider too high for the output size. However, if we only wanted to compute and find a specific hash value we look for collisions. We can find collisions using a *Birthday attack* which has a time complexity of O(2^(n/2)), where n = is the output (hash value) length of the hash function in bits [6]. The SHA-512 has a hash value size of 512bits and when using a birthday attack the time complexity would equal O(2^(512/2)) = O(2^256). The number 2^256 translates to 1 in over 115 quattuorvigintillion (78 digit number) chances of finding a collsion [7]. To put into a bigger perspective the numebr 2^256 is exponentially bigger than the number of atoms in the perceivable universe. 


### 3). How difficult is it to find a hash digest beginning with at least twelve zeroes?

## References
[1] - Cryptographic Hash Function; Wikipedia.org; https://en.wikipedia.org/wiki/Cryptographic_hash_function#SHA-1 <br/>
[2] - Why can't we reverse hashes?; StackExchange.org; https://crypto.stackexchange.com/questions/45377/why-cant-we-reverse-hashes <br/>
[3] - Avalanche Effect; Wikipedia.org; https://en.wikipedia.org/wiki/Avalanche_effect <br/>
[4] - Stackoverflow.com; https://stackoverflow.com/questions/6603849/why-is-it-not-possible-to-reverse-a-cryptographic-hash <br/>
[5] - Does hashing require non-linearity?; StackExchange.org; https://crypto.stackexchange.com/questions/41448/does-hashing-require-non-linearity <br/>
[6] - How long to brute force a salted SHA-512 hash?; Stackoverflow.com; https://stackoverflow.com/questions/6776050/how-long-to-brute-force-a-salted-sha-512-hash-salt-provided <br/>
[7] - Why is 2^256 Secure?; Privacycanada.net; https://privacycanada.net/cryptanalysis/why-is-2-256-secure/ <br/>

