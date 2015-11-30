.. 漂亮的原生库

.. post:: Nov 28, 2015
   :tags: native-library, programming, translation
   :author: Xsoda

漂亮的原生库
================

   本文翻译自：http://lucumr.pocoo.org/2013/8/18/beautiful-native-libraries/

我对漂亮的API着迷, 不仅仅是API本身, 还在于尽可能好的使用一个库的全部体验. 对于\ ``Python``\ 来
说现在有很多的最好实践, 但是感觉并没有大量信息来说明如何正确地构造一个原生库. 我说的原生库指的是
什么? 本质上是一个\ ``dylib/DLL/so``\ 文件.

由于我最近的工作中在C和C++上花了比Python还多的时间, 我想通了如何写出合适的共享库而不惹恼库的使用
者, 借这个机会整理一些我的想法.

共享库还是静态库?
------------------------

这篇文章几乎假定了你正在构建一个\ ``DLL``\ 或共享库而不是你链接的静态库. 虽然听起来动态链接和静态
链接本质是同样的, 唯一的区别是你如何链接到它, 当然远不止于此.

使用动态链接库你可以更好地控制你的符号, 在不同的编程语言中也可以更好的工作. 你使用C++编写一个库然后
在Python中使用也是可以的. 实际上, 我建议对这些库做单元测试的方法是完成正确的, 稍后谈的更多.

使用哪一种语言?
------------------

你想写的库在编译成DLL或类似东西后, 应该有些是平台独立的. 现实中你可以用哪一种语言呢? 目前你可以在
C和C++中选择, 很快你可能也可以使用Rust. 为什么不用其他的呢? C语言在实际中是唯一能定义稳定ABI的.
严谨来说, 不是语言来定义它, 而是操作系统, 从另一方面看, C是库所选择的语言并且C的调用约定是共享库的
通用方式.

“最伟大的魔术是C说服世界相信它并没有运行时”. 我不确定我在哪儿第一次听到这句话, 但是当谈论库时它非
常合适. 实质上C是如此普遍, 任何事都可以假定为C标准库提供的基本函数, 这是大家都同意的. 对于C++情况变
得更复杂. C++需要额外的函数来支持异常处理, 这些函数在C标准库里并没提供. C++能够很好的降级到C调用约定,
所有可以很容易地用它写库, 可以完整的隐藏库由C++编写这一事实.

对于其他语言来说无乱怎样都不是那么容易. 例如为什么使用Go语言来写一个库并不是一个好注意呢? 原因是Go需要
相当重量级的运行时来做垃圾收集和提供协程调度. Rust正在接近与除C标准库外不需要运行时, 这将使得用它来
编写库是可能的.

然而现在C++是你最可能要使用的语言. 为什么不是C呢? 原因是微软的C编译器在接受语言更新方面声名狼藉, 你只能
使用C89标准. 显然你也可以在Windows上使用不同的编译器, 但是这将会对库的使用者在编译库时造成很多问题.
需要非原生的操作系统工具链是疏远开发者受众的简单方式.

我通常建议使用非常像C的C++子集: 不使用异常, 不使用RTTI, 不要写令人发狂的构造函数. 文章的余下部分
假定C++是我们真正选择的语言.

公共头文件
-----------------

你构建的库应该只有一个精确的公共头文件. 而内部无乱你想有多少个头文件都可以, 有了唯一的头文件, 即使
你的库去链接不是C语言的东西都可以. 以Python为例, CFFI库可以解析头文件并且建立符号绑定. 使用各种语言
的人知道头文件如何工作, 他们会看一看建立自己的绑定.

头文件应该遵循什么规则呢?

