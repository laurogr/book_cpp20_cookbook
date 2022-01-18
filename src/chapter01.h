#pragma once

#include <map>
#include <vector>
/* * * * * * * * * * * * * * * * AUTO * * * * * * * * * * * * * * * * * * *
 * automatic type deduction (most important and most used of modern c++)
 * AAA - almost always auto
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void use_auto_whenever_possible() {
  auto i{4};
  auto d{42.5};
  auto f{12.3f};
  auto v = {1, 2, 3};  // initalizer list, if we wanted a vector, we should do
                       // it
  auto p = std::make_unique<int>(10);

  auto add = [](auto const a, auto const b) { return a + b; };

  /*
   * benefits
   * - impossible to leave variable unitilializes
   * - auto ensures we always use the correct type (no implicit conversion used)
   * - good OO : prefer interfaces over implementation
   * */

  // attention : auto is only for type, not for cont/volatile and references

  // decltype(auto) :
  // https://stackoverflow.com/questions/24109737/what-are-some-uses-of-decltypeauto
}

auto ladd = [](auto const a, auto const b) { return a + b; };
// equivalent to:
struct {
  template <typename T, typename U>
  auto operator()(T const a, U const b) const {
    return a + b;
  }
} L;

/* * *  * * * * * Creating type aliases and alias templates * * * * * * * * *
 * typedef cannot be used with templates (std::vector<T> is not a type)
 * we can instead use 'using' syntax
 * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * */

void create_type_alias_alias_template() {
  using byte = unsigned char;
  using array_t = int[10];
  using fn = void(byte, double);

  // void func(byte b,double d) { ... }
  // fn *f = func
}

/* for consistency and readability
 * - not mix typedef and using
 * - prefer using to create names of function pointer types
 */

/* * *  * * * * * Understanding uniform initialization  * * * * * * * * *
 *
 * it can be direct or copy
 *   T object {};
 *   T object = {}
 *
 * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * */

void understand_uniform_init() {

  /* Init List
   * compiler resolves the type of init list
   * compiler creates an array with the elements
   * compiler init_list to wrap the array
   * init list is passed as an argument to the constructor
   */
  std::vector<int> v{1, 2, 3};
  std::map<int, std::string> m{{1, "blabla"}, {2, "bleble"}};

  //c++17
  auto a {17}; //int, because it is a single element in direct init
  auto b = {17}; //initializer list, because it is a copy init

}

/* * * * * * * * Various forms of Non static member init  * * * * * * * * *
 * Use default member initialization when needed
 * Prefer constructor initializer list (saves operations)
 * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * */

struct Control {
  const int DefaultHeight = 14; //init constants here
  const int DefautWidth = 80; //init constants here
  int TextFont = 10; //init value that is not present in one of the constructors
  std::string text;

  Control(const std::string& text) : text(text) {}

  Control(const int defaultHeight, const int defautWidth,
          const std::string& text)
      : DefaultHeight(defaultHeight), DefautWidth(defautWidth), text(text) {}
};

//DO NOT USE assingments in the constructor, use initializer list
  //reason : when in the body of constructor, more work/copy is done


/* * * * * * * * Using scoped enum  * * * * * * * * *
 * prefer scoped enumeration
 *    enum class
 * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * */

enum class Status { Unk, Created, Connected };

void using_scoped_enum(Status const s) {
  //switch (s) {
  //  using enum Status; cpp20 new feature, to avoid using Status:: everytime
  //}
}

//specify underlying type
enum class StatusUnsInt : unsigned int { Unk, Created, Connected };


/* * * * * * * * Using override qnd final for virtual methods  * * * * * * * * *
 * c++ does not have interfaces (classes with pure virtual only)
 * virtual for declaring, naturally, virtual methods
 *     however, virtual is optional on the overrided methods (leading sometimes to confusion - you need to navigate sometimes to know)
 *     it is usefull to know if the class/function can be overriden or it is final
 * so, good practive to use final and virtual
 * * * * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * */

class Base {
  virtual void foo() = 0; //pure virtual
  virtual void bar() {};
  virtual void foobar() = 0;
};
void Base::foobar() {}

class Derived1 : Base {
  virtual void foo() override = 0;
  virtual void bar() override {};
  virtual void foobar() override {};
};

class Derived2 : Derived1 {
  virtual void foo() final {}
};

class Derived3 final : Derived1 {
  virtual void foo() override {}
  virtual void foobar() override {}
};

class Derived4 final : Derived2 {
  //ERROR
  //virtual void foo() override {}
};

//override ensures that the function is overriding a base class function
//override helps compiler to detect situation where a virtual method does not override


