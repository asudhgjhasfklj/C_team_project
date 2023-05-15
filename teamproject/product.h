#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "products.txt"

//상품 구조체 선언
typedef struct {
    int item_number;
    char name[50];
    int price;
}Product;

//상품 관리 메뉴
void product_menu(){
	Product p;
	int menu;
        printf("\033[0;36m\n상품 관리 항목입니다.\n상품 추가는 1\n상품 수정은 2\n상품 삭제는 3\n상품 목록 출력은 4\n메인 메뉴로 가려면 5을(를) 입력해 주세요\n\033[0m");
        while (1) {
		printf("\033[0;36m\n원하는 항목을 선택하세요: \033[0m");
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
            	printf("\033[0;31m잘못된 입력입니다. 다시 입력해 주세요.\n\033[0m");
        }}}
// 상품 추가 함수
void add_product() {
    FILE *fp;
    Product p;
    // 추가할 상품 정보 입력받기
	printf("추가할 상품 번호: ");
    scanf("%d", &p.item_number);
    printf("상품명: ");
    scanf("%s", p.name);
    printf("가격: ");
    scanf("%d", &p.price);

    //파일을append로 열기
    fp = fopen(FILENAME, "a");

    //입력받은 정보를 파일에 저장하기
    fwrite(&p, sizeof(Product), 1, fp);
    printf("\033[0;32m상품이 추가되었습니다.\n\033[0m");
    fclose(fp);
}
// 상품 수정 함수
void update_product() {
    FILE *fp;
    Product p;
    int item_number;
    // 수정할 상품 번호 입력받기
	printf("수정할 상품 번호: ");
    scanf("%d", &item_number);

    //파일을read+로 열기
    fp = fopen(FILENAME, "r+");

    // item_number로 상품 검색 후 정보 입력
    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.item_number == item_number) {
            //업데이트할 정보 입력받기
            printf("상품명: ");
            scanf("%s", p.name);
            printf("가격: ");
            scanf("%d", &p.price);
            fseek(fp, -sizeof(Product), SEEK_CUR);

            //업데이트된 정보를 파일에 기록하기
            fwrite(&p, sizeof(Product), 1, fp);
            printf("\033[0;32m상품이 수정되었습니다.\n\033[0m");
            fclose(fp);
            return;
        }
    }
    printf("\033[0;31m상품을 찾을 수 없습니다\n\033[0m");
    fclose(fp);
}
// 상품 제거 함수
void delete_product() {
    FILE *fp, *temp;
    Product p;
    int item_number;
    int found = 0;
    // 삭제할 상품 번호 입력받기
	printf("삭제할 상품 번호: ");
    scanf("%d", &item_number);

    //파일을readbinary로 열기
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("\033[0;31m파일을 열 수 없습니다.\n\033[0m");
        return;
    }

    //쓰기 위해 임시 파일 열기
    temp = fopen("temp.txt", "wb");
    if (temp == NULL) {
        printf("\033[0;31m임시 파일을 만들지 못했습니다.\n\033[0m");
        fclose(fp);
        return;
    }

    //삭제할 레코드를 제외한 모든 레코드를 임시 파일로 복사
    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.item_number != item_number) {
            fwrite(&p, sizeof(Product), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    //임시 파일 이름을 원래 파일 이름으로 변경
    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("\033[0;31m상품이 삭제되었습니다.\n\033[0m");
    } else {
        printf("\033[0;31m상품을 찾을 수 없습니다.\n\033[0m");
    }
}
// 상품 목록 출력 함수
void list_product(){
    FILE *fp;
    Product p;
    int count = 0;

    // 파일을read로 열기
    fp = fopen(FILENAME, "r");

    // 각 제품의 정보 읽기 및 출력
    while (fread(&p, sizeof(Product), 1, fp)) {
        printf("상품 번호: %d\n", p.item_number);
        printf("상품명: %s\n", p.name);
        printf("가격: %d원\n", p.price);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m상품이 추가되지 않았습니다.\n\033[0m");
    }
}
