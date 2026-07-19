# 执行计划

## Execution Plan

## 状态

Stage 2 设计已通过，Stage 3 已进入实现与验证阶段。已补充 `PageSceneRuleManager`
host toolchain 单元测试，覆盖 ruleJson、TEXT_EDITOR matcher 和注册/Get/注销基础 DFX 行为。
2026-07-06 追加 PageScene 稳定点调度实现和 ContentChangeManager UT：输入类控件上下树只维护计数和待检测规则，页面稳定后再检查并上报。
2026-07-09 追加命中态退出规格：同一规则已上报过 `TEXT_EDITOR` 命中后，后续稳定点检查不再命中时上报一次 `TEXT_EDITOR_EXIT`，连续未命中不重复上报。
2026-07-13 对齐最终交付规格：`ruleJson` 顶层新增 `version=1`，文本输入类控件变化不再由 `reportOnTextInputAttached` 控制，补充独立反注册用户故事和接口级错误码测试规格。

## 初始任务草案

| 任务 | 内容 | 状态 |
|------|------|------|
| TASK-001 | UISession IPC / ReportService 接口扩展：新增 SA 调用接口、transaction、proxy/stub、ReportService 回调、重复注册和 Get busy 返回 | Ready |
| TASK-002 | ruleJson 解析、校验和 Manager 状态：新增 `PageSceneRuleManager`、pid/ruleSet 状态、pending Get、operation busy、去重节流状态 | In Progress |
| TASK-003 | ArkUI 宿主 TEXT_EDITOR 匹配：新增 `PageSceneInputCountTracker`，注册/查询初始化页面可见输入控件计数，文本输入类控件上下树增量维护数量并挂起待检测规则，rect/focusable/visible 过滤，页面稳定后检测 | In Progress |
| TASK-004 | Web 规则透传通路：注册时透传 `webRules`，反注册和查询请求透传 | Ready |
| TASK-005 | UIExtension 规则透传通路：透传注册、反注册、查询请求 | Ready |
| TASK-006 | sample/hidumper 验证命令：补注册、查询、反注册命令和摘要日志 | Ready |
| TASK-007 | 单测和回归验证：覆盖 ruleJson、matcher、IPC、重复注册、Get pending busy、反注册/死亡清理、Web/UIExtension 透传入口、隐私日志 | In Progress |

## AC 到 Task 追溯

| AC 范围 | 任务 | 验证入口 |
|---------|------|----------|
| AC-1.1 - AC-1.5 | TASK-001, TASK-002, TASK-004, TASK-005 | UISession IPC/规则解析单测、Web/UIExtension 透传验证 |
| AC-2.1 - AC-2.4 | TASK-002, TASK-003, TASK-007 | `page_scene_rule_manager_test_ng`、TEXT_EDITOR matcher 单测 |
| AC-3.1 - AC-3.5 | TASK-003, TASK-007 | 稳定点检测、上下树计数、退出事件单测 |
| AC-4.1 - AC-4.4 | TASK-001, TASK-002, TASK-003, TASK-004 | GetPageScene 参数、busy 和回调路径验证 |
| AC-5.1 - AC-5.4 | TASK-004, TASK-005 | Web/UIExtension 注册、查询和反注册透传验证 |
| AC-5A.1 - AC-5A.3 | TASK-001, TASK-002, TASK-004, TASK-005, TASK-007 | UnregisterPageSceneRules 单测、sample/mock 验证 |
| AC-6.1 - AC-6.4 | TASK-002, TASK-003, TASK-007 | includeText/includeRect/includeFocusable 输出验证 |
| AC-7.1 - AC-7.4 | TASK-003, TASK-007 | ContentChangeManager 稳定点调度单测和代码检查 |
| AC-8.1 - AC-8.4 | TASK-001, TASK-002, TASK-007 | 重复注册、Get busy、并发反注册和死亡清理验证 |

## 受影响文件全量清单

- `.codespec/changes/ui-session-page-scene-awareness/manifest.md`
- `.codespec/changes/ui-session-page-scene-awareness/proposal.md`
- `.codespec/changes/ui-session-page-scene-awareness/spec.md`
- `.codespec/changes/ui-session-page-scene-awareness/design.md`
- `.codespec/changes/ui-session-page-scene-awareness/spec-for-test.md`
- `.codespec/changes/ui-session-page-scene-awareness/execution-plan.md`
- `adapter/ohos/entrance/ui_session/ui_session_manager_ohos.h`
- `adapter/ohos/entrance/ui_session/ui_session_manager_ohos.cpp`
- `frameworks/core/components_ng/manager/page_scene/page_scene_rule_manager.h`
- `frameworks/core/components_ng/manager/page_scene/page_scene_rule_manager.cpp`
- `test/unittest/core/manager/page_scene_rule_manager_test_ng.cpp`

## Stage 3 当前验证记录

