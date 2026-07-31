# Gauge Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `Gauge`

## 定位

Gauge 是仪表盘组件，用于数据占比环形展示。支持单色（Monochrome）、渐变（Gradient）、多段（MultiSegment）三种类型。支持自定义角度范围、颜色、描边宽度。行为细节以 SDK 声明、源码实现和规格文档为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp` | FrameNode 生命周期管理 |
| Model | `frameworks/core/components_ng/pattern/gauge/gauge_model_ng.cpp` | 动态范式 Model |
| Model Static | `frameworks/core/components_ng/pattern/gauge/gauge_model_static.cpp` | 静态范式 Model |
| Layout Property | `frameworks/core/components_ng/pattern/gauge/gauge_layout_property.h` | 布局属性存储 |
| Paint Property | `frameworks/core/components_ng/pattern/gauge/gauge_paint_property.h` | 绘制属性存储 |
| Paint Method | `frameworks/core/components_ng/pattern/gauge/gauge_paint_method.cpp` | 绘制方法 |
| Modifier | `frameworks/core/components_ng/pattern/gauge/gauge_modifier.cpp` | 绘制修饰器 |
| Layout Algorithm | `frameworks/core/components_ng/pattern/gauge/gauge_layout_algorithm.cpp` | 布局算法 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/gauge.d.ts` | 动态 API 声明 |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/gauge.static.d.ets` | 静态 API 声明 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/GaugeModifier.d.ts` | 动态 Modifier |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/GaugeModifier.static.d.ets` | 静态 Modifier |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/gauge/bridge/arkts_native_gauge_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/gauge/bridge/gauge_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/gauge/bridge/gauge_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/gauge/bridge/gauge_dynamic_module.cpp` | `DynamicModule` 派生类，`libarkui_gauge.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/components_ng/pattern/gauge/gauge_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 so 名称：`libarkui_gauge.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/gauge/` | Pattern/Model 层单元测试 |
| C API 测试 | `test/unittest/capi/modifiers/gauge_modifier_test.cpp` | C API Modifier 测试 |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| Gauge 设计 | `specs/05-ui-components/10-information-display-components/02-gauge/design.md` | Baselined |
| Feat-01 核心属性 | `specs/05-ui-components/10-information-display-components/02-gauge/Feat-01-gauge-core-spec.md` | Baselined |
| Feat-02 高级配置 | `specs/05-ui-components/10-information-display-components/02-gauge/Feat-02-gauge-advanced-config-spec.md` | Baselined |
| Feat-03 高级能力 | `specs/05-ui-components/10-information-display-components/02-gauge/Feat-03-gauge-advanced-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| value 范围钳制 | Bridge 和 Modifier 双级验证 |
| min >= max 处理 | Bridge 层参数验证，重置为 (0, 100) |
| GaugeType 分发 | Modifier 层绘制方法分发 |
| strokeWidth 约束 | 不支持百分比，超过半径时钳制 |
| 权重归一化 | Modifier 渲染计算逻辑 |

## 调试入口

- 搜索关键词：`Gauge`、`GaugeType`、`GaugeOptions`、`GaugeConfiguration`
- Pattern 文件：`gauge_pattern.cpp`
- Bridge 文件：`arkts_native_gauge_bridge.cpp`
- Modifier 文件：`gauge_modifier.cpp`

## 相关主题

- DataPanel：数据面板组件，同属信息展示类
- Progress：进度条组件
- LoadingProgress：加载进度组件