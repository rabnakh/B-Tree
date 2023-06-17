#ifndef BTree_h
#define BTree_h
#include <iostream>
#include <cmath>
class Root;
struct Key{
    int key = 0;
    Key* next = nullptr;
};
struct Child{
    Root* childPtr = nullptr;
    Child* next = nullptr;
};
class Root{
    public:
    Key* KeyHeadLL;
    Child* ChildHeadLL;
    int countKeys;
    int countChildren;
    bool leaf;
    Root();
    Root(int key);
};
Root::Root(){
    KeyHeadLL = nullptr;
    ChildHeadLL = nullptr;
    countKeys = 0;
    countChildren = 0;
    leaf = true;
}
Root::Root(int key_){
    KeyHeadLL = new Key;
    ChildHeadLL = nullptr;
    KeyHeadLL->key = key_;
    countKeys = 1;
    countChildren = 0;
    leaf = true;
}
class BTree{
    public:
    Root* BTreeHeadRoot;    
    int maximumKeys;
    int minimumKeys;
    int order;
    public:
    BTree(int order_);
    Root* newRoot();
    void insert(int newkey);
    void insertWrapped(int newKey, Root*&root, Root*&rootForSplitting);
    void remove();
    void traverse();
    void printKeyLL(Key*key){
        Key* traverser = key;
        while(traverser){
            std::cout << traverser->key << ' ';
            traverser = traverser->next;
        }
    }
    void printChildLL(Child*child){
        Child*traverser = child;
        while(traverser){
            std::cout << "Child: " << traverser->childPtr << std::endl;
            std::cout << "Child's " << traverser->childPtr << " keys: ";
            printKeyLL(traverser->childPtr->KeyHeadLL);
            std::cout << std::endl;
            traverser = traverser->next;
        }
    }
    void printDegree(int degree,ofstream &outPutWriter);
    void printDegreeWrapped(int degree,int& degreeCounter,Root*&degreeTraverser,ofstream &outputWriter);
    void printInorder(ofstream &outputWriter);
    void printInorderWrapped(Root*&rootTraverser,ofstream &outputWriter);
    int Height();
    void HeightWrapped(int &heightCounter, Root*&heightTraverser);
};
#endif
BTree::BTree(int order_){
    BTreeHeadRoot = nullptr;
    order = order_;
    maximumKeys = order - 1;
    minimumKeys = 2; //This could be wrong. It may not be 2 but some calculation.
}
void BTree::insert(int newKey){
    Root* defaultRoot = nullptr;
    //std::cout << "Attempting to insert: " << newKey << std::endl;
    insertWrapped(newKey,BTreeHeadRoot, defaultRoot);
}
void BTree::insertWrapped(int newKey, Root*&root, Root*&rootForSplitting){
    /*The part will create a new node for the root if it is empty*/
    if(root == nullptr){
        root = new Root(newKey);
        //std::cout << "Address of the Top Tree Root: " << root << std::endl;
        //std::cout << "Key List of Root getting Key: ";
        //printKeyLL(root->KeyHeadLL);
        //std::cout << "\n\n";
        return;
    }
    /*This part will execute if the node is not a leaf*/
    if(root->leaf == false){
        Key* keyTraverser = root->KeyHeadLL;
        Child* childTraverser = root->ChildHeadLL;

        //std::cout << "Address of the current Non-Leaf Root: " << root << std::endl;
        /*This code will print all the child's Root ptr's*/
        //std::cout << "Keys of the current Root: ";
        //printKeyLL(root->KeyHeadLL);
        //std::cout << std::endl;
        //std::cout << "Children of the current Root with their Keys:\n";
        //printChildLL(root->ChildHeadLL);
        Child* childTraverserToPrint = root->ChildHeadLL;
        //std::cout << std::endl;


        /*This loop will loop for duplicate values and find find the proper node at which to contine the path*/
        //std::cout << "Looking for Duplicates in the current Root...\n";
        while(keyTraverser){
            //std::cout << keyTraverser->key << ' ';
            if(keyTraverser->key == newKey){
                //std::cout << "Duplicate Found\n";
                return;
            }
            if(newKey < keyTraverser->key){
                break;
            }
            keyTraverser = keyTraverser->next;
            childTraverser = childTraverser->next;
        }
        //std::cout << std::endl;
        insertWrapped(newKey, childTraverser->childPtr, root);
    }
    /*This code will execute if the node is a leaf*/
    else if(root->leaf == true){
        //std::cout << "Looking for Duplicates in the current...\n";
        Key*duplicateFinder = root->KeyHeadLL;
        while(duplicateFinder){
            if(duplicateFinder->key == newKey){
                //std::cout << "Duplicate Found\n";
                return;
            }
            duplicateFinder = duplicateFinder->next;
        }
        /*This code will traverse to find the correct position to insert the new key*/
        Key*keyTracer = nullptr;
        Key*keyTraverser = root->KeyHeadLL;
        while(keyTraverser != nullptr && keyTraverser->key < newKey){
            keyTracer = keyTraverser;
            keyTraverser = keyTraverser->next;
        }
        /*This code will allocate a new key that will hold the data of the new key*/
        Key*newKeyNode = new Key;
        newKeyNode->key = newKey;
        newKeyNode->next = nullptr;
        /*This code will insert the allocate key in the correct positiion depending on what the tracer and traverser ptr's are pointing*/
        if(keyTracer == nullptr){
            newKeyNode->next = root->KeyHeadLL;
            root->KeyHeadLL = newKeyNode;
        }
        else{
            newKeyNode->next = keyTraverser;
            keyTracer->next = newKeyNode;
        }
        root->countKeys++;
        /*This code prints the values of the Keys of the node after the key was inserted*/
        //std::cout << "Address of the Root getting Key: " << root << std::endl;
        //std::cout << "Key List of Root getting Key: ";
        keyTraverser = root->KeyHeadLL;
        //printKeyLL(keyTraverser);
        //std::cout << "\n\n";
    }
    /*This code will execute if the number of keys in the root is greater than the maximum number of keys allowed in a root*/
    if(maximumKeys < root->countKeys){
        /*This code will create a new Node to hold the keys right of the middle key and any child pointers right of it as well*/
        Root *splitRightRoot = new Root;
        int middleKey = floor(maximumKeys / 2); /*HERE I CHANGED ROOT->COUNTKEYS TO MAXKEYS*/
        /*This code will traverser to the key after the middle key and point the keyHead of the new Root to it.
        It will also point the key before the middle key to null.*/
        Key* keyTraverser = root->KeyHeadLL;
        int holdMiddleKey = 0;
        Key* tempKey = nullptr;
        for(int i = 0; i < middleKey + 1;i++){
            if(i == middleKey){
                holdMiddleKey = keyTraverser->key;
            }
            if(i == middleKey - 1){
                tempKey = keyTraverser;
                keyTraverser = keyTraverser->next;
                tempKey->next = nullptr;
            }
            else{
                keyTraverser = keyTraverser->next;
            }
        }
        splitRightRoot->KeyHeadLL = keyTraverser;
        /*This code will count the number of keys in the split right root*/
        keyTraverser = splitRightRoot->KeyHeadLL;
        while(keyTraverser){
            splitRightRoot->countKeys++;
            keyTraverser = keyTraverser->next;
        }
        /*This code will calculate the number of keys in the split left root*/
        root->countKeys = root->countKeys - splitRightRoot->countKeys - 1;
        /*This code will print the keys of the Left Splint Child*/
        keyTraverser = root->KeyHeadLL;
        /*This code will print the keys of the newly created Split Right Child*/
        keyTraverser = splitRightRoot->KeyHeadLL;
        /*This code will execute if there are more child pointers after the middle key*/
        int countNumberOfChildren = 0;
        Child* traverserToCountChildren = root->ChildHeadLL;
        while(traverserToCountChildren){
            countNumberOfChildren++;
            traverserToCountChildren = traverserToCountChildren->next;
        }
        traverserToCountChildren = nullptr;
        if(countNumberOfChildren > middleKey + 1){
            /*This code will traverse to find the position of the child pointer after the middle key.
            It will then point the childHead to that position. It will also point the child before the middle key to null.*/
            Child* childTraverser = root->ChildHeadLL;
            for(int j = 0; j < middleKey + 1;j++){
                if(j == middleKey){
                    Child* tempChild = childTraverser;
                    childTraverser = childTraverser->next;
                    tempChild->next = nullptr;
                }
                else childTraverser = childTraverser->next;
            }
            splitRightRoot->ChildHeadLL = childTraverser;
            if(root->ChildHeadLL != nullptr)
                root->leaf = false;
            if(splitRightRoot->ChildHeadLL != nullptr)
                splitRightRoot->leaf = false;           
        }
        /*This code will execute if the root parameter is the root of the entire tree*/
        if(root == BTreeHeadRoot){
             /*This code will allocate a new root that will hold the middle key of the split root*/
            Root* newTreeTopParent = new Root(holdMiddleKey);
            Child* childTraverser = newTreeTopParent->ChildHeadLL;
            /*This code will point the pointer before the key to the old root that now has the keys before the middle key.
            It will also point the pointer after the key to the allocated split right root that holds the keys after the middle key.
            It will also point the B Tree pointer to the new top root that was allocated to hold the middle key of the split root.
            */
            newTreeTopParent->ChildHeadLL = new Child;
            newTreeTopParent->ChildHeadLL->childPtr = root;
            newTreeTopParent->ChildHeadLL->next = new Child;
            newTreeTopParent->ChildHeadLL->next->childPtr = splitRightRoot;
            root = newTreeTopParent;
            root->leaf = false;
            childTraverser = newTreeTopParent->ChildHeadLL;
            if(childTraverser->childPtr->ChildHeadLL != nullptr)
                childTraverser->childPtr->leaf = false;
            if(childTraverser->next->childPtr->ChildHeadLL != nullptr)
                childTraverser->next->childPtr->leaf = false;
        }
        else{
            /*This code will traverse to find the correct position to insert the new key*/
            Key*keyTracer = nullptr;
            Key*keyTraverser = rootForSplitting->KeyHeadLL;
            while(keyTraverser != nullptr && keyTraverser->key < holdMiddleKey){
                keyTracer = keyTraverser;
                keyTraverser = keyTraverser->next;
            }
            /*This code will allocate a new key that will hold the data of the new key*/
            Key*newKeyNode = new Key;
            newKeyNode->key = holdMiddleKey;
            newKeyNode->next = nullptr;
            /*This code will insert the allocate key in the correct position depending on what the tracer and traverser ptr's are pointing*/
            if(keyTracer == nullptr){
                newKeyNode->next = rootForSplitting->KeyHeadLL;
                rootForSplitting->KeyHeadLL = newKeyNode;
            }
            else{
                newKeyNode->next = keyTraverser;
                keyTracer->next = newKeyNode;
            }
            rootForSplitting->countKeys++;

            /*Here code is needed to adjust the pointers of the parent node to point to any newly formed node or other old nodes*/
            Child* childTraver = rootForSplitting->ChildHeadLL;
            while(childTraver->childPtr != root){
                childTraver = childTraver->next;
            }
            Child* newChild = new Child;
            newChild->childPtr = splitRightRoot;
            newChild->next = childTraver->next;
            childTraver->next = newChild;
            rootForSplitting->leaf = false;
        }
    }
}
int BTree::Height(){
    int heightCounter = 0;
    HeightWrapped(heightCounter, BTreeHeadRoot);
    return heightCounter;
}
void BTree::HeightWrapped(int& heightCounter,Root*&heightTraverser){
    if(heightTraverser->ChildHeadLL == nullptr){
        heightCounter++;
        return;
    }
    else{
        heightCounter++;
        HeightWrapped(heightCounter, heightTraverser->ChildHeadLL->childPtr);
    }
}
void BTree::printDegree(int degree,ofstream &outputWriter){
    int degreeCounter = 1;
    printDegreeWrapped(degree,degreeCounter,BTreeHeadRoot,outputWriter);
}
void BTree::printDegreeWrapped(int degree,int&degreeCounter, Root*&degreeTraverser,ofstream &outputWriter){
    if(degreeCounter == degree){
        Key* keyTraversal = degreeTraverser->KeyHeadLL;
        while(keyTraversal != nullptr){
            outputWriter << keyTraversal->key << ' ';
            keyTraversal = keyTraversal->next;
        }
    }
    else{
        Child* childTraverser = degreeTraverser->ChildHeadLL;
        while(childTraverser){
            degreeCounter++;
            printDegreeWrapped(degree,degreeCounter,childTraverser->childPtr,outputWriter);
            degreeCounter--;
            childTraverser = childTraverser->next;
        }
    }
}
void BTree::printInorder(ofstream &outputWriter){
    printInorderWrapped(BTreeHeadRoot,outputWriter);
}
void BTree::printInorderWrapped(Root*&rootTraverser,ofstream &outputWriter){
    if(rootTraverser->leaf == true){
        Key*keyTraverserLeaf = rootTraverser->KeyHeadLL;
        while(keyTraverserLeaf != nullptr){
            outputWriter << keyTraverserLeaf->key << ' ';
            keyTraverserLeaf = keyTraverserLeaf->next;
        }
    }
    else{
        Child*childTraverserNonLeaf = rootTraverser->ChildHeadLL;
        Key*keyTraverserNonLeaf = rootTraverser->KeyHeadLL;
        while(childTraverserNonLeaf != nullptr){
            printInorderWrapped(childTraverserNonLeaf->childPtr,outputWriter);
            if(keyTraverserNonLeaf != nullptr)
                outputWriter << keyTraverserNonLeaf->key << ' '; 
            if(keyTraverserNonLeaf != nullptr)
                keyTraverserNonLeaf = keyTraverserNonLeaf->next;
            childTraverserNonLeaf = childTraverserNonLeaf->next;
        }
    }
}
