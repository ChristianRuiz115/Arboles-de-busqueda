#include <iostream>

using namespace std;

template<class T>
class Arbol;

template<class T>
class Nodo{
	private:
		T dato;
		Nodo<T> *izq;
		Nodo<T> *der;
	public:
		Nodo():izq(nullptr),der(nullptr){};
		friend class Arbol<T>;
};

template<class T>
class Arbol{
	private:
		Nodo<T>* raiz;
		void recorrido_preorder(Nodo<T>* arbol);
		void recorrido_inorder(Nodo<T>* arbol);	
		void recorrido_postorder(Nodo<T>* arbol);
		void anula(Nodo<T>* arbol);
	public:
		Arbol(){};
		void inicializa();
		bool vacio();
		void inserta(const T& elemento);
		void insertar_nv(Nodo<T>* nodo,const T& elemento);
		void elimina(const T& elemento);
		Nodo<T>* eliminar_nv(Nodo<T>* nodo, const T& elemento);
		Nodo<T>* buscarMaximo(Nodo<T>* nodo);
		Nodo<T>* menor();
		Nodo<T>* mayor();
		Nodo<T>* localiza(const T& elem);
		T recupera(Nodo<T>* pos);
		void recorrido_preorder() {
			recorrido_preorder(raiz);
		}
		void recorrido_inorder(){
			recorrido_inorder(raiz);
		}
		void recorrido_postorder(){
			recorrido_postorder(raiz);
		}
		void anula(){
    		anula(raiz);
    		raiz = nullptr;
		}
				
		
};

template<class T>
void Arbol<T>::inicializa(){
	raiz = nullptr;
}

template<class T>
bool Arbol<T>::vacio(){
	return (raiz == nullptr);
}

template<class T>
void Arbol<T>::inserta(const T& elemento) {
    if (raiz == nullptr) {
        // El �rbol est� vac�o, crea un nuevo nodo y asigna como ra�z
        Nodo<T>* nuevoNodo = new Nodo<T>();
        nuevoNodo->dato = elemento;
        raiz = nuevoNodo;
    } else {
        // El �rbol no est� vac�o, realiza la inserci�n de manera recursiva
        insertar_nv(raiz, elemento);
    }
}

template<class T>
void Arbol<T>::insertar_nv(Nodo<T>* nodo, const T& elemento) {
    if (elemento < nodo->dato) {
        if (nodo->izq == nullptr) {
            // El sub�rbol izquierdo est� vac�o, crea un nuevo nodo y asigna como sub�rbol izquierdo
            Nodo<T>* nuevoNodo = new Nodo<T>();
            nuevoNodo->dato = elemento;
            nodo->izq = nuevoNodo;
        } else {
            // El sub�rbol izquierdo no est� vac�o, realiza la inserci�n en forma recursiva en el sub�rbol izquierdo
            insertar_nv(nodo->izq, elemento);
        }
    } else {
        if (nodo->der == nullptr) {
            // El sub�rbol derecho est� vac�o, crea un nuevo nodo y asigna como sub�rbol derecho
            Nodo<T>* nuevoNodo = new Nodo<T>();
            nuevoNodo->dato = elemento;
            nodo->der = nuevoNodo;
        } else {
            // El sub�rbol derecho no est� vac�o, realiza la inserci�n en forma recursiva en el sub�rbol derecho
            insertar_nv(nodo->der, elemento);
        }
    }
}

template<class T>
void Arbol<T>::elimina(const T& elemento) {
    raiz = eliminar_nv(raiz, elemento);
}

template<class T>
Nodo<T>* Arbol<T>::eliminar_nv(Nodo<T>* nodo, const T& elemento) {
    if (nodo == nullptr) {
        // Caso base: el nodo no existe, no hay nada que eliminar
        cout << "No hay nada que eliminar" << endl;
    }
    if (elemento < nodo->dato) {
        // El elemento a eliminar es menor, buscar en el sub�rbol izquierdo
        nodo->izq = eliminar_nv(nodo->izq, elemento);
    } else if (elemento > nodo->dato) {
        // El elemento a eliminar es mayor, buscar en el sub�rbol derecho
        nodo->der = eliminar_nv(nodo->der, elemento);
    } else {
        // El elemento a eliminar coincide con el elemento en el nodo actual
        if (nodo->izq == nullptr && nodo->der == nullptr) {
            // Caso 1: el nodo es una hoja, simplemente liberar memoria y actualizar referencia
            delete nodo;
            return nullptr;
        } else if (nodo->izq == nullptr) {
            // Caso 2: el nodo solo tiene sub�rbol derecho, reemplazar por el sub�rbol derecho
            Nodo<T>* temp = nodo->der;
            delete nodo;
            return temp;
        } else if (nodo->der == nullptr) {
            // Caso 3: el nodo solo tiene sub�rbol izquierdo, reemplazar por el sub�rbol izquierdo
            Nodo<T>* temp = nodo->izq;
            delete nodo;
            return temp;
        } else {
            // Caso 4: el nodo tiene ambos sub�rboles, encontrar el elemento mayor en el sub�rbol izquierdo y reemplazar
            Nodo<T>* maxIzq = buscarMaximo(nodo->izq);
            nodo->dato = maxIzq->dato;
            nodo->izq = eliminar_nv(nodo->izq, maxIzq->dato);
        }
    }    
    return nodo;
}

