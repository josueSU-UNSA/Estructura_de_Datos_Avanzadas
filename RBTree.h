#include "Node.h"
#include<iostream>
#include<fstream>
using namespace std;
string colores[2]={" BLACK "," RED "};
template <class T>
class RBTree{
    private:
        Node<T>*m_pRoot;

        void Add(Node<T>*&pAux,T value,Node<T>*pPadre){
            if(!pAux){
                pAux=new Node<T>(value);
                pAux->m_pSig[2]=pPadre;
                Add_case_1(pAux);
                return;
                
            }
            if(pAux->value==value)return;
            Add(pAux->m_pSig[pAux->value<value],value,pAux);
            
        }

        Node<T>* find(Node<T>* pAux,T value){
            if(!pAux)return 0;
            if(pAux->value==value)return pAux;
            else return find(pAux->m_pSig[pAux->value<value],value);
        }

        void graficar(Node<T>* nodo, ofstream &archivo){
            if(!nodo) return;
            if(nodo->m_pSig[0]){
                archivo << nodo->value << "--" << nodo->m_pSig[0]->value << ";\n";
            }
            if(nodo->m_pSig[1]){
                archivo << nodo->value << "--" << nodo->m_pSig[1]->value << ";\n";
            }
            graficar(nodo->m_pSig[0], archivo);
            graficar(nodo->m_pSig[1], archivo);
        } 

        //CASO ES ROOT

        //**********************************FUNCIONA**********************************
        void Add_case_1(Node<T>*pAux){//caso el nodo a insertar sea la raiz entonces pasa de ser rojo a negro
            if(pAux->m_pSig[2]==0)pAux->color=BLACK;
            else Add_case_2(pAux);
        }

        //**********************************FUNCIONA**********************************
        //SI EL PADRE DEL NODO NUEVO INSERTADO ES NEGRO ES DECIR NO HAY DOS NODOS ROJOS CONSECUTIVOS
        //ENTONCES NO HACE NI UN COLOR FLIP NI UNA ROTATION
        void Add_case_2(Node<T>*pAux){//
            if(pAux->m_pSig[2]->color==BLACK)return;//tiene un padre negro y no hay problema
            else Add_case_3(pAux);
        }

        //*********************OJO:***********************
        
        //SOLO EN EL COLOR FLIP PUEDE HABER DOS NODOS ROJOS CONSECUTIVOS 
        //ESTO DEBIDO A Q EL ABUELO SE VUELVE ROJO Y SU PADRE PUEDE SER ROJO

        //*************************************************

        //SI PASA POR EL "ELSE" DEL ADD 2 QUIERE DECIR Q
        //EL PADRE NO ES NEGRO ES DECIR
        //EL PADRE ES ROJO POR LO Q DEBEMOS VER AL TIO PARA HACER UN COLOR FLIP O ROTATION
        //EN ESTE ADD VEMOS Q EL TIO ES ROJO
        //EN este CASO 3 SOLO HACEMOS un COLOR FLIP

        //**********************************FUNCIONA**********************************

        void Add_case_3(Node<T>*pAux){//EL PADRE DEL NEW NODO ES ROJO Y SU TIO ES ROJO
            Node<T>*pTio=tio(pAux);//TIO DE 
            Node<T>*pAbuelo=abuelo(pAux);
            if(pTio && pTio->color==RED){//so el tio es rojo ya q como sabemos si el tio es null es negro
                pAux->m_pSig[2]->color=BLACK;
                pTio->color=BLACK;
                pAbuelo->color=RED;
                Add_case_1(pAbuelo);//SE LLAMA AL CASO 1 YA Q SI EL ABUELO ES EL ROOT
                                    //NOSOTROS LO PINTAMOS DE ROJO
                                    //POR LO Q EL CASO 1 SE ENCARGA DE COLOREARLO CON NEGRO PORQ ES EL ROOT
                                    //TAMBIEN SIRVE PARA SABER Q SI EL PADRE DEL ABUELO ES ROJO PUES SE REPITE EL CICLO PARA ASI HACER 
                                    //YA SEA UN COLOR FLIP O UN ROTATION
            }
            else Add_case_4(pAux);
        }

    // ***********ROTATIONS*******************************************

        //*********************OJO:***********************

        //DESPUES DE HACER UNA ROTACION EL NODO ABUELO SE VUELVE NEGRO 
        //ENTONCES NO HAY MANERA Q EL ABUELO Y EL PADRE DEL ABUELO
        //SEAN ROJOS DESPUES DE LA ROTACION

        //ES POR ESTO Q AL FINAL DE PASAR POR UNA DE LAS ROTACIONES 
        //NO ES RECURSIVO Y VUELVE HACIA ATRAS

        //*************************************************

