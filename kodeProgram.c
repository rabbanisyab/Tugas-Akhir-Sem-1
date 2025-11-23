#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nomor[10];
    char nama[50];
    char kebutuhan[100];
    char status[20];
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

Queue Qreg, Qprio, Qcs, Qhistory;

int countR = 1, countP = 1, countC = 1;

void initQueue(Queue *Q) {
    Q->front = NULL;
    Q->rear  = NULL;
}

int isEmpty(Queue Q) {
    return (Q.front == NULL);
}

void enqueue(Queue *Q, char nomor[]) {
    Node *baru = (Node*) malloc(sizeof(Node));
    strcpy(baru->nomor, nomor);
    strcpy(baru->status, "Menunggu");
    baru->next = NULL;

    if (Q->rear == NULL) {
        Q->front = Q->rear = baru;
    } else {
        Q->rear->next = baru;
        Q->rear = baru;
    }
}

Node* dequeue(Queue *Q) {
    if (Q->front == NULL) return NULL;

    Node *hapus = Q->front;
    Q->front = Q->front->next;

    if (Q->front == NULL) Q->rear = NULL;

    return hapus;
}

Node* cariDiQueue(Queue Q, char nomor[]) {
    Node *temp = Q.front;
    while (temp != NULL) {
        if (strcmp(temp->nomor, nomor) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void generateNomor(char *nomor, int jenis) {
    if (jenis == 1) sprintf(nomor, "R%03d", countR++);
    else if (jenis == 2) sprintf(nomor, "P%03d", countP++);
    else sprintf(nomor, "C%03d", countC++);
}

void tampilQueue(char *judul, Queue Q) {
    printf("\n--- %s ---\n", judul);

    if (isEmpty(Q)) {
        printf("Tidak ada antrian.\n");
        return;
    }

    Node *temp = Q.front;
    while (temp != NULL) {
        printf("%s (%s)\n", temp->nomor, temp->status);
        temp = temp->next;
    }
}

void menuTambah() {
    int pilihan;
    char nomor[10];

    printf("\n-----------------------------------\n");
    printf("TAMBAH ANTRIAN\n");
    printf("-----------------------------------\n");
    printf("1. Reguler\n");
    printf("2. Prioritas\n");
    printf("3. Customer Service\n");
    printf("Pilih jenis layanan: ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > 3) {
        printf("\n>>> Pilihan tidak valid!\n\n");
        return;
    }

    generateNomor(nomor, pilihan);

    if (pilihan == 1) enqueue(&Qreg, nomor);
    else if (pilihan == 2) enqueue(&Qprio, nomor);
    else enqueue(&Qcs, nomor);

    printf("\n>>> Antrian berhasil ditambahkan!\n");
    printf("Nomor Antrian: %s\n\n", nomor);
}

void menuLayani() {
    int loket;
    Queue *Q;

    if (isEmpty(Qreg) && isEmpty(Qprio) && isEmpty(Qcs)) {
        printf("\n>>> Belum ada data antrian!\n\n");
        return;
    }

    printf("\n-----------------------------------\n");
    printf("LAYANI NASABAH\n");
    printf("-----------------------------------\n");
    printf("1. Loket Reguler\n");
    printf("2. Loket Prioritas\n");
    printf("3. Loket Customer Service\n");
    printf("Pilih loket: ");
    scanf("%d", &loket);

    if (loket == 1) Q = &Qreg;
    else if (loket == 2) Q = &Qprio;
    else if (loket == 3) Q = &Qcs;
    else {
        printf("\n>>> Loket tidak valid!\n\n");
        return;
    }

    if (isEmpty(*Q)) {
        printf("\n>>> Tidak ada antrian di loket ini!\n\n");
        return;
    }

    Node *dilayani = dequeue(Q);

    printf("\nNomor antrian: %s\n", dilayani->nomor);

    int pilihan;
    printf("\n1. Lanjut Melayani\n");
    printf("2. Batal (Nasabah tidak hadir)\n");
    printf("Pilih: ");
    scanf("%d", &pilihan);

    if (pilihan == 2) {
        strcpy(dilayani->nama, "-");
        strcpy(dilayani->kebutuhan, "-");
        strcpy(dilayani->status, "Tidak Hadir");
    } else {
        printf("Masukkan Nama Nasabah   : ");
        scanf(" %[^\n]", dilayani->nama);

        printf("Masukkan Kebutuhan      : ");
        scanf(" %[^\n]", dilayani->kebutuhan);

        strcpy(dilayani->status, "Selesai");
    }

    printf("\n>>> Detail Pelayanan Nasabah <<<\n");
    printf("Nomor Antrian : %s\n", dilayani->nomor);
    printf("Loket         : %d\n", loket);
    printf("Nama          : %s\n", dilayani->nama);
    printf("Kebutuhan     : %s\n", dilayani->kebutuhan);
    printf("Status        : %s\n\n", dilayani->status);

    free(dilayani);
}

void menuCariData() {
    char nomor[10];

    printf("\n-----------------------------------\n");
    printf("CARI DATA ANTRIAN (NO)\n");
    printf("-----------------------------------\n");
    printf("Masukkan nomor antrian: ");
    scanf("%s", nomor);

    Node *hasil = NULL;

    hasil = cariDiQueue(Qreg, nomor);
    if (hasil == NULL) hasil = cariDiQueue(Qprio, nomor);
    if (hasil == NULL) hasil = cariDiQueue(Qcs, nomor);
    if (hasil == NULL) hasil = cariDiQueue(Qhistory, nomor);
    if (hasil == NULL) {
        printf("\n>>> Data tidak ditemukan!\n\n");
        return;
    }

    printf("\n>>> DATA DITEMUKAN <<<\n");
    printf("Nomor Antrian : %s\n", hasil->nomor);
    printf("Status        : %s\n\n", hasil->status);
}

void menuTampilAntrian() {
    printf("\n-----------------------------------\n");
    printf("DAFTAR ANTRIAN\n");
    printf("-----------------------------------\n");

    tampilQueue("Loket Reguler", Qreg);
    tampilQueue("Loket Prioritas", Qprio);
    tampilQueue("Loket Customer Service", Qcs);

    printf("\n");
}

int main() {
    int menu;

    initQueue(&Qreg);
    initQueue(&Qprio);
    initQueue(&Qcs);
    initQueue(&Qhistory);

    while (1) {
        printf("===================================\n");
        printf("        PROGRAM ANTRIAN BANK       \n");
        printf("===================================\n");
        printf("1. Tambah Data Antrian\n");
        printf("2. Layani Nasabah\n");
        printf("3. Cari Data Antrian (ID)\n");
        printf("4. Tampilkan Data Antrian\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                menuTambah();
                break;
            case 2:
                menuLayani();
                break;
            case 3:
                menuCariData();
                break;
            case 4:
                menuTampilAntrian();
                break;
            case 5:
                printf("\nProgram selesai.\n");
                return 0;

            default:
                printf("\nMenu tidak valid.\n");
        }
    }

    return 0;
}