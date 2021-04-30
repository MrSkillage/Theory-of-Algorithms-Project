# Theory-of-Algorithms-Project
## Project Outine
This repository contains all work done for my 4th Year module Theory of Algorithms. The objective of the project is to create the SHA-512, *Standard-Hash Algorithm*. The program is written in the C programming language. The program will take the name or path of a file as a command line arguement and output the SHA-512 digest of it. This is to be coded from scratch using **ONLY** the standard C library.

## File Structure
- **.gitignore** : Standard gitignore file.
- **Makefile** : A standard c makefile that complies **cmdargs.c** into an executable called *main*. Has two addtional functions:
  - *make test* : Runs the shell script **test.sh** (see below).
  - *make clean* : Runs a command to remove all executables created by the **Makefile**.
- **README.md** : A standard README file written in Markdown, which informs and instructions the reader on the programs design and how to use it. You are reading this right now!
- **cmdargs.c** : A c file used to execute and run the SHA Algorithms. All command line arguments and help instructions are found here. Read the ***'How to Run'*** section for more details on this executable.
- **input.txt** : A simple text file used to run and test the SHA Algorithms.
- **sha256.c** : The Secure Hash Standard algorithm SHA 256, includes a SHA256 function that is used in the cmdargs.c file.
- **sha512.c** : The Secure Hash Standard algorithm SHA 512, includes a SHA512 function that is used in the cmdargs.c file.
- **test.sh** : A simple shell script that runs tests using bash commands. Checks the functionality of both sha256 & sha512 and prints out 4 tests (two Passes & two Fails) for each.

