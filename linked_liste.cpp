#include <iostream>
#include <stdlib.h>
#include <time.h>


class Node {
public:
    int data;
    Node* next = NULL; // pointer to Node, this variabel will be stored the address of the next Node in the linked liste
};


class List {
    public:
        Node* head = NULL; // pointer to Node, that will be store the address of the head Node(temp2 Node) in linked liste , Beobachtung dass wir es als "global declareted" damit es seine aufgabe macht nämlich dass es immer auf der erste element der linked liste zeigt

        void insert(int dat, int pos) //Position entpsricht Feldindex
        {
            Node* temp = new Node;
            temp->data = dat; // identisch zu (*temp).data = x; nämlich haben wir hier temp mit Typ data (int nach unseren dekleration in der classe "struct") mit der wert dat was als parameter in der insert funktion ist
            if (head == 0)
            {
                head = temp;   
            }
            else if(pos == 0)
            {
                temp->next = head; // wenn pos ist 0 dh verbinden wir was wir hinzufügen wollen wo gerade in head "linked list" steht
                head = temp; // das sagt jetzt steht als letztes element in der lined liste was wir hinzufügen wollten
            }
            else {
                Node* temp2 = head;         // wenn wir auf temp2 arbeiten es ist wie wenn wir auf head arbeiten weil pointer, ABER ohne head zu berühren damit head auch nutzen können in anderen aufrufe von insert function


                for (int i = 0; i < pos - 1; i++)
                {
                    if (temp2 == 0) return; // falls die pos kommt nach temp2, nämlich wenn dies geschich dann hinzufügen wir unser gewolltes element da, oder wenn in einer lücke landet dann dorthin das element hinz
                    temp2 = temp2->next; // erst mal holt sich temp2 = temp2 -> next, temp2->next->next..zu beobachten es wird je weils aufgelöst (temp2->next)->next, ((temp2->next)->next)->next
                }      //identsch:*(temp2).next, zweite durchlauf *(*(temp2).next) ..

                temp->next = temp2->next; // verbindung zwischen das neue node mit den nächsten node durch dass wir in dem neuen node(pointer neue node) die adresse nächste node enthält (zeigt auf das n#chste node) 
                temp2->next = temp; // verbingdung zwischen das element vorher das gezillte element pos mit der gezillte pos(so dass wie schreiben addresse das gezillte pos in der vorherige pos) DESWEGEN schreiben wir in den for-schleife pos-1 nämlich vorherige pos !
            }    
        } ////////////// Große BEOBACHTUNG wenn wir den node auf x-pos transpotieren, wird autmatisch diesen Node(block aus pointer und wert) mit seinem gezillten wert mitgenommen und dies haben wir deshalben so in zeile 20 deklariert 

        int getData(int pos) 
        {
            Node* temp2 = head;
            for (int i = 0; i < pos; i++)
            {
                if (temp2 == 0) return 0; //out of bounce
                temp2 = temp2->next;
            }
            return temp2->data;
        }

        
        void remove(int pos){
            
            Node* temp2 = head;
            
            for (int i = 0; i < pos-1; i++)
            {
                if (temp2 == 0) temp2 = head; //out of bounce
                temp2 = temp2->next;
            }
            
            temp2->next = temp2->next->next;
            
        }

};

        void swap(int pos1, int pos2)
        {
            Node* element1;
            Node* element2;
        
            if (pos1 == 0 )
            {
               element1 = head;
            }
            else {
                Node* temp21 = head;
                for (int i = 0; i < pos1 - 1; i++)
                {
                    if (temp21 == 0) return; //out of bounce
                    temp21 = temp21->next;
                }
                element1 = temp21->next;
            }


            if (pos2 == 0)
            {
                element2 = head;
            }
            else {
                Node* temp22 = head;
                for (int i = 0; i < pos2 - 1; i++)
                {
                    if (temp22 == 0) return; //out of bounce
                    temp22 = temp22->next;
                }
                element2 = temp22->next;
            }

            int a = getData(pos1);
            int b = getData(pos2);
            
            element1->data = b;
            element2->data = a;
        }

};

void PreparePartition(List &liste, int head, int last, int& part)
{
    int pivot = liste.getData(head);
    part = head - 1;

    for (int i = head; i <= last; i++)
    {
        if (liste.getData(i) <= pivot) //Wenn aktuelles Element <= Pivot-Element, dann tausche mit erster unsortierter Stelle (anfangs erste Stelle der Teilfolge) und erhöhe diese um eine Stelle
        {
            part++;
            liste.swap(i, part);
        }
    }
    liste.swap(head, part); //Pivor Element an die richtige Stelle tauschen
}

//setzt Zufallsindex nach vorne und ruft dann PreparePartition auf
void RandomSetPartition(List &liste, int head, int last, int& part)
{
    srand(time(NULL));
    int random = head + rand() % (last - head);   //Zufallsindex zwischen head und last generieren

    liste.swap(random, head);  //tausche Zufallsindex nach an die erste Position (head)

    PreparePartition(liste, head, last, part);
}

void Quicksort(List &liste, int head, int last)
{
    int part;
    if (head < last)
    {
        RandomSetPartition(liste, head, last, part);
        Quicksort(liste, head, part - 1);    //Teil vor "part"
        Quicksort(liste, part + 1, last);     //Teil nach "part"
    }
}

int main() {

    List liste;
    liste.insert(12, 0);
    liste.insert( 5, 1);
    liste.insert(22, 2);
    liste.insert(14, 3);
    liste.insert( 3, 4);
    liste.insert( 2, 5);
    liste.insert( 7, 6);
    liste.insert( 7, 7);
    liste.insert(31, 8);
    liste.insert(12, 9);
    
    Quicksort(liste, 0, 9);
    
    std::cout << liste.getData(0) << "|" << liste.getData(1) 
        << "|" << liste.getData(2) << "|" << liste.getData(3) 
            << "|" << liste.getData(4) << "|" << liste.getData(5) 
                << "|" << liste.getData(6) << "|" << liste.getData(7)
                    << "|" << liste.getData(8) << "|" << liste.getData(9) << std::endl;

   return 0;
}