#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�Ķ����
#define LEN_MIN 15 //���� ����
#define LEN_MAX 50
#define STM_MIN 0 //������ ü��
#define STM_MAX 5
#define PROB_MIN 10 //Ȯ��
#define PROB_MAX 90
#define AGGRO_MIN 0 //��׷� ����
#define AGGRO_MAX 5

//������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

//������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGEOK 2

//������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int main(void) {

    //��Ʈ��
    printf("                o  o  O  O\n");
    printf("          , _____  ____    0\n");
    printf("          |      ��_|[]|___Y   <�λ���>\n");
    printf("          |_______|__|_|__ | \n");
    printf("========== oo--oo == oo--OOO����==========\n");
    printf("\n");

    //�Է� �ޱ�
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

    //���� �ʱ� ���� ���
    if (length >= LEN_MIN && length <= LEN_MAX) {
        if (prob >= PROB_MIN && prob <= PROB_MAX) {
            for (int i = 0; i < length; i++) { //1��°��
                printf("#");
            }
            printf("\n");
            for (int i = 0; i < length; i++) { //2��°��
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
        for (int i = 0; i < length; i++) { //3��°��
            printf("#");
        }
        printf("\n\n");
    }

    srand((unsigned int)time(NULL));

    int C = length - 6;
    int Z = length - 3;
    int M = length - 2;
    //�λ���(1)�� K�� OC, T�� OZ�� ����
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

    //�� ����
    while (1) {
        //2-3.�̵� ������

        //�ù� �̵� ��Ģ
        if (citizen <= (100 - prob)) {
            C--;
        }
        else if (citizen <= prob) {
            C = C;
        }
        //���� �̵� ��Ģ
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
        //���� ���
        for (i = 0; i < length; i++) { //1��°��
            printf("#");
        }
        printf("\n");
        for (i = 0; i < length; i++) { //2��°��
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
        for (i = 0; i < length; i++) { //3��°��
            printf("#");
        }
        printf("\n\n");
        //�ù� �̵� ���
        if (C != OC) { //�ù� �̵�
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
        else if (C == OC) { //�ù� stay
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
        //���� �̵� ���
        if (Z != OZ) { //���� �̵�
            printf("zombie: %d -> %d", OZ, Z);
        }
        else if (Z == OZ || M - Z == 1) { //���� stay
            printf("zombie: stay %d", OZ);
        }
        if (count % 2 == 0 || zombie_pulled == 1) { //���� 2��, �ٵ�� stay ǥ��
            printf("(cannot move)");
            zombie_pulled = 0;
        }
        printf("\n\n");

        if (Z - C == 1)
            break;

        //������ �̵� �Է�
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

        //���� ���
        for (i = 0; i < length; i++) { //1��°��
            printf("#");
        }
        printf("\n");
        for (i = 0; i < length; i++) { //2��°��
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
        for (i = 0; i < length; i++) { //3��°��
            printf("#");
        }
        printf("\n\n");

        //������ �̵� ���
        if (M != OM) { //������ �̵�
            Maggro++;
            printf("madongseok: %d -> %d ", OM, M);
            if (Maggro > AGGRO_MAX) {
                Maggro = AGGRO_MAX;
            }
            printf("(aggro: %d -> %d,", OMaggro, Maggro);
            printf(" stamina: %d)\n", stm);
        }
        else if (M == OM) { //������ stay
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

        //2-4.�ൿ ������
        //�ù� �ൿ ���
        printf("citizen does noting.\n");
        //���� �ൿ ���
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
        else if (Z - C == 1 && M - Z == 1) { //�� �� ����
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
        //������ �ൿ �Է�
        int action;
        while (1) {
            if (M - Z != 1) { //������ ����� �������� ���� ��� �Է�
                printf("madongseok action(%d.rest, %d.provoke)>> ", ACTION_REST, ACTION_PROVOKE);
            }
            else if (M - Z == 1) { //������ ����� ������ ��� �Է�
                printf("madongseok action(%d.rest, %d.provoke, %d.pull)>> ", ACTION_REST, ACTION_PROVOKE, ACTION_PULL);
            }
            scanf_s("%d", &action);
            if (ACTION_REST == action || ACTION_PROVOKE == action || ACTION_PULL == action)
                M = M;
            break;
        }
        printf("\n");
        //�̵��� �ൿ ���
        //������ �޽�
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
        //������ ����
        else if (action == ACTION_PROVOKE) {
            printf("madongseok provoked zombie...\n");
            printf("madongseok: %d ", OM);
            Maggro = AGGRO_MAX;
            printf("(aggro: %d -> %d,", OMaggro, Maggro);
            printf(" stamina: %d)\n", stm);
        }
        //������ �ٵ��
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

    //�ƿ�Ʈ��
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