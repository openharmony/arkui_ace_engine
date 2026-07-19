# TASK-5: C API 桥接层验证与修复

| 字段 | 值 |
|------|-----|
| Task ID | TASK-5 |
| 目标 | C API Bridge 全路径验证，修复 PixelMapDrawableDescriptor 新架构适配 |
| 依赖 | TASK-2, TASK-3 |
| 子 profile | arkui/capi |

## 受影响文件

| 文件 | 变更 | 行号 |
|------|------|------|
| `interfaces/native/node/native_node_napi.cpp` | `PixelMapDrawableDescriptor` 加入新架构分支 | 305 |
| `frameworks/bridge/.../drawable/drawable_module.cpp` | `CreateDrawableByNapiType` PIXELMAP 分支转型修正 | 698-706 |

## AC 覆盖

- AC-4.1 ~ AC-4.2（向后兼容 — C API Bridge 不破坏已有路径）
- AC-3.1 ~ AC-3.2（静态→动态 Transfer 路径正确）

## 实现要点

**1. NAPI Bridge 新架构分支**（`native_node_napi.cpp:305`）：

`OH_ArkUI_GetDrawableDescriptorFromNapiValue` 通过 typename 区分新老架构。将 `PixelMapDrawableDescriptor` 加入 Animated 并列的新架构分支：
```cpp
if (typenameStr == "AnimatedDrawableDescriptor" || typenameStr == "PixelMapDrawableDescriptor") {
    IncreaseRefDrawable(objectNapi);
    drawable->newDrawableDescriptor = objectNapi;
}
```

> `IncreaseRefDrawable` → dlsym → `OHOS_ACE_IncreaseRefDrawableDescriptor`（`drawable_descriptor.cpp:452`）→ `reinterpret_cast<Ace::DrawableDescriptor*>(object)->IncRefCount()`。类型链路正确。

**2. Static→Dynamic Transfer 路径**（`drawable_module.cpp:698`）：

`CreateDrawableByNapiType` 的 PIXELMAP 分支原先 `static_cast<Napi::DrawableDescriptor*>(unwrapResult)->GetPixelMap()`。PixelMapDrawableDescriptor 走新架构后 `unwrapResult` 是 `Ace::PixelMapDrawableDescriptor*`，转型错误。改为：
```cpp
std::shared_ptr<Media::PixelMap> pixmap;
modifier->getPixelMap(unwrapResult, &pixmap);
if (pixmap) {
    retValue = CreatePixelMapDrawableByPixelMap(env, pixmap);
}
```

**3. 已验证无需修改的文件**：
- `native_node_ani.cpp:343` — ANI bridge 通过 `nativeObj`（ani_long↔void*）传递，类型透明
- `drawable_descriptor.cpp` — 通过 `NodeModel::*`（void*）间接操作
- `native_drawable_descriptor.cpp:22` — Transfer 路径已由 TASK-2 的 `CreatPixelMapDrawable` 重写覆盖

## 验证命令

```bash
./build.sh --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```
