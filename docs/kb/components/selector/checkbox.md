# Checkbox/CheckboxGroup Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Checkbox`

## 定位

Checkbox 和 CheckboxGroup 是 ArkUI 表单选择类组件，提供多选框和多选分组能力。Checkbox 管理单个选项的选中/未选中状态，CheckboxGroup 管理分组内多选互斥逻辑和全选状态。两者有各自独立的 Pattern 目录和 Bridge。Checkbox 已完成组件化改造，输出独立 SO `libarkui_checkbox.z.so`，无遗留 JSView 文件。C API 暴露为 `ARKUI_NODE_CHECKBOX` 和 `ARKUI_NODE_CHECKBOX_GROUP` 节点类型。Checkbox 同时作为 ToggleCheckBox 的基类。

本文档用于快速定位 Checkbox/CheckboxGroup 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Checkbox Pattern | `frameworks/core/components_ng/pattern/checkbox/checkbox_pattern.cpp` | `CheckBoxPattern`，多选交互、选中状态管理 |
| Checkbox 多线程 | `frameworks/core/components_ng/pattern/checkbox/checkbox_pattern_multi_thread.cpp` | 多线程支持 |
| Checkbox 布局算法 | `frameworks/core/components_ng/pattern/checkbox/checkbox_layout_algorithm.cpp` | `CheckBoxLayoutAlgorithm` |
| Checkbox 绘制方法 | `frameworks/core/components_ng/pattern/checkbox/checkbox_paint_method.cpp` | `CheckBoxPaintMethod` |
| Checkbox 绘制属性 | `frameworks/core/components_ng/pattern/checkbox/checkbox_paint_property.cpp` | `CheckBoxPaintProperty` |
| Checkbox 事件 | `frameworks/core/components_ng/pattern/checkbox/checkbox_event_hub.h` | `CheckBoxEventHub`，onChange 等事件 |
| Checkbox Dynamic Model | `frameworks/core/components_ng/pattern/checkbox/checkbox_model_ng.cpp` | `CheckBoxModelNG`，动态属性写入、节点创建 |
| Checkbox Static Model | `frameworks/core/components_ng/pattern/checkbox/checkbox_model_static.cpp` | `CheckBoxModelStatic`，静态前端属性写入 |
| Checkbox Model 实现 | `frameworks/core/components_ng/pattern/checkbox/checkbox_model_impl.cpp` | `CheckBoxModelImpl` |
| Checkbox 无障碍 | `frameworks/core/components_ng/pattern/checkbox/checkbox_accessibility_property.cpp` | `CheckBoxAccessibilityProperty` |
| Checkbox 主题 | `frameworks/core/components_ng/pattern/checkbox/checkbox_theme_wrapper.h` | Checkbox Token 适配 |
| Checkbox Modifier | `frameworks/core/components_ng/pattern/checkbox/checkbox_modifier.h` | Checkbox Modifier 定义 |
| ToggleCheckBox Pattern | `frameworks/core/components_ng/pattern/checkbox/toggle_checkbox_pattern.h` | `ToggleCheckBoxPattern`，继承 CheckBoxPattern 的薄封装 |
| ToggleCheckBox 无障碍 | `frameworks/core/components_ng/pattern/checkbox/toggle_checkbox_accessibility_property.h` | ToggleCheckBox 无障碍属性 |
| CheckboxGroup Pattern | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.cpp` | `CheckBoxGroupPattern`，分组多选管理 |
| CheckboxGroup 多线程 | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern_multi_thread.cpp` | 多线程支持 |
| CheckboxGroup 布局算法 | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.cpp` | `CheckBoxGroupLayoutAlgorithm` |
| CheckboxGroup 绘制方法 | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h` | `CheckBoxGroupPaintMethod` |
| CheckboxGroup 绘制属性 | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.cpp` | `CheckBoxGroupPaintProperty` |
| CheckboxGroup 事件 | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_event_hub.h` | `CheckBoxGroupEventHub` |
| CheckboxGroup Dynamic Model | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.cpp` | `CheckBoxGroupModelNG` |
| CheckboxGroup Static Model | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.cpp` | `CheckBoxGroupModelStatic` |
| CheckboxGroup Model 实现 | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_model_impl.cpp` | `CheckBoxGroupModelImpl` |
| CheckboxGroup 无障碍 | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_accessibility_property.cpp` | `CheckBoxGroupAccessibilityProperty` |
| CheckboxGroup Modifier | `frameworks/core/components_ng/pattern/checkboxgroup/checkboxgroup_modifier.cpp` | CheckboxGroup Modifier 实现 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/checkbox/bridge/` | Checkbox 组件化 Bridge |
| CheckboxGroup Bridge 目录 | `frameworks/core/components_ng/pattern/checkboxgroup/bridge/` | CheckboxGroup 组件化 Bridge |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_checkbox_modifier.cpp` | Checkbox C++ 属性委托层 |
| CheckboxGroup node_modifier | `frameworks/core/interfaces/native/node/checkboxgroup_modifier.cpp` | CheckboxGroup C++ 属性委托层 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_CHECKBOX`、`ARKUI_NODE_CHECKBOX_GROUP`、`NODE_CHECKBOX_*`、`NODE_CHECKBOX_GROUP_*` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/checkbox.d.ts` | 动态 ArkTS `CheckboxInterface`、`CheckboxAttribute`、`CheckboxGroupInterface` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/checkbox.static.d.ets` | 静态 ArkTS Checkbox 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/CheckboxModifier.d.ts` | 动态 Checkbox Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/CheckboxModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | Checkbox C API 节点类型 `ARKUI_NODE_CHECKBOX`、`ARKUI_NODE_CHECKBOX_GROUP` 和属性枚举 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `CheckboxAttribute`、`CheckboxGroupAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `CheckboxInterface`、`CheckboxOptions`、`CheckboxGroupOptions`。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_CHECKBOX_`、`ARKUI_NODE_CHECKBOX`。

