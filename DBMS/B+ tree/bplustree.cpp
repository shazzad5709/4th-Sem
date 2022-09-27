#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

int degree=3;
int totalDataSize;
int leaf=0;
int depth=0;

struct word{
     string key;
     string meaning;
};

struct node{
     bool leaf;
     int numberOfData;
     vector <word> value;
     node **child;
     node *parent;
     node *sibling;
     node *temp;
};
node *root,*tempNode;
node* createNode(){

   node *newNode= new node;
   newNode->leaf=true;
   newNode->parent=NULL;
   newNode->sibling=NULL;
   newNode->temp=NULL;
   newNode->child= new node*[degree];
   int numberOfData=0;
   for(int i=0;i<degree;i++){
     newNode->child[i]=NULL;
   }
   
   return newNode;
}

void insert(node *currentNode,word Word);

bool compare(word x, word y)
{
    return x.key < y.key; 
}

void search(string se,node *node)
{
    int index = 0;
    for(int i = 0; i < node->value.size(); i++)
    {
       // cout<<  node->value[i].key << " "<<se<<" "<<node->value[i].key.compare(se)<<endl; 
        if(node->value[i].key.compare(se)==0 && node->leaf)
        {
                   // cout<<"checking"<<endl; 
            cout << "Word found" << endl;
            cout << se << "  means=  " << node->value[i].meaning << endl;
            //found = true;
        }
    }
    if(node->child[0] != NULL)
    {
        search(se,node->child[0]);
    }
    
    if(node->child[1] != NULL)
    {
        search(se,node->child[1]);
    }
    
   if(node->child[2] != NULL)
    {
        search(se,node->child[2]);
    }
   // cout<<"end"<<endl;
}


void split(node *currentNode){

     //non leaf with parent
     if(currentNode->temp!=NULL && currentNode->parent!=NULL){
        int midpos=degree/2;
        word mid=currentNode->value[midpos];
        
        node *c2= createNode();
        for(int i=midpos+1;i<degree;i++){
           c2->value.push_back(currentNode->value[i]);
        }
        c2->leaf=false;
        int fill=0;
        for(int j=0,i=midpos+1;j<degree && i<degree;i++,j++){
           c2->child[j] = currentNode->child[i];
           fill++;
            currentNode->child[i]->parent = c2;
        }
        c2->child[fill] = currentNode->temp;
        currentNode->temp->parent = c2;
        
         vector<word> newValue;
         for(int i=0;i<midpos;i++){
           newValue.push_back(currentNode->value[i]);
         }
        currentNode->value = newValue;
        for(int i=midpos+1;i<degree;i++){
           currentNode->child[i] = NULL;
        }
        currentNode->temp = NULL;
        
        if(currentNode->parent->value.size() < degree-1)
        {
            //test
            currentNode->parent->value.push_back(mid);
                        int fillup=currentNode->parent->value.size();
            currentNode->parent->child[fillup] = c2;
            c2->parent = currentNode->parent;
        }
        
        else if(currentNode->parent->value.size() == degree-1)
        {
            currentNode->parent->value.push_back(mid);
            currentNode->parent->temp = c2;
            c2->parent = currentNode->parent;
            split(currentNode->parent);
        }  
     }
     //no leaf without parent
     else if(currentNode->temp!= NULL && currentNode->parent==NULL){
        int midpos=degree/2;
        word mid=currentNode->value[midpos];
        
        node *par=createNode();
        par->value.push_back(mid);
        
         node *c2 = createNode();
         for(int i=midpos+1;i<degree;i++){
           c2->value.push_back(currentNode->value[i]);
         }

        c2->leaf = false;
        int c2fill=0;
        for(int j=0,i=midpos+1;j<degree && i<degree;i++,j++){
           c2->child[j] = currentNode->child[i];
           c2fill++;
            currentNode->child[i]->parent = c2;
        }
        c2->child[c2fill] = currentNode->temp;
        currentNode->temp->parent = c2;
        
        vector<word> newValue;
        for(int i=0;i<midpos;i++){
          newValue.push_back(currentNode->value[0]);        
        }

        currentNode->value = newValue;
        
        for(int i=midpos+1;i<degree;i++){
           currentNode->child[i] = NULL;
        }
        currentNode->temp = NULL;
        
         par->child[0] = currentNode;
        currentNode->parent = par;
        par->child[1] = c2;
        c2->parent = par;
        par->leaf = false;
        root = par;
        
     
     }
     //to split only leaf without parent
     else if(currentNode->parent==NULL && currentNode->leaf){
        int midpos=degree/2;
        word mid=currentNode->value[midpos];
        
        node *c1=createNode();
        for(int i=0;i<midpos;i++){
          insert(c1,currentNode->value[i]);
        }
        c1->parent=currentNode;
        currentNode->child[0]=c1;
        
        node*c2=createNode();
        for(int i=midpos;i<degree;i++){
          insert(c2,currentNode->value[i]);
        }
        c2->parent=currentNode;
        currentNode->child[1]=c2;
        
        c1->sibling = c2;
        
        vector<word> newValue;
        currentNode->value = newValue;
        currentNode->value.push_back(mid);
        currentNode->leaf = false;
     }
     //to split leaf with parent
     else if(currentNode->parent!=NULL && currentNode->leaf){
        int midpos=degree/2;
        word mid=currentNode->value[midpos];
        
        vector<word> newValue;
        for(int i=0;i<midpos;i++){
            newValue.push_back(currentNode->value[i]);
        }
        
        node *c3=createNode();
        for(int i=midpos;i<degree;i++){
           c3->value.push_back(currentNode->value[i]);
        }
        
        currentNode->value = newValue;
        currentNode->sibling = c3;
        
        if(currentNode->parent->value.size() < degree-1 )
        {
          //  cout<<"ok we are coming in here"<<endl;
            currentNode->parent->value.push_back(mid);
            int fillup=currentNode->parent->value.size();
            currentNode->parent->child[fillup] = c3;
            c3->parent = currentNode->parent;
        }
        
        else if(currentNode->parent->value.size() == degree-1)
        {
            currentNode->parent->value.push_back(mid);
            currentNode->parent->temp = c3;
            c3->parent = currentNode->parent;
           // cout<<"else if is also being chk"<<endl;
            split(currentNode->parent);
        }     
     
     }
}

