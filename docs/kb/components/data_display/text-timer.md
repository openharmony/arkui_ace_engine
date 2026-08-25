# TextTimer Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextTimer`

## 定位

TextTimer 是 ArkUI 的文本计时器组件，提供正计时（秒表）和倒计时两种模式的时间显示。支持自定义格式字符串、字体样式、控制器操作（start/pause/reset）、ContentModifier 自定义内容。行为事实以 SDK `.d.ts` 声明、源码、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主逻辑 | `frameworks/core/components_ng/pattern/texttimer/text_timer_pattern.h/cpp` | 生命周期、计时驱动、Tick、控制器注册 |
| Model 动态版 | `frameworks/core/components_ng/pattern/texttimer/text_timer_model_ng.h/cpp` | 动态版属性设置入口 |
| Model 静态版 | `frameworks/core/components_ng/pattern/texttimer/text_timer_model_static.h/cpp` | ArkTS 静态版 Model |
| Model 基类 | `frameworks/core/components_ng/pattern/texttimer/text_timer_model.h` | 纯虚接口声明 |
| Layout 属性 | `frameworks/core/components_ng/pattern/texttimer/text_timer_layout_property.h/cpp` | Format/IsCountDown/InputCount/StartTime/字体属性 |
| Layout 算法 | `frameworks/core/components_ng/pattern/texttimer/text_timer_layout_algorithm.h/cpp` | BoxLayoutAlgorithm 子类 |
| Event Hub | `frameworks/core/components_ng/pattern/texttimer/text_timer_event_hub.h` | onTimer 事件回调 |
| Accessibility | `frameworks/core/components_ng/pattern/texttimer/text_timer_accessibility_property.h/cpp` | 无障碍 GetText() |
| Controller | `frameworks/core/components/texttimer/texttimer_controller.h` | start/pause/reset 控制器 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_timer.d.ts` | TextTimer 公开 API |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/textTimer.static.d.ets` | 静态版 API 定义 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/TextTimerModifier.d.ts` | 属性修改器动态版 |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/TextTimerModifier.static.d.ets` | 属性修改器静态版 |

### API 解析实现路径

TextTimer **已组件化**（有 bridge/ 子目录、DynamicModule、统一 Bridge，旧 JSView 已移除）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/texttimer/bridge/arkts_native_text_timer_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_dynamic_modifier.cpp` | 动态属性路径，导出 ArkUITextTimerModifier |
| Static Modifier | `frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_static_modifier.cpp` | 静态属性路径，使用 Converter 模式 |
| Dynamic Module | `frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_dynamic_module.cpp` | 组件化入口，OHOS_ACE_DynamicModule_Create_TextTimer |
| ContentModifier Helper | `frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_content_modifier_helper.h` | ContentModifier 辅助结构 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 时间格式化 | `frameworks/core/components_ng/pattern/texttimer/text_timer_pattern.cpp` | 系统服务 | — | Localization::FormatDuration() 格式化 |
| 帧调度 | `frameworks/core/components_ng/pattern/texttimer/text_timer_pattern.cpp` | 引擎内部 | — | Scheduler 驱动帧同步定时更新 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/texttimer/` | Pattern/Model 单元测试 |
| C API Modifier 测试 | `test/unittest/capi/modifiers/` | C API 属性修改器测试 |

### 相关 Spec

- Spec: `specs/05-ui-components/10-information-display-components/08-text-timer/`
- Design: `specs/05-ui-components/10-information-display-components/08-text-timer/design.md`
- arkui-specs Specs: `Feat-01-timing-modes-format-spec.md`, `Feat-02-controller-events-spec.md`, `Feat-03-style-content-modifier-spec.md`, `Feat-04-visibility-componentization-spec.md`
- FuncID: 05-10-08

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 计时不更新 | text_timer_pattern.cpp 的 Scheduler 和可见区域逻辑 |
| 倒计时不暂停 | text_timer_pattern.cpp 的 HandlePause 和 HandleCountDown |
| 格式化结果异常 | arkts_native_text_timer_bridge.cpp 的格式校验逻辑 |
| inputCount 无效 | arkts_native_text_timer_bridge.cpp 的边界校验 (0 < count < 86400000) |

## 调试入口

- 计时驱动调试：`text_timer_pattern.cpp` 的 `OnModifyDone` 和 `OnTick`
- 格式化调试：`text_timer_pattern.cpp` 的 `FormatTime` 方法
- 控制器调试：`texttimer_controller.h` 的 start/pause/reset 回调

## 相关主题

- **Text**: TextTimer 内部创建 Text 子节点渲染时间文本
- **TextTheme**: 提供默认字体样式
- **TextClock**: 同属时间显示组件，但显示系统时钟
- **Scheduler**: 驱动帧同步定时更新
- **Localization**: 提供 FormatDuration() 时间格式化