| 日期 | 范围 | 结果 |
|------|------|------|
| 2026-07-03 | 新增 `page_scene_rule_manager_test_ng`，覆盖 ruleJson 解析/非法参数、重复注册、Get pending busy、注销清理、TEXT_EDITOR 匹配、不可获焦输入控件过滤与包含配置、`currentPageName` / `rect` / `focusable` 上报、`includeText=false` 默认不含 text、去重和 `ClearProcess` | Pass |
| 2026-07-06 | 补充 `includeText=true` 场景：节点上报携带用户输入文本或输入为空时的占位提示文本；sample PageScene 回调日志改为只打印长度，完整结果后续通过 `-tofile` 验证 | Pass |
| 2026-07-06 | 补充 `content_change_manager_test_ng` 用例，覆盖 PageScene-only VSync flush、Page/Scroll/Dialog 稳定点触发、Swiper 延迟到 VSync、Swiper 滚动中不 flush 且稳定后 flush；确认 PageScene-only 不发送 ContentChange 事件 | Pass |
| 2026-07-06 | rk3568 编译 `ui_session` 和 `//foundation/arkui/ace_engine/frameworks/core/components_ng/manager:ace_core_components_manager_ng_ohos`，确认 UISession 接口和 ContentChangeManager 目标板 toolchain 编译通过 | Pass |
| 2026-07-06 | 重新构建目标板 32 位 `libace_compatible.z.so`、`libui_session.z.so`、`libui_sa.z.so`，确认产物为 ARM 32-bit ELF；设备端镜像与代码产物完成匹配后执行推库 E2E | Pending |
| 2026-07-09 | 补充 `page_scene_rule_manager_test_ng` 用例，覆盖未曾命中不发退出、命中后跌出阈值上报一次 `TEXT_EDITOR_EXIT`、主动 Get 未命中仍返回 `TEXT_EDITOR`、退出后再次命中可重新上报 | Pass |
| 2026-07-09 | rk3568 增量编译 `arkui/ace_engine/libace_compatible.z.so`，确认 PageScene manager 改动在目标板 toolchain 下通过 | Pass |
| 2026-07-13 | 补充 `ruleJson.version` 解析校验，移除 `reportOnTextInputAttached` 规则字段依赖；补充 SDD unregister 故事、输出示例和接口错误码测试规格；`page_scene_rule_manager_test_ng --gtest_filter=PageSceneRuleManagerTestNg.*` 8 条用例通过；`ohos-sdd validate --level all` 33 项通过 | Pass |

验证命令：

```bash
./build.sh --product-name host_product --build-target page_scene_rule_manager_test_ng --ccache --no-prebuilt-sdk=true
/home/l00441630/OpenHarmony/out/host/host_product/tests/unittest/ace_engine/TextSet-Text/page_scene_rule_manager_test_ng --gtest_filter=PageSceneRuleManagerTestNg.*
prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/host/host_product page_scene_rule_manager_test_ng
/home/l00441630/OpenHarmony/out/host/host_product/tests/unittest/ace_engine/TextSet-Text/page_scene_rule_manager_test_ng --gtest_filter=PageSceneRuleManagerTestNg.*
prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/rk3568 arkui/ace_engine/libace_compatible.z.so
prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/standard/src arkui/ace_engine/libace_compatible.z.so arkui/ace_engine/libui_session.z.so arkui/ace_engine/libui_sa.z.so
```

验证结论：host toolchain 产物为 x86_64 Linux ELF，7 条 `PageSceneRuleManagerTestNg`
gtest 全部通过；2026-07-09 新增退出事件用例后，`PageSceneRuleManagerTestNg`
覆盖 8 条用例并全部通过；2026-07-09 `out/rk3568` 目标板
`arkui/ace_engine/libace_compatible.z.so` 增量编译通过。目标板 `libace_compatible.z.so`、`libui_session.z.so`、
`libui_sa.z.so` 均已完成 ARM 32-bit 构建。设备镜像与代码产物完成匹配后继续执行
`Connect -> RegisterPageSceneRules -> GetPageScene -> UnregisterPageSceneRules`。当前仍待补充
IPC、SA 死亡清理、Web/UIExtension 规则透传入口以及 `PageSceneInputCountTracker`
动态上树/下树阈值跨越后挂起检测、稳定点 flush 相关 UT。

## Stage 3 验证门槛

- `git diff --check`
- 新增/修改的 UISession 单元测试通过
- ruleJson 解析和 `TEXT_EDITOR` matcher 单元测试通过
- `ruleJson.version` 缺失或不支持版本返回参数错误，`version=1` 合法规则注册和查询通过
- `PageSceneInputCountTracker` 初始化扫描、上树计数增加、下树计数减少、阈值跨越后挂起检测、页面稳定后上报测试通过
- `TEXT_EDITOR` 已命中后跌出阈值时只上报一次 `TEXT_EDITOR_EXIT`，未曾命中和连续未命中均不补发退出事件，主动 `GetPageScene` 未命中仍使用 `TEXT_EDITOR`
- `ContentChangeManager` 稳定点调度测试通过：PageScene-only 注册、Page/Scroll/Dialog 稳定点、Swiper 延迟、滚动/转场/Swiper 滚动中不 flush
- 代码检查确认 Pipeline 不直接调用 `UiSessionManager::FlushPageSceneNodeChanged`
- 代码检查确认 Text/Image 具体 ContentChange 路径不触发 PageScene-only 检测
- 重复注册、Get pending busy、反注册并发、SA 死亡清理测试通过
- Web 验证 `webRules` 原样透传及反注册、查询请求透传入口
- UIExtension 验证规则注册、反注册、查询请求透传入口
- `ui_session_sample` 构建通过，真机 hidumper 能完成 `Connect -> RegisterPageSceneRules -> GetPageScene -> UnregisterPageSceneRules`
- 默认配置下日志、回调 JSON 省略文本正文
