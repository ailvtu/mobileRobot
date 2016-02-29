#include <Wire.h>
 
void setup()
{
  Wire.begin();        // join i2c bus (我是主人, 不必報告 IIC 號碼)
  Serial.begin(9600);  // 串口輸出
}
 
void loop()
{
  Wire.requestFrom(2, 6);    // 要求 2號僕人 透過 Wire 送 6 char 過來!
 
  while(Wire.available())    // 如果Wire上還有 char 等我讀取
  { 
    char c = Wire.read(); // 從 Wire 讀取一個 char
    Serial.print(c);      // 送到串口監視器查看
  }
 
  delay(5500);  // 等 5.5秒
  Serial.println( ); // 故意換到下一行方便查看
} // loop(
