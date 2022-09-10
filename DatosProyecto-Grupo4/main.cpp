#include "Interfaz.h"

int main() {
	Interfaz* obInter = new Interfaz();
	obInter->InterfazMenu();
	system("pause");
	delete obInter;
	return 0;
}