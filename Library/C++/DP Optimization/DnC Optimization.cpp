/*
Conditions
1) DP 점화식 꼴
D[t][i]=min{k<i}(D[t?1][k]+C[k][i])
2) A[t][i]는 D[t][i]를 만족시키는 최소 k라 할 때 아래 부등식을 만족
A[t][i]≤A[t][i+1]
혹은 비용 C에 대해 C[a][c]+C[b][d]<=C[a][d]+C[b][c]
*/

void do_dp(int t, int s, int e, int p, int q) {
    // D[t][s], D[t][s+1], ..., D[t][e]를 계산하는 함수.
    // (여기서 가능한 k의 범위는 p~q 사이)
 
    if (s > e) return;
 
    int m = (s+e) >> 1;
    // 1. D[t][m]에 대해 가능한 답을 선형 시간에 계산
    D[t][m] = 2e9;
    for (int k=p;k<=q&&k<m;k++){
        int v = D[t-1][k] + C[k][m];
        if (D[t][m] > v)
            D[t][m] = v, K[t][m] = k;
    }
    // 2. D[t][s], ..., D[t][m-1]에 대해서 계산하기 위한 재귀 호출
    do_dp(t, s, m-1, p, K[t][m]);
    // 3. D[t][m+1], ..., D[t][e]에 대해서 계산하기 위한 재귀 호출
    do_dp(t, m+1, e, K[t][m], q);
 
    // 2, 3에 대해 가능한 k의 후보는 조건에 의해 줄어든다.
}