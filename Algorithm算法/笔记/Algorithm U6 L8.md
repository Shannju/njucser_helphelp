# Algorithm U6 logn

## 1. Review

- Selection –warm up
    Max and min 两两一组
    Second largest 回溯loss to max
- Selection –Rank k (median)
    Expected linear time 不均等划分
    Worst-case linear time 强行均等
- Adversary argument
    Lower bound

## 2. logn

### 2.1 要求

每次都要减小一半啊，均等最好，不均等就平均logn，w（n）=n

每次都要减小一半，所以都是有序列

Binary Search 二分查找

### 2.2 Binary search tree (BST)

还记得吗 二叉搜索，左树更小，右树更大

### 2.3 Definition of Red-Black Tree (RBT)

p62 + 笔记

#### RBT 

- 红色不连续
- 黑色叶子高度一样
- 根为黑

#### ARB

- 根为红

#### 递归定义

略	

### RBT operations

  Insertion into a red-black tree
  Deletion from a red-black tree