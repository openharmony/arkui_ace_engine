# DrawableDescriptor Context

> 文档版本：v1.0
> 更新时间：2026-07-10
> 来源：`docs/context_registry.json` 主题 `DrawableDescriptor`

## 定位

DrawableDescriptor 是 ArkUI 图片加载相关的通用能力，不是 UI 组件。它为应用和 Native 侧提供可传递的图片资源描述对象，覆盖基础 DrawableDescriptor、LayeredDrawableDescriptor、PixelMapDrawableDescriptor、AnimatedDrawableDescriptor 和 PictureDrawableDescriptor 等类型，并被 Image、ImageAnimator 帧信息、NDK DrawableDescriptor 互操作等路径引用。

本文档只维护 DrawableDescriptor 的能力入口、SDK/API、Bridge/C API、外部依赖、测试和 Spec 路由。具体构造参数、释放语义、错误码、异步加载行为和 Picture/HDR 细节以 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ACE Core 基类 | `frameworks/core/drawable/drawable_descriptor.h`、`frameworks/core/drawable/drawable_descriptor.cpp` | DrawableDescriptor 基类、加载结果、PixelMap 访问和回调入口 |
| 分层 Drawable | `frameworks/core/drawable/layered_drawable_descriptor.h`、`frameworks/core/drawable/layered_drawable_descriptor.cpp` | 前景、背景、mask 合成和 blend mode 入口 |
| PixelMap Drawable | `frameworks/core/drawable/pixel_map_drawable_descriptor.h`、`frameworks/core/drawable/pixel_map_drawable_descriptor.cpp` | PixelMap 或资源数据转 DrawableDescriptor 入口 |
| 动画 Drawable | `frameworks/core/drawable/animated_drawable_descriptor.h`、`frameworks/core/drawable/animated_drawable_descriptor.cpp` | 动画帧、控制器和 ImageSource 映射入口 |
| Picture Drawable | `frameworks/core/drawable/picture_drawable_descriptor.h`、`frameworks/core/drawable/picture_drawable_descriptor.cpp` | Picture、HDR/FOV 合成和重绘相关入口 |
| 描述信息 | `frameworks/core/drawable/drawable_descriptor_info.h`、`frameworks/core/drawable/drawable_descriptor_info.cpp` | 字符串、文件、Base64、ResourceObject 类型解析入口 |
| 数据加载器 | `frameworks/core/drawable/drawable_descriptor_loader.h`、`frameworks/core/drawable/drawable_descriptor_loader.cpp` | 文件、Base64 和资源数据加载入口 |
| Inner API 实现 | `interfaces/inner_api/drawable_descriptor/` | NAPI 模块、旧 inner API 和资源管理对接入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts` | `@ohos.arkui.drawableDescriptor` 动态声明 |
| Static SDK API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets` | 静态 ArkTS DrawableDescriptor 声明 |
| Static ArkTS 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets` | 静态 ArkTS 侧类实现和 Native 调用入口 |
| NDK C API | `interfaces/native/drawable_descriptor.h` | `ArkUI_DrawableDescriptor`、动画控制器和 Native 创建/释放接口 |
| NAPI 互操作 | `interfaces/native/native_node_napi.h`、`interfaces/native/node/native_node_napi.cpp` | ArkTS DrawableDescriptor 到 Native 侧结构的 NAPI 获取入口 |
| ANI 互操作 | `interfaces/native/native_node_ani.h`、`interfaces/native/node/native_node_ani.cpp` | ArkTS 静态运行时对象到 Native 侧结构的 ANI 获取入口 |
| ImageAnimator 帧源 | `interfaces/native/node_attributes/image_animator.h` | 从 `ArkUI_DrawableDescriptor` 创建 ImageAnimator 帧信息的入口 |

API 检索建议：

- SDK 类型：在 SDK 文件中搜索 `DrawableDescriptor`、`LayeredDrawableDescriptor`、`PixelMapDrawableDescriptor`、`AnimatedDrawableDescriptor`、`PictureDrawableDescriptor`。
- 生命周期：在 SDK 文件和 Native 头文件中搜索 `loadSync`、`load`、`release`、`isReleased`、`redraw`。
- Native 互操作：在 `interfaces/native/` 中搜索 `ArkUI_DrawableDescriptor`、`GetDrawableDescriptorFromNapiValue`、`GetDrawableDescriptorFromAniValue`。

### Bridge / 解析入口

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic NAPI 模块 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp`、`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` | `@ohos.arkui.drawableDescriptor` 动态模块类和 NAPI 方法绑定入口 |
| Inner API 实现 | `interfaces/inner_api/drawable_descriptor/drawable_descriptor.cpp`、`interfaces/inner_api/drawable_descriptor/drawable_descriptor.h` | Inner API 层 DrawableDescriptor 类型、资源解析和 PixelMap 合成入口 |
| Inner API Bridge | `interfaces/inner_api/drawable_descriptor/drawable_bridge.cpp`、`interfaces/inner_api/drawable_descriptor/drawable_bridge.h` | 资源管理器和外部 drawable API 桥接入口 |
| Static ArkTS 类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets` | Static ArkTS 侧 DrawableDescriptor 类和 Native 方法调用入口 |
| Native Drawable 实现 | `interfaces/native/node/drawable_descriptor.cpp`、`interfaces/native/node/native_drawable_descriptor.cpp`、`interfaces/native/node/native_drawable_descriptor.h` | NDK DrawableDescriptor 创建、释放、查询和动画控制入口 |
| NAPI/ANI 提取 | `interfaces/native/node/native_node_napi.cpp`、`interfaces/native/node/native_node_ani.cpp` | 从 ArkTS 对象或 Resource 对象提取 `ArkUI_DrawableDescriptor` |

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图片解码与 PixelMap | `frameworks/core/drawable/pixel_map_drawable_descriptor.cpp`、`frameworks/core/drawable/animated_drawable_descriptor.h`、`interfaces/inner_api/drawable_descriptor/drawable_descriptor.cpp` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h`、`interfaces/innerkits/include/image_source.h`、`interfaces/kits/native/include/pixelmap_native.h` | PixelMap、ImageSource 和 Native PixelMap 互操作入口 |
| 图形合成 | `frameworks/core/drawable/layered_drawable_descriptor.cpp`、`interfaces/inner_api/drawable_descriptor/drawable_descriptor.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/*` | RSBitmap、RSCanvas、RSBrush、RSImage 和 BlendMode 合成入口 |
| 资源管理 | `frameworks/core/drawable/drawable_descriptor_loader.cpp`、`interfaces/inner_api/drawable_descriptor/drawable_bridge.cpp` | `base/global/resource_management` | `interfaces/inner_api/resource_manager/` | ResourceObject、ResourceManager 和资源数据读取入口 |
| Picture / HDR 合成 | `frameworks/core/drawable/picture_drawable_descriptor.h`、`frameworks/core/drawable/picture_drawable_descriptor.cpp` | `foundation/arkui/ace_engine` | `base/image/picture.h`、`base/image/contrast_enhancer_image.h` | PictureDrawableDescriptor 通过 ACE image 抽象进入 Picture/HDR/FOV 路径 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Core 单元测试 | `test/unittest/frameworks/core/drawable/drawable_descriptor_test.cpp` | ACE Core DrawableDescriptor 类型和加载能力回归 |
| Interfaces 单元测试 | `test/unittest/interfaces/drawable_descriptor_test.cpp`、`test/unittest/interfaces/drawable_descriptor_extended_test.cpp` | Native/接口层基础和扩展行为回归 |
| JS DrawableDescriptor 测试 | `test/unittest/interfaces/js_drawable_descriptor_test.cpp`、`test/unittest/core/interfaces/js_drawable_descriptor_extended_test.cpp` | JS/NAPI 暴露能力回归 |
| NAPI 子类型测试 | `test/unittest/interfaces/napi/animated_drawable_descriptor_test.cpp`、`test/unittest/interfaces/napi/layered_drawable_descriptor_test.cpp`、`test/unittest/interfaces/napi/pixelmap_drawable_descriptor_test.cpp` | Animated、Layered、PixelMap 子类型回归 |
| NAPI 工具测试 | `test/unittest/interfaces/napi/drawable_descriptor_utils_test.cpp`、`test/unittest/interfaces/napi/js_drawable_descriptor_extended_test.cpp` | 工具函数和扩展路径回归 |

