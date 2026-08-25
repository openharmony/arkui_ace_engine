# TASK-1: 核心层 — drawable_api 扩展 + modifier 实现

| 字段 | 值 |
|------|-----|
| Task ID | TASK-1 |
| 目标 | `ArkUIDrawableModifier` 函数表新增 `setPixelMapPath` / `setPixelMapResource`，在 modifier 中实现加载逻辑 |
| 依赖 | 无 |
| 子 profile | arkui/sdk-api |

## 受影响文件

| 文件 | 变更 | 行号 |
|------|------|------|
| `frameworks/core/interfaces/drawable/drawable_api.h` | +2 函数指针 | 35-36 |
| `frameworks/core/interfaces/native/drawable/drawable_modifier.cpp` | +include + 2 函数实现 + 函数表注册 | 116-142, 567-568 |

## AC 覆盖

- AC-1.1 ~ AC-1.4（string 路径构造）
- AC-2.1 ~ AC-2.2（Resource 引用构造）

## 实现要点

**`setPixelMapPath(void*, const char*)`**：通过 `DrawableDescriptorInfo(path)` 解析 src 类型（FILE/BASE64）→ `DrawableDescriptorLoader::LoadData(info)` → `MediaData` → `PixelMapDrawableDescriptor::SetRawData(data, len)`。加载失败（路径无效/base64 损坏）时 `LoadData` 返回空 `MediaData`，`rawData_` 保持空。

**`setPixelMapResource(void*, void*)`**：通过 `DrawableDescriptorInfo(resourceRef)` 解析 RESOURCE 类型 → 同上加载流程。

**函数表注册**：在 `GetArkUIDrawableDescriptor()` 的 `impl` 初始化列表中追加 `.setPixelMapPath` / `.setPixelMapResource`。

**include**：新增 `#include "core/drawable/drawable_descriptor_loader.h"`（`drawable_descriptor_info.h` 由其间接包含）。

## 验证命令

```bash
./build.sh --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```
