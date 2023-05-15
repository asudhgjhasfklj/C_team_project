#include <stdio.h>
#include <stdlib.h>
#include "product.h" //product menu헤더 파일
#include "customer.h" //customer menu 헤더 파일
#include "order.h" //order menu 헤더 파일

//메인 메뉴
int main() {
    int choice;
    printf("\033[0;32m\n반갑습니다.\n주문 관리 시스템입니다.\n\033[0m");
    printf("\033[0;32m상품 관리를 원하시면 1\n고객 관리를 원하시면 2\n주문 관리를 원하시면 3\n프로그램 종료를 원하시면 4를 입력해 주세요 \033[0m");
    
    do {
        printf("\n\033[0;32m번호를 입력해 주세요: \033[0m");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                product_menu(); //product_menu불러오기
                break;
            case 2:
                customer_menu(); //customer_menu불러오기
                break;
            case 3:
                order_menu(); //order_menu 불러오기
                break;
            case 4:
                printf("프로그램을 종료합니다.\n"); //프로그램 종료
                exit(0);
            default:
                printf("\033[0;31m잘못된 입력입니다. 다시 입력해 주세요.\n\033[0m");
        }}
	while (choice != 4);
    return 0;
}


