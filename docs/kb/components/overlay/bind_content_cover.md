# bindContentCover Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `bindContentCover`

## 定位

ArkUI bindContentCover 提供全模态弹窗能力，通过 `bindContentCover()` 属性挂载到组件。OverlayManager 负责创建 SheetContentCoverObject 和 ModalPresentationPattern，后者管理全屏模态的转场动画和生命周期。

本文档用于快速定位 bindContentCover 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| sheet_content_cover_object | `frameworks/core/components_ng/pattern/sheet/content_cover/sheet_content_cover_object.cpp` | |
| sheet_content_cover_layout_algorithm | `frameworks/core/components_ng/pattern/sheet/content_cover/sheet_content_cover_layout_algorithm.cpp` | |
| overlay_manager | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | |
| modal_presentation_pattern | `frameworks/core/components_ng/pattern/overlay/modal_presentation_pattern.cpp` | |
| modal_style | `frameworks/core/components_ng/pattern/overlay/modal_style.h` | |
| content_cover_param | `frameworks/core/components_ng/pattern/overlay/content_cover_param.h` | |
| dismiss_action | `frameworks/core/interfaces/native/implementation/dismiss_content_cover_action_accessor.cpp` | |
| js_view_abstract | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/overlay/sheet_content_cover_test_ng.cpp | |
| test/unittest/core/pattern/overlay/overlay_manager_content_test_ng.cpp | |
| test/unittest/core/pattern/overlay/modal_presentation_pattern_test_ng.cpp | |

### API 解析实现路径

bindContentCover 是通用属性，通过 ViewAbstractModelNG 设置，不涉及独立 Pattern/Bridge 路径。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 声明式前端 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | bindContentCover 注册 |
| Model | `frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | ViewAbstractModelNG |
| Overlay 管理 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | OverlayManager::BindContentCover |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/05-ui-components/07-modal-components/02-full-modal/` | bindContentCover 全模态弹窗，通过 OverlayManager 挂载全屏模态内容，ModalPresentationPattern 管理转场。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 全模态不显示 | 确认 OverlayManager::BindContentCover 链路和 SheetContentCoverObject 创建 |
| 转场动画异常 | 查看 ModalPresentationPattern 的动画状态机 |
| onDisappear 不触发 | 检查 dismiss 链路和 DismissContentCoverActionAccessor |

## 调试入口

- 挂载链路：ViewAbstractModelNG → OverlayManager::BindContentCover
- 内容管理：SheetContentCoverObject → ModalPresentationPattern
- C API 链路：dismiss_content_cover_action_accessor.cpp

## 相关主题

- Sheet 半模态弹窗
- 模态属性
- Dialog 弹窗组件
