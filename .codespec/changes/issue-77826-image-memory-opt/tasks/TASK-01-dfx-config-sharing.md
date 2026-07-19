# TASK-01: ImageDfxConfig 改为 shared_ptr 按需创建和共享

**ADR:** ADR-2
**优先级:** 高
**预估节省:** ~608B/节点

## 目标

将 `ImageDfxConfig` 从值类型内嵌改为 `std::shared_ptr<ImageDfxConfig>`，实现跨对象共享和按需创建。

## 改动范围

### 1. `ImageDfxConfig` 改造（image_dfx.h）
- 无需改类本身定义，保持为值类型
- 使用方改为持有 `std::shared_ptr<ImageDfxConfig>`

### 2. ImageSourceInfo 中的 imageDfxConfig_（image_source_info.h:167）
- `NG::ImageDfxConfig imageDfxConfig_` → `std::shared_ptr<NG::ImageDfxConfig> imageDfxConfig_`
- `SetImageDfxConfig()` (image_source_info.cpp:583) — 改为接收 shared_ptr 或创建 shared_ptr
- `GetImageDfxConfig()` (image_source_info.cpp:588) — 返回 `const std::shared_ptr<NG::ImageDfxConfig>&`
- 所有通过 `src.GetImageDfxConfig()` 获取 DfxConfig 的调用方需适配

### 3. ImageLoadingContext 中的 imageDfxConfig_（image_loading_context.h:237）
- `ImageDfxConfig imageDfxConfig_` → `std::shared_ptr<ImageDfxConfig> imageDfxConfig_`
- 构造函数（image_loading_context.cpp:34-46）— 从 ImageSourceInfo 获取 shared_ptr 共享
- 所有 `imageDfxConfig_` 的使用改为指针访问

### 4. ImagePattern 中的 3 个 ImageDfxConfig（image_pattern.h:409-411）
- `ImageDfxConfig imageDfxConfig_` → `std::shared_ptr<ImageDfxConfig> imageDfxConfig_`
- `ImageDfxConfig altImageDfxConfig_` → 同上
- `ImageDfxConfig altErrorImageDfxConfig_` → 同上
- `CreateImageDfxConfig()` (image_pattern.cpp:1105) — 改为返回 `std::shared_ptr<ImageDfxConfig>`
- 3 个调用点（lines 1141, 1177, 2992）无需改逻辑

### 5. ImageProvider 相关（image_provider.h）
- `ImageDecoderOptions::imageDfxConfig` — 改为 shared_ptr
- `UriDownLoadConfig::imageDfxConfig` — 改为 shared_ptr
- 所有传递 ImageDfxConfig 的代码路径适配

## 验证方法

1. 编译通过：`./build.sh --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild`
2. 单元测试通过：image_pattern_test
3. sizeof 检查：确认 ImagePattern 中 3 个 shared_ptr（24B）替代 3 个值（456B），净减 ~432B
