# ResourceDynamicSwitching Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ResourceDynamicSwitching`

## 定位

ArkUI 资源动态切换由 ConfigurationChange 结构体（含 ColorMode/Language/FontSize 等位域）驱动。切换链路：AceContainer::UpdateConfiguration → BuildResConfig → FlushReload → FrameNode::NotifyColorModeChange → Pattern::OnColorModeChange。

本文档用于快速定位 Resource Dynamic Switching 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| configuration_change | `interfaces/inner_api/ace_kit/include/ui/resource/resource_configuration.h` | |
| resource_configuration | `frameworks/base/utils/resource_configuration.h` | |
| ace_container | `adapter/ohos/entrance/ace_container.cpp` | |
| ui_content_impl | `adapter/ohos/entrance/ui_content_impl.cpp` | |
| pipeline_context | `frameworks/core/pipeline_ng/pipeline_context.cpp` | |
| frame_node | `frameworks/core/components_ng/base/frame_node.cpp` | |
| ui_node | `frameworks/core/components_ng/base/ui_node.cpp` | |
| pattern | `frameworks/core/components_ng/pattern/pattern.cpp` | |
| resource_manager | `frameworks/core/common/resource/resource_manager.cpp` | |
| bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_resource_bridge.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 无 | — | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pipeline/pipeline_context_test_ng.cpp | |
| test/unittest/core/base/frame_node_test_ng.cpp | |
| test/unittest/capi/utils/resource_converter_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/03-engine-framework/03-resource-theme/04-resource-dynamic-switching/` | 资源动态切换机制，ConfigurationChange 触发链路（AceContainer → PipelineContext → FrameNode → Pattern::OnColorModeChange）。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 深色模式切换后界面不更新 | 确认 ConfigurationChange 的 colorModeChange_ 位域已设置；跟踪 FlushReload → NotifyColorModeChange 链路 |
| 语言切换不生效 | 查看 languageTag 更新和 ResourceManager 配置重建 |

## 调试入口

- 切换链路：AceContainer::UpdateConfiguration → PipelineContext::FlushReload
- 通知链路：FrameNode::NotifyColorModeChange → Pattern::OnColorModeChange

## 相关主题

- [资源访问](resource-access.md)
- [主题分层访问](theme-layered-access.md)
- [UIAppearance](../capabilities/ui-appearance.md)