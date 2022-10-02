enum Color{BLACK,RED};//Black es 0 RED es 1
template<class T>   
class Node{
    public:
        T value;
        Node<T>*m_pSig[3];
        bool color;

    public:

        Node(T value){
            this->value=value;
            this->m_pSig[0]=this->m_pSig[1]=this->m_pSig[2]=0;
            this->color=RED;//color rojo o TRUE=1
        }
};