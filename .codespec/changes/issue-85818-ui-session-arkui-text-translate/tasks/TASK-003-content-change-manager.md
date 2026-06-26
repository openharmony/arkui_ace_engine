# TASK-003: ContentChangeManager ArkUI 文本节点快照、增量和版本

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-003 |
| 标题 | 增强 ContentChangeManager 承载 ArkUI 文本翻译节点管理 |
| 关联 Feature | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 目标仓库 | ace_engine |
| 目标模块 | frameworks/core/components_ng/manager/content_change_manager |
| 分支 | dev |
| 优先级 | P0 |
| 复杂度 | 高 |
| 执行方式 | 主线程顺序执行 |

## 任务描述

### 做什么

1. 在 `ContentChangeManager` 中新增 translate 专用入口和待翻译文本容器，例如 `ReportTranslateTextNode`、节点弱引用集合、version/hash、pending、scope、active flag；容器存储类型必须是 `WeakPtr<PageTranslateNode>` 等抽象接口类型，不保存具体 Pattern 或 `FrameNode` 翻译业务对象。
2. Text/RichEditor/TextField Pattern 在上树、离树、只读展示资格变化、placeholder 展示资格变化、文本实际绘制变化时通过 `PageTranslateNode` 接口调用 translate 专用入口；不得通过 `AddOnContentChangeNode` / `RemoveOnContentChangeNode` 这类纯内容变化监听接口接入翻译节点。
3. 只有 translate active 时才允许写入 translate 专用容器；未 StartTranslate 时触发点只做常量级开关判断后返回。
4. 增加 ArkUI 文本 snapshot 接口，收集 `Text`、Span/styled string、readonly `RichEditor`、空内容 `TextInput` 当前实际展示的 placeholder，排除输入类控件用户可编辑文本、自绘、Canvas、OCR；单次 Get 必须使用隔离 snapshot cache 保存 node 弱引用、snapshot version 和 source hash，不写入连续翻译容器。
5. Start 后根据 translate 专用入口收到的文本实际绘制和文本变化事件生成 `NODE_ADDED` / `CONTENT_CHANGED` 内部原因，对 SA 只发 `nodeId/text/version`。
6. 过滤仅占位布局、未实际绘制文本的节点；后续首次实际绘制时再上报。
7. End/Reset/SA death/连续会话结束时只清理 translate 专用容器中的节点版本、pending 和临时译文状态，不清理纯 content change 容器；单次 Get timeout 只清理 snapshot cache 和一次性状态，不误清连续监听容器。
8. 单次 `GetPageTranslateText` 只做快照收集并写隔离 snapshot cache，不开启 translate active，不留下连续监听状态；不得通过临时置 `textTranslateActive_ = true` 复用 `ReportTranslateTextNode()` 写入 `translateTextNodes_` / `translateTextVersions_`。
9. 单次 snapshot 回填必须同时校验 nodeId、snapshot version 和 source hash；当前源文本已变化时忽略迟到译文，避免旧译文覆盖新文本。

### 不做什么

- 不新增 `TextTranslateNodeManager`。
- 不处理 Web 脚本注入。
- 不向 SA 暴露节点来源或变化类型。
- 不让纯 content change start/stop/config 与 translate start/end/reset 共享运行时监听容器。
- 不使用 `AddOnContentChangeNode` / `RemoveOnContentChangeNode` 承载翻译节点注册。

## 规格映射与边界

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-1, AC-4 | spec.md | snapshot 单测 |
| AC-6, AC-7, AC-14, AC-14a | spec.md | 增量/过滤单测 |
| AC-10, AC-11, AC-13 | spec.md | reset/version 单测 |

| Rule ID | Must / Must Not |
|---------|-----------------|
| DRAWN-TEXT-ONLY | 仅实际文本绘制内容上报 |
| DATA-MIN | 对 SA 只输出 `nodeId/text/version` |
| RUNTIME-ONLY | 清理只影响运行时临时状态 |
| TRANSLATE-NODE-IFACE | manager 只保存 `WeakPtr<PageTranslateNode>`，回填和 Reset 只调用接口方法；`FrameNode` 仅用于页面遍历和可见区域判断 |
| LISTENER-ISOLATION | 翻译监听使用 `ContentChangeManager` 内独立注册/反注册入口和待翻译文本容器；纯内容变化监听和翻译监听的 start/stop/config/cleanup 不得互相影响 |
| ON-DEMAND-WRITE | 未处于连续翻译状态时不写连续 translate 容器、不维护 pending、不投递 translate 延迟任务；单次 Get 仅写隔离 snapshot cache，并在请求边界清理 |
| SMALL-FUNCTION-REUSE | 与纯 content change 共享的节点判断、实际绘制过滤、version/hash 更新、弱引用清理和 DFX dump 摘要生成必须抽成私有小函数复用，避免复制粘贴 |
| BUILD-MIN | 编译 content_change_manager 所属组件/so 目标和 content_change_manager unittest |

