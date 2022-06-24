#include <QCoreApplication>
#include "include/HCNetSDK.h"
#include<QDebug>
long Login(char* IP,WORD port , char * userName,char * passWord)
{
    NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
    long userID=NET_DVR_Login_V30(IP,port,userName,passWord,&DeviceInfoTmp);
    if(userID<0)
    {
        qDebug() << "NET_DVR_Login_V30 error;" << "error number is " << NET_DVR_GetLastError();

        return -1;
    }
    qDebug()<<"Login Success,userID:" << userID<<endl;
    return userID;
}

bool initSDK()
{
    bool isok = NET_DVR_Init();
    if(isok == false)
    {
        qDebug()<< "NET_DVR_Init error;error number is " <<NET_DVR_GetLastError();

        return isok;
    }
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    return isok;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    initSDK();
    long lUserID = Login("192.168.1.64",8000,"admin","123456789a");



      //获取压缩参数

      DWORD dwReturnLen;
      BV_CALIBRATION_TYPE_ENUM struParams ;
       bool ret = NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_BV_CALIB_TYPE, 1, &struParams, sizeof(struParams), &dwReturnLen);
                if(!ret){
                    DWORD  t= NET_DVR_GetLastError();
                    qDebug() << t;
                    return  -1;                }
    qDebug() <<"标定信息"<< struParams;


//      int i =struParams.byLensType;
//      qDebug() << "焦距类型"<< i;

//      NET_DVR_BINOC_RECTIFY_PARAM L = struParams.struLCamParam;
//      NET_DVR_BINOC_RECTIFY_PARAM R = struParams.struRCamParam;

//      qDebug() << L.fDistCoeffs;
//      qDebug() << L.fRotateMatrix;
//      qDebug() << L.fProjectMatrix;
//      qDebug() << L.fCamInternalMatrix;









    return a.exec();
}
