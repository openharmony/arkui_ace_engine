# DFX Dump Mechanism Context

> 文档版本：v1.1
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `DFXDumpMechanism`

## 定位

DFX Dump Mechanism 是 ArkUI 引擎的 Dump 诊断基础设施，涵盖 DumpLog 树日志引擎与 Pipeline 命令路由、Inspector 树形诊断系统、SimplifiedInspector 简化树、可访问性 Dump 与事件 Dump。它不是对外公共 API，而是引擎内部 DFX 能力，是开发调试和故障诊断的核心工具。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体 Dump 命令路由、Inspector 输出、诊断数据结构应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| DumpLog 核心 | `frameworks/base/log/dump_log.h` | DumpLog 单例、参数过滤、JSON 序列化、命令路由 |
| Inspector NG | `frameworks/core/components_ng/base/inspector.h` | NG Inspector、组件树 JSON 诊断、InspectorFilter 属性过滤 |
| SimplifiedInspector | `frameworks/core/components_ng/base/simplified_inspector.h` | 简化版 Inspector，只输出核心属性，性能敏感场景 |
| InspectorFilter | `frameworks/core/components_ng/base/inspector_filter.h` | InspectorFilter 属性过滤逻辑 |
| Pipeline Dump 命令 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | PipelineContext Dump，支持 -contentChange 等多种诊断参数 |

### API 入口

DFX Dump Mechanism 是引擎内部能力，没有独立 SDK API。Inspector 功能通过 DevEco IDE 和 hidumper 命令间接使用。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| zlib 压缩 | `frameworks/base/log/dump_log.cpp` | third_party/zlib | `zlib.h` | deflateInit/deflate/deflateEnd dump 输出压缩（条件编译 OHOS_PLATFORM） |
| RenderService RSUIDirector | `frameworks/core/pipeline_ng/pipeline_context.cpp` | `foundation/graphic/graphic_2d` | `render_service_client/core/ui/rs_ui_context.h` | Dump 时 GetRSUIDirector → GetIndex 写入 transactionFlags |
| Accessibility 框架 | `adapter/ohos/osal/js_accessibility_manager.cpp` | `foundation/accessibility` | `accessibility/accessibility_hidumper_osal.h` | 可访问性 hidumper 适配层 |
| hidumper 系统命令 | `adapter/ohos/entrance/ace_container.cpp` | 系统 hidumper 工具 | 命令行 → AceContainer::Dump binder 入口 | 外部 hidumper 命令通过 binder 线程调入引擎 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| DumpRecorder 测试 | `test/unittest/base/dump_recorder_test.cpp` | DumpRecorder、CompareDumpParam、记录/过滤测试 |
| FrameNode Dump | `test/unittest/core/base/frame_node_test_ng_dump.cpp` | FrameNode DumpPadding/DumpOverlayInfo/DumpCommonInfo |
| EventDump 测试 | `test/unittest/core/event/event_dump_test_ng.cpp` | EventDump 事件树记录、max 限制、JSON |
| Scroll Dump | `test/unittest/core/pattern/scroll/scroll_dump_test_ng.cpp` | ScrollPattern ScrollBar Dump |
| Inspector NG | `test/unittest/core/base/inspector_test_ng.cpp` | NG Inspector、InspectorFilter 快照生成 |
| SimplifiedInspector | `test/unittest/core/base/simplified_inspector_test_ng.cpp` | SimplifiedInspector 简化属性 Dump |
| LayoutInspector | `test/unittest/adapter/ohos/entrance/layout_inspector_test.cpp` | LayoutInspector 3D 快照过滤 |
| AccessibilityHidumper | `test/unittest/core/accessibility/hidumper/accessibitlity_hidumper_test.cpp` | 可访问性 hidumper 组件树可访问性 Dump |

### 相关 Spec

Dump 机制功能域：`specs/03-engine-framework/08-dfx-foundation/04-dump-mechanism/`（功能 ID `03-08-04`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| DumpLog 核心引擎与 Pipeline 命令路由 | `specs/03-engine-framework/08-dfx-foundation/04-dump-mechanism/Feat-01-dump-log-pipeline-routing-spec.md` | DumpLog 命令路由、参数过滤、JSON 序列化 |
| Inspector 树形诊断系统 | `specs/03-engine-framework/08-dfx-foundation/04-dump-mechanism/Feat-02-inspector-tree-diagnostic-spec.md` | NG Inspector、InspectorFilter、组件树 JSON 诊断 |
| SimplifiedInspector 与简化树 | `specs/03-engine-framework/08-dfx-foundation/04-dump-mechanism/Feat-03-simplified-inspector-spec.md` | SimplifiedInspector 简化版、性能敏感场景 |
| 可访问性 Dump 与事件 Dump | `specs/03-engine-framework/08-dfx-foundation/04-dump-mechanism/Feat-04-accessibility-event-dump-spec.md` | AccessibilityHidumper、事件 Dump、可访问性 Dump |
| 设计文档 | `specs/03-engine-framework/08-dfx-foundation/04-dump-mechanism/design.md` | 整体架构设计、ADR |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Dump 命令不路由到目标处理函数 | DumpLog 命令注册、PipelineContext dump 参数、命令到处理函数的映射 |
| Inspector 输出不完整/格式错误 | InspectorFilter 属性过滤逻辑、Inspector JSON 序列化 |
| SimplifiedInspector 性能开销大 | SimplifiedInspector 属性裁剪、只输出核心属性 |
| 可访问性 Dump 不输出 | AccessibilityHidumper 注册时机、dump 命令路由 |
| 事件 Dump 数据量过大 | EventDump MAX_EVENT_TREE_RECORD_COUNT 限制、记录裁剪 |

## 调试入口

- DumpLog 断点：DumpLog::GetInstance() 命令注册、参数解析、JSON 输出
- Inspector 断点：Inspector::Inspect、InspectorFilter 属性过滤、组件树遍历
- PipelineContext Dump 命令：PipelineContext dump 参数、-contentChange、-inspector、-render 等
- AccessibilityHidumper 断点：AccessibilityHidumper dump 命令、OSAL 适配

## 相关主题

- 日志：`docs/kb/architecture/dfx/logging.md`
- 内存管理：`docs/kb/architecture/dfx/memory-management.md`
- Trace 打点：`docs/kb/architecture/dfx/trace.md`
- 布局边界显示：`docs/kb/architecture/dfx/layout-boundary-display.md`
