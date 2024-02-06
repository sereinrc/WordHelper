#include "Headers/wordspelling.h"

#include "Forms/ui_wordspelling.h"
#include "Headers/OperateData.h"

WordSpelling::WordSpelling(QWidget *parent) : QDialog(parent), ui(new Ui::WordSpelling)
{
    ui->setupUi(this);
    // 连接数据库，并创建用户表
    OperateData::InitialData("cet4", "cha");
    ui->top_label->setText("cet4");
    // 设置标题居中
    ui->top_label->setAlignment(Qt::AlignHCenter);

    // 获取随机单词
    cont = OperateData::CreatRandom(static_cast<int>(word_data.size() - 1));
    // 得到单词的首字母和尾字母
    ui->wordfirst_label->setText(word_data[cont].word.left(1));
    ui->wordlast_label->setText(word_data[cont].word.right(1));
    ui->meaning_lineEdit->setText(word_data[cont].meaning);

    // 当用户返回一个enter键时变化
    connect(ui->word_lineEdit, &QLineEdit::returnPressed,
            [=]()
            {
                // 将单词拼接完整，用于判断
                const QString key =
                    word_data[cont].word.left(1) + ui->word_lineEdit->text() + word_data[cont].word.right(1);

                if (key == word_data[cont].word)
                {
                    // 将用户拼写的单词数据插入数据库中
                    UserTable temp(word_data[cont].word, word_data[cont].meaning, ui->new_button->isChecked());
                    user_table.emplace_back(temp);
                    OperateData::PutInTable("cha", user_table, num);
                    num++;

                    // 正确时清空文本框
                    ui->word_lineEdit->clear();
                    ui->new_button->setChecked(false);

                    // 进入下一个随机单词
                    cont = OperateData::CreatRandom(static_cast<int>(word_data.size() - 1));
                    // 设置下一个填空
                    ui->wordfirst_label->setText(word_data[cont].word.left(1));
                    ui->wordlast_label->setText(word_data[cont].word.right(1));
                    ui->meaning_lineEdit->setText(word_data[cont].meaning);
                }
                else
                {
                    // 用户输入错误时，显示正确的结果
                    ui->word_lineEdit->setText(word_data[cont].word.mid(1,word_data[cont].word.size()-2));
              }
          });
}

WordSpelling::~WordSpelling() { delete ui; }
