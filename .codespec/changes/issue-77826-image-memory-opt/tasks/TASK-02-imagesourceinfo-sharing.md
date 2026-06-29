# TASK-02: ImageSourceInfo 改为 shared_ptr 共享

**ADR:** ADR-1
**优先级:** 高
**预估节省:** ~1,792B/节点（LayoutProperty 4 份拷贝消除）

## 目标

将 `ImageLayoutProperty` 中 4 个 `std::optional<ImageSourceInfo>` 改为 `std::optional<std::shared_ptr<ImageSourceInfo>>`，`ImageLoadingContext::src_` 改为 `std::shared_ptr<ImageSourceInfo>`，消除冗余拷贝。

## 关键约束

`ImageSourceInfo` 不继承 `AceType`，不能使用 `RefPtr`。使用 `std::shared_ptr` 替代。

共享后 ImageSourceInfo 必须**不可变**——属性更新时创建新实例（copy-on-write）。

## 改动范围

### 1. 属性宏适配（property.h）
- `ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP` 宏生成的 `std::optional<type> prop##name##_` 对 `std::shared_ptr<ImageSourceInfo>` 类型需确认 NearEqual 比较是否正确
- 可能需要为 shared_ptr<ImageSourceInfo> 特化 NearEqual，比较指针内容而非指针值
- 或者直接在 ImageLayoutProperty 中手动定义这 4 个属性，不依赖宏

### 2. ImageLayoutProperty（image_layout_property.h:51-52, 64-65）
- `propImageSourceInfo_`：`std::optional<ImageSourceInfo>` → `std::optional<std::shared_ptr<ImageSourceInfo>>`
- `propAlt_`：同上
- `propAltError_`：同上
- `propAltPlaceholder_`：同上
- 对应的 Get/Set 方法适配（返回 `const std::shared_ptr<ImageSourceInfo>&` 或 `std::shared_ptr<ImageSourceInfo>`）
- Clone 方法需深拷贝（创建新 shared_ptr 指向新实例）

### 3. ImageLoadingContext（image_loading_context.h:210）
- `ImageSourceInfo src_` → `std::shared_ptr<ImageSourceInfo> src_`
- 构造函数（image_loading_context.cpp:34-46）— 接收 shared_ptr 参数
- `GetSrc()` (lines 81-84) — 改为返回 `const std::shared_ptr<ImageSourceInfo>&`
- `GetSourceInfo()` (line 71) — 改为返回 `const ImageSourceInfo&`（解引用 shared_ptr）

### 4. ImagePattern 中 3 个 ImageLoadingContext 创建点（image_pattern.cpp）
- Line 1143-1144: `LoadImage()` — 传 shared_ptr 而非值拷贝
- Line 1178-1179: `LoadAltImage()` — 同上
- Line 2993-2994: `LoadAltErrorImage()` — 同上

### 5. 所有使用 GetImageSourceInfo()/GetAlt()/GetAltError()/GetAltPlaceholder() 的调用方
- 从 LayoutProperty 获取的现在是 shared_ptr，需适配解引用

### 6. 属性更新路径
- `SetImageSourceInfo()` / `SetAlt()` 等 — 接收 shared_ptr 或值（值时包装为 shared_ptr）
- 属性更新时：如果值不变（ NearEqual ），保持现有 shared_ptr；值变化时创建新 shared_ptr

## 验证方法

1. 编译通过
2. 单元测试通过
3. sizeof 检查：LayoutProperty 中 4 个 `optional<shared_ptr<ImageSourceInfo>>`（~96B）替代 4 个 `optional<ImageSourceInfo>`（~1,824B），净减 ~1,728B
