# 一、小技巧
1. `#include<bits/stdc++.h>`包含大多数常用头文件 
2. windows输入EOF	`Enter --> Ctrl+Z --> Enter`
3. 获得程序运行时间：`(double)clock()/CLOCKS_PER_SEC`（在time.h里）
4. 文件输入输出`freopen(“input.txt”,”r”,stdin)；freopen(“output.txt”,”w”,stdout)；`
5. `std::ios::sync_with_stdio(false)`关闭输入输出同步。`std::cin.tie(0)`控制输出同步。从而处理大数据时`std::cin,std::cout`与`scanf,printf`速度几乎相同，节省大量运行时间。
6. c/c++里的64位整型不兼容问题 win下VC6.0声明用 **_int64** ，输出用 **%I64d** ；linux下的gcc/g++声明用 **long long** ，输出用 **%lld** 。win下的其他IDE（包括高版本Visual Studio），声明用以上两种均可，输出用%I64d。
7. STL中vector删除重复元素，并把堆在末尾的重复元素移除（要先排序）`a.erase(unique(a.begin(),a.end()),a.end());`
8. 	`assert(x)` x为0时异常终止程序并提示原因，要加头文件`#include<assert.h>`
9. `template<class Any>` 声明模板Any，可表示任意类型

# 二、string.h	 字符数组
char a[],b[]
* `strlen(a)`					返回a字符串的长度
* `strcat(a,b)`				    b字符串接到a后面
* `strncat(a,b,x)`			    把b的前x个字符接到a后面
* `strcpy(a,b)` 				b字符串复制给a
* `strncpy(a,b,x)`			    b字符串从左往右共x个字符复制给a
* `strcmp(a,b)`			    	按ASCII码值比较大小，a在b后则返回正数，等于即0，否则负数
* `strrev(a)`					把字符串a逆置（倒序）
* `strupr (a)`					字符串中所有小写字母转换为大写
* `strlwr(a)`					字符串中所有大写字母转换为小写
* `strchr(a,’?’)`				返回a中字符?第一次出现的首地址（左往右）
* `strrchr(a,’?’)`				返回a中字符?第一次出现的首地址（右往左）
* `strstr(a,”??”)`				返回a中字符串??第一次出现的首地址（大小写敏感）
* `stristr(a,”??”)`				返回a中字符串??第一次出现的首地址（大小写不敏感）
* `memset(a,’?’,x)`		    	把a的前x个字节的值全部替换为’?’，中间为0表示清空成NULL

# 三、ctype.h		测试字符
* `isdigit(x)`					判断x是否是数字阿拉伯数字，是返回非零，否则返回0，下同
* `isalpha(x)`					判断x是否是英文字母
* `isalnum(x)`					判断x是否是阿拉伯数字或英文字母
* `islower(x)`					判断x是否是小写字母
* `isupper(x)`					判断x是否是大写字母
* `isascii(x)`					判断x是否是ASCII码（0~127）
* `tolower(x)`					若x是大写字母，则返回小写字母
* `toupper(x)`					若x是小写字母，则返回大写字母

