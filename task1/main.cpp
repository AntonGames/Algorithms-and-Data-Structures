#define _CRT_SECURE_NO_WARNINGS
#include "BigInt.h"


int limitDigitAndDescription()
{
    std::cout << "Programa sukuria abstraktu duomenu tipa veiksmams su ilgais sveikaisiais teigiamais skaiciais atlikti. " << std::endl;
    std::cout << "Galima nustatyti skaiciu limita, du sveikuosius teigiamus skaicius " << std::endl;
    std::cout << "ir gaut ju suma, skirtuma, sandauga, dalmeni ir liekana. " << std::endl;
    std::cout << std::endl;
    int constMax;
    std::cout << "Iveskite visu skaitmenu ir rezultatu limita: ";
    std::cin >> constMax;
    constMax *= 1000;
    return constMax;
}

const int constMax = limitDigitAndDescription();

void writeInt(BigInt& A, const char prasymas[])
{
    std::cout << "Iveskite " << prasymas << " skaiciu: ";
    std::cin >> A;

    while (A.overMax())
    {
        std::cout << "Skaicius "  << A << " virsija " << constMax << " skaitmenu limita arba skacius neivestas, iveskite skaiciu dar karta: ";
        std::cin >> A;
    }
}

void ValidateNumber(int *number)
{
    char character;
    while (scanf("%d%c", number, &character) == 0 || character != '\n')
    {
        scanf("%*[^\n]");
        std::cout << "Neteisinga ivestis. Bandykite is naujo" << std::endl;
    }
}

int Input(BigInt& A, BigInt& B)
{
     int number;

    ValidateNumber(&number);
    while (number < 1 || number > 7)
    {
        std::cout << "Jusu ivestas skaicius nera nuo 1 iki 7. Bandykite dar karta" << std::endl;
        ValidateNumber(&number);
    }

    printf ("Jus pasirinkote %d\n", number);
    BigInt temp = A;
    switch(number)
    {
          case 1:
            temp += B;
            if (temp.overMax())
            {
                std::cout << "Suma virsija " << constMax/1000 << " skaitmenu limita" << std::endl;
            }
            else
            {
                std::cout << "Suma yra " << temp << std::endl;
            }
            temp = A;
            return 1;
        case 2:
            temp -= B;
            std::cout << "Skirtumas yra " << temp << std::endl;
            temp = A;
            return 1;
        case 3:
            temp *= B;
            if (temp.overMax())
            {
                std::cout << "Sandauga virsija " << constMax / 1000 << " skaitmenu limita" << std::endl;
            }
            else
            {
                std::cout << "Sandauga yra " << temp << std::endl;
            }
            temp = A;
            return 1;
        case 4:
            if (B.isZero())
            {
                std::cout << "Dalyba is 0 negalima! Rast dalmeni ir liekana neimanoma." << std::endl;
            }
            else
            {
                temp /= B;
                std::cout << "Dalmuo yra " << temp << std::endl;
            }
            temp = A;
            return 1;
        case 5:
            writeInt(A, "pirma");
            return 1;
        case 6:
            writeInt(B, "antra");
            return 1;
        case 7:
            std::cout << "Iseinama is programos" << std::endl;
            exit(0);
        default:
            return 0;
    }
}

void PrintMenu(BigInt& A, BigInt& B)
{
    std::cout << std::endl;
    std::cout << "Pasirinkite, ka toliau norite daryti su programa: " << std::endl;
    std::cout << "1. Apskaiciuoti suma" << std::endl;
    std::cout << "2. Apskaiciuoti skirtuma" << std::endl;
    std::cout << "3. Apskaiciuoti sandauga" << std::endl;
    std::cout << "4. Apskaiciuoti dalmeni ir liekana" << std::endl;
    std::cout << "5. Pakesti skaiciu " << A << std::endl;
    std::cout << "6. Pakesti skaiciu " << B << std::endl;
    std::cout << "7. Iseiti is programos" << std::endl;
    std::cout << std::endl;
}


int main() {

    BigInt A{"0", constMax};
    BigInt B{"0", constMax};

    writeInt(A, "prima");
    writeInt(B, "antra");

	int open = 1;
	while(open)
    {
        PrintMenu(A, B);
        open = Input(A, B);
    }
	return 0;

}
