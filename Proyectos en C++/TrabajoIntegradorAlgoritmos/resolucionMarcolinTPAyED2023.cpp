#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Empleado {
   char codEmp[9 + 1];
   char nombYApe[50 + 1];
   int cantProdVend;
};

struct Venta {
   char codEmp[9 + 1];
   int codProd;
   int fecha;
   float precioVenta;
};

struct VentaInfo {
   int codProd;
   int fecha;
};

struct NodoPilaReporte {
   VentaInfo info;
   NodoPilaReporte* sgte;
};

struct Reporte {
   char codEmp[9 + 1];
   char nombYApe[50 + 1];
   int cantProdVend;
   float totalRecaudado;
   NodoPilaReporte* raizPilaReporte;
};

void crearEmpleados() {

   FILE* empleados = fopen("Empleados.dat","wb+");

   Empleado vecE[4] = {
      { "EE", "Juan Gomez", 50 },
      { "AA", "Pablo Perez", 100 },
      { "ZZ", "Ariel Gimenez", 10 },
      { "NN", "Roberto Diaz", 200 }
   };

   fwrite(vecE, sizeof(Empleado), 4, empleados);
   fclose(empleados);
}

void mostrarEmpleados() {
   FILE* empleados = fopen("Empleados.dat","rb+");

   cout << "[Codigo Empleado], [Nombre y Apellido], [Cantidad de productos Vendidos]" << endl;

   Empleado e;
   fread(&e, sizeof(Empleado), 1, empleados);

   while (!feof(empleados)) {
      cout << e.codEmp << ", " << e.nombYApe << ", " << e.cantProdVend << endl;
      fread(&e, sizeof(Empleado), 1, empleados);
   }

   cout << endl;
   fclose(empleados);
}

void crearVentas() {

   FILE* ventas = fopen("Ventas.dat","wb+");

   Venta vecV[11] = {
      { "EE", 1, 20141001, 40.0 },
      { "ZZ", 5, 20141001, 30.0 },
      { "EE", 2, 20141002, 15.0 },
      { "AA", 5, 20141002, 30.0 },
      { "AA", 5, 20141002, 30.0 },
      { "EE", 2, 20141002, 15.0 },
      { "ZZ", 3, 20141004, 70.0 },
      { "ZZ", 3, 20141010, 70.0 },
      { "EE", 2, 20141011, 15.0 },
      { "ZZ", 4, 20141015, 60.0 },
      { "ZZ", 5, 20141015, 30.0 }
   };

   fwrite(vecV, sizeof(Venta), 11, ventas);
   fclose(ventas);
}

void mostrarVentas() {
   FILE* ventas = fopen("Ventas.dat","rb+");

   cout << "[Codigo Empleado], [Codigo Producto], [Fecha], [Precio de Venta]" << endl;

   Venta v;
   fread(&v, sizeof(Venta), 1, ventas);

   while (!feof(ventas)) {
      cout << v.codEmp << ", " << v.codProd << ", " << v.fecha << ", " << v.precioVenta << endl;
      fread(&v, sizeof(Venta), 1, ventas);
   }

   fclose(ventas);
}

void agregar(Reporte arr[], int& len, Reporte v) {
   arr[len] = v;
   len = len + 1;
}

int buscar(Reporte arr[], int len, char codEmp[]) {
   int pos = -1;
   int i = 0;

   while(pos == -1 && i <= len - 1) {
      if((string)arr[i].codEmp == codEmp) {
         pos = i;
      }
      i = i + 1;
   }

   return pos;
}

void push(NodoPilaReporte*& raiz, VentaInfo info) {
   NodoPilaReporte* pNuevo = new NodoPilaReporte();
   pNuevo -> info = info;
   pNuevo -> sgte = raiz;
   raiz = pNuevo;
}

VentaInfo pop(NodoPilaReporte*& raiz) {
   NodoPilaReporte* pAux = raiz;
   VentaInfo info = pAux -> info;
   raiz = pAux -> sgte;
   delete pAux;
   return info;
}

void ordenarArrDesc(Reporte arr[], int len) {
   for (int j = 1; j <= len - 1; j++) {
      for(int i = 0; i <= len - 1 - 1; i++) {
         if (arr[i].totalRecaudado < arr[i + 1].totalRecaudado) {
            Reporte aux = arr[i + 1];
            arr[i + 1] = arr[i];
            arr[i] = aux;
         }
      }
   }
}

void cargarReporteEmpleados(Reporte arr[], int& len){
   FILE* empleados = fopen("Empleados.dat","rb+");

   Empleado regE;
   fread(&regE, sizeof(Empleado), 1, empleados);

   while(!feof(empleados)){
      Reporte infoR;
      strcpy(infoR.codEmp, regE.codEmp);
      strcpy(infoR.nombYApe, regE.nombYApe);
      infoR.cantProdVend = regE.cantProdVend;
      infoR.totalRecaudado = 0;
      infoR.raizPilaReporte = NULL;

      agregar(arr, len, infoR);

      fread(&regE, sizeof(Empleado), 1, empleados);
   }
   fclose(empleados);
}

void cargarPilaVentas(Reporte arr[], int len){
   FILE* ventas = fopen("Ventas.dat","rb+");

   Venta v;
   fread(&v, sizeof(Venta), 1, ventas);

   while (!feof(ventas)) {

         VentaInfo infoV;
         infoV.codProd = v.codProd;
         infoV.fecha = v.fecha;

         int pos = buscar(arr, len, v.codEmp);

         push(arr[pos].raizPilaReporte, infoV);

         arr[pos].cantProdVend++;
         arr[pos].totalRecaudado = arr[pos].totalRecaudado + v.precioVenta;

         fread(&v, sizeof(Venta), 1, ventas);
      }

      fclose(ventas);
}

void mostrarReporte(Reporte arr[], int len){
   for(int i=0; i <= len - 1; i++){

      cout << "Codigo de empleado: " << arr[i].codEmp << endl;
      cout << "Nombre y Apellido: " << arr[i].nombYApe << endl;
      cout << "Total de productos vendidos: " << arr[i].cantProdVend << endl;
      cout << "Total recaudado: " << "$" << arr[i].totalRecaudado << endl;
      cout << "Productos vendidos: " << endl;



      while(arr[i].raizPilaReporte != NULL){
         VentaInfo info = pop(arr[i].raizPilaReporte);
         cout << "Codigo producto: " << info.codProd << " | " << "Fecha: " << info.fecha << endl;
      }
      cout << "---------------------------------------------" << endl;
   }
}


void resolucionTp(Reporte arr[], int& len) {

   cargarReporteEmpleados(arr, len);

   cargarPilaVentas(arr, len);

   ordenarArrDesc(arr, len);

   mostrarReporte(arr, len);

}

int main() {

   crearEmpleados();
   mostrarEmpleados();
   crearVentas();
   mostrarVentas();

   cout << "---------------------------------------------" << endl;
   cout << "---------------------------------------------" << endl;

   Reporte arr[50];
   int len = 0;

   resolucionTp(arr, len);

   return 0;
}
