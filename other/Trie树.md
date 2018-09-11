1. **Trie树** 即 **字典树** ，其核心思想是 **空间换时间** ，利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的，其缺点是 **空间复杂度** 较高。

2.  **Trie树性质**

* 字符的种数决定每个节点的出度，即nex数组大小
* nex数组的下标代表字符相对于a的相对位置
* 采用标记的方法确定是否为字符串
* 插入、查找的复杂度均为O(len),len为字符串长度

3. **与hash表相比下的优点：**

* 不同的关键字不会产生冲突。
* 只有在允许一个关键字关联多个值的情况下才有类似hash碰撞发生。
* 不用求 hash 值，对短字符串有更快的速度。通常，求hash值也是需要遍历字符串的。
* 可以对关键字按字典序排序。

4. **具体实现**

```c++
const int maxn = int(1e6 + 5);
int a[maxn][26], ct[maxn], k;   //ct记录字符串出现次数（或有无出现）
struct data {                   //另一种字典树的存储方式
    int ct, nex[26];
} p[maxn];

void insert(char *s) {          //插入字符串到字典树中

    int p = 0, id;
    for (char *c = s; *c; c++) {
        id = *c - 'a';
        if (!a[p][id]) a[p][id] = ++k;
        p = a[p][id];
    }
    ct[p]++;
}
int find(char *s) {             //查找有无该字符串，有则返回出现次数

    int p = 0, id;
    for (char *c = s; *c; c++) {
        id = *c - 'a';
        if (!a[p][id]) return -1;
        p = a[p][id];
    }
    return ct[p];
}
```