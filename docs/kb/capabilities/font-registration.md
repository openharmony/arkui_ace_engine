# 字体注册 Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `FontRegistration`

## 定位

字体注册是管线级共享服务而非组件级 Pattern：所有注册入口（NAPI/FFI/Arkoala 生成 C 桥/前端委托）必经 `PipelineBase::RegisterFont → FontManager`，统一去重与异步加载；TTF/OTF 字形解析外置到 graphic_2d（Rosen::FontCollection）。字体注册与文本组件解耦，文本组件仅经 `RegisterCallbackNG` 订阅加载完成并重渲染。

具体注册语义、scheme 分发、卡片隔离、API 弃用状态与兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 注册统一汇聚 chokepoint | `frameworks/core/pipeline/pipeline_base.cpp` | `PipelineBase::RegisterFont` → FontManager |
| FontManager 注册存储与去重 | `frameworks/core/common/font_manager.h`、`font_manager.cpp` | fontLoaders_/fontNames_ 双层 dedup、callbacksNG_/externalLoadCallbacks_/formLoadCallbacks_、appCustomFont_ |
| FontLoader 抽象与分发 | `frameworks/core/common/font_loader.h` | `FontLoader::Create` + scheme 分发 |
| RosenFontLoader scheme 分发 | `frameworks/core/components/font/rosen_font_loader.cpp` | network/resource/file/asset 四路径 |
| RosenFontCollection 字节落地 | `frameworks/core/components/font/rosen_font_collection.cpp` | families_ dedup → 调外部 `Rosen::FontCollection::LoadFont` |
| NG 字体集合与卡片隔离 | `frameworks/core/components_ng/render/adapter/txt_font_collection.cpp` | `Current()` form-render→GetFormLocalInstance per-NativeEngine runtimeId |
| NG 字体集合抽象 | `frameworks/core/components_ng/render/font_collection.h`、`frameworks/core/components_ng/render/` | 回调注册 |
| 系统字体查询双路径 | `frameworks/core/common/font/font_platform_proxy.h` | USE_PLATFORM_FONT→FontPlatformProxy；否则 Rosen::TextEngine::Font_parser（TEXGINE） |
| 文本组件消费（fontFamily 设置 + 回调订阅 + dirty 重渲染） | `frameworks/core/components_ng/pattern/text/` | TextPattern/SpanItem/MultipleParagraphLayoutAlgorithm |
| 主题/应用默认字体 | `adapter/ohos/entrance/ace_container.cpp` | `CheckAndSetFontFamily` + `SetAppCustomFont`（静默覆盖空 fontFamily） |
| 字体创建工厂 | `frameworks/core/components/font/` | RosenFontLoader/RosenFontCollection/RosenFontManager |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态全局 `@ohos.font` | `<OH_ROOT>/interface/sdk-js/api/@ohos.font.d.ts` | registerFont/getSystemFontList/getFontByName（@since 18 弃用）/getUIFontConfig（未弃用） |
| 动态 UIContext.Font | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `UIContext.getFont().registerFont/getSystemFontList/getFontByName` |
| 静态等价 | `<OH_ROOT>/interface/sdk-js/api/@ohos.font.static.d.ets`、`@ohos.arkui.UIContext.static.d.ets` | @since 23 static |
| NAPI 绑定 | `interfaces/napi/kits/font/js_font.cpp` | JSRegisterFont 等 4 方法 |
| Cangjie FFI | `frameworks/bridge/cj_frontend/interfaces/cj_ffi/font/` | cj_font_ffi |
| Arkoala 生成 C 桥（静态前端） | `frameworks/core/interfaces/native/implementation/global_scope_ohos_font_accessor.cpp` | 服务静态前端 |
| NDK 族名设置器（消费方，非注册） | `interfaces/native/native_styled_string_descriptor.h`、`interfaces/native/node/rich_editor_native_impl.cpp` | OH_ArkUI_TextStyle_SetFontFamily 等（ace 不提供 NDK 注册 C-API） |
| 跨子系统 LocalizationKit | `<OH_ROOT>/interface/sdk-js/api/@ohos.fontManager.d.ts` | installFont/uninstallFont（ohos.permission.UPDATE_FONT） |
| 跨子系统 Graphics | `<OH_ROOT>/interface/sdk-js/api/@ohos.graphics.text.d.ts` | FontCollection.loadFontSync/unloadFontSync |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 图形引擎（字形解析） | `rosen_font_collection.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/`（Rosen::FontCollection::LoadFont/LoadThemeFont/ClearThemeFont + FontCollectionMgr） | ace 仅读字节交 Rosen，TTF/OTF 解析不在本仓 |
| 系统字体服务 | `font_platform_proxy.h` | font-service（推测） | — | FontPlatformProxy::SetDelegate 在本仓无调用方（推测外部注册） |
| 跨子系统字体安装 | `interfaces/napi/kits/font/` | Localization | `@ohos.fontManager.d.ts` | installFont/uninstallFont |
| 跨子系统字体引擎 | — | Graphics | `@ohos.graphics.text.d.ts` | FontCollection.loadFontSync |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pipeline/pipeline_context_font_scale_env_test_ng.cpp` | 字体缩放环境 |
| C-API 测试 | `test/unittest/capi/accessors/global_scope_ohos_font_accessor_test.cpp` | Arkoala 生成 C 桥 accessor |

### 相关 Spec

| Spec 域 | 路径 |
|---------|------|
| 功能域 design | `specs/04-common-capability/13-font-text/01-font-registration/design.md` |
| Feat-01 字体注册与查询全能力 | `specs/04-common-capability/13-font-text/01-font-registration/Feat-01-font-registration-full-capability-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 注册后字体不生效/重渲染不触发 | `font_manager.cpp` 的 `RegisterCallbackNG` + `externalLoadCallbacks_`/`formLoadCallbacks_` 分发；standalone 测量不注册回调 |
| 字体下载失败静默不重试 | `rosen_font_loader.cpp` 的 `LoadFromNetwork` 失败保持 `isLoaded_=false` |
| 卡片字体互相串扰 | `txt_font_collection.cpp` 的 `GetFormLocalInstance`（per-NativeEngine runtimeId，PREVIEW 构建无隔离 runtimeId=0） |
| appCustomFont 静默覆盖预期 fontFamily | `font_manager.cpp` 的 `SetAppCustomFont`（仅存名）+ 布局期 `span_node.cpp`/`multiple_paragraph_layout_algorithm.cpp`/`text_field_layout_algorithm.cpp` 覆盖空 fontFamily |
| 系统字体列表来源不一致 | `font_manager.cpp` 的 `GetSystemFontList`：构建宏 USE_PLATFORM_FONT vs TEXGINE_SUPPORT_FOR_OHOS 双路径 |
| API 迁移混淆弃用状态 | `getUIFontConfig` 未弃用仍全局独有，其余 3 API @since 18 弃用→UIContext.Font |

## 调试入口

- 字体注册链路：`js_font.cpp` → `FrontendDelegate::RegisterFont` → `PipelineBase::RegisterFont` → `FontManager::RegisterFont`（去重）→ `RosenFontLoader::AddFont`（scheme 分发）→ `RosenFontCollection::LoadFontFromList`（dedup）→ 外部 `Rosen::FontCollection::LoadFont`
- 异步加载完成：`NG::FontCollection::Global()` load-finish 回调 → `OnLoadFontFinished`（解析 runtimeId）→ `NotifyFontChange`/`NotifyFormFontChange` → 文本节点 `MarkDirtyNode`+`SetFontReady`+`ClearParagraphCache`

## 相关主题

- `TextCommonAttributes`（文本通用属性）— fontFamily 等字体样式消费侧
- `TextMeasurement`（文本测量）— 共享同一 RosenFontCollection 单例