### API 解析实现路径

Checkbox 和 CheckboxGroup 均已完成组件化改造，JSView 文件不存在，Bridge 和动态属性路径统一到各自 `bridge/` 目录。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/components/arkcheckbox.js`、`arkcheckboxgroup.js` | 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/checkbox_modifier.ts`、`checkboxgroup_modifier.ts` |
| 统一 Bridge（Checkbox） | `frameworks/core/components_ng/pattern/checkbox/bridge/arkts_native_checkbox_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| 统一 Bridge（CheckboxGroup） | `frameworks/core/components_ng/pattern/checkboxgroup/bridge/arkts_native_checkboxgroup_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier (Checkbox) | `frameworks/core/components_ng/pattern/checkbox/bridge/checkbox_dynamic_modifier.cpp` | 动态属性路径；ContentModifier 辅助见 `checkbox_content_modifier_helper.h` |
| Dynamic Modifier (CheckboxGroup) | `frameworks/core/components_ng/pattern/checkboxgroup/bridge/checkboxgroup_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier (Checkbox) | `frameworks/core/components_ng/pattern/checkbox/bridge/checkbox_static_modifier.cpp` | 静态编译路径 |
| Static Modifier (CheckboxGroup) | `frameworks/core/components_ng/pattern/checkboxgroup/bridge/checkboxgroup_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/checkbox/bridge/checkbox_dynamic_module.cpp` | `CheckboxDynamicModule` 派生类，`libarkui_checkbox.z.so` 入口 |
| Dynamic Module (CheckboxGroup) | `frameworks/core/components_ng/pattern/checkboxgroup/bridge/checkboxgroup_dynamic_module.cpp` | `CheckboxGroupDynamicModule` 派生类 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_checkbox_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 SO：`libarkui_checkbox.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/checkbox/` | Checkbox Pattern、Model、布局、事件、ContentModifier 等回归测试 |
| Context registry | `docs/context_registry.json` | Checkbox 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Checkbox/CheckboxGroup 功能域 | `specs/05-ui-components/04-input-form-components/02-checkbox-checkbox-group/` | Checkbox 规格目录 |
| Feat-01 | `specs/05-ui-components/04-input-form-components/02-checkbox-checkbox-group/Feat-01-checkbox-full-spec.md` | Checkbox/CheckboxGroup 全量规格 |
| 架构设计 | `specs/05-ui-components/04-input-form-components/02-checkbox-checkbox-group/design.md` | Checkbox 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 多选不响应 | `CheckBoxPattern` 的点击处理和选中状态；`CheckBoxEventHub` 的 onChange |
| CheckboxGroup 全选不生效 | `CheckBoxGroupPattern` 的 `selectAll` 逻辑；`NODE_CHECKBOX_GROUP_SELECT_ALL` |
| 选中样式不对 | `CheckBoxPaintProperty` 的 SelectColor / UnselectedColor / Mark；`CheckBoxPaintMethod` |
| CheckboxGroup 选中颜色不统一 | `CheckBoxGroupPaintProperty` 的 SelectedColor / UnselectedColor |
| Toggle(Checkbox) vs 独立 Checkbox 行为差异 | ToggleCheckBoxPattern 继承 CheckBoxPattern，使用 `TOGGLE_ETS_TAG` 标签；独立 Checkbox 使用 `CHECKBOX_ETS_TAG` |
| 无障碍操作无效 | `CheckBoxAccessibilityProperty`、`CheckBoxGroupAccessibilityProperty` |
| 静态前端属性不生效 | `CheckBoxModelStatic` / `CheckBoxGroupModelStatic` 的属性写入 |

## 调试入口

- 创建链路：从 `CheckBoxModelNG::Create()` 确认 Checkbox 节点创建和 Pattern 设置。
- 属性链路：从 SDK 属性名定位 Bridge → node_modifier → Model 写入，再看 `CheckBoxPaintProperty` 的属性分组。
- 交互链路：从 `CheckBoxPattern` 的点击事件跟踪选中状态变化；CheckboxGroup 从 `CheckBoxGroupPattern` 跟踪分组联动。
- 组件化链路：从 `CheckboxDynamicModule` / `CheckboxGroupDynamicModule` 跟踪动态模块加载和属性注册。
- 回归验证：优先运行 `test/unittest/core/pattern/checkbox/` 下的定向用例。

## 相关主题

- [Toggle 组件（ToggleCheckBoxPattern 继承 CheckBoxPattern）](toggle.md)
- [Radio 组件（单选组件，同属选择类组件）](radio.md)