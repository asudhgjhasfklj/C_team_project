#include <stdio.h>
#include <stdlib.h>
#include "product.h" //product menu��� ����
#include "customer.h" //customer menu ��� ����
#include "order.h" //order menu ��� ����

//���� �޴�
int main() {
    int choice;
    printf("\033[0;32m\n�ݰ����ϴ�.\n�ֹ� ���� �ý����Դϴ�.\n\033[0m");
    printf("\033[0;32m��ǰ ������ ���Ͻø� 1\n�� ������ ���Ͻø� 2\n�ֹ� ������ ���Ͻø� 3\n���α׷� ���Ḧ ���Ͻø� 4�� �Է��� �ּ��� \033[0m");
    
    do {
        printf("\n\033[0;32m��ȣ�� �Է��� �ּ���: \033[0m");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                product_menu(); //product_menu�ҷ�����
                break;
            case 2:
                customer_menu(); //customer_menu�ҷ�����
                break;
            case 3:
                order_menu(); //order_menu �ҷ�����
                break;
            case 4:
                printf("���α׷��� �����մϴ�.\n"); //���α׷� ����
                exit(0);
            default:
                printf("\033[0;31m�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n\033[0m");
        }}
	while (choice != 4);
    return 0;
}


