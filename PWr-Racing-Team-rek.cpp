#include <iostream>
#include <bits/stdc++.h>

using namespace std;

float min_val=0;
vector<float> best_path;


//struktura wezla
struct node
{
	float data;
	struct node* left;
	struct node* right;
};

//tworzene nowego wezla
struct node* newNode(float idata)
{
	struct node* node = new struct node;
	node->data = idata;
	node->left = NULL;
	node->right = NULL;
	return node;
}


//sprawdzanie czy dany wezel nie jest lisciem (w tym wypadku punktem B na mapie)
bool isLeaf(node* node) {
    return (node->left == nullptr && node->right == nullptr);
}
 
//Przeszukuje wszystkie mozliwe sciezki w drzewie
void searchAllRootToleafPaths(node* node, vector<float> &path)
{
    if (node == nullptr) {
        return;
    }

    path.push_back(node->data);
    
    //jezeli natrafi na lisc, oblicza koszt sciezki i sprawdza z aktualna wartoscia minimalna
    if (isLeaf(node))
    {
        float temp=0;
        for (float data: path) {
            temp+=data;
            //cout << data << " ";   
        }
        //cout << " SUMA: " << temp << endl;
        //W celu wyswietlenia calego drzewa, nalezy odkomentowac dwie linijki powyzej


        if(min_val>temp || min_val ==0) 
        {
            min_val = temp;
            best_path = path;
        }

        temp = 0;
    }


    //rekurencyjnie dodaje wezly do sciezki
    searchAllRootToleafPaths(node->left, path);
    searchAllRootToleafPaths(node->right, path);

    //usuwa wezel ze sciezki, jezeli ta nie ma juz kolejnych drog dalej
    path.pop_back();
}
 

void searchAllRootToleafPaths(node* node)
{
    vector<float> path;
 
    searchAllRootToleafPaths(node, path);
}


//wpisuje dane do drzewa
//wartosci wezlow to dlugosc drogi * koszt danego typu drogi
struct node* fillTree(float g, float y, float r)
{
    struct node *root = newNode(0);

	root->right = newNode(2 * y);
	root->right->right = newNode(6.8 * r);
	root->right->right->right = newNode(2 * r);
	root->right->right->right->right = newNode(12.3 * y);//LEAF

	root->right->right->right->left = newNode(1.3 * r);
	root->right->right->right->left->right = newNode(3.3 * r);//LEAF

	root->right->right->right->left->left = newNode(3.7 * g);
	root->right->right->right->left->left->right = newNode(1.7 * y);
	root->right->right->right->left->left->right->right = newNode(7.2 * g);//LEAF


	root->right->left = newNode(7.5 * y);
	root->right->left->right = newNode(3.5 * g);
	root->right->left->right->right = root->right->right->right;//LEAF

	root->right->left->left = newNode(4.2 * y);
	root->right->left->left->right = newNode(3.7 * g);
	root->right->left->left->right->right = newNode(3.3 * r);

	root->right->left->left->left = newNode(1.7 * y);
	root->right->left->left->left->right = newNode(7.2 * g);//LEAF
	
	root->right->right->left = newNode(3.5 * g);
	root->right->right->left->right = newNode(4.2 * y);

	root->right->right->left->right->right = newNode(3.7 * g);
	root->right->right->left->right->right->left = newNode(3.3 * r);//LEAF
	root->right->right->left->right->right->right = newNode(12.3 * y);//LEAF

	root->right->right->left->right->left = newNode(1.7 * y);
	root->right->right->left->right->left->left = newNode(7.2 * g);//LEAF


	root->left = newNode(10 * g);
	root->left->right = newNode(4.5 * g);
	root->left->right->right = newNode(3.5 * g);
	root->left->right->right->left = root->right->right->right;
	root->left->right->left = root->right->left->left;


	root->left->left = newNode(7.8 * r);
	root->left->left->left = newNode(7.2 * g);//END

	root->left->left->right = newNode(1.7 * y);
	root->left->left->right->right = newNode(4.2 * y);
	root->left->left->right->right->left = newNode(3.5 * g);
	root->left->left->right->right->left->left = root->right->right->right;

	root->left->left->right->left = newNode(3.7 * g);
	root->left->left->right->left->left = newNode(3.3 * r);//LEAF

	root->left->left->right->left->right = newNode(1.3 * r);
	root->left->left->right->left->right->left = newNode(12.3 * y);//LEAF

    return root;
}

int main()
{
    float green=1, yellow=1, red=1;

    cout<<"Podaj wartosc zielona: ";
    cin>>green;
    cout<<endl<<"Podaj wartosc zolta: ";
    cin>>yellow;
    cout<<endl<<"Podaj wartosc czerwona: ";
    cin>>red;

    struct node *tree = fillTree(green, yellow, red);

    searchAllRootToleafPaths(tree);
	
    for (float data: best_path) {
            cout << data << " ";
        }
        cout<<" SUMA "<<min_val<<endl;

	return 0;
}

