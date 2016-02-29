#include <Wire.h>
 
void setup()
{
  Wire.begin(2);   // 報告大家, 我是 2 號 IIC 設備喔, 在此等待服務主人
  Wire.onRequest(ggyy); // 註冊 ! 如果主人給我命令, 就調用函數 ggyy( )
}
 
void loop()
{
  // 我是僕人, 平常沒事做
}
 
// 這函數必須在 setup( ) 內用 onRequest( ) 註冊!
void ggyy()
{
  Wire.write("Hello "); // 送出 6 個 char 給 IIC 上的主人
} // loop(
