#include "mainwindow.h"
#include "tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

// LIGNES A AJOUTER DANS binaytree.h :
//// ACCESSORS
//// in reading
//virtual Node* get_left_child() const {return nullptr;}
//virtual Node* get_right_child() const {return nullptr;}

//// in setting
//virtual void set_value(int newValue){}
//virtual void set_left_child(Node* leftChild){}
//virtual void set_right_child(Node* rightChild){}

//// METHODS
//virtual void leftRotate(){}
//virtual void rightRotate(){}

struct BinarySearchTree : public BinaryTree
{    
    Node* left;
    Node* right;
    int value;

    void initNode(int aValue)
    {
        // init initial node without children
        this->value = aValue;
        this->left = NULL;
        this->right = NULL;
    }

    void insertNumber(int aValue) {
        // create a new node and insert it in right or left child
        if(this->value > aValue){
            if(this->left == NULL){
                this->left = createNode(aValue);
            }else{
                this->left->insertNumber(aValue);
            }
        }else{
            if(this->right == NULL){
                this->right = createNode(aValue);
            }else{
                this->right->insertNumber(aValue);
            }
        }

        if(balance(this) == -2){
            if(this->height() == 3){
                this->simpleRightRotate();
            }else{

//  HUGE_ROTATION_LEFT IN MAINTENANCE

//                if(balance(this->left) < 0){
//                    this->rightRotate();
//                }else{
//                    this->left->leftRotate();
//                    this->rightRotate();
//                }
            }

        }

        if(balance(this) == 2){
            if(this->height() == 3){
                this->simpleLeftRotate();
            }else{

// HUGE_ROTATION_RIGHT IN MAINTENANCE

//                if(balance(this->right) < 0){
//                    this->right->rightRotate();
//                    this->leftRotate();
//                }else{
//                    this->leftRotate();
//                }
            }
        }
    }

    int balance(Node* node)
    {
        int leftHeight, rightHeight;

        // computing of the left height
        if(node->get_left_child() == NULL){
            leftHeight = 0;
        }else{
            leftHeight = this->left->height();
        }

        // computing of the right height
        if(node->get_right_child() == NULL){
            rightHeight = 0;
        }else{
            rightHeight = this->right->height();
        }

        return rightHeight - leftHeight;
    }

    void simpleRightRotate(){
        if(this->left->get_left_child()){
            this->right = createNode(this->value);
            this->value = this->left->get_value();
            this->left->set_value(this->left->get_left_child()->get_value());
            delete this->left->get_left_child();
            this->left->set_left_child(NULL);
        }else{
            this->right = createNode(this->value);
            this->value = this->left->get_right_child()->get_value();
            delete this->left->get_right_child();
            this->left->set_right_child(NULL);
        }
    }

    void simpleLeftRotate(){
        if(this->right->get_right_child()){
            this->left = createNode(this->value);
            this->value = this->right->get_value();
            this->right->set_value(this->right->get_right_child()->get_value());
            delete this->right->get_right_child();
            this->right->set_right_child(NULL);
        }else{
            this->left = createNode(this->value);
            this->value = this->right->get_left_child()->get_value();
            delete this->right->get_left_child();
            this->right->set_left_child(NULL);
        }
    }

    void rightRotate(){
        qDebug("ok1.0\n");
        Node* right_right = NULL;
        Node* right_left = NULL;

        if(this->right){
            right_right = this->right;
            this->right = NULL;
        }

        if(this->left->get_right_child()){
            right_left = this->left->get_right_child();
            this->left->set_right_child(NULL);
        }

        this->right = createNode(this->value);

        this->value = this->left->get_value();

        if(this->left->get_left_child()){
            this->left = this->left->get_left_child();
        }
        qDebug("ok2.0\n");

        if(right_left){
            this->right->set_left_child(right_left);
        }

        if(right_right){
            this->right->set_right_child(right_right);
        }
    }