## 复用函数要求

| 候选小函数 | 用途 | 约束 |
|------------|------|------|
| `IsValidTranslateTextNode` | 统一判断 Text / readonly RichEditor / 空内容 TextInput placeholder 是否可进入翻译容器 | 不读取或修改纯 content change 容器状态 |
| `HasActualTextPaintContent` | 统一实际文本绘制过滤 | 未 StartTranslate 时不得触发文本提取的重计算 |
| `BuildTranslateTextSnapshot` | 生成 nodeId/text/version 的内部快照 | 对 SA payload 只输出 `nodeId/text/version` |
| `CollectTranslateTextSnapshot` | 单次 Get 的隔离快照收集 | 不修改 active flag、连续 translate 容器、连续版本缓存或 pending；可写 snapshot cache 的 node 弱引用、snapshot version 和 source hash |
| `CleanupTranslateSnapshotCache` | 清理单次 Get 的隔离快照缓存 | 在新请求开始、单次完成、失败、timeout、End/Reset/SA death 时调用，不清理纯 content change 容器 |
| `UpdateTranslateVersionIfNeeded` | 比较文本摘要并维护 version/hash | 仅 translate active 时调用 |
| `CleanupTranslateNodeState` | 清理弱引用、pending、临时译文状态 | 不清理纯 content change 容器 |
| `BuildSafeTranslateDumpInfo` | 生成非正文 DFX 摘要 | 禁止输出原文/译文 |

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `frameworks/core/components_ng/manager/content_change_manager/content_change_manager.h` | 新增 translate 专用注册/反注册入口、待翻译文本容器、版本状态和接口 |
| 修改 | `frameworks/core/components_ng/manager/content_change_manager/content_change_manager.cpp` | snapshot、增量、version、清理、监听隔离 |
| 新增 | `frameworks/core/components_ng/pattern/page_translate/page_translate_node.h` | 可翻译节点抽象接口；ArkUI 方法为纯虚，Web hook 为默认空实现 |
| 修改 | `frameworks/core/pipeline_ng/pipeline_context.*` | 暴露 manager 调用入口 |
| 修改 | `test/mock/frameworks/core/components_ng/manager/content_change_manager/mock_content_change_manager.cpp` | mock 新接口 |
| 测试 | `test/unittest/core/manager/content_change_manager_test_ng.cpp` | 节点注册、过滤、version、reset |

## 完成判据

- snapshot 只返回 scope 覆盖且实际绘制文本的节点。
- `ContentChangeManager` 的连续和 snapshot 翻译节点缓存只保存 `WeakPtr<PageTranslateNode>`，UT 可通过轻量接口桩覆盖上报、回填和 Reset。
- 翻译节点注册/反注册通过 translate 专用入口完成，不调用 `AddOnContentChangeNode` / `RemoveOnContentChangeNode`。
- 相同 nodeId 相同文本不重复上报，文本变化 version 增加。
- 节点离树只做 UI 内部清理，不生成 `NODE_REMOVED`。
- Reset/End/SA death 可清理连续翻译状态和临时译文；单次 Get timeout 可清理 snapshot cache 和一次性状态，不误清纯 content change 容器。
- 纯 content change 监听开启/停止不改变 translate 容器；translate Start/End/Reset 不改变纯 content change 容器。
- 未 StartTranslate 时，上树/离树/文本变化触发点不会写 translate 容器、不会计算 translate version/hash、不会投递 translate 任务。
- 单次 GetPageTranslateText 不留下连续监听状态。
- 单次 GetPageTranslateText 完成后 `translateTextNodes_`、连续版本缓存、pending 和 active flag 与调用前一致；snapshot cache 在请求完成、失败或 timeout 后清空。
- 单次 snapshot 译文回填在 nodeId/version 匹配但 source hash 已变化时忽略该条结果。
- 共用逻辑通过私有小函数复用，任务实现中不得出现多处分叉复制同一段节点过滤、version/hash 或清理逻辑。

## 停止条件

- 无法从 Pattern 或 content change hook 判断实际文本绘制状态。
- RichEditor 只读状态无法在该层可靠识别，需要 Task-005 先提供接口。
- 现有 `ContentChangeManager` 生命周期钩子无法同时驱动两套独立容器，需回传修订设计。

## 验证检查清单

- [ ] content_change_manager 单测覆盖 snapshot、增量、实际绘制过滤、version 去重、reset 清理、翻译监听与纯 content change 监听隔离、未 Start 时无连续 translate 容器写入、单次 Get 不改变 active flag/连续版本缓存/连续节点缓存/pending
- [ ] content_change_manager 单测覆盖 snapshot cache 请求边界清理、snapshot version/source hash 防迟到译文回填
- [ ] 编译 content_change_manager 所属组件/so 目标；必要时补相关 unittest 目标
