# ArcButton Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `ArcButton`

## 定位

ArcButton 是 ArkUI 高级 UI 组件（Advanced UI Component），提供圆弧按钮交互能力，位于 `advanced_ui_component/arcbutton/`。ArcButton 是高级封装组件，基于 ArkTS 声明式语法构建，通过 `@ohos.arkui.advanced.ArcButton` 模块导出。ArcButton 没有独立的 `components_ng/pattern/` 实现，不涉及独立 Pattern 和 C API。

本文档用于快速定位 ArcButton 相关源码、SDK 声明和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ArcButton 源码 | `advanced_ui_component/arcbutton/source/arcbutton.ets` | ArcButton 组件实现 |
| ArcButton 接口 | `advanced_ui_component/arcbutton/interfaces/arcbutton.cpp` | ArcButton 接口桥接 |
| ArcButton JS 接口 | `advanced_ui_component/arcbutton/interfaces/arcbutton.js` | ArcButton JS 接口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.ArcButton.d.ets` | `@ohos.arkui.advanced.ArcButton` 动态声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.ArcButton.static.d.ets` | `@ohos.arkui.advanced.ArcButton` 静态声明 |
| CAPI / NDK | 无 | 高级组件无独立 C API 接口 |

API 检索建议：

- API 声明：在 SDK 文件中搜索 `ArcButton`、`ArcButtonOptions`。
- 模块导入：搜索 `@ohos.arkui.advanced.ArcButton`。

### API 解析实现路径

ArcButton 是 ArkTS 应用层高级组件，不涉及底层 Pattern/Bridge/Modifier 路径。组件通过 `advanced_ui_component/` 构建系统生成 `.cpp` / `.js` 接口。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 动态前端源码 | `advanced_ui_component/arcbutton/source/arcbutton.ets` | ArkTS 组件源码 |
| 动态接口桥接 | `advanced_ui_component/arcbutton/interfaces/arcbutton.cpp` | C++ 接口桥接 |
| 动态 JS 接口 | `advanced_ui_component/arcbutton/interfaces/arcbutton.js` | JS 接口导出 |

注：ArcButton 无静态前端聚合源码（`advanced_ui_component_static/` 中不存在），无独立 SO。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Context registry | `docs/context_registry.json` | ArcButton 的 KB、源码、API 统一路由 |

> 注：ArcButton 当前暂无独立单元测试，后续 PR 计划补齐。

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 弧形组件功能域 | `specs/10-product-customization/01-wearable/01-arc-component/` | ArcSlider/ArcButton 共享规格目录 |
| Feat-02 | `specs/10-product-customization/01-wearable/01-arc-component/Feat-02-arc-button-full-spec.md` | ArcButton 全量规格 |
| 架构设计 | `specs/10-product-customization/01-wearable/01-arc-component/design.md` | 弧形组件架构设计文档（ArcSlider/ArcButton 共享） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ArcButton 不显示 | `arcbutton.ets` 的组件实现和属性传递 |
| 静态前端不生效 | ArcButton 当前无静态聚合源码，静态构建支持待确认 |

## 调试入口

- 组件源码：从 `arcbutton.ets` 跟踪组件实现和属性传递。
- 底层依赖：ArcButton 可能基于 Button 或自定义绘制能力构建，查看 Button 相关源码。

## 相关主题

- Button 组件（底层按钮组件）
- 组件化改造通用方案
