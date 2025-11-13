#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 存放期數的二進位檔案
#define COUNTER_FILE "counter.bin"
// 樂透檔案的前綴
#define LOTTO_PREFIX "lotto"
// 每次開獎產生幾組號碼
#define NUM_SETS 5
// 每組號碼有幾個數字 (範例中為 6+1 = 7 個)
#define NUM_PER_SET 7
// 樂透號碼最大值
#define MAX_LOTTO_NUM 49

/*
 * 檢查一個數字是否已經存在於陣列中
 * (用於產生不重複的號碼)
 */
int is_duplicate(int* arr, int length, int value) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == value) {
            return 1; // 1 代表 true (重複)
        }
    }
    return 0; // 0 代表 false (不重複)
}

/*
 * 產生一組樂透號碼 (7個不重複數字)
 * * * ！！！注意！！！
 * 這裡是模擬的 hw3 邏輯。
 * 您應該將您原始 hw3 產生號碼的核心程式碼
 * 放到這個函數中。
 * * */
void generate_lotto_set(int* set) {
    for (int i = 0; i < NUM_PER_SET; i++) {
        int temp_num;
        do {
            temp_num = (rand() % MAX_LOTTO_NUM) + 1;
        } while (is_duplicate(set, i, temp_num));
        set[i] = temp_num;
    }
}

/*
 * 讀取、更新並回傳新的期數
 */
int get_and_update_counter() {
    int counter = 0;
    FILE *file;

    // 1. 嘗試以 "rb" (讀取二進位) 模式開啟檔案
    file = fopen(COUNTER_FILE, "rb");

    if (file == NULL) {
        // 檔案不存在 (如提示所述，第一次是零)
        // 所以新的期數是 1
        counter = 1;
    } else {
        // 檔案存在，讀取目前的數字
        fread(&counter, sizeof(int), 1, file);
        fclose(file);
        // 將期數加 1
        counter++;
    }

    // 2. 以 "wb" (寫入二進位) 模式開啟檔案
    //    (這會覆蓋掉舊檔案)
    file = fopen(COUNTER_FILE, "wb");
    if (file == NULL) {
        perror("錯誤：無法寫入 counter.bin");
        return -1; // 回傳錯誤
    }

    // 3. 將新的期數寫入檔案
    fwrite(&counter, sizeof(int), 1, file);
    fclose(file);

    // 4. 回傳新的期數
    return counter;
}

int main() {
    // 初始化隨機數種子
    srand(time(NULL));

    // 1. 取得並更新期數
    int issue_number = get_and_update_counter();
    if (issue_number == -1) {
        return 1; // 寫入 counter 失敗
    }

    // 2. 根據期數產生檔案名稱
    char filename[50];
    sprintf(filename, "%s[%05d].txt", LOTTO_PREFIX, issue_number);

    // 3. 開啟新的樂透檔案
    FILE *lotto_file = fopen(filename, "w");
    if (lotto_file == NULL) {
        perror("錯誤：無法建立樂透檔案");
        return 1;
    }

    // 4. 取得目前時間 (如簡報範例)
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[100];
    // 格式化時間字串
    strftime(time_str, sizeof(time_str), "%a %b %d %H:%M:%S %Y", t);

    // 5. 寫入檔案標頭 (如簡報範例)
    fprintf(lotto_file, "======== lotto649 =========\n");
    fprintf(lotto_file, "=======+ No.%05d +========\n", issue_number);
    fprintf(lotto_file, "= %s =\n", time_str);

    // 6. 產生並寫入 5 組樂透號碼
    int lotto_set[NUM_PER_SET];
    for (int i = 0; i < NUM_SETS; i++) {
        // 產生一組號碼 (7個數字)
        generate_lotto_set(lotto_set);

        fprintf(lotto_file, "[%d]:", i + 1);
        for (int j = 0; j < NUM_PER_SET; j++) {
            fprintf(lotto_file, " %02d", lotto_set[j]);
        }
        fprintf(lotto_file, "\n");
    }

    // 7. 寫入檔案結尾
    fprintf(lotto_file, "======== csie@CGU =========\n");

    // 8. 關閉檔案並顯示訊息
    fclose(lotto_file);
    printf("已產生檔案: %s\n", filename);

    return 0;
}
