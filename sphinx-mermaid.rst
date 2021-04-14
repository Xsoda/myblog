.. sphinx中使用mermaid画图

.. post:: Apr 14, 2021
   :tags: sphinx, mermaidjs
   :author: Xsoda

sphinx中使用mermaid画图
===========================

目前博客中的图片使用\ ``graphviz``\ 生成, 当要绘制复杂图形时很复杂.
相对使用\ ``mermaid``\ 比较简单.

config.py
----------------

安装\ ``sphinxcontrib-mermaid``\ 后, 在\ ``config.py``\ 中的加上扩展支持

.. code:: python

   extensions = [
       'sphinxcontrib.mermaid',
       # ...
   ]
   mermaid_output_format = 'raw'

如果需要生成\ ``png``\ 图片, 还需要安装\ ``nodejs``, ``mermaid``, ``mermaid-cli``\ 等
包, 这里只是在浏览器中使用.

序列图
----------------

在\ ``RST``\ 中加入

::

   .. mermaid::

      sequenceDiagram
        participant Alice
        participant Bob
        Alice->John: Hello John, how are you?
        loop Healthcheck
          John->John: Fight against hypochondria
        end
        Note right of John: Rational thoughts <br/>prevail...
        John-->Alice: Great!
        John->Bob: How about you?
        Bob-->John: Jolly good!

生成图形:

.. mermaid::

   sequenceDiagram
     participant Alice
     participant Bob
     Alice->John: Hello John, how are you?
     loop Healthcheck
       John->John: Fight against hypochondria
     end
     Note right of John: Rational thoughts <br/>prevail...
     John-->Alice: Great!
     John->Bob: How about you?
     Bob-->John: Jolly good!

普通二叉树图形
--------------

::

   .. mermaid::

      graph TB
        A --- B & C
        B --- D & E
        C --- F & G
        D -- left --- H
        D -- right --- J
        E -- left --- K
        E -- right --- L
        F -- left --- M
        F -- right --- N
        G -- left --- O
        G -- right --- P

生成图形

.. mermaid::

   graph TB
     A --- B & C
     B --- D & E
     C --- F & G
     D -- left --- H
     D -- right --- J
     E -- left --- K
     E -- right --- L
     F -- left --- M
     F -- right --- N
     G -- left --- O
     G -- right --- P