        //ESTE CASO SE REALIZA CUANDO EL PADRE ES ROJO
        //Y EL TIO ES NEGRO O NULL Q TMBN ES NEGRO
        //POR LO Q NECESITAMOS HACER UNA ROTACION
        //************ROTACIONES DOBLES***********

        //************ NO FUNCIONA AUN*****************************
        void Add_case_4(Node<T>*pAux){//LO Q HACE ES Q CAMBIA LOS CASOS NARIZ POR CASOS SIMPLES
            Node<T>*pAbuelo=abuelo(pAux);
            if((pAux==pAux->m_pSig[2]->m_pSig[1]) && (pAux->m_pSig[2]==pAbuelo->m_pSig[0])){//ROTACION IZQ DCHA
                rotar_izq(pAux->m_pSig[2]);
                pAux=pAux->m_pSig[0];
                //rotar_dcha(pAux->m_pSig[2]->m_pSig[2]);
                //return;
            }
            else if((pAux==pAux->m_pSig[2]->m_pSig[0]) &&(pAux->m_pSig[2]==pAbuelo->m_pSig[1])){//ROTACION DCHA IZQ
                rotar_dcha(pAux->m_pSig[2]);
                pAux=pAux->m_pSig[1];
                //rotar_izq(pAux->m_pSig[2]->m_pSig[2]);
                //return;
            }
            Add_case_5(pAux);//ES POR EL HECHO DE Q TRANSFORMA A UN SIMPLE Q TIENE Q LLAMAR AL CASO 5
        }
        //************ROTACIONES SIMPLES**********
        //******ESTE CASO CONVIERTE DE FORMATO SIMPLE A EQUILIBRADO*********

        //************FUNCIONA************************
        void Add_case_5(Node<T>*pAux){//LOS NODOS A ROTAR SE ENCUENTRAN EN UNA SOLA LINEA
            Node<T>*pAbuelo=abuelo(pAux);
            //LO Q REALIZAMOS EN ESTA PARTE ES EL CAMBIO DE COLOR DE LOS NODOS 
            //YA Q SIEMPRE EL CAMBIO SERA EN EL ABUELO Y EN EL PADRE
            //YA Q SOLO EL ABUELO BAJA A LA DCHA DEL PADRE DEL NODO A INSERTAR
            pAbuelo->color=RED;//ES ROJO XQ EL ABUELO SERA UN CHILDREN Y ESTOS SERAN ROJOS
            pAux->m_pSig[2]->color=BLACK;//ESTE NODO SERA EL PADRE POR LO Q SERA NEGRO

            //NO PUSIMOS LO SGTE XQ SE SOBREENTIENDE:

            //pAux->color=RED;

            //DAMOS POR HECHO Q EL NODO A INSERTAR ES ROJO 
            if ( (pAux==pAux->m_pSig[2]->m_pSig[0]) && (pAbuelo->m_pSig[0]==pAux->m_pSig[2]) )//ROTACION IZQ IZQ
            {
                rotar_dcha(pAbuelo);
            }
            else /*if ( (pAux->m_pSig[2]->m_pSig[1]==pAux) && (pAbuelo->m_pSig[1]==pAux->m_pSig[2]) )*/ //ROTACION DCHA DCHA
            {
                rotar_izq(pAbuelo);
            }
        }
        
        //*******ROTATIONS RBT**********

        void rotar_izq(Node<T>*p){
            Node<T>**aux=&(this->m_pRoot);
            if(p->m_pSig[2] && p->m_pSig[2]->m_pSig[1]==p) aux=&(p->m_pSig[2]->m_pSig[1]);//P ES EL HIJO DERECHO DE SU PADRE
            else if(p->m_pSig[2] && p->m_pSig[2]->m_pSig[0]==p)aux=&(p->m_pSig[2]->m_pSig[0]);//P ES EL HIJO IZQ DE SU PADRE
            //ESTA ES LA ROTACION PROPIAMENTE DICHA
            *aux=p->m_pSig[1];
            (*aux)->m_pSig[2]=p->m_pSig[2];
            p->m_pSig[2]=*aux;
            p->m_pSig[1]=(*aux)->m_pSig[0];
            (*aux)->m_pSig[0]=p;
            if(p->m_pSig[1])p->m_pSig[1]->m_pSig[2]=p;
        }

        void rotar_dcha(Node<T>*p){
            Node<T>**aux=&(this->m_pRoot);
            if(p->m_pSig[2] && p->m_pSig[2]->m_pSig[1]==p) aux=&(p->m_pSig[2]->m_pSig[1]);
            else if(p->m_pSig[2] && p->m_pSig[2]->m_pSig[0]==p) aux=&(p->m_pSig[2]->m_pSig[0]);

            *aux=p->m_pSig[0];
            (*aux)->m_pSig[2]=p->m_pSig[2];
            p->m_pSig[2]=*aux;
            p->m_pSig[0]=(*aux)->m_pSig[1];
            (*aux)->m_pSig[1]=p;

            if(p->m_pSig[0]) p->m_pSig[0]->m_pSig[2]=p;
            
        }

