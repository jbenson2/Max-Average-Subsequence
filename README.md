# Maximum Average Subsequence
## Compiling the Program
This program is designed to be compiled using g++. To do so, run:
```bash
g++ main.cpp -o <executable name>
```
## Running the Program
This program is designed to take arguments from the command line.
* <executable name> - The name assigned when compiling
* <input file name> - The name of the input file to be used. Several are included in this repo
* <k> - The length of the subsequence to be found
* <-b|-d> - Brute-force or Divide & Conquer
### For Brute-Force
To use the brute-force algorithm run:
```bash
./<executable name> <input file name> <k> -b
```
### For Divide & Conquer
To use the divide & conquer algorithm run:
```bash
./<executable name> <input file name> <k> -d
```