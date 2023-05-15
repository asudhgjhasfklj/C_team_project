#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME3 "order.txt"

//주문 구조체 선언
typedef struct {
    int order_number;
    char product_name[50];
    int price;
    char customer_name[50];
    char phone_number[20];
} Order;

//주문 관리 메뉴
void order_menu(){
	int menu3;
        printf("\033[0;96m\n주문 관리 항목입니다.\n주문 추가는 1\n주문 수정은 2\n주문 삭제는 3\n주문 목록 출력은 4\n주문 상세 출력은 5\n메인 메뉴로 가려면 6을(를) 입력해 주세요\n\033[0m");
        while (1) {
		printf("\033[0;96m\n원하는 항목을 선택하세요: \033[0m");
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
            	printf("\033[0;31m잘못된 입력입니다. 다시 입력해 주세요.\n\033[0m");
        }}}

//주문 추가 함수
void add_order() {
    FILE *fp;
	Order o;
    // 추가할 주문 정보 입력받기
	printf("주문 번호: ");
    scanf("%d", &o.order_number);
    printf("상품명: ");
    scanf("%s", o.product_name);
    printf("가격: ");
    scanf("%d", &o.price);
    printf("주문자: ");
    scanf("%s", o.customer_name);
    printf("전화번호: ");
    scanf("%s", o.phone_number);

    //파일을append로 열기
    fp = fopen(FILENAME3, "a");

    //입력받은 정보를 파일에 저장하기
    fwrite(&o, sizeof(Order), 1, fp);
    printf("\033[0;32m주문이 추가되었습니다.\n\033[0m");
    fclose(fp);
}
// 주문 수정 함수
void update_order() {
    FILE *fp;
    Order o;
    int order_number;
    // 수정할 주문 정보 입력받기
    printf("수정할 주문 번호: ");
    scanf("%d", &order_number);

    //파일을readbinary로 열기
    fp = fopen(FILENAME3, "r+");

    // order_number로 상품 검색 후 정보 입력
    while (fread(&o, sizeof(Order), 1, fp)) {
        if (o.order_number == order_number) {
            printf("상품명: ");
            scanf("%s", o.product_name);
			printf("가격: ");
            scanf("%d", &o.price);
			printf("주문자: ");
            scanf("%s", o.customer_name);
            printf("전화번호: ");
            scanf("%s", o.phone_number);
    		fseek(fp, -sizeof(Order), SEEK_CUR);
		//업데이트된 정보를 파일에 기록하기		
		fwrite(&o, sizeof(Order), 1, fp);
    	printf("\033[0;32m주문 정보가 수정되었습니다.\n\033[0m");
    	fclose(fp);
    	return;
	}}
	printf("\033[0;31m주문을 찾을 수 없습니다\n\033[0m");
    fclose(fp);
}
//주문 제거 함수
void delete_order() {
    FILE *fp, *temp;
    Order o;
    int order_number;
    int found = 0;
    // 삭제할 주문 번호 입력받기
    printf("삭제할 주문 번호: ");
    scanf("%d", &order_number);

    //파일을readbinary로 열기
    fp = fopen(FILENAME3, "rb");
    if (fp == NULL) {
        printf("\033[0;31m파일을 열 수 없습니다.\n\033[0m");
        return;
    }

    //쓰기 위해 임시 파일 열기
    temp = fopen("temp3.txt", "wb");
    if (temp == NULL) {
        printf("\033[0;31m임시 파일을 만들지 못했습니다.\n\033[0m");
        fclose(fp);
        return;
    }
    //삭제할 레코드를 제외한 모든 레코드를 임시 파일로 복사
    while (fread(&o, sizeof(Order), 1, fp)) {
        if (o.order_number != order_number) {
            fwrite(&o, sizeof(Order), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    //임시 파일 이름을 원래 파일 이름으로 변경
    remove(FILENAME3);
    rename("temp3.txt", FILENAME3);

    if (found) {
        printf("\033[0;31m주문이 삭제되었습니다.\n\033[0m");
    } else {
        printf("\033[0;31m주문을 찾을 수 없습니다.\n\033[0m");
    }
}
//주문 목록 출력 함수
void list_order(){
    FILE *fp;
    Order o;
    int count = 0;

    //파일을 read로 열기
    fp = fopen(FILENAME3, "r");

    // 각 제품의 정보 읽기 및 출력
    while (fread(&o, sizeof(Order), 1, fp)) {
        printf("주문 번호: %d\n", o.order_number);
        printf("상품명: %s\n", o.product_name);
        printf("주문자: %s\n", o.customer_name);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m주문이 추가되지 않았습니다.\n\033[0m");
    }
}
//주문 상세 내역 출력 함수
void detail_order(){
    FILE *fp;
    Order o;
    int count = 0;

    //파일을read로 열기
    fp = fopen(FILENAME3, "r");

    // 각 제품과 고객의  정보 읽기 및 출력
    while (fread(&o, sizeof(Order), 1, fp)) {
        printf("주문 번호: %d\n", o.order_number);
        printf("상품명: %s\n", o.product_name);
	    printf("가격: %d원\n", o.price);
        printf("주문자: %s\n", o.customer_name);
	    printf("전화번호: %s\n", o.phone_number);
        count++;
    }
    fclose(fp);
    if (count == 0) {
        printf("\033[0;31m주문이 추가되지 않았습니다.\n\033[0m");
    }
}