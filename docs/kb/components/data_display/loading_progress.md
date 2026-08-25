# LoadingProgress Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `LoadingProgress`

## 定位

LoadingProgress 是加载进度组件，用于加载状态可视化展示。采用彗星-环动画效果，分 5 个阶段循环播放。支持自定义颜色、前景色和加载状态控制。行为细节以 SDK 声明、源码实现和规格文档为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.cpp` | 生命周期、动画启停、主题更新 |
| Model | `frameworks/core/components_ng/pattern/loading_progress/loading_progress_model_ng.cpp` | 动态范式 Model |
| Model Static | `frameworks/core/components_ng/pattern/loading_progress/loading_progress_model_static.cpp` | 静态范式 Model |
| Paint Property | `frameworks/core/components_ng/pattern/loading_progress/loading_progress_paint_property.h` | 绘制属性存储 |
| Modifier | `frameworks/core/components_ng/pattern/loading_progress/loading_progress_modifier.cpp` | 彗星-环动画绘制 |
| Layout Algorithm | `frameworks/core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.cpp` | 默认尺寸计算 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/loading_progress.d.ts` | 动态 API 声明 |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/loadingProgress.static.d.ets` | 静态 API 声明 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/LoadingProgressModifier.d.ts` | 动态 Modifier |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/LoadingProgressModifier.static.d.ets` | 静态 Modifier |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/loading_progress/bridge/arkts_native_loading_progress_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/loading_progress/bridge/loading_progress_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/loading_progress/bridge/loading_progress_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/loading_progress/bridge/loading_progress_dynamic_module.cpp` | `DynamicModule` 派生类，`libarkui_loading_progress.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/components_ng/pattern/loading_progress/loading_progress_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 so 名称：`libarkui_loading_progress.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/loading_progress/` | Pattern/Model 层单元测试 |
| C API 测试 | `test/unittest/capi/modifiers/loading_progress_modifier_test.cpp` | C API Modifier 测试 |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| LoadingProgress 设计 | `specs/05-ui-components/10-information-display-components/03-loading-progress/design.md` | Baselined |
| Feat-01 全量规格 | `specs/05-ui-components/10-information-display-components/03-loading-progress/Feat-01-loading-progress-full-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 动画阶段控制 | Modifier 层 5 阶段绘制逻辑 |
| 颜色属性合并 | color/foregroundColor 共享属性，`colorSetByUser` 标志区分 |
| visibility 联动 | Pattern 层可见性变化自动启停动画 |
| enableLoading 控制 | Pattern 层状态管理 |

## 调试入口

- 搜索关键词：`LoadingProgress`、`LoadingProgressStyle`、`enableLoading`
- Pattern 文件：`loading_progress_pattern.cpp`
- Bridge 文件：`arkts_native_loading_progress_bridge.cpp`
- Modifier 文件：`loading_progress_modifier.cpp`

## 相关主题

- Progress：进度条组件
- DataPanel：数据面板组件
- Gauge：仪表盘组件