.. �������ķǵݹ��������

.. post:: Nov 16, 2015
   :tags: binary-tree, algorithm
   :author: Xsoda

���ڶ�����������һ��˼����
============================

żȻ�����Ͽ���һ�����ڶ�������������Ŀ, �ͳ���������һ��. ��Ŀ���£�
����һ������, �жϴӶ����׶�����֮���Ƿ���Ŀ���������.

ʾ��:

  .. graphviz::

     digraph G {
        graph [ordering="out"];
        node [shape=circle];
        5 -> 4;
        5 -> 8
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
     };

����1, 5 + 4 + 11 + 2 == 22

��Ҫ�������жϸ��ڵ㵽Ҷ�ڵ��·����, �����Ľڵ�֮���Ƿ�����������������22��ȵ�·��.
ֻ��ͨ��������������ʵ��, ���������������ִ���Ҳֻ��ʹ���������, ����ͺ���û�а취
��������·������.

�ڶ������ı����㷨�г��õ��еݹ��㷨�ʹ���ջ�ķǵݹ��㷨, ����ʹ�ô��и��ڵ�ķǵݹ��㷨. �������ڵ������븸�ڵ�Ҳ�Ǻ�ջһ���ڻ���ʱ��ȡ���ڵ��, ���߱����޲��.

�ȶ���ڵ�ṹ��:

  .. literalinclude: ./code/binary-tree-iterator-non-recurion.c
     :language: c
     :lines: 5-10

Ȼ�������������Ĺ���д��������:

  .. literalinclude: ./code/binary-tree-iterator-non-recursion.c
     :language: c
     :lines: 51-72
     :emphasize-lines: 60-69

60-69��Ϊ�ؼ��Ļ��ݴ���, �����ǵ�ĳһ�����ڵ����Һ����Ҹ��ڵ㲻�Ǵ��Һ��ӵ�·�����ݱ����Һ��ӻ�û�б�����, �򷵻��Һ���. ����ͼ�нڵ�7�Ѿ�û�����Ӻ��Һ�����, ��һ��Ӧ���ǻ��ݵ��丸�ڵ�11, �ٻ�ȡ���ڵ�2. ���������ڵ�1ʱ, �������Ѿ�û�нڵ���Ա�����, ���ϻ���, ÿ���ڵ㶼���丸�ڵ���Һ���, �Ѿ���������, ֱ�����ڵ�ΪNULL, ��������.

����������Ĺ���ʡ��, ��Դ����\ [#source]_\ . ʹ�����µĴ����������������Ľ�������������Ĺ����Ƿ���ȷ

  .. literalinclude: ./code/binary-tree-iterator-non-recursion.c
     :language: c
     :lines: 74-80

�����������£�

>>> 5 4 11 7 2 8 13 4 1

�����Ľ������ȷ��. �����ڱ��������м��������̣�

  .. literalinclude: ./code/binary-tree-iterator-non-recursion.c
     :language: c
     :lines: 82-104
     :emphasize-lines: 94

���������������ȫ��ͬ, ֻ���ڻ��ݹ����м�ȥ�˽ڵ��ֵ, �ڱ���ʱ���Ͻڵ��ֵ.

  >>> gcc -g binary-tree-iterator-non-recursion.c
  >>> ./a.exe
  5 4 11 7 2 8 13 4 1
  leaf node: 7, path sum: 27
  leaf node: 2, path sum: 22
  leaf node: 13, path sum: 26
  leaf node: 1, path sum: 18

��һƪ���͵�������ô�����������.

  .. [#source] ���Ĳ��Դ���: ./code/binary-tree-iterator-non-recursion.c
