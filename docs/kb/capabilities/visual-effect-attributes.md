# VisualEffectAttributes Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `VisualEffectAttributes`

## 定位

ArkUI 视效属性包括模糊（blur/backdropBlur）、亮度（brightness）、对比度（contrast）、饱和度（saturatae）、复古（sepia）、反色（invert）等。属性通过 ViewAbstract 设置到 RenderContext 的 RenderProperty，C API 通过 node_common_modifier 暴露。

本文档用于快速定位 Visual Effect Attributes 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| view_abstract | `frameworks/core/components_ng/base/view_abstract.cpp` | |
| view_abstract_model_ng | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | |
| view_abstract_model_static | `frameworks/core/components_ng/base/view_abstract_model_static.cpp` | |
| render_context | `frameworks/core/components_ng/render/render_context.h` | |
| render_property | `frameworks/core/components_ng/render/render_property.cpp` | |
| color_filter | `frameworks/core/components_ng/render/color_filter.h` | |
| js_view_abstract | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | |
| node_common_modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | |
| visual_effect_ani_modifier | `frameworks/core/interfaces/native/ani/visual_effect_ani_modifier.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |
| ui_effect | `<OH_ROOT>/interface/sdk-js/api/@ohos.graphics.uiEffect.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/base/view_abstract_test_ng_for_visual_effect.cpp | |
| test/unittest/core/base/view_abstract_test_ng.cpp | |
| test/unittest/core/base/view_abstract_model_test_ng.cpp | |
| test/unittest/core/base/view_abstract_model_static_test_ng.cpp | |
| test/unittest/interfaces/node_visual_effect_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/04-common-capability/03-common-attributes/02-visual-effect-attributes/` | 视效属性（blur/brightness/contrast/saturate/sepia/invert/backdropBlur 等），通过 ViewAbstract 设置到 RenderContext。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| blur 不生效 | 确认 RenderContext 的 backdropBlur 和 frontBlur 属性设置 |
| 颜色滤镜不正确 | 检查 ColorFilter 构建链路和 RenderProperty 的 propFrontBrightness/Contrast/Saturate |

## 调试入口

- 属性链路：ViewAbstract → RenderContext → RenderProperty
- C API 链路：node_common_modifier → visual_effect_ani_modifier

## 相关主题

- 基础布局属性
- 基础单位
