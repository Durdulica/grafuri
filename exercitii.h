#ifndef EXERCITII_H
#define EXERCITII_H
#include <iostream>
#include <ranges>
using namespace std;

constexpr int MAX_N = 100;
//se citesc muchiile unui graf neorientat, se afiseaza mat. si listele de adiacenta
void ex1() {
    int n = 4, m = 4;
    int muchii[][2] = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 1}
    };

    int matrice[MAX_N][MAX_N] = {0};
    int liste[MAX_N][MAX_N] = {0};
    int dimensiune[MAX_N] = {0};

    for(int i = 0; i < m; i++) {
        int x = muchii[i][0];
        int y = muchii[i][1];
        matrice[x][y] = matrice[y][x] = 1;
        liste[x][dimensiune[x]++] = y;
        liste[y][dimensiune[y]++] = x;
    }

    cout << "Matrice:\n";
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            cout << matrice[i][j] << ' ';
        cout << '\n';
    }

    cout << "\nListe:\n";
    for(int i = 1; i <= n; i++) {
        cout << i << ": ";
        for(int j = 0; j < dimensiune[i]; j++)
            cout << liste[i][j] << ' ';
        cout << '\n';
    }
}

//model simplu pe citire: primia linie contine n (noduri) si m (muchii), urmate de m linii cu perechi de noduri

void ex2() {
    int n, m;
    cin >> n >> m;
    int matrice[MAX_N][MAX_N] = {};

    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        matrice[x][y] = matrice[y][x] = 1;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << matrice[i][j] << ' ';
        }
        cout << '\n';
    }
}

//parcurgere pe latime

void BFS(int matrice[MAX_N][MAX_N], bool vizitat[MAX_N], int distanta[MAX_N], int n, int start) {
    int coada[MAX_N];
    int fata = 0, spate = 0;
    vizitat[start] = true;
    distanta[start] = 0;
    coada[spate++] = start;
    while(fata < spate) {
        int nod = coada[fata++];
        for(int vecin = 1; vecin <= n; vecin++) {
            if(matrice[nod][vecin] != 0 && !vizitat[vecin]) {
                vizitat[vecin] = true;
                distanta[vecin] = distanta[nod] + 1;
                coada[spate++] = vecin;
            }
        }
    }
}

void ex3() {
    int muchii[][2] = {{1, 2}, {1, 3}, {2, 4}, {3, 5}};
    int matrice[MAX_N][MAX_N] = {};
    bool vizitat[MAX_N] = {};
    int distanta[MAX_N] = {};
    int n = 5;
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }
    BFS(matrice, vizitat, distanta, n, 2);
    for(int i = 1; i <= n; i++) {
        cout << "Distanta la " << i << ": " << distanta[i] << '\n';
    }
}

//parcurgere care viziteaza toate nodurile

void DFS(int matrice[MAX_N][MAX_N], bool vizitat[MAX_N], int n, int nod) {
    vizitat[nod] = true;
    // cout << nod << " ";
    for(int vecin = 1; vecin <= n; vecin++) {
        if(matrice[nod][vecin] == 1 && !vizitat[vecin]) {

            DFS(matrice, vizitat, n, vecin);
        }
    }
}

//se poate gasi un nod cu aceasta metoda

bool search(int matrice[MAX_N][MAX_N], bool vizitat[MAX_N], int n, int nod, int target) {
    vizitat[nod] = true;
    if(nod == target) {
        return true;
    }

    for(int vecin = 1; vecin <= n; vecin++) {
        if(matrice[nod][vecin] && !vizitat[vecin]) {
            return search(matrice, vizitat, n, vecin, target);
        }
    }

    return false;
}

void ex4() {
    int muchii[][2] = {{1, 2}, {2, 3}, {3, 4}};
    int matrice[MAX_N][MAX_N] = {}, n = 4;
    bool vizitat[MAX_N] = {};
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }

    cout << search(matrice,vizitat,n,1,1);
}

//modificarea grafului si verificarea adiacentei

bool suntConectate(int start, int destinatie, int matrice[MAX_N][MAX_N], bool vizitat[MAX_N], int n) {
    for(int i = 1; i <= n; i++) {
        vizitat[i] = false;
    }
    for(int i = 1; i <= n; i++) {
        cout << vizitat[i] << " ";
    }
    cout << '\n';
    DFS(matrice,vizitat,n,start);
    for(int i = 1; i <= n; i++) {
        cout << vizitat[i] << " ";
    }
    cout << '\n';
    return vizitat[destinatie];
}

void ex5() {
    int muchii[][2] = {{1, 2}, {2, 3}, {3, 4}, {1, 4}};
    int matrice[MAX_N][MAX_N] = {}, n = 4;
    bool vizitat[MAX_N] = {};
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }

    cout << suntConectate(1,3,matrice,vizitat,n) << endl;
    matrice[2][3] = matrice[3][2] = 0;
    cout << suntConectate(1,3,matrice,vizitat,n);
}

//sa se gaseasca subgraful dominant

