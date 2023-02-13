#include <iostream>
#include <set>
#include <ctime>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cmath>
// SORT
int partition(int A[],int left,int right){
    int pivot = A[right];

    int i = (left - 1);
    for (int j = left; j < right; j++) {
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
        }
    }

    std::swap(A[i + 1], A[right]);

    return (i + 1);
}

void quickSort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}



class TreeA{
    struct node{
        int key;
        node *left;
        node *right;
        ~node(){
            delete left;
            delete right;
        }
        node(int k){
            key =k;
            left = right = nullptr;
        }
    };
    node* root;
public:
    TreeA(){
        root = nullptr;
    }
    ~TreeA(){
        delete root;
    }
    void insert(int key){
        srand(time(NULL));
        if(root==nullptr){
            root =new node(key);
            return;
        }
        node *ptr=root;
        while(true)
        {
            int r=rand()%2;
            if(r==1)
            {
                if (ptr->right == nullptr)
                {
                    ptr->right = new node(key);
                    break;
                }
                else
                {
                    ptr=ptr->right;
                }
            }
            else if(r==0)
            {
                if (ptr->left == nullptr)
                {
                    ptr->left = new node(key);
                    break;
                }
                else
                {
                    ptr=ptr->left;
                }

            }
        }
    }
    bool search_node(node* n, int k)
    {
        if (n == nullptr)
            return false;

        if (n->key == k)
            return true;


        if(search_node(n->left, k))
            return true;

        if(search_node(n->right, k))
            return true;

        return false;
    }

    bool find(int k){
        node *ptr = root;
        if(search_node(ptr,k))
            return true;

        return false;
    }


    void print_helper(std::ostream &os, struct node *ptr){
        if(ptr==nullptr){
            return;
        }
        os << "(";
        print_helper(os,ptr->left);
        os<<";" << ptr->key <<";";
        print_helper(os,ptr->right);
        os << ")";
    }

    friend std::ostream &operator<<(std::ostream &os, TreeA &T){
        T.print_helper(os,T.root);
        return os;
    }


};

class TreeB {
    struct node {
        int key;
        node *left;
        node *right;

        ~node() {
            delete left;
            delete right;
        }

        node(int k) {
            key = k;
            left = right = nullptr;
        }
    };

    node *root;
public:
    TreeB() {
        root = nullptr;
    }

    ~TreeB() {
        delete root;
    }
    node* helper(std::vector<int>& nums, int start, int end){
        if(start > end){
            return nullptr;
        }
        int mid = (start + end) / 2;
        node* ptr= new node(nums[mid]);
        ptr->left = helper(nums, start, mid-1);
        ptr->right = helper(nums, mid+1 , end);
        return ptr;
    }

    node* insert(std::vector<int>& nums) {
        root = helper(nums, 0, nums.size()-1);
        return root;
    }
    bool find(int k){
        struct node *ptr = root;
        while(true){
            if(k<ptr->key){
                if(ptr->left){
                    ptr=ptr->left;
                }
                else{
                    return false;
                }
            }
            else if(k>ptr->key){
                if(ptr->right){
                    ptr=ptr->right;
                }
                else{
                    return false;
                }
            }
            else{ //k==ptr->key
                return true;
            }
        }
    }


    void print_helper(std::ostream &os, struct node *ptr){
        if(ptr==nullptr){
            return;
        }
        os << "(";
        print_helper(os,ptr->left);
        os<<";" << ptr->key <<";";
        print_helper(os,ptr->right);
        os << ")";
    }

    friend std::ostream &operator<<(std::ostream &os, TreeB &T){
        T.print_helper(os,T.root);
        return os;
    }

};
class TreeAVL {
    struct node {
        int key;
        node *left;
        node *right;
        int height;

        ~node() {
            delete left;
            delete right;
        }

        node(int k) {
            key = k;
            left = right = nullptr;
            height = 1;
        }
    };

    node *root;
public:
    TreeAVL() {
        root = nullptr;
    }

    ~TreeAVL() {
        delete root;
    }
    int height(node *n){
        if(n==nullptr)
            return 0;
        return n->height;
    }


    node *rightRotation(node *n){
        node *temp = n->left;
        n->left = temp->right;
        temp->right = n;
        n->height = 1+std::max(height(n->left), height(n->right));
        temp->height = 1+std::max(height(temp->left), height(temp->right));
        return temp;
    }

    node *leftRotation(node *n){
        node *temp = n->right;
        n->right = temp->left;
        temp->left = n;
        n->height = 1+std::max(height(n->left), height(n->right));
        temp->height = 1+std::max(height(temp->left), height(temp->right));
        return temp;
    }

    node *insert_helper(node *n, int k){
        if(n==nullptr){
            node * temp = new node(k);
            return temp;
        }
        if(k < n->key) n->left = insert_helper(n->left, k);
        else if(k > n->key) n->right = insert_helper(n->right, k);
        n->height = 1 + std::max(height(n->left), height(n->right));
        int balance = height(n->left) - height(n->right);
        if(balance>1){
            if(k < n->left->key){
                return rightRotation(n);
            }else{
                n->left = leftRotation(n->left);
                return rightRotation(n);
            }
        }else if(balance<-1){
            if(k > n->right->key){
                return leftRotation(n);
            }else{
                n->right = rightRotation(n->right);
                return leftRotation(n);
            }
        }
        return n;
    }
    void insert(int key){
        root=insert_helper(root, key);
    }

