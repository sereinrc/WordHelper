#ifndef WORDDICTATION_H
#define WORDDICTATION_H

#include <QDialog>

namespace Ui
{
    class WordDictation;
}

class WordDictation final : public QDialog
{
    Q_OBJECT

public:
    explicit WordDictation(QWidget *parent = nullptr);

    ~WordDictation() override;

private:
    Ui::WordDictation *ui;
    int cont = 0;
    int num = 0;
    static void Dictation(int cont);
};

#endif  // WORDDICTATION_H
