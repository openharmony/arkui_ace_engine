# ImageAnimator Context

> 文档版本：v1.0
> 更新时间：2026-07-10
> 来源：`docs/context_registry.json` 主题 `ImageAnimator`

## 定位

ImageAnimator 是 ArkUI 的图片帧动画组件，面向应用侧提供按帧图片序列播放、播放状态控制、循环控制、方向控制、填充模式和动画事件回调等能力。每帧图片最终通过 Image 子节点承载，因此图片源、解码和绘制问题需要同时路由到 Image 组件与 image_provider 子系统确认。

本文档只维护 ImageAnimator 的源码、SDK/API、组件化解析路径、测试和 Spec 路由。具体属性语义、默认值、边界条件和兼容性说明以 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期和播放控制 | `frameworks/core/components_ng/pattern/image_animator/image_animator_pattern.cpp` | ImageAnimator 组件核心行为入口 |
| Pattern 类型声明 | `frameworks/core/components_ng/pattern/image_animator/image_animator_pattern.h` | `ImageAnimatorPattern`、帧缓存、播放状态和回调接口声明 |
| 多线程路径 | `frameworks/core/components_ng/pattern/image_animator/image_animator_pattern_multi_thread.cpp` | 多线程场景下的图片动画处理入口 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/image_animator/image_animator_model_ng.cpp` | 动态前端创建 ImageAnimator 节点和 Image 子节点入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/image_animator/image_animator_model_static.cpp` | 静态前端创建 ImageAnimator 节点和 Image 子节点入口 |
| Model 抽象 | `frameworks/core/components_ng/pattern/image_animator/image_animator_model.h` | ImageAnimator Model 抽象接口声明 |
| 事件中心 | `frameworks/core/components_ng/pattern/image_animator/image_animator_event_hub.h` | onStart、onPause、onRepeat、onCancel、onFinish 回调存储 |
| 组件构建入口 | `frameworks/core/components_ng/pattern/image_animator/BUILD.gn` | 组件化构建目标和 bridge 源文件入口 |
| Image 子节点依赖 | `frameworks/core/components_ng/pattern/image/` | 单帧图片加载、布局和绘制的下游组件入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/image_animator.d.ts` | 动态 ArkTS `ImageAnimatorInterface`、`ImageFrameInfo`、`ImageAnimatorAttribute` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/imageAnimator.static.d.ets` | 静态 ArkTS ImageAnimator 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageAnimatorModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageAnimatorModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK 节点枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_IMAGE_ANIMATOR`、`NODE_IMAGE_ANIMATOR_*`、`NODE_IMAGE_ANIMATOR_EVENT_*` 枚举 |
| CAPI 帧信息工具 | `interfaces/native/node_attributes/image_animator.h` | `ArkUI_ImageAnimatorFrameInfo` 创建、释放和属性访问接口 |

API 检索建议：

- 构造与帧数据：在 SDK 文件中搜索 `ImageAnimatorInterface`、`ImageFrameInfo`、`images`。
- 播放控制属性：在 SDK 文件中搜索 `state`、`duration`、`reverse`、`fixedSize`、`fillMode`、`iterations`、`monitorInvisibleArea`。
- 事件：在 SDK 文件和事件中心中搜索 `onStart`、`onPause`、`onRepeat`、`onCancel`、`onFinish`。
- NDK 帧数据：在 `interfaces/native/node_attributes/image_animator.h` 中搜索 `ArkUI_ImageAnimatorFrameInfo`。

### API 解析实现路径

ImageAnimator 已完成组件化改造。动态模块注册名为 `ImageAnimator`，模块名为 `imageanimator`；组件化构建由 `image_animator_pattern_ng` 目标承载，独立组件模块按组件化规则输出 `libarkui_imageanimator.z.so`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/image_animator/bridge/arkts_native_image_animator_bridge.cpp` | 统一处理 ArkTS 侧 ImageAnimator 参数解析和事件注册 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/image_animator/bridge/image_animator_dynamic_modifier.cpp` | 动态属性和事件写入路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/image_animator/bridge/image_animator_static_modifier.cpp` | 静态编译属性写入路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/image_animator/bridge/image_animator_dynamic_module.cpp` | `DynamicModule` 派生模块入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/image_animator_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到 ImageAnimator 动态模块 |
| C API 节点枚举 | `interfaces/native/native_node.h` | ImageAnimator 节点属性和事件枚举入口 |
| C API 帧信息 | `interfaces/native/node_attributes/image_animator.h` | 字符串源和 `ArkUI_DrawableDescriptor` 帧源转换入口 |

组件化状态验证入口：

- 动态模块注册：`adapter/ohos/osal/dynamic_module_helper.cpp`
- 组件 bridge 目录：`frameworks/core/components_ng/pattern/image_animator/bridge/`
- 旧 JSView 路径：`frameworks/bridge/declarative_frontend/jsview/js_image_animator.cpp` 在当前代码中未找到。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 单帧图片组件 | `frameworks/core/components_ng/pattern/image_animator/image_animator_model_ng.cpp`、`frameworks/core/components_ng/pattern/image_animator/image_animator_model_static.cpp` | `foundation/arkui/ace_engine` | `frameworks/core/components_ng/pattern/image/` | ImageAnimator 创建 Image 子节点承载每帧图片 |
| 图片解码框架（经 Image 子节点） | `frameworks/core/components_ng/pattern/image/`、`frameworks/core/components_ng/image_provider/` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h`、`interfaces/innerkits/include/image_source.h` | 帧图片源最终进入 Image/image_provider 加载和解码链路 |
| 图形绘制（经 Image 子节点） | `frameworks/core/components_ng/render/adapter/` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/*` | 帧图片绘制和 CanvasImage 适配入口 |
| DrawableDescriptor 帧源 | `interfaces/native/node_attributes/image_animator.h` | `foundation/arkui/ace_engine` | `interfaces/native/drawable_descriptor.h` | NDK 侧可从 `ArkUI_DrawableDescriptor` 创建帧信息 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern 单元测试 | `test/unittest/core/pattern/image_animator/` | Pattern、播放控制、事件、帧切换和 ControlledAnimator 回归 |
| C API Modifier 测试 | `test/unittest/capi/modifiers/image_animator_modifier_test.cpp` | ImageAnimator C API 属性和事件 modifier 覆盖 |
| 生成 Modifier 测试 | `test/unittest/capi/modifiers/generated/image_animator_modifier_test.cpp` | 生成侧 ImageAnimator modifier 回归 |
| 组件样例/组件测试 | `test/component_test/test_cases/components/image_video_and_media/entry/src/main/ets/pages/image_animator/` | ArkTS 页面级样例和手工验证入口 |

### 相关 Spec

ImageAnimator 功能域：`specs/05-ui-components/08-image-components/02-image-animator/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 帧数据和缓存 | `Feat-01-image-animator-frame-data-cache-spec.md` |
| Feat-02 | 播放控制 | `Feat-02-image-animator-playback-control-spec.md` |
| Feat-03 | 事件和接口 | `Feat-03-image-animator-events-interfaces-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ImageAnimator 节点没有创建或没有 Image 子节点 | Dynamic/Static Model、组件构建入口、`IMAGE_ANIMATOR_ETS_TAG` 和 Image 子节点创建路径 |
| 帧图片不显示或只显示第一帧 | `ImageAnimatorPattern` 帧切换逻辑、Image 子节点 `ImageSourceInfo` 写入、Image KB 的加载链路 |
| 播放状态不符合预期 | SDK `state` 声明、Pattern 播放控制入口、ControlledAnimator 单元测试 |
| duration、iterations、reverse、fillMode 不生效 | SDK 属性声明、bridge 参数解析、dynamic/static modifier、Pattern 属性落点 |
| onStart/onPause/onRepeat/onCancel/onFinish 不触发 | SDK 事件声明、bridge 事件注册、`ImageAnimatorEventHub`、C API 事件枚举 |
| NDK 帧数据或 DrawableDescriptor 帧源异常 | `interfaces/native/node_attributes/image_animator.h`、`interfaces/native/drawable_descriptor.h`、DrawableDescriptor KB |
| 帧图片加载或绘制异常 | Image KB、`frameworks/core/components_ng/pattern/image/`、`frameworks/core/components_ng/image_provider/` |

## 调试入口

- 创建链路：从 Dynamic/Static Model 确认 ImageAnimator 节点和 Image 子节点是否建立。
- 属性解析链路：从 `bridge/arkts_native_image_animator_bridge.cpp` 或 dynamic/static modifier 确认属性参数是否落到 Pattern。
- 播放链路：从 `ImageAnimatorPattern` 播放状态、帧索引和 ControlledAnimator 用例定位。
- 图片链路：从 Image 子节点的 ImageSourceInfo 写入进入 Image KB 所列加载、布局和绘制入口。
- C API 链路：从 `interfaces/native/native_node.h` 的 `NODE_IMAGE_ANIMATOR_*` 和 `frameworks/core/interfaces/native/node/image_animator_modifier.cpp` 的动态模块转发入口定位。
- 回归验证：优先运行 `test/unittest/core/pattern/image_animator/` 和 C API modifier 定向用例。

## 相关主题

- `Image`：`docs/kb/components/media/image.md`
- `DrawableDescriptor`：`docs/kb/capabilities/drawable_descriptor.md`
- 图片加载机制（通用能力）：`specs/04-common-capability/01-image-loading/01-image-loading-mechanism/`
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`
