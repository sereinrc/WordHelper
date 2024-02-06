//
// Created by charles on 24-2-1.
//

#ifndef WORDHELPER_OPERATEDATA_H
#define WORDHELPER_OPERATEDATA_H
#include <QString>
#include <utility>
#include <vector>

// 储存单词及意思
struct CET
{
    QString word;
    QString meaning;

    CET(QString a, QString b) : word(std::move(a)), meaning(std::move(b)) {}
};

// 用户表
struct UserTable
{
    QString word;
    QString meaning;
    int is_new = 0;  // 判断是否为生词，0为否，1为是

    UserTable(QString a, QString b, const int c) : word(std::move(a)), meaning(std::move(b)), is_new(c) {}
};

struct UserData
{
    QString word;
    QString meaning;
    QString data;
    int is_new;
    QString notes;
    UserData(QString a, QString b, QString c, const int d, QString e) :
        word(std::move(a)), meaning(std::move(b)), data(std::move(c)), is_new(d), notes(std::move(e))
    {
    }
};

extern std::vector<CET> word_data;
extern std::vector<UserTable> user_table;
extern std::vector<UserData> user_data;
extern QStringList date_list;

class OperateData
{
public:
    explicit OperateData();

    ~OperateData();

    static void InitialData(const QString &table_name, const QString &user_name);
    static void InitialData(const QString &user_name);
    static void PutInTable(const QString &user_name, const std::vector<UserTable> &user_table_sec, int num);
    static int CreatRandom(int max);
    static  void ChangeData(const QString &user_name,const QString &date);

private:
    static void OpenDB();
    static void CreateTable(const QString &user_name);
};


#endif  // WORDHELPER_OPERATEDATA_H
