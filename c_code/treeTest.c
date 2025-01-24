#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 3  // B+트리에서 최대 키 개수 (차수 - 1)

// 포켓몬 구조체 정의
typedef struct Pokemon {
    unsigned short number;
    char name[22];
    unsigned short atk;
    unsigned short hp;
    unsigned short def;
    unsigned short spa;
    unsigned short spd;
    unsigned short speed;
} Pokemon;

// B+트리 노드 정의
typedef struct Node {
    int is_leaf;
    int num_keys;
    unsigned short keys[MAX_KEYS];
    struct Node* children[MAX_KEYS + 1];
    Pokemon* records[MAX_KEYS];  // 리프 노드에만 사용
    struct Node* next;           // 리프 노드 연결 리스트
} Node;

// B+트리 정의
typedef struct BPlusTree {
    Node* root;
    unsigned short (*get_key)(Pokemon*);  // 키값을 추출하는 함수 포인터
} BPlusTree;

// 키 추출 함수 예시
unsigned short get_num(Pokemon* p) { return p->number; }
unsigned short get_atk(Pokemon* p) { return p->atk; }
unsigned short get_hp(Pokemon* p) { return p->hp; }
unsigned short get_def(Pokemon* p) { return p->def; }
unsigned short get_spa(Pokemon* p) { return p->spa; }
unsigned short get_spd(Pokemon* p) { return p->spd; }
unsigned short get_speed(Pokemon* p) { return p->speed; }

// 새로운 노드 생성
Node* create_node(int is_leaf) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->next = NULL;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        node->children[i] = NULL;
        if (is_leaf) node->records[i] = NULL;
    }
    return node;
}

// B+트리 초기화
BPlusTree* create_tree(unsigned short (*get_key)(Pokemon*)) {
    BPlusTree* tree = (BPlusTree*)malloc(sizeof(BPlusTree));
    tree->root = create_node(1);  // 루트는 처음엔 리프 노드
    tree->get_key = get_key;
    return tree;
}

// 키 삽입 위치 찾기
int find_insert_position(Node* node, unsigned short key) {
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    return i;
}

// 노드 분할
void split_node(Node* parent, int index, Node* child) {
    int mid = MAX_KEYS / 2;
    Node* new_node = create_node(child->is_leaf);
    new_node->num_keys = MAX_KEYS - mid - 1;

    // 중간 이후의 키와 데이터를 새로운 노드로 이동
    for (int i = 0; i < new_node->num_keys; i++) {
        new_node->keys[i] = child->keys[mid + 1 + i];
        if (child->is_leaf) {
            new_node->records[i] = child->records[mid + 1 + i];
        } else {
            new_node->children[i] = child->children[mid + 1 + i];
        }
    }
    if (!child->is_leaf) {
        new_node->children[new_node->num_keys] = child->children[MAX_KEYS];
    }
    if (child->is_leaf) {
        new_node->next = child->next;  // 기존 연결 유지
        child->next = new_node;       // 새로운 리프 노드 연결
    }

    child->num_keys = mid;

    // 부모 노드에 새 키와 포인터 삽입
    for (int i = parent->num_keys; i > index; i--) {
        parent->keys[i] = parent->keys[i - 1];
        parent->children[i + 1] = parent->children[i];
    }
    parent->keys[index] = child->keys[mid];
    parent->children[index + 1] = new_node;
    parent->num_keys++;
}

// 데이터 삽입 (재귀)
void insert_non_full(Node* node, Pokemon* pokemon, unsigned short key, BPlusTree* tree) {
    if (node->is_leaf) {
        int pos = find_insert_position(node, key);

        // 키와 데이터를 삽입
        for (int i = node->num_keys; i > pos; i--) {
            node->keys[i] = node->keys[i - 1];
            node->records[i] = node->records[i - 1];
        }
        node->keys[pos] = key;
        node->records[pos] = pokemon;
        node->num_keys++;
    } else {
        int pos = find_insert_position(node, key);
        if (node->children[pos]->num_keys == MAX_KEYS) {
            split_node(node, pos, node->children[pos]);
            if (key > node->keys[pos]) {
                pos++;
            }
        }
        insert_non_full(node->children[pos], pokemon, key, tree);
    }
}

// 루트 분할
void split_root(BPlusTree* tree) {
    Node* old_root = tree->root;
    Node* new_root = create_node(0);
    new_root->children[0] = old_root;
    split_node(new_root, 0, old_root);
    tree->root = new_root;
}

// 데이터 삽입 (루트 처리)
void insert(BPlusTree* tree, Pokemon* pokemon) {
    unsigned short key = tree->get_key(pokemon);
    if (tree->root->num_keys == MAX_KEYS) {
        split_root(tree);
    }
    insert_non_full(tree->root, pokemon, key, tree);
}

// 트리 출력 (리프 노드 순회)
void print_tree(BPlusTree* tree) {
    Node* node = tree->root;
    while (!node->is_leaf) {
        node = node->children[0];
    }
    while (node) {
        for (int i = 0; i < node->num_keys; i++) {
            printf("Pokemon: %s, Key: %u\n", node->records[i]->name, node->keys[i]);
        }
        node = node->next;
    }
}

// 테스트
int main() {
    BPlusTree* tree = create_tree(get_num);

    Pokemon p1 = {1, "Bulbasaur", 49, 45, 49, 65, 65, 45};
    Pokemon p2 = {4, "Charmander", 52, 39, 43, 60, 50, 65};
    Pokemon p3 = {7, "Squirtle", 48, 44, 65, 50, 64, 43};
    Pokemon p4 = {25, "Pikachu", 55, 35, 40, 50, 50, 90};
    Pokemon p5 = {133, "Eevee", 55, 55, 50, 45, 65, 55};
    Pokemon p6 = {143, "Snorlax", 110, 160, 65, 65, 65, 30};
    Pokemon p7 = {6, "Charizard", 84, 78, 78, 109, 85, 100};
    Pokemon p8 = {9, "Blastoise", 83, 79, 100, 85, 105, 78};
    Pokemon p9 = {26, "Raichu", 90, 60, 55, 90, 80, 110};
    Pokemon p10 = {134, "Vaporeon", 65, 130, 60, 110, 95, 65};

    insert(tree, &p1);
    insert(tree, &p2);
    insert(tree, &p3);
    insert(tree, &p4);
    insert(tree, &p5);
    insert(tree, &p6);
    insert(tree, &p7);
    insert(tree, &p8);
    insert(tree, &p9);
    insert(tree, &p10);

    print_tree(tree);

    return 0;
}