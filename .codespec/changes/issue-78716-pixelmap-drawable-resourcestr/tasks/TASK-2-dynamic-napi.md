# TASK-2: 动态 NAPI — PixelMapConstructor 重写 + GetPixelMap 扩展 + CreatPixelMapDrawable 重写

| 字段 | 值 |
|------|-----|
| Task ID | TASK-2 |
| 目标 | `PixelMapConstructor` 走新架构，新增 string/Resource 分支；`GetPixelMap` 扩展；`CreatPixelMapDrawable` 重写 |
| 依赖 | TASK-1 |
| 子 profile | arkui/sdk-api |

## 受影响文件

| 文件 | 变更 | 行号 |
|------|------|------|
| `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp` | 4 处变更 | 85, 459-478, 706, 1513-1569 |

## AC 覆盖

- AC-1.1 ~ AC-1.4（string 路径构造）
- AC-2.1 ~ AC-2.2（Resource 引用构造）
- AC-4.1 ~ AC-4.2（向后兼容）

## 实现要点

**1. `PIXELMAP_TYPE` 常量（line 85）**：`constexpr uint32_t PIXELMAP_TYPE = 3;`，与核心 `DrawableType::PIXELMAP` 一致。

**2. `PixelMapConstructor` 重写（line 1513-1569）**：
- 使用 `modifier->createDrawableDescriptorByType(PIXELMAP_TYPE)` 创建（新架构）
- 三分支处理参数：
  - `napi_string` → `GetStringFromNapiValue` → `modifier->setPixelMapPath`
  - `napi_object` → `Media::PixelMapNapi::GetPixelMap` 成功 → `modifier->setPixelMapByPixelMap`
  - `napi_object` → `GetPixelMap` 失败 → `ParseResourceObject` → `modifier->setPixelMapResource`
- `napi_wrap` 使用 `NewDestructor`（ref-count）+ `increaseRef`

**3. `GetPixelMap` 扩展（line 706）**：`PixelMapDrawableDescriptor` 加入 modifier 分支：
```cpp
if (type == "AnimatedDrawableDescriptor" || type == "PixelMapDrawableDescriptor")
```

**4. `CreatPixelMapDrawable` 重写（line 459-478）**：用于静态→动态 Transfer。改为 `NewDestructor` + `modifier->increaseRef(native)`，与 `CreatAnimatedDrawable` 一致。

## 验证命令

```bash
./build.sh --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```
