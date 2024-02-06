#include "Headers/wordreview.h"

#include "Forms/ui_wordreview.h"
#include "Headers/OperateData.h"
#include "Headers/worddictation.h"

WordReview::WordReview(QWidget *parent) : QDialog(parent), ui(new Ui::WordReview)
{
    ui->setupUi(this);
    //初始化数据
    OperateData::InitialData("cha");
    ui->top_label->setText("cet4");
    ui->top_label->setAlignment(Qt::AlignHCenter);

    // 添加日期选择
    ui->comboBox->addItems(date_list);

    OutPut();

    connect(ui->comboBox, &QComboBox::currentTextChanged,
            [=]()
            {
                //根据用户选择的日期更新向量
                OperateData::ChangeData("cha", ui->comboBox->currentText());
                // 重置计数
                cont = 0;
                OutPut();
            });

    connect(ui->next_button, &QPushButton::pressed,
            [=]()
            {
                cont++;
                OutPut();
            });

    connect(ui->sound_button, &QPushButton::pressed, [=]() { WordDictation::Dictation(user_data[cont].word); });

    connect(ui->close_button, &QPushButton::pressed, [=]() { this->close(); });
}

WordReview::~WordReview() { delete ui; }

// 输出单词及发音
void WordReview::OutPut() const
{
    ui->word_lineedit->setText(user_data[cont].word);
    ui->meaning_lineedit->setText(user_data[cont].meaning);
    ui->new_button->setChecked(user_data[cont].is_new == 1);
    WordDictation::Dictation(user_data[cont].word);
}
