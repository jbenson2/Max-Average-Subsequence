#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void bruteForce(vector<double> seq, int k, int left, int right, int &startIndex, int &endIndex, double &maxAvg)
{
    double sum = 0;
    double avg = 0;

    for (int i = left; i <= right - k; i++)
    {
        sum = 0;
        for (int j = i; j < i + k; j++)
        {
            sum += seq.at(j);
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

void divideAndConquer(vector<double> seq, int k, int left, int right, int &startIndex, int &endIndex, double &maxAvg)
{
    int mid;
    double leftSum;
    double rightSum;

    if (right - left < k)
    {
        return;
    }
    if (right - left == k)
    {
        bruteForce(seq, k, left, right, startIndex, endIndex, maxAvg);
        return;
    }

    mid = (left + right) / 2;
    divideAndConquer(seq, k, left, mid, startIndex, endIndex, maxAvg);
    divideAndConquer(seq, k, mid + 1, right, startIndex, endIndex, maxAvg);
}

/*void divideAndConquer(vector<double> &sequence, int k, int left, int right, int &start, int &end, double &maxAvg)
{
    if (right - left + 1 < k)
    {
        return;
    }

    if (right - left + 1 == k)
    {
        double sum = 0;
        for (int i = left; i <= right; i++)
        {
            sum += sequence.at(i);
        }
        double avg = sum / k;
        if (avg > maxAvg)
        {
            maxAvg = avg;
            start = left;
            end = right;
        }
        return;
    }
    int mid = (left + right) / 2;
    divideAndConquer(sequence, k, left, mid, start, end, maxAvg);
    divideAndConquer(sequence, k, mid + 1, right, start, end, maxAvg);

    double leftSum = 0;
    double leftMaxAvg = 0;
    for (int i = mid; i >= left; i--)
    {
        leftSum += sequence.at(i);
        double avg = leftSum / (mid - i + 1);
        if (avg > leftMaxAvg)
        {
            leftMaxAvg = avg;
            start = i;
        }
    }

    double rightSum = 0;
    double rightMaxAvg = 0;
    for (int i = mid + 1; i <= right; i++)
    {
        rightSum += sequence.at(i);
        double avg = rightSum / (i - mid);
        if (avg > rightMaxAvg)
        {
            rightMaxAvg = avg;
            end = i;
        }
    }

    if (leftMaxAvg + rightMaxAvg > maxAvg)
    {
        maxAvg = leftMaxAvg + rightMaxAvg;
    }
}*/

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
        bruteForce(sequence, k, 0, n, startIndex, endIndex, maxAvg);
        endTime = clock();
    }
    else
    {
        divideAndConquer(sequence, k, 0, n, startIndex, endIndex, maxAvg);
    }
    cout << "k = " << k << ", n = " << n << endl;
    cout << "Indices: [" << startIndex << ", " << endIndex << "]" << endl;
    cout << "Maximum average: " << maxAvg << endl;
    cout << "Elapsed time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
}