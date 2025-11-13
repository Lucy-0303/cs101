#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256

int main() {
    int user_nums[3];

    printf("請輸入中獎號碼三個：");
    scanf("%d %d %d", &user_nums[0], &user_nums[1], &user_nums[2]);
    printf("輸入中獎號碼為：%02d %02d %02d\n", user_nums[0], user_nums[1], user_nums[2]);
    printf("以下為中獎彩券：\n");

    FILE *file = fopen("lotto.txt", "r");
    if (file == NULL) {
        perror("錯誤：無法開啟 lotto.txt");
        printf("請確認 lotto.txt 檔案存在於同一個目錄下。\n");
        printf("您可以執行 main2.c 產生一個 lotto[00001].txt，然後將其改名為 lotto.txt 來測試。\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char sale_time_line[MAX_LINE_LENGTH] = ""; // 用來儲存 "售出時間" 那一行

    while (fgets(line, sizeof(line), file)) {

        line[strcspn(line, "\n")] = 0;

        if (strstr(line, "售出時間:") != NULL) {
            strcpy(sale_time_line, line);
        }
        
        if (line[0] == '[') {
            int set_id;
            int lotto_nums[7];

            int parsed_count = sscanf(line, "[%d]: %d %d %d %d %d %d %d", 
                                      &set_id, &lotto_nums[0], &lotto_nums[1], 
                                      &lotto_nums[2], &lotto_nums[3], &lotto_nums[4], 
                                      &lotto_nums[5], &lotto_nums[6]);
            
            if (parsed_count == 8) { 
                int found_match = 0;
                
                for (int i = 0; i < 3; i++) { 
                    for (int j = 0; j < 7; j++) { 
                        if (user_nums[i] == lotto_nums[j]) {
                            found_match = 1;
                            break;
                        }
                    }
                    if (found_match) {
                        break;
                    }
                }
                if (found_match) {
                    printf("%s %s\n", sale_time_line, line);
                }
            }
        }
    }

    fclose(file);
    return 0;
