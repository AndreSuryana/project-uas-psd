#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define INFINITY 99
#define MAX 10

int jmlVertex;
int jarak[MAX][MAX];
int adjoin[MAX][MAX];

void header() {
    printf("===============================================================\n");
    printf("             PROJECT UAS PRAKTIKUM STRUKTUR DATA\n");
    printf("   MENCARI JARAK TERPENDEK DARI WAREHOUSE KE LOKASI CUSTOMER\n");
    printf("                 BAGI KURIR PENGANTAR BARANG\n");
    printf("                  DENGAN ALGORITMA DIJKSTRA\n");
    printf("===============================================================\n");
    printf("Anggota :\n");
    printf("  1. I Kadek Krisna Dwi Payana    (1908561100)\n");
    printf("  2. I Made Adika Bhavanta        (1908561101)\n");
    printf("  3. Rafif Jhordi                 (1908561102)\n");
    printf("  4. Kadek Andre Suryana          (1908561103)\n");
    printf("===============================================================\n\n");
}

void showGraph() {
    system("cls");
    header();
    printf("\nTampilan Graph :\n");

    for (int i=0; i<jmlVertex; i++) {
        for (int j=0; j<jmlVertex; j++) {
            printf("%d ", jarak[i][j]);
        }
        printf("\n");
    }

    printf("\n\nTampilan Ketetanggaan Kota : \n\n");

    for(int i=0; i<jmlVertex; i++)
    {
        for(int j=0; j<jmlVertex; j++)
        {
            if(adjoin[i][j] == 1)
            {
                printf("Kota %d bertetangga dengan Kota %d dengan jarak %d\n", i+1, j+1, jarak[i][j]);
            }
            // Kota yang tidak terhubung akan di set menjadi INF atau 99
        }
    }
    printf("\n");
    getch();
}

// Fungsi init() adalah untuk menginisialisasikan struktur graf (STATIC)
void init(int jml, int arr[MAX][MAX], int adj[MAX][MAX]) {
    // Assign jmlVertex
    jmlVertex = jml;

    // Assign array 2d yaitu jarak dengan array
    for (int i=0; i<jmlVertex; i++) {
        for (int j=0; j<jmlVertex; j++) {
            jarak[i][j] = arr[i][j];
        }
    }

    // Assign array 2d adjoin
    for (int i=0; i<jmlVertex; i++) {
        for (int j=0; j<jmlVertex; j++) {
            adjoin[i][j] = adj[i][j];
        }
    }
}

// Fungsi addNewData() adalah untuk meminta inputan data ke user (DINAMIC)
void addNewData() {
    int adj, dis;

    system("cls");
    header();
    printf("Masukkan jumlah kota (vertex) : ");
    scanf("%d", &jmlVertex);

    if (jmlVertex > MAX) {
        printf("\nJumlah kota tidak boleh lebih dari 10!\n\n");
        return;
    }

    printf("\nInput Data Baru :\n");
    printf("*NB : - Input '1' jika Kota bertetangga, jika Kota tidak bertetangga input '0'!!..\n");
    printf("      - Jika Kota bertetangga, input jarak tempuh (jarak tidak boleh '0')!!..\n\n");

    for (int i=0; i<jmlVertex; i++)
    {
        for (int j=i+0; j<jmlVertex; j++)
        {
            if (i != j)
            {
                printf("Apakah Kota %d bertetangga dengan Kota %d? : ", i+1, j+1);
                scanf("%d", &adj);
                if (adj == 1)
                {
                    adjoin[i][j] = adjoin[j][i] = 1;
                    printf("Jarak Kota %d dengan Kota %d : ", i+1, j+1);
                    scanf("%d", &dis);
                    {
                        if(dis != 0)
                        {
                            jarak[i][j] = jarak[j][i] = dis;
                        }
                        else
                        {
                            printf("\nError! Jarak tempuh tidak boleh bernilai 0!\n");
                            exit(1);
                        }
                    }
                }
                else
                {
                    adjoin[i][j] = adjoin[j][i] = 0;
                    jarak[i][j] = jarak[j][i] = 0;
                }
            }
            else
            {
                jarak[i][j] = jarak[j][i] = 0;
            }
        }
        printf("\n");
    }
    printf("\nData berhasil di input! \n\n");
}

