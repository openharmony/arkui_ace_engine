# Rating Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `Rating`

## 定位

ArkUI Rating 组件提供星级评分交互能力，支持 stars（星数）、stepSize（步长）、indicator（指示器模式）等属性。已完成组件化改造，输出独立 SO。支持 ContentModifier 自定义渲染。C API 暴露为 `ARKUI_NODE_RATING` 节点类型。

本文档用于快速定位 Rating 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| pattern | `frameworks/core/components_ng/pattern/rating/rating_pattern.cpp` | |
| pattern_h | `frameworks/core/components_ng/pattern/rating/rating_pattern.h` | |
| model | `frameworks/core/components_ng/pattern/rating/rating_model_ng.cpp` | |
| static_model | `frameworks/core/components_ng/pattern/rating/rating_model_static.cpp` | |
| layout_algorithm | `frameworks/core/components_ng/pattern/rating/rating_layout_algorithm.cpp` | |
| layout_property | `frameworks/core/components_ng/pattern/rating/rating_layout_property.h` | |
| paint_method | `frameworks/core/components_ng/pattern/rating/rating_paint_method.h` | |
| render_property | `frameworks/core/components_ng/pattern/rating/rating_render_property.h` | |
| modifier | `frameworks/core/components_ng/pattern/rating/rating_modifier.cpp` | |
| event_hub | `frameworks/core/components_ng/pattern/rating/rating_event_hub.h` | |
| accessibility | `frameworks/core/components_ng/pattern/rating/rating_accessibility_property.cpp` | |
| bridge | `frameworks/core/components_ng/pattern/rating/bridge/arkts_native_rating_bridge.cpp` | |
| dynamic_modifier | `frameworks/core/components_ng/pattern/rating/bridge/rating_dynamic_modifier.cpp` | |
| static_modifier | `frameworks/core/components_ng/pattern/rating/bridge/rating_static_modifier.cpp` | |
| dynamic_module | `frameworks/core/components_ng/pattern/rating/bridge/rating_dynamic_module.cpp` | |
| content_modifier_helper | `frameworks/core/components_ng/pattern/rating/bridge/rating_content_modifier_helper.h` | |
| node_modifier | `frameworks/core/interfaces/native/implementation/rating_modifier.cpp` | |
| node_ops_accessor | `frameworks/core/interfaces/native/implementation/rating_ops_accessor.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/rating.d.ts` | |
| static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/rating.static.d.ets` | |

### API 解析实现路径

Rating **已组件化**（有 `bridge/` 子目录、DynamicModule、统一 Bridge，旧 JSView 已移除），输出独立 SO。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/rating/bridge/arkts_native_rating_bridge.cpp` | ArkTS Native Bridge |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/rating/bridge/rating_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/rating/bridge/rating_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/rating/bridge/rating_dynamic_module.cpp` | DynamicModule 派生类 |
| Content Modifier | `frameworks/core/components_ng/pattern/rating/bridge/rating_content_modifier_helper.h` | ContentModifier 自定义内容 |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/rating/ | |
| test/unittest/capi/modifiers/rating_modifier_test.cpp | |
| test/unittest/capi/accessors/rating_content_modifier_accessor_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/05-ui-components/04-input-form-components/03-rating/` | Rating 评分组件，支持星级评分、步长、指示器模式和 ContentModifier 自定义内容。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 评分不响应触摸 | 检查 RatingPattern 的 OnTouch 事件处理和热区判定 |
| 自定义内容不生效 | 确认 UseContentModifier() 和 BuildContentModifierNode 链路 |
| 星级图标显示异常 | 查看 RatingPaintMethod 的绘制逻辑和 rating_render_property |

## 调试入口

- 创建链路：RatingModelNG::Create() → RatingPattern
- 交互链路：RatingPattern::OnTouch → 评分计算
- 渲染链路：RatingPaintMethod → RatingRenderProperty

## 相关主题

- [Slider 组件](slider.md)
- [自定义内容-表单类](../../capabilities/content-modifier-form.md)
- [Toggle 组件](../selector/toggle.md)