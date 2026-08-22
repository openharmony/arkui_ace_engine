# Image Analyzer Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `ImageAnalyzer`

## 定位

Image 分析能力为 Image 组件提供 AI 图像分析开关、分析配置、控制器和分析覆盖层生命周期管理。ImagePattern 负责组件侧接入，ImageAnalyzerManager 负责像素数据、覆盖层和平台分析引擎之间的协调。

本文档聚焦 Image 组件的分析能力。Canvas、Video、XComponent 等其他组件也存在分析接入点，但其组件行为应分别从对应 KB、SDK 和源码确认。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Image 组件接入 | `frameworks/core/components_ng/pattern/image/image_pattern.cpp`、`frameworks/core/components_ng/pattern/image/image_pattern.h` | 分析开关、配置、覆盖层创建更新和释放入口 |
| Image Model | `frameworks/core/components_ng/pattern/image/image_model_ng.cpp`、`frameworks/core/components_ng/pattern/image/image_model_ng.h` | Image 属性写入 Pattern 的入口 |
| Dynamic Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.cpp` | `enableAnalyzer` 与 `analyzerConfig` 参数解析入口 |
| Dynamic JSView | `frameworks/bridge/declarative_frontend/jsview/js_image.cpp` | Image 动态前端兼容入口 |
| node_modifier | `frameworks/core/interfaces/native/node/node_image_modifier.cpp` | Bridge 与 Native Image modifier 的委托入口 |
| Static ArkTS modifier | `frameworks/core/interfaces/native/implementation/image_modifier.cpp` | Static ArkTS Image 分析属性转换入口 |
| 分析管理器抽象 | `frameworks/core/common/ai/image_analyzer_manager.h`、`frameworks/core/common/ai/image_analyzer_mgr.h` | Core 侧分析管理与引擎抽象入口 |
| OHOS 平台实现 | `adapter/ohos/osal/image_analyzer_manager.cpp`、`adapter/ohos/osal/image_analyzer_mgr.cpp` | 分析覆盖层、平台引擎调用和生命周期实现 |
| 平台引擎加载 | `adapter/ohos/osal/image_analyzer_loader.cpp` | 平台分析引擎动态加载入口 |
| 分析接口 | `interfaces/inner_api/ace/ai/image_analyzer_interface.h`、`interfaces/inner_api/ace/ai/image_analyzer.h` | ACE 与分析引擎之间的接口定义 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Image API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/image.d.ts` | `enableAnalyzer`、`analyzerConfig` 声明 |
| Dynamic 分析类型 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/image_common.d.ts` | ImageAnalyzerController、ImageAnalyzerConfig 等类型声明 |
| Static Image API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/image.static.d.ets` | Static ArkTS Image 分析属性声明 |
| Static 分析类型 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/imageCommon.static.d.ets` | Static ArkTS 分析配置和控制器声明 |
| Native Image 属性 | `interfaces/native/native_node.h` | Image 分析开关属性入口 |
| Static 内部 accessor | `frameworks/core/interfaces/native/implementation/image_analyzer_controller_accessor.cpp` | Static ArkTS 运行时控制器接入；不是公开 NDK API |

API 检索建议：在 SDK 与源码中搜索 `enableAnalyzer`、`analyzerConfig`、`ImageAnalyzerConfig`、`ImageAnalyzerController`、`ImageAnalyzerState`。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部接口 | 说明 |
|----------|----------|----------|------|
| 平台 AI 分析引擎 | `adapter/ohos/osal/image_analyzer_loader.cpp`、`adapter/ohos/osal/image_analyzer_mgr.cpp` | `interfaces/inner_api/ace/ai/image_analyzer_interface.h` | 通过平台动态实现创建分析引擎，缺失时走 ACE 默认实现 |
| PixelMap 数据 | `adapter/ohos/osal/image_analyzer_adapter_impl.cpp`、`adapter/ohos/osal/image_analyzer_manager.cpp` | `foundation/multimedia/image_framework` | 将 Image 像素数据转换后交给分析引擎 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Image Pattern 测试 | `test/unittest/core/pattern/image/` | Image 分析开关、配置和覆盖层生命周期回归 |
| Static accessor 测试 | `test/unittest/capi/accessors/image_analyzer_controller_accessor_test.cpp` | Static ArkTS 内部控制器 accessor 回归 |
| Static Image modifier 测试 | `test/unittest/capi/modifiers/generated/image_modifier_test.cpp` | Static Image 分析属性转换回归 |
| 组件测试样例 | `test/component_test/test_cases/components/image_video_and_media/entry/src/main/ets/pages/image/` | Image 分析能力的组件级执行入口 |

### 相关 Spec

| Spec | 路径 |
|------|------|
| 设计文档 | `specs/04-common-capability/23-ai-capability/01-image-analysis/design.md` |
| 分析能力支持 | `specs/04-common-capability/23-ai-capability/01-image-analysis/Feat-01-image-analyzer-support-spec.md` |
| 覆盖层生命周期 | `specs/04-common-capability/23-ai-capability/01-image-analysis/Feat-02-image-analyzer-overlay-lifecycle-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| enableAnalyzer 设置后未生效 | SDK 声明、Image Bridge、ImageModelNG、ImagePattern |
| analyzerConfig 未更新 | Dynamic/Static modifier、ImagePattern、ImageAnalyzerManager |
| 分析覆盖层未创建或未刷新 | ImagePattern 支持条件、ImageAnalyzerManager、平台引擎支持查询 |
| 覆盖层未释放 | ImagePattern 释放入口、ImageAnalyzerManager 生命周期、覆盖层生命周期规格 |
| Static ArkTS 控制器行为异常 | `image_analyzer_controller_accessor.cpp` 和对应 accessor 测试 |
| 仅特定设备或系统镜像不支持 | `image_analyzer_loader.cpp`、`ImageAnalyzerMgr` 和平台实现可用性 |

## 调试入口

- 从 SDK 属性进入 Image Bridge 或 Static Image modifier，确认配置是否到达 ImageModelNG。
- 在 ImagePattern 检查分析开关、图片加载状态和覆盖层生命周期入口。
- 平台能力问题从 ImageAnalyzerManager 跟到 ImageAnalyzerMgr 和 ImageAnalyzerLoader。
- Static ArkTS 控制器问题单独检查内部 accessor；不要把该入口当作公开 NDK API。
- 回归验证优先运行 Image Pattern 分析相关用例和 image analyzer controller accessor 测试。

## 相关主题

- `Image`：[docs/kb/components/media/image.md](../components/media/image.md)
- `ImageLoading`：[docs/kb/capabilities/image-loading.md](image-loading.md)
- `Video`：[docs/kb/components/media/video.md](../components/media/video.md)
