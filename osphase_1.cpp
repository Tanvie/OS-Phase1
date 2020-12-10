#include <bits/stdc++.h>
using namespace std;
ifstream fin;
ofstream fout;
//int toggle = 0;
void INIT(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{
    cout << __LINE__ << "\t";
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    }
    for (int i = 0; i < 4; i++)
    {
        IR[i] = '\0';
        R[i] = '\0';
    }
    IC = 0;
    SI = 0;
    C = 0;
    // toggle = 0;
    cout << __LINE__ << "\t";
}

void getData(char M[100][4], char *IR)
{
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;
    //string line;
    char line[40];
    string line2;
    // memset(line, '\0', sizeof(line));
    getline(fin, line2);
    strcpy(line, line2.c_str());
    //fin >> line;
    char c = line[0];
    int index = 0;
    //line = "M A N A L I _ T A N V  I "
    //index = 0 1 2 3 4 5 6 7 8 9 10 11\
    //GD 10
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
void putData(char M[100][4], char *IR)
{
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;

    char ch, *buffer;
    buffer = (char *)malloc(sizeof(char) * 4);
    int index = 0, flag = 0;

    for (int i = 0; i < 10; i++)
    {
        buffer[0] = M[mem][0];
        buffer[1] = M[mem][1];
        buffer[2] = M[mem][2];
        buffer[3] = M[mem][3];

        for (int j = 0; j < 4; j++)
        {
            if (buffer[j] == '\0')
            {
                flag = 1;
                break;
            }
            else
            {
                ch = buffer[j];
                fout.put(ch);
                cout << ch;
            }
        }
        if (flag)
        {

            break;
        }
        mem += 1;
    }
    fout.put('\n');
}

void Halt(int &terminate)
{
    fout.put('\n');
    fout.put('\n');
    terminate = 1;
}
void loadData(char M[100][4], char *IR, char *R)
{
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;
    R[0] = M[mem][0];
    R[1] = M[mem][1];
    R[2] = M[mem][2];
    R[3] = M[mem][3];
}
void storeData(char M[100][4], char *IR, char *R)
{
    //IR = SR10
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;
    M[mem][0] = R[0];
    M[mem][1] = R[1];
    M[mem][2] = R[2];
    M[mem][3] = R[3];
}
void compare(char M[100][4], char *IR, char *R, int &C)
{
    cout << __LINE__ << "\t";
    int a1 = IR[2] - '0';
    int a0 = IR[3] - '0';
    int mem = a1 * 10 + a0;
    char operand2[4];
    int result;
    operand2[0] = M[mem][0];
    operand2[1] = M[mem][1];
    operand2[2] = M[mem][2];
    operand2[3] = M[mem][3];

    cout << __LINE__ << "\t";
    result = (operand2[0] == R[0]);
    cout << "\nIN COMPARE FOR DEBUG " << result << endl;
    for (int i = 1; i < 4; i++)
    {
        cout << "\nIN COMPARE FOR DEBUG " << result << endl;
        result &= (operand2[i] == R[i]);
    }

    // C = result;
    cout << "\nIN C VAL COMPARE FOR DEBUG " << result << endl;
    cout << __LINE__ << "\t";
    C = result;
    //toggle = result;
}

void branch(char *IR, int &IC, int &C)
{
    if (C)
    {
        //C is true then branch  the prog flow
        int a1 = IR[2] - '0';
        int a0 = IR[3] - '0';
        int mem = a1 * 10 + a0;

        IC = mem;
        C = 0;
    }
}
void MOS(char M[100][4], char *IR, int &SI, int &terminate)
{
    cout << __LINE__ << "\t";
    switch (SI)
    {
    case 1:
        cout << __LINE__ << "\t";
        getData(M, IR);
        break;
    case 2:
        cout << __LINE__ << "\t";
        putData(M, IR);
        break;
    case 3:
        cout << __LINE__ << "\t";
        Halt(terminate);
        break;

    default:
        cout << "ERROR IN MOS SI CODE!!" << endl;
        break;
    }

    SI = 0;
}

void EXECUTEUSERPROGRAM(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{
    cout << __LINE__ << "\t";
    IC = 0;
    C = 0;
    // *(SI) = 0;
    SI = 0;
    int terminate = 0;
    cout << __LINE__ << "\t";
    while (!terminate)
    {
        cout << __LINE__ << "\t";
        //strcpy(M[IC],IR);
        IR[0] = M[IC][0];
        IR[1] = M[IC][1];
        IR[2] = M[IC][2];
        IR[3] = M[IC][3];
        IC++;
        cout << __LINE__ << "\t";
        cout << IR[0] << IR[1] << IR[2] << IR[3] << endl;
        cout << __LINE__ << "\t";
        //for load store debug
        int a1 = IR[2] - '0';
        int a0 = IR[3] - '0';
        int mem = a1 * 10 + a0;
        if (IR[0] == 'G')
        {
            cout << __LINE__ << "\t";
            SI = 1;
            MOS(M, IR, SI, terminate);
        }
        else if (IR[0] == 'P')
        {
            cout << __LINE__ << "\t";
            SI = 2;
            MOS(M, IR, SI, terminate);
        }
        else if (IR[0] == 'H')
        {
            cout << __LINE__ << "\t";
            SI = 3;
            MOS(M, IR, SI, terminate);
        }
        else if (IR[0] == 'L')
        {
            cout << __LINE__ << "\t";
            loadData(M, IR, R);
            cout << "\n\nIN LOAD FOR DEBUG\n";
            cout << R[0] << R[1] << R[2] << R[3] << "-----" << endl;
        }
        else if (IR[0] == 'S')
        {
            cout << __LINE__ << "\t";
            storeData(M, IR, R);
            cout << "\n\nIN STORE FOR DEBUG\n";
            cout << M[31][0] << M[31][1] << M[31][2] << M[31][3] << "-----" << endl;
        }
        else if (IR[0] == 'C')
        {
            cout << __LINE__ << "\t";
            compare(M, IR, R, C);
            // cout << __LINE__ << "\t";
            // cout << "\n238 IN COMPARE FOR DEBUG " << toggle << endl;
            // cout << __LINE__ << "\t";
        }
        else if (IR[0] == 'B')
        {
            cout << __LINE__ << "\t";
            //branch if true
            branch(IR, IC, C);
        }
        cout << __LINE__ << "\t";
    }
}
void STARTEXECUTION(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{
    cout << __LINE__ << "\t";
    IC = 0;
    EXECUTEUSERPROGRAM(M, IR, R, IC, SI, C);
    cout << __LINE__ << "\t";
}
void LOAD(char M[100][4], char *IR, char *R, int &IC, int &SI, int &C)
{
    int instC, pcCount;
    int m;
    string line;
    cout << __LINE__ << "\t";
    while (!fin.eof())
    {
        cout << __LINE__ << "\t";
        getline(fin, line);
        if (!(line.find("$AMJ") == string::npos))
        {
            m = 0;
            cout << __LINE__ << "\t";
            instC = stoi(line.substr(8, 4));
            if (instC % 10 == 0)
                pcCount = instC / 10;
            else
                pcCount = (instC / 10) + 1;
            for (int i = 0; i < pcCount; i++)
            {
                cout << __LINE__ << "\t";
                getline(fin, line);
                for (int j = 0; j < line.length(); j += 4)
                {
                    M[m][0] = line[j + 0];
                    M[m][1] = line[j + 1];
                    M[m][2] = line[j + 2];
                    M[m][3] = line[j + 3];
                    m++;
                }
            }
        }

        else if (!(line.find("$DTA") == string::npos))
        {
            cout << __LINE__ << "\t";
            STARTEXECUTION(M, IR, R, IC, SI, C);
        }
        else if (!(line.find("$END") == string::npos))
        {
            cout << __LINE__ << endl;
            cout << "END DETECTED" << endl;
            INIT(M, IR, R, IC, SI, C);
        }
        cout << __LINE__ << "\t";
        //mem exceed condition
    }
    // for (int i = 0; i < 5; i++)
    // {
    //     cout << "FOR DEBUG IN LOAD" << endl;
    //     cout << endl
    //          << endl;
    //     cout << M[i][0] << M[i][1] << M[i][2] << M[i][3] << endl;
    // }
}
int main()
{
    fin.open("given_input.txt");
    fout.open("test_output.txt");
    char M[100][4];
    char IR[4];
    char R[4];
    cout << __LINE__ << "\t";
    int C = 0;
    int IC = 0;
    int SI = 0;
    cout << __LINE__ << "\t";
    INIT(M, IR, R, IC, SI, C);
    cout << __LINE__ << "\t";
    LOAD(M, IR, R, IC, SI, C);
    cout << __LINE__ << "\t";

    fin.close();
    fout.close();
    return 0;
}

// 1
// 2
// 3
// 4
// 5  BR 8
// 6
// 7
// 8
// 9