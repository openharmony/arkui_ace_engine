# UIAppearance Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `UIAppearance`

## 定位

ArkUI UIAppearance 管理深色/浅色模式切换。ColorMode 枚举定义在 AceType。系统配置通过 AceAbility → UiContentImpl → AceContainer → PipelineContext 传播，最终通知 FrameNode 和 Pattern。C API 支持强制深色模式（OH_ArkUI_SetForceDarkConfig）。

本文档用于快速定位 UIAppearance 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ace_ability | `adapter/ohos/entrance/ace_ability.cpp` | |
| ui_content_impl | `adapter/ohos/entrance/ui_content_impl.cpp` | |
| ace_container | `adapter/ohos/entrance/ace_container.cpp` | |
| resource_adapter_impl_v2 | `adapter/ohos/osal/resource_adapter_impl_v2.cpp` | |
| resource_convertor | `adapter/ohos/osal/resource_convertor.cpp` | |
| pipeline_context | `frameworks/core/pipeline_ng/pipeline_context.cpp` | |
| frame_node | `frameworks/core/components_ng/base/frame_node.cpp` | |
| native_node | `interfaces/native/native_node.h` | |
| device_config | `frameworks/base/utils/device_config.h` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| ui_appearance | `<OH_ROOT>/interface/sdk-js/api/@ohos.uiAppearance.d.ts` | |
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/withtheme/withtheme_test_ng.cpp | |
| test/unittest/core/pattern/rich_editor/rich_editor_color_mode_test_ng.cpp | |
| test/unittest/interfaces/native_node_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/04-common-capability/16-ui-appearance/01-ui-appearance/` | UIAppearance 色彩模式管理（深色/浅色模式），ColorMode 枚举和系统配置通知链路。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 深色模式不生效 | 确认 PipelineContext::NotifyColorModeChange 被调用 |
| 强制深色不生效 | 检查 OH_ArkUI_SetForceDarkConfig 设置和 FrameNode 的 forceDark_ 标志 |

## 调试入口

- 系统链路：AceAbility → UiContentImpl → AceContainer → PipelineContext
- 通知链路：PipelineContext::NotifyColorModeChange → FrameNode → Pattern::OnColorModeChange

## 相关主题

- 资源动态切换
- 主题分层访问
- WithTheme 组件