    bool find_helper(node* n, int k)
    {
        if (n == nullptr)
            return false;

        if (n->key == k)
            return true;

        if(n->key > k) {
            if (find_helper(n->left, k))
                return true;
        }
        else if(n->key < k) {
            if (find_helper(n->right, k))
                return true;
        }

        return false;
    }

    bool find(int k){
        node *ptr = root;
        if(find_helper(ptr,k))
            return true;

        return false;
    }

    void print_helper(std::ostream &os, struct node *ptr){
        if(ptr==nullptr){
            return;
        }
        os << "(";
        print_helper(os,ptr->left);
        os<<";" << ptr->key <<";";
        print_helper(os,ptr->right);
        os << ")";
    }

    friend std::ostream &operator<<(std::ostream &os, TreeAVL &T){
        T.print_helper(os,T.root);
        return os;
    }

};

void count_insert(int size,std::vector<double>&a_time,std::vector<double>&b_time,std::vector<double>&s_time,std::vector<double>&avl_time){
    LARGE_INTEGER t1, t2, f, diff;
    srand(time(NULL));
    TreeA tree_a;
    TreeB tree_b;
    std::set<int>tree_standard;
    double time;
    TreeAVL tree_avl;

    int A[size];
    int B[size];

    for(int i=0;i<size;i++)
        A[i] = rand();
    for(int i=0;i<size;i++)
        B[i] = A[i];

    quickSort(B,0,size-1);
    std::vector<int>B_v;
    for(int i=0;i<size;i++)
        B_v.push_back(B[i]);


    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<size;i++)
        tree_a.insert(A[i]);
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;

    a_time.push_back(time);

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    tree_b.insert(B_v);
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;

    b_time.push_back(time);

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<size;i++)
        tree_standard.insert(A[i]);
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;

    s_time.push_back(time);

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<size;i++)
        tree_avl.insert(A[i]);
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;
    avl_time.push_back(time);
}

void count_find(int size,std::vector<double>&a_time,std::vector<double>&b_time,std::vector<double>&s_time,std::vector<double>&avl_time){
    LARGE_INTEGER t1, t2, f, diff;
    srand(time(NULL));
    TreeA tree_a;
    TreeB tree_b;
    std::set<int>tree_standard;
    TreeAVL tree_avl;
    double time;
    int count;

    int A[size];
    int B[size];

    for(int i=0;i<size;i++)
        A[i] = rand();
    for(int i=0;i<size;i++)
        B[i] = A[i];

    quickSort(B,0,size-1);
    std::vector<int>B_v;
    for(int i=0;i<size;i++)
        B_v.push_back(B[i]);


    for(int i=0;i<size;i++){
        tree_a.insert(A[i]);
        tree_standard.insert(A[i]);
        tree_avl.insert(A[i]);
    }
    tree_b.insert(B_v);

    count =0;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    while(count!=size){
        for(int i=0;i<size;i++){
            if(tree_a.find(A[i])){
                count++;
            }
        }
    }
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;

    a_time.push_back(time);
    count =0;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    while(count!=size){
        for(int i=0;i<size;i++){
            if(tree_b.find(A[i])){
                count++;
            }
        }
    }
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;

    b_time.push_back(time);
    count =0;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    while(count!=size){
        for(int i=0;i<size;i++){
            if(tree_standard.contains(A[i])){    //equivalent to find
                count++;
            }
        }
    }
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;

    s_time.push_back(time);

    count =0;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    while(count!=size){
        for(int i=0;i<size;i++){
            if(tree_avl.find(A[i])){
                count++;
            }
        }
    }
    QueryPerformanceCounter(&t2);
    time = (t2.QuadPart - t1.QuadPart) / (double)f.QuadPart;

    avl_time.push_back(time);
}



int main() {
    srand(time(NULL));
    LARGE_INTEGER t1, t2, f, diff;
    std::vector<double>tree_a_time_insert,tree_a_time_find;
    std::vector<double>tree_b_time_insert,tree_b_time_find;
    std::vector<double>tree_standard_time_insert,tree_standard_time_find;
    std::vector<double>tree_avl_time_insert,tree_avl_time_find;

    std::vector<int>size;

    for(int i=1;i<15;i++) {
        int n = pow(2, i) - 1;
        count_insert(n, tree_a_time_insert, tree_b_time_insert, tree_standard_time_insert,tree_avl_time_insert);
        count_find(n, tree_a_time_find, tree_b_time_find, tree_standard_time_find,tree_avl_time_find);
        size.push_back(n);
    }


    std::ofstream of("p.txt", std::ofstream::out);
    of << "size\tTreeA_Insert\tTreeB_Insert\tTreeStandard_Insert\tTreeAVl_Insert\tTreeA_Find\tTreeB_Find\tTreeStandard_Find\tTreeAVL_Find\n";
    for (int i = 0; i < size.size(); i++) {
        of << size[i]
           << '\t'
           <<std::fixed << tree_a_time_insert[i]
           << '\t'
           <<std::fixed << tree_b_time_insert[i]
           << '\t'
           <<std::fixed << tree_standard_time_insert[i]
           << '\t'
           <<std::fixed << tree_avl_time_insert[i]
           << '\t'
           <<std::fixed << tree_a_time_find[i]
           << '\t'
           <<std::fixed << tree_b_time_find[i]
           << '\t'
           <<std::fixed << tree_standard_time_find[i]
           << '\t'
           <<std::fixed << tree_avl_time_find[i]
           << '\n';
    }
    of.close();
    system("START \"\" \"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\" p.txt");

    return 0;
}
