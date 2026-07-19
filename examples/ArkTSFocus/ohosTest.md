# ArkTSFocus 测试用例归档

## 用例表

| 测试功能 | 预置条件 | 输入 | 预期输出 | 是否自动 | 测试结果 |
| --- | --- | --- | --- | :------- | -------- |
| defaultFocus 验证 | 设备正常运行 | 1.进入首页<br/>2.点击"基础焦点能力" | 页面加载时 Button A（defaultFocus）自动获焦变色 | 是 | Pass |
| onFocus/onBlur 验证 | 进入 BasicFocus 页面 | 1.按 Tab 键切换焦点 | 失焦按钮变灰，获焦按钮变色，状态文字更新 | 是 | Pass |
| focusable(false) 验证 | 进入 BasicFocus 页面 | 1.连续按 Tab 键 | focusable(false) 的 Text 不会被聚焦 | 是 | Pass |
| tabIndex 顺序验证 | 进入 TabNavigation 页面 | 1.连续按 Tab 键 3 次 | 焦点按 tabIndex 1→2→3 顺序跳转（Button 2→3→1） | 是 | Pass |
| tabStop 跳过验证 | 进入 TabNavigation 页面 | 1.按 Tab 键循环 | Button 4（tabStop: false）被跳过 | 是 | Pass |
| nextFocus 方向验证 | 进入 CustomNextFocus 页面 | 1.聚焦 B3<br/>2.按右方向键 | 跳转到配置的 nextFocus.right 目标 B4 | 是 | Pass |
| nextFocus 上下验证 | 进入 CustomNextFocus 页面 | 1.聚焦 B3<br/>2.按下方向键 | 跳转到配置的 nextFocus.down 目标 B5 | 是 | Pass |
| 焦点域分组验证 | 进入 FocusScope 页面 | 1.在 Scope A 内按 Tab | 焦点在 A1→A2→A3 间循环 | 是 | Pass |
| groupDefaultFocus 验证 | 进入 FocusScope 页面 | 1.从 Scope A 按 Tab 进入 Scope B | 默认聚焦 groupDefaultFocus 节点 B2 | 是 | Pass |
| 焦点框样式验证 | 进入 FocusBoxStyle 页面 | 1.聚焦自定义按钮 | 显示红色 3px 自定义焦点框（区别于默认样式） | 是 | Pass |
| focusOnTouch 验证 | 进入 FocusOnTouch 页面 | 1.点击触摸区域 | 区域获焦变色（focusOnTouch 开启时） | 是 | Pass |
| focusOnTouch 关闭验证 | 进入 FocusOnTouch 页面 | 1.关闭 focusOnTouch<br/>2.点击触摸区域 | 区域不获焦，颜色不变 | 是 | Pass |
| 命令式 requestFocus 验证 | 进入 FocusOnTouch 页面 | 1.点击"请求聚焦"按钮 | 指定 id 的组件获焦变色 | 是 | Pass |
