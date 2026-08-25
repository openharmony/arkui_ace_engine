# PatternLock Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `PatternLock`

## 定位

PatternLock 是九宫格图案锁组件，用于安全解锁场景。提供 3x3 点阵布局，支持手势滑动连接。支持自定义颜色、圆点半径、线宽、侧边长度等属性。提供图案完成和点连接事件回调。行为细节以 SDK 声明、源码实现和规格文档为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/patternlock/patternlock_pattern.cpp` | 生命周期、触摸事件、控制器绑定 |
| Model | `frameworks/core/components_ng/pattern/patternlock/patternlock_model_ng.cpp` | 动态范式 Model |
| Model Static | `frameworks/core/components_ng/pattern/patternlock/patternlock_model_static.cpp` | 静态范式 Model |
| Layout Property | `frameworks/core/components_ng/pattern/patternlock/patternlock_layout_property.h` | sideLength 属性存储 |
| Paint Property | `frameworks/core/components_ng/pattern/patternlock/patternlock_paint_property.h` | 颜色、半径等属性存储 |
| Paint Method | `frameworks/core/components_ng/pattern/patternlock/patternlock_paint_method.cpp` | 属性传递到 Modifier |
| Modifier | `frameworks/core/components_ng/pattern/patternlock/patternlock_modifier.cpp` | 9 宫格绘制、路径连接 |
| Layout Algorithm | `frameworks/core/components_ng/pattern/patternlock/patternlock_layout_algorithm.cpp` | 正方形尺寸测量 |
| Controller | `frameworks/core/components_ng/pattern/patternlock/pattern_lock_controller.cpp` | 控制器实现 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/pattern_lock.d.ts` | 动态 API 声明 |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/patternLock.static.d.ets` | 静态 API 声明 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/PatternLockModifier.d.ts` | 动态 Modifier |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/PatternLockModifier.static.d.ets` | 静态 Modifier |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/patternlock/arkts_native_pattern_lock_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/patternlock/patternlock_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/patternlock/patternlock_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/patternlock/patternlock_dynamic_module.cpp` | `DynamicModule` 派生类，`libarkui_patternlock.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/components_ng/pattern/patternlock/patternlock_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |

独立 so 名称：`libarkui_patternlock.z.so`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/patternlock/` | Pattern/Model 层单元测试 |
| C API 测试 | `test/unittest/capi/modifiers/pattern_lock_modifier_test.cpp` | C API Modifier 测试 |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| PatternLock 设计 | `specs/05-ui-components/10-information-display-components/04-pattern-lock/design.md` | Baselined |
| Feat-01 核心属性 | `specs/05-ui-components/10-information-display-components/04-pattern-lock/Feat-01-pattern-lock-core-properties-visual-spec.md` | Baselined |
| Feat-02 交互事件 | `specs/05-ui-components/10-information-display-components/04-pattern-lock/Feat-02-pattern-lock-interaction-events-controller-spec.md` | Baselined |
| Feat-03 多范式接口 | `specs/05-ui-components/10-information-display-components/04-pattern-lock/Feat-03-pattern-lock-multi-paradigm-capi-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| sideLength 存储位置 | LayoutProperty，触发重新测量 |
| 颜色属性追踪 | SetByUser 标志位，主题切换优先级 |
| 单元格中心计算 | Modifier 层公式计算 |
| 多点触控处理 | Pattern 层只跟踪第一个手指 |
| 自动重置策略 | Pattern 层 `autoReset` 标志 |
| 跳过未选中点 | 共线检测自动添加中间点 |
| 波纹效果控制 | `enableWaveEffect` 标志 |

## 调试入口

- 搜索关键词：`PatternLock`、`PatternLockCell`、`PatternLockController`、`patternComplete`、`dotConnect`
- Pattern 文件：`patternlock_pattern.cpp`
- Bridge 文件：`arkts_native_pattern_lock_bridge.cpp`
- Modifier 文件：`patternlock_modifier.cpp`
- Controller 文件：`pattern_lock_controller.cpp`

## 相关主题

- DataPanel：数据面板组件
- Gauge：仪表盘组件
- 安全验证：应用层实现密码验证逻辑