void DFS2(int matrice[MAX_N][MAX_N], bool vizitat[MAX_N], int compNod[MAX_N], int compCurr, int&dimCurr, int n, int nod){
    vizitat[nod] = true;
    compNod[nod] =  compCurr;
    dimCurr++;
    for(int vecin = 1; vecin <= n; vecin++) {
        if(matrice[nod][vecin] && !vizitat[vecin]) {
            DFS2(matrice, vizitat, compNod, compCurr, dimCurr, n,vecin);
        }
    }
}

void ex6() {
    int muchii[][2] = {{1, 2}, {2, 3}, {4, 5}, {5, 6}, {6, 4}};
    int matrice[MAX_N][MAX_N] = {}, n = 7;
    int compNod[MAX_N];
    bool vizitat[MAX_N] = {};
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }

    int maxComp = 0, compMax = 0, compCurr = 0, dimCurr;
    for(int i = 1; i <= n; i++) {
        if(!vizitat[i]) {
            compCurr++;
            dimCurr = 0;
            DFS2(matrice, vizitat, compNod, compCurr, dimCurr, n, i);
            if(dimCurr > maxComp) {
                maxComp = dimCurr;
                compMax = compCurr;
            }
        }
    }
    cout << "Comp maxima: ";
    for(int i = 1; i <= n; i++) {
        if(compNod[i] == compMax) {
            cout << i << " ";
        }
    }
    cout << endl;
}

//memorarea parintelui fiecarui nod pt. afisare drumului (BFS)

void BFS2(int matr[MAX_N][MAX_N], bool viz[MAX_N], int dist[MAX_N], int parinte[MAX_N], int n, int start) {
    int coada[MAX_N];
    int fata = 0, spate = 0;

    viz[start] = true;
    dist[start] = 0;
    parinte[start] = -1;
    coada[spate++] = start;

    while(fata < spate) {
        int nod = coada[fata++];
        for(int vecin = 1; vecin <= n; vecin++) {
            if(matr[nod][vecin] && !viz[vecin]) {
                viz[vecin] = true;
                dist[vecin] = dist[nod] + 1;
                parinte[vecin] = nod;
                coada[spate++] = vecin;
            }
        }
    }
}

void afisDrum(int parinte[MAX_N], int destinatie) {
    if(destinatie == -1) {
        return;
    }
    afisDrum(parinte,parinte[destinatie]);
    if(destinatie != -1) {
        cout << destinatie << ' ';
    }
}

void ex7() {
    int muchii[][2] = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 6}, {6, 5}};
    int matrice[MAX_N][MAX_N], n = 7;
    int distanta[MAX_N], parinte[MAX_N];
    bool vizitat[MAX_N] = {};
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }

    BFS2(matrice, vizitat, distanta, parinte, n,1);
    afisDrum(parinte, 5);
    cout << endl << distanta[5];
}

//detectarea unui ciclu intr-un graf neorientat cu DFS

bool detecteazaCiclu(int matrice[MAX_N][MAX_N], bool vizitat[MAX_N], int n, int nod, int parinte) {
    vizitat[nod] = true;
    for(int vecin = 1; vecin <=n; vecin++) {
        if(matrice[nod][vecin]) {
            if(!vizitat[vecin]) {
                if(detecteazaCiclu(matrice, vizitat, n, vecin, nod)) {
                    return true;
                }
            }else if(vecin != parinte) {
                return true;
            }
        }
    }
    return false;
}

void ex8() {
    int muchii[][2] = {{1, 2}, {2, 3}, {3, 1}, {3, 4}};
    int matrice[MAX_N][MAX_N], n = 4;
    bool vizitat[MAX_N] = {};
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }

    bool ciclu = false;
    for(int i = 1; i <= n; i++) {
        if(!vizitat[i] && detecteazaCiclu(matrice, vizitat, n, i, -1)) {
            ciclu = true;
            break;
        }
    }
    cout << ciclu << endl;
}

//sa se citeste un graf neorientat si sa se afiseze gardul fiecarui nod

int gradNod(int matrice[MAX_N][MAX_N], int n,int nod) {
    int grad = 0;
    for(int vecin = 1; vecin <= n; vecin++) {
        if(matrice[nod][vecin]) {
            grad++;
        }
    }
    return grad;
}

void ex9() {
    int muchii[][2] = {{1, 2}, {2, 3}, {3, 1}, {3, 4}};
    int matrice[MAX_N][MAX_N], n = 4;
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }
    for(int i = 1; i <= n; i++) {
        cout << i << " grad: " << gradNod(matrice, n, i) << endl;
    }
}

//sa se verif. daca un graf este complet(fiecare nod este conectat cu toate celelalte)

bool esteComplet(int matrice[MAX_N][MAX_N], int n) {
    for(int i = 1; i <= n; i++) {
        if(gradNod(matrice, n, i) != n - 1) {
            return false;
        }
    }
    return true;
}

