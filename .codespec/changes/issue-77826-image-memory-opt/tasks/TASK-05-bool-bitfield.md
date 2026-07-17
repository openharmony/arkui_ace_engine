# TASK-05: Bool 位域合并

**ADR:** ADR-6
**优先级:** 低
**预估节省:** ~17B/节点

## 目标

将 ImagePattern 中 21 个 bool 成员合并为 1 个 uint32_t 位掩码结构体，减少 padding 浪费。

## 改动范围

### 1. 定义位域结构体（image_pattern.h）

```cpp
struct ImagePatternFlags {
    // byte 0
    bool isRecycledImage_ : 1;
    bool needLoadAlt_ : 1;
    bool enableDrag_ : 1;
    bool syncLoad_ : 1;
    bool needBorderRadius_ : 1;
    bool isImageReloadNeeded_ : 1;
    bool isEnableAnalyzer_ : 1;
    bool autoResizeDefault_ : 1;
    // byte 1
    bool isSceneBoardWindow_ : 1;
    bool isSensitive_ : 1;
    bool isFullyInitializedFromTheme_ : 1;
    bool isSelected_ : 1;
    bool isOrientationChange_ : 1;
    bool isImageAnimator_ : 1;
    bool isPixelMapChanged_ : 1;
    bool isComponentSnapshotNode_ : 1;
    // byte 2
    bool isNeedReset_ : 1;
    bool hasSetPixelMapMemoryName_ : 1;
    bool previousVisibility_ : 1;
    bool supportSvg2_ : 1;
    bool isMeasured_ : 1;
    bool loadFailed_ : 1;
    bool isLoadAlt_ : 1;
    // byte 3: reserved
    uint8_t reserved_ : 1;
};
static_assert(sizeof(ImagePatternFlags) == 4, "ImagePatternFlags must be 4 bytes");
```

### 2. ImagePattern 成员替换

将 21 个独立 bool 声明替换为：
```cpp
ImagePatternFlags flags_ {};
```

### 3. 所有 bool 引用适配

- `syncLoad_` → `flags_.syncLoad_`
- `isMeasured_` → `flags_.isMeasured_`
- 以此类推，所有 21 个 bool

### 4. 初始化列表适配

构造函数中 21 个 bool 初始化值写入 `flags_` 的初始化：
```cpp
ImagePattern()
    : flags_{.autoResizeDefault_ = true, .needLoadAlt_ = true}
```

## 验证方法

1. 编译通过（位域访问语法正确）
2. 单元测试通过
3. sizeof(ImagePattern) 对比（减少 ~17B）
