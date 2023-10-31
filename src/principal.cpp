/*
 * principal.cpp
 *
 *  Created on: 31/10/2023
 *      Author: algo2
 */

#include <iostream>
#include "Lista.h"

using namespace std;

class Cuenta {
  public:
    /* post: Cuenta con el nombre indicado.
     */
    Cuenta(string nombre);

    /* post: identificador de la cuenta.
     */
    string obtenerNombre();
    /* post: devuelve aquellas Cuentas de las
     *       que no se desean recibir Mensajes.
     */
    Lista<Cuenta*>* obtenerRemitentesBloqueados();

};

class Mensaje {
  public:
    /* post: Mensaje con el contenido indicado y sin Destinatarios.
     */
    Mensaje(Cuenta* remitente, string contenido);
    /* post: elimina todos los Destinatarios asociadas.
     */
    ~Mensaje();
    /* post: devuelve el contenido del Mensaje.
     */
    string obtenerContenido();
    /* post: devuelve la Cuenta que envía el Mensaje.
     */
    Cuenta* obtenerRemitente();
    /* post: devuelve todas las Cuentas a las que debe enviar el Mensaje.
     */
    Lista<Cuenta*>* obtenerDestinatarios();
 };


bool DestinatarioEstaBloqueado(Cuenta * remitente, Cuenta * destinatario){

	destinatario->obtenerRemitentesBloqueados()->iniciarCursor();

	while (destinatario->obtenerRemitentesBloqueados()->avanzarCursor()){
		Cuenta * remitentesBloqueados = destinatario->obtenerRemitentesBloqueados()->obtenerCursor();
		if (remitente->obtenerNombre() != remitentesBloqueados->obtenerNombre()){
			return true;
		}
	}
	return false;
}

class Mensajero {



	void AgregarRemitenteNoBloqueado(Mensaje * mensaje, Lista<Cuenta*>* destinatoriosAdicionales){

		Cuenta * remitenteDelMensaje = mensaje->obtenerRemitente();

		destinatoriosAdicionales->iniciarCursor();

		while(destinatoriosAdicionales->avanzarCursor()){
			Cuenta * destinatario = destinatoriosAdicionales->obtenerCursor();
			if (!DestinatarioEstaBloqueado(remitenteDelMensaje, destinatario)){
				mensaje->obtenerDestinatarios()->agregar(destinatario);
				destinatario->obtenerRemitentesBloqueados()->iniciarCursor();
			}
		}

	}


public:
	/* post: procesa 'mensajesPendientes' y a cada Mensaje le agrega como destinatario cada una de las Cuentas de la lista
	 *       'destinatariosAdicionales' siempre y cuando el remitente del Mensaje no está en la lista de remitentes
	 *       bloqueados de la Cuenta a ser agregada.
	 */
	void agregarDestinatarios(Lista<Mensaje*>* mensajesPendientes, Lista<Cuenta*>* destinatoriosAdicionales){

		mensajesPendientes->iniciarCursor();

		while (mensajesPendientes->avanzarCursor()){
			Mensaje * mensaje = mensajesPendientes->obtenerCursor();
			AgregarRemitenteNoBloqueado(mensaje, destinatoriosAdicionales);
		}

	}
};

int main(){



	return 0;
}
