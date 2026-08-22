# Inspector Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `Inspector`

## 定位

Inspector 是 ArkUI 引擎的组件树序列化与诊断能力，把运行时 `FrameNode`/`UINode` 树按属性过滤生成 JSON（供 DevEco Studio Inspector、UiSession 自动化测试消费）。核心是 `NG::Inspector` 静态方法集 + `InspectorFilter` 逐属性过滤 + `SimplifiedInspector` 异步采集 + `LayoutInspector` 平台调度入口，通过 `@ohos.arkui.inspector` 对外提供 `getInspectorTree`/`getInspectorByKey`/`sendEventByKey`/`getFilteredInspectorTree*` 与 `createComponentObserver`。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体属性过滤位、JSON 字段、过滤深度语义应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG Inspector 主实现 | `frameworks/core/components_ng/base/inspector.cpp` | 静态方法集；`GetInspector(isLayoutInspector, filter, needThrow)` 主树转储入口、`GetInspectorNodeByKey`、`GetRectangleById`、`GetInspectorTree`、`SendEventByKey` |
| NG Inspector 声明 | `frameworks/core/components_ng/base/inspector.h` | `Inspector` 类 + `InspectorOffscreenNodesMgr` 离屏节点管理 |
| SimplifiedInspector | `frameworks/core/components_ng/base/simplified_inspector.cpp` | 异步树采集 + UICommand 执行；DevEco/UiSession 路径；`TestScrollToTarget` |
| InspectorFilter（权威声明） | `interfaces/inner_api/ace_kit/include/ui/base/inspector_filter.h` | `InspectorFilter` + `FixedAttrBit` 枚举 + `TreeKey` 命名空间 + `InspectorConfig`（AceKit inner-API 面） |
| InspectorFilter 实现 | `frameworks/core/components_ng/base/inspector_filter.cpp` | `inspector_filter.h` 是 21 行 shim，真正实现在 AceKit 头 + 此 cpp |
| LayoutInspector（平台调度） | `adapter/ohos/osal/layout_inspector.cpp` | OHOS 实现；调用 `NG::Inspector::GetInspector(true)`；`ProcessMessages` 解析 `{windowId, method}` 消息；3D 快照/RS profiler 钩子 |
| LayoutInspector 头/跨平台 | `frameworks/core/common/layout_inspector.h` | `SupportInspector`、`GetInspectorTreeJsonStr`、`CreateLayoutInfo`、`GetSnapshotJson` |
| InspectorTreeCollector | `frameworks/core/common/recorder/inspector_tree_collector.h` | 异步 JSON 聚合，被 `SimplifiedInspector::GetInspectorAsync` 使用 |
| Pipeline 集成 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | `GetInspectorTree`（后台线程构建 JSON → `UiSessionManager::ReportInspectorTreeValue`）、`DumpInspector`（DFX Dump 桥） |
| 声明式 Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register.cpp` | `NG::Inspector::GetInspector/GetInspectorNodeByKey/SendEventByKey` JS 侧入口（含 V2 fallback） |
| CJ FFI 入口 | `frameworks/bridge/cj_frontend/interfaces/cj_ffi/cj_component_id_ffi.cpp` | Cangjie 前端 inspector 入口（NG 路径） |
| Preview Inspector | `adapter/preview/inspector/js_inspector_manager.cpp` | 预览器 inspector 客户端 → `NG::Inspector::GetInspector(false)` |
| Legacy V2 Inspector | `frameworks/core/components_v2/inspector/inspector.h` | 旧 `V2::Inspector`（`RefPtr<PipelineContext>`），历史路径，新代码用 NG |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK d.ts | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.inspector.d.ts` | `@ohos.arkui.inspector` 公共声明（路径以 SDK 仓实际为准） |
| Static SDK d.ets | `<OH_ROOT>/interface/sdk-js/api/arkui/inspector.static.d.ets` | 静态 ArkTS 声明（路径以 SDK 仓实际为准） |
| NAPI 模块（动态） | `interfaces/napi/kits/inspector/js_inspector.cpp` | 模块名 `arkui.inspector`；仅导出 `createComponentObserver`（组件观察者/布局回调入口） |
| ANI 模块（静态） | `interfaces/ets/ani/inspector/src/inspector.cpp` | 富 API：`getInspectorTree`/`getInspectorByKey`/`sendEventByKey`/`getFilteredInspectorTree*` 原生绑定 |
| ANI ArkTS 定义 | `interfaces/ets/ani/inspector/ets/@ohos.arkui.inspector.ets` | `getInspectorTree`、`createComponentObserver`、`InspectorTreeSerializeTool` 等 ArkTS 定义 |
| Inner API（AceKit） | `interfaces/inner_api/ace_kit/include/ui/base/inspector_filter.h` | `InspectorFilter`/`FixedAttrBit`/`TreeKey`/`InspectorConfig` 对外暴露 |
| C API / NDK | 无 | Inspector 不作为 Node C-API 暴露（区别于 modifier 体系），仅 ArkTS + inner-API |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| DevEco Inspector 桥接 | `adapter/ohos/osal/layout_inspector.cpp`（`dlopen` + `ConnectServerManager`） | `<OH_ROOT>/foundation/communication/connect_server` | `libark_connect_inspector.z.so`（dlsym 符号 `SetArkUICallback`） | 运行时 `dlopen("libark_connect_inspector.z.so")` 取 `SetArkUICallback`，经 `ConnectServerManager::SendInspector` 把树 JSON 推给 DevEco Inspector |
| 图形渲染/窗口 | `adapter/ohos/osal/layout_inspector.cpp`（`GetWindow`） | `<OH_ROOT>/foundation/graphic/graphic_2d` | `render_service_client/core/pipeline/rs_node_map.h` | `OHOS::Rosen::Window::Find/GetTopWindowWithId` 按 containerId 取窗口用于 layout 信息采集与快照 |

