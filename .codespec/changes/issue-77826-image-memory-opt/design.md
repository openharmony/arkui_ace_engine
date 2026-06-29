# design.md — Image 组件基础内存优化

## 概述

本设计文档描述 NG Image 组件基础内存占用优化的架构方案。目标是通过对 `ImageSourceInfo`、`ImageDfxConfig`、`ImageLoadingContext`、`ImagePattern`、`ImageLayoutProperty` 等核心对象的内存优化，在真实设备上每个 Image 节点削减 5-10KB。

---

## 当前架构与问题

### 对象关系图

```
ImageLayoutProperty (~2,000B+)
├── propImageSourceInfo_:  optional<ImageSourceInfo>   (~456B)
├── propAlt_:              optional<ImageSourceInfo>   (~456B)  ← 多数场景空
├── propAltError_:         optional<ImageSourceInfo>   (~456B)  ← 多数场景空
├── propAltPlaceholder_:   optional<ImageSourceInfo>   (~456B)  ← 几乎不用
└── [base LayoutProperty]

ImagePattern (~1,056B)
├── imageDfxConfig_:       ImageDfxConfig              (152B)
├── altImageDfxConfig_:    ImageDfxConfig              (152B)  ← 多数场景空
├── altErrorImageDfxConfig_: ImageDfxConfig            (152B)  ← 多数场景空
├── renderedImageInfo_:    RenderedImageInfo            (140B)
├── loadingCtx_:           RefPtr<ImageLoadingContext>  (8B → ~1,120B 堆)
├── altLoadingCtx_:        RefPtr<ImageLoadingContext>  (8B)
├── altErrorCtx_:          RefPtr<ImageLoadingContext>  (8B)
├── keyEventCallback_:     function                    (32B)
├── onProgressCallback_:   function                    (32B)
└── [14个 RefPtr + 19个 bool]

ImageLoadingContext (~1,120B)
├── src_:                  ImageSourceInfo              (~448B)
├── imageDfxConfig_:       ImageDfxConfig              (152B)
├── notifiers_:            LoadNotifier                (128B = 4个 function)
├── pendingMakeCanvasImageTask_: function               (32B)
├── onProgressCallback_:   function                    (32B)
├── canvasKey_:            string                      (32B)
├── traceTag_:             string                      (32B)
└── [其他成员]
```

### 核心问题

| 问题 | 影响范围 | 预计浪费 |
|------|----------|----------|
| ImageSourceInfo 拷贝冗余 | 5 份/节点 | ~1,800B (LayoutProperty 4份 + LoadingContext 1份) |
| ImageDfxConfig 拷贝冗余 | 5-6 份/节点 | ~600-900B (Pattern 3份 + LoadingContext 1份 + SourceInfo 内嵌) |
| ImageDfxConfig 始终内嵌 | 即使不用也占 152B | ~456B (Pattern 3份) |
| alt/altError 相关对象始终分配 | 多数 Image 无 alt | ~64B 指针 + 304B DfxConfig |
| 函数对象始终占空间 | 多数回调未注册 | ~256B (Pattern 64B + LoadingContext 192B) |
| Bool 分散导致对齐浪费 | 19 个 bool 散布各处 | ~21B padding |

---

## 设计决策

### ADR-1: ImageSourceInfo 改为 RefPtr 共享

**问题：** ImageSourceInfo 在单节点中存在 5 份拷贝（~2,240B），其中 LayoutProperty 的 4 个 optional<ImageSourceInfo> 是最大贡献者。

**推荐方案：** 将 `ImageLayoutProperty` 中的 `propImageSourceInfo_`、`propAlt_`、`propAltError_`、`propAltPlaceholder_` 从 `std::optional<ImageSourceInfo>` 改为 `std::optional<RefPtr<ImageSourceInfo>>`。

同时将 `ImageLoadingContext::src_` 改为持有 `RefPtr<ImageSourceInfo>` 而非内嵌拷贝。在创建 ImageLoadingContext 时，直接传入 Pattern 已持有的 RefPtr，避免拷贝。

**取舍：**
- 优势：单节点 ImageSourceInfo 从 5 份降至 1 份（LayoutProperty src）+ 1 份共享引用（LoadingContext），节省 ~1,344B
- 风险：RefPtr 引入引用计数开销（8B 控制块指针），但对 ImageSourceInfo（448B）来说开销可忽略
- 限制：需确保 ImageSourceInfo 在共享后不被修改。如果属性更新需要修改，应创建新的 ImageSourceInfo 而非就地修改（copy-on-write 语义）

