1. auto
  > 当不声明为指针或引用时，auto的推导结果和初始化表达式抛弃引用和cv属性(const/volatile).
  > 当声明为引用或指针时，auto的推导结果将保持初始化表达式的cv属性.
  > auto不能用于函数参数.
  > auto仅能用于推导static const的整形或者枚举成员(其他静态类型在c++标准中无法就地初始化,c++11中可以接受非静态成员变量的就地初始化, 静态成员变量必须const限定，但不支持auto类型非静态成员变量的初始化).
  > auto不能用于定义数组.
2. decltype
  > **auto只能根据变量的初始化表达式推导出变量应该具有的类型**.
  > decltype通过表达式得到的类型可以保留住表达式的引用及const限定符.
  > decltype可以和auto一样加上引用和指针，以及cv限定符(int x = 0; decltype(x) * pi = &x).
  > **指针和引用属于说明符(declarators),在定义的时候，是和变量名而不是类型标识符(type-specifiers)相结合的.
  > decltype(exp)推导规则:
      1. exp是标识符、类访问表达式，decltype(exp)与exp的类型一致.
      2. exp是函数调用，decltype(exp)和返回值的类型一致.
      3. 其他情况，若exp是一个左值，则decltype(exp)实exp类型的左值引用，否则和exp类型一致.
          const int func_cint(void);
          decltype(func_cint()) c2 = 0;  // c2->int  //因为函数返回的是纯右值，对于纯右值，只有类类型可以携带cv限定符.

          const Foo func_cfoo();
          decltype(func_cfoo()) ff = Foo();  // ff -> const Foo

          struct Foo { int x; };
          const Foo foo = Foo();

          decltype(foo.x) a = 0;  // a -> int  根据推导规则1
          decltype((foo.x)) b = a;  // a -> const int&  foo.x是一个左值，所以括号表达式是一个左值，由推导规则3得左值引用

          int m = 0, n = 0;
          decltype(n + m) c = 0;  // c-> int 规则3,n + m返回一个右值，得int
          decltype(n += m) d = 0;  / d -> int&  返回一个左值，结果为int&
  > 范型类型定义的时候typename ContainerT::iterator it_如果上下文传入一个const容器类型的时候就会出错，因为当ContainerT是一个const类型的时候，应当使用const_iterator.为了解决这个问题以前需要模板特化typename ContainerT::const_iterator it_.现在可以decltype(ContainerT().begin()) it_.
  > 返回类型后置语法
      template <typename R, typename T, typename U>
      R add(T t, U u)
      {
          return t + u;
      }

      int a = 1, float = 2.0;
      auto c = add<decltype(a + b)>(a, b);

      template <typename T, typename U>
      decltype(T() + U()) add(T t, U u)
      {
          return t + u;
      }
      //可能没有无参构造函数
      template <typename T, typename U>
      decltype((*(T*)0) + (*(U*)0)) add(T t, U u)
      {
          return t + u;
      }

      //c++11写法
      template <typename T, typename U>
      auto add(T t, Uu) -> decltype(t + u）{return t + u;}

      //test
 
3. 列表初始化
  > 聚合类型初始化列表将以拷贝的形式初始化
  > 聚合类型的定义:
    * 类型是一个普通数组
    * 类型是一个类(class、struct、union),且无用户自定义构造函数，无私有或保护的非静态数据成员，无基类，无虚函数，不能有{}和=直接初始化的非静态数据成员
    * 聚合类型的定义并非递归的，当一个类的非静态成员是非聚合类型时，这个类可能是聚合类型
    * 自定义类想使用初始化列表体够std::initializer_list构造函数就好，但是要求元素必须是同类型的，他有三个成员结构:begin,end,size,他只能被整体初始化或赋值.
    * std::initializer_list不保存元素的拷贝，仅仅存储了列表中元素的引用
        //所以不能这么用
        std::initializer_list<int> func(void) { return {1, 2}; }
        //需要这么用
        std::vector<int> func(void) { return {1, 2}; }

  > 初始化列表可以防止类型收窄
  > int a = 1.1;  //ok
  > int b = { 1.1 };  // error
  > const int x = 1024, y = 1;
  > char c = x; char e = y; char f = {y};  //ok
  > char d = {x};  // error
