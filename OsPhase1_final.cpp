// A.Y.2020-2021 CAOS course project
// OS-Phase-1 Implementation
// SY-CS-D Group-17

#include <bits/stdc++.h>
using namespace std;

ifstream fin;
ofstream fout;

// Function to initialise all the register variables and memory
void INIT(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{

    // Initialising memory to null
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    }

    // Initialising Instruction register and general purpose reg "R" to null
    for (int i = 0; i < 4; i++)
    {
        IR[i] = '\0';
        R[i] = '\0';
    }

    // Initialising Instruction counter, toggle reg "C" and Interrupt to zero
    IC = 0;
    SI = 0;
    C = 0;
}

// Getting the data from the data card and storing it to memory block
// GD [mem] Instruction
void getData(char M[100][4], char *IR)
{
    // To get memory operand
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;

    // Reading the line from data card
    char line[40];
    string line2;
    getline(fin, line2);
    strcpy(line, line2.c_str());

    // Storing the input characters to the memory loc specified
    char c = line[0];
    int index = 0;
    int memIndex = 0;

    while (c != '\0')
    {

        M[mem][memIndex] = c;
        index++;
        c = line[index];

        if (memIndex == 3)
            mem += 1;
        memIndex = index % 4;
    }
}

// Reading the data from the memory and writing it to output file
// PD [mem] Instruction
void putData(char M[100][4], char *IR)
{
    // To get memory operand
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;

    // To read data at memory
    char ch, *buffer;
    buffer = (char *)malloc(sizeof(char) * 4);
    int index = 0, flag = 0;

    for (int i = 0; i < 10; i++)
    {
        // Getting characters from memory into buffer
        for (int k = 0; k < 4; k++)
        {
            buffer[k] = M[mem][k];
        }

        for (int j = 0; j < 4; j++)
        {
            // Writing characters to the output file
            ch = buffer[j];
            fout.put(ch);
            //cout << ch;
        }
        mem += 1;
    }
    fout.put('\n');
}

// Ends the job
// H Instruction
void Halt(int &terminate)
{
    // Inserting two '\n' charcters to indicate end of Job
    fout.put('\n');
    fout.put('\n');

    // Varible used for Terminating the Job
    terminate = 1;
}

// Load the contents at specified memory location to general purpose reg 'R'
// LR [mem] Instruction
void loadData(char M[100][4], char *IR, char *R)
{
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;

    for (int k = 0; k < 4; k++)
    {
        R[k] = M[mem][k];
    }
}

// Store the contents of general purpose reg 'R' to specified memory location
// SR [mem] Instruction
void storeData(char M[100][4], char *IR, char *R)
{
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;

    for (int k = 0; k < 4; k++)
    {
        M[mem][k] = R[k];
    }
}

// Comapre the contents at specified memory location and contents of general purpose register 'R'
// CR [mem] Instruction
void compare(char M[100][4], char *IR, char *R, int &C)
{

    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;
    char operand2[4];
    int result;

    for (int k = 0; k < 4; k++)
    {
        operand2[k] = M[mem][k];
    }

    result = (operand2[0] == R[0]);
    for (int i = 1; i < 4; i++)
    {
        result &= (operand2[i] == R[i]);
    }

    C = result;
}

// Transfers the program flow to specified memory location in program card
// BR [mem] Instruction
void branch(char *IR, int &IC, int &C)
{
    if (C)
    {
        int a1 = IR[2] - '0';
        int a0 = IR[3] - '0';
        int mem = a1 * 10 + a0;

        IC = mem;
        C = 0;
    }
}

// Master mode
void MOS(char M[100][4], char *IR, int &SI, int &terminate)
{

    switch (SI)
    {
    case 1:

        getData(M, IR);
        break;
    case 2:

        putData(M, IR);
        break;
    case 3:

        Halt(terminate);
        break;

    default:
        cout << "ERROR IN MOS SI CODE!!" << endl;
        break;
    }

    SI = 0;
}

// Slave mode
void EXECUTEUSERPROGRAM(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{

    IC = 0;
    C = 0;
    SI = 0;
    int terminate = 0;

    while (!terminate)
    {
        for (int k = 0; k < 4; k++)
        {
            IR[k] = M[IC][k];
        }
        IC++;

        //cout << IR[0] << IR[1] << IR[2] << IR[3] << endl;
        if (IR[0] == 'G')
        {
            // Set Interrupt to 1 for reading data from data card (INPUT)
            SI = 1;
            MOS(M, IR, SI, terminate);
        }
        else if (IR[0] == 'P')
        {
            // Set Interrupt to 2 for writing data to outpt file (OUTPUT)
            SI = 2;
            MOS(M, IR, SI, terminate);
        }
        else if (IR[0] == 'H')
        {
            // Set interrupt to 3 for Halt
            SI = 3;
            MOS(M, IR, SI, terminate);
        }
        else if (IR[0] == 'L')
        {

            loadData(M, IR, R);
            //cout << R[0] << R[1] << R[2] << R[3] << "-----" << endl;
        }
        else if (IR[0] == 'S')
        {

            storeData(M, IR, R);
        }
        else if (IR[0] == 'C')
        {

            compare(M, IR, R, C);
        }
        else if (IR[0] == 'B')
        {
            branch(IR, IC, C);
        }
    }
}

// Starts the execution of program
void STARTEXECUTION(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{

    IC = 0;
    EXECUTEUSERPROGRAM(M, IR, R, IC, SI, C);
}

// Job execution
void LOAD(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{
    // instC - total number of instructions in a job
    int instC;
    // pcCount - total number of program card
    int pcCount;

    int m;
    string line;

    while (!fin.eof())
    {

        getline(fin, line);
        if (!(line.find("$AMJ") == string::npos))
        {
            m = 0;

            instC = stoi(line.substr(8, 4));
            if (instC % 10 == 0)
                pcCount = instC / 10;
            else
                pcCount = (instC / 10) + 1;
            // Reading program card and storing instructions in the memory
            for (int i = 0; i < pcCount; i++)
            {

                getline(fin, line);
                for (int j = 0; j < line.length(); j += 4)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        M[m][k] = line[j + k];
                    }
                    m++;
                }
            }
        }

        else if (!(line.find("$DTA") == string::npos))
        {

            STARTEXECUTION(M, IR, R, IC, SI, C);
        }
        else if (!(line.find("$END") == string::npos))
        {
            // cout << "END DETECTED" << endl;
            INIT(M, IR, R, IC, SI, C);
        }
    }
}
int main()
{
    // Reading the input file
    fin.open("input_phase1.txt");
    // For writing in output file
    fout.open("output.txt");

    // 2D array for memory
    char M[100][4];
    // Instruction register
    char IR[4];
    // General Purpose Register
    char R[4];

    // Toggle
    int C = 0;
    // Instruction counter
    int IC = 0;
    // Interuppt
    int SI = 0;

    INIT(M, IR, R, IC, SI, C);
    LOAD(M, IR, R, IC, SI, C);

    fin.close();
    fout.close();
    return 0;
}
