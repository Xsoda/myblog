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

   digraph {
     A -- B;
     A -- C;
     B -- D;
     B -- E;
     C -- F;
     C -- G;
     E -- H;
     E -- I;
  };