### 相关 Spec

DrawableDescriptor 功能域：`specs/04-common-capability/01-image-loading/03-drawable-descriptor/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | DrawableDescriptor 能力 | `Feat-01-drawable-descriptor-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ArkTS DrawableDescriptor 无法传入 Native | NAPI/ANI 提取入口、`interfaces/native/drawable_descriptor.h`、Native 侧释放状态 |
| getPixelMap/load/loadSync 行为异常 | SDK 声明、ACE Core 基类、PixelMap Drawable、Inner API 实现 |
| LayeredDrawableDescriptor 合成结果异常 | Layered Drawable Core 实现、Inner API layered 实现、graphic_2d 合成入口 |
| AnimatedDrawableDescriptor 在 Image 中播放异常 | Animated Drawable Core 实现、Image KB、ImageAnimator KB、SDK 中 AnimatedDrawableDescriptor 约束 |
| PictureDrawableDescriptor 重绘或 HDR 路径异常 | Picture Drawable Core 实现、Static ArkTS 类、Picture/HDR 外部依赖入口 |
| ResourceStr 或 ResourceObject 加载失败 | DrawableDescriptorInfo、DrawableDescriptorLoader、Inner API resource bridge |
| release/isReleased 后仍被访问 | SDK 声明、NAPI/ANI 提取入口、Native Drawable 实现和相关接口测试 |

## 调试入口

- SDK 行为：先从 `@ohos.arkui.drawableDescriptor*.d.*` 确认公开类型、方法和异常约束。
- Dynamic NAPI 链路：从 `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.*` 进入构造和方法绑定，再路由到 inner API 类型实现。
- Static ArkTS 链路：从 `@ohos.arkui.drawableDescriptor.ets` 确认 ArkTS 类、Native 调用和对象字段。
- Native 互操作：从 NAPI/ANI 提取函数确认 ArkTS 对象如何映射到 `ArkUI_DrawableDescriptor`。
- 资源加载：从 `DrawableDescriptorInfo` 和 `DrawableDescriptorLoader` 确认字符串、文件、Base64、ResourceObject 的类型解析和数据读取。
- 图形合成：从 layered/picture descriptor 的 Core 实现进入 PixelMap、RSCanvas/RSBitmap 或 Picture/HDR 依赖。
- 回归验证：优先运行 `test/unittest/frameworks/core/drawable/`、`test/unittest/interfaces/` 和 `test/unittest/interfaces/napi/` 中 DrawableDescriptor 相关用例。

## 相关主题

- `Image`：`docs/kb/components/media/image.md`
- `ImageAnimator`：`docs/kb/components/media/image_animator.md`
- 图片加载机制（通用能力）：`specs/04-common-capability/01-image-loading/01-image-loading-mechanism/`
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`
