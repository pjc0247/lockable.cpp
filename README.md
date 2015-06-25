# lockable.cpp

```C++
auto value = make_lockable<test>(arg1, arg2);

value.lock([](test &v){
  v.do_work();
});
```
