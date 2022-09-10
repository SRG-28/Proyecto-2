#include "Interfaz.h"

void Interfaz::InterfazMenu(){
    auto* theTree = new TwoFour();
    auto* random = new Random();
    int opcion,n;
    while (true) {

        try {
            {
                     cout << " ___________________________________________________________\n" <<
                             "|                                                           | \n"
                             "|                      Proyecto Final                       |\n"
                             "|___________________________________________________________|\n"
                             "|-->DIGITE 1:| Insertar n numeros aleatorios                |\n"
                             "|-->DIGITE 2:| Realizar 2n operaciones con probabilidades   |\n"
                             "|-->DIGITE 3:| Mostrar en InOrder                           |\n"
                             "|-->DIGITE 4:| Ver el arbol nivel por nivel                 |\n"
                             "|-->DIGITE 5:| Insertar un elemento                         |\n"
                             "|-->DIGITE 6:| Eliminar un elemento                         |\n"
                             "|-->DIGITE 7:| Encontrar un elemento                        |\n"
                             "|-->DIGITE 8:| Salir                                        |\n"
                             "|___________________________________________________________|\n" 
                             "->Digite una opcion: ";

                cin >> opcion;
                switch (opcion) {
                case 1: {
                    cout << "Ingrese el valor de n: ";
                    int aux = 0;
                    n = Validacion::validaInt(aux);
                    for (int a = 1; a < n + 1; a++) {
                        Node* present = theTree->find(a);
                        if (present != nullptr) {
                        }
                        else {
                            theTree->insert(a);
                        }
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                case 2: {
                    cout << "Ingrese el valor de n:";
                    cin >> n;
                        if (n == 3) {
                            while (n == 3) {
                                cout << "Ingrese un valor diferente a 3" << endl;
                                cout << "Ingrese el valor de n: ";
                                cin >> n;
                            }
                        }
                    int operation = 0;
                    int searchCount = 0;
                    int insertCount = 0;
                    int deleteCount = 0;
                    auto start = std::chrono::high_resolution_clock::now();
                    while (operation < (2 * n)) {
                        double rand = Random::nextDouble();
                        if (rand < 0.4) {
                            int x = Random::nextInt(n);
                            Node* present = theTree->find(x);
                            if (present != nullptr) {

                            }
                            else {
                                theTree->insert(x);
                            }
                            operation++;
                            insertCount++;
                        }
                        rand = Random::nextDouble();
                        if (rand < 0.25) {
                            int x = Random::nextInt(n);
                            Node* del = theTree->find(x);
                            if (del != nullptr) {
                                if (theTree->deleteD(del, x) != nullptr) {
                                }
                                else {
                                }
                            }
                            else {
                                operation++;
                            }
                            deleteCount++;
                        }
                        rand = Random::nextDouble();
                        if (rand < 0.35) { 
                            theTree->find(Random::nextInt(n));
                            operation++;
                            searchCount++;
                        }
                    }
                    auto finish = std::chrono::high_resolution_clock::now();
                    cout << "Numero total de operaciones de busqueda realizadas: " << searchCount <<endl;
                    cout << "Numero total de operaciones de eliminacion realizadas: " << deleteCount <<endl;
                    cout << "Numero total de operaciones deinsercion reaizadas: " << insertCount <<endl;
                    cout << "Tiempo de duracion: ";
                    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << " nanosegundos" << endl;
                    system("pause");
                    system("cls");
                    break;
                }
                case 3: {
                    cout << "===Mostrando==="<< endl;
                    cout << "In Order: " <<endl;
                    theTree->displayTree(1);
                    system("pause");
                    system("cls");
                    break;
                }
                case 4: {
                    cout << "===Ver arbol por nivel===" << endl;
                    cout << "Tree:" <<endl;
                    theTree->displayTree(0);
                    system("pause");
                    system("cls");
                    break;
                }
                case 5: {
                    cout << "Ingrese el valor que desea insertar: " ;
                    int value;
                    cin >> value;
                    Node* present = theTree->find(value);
                    if (present != nullptr) {
                        cout << "Datos ya presentes!!!" << endl;
                    }
                    else {
                        theTree->insert(value);
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                case 6: {
                    cout << "Ingrese el valor que desea eliminar: " ;
                    int value;
                    cin >> value;
                    Node* del = theTree->find(value);
                    if (del != nullptr) {
                        if (theTree->deleteD(del, value) != nullptr) {
                            cout << "Valor eliminado: " << value << endl;
                        }
                        else {
                            cout << "No eliminado!" << endl;
                        }
                    }
                    else {
                        cout << "Valor no encontrado:  " << value << endl;
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                case 7: {
                    cout << "Ingrese el valor que desea encontrar: ";
                    int value;
                    cin >> value;
                    Node* found = theTree->find(value);
                    if (found != nullptr) {
                        cout << "Valor encontrado:  " << value << endl;
                    }
                    else {
                        cout << "Valor no encontrado:  " << value << endl;
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                case 8:
                    cout << "Gracias por utilizar nuestra aplicacion!!!" <<endl;
                    exit(0);

                default:
                    cout << "Entrada invalida\n" << endl;
                }
            }
        }

        catch (exception e) {
            e.what();
        }
    }
}
