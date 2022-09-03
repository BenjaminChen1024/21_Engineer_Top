# 21_Engineer_Top
Robomaster Competition engineering robot embedded software code.



### Motor ID

| LeftExtendMotor_ID  | 0x201 |
| :------------------ | ----- |
| RightExtendMotor_ID | 0x202 |
| LeftRotateMotor_ID  | 0x203 |
| RightRotateMotor_ID | 0x204 |
| LeftLiftMotor_ID    | 0x205 |
| RightLiftMotor_ID   | 0x206 |
| TurnMotor_ID        | 0x207 |



### Motor Steering

| LeftExtend_PosPID  | +    |
| ------------------ | ---- |
| RightExtend_PosPID | -    |
| LeftRotate_PosPID  | +    |
| RightRotate_PosPID | -    |
| LeftLift_PosPID    | +    |
| RightLift_PosPID   | +    |



### Photoelectric switch

| PB5  | 正常 | 左下光电门 | F1   |
| ---- | ---- | ---------- | ---- |
| PB6  | 正常 | 右下光电门 | F2   |
| PB8  | 正常 |            |      |
| PB3  | 正常 |            |      |
| PB4  | 正常 | 识矿光电门 | F5   |
| PB9  | 正常 |            |      |
| PA4  | 正常 | 右上光电门 | F7   |
| PC2  | 正常 | 左上光电门 | F8   |



### Relay

| PC5  | 1    | 夹取     |
| ---- | ---- | -------- |
| PC4  | 2    | 普通救援 |
| PB1  | 3    | 舵宝救援 |
| PB0  | 4    | 刷卡     |



### Visual flag

| IdentifyBox识别矿石     | 0：无操作 | 1：夹取成功 | 2：夹取失败     |         |         |
| ----------------------- | --------- | ----------- | --------------- | ------- | ------- |
| Turn_to_Hor水平旋转     | 0：无操作 | 1：正转     | 2：调整结束     | 3：反转 |         |
| Turn_to_QR定位旋转      | 0：无操作 | 1：R上      | 2：二维码       | 3：R下  | 4：空白 |
| Extend_Back伸出收回调整 | 0：无操作 | 1：伸出收回 | 2：伸出收回结束 |         |         |



### Motor encoder values

| Rotate Motor                          | Extend Motor                           | Lift Motor                           |
| ------------------------------------- | -------------------------------------- | ------------------------------------ |
| Rotate_Pos_Limit = 960000.0f          | Extension_Buffer_Zone = 20000.0f       | Lift_Buffer_Zone = 50000.0f          |
| Rotate_Pos_Limit_Middle = 88000.0f    | Vision_Extension_Pos = 600.0f          | None_Lift_Pos = 0.0f                 |
| Rotate_Pos_Hor = 78000.0f             | None_Extension_Pos = 10000.0f          | First_Lift_Pos = 50000.0f            |
| Rotate_Pos_Hor_Middle = 70000.0f      | Mini_Extension_Pos = 50000.0f          | Second_Lift_Pos = 500000.0f          |
| Rotate_Pos_Exchange = 64000.0f        | First_Extension_Pos= 		200000.0f | Third_Lift_Pos = 1400000.0f          |
| Rotate_Pos_Exchange_Middle = 56000.0f | Second_Extension_Pos = 420000.0f       | Take_BigBox_Lift_Pos = 600000.0f     |
| Rotate_Pos_Top = 50000.0f             | Extension_Pos_Limit = 420000.0f        | Take_SmallBox_Lift_Pos = 1400000.0f; |
| Rotate_Pos_Top_Middle = 42000.0f      |                                        | Exchange_Box_Lift_Pos = 1400000.0f;  |
| Rotate_Back_Start_Middle = 9000.0f    |                                        | Lift_Pos_Limit = 1400000.0f;         |
| Rotate_Pos_Start = 1000.0f            |                                        |                                      |









