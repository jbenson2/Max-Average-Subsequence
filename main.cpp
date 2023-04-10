#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void bruteForce(const vector<double> &seq, int k, int left, int right, int &startIndex, int &endIndex, double &maxAvg)
{
    double sum = 0;
    double avg = 0;

    for (int i = left; i <= right - k + 1; i++)
    {
        sum = 0;
        for (int j = i; j < i + k; j++)
        {
            sum += seq[j];
        }
        avg = sum / k;
        if (avg > maxAvg)
        {
            maxAvg = avg;
            startIndex = i;
            endIndex = i + k - 1;
        }
    }
}

void divideAndConquer(vector<double> &seq, int k, int left, int right, int &startIndex, int &endIndex, double &maxAvg)
{
    int mid;
    int leftStartIndex = 0;
    int leftEndIndex = 0;
    int rightStartIndex = 0;
    int rightEndIndex = 0;
    int crossStartIndex = 0;
    int crossEndIndex = 0;
    double leftMaxAvg = 0;
    double rightMaxAvg = 0;
    double crossMaxAvg = 0;
    double sum = 0;
    double avg = 0;

    if ((right - left + 1) < k)
    {
        return;
    }

    mid = (right + left) / 2;

    divideAndConquer(seq, k, left, mid, leftStartIndex, leftEndIndex, leftMaxAvg);
    divideAndConquer(seq, k, mid + 1, right, rightStartIndex, rightEndIndex, rightMaxAvg);

    crossStartIndex = mid;
    crossEndIndex = mid + k - 1;

    bruteForce(seq,k,mid,mid+(k+k)-2,crossStartIndex,crossEndIndex,crossMaxAvg);

    maxAvg = max(max(leftMaxAvg,rightMaxAvg),crossMaxAvg);
    if (maxAvg == crossMaxAvg)
    {
        startIndex = crossStartIndex;
        endIndex = crossEndIndex;
    }
    else if (maxAvg == leftMaxAvg)
    {
        startIndex = leftStartIndex;
        endIndex = leftEndIndex;
    }
    else
    {
        startIndex = rightStartIndex;
        endIndex = rightEndIndex;
    }
}

int main(int argc, char *argv[])
{
    string inputFileName;
    int k;
    int n;
    int startIndex = 0;
    int endIndex = 0;
    double maxAvg = 0;
    bool isBruteForce = false;
    double num;
    vector<double> sequence;
    clock_t startTime;
    clock_t endTime;

    if (argc != 4)
    {
        cout << "Missing commands: " << argv[0] << " <inputFileName> <k> <-b|-d>" << endl;
        return 1;
    }

    inputFileName = argv[1];
    k = atoi(argv[2]);
    if (string(argv[3]) == "-b")
    {
        isBruteForce = true;
    }
    else if (string(argv[3]) != "-d")
    {
        cout << "Invalid algorithm flag: " << argv[3] << endl;
        return 1;
    }

    // open the input file
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        cout << "Cannot open file" << endl;
        return 1;
    }

    // read the input file
    inputFile >> n;
    sequence.reserve(n);
    for (int i = 0; i < n; i++)
    {
        inputFile >> num;
        sequence.push_back(num);
    }

    // call the appropriate algorithm
    if (isBruteForce)
    {
        startTime = clock();
        bruteForce(sequence, k, 0, n - 1, startIndex, endIndex, maxAvg);
        endTime = clock();
    }
    else
    {
        startTime = clock();
        divideAndConquer(sequence, k, 0, n - 1, startIndex, endIndex, maxAvg);
        endTime = clock();
    }
    cout << "k = " << k << ", n = " << n << endl;
    cout << "Indices: [" << startIndex << ", " << endIndex << "]" << endl;
    cout << "Maximum average: " << maxAvg << endl;
    cout << "Elapsed time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
}