**影响范围：**
- `image_layout_property.h` — 属性类型变更
- `image_loading_context.h` — `src_` 类型变更
- `image_pattern.cpp` — 传递 RefPtr 而非值
- `image_provider.h/cpp` — 接受 RefPtr 参数
- 所有使用 `GetImageSourceInfo()` 的调用方

### ADR-2: ImageDfxConfig 改为按需创建 + RefPtr 共享

**问题：** ImageDfxConfig（~152B）在单节点中存在 5-6 份，且多数时候不活跃使用。

**推荐方案：**
1. `ImagePattern` 中 3 个 `ImageDfxConfig`（main/alt/altError）改为 `std::optional<RefPtr<ImageDfxConfig>>`
2. `ImageSourceInfo::imageDfxConfig_` 从内嵌改为 `RefPtr<ImageDfxConfig>`，多个持有者共享同一个实例
3. `ImageLoadingContext::imageDfxConfig_` 同样改为 `RefPtr<ImageDfxConfig>`
4. 创建时机：首次调用 `CreateImageDfxConfig()` 时才分配

**取舍：**
- 优势：DFX 配置从 5-6 份降至 1 份，且不使用时零开销
- 风险：首次访问时需检查 RefPtr 是否为空
- 限制：需要确保在 DFX 日志写入前已完成初始化

### ADR-3: ImageSourceInfo 内部字段按需分配

**问题：** ImageSourceInfo 为所有场景（文件/资源/PixelMap/Base64/网络）维护统一的成员布局，导致 PixelMap 场景下 ~227B 的字段始终为空。

**推荐方案：** 不做 union/variant 拆分（改动过大），但将以下不常用字段改为按需堆分配：

1. `fillColor_`（~56B）→ `std::unique_ptr<Color>` 或移除（已 deprecated in NG）
2. `reloadKey_`（~33B）→ `std::optional<std::string>` 改为 `std::unique_ptr<std::string>` 按需分配
3. `srcRef_`（8B）→ 保留 shared_ptr（已是最优）
4. `pixmapBuffer_`（8B）→ 移除或合并到 buffer_ 的语义中

**取舍：**
- 优势：减少 ImageSourceInfo 基础大小 ~60-80B
- 风险：fillColor_ 的移除需确认 NG 代码路径不再使用
- 注意：由于 ADR-1 已改为 RefPtr 共享，单个 ImageSourceInfo 节省的字节会被所有引用者共享

### ADR-4: ImagePattern alt 相关字段按需创建

**问题：** altLoadingCtx_、altImage_、altDstRect_、altSrcRect_、altErrorCtx_、altErrorImage_、altErrorDstRect_、altErrorSrcRect_ 共 64B 指针空间始终占用，且关联的 altImageDfxConfig_（152B）也始终内嵌。

**推荐方案：** 将 alt 相关状态合并为一个按需分配的结构体：

```cpp
struct AltImageState {
    RefPtr<ImageLoadingContext> loadingCtx;
    RefPtr<CanvasImage> image;
    std::unique_ptr<RectF> dstRect;
    std::unique_ptr<RectF> srcRect;
    RefPtr<ImageDfxConfig> dfxConfig;
};

struct AltErrorState {
    RefPtr<ImageLoadingContext> loadingCtx;
    RefPtr<CanvasImage> image;
    std::unique_ptr<RectF> dstRect;
    std::unique_ptr<RectF> srcRect;
    RefPtr<ImageDfxConfig> dfxConfig;
};

std::unique_ptr<AltImageState> altState_;
std::unique_ptr<AltErrorState> altErrorState_;
```

**取舍：**
- 优势：alt 未设置时仅占 2 个 unique_ptr（16B），而非当前 8 个指针 + 2 个 DfxConfig（~464B）
- 风险：需改动 alt fallback 链路代码，但逻辑不变，只是访问路径变了

### ADR-5: ImagePattern 回调函数按需分配

**问题：** `keyEventCallback_`（32B）和 `onProgressCallback_`（32B）始终占用空间，但多数 Image 不注册这些回调。

**推荐方案：** 将回调函数从直接持有改为 `std::unique_ptr<function<...>>`，仅在注册时分配。或者利用已有的 `ImageEventHub` 持有回调，Pattern 不重复持有。

**取舍：**
- 优势：节省 ~64B
- 风险：需确认回调注册/触发的生命周期管理
- 替代方案：如果 `onProgressCallback_` 可移到 ImageEventHub，直接删除 Pattern 中的成员

