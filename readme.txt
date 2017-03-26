1.程序从main进入，执行w.show()时调用paintEvent函数。


2.在执行show()之前，类 w 先执行构造函数，初始化具体数值。棋子半径、格子宽度、棋子状态等都在构造函数中完成。start()函数就是初始化棋子状态。


3.paintEvent函数中分两部分：画棋盘和画棋子。其中画棋盘是固定的。而画棋子是变化的。

	01：棋子死亡（dead==true），不显示此棋子

	02：棋子是否被选中。若被选中（choose==true），棋子背景色为灰色。否则为白色。

	03：判断棋子颜色。若为红方（side==true），则画红色字体。


4.然后执行鼠标事件函数mouseReleaseEvent(QMouseEvent *ev)，其中ev返回鼠标点击位置的坐标。
	01：获得鼠标点击位置所属的棋盘坐标。getXY(),返回值为QPoint类型，比如在棋盘坐标（1,1）附近，半径为r的范围内，便属于棋盘坐标（1,1）所属。如果鼠标点击位置不在棋盘内，则返回坐标（-1，-1）。

	02：判断该棋盘坐标上是否有棋子，haveStone()，如果该位置有棋子，且dead==false，则返回棋子id。否则返回-1。

	03：判断棋子id所属阵营的王（将帅）是否dead。如果是，则无操作。如果否，则执行人走棋persionMove()
		01:persionMove(int &id,QPoint &pt)参数分别是棋子id和鼠标第二次点击的位置。
		02：第一次点击（select==-1），第一次点击的位置有棋子（id!=-1),的确该本方走棋redTurn==side /side表示被选中的棋子所属阵营）。以上都成立时，该棋子被选中。redTrun取反,把id赋值给select，使第二次鼠标点击事件生效。
		03：第二次点击（select!=-1),新位置由id表示。id==-1,表示第二次点击出无棋子，则判断是否能走，bool canMove(int id,QPoint p)
		04：能走，则走棋。否则，重置到第一次点击前的状态(第一次点击时，被选中状态取消。select重置为-1，强制回到第一次点击之前)。resetting(int id)将棋子id的状态重置。
		05:第二次点击，新位置id!=-1时。判断id是否属于本方阵营棋子。如果是，交换被选中状态。如果不是，判断时候可行。不可行就重置第一次点击前状态。

5.随着鼠标事件的发生，改变了一些数据后执行update，重新调用paintEvent。


6.退出


其他函数：
camMove(int id,QPoint p)其中有分别有：
	将帅：KingMove（）
	士仕：AdvisorMove（）
	相象：BishopMove（）
	马  ：KnightMove（）
	车  ：RookMove（）
	炮  ：CannonMove（）
	兵卒：PawnMove（）

将帅是否照面函数：			king_RedAndBlack()

计算两个左边点内棋子数量的函数：	numberOfStone（）

获得本方王的id：			getKingID（）

判断所属阵营函数：			ifRed（）

最大数最小数函数：			max（）、min（）

两个数之间的差：			len（）

获取中心点：				getCenterXY（）

