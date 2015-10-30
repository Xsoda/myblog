.. My Blog post example, created by `ablog start` on Oct 30, 2015.

.. post:: Oct 30, 2015
   :tags: atag
   :author: Xsoda

First Post
==========

World, hello again! This very first paragraph of the post will be used
as excerpt in archives and feeds. Find out how to control how much is shown
in `Post Excerpts and Images
<http://ablog.readthedocs.org/manual/post-excerpts-and-images/>`_. Remember
that you can refer to posts by file name, e.g. ``:ref:`first-post``` results
in :ref:`first-post`. Find out more at `Cross-Referencing Blog Pages
<http://ablog.readthedocs.org/manual/cross-referencing-blog-pages/>`_.

graphviz测试
--------------------

简单二叉树的表示:

  .. graphviz::

     graph G {
       node [shape=circle];
       A -- B;
       A -- C;
       B -- D;
       B -- E;
       C -- F;
       C -- G;
       E -- H;
       E -- I;
       F -- J;
       F -- K;
    };

代码高亮测试
------------------

\ ``python``\ 代码高亮测试

  .. code-block:: python
     :linenos:

     def test(a, b, c):
        if a >= 0 and b >= a:
           return a / b
        elif a >= 0 and c >= a:
           return a / c
        else:
           return a * b + c

     def add(start, end):
        r = 0
        if end > 0 and start < end:
           for x in range(start, end):
              r = r + x
        elif end <= 0 and start > end:
           for x in range(start, end, -1):
              r = r + x
        return r

\ ``C``\ 代码高亮测试

  .. code-block:: c
     :linenos:

     #include <stdio.h>
     #include <stdlib.h>

     int test(int a, int b, int c) {
        if (a >= 0 && b >= a)
           return a / b;
        else if (a >= 0 && c >= a)
           return a / c;
        else
           return a * b + c;
     }

     int add(int start, int end) {
        int r = 0;
        if (end > 0 && start < end)
           for (int i = start; i < end; i++)
              r += i;
        else if (end < 0 && start > end)
           for (int i = start; i > end; i--)
              r += i;
        return r;
     }
