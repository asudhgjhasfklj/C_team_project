#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME2 "customer.txt"

//고객 구조체 선언
typedef struct {
    int customer_number;
    char name[50];
    char phone_number[20];
}Customer;

//고객 관리 메뉴
void customer_menu(){
	Customer c;
	int menu2;
        printf("\033[0;33m\n고객 관리 항목입니다.\n고객 추가는 1\n고객 수정은 2\n고객 삭제는 3\n고객 목록 출력은 4\n메인 메뉴로 가려면 5을(를) 입력해 주세요\n\033[0m");
        while (1) {
		printf("\033[0;33m\n원하는 항목을 선택하세요: \033[0m");
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
            	printf("\033[0;31m잘못된 입력입니다. 다시 입력해 주세요.\n\033[0m");
        }}}
        
//고객 추가 함수
void add_customer() {
    FILE *fp;
    Customer c;
    // 추가할 고객 정보 입력받기
	printf("추가할 고객 번호: ");
    scanf("%d", &c.customer_number);
    printf("고객 이름: ");
    scanf("%s", c.name);
    printf("전화번호: ");
    scanf("%s", c.phone_number);

    //파일을append로 열기
    fp = fopen(FILENAME2, "a");

    //입력받은 정보를 파일에 저장하기
    fwrite(&c, sizeof(Customer), 1, fp);
    printf("\033[0;32m고객이 추가되었습니다.\n\033[0m");
    fclose(fp);
}
// 고객 수정 함수
void update_customer() {
    FILE *fp;
    Customer c;
    int customer_number;
    // 수정할 고객 번호 입력받기
    printf("수정할 고객 번호: ");
    scanf("%d", &customer_number);

    //파일을read+로 열기
    fp = fopen(FILENAME2, "r+");

    // customer_number로 상품 검색 후 정보 입력
    while (fread(&c, sizeof(Customer), 1, fp)) {
        if (c.customer_number == customer_number) {
            printf("고객 이름: ");
            scanf("%s", c.name);
            printf("전화번호: ");
            scanf("%s", c.phone_number);
    		fseek(fp, -sizeof(Customer), SEEK_CUR);
			//업데이트된 정보를 파일에 기록하기
			fwrite(&c, sizeof(Customer), 1, fp);
    		printf("\033[0;32m고객 정보가 수정되었습니다.\n\033[0m");
			fclose(fp);
    		return;
		}
	}
	printf("\033[0;31m고객을 찾을 수 없습니다\n\033[0m");
    fclose(fp);
	}
//고객 제거 함수
void delete_customer() {
    FILE *fp, *temp;
    Customer c;
    int customer_number;
    int found = 0;
    // 삭제할 고객 번호 입력받기
    printf("삭제할 고객 번호: ");
    scanf("%d", &customer_number);

    //파일을readbinary로 열기
    fp = fopen(FILENAME2, "rb");
    if (fp == NULL) {
        printf("\033[0;31m파일을 열 수 없습니다.\n\033[0m");
        return;
    }
    //쓰기 위해 임시 파일 열기
    temp = fopen("temp2.txt", "wb");
    if (temp == NULL) {
        printf("\033[0;31m임시 파일을 만들지 못했습니다.\n\033[0m");
        fclose(fp);
        return;
    }
    //삭제할 레코드를 제외한 모든 레코드를 임시 파일로 복사
    while (fread(&c, sizeof(Customer), 1, fp)) {
        if (c.customer_number != customer_number) {
            fwrite(&c, sizeof(Customer), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    //임시 파일 이름을 원래 파일 이름으로 변경
    remove(FILENAME2);
    rename("temp2.txt", FILENAME2);

    if (found) {
        printf("\033[0;31m고객이 삭제되었습니다.\n\033[0m");
    } else {
        printf("\033[0;31m고객을 찾을 수 없습니다.\n\033[0m");
    }
}


//고객 목록 출력 함수
void list_customer(){
    FILE *fp;
    Customer c;
    int count = 0;

    //파일을 read로 열기
    fp = fopen(FILENAME2, "r");

    // 각 제품의 정보 읽기 및 출력
    while (fread(&c, sizeof(Customer), 1, fp)) {
        printf("고객 번호: %d\n", c.customer_number);
        printf("고객 이름: %s\n", c.name);
        printf("전화번호: %s\n", c.phone_number);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m고객이 추가되지 않았습니다.\n\033[0m");
    }
}