# 四、stdlib.h		标准库
char str[] 
* `itoa(n,str,k)`			    	表示把整数n转换成k进制并赋给字符串str
* `atoi(str)`				        返回字符串转换为int型的值
* `atof(str)`				    	返回字符串转换为double型的值
* `atol(str)`				    	返回字符串转换为long型的值
* `atoll(str)`					返回字符串转换为long long型的值
* `malloc(x)`					    分配x个字节的内存空间，返回存储区起始地址的指针，类型为void*，可以强制转换为任何类型的指针
* `calloc(n,x)`				    分配n个大小为x字节的空间，同上
* `realloc(str,x)`				把malloc或calloc分配的str指向的存储空间的大小改为x
* `free(str)`					    释放动态开辟的str指向的内存空间
* `rand()%(y-x+1)+x	`		    随机产生一个[x,y]区间里的数
* `srand((size_t)time(NULL))`		随机数发生器的初始化,用到time.h
* `labs(long x)`				    返回长整型参数的绝对值
* `abort();	`					异常终止程序
* `qsort(a,n,sizeof(int),cmp)`	对序列a快速排序。cmp函数如下：
```c++
int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b; //由小到大排序
    //return *(int *)b - *(int *)a; 由大到小排序
}
```
# 五、stdio.h		标准输入输出
char str[]；FILE *fp；char ch
* `sscanf(str,”%s %d”,str1,&x)`	把字符串str拆分成str1和x
* `sprintf(str,”%s %d”,str1,x)`	把str1和x赋值给字符串str
* `fscanf(fp,”%d”,&x)`			读取文件流fp中一个整数赋给x
* `fprintf(fp,”%s”,str)`			把字符串str存入文件流fp中
* `fgetc(fp)`						返回从文件流中读取的一个字符
* `fputc(ch,fp)	`				把字符ch写入文件流fp中
* `fopen(“c:\\new\\hello.txt”,”r”)	`以只读方式打开hello.txt,返回文件的首地址
* `fclose(fp)`						关闭文件流fp
* `fgets(str,n,fp)`				从字符流中读取n个字符存入str中
* `fputs(str,fp)`					把字符串str存入字符流fp中
* `freopen(“input.txt”,”r”,fp)`	不改变代码的情况下改变输入输出环境，对输入输出流进行重定向
**文件的调用一旦失败，则返回NULL**
**r**		只读方式打开，文件必须存在
**r+**		可读写方式，文件必须存在
**rb+**		读写方式打开二进制文件，文件必须存在
**w**		打开只写文件，文件存在则重写，不存在则新建
**w+** 		打开可读写文件，文件存在则重写，不存在则新建
**a**	 	以附加方式打开只写文件，文件存在则从末尾开始写入，否则新建
**a+**		以附加方式打开可读写文件，文件存在则从末尾开始写入，否则新建

# 六、algorithm		演算法(STL)
int a[n],b[];string str1,str2
* `swap(a,b)`					交换两个对象的值
* `max(a,b)`					返回两者中的较大者
* `min(a,b)	`				返回两者中的较小者
* `sort(a,a+n)	`				把序列按升序排序
* `reverse(a,a+n)`				把序列反转顺序
* `unique(a,a+n)`				删除序列中的重复元素，末尾出现重复
* `remove(a,a+n,x)`			删除序列中等于x的元素，末尾出现重复
* `equal(a,a+n,b)`				若两序列在标志范围内元素都相等，返回true，否则返回false,允许b序列元素比a多
* `fill(a,a+n,x)`				把a序列所有元素替换为x
* `count(a,a+n,x)`				返回序列a中x出现的次数
* `rotate(a,a+x,a+n)`			序列前x项与之后n-x项交换
* `includes(a,a+n,b,b+n)`		若a包含b，则返回true，否则返回false
* `next_permutation(a,a+n)`	按字典序生成下一个排列，若已是降序则返回false，否则返回true
* `lower_bound(a,a+n,x)-a`	返回>=x的第一个元素的迭代器，减去受元素的迭代器即表示数组下标。若x比a[0]小则返回0，若x比a[n-1]大则返回n。（前提：a为非递减序列）
* `upper_bound(a,a+n,x)-a`	返回>x的第一个元素的地址。
* `binary_search(a,a+n,x)`	判断序列中是否有x，返回布尔值

# 七、string		字符串型(STL)
string a,b,c;
* `a.find(b)`					在a中查找子串b第一次出现的位置，查找失败返回std::string::npos，强制转化为int值-1
* `a.rfind(b)`					在a 中查找子串b 最后一次出现的位置，查找失败返回-1，需要强制转化
* `a.find_first_of(b)`			在a中查找b中任一字符第一次出现的位置
* `a.find_first_of(b)`			在a中查找b中任一字符最后一次出现的位置
* `a.compare(b)`				类似于strcmp，比较字符
* `a.assign(b,x,y)`			把char *b的下标自x开始宽为y的字符赋给a
* `a.append(b,x,y)`			把b下标自x开始宽为y的字符接在a后面
* `a.insert(x,b)`				a下标为x处插入b
* `a.replace(x,y,b)`			a下标自x开始宽为y的字符替换为b
* `a.erase(x,y)`				a下标自x开始宽为y的字符删除
* `a.substr(x,y)`				返回a下标自x开始宽为y的全部字符
* `a.size() / a.length()`	返回a的长度
* `a.push_back(‘x’)`			把单个字符x放到a的末尾
* `a.c_str`                     返回char*类型指针