头文件守卫
```````````

提供其他人使用的每一个头文件应该最大限度的使用唯一的头文件守卫标记来确保他们可以安全的被包含多次.
守卫表记不用太有创新, 但也别太普通. 包含一个在顶部使用一个超级通用的包含守卫(例如\ ``UTILS_H``\ 或其他)
的头文件并不有趣. 你也想在C++文件包含时确保有\ ``extern "C"``\ 标记.

下面是你的最小头文件:

.. code-block:: c
   :linenos:

   #ifndef YOURLIB_H_INCLUDED
   #define YOURLIB_H_INCLUDED
   #ifdef __cplusplus
   extern "C" {
   #endif

   /* code goes here */

   #ifdef __cplusplus
   }
   #endif
   #endif

导出符号标记
````````````````````

因为你自己将可能包含你的头文件, 同样你也需要确保导出函数的宏被定义. 在Windows上这是必要的, 并且在其他平台上
也是一个不错的主意. 实质上导出符号标记用来改变符号的可视性. 稍后我再讲他们, 现在仅仅把下面的代码添加进去:

.. code-block:: c
   :linenos:

   #ifndef YL_API
   #  ifdef _WIN32
   #     if defined(YL_BUILD_SHARED) /* build dll */
   #         define YL_API __declspec(dllexport)
   #     elif !defined(YL_BUILD_STATIC) /* use dll */
   #         define YL_API __declspec(dllimport)
   #     else /* static library */
   #         define YL_API
   #     endif
   #  else
   #     if __GNUC__ >= 4
   #         define YL_API __attribute((visibility("default")))
   #     else
   #         define YL_API
   #     endif
   #  endif
   #endif

在Windows上将为DLL妥善的设置\ ``YL_API``\ (我这里使用"Your Library"的缩写版本, 你可以挑选一个适合你的前缀),
这取决与哪一个标志被设置. 无论谁包含了头文件而什么也不做将自动获得\ ``__declspec(dllimport)``\ . 在Windows下
这是很好的默认行为. 对于其他平台什么也不设置除非是用的是最近被添加了默认符号可视性的GCC/clang版本. 你可以看到
一些宏定义后, 改变了编译器使用的分支. 例如当你构建库本身时, 你可以定义\ ``YL_BUILD_SHARED``\ 来告诉编译器.

在Windows上DLL的默认行为总是: 所有的符号并不会被导出, 除非使用\ ``__declspec(dllexport)``\ 标记. 不幸的是,
在其他平台上编译器的行为总是导出任何符号. 有很多的方法来修复它, 其一就是控制GCC 4的可视性. 这可以很好的工作,
但是还有一下额外的事需要考虑.

第一就是在源代码上的可视性控制并不是银弹. 刚开始标记将什么也不做除非库使用了\ ``--fvisibility=hidden``\ .
更重要是这只对你自己的库有影响. 如果你静态链接到你的库, 而这个库却暴露了你并不想暴露的符号. 设想一下, 你写了
一个库, 而这个库依赖与其他你想要静态链接的库. 这个库的符号将也会从你的库导出, 必须阻止这样的事发生.

这个工作在不同的平台而不同. Linux下你可以传递\ ``--exclude-libs ALL``\ 给\ ``ld``\ , 然后链接器将会
自动移除这些符号. OS X下是一个骗子, 因为链接器没有符合的功能. 最简单的解决方案是为所有的函数使用一个公共前缀.
在本例中如果你所有的函数都以\ ``yl_``\ 开头, 告诉链接器隐藏其他的符号就简单了. 你创建符号文件然后给链接器指明
参数\ ``-exported_symbols_list symbols.txt``\ , 文件的内容可以是单独的一行\ ``_yl_*``\ .
Windows下我们可以忽略因为DLL需要显式的导出标记.

小心地包含和定义
---------------------

头文件需要注意的是不应该包含太多的东西. 通常情况下我认为头文件包含一些像如\ ``stdint.h``\ 来获取通用的整数类型
是不错的. 但是你不应该自作聪明的定义自己的类型. 例如msgpack有一个很天才的想法定义了\ ``int32_t``\ 和少量其他
类型, 因为Visual Studio 2008缺少了\ ``stdint.h``\ . 这是有问题的, 仅仅只有这一个库可以定义这些类型. 更好的
解决方案是为使用更老的Visual Studio版本的用户提供一个\ ``stdint.h``\ 头文件.

特别重要的的是库头文件中永远不要包含\ ``windows.h``\ . 这个头文件中有太多的东西以至于微软添加额外的定义来让他
精简(\ ``WINDOWS_LEAN_AND_MEAN``\ , \ ``WINDOWS_EXTRA_LEAN``\ , \ ``NOMINMAX``\ ).
如果你需要包含\ ``windows.h``\ , 使用一个私有的头文件仅仅在你的\ ``.cpp``\ 文件中包含.

稳定的ABI
-------------

在公共头文件中不要放入任何结构体定义, 除非你100%确定你将永远不会改变他们. 如果你想暴露结构体并且以后想要添加额外
的成员, 确保用户不需要使用那个头文件来为结构体分配内存. 如果用户不得不为结构体分配内存, 添加一个版本或者尺寸信息
作为结构体的第一个成员.

微软通常把结构体的尺寸放入结构体中, 然后再添加成员, 但是这导致API的使用并不有趣. 如果你能尝试在头文件中避免定义
太多的结构体, 如果你不能至少尝试替代方法, 来减少API的数量.

结构题中你也许会在不同的编译器中遇到字节对齐问题. 不幸的是, 如果你正在处理一个项目, 这个项目和整个工程有着不同的
对齐方式, 这样的话显然也会对你头文件中的结构体有影响. 更少的结构体更好:-)

应该不用说的东西: 不要让宏称为API的一部分. 宏不是一个符号, 不基于C语言的用户会因为有宏而恨你.

一个稳定的ABI说明: 在库的头文件和编译的二进制文件中包含版本是一个很好的想法. 这样你可以更容易的验证头文件和二进制库
是否匹配, 这是一个很头疼的问题.

头文件中版本类似与这样:

.. code-block:: c
   :linenos:

   #define YL_VERSION_MAJOR 1
   #define YL_VERSION_MINOR 0
   #define YL_VERSION ((YL_VERSION_MAJOR << 16) | YL_VERSION_MINOR)

   unsigned int yl_get_version(void);
   int yl_is_compatible_dll(void);

这些在实现文件中:

.. code-block:: c
   :linenos:

   unsigned int yl_get_version(void)
   {
       return YL_VERSION;
   }

   int yl_is_compatible_dll(void)
   {
       unsigned int major = yl_get_version() >> 16;
       return major == YL_VERSION_MAJOR;
   }


导出为C语言API
------------------

但为C暴露C++的API时没有太多考虑. 通常你拥有的每一个内部类, 你应该都要有一个不透明的没有任何字段的结构体.
然后提供函数, 调用到库的内部函数. 设想一个如下的一个类:

.. code-block:: cpp
   :linenos:

   namespace yourlibrary {
       class Task {
       public:
           Task();
           ~Task();

           bool is_pending() const;
           boid tick();
           const char *result_string() const;
       };
   }

内部的C++ API相当明显了, 但是怎么使用C暴露出来呢? 因为外部ABI现在不再知道结构体的大小, 你需要为外部的调用者
分配内存, 或给出一个方法指出需要分配多少内存. 我通常跟喜欢为外部用户分配内存, 并提供一个释放函数. 如何让内存
分配系统更具有弹性, 将在下一个部分指明.

下面是外部头文件(这里必须在\ ``extern "C"``\ 中括号里面):

.. code-block:: c
   :linenos:

   struct yl_task_s;
   typedef struct yl_task_s yl_task_t;

   YL_API yl_task_t *yl_task_new();
   YL_API void yl_task_free(yl_task_t *task);
   YL_API int yl_task_is_pending(const yl_task_t *task);
   YL_API const char *yl_task_get_result_string(const yl_task_t *task);

在下面的实现中, 中间层看起来像是这样:

.. code-block:: cpp
   :linenos:

   #define AS_TYPE(Type, Obj) reinterpret_cast<Type *>(Obj)
   #define AS_CTYPE(Type, Obj) reinterpret_cast<const Type *>(Obj)

   yl_task_t *yl_task_new()
   {
       return AS_TYPE(yl_task_t, new yourlibrary::Task());
   }

   void yl_task_free(yl_task_t *task)
   {
       if (!task)
           return;
       delete AS_TYPE(yourlibrary::Task, task);
   }

   int yl_task_is_pending(const yl_task_t *task)
   {
       return AS_CTYPE(yourlibrary::Task, task)->is_pending() ? 1 : 0;
   }

   void yl_task_tick(yl_task_t *task)
   {
       AS_TYPE(yourlibrary::Task, task)->tick();
   }

   const char *yl_task_get_result_string(const yl_task_t *task)
   {
       return AS_CTYPE(yourlibrary::Task, task)->result_string();
   }

注意构造和析构函数是如何全部包裹的. 现在使用标准C++有一个问题: 他会抛出异常. 因为如果内存分配失败了它将抛出异常,
构造函数没有返回值来通知调用者. 现在我们怎么样自定义库的内存分配呢? C++在这方面相当丑陋. 但是在很大程度上是可以解决的.

对象上下文
----------------

全局状态是可怕的, 所以有解决方案吗? 通常的解决方法是使用一个我要调用的上下文对象, 代替绑定的状态. 这些对象拥有所有终于的
东西, 包括你要放入的全局变量. 这样的话用户在使用时将会拥有多个上下文. 然后使这个上下文对象作为每一个API接受的第一个参数.

当你的库不是线程安全时特别有用. 那种方式下你可以至少有一个线程, 对于一些需要并行的代码已经足够用了.

理论上这些上下文对象也可以使用不同的分配器, 但是鉴于C++的复杂性, 即使你没有这样做, 我也不会太失望.

客户化内存分配
-----------------

前面提到的, 构造函数会失败, 并且我们想要自定义内存分配, 我们该怎么做到呢? 在C++中有两个系统负责内存分配:
分配操作符\ ``operator new``\ 和容器分配操作符\ ``operator new[]``\ . 如果你想要自定义分配器,
你两个都需要处理. 首先你需要一种方式来重写分配器函数. 最简单的是在公共头文件中提供某种类似于下面的方法:

.. code-block:: c
   :linenos:

   YL_API void yl_set_allocators(void *(*f_malloc)(size_t),
                                 void *(*f_realloc)(void *, size_t),
                                 void (f_free)(void *));
   YL_API void *yl_malloc(size_t size);
   YL_API void *yl_realloc(void *ptr, size_t size);
   YL_API void *yl_calloc(size_t count, size_t size);
   YL_API void yl_free(void *ptr);
   YL_API char *yl_strdup(const char *str);

然后在你内部的头文件添加一些内嵌函数, 重定向到内部结构体中的函数指针值. 因为我们不能让用户
提供\ ``calloc``\ 和\ ``strdup``\ , 你可能也要重新实现这些函数:

.. code-block:: c
   :linenos:

   struct yl_allocators_s {
       void *(*f_malloc)(size_t);
       void *(*f_realloc)(void *, size_t);
       void  (*f_free)(void *);
   };
   extern struct yl_allocators_s _yl_allocators;

   inline void *yl_malloc(size_t size)
   {
       return _yl_allocators.f_malloc(size);
   }

   inline void *yl_realloc(void *ptr, size_t size)
   {
       return _yl_allocators.f_realloc(ptr, size);
   }

   inline void yl_free(void *ptr)
   {
       _yl_allocators.f_free(ptr);
   }

   inline void *yl_calloc(size_t count, size_t size)
   {
       void *ptr = _yl_allocators.f_malloc(count * size);
       memset(ptr, 0, count * size);
       return ptr;
   }

   inline char *yl_strdup(const char *str)
   {
       size_t length = strlen(str) + 1;
       char *rv = (char *)yl_malloc(length);
       memcpy(rv, str, length);
       return rv;
   }

对于分配器的设置, 你大概想要把他们放到单独的源文件中:

.. code-block:: c
   :linenos:

   struct yl_allocators_s _yl_allocators = {
       malloc,
       realloc,
       free
   };

   void yl_set_allocators(void *(*f_malloc)(size_t),
                          void *(*f_realloc)(void *, size_t),
                          void (*f_free)(void*))
   {
       _yl_allocators.f_malloc = f_malloc;
       _yl_allocators.f_realloc = f_realloc;
       _yl_allocators.f_free = f_free;
   }

内存分配和C++
------------------

现在我们已经设置好了这些函数, 但是我们如何让C++使用他们呢? 这部分想多棘手和恼人. 为了得到你的类能够
使用\ ``yl_malloc``\ 来分配, 你需要在你所有的类中实现内存分配操作符. 因为这是十分繁复的过程, 我建
议为这个过程写一个宏, 能够放在类的私有段中. 我选择按照惯例, 它必须放在私有段中, 尽管这些函数的实现的
公共的. 我主要做的是让他接近于数据定义的地方, 在我的例子中这通常是私有的. 你可能需要确保你没有忘记在
你所有类的私有段中加入这个宏:

.. code-block:: cpp
   :linenos:

   #define YL_IMPLEMENTS_ALLOCATORS \
   public: \
       void *operator new(size_t size) { return yl_malloc(size); } \
       void operator delete(void *ptr) { yl_free(ptr); } \
       void *operator new[](size_t size) { return yl_malloc(size); } \
       void operator delete[](void *ptr) { yl_free(ptr); } \
       void *operator new(size_t, void *ptr) { return ptr; } \
       void operator delete(void *, void *) { } \
       void *operator new[](size_t, void *ptr) { return ptr; } \
       void operator delete[](void *, void *) { } \
   private:

这是一个如何使用的例子:

.. code-block:: cpp
   :linenos:

   class Task {
   public:
       Task();
       ~Task();

   private:
       YL_IMPLEMENTS_ALLOCATORS;
       // ...
   };

现在你所有的类都能够通过你的分配器函数来分配内存了. 但是如果你想使用STL容器怎么办? 这些容器
还不能通过你的函数来分配内存. 为了修复这个特殊的问题你还需要写一个STL代理分配器. 这也是一个
极其恼人的过程, 因为复杂的接口, 基本上什么也不做.

.. code-block:: cpp
   :linenos:

   #include <limits>

   template <class T>
   struct proxy_allocator {
       typedef size_t size_type;
       typedef ptrdiff_t difference_type;
       typedef T *pointer;
       typedef const T *const_pointer;
       typedef T &reference;
       typedef cons T &const_reference;
       typedef T value_type;

       template <class U>
       struct rebind {
           typedef proxy_allocator<U> other;
       };

       proxy_allocator() throw() {}
       proxy_allocator(const proxy_allocator &) throw() {}
       template <class U>
       proxy_allocator(const proxy_allocator<U> &) throw() {}
       ~proxy_allocator() throw() {}

       pointer address(reference x) const { return &x; }
       const_pointer address(const_reference x) const { return &x; }

       pointer allocate(size_type s, void const * = 0) {
           return s ? reinterpret_cast<pointer>(yl_malloc(s * sizeof(T))) : 0;
       }

       void deallocate(pointer p, size_type) {
           yl_free(p);
       }

       size_type max_size() const throw() {
           return std::numeric_limits<size_t>::max() / sizeof(T);
       }

       void construct(pointer p, const T &val) {
           new (reinterpret_cast<void *>(p)) T(val);
       }

       void destroy(pointer p) {
           p->~T();
       }

       bool operator==(const proxy_allocator<T> &other) const {
           return true;
       }

       bool operator!=(const proxy_allocator<T> &other) const {
           return false;
       }
   };

接下来我们继续, 如何使用这么恶心的代码呢? 看下面:

.. code-block:: cpp
   :linenos:

   #include <deque>
   #include <string>

   typedef std::deque<Task *, proxy_allocator<Task *>> TaskQueue;
   typedef std::basic_string<char, std::char_traits<char>,
                             proxy_allocator<char>> String;

我建议将所有你想要使用的容器定义到头文件中, 然后强迫自己不要使用没有别名定义的STL以便正确的
使用分配器. 小心: 不要做\ ``new TaskQueue()``\ 这样你会调用到全局的new操作符. 把他们作为
成员放到你的结构体中使内存分配在拥有自定义内存分配器的对象中发生. 或者只是把他们放到栈上.

内存分配失败
-----------------

在我的印象中处理内存分配失败的最好方式就是不处理他们. 仅仅是不引起任何的内存分配失败.
对一个库来说是很容易完成的, 明白在最坏情况下你将会申请多少内存, 如果是无限的, 告诉用户某些
方式是很糟糕的. 原因是这样没人能处理内存分配失败.

刚开始STL完全依赖于\ ``std::bad_alloc``\ 来从new操作符抛出异常(我们上面没做这些事),
然后扔给你来处理错误. 当你编译你的库而没有异常处理时库将会终止整个进程. 这是相当可怕的,
如果你不够小心的话, 这种事总会发生. 我见过许多忽略了malloc返回值的代码, 而不是合适地处理它.

除此之外: 在一些系统中malloc完全不真实, 不管怎样都没法告诉你有多少内存是可用的. Linux会很乐意地
给你一个内存指针而不能映射到实际的物理内存. 这个认可的内存行为非常有用, 但是这通常也将让你不得不
假定内存分配失败可能没有发生. 所以代替内存分配错误的是, 如果你使用C++并且你也想坚持使用STL, 那么
放弃这样做吧, 不要耗尽内存.

在计算机游戏中常规概念是有他们自己的内存分配子系统, 为了保证他们从不申请超过他们给定的内存. EA似乎
建议分配器来处理内存分配错误. 比如说当载入更多内存失败时, 它能检查是否可以释放一些不需要的资源
(比如缓存), 而不是让调用者知道有内存错误发生. 这个工作甚至限制了C++标准给出的内存分配器的设计.

构建
---------

现在已经写完了代码, 你要如何构建你的库而不惹恼你的用户呢? 如果你像我一样具有Unix背景使用makefile来
构建软件, 但不是所有人都想要的. Autotools/autoconf太糟糕了, 可怕的软件碎片, 并且如果你给Windows用户
使用, 他们会叫你各种各样的的名字. 取而代之的是确保有Visual Studio解决方案工程文件.

如果你不想为Visual Studio提供编译因为它不是你选择的工具链呢? 如果你想保持解决方案文件和makefile文件
同步呢? 这个问题的答案是使用\ `premake <http://industriousone.com/premake>`_\ 或者
\ `cmake <http://www.cmake.org/>`_\ . 这两个的使用很大程度上取决与你. 他们都能使用简单的定义脚本
生成Makefiles, XCode或者Visual Studio解决方案.

