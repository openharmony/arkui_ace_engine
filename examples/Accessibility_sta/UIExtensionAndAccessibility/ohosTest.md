# UIExtensionAndAccessibility 测试用例归档

## 用例表

|测试功能|预置条件|输入|预期输出|是否自动|测试结果|
|--------------------------------|--------------------------------|--------------------------------|--------------------------------|--------------------------------|--------------------------------|
|拉起应用|设备正常运行||成功拉起应用，首页显示5个按钮：UIExtensionComponent、EmbeddedComponent、FullScreenLaunchComponent、Accessibility、ShowPage|是|Pass|
|进入UIExtensionComponent界面|在首页|点击 UIExtensionComponent 按钮|进入 UIExtensionComponent 子页面，显示 UIExtension 按钮|是|Pass|
|进入EmbeddedComponent界面|在首页|点击 EmbeddedComponent 按钮|进入 EmbeddedComponent 子页面，显示 Embedded 按钮|是|Pass|
|进入FullScreenLaunchComponent界面|在首页|点击 FullScreenLaunchComponent 按钮|进入 FullScreenLaunchComponent 子页面，显示 FullScreenLaunch 按钮|是|Pass|
|进入Accessibility界面|在首页|点击 Accessibility 按钮|进入 UniversalAttributesAccessibility 子页面，显示10个无障碍功能按钮|是|Pass|
|进入ShowPage界面|在首页|点击 ShowPage 按钮|进入 ShowPage 页面，显示原生渲染内容|是|Pass|
|UIExtensionComponent 组件页面|在 UIExtensionComponent 子页面|点击 UIExtension 按钮|进入 UIExtension 页面，显示 UIExtensionComponent 组件及数据收发按钮|是|Pass|
|EmbeddedComponent 组件页面|在 EmbeddedComponent 子页面|点击 Embedded 按钮|进入 Embedded 页面，显示 EmbeddedComponent 组件|是|Pass|
|FullScreenLaunchComponent 组件页面|在 FullScreenLaunchComponent 子页面|点击 FullScreenLaunch 按钮|进入 FullScreenLaunch 页面，显示 FullScreenLaunchComponent 组件|是|Pass|
|UIExtensionComponent 发送数据|在 UIExtension 页面，UIExtensionComponent 已连接|点击发送按钮|通过 proxy.send/sendSync 发送数据到 Provider，Provider 端 storageLink 更新显示收到的数据|是|Pass|
|UIExtensionComponent 接收数据|在 Provider 端 Extension 页面|点击 button1 按钮|Provider 通过 session.sendData 回传数据，Host 端 onReceive 触发，message3 更新显示|是|Pass|
|AccessibilityText 页面|在 Accessibility 子页面|点击 AccessibilityText 按钮|进入 AccessibilityText 页面，显示无障碍文本属性示例|是|Pass|
|AccessibilityGroup 页面|在 Accessibility 子页面|点击 AccessibilityGroup 按钮|进入 AccessibilityGroup 页面，显示无障碍分组属性示例|是|Pass|
|AccessibilityFocusDrawLevel 页面|在 Accessibility 子页面|点击 AccessibilityFocusDrawLevel 按钮|进入 AccessibilityFocusDrawLevel 页面，显示无障碍焦点绘制层级示例|是|Pass|
|AccessibilityTextCase01 页面|在 Accessibility 子页面|点击 AccessibilityTextCase01 按钮|进入 AccessibilityTextCase01 页面|是|Pass|
|AccessibilityTextCase02 页面|在 Accessibility 子页面|点击 AccessibilityTextCase02 按钮|进入 AccessibilityTextCase02 页面|是|Pass|
|AccessibilityDescriptionCase01 页面|在 Accessibility 子页面|点击 AccessibilityDescriptionCase01 按钮|进入 AccessibilityDescriptionCase01 页面|是|Pass|
|AccessibilityDescriptionCase02 页面|在 Accessibility 子页面|点击 AccessibilityDescriptionCase02 按钮|进入 AccessibilityDescriptionCase02 页面|是|Pass|
|AccessibilityGroupCase01 页面|在 Accessibility 子页面|点击 AccessibilityGroupCase01 按钮|进入 AccessibilityGroupCase01 页面|是|Pass|
|AccessibilityGroupCase02 页面|在 Accessibility 子页面|点击 AccessibilityGroupCase02 按钮|进入 AccessibilityGroupCase02 页面|是|Pass|
|AccessibilityLevelCase01 页面|在 Accessibility 子页面|点击 AccessibilityLevelCase01 按钮|进入 AccessibilityLevelCase01 页面|是|Pass|