# 八、STL模板
`xxx<xxx>::iterator  p`			正向迭代器`a.begin()，a.end()，p++`
`xxx<xxx>::reverse_iterator  p`	反向迭代器`a.rbegin()，a.rend()，p++`
#### 1. queue		队列（1）
* `queue<int>a`				声明队列
* `priority_queue<int>b`		声明优先队列
#### 2. stack			栈（2）
* `stack<int>a`			声明栈
#### 3. vector		数组/向量（3）
* `vector<int>a(n)`			声明初始大小为n的向量，n可省去
* `vector<int>a(n,x)`			初始大小为n且值都是x的向量
* `vector<int>a(tmp)`			用向量tmp初始化a
* `vector<int>a(tmp.begin(),tmp.end())	`	同上
* `vector<int>a(b,b+n)`		用数组b初始化a
#### 4. set				集合（4）
* `set<int>a`声明集合
#### 5. utility			对组（5）
* `pair<string,int> a`			声明一个对组（有2个元素的结构体）
* `pair<int,pair<int,int> >a`	声明有3个元素的结构体
#### 6. map			映射（6）
* `map<string,int>a`			声明一个从string类（key）到int类（value）的映射，自动按key升序排序
* `multimap<string,int>a`		声明一个映射（允许一个键对应多个值）
#### 7. bitset          二进制数（7）
* `bitset<maxn>a`    声明一个有maxn位的二进制数
* `bitset<maxn>a(x,s,e)` 将x从s位到e位构造二进制数，其余为0（x只能说string类，且每一位都是0或1）
#### 8. complex         复数类(8)
* `complex<double> a(1,2)` 声明一个复数对象,实部虚部分别是1,2

## 具体实现:
* `a.push_back()`				末尾添加元素（3）
* `a.push()`				末尾添加元素（1，2）
* `a.size()	`					返回队列中元素的个数（1，2，3，4，6，7）
* `a.empty()`					判断队列是否为空，返回布尔值（1，2，3，4，6）
* `a.pop()	`					删除第一个元素（1，2）
* `a.front()	`				返回第一个元素的引用（1，3）
* `a.back()`				返回最后一个元素的引用（1，3）
* `a.top()`						返回最后一个元素（2）
* `a.max_size()`				返回最大容量（3，4，6）
* `a.resize(x)	`				把大小更改为x（3，4）
* `a.pop_back()`				末尾删除元素（3）
* `a.begin()`					初始位置的迭代器（3，4，6）
* `a.end()`						末尾位置的迭代器（3，4，6）
* `a.rbegin()	`				末尾位置的反向迭代器（3，4，6）
* `a.rend()	`				初始位置的反向迭代器（3，4，6）
* `a.data()	`				初始位置的指针（3）
* `a.clear()`					清空所有元素（3，4，6）
* `a.assign(b.brgin(),b.end())`	把b复制给a（3）
* `a.insert(x)	`				在a中插入x（4，6）
* `a.insert(a.begin(),n,x)`		在a.begin()前插入n个x，若n省去则插入一个x且返回x的迭代器（3）
* `a.insert(a.begin(),b.begin(),b.end())`在a.begin()前插入b的对应元素（3）
* `a.erase(a.begin(),a.end())`	把区间内的元素删去（3，4，6）
* `a.count(x)	`				返回a中x出现的次数（4，6，7）
* `a.lower_bound(x)`			返回>=x的第一个元素的迭代器（4，6）
* `a.upper_bound(x)`			返回>x的第一个元素的迭代器（4，6）
* `a.find(x)`					返回x元素的迭代器，若无x则返回a.end()（4，6）
* `make_pair(x,y)`			返回一个对组（x,y）,用于给pair赋值（5）
* `a.first`						访问pair的第一个元素（5）
* `a.second`					访问pair的第二个元素（5）
* `a[key]=value`				插入数据（6）
* `a.insert(map<string,int>::value_type("b",2))`		插入数据（6）
* `a.insert(make_pair(“b”,2))`						插入数据（6）
* `a.any()`    判断是二进制数否有一位是1（7）
* `a.none()`判断是否每一位都是0（7）
* `a.flip(n)`第n位取反，省去n则所有位都取反（7）
* `a.set(n)`第n位置为1，省去n则所有位都置为1（7）
* `a.reset(n)`第n位置为1，同上（7）
* `a.to_string()`返回二进制数对应的字符串（7）
* `a.to_ulong()`返回 unsigned long 整数(7)
* `real(a)`返回复数的实部(8)
* `imag(a)`返回复数的虚部(8)
* `abs(a)`返回复数的幅度(8)
* `norm(a)`返回幅度的平方(8)
* `arg(a)`返回复数的弧度(8)
* `conj(a)`返回共轭复数(8)
* `polar(double,double)`极坐标(len,ang)转化为复数(9)