我曾经是cmake的大粉丝, 但现在我换到了premake. 原因是cmake有一些东西是硬编码而我需要自定义化(例如为
使用Visual Studio构建一个Xbox 360解决方案时没法使用cmake预定义的变量). premake像cmake一样有同样的
问题, 但是它几乎全部是用lua写的, 很容易自定义. premake基本上是一个可执行文件, 包含了一个lua解释器和
一堆lua脚本. 如果你想的话很容易重新编译, 你知道怎么做的话, premake文件可以重载所有事.

测试
---------

最后提及: 你怎么测试你的库? 现在显然有很多用C和C++写的测试工具可以使用, 但是我认为最好的工具是在其他地方.
共享库不仅仅是为C和C++写的, 你可以在多种语言中使用他们. 最好的方法是你从一门不是C++的语言中使用它.

在我的实例中我使用Python来测试我的库. 更确切地说: 我使用\ `py.test <http://pytest.org/>`_\ 和
\ `CFFI <http://cffi.readthedocs.org/>`_\ 来测试我的库. 比起直接使用C/C++, 这样做有两个优势.

最大的优势是增加迭代的速度. 我不需要编译我所有的测试, 直接运行就可以了. 不仅仅编译步骤小时, 我也可以
享受Python动态类型和py.test断言语句的优势. 我可以写助手脚本来打印信息, 在我的库和Python中转换数据,
我也可以从好的错误报告中获益.