void ex10() {
    int muchii[][2] = {{1, 2}, {1, 3}, {1, 4},{2,3},  {2,4}, {3, 4}};
    int matrice[MAX_N][MAX_N], n = 4;
    for(auto & muchie : muchii) {
        int x = muchie[0];
        int y = muchie[1];
        matrice[x][y] = matrice[y][x] = 1;
    }

    cout << esteComplet(matrice, n) << endl;
}

//pentru un graf orientat, numara cate arce ies din fiecare nod si cate intra

int ctArcIn(int matrice[MAX_N][MAX_N], int n, int nod) {
    int ct = 0;
    for(int i = 1; i <= n; i++) {
        if(matrice[i][nod]) {
            ct++;
        }
    }
    return ct;
}

int ctArcOut(int matrice[MAX_N][MAX_N], int n, int nod) {
    int ct = 0;
    for(int i = 1; i <= n; i++) {
        if(matrice[nod][i]) {
            ct++;
        }
    }
    return ct;
}

void ex11() {
    int muchii[][2] = {{1, 2}, {2, 3}, {3, 1}, {3, 4}};
    int matrice[MAX_N][MAX_N], n = 4;
    for(auto muchie : muchii) {
        matrice[muchie[0]][muchie[1]] = 1;
    }

    for(int i = 1; i <= n; i++) {
        cout << i << " arc in: " << ctArcIn(matrice, n, i) <<  " arc out: " << ctArcOut(matrice,n,i) << endl;
    }
}

//sa se verifice daca un graf este partial folosind BFS

bool eGrafBipartit(int matrice[MAX_N][MAX_N], int culoare[MAX_N], int n, int start) {
    int coada[100]{};
    int fata = 0, spate = 0;
    coada[spate++] = start;
    culoare[start] = 0;

    while(fata < spate) {
        int nod = coada[fata++];
        for(int i = 1; i <= n; i++) {
            if(matrice[nod][i]) {//exista muchie intre nod si i
                if(culoare[i] == -1) {//nodul i nu are culoare
                    culoare[i] =1-culoare[nod];//coloram cu culoarea opuse
                    coada[spate++] = i;
                }else if(culoare[i] == culoare[nod]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void ex12() {
    int muchii[][2] = {{1,4},{1,3},{2, 3},{2,4},{3,5},{5,6},{6,3}};
    int matrice[MAX_N][MAX_N], n = 4;
    int culoare[MAX_N]{};
    for(int i = 0; i <= n; i++) {
        culoare[i] = -1;
    }

    for(auto & muchie : muchii) {
        matrice[muchie[0]][muchie[1]] = matrice[muchie[1]][muchie[0]] = 1;
    }

    cout << eGrafBipartit(matrice, culoare, n, 1);
}

//sa se verif daca o matr. este sau nu matr. de adiacenta asociata unui graf neorientat

bool verifMatrAdiacenta(int matr[MAX_N][MAX_N], int n) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(matr[i][j] != matr[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void ex13() {
    int matrice[MAX_N][MAX_N] , n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> matrice[i][j];
        }
    }

    cout << verifMatrAdiacenta(matrice, n);
}

//sa se det. nodurile din graf care au gradul egau cu gradul nodului k

int ctNoduriGradK(int matr[MAX_N][MAX_N], int n, int k) {
    int aux = gradNod(matr,n,k), ct = 0;
    for(int i = 1; i <= n; i++) {
        if(gradNod(matr,n,i) == aux) {
            cout << i << " ";
            ct++;
        }
    }
    cout << endl;
    return ct;
}

void ex14() {
    int muchii[][2] = {{5,3},{1,4},{1,3},{4,5},{2,4},{1,2},{3,4}};
    int matrice[MAX_N][MAX_N], n = 5, k = 3;
    for(auto & muchie : muchii) {
        matrice[muchie[0]][muchie[1]] = matrice[muchie[1]][muchie[0]] = 1;
    }

    cout << ctNoduriGradK(matrice, n, k);
}

//sa se afis. nodurile izolate ale grafului

void afisNodIzolate(int matr[MAX_N][MAX_N], int n) {
    int ct = 0;
    for(int i = 1; i <= n; i++) {
        if(gradNod(matr,n,i) == 0) {
            ct++;
            cout << i << " ";
        }
    }
    cout << ct << endl;
}

void ex15() {
    int muchii[][2] = {{1,4},{3,6},{4,3},{1,6},{6,4}};
    int matrice[MAX_N][MAX_N], n = 6;
    for(auto & muchie : muchii) {
        matrice[muchie[0]][muchie[1]] = matrice[muchie[1]][muchie[0]] = 1;
    }

    afisNodIzolate(matrice,n);
}

//se da un graf orientat cu n noduri si m muchii. Se numeste nod saturat un vf. care are gradul mai mare sau egal cu jumatatea nr. de noduri
//daca nr. de vf. este impar, atunci gradul tb. sa fie mai mare strict decat jumatatea nr. de noduri. Sa se afis. nodurile saturate din graf


#endif //EXERCITII_H