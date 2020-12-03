#include <bits/stdc++.h>
using namespace std;
ifstream fin;
ofstream fout;
void INIT(char M[100][4], char *IR, char *R, int *C, int *IC)
{
    // cout<<__LINE__<<"\t";
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    // cout<<__LINE__<<"\t";
    for (int i = 0; i < 4; i++)
    {
        IR[i] = '\0';
        R[i] = '\0';
    }
    IC[0] = 0;
    cout<<__LINE__<<"\t";
    C[0] = 0;
    //cout<<__LINE__<<"\t";
}
void LOAD(char M[100][4], char *IR, char *R, int *C, int *IC)
{
    // cout<<__LINE__<<"\t";
    int instC, pcCount;
    int m = 0;
    string line;
    while (!fin.eof())
    {
        // cout<<__LINE__<<"\t";
        getline(fin, line);
        if (!(line.find("$AMJ") == string::npos))
        {
            //cout<<__LINE__<<"\t";
            instC = stoi(line.substr(8, 4));
            //cout<<"STOI"<<instC;
            pcCount = (instC / 10) + 1;
            cout << "PCCOUNT " << pcCount;
            for (int i = 0; i < pcCount; i++)
            {
                //cout<<__LINE__<<"\t";
                getline(fin, line);
                for (int j = 0; j < line.length(); j += 4)
                {
                    //cout<<__LINE__<<"\t";
                    M[m][0] = line[j + 0];
                    M[m][1] = line[j + 1];
                    M[m][2] = line[j + 2];
                    M[m][3] = line[j + 3];
                    m++;
                }
            }
        }

        // else if ("$DTA")
        //     //startexecution
        else            //$END
            cout << ""; //reading
    }
    for (int i = 0; i < 5; i++)
    {
        cout << __LINE__ << "\t";
        cout << M[i][0] << M[i][1] << M[i][2] << M[i][3] << endl;
    }
}
int main()
{
    fin.open("input1.txt");
    fout.open("output1.txt");
    cout << __LINE__ << "\t";
    char M[100][4];
    char IR[4];
    char R[4];
    int *C;
    int *IC;
    //cout<<__LINE__<<"\t";
    // while(1)
    {
        cout << __LINE__ << "\t";
        INIT(M, IR, R, C, IC);
        cout << __LINE__ << "\t";
        LOAD(M, IR, R, C, IC);
    }

    fin.close();
    fout.close();
    return 0;
}