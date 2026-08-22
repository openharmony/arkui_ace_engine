# SubwindowMechanism Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `SubwindowMechanism`

## 定位

ArkUI 子窗机制通过 SubwindowManager 单例管理七种子窗类型（基于 SubwindowKey: instanceId/displayId/foldStatus/windowType/nodeId）。Subwindow 抽象基类定义接口，SubwindowOhos 适配层持有 Rosen::Window。

本文档用于快速定位 Subwindow Mechanism 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| subwindow | `frameworks/base/subwindow/subwindow.h` | |
| subwindow_manager | `frameworks/base/subwindow/subwindow_manager.h` | |
| subwindow_manager_impl | `frameworks/base/subwindow/subwindow_manager.cpp` | |
| subwindow_ohos | `adapter/ohos/entrance/subwindow/subwindow_ohos.h` | |
| subwindow_ohos_impl | `adapter/ohos/entrance/subwindow/subwindow_ohos.cpp` | |
| ace_container | `adapter/ohos/entrance/ace_container.cpp` | |
| ui_content_impl | `adapter/ohos/entrance/ui_content_impl.cpp` | |
| pipeline_context | `frameworks/core/pipeline_ng/pipeline_context.cpp` | |
| overlay_manager | `frameworks/core/components_ng/pattern/overlay/overlay_manager.h` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| window | `<OH_ROOT>/interface/sdk-js/api/@ohos.window.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/base/subwindow_manager_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/03-engine-framework/05-window-mechanism/02-subwindow-mechanism/` | 子窗机制，SubwindowManager 单例管理七种子窗类型，基于 SubwindowKey 路由。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 弹窗显示在错误窗口 | 确认 SubwindowKey 的 windowType 和 displayId |
| 子窗不显示 | 查看 SubwindowOhos 的 Rosen::Window 创建和挂载链路 |

## 调试入口

- 子窗创建：SubwindowManager → ShowSubwindow → SubwindowOhos
- 窗口管理：SubwindowOhos 持有 sptr<Rosen::Window>

## 相关主题

- [弹窗类组件](../capabilities/overlay-capability.md)
- [半模态弹窗](../components/overlay/sheet.md)
- [布局框架](layout-framework.md)
- UISession：[docs/kb/architecture/uisession-service.md](uisession-service.md)（跨进程 UI 会话通道）