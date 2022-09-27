#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;
int n, mx; // number of child;

struct mystruct
{
    int currentNode;
    mystruct *parent, *next;
    string *word, *meaning;
    bool lf;
    mystruct **point;
};
mystruct *root, *firstLeaf;

mystruct *createNode()
{
    mystruct *m = new mystruct();

    m->point = new mystruct *[n + 1];
    m->word = new string[n];
    m->meaning = new string[n];

    m->currentNode = 0;
    m->parent = NULL;
    m->next = NULL;
    m->lf = true;
    return m;
}
mystruct *findLeaf(mystruct *tempRt, string word)
{

    while (tempRt->lf == false)
    {
        int i;
        for (i = 0; i < tempRt->currentNode; i++)
            if (word < tempRt->word[i])
                break;
        tempRt = tempRt->point[i];
    }
    return tempRt;
}

void insertValueAndPoint(mystruct *parent, string value, mystruct *right)
{
    int i = parent->currentNode - 1;
    for (; i >= 0; i--)
    {
        if (parent->word[i] <= value)
            break;
        else
        {
            parent->word[i + 1] = parent->word[i];
            parent->point[i + 2] = parent->point[i + 1];
        }
    }
    parent->word[i + 1] = value;
    parent->point[i + 2] = right;
    parent->currentNode++;
}

void insertMiddle(mystruct *parent, string value, mystruct *left, mystruct *right)
{
    if (parent == NULL)
    {
        parent = createNode();
        parent->word[0] = value;
        parent->point[0] = left;
        parent->point[1] = right;
        parent->currentNode++;
        parent->lf = false;
        root = parent;
        left->parent = parent;
        right->parent = parent;
        return;
    }
    right->parent = parent;
    insertValueAndPoint(parent, value, right);
    if (parent->currentNode == mx)
    {
        mystruct *splitNode = createNode();
        splitNode->lf = false;
        int j = 0;
        for (int i = parent->currentNode - (n - 1) / 2; i < mx; i++)
        {
            splitNode->word[j] = parent->word[i];
            if (j == 0)
            {
                splitNode->point[0] = parent->point[i];
                splitNode->point[0]->parent = splitNode;
            }
            splitNode->point[j + 1] = parent->point[i + 1];
            splitNode->point[j + 1]->parent = splitNode;
            j++;
        }
        parent->currentNode -= (n - 1) / 2 + 1;
        splitNode->currentNode = (n - 1) / 2;
        insertMiddle(parent->parent, parent->word[parent->currentNode], parent, splitNode);
    }
}

void insertLeaf(string word, string meaning)
{
    mystruct *leaf = findLeaf(root, word);
    int i = leaf->currentNode - 1;
    if (i > -1)
    {
        for (; i >= 0; i--)
        {
            if (word < leaf->word[i])
            {
                leaf->word[i + 1] = leaf->word[i];
                leaf->meaning[i + 1] = leaf->meaning[i];
            }
            else
                break;
        }
    }
    leaf->word[i + 1] = word;
    leaf->meaning[i + 1] = meaning;
    leaf->currentNode++;

    if (leaf->currentNode == mx)
    {
        mystruct *splitNode = createNode();
        int j = 0;
        for (int i = leaf->currentNode - n / 2; i < mx; i++)
        {
            splitNode->word[j] = leaf->word[i];
            splitNode->meaning[j] = leaf->meaning[i];
            j++;
        }
        leaf->currentNode -= n / 2;
        splitNode->currentNode = n / 2;
        splitNode->next = leaf->next;
        leaf->next = splitNode;
        insertMiddle(leaf->parent, splitNode->word[0], leaf, splitNode);
    }
}

int main(void)
{
    cout << "number of Child: ";
    cin >> n;
    // n=3;
    mx = n;
    root = createNode();
    mystruct *leaf;
    int i = 0;
    string word, meaning, searchword;
    ifstream ifile;
    ifile.open("dictionary.txt");
    if (!ifile)
        cout << "ayhay";
    auto start1 = high_resolution_clock::now();
    while (ifile >> word)
    {
        getline(ifile, meaning);
        insertLeaf(word, meaning);
    }
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    cout << "Time taken to build Tree: " << duration1.count() << endl;
    cout << "enter text to search: ";
    while (cin >> searchword)
    {
        auto start = high_resolution_clock::now();
        leaf = findLeaf(root, searchword);
        for (i = 0; i < leaf->currentNode; i++)
            if (searchword == leaf->word[i])
                break;
        if (i == leaf->currentNode)
            cout << "no word founds\n";
        else
            cout << searchword << ": " << leaf->meaning[i] << endl;
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken to search: " << duration.count() << endl;
        cout << "enter text to search: ";
    }
}