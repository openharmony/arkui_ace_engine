# TASK-04: Alt/AltError 状态合并为 unique_ptr 结构体

**ADR:** ADR-4 + ADR-5（部分）
**优先级:** 中
**预估节省:** ~448B/节点（含 alt DfxConfig 和回调）

## 前置依赖

- TASK-01（ImageDfxConfig 已改为 shared_ptr）
- TASK-02（ImageSourceInfo 已改为 shared_ptr）

## 目标

将 ImagePattern 中 10 个 alt/altError 相关成员合并为 2 个 `unique_ptr` 结构体，仅在有 alt 配置时才分配。

## 改动范围

### 1. 定义 AltImageState 和 AltErrorState 结构体（image_pattern.h）

```cpp
struct AltImageState {
    RefPtr<ImageLoadingContext> loadingCtx;
    RefPtr<CanvasImage> image;
    std::unique_ptr<RectF> dstRect;
    std::unique_ptr<RectF> srcRect;
    std::shared_ptr<ImageDfxConfig> dfxConfig;
};

struct AltErrorState {
    RefPtr<ImageLoadingContext> loadingCtx;
    RefPtr<CanvasImage> image;
    std::unique_ptr<RectF> dstRect;
    std::unique_ptr<RectF> srcRect;
    std::shared_ptr<ImageDfxConfig> dfxConfig;
};
```

### 2. ImagePattern 成员替换（image_pattern.h:393-401, 410-411）

替换前（10 个成员，~320B 指针 + ~304B DfxConfig = ~624B）：
```
altLoadingCtx_, altImage_, altDstRect_, altSrcRect_,
altErrorCtx_, altErrorImage_, altErrorDstRect_, altErrorSrcRect_,
altImageDfxConfig_, altErrorImageDfxConfig_
```

替换后（2 个成员，~16B）：
```
std::unique_ptr<AltImageState> altState_;
std::unique_ptr<AltErrorState> altErrorState_;
```

### 3. image_pattern.cpp 中 ~70 处引用适配

所有对 alt 成员的直接访问改为通过结构体访问：
- `altLoadingCtx_` → `altState_->loadingCtx`
- `altImage_` → `altState_->image`
- `altDstRect_` → `altState_->dstRect`
- `altSrcRect_` → `altState_->srcRect`
- `altImageDfxConfig_` → `altState_->dfxConfig`
- 同理 altError 系列

关键修改点：
- `ClearAltData()` (lines 411-419) — 改为 `altState_.reset()` / `altErrorState_.reset()`
- `LoadAltImage()` (line 1172-1181) — 创建 altState_ 后赋值
- `LoadAltErrorImage()` (line 2988-2998) — 创建 altErrorState_ 后赋值
- `OnAltImageDataReady()` (line 1519-1578) — 通过 altState_-> 访问
- `OnAltErrorImageDataReady()` (line 3007-3061) — 通过 altErrorState_-> 访问
- `StartDecoding()` (line 870-883) — nullptr 检查改为 altState_ != nullptr
- 所有条件判断：`if (altLoadingCtx_)` → `if (altState_)`

### 4. 新增 alt 检查
- 所有原先检查 alt 成员的地方，需要先检查 `altState_ != nullptr`
- 新增 `HasAlt() const { return altState_ != nullptr; }` 便捷方法

## 验证方法

1. 编译通过
2. 单元测试通过（重点：alt fallback 链路测试）
3. 手动验证：设置 alt 图片，加载失败后触发 alt 显示
