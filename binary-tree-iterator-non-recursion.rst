.. 二叉树的非递归先序遍历

.. post:: Nov 16, 2015
   :tags: binary-tree, algorithm
   :author: Xsoda

关于二叉树遍历的一道思考题
============================

偶然在网上看到一道关于二叉树的面试题目, 就尝试着做了一下. 题目如下：
给出一二叉树, 判断从顶到底段数据之和是否与目标数字相等.

示例:

.. graphviz::

   digraph G {
      graph [ordering="out"];
      node [shape=circle];
      5 -> 4;
      5 -> 8;
      4 -> 11;
      null0 [shape=point];
      4 -> null0;
      11 -> 7;
      11 -> 2;
      8 -> 13;
      node4 [label="4"];
      8 -> node4;
      null1 [shape=point];
      node4 -> null1;
      node4 -> 1;
   }

返回\ ``1``\ , 表示可以找到一个叶子节点并且从根节点到此节点的值的和等于\ ``22``\ .

需要我们来判断根节点到叶节点的路径中, 经过的节点之和是否有与所给定的数字\ ``22``\ 相等的路径.
只能通过遍历二叉树来实现, 遍历二叉树的三种次序也只能使用先序遍历, 中序和后序都不便于
处理类似路径问题.

在二叉树的遍历算法中常用的有递归算法和带有栈的非递归算法, 这里使用带有父节点的非递归算法. 二叉树节点中引入父节点也是
和栈一样在回溯时获取父节点, 保存路径, 二者本质无差别.

先定义节点结构体:

.. literalinclude:: ./code/binary-tree-iterator-non-recursion.c
   :linenos:
   :encoding: utf-8
   :language: c
   :lines: 5-10

然后根据先序遍历的规则写出遍历器:

.. literalinclude:: ./code/binary-tree-iterator-non-recursion.c
   :linenos:
   :encoding: utf-8
   :language: c
   :lines: 51-72
   :emphasize-lines: 60-69

60-69行为关键的回溯代码, 规则是当某一个父节点有右孩子且父节点不是从右孩子的路径回溯表明右孩子还没有遍历过, 则返回右孩子.
例如图中节点7已经没有左孩子和右孩子了, 下一步应该是回溯到其父节点11, 再获取到节点2. 当遍历到节点1时, 很明显已经没有节点
可以遍历了, 往上回溯, 每个节点都是其父节点的右孩子, 已经遍历过了, 直至父节点为\ ``NULL``\ , 遍历结束.

构造二叉树的过程省略, 见源代码\ [#source]_\ . 使用如下的代码先输出先序遍历的结果来看看遍历的过程是否正确

.. literalinclude:: ./code/binary-tree-iterator-non-recursion.c
   :linenos:
   :encoding: utf-8
   :language: c
   :lines: 74-80

编译后输出如下：

  >>> ./a.exe
  5 4 11 7 2 8 13 4 1

遍历的结果是正确的. 下面在遍历过程中加入计算过程：

.. literalinclude:: ./code/binary-tree-iterator-non-recursion.c
   :linenos:
   :encoding: utf-8
   :language: c
   :lines: 82-104
   :emphasize-lines: 94

基本过程与遍历完全相同, 只是在回溯过程中减去了节点的值, 在遍历时加上节点的值.

  >>> gcc -g binary-tree-iterator-non-recursion.c
  >>> ./a.exe
  5 4 11 7 2 8 13 4 1
  leaf node: 7, path sum: 27
  leaf node: 2, path sum: 22
  leaf node: 13, path sum: 26
  leaf node: 1, path sum: 18

第一篇博客耽搁了这么久总算完成了.

.. [#source] 本文测试代码: `<../_static/binary-tree-iterator-non-recursion.c>`_
