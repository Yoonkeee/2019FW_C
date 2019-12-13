
char* cal_minus(char *A, char *B) {  // 뺄셈
    int i, sum, oneA, oneB, carry = 0, exception_minus = 0, A_bigger_abs = 0, length, longer_length;
    char *a, *b;  // A와 B를 바꿀 부분  <<----- B > A 라서 뺄셈시 음수가 될 때
    a = A; b = B;  // X,Y로 받아 A,B로 이름 바꿔서 사용
    char *return_result, doMinus, *temp, *finalResult;
    if(strlen(a) >= strlen(b)) {
        longer_length = strlen(a) + 1;
    } else {
        longer_length = strlen(b) + 1;
    }
    temp = malloc(sizeof(char) * longer_length);
    return_result = malloc(sizeof(char) * longer_length);
    finalResult = malloc(sizeof(char) * longer_length);
    A_bigger_abs = abs_compare(a, b);

    if (a[0] != '-' && b[0] != '-' && abs_compare(b, a)) {
        b = A;
        a = B;
        exception_minus = 1;
    }
    if (a[0] == '-') {
        if (b[0] == '-') {
            if (A_bigger_abs) { // if abs A > abs B => -1 = - (19 - 18)
                a++;
                b++;
                return_result = cal_minus(a, b);
                strcat(finalResult, "-");
                strcat(finalResult, return_result);
                return finalResult;
            } else {  // not A_bigger_abs
                a++;
                b++;
                return_result = cal_minus(b, a);
                return return_result;
            }
        }  // end if(b[0] == '-')
        else { // -1 - 8
            a++;  //X에서 -만 빼기
            return_result = cal_plus(a, b);
            strcat(finalResult, "-");
            strcat(finalResult, return_result);
            return finalResult;
        }
    }  // end if(a[0] == '-')
    else if (b[0] == '-') { // 1 + (-3)
        b++;
        return_result = cal_plus(a, b);
        return return_result;
    }
    //------------------------------------------------------
    if(find_dot(a) > find_dot(b))
        b = fill_zero_int(a, b);
    else if(find_dot(b) > find_dot(a))
        a = fill_zero_int(b, a);
    if(strlen(a) - find_dot(a) > strlen(b) - find_dot(b))
        b = fill_zero_dec(a, b);
    else if(strlen(b) - find_dot(b) > strlen(a) - find_dot(a))
        a = fill_zero_dec(b, a);
    length = strlen(a);
    for (i = 0; i < length - 1; i++, a++, b++) ;  // A와 B의 포인터 위치를 맨 끝으로 이동하여 맨 뒤부터 계산하도록 함
    for (i = length - 1; i >= 0; i--, a--, b--) {  // 계산부
        if (*a == '.' || *b == '.') {  // 소수점을 만나게 되면 점을 찍고 다음 반복 수행
            return_result[i] = '.';
            continue;
        }
        oneA = *a - 48;  // ASCII 값 중 0~9로 위치하도록 보정
        oneB = *b - 48;
        sum = oneA - oneB;  // 뺄셈 수행
        if (carry) {  // 직전 반복 뺼셈에서 carry 발생했을 경우 -1
            sum--;
            carry = 0;  // carry 사용 후 0으로 초기화
        }
        if (sum < 0 && i == 0) {  // 맨 앞자리 뺄셈인데 음수일 경우
            sum *= -1;  // 양수화
            carry++;  // 캐리 ++
        }
        else if (sum < 0) {  // 뺄셈이 음수일 경우
            sum += 10;  // 10을 더하고 캐리 ++
            carry++;
        }
        doMinus = (sum % 10) + 48;  // ASCII 0~9값 설정
        return_result[i] = doMinus;
    }
    if (exception_minus) {
        strcat(temp, "-");
        strcat(temp, return_result);
        printf("Line : %d  , temp : %s \n", __LINE__, temp);
        return temp;
    }
    return_result[strlen(return_result)] = '\0';
    return return_result;
}  // end cal_minus
