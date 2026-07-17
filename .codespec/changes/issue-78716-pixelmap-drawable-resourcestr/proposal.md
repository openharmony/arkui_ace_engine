# 需求澄清与基线

## 原始需求

为 `PixelMapDrawableDescriptor` 补全 `ResourceStr` 构造函数实现。

**背景**：SDK 声明文件（`@ohos.arkui.drawableDescriptor.d.ts` 和 `.static.d.ets`）已在 @since 26.0.0 声明 `constructor(src?: image.PixelMap | ResourceStr)` 重载，但目前仅 `PixelMap` 路径有实现，`ResourceStr` 路径缺失。

**要求**：
- 动态 API 和静态 API 均需实现
- 走新架构（`frameworks/core/drawable/` 下的 `Ace::PixelMapDrawableDescriptor`）

## 澄清记录

| 轮次 | 问题 | 回答 | 确认来源 |
|------|------|------|----------|
| 1 | FuncID=04-01-03, FeatID=Feat-02？ | 确认 | Owner 对话 |
| 2 | Profile=arkui/sdk-api, lineage=new-on-legacy？ | 确认 | Owner 对话 |
| 3 | 实现范围：动态 NAPI+Core, 静态 Koala+ANI, 单元测试？ | 全选 | Owner 对话 |
| 4 | 理解确认：ResourceStr 补全，复用 DrawableDescriptorInfo/Loader，参考 AnimatedDrawableDescriptor 模式？ | 正确 | Owner 对话 |

## 需求基线

### 目标

`PixelMapDrawableDescriptor` 构造函数支持 `ResourceStr` 输入类型，使得开发者可以直接传入文件路径（string）或资源引用（Resource）来创建描述符，无需先手动解码为 PixelMap。

### 范围（In Scope）

| 层 | 变更内容 | 关键文件 |
|----|----------|----------|
| 动态 NAPI 桥接 | `JsDrawableDescriptor::PixelMapConstructor` 新增 ResourceStr 分支，解析 string/Resource 并传给核心 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp` |
| 核心层 | `Ace::PixelMapDrawableDescriptor` 新增从 `DrawableDescriptorInfo` 构造的能力，调用 `DrawableDescriptorLoader::LoadData` 加载资源 | `frameworks/core/drawable/pixel_map_drawable_descriptor.h/.cpp` |
| 静态前端 ArkTS | `PixelMapDrawableDescriptor` 新增 `constructor(src: ResourceStr)` 重载，参考 `AnimatedDrawableDescriptor` 已有模式 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets` |
| 静态 ANI Bridge | 新增 `_Drawable_CreatePixelMapDrawableByString` / `_Drawable_CreatePixelMapDrawableByResource` 两个 ANI 方法 | ANI 注册和 C++ 实现 |
| 单元测试 | 新增 ResourceStr 构造的测试用例（string 路径 + Resource 引用） | `test/unittest/` 对应位置 |

### 不涉及（Out of Scope）

| 项 | 理由 |
|----|------|
| C API 公开头文件 (`interfaces/native/drawable_descriptor.h`) | C API 仅接受 `OH_PixelmapNativeHandle`，无 ResourceStr 等价物 |
| C API 内部桥接 (`native_node_napi.cpp`, `native_node_ani.cpp`) | PixelMapDrawableDescriptor 走新架构后需在 NAPI Bridge 中显式加入新架构分支 |
| SDK 声明文件修改 | 已声明 @since 26.0.0 |
| 其他 DrawableDescriptor 子类 | `AnimatedDrawableDescriptor` 已有 ResourceStr；`LayeredDrawableDescriptor` / `PictureDrawableDescriptor` 不适用 |
| `DrawableDescriptor` 基类 | 基类构造仅内部使用（@systemapi），不暴露 ResourceStr |

### 验收标准（P0）

- **AC-1**: WHEN 通过 `new PixelMapDrawableDescriptor("/data/storage/image.png")` (string 路径) 构造 THEN `getPixelMap()` 返回从文件加载的有效 PixelMap
- **AC-2**: WHEN 通过 `new PixelMapDrawableDescriptor($r('app.media.icon'))` (Resource 引用) 构造 THEN `getPixelMap()` 返回从资源管理系统加载的有效 PixelMap
- **AC-3**: WHEN 通过 `new PixelMapDrawableDescriptor("data:image/png;base64,...")` (base64) 构造 THEN `getPixelMap()` 返回解码后的有效 PixelMap
- **AC-4**: WHEN 传入无效路径或资源不存在 THEN 构造成功但 `getPixelMap()` 返回 `nullptr`/`undefined`（不抛异常，与已有错误处理一致）
- **AC-5**: WHEN 静态前端调用 `new PixelMapDrawableDescriptor(src: ResourceStr)` THEN 行为与动态一致（string + Resource 均支持）
- **AC-6**: WHEN 已有 `constructor(src?: image.PixelMap)` 路径 THEN 行为不变（向后兼容）

### 复杂度判定

**标准** — 单仓内多文件变更，涉及 NAPI / Core / Static Frontend 三层，但可参考已有 `AnimatedDrawableDescriptor` 模式。

## 受影响子系统与仓库

| 仓库 | 路径 | 影响 |
|------|------|------|
| ace_engine | `interfaces/inner_api/drawable_descriptor/` | NAPI 桥接 |
| ace_engine | `frameworks/core/drawable/pixel_map_drawable_descriptor.*` | 核心实现 |
| ace_engine | `frameworks/core/interfaces/drawable/drawable_api.h` | modifier 函数表 |
| ace_engine | `interfaces/native/node/native_node_napi.cpp` | C API NAPI Bridge（新架构分支） |
| ace_engine | `frameworks/bridge/arkts_frontend/koala_projects/` | 静态前端 + ANI |
| ace_engine | `test/unittest/` | 单元测试 |

## 不涉及项确认

| 维度 | 结论 | 理由 |
|------|------|------|
| 无障碍 | N/A | 数据对象 |
| 大字体 | N/A | 无文本 |
| 深色模式 | N/A | 不感知主题 |
| 多窗口/分屏 | N/A | 不感知窗口 |
| 多用户 | N/A | 不涉及用户数据 |
| 版本升级 | 适用 | API 26 新功能，向前兼容 |
| 生态兼容 | 适用 | 新增构造重载，不破坏已有 API |
| 热路径 | N/A | 构造为一次性操作 |

## 基线审批

| 字段 | 值 |
|------|-----|
| 状态 | Baselined |
| 审批人 | Owner (liyujie43) |
| 证据 | 当前会话 Owner 明确批准 |
