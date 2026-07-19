# Video Context

> 文档版本：v1.2
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `Video`

## 定位

Video 是 ArkUI 的视频播放组件，面向应用侧提供视频源加载、播放/暂停/停止/Seek、静音、自动播放、循环、内置控制条、全屏切换、播放速率、Poster/预览图、AI 图像分析等能力。支持网络视频、本地文件、应用资源等多种数据源。

Video 组件采用 Pattern + Model + Controller + 状态机 架构：`VideoPattern`（及全屏派生的 `VideoFullScreenPattern`、异步版本 `VideoStateMachinePattern`）承载核心行为；`VideoControllerV2`/`VideoController` 提供命令式控制入口；`VideoStateManager` 承载播放状态转换；底层通过 `MediaPlayer` + `RenderSurface` 抽象接入 OHOS `player_framework` 和 `graphic_2d`。Video 已纳入动态组件模块加载，`DynamicModuleHelper` 将组件名 `Video` 映射到 `video` 动态模块，桥接实现集中在 `frameworks/core/components_ng/pattern/video/bridge/`。

本文档用于快速定位 Video 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、播放控制、事件分发 | `frameworks/core/components_ng/pattern/video/video_pattern.cpp` | Video 核心行为实现入口 |
| Pattern 类型和接口声明 | `frameworks/core/components_ng/pattern/video/video_pattern.h` | `VideoPattern` 类型、MediaPlayer/RenderSurface 三件套、控制条构建、全屏管理接口 |
| OHOS 平台专有 Pattern 实现 | `frameworks/core/components_ng/pattern/video/video_pattern_ohos.cpp` | Video Pattern 的 OHOS 平台分支实现 |
| Pattern 通用工具 | `frameworks/core/components_ng/pattern/video/video_pattern_util.h` | Video Pattern 辅助工具 |
| 全屏 Pattern | `frameworks/core/components_ng/pattern/video/video_full_screen_pattern.*` | 全屏子节点行为 |
| 全屏 Node | `frameworks/core/components_ng/pattern/video/video_full_screen_node.*` | 全屏 FrameNode 挂载到 root overlay |
| 异步控制 Pattern（状态机） | `frameworks/core/components_ng/pattern/video/video_state_machine_pattern.*` | `VideoControllerAsync` 背后的 Pattern 主体 |
| 全屏 · 状态机 Pattern | `frameworks/core/components_ng/pattern/video/video_state_machine_full_screen_pattern.*` | 异步版本全屏派生 Pattern |
| 状态管理器 | `frameworks/core/components_ng/pattern/video/video_state_manager.*` | `VideoPlaybackState` / `VideoPlaybackCommand` / `VideoStateMachine` 定义 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/video/video_model_ng.cpp` | 动态前端 Video 创建和属性写入入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/video/video_model_static.cpp` | 静态前端 Video 属性写入入口 |
| Model 抽象 | `frameworks/core/components_ng/pattern/video/video_model.h` | Video Model 抽象接口声明 |
| 布局算法 | `frameworks/core/components_ng/pattern/video/video_layout_algorithm.cpp` | 视频显示区域测量、ObjectFit 计算 |
| 布局属性 | `frameworks/core/components_ng/pattern/video/video_layout_property.h` | `VideoStyle` 属性组、ObjectFit 等布局属性声明 |
| 事件中心 | `frameworks/core/components_ng/pattern/video/video_event_hub.h` | onStart/onPause/onFinish/onFullscreenChange/onPrepared/onSeeking/onSeeked/onUpdate/onError/onStop 事件回调存储 |
| Controller v1（同步） | `frameworks/core/components_ng/pattern/video/video_controller_v2.h` | `VideoController` 与 `VideoControllerV2` 类型定义（API 7） |
| Controller v2（异步） | `frameworks/core/components_ng/pattern/video/video_controller_async.*` | 异步控制器实现（API 26） |
| Video Node | `frameworks/core/components_ng/pattern/video/video_node.*` | Video 自定义 FrameNode 结构和子节点管理（控制条 SVG、Slider、时间文本） |
| MediaPlayer 事件回调 | `frameworks/core/components_ng/pattern/video/media_player_callback.h` | Media 层事件到 Video Pattern 的桥接 |
| 无障碍属性 | `frameworks/core/components_ng/pattern/video/video_accessibility_property.*` | 无障碍读屏文案 |
| Video 主题 | `frameworks/core/components_ng/pattern/video/video_theme.h` | 内置控制条的颜色、字号、图标资源 |
| Video 样式与工具 | `frameworks/core/components_ng/pattern/video/video_styles.h`、`video_utils.h` | 属性组 / 工具方法 |
| Video 资源 | `frameworks/core/components_ng/pattern/video/resource/` | 控制条 SVG 图标等内置资源 |
| MediaPlayer 抽象 | `frameworks/core/components_ng/render/media_player.h` | Video 使用的 MediaPlayer 抽象接口 |
| MediaPlayer 适配实现 | `frameworks/core/components_ng/render/adapter/media_player_impl.*` | MediaPlayer 抽象的适配层实现 |
| MediaPlayer 工厂 | `frameworks/core/components_ng/render/media_player_creator.cpp` | `MediaPlayer::Create()` 实例化入口 |
| RenderSurface 抽象 | `frameworks/core/components_ng/render/render_surface.h` | Video 使用的 RenderSurface 抽象 |
| RenderSurface 适配实现 | `frameworks/core/components_ng/render/adapter/render_surface_impl.*` | Surface 到 Rosen SurfaceNode 的绑定 |
| 组件动态模块 | `frameworks/core/components_ng/pattern/video/bridge/video_dynamic_module.*` | `OHOS_ACE_DynamicModule_Create_Video` 和动态/静态 modifier/model 导出 |
| 动态属性解析 | `frameworks/core/components_ng/pattern/video/bridge/video_dynamic_modifier.cpp` | JSView/动态属性侧属性写入入口 |
| ArkTS Bridge | `frameworks/core/components_ng/pattern/video/bridge/arkts_native_video_bridge.cpp` | ArkTS runtime 参数解析和 `VideoBridge::RegisterVideoAttributes` |
| 静态属性解析 | `frameworks/core/components_ng/pattern/video/bridge/video_static_modifier.cpp` | 静态 ArkTS / 生成态 modifier 属性解析 |
| 异步控制器动态 modifier | `frameworks/core/components_ng/pattern/video/bridge/video_controller_async_dynamic_modifier.cpp` | `VideoControllerAsync` 自定义动态 modifier |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/video.d.ts` | 动态 ArkTS `VideoInterface`、`VideoAttribute`、`VideoOptions`、`VideoController` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/video.static.d.ets` | 静态 ArkTS Video 组件与 `VideoControllerAsync` 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/VideoModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/VideoModifier.static.d.ets` | 静态 Modifier 声明 |
| 公开 NDK 节点枚举 | `interfaces/native/native_node.h` | 未定义 `ARKUI_NODE_VIDEO`，不要按公开 `ArkUI_NodeType` 路由 Video |
| 生成态 arkoala/CAPI 接口 | `frameworks/core/interfaces/native/generated/interface/arkoala_api_generated.h` | `GENERATED_ARKUI_VIDEO`、`GENERATED_ArkUIVideoModifier`、`VideoController`/`VideoControllerAsync` accessor 声明 |
| Native modifier / accessor 实现 | `frameworks/core/interfaces/native/node/video_modifier.cpp`、`frameworks/core/interfaces/native/implementation/video_modifier.cpp`、`video_controller_accessor.cpp`、`video_controller_async_accessor.cpp` | 动态模块委托、生成态 modifier 和 controller peer/accessor 实现 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `VideoAttribute` 和具体属性名（如 `muted`、`autoPlay`、`controls`、`loop`、`objectFit`、`surfaceBackgroundColor`）。
- 构造参数：在 SDK 文件中搜索 `VideoOptions`、`VideoInterface` 或 `Video(`。
- 事件：在 SDK 文件中搜索 `onStart`、`onPause`、`onFinish`、`onFullscreenChange`、`onPrepared`、`onSeeking`、`onSeeked`、`onUpdate`、`onError`、`onStop`。
- Controller：在 SDK 文件中搜索 `VideoController`、`VideoControllerAsync`。
- Modifier：在 `VideoModifier*.d.ts` / `VideoModifier*.d.ets` 中确认声明。
- 生成态接口：在 `arkoala_api_generated.h` 中搜索 `GENERATED_ARKUI_VIDEO`、`GENERATED_ArkUIVideoModifier`、`GENERATED_ArkUIVideoControllerAccessor`。

### API 解析实现路径

Video 组件已完成组件动态模块化：`adapter/ohos/osal/dynamic_module_helper.cpp` 中存在 `Video` → `video` 映射，组件桥接目录包含 `video_dynamic_module.*`，运行时通过 `libarkui_video.z.so` 形态加载动态模块。公开 NDK `interfaces/native/native_node.h` 仍没有 `ARKUI_NODE_VIDEO`；需要区分“公开 Native 节点枚举”与“生成态 arkoala/CAPI modifier/accessor”。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **前端 JS/TS 定义** | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arkvideo.ts`、`frameworks/bridge/declarative_frontend/ark_component/dist/ArkVideo.js` | 动态前端 Video 组件类和 ArkComponent/JSView 侧入口 |
| **组件动态模块** | `frameworks/core/components_ng/pattern/video/bridge/video_dynamic_module.cpp` | 导出 `OHOS_ACE_DynamicModule_Create_Video`，提供 dynamic/static/CJ/custom modifier 和 `VideoModelNG` |
| **动态前端入口** | `frameworks/core/components_ng/pattern/video/bridge/video_dynamic_modifier.cpp` | JSView/动态属性侧属性写入入口 |
| **JSView Controller（同步）** | `frameworks/bridge/declarative_frontend/jsview/js_video_controller.cpp` | `VideoController` 命令式接口的 JS 桥 |
| **JSView Controller（异步）** | `frameworks/bridge/declarative_frontend/jsview/js_video_controller_async.cpp` | `VideoControllerAsync` 命令式接口的 JS 桥 |
| **ArkTS Bridge（动态属性 / Modifier / FrameNode 命令式）** | `frameworks/core/components_ng/pattern/video/bridge/arkts_native_video_bridge.cpp` | `VideoBridge::SetXxx()` / `Create()` 解析参数后经 `getVideoModifier()` 写入 `VideoModelNG` |
| **Dynamic Modifier** | `frameworks/core/components_ng/pattern/video/bridge/video_dynamic_modifier.cpp` | `ArkUIVideoModifier` / `CJUIVideoModifier` 动态属性函数表 |
| **Static Modifier** | `frameworks/core/components_ng/pattern/video/bridge/video_static_modifier.cpp` | `GENERATED_ArkUIVideoModifier` 静态属性函数表 |
| **Async Controller Custom Modifier** | `frameworks/core/components_ng/pattern/video/bridge/video_controller_async_dynamic_modifier.cpp` | `VideoControllerAsync` 的 start/pause/stop/reset/seek/fullscreen 自定义函数表 |
| **node_modifier 委托层** | `frameworks/core/interfaces/native/node/video_modifier.cpp` | 通过 `DynamicModuleHelper::GetDynamicModule("Video")` 转发到动态模块 |
| **生成态 modifier 委托层** | `frameworks/core/interfaces/native/implementation/video_modifier.cpp` | 通过动态模块取得 static modifier，供生成态 arkoala/CAPI 测试和 peer 层使用 |
| **ANI Modifier（静态 ArkTS）** | `frameworks/core/interfaces/native/ani/video_ani_modifier.cpp` | 静态 ArkTS 侧 onError 相关桥 |
| **Peer / Accessor（Peer 层）** | `frameworks/core/interfaces/native/implementation/video_controller_peer_impl.cpp`、`video_controller_async_peer_impl.cpp`、`video_controller_accessor.cpp`、`video_controller_async_accessor.cpp` | 静态 ArkTS / 生成态 controller peer 与 accessor 实现 |
| **前端 Modifier（ArkTS 侧）** | `frameworks/bridge/declarative_frontend/ark_modifier/src/video_modifier.ts` | ArkTS `VideoModifier` 类定义 |
| **公开 C API / NDK 节点** | `interfaces/native/native_node.h` | 无 `ARKUI_NODE_VIDEO`，无 `interfaces/native/node/video_native_impl.*` |
| **生成态 arkoala/CAPI** | `frameworks/core/interfaces/native/generated/interface/arkoala_api_generated.h` | 存在 `GENERATED_ARKUI_VIDEO` 和 Video modifier/controller accessor，测试位于 `test/unittest/capi/` |

组件化改造参考：`./组件化重构通用方案.md`。Video 当前已具备 `pattern/video/bridge/` 动态模块入口，后续确认产物或符号时优先检查 `libarkui_video.z.so`、`OHOS_ACE_DynamicModule_Create_Video` 与 `DynamicModuleHelper` 映射。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。以下依赖通过 `#include` / 抽象工厂调用在 Video 源码中确认。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|-------------------------------|------|
| 媒体播放框架 | `frameworks/core/components_ng/render/media_player.h` 抽象 → `frameworks/core/components_ng/render/adapter/media_player_impl.cpp`；`frameworks/core/components_ng/pattern/video/BUILD.gn` | `foundation/multimedia/player_framework` | `interfaces/inner_api/native/player.h`、`media_errors.h`、`player_framework:media_client` | Video 通过 `MediaPlayer` 抽象接入 `Media::Player`，负责解码、音视频同步、Seek、事件回调 |
| 图形渲染 / 合成 | `frameworks/core/components_ng/render/render_surface.h` 抽象 → `frameworks/core/components_ng/render/adapter/render_surface_impl.cpp`；`video_pattern*.cpp` 中的 `renderContextForMediaPlayer_` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_base/include/`、`rosen/modules/render_service_client/` | Video 画面通过 `RenderSurface` / RenderContext 绑定到 Rosen Surface/Texture 参与合成 |
| JS 栈事件上报 | `frameworks/core/components_ng/pattern/video/bridge/arkts_native_video_bridge.cpp`；`frameworks/core/components_ng/pattern/video/BUILD.gn` | `base/hiviewdfx/hiview` | `hiview:libxpower_event_js` | `SUPPORT_JSSTACK` 场景下桥接层引用 `xpower_event_jsvm.h` |
| AI 图像分析 | `frameworks/core/components_ng/pattern/video/video_pattern.cpp`、`video_state_machine_pattern.cpp` → `core/common/ai/image_analyzer_manager.h` | 本仓 `interfaces/inner_api/ace/ai/`，底层由 ImageAnalyzer loader/adapter 接入 | `interfaces/inner_api/ace/ai/image_analyzer.h`、`image_analyzer_interface.h` | AI overlay / 内容分析（Feat-03） |
| UI Session（本仓 inner_api） | `frameworks/core/components_ng/pattern/video/video_pattern.cpp`、`video_state_machine_pattern.cpp`；`frameworks/core/components_ng/pattern/video/BUILD.gn` | `foundation/arkui/ace_engine` | `interfaces/inner_api/ui_session/ui_session_manager.h` | Video 事件与会话状态上报，属于本仓 inner_api 依赖 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/video/` | Pattern、控制器、状态机、属性、资源、事件等 Video 行为回归 |
| 状态机测试组 | `test/unittest/core/pattern/video/video_state_machine_pattern_test*.cpp` | 异步控制器 / 状态机路径专项 |
| 属性测试 | `test/unittest/core/pattern/video/video_property_test_ng.cpp` | 属性写入与 `VideoStyle` 组回归 |
| 资源测试 | `test/unittest/core/pattern/video/video_resource_test_ng.cpp` | 内置控制条资源 / Poster 相关 |
| 控制器（异步）测试 | `test/unittest/core/pattern/video/video_controller_async_test.cpp` | `VideoControllerAsync` 行为回归 |
| 生成态 CAPI modifier 测试 | `test/unittest/capi/modifiers/video_modifier_test.cpp` | `GENERATED_ArkUIVideoModifier`、`GENERATED_ARKUI_VIDEO` 属性与事件回归 |
| 生成态 CAPI controller accessor 测试 | `test/unittest/capi/accessors/video_controller_accessor_test.cpp`、`video_controller_async_accessor_test.cpp` | `VideoController` / `VideoControllerAsync` accessor 回归 |
| 组件样例测试 | `test/component_test/test_cases/components/image_video_and_media/` | Image/Video/Media 组合场景 |
| Spec 功能域 | `specs/05-ui-components/13-platform-components/02-video/` | Video 功能域设计和验收契约 |
| Context registry | `docs/context_registry.json` | Video 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Video 功能域：`specs/05-ui-components/13-platform-components/02-video/`

| Feat | 主题 | 文件 |
|------|------|------|
| Design | 架构设计（补录） | `design.md` |
| Feat-01 | 显示、播放与事件 | `Feat-01-video-display-playback-events-spec.md` |
| Feat-02 | 控制器与全屏 | `Feat-02-video-controller-fullscreen-spec.md` |
| Feat-03 | 高级能力（AI 分析 / Poster / 快捷键） | `Feat-03-video-advanced-capabilities-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 视频不播放 / 黑屏 | `VideoPattern::PrepareMediaPlayer` / `SetSourceForMediaPlayer` 链路、`media_player_impl.cpp` MediaPlayer 创建、Feat-01 |
| autoPlay / muted / loop 不生效 | SDK `VideoAttribute` 属性声明、`video_model_ng.cpp` 属性写入、`video_layout_property.h` |
| onError 不触发或错误码异常 | `video_event_hub.h` FireError、`media_player_callback.h` 错误回调转发、SDK `onError` 签名 |
| 全屏切换异常 | `VideoFullScreenPattern`、`VideoFullScreenNode`、`fullScreenNodeId_` 管理逻辑 |
| 同步 / 异步 Controller 混用 | `video_controller_v2.h`（同步）vs `video_controller_async.*`（异步）、异步版本背后 `VideoStateMachinePattern` |
| 播放状态机异常 | `video_state_manager.*` 的 `VideoPlaybackState` / `Command`、状态机测试组 |
| 控制条 UI 异常（按钮/Slider/时间文本） | `video_node.*` 子节点管理、`video_theme.h` 内置资源、Feat-01 |
| Seek/Speed/Progress 更新异常 | `VideoController`/`VideoControllerAsync` 命令入口、Pattern 内 `OnUpdateTime`/`OnSeeking`/`OnSeeked` 分发 |
| ObjectFit / 显示区域异常 | `video_layout_algorithm.cpp`、SDK `objectFit` 声明 |
| Surface / 渲染上下文异常 | `renderContextForMediaPlayer_`、`renderSurface_`、`RemoveMediaPlayerSurfaceNode` 链路 |
| 深色模式颜色未跟随 | `VideoPattern::OnColorConfigurationUpdate`、`video_theme.h` |
| AI 图像分析异常 | `IsSupportImageAnalyzer` / `DestroyAnalyzerOverlay`、`core/common/ai/image_analyzer_manager.h` |
| 无障碍读屏异常 | `video_accessibility_property.*`、`video_theme.h` 中控制条子节点文案 |
| 生成态 CAPI / arkoala 路由异常 | `arkoala_api_generated.h`、`frameworks/core/interfaces/native/implementation/video_modifier.cpp`、`test/unittest/capi/modifiers/video_modifier_test.cpp` |

## 调试入口

- 创建链路：从 `VideoModel::GetInstance()->Create()`（`video_model_ng.cpp`）确认 Video 节点、Pattern 与 Controller 是否建立。
- MediaPlayer 链路：`VideoPattern::PrepareMediaPlayer` → `SetSourceForMediaPlayer` → `MediaPlayerImpl::CreateMediaPlayer` → `Media::Player`。
- 动态模块链路：`DynamicModuleHelper::GetDynamicModule("Video")` → `libarkui_video.z.so` → `OHOS_ACE_DynamicModule_Create_Video` → `VideoDynamicModule`。
- 事件链路：`RegisterMediaPlayerEvent`（`video_pattern.cpp`）→ `media_player_callback.h` → `VideoEventHub::FireXxx` → JS 侧回调。
- 全屏链路：`VideoPattern::FullScreen` / `ExitFullScreen` → `VideoFullScreenNode::CreateFullScreenNode` → 挂载到 root overlay。
- 状态机链路（异步）：`VideoControllerAsync` 命令 → `VideoStateMachinePattern` → `VideoStateManager` 状态转换。
- 布局链路：`VideoLayoutAlgorithm::Measure/Layout` 确认约束、ObjectFit 计算与 srcRect/dstRect 输出。
- 日志 tag：`AceLogTag::ACE_VIDEO` 为 Video 组件统一 hilog tag。
- 回归验证：优先运行 `test/unittest/core/pattern/video/` 下的定向用例，异步 Controller 场景关注 `video_state_machine_pattern_test*`。

## 相关主题

- 图片组件（Poster 关联）：`docs/kb/components/media/image.md`
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`
- 组件化重构通用方案：`docs/组件化重构通用方案.md`