        // * ROTACIONES DOBLES Y SIMPLES

        //ROTACIONES DOBLES:

        //ROTACION DERECHA IZQUIERDA

        void RDI(Node<T>*&p){
            Node<T>*q=p->m_pSig[1];
            Node<T>*r=q->m_pSig[0];
            p->m_pSig[1]=r->m_pSig[0];
            q->m_pSig[0]=r->m_pSig[1];
            r->m_pSig[0]=p;
            r->m_pSig[1]=q;
            r->m_pSig[2]=p->m_pSig[2];
            p->m_pSig[2]=r;
            q->m_pSig[2]=r;
            r->color=BLACK;
            p->color=RED;
            q->color=RED;
            p=r;
        }

        //ROTACION IZQUIERDA DERECHA
        void RID(Node<T>*&p){
            
            Node<T>*q=p->m_pSig[0];
            Node<T>*r=q->m_pSig[1];
            
            q->m_pSig[1]=r->m_pSig[0];
            p->m_pSig[0]=r->m_pSig[1];
            r->m_pSig[1]=p;
            r->m_pSig[0]=q;
            r->m_pSig[2]=p->m_pSig[2];
            p->m_pSig[2]=r;
            q->m_pSig[2]=r;
            r->color=BLACK;
            q->color=RED;
            p->color=RED;

            p=r;//colocamos el r como punta del triangulo provocado por la rotacion
        }

        // * ROTACIONES SIMPLES:

        //ROTACION IZQUIERDA IZQUIERDA
        void RII(Node<T>*&p){
            Node<T>*q=p->m_pSig[0];
            p->m_pSig[0]=q->m_pSig[1];
            q->m_pSig[1]=p;

            //esto pasa cuando "q" no tiene  un hijo dcho y "p" no tiene un hijo dcho
            if(!p->m_pSig[0])q->FE=p->FE=0;
            else{//si "q" tiene un hijo dcho antes de la rotacion quiere decir q "p" tiene un hijo dcho
                q->FE=0;
                p->FE=0;
            }

            p=q;
        }

        //ROTACION DERECHA DERECHA
        void RDD(Node<T>*&p){
            Node<T>*q=p->m_pSig[1];
            p->m_pSig[1]=q->m_pSig[0];
            q->m_pSig[0]=p;

            //entara a esta 1ra condiciona cuando "q" no tenga un hijo izq es decir "p" no tiene un hijo izq  y mucho menos el "r" q es el posterior "q" , se coloca p xq la rotacion ya esta hecha y el hijo izq de q se traslado hacia esta parte
            if(!p->m_pSig[1])q->FE=p->FE=0;
            else{//quiere decir q "p" tiene un hijo izq y "q" un hijo izq 
                p->FE=0;
                q->FE=0;
            }

            p=q;//"q" asume la punta del triangulo
        }

    public:
        Node<T>* hermano(Node<T>* pAux){
            return ((pAux->son[2])->son[0] != pAux) ? pAux : (pAux->son[2])->son[1];
        }

        Node<T>* find(T value){
            return find(this->m_pRoot,value);
        }
        Node<T>* tio(Node<T>* t){
            return (((t->m_pSig[2])->m_pSig[2])->m_pSig[0] != t->m_pSig[2]) ? ((t->m_pSig[2])->m_pSig[2])->m_pSig[0] : ((t->m_pSig[2])->m_pSig[2])->m_pSig[1];
        }
        T tio(T value){
            return tio(find(value))->value;
        }
        void Add(T value){
            Add(this->m_pRoot,value,0);
        }
        
        void graficar(){
            if(!this->m_pRoot) return;
            ofstream archivo;
            archivo.open("grafo.dot");
            archivo << "graph A{\n";
            graficar(this->m_pRoot,archivo);
            archivo << "\n}";
            archivo.close();
            system("dot grafo.dot -o grafo.png -Tpng");
            system("grafo.png");
        }
        Node<T>*abuelo(Node<T>*pAux,int i){
            if(i==0)return pAux;
            if(!pAux->m_pSig[2])return 0;
            else return abuelo(pAux->m_pSig[2],--i);
        }
        Node<T>*abuelo(Node<T>*pAux){
            return abuelo(pAux,2);
        }

        // T abuelo(T value){
        //     return abuelo(find(value))->value;
        // }
        void print(Node<T>*pAux){
            if(!pAux)return;
            cout<<pAux->value<<" color is "<< colores[pAux->color]<<endl;
            print(pAux->m_pSig[0]);
            print(pAux->m_pSig[1]);
        }
        void print(){
            print(this->m_pRoot);
        }
        
    public:
        RBTree(){
            this->m_pRoot=0;
        }
        
};