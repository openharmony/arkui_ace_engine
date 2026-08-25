# 审查记录

> FuncID: 04-01-03 | FeatID: Feat-02 | 变更 ID: issue-78716-pixelmap-drawable-resourcestr

## Spec 符合性审查

| AC ID | 状态 | 证据 |
|-------|------|------|
| AC-1.1 (string路径构造) | 已实现 | NAPI: `napi_string` → `setPixelMapPath`; ANI: `_Drawable_CreatePixelMapDrawableByString`; ArkTS: `src instanceof string` 分支 |
| AC-1.2 (base64构造) | 已实现 | `DrawableDescriptorInfo` 解析 base64 → `DrawableDescriptorLoader` → `rawData_` → `CreatePixelMap` 懒解码 |
| AC-1.3 (无效路径) | 已实现 | `setPixelMapPath` 仅当加载有效时设置 `rawData_`；无效时保持空，`getPixelMap()` 返回 null |
| AC-2.1 (Resource引用构造) | 已实现 | NAPI: `ParseResourceObject` → `setPixelMapResource`; ANI: `SystemOps.createResourceObject` → `setPixelMapResource`; ArkTS: `src instanceof Resource` 分支 |
| AC-2.2 (无效Resource) | 已实现 | 加载失败不抛异常，`getPixelMap()` 返回 null |
| AC-3.1 (静态string) | 已实现 | ArkTS → ANI `ByString` → modifier |
| AC-3.2 (静态Resource) | 已实现 | ArkTS → `SystemOps.createResourceObject` → ANI `ByResource` → modifier |
| AC-4.1 (PixelMap路径不变) | 已实现 | `napi_object` + `GetPixelMap` 成功 → `setPixelMapByPixelMap` |
| AC-4.2 (无参构造不变) | 已实现 | `argc==0` → 空描述符 |

**结论：通过** — 10 条 AC 全部实现，无超范围变更。

## 代码质量审查

| 检查项 | 状态 | 说明 |
|--------|------|------|
| 遵循已有模式 | ✓ | 参考 `AnimatedConstructor` 三分支模式（string/PixelMap/Resource） |
| PixelMapDrawableDescriptor 不接受数组 | ✓ | SDK 签名不含数组，无冗余 isArray 判断 |
| 走新架构 | ✓ | `modifier->createDrawableDescriptorByType(PIXELMAP)` + `NewDestructor` |
| C API Bridge 新架构分支 | ✓ | `native_node_napi.cpp` 显式区分新老架构类型 |
| Transfer 路径类型正确 | ✓ | `drawable_module.cpp` 的 `CreateDrawableByNapiType` PIXELMAP 改用 `modifier->getPixelMap()` |
| 动静态一致 | ✓ | string/Resource 分支逻辑对称 |

## 变更文件清单

| 文件 | 变更 |
|------|------|
| `frameworks/core/interfaces/drawable/drawable_api.h` | +2 函数指针 |
| `frameworks/core/interfaces/native/drawable/drawable_modifier.cpp` | +include + 2 函数实现 + 函数表注册 |
| `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp` | +PIXELMAP_TYPE + PixelMapConstructor 重写（三分支） + GetPixelMap 扩展 + CreatPixelMapDrawable 重写 |
| `interfaces/native/node/native_node_napi.cpp` | PixelMapDrawableDescriptor 加入新架构分支 |
| `frameworks/bridge/.../drawable_module.h` | +2 声明 |
| `frameworks/bridge/.../drawable_module.cpp` | +2 ANI 函数 + Transfer 路径 PIXELMAP 修正 |
| `frameworks/bridge/.../module.cpp` | +2 ANI 注册 |
| `frameworks/bridge/.../ArkUIAniModule.ts` | +2 native 声明 |
| `frameworks/bridge/.../drawableDescriptor.ets` | +constructor(ResourceStr) |

## C API 桥接验证

| 文件 | 结论 | 说明 |
|------|------|------|
| `native_node_napi.cpp:305` | **已修复** | `PixelMapDrawableDescriptor` 加入 `AnimatedDrawableDescriptor` 并列的新架构分支 |
| `native_node_ani.cpp:343` | **无需修改** | ANI bridge 通过 `nativeObj` (ani_long↔void*) 传递，类型透明 |
| `drawable_descriptor.cpp` | **无需修改** | 通过 `NodeModel::*` (void*) 间接操作 |
| `native_drawable_descriptor.cpp` | **无需修改** | Transfer 路径已在 `CreatPixelMapDrawable` 重写 |
| `drawable_module.cpp:698` | **已修复** | `CreateDrawableByNapiType` PIXELMAP: `Napi::DrawableDescriptor*` → `modifier->getPixelMap()` |

## 编译验证

js_drawable_descriptor.cpp 含 13 个预存错误（PictureDrawableDescriptor API 26 未完成集成）。本变更未引入新编译错误。

## 回退分析

git log 显示有 `Revert "feature: support resource string for pixelmap drawable descriptor"` commit。本实现差异：
- 走新架构（`Ace::PixelMapDrawableDescriptor` + modifier），非旧 `Napi::DrawableDescriptor`
- 复用 `DrawableDescriptorInfo` + `DrawableDescriptorLoader` 基础设施
- 参考已验证的 `AnimatedDrawableDescriptor` ResourceStr 模式
- C API 桥接层完整覆盖（新架构分支 + Transfer 路径修正）
- 无冗余 isArray 判断（SDK 签名不含数组）
