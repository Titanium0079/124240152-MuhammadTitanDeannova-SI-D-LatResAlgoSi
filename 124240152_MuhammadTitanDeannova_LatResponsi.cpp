#include <iostream>
#include <string>
using namespace std;

//Struktur untuk menyimpan data buku 
struct Book {
    string judul;
    string pengarang;
    int tahun; 
};

//Struktur node untuk Binary Search Tree (BST)
struct BSTNode {
    Book data;
    BSTNode* left;
    BSTNode* right;
};

// Fungsi untuk menambah buku ke BST
BSTNode* insert(BSTNode* root, Book buku) {
    if (!root) {
        root = new BSTNode{buku, nullptr, nullptr};
    } else if (buku.judul < root->data.judul) {
        root->left = insert(root->left, buku);
    } else if (buku.judul > root->data.judul) {
        root->right = insert(root->right, buku);
    } else {
        cout << "Judul sudah ada, tidak boleh duplikat.\n";
    }
    return root;
}

// Fungsi in-order traversal untuk menampilkan buku
void inOrder(BSTNode* root){
    if(root){
        inOrder(root->left);
        cout << "Judul: " << root->data.judul 
             << ", Pengarang: " << root->data.pengarang
             << ", Tahun: " << root->data.tahun << endl;
        inOrder(root->right);
    }
}

// Mencari node dengan nilai minimum (digunakan saat hapus)
BSTNode* findMin(BSTNode* root) {
    while (root && root->left){
        root = root ->left;
    }
    return root;
}

// Fungsi untuk menghapus buku berdasarkan judul
BSTNode* remove(BSTNode* root, string judul, bool &found){
    if(!root){
        found = false;
        return nullptr;
    }

    if (judul < root->data.judul){
        root->left = remove(root->left, judul, found);
    } else if (judul > root->data.judul){
        root->right = remove(root->right, judul, found);
    } else {
        found = true;
        if(!root->left){
            BSTNode* temp = root->right;
            delete root;
            return temp;
        }else if(!root->right){
            BSTNode* temp = root->left;
            delete root;
            return temp;
        } else {
            BSTNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data.judul, found);
        }
    }

    return root;
}

//Menu
void showMenu() {
        cout << "\n=== MENU KENANGAN DALAM SEBUAH BUKU ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilan Buku\n";
        cout << "3. Hapus Buku\n";
        cout << "4. Keluar\n";
        cout << "Pilih : ";
}

int main(){
    BSTNode* root = nullptr;
    int pilihan;

    do{
        showMenu();
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1){
            Book buku;
            cout << "Judul: ";
            getline(cin, buku.judul);
            cout << "Pengarang: ";
            getline(cin, buku.pengarang);
            cout <<"Tahun terbit: ";
            cin >> buku.tahun;
            cin.ignore();

            root = insert(root, buku);
            cout << "Buku ditambahkan.\n";

        } else if (pilihan == 2){
            if(!root){
                cout << "belum ada buku.\n";
            } else {
                 cout << "\n=== DAFTAR BUKU ===\n";
                 inOrder(root);
            }

        } else if (pilihan == 3){
            string judul;
            cout << "Masukkna judul buku yang ingin dihapus: ";
            getline(cin, judul);
            bool found = false;
            root = remove(root, judul, found);
            if (found){
                cout << "Buku \"" << judul << "\" berhasil dihapus. \n";
            } else {
                cout << "Buku tidak ditemukan.\n";
            }

        }else if (pilihan == 4) {
            cout << "Keluar dari aplikasi. Terimakasih! \n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    
    } while (pilihan != 4);
    return 0;
}