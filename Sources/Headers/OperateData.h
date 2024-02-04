//
// Created by charles on 24-2-1.
//

#ifndef WORDHELPER_OPERATEDATA_H
#define WORDHELPER_OPERATEDATA_H
#include <QString>
#include <vector>

//储存单词及意思
struct CET
{
    QString word;
    QString meaning;

    CET(QString a, QString b) : word(std::move(a)), meaning(std::move(b)) {}
};

//用户表
struct UserTable
{
    QString word;
    QString meaning;
    int is_new = 0; //判断是否为生词，0为否，1为是

    UserTable(QString a, QString b, const int c) : word(std::move(a)), meaning(std::move(b)), is_new(c) {}
};

extern std::vector<CET> word_data;
extern std::vector<UserTable> user_table;

class OperateData
{
public:
    explicit OperateData();

    ~OperateData();

    static void InitialData(const QString &table_name, const QString &user_name);
    static void PutInTable(const QString &user_name, const std::vector<UserTable> &user_table_sec, int num);
    static int CreatRandom(int max);

private:
    static void OpenDB();

    static void CreateTable(const QString &user_name);
};


#endif  // WORDHELPER_OPERATEDATA_H
