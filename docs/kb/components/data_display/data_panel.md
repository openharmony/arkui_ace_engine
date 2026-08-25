# DataPanel Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `DataPanel`

## 定位

DataPanel 是数据面板组件，用于数据占比可视化展示。支持环形进度（CIRCLE）和线性进度（LINE）两种类型。最多支持 9 个数据段，支持自定义颜色、阴影和圆角。行为细节以 SDK 声明、源码实现和规格文档为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/data_panel/data_panel_pattern.cpp` | FrameNode 生命周期管理 |
| Model | `frameworks/core/components_ng/pattern/data_panel/data_panel_model_ng.cpp` | 动态范式 Model |
| Model Static | `frameworks/core/components_ng/pattern/data_panel/data_panel_model_static.cpp` | 静态范式 Model |
| Paint Property | `frameworks/core/components_ng/pattern/data_panel/data_panel_paint_property.h` | 绘制属性存储 |
| Paint Method | `frameworks/core/components_ng/pattern/data_panel/data_panel_paint_method.cpp` | 绘制方法 |
| Modifier | `frameworks/core/components_ng/pattern/data_panel/data_panel_modifier.cpp` | 绘制修饰器 |
| Layout Algorithm | `frameworks/core/components_ng/pattern/data_panel/data_panel_layout_algorithm.cpp` | 布局算法 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/data_panel.d.ts` | 动态 API 声明 |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/dataPanel.static.d.ets` | 静态 API 声明 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/DataPanelModifier.d.ts` | 动态 Modifier |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/DataPanelModifier.static.d.ets` | 静态 Modifier |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/data_panel/bridge/arkts_native_data_panel_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/data_panel/bridge/data_panel_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/data_panel/bridge/data_panel_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/data_panel/bridge/data_panel_dynamic_module.cpp` | `DynamicModule` 派生类，`libarkui_data_panel.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/components_ng/pattern/data_panel/data_panel_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 so 名称：`libarkui_data_panel.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/data_panel/` | Pattern/Model 层单元测试 |
| C API 测试 | `test/unittest/capi/modifiers/data_panel_modifier_test.cpp` | C API Modifier 测试 |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| DataPanel 设计 | `specs/05-ui-components/10-information-display-components/01-data-panel/design.md` | Baselined |
| Feat-01 基础构造 | `specs/05-ui-components/10-information-display-components/01-data-panel/Feat-01-data-panel-ctor-spec.md` | Baselined |
| Feat-02 样式属性 | `specs/05-ui-components/10-information-display-components/01-data-panel/Feat-02-data-panel-style-spec.md` | Baselined |
| Feat-03 高级能力 | `specs/05-ui-components/10-information-display-components/01-data-panel/Feat-03-data-panel-advanced-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| values 数组限制 | Bridge 层参数验证、PaintProperty 存取逻辑 |
| type 不可变 | Pattern 层 `isFirstCreate_` 标志 |
| closeEffect 反转存储 | PaintProperty 中 `Effect = !closeEffect` |
| valueColors 长度限制 | Modifier 绘制逻辑，主题色对预定义 |

## 调试入口

- 搜索关键词：`DataPanel`、`DataPanelType`、`DataPanelOptions`、`DataPanelShadow`
- Pattern 文件：`data_panel_pattern.cpp`
- Bridge 文件：`arkts_native_data_panel_bridge.cpp`
- Modifier 文件：`data_panel_modifier.cpp`

## 相关主题

- Gauge：仪表盘组件，同属信息展示类
- Progress：进度条组件
- LoadingProgress：加载进度组件