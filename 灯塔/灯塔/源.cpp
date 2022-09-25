//#include<cstdio>
//#include<cstring>
//#define MAXN 4000005
//#define ll long long 
//using namespace std;
//
//struct node {
//    ll x;
//    ll y;
//} tower[MAXN];
//ll des[MAXN];
//struct node des1[MAXN];
//int N;
//ll num;
//void merg(int l, int mid, int r)
//{
//    int i, j;
//    int k;
//    i = l;
//    k = l;
//    j = mid + 1;
//    while (i <= mid && j <= r) {
//        if (tower[i].x < tower[j].x) {
//            des1[k].x = tower[i].x;
//            des1[k++].y = tower[i++].y;
//        }
//        else {
//            des1[k].x = tower[j].x;
//            des1[k++].y = tower[j++].y;
//        }
//    }
//    while (i <= mid) {
//        des1[k].x = tower[i].x;
//        des1[k++].y = tower[i++].y;
//    }
//    while (j <= r) {
//        des1[k].x = tower[j].x;
//        des1[k++].y = tower[j++].y;
//    }
//
//    for (i = l; i <= r; i++) {
//        tower[i].x = des1[i].x;
//        tower[i].y = des1[i].y;
//    }
//}
//void msort(int l, int r) {
//    if (l >= r - 1)
//    {
//        if (tower[l].x > tower[r].x) {
//            int x, y;
//            x = tower[l].x;
//            y = tower[l].y;
//            tower[l].x = tower[r].x;
//            tower[l].y = tower[r].y;
//            tower[r].x = x;
//            tower[r].y = y;
//        }
//        return;
//    }
//    int mid = (l + r) >> 1;
//    msort(l, mid);
//    msort(mid + 1, r);
//    merg(l, mid, r);
//}
//
//void merge1(int l, int mid, int r)
//{
//    int i, j;
//    ll cnt = 0;
//    int k = l;
//    i = l;
//    j = mid + 1;
//    while (i <= mid && j <= r) {
//        if (tower[i].y < tower[j].y) {
//            des[k++] = tower[i++].y;
//            cnt += r - j + 1;
//        }
//        else {
//            des[k++] = tower[j++].y;
//        }
//    }
//    while (i <= mid)
//        des[k++] = tower[i++].y;
//    while (j <= r)
//        des[k++] = tower[j++].y;
//    for (i = l; i <= r; i++) {
//        tower[i].y = des[i];
//    }
//    num += cnt;
//}
//void get_num(int l, int r)
//{
//    if (l >= r - 1) {
//        if (tower[l].y < tower[r].y) {
//            num++;
//        }
//        else {
//            int temp = tower[l].y;
//            tower[l].y = tower[r].y;
//            tower[r].y = temp;
//        }
//        return;
//    }
//    int mid = (l + r) >> 1;
//    get_num(l, mid);
//    get_num(mid + 1, r);
//    merge1(l, mid, r);
//}
//
//int main()
//{
//    scanf("%d", &N);
//    num = 0;
//    for (int i = 0; i < N; i++)
//    {
//        scanf("%lld %lld", &tower[i].x, &tower[i].y);
//    }
//    msort(0, N - 1);
//    get_num(0, N - 1);
//    printf("%lld\n", num);
//
//
//    return 0;
//}