#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nomor[10]; 
    int jenis;          
    char status[20];    
    struct Node *next;
} Node;

Node *front = NULL;
Node *rear = NULL;

int countR = 1;
int countP = 1;
int countC = 1;

void generateNomor(char *nomor, int jenis) {
    if (jenis == 1)
        sprintf(nomor, "R%03d", countR++);
    else if (jenis == 2)
        sprintf(nomor, "P%03d", countP++);
    else
        sprintf(nomor, "C%03d", countC++);
}

Node* createNode(int jenis) {
    Node *baru = (Node*) malloc(sizeof(Node));

    generateNomor(baru->nomor, jenis);
    baru->jenis = jenis;
    strcpy(baru->status, "Menunggu");
    baru->next = NULL;

    return baru;
}

void enqueue(int jenis) {
    Node *baru = createNode(jenis);

    if (rear == NULL) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }

    printf("\n>>> Antrian berhasil ditambahkan!\n");
    printf("Nomor: %s | Jenis: %d | Status: %s\n\n", 
        baru->nomor, baru->jenis, baru->status);
}

void menuTambah() {
    int pilihan;
    printf("\n=== TAMBAH DATA ANTRIAN ===\n");
    printf("1. Reguler\n");
    printf("2. Prioritas\n");
    printf("3. Customer Service\n");
    printf("Pilih jenis layanan: ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > 3) {
        printf("\n>>> Pilihan tidak valid! Data tidak ditambahkan.\n\n");
        return;
    }

    enqueue(pilihan);
}

int main() {
    int menu;

    while (1) {
        printf("=== MENU UTAMA ===\n");
        printf("1. Tambah Data Antrian\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &menu);

        if (menu == 1) {
            menuTambah();
        }
        else if (menu == 6) {
            printf("Program selesai.\n");
            break;
        } 
        else {
            printf("Menu tidak tersedia!\n");
        }
    }

    return 0;
}
