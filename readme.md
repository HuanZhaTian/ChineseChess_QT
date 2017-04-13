程序可以直接QT5中编译执行，在win7和Ubuntu14.04上测试通过。  

代码在mainwindow.cpp中，虽然用了class关键字，但我总感觉我这代码是过程式编程。  
#关键之处在于鼠标事件处理
##鼠标事件是用来处理用户走棋动作的

###算法表述
	if（第一次点击？)
		选中该棋子
	else
	{
		if（有棋子？）
		{
			if（自己人？）
				交换被选中的棋子
			else
				吃掉对方棋子
		}
		else
			走棋
	}
以上都是在canMove为TRUE的情况

###鼠标的第一次和第二次点击的实现
设置一个变量select，初始值为-1，第一次点击的条件就可以表示为
>if(select==-1)  
>else  
>    ...
>    select=-1

然后调用棋子查找函数，并把查找到的棋子的id赋值给select，这样，当mouseReleaseEvent()再次执行的时候，就可以执行else部分。
  
else就是相当于走棋的放下棋子的动作，一拿一放这个循环完成了，就要重新开始下个循环，所以就需要把select重新初始化为-1
