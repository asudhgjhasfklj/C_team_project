#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME3 "order.txt"

//�ֹ� ����ü ����
typedef struct {
    int order_number;
    char product_name[50];
    int price;
    char customer_name[50];
    char phone_number[20];
} Order;

//�ֹ� ���� �޴�
void order_menu(){
	int menu3;
        printf("\033[0;96m\n�ֹ� ���� �׸��Դϴ�.\n�ֹ� �߰��� 1\n�ֹ� ������ 2\n�ֹ� ������ 3\n�ֹ� ��� ����� 4\n�ֹ� �� ����� 5\n���� �޴��� ������ 6��(��) �Է��� �ּ���\n\033[0m");
        while (1) {
		printf("\033[0;96m\n���ϴ� �׸��� �����ϼ���: \033[0m");
        scanf("%d", &menu3);
        switch (menu3) {
            case 1:
                add_order();
                break;
            case 2:
                update_order();
                break;
            case 3:
                delete_order();
                break;
            case 4:
            	list_order();
            	break;
            case 5:
            	detail_order();
            	break;
			case 6:
            	main();
            	break;
			default:
            	printf("\033[0;31m�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n\033[0m");
        }}}

//�ֹ� �߰� �Լ�
void add_order() {
    FILE *fp;
	Order o;
    // �߰��� �ֹ� ���� �Է¹ޱ�
	printf("�ֹ� ��ȣ: ");
    scanf("%d", &o.order_number);
    printf("��ǰ��: ");
    scanf("%s", o.product_name);
    printf("����: ");
    scanf("%d", &o.price);
    printf("�ֹ���: ");
    scanf("%s", o.customer_name);
    printf("��ȭ��ȣ: ");
    scanf("%s", o.phone_number);

    //������append�� ����
    fp = fopen(FILENAME3, "a");

    //�Է¹��� ������ ���Ͽ� �����ϱ�
    fwrite(&o, sizeof(Order), 1, fp);
    printf("\033[0;32m�ֹ��� �߰��Ǿ����ϴ�.\n\033[0m");
    fclose(fp);
}
// �ֹ� ���� �Լ�
void update_order() {
    FILE *fp;
    Order o;
    int order_number;
    // ������ �ֹ� ���� �Է¹ޱ�
    printf("������ �ֹ� ��ȣ: ");
    scanf("%d", &order_number);

    //������readbinary�� ����
    fp = fopen(FILENAME3, "r+");

    // order_number�� ��ǰ �˻� �� ���� �Է�
    while (fread(&o, sizeof(Order), 1, fp)) {
        if (o.order_number == order_number) {
            printf("��ǰ��: ");
            scanf("%s", o.product_name);
			printf("����: ");
            scanf("%d", &o.price);
			printf("�ֹ���: ");
            scanf("%s", o.customer_name);
            printf("��ȭ��ȣ: ");
            scanf("%s", o.phone_number);
    		fseek(fp, -sizeof(Order), SEEK_CUR);
		//������Ʈ�� ������ ���Ͽ� ����ϱ�		
		fwrite(&o, sizeof(Order), 1, fp);
    	printf("\033[0;32m�ֹ� ������ �����Ǿ����ϴ�.\n\033[0m");
    	fclose(fp);
    	return;
	}}
	printf("\033[0;31m�ֹ��� ã�� �� �����ϴ�\n\033[0m");
    fclose(fp);
}
//�ֹ� ���� �Լ�
void delete_order() {
    FILE *fp, *temp;
    Order o;
    int order_number;
    int found = 0;
    // ������ �ֹ� ��ȣ �Է¹ޱ�
    printf("������ �ֹ� ��ȣ: ");
    scanf("%d", &order_number);

    //������readbinary�� ����
    fp = fopen(FILENAME3, "rb");
    if (fp == NULL) {
        printf("\033[0;31m������ �� �� �����ϴ�.\n\033[0m");
        return;
    }

    //���� ���� �ӽ� ���� ����
    temp = fopen("temp3.txt", "wb");
    if (temp == NULL) {
        printf("\033[0;31m�ӽ� ������ ������ ���߽��ϴ�.\n\033[0m");
        fclose(fp);
        return;
    }
    //������ ���ڵ带 ������ ��� ���ڵ带 �ӽ� ���Ϸ� ����
    while (fread(&o, sizeof(Order), 1, fp)) {
        if (o.order_number != order_number) {
            fwrite(&o, sizeof(Order), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    //�ӽ� ���� �̸��� ���� ���� �̸����� ����
    remove(FILENAME3);
    rename("temp3.txt", FILENAME3);

    if (found) {
        printf("\033[0;31m�ֹ��� �����Ǿ����ϴ�.\n\033[0m");
    } else {
        printf("\033[0;31m�ֹ��� ã�� �� �����ϴ�.\n\033[0m");
    }
}
//�ֹ� ��� ��� �Լ�
void list_order(){
    FILE *fp;
    Order o;
    int count = 0;

    //������ read�� ����
    fp = fopen(FILENAME3, "r");

    // �� ��ǰ�� ���� �б� �� ���
    while (fread(&o, sizeof(Order), 1, fp)) {
        printf("�ֹ� ��ȣ: %d\n", o.order_number);
        printf("��ǰ��: %s\n", o.product_name);
        printf("�ֹ���: %s\n", o.customer_name);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m�ֹ��� �߰����� �ʾҽ��ϴ�.\n\033[0m");
    }
}
//�ֹ� �� ���� ��� �Լ�
void detail_order(){
    FILE *fp;
    Order o;
    int count = 0;

    //������read�� ����
    fp = fopen(FILENAME3, "r");

    // �� ��ǰ�� ����  ���� �б� �� ���
    while (fread(&o, sizeof(Order), 1, fp)) {
        printf("�ֹ� ��ȣ: %d\n", o.order_number);
        printf("��ǰ��: %s\n", o.product_name);
	    printf("����: %d��\n", o.price);
        printf("�ֹ���: %s\n", o.customer_name);
	    printf("��ȭ��ȣ: %s\n", o.phone_number);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m�ֹ��� �߰����� �ʾҽ��ϴ�.\n\033[0m");
    }
}