# Popup Advanced Context

> 文档版本：v1.1
> 更新时间：2026-07-23
> 来源：`docs/context_registry.json` 主题 `PopupAdvanced`

## 定位

Popup 高级组件是 ArkUI 高级 UI 组件（Advanced UI Component），位于 `advanced_ui_component/popup/`（v1）和 `advanced_ui_component/popupv2/`（v2），提供封装好的气泡弹窗能力。高级组件基于 ArkTS 声明式语法构建，通过 `@ohos.arkui.advanced.Popup` 和 `@ohos.arkui.advanced.PopupV2` 模块导出。与底层 `bindPopup` 属性和 `BubblePattern` 不同，高级 Popup 是应用层封装组件，不涉及独立 Pattern 和 C API。

本文档用于快速定位 Popup 高级组件相关源码、SDK 声明和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Popup v1 源码 | `advanced_ui_component/popup/source/popup.ets` | Popup v1 组件实现 |
| Popup v1 接口 | `advanced_ui_component/popup/interfaces/popup.cpp` | Popup v1 接口桥接 |
| Popup v1 JS 接口 | `advanced_ui_component/popup/interfaces/popup.js` | Popup v1 JS 接口 |
| Popup v2 源码 | `advanced_ui_component/popupv2/source/popupv2.ets` | Popup v2 组件实现 |
| Popup v2 接口 | `advanced_ui_component/popupv2/interfaces/popupv2.cpp` | Popup v2 接口桥接 |
| Popup v2 JS 接口 | `advanced_ui_component/popupv2/interfaces/popupv2.js` | Popup v2 JS 接口 |
| 静态 Popup v1 | `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.Popup.ets` | 静态前端 Popup v1 聚合源码 |
| 静态 Popup v2 | `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.PopupV2.ets` | 静态前端 Popup v2 聚合源码 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API (Popup v1) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.Popup.d.ets` | `@ohos.arkui.advanced.Popup` 动态声明 |
| Static API (Popup v1) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.Popup.static.d.ets` | `@ohos.arkui.advanced.Popup` 静态声明 |
| Dynamic API (Popup v2) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.PopupV2.d.ets` | `@ohos.arkui.advanced.PopupV2` 动态声明 |
| Static API (Popup v2) | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.advanced.PopupV2.static.d.ets` | `@ohos.arkui.advanced.PopupV2` 静态声明 |
| CAPI / NDK | 无 | 高级组件无独立 C API 接口 |

API 检索建议：

- API 声明：在 SDK 文件中搜索 `Popup`、`PopupOptions`、`PopupV2`。
- 模块导入：搜索 `@ohos.arkui.advanced.Popup`。

### API 解析实现路径

**尚未组件化**，属性解析仍采用双路径架构，编译产物在主 `libace_compatible.z.so` 中。

Popup 高级组件是 ArkTS 应用层组件，不涉及底层 Pattern/Bridge/Modifier 路径。组件通过 `advanced_ui_component/` 构建系统生成 `.cpp` / `.js` 接口，在静态前端下聚合到 `assembled_advanced_ui_component/`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 动态前端源码 | `advanced_ui_component/popup/source/popup.ets`、`advanced_ui_component/popupv2/source/popupv2.ets` | ArkTS 组件源码 |
| 动态接口桥接 | `advanced_ui_component/popup/interfaces/popup.cpp`、`advanced_ui_component/popupv2/interfaces/popupv2.cpp` | C++ 接口桥接 |
| 动态 JS 接口 | `advanced_ui_component/popup/interfaces/popup.js`、`advanced_ui_component/popupv2/interfaces/popupv2.js` | JS 接口导出 |
| 静态前端聚合 | `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.Popup.ets`、`@ohos.arkui.advanced.PopupV2.ets` | 静态前端聚合组件 |

注：高级组件无独立 SO，作为高级 UI 组件库的一部分打包。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Context registry | `docs/context_registry.json` | Popup 高级组件的 KB、源码、API 统一路由 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| Popup 高级组件功能域 | `specs/07-frontend/01-arkts-advanced-components/16-popup/` | Popup 高级组件规格目录 |
| Feat-01 | `specs/07-frontend/01-arkts-advanced-components/16-popup/Feat-01-popup-advanced-full-spec.md` | Popup 高级组件全量规格 (v1/v2) |
| 架构设计 | `specs/07-frontend/01-arkts-advanced-components/16-popup/design.md` | Popup 高级组件架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Popup v1 vs v2 差异 | `popup.ets` vs `popupv2.ets` 的 API 和行为差异 |
| 高级 Popup 不显示 | 底层依赖 `bindPopup` / `BubblePattern`，查看 bindPopup 链路 |
| 静态前端 Popup 不生效 | `assembled_advanced_ui_component/` 中的聚合源码 |

## 调试入口

- 组件源码：从 `popup.ets` / `popupv2.ets` 跟踪组件实现和属性传递。
- 底层链路：高级 Popup 最终使用 `bindPopup` 属性，查看 `BubblePattern` 和 `OverlayManager` 路径。

## 相关主题

- [bindPopup 组件（底层气泡弹窗属性，高级 Popup 基于此构建）](bind-popup.md)
- Overlay 管理器（弹窗挂载基础设施）