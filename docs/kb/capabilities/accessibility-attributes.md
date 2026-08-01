# 通用无障碍属性 Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `AccessibilityAttributes`

## 定位

通用无障碍属性是 ArkUI 组件树侧的无障碍语义声明层，所有 ArkUI 组件均可通过通用属性接口设置无障碍文本、角色、状态、值、动作等语义标签，引擎内部由 `AccessibilityProperty` 基类承载存储，组件可特化 `AccessibilityProperty` 子类实现差异化无障碍暴露。本功能域关注：从应用侧到 `AccessibilityProperty` 的写入路径、属性语义模型与组件侧特化模式，不涉及引擎对系统无障碍服务侧的桥接（属 `03-07-01`）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| AccessibilityProperty 基类 | `frameworks/core/components_ng/property/accessibility_property.h`、`accessibility_property.cpp` | 无障碍属性存储基类；`GetText/GetAccessibilityText/GetSupportAction` 等语义访问接口 |
| AccessibilityProperty 多线程实现 | `frameworks/core/components_ng/property/accessibility_property_mutilthread.cpp` | 多线程场景下的无障碍属性并发访问 |
| AccessibilityProperty 函数/辅助 | `frameworks/core/components_ng/property/accessibility_property_function.h`、`accessibility_property_helper.h` | 属性函数封装与辅助工具 |
| 属性工具 | `frameworks/core/accessibility/utils/accessibility_property_utils.h` | `GetContent/GetAccessibilityText` 等工具函数，处理默认/设置值优先级 |
| 应用侧通用属性写入（NG Model） | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp`、`view_abstract.h`/`view_abstract.cpp` | `SetAccessibilityGroup/Text/Level/...` 系列静态方法，将通用属性写入节点的 `AccessibilityProperty` |
| JSView 通用属性入口 | `frameworks/bridge/declarative_frontend/jsview/js_accessibility.cpp`、`js_view_abstract.cpp` | `accessibilityText/Level/Description/...` 在 JSView 侧的解析与写入 |
| 动态属性 / Modifier 入口 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | 通用无障碍属性在动态 Modifier / FrameNode 命令式 API 路径下的 bridge 入口 |
| 组件特化子类 | `frameworks/core/components_ng/pattern/<component>/*_accessibility_property.h` 或 `.cpp` | 各组件对 `AccessibilityProperty` 的特化（Text、Slider、Checkbox、Grid、Picker、XComponent 等） |
| C API 节点无障碍属性 | `interfaces/native/native_node.h` | `NODE_ACCESSIBILITY_GROUP/TEXT/ROLE/STATE/VALUE/ACTIONS/ON_ACCESSIBILITY_ACTIONS` 枚举；由通用 node modifier 框架分发到 `ViewAbstractModelNG::SetAccessibility*` |
| 内部 API 常量 | `interfaces/inner_api/ace_kit/include/ui/accessibility/accessibility_constants.h` | `AccessibilityRoleType` 等角色常量定义 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic 通用属性 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `accessibilityText`、`accessibilityLevel`、`accessibilityDescription`、`accessibilityChecked`、`accessibilityGroup`、`accessibilityValue` 等通用无障碍属性声明 |
| Static 通用属性 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态编译路径下的通用无障碍属性声明 |
| C API 节点属性 | `interfaces/native/native_node.h` | `NODE_ACCESSIBILITY_*` 系列枚举；通用 node modifier 分发到 `ViewAbstractModelNG::SetAccessibility*`、`AccessibilityProperty::Set*` |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| 系统无障碍服务 | `AccessorImpl::SetAccessibilityGroup` 最终透传到 `AccessibilitySessionAdapter` | `<OH_ROOT>/foundation/barrierfree/accessibility` | `services/accessibility/src/accessibility_system_ability_client.h` | 属性值通过 NDK 接口暴露给系统无障碍服务（运行时跨进程调用） |
| 窗口管理 | `AccessibilitySessionAdapter` 跨进程子类需会话通道 | `<OH_ROOT>/foundation/window/window_manager` | `interfaces/innerkits/wm/` | 跨进程组件的无障碍适配窗口绑定 |
| SDK 通用属性声明 | 应用侧属性入口 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | — | 通用无障碍属性声明入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| AccessibilityProperty 基类单测 | `test/unittest/core/property/accessibility_property_test_ng.cpp`、`accessibility_property_testtwo_ng.cpp`、`accessibility_property_test_three_ng.cpp` | 基类属性写入/读取回归 |
| 无障碍管理/节点单测 | `test/unittest/core/accessibility/` | `accessibility_manager_ng_test`、`accessibility_node_test`、`accessibility_next_focus_attr_test` 等回归 |
| 组件无障碍属性特化单测 | `test/unittest/core/pattern/<component>/*_accessibility_property_test*.cpp` | 各组件特化无障碍属性回归 |
| Mock | `test/mock/frameworks/core/components_ng/property/mock_accessibility_property.cpp` | AccessibilityProperty 测试替身 |

### 相关 Spec

通用无障碍属性功能域：`specs/04-common-capability/03-common-attributes/09-accessibility-attributes/`（功能 ID `04-03-09`，`design.md` + Feat-01~05 规格已创建，spec_status `active`）。

相关但独立的主题：

- 系统无障碍桥接机制（`03-07-01`）：`frameworks/core/accessibility/`、`adapter/ohos/osal/js_accessibility_manager.*`
- Inspector（`03-07-02`）：`frameworks/core/components_ng/base/inspector.*`

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 应用侧设置无障碍属性不生效 | `ViewAbstractModelNG::SetAccessibility*`、`ViewAbstract::SetAccessibility*`、JSView `js_accessibility.cpp` |
| 组件朗读文本与显示不一致 | `AccessibilityPropertyUtils::GetContent/GetAccessibilityText` 优先级；用户设置的 `accessibilityText` 优先于 `GetText()` 自动提取 |
| 组件不支持特化无障碍语义 | 对应 `pattern/<component>/*_accessibility_property.h` 特化子类；NG 组件不走旧 `js_inspector/` 路径 |
| C API 设置无障碍属性不生效 | `native_node.h` `NODE_ACCESSIBILITY_*` 枚举；通用 node modifier 分发；`ViewAbstractModelNG::SetAccessibility*`、`AccessibilityProperty::Set*` |
| 默认值行为不符合预期 | `AccessibilityProperty` 基类默认值；属性工具优先级逻辑 |

## 调试入口

- 属性写入断点：`ViewAbstractModelNG::SetAccessibility*`、`AccessibilityProperty::Set*`
- 属性读取/朗读断点：`AccessibilityProperty::GetText/GetAccessibilityText`、`AccessibilityPropertyUtils::GetContent`
- 特化子类检查：`pattern/<component>/*_accessibility_property.*` 的 `IsCheckable/IsChecked/IsSelected` 等
- 日志域：打开 accessibility 日志域，追踪属性写入/读取链路

## 相关主题

- 系统无障碍桥接机制（`03-07-01`）：`docs/kb/architecture/accessibility.md`
- Inspector（`03-07-02`）：`docs/kb/capabilities/inspector.md`
- 组件无障碍属性实现：`frameworks/core/components_ng/pattern/<component>/*_accessibility_property.h`
