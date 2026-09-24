# 执行计划

## Execution Plan

## 状态

Stage 2 设计已通过，Stage 3 已进入实现与验证阶段。已补充 `PageSceneRuleManager`
host toolchain 单元测试，覆盖 ruleJson、TEXT_EDITOR matcher 和注册/Get/注销基础 DFX 行为。
2026-07-06 追加 PageScene 稳定点调度实现和 ContentChangeManager UT。
2026-07-09 追加命中态退出规格：同一规则已上报过 `TEXT_EDITOR` 命中后，后续稳定点检查不再命中时上报一次 `TEXT_EDITOR_EXIT`，连续未命中不重复上报。
2026-07-13 对齐最终交付规格：`ruleJson` 顶层新增 `version=1`，文本输入类控件变化不再由 `reportOnTextInputAttached` 控制，补充独立反注册用户故事和接口级错误码测试规格。
2026-07-21 Owner 收缩本阶段范围：回退候选快照、增量计数、多 UIContext 路由和延迟构造等性能优化；上下树仅挂起待检测规则，稳定点全量扫描当前页面树。保留按节点 ID 列表去重。
2026-08-07 补充 Navigation 转场状态恢复缺陷修复：按实际登记的 NavDestination ID 跟踪活跃转场，并覆盖正常完成、节点提前下树、Navigation 整体下树及交互取消的 ID 释放。
2026-08-22 更新正式规格：`onlyVisible` 仅负责组件属性可见性过滤；新增 `rectCulling`（缺省 false）负责 viewport 相交过滤；增加 opacity 及父子树 dirty 通知，rect/page viewport 按需计算。

## 初始任务草案

| 任务 | 内容 | 状态 |
|------|------|------|
| TASK-001 | UISession IPC / ReportService 接口扩展：新增 SA 调用接口、transaction、proxy/stub、ReportService 回调、重复注册和 Get busy 返回 | Ready |
| TASK-002 | ruleJson 解析、校验和 Manager 状态：新增 `PageSceneRuleManager`、pid/ruleSet 状态、pending Get、operation busy、去重节流状态 | In Progress |
| TASK-003 | ArkUI 宿主 TEXT_EDITOR 匹配：注册、查询和稳定点检测均全量扫描当前页面树；`onlyVisible` 过滤组件属性可见性，`rectCulling` 独立过滤 viewport；去重仅比较上次上报节点 ID 列表 | In Progress |
| TASK-003A | Rect 计算与可见属性通知优化：按开关跳过无用 rect/page viewport 计算；增加 opacity dirty；父节点 visibility 变化只合并一次 dirty，稳定点重算父子树 | In Progress |
| TASK-004 | Web 规则透传通路：注册时透传 `webRules`，反注册和查询请求透传 | Ready |
| TASK-005 | UIExtension 规则透传通路：透传注册、反注册、查询请求 | Ready |
| TASK-006 | sample/hidumper 验证命令：补注册、查询、反注册命令和摘要日志 | Ready |
| TASK-007 | 单测和回归验证：覆盖 ruleJson、matcher、IPC、重复注册、Get pending busy、反注册/死亡清理、Web/UIExtension 透传入口、隐私日志，以及 Navigation 转场 ID 在正常完成、提前下树和交互取消后的释放 | In Progress |

## AC 到 Task 追溯

| AC 范围 | 任务 | 验证入口 |
|---------|------|----------|
| AC-1.1 - AC-1.5 | TASK-001, TASK-002, TASK-004, TASK-005 | UISession IPC/规则解析单测、Web/UIExtension 透传验证 |
| AC-2.1 - AC-2.6 | TASK-002, TASK-003, TASK-007 | `page_scene_rule_manager_test_ng`、TEXT_EDITOR matcher 四象限和 opacity 单测 |
| AC-3.1 - AC-3.7 | TASK-003, TASK-003A, TASK-007 | 稳定点全量检测、父子树状态重算、opacity 通知、上下树 ID 变化、坐标去重、退出事件单测 |
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
- `frameworks/core/components_ng/base/frame_node.h`
- `frameworks/core/components_ng/base/frame_node.cpp`
- `frameworks/core/components_ng/base/view_abstract.cpp`
- `interfaces/inner_api/ui_session/ui_session_manager.h`
- `frameworks/core/components_ng/pattern/navigation/navigation_pattern.h`
- `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp`
- `frameworks/core/components_ng/pattern/navigation/navigation_group_node.cpp`
- `frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h`
- `frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.cpp`
- `test/mock/frameworks/core/components_ng/pattern/navigation/mock_navigation_pattern.cpp`
- `test/unittest/core/manager/page_scene_rule_manager_test_ng.cpp`
- `test/unittest/core/pattern/navigation/navigation_pattern_test_five_ng.cpp`
- `test/unittest/core/pattern/navigation/navigation_animation_test_ng.cpp`

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
| 2026-07-21 | 回退候选索引、多 UIContext 路由和延迟构造等性能优化；保留节点 ID 列表去重、上下树触发稳定点全量重检。Host `page_scene_rule_manager_test_ng` 11/11、`content_change_manager_test_ng` 45/45 通过，产物均为 x86-64 ELF | Pass |
| 2026-07-21 | 从 OpenHarmony 根目录执行完整 `./build.sh --product-name rk3568 --build-target ace_engine --ccache`，Ninja 5888/5888 完成，`libace_compatible.z.so` 和最终 `ace_engine.stamp` 生成，构建输出 `rk3568 build success` / `build successful` | Pass |
| 2026-08-07 | 修复 Navigation 转场登记 NavDestination ID、整体下树却按 Navigation host ID 清理的不一致；补充正常完成、单 NavDestination 下树、Navigation 整体下树、多个 ID 独立清理及交互取消回归用例 | Code/UT Ready；编译与用例执行由 Owner 手工验证 |
| 2026-08-22 | 完成 `onlyVisible`/`rectCulling` 语义拆分、opacity 过滤与通知、父节点 visibility dirty 收敛、rect 按需计算及四象限/透明度/坐标去重测试补充；目标文件语法检查完成，完整 GN 构建受既有重复规则错误阻断，测试二进制未运行 | Code updated；Build/UT pending |

