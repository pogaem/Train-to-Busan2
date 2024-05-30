#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//파라미터
#define LEN_MIN 15 //기차 길이
#define LEN_MAX 50
#define STM_MIN 0 //마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 //확률
#define PROB_MAX 90
#define AGGRO_MIN 0 //어그로 범위
#define AGGRO_MAX 5

//마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

//좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGEOK 2

//마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int main(void) {

    //인트로
    printf("                o  o  O  O\n");
    printf("          , _____  ____    0\n");
    printf("          |      ＼_|[]|___Y   <부산헹>\n");
    printf("          |_______|__|_|__ | \n");
    printf("========== oo--oo == oo--OOO＼＼==========\n");
    printf("\n");

    //입력 받기
    int length;
    while (1) {
        printf("train lenght(%d~%d)>> ", LEN_MIN, LEN_MAX);
        scanf_s("%d", &length);
        if (LEN_MIN <= length && length <= LEN_MAX)
            break;
    }
    int stm;
    while (1) {
        printf("madomgseok stamina(%d~%d)>> ", STM_MIN, STM_MAX);
        scanf_s("%d", &stm);
        if (STM_MIN <= stm && stm <= STM_MAX)
            break;
    }
    int prob;
    while (1) {
        printf("percentile probability 'p'(%d~%d)>> ", PROB_MIN, PROB_MAX);
        scanf_s("%d", &prob);
        if (PROB_MIN <= prob && prob <= PROB_MAX)
            break;
    }
    printf("\n");

    //열차 초기 상태 출력
    if (length >= LEN_MIN && length <= LEN_MAX) {
        if (prob >= PROB_MIN && prob <= PROB_MAX) {
            for (int i = 0; i < length; i++) { //1번째줄
                printf("#");
            }
            printf("\n");
            for (int i = 0; i < length; i++) { //2번째줄
                if (i == 0) {
                    printf("#");
                }
                else if (i == (length - 1)) {
                    printf("#");
                }
                else if (i == (length - 2)) {
                    printf("M");
                }
                else if (i == (length - 3)) {
                    printf("Z");
                }
                else if (i == (length - 4)) {
                    printf(" ");
                }
                else if (i == (length - 5)) {
                    printf(" ");
                }
                else if (i == (length - 6)) {
                    printf("C");
                }
                else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        for (int i = 0; i < length; i++) { //3번째줄
            printf("#");
        }
        printf("\n\n");
    }

    srand((unsigned int)time(NULL));

    int C = length - 6;
    int Z = length - 3;
    int M = length - 2;
    //부산헹(1)의 K는 OC, T는 OZ로 변경
    int OC = C;
    int OZ = Z;
    int OM = M;
    int move;
    int Caggro = 1;
    int OCaggro = Caggro;
    int Maggro = 1;
    int OMaggro = Maggro;
    int i;
    int count = 1;
    int zombie_pulled = 0;

    int citizen = rand() % 100;
    int zombie = rand() % 100;
    int pull = rand() % 100;

    //턴 시작
    while (1) {
        //2-3.이동 페이즈

        //시민 이동 규칙
        if (citizen <= (100 - prob)) {
            C--;
        }
        else if (citizen <= prob) {
            C = C;
        }
        //좀비 이동 규칙
        if (count % 2 == 0) {
            Z = Z;
        }
        else if (zombie <= prob) {
            if (Maggro > Caggro) {
                if (M - Z == 1) {
                    Z = Z;
                }
                else {
                    Z++;
                }
            }
            else {
                Z--;
            }
        }
        //상태 출력
        for (i = 0; i < length; i++) { //1번째줄
            printf("#");
        }
        printf("\n");
        for (i = 0; i < length; i++) { //2번째줄
            if (i == 0) {
                printf("#");
            }
            else if (i == (length - 1)) {
                printf("#");
            }
            else if (i == M) {
                printf("M");
            }
            else if (i == Z) {
                printf("Z");
            }
            else if (i == C) {
                printf("C");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
        for (i = 0; i < length; i++) { //3번째줄
            printf("#");
        }
        printf("\n\n");
        //시민 이동 출력
        if (C != OC) { //시민 이동
            Caggro++;
            printf("citizen: %d -> %d ", OC, C);
            if (Caggro > AGGRO_MAX) {
                Caggro = AGGRO_MAX;
                printf("(aggro: %d -> %d)\n", OCaggro, Caggro);
            }
            else {
                printf("(aggro: %d -> %d)\n", OCaggro, Caggro);
            }
        }
        else if (C == OC) { //시민 stay
            Caggro--;
            printf("citizen: stay %d ", OC);
            if (Caggro < AGGRO_MIN) {
                Caggro = AGGRO_MIN;
                printf("(aggro: %d -> %d)\n", OCaggro, Caggro);
            }
            else {
                printf("(aggro: %d -> %d)\n", OCaggro, Caggro);
            }
        }
        //좀비 이동 출력
        if (Z != OZ) { //좀비 이동
            printf("zombie: %d -> %d", OZ, Z);
        }
        else if (Z == OZ || M - Z == 1) { //좀비 stay
            printf("zombie: stay %d", OZ);
        }
        if (count % 2 == 0 || zombie_pulled == 1) { //좀비 2턴, 붙들기 stay 표시
            printf("(cannot move)");
            zombie_pulled = 0;
        }
        printf("\n\n");

        if (Z - C == 1)
            break;

        //마동석 이동 입력
        while (1) {
            if (M - Z != 1) {
                printf("madongseok move(%d:stay, %d:left)>> ", MOVE_STAY, MOVE_LEFT);
            }
            else if (M - Z == 1) {
                printf("madongseok move(%d:stay)>> ", MOVE_STAY);
            }
            scanf_s("%d", &move);
            if (MOVE_STAY == move || MOVE_LEFT == move)
                break;
        }
        if (move == MOVE_STAY) {
            M = M;
        }
        else if (move == MOVE_LEFT) {
            M--;
        }

        //상태 출력
        for (i = 0; i < length; i++) { //1번째줄
            printf("#");
        }
        printf("\n");
        for (i = 0; i < length; i++) { //2번째줄
            if (i == 0) {
                printf("#");
            }
            else if (i == (length - 1)) {
                printf("#");
            }
            else if (i == M) {
                printf("M");
            }
            else if (i == Z) {
                printf("Z");
            }
            else if (i == C) {
                printf("C");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
        for (i = 0; i < length; i++) { //3번째줄
            printf("#");
        }
        printf("\n\n");

        //마동석 이동 출력
        if (M != OM) { //마동석 이동
            Maggro++;
            printf("madongseok: %d -> %d ", OM, M);
            if (Maggro > AGGRO_MAX) {
                Maggro = AGGRO_MAX;
            }
            printf("(aggro: %d -> %d,", OMaggro, Maggro);
            printf(" stamina: %d)\n", stm);
        }
        else if (M == OM) { //마동석 stay
            Maggro--;
            printf("madongseok: stay %d ", OM);
            if (Maggro < AGGRO_MIN) {
                Maggro = AGGRO_MIN;
            }
            printf("(aggro: %d -> %d,", OMaggro, Maggro);
            printf(" stamina: %d)\n", stm);
        }
        OMaggro = Maggro;
        printf("\n");

        //2-4.행동 페이즈
        //시민 행동 출력
        printf("citizen does noting.\n");
        //좀비 행동 출력
        if (M - Z == 1) {
            if (stm != STM_MIN) {
                printf("zombie attacked madongseok (madongseok stamina: %d -> %d)\n", stm, stm - 1);
                stm = stm - 1;
            }
            else if (stm == STM_MIN) {
                printf("zombie attacked madongseok (madongseok stamina: %d -> %d)\n", stm, stm);
            }
            if (stm <= STM_MIN)
                break;
        }
        else if (Z - C != 1 && M - Z != 1) {
            printf("zombie attacked nobody.\n");
        }
        else if (Z - C == 1 && M - Z == 1) { //둘 다 인접
            if (Caggro < Maggro) {
                printf("zombie attacked madongseok (aggro: %d vs. %d, madongseok stamina: %d -> %d\n)", Caggro, Maggro, stm, stm - 1);
                stm = stm - 1;
                if (stm <= STM_MIN)
                    break;
            }
            else if (Caggro >= Maggro) {
                break;
            }
        }
        if (Z - C == 1)
            break;
        //마동석 행동 입력
        int action;
        while (1) {
            if (M - Z != 1) { //마동석 좀비와 인접하지 않은 경우 입력
                printf("madongseok action(%d.rest, %d.provoke)>> ", ACTION_REST, ACTION_PROVOKE);
            }
            else if (M - Z == 1) { //마동석 좀비와 인접한 경우 입력
                printf("madongseok action(%d.rest, %d.provoke, %d.pull)>> ", ACTION_REST, ACTION_PROVOKE, ACTION_PULL);
            }
            scanf_s("%d", &action);
            if (ACTION_REST == action || ACTION_PROVOKE == action || ACTION_PULL == action)
                M = M;
            break;
        }
        printf("\n");
        //미동석 행동 출력
        //마동석 휴식
        if (action == ACTION_REST) {
            printf("madongseok rests...\n");
            printf("madongseok: %d ", OM);
            Maggro--;
            if (Maggro < AGGRO_MIN) {
                Maggro = AGGRO_MIN;
            }
            printf("(aggro: %d -> %d,", OMaggro, Maggro);

            if (stm < STM_MAX) {
                printf(" stamina: %d -> %d)\n", stm, stm + 1);
                stm = stm + 1;
            }
            else if (stm >= STM_MAX) {
                stm = STM_MAX;
                printf(" stamina: %d -> %d)\n", stm, stm);
            }
        }
        //마동석 도발
        else if (action == ACTION_PROVOKE) {
            printf("madongseok provoked zombie...\n");
            printf("madongseok: %d ", OM);
            Maggro = AGGRO_MAX;
            printf("(aggro: %d -> %d,", OMaggro, Maggro);
            printf(" stamina: %d)\n", stm);
        }
        //마동석 붙들기
        else if (action == ACTION_PULL) {
            if (pull <= (100 - prob)) {
                printf("madongseok pulled zombie... Next turn, it can't move\n");
                zombie_pulled = 1;
            }
            else if (pull <= prob) {
                printf("madongseok failed to pull zombie\n");
            }
            if (Maggro < AGGRO_MAX) {
                Maggro = Maggro + 2;
                if (Maggro >= AGGRO_MAX) {
                    Maggro = AGGRO_MAX;
                }
            }
            if (stm != STM_MIN) {
                printf("madonseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, OMaggro, Maggro, stm, stm - 1);
                stm = stm - 1;
            }
            else if (stm == STM_MIN) {
                printf("madonseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", M, OMaggro, Maggro, stm, stm);
            }
        }
        printf("\n");
        count++;
        OC = C;
        OZ = Z;
        OM = M;
        OCaggro = Caggro;
        OMaggro = Maggro;
        if (OC == 1)
            break;
    }

    //아웃트로
    if (OC == 1) {
        printf("YOU WIN!\nCitizen escaped to the next train\n");
    }
    else if (Z - C == 1) {
        printf("GAME OVER! citizen dead...\n");
    }
    else if (stm <= STM_MIN) {
        printf("GAME OVER!\n");
    }
    else if (Z - C == 1 && M - Z == 1 && Caggro >= Maggro) {
        printf("GAME OVER! citizen dead...\n");
    }

    return 0;
}