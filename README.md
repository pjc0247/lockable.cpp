# lockable.cpp

```C++
auto value = make_lockable<test>(arg1, arg2);

value.lock([](test &v){
  v.do_work();
});
```


exclusive
----
```C++
auto value = make_exclusive<test>(arg1, arg2);

value.unsafe().do_work();
value.lock([](test &v){
  v.do_work(); /* thread-safe */
});
```

exclusive-with-RAII
----
```C++
auto value = make_exclusive<test>(arg1, arg2);

value.unsafe().do_work();

{
  auto safe_value = value.safe();
  
  safe_value.do_work();
}
```
