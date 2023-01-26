#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

//by Momen Odeh & Noor Aldeen Abu Shehadeh
void AluSatge(int stage) {
	char A, B, Cin, Zin, op, SRI;
	char F, Zout;
	char Cout;
	int address;
	enum operation
	{
		ADD=0, SUB=1, INC=2, DEC=3, AND=4, OR=5, XOR=6, NOT=7, PASSA=8, PASSB=9, ROL=10, ROR=11
	};
	ofstream Stage1File, Stage2File;

	int addresslimit;

	if (stage == 1) {
		addresslimit = pow(2, 14);
		Stage1File.open("Stage1.bin", ios::binary | ios::out);
	}


	else if (stage == 2) {
		addresslimit = pow(2, 15);
		Stage2File.open("Stage2.bin", ios::binary | ios::out);
	}



	for ( int i = 0; i < addresslimit; i++) {

		address = i;

		A = address & 0x0F;            //                  0000 A3A2A1A0
		B = (address >> 4) & 0x0F;     //                  0000 B3B2B1B0
		Cin = (address >> 8) & 0x01;   //                  0000 000Cin
		SRI = (address >> 5) & 0x10;   //                000SRI 0000
		op = (address >> 10) & 0x0F;   //                  0000 op3op2op1op0
		if (stage == 2)
	    Zin = (address >> 9) & 0x20;   //                00Zin0 0000

		switch (op) {
		case ADD:
			if (stage == 1) { F = A + B; }
			else { F = A + B + Cin; }
			break;
		case SUB:
			if (stage == 1) { F = A - B; }
			else { F = A - B - Cin; }
			break;
		case INC:
			if (stage == 1) { F = A + 1; }
			else { F = A + Cin; }
			break;
		case DEC:
			if (stage == 1) { F = A - 1; }
			else { F = A - Cin; }
			break;
		case AND:
			F = A & B;
			if (stage == 2) { F = F | SRI; }
			break;
		case OR:
			F = A | B;
			if (stage == 2) { F = F | SRI; }
			break;
		case XOR:
			F = A ^ B;
			if (stage == 2) { F = F | SRI; }
			break;
		case NOT:
			F = ~A;
			F = F & 0x0F;
			if (stage == 2) {
				F = F | SRI;
			}
			break;
		case PASSA:
			F = A;
			if (stage == 2) { F = F | SRI; }
			break;
		case PASSB:
			F = B;
			if (stage == 2) { F = F | SRI; }
			break;
		case ROL:
			F = A << 1;
			F = F | Cin;
			break;
		case ROR:
			F = (A | SRI) >> 1;
			if (stage == 1) { Cin = A & 0x0001; }   //Cin = A0
			Cout = Cin << 4;                        //Cout = Cin = A0 0000 to set the 5th bit 
			F = F | Cout;
			break;
		}


		Zout = F & 0x0F;
		if (Zout == 0)Zout = 0x20;                 //to set the 6th bit
		else Zout = 0;                            // if the result not zero

		if (stage == 2)  Zout = Zout & Zin;

		F = F & 0x01F;

		F = F | Zout;

		if (stage == 1) {
			Stage1File << F;
		}
		else if (stage == 2) {
			Stage2File << F;
		}
	}
	if (stage == 1) {
		Stage1File.close();
	}
	else if (stage == 2) {
		Stage2File.close();
	}
}




int main()
{

	AluSatge(1);
	AluSatge(2);

	return 0;
}


