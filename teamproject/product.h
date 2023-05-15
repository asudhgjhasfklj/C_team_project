#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "products.txt"

//��ǰ ����ü ����
typedef struct {
    int item_number;
    char name[50];
    int price;
}Product;

//��ǰ ���� �޴�
void product_menu(){
	Product p;
	int menu;
        printf("\033[0;36m\n��ǰ ���� �׸��Դϴ�.\n��ǰ �߰��� 1\n��ǰ ������ 2\n��ǰ ������ 3\n��ǰ ��� ����� 4\n���� �޴��� ������ 5��(��) �Է��� �ּ���\n\033[0m");
        while (1) {
		printf("\033[0;36m\n���ϴ� �׸��� �����ϼ���: \033[0m");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                add_product();
				break;
            case 2:
                update_product();
                break;
            case 3:
                delete_product();
                break;
            case 4:
            	list_product();
            	break;
            case 5:
            	main();
            	break;
			default:
            	printf("\033[0;31m�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n\033[0m");
        }}}
// ��ǰ �߰� �Լ�
void add_product() {
    FILE *fp;
    Product p;
    // �߰��� ��ǰ ���� �Է¹ޱ�
	printf("�߰��� ��ǰ ��ȣ: ");
    scanf("%d", &p.item_number);
    printf("��ǰ��: ");
    scanf("%s", p.name);
    printf("����: ");
    scanf("%d", &p.price);

    //������append�� ����
    fp = fopen(FILENAME, "a");

    //�Է¹��� ������ ���Ͽ� �����ϱ�
    fwrite(&p, sizeof(Product), 1, fp);
    printf("\033[0;32m��ǰ�� �߰��Ǿ����ϴ�.\n\033[0m");
    fclose(fp);
}
// ��ǰ ���� �Լ�
void update_product() {
    FILE *fp;
    Product p;
    int item_number;
    // ������ ��ǰ ��ȣ �Է¹ޱ�
	printf("������ ��ǰ ��ȣ: ");
    scanf("%d", &item_number);

    //������read+�� ����
    fp = fopen(FILENAME, "r+");

    // item_number�� ��ǰ �˻� �� ���� �Է�
    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.item_number == item_number) {
            //������Ʈ�� ���� �Է¹ޱ�
            printf("��ǰ��: ");
            scanf("%s", p.name);
            printf("����: ");
            scanf("%d", &p.price);
            fseek(fp, -sizeof(Product), SEEK_CUR);

            //������Ʈ�� ������ ���Ͽ� ����ϱ�
            fwrite(&p, sizeof(Product), 1, fp);
            printf("\033[0;32m��ǰ�� �����Ǿ����ϴ�.\n\033[0m");
            fclose(fp);
            return;
        }
    }
    printf("\033[0;31m��ǰ�� ã�� �� �����ϴ�\n\033[0m");
    fclose(fp);
}
// ��ǰ ���� �Լ�
void delete_product() {
    FILE *fp, *temp;
    Product p;
    int item_number;
    int found = 0;
    // ������ ��ǰ ��ȣ �Է¹ޱ�
	printf("������ ��ǰ ��ȣ: ");
    scanf("%d", &item_number);

    //������readbinary�� ����
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("\033[0;31m������ �� �� �����ϴ�.\n\033[0m");
        return;
    }

    //���� ���� �ӽ� ���� ����
    temp = fopen("temp.txt", "wb");
    if (temp == NULL) {
        printf("\033[0;31m�ӽ� ������ ������ ���߽��ϴ�.\n\033[0m");
        fclose(fp);
        return;
    }

    //������ ���ڵ带 ������ ��� ���ڵ带 �ӽ� ���Ϸ� ����
    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.item_number != item_number) {
            fwrite(&p, sizeof(Product), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    //�ӽ� ���� �̸��� ���� ���� �̸����� ����
    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("\033[0;31m��ǰ�� �����Ǿ����ϴ�.\n\033[0m");
    } else {
        printf("\033[0;31m��ǰ�� ã�� �� �����ϴ�.\n\033[0m");
    }
}
// ��ǰ ��� ��� �Լ�
void list_product(){
    FILE *fp;
    Product p;
    int count = 0;

    // ������read�� ����
    fp = fopen(FILENAME, "r");

    // �� ��ǰ�� ���� �б� �� ���
    while (fread(&p, sizeof(Product), 1, fp)) {
        printf("��ǰ ��ȣ: %d\n", p.item_number);
        printf("��ǰ��: %s\n", p.name);
        printf("����: %d��\n", p.price);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m��ǰ�� �߰����� �ʾҽ��ϴ�.\n\033[0m");
    }
}
