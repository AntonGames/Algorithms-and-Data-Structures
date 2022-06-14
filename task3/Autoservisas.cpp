//Anton Zagzin, 4 grupe, 2 pogrupis, 3 uzdavinis, 13 variantas

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <queue>
#include "BigInt.h"
using namespace std;

const unsigned int constMax = 1000; // kintamuju (BigInt) A, A1, B ir U zenklu limitas 
//const unsigned int T = 500; // dienu skaicius
//const unsigned int dailyHourLimit = 8; // darbo valandos per diena

void readFromFile(string filename, ofstream& out, 
    BigInt& A, BigInt& A1, BigInt& B, BigInt& U, 
    int& K, int& T1, int& T2, int& T, int& dailyHourLimit)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Failo " << filename << " neimanoma atidaryti" << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1. Programa sekmingai nebaige darbo" << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }


    string tmp;
    file >> A;
    cout << "VIP francize: " << A << " Lt" << endl;
    out << "  4. VIP francize: " << A << " Lt" << endl;
    getline(file, tmp);

    file >> A1;
    cout << "VIP priedas: " << A1 << " Lt" << endl;
    out << "  5. VIP priedas: " << A1 << " Lt" << endl;
    getline(file, tmp);

    file >> B;
    cout << "Francize: " << B << " Lt" << endl;
    out << "  6. Francize: " << B << " Lt" << endl;
    getline(file, tmp);

    file >> U;
    cout << "Darbuotojo valandine alga: " << U << " Lt" << endl;
    out << "  7. Darbuotojo valandine alga: " << U << " Lt" << endl;
    getline(file, tmp);

    file >> K;
    cout << "Darbuotoju skaicius: " << K << endl;
    out << "  8. Darbuotoju skaicius: " << K << endl;
    getline(file, tmp);

    file >> T1;
    cout << "Tikimybe, kad masina pristatys VIP klientas: " << T1 << "%" << endl;
    out << "  9. Tikimybe, kad masina pristatys VIP klientas: " << T1 << "%" << endl;
    getline(file, tmp);

    file >> T2;
    cout << "Tikimybe, kad masina pristatys paprastas klientas: " << T2 << "%" << endl;
    out << "  10. Tikimybe, kad masina pristatys paprastas klientas: " << T2 << "%" << endl;
    getline(file, tmp);

    file >> T;
    cout << "Dienu skaicius: " << T << endl;
    out << "  11. Dienu skaicius: " << T << endl;
    getline(file, tmp);

    file >> dailyHourLimit;
    cout << "Darbo valandu per diena: " << dailyHourLimit << endl;
    out << "  12. Darbo valandu per diena: " << dailyHourLimit << endl;
    getline(file, tmp);

    file.close();
}

int randomGen(int min, int max)
{
    int range;
    range = max - min + 1;
    return rand() % range + min;
}

void showQueue(priority_queue<int, vector<int> > gq)
{
    priority_queue<int, vector<int> > g = gq;
    while (!g.empty()) {
        cout << '\t' << g.top();
        g.pop();
    }
    cout << '\n';
}

void clearQueue(priority_queue<int, vector<int> > gq)
{
    priority_queue<int, vector<int> > g = gq;
    while (!g.empty()) {
        g.pop();
    }
}
void clearArray(int Array[], int& pointer)
{
    for (int i = 0; i < pointer; ++i)
    {
        Array[i] = 0;
    }
    pointer = 0;
}

void showTheClients(ofstream& out, priority_queue< int, vector<int> > &dailyClients, 
    int timeCommon[], int timeVIP[], int dailyTime, int& pointerVIP)
{
    int clientNuber = 1;
    int pointerVIPTemp = 0;
    int pointerCommonTemp = 0;
    while (!dailyClients.empty())
    {
        if (dailyClients.top())
        {
            out << "      " << clientNuber << " VIP klientas uztruko " << timeVIP[pointerVIPTemp] << " val." ;
            dailyClients.pop();
            ++clientNuber;
            ++pointerVIPTemp;
            if (pointerVIPTemp == pointerVIP && dailyTime < 0)
            {
                out << " is kuriu virsvalandziu " << -1 * dailyTime << " val.";
            }
            out << endl;
        }
        else
        {
            out << "      " << clientNuber << " klientas uztruko " << timeCommon[pointerCommonTemp] << " val." << endl;
            dailyClients.pop();
            ++clientNuber;
            ++pointerCommonTemp;
        }
    }
}

