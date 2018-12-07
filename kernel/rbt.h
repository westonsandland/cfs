#include "stdint.h"
#include "debug.h"

#define RED false
#define BLACK true

template <typename T>
struct RBTNode {
        T* item;
        bool black;
        RBTNode<T>* left;
        RBTNode<T>* right;
        RBTNode<T>* parent;

public:
        RBTNode(T* item, bool black, RBTNode<T>* left, RBTNode<T>* right,  
                       RBTNode<T>* parent){ 
                this->item = item;
                this->black = black;
                this->left = left; 
                this->right = right;
                this->parent = parent;
        }

        bool isBlack(){
                if(black)
                        return true;
                return false;
        }

        void setColor(bool black){
                this->black = black;
        }

        void printNode(uint32_t tab) {
            Debug::printf("***");
            for(uint32_t i = 0; i < tab; i++) {
                Debug::printf("\t");
            }
            Debug::printf("item = %d\n",(uint32_t)*item);
        } 
};

template <typename T>
class RBT {
        RBTNode<T>* root;
        uint32_t size;

        RBTNode<T>* getUncle(RBTNode<T>* n) {
            RBTNode<T>* parent = n->parent;
            RBTNode<T>* gparent = n->parent->parent;

            if(gparent->left == parent)
                return gparent->right;
            else
                return gparent->left;
        }

        void rotateLeft(RBTNode<T>* cur) {
             RBTNode<T>* oldRight = cur->right;
             cur->right = oldRight->left;

             if(oldRight->left != nullptr) {
                   cur->right->parent = cur;
             }
             
             oldRight->parent = cur->parent;
             
             if(cur->parent == nullptr)
                 root = oldRight;
             else if(cur == cur->parent->left)
                 cur->parent->left = oldRight;
             else
                 cur->parent->right = oldRight;

             oldRight->left = cur;
             cur->parent = oldRight;
        }

       void rotateRight(RBTNode<T>* cur) {
             RBTNode<T>* oldLeft = cur->left;
             cur->left = oldLeft->right;

             if(oldLeft->right != nullptr) {
                   cur->left->parent = cur;
             }
             
             oldLeft->parent = cur->parent;
             
             if(cur->parent == nullptr)
                 root = oldLeft;
             else if(cur == cur->parent->right)
                 cur->parent->right = oldLeft;
             else
                 cur->parent->left = oldLeft;

             oldLeft->right = cur;
             cur->parent = oldLeft;
        }

        void recursiveAdd(RBTNode<T>* current, RBTNode<T>* parent, T* item){
            if(root == nullptr) {
                root = new RBTNode<T>(item, BLACK, nullptr, nullptr, parent);
                return;
            }

            if(current == nullptr){
                current = new RBTNode<T>(item, RED, nullptr, nullptr, parent);
                addCheck(current);
                return;
            }
            if(*(current->item) > *item){
                recursiveAdd(current->left, current, item);
            }
            else{
                recursiveAdd(current->right, current, item);
            }
        }

        void addCheck(RBTNode<T>* justAdded)
        {
            RBTNode<T>* parent = justAdded->parent;
            RBTNode<T>* gparent = justAdded->parent->parent;
            RBTNode<T>* uncle = getUncle(justAdded);
            
            if(parent == nullptr)
            {
                justAdded->setColor(BLACK);
            }
            else if(!parent->isBlack()){
                return;
            }
            else if(!(uncle->isBlack())){
                parent->setColor(BLACK);
                uncle->setColor(BLACK);
                gparent->setColor(RED);
                addCheck(gparent);
            }
            else{
                if(justAdded == gparent->left->right){
                    rotateLeft(parent);
                    justAdded = justAdded->left;
                }
                else if(justAdded == gparent->right->left) {
                    rotateRight(parent);
                    justAdded = justAdded->right;
                }

                if(justAdded == parent->left) {
                    rotateRight(gparent);
                }
                else
                    rotateLeft(gparent);

                parent->setColor(BLACK);
                gparent->setColor(RED);
            }
        }

        void redParent(RBTNode<T>* cur) {
            RBTNode<T>* parent = cur->parent;
            RBTNode<T>* sibling = parent->right;

            if(!parent->isBlack() && sibling->isBlack() &&
                    sibling->right->isBlack() &&
                    sibling->left->isBlack()) {
                sibling->setColor(RED);
                parent->setColor(BLACK);
            }
            else {
                sibling->setColor(RED);
                if(sibling->right->isBlack()) {
                    sibling->left->setColor(BLACK);
                    rotateRight(sibling);
                }
                else {
                    sibling->right->setColor(BLACK);
                    rotateLeft(sibling);
                }

                sibling = parent->right;
                sibling->setColor(parent->isBlack());
                parent->setColor(BLACK);
                sibling->right->setColor(BLACK);
                rotateLeft(parent);
            }
        }

        void allBlack(RBTNode<T>* cur) {
            RBTNode<T>* parent = cur->parent;
            RBTNode<T>* sibling = parent->right;

            if(parent->isBlack() && sibling->isBlack() && 
                    sibling->left->isBlack() && 
                    sibling->right->isBlack()) {
                sibling->setColor(RED);
                redSib(cur);
            }
            else {
                redParent(cur);
            }
        }

        void redSib(RBTNode<T>* cur) {
            RBTNode<T>* parent = cur->parent;
            RBTNode<T>* sibling = parent->right;

            if(!(sibling->isBlack())) {
                parent->setColor(RED);
                sibling->setColor(BLACK);
                if(cur == parent->left)
                    rotateLeft(parent);
                else
                    rotateRight(parent);
            }
            allBlack(cur);
        }

        void removeCheck(RBTNode<T>* cur)
        {
            if(cur->isBlack()) {
                if(cur->parent == nullptr) {
                    cur->left->right = cur->right;
                    cur->left->parent = nullptr;
                    cur->right->parent = cur->left;
                    return;
                } 

                redSib(cur);   
            }
            else
                cur = nullptr;
        }
        
        T* removeLeftMostChecked(RBTNode<T>* current){
            RBTNode<T>* parent = nullptr;
            while(current != nullptr) {
                parent = current;
                current = current->left;
            }

            removeCheck(parent);
            T* proc = parent->item;
            return proc;
        }

        void printTreeRec(RBTNode<T>* cur, uint32_t tab) {
            if(cur == nullptr) {
                Debug::printf("*** found null\n");
                return;
            }

            printTreeRec(cur->left, tab + 1);
            cur->printNode(tab);
            printTreeRec(cur->right, tab + 1);
        }

public:
        RBT(){} //for nullptr root
        RBT(RBTNode<T>* root): root(root) {size++;}

        void add(T* item){
                recursiveAdd(root, nullptr, item);
                size++;
        }
     
        T* removeLeftMost(){
             T* toRemove = removeLeftMostChecked(root);
             size--;
             return toRemove;
        }

        uint32_t getSize() {
            return size;
        }

        void printTree() {
            Debug::printf("*** printing tree\n");
            printTreeRec(root, 0);
        }
};