void insert(node *currentNode,word Word){
        //cout<<"eating here"<<endl;
        //cout<<"we are here "<<endl<<currentNode->leaf<<endl;
   if(currentNode->leaf==true){
     currentNode->value.push_back(Word);
     sort(currentNode->value.begin(),currentNode->value.end(),compare);
     if(currentNode->value.size()==degree){
     // cout<<"child is being split $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        split(currentNode);
     }
   }
   else{
   //cout<<"it is entering the else section &&&&&&&&&&&&&&&&&&&&&&&"<<endl;
    /* for(int i=0;i<currentNode->value.size() && i<degree-1;i++){
        if(Word.key<currentNode->value[i].key){
         insert(currentNode->child[0],Word);
         break;
        }
        else if(Word.key > currentNode->value[i].key && (Word.key<currentNode->value[i+1].key || currentNode->value[i+1].key==" ") ){
         insert(currentNode->child[i+1],Word);
         break;
        }
        else if(Word.key==currentNode->value[i].key){
         insert(currentNode->child[i+1],Word);
         break;
        }
        else{
         insert(currentNode->child[degree-1],Word);
         break;
        }}*/
        
         if(Word.key < currentNode->value[0].key)
            insert(currentNode->child[0], Word);
       // test
        else {
            if(currentNode->value.size() == 1)
            {
                //test
           
                insert(currentNode->child[1], Word);
            }
            
            else{
                //test
                if(Word.key < currentNode->value[1].key)
                {
                    insert(currentNode->child[1],Word);
                }
                else
                {
                    insert(currentNode->child[2],Word);
                }
            }
        }    
        
        
     }
       
}



void input(){

   
}

void traverse(node *node)
{
    cout << endl;
    if(node->leaf){
      cout << "Leaf" << " $$$$$$$$$$$$$$$$$$$$$$$   "<< leaf++<< endl;
    } 
    
    for(int i = 0; i < node->value.size(); i++)
        cout << node->value[i].key << " ===== " << node->value[i].meaning << "   "<<endl;;
    cout << endl;
    for(int i=0;i<degree;i++){
       if(node->child[i] != NULL){
         traverse(node->child[i]);
       }
    }
    
}
void deepth(node* node){
    while(1){
    if(node->leaf==false){
            depth++;
            node=node->child[0];
    }
    else{
      break;
    }

    }
}



int main(){

   //cout<<"Enter degree of your b+ tree"<<endl;
   //cin>>degree;
   root = createNode();
   // input();
    
    /*ifstream iFile;
    string key,meaning;;
    iFile.open("input.txt");

        iFile >> totalDataSize;
        cout<<totalDataSize<<endl;
        string faltu;
        getline(iFile, faltu);
        //iFile>>faltu;
        cout<<faltu<<endl;
        for(int i = 0; i < totalDataSize; i++){
        string s1, s2;
        getline(iFile, s1);
        iFile>>s1;
        getline(iFile, s2); 
        cout<<s1<<" "<<s2<<endl;  
        word temp;
        temp.key = s1;
        temp.meaning = s2;
        //cout<<i<<endl;
        insert(root,temp);
        
            
    }*/
       ifstream inputFile;
    string engWord,bangWord;
    inputFile.open("input.txt");


    while(inputFile >> engWord)
    {
        getline(inputFile,bangWord);
           word temp;
        temp.key = engWord;
        temp.meaning = bangWord;
        insert(root,temp);
    }
    inputFile.close();
    //iFile.close();
    cout<<"dictionary is created"<<endl;

    traverse(root);
    deepth(root);
    cout<<depth+1<<endl;
    while(1){
      string se;
      cin>>se;
      search(se,root);
      cout<<"hmmm"<<endl;
      if(se=="%"){
          break;
      }
    }
    return 0;
}
