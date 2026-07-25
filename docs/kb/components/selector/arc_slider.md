# ArcSlider Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `ArcSlider`

## 定位

ArcSlider 是 ArkUI 高级 UI 组件（Advanced UI Component），提供圆弧滑动选择器能力，位于 `advanced_ui_component/arcslider/`。ArcSlider 是高级封装组件，基于 ArkTS 声明式语法构建，通过 `@ohos.arkui.advanced.ArcSlider` 模块导出。ArcSlider 没有独立的 `components_ng/pattern/` 实现，不涉及独立 Pattern 和 C API。

本文档用于快速定位 ArcSlider 相关源码、SDK 声明和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ArcSlider 源码 | `advanced_ui_component/arcslider/source/arcslider.ets` | ArcSlider 组件实现 |
| ArcSlider 接口 | `advanced_ui_component/arcslider/interfaces/arcslider.cpp` | ArcSlider 接口桥接 |
| ArcSlider JS 接口 | `advanced_ui_component/arcslider/interfaces/arcslider.js` | ArcSlider JS 接口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.ArcSlider.d.ets` | `@ohos.arkui.advanced.ArcSlider` 动态声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.ArcSlider.static.d.ets` | `@ohos.arkui.advanced.ArcSlider` 静态声明 |
| CAPI / NDK | 无 | 高级组件无独立 C API 接口 |

API 检索建议：

- API 声明：在 SDK 文件中搜索 `ArcSlider`、`ArcSliderOptions`。
- 模块导入：搜索 `@ohos.arkui.advanced.ArcSlider`。

### API 解析实现路径

ArcSlider 是 ArkTS 应用层高级组件，不涉及底层 Pattern/Bridge/Modifier 路径。组件通过 `advanced_ui_component/` 构建系统生成 `.cpp` / `.js` 接口。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 动态前端源码 | `advanced_ui_component/arcslider/source/arcslider.ets` | ArkTS 组件源码 |
| 动态接口桥接 | `advanced_ui_component/arcslider/interfaces/arcslider.cpp` | C++ 接口桥接 |
| 动态 JS 接口 | `advanced_ui_component/arcslider/interfaces/arcslider.js` | JS 接口导出 |

注：ArcSlider 无静态前端聚合源码（`advanced_ui_component_static/` 中不存在），无独立 SO。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Context registry | `docs/context_registry.json` | ArcSlider 的 KB、源码、API 统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 弧形组件功能域 | `specs/10-product-customization/01-wearable/01-arc-component/` | ArcSlider/ArcButton 共享规格目录 |
| Feat-01 | `specs/10-product-customization/01-wearable/01-arc-component/Feat-01-arc-slider-full-spec.md` | ArcSlider 全量规格 |
| 架构设计 | `specs/10-product-customization/01-wearable/01-arc-component/design.md` | 弧形组件架构设计文档（ArcSlider/ArcButton 共享） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ArcSlider 不显示 | `arcslider.ets` 的组件实现和属性传递 |
| 静态前端不生效 | ArcSlider 当前无静态聚合源码，静态构建支持待确认 |

## 调试入口

- 组件源码：从 `arcslider.ets` 跟踪组件实现和属性传递。
- 底层依赖：ArcSlider 可能基于 Slider 或自定义绘制能力构建，查看 Slider 相关源码。

## 相关主题

- Slider 组件（底层滑动选择器组件）
- 组件化改造通用方案
