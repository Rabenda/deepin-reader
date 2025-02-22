/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     gaoxiang <gaoxiang@uniontech.com>
*
* Maintainer: gaoxiang <gaoxiang@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "FileAttrWidget.h"
#include "Global.h"
#include "DocSheet.h"
#include "ut_defines.h"

#include "stub.h"

#include <gtest/gtest.h>
#include <QTest>
#include <QVBoxLayout>
namespace  {
class TestFileAttrWidget : public ::testing::Test
{
public:
    TestFileAttrWidget(): m_tester(nullptr) {}

public:
    virtual void SetUp()
    {
        m_tester = new FileAttrWidget();
        m_tester->disconnect();
    }

    virtual void TearDown()
    {
        delete m_tester;
    }

protected:
    FileAttrWidget *m_tester;
};

static QString g_funcname;
static void show_stub()
{
    g_funcname = __FUNCTION__;
}
}

TEST_F(TestFileAttrWidget, initTest)
{

}

TEST_F(TestFileAttrWidget, testsetFileAttr)
{
    int childrencount = m_tester->m_pVBoxLayout->children().count();
    m_tester->setFileAttr(nullptr);
    EXPECT_EQ(m_tester->m_pVBoxLayout->children().count(), childrencount + 0) ;

    QString filePath = QCoreApplication::applicationDirPath() + "/" + "files" + "/" + UT_FILE_PDF;
    if (!QFile(filePath).exists() && QFile(":/files/" + QString(UT_FILE_PDF)).exists()) {
        QDir().mkpath(QCoreApplication::applicationDirPath() + "/" + "files");
        QFile(":/files/" + QString(UT_FILE_PDF)).copy(filePath);
    }
    DocSheet *sheet = new DocSheet(Dr::FileType::PDF, filePath, m_tester);
    m_tester->setFileAttr(sheet);
    EXPECT_EQ(m_tester->m_pVBoxLayout->children().count(), childrencount + 1) ;
}

TEST_F(TestFileAttrWidget, testaddTitleFrame)
{
    int childrencount = m_tester->children().count();
    m_tester->addTitleFrame("111111");
    EXPECT_EQ(m_tester->children().count(), childrencount + 1);
}

TEST_F(TestFileAttrWidget, testshowScreenCenter)
{
    Stub s;
    s.set(ADDR(QWidget, show), show_stub);
    m_tester->showScreenCenter();
    EXPECT_TRUE(g_funcname == "show_stub");
}
