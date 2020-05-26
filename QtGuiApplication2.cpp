#include "QtGuiApplication2.h"
#include<QApplication>
QtGuiApplication2::QtGuiApplication2(QWidget* parent)
	: QMainWindow(parent), turn(0), Alpha_Doge()
{
	for (int i = 0; i < BoardLength; i++)			//��ʼ����ά����
		for (int j = 0; j < BoardLength; j++)
			Board[i][j] = 0;

	ui.setupUi(this);
}

void QtGuiApplication2::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(Qt::black);
	QBrush brush;
	
	for (int i = 0; i < BoardLength; i++)
	{
		painter.drawLine(BoardMargin+BoardOneSize*i, BoardMargin, BoardMargin+BoardOneSize*i, BoardLineLong);
		painter.drawLine(BoardMargin, BoardMargin+BoardOneSize*i, BoardLineLong, BoardMargin + BoardOneSize * i);
	}
	for (int i = 0; i < BoardLength; i++) {
		for (int j = 0; j < BoardLength; j++) {
			if (Board[i][j] != 0) {
				if (Board[i][j] == BLACK)
					brush.setColor(Qt::black);
				else if (Board[i][j] == WHITE)
					brush.setColor(Qt::white);
				brush.setStyle(Qt::SolidPattern);
				painter.setBrush(brush);	
				//��drawEllipse��һ�������ǵ������߽�y��Ĵ�С���ڶ����Ǿ����ϱ߽�x���С�����Ե�һ������Ӧ���趨Ϊj*BS��ʾ�о�
				painter.drawEllipse(j*BoardOneSize + BoardMargin - 15, i * BoardOneSize + BoardMargin - 15, 30, 30);
			}
		}
	}
	if (Alpha_Doge.GamingOrNot() == false)
	{
		QFont font;
		font.setFamily("Microsoft YaHei");
		font.setPointSize(50);
		font.setItalic(true);
		painter.setFont(font);
		painter.drawText(rect(), Qt::AlignCenter, "GAME END");
	}
}

void QtGuiApplication2::mousePressEvent(QMouseEvent* event)
{
	QPainter painter(this);
	QPoint ai_chess;
	int x = event->x();
	int y = event->y();
	if (event->button() == Qt::LeftButton) {
		if (InBoard(x, y)) {		//row �У�col��
			int col = round((double)(x - BoardMargin) / (BoardOneSize));		//�����ŵ�������x����->ʵ�ʴ���������
			int row = round((double)(y - BoardMargin) / (BoardOneSize));		//Ϊ����ƺ���xy��Ϊ����
			Board[row][col] = WHITE;
			Alpha_Doge.UpdateBoard(row,col,WHITE);
			Board[Alpha_Doge.BestChess().x][Alpha_Doge.BestChess().y] = BLACK;
			
			//Alpha_Doge.UpdateBoard(Alpha_Doge.BestChess().x,Alpha_Doge.BestChess().y,BLACK);
		}
	}
	update();
}