# 九、limits.h		数据类型极值
* `SHRT_MIN`				最小short值
* `SHRT_MAX	`			最大short值
* `USHRT_MAX	`		最大无符号short
* `INT _MIN	`				最小int
* `INT_MAX	`				最大int
* `UINT_MAX	`			最大无符号int
* `LONG_MIN`				最小long
* `LONG_MAX`				最大long
* `ULONG_MAX	`		最大无符号long
* `CHAR_BIT`				每个字符包含位数
* `CHAR_MIN	`			最小字符
* `CHAR_MAX	`			最大字符
* `SCHAR_MIN`				最小又符号字符
* `SCHAR_MAX`			最大有符号字符
* `UCHAR_MAX`			最大无符号字符
* `MB_LEN_MAX	`		多字节字符最多包含的字符数

# 十、iomanip		操纵输入输出
* `cout<<setw(x)<<3`			把3按宽度为x输出（默认右对齐）
* `cout<<setfill('x')	`		填充字符x
* `cout<<left	`				改为左对齐
* `cout<<right`				改为右对齐
* `cout<<dec`					以十进制输出，%d
* `cout<<hex`					以十六进制输出，%x
* `cout<<oct`					以八进制输出，%o
* `cout<<setbase(x)	`		以x进制输出（x只能是8,10,16）
* `cout<<setprecision(x)`		浮点数保留x位有效数字（默认为6）
* `cout<<fixed<<setprecision(x)	`保留小数点后x位

# 十一、fstream		文件输入输出流
open(const char* filename,int mode,int access)打开文件，
如果open函数只有文件名一个参数，则是以读/写普通文件打开。
打开方式（mode）：
* ios::app：　　　 	        以追加的方式打开文件 
* ios::ate：　　　 	        文件打开后定位到文件尾，ios:app就包含有此属性 
* ios::binary：　 		  以二进制方式打开文件，缺省的方式是文本方式。两种方式的区别见前文 
* ios::in：　　　 		    文件以输入方式打开（文件数据输入到内存） 
* ios::out：　　　      	文件以输出方式打开（内存数据输出到文件） 
* ios::nocreate： 	      不建立文件，所以文件不存在时打开失败 
* ios::noreplace：	      不覆盖文件，所以打开文件时如果文件存在失败 
* ios::trunc：　 		      如果文件存在，把文件长度设为0
打开文件的属性取值（access）,可以用“|”或者“+”把以上属性连接起来：
* 0：普通文件，打开访问  
* 1：只读文件  
* 2：隐含文件  
* 4：系统文件 

# 十二、stddef.h		标准宏及类型的定义
* null						NULL
* size_t						unsigned int（sizeof操作符的结果类型）
* ptrdiff_t					int（表示指针相减的结果类型）
* wchar_t					char（表示宽字符类型）


