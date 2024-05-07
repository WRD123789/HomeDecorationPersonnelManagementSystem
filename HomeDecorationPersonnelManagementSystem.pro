QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountinstance.cpp \
    accountmodel.cpp \
    addcustomer.cpp \
    addemployee.cpp \
    adminclient.cpp \
    admincustomertable.cpp \
    adminemployeetable.cpp \
    adminprojecttable.cpp \
    client.cpp \
    connectdatabase.cpp \
    customermodel.cpp \
    customertable.cpp \
    designdirectorclient.cpp \
    designdirectorprojtable.cpp \
    designerclient.cpp \
    designerprojtable.cpp \
    designertable.cpp \
    employeeinfo.cpp \
    employeemodel.cpp \
    financeclient.cpp \
    financemodel.cpp \
    financeprojtable.cpp \
    information.cpp \
    infotable.cpp \
    main.cpp \
    mainwindow.cpp \
    managerprojtable.cpp \
    modifycustomer.cpp \
    modifyfinance.cpp \
    modifypassword.cpp \
    projectdirectorclient.cpp \
    projectdirectorprojtable.cpp \
    projectinfo.cpp \
    projectlist.cpp \
    projectmanagerclient.cpp \
    projectmanagertable.cpp \
    projectmodel.cpp \
    salesmanclient.cpp \
    solvedprojecttable.cpp

HEADERS += \
    account.h \
    accountinstance.h \
    accountmodel.h \
    addcustomer.h \
    addemployee.h \
    adminclient.h \
    admincustomertable.h \
    adminemployeetable.h \
    adminprojecttable.h \
    client.h \
    connectdatabase.h \
    customer.h \
    customermodel.h \
    customertable.h \
    designdirectorclient.h \
    designdirectorprojtable.h \
    designerclient.h \
    designerprojtable.h \
    designertable.h \
    employee.h \
    employeeinfo.h \
    employeemodel.h \
    finance.h \
    financeclient.h \
    financemodel.h \
    financeprojtable.h \
    information.h \
    infotable.h \
    mainwindow.h \
    managerprojtable.h \
    modifycustomer.h \
    modifyfinance.h \
    modifypassword.h \
    project.h \
    projectdirectorclient.h \
    projectdirectorprojtable.h \
    projectinfo.h \
    projectlist.h \
    projectmanagerclient.h \
    projectmanagertable.h \
    projectmodel.h \
    salesmanclient.h \
    solvedprojecttable.h

FORMS += \
    client.ui \
    mainwindow.ui \
    infotable.ui \
    information.ui \
    modifypassword.ui \
    projectinfo.ui \
    addcustomer.ui \
    modifyfinance.ui \
    addemployee.ui \
    modifycustomer.ui \
    connectdatabase.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
