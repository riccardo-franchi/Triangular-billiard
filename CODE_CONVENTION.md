Do:
~~~c++
const float GLOBAL_CONSTANT_VALUE{3.14f};

void someFuncition(const std::string& s)
{
    int someVariableName{};
    ...
}

template<typename T>
class SomeClass
{
public:
    SomeClass(...);

private:
    T m_firstMember{};
    double m_secondMember{0.};
};
~~~

Don't do:
~~~c++
const float globalConstantValue{3.14};

void some_funcition(std::string const& s) {
    int some_variable_name{};
    ...
}

template<class T>
class Some_class {
    T _firstMember;
    double _secondMember;

public:
    SomeClass(...);
    ~SomeClass();
};
~~~