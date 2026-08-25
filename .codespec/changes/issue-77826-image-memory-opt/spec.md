# spec.md — Image 组件基础内存优化

## 概述

本规格定义 Image 组件基础内存优化的行为规则、验收标准和验证映射。优化范围限定在 NG Image 组件的内部数据结构，不影响公共 API 和用户可见行为。

---

## 用户故事

### US-1: 减少单个 Image 节点的基础内存

**作为** OpenHarmony 应用开发者
**我想要** Image 组件在加载和显示图片时占用更少内存
**以便** 在列表/网格等大量使用 Image 的场景下，应用整体内存占用更低

### US-2: 保持功能完全兼容

**作为** Image 组件的现有使用者
**我想要** 升级后所有现有功能（加载/显示/事件/alt 回退）行为不变
**以便** 不需要修改任何现有代码

---

## 验收标准

### P0 验收标准

| AC ID | 用户故事 | WHEN/THEN |
|-------|---------|-----------|
| AC-1.1 | US-1 | WHEN 500 个静态 Image 节点（src 为资源图片）加载完成 THEN 真实设备上单节点基础内存较优化前减少 ≥5KB |
| AC-1.2 | US-1 | WHEN 500 个 PixelMap Image 节点加载完成 THEN 真实设备上单节点基础内存较优化前减少 ≥5KB |
| AC-2.1 | US-2 | WHEN Image 组件正常加载/显示/销毁 THEN 行为与优化前完全一致（无功能回归） |
| AC-2.2 | US-2 | WHEN 运行 Image 相关全部单元测试 THEN 全部通过 |
| AC-2.3 | US-2 | WHEN Image 触发 onError 进入 alt 回退链 THEN alt 显示和事件行为与优化前一致 |

### P1 验收标准

| AC ID | 用户故事 | WHEN/THEN |
|-------|---------|-----------|
| AC-3.1 | US-1 | WHEN 编译完成后 THEN sizeof(ImageSourceInfo) 较优化前减少 30%+ |
| AC-3.2 | US-1 | WHEN ImageDfxConfig 改为共享 THEN 单节点中 ImageDfxConfig 实例从 5-6 份降至 1 份 |
| AC-3.3 | US-1 | WHEN ImageLoadingContext 完成加载并释放 THEN 其持有的 ImageObject/CanvasImage 被主动释放 |
| AC-3.4 | US-1 | WHEN Image 无 alt 配置 THEN alt 相关状态不分配内存 |

---

## 功能规则

### FR-1: ImageSourceInfo 共享语义

- FR-1.1: `ImageLayoutProperty` 中的 `propImageSourceInfo_`、`propAlt_`、`propAltError_`、`propAltPlaceholder_` 改为 `std::optional<RefPtr<ImageSourceInfo>>`
- FR-1.2: `ImageLoadingContext::src_` 改为 `RefPtr<ImageSourceInfo>`，创建时传入 Pattern 持有的引用
- FR-1.3: ImageSourceInfo 在共享后必须保持不可变；属性更新时创建新的 ImageSourceInfo 实例
- FR-1.4: `GetImageSourceInfo()` 返回 `const RefPtr<ImageSourceInfo>&` 而非值拷贝

### FR-2: ImageDfxConfig 按需创建和共享

- FR-2.1: `ImagePattern` 中 3 个 ImageDfxConfig 改为 `RefPtr<ImageDfxConfig>`，首次需要时创建
- FR-2.2: `ImageSourceInfo::imageDfxConfig_` 改为 `RefPtr<ImageDfxConfig>`
- FR-2.3: `ImageLoadingContext::imageDfxConfig_` 改为 `RefPtr<ImageDfxConfig>`
- FR-2.4: DFX 日志写入前检查 RefPtr 是否已初始化，未初始化时跳过该条日志（不崩溃）

### FR-3: Alt 状态按需创建

