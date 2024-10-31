#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct _elem {
	char * a;
	struct _elem* next; /** Самая важная часть, образующая список из структуры */
} elem;

/** Сортировка списка lst, путем вставки каждого его элемента
 * в список result, cur -- текущий элемент отсортированного списка для проверки
 */
int list_sort(elem** result, elem** cur, elem* lst) {
	if ( !lst ) return 0;
	if ( !*cur || strcmp((*cur)->a, lst->a) > 0 ) {
		elem* next = lst->next;
		lst->next = *cur;
		*cur = lst;
		return list_sort(result, result,  next); /* начинаем опять вставлять сначала */
	} else
		return list_sort(result, &(*cur)->next, lst); /* перемещаемя дальше по списку */
}

/** Вставка элемента на нужное место в уже отсортированный список */
int insert_sort(elem** lst, char * a) {
	if (!*lst || (*lst)->a > a) {
		elem* n = malloc(sizeof(elem));
		*n = (elem){a, *lst};
		*lst = n;
		return 0;
	} else
		return insert_sort(&(*lst)->next, a);
}

int print_list(elem* e) {
	if ( e ) {
		printf("%s", e->a);
		return print_list(e->next);
	}
	return 0;
}

void free_list(elem* e) {
	if ( e ) {
		elem* next = e->next;
		free(e->a);
		free(e);
		free_list(next);
	}
}

int main() {
	char * x;
	elem* list = NULL;
	elem* result = NULL;
	char * buf = calloc(100, 1);
	while (fgets(buf, 100, stdin) != NULL) {
		x = strdup(buf);
		elem* n = malloc(sizeof(elem));
		*n = (elem){x, list};
		list = n;
	}
	printf("List:\n");
	print_list(list);
	printf("SOrting\n");
	list_sort(&result, &result, list);
	print_list(result);
	free_list(result);
}
