# ContentSlot Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ContentSlot`

## 定位

`ContentSlot`（FuncID `05-16-02`）是自定义占位组件之一，为命令式节点提供多子节点挂载能力。它是 `XComponentType.NODE` 的继任（`XComponentType.NODE` `@deprecated since 20 @useinstead ContentSlot`）。

关键架构差异：与 `NodeContainer`（FrameNode + Pattern + Layout）不同，`ContentSlotNode` **继承 UINode 而非 FrameNode**——无 Pattern / LayoutProperty / LayoutAlgorithm / EventHub；子节点增删经 `MarkNeedFrameFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST)` 上传父链到最近 FrameNode 祖先触发重布局。`NodeContent` 是 `AceType`（非 UINode），管理子节点并在 attach/detach 时重放/回收。具体行为、默认值、错误码以对应 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG 语法节点 | `frameworks/core/components_ng/syntax/content_slot_node.cpp`、`.h` | `ContentSlotNode : UINode`（非 FrameNode）；tag "NodeSlot"；`AttachNodeContent` / `DetachNodeContent`（所有权守卫）；OnAttach/Detach 转发 |
| NodeContent 管理器 | `frameworks/core/components_ng/syntax/node_content.cpp`、`.h` | `NodeContent : AceType`（非 UINode）；`children_` 管理；`AttachToNode` / `DetachFromNode`（重放/回收）；`AddNode` / `RemoveNode`；生命周期 callbacks |
| NG Model | `frameworks/core/components_ng/syntax/content_slot_model_ng.cpp` | `Create(NodeContent*)`：ClaimNodeId + GetOrCreateContentSlot + Push + attach/detach |
| JS 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_content_slot.cpp` | `JSContentSlot::Create`（unwrap `nativePtr_` → `NodeContent*`）、`JSNodeContent` |
| NDK Modifier | `frameworks/core/interfaces/native/node/node_content_modifier.cpp` | AddChild / InsertChild / RemoveChild / RegisterEvent / SetUserData / GetUserData vtable |
| Extender Accessor | `frameworks/core/interfaces/native/implementation/node_content_extender_accessor.cpp` | `AddFrameNodeImpl` / `RemoveFrameNodeImpl`（`IsAdopted` 守卫 + MarkDirtyNode） |
| ANI Modifier | `frameworks/core/interfaces/native/ani/content_slot_ani_modifier.cpp` | `ContentSlotConstruct` / `SetContentSlotOptions`（static/C-API） |
| 父容器 | FrameNode 祖先 | 接收 `PROPERTY_UPDATE_BY_CHILD_REQUEST` 上传触发重布局 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/content_slot.d.ts`、`NodeContent.d.ts`、`Content.d.ts` | `ContentSlot(content)` `@since12`；`NodeContent.addFrameNode` / `removeFrameNode`（`BusinessError 100025` `@since22`） |
| Static SDK | `<OH_ROOT>/interface/sdk-js/api/arkui/component/contentSlot.static.d.ets`、`NodeContent.static.d.ets` | `@since23` 整套，`@since26 staticonly` style-builder + 属性方法 |
| 废弃继任 | `<OH_ROOT>/interface/sdk-js` 中 `enums.d.ts` | `XComponentType.NODE` `@deprecated since 20 @useinstead ContentSlot` |
| CAPI / NDK | `frameworks/core/interfaces/native/node/node_content_modifier.cpp` | AddChild / RemoveChild / RegisterEvent 等 |
| re-export | `@ohos.arkui.node(.static)` / `@kit.ArkUI` | Kit：ArkUI；SysCap：`SystemCapability.ArkUI.ArkUI.Full`；无权限 |

API 检索建议：在 SDK 中搜索 `ContentSlot`、`NodeContent`、`addFrameNode`、`removeFrameNode`、`IsAdopted`。

### API 解析实现路径

ContentSlot 为 UINode 语法节点（非 FrameNode Pattern 组件），**不走标准组件化改造模型**，属性 / 内容解析为多前端路径架构，编译产物在主 `libace_compatible.z.so` 中。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **JSView（声明式）** | `frameworks/bridge/declarative_frontend/jsview/js_content_slot.cpp` | `JSContentSlot::Create` unwrap `nativePtr_` → `NodeContent*` → Model `Create` |
| **NG Model 工厂** | `frameworks/core/components_ng/syntax/content_slot_model_ng.cpp` | `Create(NodeContent*)` + `AttachNodeContent` / `DetachNodeContent` |
| **NDK Modifier（命令式）** | `frameworks/core/interfaces/native/node/node_content_modifier.cpp` | AddChild / InsertChild / RemoveChild / RegisterEvent / SetUserData / GetUserData |
| **Extender Accessor（ArkTS 命令式）** | `frameworks/core/interfaces/native/implementation/node_content_extender_accessor.cpp` | `AddFrameNodeImpl` / `RemoveFrameNodeImpl`（`IsAdopted` 守卫 + MarkDirtyNode） |
| **ANI Modifier（static/C-API）** | `frameworks/core/interfaces/native/ani/content_slot_ani_modifier.cpp` | `ContentSlotConstruct` / `SetContentSlotOptions` |


### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/syntax/content_slot_syntax_test_ng.cpp` | ContentSlotNode / NodeContent 内容管理、所有权守卫、脏标记 |
| 扩展自定义节点 UT | `test/unittest/interfaces/extension_custom_node_test_ng.cpp` | 命令式扩展节点 |
| XTS | `test/xts` | ContentSlot + NodeContent 端到端 |
| Spec 功能域 | `specs/05-ui-components/16-custom-placeholder-components/02-content-slot/` | 设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `05-16-02` 功能域注册入口 |

### 相关 Spec

ContentSlot 功能域：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | ContentSlot 语法节点与 NodeContent 内容管理（基线） | `specs/05-ui-components/16-custom-placeholder-components/02-content-slot/Feat-01-contentslot-syntax-node-and-nodecontent-management-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 子节点增删不触发重布局 | `node_content.cpp` `AddNode` / `RemoveNode`（`MarkNeedFrameFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST)` 上传父链）；ContentSlot 自身无 dirty |
| addFrameNode 报 106206 / 100025 | `node_content_extender_accessor.cpp` `AddFrameNodeImpl`（`IsAdopted` 守卫，节点已被领养） |
| ContentSlot 与 NodeContainer 如何选 | ContentSlot（多子节点 UINode 轻量）vs NodeContainer（单根 FrameNode + Pattern/Layout） |
| XComponentType.NODE 迁移 | `@deprecated since 20` `@useinstead ContentSlot` |
| 两路径脏标记差异 | extender ArkTS 额外 `MarkDirtyNode(MEASURE_SELF_AND_PARENT)`，NDK 仅 `BY_CHILD_REQUEST` 上传 |

## 调试入口

- 创建链路：`JSContentSlot::Create` → Model `Create(NodeContent*)` → `AttachNodeContent`（所有权守卫）→ `AttachToNode` 重放 `children_`。
- 内容管理链路：`addFrameNode` → extender `AddFrameNodeImpl`（`IsAdopted` 守卫）→ `NodeContent::AddNode`（slot `AddChild` + 上传 dirty）。
- 生命周期链路：`ContentSlotNode::OnAttachToMainTree/Detach` → `content_->OnAttachToMainTree` + callback。

## 相关主题

- [NodeContainer：`docs/kb/components/custom-node/node-container.md`](node-container.md)
- [NodeAdapter：`docs/kb/capabilities/node-adapter.md`](../../capabilities/node-adapter.md)
- 占位组件概念入口：`docs/kb/capabilities/placeholder-component.md`