- FR-3.1: `ImagePattern` 中 alt 相关字段合并为 `std::unique_ptr<AltImageState>`
- FR-3.2: `ImagePattern` 中 altError 相关字段合并为 `std::unique_ptr<AltErrorState>`
- FR-3.3: 仅在 alt/altError src 被设置时才创建对应状态对象
- FR-3.4: alt 回退链逻辑不变，只是通过 `altState_->loadingCtx` 替代 `altLoadingCtx_` 访问

### FR-4: 回调按需分配

- FR-4.1: `ImagePattern::keyEventCallback_` 和 `onProgressCallback_` 改为按需分配
- FR-4.2: 注册回调时检查并分配，未注册时零开销

### FR-5: Bool 位域合并

- FR-5.1: `ImagePattern` 中 22 个 bool 合并为 `uint32_t` 位掩码结构体
- FR-5.2: 确认所有 bool 均在 UI 线程访问（不涉及跨线程原子操作需求）
- FR-5.3: 提供内联 getter/setter 保持代码可读性

---

## 异常/豁免规则

### ER-1: DFX 配置未初始化

- ER-1.1: 当 ImageDfxConfig 的 RefPtr 为空时，DFX 日志跳过该条记录
- ER-1.2: 不因 DFX 配置未初始化而阻塞正常加载和显示流程

### ER-2: ImageSourceInfo 共享修改

- ER-2.1: 如果代码路径需要修改共享的 ImageSourceInfo，必须创建新实例（copy-on-write）
- ER-2.2: 不得在共享引用上直接修改成员

---

## 恢复契约

### RC-1: 属性更新时的内存处理

- RC-1.1: 当 src 属性更新时，旧的 ImageSourceInfo RefPtr 引用计数自然递减，无需手动释放
- RC-1.2: 当 alt 被移除时，`altState_` 的 unique_ptr 析构自动释放所有关联资源

### RC-2: 组件销毁时的内存释放

- RC-2.1: ImagePattern 析构时，所有 RefPtr 和 unique_ptr 自然释放
- RC-2.2: ImageLoadingContext 在不再被引用时释放 ImageObject 和 CanvasImage

---

## 兼容性

| 维度 | 影响 |
|------|------|
| ArkTS API | 无变化 |
| C API | 无变化 |
| 默认行为 | 无变化 |
| 序列化/IPC | ImageSourceInfo 和 ImageDfxConfig 为内部类，不涉及 IPC |
| 单元测试 | 现有测试逻辑不变，可能需要调整 mock 数据构造方式 |

---

## 验证映射

| AC ID | 验证方法 | 验证命令/工具 |
|-------|---------|-------------|
| AC-1.1 | 500 Image 真实设备内存实测 | SpecTest 测试用例 + 设备内存 profiling |
| AC-1.2 | 500 PixelMap Image 真实设备内存实测 | SpecTest 测试用例 + 设备内存 profiling |
| AC-2.1 | Image 相关单元测试全量 | `./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/test/unittest/core/pattern:image_pattern_test --ccache` |
| AC-2.2 | Image 相关单元测试全量 | 同上 |
| AC-2.3 | Alt fallback 单元测试 | 同上（gtest_filter=*Alt*） |
| AC-3.1 | sizeof 编译期检查 | `static_assert(sizeof(ImageSourceInfo) < X)` |
| AC-3.2 | 调试期实例计数 | 添加临时计数器验证 |
| AC-3.3 | 单元测试验证释放 | Mock ImageLoadingContext 生命周期 |
| AC-3.4 | 单元测试验证无 alt 时不分配 | 检查 altState_ == nullptr |

---

## SpecTest 适用性

**N/A** — 本次优化为内部数据结构重构，不改变用户可见行为，不改变 Inspector 可观测的节点树/属性/布局。无法通过 SpecTest Host Preview 断言。

替代验证：sizeof 对比 + 单元测试 + 真实设备内存 profiling。

---

## 不涉及项

- 图片解码/加载底层流程
- 动画图 / SVG 代码路径
- Legacy Image 组件
- 渲染/绘制路径优化
- 公共 API 变更
