# NdkKeyEvent 测试用例归档

## 用例表

| 测试功能                                     | 预置条件       | 输入                            | 预期输出                                                  | 是否自动 | 测试结果 |
|------------------------------------------| -------------- |-------------------------------|-------------------------------------------------------| :------- | -------- |
| NODE_ON_KEY_EVENT示例验证                    | 设备正常运行   | 进入首页，点击第一个Button后按下A          | Button变成浅红色                                           | 是       | Pass     |
| NODE_ON_KEY_PRE_IME示例代码验证                | 设备正常运行   | 进入首页，点击第二个Button后按下A          | Button变成浅红色                                           | 是       | Pass     |
| NODE_DISPATCH_KEY_EVENT示例代码验证            | 设备正常运行   | 进入首页，点击第三个Button后按下A          | Button变成浅红色                                           | 是       | Pass     |
| OH_ArkUI_KeyEvent_SetConsumed和OH_ArkUI_KeyEvent_StopPropagation事件冒泡示例代码验证 | 设备正常运行   | 进入首页，点击第四个Button后分别按下ESC、F1、A | Button均变浅红色，ESC和F1拦截事件冒泡，外层Column不变色，按下A后外层Column变浅红色 | 是       | Pass     |