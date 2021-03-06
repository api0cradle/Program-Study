#include "dlist.h"

// define dlist init func
void DlistInit(Dlist *dlist) {
	dlist->size = 0;
	dlist->dlist_head = dlist->dlist_tail = NULL;
}

//define dlist insert next func
bool DlistInsertNextNode(Dlist *dlist, DlistNode *dlist_node, int data) {
	DlistNode *tmp_node;
	tmp_node = (DlistNode *)malloc(sizeof(DlistNode));
	tmp_node->data = data;
	tmp_node->node_prev = tmp_node->node_next = NULL;
	if (dlist->size == 0 && dlist_node == NULL) {
		dlist->dlist_head = dlist->dlist_tail = tmp_node;
		dlist->size++;
		return true;
	}
	if (dlist_node->node_next != NULL) {
		tmp_node->node_next = dlist_node->node_next;
		dlist_node->node_next->node_prev = tmp_node;
		dlist_node->node_next = tmp_node;
		tmp_node->node_prev = dlist_node;		
	} else {
		tmp_node->node_prev = dlist_node;
		dlist_node->node_next = tmp_node;
		dlist->dlist_tail = tmp_node;
	}
	dlist->size++;
	return true;
}

// define dlist insert prev func
bool DlistInsertPrevNode(Dlist *dlist, DlistNode *dlist_node, int data) {
	DlistNode *tmp_node;
	tmp_node = (DlistNode *)malloc(sizeof(DlistNode));
	tmp_node->data = data;
	tmp_node->node_next = tmp_node->node_prev = NULL;
	if (dlist->size == 0 && dlist_node == NULL) {
		dlist->dlist_head = dlist->dlist_tail = tmp_node;
		dlist->size++;
		return true;
	}

	if (dlist_node->node_prev != NULL) {
		tmp_node->node_prev = dlist_node->node_prev;
		tmp_node->node_next = dlist_node;
		dlist_node->node_prev->node_next = tmp_node;
		dlist_node->node_prev = tmp_node;
	} else {
		tmp_node->node_next = dlist_node;	
		dlist_node->node_prev = tmp_node;
		dlist->dlist_head = tmp_node;
	}
	dlist->size++;
	return true;
}

// define dlist remove next func
bool DlistRemoveNextNode(Dlist *dlist, DlistNode *dlist_node, int *data) {
	if (dlist->size <= 1) {
		printf("The dlist is empty or only have one node, can not do remove next operation.\n");
		return false;	
	}
	DlistNode *old_dlist_node = NULL;
	if (dlist_node->node_next != NULL) {
		old_dlist_node = dlist_node->node_next;
		*data = old_dlist_node->data;
		if (old_dlist_node->node_next != NULL) {
			old_dlist_node->node_next->node_prev = dlist_node;
		} else {
			dlist->dlist_tail = dlist_node;
		}
		dlist_node->node_next = old_dlist_node->node_next;
		free(old_dlist_node);
	} else {
		dlist->dlist_tail = dlist_node->node_prev;
		dlist_node->node_prev->node_next = NULL;
		*data = 0;
	}
	dlist->size--;
	return true;
}

// define dlist remove prev func
bool DlistRemovePrevNode(Dlist *dlist, DlistNode *dlist_node, int *data) {
	if (dlist->size <= 1) {
		printf("The dlist is empty or only have one node, can not do remove prev operation.\n");
		return false;
	}
	DlistNode *old_dlist_node = NULL;
	if (dlist_node->node_prev != NULL) {
		old_dlist_node = dlist_node->node_prev;
		*data = old_dlist_node->data;
		if (old_dlist_node->node_prev != NULL) {
			old_dlist_node->node_prev->node_next = dlist_node;
		} else {
			dlist->dlist_head = dlist_node;
		}
		dlist_node->node_prev = old_dlist_node->node_prev;
		free(old_dlist_node);
	} else {
		dlist->dlist_head = dlist_node->node_next;
		dlist_node->node_next->node_prev = NULL;
		*data = 0;
	}
	dlist->size--;
	return true;
}

// define dlist show func
void DlistShow(Dlist *dlist) {
	DlistNode *tmp_node;
	tmp_node = dlist->dlist_head;
	printf("Show the dlist information: \n");
	printf("The dlist head data is %d.\n", tmp_node->data);
	printf("The dlist tail data is %d.\n", dlist->dlist_tail->data);
	printf("The dlist size is %d.\n", dlist->size);
	for (int i=0; i < dlist->size; ++i) {
		printf("\tThe dlist data is %d.\n", tmp_node->data);
		tmp_node = NextNode(tmp_node); 
	}
}

// define dlist destory func
void DlistDestory(Dlist *dlist) {
	DlistNode *tmp_node;
	int *recv_num = (int *)malloc(sizeof(int));
	int size;
	tmp_node = DlistTailNode(dlist);
	size = dlist->size;	
	for (int i = 1; i < size; ++i) {
		DlistRemovePrevNode(dlist, tmp_node, recv_num);
	}
	free(tmp_node);
	free(recv_num);
	printf("The dlist destory complete.\n");		
}
