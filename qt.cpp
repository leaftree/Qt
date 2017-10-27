#include <QApplication>
#include <QPushButton>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv); //初始化

	QWidget w;
	w.show();

	QPushButton button("Second Qt project", &w);

	button.setParent(&w);
	button.show();

	app.exec(); //主事件循环
	return 0;
}
