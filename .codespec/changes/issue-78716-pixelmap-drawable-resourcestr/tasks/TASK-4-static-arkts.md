# TASK-4: 静态 ArkTS — PixelMapDrawableDescriptor ResourceStr 构造重载

| 字段 | 值 |
|------|-----|
| Task ID | TASK-4 |
| 目标 | `drawableDescriptor.ets` 中 `PixelMapDrawableDescriptor` 新增 `constructor(src: ResourceStr)` |
| 依赖 | TASK-3 |
| 子 profile | arkui/sdk-api |

## 受影响文件

| 文件 | 变更 | 行号 |
|------|------|------|
| `frameworks/bridge/.../drawableDescriptor.ets` | +constructor(ResourceStr) | 149-160 |

## AC 覆盖

- AC-3.1 ~ AC-3.2（静态前端 string/Resource）

## 实现要点

```typescript
constructor(src: ResourceStr) {
    super()
    if (src instanceof string) {
        ArkUIAniModule._Drawable_CreatePixelMapDrawableByString(this, src as string)
    } else if (src instanceof Resource) {
        let resourceObjectKPointer = SystemOps.createResourceObject(src as Resource)
        ArkUIAniModule._Drawable_CreatePixelMapDrawableByResource(this, resourceObjectKPointer)
    }
    let finalization = new NativeDestructor(this.nativeObj)
    this.finalization = finalization
    finalizerRegister(this, finalization)
}
```

> `ResourceStr` / `Resource` / `SystemOps` 已在文件头部 import。

## 验证命令

```bash
./build.sh --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```
