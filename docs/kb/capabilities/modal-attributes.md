# ModalAttributes Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ModalAttributes`

## 定位

ArkUI 模态属性包括 bindSheet（半模态弹窗）和 bindContentCover（全模态弹窗）。两者通过 ViewAbstractModelNG 设置，OverlayManager 负责创建和管理模态内容节点，ModalPresentationPattern 处理转场动画。

本文档用于快速定位 Modal Attributes 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| view_abstract_model_ng | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | |
| view_abstract_model_static | `frameworks/core/components_ng/base/view_abstract_model_static.cpp` | |
| overlay_manager | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | |
| modal_presentation_pattern | `frameworks/core/components_ng/pattern/overlay/modal_presentation_pattern.cpp` | |
| modal_style | `frameworks/core/components_ng/pattern/overlay/modal_style.h` | |
| content_cover_param | `frameworks/core/components_ng/pattern/overlay/content_cover_param.h` | |
| js_view_abstract | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/overlay/overlay_manager_test_ng.cpp | |
| test/unittest/core/pattern/overlay/modal_presentation_pattern_test_ng.cpp | |
| test/unittest/core/pattern/overlay/sheet_content_cover_test_ng.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/04-common-capability/03-common-attributes/06-modal-attributes/` | 模态属性（bindSheet/bindContentCover），通过 OverlayManager 挂载模态内容到 Overlay 节点。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| bindSheet 不显示 | 确认 OverlayManager::BindSheet 链路和 ModalPresentationPattern 创建 |
| 模态转场动画异常 | 查看 ModalPresentationPattern 的动画状态机 |

## 调试入口

- 挂载链路：ViewAbstractModelNG → OverlayManager::BindSheet/BindContentCover
- 模态管理：OverlayManager → ModalPresentationPattern

## 相关主题

- [弹窗类属性](modal-attributes.md)
- [半模态弹窗](../components/overlay/sheet.md)
- [全模态弹窗](../components/overlay/bind-content-cover.md)