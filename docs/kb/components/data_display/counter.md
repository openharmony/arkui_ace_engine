# Counter Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `Counter`

## 定位

Counter 是三节点计数器组件，由减号按钮、内容区域、加号按钮三部分组成。用于数量选择场景。支持自定义高度、宽度、背景色。提供增减按钮点击事件回调。行为细节以 SDK 声明、源码实现和规格文档为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/counter/counter_pattern.cpp` | 三节点管理、焦点模式、主题更新 |
| Model | `frameworks/core/components_ng/pattern/counter/counter_model_ng.cpp` | 动态范式 Model |
| Model Static | `frameworks/core/components_ng/pattern/counter/counter_model_static.cpp` | 静态范式 Model |
| Layout Algorithm | `frameworks/core/components_ng/pattern/counter/counter_layout_algorithm.cpp` | 三节点测量布局、RTL/LTR 处理 |
| Counter Node | `frameworks/core/components_ng/pattern/counter/counter_node.cpp` | CounterNode (GroupNode) 实现 |
| Theme | `frameworks/core/components_ng/pattern/counter/counter_theme_wrapper.h` | 主题常量 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/counter.d.ts` | 动态 API 声明 |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/counter.static.d.ets` | 静态 API 声明 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/CounterModifier.d.ts` | 动态 Modifier |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/CounterModifier.static.d.ets` | 静态 Modifier |

### API 解析实现路径

**已组件化**（有 `bridge/` 子目录、统一 Bridge，旧 JSView 已移除），输出独立 SO。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/counter/bridge/arkts_native_counter_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/counter/bridge/counter_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/counter/bridge/counter_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/counter/bridge/counter_dynamic_module.cpp` | `DynamicModule` 派生类，`libarkui_counter.z.so` 入口 |

独立 so 名称：`libarkui_counter.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/counter/` | Pattern/Model 层单元测试 |
| C API 测试 | `test/unittest/capi/modifiers/counter_modifier_test.cpp` | C API Modifier 测试 |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| Counter 设计 | `specs/05-ui-components/10-information-display-components/10-counter/design.md` | Baselined |
| Feat-01 创建与样式 | `specs/05-ui-components/10-information-display-components/10-counter/Feat-01-counter-creation-size-style-spec.md` | Baselined |
| Feat-02 按钮控制事件 | `specs/05-ui-components/10-information-display-components/10-counter/Feat-02-counter-button-control-events-spec.md` | Baselined |
| Feat-03 多范式接口 | `specs/05-ui-components/10-information-display-components/10-counter/Feat-03-counter-multi-paradigm-capi-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 三节点结构 | 固定顺序：SUB_BUTTON(0) → CONTENT(1) → ADD_BUTTON(2) |
| 高度属性传播 | Model 层 SetHeight() 更新所有子节点高度 |
| 宽度属性处理 | SetWidth() 仅更新容器，子节点使用 LayoutWeight |
| 背景色存储位置 | RenderContext，非 LayoutProperty |
| RTL/LTR 自动切换 | LayoutAlgorithm 根据 TextDirection 调整按钮位置 |
| 焦点模式版本差异 | API 18+ 使用 FocusType::SCOPE |

## 调试入口

- 搜索关键词：`Counter`、`CounterNode`、`onInc`、`onDec`、`enableInc`、`enableDec`
- Pattern 文件：`counter_pattern.cpp`
- Bridge 文件：`arkts_native_counter_bridge.cpp`
- Layout Algorithm 文件：`counter_layout_algorithm.cpp`
- Counter Node 文件：`counter_node.cpp`

## 相关主题

- [Button：按钮组件](../basic/button.md)
- [TextInput：文本输入组件](../basic/text-input.md)
- 数值管理：外部状态管理，通过事件回调处理