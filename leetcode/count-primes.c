/***
 * 
统计所有小于非负整数 n 的质数的数量。

示例:

输入: 10
输出: 4
解释: 小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
 * 
 */ 

//最笨的方法，单个检查
int countPrimes(int n){
    int sum = 0;
    bool isPrime;
    //质数的尾数只可能是1,3,5,7
    for (int i = 1; i < n; i += 2) {
        int max = (int)sqrt(i) + 1;
        isPrime = true;
        for (int j = 2; j < max; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime && n > 2) sum += 1;
    }

    return sum;
}

int countPrimes(int n){
    if (n <= 2) return 0;
    bool isPrim[n];
    for (int i = 0; i < n; i++) {
        isPrim[i] = true;
    }

    for (int i = 2; i < n; i++) {
        if (isPrim[i]) {
            for (int j = 2 * i; j < n; j += i) {
                isPrim[j] = false;
            }
        }
    }

    int count = 0;
    for (int i = 2; i < n; i++) {
        if (isPrim[i]) count++;
    }

    return count;
}

int countPrimes(int n){
    if (n <= 2) return 0;

    bool isPrim[n];
    for (int i = 0; i < n; i++) {
        isPrim[i] = true;
    }

    for (int i = 2; i * i < n; i++) {
        if (isPrim[i]) {
            for (int j = i * i; j < n; j += i) {
                isPrim[j] = false;
            }   
        }
    }

    int count = 0;
    for (int i = 2; i < n; i++) {
        if (isPrim[i]) count++;
    }

    return count;
}
