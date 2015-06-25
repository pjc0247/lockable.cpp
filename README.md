# lockable.cpp

```C++
auto value = make_lockable<test>(arg1, arg2);

value.lock([&value](){
  value->do_work();
});
```
