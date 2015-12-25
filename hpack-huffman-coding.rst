.. HPACK中的霍夫曼编码

.. post:: Dec 26, 2015
   :tags: http2.0, algorithm, huffman
   :author: Xsoda

HPACK中的霍夫曼编码
=======================

\ ``HTTP2.0``\ [#http2.0]_\ 中头部采用了二进制格式，具体编码在\ ``HPACK``\ [#hpack]_\ 也已经详细解释了。
\ ``HPACK``\ 中对于字符串使用了霍夫曼编码\ [#huffman]_\ 来让传输更有效率，但是对于霍夫曼的解码过程一直没想
到如何仅仅使用查表的方法来进行。在看过一些论文和博客之后勉强想到了一个简单的可能不是很有效率的查表办法。

下图是简单的霍夫曼编码树的展示，简洁说明5个符号的查表构造过程：

  .. image:: ./image/hpack_huffman.svg

     霍夫曼编码树与下文将提到的查表构造过程

从编码树中我们可以获取符号的编码表：

======== ============= ============
Symbol   code as bits  len in bits
======== ============= ============
A        00            2
B        01            2
C        10            2
D        110           3
E        111           3
======== ============= ============

霍夫曼解码的过程常规仍是构造和编码时一样的霍夫曼树，如图1，然后从根节点开始一次读取每一个\ ``bit``\ 为
\ ``0``\ 时向\ **左孩子**\ 行进，为\ ``1``\ 时向\ **右孩子**\ 行进，直到到达叶子节点，获取解码后的符号。
这是解码一个符号的步骤，但是每次动态的构造霍夫曼树，并且一次只能解码一个比特位，效率很低。

我们可以构造一个多叉树，根据比特位的值来获取孩子节点的索引，这是图2所表达的内容。这样我们的霍夫曼节点
可以表示为：

  .. code-block:: c
     :linenos:

     struct huff_node_s {
        unsigned char ending;
        unsigned char symbol;
        struct huff_node_s *child[4];
     };

如上代码我们就可以表示一个四叉解码树了，要构建这样的树，首先应该两个比特位一组分割编码字节，比如\ ``E``\ 分割为\ ``11``\ ，
\ ``1``\ 。而后就可以构造出如图2中的解码树。

需要特别注意的是即使构造了如图2中所示的解码树也是依然没办法解码的。因为我们假设了孩子节点索引的比特值是编码的一部分，
\ ``E``\ 所在的索引是\ ``1``\ ，但是从二进制角度来说是\ ``01``\ ，假设我们要解码\ ``110110``\ ，结果应该是
\ ``DD``\ 。如果照这样的话，那么解码的步骤为：

  .. code-block:: py
     :linenos:

     def decode_symbol(root, src, dst):
         node = root
         ending = False

         while ending is True:
            idx = read_2bit(src)
            node = node.child[idx]
            ending = node.ending

         push_symbol(dst, node.symbol)

照这个过程我们解码的结果是\ ``ED``\ ，所以我们需要对不能完整分组的符号进行重新计算孩子节点的索引，比如\ ``E``\ ，
\ ``3 % 2``\ 最后会余下一个比特位\ ``1``\ 。这种情况下我们应该让孩子节点索引值为\ ``1x``\ 的节点都为\ ``E``\ 的终止
节点，然后回流多取到的一个比特位。整理后的结果如图3。


.. [#http2.0] https://httpwg.github.io/specs/rfc7540.html
.. [#hpack] https://httpwg.github.io/specs/rfc7541.html
.. [#huffman] https://en.wikipedia.org/wiki/Huffman_coding