## How To Run
Before we begin the how to section you first need to git clone this repository and make sure the files have downloaded correctly and navigate inside the project folder. The images used in this section are taken from a Linux Debian command line, to find out more about debian [click here](https://www.debian.org/). You will also need to have installed the coreutils package, instructions can be found at [GNU](https://www.gnu.org/software/coreutils/). 
![image](https://user-images.githubusercontent.com/43910132/116561712-7a2d1f80-a8fa-11eb-8fc3-9ac7a1861c6c.png)

### Testing
Once you have cloned the git repository you need to make sure you have the coreutils package installed. You can check if you have the coreutils package installed by running the command *sudo dpkg -s coreutils*.
![image](https://user-images.githubusercontent.com/43910132/116562366-00e1fc80-a8fb-11eb-9152-381ba2cfd8e2.png)
If you don't have the package installed you can install it by running the command *sudo apt install coreutils*.
![image](https://user-images.githubusercontent.com/43910132/116562568-2c64e700-a8fb-11eb-9fd5-163037887e72.png)
Once you have coreutils installed you can begin the testing. To do this we simple use a [Makefile](https://makefiletutorial.com/) command found inside the project folder. Run the command *make test* to execute the test shell script. This will run 4 tests in total on the *input.txt* file. The first 2 tests are run using the *sha512* file I have created and the last 2 test are run using the *sha256* file I have created. Each pair of the SHA tests contain one PASS test and one FAIL test. Each PASS test compares the SHA files I created (*sha256 & sha512*) with the coreutils sha256sum and sha512sum, respectively. Each FAIL test compares the SHA (*sha256 & sha512*) files I created with the string 'FAILED-HASH-VALUE'. All tests print PASS if both the Expected and Output match and print FAIL if they don't match.
![image](https://user-images.githubusercontent.com/43910132/116565304-a4cca780-a8fd-11eb-95a6-5b8f5463b742.png)

### Running
After successfully testing we can move onto running the file ourselves, passing in our own files, and choosing the algorithm we wish to use. Run the command *make* to ensure we create a new executable called *main*.
![image](https://user-images.githubusercontent.com/43910132/116565871-28869400-a8fe-11eb-8108-309d7f73a014.png)
Note that when we run our tests the *main* executable is automatically created as our tests depend on it, the Makefile inherently knows this and creates the dependent files for us. Now that we have our executable ready run the command *./main -h*. The *-h* brings up the help options and instructions on how to use the executable *main*.
![image](https://user-images.githubusercontent.com/43910132/116566307-8e731b80-a8fe-11eb-823f-99bd03798c5e.png)
As you can see we can change the type of SHA algorithm we wish to use using the optional parameter *-a*. The default algorithm is always set to the sha512 algorithm. Lets run the sha512 algorithm on the input.txt file. Run the command *./main -f input.txt*, where *-f* is the optional parameter of the file we wish to pass.
![image](https://user-images.githubusercontent.com/43910132/116567013-2b35b900-a8ff-11eb-9161-6ee86b7e4146.png)
We can run the algorithm on any file we wish for instance run the command *./main -f README.md* to get get the sha512 hash value of the *README.md*.
![image](https://user-images.githubusercontent.com/43910132/116567281-62a46580-a8ff-11eb-9e32-2f15df151865.png)
Lets change the algorithm and get the sha256 hash value of the *README.md*. Run the command *./main -a 256 -f README.md*.
![image](https://user-images.githubusercontent.com/43910132/116567648-ba42d100-a8ff-11eb-9e3e-bf4d81c5fd19.png)
We can run more then one algorithm on more then one file at the same time. For instance we can calculate the sha256 hash value of *input.txt* and the sha512 hash value of *README.md*. Run the command *./main -a 256 -f input.txt -a 512 -f README.md*.
![image](https://user-images.githubusercontent.com/43910132/116568336-5076f700-a900-11eb-81af-dc17315ead41.png)
We can run the same algorithm on multiple files. For intance we can calculate the sha512 hash value of *sha256.c*, *sha512.c*, *cmdargs.c*, and *main*. Run the command *./main -f sha256.c -f sha512.c -f cmdargs.c -f main*. Note we don't have to set the SHA algorithm *-a* because the sha512 algorithm is set by default.
![image](https://user-images.githubusercontent.com/43910132/116568784-b1063400-a900-11eb-8b9e-be1e7b6b075f.png)

### Error Checking
The executable *main* requires being pass a file. A failure to do so will result in the program shutting down. Run the command *./main* and you will see the program execuates and exits. This is not a bug but a design decision.
![image](https://user-images.githubusercontent.com/43910132/116574442-9da99780-a905-11eb-9d5d-98096b50e019.png)
The user may use one of the options but not provide a value for that option such as *./main -f*. The user will be prompted with a message informing them they have selected an optional parameter but have give no value. They will then be given an example of how to use optional parameters. Run the command *./main -f*.
![image](https://user-images.githubusercontent.com/43910132/116575053-36401780-a906-11eb-9ff2-43c011a2faf7.png)x
If the user enters in a valid command but adds an additional parameter they will be prompt with a message at the end of the program showing them an 'Extra arguements:' they included. Run the command *./main -a 256 -f input.txt extrafile*.
![image](https://user-images.githubusercontent.com/43910132/116576299-57553800-a907-11eb-9222-3eca977660cd.png)
Lastly the user may enter in a invalid algorthim value and be prompted with a message informing them they have input an incorrect value for the optioanl parameter. Note if the user passes in a file as a parameter by default the executable will run the sha512 algorithm on the file if they specify an incorrect algorthim. Run the command *./main -a 117 -f input.txt*.
![image](https://user-images.githubusercontent.com/43910132/116575919-00e7f980-a907-11eb-8197-2a75631da870.png)






## What is the SHA-512 and why is it important?

## Module Questions
The module requires answering 3 questions. Each question is related to the topics covered in the module Theory of Algorithm. These topics include the Secure Hash Standard, Standard-Hash Algorithms (SHA) 256 and 512, Turing Machines, and more. The questions are labeled 1-3 and answer up to 500 words each below.
### 1). Why can't we reverse the SHA-512 algorithm to retrience the original message from a hash digest?
We can't reverse the SHA-512 algorithm for a number of design reasons. Firstly, the SHA-512 is a cryptographic hash function, which is a mathematical algorithm that maps data of abbitrary size, known as the *message*, to a bit array of a fixed size, the *message digest* [1]. The hash algorithm is designed to ensure that each bit of the output is dependent upon every bit in the input. This form of **bit dependency** prevents malicious attempts to split-up the algorithm and attempt to reverse calculate the input. Furthermore, being bit dependent any change in a *single bit* in our input will result in the **Avalanche Effect** [2,3]. Any input change of the slightest kind (from 0 to 1 or vice-versa) will change the output significantly, this could be upto half or more of the entire message changing. Hash functions that do not exhibit the avalanche effect to a high degree are said to have poor randomness and are open to cryptanalyst to make predictions about the input, when given the output. <br/>
The SHA-512 algorithm is known in computer science as **one-way function**. This is a function that is considered easy to compute on every input, but hard to invert given the image *(the set of all output values the function may produce)* of a random input. It is infeasible to reverse the process that generated the given hash value. The only way to find a message that prodces a given hash would be to attempt a brute-force search of possible inputs to see if they match. This is both a tedious and time-consuming method that may never yield any tangible results and could theoretically take years to complete. <br/>
The SHA-512 algorithm contains non-linear operations which prevents malicious users from using linear algebra techniques to solve the input of a given output. Non-linear operations make it much harder to calculate the inverse than it is to calculate the hash. During the hash computation each message block from, M^1, ..., M^N is processed and compressed using non-linear operations and has its internal state updated. The next message block comes in and has its internal state processed, compressed and updated. This continues until no more message blocks remain at which point the updated message blocks are concatenated together to create the final hash value [5]. <br/>

### 2). Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
First let me put into perspective the time complexity (length of time an algorithm takes to complete) of finding the input message of a given 512-bit string i.e. only finding one possible 512-bit string. There are a number of techniques we could use such as a brute-force attack, in which the user attempts to guess the correct answer, to find the the input message of a given 512-bit string. If we want to try and find a message that has a specific hash value we could use a *Preimage attack*. The most efficient way to compute a preimage is through the use of a brute-force attack. This has a time complexity of O(2^n), where n = is the output (hash value) length of the hash function in bits. However, if we only wanted to compute and find a specific hash value we look for collisions. We can find collisions using a technique known as a *Birthday attack* which has a time complexity of O(2^(n/2)), where n = is the output (hash value) length of the hash function in bits [6]. The SHA-512 has a hash value size of 512bits and when using a birthday attack the time complexity would equal O(2^(512/2)) = O(2^256). The number 2^256 translates to 1 in over 115 quattuorvigintillion (78 digit number) chances of finding a collsion [7]. To put into a bigger perspective the numebr 2^256 is exponentially bigger than the number of atoms in the perceivable universe.<br/>
Lets say for a moment we wanted to find the sha512 hash values of all the words in the dictionary. We could us another technique called *rainbow tables* [8] a precomputed table for caching the ouput of our hash function. This has a time complexity of O(1), the best time complexity we could achieve it is only as long as the length of our data. However, now that we solved our time complexity problem we run into another problem of storage space. Creating a table of every word in the dictionary and its sha512 has value would require an enormous amount of storage for our data. No such device exists to hold that amount of data. This trading off time and space is a commonly understood computer science dilemma known as time-memory trade-off [9]. <br/>
Now we go back to our original question of can we design an algorithm that, given enough time, will find the input messages that given each of the possible 512-bit strings?
The answer is yes and no. We can theoretically design such an algorithm, however we would never see **ALL** the results, and be lucky to see even a few. Furthermore, we would never be able to save and storage all the different 512-bit strings. Maybe one day when ManKind masters everlasting life and supercomputing power, possibly quantum computing, we would be able to calculate, store, and most importantly wait idly by why the algorithm does the heavy lifting.


### 3). How difficult is it to find a hash digest beginning with at least twelve zeroes?
The idea of finding specific hash digests beginning with at least tweleve zeroes stems mainly from the Bitcoin community. Bitcoin is a cryptocurrency that uses a peer-to-peer connection which eliminates the need for a central banking system. Bitcoins are created through mining and there transactions are recorded in publicly distributed ledgers called blockchain [11]. Miners group new transactions in *blocks* and broadcast across the network. Each block contains a SHA-256 digest of the previous block linking them together to created a blockchain. To mine a block currently the average time is 10mins per block [12]. The community of Bitcoin miners have found *low block hashes* with tweleve leading zeroes, you can look here for the 12 lowest block hashes in Bitcoin [here](https://bitcoin.stackexchange.com/questions/65478/which-is-the-smallest-hash-that-has-ever-been-hashed) which are dated Dec 2018.


## Conclusion

## References
[1] - Cryptographic Hash Function; Wikipedia.org; https://en.wikipedia.org/wiki/Cryptographic_hash_function#SHA-1 <br/>
[2] - Why can't we reverse hashes?; StackExchange.org; https://crypto.stackexchange.com/questions/45377/why-cant-we-reverse-hashes <br/>
[3] - Avalanche Effect; Wikipedia.org; https://en.wikipedia.org/wiki/Avalanche_effect <br/>
[4] - Stackoverflow.com; https://stackoverflow.com/questions/6603849/why-is-it-not-possible-to-reverse-a-cryptographic-hash <br/>
[5] - Does hashing require non-linearity?; StackExchange.org; https://crypto.stackexchange.com/questions/41448/does-hashing-require-non-linearity <br/>
[6] - How long to brute force a salted SHA-512 hash?; Stackoverflow.com; https://stackoverflow.com/questions/6776050/how-long-to-brute-force-a-salted-sha-512-hash-salt-provided <br/>
[7] - Why is 2^256 Secure?; Privacycanada.net; https://privacycanada.net/cryptanalysis/why-is-2-256-secure/ <br/>
[8] - Rainbow Tables; Wikipedia.org; https://en.wikipedia.org/wiki/Rainbow_table <br/>
[9] - Space-time Tradeoff; Wikipedia.org; https://en.wikipedia.org/wiki/Space%E2%80%93time_tradeoff <br/>
[10] - Which is the smallest hash that has ever been hashed?; StackExchange.org; https://bitcoin.stackexchange.com/questions/65478/which-is-the-smallest-hash-that-has-ever-been-hashed <br/>
[11] - Bitcoin; Wikipedia.org; https://en.wikipedia.org/wiki/Bitcoin <br/>
[12] - Bitcoin Miners; Coindesk.com; https://www.coindesk.com/bitcoin-miners-usually-create-6-blocks-per-hour-they-just-banged-out-16 <br/>
[13] - SHA-512; StackExchange.org; https://crypto.stackexchange.com/questions/89690/sha-512-how-difficult-is-it-to-find-a-hash-digest-beginning-with-at-least-twel <br/>


