# TextClock Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextClock`

## 定位

TextClock 是信息展示类组件，用于显示当前系统时间。支持多种时间格式、时区偏移、12/24 小时制自动适配、ContentModifier 自定义、可见区域优化。行为事实以 SDK `.d.ts` 声明、源码、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主逻辑 | `frameworks/core/components_ng/pattern/text_clock/text_clock_pattern.h/cpp` | 生命周期、计时驱动、Tick、控制器注册 |
| Model 动态版 | `frameworks/core/components_ng/pattern/text_clock/text_clock_model_ng.h/cpp` | 动态版属性设置入口 |
| Model 静态版 | `frameworks/core/components_ng/pattern/text_clock/text_clock_model_static.h/cpp` | ArkTS 静态版 Model |
| Model 基类 | `frameworks/core/components_ng/pattern/text_clock/text_clock_model.h` | 纯虚接口声明 |
| Layout 属性 | `frameworks/core/components_ng/pattern/text_clock/text_clock_layout_property.h/cpp` | Format/timeZoneOffset/字体属性 |
| Layout 算法 | `frameworks/core/components_ng/pattern/text_clock/text_clock_layout_algorithm.h/cpp` | BoxLayoutAlgorithm 子类 |
| Event Hub | `frameworks/core/components_ng/pattern/text_clock/text_clock_event_hub.h` | onDateChange 事件回调 |
| Accessibility | `frameworks/core/components_ng/pattern/text_clock/text_clock_accessibility_property.h/cpp` | 无障碍 GetText() |
| MultiThread | `frameworks/core/components_ng/pattern/text_clock/text_clock_pattern_multi_thread.cpp` | 多线程场景 |
| Bridge | `frameworks/core/components_ng/pattern/text_clock/bridge/arkts_native_text_clock_bridge.cpp` | ArkTS Native Bridge |
| DynamicModule | `frameworks/core/components_ng/pattern/text_clock/bridge/text_clock_dynamic_module.cpp` | 组件化入口 |
| C API Modifier | `frameworks/core/interfaces/native/node/text_clock_modifier.cpp` | C API 属性修改器 |
| Controller | `frameworks/core/components/text_clock/text_clock_controller.h` | start/stop 控制器 |
| JSView | `frameworks/bridge/declarative_frontend/jsview/js_text_clock.h` | 旧版声明式前端 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_clock.d.ts` | TextClock 公开 API |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/textClock.static.d.ets` | 静态版 API 定义 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/TextClockModifier.d.ts` | 属性修改器动态版 |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/TextClockModifier.static.d.ets` | 属性修改器静态版 |

### API 解析实现路径

TextClock **已组件化**（有 bridge/ 子目录、DynamicModule、统一 Bridge，旧 JSView 已移除）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/text_clock/bridge/arkts_native_text_clock_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/text_clock/bridge/text_clock_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/text_clock/bridge/text_clock_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/text_clock/bridge/text_clock_dynamic_module.cpp` | DynamicModule 派生类 |
| ContentModifier Helper | `frameworks/core/components_ng/pattern/text_clock/text_clock_content_modifier_helper.h` | ContentModifier 辅助结构 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 系统时间监听 | `frameworks/core/event/time/time_event_proxy.h` | 系统服务 | — | TimeEventProxy 监听系统时间变更 |
| 本地化 | `frameworks/core/components_ng/pattern/text_clock/text_clock_pattern.cpp` | 系统服务 | — | Localization 获取月份/星期/AM-PM |
| 12/24小时制 | `frameworks/core/components_ng/pattern/text_clock/text_clock_pattern.cpp` | 系统属性 | — | SystemProperties::Is24HourClock() |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text_clock/` | Pattern/Model 单元测试 |
| C API Modifier 测试 | `test/unittest/capi/modifiers/` | C API 属性修改器测试 |

### 相关 Spec

- Spec: `specs/05-ui-components/10-information-display-components/07-text-clock/`
- Design: `specs/05-ui-components/10-information-display-components/07-text-clock/design.md`
- arkui-specs Specs: `Feat-01-time-format-spec.md`, `Feat-02-controller-scheduling-spec.md`, `Feat-03-style-content-modifier-spec.md`, `Feat-04-events-config-componentization-spec.md`
- FuncID: 05-10-07

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 时间不更新 | text_clock_pattern.cpp 的 PostDelayedTask 和可见区域逻辑 |
| 时区偏移无效 | text_clock_layout_property.h 的 timeZoneOffset 处理 |
| 格式化结果异常 | text_clock_pattern.cpp 的 FormatTime 逻辑 |
| 12/24小时制不正确 | SystemProperties::Is24HourClock() 和 format 中 H/h 判断 |

## 调试入口

- 时间更新调试：`text_clock_pattern.cpp` 的 `OnVisibleChange` 和 `PostDelayedTask`
- 格式化调试：`text_clock_pattern.cpp` 的 `FormatTime` 方法
- 时区偏移调试：`text_clock_layout_property.h` 的 `GetTimeZoneOffset` 方法

## 相关主题

- **Text**: TextClock 内部创建 Text 子节点渲染时间文本
- **TextTheme**: 提供默认字体样式
- **TextTimer**: 同属时间显示组件，但提供正/倒计时功能
- **Localization**: 本地化时间格式
- **DynamicModuleHelper**: 组件化动态加载
