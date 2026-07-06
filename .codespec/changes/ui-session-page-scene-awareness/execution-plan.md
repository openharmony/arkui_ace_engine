# Execution Plan

## 状态

Stage 2 设计已通过，Stage 3 已进入实现与验证阶段。已补充 `PageSceneRuleManager`
host toolchain 单元测试，覆盖 ruleJson、TEXT_EDITOR matcher 和注册/Get/注销基础 DFX 行为。
2026-07-06 追加 PageScene 稳定点调度实现和 ContentChangeManager UT：输入类控件上下树只维护计数和待检测规则，页面稳定后再检查并上报。

## 初始任务草案

| 任务 | 内容 | 状态 |
|------|------|------|
| TASK-001 | UISession IPC / ReportService 接口扩展：新增 SA 调用接口、transaction、proxy/stub、ReportService 回调、重复注册和 Get busy 返回 | Ready |
| TASK-002 | ruleJson 解析、校验和 Manager 状态：新增 `PageSceneRuleManager`、pid/ruleSet 状态、pending Get、operation busy、去重节流状态 | In Progress |
| TASK-003 | ArkUI 宿主 TEXT_EDITOR 匹配：新增 `PageSceneInputCountTracker`，注册/查询初始化页面可见输入控件计数，文本输入类控件上下树增量维护数量并挂起待检测规则，rect/focusable/visible 过滤，页面稳定后检测 | In Progress |
| TASK-004 | Web 规则透传通路：注册时透传 `webRules`，反注册和查询请求透传，不设计 `webRules` 规格，不实现 Web 内部匹配和回传 | Ready |
| TASK-005 | UIExtension 规则透传通路：透传注册、反注册、查询请求，不实现 UIExtension 内部匹配和回传 | Ready |
| TASK-006 | sample/hidumper 验证命令：补注册、查询、反注册命令和摘要日志 | Ready |
| TASK-007 | 单测和回归验证：覆盖 ruleJson、matcher、IPC、重复注册、Get pending busy、反注册/死亡清理、Web/UIExtension 透传入口、隐私日志 | In Progress |

## Stage 3 当前验证记录

| 日期 | 范围 | 结果 |
|------|------|------|
| 2026-07-03 | 新增 `page_scene_rule_manager_test_ng`，覆盖 ruleJson 解析/非法参数、重复注册、Get pending busy、注销清理、TEXT_EDITOR 匹配、不可获焦输入控件过滤与包含配置、`currentPageName` / `rect` / `focusable` 上报、`includeText=false` 默认不含 text、无完整树上报、去重和 `ClearProcess` | Pass |
| 2026-07-06 | 补充 `includeText=true` 场景：节点上报携带用户输入文本或输入为空时的占位提示文本；移除完整树上报 ruleJson 规格；sample PageScene 回调日志改为只打印长度，完整结果后续通过 `-tofile` 验证 | Pass |
| 2026-07-06 | 补充 `content_change_manager_test_ng` 用例，覆盖 PageScene-only VSync flush、Page/Scroll/Dialog 稳定点触发、Swiper 延迟到 VSync、Swiper 滚动中不 flush 且稳定后 flush；确认 PageScene-only 不发送 ContentChange 事件 | Pass |
| 2026-07-06 | rk3568 编译 `ui_session` 和 `//foundation/arkui/ace_engine/frameworks/core/components_ng/manager:ace_core_components_manager_ng_ohos`，确认 UISession 接口和 ContentChangeManager 目标板 toolchain 编译通过 | Pass |
| 2026-07-06 | 重新构建目标板 32 位 `libace_compatible.z.so`、`libui_session.z.so`、`libui_sa.z.so`，确认产物为 ARM 32-bit ELF；设备端当前镜像与代码产物存在不匹配，推库 E2E 待重新刷机后执行 | Deferred |

验证命令：

```bash
./build.sh --product-name host_product --build-target page_scene_rule_manager_test_ng --ccache --no-prebuilt-sdk=true
/home/l00441630/OpenHarmony/out/host/host_product/tests/unittest/ace_engine/TextSet-Text/page_scene_rule_manager_test_ng --gtest_filter=PageSceneRuleManagerTestNg.*
prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/standard/src arkui/ace_engine/libace_compatible.z.so arkui/ace_engine/libui_session.z.so arkui/ace_engine/libui_sa.z.so
```

验证结论：host toolchain 产物为 x86_64 Linux ELF，7 条 `PageSceneRuleManagerTestNg`
gtest 全部通过；目标板 `libace_compatible.z.so`、`libui_session.z.so`、
`libui_sa.z.so` 均已完成 ARM 32-bit 构建。当前设备镜像与代码产物存在不匹配，
本轮不做推库端到端判定，待重新刷机后继续执行
`Connect -> RegisterPageSceneRules -> GetPageScene -> UnregisterPageSceneRules`。当前仍待补充
IPC、SA 死亡清理、Web/UIExtension 规则透传入口以及 `PageSceneInputCountTracker`
动态上树/下树阈值跨越后挂起检测、稳定点 flush 相关 UT。

## Stage 3 验证门槛

- `git diff --check`
- 新增/修改的 UISession 单元测试通过
- ruleJson 解析和 `TEXT_EDITOR` matcher 单元测试通过
- `PageSceneInputCountTracker` 初始化扫描、上树计数增加、下树计数减少、阈值跨越后挂起检测、页面稳定后上报测试通过
- `ContentChangeManager` 稳定点调度测试通过：PageScene-only 注册、Page/Scroll/Dialog 稳定点、Swiper 延迟、滚动/转场/Swiper 滚动中不 flush
- 代码检查确认 Pipeline 不直接调用 `UiSessionManager::FlushPageSceneNodeChanged`
- 代码检查确认 Text/Image 具体 ContentChange 路径不触发 PageScene-only 检测
- 重复注册、Get pending busy、反注册并发、SA 死亡清理测试通过
- Web 只验证 `webRules` 原样透传及反注册、查询请求透传入口；不验证 `webRules` 内部规格、Web 内部匹配和上报
- UIExtension 只验证规则注册、反注册、查询请求透传入口；不验证内部匹配和上报
- `ui_session_sample` 构建通过，真机 hidumper 能完成 `Connect -> RegisterPageSceneRules -> GetPageScene -> UnregisterPageSceneRules`
- 默认配置下日志、回调 JSON 不包含文本正文和完整控件树
