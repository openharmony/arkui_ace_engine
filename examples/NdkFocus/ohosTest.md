# NdkFocus 测试用例归档

## 用例表

| 测试功能            | 预置条件       | 输入          | 预期输出                    | 是否自动 | 测试结果 |
| ------------------- | -------------- |-------------|-------------------------| :------- | -------- |
| NODE_DEFAULT_FOCUS示例代码验证    | 设备正常运行   | 设置Buttondefault为默认焦点 | 打开首页，Buttondefault默认获焦，背景色变为红色 | 是       | Pass     |
| NODE_FOCUSABLE和OH_ArkUI_FocusRequest示例代码验证    | 设备正常运行   | 1.设置Button0不可获焦，给Button0请求焦点<br/>2.设置Button0可获焦，给Button0请求焦点 | 1.Button0未获焦，返回错误码150002<br/>2.Button0获焦，背景色变为红色 | 是       | Pass     |
| OH_ArkUI_FocusClear和NODE_FOCUS_STATE示例代码验证    | 设备正常运行   | 1.通过NODE_FOCUS_STATE异步请求Button1焦点<br/>2.通过OH_ArkUI_FocusClear清理焦点到根容器 | 1.Button1获焦，背景色变成红色<br/>2.Button1失焦，背景色变为黑色 | 是       | Pass     |
| NODE_FOCUS_ON_TOUCH示例代码验证    | 设备正常运行   | 1.配置Button2不可触摸获焦，并点击<br/>2.配置Button3可触摸获焦并点击 | 1.Button2未获焦，背景色保持蓝色<br/>2.Button3获焦，背景色变为红色 | 是       | Pass     |
| NODE_TAB_STOP示例代码验证    | 设备正常运行   | 1.配置Button4父组件NODE_TAB_STOP为true后给Button3请求焦点并使用Tab走焦<br/>2.按下Enter键 | 1.Tab走焦后，Button4未获焦，焦点停留在Button4父组件上<br/>2.Button4获焦，背景色变为红色 | 是       | Pass     |
| NODE_NEXT_FOCUS示例代码验证    | 设备正常运行   | 配置Button5的Tab键走焦的组件为Button7，让Button5获焦并使用Tab键走焦 | 焦点可以从Button5通过Tab走焦Button7，Button6未获焦过，背景色不变 | 是       | Pass     |
| NODE_FOCUS_BOX示例代码验证    | 设备正常运行   | 配置Button8的NODE_FOCUS_BOX，让Button8获焦并进入走焦态 | 焦点框为自定义的黄色外框 | 是       | Pass     |
| OH_ArkUI_FocusSetAutoTransfer示例代码验证    | 设备正常运行   | 给Button9请求焦点，设置AutoTransfer为false，通过菜单测试按钮拉起menu | Button9保持焦点，背景为红色 | 是       | Pass     |