### ADR-6: Bool 字段合并为位域

**问题：** ImagePattern 中 19 个 bool 散布各处，导致 ~21B 的 padding 浪费。

**推荐方案：** 将相关 bool 合并为位域或 uint32_t 位掩码：

```cpp
struct ImageFlags {
    bool enableDrag : 1;
    bool syncLoad : 1;
    bool needBorderRadius : 1;
    bool isImageReloadNeeded : 1;
    bool isEnableAnalyzer : 1;
    bool autoResizeDefault : 1;
    bool isSceneBoardWindow : 1;
    bool isSensitive : 1;
    bool isFullyInitializedFromTheme : 1;
    bool isSelected : 1;
    bool isOrientationChange : 1;
    bool isImageAnimator : 1;
    bool isPixelMapChanged : 1;
    bool isComponentSnapshotNode : 1;
    bool isNeedReset : 1;
    bool hasSetPixelMapMemoryName : 1;
    bool previousVisibility : 1;
    bool supportSvg2 : 1;
    bool isMeasured : 1;
    bool loadFailed : 1;
    bool isLoadAlt : 1;
    bool needLoadAlt : 1;
};  // sizeof = 4 bytes (22 bits packed into uint32_t)
```

**取舍：**
- 优势：从 ~40B（含 padding）降至 4B
- 风险：位域访问有微小的性能开销（bit manipulation），但对 bool 来说编译器优化后可忽略
- 注意：部分 bool 需要确认是否跨线程访问（如果是，不能用位域）

---

## 性能与内存预算

### 优化前估算（单节点，无 alt）

| 对象 | sizeof | 数量 | 总计 |
|------|--------|------|------|
| ImageSourceInfo | ~448B | 5 | 2,240B |
| ImageDfxConfig | ~152B | 5 | 760B |
| ImageLayoutProperty（含 base） | ~2,000B | 1 | 2,000B |
| ImagePattern | ~1,056B | 1 | 1,056B |
| ImageLoadingContext | ~1,120B | 1 | 1,120B |
| RenderedImageInfo | ~140B | 1 | 140B |
| LoadNotifier | ~128B | 1 | 128B |
| **合计** | | | **~7,444B** |

### 优化后估算（单节点，无 alt）

| 对象 | 优化后 sizeof | 变化 | 节省 |
|------|-------------|------|------|
| ImageSourceInfo (共享) | ~448B | 1 份 + 4 个 RefPtr | -1,792B |
| ImageDfxConfig (共享) | ~152B | 1 份 + 4 个 RefPtr | -608B |
| ImagePattern | ~660B | 合并 alt 状态、位域、按需回调 | -396B |
| ImageLayoutProperty | ~640B | RefPtr<ImageSourceInfo> 替代 optional<ImageSourceInfo> | -1,360B |
| ImageLoadingContext | ~800B | RefPtr<ImageSourceInfo> + RefPtr<ImageDfxConfig> | -320B |
| **合计** | **~2,700B** | | **~-4,744B** |

**说明：** 以上为结构体级别的 sizeof 节省。由于 `std::optional<RefPtr<ImageSourceInfo>>` 的 sizeof 仍为 ~24B（RefPtr 16B + bool 1B + padding），LayoutProperty 的 ImageSourceInfo 相关空间从 4×456=1,824B 降至 4×24=96B，节省 1,728B。

实际运行时内存节省还会包括：alt 状态的按需分配节省、DFX 的按需创建节省、以及堆上 ImageSourceInfo 拷贝的消除。

---

## 不涉及项

- 图片解码/加载流程
- ArkTS / C 公共 API
- 渲染/绘制路径
- 动画图 / SVG 路径
- Legacy Image 组件
- `ImageLayoutAlgorithm`、`ImageContentModifier`、`ImageEventHub`

---

## 构建影响

- 不引入新的 BUILD.gn 依赖
- 不影响编译目标
- 可能需要更新 `image_pattern_test` 等相关单元测试的 mock 数据

---

## 验证路径

| 验证项 | 方法 |
|--------|------|
| sizeof 对比 | 编译期 `static_assert(sizeof(ImageSourceInfo) < 原值)` |
| 功能无回归 | 运行 Image 相关单元测试全量 |
| 内存实测 | 500 Image 测试用例在 Previewer 和真实设备上对比 |
| DFX 无损 | 验证优化后 DFX 日志信息完整输出 |
