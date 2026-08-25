# NodeAdapter Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `NodeAdapter`

## 定位

`NodeAdapter` 是 ArkUI 命令式懒渲染适配器（FuncID `04-06-06`），面向 `@ohos.arkui.node` 命令式开发场景，将 ArkTS 创建的 `FrameNode` 子节点经懒渲染管线挂入容器。它复用 LazyForEach 的 `LazyForEachNode` / `LazyForEachBuilder` / `DataChangeListener` 内核，不重新实现按需渲染管线。

本设计以 **TS（ArkTS）侧 `NodeAdapter`** 为基线 Feat-01。C-API/NDK 公开层（`OH_ArkUI_NodeAdapter_*`）为另一独立 Feat，后续补录。具体行为、默认值、错误码以对应 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ArkTS 运行时实现 | `frameworks/bridge/declarative_frontend/ark_node/src/node_adapter.ts` | `NodeAdapter` class：字段、6 用户回调、构造/生命周期/计数/变更/查询/6 native trampoline、静态 attach |
| JSI 桥注册 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_impl_bridge.cpp` | 注册 `nodeAdapter` JS 对象到 `NodeAdapterBridge::*` |
| JSI 桥实现 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_node_adapter_bridge.cpp`、`arkts_native_node_adapter_bridge.h` | JS↔C 值/指针/回调 marshalling |
| C++ 包装层 | `frameworks/core/interfaces/native/node/node_adapter_impl.cpp`、`node_adapter_impl.h` | `UINodeAdapter : AceType`，持 raw handle + 回调槽；`NativeLazyForEachBuilder extends LazyForEachBuilder` |
| 共享 vtable | `frameworks/core/interfaces/arkoala/arkoala_api.h` | `ArkUINodeAdapterAPI` vtable——TS/NDK/CJ 汇聚点 |
| 懒渲染管线（共用） | `frameworks/core/components_ng/syntax/lazy_for_each_node.*`、`lazy_for_each_builder.h`、`frameworks/core/components_v2/foreach/lazy_foreach_component.h` | LazyForEachNode / LazyForEachBuilder / DataChangeListener，详见 07-05-02 |
| 父容器 Pattern | List / Grid / WaterFlow / ListItemGroup Pattern | `OnAttachAdapter` / `DetachHostNodeAdapter`（容器自定义 attach） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.d.ts` | 动态版 `NodeAdapter` class（`@since 12 dynamic`，`isDisposed` 为 `@since 20 dynamic`） |
| Static SDK | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.static.d.ets` | 静态版 `NodeAdapter` class（`@since 23 static`，`int`、必填回调） |
| re-export | `@ohos.arkui.node` / `@ohos.arkui.node.static` / `@kit.ArkUI` | Kit：ArkUI；SysCap：`SystemCapability.ArkUI.ArkUI.Full`；无权限 |

API 检索建议：在 SDK 文件中搜索 `class NodeAdapter`、`attachNodeAdapter`、`detachNodeAdapter`、`getAllAvailableItems`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/pattern/node_container/ui_node_adapter_test.cpp` | `UINodeAdapter` 包装、回调绑定、负参守卫、attach 预校验 |
| UT | `test/unittest/core/interfaces/native/node/node_adapter_impl_test.cpp` | native `node_adapter_impl` 行为 |
| XTS | `test/xts` | ArkTS 端到端 NodeAdapter 绑定容器 |
| Spec 功能域 | `specs/04-common-capability/06-custom-node/06-node-adapter/` | NodeAdapter 设计、验收契约 |
| Spec 总索引 | `specs/index.md` | `04-06-06` 功能域注册入口 |

### 相关 Spec

NodeAdapter 功能域：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | NodeAdapter ArkTS 前端规格（基线） | `specs/04-common-capability/06-custom-node/06-node-adapter/Feat-01-nodeadapter-arkts-frontend-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 构造后赋值实例字段回调不生效 | `node_adapter.ts` 构造与回调绑定；回调须构造时绑定（子类方法覆写或构造时赋值），详见 Spec RISK |
| `onUpdateChild` 复用语义与 C-API 不同 | `node_adapter_impl.cpp`（`UINodeAdapter` ctor `SetNeedUpdateEvent(true)`）；TS 路径 cache hit 触发 `ON_UPDATE_NODE` |
| 负参静默忽略、无错误反馈 | `node_adapter.ts`（`totalNodeCount` / `reloadItem` / `removeItem` / `insertItem` / `moveItem` 守卫） |
| `attachNodeAdapter` 返回 false 多源 | `node_adapter.ts` 预校验（null / `isModifiable` / `allowChildCount<=1`）+ native 侧 |
| `getAllAvailableItems` 返回项少于 native 持有 | `node_adapter.ts`（`ElementIdToOwningFrameNode_` 反查跳过逻辑） |
| 懒渲染 / 数据变更 dirty 机制 | 转跳 LazyForEach（07-05-02） |

## 调试入口

- 桥接链路：从 `node_adapter.ts` 构造经 `NodeAdapterBridge` → `UINodeAdapter` → `NativeLazyForEachBuilder` → `LazyForEachNode`。
- 回调绑定时机：在 `node_adapter.ts` 构造函数 `setCallbacks` 处确认哪些 trampoline 按构造时 `!== undefined` 绑定。
- 复用 / dirty：复用 LazyForEach 管线，参见 LazyForEach KB 的缓存与数据变更路由。

## 相关主题

- LazyForEach：`docs/kb/syntax/lazy_for_each.md`
- NodeContainer：`docs/kb/components/custom-node/node_container.md`
- 占位组件概念入口：`docs/kb/capabilities/placeholder_component.md`