> 本仓 `frameworks/core/common/connect_server_manager.h` 是对 connect-server SO 的内部封装；外部依赖点为该 SO 本身与 Rosen 渲染服务。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| NG Inspector 单测 | `test/unittest/core/base/inspector_test_ng.cpp` | `GetInspectorNodeByKey`、`GetInspector(true/false)`、`SendEventByKey`、filter、free-nodes 解析、`GetRectangleById` |
| SimplifiedInspector 单测 | `test/unittest/core/base/simplified_inspector_test_ng.cpp` | 异步采集与 UICommand 执行回归 |
| LayoutInspector 测试 | `test/unittest/adapter/ohos/entrance/layout_inspector_test.cpp` | `ProcessMessages` 消息解析、3D 快照、profiler 钩子 |
| LayoutInspector Mock | `test/mock/frameworks/core/common/mock_layout_inspector.cpp` | `SupportInspector` 等 Pipeline 测试替身 |
| Pipeline Dump 测试 | `test/unittest/core/pipeline/pipeline_context_test_ng_seven.cpp` | `PipelineContext::DumpInspector` |

### 相关 Spec

Inspector 功能域：`specs/03-engine-framework/07-accessibility-mechanism/02-inspector/`（功能 ID `03-07-02`，当前 spec_status `pending`：已在 registry 注册，但目录与 Feat 规格尚未创建）。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| DevEco Inspector 拿不到树 | `LayoutInspector::SupportInspector`（pipeline 设置期）、`adapter/ohos/osal/layout_inspector.cpp` 消息链、connect-server |
| JSON 树属性缺失/过多 | `InspectorFilter` 的 `FixedAttrBit` 位掩码、`AddFilterAttr`、`SetFilterDepth`、各属性 `DumpInfo(json, filter)` |
| 异步树不回报 | `PipelineContext::GetInspectorTree` 后台线程派发、`UiSessionManager::ReportInspectorTreeValue`、`SimplifiedInspector::GetInspectorAsync` |
| `getInspectorByKey` 返回空 | `Inspector::GetFrameNodeByKey` key 查找、节点是否已 detach、`GetInspectorNodeByKey` |
| `sendEventByKey` 不生效 | `Inspector::SendEventByKey` action/params 解析、目标节点命中 |
| offscreen 节点丢失 | `InspectorOffscreenNodesMgr` 注册/查询、`GetFreeNodesInspector`、`ParseNeedFreeNodes` |
| NAPI 模块找不到富 API | NAPI 仅 `createComponentObserver`；`getInspectorTree` 等走 ANI/动态 bridge，非 NAPI 模块导出 |
| 与 DFX Dump 混淆 | DFX Dump 经 `PipelineContext::DumpInspector`→`OnDumpInfoNG`；Inspector JSON 树经 `Inspector::GetInspector`/`GetInspectorTree`，二者共用 `InspectorFilter` |

## 调试入口

- 树转储断点：`NG::Inspector::GetInspector(isLayoutInspector, filter, needThrow)`（inspector.cpp）→ 逐节点 `DumpInfo`
- 异步链路断点：`PipelineContext::GetInspectorTree` → 后台线程 → `UiSessionManager::ReportInspectorTreeValue`
- 过滤断点：`InspectorFilter::CheckFixedAttr/CheckExtAttr/IsFastFilter`
- DevEco 链路断点：`LayoutInspector::ProcessMessages`（windowId/method 分发）→ `NG::Inspector::GetInspector(true)`
- ANI 绑定断点：`AniGetInspectorTree/AniGetFilteredInspectorTree*`（inspector.cpp ANI 段）

## 相关主题

- [DFX Dump 机制：[docs/kb/architecture/dfx/dump-mechanism.md](../architecture/dfx/dump-mechanism.md)（Dump 管线，与 Inspector 共用 `InspectorFilter`）](../architecture/dfx/dump-mechanism.md)
- 布局回调：[docs/kb/capabilities/inspector-layout-callback.md](inspector-layout-callback.md)（`createComponentObserver` 布局/绘制回调）
- [无感监听：[docs/kb/capabilities/ui-observer.md](ui-observer.md)（UIObserver，sibling 04-11-02）](ui-observer.md)