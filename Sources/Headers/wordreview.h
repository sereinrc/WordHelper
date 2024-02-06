#ifndef WORDREVIEW_H
#define WORDREVIEW_H

#include <QDialog>

namespace Ui
{
    class WordReview;
}

class WordReview : public QDialog
{
    Q_OBJECT

public:
    explicit WordReview(QWidget *parent = nullptr);
    ~WordReview() override;

private:
    Ui::WordReview *ui;
    int cont = 0;
    void OutPut() const;
};

#endif  // WORDREVIEW_H
