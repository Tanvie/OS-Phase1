#include <bits/stdc++.h>
using namespace std;
ifstream fin;
ofstream fout;
void INIT(char M[100][4], char *IR, char *R, int *C, int *IC)
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
    //C[0] = 0;
}
void EXECUTEUSERPROGRAM(char M[100][4], char *IR, char *R, int *C, int IC)
{
    IC = 0;
    while(M[IC][0]!='H')
    {
        //strcpy(M[IC],IR);
        IR[0] = M[IC][0];
        IR[1] = M[IC][1];
        IR[2] = M[IC][2];
        IR[3] = M[IC][3];
        IC++;
        // cout<<__LINE__<<"\t";
        // cout<<IR[0]<<IR[1]<<IR[2]<<IR[3]<<endl;
        
        
    }
}
void STARTEXECUTION(char M[100][4], char *IR, char *R, int *C, int *IC)
{
    IC[0] = 0;
    EXECUTEUSERPROGRAM(M, IR, R, C, IC[0]);
}
void LOAD(char M[100][4], char *IR, char *R, int *C, int *IC)
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
            STARTEXECUTION(M, IR, R, C, IC);
        }
        else
            cout << "";
    }
    for (int i = 0; i < 5; i++)
    {
        cout << "FOR DEBUG IN LOAD" << endl;
        cout << endl
             << endl;
        cout << M[i][0] << M[i][1] << M[i][2] << M[i][3] << endl;
        
    }
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
    // while(1)
    {
        INIT(M, IR, R, C, IC);
        LOAD(M, IR, R, C, IC);
    }

    fin.close();
    fout.close();
    return 0;
}