第二个优势是很好的隔离. \ `pytest-xdist <https://pypi.python.org/pypi/pytest-xdist>`_\ 是
py.test的一个插件, 但给py.test添加了\ ``--boxed``\ 标志后能在单独的进程中运行每一个测试.
如果你有一些测试遇到段错误崩溃了, 会有意想不到的作用. 在系统中启用coredumps后, 然后在gdb中载入段错误,
指出错误发生的地方. 你不需要处理内存内存泄漏的发生, 因为断言失败时能够跳到清理部分. 操作系统将会分别清理
每一个测试. 不幸的是, 通过\ ``fork()``\ 系统调用的实现现在在Windows下无法很好的工作.

那你怎么通过CFFI来使用你的库呢? 你将需要做两件事情: 你需要你的头文件没有包含其他的头文件.
如果没法做到, 就添加一个禁用文件包含的宏定义(例如\ ``YL_NOINCLUDE``\ ).

这是使CFFI工作所需要的:

.. code-block:: py
   :linenos:

   import os
   import subprocess
   from cffi import FFI

   here = os.path.abspath(os.path.dirname(__file__))
   header = os.path.join(here, 'include', 'yourlibrary.h')

   ffi.cdef(subprocess.Popen([
       'cc', '-E', '-DYL_API=', '-DYL_NOINCLUDE', header],
       stdout=subprocess.PIPE).communicate()[0])
   lib = ffi.dlopen(os.path.join(here, 'build', 'libyourlibrary.dylib'))