验证命令：

```bash
./build.sh --product-name host_product --build-target page_scene_rule_manager_test_ng --ccache --no-prebuilt-sdk=true
/home/l00441630/OpenHarmony/out/host/host_product/tests/unittest/ace_engine/TextSet-Text/page_scene_rule_manager_test_ng --gtest_filter=PageSceneRuleManagerTestNg.*
prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/host/host_product page_scene_rule_manager_test_ng
/home/l00441630/OpenHarmony/out/host/host_product/tests/unittest/ace_engine/TextSet-Text/page_scene_rule_manager_test_ng --gtest_filter=PageSceneRuleManagerTestNg.*
prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/rk3568 arkui/ace_engine/libace_compatible.z.so
prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/standard/src arkui/ace_engine/libace_compatible.z.so arkui/ace_engine/libui_session.z.so arkui/ace_engine/libui_sa.z.so
./build.sh --product-name rk3568 --build-target ace_engine --ccache
```

验证结论：2026-07-21 host toolchain 产物为 x86_64 Linux ELF，`PageSceneRuleManagerTestNg`
覆盖 11 条用例并全部通过，`ContentChangeManagerTestNg` 覆盖 45 条用例并全部通过。
同日完整 `rk3568 ace_engine` 构建完成 5888/5888，最终输出 `build successful`。
2026-07-09 `out/rk3568` 目标板 `arkui/ace_engine/libace_compatible.z.so` 增量编译通过。
目标板 `libace_compatible.z.so`、`libui_session.z.so`、
`libui_sa.z.so` 均已完成 ARM 32-bit 构建。设备镜像与代码产物完成匹配后继续执行
`Connect -> RegisterPageSceneRules -> GetPageScene -> UnregisterPageSceneRules`。当前仍待补充
IPC、SA 死亡清理和 Web/UIExtension 规则透传入口验证。

2026-08-07 Navigation 转场 ID 清理代码和定向 UT 已补齐；本轮不在 Agent 侧执行编译或
测试，Owner 手工验证命令和预期结果记录在
`evidence/checks/check-navigation-transition-id-cleanup.md`。在手工结果回填前，不将该项标记为 Pass。

## Stage 3 验证门槛

- `git diff --check`
- 新增/修改的 UISession 单元测试通过
- ruleJson 解析和 `TEXT_EDITOR` matcher 单元测试通过
- `ruleJson.version` 缺失或不支持版本返回参数错误，`version=1` 合法规则注册和查询通过
- `PageSceneInputCountTracker` 全量扫描、`onlyVisible` 属性过滤、`rectCulling` 屏内/屏外组合、opacity 过滤、坐标变化去重、上下树节点 ID 变化后重检和退出事件测试通过
- rect/page viewport 按需计算；父节点 visibility dirty 收敛、opacity 实际变化通知和稳定点父子树重算需完成目标板构建及运行时回归
- `TEXT_EDITOR` 已命中后跌出阈值时只上报一次 `TEXT_EDITOR_EXIT`，未曾命中和连续未命中均不补发退出事件，主动 `GetPageScene` 未命中仍使用 `TEXT_EDITOR`
- `ContentChangeManager` 稳定点调度测试通过：PageScene-only 注册、Page/Scroll/Dialog 稳定点、Swiper 延迟、滚动/转场/Swiper 滚动中不 flush；Navigation 转场在正常完成、NavDestination/Navigation 提前下树和交互取消后释放对应 destination ID，最后一个 ID 释放后 `IsTransitioning()` 为 false
- 代码检查确认 Pipeline 不直接调用 `UiSessionManager::FlushPageSceneNodeChanged`
- 代码检查确认 Text/Image 具体 ContentChange 路径不触发 PageScene-only 检测
- 重复注册、Get pending busy、反注册并发、SA 死亡清理测试通过
- Web 验证 `webRules` 原样透传及反注册、查询请求透传入口
- UIExtension 验证规则注册、反注册、查询请求透传入口
- `ui_session_sample` 构建通过，真机 hidumper 能完成 `Connect -> RegisterPageSceneRules -> GetPageScene -> UnregisterPageSceneRules`
- 默认配置下日志、回调 JSON 省略文本正文
