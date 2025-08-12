#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    window.setWindowTitle("Slider and SpinBox Example");

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(50);

    QSpinBox *spinBox = new QSpinBox;
    spinBox->setRange(0, 100);
    spinBox->setValue(50);

    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    QObject::connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(spinBox);
    window.setLayout(layout);

    window.show();
    return a.exec();
}