把它放在一个文件名为\ ``testhelpers.py``\ 中继续你的测试.

现在显然这个简单的版本只能在OS X下工作, 但可以简单的扩展到不同的操作系统. 本质上是调用了C的预处理器
并添加了额外的定义, 然后CFFI解析器订阅了其返回值. 之后你就有了一个可以工作的漂亮的装饰库.

一个测试的例子应该像这样, 把下面代码放入一个叫做\ ``test_something.py``\ 的文件, 然后让\ ``py.test``\ 执行它:

.. code-block:: py
   :linenos:

   import time
   from testhelpers import ffi, lib

   def test_basic_functionality():
       task = lib.yl_task_new()
       while lib.yl_task_is_pending(task):
           lib.yl_task_process(task)
           time.sleep(0.001)
       result = lib.yl_task_get_result_string(task)
       assert ffi.string(result) == ''
       lib.yl_task_free(task)

py.test也有其他的优势. 例如它支持fixture装饰器允许你建立通用资源, 可以在测试用例间重用.
当你的库需要创建一些上下文对象时非常有用, 建立通用的配置, 用后释放它.

为了演示这个, 创建一个\ ``conftest.py``\ 文件输入下面的内容:

.. code-block:: py
   :linenos:

   import pytest
   from testhelpers import lib, ffi

   @pytest.fixture(scope='function')
   def context(request):
       ctx = lib.yl_context_new()
       lib.yl_context_set_api_key(ctx, "my api key")
       lib.yl_context_set_debug_mode(ctx, 1)
       def cleanup():
           lib.yl_context_free(ctx)
       request.addfinalizer(cleanup)
       return ctx

