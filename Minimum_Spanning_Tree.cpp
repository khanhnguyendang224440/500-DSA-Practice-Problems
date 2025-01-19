#include <iostream> // Thu vien cho phep nhap xuat du lieu
using namespace std;
/*

#Mô tải bài toán:
    Cho một đồ thị vô hướng có trọng số, hãy tìm Cây Khung Nhỏ Nhất (MST) của đồ thị.
        -Cây khung (Spanning Tree):
            +Là một cây con của đồ thị ban đầu.
            +Bao gồm tất cả các đỉnh của đồ thị.
            +Không chứa chu trình (cycle).
            +Có đúng V−1 cạnh, với V là số đỉnh trong đồ thị.
        -Cây khung nhỏ nhất (Minimum Spanning Tree):
            +Là cây khung có tổng trọng số nhỏ nhất trong tất cả các cây khung của đồ thị.
        -Yêu cầu:
            +Tìm các cạnh thuộc cây khung nhỏ nhất và tính tổng trọng số của nó.
        -Điều kiện bài toán:
            +Đồ thị phải liên thông (có ít nhất một đường đi giữa mọi cặp đỉnh).
            +Trọng số các cạnh không âm.
            
#Ý tưởng thuật toán (Kruskal):
    Thuật toán Kruskal sử dụng tư duy "Greedy" (Tham lam):
        -Sắp xếp các cạnh theo trọng số tăng dần.
        -Thêm các cạnh nhỏ nhất vào cây khung nhỏ nhất (MST):
            +Lần lượt duyệt qua các cạnh đã sắp xếp.
            +Chỉ thêm cạnh nếu nó không tạo chu trình trong cây khung hiện tại.
        -Dừng lại khi MST có đủ V−1 cạnh.
*/
const int MAX = 100;        // So luong canh va dinh toi da
const int INF = 1000000000; // Gia tri lon dai dien cho vo han

// Cau truc canh de luu thong tin cua mot canh trong do thi
struct Edge {
    int u, v, weight; // Dinh dau, dinh cuoi, trong so
};

// Ham hoan doi hai canh
void swap(Edge& a, Edge& b) {
    Edge temp = a;
    a = b;
    b = temp;
}

// Sap xep cac canh bang thuat toan sap xep noi bot (Bubble Sort)
void bubbleSort(Edge edges[], int E) {
    for (int i = 0; i < E - 1; ++i) {
        for (int j = 0; j < E - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                swap(edges[j], edges[j + 1]); // Hoan doi neu canh truoc co trong so lon hon
            }
        }
    }
}

// Ham tim goc cua mot dinh trong cay (thuoc Union-Find)
int find(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]); // Path compression
    }
    return parent[x];
}

// Ham hop nhat hai tap hop (Union trong Union-Find)
void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Ham chinh: Thuat toan Kruskal
void kruskal(Edge edges[], int V, int E) {
    bubbleSort(edges, E); // Sap xep cac canh theo trong so tang dan

    int parent[MAX]; // Mang cha de quan ly cac tap hop trong Union-Find
    int rank[MAX];   // Mang cap bac de toi uu hoa Union-Find
    Edge MST[MAX];   // Mang luu cac canh cua cay khung nho nhat
    int mstSize = 0; // So luong canh trong cay khung nho nhat

    // Khoi tao Union-Find
    for (int i = 0; i < V; ++i) {
        parent[i] = i; // Moi dinh ban dau la mot tap hop rieng
        rank[i] = 0;   // Cap bac cua moi tap hop ban dau la 0
    }

    // Duyet qua tung canh
    for (int i = 0; i < E; ++i) {
        int u = edges[i].u;         // Dinh dau cua canh
        int v = edges[i].v;         // Dinh cuoi cua canh
        int weight = edges[i].weight; // Trong so cua canh

        // Neu hai dinh u va v khong thuoc cung mot tap hop
        if (find(parent, u) != find(parent, v)) {
            MST[mstSize++] = edges[i]; // Them canh vao cay khung nho nhat
            unionSets(parent, rank, u, v); // Hop nhat hai tap hop

            if (mstSize == V - 1) break; // Neu cay khung da du V-1 canh thi dung lai
        }
    }

    // In ket qua
    cout << "Cay khung nho nhat gom cac canh:\n";
    for (int i = 0; i < mstSize; ++i) {
        cout << MST[i].u << " - " << MST[i].v << " : " << MST[i].weight << endl;
    }
}

int main() {
    int V, E; // So dinh va so canh
    cout << "Nhap so dinh va so canh: ";
    cin >> V >> E; // Nguoi dung nhap so dinh va canh

    Edge edges[MAX]; // Mang luu thong tin cac canh

    // Nguoi dung nhap danh sach cac canh
    cout << "Nhap cac canh (dinh u, dinh v, trong so):\n";
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // Goi thuat toan Kruskal
    kruskal(edges, V, E);

    return 0; // Ket thuc chuong trinh
}

