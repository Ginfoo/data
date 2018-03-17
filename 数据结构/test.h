#pragma once
typedef struct treeNode {
	char e;
	struct treeNode* left;
	struct treeNode* right;
};
void insertSort(int a[], int len) {
	int left = 0; int right = len - 1;
	for (int i = left; i <= right; i++) {
		if (a[i] < a[i - 1]) {
			int key = a[i];
			int j = i - 1;
			do {
				a[j + 1] = a[j];
				j = j - 1;
			} while (j >= left && key < a[j]);
			a[j + 1] = key;
		}
	}
}