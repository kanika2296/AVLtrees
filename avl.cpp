
#include<bits/stdc++.h> 
using namespace std; 

struct Avl
{
    public:
    int  key;
    Avl *left;
    Avl *right;
    int height;
};
// create new node 
struct Avl* newNode(int key)
{
    Avl* a = new Avl();
    a->key = key;
    a->left = NULL;
    a->right = NULL;
    a->height=1;    
    return a;
}
// return height
int nodeHeight(struct Avl* a)
{
    return (a == NULL)?0:a->height;
}
// maximum of two key values
int maxkey(int n,int m)
{
    return (n>m)? n:m;
}
// check balance at node
int checkBalance(Avl* node)
{
    return (node == NULL)?0:nodeHeight(node->left)-nodeHeight(node->right);
}
// rotations
struct Avl* leftRotateTree(struct Avl* a)
{
    Avl* cur_right = a->right;
    Avl* future_right = cur_right->left;
    // rotate
    cur_right->left =a;
    a->right = future_right;
    a->height=maxkey(nodeHeight(a->left),nodeHeight(a->right))+1;
    cur_right->height = maxkey(nodeHeight(cur_right->left),nodeHeight(cur_right->right))+1;
    return cur_right;
}
struct Avl *rightRotateTree(struct Avl *a)
{
    Avl* cur_left = a->left;
    Avl* future_left = cur_left->right;
    // rotate
    cur_left->right = a;
    a->left = future_left;

    a->height=maxkey(nodeHeight(a->left),nodeHeight(a->right))+1;
    cur_left->height = maxkey(nodeHeight(cur_left->left),nodeHeight(cur_left->right))+1;
    return cur_left;
}
struct Avl *rightLeftRotateTree(struct Avl* a)
{
    a->right = rightRotateTree(a->right);  
    return leftRotateTree(a);  
}
struct Avl* leftRightRotateTree(struct Avl* a)
{
    a->left = leftRotateTree(a->left);  
    return rightRotateTree(a);  
}
struct Avl* insert(struct Avl* root, int key)
{
    if(root == NULL)
        return newNode(key);
    if(key < root->key)
        root->left = insert(root->left,key);
    else if(key > root->key)
        root->right = insert(root->right,key);
    else 
        return root;
    // set new height
    int maxH = maxkey(nodeHeight(root->left),nodeHeight(root->right));
    root->height = 1+maxH;

    int balance = checkBalance(root);
 
    if (balance > 1 && key < root->left->key)  // left
        return rightRotateTree(root);   
    if (balance < -1 && key > root->right->key)  //right
        return leftRotateTree(root);    
    if (balance > 1 && key > root->left->key)  // left right
        return leftRightRotateTree(root);   
    if (balance < -1 && key < root->right->key)   // right left
        return rightLeftRotateTree(root); 
  
    return root;
}
struct Avl* deleteN(struct Avl* root, int key) 
{
    if(root == NULL)
        return root;
    if (key > root->key)
        root->right = deleteN(root->right,key);
    else if(key < root->key)
        root->left = deleteN(root->left,key);  
    else
    {
        if(root->left == NULL)
        {
            struct Avl* new_node = root->left;
            free(root);
            return new_node;
        }
        else if(root->right == NULL)
        {
            struct Avl* new_node = root->right;
            free(root);
            return new_node;
        }
        
        struct Avl* current = root->right; 
         while (current->left != NULL) 
            current = current->left;  
        //struct Avl* temp = current;

        root->key = current->key;
        root->right = deleteN(root->right,current->key);
        
    }
    if(root == NULL)
        return 0;
    int maxH = maxkey(nodeHeight(root->left),nodeHeight(root->right));
    root->height = 1+maxH;

    int balance = checkBalance(root);


    // rotation conditions
    if (balance > 1 && checkBalance(root->left) >= 0)  // left
        return rightRotateTree(root);   
    if (balance < -1 && checkBalance(root->right) <= 0)  //right
        return leftRotateTree(root);    
    if (balance > 1 &&  checkBalance(root->left) < 0)  // left right
        return leftRightRotateTree(root);   
    if (balance < -1 &&  checkBalance(root->right) > 0)   // right left
        return rightLeftRotateTree(root); 
  
    return root;

}
struct Avl* updateN(struct Avl* root,int oldKey,int newKey)
{
    root = deleteN(root,oldKey);
    root = insert(root,newKey);
    return root;
}
bool searchN(struct Avl* node,int key)
{
    if(node == NULL)
        return false;
    if( node->key == key)
        return true;
    else if(key > node->key)
        searchN(node->right,key);
    else
        searchN(node->left,key);

}
// traversals
void preOrder(struct Avl *root)  
{  
    if(root != NULL)  
    {  
        cout << root->key << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  
void inOrder(struct Avl *root)  
{  
    if(root != NULL)  
    {  
        inOrder(root->left);
        cout << root->key << " ";    
        inOrder(root->right);  
    }  
}  
void postOrder(struct Avl *root)  
{  
    if(root != NULL)  
    {   
        postOrder(root->left);  
        postOrder(root->right); 
        cout << root->key << " ";  
    }  
}
int main()
{
    struct Avl *head = NULL;  
    int n,val,val_new;
    while(1)
    {
    cout<<"\nSELECT OPTION :\n 1. INSERT\n 2. SEARCH \n 3. UPDATE \n 4. DELETE \n 5. DISPLAY INORDER \n 6. DISPLAY POREORDER \n 7. DISPLAY POSTORDER\n ";
    cin>>n;
        switch(n)
        {
            case 1: cout <<"Enter item value \n";
                    cin >> val;
                    head = insert(head,val);
                    break;
            case 2: cout <<"Enter item value \n";
                    cin >> val;
                    //cout << searchN(head,val) ;
                    if(searchN(head,val))
                    {
                        cout <<"FOUND\n";
                    }
                    else
                    {
                        cout <<"NOT FOUND\n";
                    }
                    break;
            case 3: cout <<"Enter item value \n";
                    cin >> val;
                    cout<<" Enter the updated value \n";
                    cin >> val_new;
                    head = updateN(head,val,val_new);
                    break;
            case 4: cout <<"Enter item value \n";
                    cin >> val;
                    head = deleteN(head,val);
                    break;
            case 5: inOrder(head);
                    break;
            case 6: preOrder(head);
                    break;
            case 7: postOrder(head);
                    break;
            default: cout << "Select a valid option \n";
        }
    }
    return 0;
}
