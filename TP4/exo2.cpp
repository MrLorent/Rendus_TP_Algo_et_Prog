#include <time.h>
#include <stdio.h>

#include <QApplication>
#include <QDebug>

#include "tp3.h"
#include "HuffmanNode.h"

_TestMainWindow* w = nullptr;
using std::size_t;
using std::string;

void HuffmanHeap::insertHeapNode(int heapSize, unsigned char c, int frequences)
{
    /**
      * Do Like Heap::insertHeapNode (exo1) but use HuffmanNode instead of
      * int, this->get(i): HuffmanNode*  <-> this->get(i).frequences
     **/
    int i = heapSize;
    HuffmanNode * newNode = new HuffmanNode(c,frequences);
    this->set(heapSize, *newNode);

    while(i>0 && this->get(i).frequences < this->get((i-1)/2).frequences){
        this->swap(i, (i-1)/2);
        i = (i-1)/2;
    }

}

void HuffmanNode::insertNode(HuffmanNode* node)
{
    if( this->isLeaf() )
    {
        /**
         * On crée un nouveau noeud qui copie les données de this
         * (char, frequences)
         * Selon la valeur du noeud à insérer on l'insère soit à gauche
         * soit à droite et on insère la copie de this de l'autre coté
         *
         * La feuille courante (this) devient un parent et donc sa
         * fréquence devient la somme de ses nouveaux enfants et
         * son caractère devient '\0'
        **/
        HuffmanNode* copy = new HuffmanNode(this->character, this->frequences);
        this->character = '\0';
        if(3*node->frequences < this->frequences){
            this->left = node;
            this->right = copy;
        }else{
            this->left = copy;
            this->right = node;
        }
    }
    else
    {
        /**
         * Le noeud courant est un parent donc il faut demander
         * aux enfants d'insérer (soit à gauche si 3*node->frequences < this->frequences
         * soit à droite)
         * Remarques: Si un noeud n'est pas une feuille alors ses deux enfants sont
         * non-null (grâce à la condition d'au-dessus)
        **/
        if(3*node->frequences < this->frequences){
            this->left->insertNode(node);
        }else{
            this->right->insertNode(node);
        }

    }
    /**
     * à chaque insertion on additionne au noeud courant la valeur
     * du noeud à insérer (pour faire en sorte que la valeur du parent soit
     * toujours la somme de ses deux enfants)
     **/
    this->frequences += node->frequences;
}

void HuffmanNode::processCodes(std::string baseCode)
{
    /**
      * Travel whole tree of HuffmanNode, each time you call the left
      * child, add '0' to the baseCode and each time call the right
      * child, add '1'. If the node is a leaf, it takes the baseCode.
     **/
    if(this->isLeaf()){
        this->code = baseCode;
    }else{
        this->left->processCodes(baseCode + "0");
        this->right->processCodes(baseCode + "1");
    }
}

void HuffmanNode::fillCharactersArray(HuffmanNode** nodes_for_chars)
{
    if (!this->left && !this->right)
        nodes_for_chars[this->character] = this;
    else {
        if (this->left)
            this->left->fillCharactersArray(nodes_for_chars);
        if (this->right)
            this->right->fillCharactersArray(nodes_for_chars);
    }
}

void charFrequences(string data, Array& frequences)
{
    /**
      * frequences is an array of 256 int. frequences[i]
      * is the frequence of the caracter with ASCII code i
     **/
    for(int i=0; i<(int)data.size(); i++){
        frequences.get(data.at(i))++;
    }
}

void huffmanHeap(Array& frequences, HuffmanHeap& heap, int& heapSize)
{
    /**
      * Do like Heap::buildHeap. Use only non-null frequences
      * Define heapSize as numbers of inserted nodes
     **/
    heapSize = 0;
    for(int i=0; i<(int)frequences.size(); i++){
        if(frequences.get(i) > 0){
            heap.insertHeapNode(heapSize, (char)i, frequences.get(i));
            heapSize++;
        }
    }
}

void huffmanDict(HuffmanHeap& heap, int heapSize, HuffmanNode*& dict)
{
    /**
      * For each value in heap, insert a new node in dict
     **/
    dict = new HuffmanNode(heap.get(0).character, heap.get(0).frequences);
    for(int i=1; i<heapSize; i++){
        dict->insertNode(new HuffmanNode(heap.get(i).character, heap.get(i).frequences));
    }
}

string huffmanEncode(HuffmanNode** characters, string toEncode)
{
    /**
      * characters gather all leaves in the Huffman dict
      * characters[i] is the HuffmanNode representing the
      * character with the ASCII code i
     **/
    string encoded = "";

    for(int i=0; i<(int)toEncode.size(); i++){
        encoded += characters[(int)toEncode.at(i)]->code;
    }

    return encoded;
}

string huffmanDecode(HuffmanNode* dict, string toDecode)
{
    /**
      * Use each caracters of toDecode, which is '0' either '1',
      * to travel the Huffman dict. Each time you get a leaf, get
      * the decoded character of this node.
     **/
    string decoded = "";
    HuffmanNode * tmp = dict;

    for(int i=0; i<(int)toDecode.size(); i++){
        if(tmp->isLeaf()){
            decoded += tmp->character;
            tmp = dict;
            i--;
        }else{
            if(toDecode.at(i) == '0'){
                tmp = tmp->left;
            }else{
                tmp = tmp->right;
            }
        }
    }
    decoded += tmp->character;

    return decoded;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Array::wait_for_operations = false;
    w = new _TestMainWindow();

    string data = "Yo les djeuns ! Alors, on code l'internet ou quoi la ?";

    Array& frequences = w->newArray(256);
    HuffmanHeap heap(256);
    HuffmanNode* dict;
    int i;

    for (i=0; i < (int)frequences.size(); ++i)
        frequences.__set__(i, 0);

    charFrequences(data, frequences);

    for (i=0; i < (int)frequences.size(); ++i)
        if (frequences[i]>0)
            qDebug() << (char)i << ": " << frequences[i];

    int heapSize=0;

    huffmanHeap(frequences, heap, heapSize);
    huffmanDict(heap, heapSize, dict);
    dict->processCodes("");

    HuffmanNode* characters[256];
    memset(characters, 0, 256 * sizeof (HuffmanNode*));
    dict->fillCharactersArray(characters);

    string encoded = huffmanEncode(characters, data);
    string decoded = huffmanDecode(dict, encoded);

    w->addBinaryNode(dict);
    w->updateScene();
    qDebug("Encoded: %s\n", encoded.c_str());
    qDebug("Decoded: %s\n", decoded.c_str());
    w->show();

    return a.exec();
}
