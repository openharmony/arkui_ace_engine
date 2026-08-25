# Radio Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `Radio`

## 定位

Radio 是 ArkUI 表单选择类组件，提供单选按钮交互能力，支持 RadioGroup 分组单选。Radio 已完成组件化改造，输出独立 SO `libarkui_radio.z.so`，无遗留 JSView 文件。C API 暴露为 `ARKUI_NODE_RADIO` 节点类型。

本文档用于快速定位 Radio 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Radio Pattern | `frameworks/core/components_ng/pattern/radio/radio_pattern.cpp` | `RadioPattern`，单选交互、选中状态管理 |
| Radio 多线程 | `frameworks/core/components_ng/pattern/radio/radio_pattern_multi_thread.cpp` | 多线程支持 |
| Radio 布局算法 | `frameworks/core/components_ng/pattern/radio/radio_layout_algorithm.cpp` | `RadioLayoutAlgorithm` |
| Radio 绘制方法 | `frameworks/core/components_ng/pattern/radio/radio_paint_method.cpp` | `RadioPaintMethod` |
| Radio 绘制属性 | `frameworks/core/components_ng/pattern/radio/radio_paint_property.cpp` | `RadioPaintProperty` |
| Radio 事件 | `frameworks/core/components_ng/pattern/radio/radio_event_hub.h` | `RadioEventHub`，onChange 等事件 |
| Radio Dynamic Model | `frameworks/core/components_ng/pattern/radio/radio_model_ng.cpp` | `RadioModelNG`，动态属性写入、节点创建 |
| Radio Static Model | `frameworks/core/components_ng/pattern/radio/radio_model_static.cpp` | `RadioModelStatic`，静态前端属性写入 |
| Radio Model 实现 | `frameworks/core/components_ng/pattern/radio/bridge/radio_model_impl.cpp` | `RadioModelImpl` |
| Radio 无障碍 | `frameworks/core/components_ng/pattern/radio/radio_accessibility_property.cpp` | `RadioAccessibilityProperty` |
| Radio 主题 | `frameworks/core/components_ng/pattern/radio/radio_theme.h` | Radio 主题定义 |
| Radio Modifier | `frameworks/core/components_ng/pattern/radio/radio_modifier.h` | Radio Modifier 定义 |
| 组件化 Bridge 目录 | `frameworks/core/components_ng/pattern/radio/bridge/` | 组件化后的统一 Bridge / DynamicModule 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/radio_modifier.cpp` | Radio C++ 属性委托层 |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_RADIO`、`NODE_RADIO_CHECKED`、`NODE_RADIO_STYLE`、`NODE_RADIO_VALUE`、`NODE_RADIO_GROUP` 等 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/radio.d.ts` | 动态 ArkTS `RadioInterface`、`RadioAttribute` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/radio.static.d.ets` | 静态 ArkTS Radio 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/RadioModifier.d.ts` | 动态 Radio Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/RadioModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | Radio C API 节点类型 `ARKUI_NODE_RADIO` 和属性 `NODE_RADIO_*` |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `RadioAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `RadioInterface`、`RadioOptions`、`RadioStyle`。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_RADIO_`、`ARKUI_NODE_RADIO`。

### API 解析实现路径

Radio 已完成组件化改造，JSView 文件不存在，Bridge 和动态属性路径统一到 `pattern/radio/bridge/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/components/arkradio.js` | 前端组件类；ArkTS Modifier 类见 `frameworks/bridge/declarative_frontend/ark_modifier/src/radio_modifier.ts` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/radio/bridge/arkts_native_radio_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/radio/bridge/radio_dynamic_modifier.cpp` | 动态属性路径；ContentModifier 辅助见 `radio_content_modifier_helper.h` |
| Static Modifier | `frameworks/core/components_ng/pattern/radio/bridge/radio_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/radio/bridge/radio_dynamic_module.cpp` | `RadioDynamicModule` 派生类，`libarkui_radio.z.so` 入口 |
| Model Impl | `frameworks/core/components_ng/pattern/radio/bridge/radio_model_impl.cpp` | Model 实现桥接 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/radio_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 SO：`libarkui_radio.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/radio/` | Radio Pattern、Model、事件、布局、值、SetBuilder 等回归测试 |
| Context registry | `docs/context_registry.json` | Radio 的 KB、源码、API、测试统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Radio 功能域 | `specs/05-ui-components/04-input-form-components/04-radio/` | Radio 规格目录 |
| Feat-01 | `specs/05-ui-components/04-input-form-components/04-radio/Feat-01-radio-full-spec.md` | Radio 全量规格 |
| 架构设计 | `specs/05-ui-components/04-input-form-components/04-radio/design.md` | Radio 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 单选不响应 | `RadioPattern` 的点击处理和选中状态；`RadioEventHub` 的 onChange |
| RadioGroup 分组不生效 | `NODE_RADIO_GROUP` 属性；`RadioModelNG::SetGroup()` |
| 选中样式不对 | `RadioPaintProperty` 的绘制属性；`RadioPaintMethod` |
| 无障碍操作无效 | `RadioAccessibilityProperty` |
| 静态前端属性不生效 | `RadioModelStatic` 的属性写入；`radio_static_modifier.cpp` |

## 调试入口

- 创建链路：从 `RadioModelNG::Create()` 确认 Radio 节点创建和 Pattern 设置。
- 属性链路：从 SDK 属性名定位 Bridge → node_modifier → Model 写入，再看 `RadioPaintProperty` 的属性分组。
- 交互链路：从 `RadioPattern` 的点击事件跟踪选中状态变化和 RadioGroup 联动。
- 组件化链路：从 `RadioDynamicModule` 跟踪动态模块加载和属性注册。
- 回归验证：优先运行 `test/unittest/core/pattern/radio/` 下的定向用例。

## 相关主题

- [Checkbox/CheckboxGroup 组件（多选组件，同属选择类组件）](checkbox.md)
- [Toggle 组件（开关组件，同属选择类组件）](toggle.md)