template<class T>
Nodo<T>* Arbol<T>::buscarMaximo(Nodo<T>* nodo) {
    while (nodo->der != nullptr) {
        nodo = nodo->der;
    }
    return nodo;
}

template<class T>
Nodo<T>* Arbol<T>::menor() {
    if (raiz == nullptr) {
        // El �rbol est� vac�o, devuelve nullptr
        return nullptr;
    } else {
        if (raiz->izq == nullptr) {
            // No hay sub�rbol izquierdo, devuelve el nodo ra�z
            return raiz;
        } else {
            // Hay un sub�rbol izquierdo, llama recursivamente a menor en el sub�rbol izquierdo
            Arbol<T> subarbol_izquierdo;
            subarbol_izquierdo.raiz = raiz->izq;
            return subarbol_izquierdo.menor();
        }
    }
}

template<class T>
Nodo<T>* Arbol<T>::mayor() {
    if (raiz == nullptr) {
        // El �rbol est� vac�o, devuelve nullptr
        return nullptr;
    } else {
        if (raiz->der == nullptr) {
            // No hay sub�rbol derecho, devuelve el nodo ra�z
            return raiz;
        } else {
            // Hay un sub�rbol derecho, llama recursivamente a mayor en el sub�rbol derecho
            Arbol<T> subarbol_derecho;
            subarbol_derecho.raiz = raiz->der;
            return subarbol_derecho.mayor();
        }
    }
}

template<class T>
Nodo<T>* Arbol<T>::localiza(const T& elem){
    if (raiz == nullptr) {
        // El �rbol est� vac�o, devuelve nullptr
        return nullptr;
    } else {
        if (elem == raiz->dato) {
            // El elemento coincide con el valor en el nodo ra�z
            return raiz;
        } 
		else if (elem < raiz->dato) {
            // El elemento es menor que el valor en el nodo ra�z, busca en el sub�rbol izquierdo
            Arbol<T> subarbol_izquierdo;
            subarbol_izquierdo.raiz = raiz->izq;
            return subarbol_izquierdo.localiza(elem);
        } 
		else {
            // El elemento es mayor que el valor en el nodo ra�z, busca en el sub�rbol derecho
            Arbol<T> subarbol_derecho;
            subarbol_derecho.raiz = raiz->der;
            return subarbol_derecho.localiza(elem);
        }
    }
}

template<class T>
T Arbol<T>::recupera(Nodo<T>* pos) {
    if (pos == nullptr) {
        // Error de excepci�n: Posici�n inv�lida
        throw "Error de excepci�n: Insuficiencia de datos";
    } else {
        return pos->dato;
    }
}

template<class T>
void Arbol<T>::recorrido_preorder(Nodo<T>* arbol) {
    if (arbol == nullptr) {
        // El �rbol est� vac�o, terminar
        return;
    } else {
        // Imprimir el valor del nodo actual
        cout << arbol->dato << " ";
        
        // Recorrer el sub�rbol izquierdo en preorden
        recorrido_preorder(arbol->izq);
        
        // Recorrer el sub�rbol derecho en preorden
        recorrido_preorder(arbol->der);
    }
}

template<class T>
void Arbol<T>::recorrido_inorder(Nodo<T>* arbol) {
    if (arbol == nullptr) {
        // El �rbol est� vac�o, terminar
        return;
    } else {
        // Recorrer el sub�rbol izquierdo en inorder
        recorrido_inorder(arbol->izq);
        
        // Imprimir el valor del nodo actual
        cout << arbol->dato << " ";
        
        // Recorrer el sub�rbol derecho en inorder
        recorrido_inorder(arbol->der);
    }
}

template<class T>
void Arbol<T>::recorrido_postorder(Nodo<T>* arbol) {
    if (arbol == nullptr) {
        // El �rbol est� vac�o, terminar
        return;
    } else {
        // Recorrer el sub�rbol izquierdo en postorder
        recorrido_postorder(arbol->izq);
        
        // Recorrer el sub�rbol derecho en postorder
        recorrido_postorder(arbol->der);
        
        // Imprimir el valor del nodo actual
        cout << arbol->dato << " ";
    }
}

template<class T>
void Arbol<T>::anula(Nodo<T>* arbol) {
    if (arbol == nullptr) {
        // El nodo es nulo, no hay nada que eliminar
        return;
    }
    // Anular el sub�rbol izquierdo
    anula(arbol->izq);
    // Anular el sub�rbol derecho
    anula(arbol->der);
    // Liberar memoria del nodo actual
    delete arbol;
}



int main(){
	Arbol<int> mi_arbol;
	mi_arbol.inicializa();
	mi_arbol.inserta(2);
	mi_arbol.inserta(3);
	mi_arbol.inserta(4);
	mi_arbol.inserta(1);
	Nodo<int>* max = mi_arbol.menor();
	Nodo<int>* menor = mi_arbol.mayor();
	mi_arbol.recorrido_preorder();
	cout << endl;
	mi_arbol.recorrido_inorder();
	cout << endl;
	mi_arbol.recorrido_postorder();
	mi_arbol.anula();
	cout << endl;
	cout << mi_arbol.vacio();
	return 0;
}

