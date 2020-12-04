#include <bits/stdc++.h>
using namespace std;
ifstream fin;
ofstream fout;
void INIT(char M[100][4], char *IR, char *R, int *C, int *IC,int *SI)
{
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    for (int i = 0; i < 4; i++)
    {
        IR[i] = '\0';
        R[i] = '\0';
    }
    IC[0] = 0;
    SI[0] =0;
    //C[0] = 0;
}
void getData(char M[100][4],char *IR)
{
    int a1 = IR[1] - '0';
    int a0 = IR[0] - '0';
    int mem = a1 * 10 + a0;
    

}
void putData(char M[100][4],char *IR)
{
}
void loadData(char M[100][4], char *IR, char *R)
{
    int a1 = IR[1] - '0';
    int a0 = IR[0] - '0';
    int mem = a1 * 10 + a0;
    R[0] = M[mem][0];
    R[1] = M[mem][1];
    R[2] = M[mem][2];
    R[3] = M[mem][3];
}
void storeData(char M[100][4], char *IR, char *R)
{
    int a1 = IR[1] - '0';
    int a0 = IR[0] - '0';
    int mem = a1 * 10 + a0;
    M[mem][0] = R[0];
    M[mem][1] = R[1];
    M[mem][2] = R[2];
    M[mem][3] = R[3];
}
void compare(char M[100][4], char *IR, char *R, int *C)
{
    int a1 = IR[1] - '0';
    int a0 = IR[0] - '0';
    int mem = a1 * 10 + a0;
    char *operand2;
    int result;
    operand2[0] = M[mem][0];
    operand2[1] = M[mem][1];
    operand2[2] = M[mem][2];
    operand2[3] = M[mem][3];

    result = (operand2[0] == R[0]);
    for (int i = 1; i < 4; i++)
    {
        result &= (operand2[i] == R[i]);
    }

    C[0] = result;
}

void EXECUTEUSERPROGRAM(char M[100][4], char *IR, char *R, int *C, int IC,int *SI)
{
    IC = 0;
    SI[0] = 0;
    while (M[IC][0] != 'H')
    {
        //strcpy(M[IC],IR);
        IR[0] = M[IC][0];
        IR[1] = M[IC][1];
        IR[2] = M[IC][2];
        IR[3] = M[IC][3];
        IC++;
        // cout<<__LINE__<<"\t";
        // cout<<IR[0]<<IR[1]<<IR[2]<<IR[3]<<endl;
        switch (IR[0])
        {
        case 'G':
            SI[0] = 1;
            break;
        case 'P':
            SI[0] = 2;
            break;
        case 'L':
            loadData(M, IR, R);
            break;
        case 'S':
            storeData(M, IR, R);
            break;
        case 'C':
            compare(M, IR, R, C);
            break;
        case 'B':
            //branch if true
            break;
        default:
            cout << "\nINVALID INSTRUCTION!!!";
            exit(1);
        }
    }
}
void STARTEXECUTION(char M[100][4], char *IR, char *R, int *C, int *IC,int *SI)
{
    IC[0] = 0;
    EXECUTEUSERPROGRAM(M, IR, R, C, IC[0],SI);
}
void LOAD(char M[100][4], char *IR, char *R, int *C, int *IC,int *SI)
{
    int instC, pcCount;
    int m = 0;
    string line;
    while (!fin.eof())
    {
        getline(fin, line);
        if (!(line.find("$AMJ") == string::npos))
        {
            instC = stoi(line.substr(8, 4));
            pcCount = (instC / 10) + 1;
            for (int i = 0; i < pcCount; i++)
            {
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
            STARTEXECUTION(M, IR, R, C, IC,SI);

        }
        else if (!(line.find("$END") == string::npos))
            cout << "";
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
    fin.open("input1.txt");
    fout.open("output1.txt");
    char M[100][4];
    char IR[4];
    char R[4];
    int *C;
    int *IC;
    int *SI;
    // while(1)
    {
        INIT(M, IR, R, C, IC,SI);
        LOAD(M, IR, R, C, IC,SI);
    }

    fin.close();
    fout.close();
    return 0;
}