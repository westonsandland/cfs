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
};

template <typename T>
class RBT {
        RBTNode<T>* root;
        uint32_t size;

        void recursiveAdd(RBTNode<T>* current, T* item){
                if(current == nullptr){
                  current = new RBTNode<T>(item, RED, nullptr, nullptr);
            return;
                }
                if(current->item > item){
                     recursiveAdd(current->left, item);           
                }
                else{
                     recursiveAdd(current->right, item);
                }
        }
        
        T* removeLeftMostRecursive(RBTNode<T>* current){
             if(current->left==nullptr){
                 T* leftist = current->item;
                 if(current != root){
                      RBTNode<T>* parent = current->parent;
                      if(parent!=nullptr){
                           parent->left = nullptr;
                           if(current->right!=nullptr)
                                parent->left = current->right;
                           current->parent = nullptr;
                      }
                 }
                 else{
                      root = current->right;
                      current->right->parent = nullptr;
                      current->right = nullptr;
                 }
                 delete current;
                 return leftist;
             }else
                  return removeLeftMostRecursive(current->left);
        }

        void addCheck(RBTNode<T>* justAdded)
        {
            RBTNode<T>* parent = justAdded->parent;
            RBTNode<T>* gparent = justAdded->parent->parent;
            
            if(parent == null)
            {
                 justAdded->setColor(BLACK);
            }
            else if(!parent->isBlack()){
                
            }
        }

        

        void removeCheck()
        {
        
        }
public:
        RBT(){} //for nullptr root
        RBT(RBTNode<T>* root): root(root) {size++;}

        void add(T* item){
                recursiveAdd(root, item);
                size++;HAH
        }
     
        T* removeLeftMost(){
             T* toRemove = removeLeftMostRecursive(root);
             size--;
             removeCheck(); //someone make this you thot!
             return toRemove;
        }

        void rotateLeft(RBTNode<T>* root, RBTNode<T>* cur) {
             RBTNode<T>* oldRight = cur->right
             cur->right = oldRight->left;;

             if(oldRight->left != null) {
                   cur->right->parent = cur;
             }
             
             oldRight->parent = cur->parent
             
             if(cur->parent == null)
                 root = oldRight;
             else if(cur == cur->parent->left)
                 cur->parent->left = oldRight;
             else
                 cur->parent->right = oldRight;

             oldRight->left = cur;
             cur->parent = oldRight;
        }

       void rotateRight(RBTNode<T>* root, RBTNode<T>* cur) {
             RBTNode<T>* oldLeft = cur->left
             cur->left = oldLeft->right;;

             if(oldLeft->right != null) {
                   cur->left->parent = cur;
             }
             
             oldLeft->parent = cur->parent
             
             if(cur->parent == null)
                 root = oldLeft;
             else if(cur == cur->parent->right)
                 cur->parent->right = oldLeft;
             else
                 cur->parent->left = oldLeft;

             oldRight->right = cur;
             cur->parent = oldLeft;
        }
 
};
