#include "Headers/OperateData.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <random>

std::vector<CET> word_data;
std::vector<UserTable> user_table;

OperateData::OperateData() = default;

OperateData::~OperateData() = default;


//打开数据库
void OperateData::OpenDB()
{
    auto db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("qt");
    db.setUserName("sereinrc");
    db.setPassword("123456");
    if (const bool ok = db.open(); !ok)
    {
        qDebug() << "error open database because" << db.lastError().text();
    }
}

//初始化数据
void OperateData::InitialData(const QString& table_name, const QString& user_name)
{
    // 打开数据库
    OpenDB();
    //创建用户表
    CreateTable(user_name);
    // 选择对应的表格,将其加入队列中
    auto sql = QString("select * from ");
    sql = sql + table_name;
    QSqlQuery query;
    query.exec(sql);

    // 循环遍历，将数据加载至向量中
    while (query.next())
    {
        const QString data1 = query.value(0).toString();
        const QString data2 = query.value(1).toString();
        CET a(data1, data2);
        word_data.emplace_back(a);
    }
}

//创建用户表
void OperateData::CreateTable(const QString& user_name)
{
    QSqlQuery query;
    QString temp = "create table " + user_name +
        " (word text null,meaning text null,date date null,is_new int null,notes text null)";
    query.exec(temp);
    temp = "collate = uca1400_as_ci";
    query.exec(temp);
}

// 将数据插入到用户表中
void OperateData::PutInTable(const QString& user_name, const std::vector<UserTable>& user_table_sec, const int num)
{
    QSqlQuery query;
    const QString temp = "INSERT INTO " + user_name + " (word ,meaning ,date ,is_new) VALUES (?,?,DATE(NOW()),?)";
    query.prepare(temp);
    query.bindValue(0, user_table_sec[num].word);
    query.bindValue(1, user_table_sec[num].meaning);
    query.bindValue(2, user_table_sec[num].is_new);
    query.exec();
}

//传出一个单词表范围内的随机数
int OperateData::CreatRandom(int max)
{
    std::random_device seed;
    std::ranlux48 engine(seed());
    std::uniform_int_distribution<> distrib(0,max);
    const int random=distrib(engine);
    return random;
}
