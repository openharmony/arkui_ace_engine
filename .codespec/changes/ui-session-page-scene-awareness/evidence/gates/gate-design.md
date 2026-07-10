# Design Gate

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| Stage 1 输入已继承 | 通过 | `design.md` 继承 `TEXT_EDITOR`、`ruleJson`、上报字段、Web/UIExtension 边界和隐私默认值 |
| 现有代码事实已核验 | 通过 | `design.md` 引用 `ui_content_service_interface.h`、`ui_content_stub.cpp`、`ui_session_manager.h`、`ui_session_manager_ohos.*`、`ui_content_impl.cpp` 等真实源码位置 |
| UISession 接口方案已明确 | 通过 | 明确 `RegisterPageSceneRules`、`UnregisterPageSceneRules`、`GetPageScene` 和 `ReportPageSceneEvent` 的职责、callback 路由及 DFX 并发保护 |
| 规则解析和扩展模型已明确 | 通过 | 明确 `PageSceneRuleManager`、ruleSet/rule/report 状态结构、校验规则和 scene/operator/source 扩展方式 |
| 首批 ArkUI 匹配设计已明确 | 通过 | 明确 `TEXT_EDITOR` tag 白名单、`PageSceneInputCountTracker` 页面可见输入控件计数维护、首次注册初始化扫描、文本输入类控件上下树增量维护、可见性/可获焦/rect 计算策略 |
| Web 透传边界已明确 | 通过 | 明确 `webRules` 注册透传、反注册和查询请求透传 |
| UIExtension 透传边界已明确 | 通过 | 明确规则注册、反注册、查询请求透传 |
| 隐私和安全约束已明确 | 通过 | 默认不上报文本正文，日志只输出摘要，非法 ruleJson 不保存不触发 |
| 错误恢复已明确 | 通过 | 覆盖非 SA 调用、非法参数、重复注册、Get pending busy、未连接 ReportService、SA 死亡、来源不支持、节流去重 |
| 测试验证计划已明确 | 通过 | 覆盖 ruleJson、ArkUI matcher、UISession IPC、并发 DFX、Web/UIExtension 规则透传入口、sample/hidumper |
| 测试向规格已拆分 | 通过 | 新增 `spec-for-test.md`，自包含复制 AC/API/规则，并补充测试数据、验证方式、2D/2C 和 DFX 测试维度 |
| 实现阶段稳定点约束已回写 | 通过 | 2026-07-06 已将 PageScene-only 复用 `ContentChangeManager` 页面稳定点、Pipeline 不直接 flush PageScene、Text/Image 具体事件不触发 PageScene-only 检测等关键点同步到 `spec.md`、`design.md`、`spec-for-test.md` 和 `execution-plan.md` |

## 结论

Design 阶段通过。

允许进入 Stage 3：实现任务拆解与代码验证。
