#ifndef WORDSPELLING_H
#define WORDSPELLING_H

#include <QDialog>

namespace Ui
{
    class WordSpelling;
}

class WordSpelling final : public QDialog
{
    Q_OBJECT

public:
    explicit WordSpelling(QWidget *parent = nullptr);
    ~WordSpelling() override;

private:
    Ui::WordSpelling *ui;
    int cont = 0;
    int num = 0;
};

#endif  // WORDSPELLING_H
