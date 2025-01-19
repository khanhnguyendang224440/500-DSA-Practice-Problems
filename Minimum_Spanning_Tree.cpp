#include <iostream> // Thư viện cho phép nhập xuất dữ liệu
using namespace std;
/*

#Mô tả bài toán:
    Cho một đồ thị vô hướng có trọng số, hãy tìm Cây Khung Nhỏ Nhất (MST) của đồ thị.
        - Cây khung (Spanning Tree):
            + Là một cây con của đồ thị ban đầu.
            + Bao gồm tất cả các đỉnh của đồ thị.
            + Không chứa chu trình (cycle).
            + Có đúng V−1 cạnh, với V là số đỉnh trong đồ thị.
        - Cây khung nhỏ nhất (Minimum Spanning Tree):
            + Là cây khung có tổng trọng số nhỏ nhất trong tất cả các cây khung của đồ thị.
        - Yêu cầu:
            + Tìm các cạnh thuộc cây khung nhỏ nhất và tính tổng trọng số của nó.
        - Điều kiện bài toán:
            + Đồ thị phải liên thông (có ít nhất một đường đi giữa mọi cặp đỉnh).
            + Trọng số các cạnh không âm.
            
#Ý tưởng thuật toán (Kruskal):
    Thuật toán Kruskal sử dụng tư duy "Greedy" (Tham lam):
        - Sắp xếp các cạnh theo trọng số tăng dần.
        - Thêm các cạnh nhỏ nhất vào cây khung nhỏ nhất (MST):
            + Lần lượt duyệt qua các cạnh đã sắp xếp.
            + Chỉ thêm cạnh nếu nó không tạo chu trình trong cây khung hiện tại.
        - Dừng lại khi MST có đủ V−1 cạnh.
*/
const int MAX = 100;        // Số lượng cạnh và đỉnh tối đa
const int INF = 1000000000; // Giá trị lớn đại diện cho vô hạn

// Cấu trúc cạnh để lưu thông tin của một cạnh trong đồ thị
struct Edge {
    int u, v, weight; // Đỉnh đầu, đỉnh cuối, trọng số
};

// Hàm hoán đổi hai cạnh
void swap(Edge& a, Edge& b) {
    Edge temp = a;
    a = b;
    b = temp;
}

// Sắp xếp các cạnh bằng thuật toán sắp xếp nổi bọt (Bubble Sort)
void bubbleSort(Edge edges[], int E) {
    for (int i = 0; i < E - 1; ++i) {
        for (int j = 0; j < E - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                swap(edges[j], edges[j + 1]); // Hoán đổi nếu cạnh trước có trọng số lớn hơn
            }
        }
    }
}

// Hàm tìm gốc của một đỉnh trong cây (thuộc Union-Find)
int find(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]); // Tối ưu hóa bằng Path Compression
    }
    return parent[x];
}

// Hàm hợp nhất hai tập hợp (Union trong Union-Find)
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

// Hàm chính: Thuật toán Kruskal
void kruskal(Edge edges[], int V, int E) {
    bubbleSort(edges, E); // Sắp xếp các cạnh theo trọng số tăng dần

    int parent[MAX]; // Mảng cha để quản lý các tập hợp trong Union-Find
    int rank[MAX];   // Mảng cấp bậc để tối ưu hóa Union-Find
    Edge MST[MAX];   // Mảng lưu các cạnh của cây khung nhỏ nhất
    int mstSize = 0; // Số lượng cạnh trong cây khung nhỏ nhất

    // Khởi tạo Union-Find
    for (int i = 0; i < V; ++i) {
        parent[i] = i; // Mỗi đỉnh ban đầu là một tập hợp riêng
        rank[i] = 0;   // Cấp bậc của mỗi tập hợp ban đầu là 0
    }

    // Duyệt qua từng cạnh
    for (int i = 0; i < E; ++i) {
        int u = edges[i].u;         // Đỉnh đầu của cạnh
        int v = edges[i].v;         // Đỉnh cuối của cạnh
        int weight = edges[i].weight; // Trọng số của cạnh

        // Nếu hai đỉnh u và v không thuộc cùng một tập hợp
        if (find(parent, u) != find(parent, v)) {
            MST[mstSize++] = edges[i]; // Thêm cạnh vào cây khung nhỏ nhất
            unionSets(parent, rank, u, v); // Hợp nhất hai tập hợp

            if (mstSize == V - 1) break; // Nếu cây khung đã đủ V-1 cạnh thì dừng lại
        }
    }

    // In kết quả
    cout << "Cây khung nhỏ nhất gồm các cạnh:\n";
    for (int i = 0; i < mstSize; ++i) {
        cout << MST[i].u << " - " << MST[i].v << " : " << MST[i].weight << endl;
    }
}

int main() {
    int V, E; // Số đỉnh và số cạnh
    cout << "Nhập số đỉnh và số cạnh: ";
    cin >> V >> E; // Người dùng nhập số đỉnh và cạnh

    Edge edges[MAX]; // Mảng lưu thông tin các cạnh

    // Người dùng nhập danh sách các cạnh
    cout << "Nhập các cạnh (đỉnh u, đỉnh v, trọng số):\n";
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // Gọi thuật toán Kruskal
    kruskal(edges, V, E);

    return 0; // Kết thúc chương trình
}
