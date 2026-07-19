# TASK-3: 静态 ANI — 新方法 + 注册

| 字段 | 值 |
|------|-----|
| Task ID | TASK-3 |
| 目标 | ANI 桥接层新增 `DrawableCreatePixelMapDrawableByString` / `DrawableCreatePixelMapDrawableByResource`，并在 module.cpp + ArkUIAniModule.ts 注册 |
| 依赖 | TASK-1 |
| 子 profile | arkui/sdk-api |

## 受影响文件

| 文件 | 变更 | 行号 |
|------|------|------|
| `frameworks/bridge/.../drawable/drawable_module.h` | +2 函数声明 | 32-35 |
| `frameworks/bridge/.../drawable/drawable_module.cpp` | +2 函数实现 | 407-440 |
| `frameworks/bridge/.../module.cpp` | +2 ANI_CALL 注册 | 745-750 |
| `frameworks/bridge/.../ArkUIAniModule.ts` | +2 native static 声明 | 270-273 |

## AC 覆盖

- AC-3.1 ~ AC-3.2（静态前端 string/Resource）

## 实现要点

**`DrawableCreatePixelMapDrawableByString`**：`modifier->createDrawableDescriptorByType(PIXELMAP)` → `increaseRef` → 设置 `nativeObj` → `modifier->setPixelMapPath(drawable, src)`。

**`DrawableCreatePixelMapDrawableByResource`**：同上但调用 `modifier->setPixelMapResource(drawable, reinterpret_cast<void*>(resourceObjectKPointer))`。

**注册**：三处同步——`module.cpp` 的 `ani_native_function` 表、`ArkUIAniModule.ts` 的 `native static` 声明、`drawable_module.h` 的 C++ 声明。

## 验证命令

```bash
./build.sh --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```