void fillTheClients(ofstream& out, int T1, priority_queue< int, vector<int> > dailyClients,
    int timeCommon[], int timeVIP[], int timeAll[], int& pointerVIP,
    int& pointerCommon, int& pointerAll, int K, BigInt A, BigInt B, 
    BigInt U, BigInt& profitVIP, BigInt& profitCommon, 
    BigInt& dailyProfitVIP, BigInt& dailyProfitCommon, int &dayTime)
{
    int TR;
    while (dayTime > 0)
    {
        
        if ((rand() % 100) < T1)
        {
            dailyClients.push(1);
            TR = randomGen(1, 5 * K);
            timeVIP[pointerVIP] = TR;
            ++pointerVIP;
            for (int i = 0; i < TR; ++i)
            {
                --dayTime;
                dailyProfitVIP += A;
                if (dayTime < 0)
                {
                    dailyProfitVIP -= U;
                    dailyProfitVIP -= U;
                }
                else
                {
                    dailyProfitVIP -= U;
                }

            }
            if (dayTime < 0)
            {
                profitCommon += dailyProfitCommon;
                profitVIP += dailyProfitVIP;
                showTheClients(out, dailyClients, timeCommon, timeVIP, dayTime, pointerVIP);
                clearArray(timeVIP, pointerVIP);
                clearArray(timeCommon, pointerCommon);
                clearArray(timeAll, pointerAll);
                return;
            }
            timeAll[pointerAll] = TR;
            ++pointerAll;
            for (int i = 0; i < TR; ++i)
            {
                dailyProfitCommon -= U;
                dailyProfitCommon += B;
            }
        }
        else
        {
            TR = randomGen(1, 5 * K);
            if (dayTime - TR < 0)
            {
                profitCommon += dailyProfitCommon;
                profitVIP += dailyProfitVIP;
                showTheClients(out, dailyClients, timeCommon, timeVIP, dayTime, pointerVIP);
                clearArray(timeVIP, pointerVIP);
                clearArray(timeCommon, pointerCommon);
                clearArray(timeAll, pointerAll);
                return;
            }
            dailyClients.push(0);
            dayTime -= TR;
            timeCommon[pointerCommon] = TR;
            timeAll[pointerAll] = TR;
            ++pointerAll;
            ++pointerCommon;
            for (int i = 0; i < TR; ++i)
            {
                dailyProfitCommon -= U;
                dailyProfitCommon += B;
                dailyProfitVIP += A;
                dailyProfitVIP -= U;
            }
        }
    }
    profitCommon += dailyProfitCommon;
    profitVIP += dailyProfitVIP;
    showTheClients(out, dailyClients, timeCommon, timeVIP, dayTime, pointerVIP);
    clearArray(timeVIP, pointerVIP);
    clearArray(timeCommon, pointerCommon);
    clearArray(timeAll, pointerAll);
}