    void leftRotate(){
        qDebug("ok1.1\n");
        Node* left_left = NULL;
        Node* left_right = NULL;

        if(this->left){
            left_left = this->left;
            this->left = NULL;
        }

        if(this->right->get_left_child()){
            left_right = this->right->get_left_child();
            this->right->set_left_child(NULL);
        }

        this->left = createNode(this->value);

        this->value = this->right->get_value();

        if(this->right->get_right_child()){
            this->right = this->right->get_right_child();
        }
        qDebug("ok2.1\n");

        if(left_left){
            this->left->set_left_child(left_left);
        }

        if(left_right){
            this->left->set_right_child(left_right);
        }

    }

	uint height() const	{
        // should return the maximum height between left child and
        // right child +1 for itself. If there is no child, return
        // just 1

        int leftHeight = 0, rightHeight = 0;

        if(this->isLeaf()){
            return 1;
        }else{
            // computing of the left height
            if(this->left == NULL){
                leftHeight = 0;
            }else{
                leftHeight = this->left->height();
            }

            // computing of the right height
            if(this->right == NULL){
                rightHeight = 0;
            }else{
                rightHeight = this->right->height();
            }

            // We send back the longer length
            if(leftHeight > rightHeight){
                return leftHeight + 1;
            }else{
                return rightHeight + 1;
            }
        }
    }

	uint nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1

        int leftHeight = 0, rightHeight = 0;

        if(this->isLeaf()){
            return 1;
        }else{
            // computing of the left height
            if(this->left == NULL){
                leftHeight = 0;
            }else{
                leftHeight = this->left->nodesCount();
            }

            // computing of the right height
            if(this->right == NULL){
                rightHeight = 0;
            }else{
                rightHeight = this->right->nodesCount();
            }

            // We send back the length of the the two branches plus
            // the current node
            return leftHeight + rightHeight + 1;
        }
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        if(this->left == NULL && this->right == NULL){
            return true;
        }else{
            return false;
        }
	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        // fill leaves array with all leaves of this tree
        if(this->isLeaf()){
            leaves[leavesCount] = this;
            leavesCount++;
        }else{
            if(this->left != NULL){
                this->left->allLeaves(leaves, leavesCount);
            }
            if(this->right != NULL){
                this->right->allLeaves(leaves, leavesCount);
            }
        }
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with inorder travel
        if(this->left != NULL){
            this->left->inorderTravel(nodes, nodesCount);
        }

        nodes[nodesCount] = this;
        nodesCount++;

        if(this->right != NULL){
            this->right->inorderTravel(nodes, nodesCount);
        }
	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with preorder travel
        nodes[nodesCount] = this;
        nodesCount++;

        if(this->left != NULL){
            this->left->preorderTravel(nodes, nodesCount);
        }

        if(this->right != NULL){
            this->right->preorderTravel(nodes, nodesCount);
        }
	}

    void postorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with postorder travel
        if(this->left != NULL){
            this->left->postorderTravel(nodes, nodesCount);
        }

        if(this->right != NULL){
            this->right->postorderTravel(nodes, nodesCount);
        }

        nodes[nodesCount] = this;
        nodesCount++;
	}

    Node* find(int aValue) {
        // find the node containing value
        if(this->isLeaf() && this->value != aValue){
            return NULL;
        }else{
            if(this->value == aValue){
                return this;
            }else{
                if(this->value < aValue){
                    this->right->find(aValue);
                }else{
                    this->left->find(aValue);
                }
            }
        }
	}

    void reset()
    {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
        left = right = NULL;
    }

    void set_value(int newValue){
        value = newValue;
    }

    void set_left_child(Node * leftChild){
        this->left = leftChild;
    }

    void set_right_child(Node * rightChild){
        this->right = rightChild;
    }


    BinarySearchTree(int value) : BinaryTree(value) {initNode(value);}
    ~BinarySearchTree() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}

};

Node* createNode(int value) {
    return new BinarySearchTree(value);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow<BinarySearchTree>();
	w->show();

	return a.exec();
}
