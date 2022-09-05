# Algorithm U4 -- divide

## 1 InsertionSort

往前看 前面是排好序的 试图插入

### 1.1 Shifting Vacancy

**为待插入的元素找到合适的位置**（到一个已经排好序的序列中）

比x小的数在原位置

比x大的数

![1646029603744](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\1646029603744.png)

## 2 quick sort

Hard divide, Easy combination

与pivot比较 分成大段小段 递归解决

> **pivot**  1  
> ![img](file:///C:/Users/Lenovo/AppData/Local/Temp/Lingoes/Translator/lingoes-cn/dict/temp/D4722835273E184582F2D24696A738EA/res_i_95D5C9C1.png)a  central point or pin on which something balances or turns

### 2.1 Partition

![1646029951197](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\1646029951197.png)

![1646016342416](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\1646016342416.png)

### 2.2 example

pivot 在前 与最后的比

20更小 与pivot交换 交换后 方向变化 和前面的比

14 更小 确实在前 不变

62 更大 与pivot换  交换后 方向变化 和后面的比

84 更大 不变

33 更小 与p换 交换后 方向变化 和前面的比

51 更大 与p交换 交换后 方向变化 和后面的比

96 75 更大 结束

![1646015970768](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\1646015970768.png)



### 2.3 Average-case Analysis

p40

## 3 Merge sort

### 3.1 The MergeSortD&C

在on的时间内合起来就可nlogn

- Max-sum subsequence 最大和字串 跨越问题

- Finding the frequent element 找频率最多的元素---找出所有频率>n/k的元素
- Find the nearest two points on the plane 平面上的二元关系

- Counting inversions
- 大整数相乘 矩阵相乘
- 。。。。。。

### 3.2 Worst-case analysis of MergeSort

p44

### 3.3 Lower Bounds for comparison-based sorting

最优

Worst-ca se
Average-case