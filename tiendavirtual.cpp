#include<iostream>
#include<locale>
#include<string.h>
using namespace std;

struct producto
{
    int id;
    string nombre;
    float precio;
    int cantidad;
    bool disponible;
};producto productos[20];
int totalprodu=0;

void ingresarprodu()
{
cout<<"==== INGRESE EL PRODUCTO ===="<<endl;
cout<<"ingrese el id del producto"<<endl;
cin>>productos[totalprodu].id;
cin.ignore();
cout<<"ingrese el nombre del producto"<<endl;
getline(cin,productos[totalprodu].nombre);
cout<<"ingrese el precio"<<endl;
cin>>productos[totalprodu].precio;
cout<<"ingrese la cantidad"<<endl;
cin>>productos[totalprodu].cantidad;

productos[totalprodu].disponible=true;

cout<<"producto ingresado correctamente";
totalprodu++;
}
void mostrarprodu()
{
    cout<<"==== lista de productos ===="<<endl;
    for (int i = 0; i < totalprodu; i++)
    {
        if (productos[i].disponible)
        {
            cout<<"ID: "<<productos[i].id<<endl;
            cout<<"NOMBRE: "<<productos[i].nombre<<endl;
            cout<<"PRECIO: Q"<<productos[i].precio<<endl;
            cout<<"CANTIDAD: "<<productos[i].cantidad<<endl;
            cout<<endl;
        }
        
    }
    
}
void buscarprodu(){}
void modificarprodu()
{
    int id;
    cout<<"ingrese el ID del producto a modificar: "<<endl;
    for (int i = 0; i < totalprodu; i++)
    {
        if (productos[i].id==id && productos[i].disponible)
        {
            cout<<"ingrese un nuevo nombre para el producto"<<endl;
            cin.ignore();
            getline(cin, productos[i].nombre);
            cout<<"ingrese un nuevo precio"<<endl;
            cin>>productos[i].precio;
            cout<<"ingrese nueva cantidad"<<endl;
            cin>>productos[i].cantidad;
            cout<<"producto modificado correctamente"<<endl;
            cout<<endl;
        }
        
    }
    cout<<"no se encontro el producto";
}
void eliminar(){}
void facturar(){}

main()
{
    setlocale(LC_ALL,"");
    int opcion;
    do
    {
    cout<<"===== TIENDA ELECTRÓNICA ====="<<endl;
    cout<<"1. Ingresar productos"<<endl;
    cout<<"2. Mostrar productos"<<endl;
    cout<<"3. Buscar productos"<<endl;
    cout<<"4. Modificar producto"<<endl;
    cout<<"5. Eliminar producto"<<endl;
    cout<<"6. Facturar"<<endl;
    cout<<"0. Salir"<<endl;
    cout<<"=====SELECCIONE UNA OPCIÓN====="<<endl;
    cin>>opcion;

    switch (opcion)
    {
        case 1:
        ingresarprodu();
        break;
        case 2:
        mostrarprodu();    
        break;
        case 3:
        buscarprodu();
        break;
        case 4:
        modificarprodu();
        break;
        case 5:
        eliminar();
        break;
        case 6:
        facturar();
        break;
        case 0:
        cout<<"saliendo del programa";
        break;
        default:
        cout<<"opción inválida";
    }
    } while (opcion!=0);
    
   
}