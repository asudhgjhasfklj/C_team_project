#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME2 "customer.txt"

//�� ����ü ����
typedef struct {
    int customer_number;
    char name[50];
    char phone_number[20];
}Customer;

//�� ���� �޴�
void customer_menu(){
	Customer c;
	int menu2;
        printf("\033[0;33m\n�� ���� �׸��Դϴ�.\n�� �߰��� 1\n�� ������ 2\n�� ������ 3\n�� ��� ����� 4\n���� �޴��� ������ 5��(��) �Է��� �ּ���\n\033[0m");
        while (1) {
		printf("\033[0;33m\n���ϴ� �׸��� �����ϼ���: \033[0m");
        scanf("%d", &menu2);
        switch (menu2) {
            case 1:
                add_customer();
				break;
            case 2:
                update_customer();
                break;
            case 3:
                delete_customer();
                break;
            case 4:
            	list_customer();
            	break;
            case 5:
            	main();
            	break;
			default:
            	printf("\033[0;31m�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n\033[0m");
        }}}
        
//�� �߰� �Լ�
void add_customer() {
    FILE *fp;
    Customer c;
    // �߰��� �� ���� �Է¹ޱ�
	printf("�߰��� �� ��ȣ: ");
    scanf("%d", &c.customer_number);
    printf("�� �̸�: ");
    scanf("%s", c.name);
    printf("��ȭ��ȣ: ");
    scanf("%s", c.phone_number);

    //������append�� ����
    fp = fopen(FILENAME2, "a");

    //�Է¹��� ������ ���Ͽ� �����ϱ�
    fwrite(&c, sizeof(Customer), 1, fp);
    printf("\033[0;32m���� �߰��Ǿ����ϴ�.\n\033[0m");
    fclose(fp);
}
// �� ���� �Լ�
void update_customer() {
    FILE *fp;
    Customer c;
    int customer_number;
    // ������ �� ��ȣ �Է¹ޱ�
    printf("������ �� ��ȣ: ");
    scanf("%d", &customer_number);

    //������read+�� ����
    fp = fopen(FILENAME2, "r+");

    // customer_number�� ��ǰ �˻� �� ���� �Է�
    while (fread(&c, sizeof(Customer), 1, fp)) {
        if (c.customer_number == customer_number) {
            printf("�� �̸�: ");
            scanf("%s", c.name);
            printf("��ȭ��ȣ: ");
            scanf("%s", c.phone_number);
    		fseek(fp, -sizeof(Customer), SEEK_CUR);
			//������Ʈ�� ������ ���Ͽ� ����ϱ�
			fwrite(&c, sizeof(Customer), 1, fp);
    		printf("\033[0;32m�� ������ �����Ǿ����ϴ�.\n\033[0m");
			fclose(fp);
    		return;
		}
	}
	printf("\033[0;31m���� ã�� �� �����ϴ�\n\033[0m");
    fclose(fp);
	}
//�� ���� �Լ�
void delete_customer() {
    FILE *fp, *temp;
    Customer c;
    int customer_number;
    int found = 0;
    // ������ �� ��ȣ �Է¹ޱ�
    printf("������ �� ��ȣ: ");
    scanf("%d", &customer_number);

    //������readbinary�� ����
    fp = fopen(FILENAME2, "rb");
    if (fp == NULL) {
        printf("\033[0;31m������ �� �� �����ϴ�.\n\033[0m");
        return;
    }
    //���� ���� �ӽ� ���� ����
    temp = fopen("temp2.txt", "wb");
    if (temp == NULL) {
        printf("\033[0;31m�ӽ� ������ ������ ���߽��ϴ�.\n\033[0m");
        fclose(fp);
        return;
    }
    //������ ���ڵ带 ������ ��� ���ڵ带 �ӽ� ���Ϸ� ����
    while (fread(&c, sizeof(Customer), 1, fp)) {
        if (c.customer_number != customer_number) {
            fwrite(&c, sizeof(Customer), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    //�ӽ� ���� �̸��� ���� ���� �̸����� ����
    remove(FILENAME2);
    rename("temp2.txt", FILENAME2);

    if (found) {
        printf("\033[0;31m���� �����Ǿ����ϴ�.\n\033[0m");
    } else {
        printf("\033[0;31m���� ã�� �� �����ϴ�.\n\033[0m");
    }
}


//�� ��� ��� �Լ�
void list_customer(){
    FILE *fp;
    Customer c;
    int count = 0;

    //������ read�� ����
    fp = fopen(FILENAME2, "r");

    // �� ��ǰ�� ���� �б� �� ���
    while (fread(&c, sizeof(Customer), 1, fp)) {
        printf("�� ��ȣ: %d\n", c.customer_number);
        printf("�� �̸�: %s\n", c.name);
        printf("��ȭ��ȣ: %s\n", c.phone_number);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m���� �߰����� �ʾҽ��ϴ�.\n\033[0m");
    }
}