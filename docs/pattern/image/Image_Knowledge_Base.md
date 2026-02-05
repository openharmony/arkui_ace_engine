# ArkUI Image 组件完整知识库

> **版本**: 1.0
> **更新时间**: 2026-02-02
> **基于**: OpenHarmony ace_engine (master 分支)

---

## 目录

1. [架构概述](#1-架构概述)
2. [核心类详解](#2-核心类详解)
3. [完整加载流程](#3-完整加载流程)
4. [关键技术点](#4-关键技术点)
5. [属性系统](#5-属性系统)
6. [事件系统](#6-事件系统)
7. [性能优化](#7-性能优化)
8. [错误处理](#8-错误处理)
9. [高级特性](#9-高级特性)
10. [最佳实践](#10-最佳实践)
11. [问题排查](#11-问题排查)

---

## 1. 架构概述

### 1.1 系统架构

Image 组件实现了一个完整的图像加载、解码和渲染流水线，采用 6 层架构：

```
ArkTS 前端
    ↓
桥接层 (ImageModifier) - 属性解析和应用
    ↓
属性系统 (Layout + Render) - 布局和渲染属性
    ↓
模式层 (ImagePattern) - 业务逻辑和生命周期管理
    ↓
提供者层 (ImageLoadingContext) - 状态机和加载协调
    ↓
核心层 (ImageLoader + ImageObject + ImageDecoder) - 数据处理
    ↓
渲染层 (CanvasImage) - GPU 渲染
```

**设计原则**：
- **异步流水线**: I/O 和 CPU 密集型操作在后台线程执行
- **布局感知**: 解码延迟到最终布局尺寸确定后
- **内存高效**: 自动调整大小、激进缓存、基于可见性的回收
- **降级策略**: 三级降级确保健壮性

### 1.2 线程模型

**主线程职责**：
- UI 操作和事件处理
- 布局计算
- CanvasImage 绘制
- 回调执行

**后台线程职责**：
- 网络下载
- 文件 I/O 操作
- 图像解码
- GPU 纹理上传

**线程切换**：
- 主线程 → 后台: `ImageUtils::PostToBg(task, name, containerId)`
- 后台 → 主线程: `ImageUtils::PostToUI(callback, name, containerId)`
- 关键: `containerId` 确保线程亲和性

---

## 2. 核心类详解

### 2.1 ImagePattern

**职责**：
- 协调图像加载生命周期
- 管理主图像和备用图像
- 处理动画播放
- 实现内存管理

**关键成员变量**：
```cpp
RefPtr<ImageLoadingContext> loadingCtx_;    // 主图像加载上下文
RefPtr<ImageLoadingContext> altLoadingCtx_; // 备用图加载上下文
RefPtr<CanvasImage> image_;                 // 最终渲染的图像
RectF dstRect_, srcRect_;                  // 渲染矩形
```

**生命周期流程**：
```
OnModifyDone() → LoadImageData()
    → OnImageDataReady() [异步回调]
    → OnDirtyLayoutWrapperSwap()
    → OnImageLoadSuccess()
    → Paint()
```

**关键方法说明**：

- **OnModifyDone()**: 入口点，触发图像加载
  ```cpp
  void ImagePattern::OnModifyDone() {
      Pattern::OnModifyDone();
      LoadImageDataIfNeed();              // 触发加载
      UpdateGestureAndDragWhenModify();   // 更新手势
      CheckImagePrivacyForCopyOption();   // 隐私检查
  }
  ```

- **OnImageDataReady()**: 图像尺寸已知，决定是否需要重新布局
  ```cpp
  void ImagePattern::OnImageDataReady(const RefPtr<ImageObject>& imageObj) {
      UpdateOrientation(imageObj);        // EXIF 旋转
      PreprocessYUVDecodeFormat(host);    // YUV 预处理

      if (CheckIfNeedLayout(imageObj)) {
          // 尺寸改变 - 需要重新布局
          MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
          return; // 等待 OnDirtyLayoutWrapperSwap
      }

      // 尺寸未变 - 直接解码
      StartDecoding(GetDstSize());
  }
  ```

- **OnDirtyLayoutWrapperSwap()**: 布局完成，最终尺寸已知
  ```cpp
  void ImagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty) {
      auto algorithm = DynamicCast<ImageLayoutAlgorithm>(dirty->GetLayoutAlgorithm());
      SizeF finalSize = algorithm->GetDstSize();  // 获取最终显示尺寸

      srcRect_ = algorithm->GetSrcRect();
      dstRect_ = algorithm->GetDstRect();

      StartDecoding(finalSize);  // 解码一次，避免重新解码
  }
  ```

- **OnVisibleChange()**: 可见性变化
  ```cpp
  void ImagePattern::OnVisibleChange(bool isVisible) {
      if (isVisible) {
          loadingCtx_->ResumeLoading();           // 恢复加载
          if (image_ && image_->IsAnimated()) {
              image_->ResumeAnimation();           // 恢复动画
          }
      } else {
          if (image_ && image_->IsAnimated()) {
              image_->PauseAnimation();            // 暂停动画
          }
          if (ShouldRecycleWhenInvisible()) {
              RecycleImageData();                     // 回收内存
          }
      }
  }
  ```

### 2.2 ImageLoadingContext

**职责**：
- 状态机管理（通过 ImageStateManager）
- 回调协调
- 线程切换
- 目标尺寸计算

**状态机**：
```
UNLOADED → DATA_LOADING → DATA_READY → MAKE_CANVAS_IMAGE → SUCCESS
                                      ↓
                                   LOAD_FAIL
```

**核心接口**：
```cpp
class ImageLoadingContext : public AceType {
public:
    // 阶段 1: 加载图像数据
    void LoadImageData();

    // 阶段 2: 解码为 CanvasImage
    void MakeCanvasImage(const SizeF& dstSize, bool autoResize, ImageFit imageFit);

    // 优化检查：避免重复解码
    bool MakeCanvasImageIfNeed(const SizeF& dstSize, bool autoResize, ImageFit imageFit);

    // 回调接口
    void DataReadyCallback(const RefPtr<ImageObject>& imageObj);
    void SuccessCallback(const RefPtr<CanvasImage>& canvasImage);
    void FailCallback(const std::string& errorMsg, const ImageErrorInfo& errorInfo);
};
```

**MakeCanvasImageIfNeed 优化原理**：

```cpp
bool ImageLoadingContext::MakeCanvasImageIfNeed(
    const SizeF& dstSize, bool autoResize, ImageFit imageFit)
{
    // 计算尺寸级别（log2 刻度）
    int32_t newSizeLevel = CalculateSizeLevel(dstSize.Width());

    // 检查尺寸级别是否变化
    if (newSizeLevel == sizeLevel_) {
        return false;  // 尺寸未变，无需重新解码
    }

    sizeLevel_ = newSizeLevel;
    MakeCanvasImage(dstSize, autoResize, imageFit);
    return true;
}

// 向上取整到最近的 2 的幂次
int32_t ImageLoadingContext::CalculateSizeLevel(float width)
{
    int32_t level = 0;
    while (std::pow(2, level) < width) {
        level++;
    }
    return level;
}
```

**优势**：滚动场景下，相同尺寸避免重复解码

### 2.3 ImageProvider

**职责**：
- 图像操作的静态工厂
- 根据源类型选择加载器
- 缓存管理
- 任务去重

**核心方法**：

```cpp
class ImageProvider {
public:
    // 创建 ImageObject（阶段 1）
    static void CreateImageObject(
        const ImageSourceInfo& src,
        const WeakPtr<ImageLoadingContext>& ctxWp,
        bool sync,
        bool isSceneBoardWindow);

    // 创建 CanvasImage（阶段 2）
    static void MakeCanvasImage(
        const RefPtr<ImageObject>& imageObj,
        const WeakPtr<ImageLoadingContext>& ctxWp,
        const SizeF& targetSize,
        const ImageDecoderOptions& options);
};
```

**加载器选择**：

```cpp
RefPtr<ImageLoader> SelectLoader(SrcType srcType) {
    switch (srcType) {
        case SrcType::NETWORK:
            return NetworkImageLoader::GetInstance();      // http/https
        case SrcType::FILE:
            return FileImageLoader::GetInstance();         // file://
        case SrcType::ASSET:
            return AssetImageLoader::GetInstance();        // 应用资源
        case SrcType::BASE64:
            return Base64ImageLoader::GetInstance();       // data:image/
        case SrcType::PIXMAP:
            return PixelMapImageLoader::GetInstance();      // 像素图
        default:
            return nullptr;
    }
}
```

---

## 3. 完整加载流程

### 阶段 1: 属性配置

**ArkTS 代码**：
```typescript
Image('https://example.com/photo.jpg')
  .width(300)
  .height(200)
  .fit(ImageFit.Cover)
```

**内部流程**：
```
ImageModifier::ApplySrc()
    → ImageLayoutProperty::UpdateImageSourceInfo()
    → 设置 ImageSourceInfo（包含 URI 和类型）
```

### 阶段 2: 触发加载

```cpp
void ImagePattern::LoadImageDataIfNeed()
{
    auto src = layoutProp->GetImageSourceInfo();

    // 创建加载上下文，注册三个回调
    loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        src,
        LoadNotifier {
            .onDataReady_ = CreateDataReadyCallback(),
            .onLoadSuccess_ = CreateLoadSuccessCallback(),
            .onLoadFail_ = CreateLoadFailCallback()
        },
        syncLoad_,
        isSceneBoardWindow_,
        imageDfxConfig_
    );

    loadingCtx_->LoadImageData();  // 开始加载
}
```

### 阶段 3: 数据加载（后台线程）

**加载器选择**：

| 源类型 | 加载器 | URI 示例 |
|--------|--------|---------|
| Network | NetworkImageLoader | `https://example.com/image.jpg` |
| File | FileImageLoader | `file:///data/local/image.png` |
| Asset | AssetImageLoader | `app.media.icon` |
| Base64 | Base64ImageLoader | `data:image/png;base64,iVBOR...` |
| PixelMap | PixelMapImageLoader | 内存中的像素图 |

**输出**: ImageObject（Static/Animated/Svg）

### 阶段 4: 数据就绪（主线程）

**关键决策点**：

```cpp
void ImagePattern::OnImageDataReady(const RefPtr<ImageObject>& imageObj)
{
    // 1. 更新方向（EXIF 旋转）
    UpdateOrientation(imageObj);

    // 2. YUV 格式预处理（性能优化）
    PreprocessYUVDecodeFormat(host);

    // 3. 关键决策：是否需要重新布局？
    if (CheckIfNeedLayout(imageObj)) {
        // 尺寸改变 → 触发布局
        MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        return;  // 等待 OnDirtyLayoutWrapperSwap
    }

    // 4. 尺寸未变 → 直接解码
    StartDecoding(dstSize);
}
```

**布局同步原理**：
- 问题：图像尺寸在加载前未知
- 方案：两阶段方法
- 好处：避免重复解码

### 阶段 5: 解码（后台线程）

**解码配置**：

```cpp
ImageDecoderOptions options;
options.preMultiply = true;                    // Alpha 预乘
options.desiredPixelFormat = PixelFormat::RGBA_8888;
options.desiredSize = dstSize;                  // 自动调整大小的目标尺寸
```

**解码流程**：
```
计算最优尺寸（自动调整）
    → ImageObject::MakeCanvasImage()
    → ImageDecoder::Decode() → PixelMap
    → CanvasImage::Build() → GPU 纹理上传
```

### 阶段 6: 加载成功（主线程）

```cpp
void ImagePattern::OnImageLoadSuccess(const RefPtr<CanvasImage>& canvasImage)
{
    // 1. 转移 CanvasImage 所有权
    image_ = loadingCtx_->MoveCanvasImage();

    // 2. 获取渲染矩形
    srcRect_ = loadingCtx_->GetSrcRect();  // 源裁剪区域
    dstRect_ = loadingCtx_->GetDstRect();  // 目标位置

    // 3. 应用绘制配置
    SetImagePaintConfig(image_, srcRect_, dstRect_, ...);

    // 4. 准备动画（如果是动画图）
    if (image_->IsAnimated()) {
        PrepareAnimation(image_);
    }

    // 5. 清除备用数据
    ClearAltData();

    // 6. 触发完成事件
    FireCompleteEvent();

    // 7. 标记需要重绘
    MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}
```

**绘制配置设置**：

```cpp
void ImagePattern::SetImagePaintConfig(
    const RefPtr<CanvasImage>& canvasImage,
    const RectF& srcRect,
    const RectF& dstRect,
    const ImageSourceInfo& sourceInfo)
{
    auto paintConfig = AceType::MakeRefPtr<ImagePaintConfig>();

    paintConfig->SetSrcRect(srcRect);
    paintConfig->SetDstRect(dstRect);

    auto layoutProp = GetLayoutProperty<ImageLayoutProperty>();
    paintConfig->SetImageFit(layoutProp->GetImageFitValue());

    auto renderProp = GetRenderProperty<ImageRenderProperty>();
    paintConfig->SetImageInterpolation(renderProp->GetInterpolationValue());
    paintConfig->SetAntiAlias(renderProp->GetAntiAliasValue());

    canvasImage->SetPaintConfig(paintConfig);
}
```

### 阶段 7: 渲染

```cpp
Paint()
    → ImageContentModifier::Draw(image_, srcRect_, dstRect_)
    → canvasImage_->DrawToRSCanvas()
    → GPU 渲染
```

---

## 4. 关键技术点

### 4.1 自动调整大小优化

**目的**：按显示尺寸解码，而非全分辨率

**算法**：
```cpp
// 向上取整到最近的 2 的幂次
int32_t sizeLevel = std::ceil(std::log2(displayWidth));
float targetWidth = std::pow(2, sizeLevel);
float targetHeight = targetWidth * aspectRatio;

ImageDecoderOptions.desiredSize = SizeF(targetWidth, targetHeight);
```

**性能收益**：
- 2x 缩放：4倍内存减少
- 典型场景：74% 内存减少

**示例**：
```
原图: 4000x3000 (12MP)
显示: 300x200

无优化:
  解码尺寸: 4000x3000 = 12,000,000 像素
  内存 (RGBA8888): 48 MB

有优化:
  sizeLevel = ceil(log2(300)) = 9
  targetWidth = 2^9 = 512
  targetHeight = 512 * (200/300) = 341
  解码尺寸: 512x341 = 174,592 像素
  内存 (RGBA8888): 698 KB

节省: 98.5%
```

### 4.2 布局同步

**问题**：图像尺寸在加载前未知

**方案**：两阶段方法

**时序**：
```
T0: OnModifyDone()
    - 创建 ImageLoadingContext
    - 开始异步加载
    - 使用占位尺寸进行初始布局

T1: 布局（占位尺寸）
    - 测量和布局

T2: OnImageDataReady() [异步回调]
    - 图像尺寸已知
    - 检查尺寸是否改变
    - 如果改变 → 触发布局
    - 返回等待

T3: 重新布局（实际尺寸）
    - 使用实际图像尺寸布局

T4: OnDirtyLayoutWrapperSwap()
    - 最终显示尺寸确认
    - 开始解码（一次性正确尺寸）
```

**关键点**：
- 解码延迟到布局完成后
- 避免重复解码
- 确保 dstSize 是最终尺寸

### 4.3 ImageFit 计算

**Cover 模式**（可能裁剪）：

```cpp
SizeF CalculateCoverSize(const SizeF& imageSize, const SizeF& containerSize)
{
    float widthRatio = containerSize.Width() / imageSize.Width();
    float heightRatio = containerSize.Height() / imageSize.Height();

    // 使用较大比例确保完全覆盖
    float ratio = std::max(widthRatio, heightRatio);

    return SizeF(imageSize.Width() * ratio, imageSize.Height() * ratio);
}

// 源矩形计算（中心裁剪）
SizeF fittedSize = CalculateCoverSize(imageSize, containerSize);
dstRect = RectF(0, 0, containerSize.Width(), containerSize.Height());
srcRect = RectF(
    (fittedSize.Width() - containerSize.Width()) / 2.0f * scaleX,
    (fittedSize.Height() - containerSize.Height()) / 2.0f * scaleY,
    containerSize.Width() * scaleX,
    containerSize.Height() * scaleY
);
```

**Contain 模式**（完整显示）：

```cpp
SizeF CalculateContainSize(const SizeF& imageSize, const SizeF& containerSize)
{
    float widthRatio = containerSize.Width() / imageSize.Width();
    float heightRatio = containerSize.Height() / imageSize.Height();

    // 使用较小比例确保完整显示
    float ratio = std::min(widthRatio, heightRatio);

    return SizeF(imageSize.Width() * ratio, imageSize.Height() * ratio);
}
```

**对比**：

| 模式 | 算法 | 可能裁剪 | 留白 |
|------|------|---------|------|
| Cover | max(ratioX, ratioY) | 是 | 否 |
| Contain | min(ratioX, ratioY) | 否 | 是 |
| Fill | 拉伸 | 是 | 否 |
| None | 原始尺寸 | 是 | 是 |
| ScaleDown | Contain 但不放大 | 否 | 可能 |

### 4.4 三级降级策略

**降级流程**：

```cpp
void ImagePattern::LoadImageData()
{
    // 1. 尝试主图
    loadingCtx_ = CreateLoadingContext(mainSrc);
    loadingCtx_->LoadImageData();
}

void ImagePattern::OnImageLoadFail(...)
{
    // 2. 主图失败 - 尝试备用图
    auto altSrc = layoutProp->GetAlt();
    if (altSrc.IsValid()) {
        altLoadingCtx_ = CreateLoadingContext(altSrc);
        altLoadingCtx_->LoadImageData();
        return;
    }

    // 3. 备用图失败 - 尝试错误图
    auto altErrorSrc = layoutProp->GetAltError();
    if (altErrorSrc.IsValid()) {
        altErrorCtx_ = CreateLoadingContext(altErrorSrc);
        altErrorCtx_->LoadImageData();
        return;
    }

    // 4. 所有失败 - 显示占位符或空白
    ShowPlaceholder();
    FireErrorEvent(errorMsg, errorInfo);
}
```

**ArkTS 使用**：
```typescript
Image('https://example.com/photo.jpg')  // 主图
  .alt('local_photo.jpg')              // 备用图
  .altError('error_icon.png')          // 错误图
  .altPlaceholder('loading.png')       // 占位符
```

**成员变量**：
```cpp
RefPtr<ImageLoadingContext> altLoadingCtx_;    // 备用图加载
RefPtr<CanvasImage> altImage_;               // 备用图

RefPtr<ImageLoadingContext> altErrorCtx_;     // 错误图加载
RefPtr<CanvasImage> altErrorImage_;         // 错误图
```

### 4.5 动画管理

**支持格式**: GIF, WebP, animated SVG

**生命周期**：

```cpp
void ImagePattern::PrepareAnimation(const RefPtr<CanvasImage>& canvasImage)
{
    // 1. 设置重绘回调（每帧触发）
    canvasImage->SetRedrawCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->MarkDirtyNode(PROPERTY_UPDATE_RENDER);  // 触发重绘
        }
    });

    // 2. 设置完成回调
    canvasImage->SetOnFinishCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->FireFinishEvent();  // 通知应用
        }
    });

    // 3. 注册可见区域变化
    RegisterVisibleAreaChange();

    // 4. 开始播放
    canvasImage->StartAnimation();
}
```

**可见性优化**：

```cpp
void ImagePattern::OnVisibleChange(bool isVisible)
{
    if (!image_ || !image_->IsAnimated()) {
        return;
    }

    if (isVisible) {
        image_->ResumeAnimation();  // 恢复播放
    } else {
        image_->PauseAnimation();   // 暂停播放，节省 CPU/电池
    }
}
```

### 4.6 内存管理

**内存级别回调**：

```cpp
void ImagePattern::OnNotifyMemoryLevel(int32_t level)
{
    switch (level) {
        case MEMORY_LEVEL_CRITICAL:
            // 关键内存压力 - 回收所有图像
            RecycleAllImageData();
            RecycleAltData();
            break;

        case MEMORY_LEVEL_HIGH:
            // 高内存使用 - 回收备用图
            RecycleAltData();
            break;

        case MEMORY_LEVEL_NORMAL:
            // 正常 - 无需操作
            break;
    }
}

void ImagePattern::RecycleAllImageData()
{
    // 清除主图
    if (image_) {
        image_.Reset();
    }

    // 清除备用图
    if (altImage_) {
        altImage_.Reset();
    }
    if (altErrorImage_) {
        altErrorImage_.Reset();
    }

    // 清除加载上下文
    loadingCtx_.Reset();
    altLoadingCtx_.Reset();
    altErrorCtx_.Reset();
}
```

**可见性回收**：

```cpp
void ImagePattern::OnVisibleChange(bool isVisible)
{
    if (!isVisible && ShouldRecycleWhenInvisible()) {
        RecycleImageData();  // 不可见且回收条件满足
    }
}

bool ImagePattern::ShouldRecycleWhenInvisible()
{
    // 回收条件：
    // 1. 非主图（主图可从缓存恢复）
    // 2. 不在缓存中（无法恢复）
    // 3. 内存压力高

    if (!image_) return false;

    if (IsInCache(image_)) return false;  // 可从缓存恢复

    auto memoryLevel = GetMemoryLevel();
    return memoryLevel >= MEMORY_LEVEL_HIGH;
}
```

---

## 5. 属性系统

### 5.1 布局属性 (ImageLayoutProperty)

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| **ImageSourceInfo** | ImageSourceInfo | - | 图像源（URI + 类型） |
| **ImageFit** | ImageFit | Cover | 适配模式 |
| **AutoResize** | bool | true (大屏) / false (移动) | 自动调整解码大小 |
| **SourceSize** | SizeF | - | 显式指定源尺寸 |
| **Alt** | ImageSourceInfo | - | 备用图像 |
| **AltError** | ImageSourceInfo | - | 错误图像 |
| **AltPlaceholder** | ImageSourceInfo | - | 占位符图像 |
| **IsYUVDecode** | bool | false | YUV 格式优化 |

### 5.2 渲染属性 (ImageRenderProperty)

| 属性 | 类型 | 说明 |
|------|------|------|
| **ColorFilter** | PixelMap | 颜色滤镜 |
| **Repeat** | ImageRepeat | 重复模式 (NoRepeat, X, Y, XY) |
| **FillColor** | Color | SVG 填充颜色 |
| **DynamicRangeMode** | DynamicRangeMode | 动态范围模式 (Standard, HDR, SDR) |
| **MatchTextDirection** | bool | 匹配文本方向（RTL/LTR） |
| **Interpolation** | ImageInterpolation | 插值质量 (High, Low, Medium, None) |
| **HdrBrightness** | float | HDR 亮度增强 (0.0 - 2.0) |
| **AntiAlias** | bool | 抗锯齿 |

---

## 6. 事件系统

### 6.1 事件类型

**onComplete** - 加载成功：
```cpp
struct LoadImageSuccessEvent {
    float componentWidth;    // 组件宽度
    float componentHeight;   // 组件高度
    int32_t loadingStatus;   // 加载状态 (1=成功)
    float contentWidth;      // 内容宽度
    float contentHeight;     // 内容高度
};
```

**onError** - 加载失败：
```cpp
struct LoadImageFailEvent {
    float componentWidth;
    float componentHeight;
    int32_t errorCode;       // 错误码
    std::string errorMsg;    // 错误消息
};
```

**onFinish** - 动画播放完成（SVG）

**onProgress** - 下载进度（仅网络图像）：
```cpp
using OnProgressCallback = std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>;

// 设置进度回调
loadingCtx_->SetOnProgressCallback([](uint32_t dlNow, uint32_t dlTotal) {
    double progress = static_cast<double>(dlNow) / dlTotal;
    UpdateProgressBar(progress);
});
```

### 6.2 事件注册流程

```cpp
// ArkTS 前端
Image(src)
  .onComplete((event: LoadImageSuccessEvent) => {
    console.log('Loaded:', event.componentWidth, event.componentHeight);
  })
  .onError((event: LoadImageFailEvent) => {
    console.error('Failed:', event.errorMsg);
  })
    ↓
// 桥接层
eventHub->SetOnComplete(callback);
eventHub->SetOnError(callback);
    ↓
// 模式层
void ImagePattern::FireCompleteEvent() {
    auto callback = eventHub->GetOnCompleteCallback();
    if (callback) {
        LoadImageSuccessEvent info;
        // 填充信息
        callback(info);
    }
}
```

---

## 7. 性能优化

### 7.1 四级缓存策略

**Level 1 - 下载缓存** (DownloadManager)：
- 键: URL
- 内容: 已下载文件
- 收益: 跳过网络 I/O

**Level 2 - ImageObject 缓存** (ImageCache)：
- 键: ImageSourceInfo.GetKey()
- 内容: ImageObject（解码前）
- 容量: 2000 对象（LRU 淘汰）
- 收益: 跳过 I/O 和解析

**Level 3 - PixelMap 缓存** (weakPixelMapCache_)：
- 键: ImageObject + Size
- 内容: PixelMap（解码后）
- 特性: 弱引用，允许 GC 回收
- 收益: 跳过解码

**Level 4 - CanvasImage 缓存** (CanvasImage::Cache)：
- 键: ImageObject + Size + Options
- 内容: CanvasImage（GPU 纹理）
- 收益: 零 CPU/GPU 工作

**缓存收益对比**：
```
Level 1 命中: 跳过网络下载（~1000ms）
Level 2 命中: 跳过解析（~50ms）
Level 3 命中: 跳过解码（~200ms）
Level 4 命中: 跳过 GPU 上传（~50ms）

全部命中: ~0ms（直接从缓存返回）
```

### 7.2 线程模型

**任务分配**：

```cpp
// 主线程执行
void ImagePattern::OnModifyDone() {
    // UI 线程
    LoadImageDataIfNeed();  // 后台执行加载
}

// 后台线程执行
void ImageLoader::Load() {
    // 后台线程
    auto data = Download(url);  // 网络 I/O
}
```

**线程切换**：

```cpp
// 主线程 → 后台线程
ImageUtils::PostToBg([ctx]() {
    // 此代码在后台线程执行
    ctx->LoadTask();
}, "LoadImage", containerId);

// 后台线程 → 主线程
ImageUtils::PostToUI([ctx]() {
    // 此代码在主线程执行
    ctx->Callback();
}, "ImageCallback", containerId);
```

### 7.3 DFX 性能追踪

**追踪指标**：

```cpp
struct ImageDfxConfig {
    int64_t loadStartTimestamp;      // OnModifyDone 时间戳
    int64_t dataReadyTimestamp;      // 数据就绪时间戳
    int64_t loadSuccessTimestamp;    // 加载成功时间戳
    int64_t imageWidth;              // 图像宽度
    int64_t imageHeight;             // 图像高度
    std::string srcType;             // 源类型
    std::string componentId;         // 组件 ID
};
```

**自动报告**：

```cpp
// 状态转换时自动记录
void ImageLoadingContext::OnDataReady() {
    imageDfxConfig_.dataReadyTimestamp = GetTimestamp();

    int64_t loadDuration = dataReadyTimestamp - loadStartTimestamp;

    ACE_PERFORMANCE_LOG(
        "ImageLoad",
        "component=%{public}s, stage=DataReady, duration=%{public}ld ms",
        componentId_.c_str(),
        loadDuration
    );
}
```

---

## 8. 错误处理

### 8.1 错误码

```cpp
enum class ImageErrorCode {
    NETWORK_ERROR,           // 网络下载失败
    FILE_NOT_FOUND,          // 文件不存在
    UNSUPPORTED_FORMAT,      // 不支持的格式
    DATA_CORRUPTED,          // 数据损坏
    DECODE_ERROR,            // 解码失败
    OUT_OF_MEMORY,           // 内存不足
    LOAD_FAIL,               // 通用失败
};
```

### 8.2 错误传播

```
Loader::Load() 失败
    ↓
ImageLoadingContext::FailCallback(errorMsg, errorInfo)
    ↓
ImagePattern::OnImageLoadFail(errorMsg, errorInfo)
    ↓
尝试加载备用图（如果存在）
    ↓
FireErrorEvent(info)
    ↓
ArkTS onError 回调
```

### 8.3 重试机制

```cpp
void ImagePattern::OnImageLoadFail(...)
{
    if (retryCount_ < MAX_RETRY_COUNT) {
        retryCount_++;

        // 指数退避重试
        auto delay = CalculateRetryDelay(retryCount_);

        TaskExecutor::GetInstance()->PostDelayedTask(
            [this]() {
                LoadImageData();  // 重新加载
            },
            delay
        );
        return;
    }

    // 达到最大重试次数
    HandleFinalError();
}
```

---

## 9. 高级特性

### 9.1 AI 图像增强

**能力**：
- 图像质量增强
- 超分辨率
- 智能裁剪

**配置**：
```cpp
void SetImageQuality(AIImageQuality quality);
// quality: LOW, MEDIUM, HIGH
```

### 9.2 HDR 支持

**功能**：
- HDR 图像加载
- 色调映射（HDR 转 SDR）
- 亮度增强控制

**属性**：
- `DynamicRangeMode`: Standard / HDR / SDR
- `HdrBrightness`: 0.0 - 2.0（默认 1.0）

### 9. SVG 优化

**渲染方式**：
- 自定义 SVG DOM 解析器
- Skia SVG 渲染器

**特性**：
- 动态调整大小无质量损失
- 主题色支持
- 填充颜色覆盖

---

## 10. 最佳实践

### 10.1 性能优化

**推荐做法**：
```typescript
// 1. 启用自动调整大小
Image(src).autoResize(true)

// 2. 使用合适的 ImageFit
Image(src).fit(ImageFit.Cover)  // 而非必要不用 Fill

// 3. 提供备用图
Image('network_photo.jpg').alt('local_photo.jpg')

// 4. 设置源尺寸（如果已知）
Image(src).sourceSize({ width: 100, height: 100 })
```

**避免**：
```typescript
// ❌ 拉伸图像，破坏宽高比
Image(src).fit(ImageFit.Fill)

// ❌ 缩略图却全尺寸解码
Image('large_photo.jpg')
  .width(50)
  .height(50)

// ❌ 同步加载
Image(src).syncLoad(true)
```

### 10.2 内存管理

**推荐做法**：
```cpp
// 1. 实现内存级别回调
void OnNotifyMemoryLevel(int32_t level) override {
    if (level >= MEMORY_LEVEL_CRITICAL) {
        RecycleAllImageData();
    }
}

// 2. 不可见时回收内存
void OnVisibleChange(bool isVisible) override {
    if (!isVisible) {
        RecycleImageData();
    }
}

// 3. 成功后清除备用数据
void OnImageLoadSuccess(...) {
    ClearAltData();
}
```

### 10.3 错误处理

**推荐做法**：
```typescript
// 1. 提供三级降级
Image('network.jpg')
  .alt('fallback.jpg')
  .altError('error.png')
  .altPlaceholder('loading.png')

// 2. 处理错误事件
Image(src)
  .onError((event) => {
    console.error('Load failed:', event.errorMsg);
  })

// 3. 显示加载状态
Image(src)
  .altPlaceholder('loading.png')
  .onComplete(() => {
    hideLoadingIndicator();
  })
```

---

## 11. 问题排查

### 11.1 常见问题

| 症状 | 可能原因 | 解决方案 |
|------|---------|----------|
| 加载缓慢 | 无缓存、全尺寸解码 | 启用 autoResize，检查缓存 |
| 内存占用高 | 大图像、无调整 | 启用 autoResize，实现内存回调 |
| 图像模糊 | 插值质量低 | 设置 interpolation 为 High |
| 宽高比错误 | ImageFit 错误 | 使用 Cover 或 Contain |
| 动画卡顿 | 不可见时未暂停 | 实现 OnVisibleChange 暂停 |
| 闪烁闪烁 | 重复解码 | 检查布局同步 |

### 11.2 调试工具

**Dump 接口**：

```cpp
DumpInfo();         // 基本信息：源、状态、尺寸
DumpLayoutInfo();   // 布局信息：矩形、ImageFit
DumpRenderInfo();   // 渲染信息：CanvasImage、动画
DumpAdvanceInfo();  // 高级信息：质量、方向
DumpSvgInfo();      // SVG 信息：类型、支持
```

**日志命令**：
```bash
# 查看 Image 相关日志
hilog -T ArkUI | grep -i image

# 查看性能日志
hilog -T ArkUI | grep -i PERF
```

**内存分析**：
```bash
# 导出内存信息
hidumper -s 3001 -a -d "DumpMemory"

# 查看图像缓存
hidumper -s 3001 -a -d "DumpImageCache"
```

---

## 相关目录

```
frameworks/core/
├── components_ng/pattern/image/
│   ├── image_pattern.h/cpp           # 主要逻辑
│   ├── image_layout_property.h       # 布局属性
│   └── image_render_property.h       # 渲染属性
├── components_ng/image_provider/
│   ├── image_provider.h/cpp          # 加载协调
│   ├── image_loading_context.h/cpp   # 状态管理
│   ├── image_state_manager.h/cpp     # 状态机
│   ├── image_object.h/cpp            # 图像对象
│   ├── static_image_object.h/cpp     # 静态图像
│   ├── animated_image_object.h/cpp   # 动画图像
│   └── svg_image_object.h/cpp        # SVG 图像
├── image/
│   ├── image_loader.h/cpp            # 加载器基类
│   ├── network_image_loader.h/cpp    # 网络加载
│   ├── file_image_loader.h/cpp       # 文件加载
│   └── image_decoder.h/cpp           # 解码器
└── components_ng/render/
    └── canvas_image.h/cpp            # GPU 渲染
```

---

## 关键要点总结

1. **异步流水线**: 加载/解码在后台，UI 在主线程
2. **布局感知**: 解码延迟到最终尺寸确定后
3. **自动调整**: 按显示尺寸解码，节省内存
4. **三级降级**: 主图 → 备用图 → 错误图 → 占位符
5. **四级缓存**: 下载 → 对象 → 像素图 → GPU
6. **状态机**: 明确的状态转换避免竞态条件
7. **动画支持**: GIF/WebP/SVG 带可见性优化
8. **内存管理**: 基于可见性 + 内存级别回调

---
