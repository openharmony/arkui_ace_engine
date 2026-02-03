# ArkUI ImageAnimator 组件完整知识库

> **版本**: 1.0
> **更新时间**: 2026-02-02
> **基于**: OpenHarmony ace_engine (master 分支)

---

## 目录

1. [架构概述](#1-架构概述)
2. [核心类详解](#2-核心类详解)
3. [完整动画流程](#3-完整动画流程)
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

ImageAnimator 组件实现了一个帧动画播放器，采用 3 层架构：

```
ArkTS 前端
    ↓
模式层 (ImageAnimatorPattern) - 业务逻辑和状态管理
    ↓
动画控制层 (ControlledAnimator) - 动画调度和时间控制
    ↓
图像层 (ImagePattern) - 单帧图像加载和渲染
```

**设计原则**：
- **预加载缓存**: 提前加载后续帧，减少播放卡顿
- **自适应大小**: 根据所有帧尺寸自动调整容器大小
- **状态驱动**: 清晰的状态机管理动画生命周期
- **内存优化**: 智能缓存策略，平衡性能和内存

### 1.2 线程模型

**主线程职责**：
- UI 更新和事件处理
- 动画状态控制
- 图像节点切换
- 回调执行

**后台线程职责**：
- 图像数据加载 (ImageLoader)
- 图像解码 (ImageDecoder)

**关键**: 图像缓存节点在后台加载，主线程负责切换显示

---

## 2. 核心类详解

### 2.1 ImageAnimatorPattern

**职责**：
- 管理动画帧序列
- 控制动画播放状态
- 实现图像预加载缓存
- 处理动画可见性

**关键成员变量**：
```cpp
RefPtr<ControlledAnimator> controlledAnimator_;  // 动画控制器
std::vector<ImageProperties> images_;             // 图像序列
std::list<CacheImageStruct> cacheImages_;         // 预加载缓存
ControlledAnimator::ControlStatus status_;        // 动画状态
int32_t iteration_ = 1;                           // 迭代次数
int32_t durationTotal_;                           // 总时长
int32_t nowImageIndex_;                           // 当前帧索引
bool isReverse_;                                  // 反向播放
bool fixedSize_;                                  // 固定尺寸模式
```

**状态机**：
```
IDLE (初始状态)
    ↓ Forward() / Backward()
RUNNING (播放中)
    ↓ Pause()
PAUSED (已暂停)
    ↓ Forward() / Backward()
RUNNING
    ↓ Finish() / Stop()
STOPPED (已停止)
```

**关键方法**：

- **OnModifyDone()**: 入口点，初始化动画
  ```cpp
  void ImageAnimatorPattern::OnModifyDone() {
      Pattern::OnModifyDone();
      UpdateBorderRadius();

      auto size = static_cast<int32_t>(images_.size());
      if (size <= 0) return;

      // 生成缓存图像
      GenerateCachedImages();

      // 创建动画插值器
      if (imagesChangedFlag_) {
          controlledAnimator_->ClearInterpolators();
          controlledAnimator_->AddInterpolator(CreatePictureAnimation(size));
          imagesChangedFlag_ = false;
      }

      // 更新事件回调
      if (firstUpdateEvent_) {
          UpdateEventCallback();
          firstUpdateEvent_ = false;
      }

      RunAnimatorByStatus(nowImageIndex_);
  }
  ```

- **SetShowingIndex()**: 切换显示帧
  ```cpp
  void ImageAnimatorPattern::SetShowingIndex(int32_t index) {
      auto host = GetHost();
      auto imageFrameNode = DynamicCast<FrameNode>(host->GetChildren().front());
      auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();

      nowImageIndex_ = index;

      // 检查是否已显示相同源
      bool isShowingSrc = IsShowingSrc(imageFrameNode, images_[index].src);

      // 查找缓存
      auto cacheImageIter = FindCacheImageNode(images_[index].src);

      if (isShowingSrc) {
          // 相同源，仅更新信息
          UpdateShowingImageInfo(imageFrameNode, index);
      } else if (cacheImageIter == cacheImages_.end()) {
          // 无缓存，直接显示
          UpdateShowingImageInfo(imageFrameNode, index);
      } else if (cacheImageIter->isLoaded) {
          // 使用缓存节点
          auto cacheImageNode = cacheImageIter->imageNode;
          host->RemoveChild(imageFrameNode);
          host->AddChild(cacheImageNode, DEFAULT_NODE_SLOT, true);
          cacheImages_.erase(cacheImageIter);
          // 将旧节点加入缓存
          CacheImageStruct newCacheImageStruct(imageFrameNode);
          newCacheImageStruct.isLoaded = true;
          cacheImages_.emplace_back(newCacheImageStruct);
      }

      // 更新缓存队列
      int32_t nextIndex = GetNextIndex(index);
      for (auto& cacheImage : cacheImages_) {
          UpdateCacheImageInfo(cacheImage, nextIndex);
          nextIndex = GetNextIndex(nextIndex);
      }

      host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
  }
  ```

- **GenerateCachedImages()**: 生成预加载缓存
  ```cpp
  void ImageAnimatorPattern::GenerateCachedImages() {
      CHECK_NULL_VOID(images_.size());

      // 根据平均显示时间计算缓存数量
      auto averageShowTime = controlledAnimator_->GetDuration() / static_cast<int32_t>(images_.size());
      size_t cacheImageNum = static_cast<uint32_t>(averageShowTime) >= CRITICAL_TIME ? 1 : 2;
      cacheImageNum = std::min(images_.size() - 1, cacheImageNum);

      if (cacheImages_.size() > cacheImageNum) {
          cacheImages_.resize(cacheImageNum);
          return;
      }

      // 创建缓存图像节点
      while (cacheImages_.size() < cacheImageNum) {
          auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1,
              MakeRefPtr<ImagePattern>());
          auto imagePattern = DynamicCast<ImagePattern>(imageNode->GetPattern());
          imagePattern->SetImageAnimator(true);

          auto imageLayoutProperty = imageNode->GetLayoutProperty();
          imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
          imageLayoutProperty->UpdateAlignment(Alignment::TOP_LEFT);

          AddImageLoadSuccessEvent(imageNode);
          cacheImages_.emplace_back(CacheImageStruct(imageNode));
      }
  }
  ```

### 2.2 ControlledAnimator

**职责**：
- 动画时间控制
- 插值器管理
- 状态转换
- 回调分发

**核心接口**：
```cpp
class ControlledAnimator {
public:
    void SetDuration(int32_t duration);                  // 设置动画时长
    void SetIteration(int32_t iteration);               // 设置迭代次数
    void SetFillMode(FillMode fillMode);                // 设置填充模式

    void Forward();                                      // 正向播放
    void Backward();                                     // 反向播放
    void Pause();                                        // 暂停
    void Finish();                                       // 完成
    void Cancel();                                       // 取消

    void AddInterpolator(const std::vector<PictureInfo>& pictures);  // 添加插值器
    void AddListener(const OnFrameCallback& callback);  // 添加帧回调

    ControlStatus GetControlStatus() const;             // 获取状态
    int32_t GetDuration() const;                        // 获取时长
};
```

**PictureInfo 结构**：
```cpp
struct PictureInfo {
    float weight;    // 权重 (显示时长占比)
    int32_t index;   // 图像索引
};
```

---

## 3. 完整动画流程

### 阶段 1: 属性配置

**ArkTS 代码**：
```typescript
ImageAnimator()
  .images([{ src: 'frame1.png', duration: 100 },
           { src: 'frame2.png', duration: 100 }])
  .duration(1000)
  .iterations(3)
  .reverse(false)
  .fixedSize(true)
```

### 阶段 2: 初始化动画

```cpp
void ImageAnimatorPattern::OnModifyDone() {
    // 1. 创建动画插值器
    auto pictureAnimation = CreatePictureAnimation(size);
    /*
     * 每帧的 weight = frame.duration / totalDuration
     * 例如: [{weight: 0.1, index: 0}, {weight: 0.1, index: 1}, ...]
     */

    // 2. 注册帧回调
    controlledAnimator_->AddListener([weak = WeakClaim(this)](int32_t index) {
        auto imageAnimator = weak.Upgrade();
        CHECK_NULL_VOID(imageAnimator);
        imageAnimator->SetShowingIndex(index);
    });

    // 3. 设置动画参数
    controlledAnimator_->SetIteration(GetIteration());
    controlledAnimator_->SetDuration(durationTotal_);
}
```

### 阶段 3: 开始播放

```cpp
void ImageAnimatorPattern::RunAnimatorByStatus(int32_t index) {
    switch (status_) {
        case ControlledAnimator::ControlStatus::IDLE:
            // 首次显示第一帧
            SetShowingIndex(index);
            break;

        case ControlledAnimator::ControlStatus::RUNNING:
            // 开始动画播放
            isReverse_ ? controlledAnimator_->Backward() : controlledAnimator_->Forward();
            break;

        case ControlledAnimator::ControlStatus::PAUSED:
            // 暂停状态
            controlledAnimator_->Pause();
            break;

        case ControlledAnimator::ControlStatus::STOPPED:
            // 停止状态
            controlledAnimator_->Finish();
            break;
    }
}
```

### 阶段 4: 帧切换

```
ControlledAnimator 触发帧回调
    ↓
SetShowingIndex(index)
    ↓
检查当前显示源 vs 目标源
    ↓
[相同源] → 仅更新信息
[不同源 + 无缓存] → 直接加载显示
[不同源 + 有缓存] → 切换缓存节点
    ↓
更新预加载缓存队列
    ↓
标记 UI 刷新
```

### 阶段 5: 渲染显示

```cpp
ImagePattern::OnModifyDone()
    → LoadImageDataIfNeed()
    → OnImageDataReady()
    → OnDirtyLayoutWrapperSwap()
    → OnImageLoadSuccess()
    → Paint()
```

---

## 4. 关键技术点

### 4.1 预加载缓存策略

**缓存数量计算**：
```cpp
// CRITICAL_TIME = 50ms
auto averageShowTime = totalDuration / frameCount;

if (averageShowTime >= CRITICAL_TIME) {
    cacheCount = 1;  // 慢速动画，缓存1帧
} else {
    cacheCount = 2;  // 快速动画，缓存2帧
}

cacheCount = std::min(frameCount - 1, cacheCount);
```

**缓存节点管理**：
```cpp
struct CacheImageStruct {
    RefPtr<FrameNode> imageNode;  // 缓存的图像节点
    int32_t index;                 // 当前缓存的帧索引
    bool isLoaded;                 // 是否已加载完成
};
```

**缓存更新流程**：
```
显示第 N 帧
    ↓
计算下一帧: nextIndex = GetNextIndex(N)
    ↓
遍历 cacheImages_:
    UpdateCacheImageInfo(cacheImage, nextIndex)
    nextIndex = GetNextIndex(nextIndex)
```

### 4.2 自适应容器大小

```cpp
void ImageAnimatorPattern::AdaptSelfSize() {
    auto host = GetHost();
    const auto& layoutProperty = host->GetLayoutProperty();

    // 已设置明确尺寸，跳过
    if (layoutProperty->GetCalcLayoutConstraint()->selfIdealSize->IsValid()) {
        return;
    }

    // 遍历所有帧，找最大尺寸
    Dimension maxWidth;
    Dimension maxHeight;
    double maxWidthPx = 0.0;
    double maxHeightPx = 0.0;

    for (const auto& image : images_) {
        auto widthPx = image.width.ConvertToPx();
        if (widthPx > maxWidthPx) {
            maxWidthPx = widthPx;
            maxWidth = image.width;
        }

        auto heightPx = image.height.ConvertToPx();
        if (heightPx > maxHeightPx) {
            maxHeightPx = heightPx;
            maxHeight = image.height;
        }
    }

    // 设置容器尺寸
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(maxWidth), CalcLength(maxHeight))
    );
}
```

### 4.3 固定尺寸 vs 自适应尺寸

**fixedSize = true (默认)**：
```cpp
// 所有帧填充容器
imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
margin.SetEdges(CalcLength(0.0));
```

**fixedSize = false**：
```cpp
// 每帧独立尺寸和位置
imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
margin.left = CalcLength(images_[index].left);
margin.top = CalcLength(images_[index].top);
CalcSize realSize = {
    CalcLength(images_[index].width),
    CalcLength(images_[index].height)
};
imageLayoutProperty->UpdateUserDefinedIdealSize(realSize);
```

### 4.4 反向播放

```cpp
int32_t ImageAnimatorPattern::GetNextIndex(int32_t preIndex) {
    if (isReverse_) {
        // 反向: 前一帧 (循环到末尾)
        return preIndex == 0 ? (static_cast<int32_t>(images_.size()) - 1) : (preIndex - 1);
    }
    // 正向: 下一帧 (循环到开头)
    return (preIndex + 1) % static_cast<int32_t>(images_.size());
}
```

### 4.5 可见性优化

```cpp
void ImageAnimatorPattern::OnVisibleAreaChange(bool visible, double ratio) {
    if (!visible) {
        // 不可见时暂停
        OnInActiveImageAnimator();  // → controlledAnimator_->Pause()
    } else {
        // 可见时恢复
        OnActiveImageAnimator();    // → Forward() / Backward()
    }
}

void ImageAnimatorPattern::OnInActiveImageAnimator() {
    if (status_ == ControlledAnimator::ControlStatus::RUNNING) {
        controlledAnimator_->Pause();
    }
}

void ImageAnimatorPattern::OnActiveImageAnimator() {
    if (status_ == ControlledAnimator::ControlStatus::RUNNING &&
        controlledAnimator_->GetControlStatus() != ControlledAnimator::ControlStatus::RUNNING) {
        isReverse_ ? controlledAnimator_->Backward() : controlledAnimator_->Forward();
    }
}
```

---

## 5. 属性系统

### 5.1 布局属性 (ImageAnimatorLayoutProperty)

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| **images** | vector\<ImageProperties\> | - | 图像序列 (src, duration, width, height) |
| **duration** | int32_t | 1000 | 动画总时长 (ms) |
| **iterations** | int32_t | 1 | 迭代次数 (-1 = 无限循环) |
| **reverse** | bool | false | 反向播放 |
| **fixedSize** | bool | true | 固定尺寸模式 |

### 5.2 ImageProperties 结构

```cpp
struct ImageProperties {
    std::string src;              // 图像源 (网络/本地/资源)
    RefPtr<PixelMap> pixelMap;    // 像素图
    int32_t duration = 0;         // 显示时长 (ms)
    Dimension left = 0.0_vp;      // 左边距 (fixedSize=false)
    Dimension top = 0.0_vp;       // 上边距 (fixedSize=false)
    Dimension width = 0.0_vp;     // 宽度 (fixedSize=false)
    Dimension height = 0.0_vp;    // 高度 (fixedSize=false)
    std::string bundleName;       // 应用包名
    std::string moduleName;       // 模块名
};
```

### 5.3 填充模式 (FillMode)

| 模式 | 说明 |
|------|------|
| **None** | 动画结束后回到初始状态 |
| **Forwards** (默认) | 动画结束后保持最后一帧状态 |
| **Backwards** | 动画开始前应用第一帧状态 |
| **Both** | 结合 Forwards 和 Backwards |

---

## 6. 事件系统

### 6.1 事件类型

**onStart** - 动画开始：
```cpp
controlledAnimator_->AddStartListener([startEvent] {
    startEvent();  // 触发 ArkTS onStart 回调
});
```

**onStop** - 动画停止：
```cpp
controlledAnimator_->AddStopListener([stopEvent] {
    stopEvent();
});
```

**onPause** - 动画暂停：
```cpp
controlledAnimator_->AddPauseListener([pauseEvent] {
    pauseEvent();
});
```

**onRepeat** - 动画重复：
```cpp
controlledAnimator_->AddRepeatListener([repeatEvent] {
    repeatEvent();
});
```

**onCancel** - 动画取消：
```cpp
controlledAnimator_->AddCancelListener([cancelEvent] {
    cancelEvent();
});
```

### 6.2 事件注册流程

```cpp
void ImageAnimatorPattern::UpdateEventCallback() {
    auto eventHub = GetEventHub<ImageAnimatorEventHub>();

    controlledAnimator_->ClearAllListeners();

    auto startEvent = eventHub->GetStartEvent();
    if (startEvent != nullptr) {
        controlledAnimator_->AddStartListener([startEvent] { startEvent(); });
    }

    // ... 其他事件

    auto repeatEvent = eventHub->GetRepeatEvent();
    if (repeatEvent != nullptr) {
        controlledAnimator_->AddRepeatListener([repeatEvent] { repeatEvent(); });
    }
}
```

---

## 7. 性能优化

### 7.1 缓存优化

**策略**: 预加载下一帧 (或两帧)

**收益**:
- 减少帧切换延迟
- 避免播放卡顿
- 提升流畅度

**内存权衡**:
- 慢速动画 (>= 50ms/帧): 缓存1帧
- 快速动画 (< 50ms/帧): 缓存2帧

### 7.2 节点复用

```cpp
// 缓存节点切换，而非销毁重建
if (cacheImageIter->isLoaded) {
    auto cacheImageNode = cacheImageIter->imageNode;
    host->RemoveChild(imageFrameNode);           // 移除旧节点
    host->AddChild(cacheImageNode, ...);         // 添加缓存节点
    cacheImages_.erase(cacheImageIter);          // 从缓存移除

    // 旧节点加入缓存池复用
    CacheImageStruct newCacheImageStruct(imageFrameNode);
    newCacheImageStruct.isLoaded = true;
    cacheImages_.emplace_back(newCacheImageStruct);
}
```

### 7.3 可见性暂停

```cpp
// 不可见时自动暂停，节省 CPU/GPU
void ImageAnimatorPattern::OnVisibleAreaChange(bool visible, double ratio) {
    if (!visible) {
        OnInActiveImageAnimator();  // Pause
    } else {
        OnActiveImageAnimator();    // Resume
    }
}
```

---

## 8. 错误处理

### 8.1 图像加载失败

```cpp
void ImageAnimatorPattern::AddImageLoadSuccessEvent(...) {
    auto eventHub = imageFrameNode->GetEventHub<ImageEventHub>();
    eventHub->SetOnComplete([](const LoadImageSuccessEvent& info) {
        if (info.GetLoadingStatus() != 1) {  // 非 1 = 失败
            // 处理加载失败
            LOGE("Image load failed");
            return;
        }

        // 标记缓存已加载
        iter->isLoaded = true;
    });
}
```

### 8.2 索引越界保护

```cpp
void ImageAnimatorPattern::SetShowingIndex(int32_t index) {
    if (index >= static_cast<int32_t>(images_.size()) || index < 0) {
        LOGW("ImageAnimator update index error, index: %{public}d, size: %{public}zu",
             index, images_.size());
        return;
    }
    // ...
}
```

---

## 9. 高级特性

### 9.1 卡片渲染优化

```cpp
void ImageAnimatorPattern::UpdateFormDurationByRemainder() {
    if (IsFormRender()) {
        // 计算剩余显示时间
        formAnimationRemainder_ = DEFAULT_DURATION -
            (GetMicroTickCount() - formAnimationStartTime_) / MICROSEC_TO_MILLISEC;

        // 使用剩余时间作为动画时长
        if ((formAnimationRemainder_ > 0) &&
            (controlledAnimator_->GetDuration() > formAnimationRemainder_)) {
            controlledAnimator_->SetDuration(formAnimationRemainder_);
        }

        // 时间用尽，结束动画
        if (formAnimationRemainder_ <= 0) {
            isFormAnimationEnd_ = true;
        }
    }
}
```

### 9.2 动画图像控制

```cpp
void ImageAnimatorPattern::ControlAnimatedImageAnimation(
    const RefPtr<FrameNode>& imageFrameNode, bool play)
{
    auto imagePattern = DynamicCast<ImagePattern>(imageFrameNode->GetPattern());
    auto image = imagePattern->GetCanvasImage();

    if (!image->IsStatic()) {  // GIF/WebP
        image->ControlAnimation(play);  // 控制内部动画
    }
}
```

---

## 10. 最佳实践

### 10.1 性能优化

**推荐做法**：
```typescript
// 1. 使用合理尺寸的图像
ImageAnimator()
  .images([{ src: 'frame1_100x100.png', duration: 100 }])
  // 避免使用过大的图像 (如 4K)

// 2. 设置合适的总时长
ImageAnimator()
  .images([...])  // 10 帧
  .duration(1000)  // 总时长 1000ms，每帧 100ms

// 3. 启用自动可见性监控
ImageAnimator()
  .images(...)
  .monitorInvisibleArea(true)
```

**避免**：
```typescript
// ❌ 使用无限循环且不监控可见性
ImageAnimator()
  .images([...])
  .iterations(-1)  // 无限循环
  .monitorInvisibleArea(false)  // 不监控可见性

// ❌ fixedSize=false 但设置不全
ImageAnimator()
  .images([{ src: 'frame.png' }])  // 缺少 width/height
  .fixedSize(false)
```

### 10.2 内存管理

**推荐做法**：
```typescript
// 1. 设置合理迭代次数
ImageAnimator()
  .iterations(1)  // 播放一次后停止

// 2. 监听停止事件释放资源
ImageAnimator()
  .onStop(() => {
    // 清理资源
  })
```

---

## 11. 问题排查

### 11.1 常见问题

| 症状 | 可能原因 | 解决方案 |
|------|---------|----------|
| 播放卡顿 | 图像过大、无缓存 | 缩小图像尺寸，检查缓存策略 |
| 内存占用高 | 无限循环、大图像 | 设置 iterations，使用合理尺寸 |
| 切换闪烁 | 缓存未命中 | 检查预加载逻辑 |
| 尺寸不正确 | fixedSize 设置错误 | 根据需求选择 fixedSize 模式 |

### 11.2 调试工具

**日志标签**：
```bash
# 查看动画日志
hilog -T ACE_IMAGE | grep -i animator
```

**状态检查**：
```cpp
ToJsonValue()  // 输出当前状态
// state: AnimationStatus.Running
// duration: 1000
// reverse: false
// iterations: 1
```

---

## 相关目录

```
frameworks/core/components_ng/pattern/image_animator/
├── image_animator_pattern.h/cpp           # 主要逻辑
├── image_animator_event_hub.h             # 事件处理
└── image_animator_model.h                 # 数据模型

base/image/
└── controlled_animator.h/cpp              # 动画控制器
```

---

## 关键要点总结

1. **预加载缓存**: 根据帧时长动态调整缓存数量
2. **自适应大小**: 自动计算最大帧尺寸作为容器大小
3. **状态驱动**: 清晰的状态机管理动画生命周期
4. **节点复用**: 缓存节点池复用，减少创建销毁开销
5. **可见性优化**: 不可见时自动暂停，节省资源
6. **反向支持**: 支持正反向播放，缓存的更新顺序相应调整
7. **卡片优化**: 卡片场景下特殊处理动画时长
8. **动画图像**: 支持 GIF/WebP 内部动画的控制

---