int main()
{
    BigInt A{ "0", constMax }; // VIP frančizė A (Lt)
    BigInt A1{ "0", constMax }; // kiek atitenka servisui dėl bendradarbiavimo sutarties kaip priedas A1 (Lt)
    BigInt B{ "0", constMax }; // frančizė B=A-A1 (Lt)
    BigInt U{ "0", constMax }; // serviso darbuotojo valandinė alga U (Lt)
    BigInt profitVIP{ "0", constMax };
    BigInt profitCommon{ "0", constMax };
    BigInt dailyProfitVIP{ "0", constMax };
    BigInt dailyProfitCommon{ "0", constMax };
    BigInt zero{ "0", constMax };
    int K = 1; // darbuotojų skaičius K
    int T1 = 50; // tikimybė procentais, kad mašiną pristatys VIP klientas T1 (%)
    int T2 = 50; // tikimybe procentais, kad mašiną pristatys paprastas klientas T2 (%)
    int TR = 1; // atsitiktinis dydis valandomis, kurio reikia vienam darbuotojui sutvarkyti atvežtą mašiną TR (1 <= TR <= 5*K) (val)
    int T; // dienu skaicius
    int dailyHourLimit; // darbo valandos per diena
    int timeCommon[constMax];
    int timeVIP[constMax];
    int timeAll[constMax];
    int pointerVIP = 0;
    int pointerCommon = 0;
    int pointerAll = 0;

    priority_queue< int, vector<int> > dailyClients;
    ofstream file("protokolas.txt");

    system("cls");
    cout << "Anton Zagzin, 4 grupe, 2 pogrupis, 3 uzdavinis, 13 variantas" << endl;
    cout << "Uzduotis - kasko draudimas/autoservisas (ADT: prioritene eile, ilgas sveikas skaicius)" << endl;
    cout << "Programos tikslas pamodeliuoti, kokia verslo logika servisui naudingiausia: " << endl; 
    cout << "tureti kuo daugiau bendradarbiavimo sutarciu, ar dirbti visai be ju" << endl << endl;
    cout << "Pradiniai duomenys:" << endl;

    file << "PIRMA DALIS. Duomenys" << endl << endl;
    file << "  1. Anton Zagzin, 4 grupe, 2 pogrupis, 3 uzdavinis, 13 variantas" << endl;
    file << "  2. Uzduotis - kasko draudimas/autoservisas (ADT: prioritetine eile, ilgas sveikas skaicius)" << endl;
    file << "  3. Programos tikslas pamodeliuoti, kokia verslo logika servisui naudingiausia: " << endl;
    file << "     tureti kuo daugiau bendradarbiavimo sutarciu, ar dirbti visai be ju" << endl;

    readFromFile("duom_max.txt", file, A, A1, B, U, K, T1, T2, T, dailyHourLimit);
    srand(time(NULL));

    file << endl << "ANTRA DALIS. Vykdymas" << endl << endl;
    for (int i = 0; i < T; ++i)
    {
        
        file << endl << i + 1 << " diena" << endl << endl;
        for (int j = 0; j < K; ++j)
        {
            int dayTime = dailyHourLimit;
            file << "   " << j + 1 << " darbuotojas" << endl;
            fillTheClients(file, T1, dailyClients, timeCommon, timeVIP, timeAll,
                pointerVIP, pointerCommon, pointerAll, K, A, B, U, 
                profitVIP, profitCommon, dailyProfitVIP, dailyProfitCommon, dayTime);
        }
        file << endl << "Dienos pelnas be VIP sistemos: " << dailyProfitCommon << " Lt" << endl;
        file << "Dienos pelnas su VIP sistema:  " << dailyProfitVIP << " Lt" << endl;
        dailyProfitCommon = zero;
        dailyProfitVIP = zero;
    }

    file << endl << "TRECIA DALIS. Rezultatai" << endl;
    file << "  1. Is viso autoservisas dirbo " << T << " dienu po " << dailyHourLimit << " valandas" << endl;
    cout << endl << "Is viso autoservisas dirbo " << T << " dienu po " << dailyHourLimit << " valandas" << endl;
    file << "  2. Bendras pelnas be VIP sistemos: " << profitCommon << " Lt" << endl;
    cout << "Bendras pelnas be VIP sistemos: " << profitCommon << " Lt" << endl;
    file << "  3. Bendras pelnas su VIP sistema:  " << profitVIP << " Lt" << endl;
    cout << "Bendras pelnas su VIP sistema:  " << profitVIP << " Lt" << endl;

    if (profitVIP == profitCommon)
    {
        file << "  4. Abu verslo logikos budai gavo vienoda pelna " << endl;
        cout << "Abu verslo logikos budai gavo vienoda pelna " << endl;
    }
    else if (profitVIP > profitCommon)
    {
        file << "  4. Didesnis pelnas gautas su VIP sistema" << endl;
        cout << "Didesnis pelnas gautas su VIP sistema" << endl;
    }
    else
    {
        file << "  4. Didesnis pelnas gautas be VIP sistemos" << endl;
        cout << "Didesnis pelnas gautas be VIP sistemos" << endl;
    }

    return 0;
}
