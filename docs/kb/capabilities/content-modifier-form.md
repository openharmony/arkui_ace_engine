# ContentModifierForm Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ContentModifierForm`

## 定位

ArkUI 表单类组件 ContentModifier 允许开发者自定义组件内部渲染内容。覆盖 Button/Checkbox/Radio/Rating/Select/Slider/Toggle。每个组件在 bridge/ 目录下有 ContentModifierHelper，通过 Pattern::UseContentModifier 切换渲染路径。

本文档用于快速定位 ContentModifier (Form) 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| modifier_base | `frameworks/core/components_ng/base/modifier.h` | |
| button_content_modifier_helper | `frameworks/core/components_ng/pattern/button/bridge/button_content_modifier_helper.h` | |
| checkbox_content_modifier_helper | `frameworks/core/components_ng/pattern/checkbox/bridge/checkbox_content_modifier_helper.h` | |
| radio_content_modifier_helper | `frameworks/core/components_ng/pattern/radio/bridge/radio_content_modifier_helper.h` | |
| rating_content_modifier_helper | `frameworks/core/components_ng/pattern/rating/bridge/rating_content_modifier_helper.h` | |
| slider_content_modifier_helper | `frameworks/core/components_ng/pattern/slider/bridge/slider_content_modifier_helper.h` | |
| toggle_content_modifier_helper | `frameworks/core/components_ng/pattern/toggle/bridge/toggle_content_modifier_helper.h` | |
| select_pattern | `frameworks/core/components_ng/pattern/select/select_pattern.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |
| button | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/button.d.ts` | |
| slider | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/slider.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/button/button_content_modifier_test_ng.cpp | |
| test/unittest/core/pattern/checkbox/checkbox_content_modifier_test_ng.cpp | |
| test/unittest/core/pattern/rating/rating_content_modifier_test_ng.cpp | |
| test/unittest/core/pattern/slider/slider_content_modifier_test_ng.cpp | |
| test/unittest/core/pattern/toggle/toggle_content_modifier_test_ng.cpp | |
| test/unittest/interfaces/ace_kit/content_modifier_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/04-common-capability/05-custom-extension/03-content-modifier-form/` | 表单类组件（Button/Checkbox/Radio/Rating/Select/Slider/Toggle）的 ContentModifier 自定义内容机制。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ContentModifier 不生效 | 确认 Pattern::UseContentModifier() 返回 true 且 BuildContentModifierNode 被调用 |
| 自定义内容样式异常 | 检查 ContentModifierHelper 的属性透传逻辑 |

## 调试入口

- 渲染链路：Pattern::BuildContentModifierNode → ContentModifierHelper
- 切换链路：UseContentModifier() 控制 Pattern 走自定义或默认渲染

## 相关主题

- [自定义内容-信息展示类](content-modifier-display.md)
- [Rating 组件](../components/input-form/rating.md)
- [Slider 组件](../components/input-form/slider.md)