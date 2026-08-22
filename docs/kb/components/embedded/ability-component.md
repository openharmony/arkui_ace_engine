# AbilityComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `AbilityComponent`

## 定位

`AbilityComponent`（FuncID `05-12-02`）是 ArkUI 早期跨进程能力嵌入组件，经 `WindowExtension` 将外部 Ability 的 surface 嵌入声明式树。该组件**已废弃**（`@deprecated since 10`，`@useinstead UIExtensionComponent`），继任者为 `UIExtensionComponent`（`05-12-03`，`@since 12`）与 `EmbeddedComponent`（`05-12-04`，`@since 12`）。仅系统 API（`@internal` + `@syscap`），无 static `.d.ets`。

具体行为、默认值以对应 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG Pattern（渲染宿主） | `frameworks/core/components_ng/pattern/ability_component/ability_component_pattern.cpp`、`.h` | `AbilityComponentPattern : WindowPattern`；adapter 创建（SceneBoard vs legacy）、rect/visibility 同步、event 转发 |
| NG Model | `frameworks/core/components_ng/pattern/ability_component/ability_component_model_ng.cpp` | `Create` / `SetWant` / `SetOnConnect` / `SetOnDisConnect` / `SetWidth` / `SetHeight` |
| EventHub | `frameworks/core/components_ng/pattern/ability_component/ability_component_event_hub.h` | onConnect / onDisconnect 回调存储与 fire |
| Layout | `frameworks/core/components_ng/pattern/ability_component/ability_component_layout_algorithm.cpp` | extension surface 尺寸 |
| RenderProperty | `frameworks/core/components_ng/pattern/ability_component/ability_component_render_property.h` | render 属性 bag |
| JS 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_ability_component.cpp` | `JSAbilityComponent::Create` 解析 want + `JSBind` |
| 跨进程适配 | `WindowExtensionConnectionAdapterNG`（adapter 层） | WindowExtension 跨进程连接适配 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK（仅系统 API） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/ability_component.d.ts` | `AbilityComponent({want})` + `onConnect` / `onDisconnect`，`@since 9 dynamiconly` `@deprecated since 10` |
| Static | 无 | 仅 dynamic `@internal`+`@syscap`，无 static `.d.ets` |

API 检索建议：在 SDK 文件中搜索 `AbilityComponent`、`AbilityComponentAttribute`、`onConnect`、`@useinstead`。

### API 解析实现路径

AbilityComponent **尚未进行组件化改造**，属性解析为单路径（声明式 JSView）。组件已废弃，编译产物在主 `libace_compatible.z.so` 中。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **JSView（声明式组件）** | `frameworks/bridge/declarative_frontend/jsview/js_ability_component.cpp` | `JSAbilityComponent::Create` 解析 want → `AbilityComponentModel::GetInstance()->SetWant` |
| **NG Model 层** | `frameworks/core/components_ng/pattern/ability_component/ability_component_model_ng.cpp` | `Create` / `SetWant` / `SetOnConnect` 等 ModelNG 入口 |


### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|------------------------------|------|
| 跨进程能力嵌入 | `ability_component_pattern.cpp`、`WindowExtensionConnectionAdapterNG` | WindowExtension / SceneBoard 系统服务 | ExtensionSession / ConnectExtension 适配接口 | SceneBoard 启用时走 `ExtensionSession`，否则 legacy `ConnectExtension` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/pattern/ability_component/`（如存在） | Pattern OnModifyDone / SceneBoard 分支、EventHub、Model |
| XTS | `test/xts` | 废弃组件端到端兼容 |
| Spec 功能域 | `specs/05-ui-components/12-embedded-display-components/02-ability-component/` | 设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `05-12-02` 功能域注册入口 |

### 相关 Spec

AbilityComponent 功能域（废弃，存量补录）：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | AbilityComponent 跨进程能力嵌入（已废弃） | `specs/05-ui-components/12-embedded-display-components/02-ability-component/Feat-01-ability-component-cross-process-embed-deprecated-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 组件已废弃，应迁移到什么 | `UIExtensionComponent`（05-12-03）/ `EmbeddedComponent`（05-12-04）；`@deprecated since 10` `@useinstead UIExtensionComponent` |
| onConnect / onDisconnect 的继任语义 | 继任者 `onRemoteReady` / `onRelease`（详见 05-12-03） |
| 设备连接路径不同 | `ability_component_pattern.cpp` `OnModifyDone`（`IsSceneBoardEnabled()` → ExtensionSession vs legacy ConnectExtension） |
| JSBind 绑定的非公开方法 | `js_ability_component.cpp` legacy `onReady` / `onDestroy` 等（不在 `.d.ts` 公开面） |

## 调试入口

- 创建链路：`JSAbilityComponent::Create` → Model `SetWant` → Pattern 创建 FrameNode + adapter。
- 连接链路：Pattern `OnModifyDone` → adapter `ConnectExtension` / `ExtensionSession` → EventHub fire `onConnect`。
- 同步链路：`UpdateRect` → adapter；可见性变化 → show / hide 转发。

## 相关主题

- [NodeContainer：[docs/kb/components/custom-node/node-container.md](../custom-node/node-container.md)](../custom-node/node-container.md)
- 占位组件概念入口：[docs/kb/capabilities/placeholder-component.md](../../capabilities/placeholder-component.md)