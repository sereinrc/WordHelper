#include "Headers/worddictation.h"

#include <QMediaPlayer>

#include "Forms/ui_worddictation.h"
#include "Headers/OperateData.h"


WordDictation::WordDictation(QWidget* parent) : QDialog(parent), ui(new Ui::WordDictation)
{
    ui->setupUi(this);
    // 连接数据库，并创建用户表
    OperateData::InitialData("cet4", "cha");
    ui->top_label->setText("cet4");
    // 设置标题居中
    ui->top_label->setAlignment(Qt::AlignHCenter);

    // 开始听力练习
    cont = OperateData::CreatRandom(static_cast<int>(word_data.size() - 1));
    Dictation(word_data[cont].word);
    connect(ui->word_lineEdit, &QLineEdit::returnPressed,
            [=]()
            {
                if (ui->word_lineEdit->text() == word_data[cont].word)
                {
                    // 正确时清空文本框
                    ui->word_lineEdit->clear();
                    ui->meaning_lineEdit->clear();

                    // 将用户听写的单词数据插入数据库中
                    UserTable temp(word_data[cont].word, word_data[cont].meaning, ui->new_button->isChecked());
                    user_table.emplace_back(temp);
                    OperateData::PutInTable("cha", user_table, num);

                    // 将按钮初始化
                    ui->new_button->setChecked(false);

                    // 进入下一个单词
                    cont = OperateData::CreatRandom(static_cast<int>(word_data.size() - 1));
                    num++;
                }
                else
                {
                    // 用户输入错误时，显示正确的结果
                    ui->word_lineEdit->setText(word_data[cont].word);
                    ui->meaning_lineEdit->setText(word_data[cont].meaning);
                }
            });

    connect(ui->again_button, &QPushButton::pressed, [=]() { Dictation(word_data[cont].word); });
}

WordDictation::~WordDictation() { delete ui; }

// 根据单词连接网络音频发音
void WordDictation::Dictation(const QString &word)
{
    const QString key = "https://dict.youdao.com/dictvoice?audio={" + word + "}&type={1}";
    const QUrl audio_url(key);
    auto* player = new QMediaPlayer;
    player->setMedia(audio_url);
    player->setVolume(50); //0~100音量范围,默认是100
    player->play();
}