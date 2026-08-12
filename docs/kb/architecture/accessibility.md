# Accessibility Context

> 文档版本：v1.0
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Accessibility`

## 定位

Accessibility 是 ACE Engine 中的**无障碍桥接层**，负责把 ArkUI 组件树信息（属性、状态、位置）暴露给系统无障碍服务（屏幕阅读器等），并把无障碍服务的动作请求分发回组件。它是一套引擎内部机制，不是独立的应用侧组件；应用侧通过“通用无障碍属性”（`accessibilityText`、`accessibilityLevel` 等，属 `04-03-09` 主题）接入，Native 侧通过 NDK provider 接口接入。

跨进程/跨语言边界由 NDK 接口承担：系统 Accessibility SA 在运行时通过 `ArkUI_AccessibilityProvider` 回调进入 ace_engine，ace_engine 本身不包含对系统无障碍服务仓（`barrierfree/*`）的编译期依赖。

本文档只提供稳定的源码、API、测试和 Spec 路由。具体动作集合、事件类型、焦点算法行为和默认值应回到当前源码、NDK 头文件、测试与相关 Spec 核实。

## 快速路由

### 通用无障碍属性

通用无障碍属性（功能 ID `04-03-09`）提供组件树侧的无障碍语义声明层，所有 ArkUI 组件均可通过通用属性接口设置无障碍文本、角色、状态、值等。

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| AccessibilityProperty 基类 | `frameworks/core/components_ng/property/accessibility_property.h`、`accessibility_property.cpp` | 无障碍属性存储基类；`GetText/GetSupportAction` 等 |
| AccessibilityProperty 多线程 | `frameworks/core/components_ng/property/accessibility_property_mutilthread.cpp` | 多线程并发访问 |
| AccessibilityProperty 辅助 | `frameworks/core/components_ng/property/accessibility_property_function.h`、`accessibility_property_helper.h` | 属性函数封装 |
| 属性工具 | `frameworks/core/accessibility/utils/accessibility_property_utils.h` | `GetContent/GetAccessibilityText` 优先级 |
| 通用属性写入（NG Model） | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp`、`view_abstract.h`/`view_abstract.cpp` | `SetAccessibilityGroup/Text/Level/...` 系列方法 |
| JSView 通用属性入口 | `frameworks/bridge/declarative_frontend/jsview/js_accessibility.cpp`、`js_view_abstract.cpp` | JSView 侧解析与写入 |
| 组件特化子类 | `frameworks/core/components_ng/pattern/<component>/*_accessibility_property.h` | 各组件特化实现（Text、Slider、Checkbox、Grid 等） |

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Core 抽象接口 | `frameworks/core/accessibility/accessibility_provider.h` | 节点查询、动作执行、焦点查找、事件上报等抽象接口 |
| 会话适配 | `frameworks/core/accessibility/accessibility_session_adapter.h`、`accessibility_session_adapter.cpp` | 跨进程组件（Form / UIExtension / Isolated / XComponent / Web）的会话适配基类与子类 |
| NG 悬停管理 | `frameworks/core/accessibility/accessibility_manager_ng.h`、`accessibility_manager_ng.cpp` | 辅助技术悬停探测状态机（`HandleAccessibilityHoverEvent` 等） |
| 旧架构节点 | `frameworks/core/accessibility/accessibility_node.h`、`accessibility_node.cpp` | 旧 DOM 无障碍节点及动作回调 |
| 旧架构管理器接口 | `frameworks/core/accessibility/accessibility_manager.h` | `AccessibilityManager` 接口、回调与事件载荷定义 |
| 第三方管理 | `frameworks/core/accessibility/third_accessibility_manager.h` | 第三方 Provider 管理抽象 |
| 常量与工具 | `frameworks/core/accessibility/accessibility_constants.h`、`accessibility_utils.h`、`accessibility_utils.cpp` | 事件类型、动作、组件标签常量与角色转换工具 |
| Core 子工具目录 | `frameworks/core/accessibility/utils/`、`node_utils/`、`static/` | property/action/rect/manager 等细分工具 |
| 旧 DOM 组件 inspect | `frameworks/core/accessibility/js_inspector/` | 旧 DOM 组件的无障碍属性抽取实现（`inspect_<component>.*`） |
| Core 调试 | `frameworks/core/accessibility/hidumper/` | Core 侧 dump 工具 |
| NG 属性基类 | `frameworks/core/components_ng/property/accessibility_property.h`、`accessibility_property.cpp` | `AccessibilityProperty` 基类；各组件特化实现位于对应 `pattern/<comp>/*_accessibility_property.h` |
| NG 属性扩展 | `frameworks/core/components_ng/property/accessibility_property_function.h`、`accessibility_property_helper.h`、`accessibility_property_mutilthread.cpp` | 属性函数、辅助与多线程实现 |
| OSAL 核心 | `adapter/ohos/osal/js_accessibility_manager.h`、`js_accessibility_manager.cpp` | `JsAccessibilityManager`：节点搜索、动作执行、事件发送、第三方 Provider 注册、Web 无障碍 |
| OSAL 第三方悬停 | `adapter/ohos/osal/js_third_accessibility_hover_ng.h`、`js_third_accessibility_hover_ng.cpp`、`js_third_provider_interaction_operation.h`、`js_third_provider_interaction_operation.cpp` | 第三方 Provider 悬停与交互操作 |
| OSAL element_info / focus_move | `adapter/ohos/osal/accessibility/element_info/`、`adapter/ohos/osal/accessibility/focus_move/` | 元素信息组装与焦点移动算法（含 `accessibility_focus_strategy.*`） |
| OSAL 调试 | `adapter/ohos/osal/accessibility/accessibility_hidumper_osal.h`、`accessibility_hidumper_osal.cpp` | 平台侧 HiDumper 适配 |
| Bridge 节点管理 | `frameworks/bridge/common/accessibility/accessibility_node_manager.h`、`accessibility_node_manager.cpp` | Bridge 层节点管理器接口 |
| 应用侧属性接入（声明式 JSView） | `frameworks/bridge/declarative_frontend/jsview/js_accessibility.cpp`、`frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `accessibilityText` / `accessibilityLevel` / `accessibilityGroup` 等通用属性的 JSView 解析入口；调用 `ViewAbstractModel` |
| 应用侧属性接入（NG Model） | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp`、`frameworks/core/components_ng/base/view_abstract.cpp` | `SetAccessibilityGroup/Text/...` 落到 `AccessibilityProperty` 的写入入口 |
| 应用侧属性接入（动态属性 / Modifier） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | 动态属性 / Modifier / FrameNode 命令式路径下通用属性（含无障碍）的 bridge 入口 |

应用侧无障碍属性（`accessibilityText` 等）从 JSView / bridge 进入引擎后写入 `AccessibilityProperty`，属 `04-03-09` 主题；本页只提供入口路由，不重复其属性语义。

建议按问题使用类型名或方法名检索，不依赖行号：

| 问题方向 | 优先检索 |
|----------|----------|
| 读屏节点查询/搜索 | `SearchElementInfoByAccessibilityId`、`SearchElementInfosByText`、`JsInteractionOperation` |
| 动作不生效 | `ExecuteAction`、`ExecuteActionNG`、`GetSupportAction`、`AceAction` |
| 无障碍焦点移动 | `AccessibilityFocusStrategy`、`FindNextReadableNode`、`FocusMoveSearchNG`、`FocusRulesCheckNode` |
| 悬停命中 | `HandleAccessibilityHoverEvent`、`AccessibilityHoverStateManager`、`HoverTestDebug` |
| 跨进程组件上报 | `AccessibilitySessionAdapter` 及各子类、`RegisterJsThirdProviderInteractionOperation` |
| 旧 DOM 组件属性缺失 | `js_inspector/inspect_<component>` |

### API 入口

无障碍涉及两套不同方向的 C/NDK 接口，排查时先区分方向：

| 方向 | 范式 | 稳定路径 | 说明 |
|------|------|----------|------|
| 系统服务 → 引擎（Provider） | C API / NDK | `interfaces/native/native_interface_accessibility.h`、`interfaces/native/native_interface_accessibility.cpp` | `ArkUI_AccessibilityElementInfo` / `ArkUI_AccessibilityEventInfo` / `ArkUI_AccessibilityProvider` / `ArkUI_AccessibilityActionArguments` 等结构、回调与注册接口；Native 侧自定义节点能力（跨进程/跨语言）的接入入口 |
| 应用/组件 → 节点（属性设置） | C API / NDK | `interfaces/native/native_node.h` | `NODE_ACCESSIBILITY_GROUP` / `NODE_ACCESSIBILITY_TEXT` / `NODE_ACCESSIBILITY_ROLE` / `NODE_ACCESSIBILITY_STATE` / `NODE_ACCESSIBILITY_VALUE` / `NODE_ACCESSIBILITY_ACTIONS` / `NODE_ON_ACCESSIBILITY_ACTIONS` 等节点属性与事件枚举（由通用 node modifier 框架分发） |
| 内部 API | Inner API | `interfaces/inner_api/ace_kit/include/ui/accessibility/accessibility_constants.h` | `AccessibilityRoleType` 等内部角色常量定义 |
| 应用侧通用属性 | SDK | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts`、`<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | `accessibilityText`、`accessibilityDescription`、`accessibilityLevel`、`accessibilityChecked`、`accessibilityGroup` 等通用无障碍属性声明（属 `04-03-09` 主题） |

> Provider 方向的数据结构（`ArkUI_AccessibilityElementInfo` 等）实际定义在 `frameworks/core/accessibility/native_interface_accessibility_impl.h`，provider 接口在 `frameworks/core/accessibility/native_interface_accessibility_provider.*`。
>
> 注：`interface_sdk-js` 仓未在当前工作区检出，上表 SDK 声明仅给出稳定路径，具体属性语义和 API 版本以 SDK 声明为准，未在此逐一核验。

无障碍属性从前端到 `AccessibilityProperty` 的解析属于“通用无障碍属性”主题（`04-03-09`），本页不重复。多数 NG 组件在各自 pattern 目录下提供 `*_accessibility_property.h` 特化实现。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| 系统无障碍服务 | `adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h`、`adapter/ohos/osal/accessibility/accessibility_hidumper_osal.cpp`、`adapter/ohos/osal/js_third_provider_interaction_operation.cpp` | `<OH_ROOT>/foundation/barrierfree/accessibility` | `services/accessibility/src/accessibility_system_ability_client.h` | `AccessibilitySystemAbilityClient` 焦点移动、HiDumper、第三方 Provider 交互等；运行时通过 `ServiceProxy` 跨进程调用 |
| 窗口管理 | `adapter/ohos/entrance/ace_container.h`、跨进程 `AccessibilitySessionAdapter` 子类 | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/wm/` | 窗口句柄和 Session 通道，用于跨进程组件无障碍适配 |
| SDK 通用无障碍属性 | 应用侧 `accessibilityText` 等通用属性 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | 应用侧属性声明入口 | 属 `04-03-09` 主题（通用无障碍属性） |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 无障碍单测根目录 | `test/unittest/core/accessibility/` | manager、node、provider、hover、inspector 等回归 |
| OSAL 单测 | `test/unittest/core/accessibility/osal/` | element_info、hover、focus_move、osal 覆盖回归 |
| 焦点移动单测 | `test/unittest/core/accessibility/focus_move/`、`test/unittest/core/accessibility/osal/focus_move/` | 焦点策略与边界判定回归 |
| 工具/调试单测 | `test/unittest/core/accessibility/utils/`、`test/unittest/core/accessibility/node_uitls/`、`test/unittest/core/accessibility/hidumper/` | 工具函数、节点工具与 dump 回归 |
| 测试 Mock | `test/mock/frameworks/core/accessibility/` | 依赖无障碍内部类型的测试替身 |
| AccessibilityProperty 基类单测 | `test/unittest/core/property/accessibility_property_test_ng.cpp`、`accessibility_property_testtwo_ng.cpp`、`accessibility_property_test_three_ng.cpp` | 通用无障碍属性（`04-03-09`）基类属性写入/读取回归 |
| 组件无障碍属性特化单测 | `test/unittest/core/pattern/<component>/*_accessibility_property_test*.cpp` | 各组件特化无障碍属性回归 |
| Property Mock | `test/mock/frameworks/core/components_ng/property/mock_accessibility_property.cpp` | AccessibilityProperty 测试替身 |
| Context registry | `docs/context_registry.json` | `Accessibility` 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

无障碍能力功能域：`specs/03-engine-framework/07-accessibility-mechanism/01-accessibility-capability/`（功能 ID `03-07-01`）。

相关但独立的主题：

- 通用无障碍属性（`accessibilityText` 等）：功能域 `specs/04-common-capability/03-common-attributes/09-accessibility-attributes/`，功能 ID `04-03-09`。
- Inspector：功能域 `specs/03-engine-framework/07-accessibility-mechanism/02-inspector/`，功能 ID `03-07-02`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 自定义/普通组件读屏不朗读 | 应用侧 `accessibilityText` / `accessibilityLevel` 声明、`AccessibilityProperty::GetText/GetAccessibilityText`、`accessibility_property_utils` |
| 滚动容器内焦点无法跳到下一项 | `AccessibilityFocusStrategy`、`FocusRulesCheckNode` 的可见性与可滚动祖先判定 |
| 第三方/跨进程组件节点未上报 | 对应 `AccessibilitySessionAdapter` 子类、`RegisterJsThirdProviderInteractionOperation`、`AccessibilityHoverManagerForThirdNG` |
| 旧 DOM 组件属性缺失 | `frameworks/core/accessibility/js_inspector/inspect_<component>`（NG 组件改用 `AccessibilityProperty` 子类） |
| 动作（点击/设值/滚动）无响应 | `AceAction`、`AccessibilityProperty::GetSupportAction`、`ExecuteActionNG` |
| Native 自定义节点能力不生效 | NDK provider 注册路径、`native_interface_accessibility_provider.*` |
| C API 设置节点无障碍属性不生效 | `native_node.h` 中 `NODE_ACCESSIBILITY_*` 枚举、通用 node modifier 分发、`ViewAbstractModelNG::SetAccessibility*`、`AccessibilityProperty::Set*` |

## 调试入口

- HiDumper：`adapter/ohos/osal/accessibility/accessibility_hidumper_osal.*` 与 `frameworks/core/accessibility/hidumper/`，用于 dump 指定窗口/节点的无障碍信息。
- 悬停命中调试：`AccessibilityManagerNG::HoverTestDebug` 可输出悬停命中链与详细信息。
- 关键日志入口：节点查询 `SearchElementInfoByAccessibilityId`、动作分发 `ExecuteActionNG`、焦点搜索 `FindNextReadableNode`。
- 排查顺序：复现时打开 accessibility 日志域 → 确认 `AccessibilityProperty` 是否暴露预期 text/role/state → 检查动作是否在 `GetSupportAction()` 集合中 → 跨进程组件检查对应 `AccessibilitySessionAdapter` 实现。

## 相关主题

- 通用无障碍属性（`04-03-09`）：`specs/04-common-capability/03-common-attributes/09-accessibility-attributes/`
- Inspector（`03-07-02`）：`specs/03-engine-framework/07-accessibility-mechanism/02-inspector/`
- 组件无障碍属性实现：`frameworks/core/components_ng/pattern/<component>/*_accessibility_property.h`
- 焦点导航（通用能力）：`frameworks/core/components_ng/base/focus_view.h`、`adapter/ohos/osal/accessibility/focus_move/`
