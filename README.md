# nodelet_demo
Demonstrate ros nodelets


Run without using multi-threaded callbacks:

```
roslaunch nodelet_demo demo.launch period:=0.1 mt_callback:=false
```



Run with using multi-threaded callbacks:

```
roslaunch nodelet_demo demo.launch period:=0.1 mt_callback:=true
```

https://answers.ros.org/question/298750/getmtnodehandlegetmtprivatenodehandle-doesnt-result-in-additional-callbacks-but-does-take-more-cpu/
