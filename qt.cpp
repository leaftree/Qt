#include <QApplication>
#include <QPushButton>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget w;
	w.show();

	QPushButton button("Second Qt project", &w);

	button.setParent(&w);
	button.show();

	app.exec();
	return 0;
}