现在来使用这个功能, 你需要做的就是在你的测试函数中添加一个\ ``context``\ 参数:

.. code-block:: py
   :linenos:

   from testhelpers import ffi, lib

   def test_basic_functionality(context):
       task = lib.yl_task_new(context)
       ...

总结
----------

因为这篇博客比以往的要长, 下面是最重要的原则概要, 当你构建原生库时应该时刻想起它:

* 使用C或C++来写, 不要和一门语言一起构建, 以至于让整个运行时拖累CPU和内存

* 尽量不要使用全局变量

* 公共头文件中不要定义通用数据类型

* 公共头文件中不要包含像\ ``windows.h``\ 那样疯狂的头文件

* 公共头文件中包含所有需要的头文件. 考虑通过一个宏定义来禁止包含所有的头文件

* 管理好你的命名空间. 不要暴露你不想暴露的符号

* 创建一个类似与\ ``YL_API``\ 的宏作为你想暴露的每一个符号的前缀

* 尝试构建稳定的ABI

* 不要定义疯狂的结构体

* 让用户自定义内存分配器. 如果你不能做到每个上下文一个分配器, 至少应该每个库一个

* 小心的使用STL, 总是仅仅使用添加了你的分配器的类型定义

* 不要强制你的用户使用你最喜欢的构建工具, 总是确保用户在同一地方可以找到Visual Studio解决方案文件和makefile文件

就这些！构建原生库快乐！