void algoritmaDijkstra() {
    int awal, tujuan;
    int indexAwal, indexTujuan;
    int tempJarak[jmlVertex][jmlVertex];
    int distance[jmlVertex];
    int temporary[jmlVertex];
    int visited[jmlVertex];
    int jarakMin, nextKota;
    int count; // counter variable untuk loop pada vertex

    system("cls");
    header();
    printf("Lokasi Warehouse : "); scanf("%d", &awal);
    printf("Lokasi Tujuan    : "); scanf("%d", &tujuan);

    indexAwal = awal - 1;
    indexTujuan = tujuan - 1;

    // Initialize tempJarak
    for (int i=0; i<jmlVertex; i++) {
        for (int j=0; j<jmlVertex; j++) {
            if (jarak[i][j] == 0)
                tempJarak[i][j] = INFINITY;
            else
                tempJarak[i][j] = jarak[i][j];
        }
    }

    // Setting up value
    for (int i=0; i<jmlVertex; i++) {
        distance[i] = tempJarak[indexAwal][i];
        temporary[i] = indexAwal;
        visited[i] = 0;
    }

    distance[indexAwal] = 0;
    visited[indexAwal] = 1;
    count = 1;

    while (count < jmlVertex - 1) {
        jarakMin = INFINITY;

        for (int i=0; i<jmlVertex; i++) {
            if (distance[i] < jarakMin && visited[i] != 1) {
                jarakMin = distance[i];
                nextKota = i;
            }
        }

        visited[nextKota] = 1;

        for (int i=0; i<jmlVertex; i++) {
            if (visited[i] != 1) {
                if (jarakMin + tempJarak[nextKota][i] < distance[i]) {
                    distance[i] = jarakMin + tempJarak[nextKota][i];
                    temporary[i] = nextKota;
                }
            }
        }
        count += 1;
    }

    // Output :
    printf("\nJarak Minimum yang dapat dilalui Kurir Dari Kota %d ke Kota %d adalah %d\n", awal, tujuan, distance[indexTujuan]);
    printf("Lintasan :\n");

    for (int i=0; i<jmlVertex; i++) {
        if (i == indexTujuan) {
            printf("%d", i + 1);
            int j = i;
            while (j != indexAwal) {
                j = temporary[j];
                printf(" <- %d", j + 1);
            }
        }
    }
    printf("\n\n");
    system("pause");
}

int main() {
    int menu;

    int jml = 7;
    int graph[MAX][MAX] = {
        {0,7,4,0,0,0,0},
        {7,0,3,0,5,0,0},
        {4,3,0,4,0,0,0},
        {0,0,4,0,8,1,0},
        {0,5,0,8,0,2,0},
        {0,0,0,1,2,0,4},
        {0,0,0,0,0,4,0}
    };
    int adj[MAX][MAX] = {
        {0,1,1,0,0,0,0},
        {1,0,1,0,1,0,0},
        {1,1,0,1,0,0,0},
        {0,0,1,0,1,1,0},
        {0,1,0,1,0,1,0},
        {0,0,0,1,1,0,1},
        {0,0,0,0,0,1,0}
    };

    do {
        system("cls");
        header();
        printf("Menu : \n");
        printf("[1] Gunakan data yang sudah ada\n");
        printf("[2] Masukkan data yang baru\n");
        printf("[3] Keluar\n");
        printf(">>> "); scanf("%d", &menu);

        switch(menu) {
            case 1:
                // STATIC DATA:
                init(jml, graph, adj);
                showGraph();
                algoritmaDijkstra();
                break;
            case 2:
                // DINAMIC DATA:
                addNewData();
                showGraph();
                algoritmaDijkstra();
                break;
            case 3:
                printf("\nTerima kasih!\n\n");
                exit(0);
                break;
            default:
                printf("\nInput Anda salah!\n\n");
                break;
        }
        getch();
    } while (menu != 3);

    return 0;
}
