KulvCompiler
============

一个类YACC语法分析器，词法，语法，语义分析。支持标准C文法，做到中间代码生成，不过只生成了常用语义。
这是在大三第一学期王宏志老师的《编译原理》课上做的实验，请忽略docs/目录下为了迎合TA写的NC的句子，鄙视我吧····



关于语法分析：
一个类YACC - - 的语法分析器生成器。能够读入文法，然后产生LALR(1)的语法分析表。并能够对一般文法进行分析模拟测试。
实现方法：
1．	首先对文法进行建模，设计好数据结构，能够对文法进行快速的存储访问。

2．	程序自动求出frist表，能够基于LR(0) , LR(1)的方法进行求解。

3．	首先能用LR(0)的方法求解。

4．	再进一步升级到LR(1),实现。

5．	在上两步的基础上进一步优化处理，用LALR(1)方法进行求解。并将语法分析表进行压缩处理，降低存储空间。

关于语义分析：
由于时间关系，只做了一部分基本的语义分析，没有一一实现了，点到为止；

关于中间代码生成：
实现基本算数运算的中间代码，函数调用等；

目标代码生成：
这部分没有实现了，得查Intel文档写010101····



测试文法和C语言文法在这里：LALR\CompPrinLab\Grammar Analyze\Grammar

语法分析的结果，GOTO表，跳转表在这里：LALR\CompPrinLab\Grammar Analyze\Result

中间代码生成的结果在这里：KulvCompiler\CompPrinLab\Semantic Analyze 

要编译的源代码在这里：LALR\CompPrinLab\Shared\CodeFile.cpp

使用VS 2008编译即可。
