#include <stdio.h>
#include <string.h>
#include "bPlusTree.h"
#include "parser.h"

// 테스트
int main() {
    
    BPlusTree *tree = createBPlusTree(4);

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
    Pokemon p11 = {144, "Articuno", 85, 100, 85, 95, 125, 85};
    Pokemon p12 = {145, "Zapdos", 90, 90, 85, 125, 90, 100};
    Pokemon p13 = {146, "Moltres", 100, 90, 90, 125, 85, 90};
    Pokemon p14 = {150, "Mewtwo", 110, 106, 90, 154, 90, 130};
    Pokemon p15 = {151, "Mew", 100, 100, 100, 100, 100, 100};

    insertBPlusTree(tree, &p1, p1.hp);
    insertBPlusTree(tree, &p2, p2.hp);
    insertBPlusTree(tree, &p3, p3.hp);
    insertBPlusTree(tree, &p4, p4.hp);
    insertBPlusTree(tree, &p5, p5.hp);
    insertBPlusTree(tree, &p6, p6.hp);
    insertBPlusTree(tree, &p7, p7.hp);
    insertBPlusTree(tree, &p8, p8.hp);
    insertBPlusTree(tree, &p9, p9.hp);
    insertBPlusTree(tree, &p10, p10.hp);
    insertBPlusTree(tree, &p11, p11.hp);
    insertBPlusTree(tree, &p12, p12.hp);
    insertBPlusTree(tree, &p13, p13.hp);
    insertBPlusTree(tree, &p14, p14.hp);
    insertBPlusTree(tree, &p15, p15.hp);

    printAllLeafNodes(tree);

    removeFromBPlusTree(tree, 25);
    removeFromBPlusTree(tree, 6);
    removeFromBPlusTree(tree, 150);

    //메모리 회수

    testSQLParser();

    char c1 = getchar();

    return 0;
}