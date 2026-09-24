# ContentModifierDisplay Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ContentModifierDisplay`

## 定位

ArkUI 信息展示类组件 ContentModifier 允许开发者自定义组件内部渲染内容。覆盖 DataPanel/Gauge/Progress/LoadingProgress/TextClock/TextTimer。每个组件在 bridge/ 目录下有 ContentModifierHelper，通过 Pattern::UseContentModifier 切换渲染路径。

本文档用于快速定位 ContentModifier (Display) 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| modifier_base | `frameworks/core/components_ng/base/modifier.h` | |
| data_panel_content_modifier_helper | `frameworks/core/components_ng/pattern/data_panel/bridge/data_panel_content_modifier_helper.h` | |
| gauge_content_modifier_helper | `frameworks/core/components_ng/pattern/gauge/bridge/content_modifier_helper.h` | |
| progress_pattern | `frameworks/core/components_ng/pattern/progress/progress_pattern.h` | |
| loading_progress_content_modifier_helper | `frameworks/core/components_ng/pattern/loading_progress/bridge/content_modifier_helper.h` | |
| text_clock_content_modifier_helper | `frameworks/core/components_ng/pattern/text_clock/bridge/text_clock_content_modifier_helper.h` | |
| text_timer_content_modifier_helper | `frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_content_modifier_helper.h` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |
| progress | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/progress.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/data_panel/data_panel_content_modifier_test_ng.cpp | |
| test/unittest/core/pattern/progress/progress_content_modifier_test_ng.cpp | |
| test/unittest/core/pattern/text_clock/text_clock_content_modifier_test_ng.cpp | |
| test/unittest/interfaces/ace_kit/content_modifier_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/04-common-capability/05-custom-extension/04-content-modifier-display/` | 信息展示类组件（DataPanel/Gauge/Progress/LoadingProgress/TextClock/TextTimer）的 ContentModifier 自定义内容机制。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ContentModifier 不生效 | 确认 Pattern::UseContentModifier() 和 BuildContentModifierNode 链路 |
| 自定义内容不更新 | 检查 @ObservedV2/@Trace 响应式更新是否触发 ContentModifier 重建 |

## 调试入口

- 渲染链路：Pattern::BuildContentModifierNode → ContentModifierHelper
- 切换链路：UseContentModifier() 控制自定义渲染

## 相关主题

- [自定义内容-表单类](content-modifier-form.md)
- [Progress 组件](../components/data_display/progress.md)
- [Gauge 组件](../components/data_display/gauge.md)