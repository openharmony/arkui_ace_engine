| 测试功能     | 预置条件     | 输入                   | 预期输出                    | 测试结果 |
| ------------ | ------------ | ---------------------- | --------------------------- | -------- |
| 首页加载测试 | 设备正常运行 | 验证基础元素渲染       | 页面加载成功,检查标题和列表组件显示正常         | Pass     |
| 一键截图 | 设备正常运行 | 1. 点击"ScrollSnapshot"<br/>2. 点击"Scroll Screenshot"<br/>3. 点击"One-Tap Screenshot" | 截图成功，图片显示无异常 | Pass     |
| 滚动截图 | 设备正常运行 | 1. 点击"ScrollSnapshot"<br/>2. 点击"Scroll Screenshot"<br/>3. 点击"Scrolling Snapshot" | 截图成功，图片显示无异常 | Pass     |
| 封装全局截图接口 | 设备正常运行 | 1. 点击"GlobalSnapshot"<br/>2.点击"click to get snapshot" | 显示区域内item索引增加 | Pass     |


