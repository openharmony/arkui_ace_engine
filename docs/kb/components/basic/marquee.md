# Marquee Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Marquee`

## 定位

Marquee 是 ArkUI 的单行滚动文本组件，仅在文本内容宽度（含水平 padding）大于等于组件宽度时启动滚动，常用于公告、通知、广告等场景。组件不支持子组件，内部按需创建最多两个 Text 子节点（设置 spacing 或 delay 时启用第二子节点实现无缝双滚动）。

Marquee 已完成组件化改造，属性解析统一在 `pattern/marquee/bridge/` 下，编译产物为独立动态库 `libarkui_marquee.z.so`。独立 Marquee 组件无公开 NDK C-API；跨语言入口仅 ArkTS 动态/静态版与 Cangjie FFI（NDK 仅有 Text 组件的 `ArkUI_TextMarqueeOptions`）。

本文档用于快速定位 Marquee 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、滚动状态机、动画播放、事件触发 | `frameworks/core/components_ng/pattern/marquee/marquee_pattern.cpp` | Marquee 核心行为实现入口（IsRunMarquee、StartMarqueeAnimation、PlayMarqueeAnimation/PlayMarqueeDoubleAnimation、ChangeAnimationPlayStatus、ExecuteStopMarquee） |
| Pattern 类型、状态成员 | `frameworks/core/components_ng/pattern/marquee/marquee_pattern.h` | MarqueePattern 类型、LastAnimationParam、多线程 attach/detach 钩子 |
| 多线程生命周期 | `frameworks/core/components_ng/pattern/marquee/marquee_pattern_multi_thread.cpp` | OnAttachToMainTreeMultiThread / OnDetachFromMainTreeMultiThread |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/marquee/marquee_model_ng.cpp` | 动态前端 Marquee 创建和七参数 + 字体属性写入入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/marquee/marquee_model_static.cpp` | 静态前端 ScrollAmount 写入入口（仅 SetScrollAmount） |
| 布局算法 | `frameworks/core/components_ng/pattern/marquee/marquee_layout_algorithm.cpp` | 文本全宽测量、初始偏移、RTL 对齐、第二子节点布局 |
| Layout 属性存储 | `frameworks/core/components_ng/pattern/marquee/marquee_layout_property.h` | Src/MarqueeSpacing/MarqueeDelay/字体属性/MarqueeUpdateStrategy 存储 |
| Paint 属性存储 | `frameworks/core/components_ng/pattern/marquee/marquee_paint_property.h` | PlayerStatus/ScrollAmount/Loop/Direction 存储（NG 运行时读取 Paint 属性） |
| 事件 Hub | `frameworks/core/components_ng/pattern/marquee/marquee_event_hub.h` | onStart/onBounce/onFinish/onStop 注册与触发 |
| 无障碍 | `frameworks/core/components_ng/pattern/marquee/marquee_accessibility_property.cpp` | 仅暴露文本内容，不暴露滚动/播放状态 |
| 旧版主题（兼容） | `frameworks/core/components/marquee/marquee_theme.h` | MarqueeTheme；NG 字体默认值实际取自 TextTheme |
| 旧版 Option struct | `frameworks/core/components/common/properties/marquee_option.h` | 非 NG 路径 MarqueeOption struct |
| 枚举定义 | `frameworks/core/components/common/layout/constants.h` | MarqueeDirection / MarqueeUpdateStrategy / MarqueeDynamicSyncSceneType |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/marquee.d.ts` | 动态 ArkTS `MarqueeInterface`、`MarqueeOptions`、`MarqueeAttribute` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/marquee.static.d.ets` | 静态 ArkTS Marquee 组件、`MarqueeOptions`、`setMarqueeOptions` 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/MarqueeModifier.d.ts` | 动态 MarqueeModifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/MarqueeModifier.static.d.ets` | 静态 MarqueeModifier 声明 |
| Cangjie FFI | `frameworks/bridge/cj_frontend/interfaces/cj_ffi/cj_marquee_ffi.h` | Cangjie FFI 入口（子集：缺 onStop/spacing/delay/direction setter） |
| C API（NDK） | 无独立 Marquee C API | NDK 仅有 Text 组件的 `ArkUI_TextMarqueeOptions`（`interfaces/native/node_attributes/text.h`），非独立 Marquee 节点 |

API 检索建议：

- 构造参数：在 SDK 文件中搜索 `MarqueeOptions`、`start`、`step`、`loop`、`fromStart`、`src`、`spacing`、`delay`。
- 属性方法：在 SDK 文件中搜索 `MarqueeAttribute` 和具体方法名（`fontColor`、`fontSize`、`allowScale`、`fontWeight`、`fontFamily`、`marqueeUpdateStrategy`、`onStart`、`onBounce`、`onFinish`、`onStop`）。
- Modifier：在 `MarqueeModifier*.d.ts` / `*.d.ets` 中确认继承关系（注意 TS Modifier 未暴露 onStop）。
- Cangjie：在 `cj_marquee_ffi.h` 中搜索 `FfiOHOSAceFrameworkMarquee*`。

### API 解析实现路径

Marquee 组件**已完成组件化改造**，属性解析统一在 `pattern/marquee/bridge/` 下，编译产物为独立动态库 `libarkui_marquee.z.so`（动态模块入口 `OHOS_ACE_DynamicModule_Create_Marquee`，注册于 `adapter/ohos/osal/dynamic_module_helper.cpp`）。无旧版 `js_marquee.cpp` JSView 文件。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/components/arkmarquee.js`、`frameworks/bridge/declarative_frontend/ark_component/src/ArkMarquee.ts` | 前端 Marquee 组件类，调用 `setInitialize` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/marquee/bridge/arkts_native_marquee_bridge.cpp` | `MarqueeBridge` 静态方法，create/setInitialize/属性解析，通过 `IsJsView()` 区分模式 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/marquee/bridge/marquee_dynamic_modifier.cpp` | `ArkUIMarqueeModifier` 函数指针表（`GetMarqueeDynamicModifier`），分发到 MarqueeModelNG |
| Static Modifier | `frameworks/core/components_ng/pattern/marquee/bridge/marquee_static_modifier.cpp` | `GENERATED_ArkUIMarqueeModifier` 静态路径，`setMarqueeOptions`/`construct` 等 |
| Dynamic Module | `frameworks/core/components_ng/pattern/marquee/bridge/marquee_dynamic_module.cpp` | `MarqueeDynamicModule` 派生类，`libarkui_marquee.z.so` 入口，分发 Dynamic/Static/Cj/Custom Modifier |
| Custom Modifier | `frameworks/core/components_ng/pattern/marquee/bridge/marquee_custom_modifier.cpp` | 仅 `setMarqueeFrameRateRange`（帧率范围同步） |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/marquee_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/marquee_modifier.ts` | ArkTS `MarqueeModifier` 类（未暴露 onStop） |
| 内部 API struct | `frameworks/core/interfaces/arkoala/arkoala_api.h` | `ArkUIMarqueeModifier` 函数指针 struct 定义 |
| 生成 API struct | `frameworks/core/interfaces/native/generated/interface/arkoala_api_generated.h` | `GENERATED_ArkUIMarqueeModifier`、`Ark_MarqueeOptions` 定义 |

### 外部依赖入口

Marquee 无直接跨仓依赖。文本测量、排版、字体渲染均委托给内部创建的 Text 子节点（`TextPattern` / `TextTheme`），滚动动画通过内部 `AnimationUtils` 与 `RenderContext` 实现。以下为内部依赖入口（均位于 ace_engine 仓内）：

| 依赖方向 | 本仓入口 | 说明 |
|----------|----------|------|
| 文本子节点 | `frameworks/core/components_ng/pattern/text/text_pattern.h`、`frameworks/core/components/text/text_theme.h` | Marquee 创建 Text 子节点承载文本，字体默认值取自 TextTheme |
| 动画框架 | `frameworks/core/components_ng/render/animation_utils.h` | 滚动动画启动/关键帧/finish 回调 |
| 渲染上下文 | `frameworks/core/components_ng/render/adapter/rosen_render_context.*` | 文本子节点 translate 偏移动画 |
| 动态模块加载 | `frameworks/core/common/dynamic_module_helper.h` | `libarkui_marquee.z.so` 动态加载 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/marquee/` | Pattern 行为、属性更新策略等回归（`marquee_pattern_test_ng.cpp`、`marquee_test_ng.cpp`、`marquee_test_update_strategy.cpp`） |
| 组件测试 | `test/component_test/test_cases/components/information_display/entry/src/main/ets/pages/marquee/` | 字体样式、滚动行为组件级用例 |
| Spec 功能域 | `specs/05-ui-components/09-text-components/01-marquee/` | Marquee 功能域设计、验收和验证契约 |
| Spec 总索引 | `specs/index.md` | `05-09-01 Marquee` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | Marquee 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Marquee 功能域：`specs/05-ui-components/09-text-components/01-marquee/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 创建与滚动参数 | `Feat-01-marquee-creation-scroll-params-spec.md` |
| Feat-02 | 字体样式 | `Feat-02-marquee-font-style-spec.md` |
| Feat-03 | 滚动策略、事件回调与多范式 | `Feat-03-marquee-strategy-events-multi-paradigm-spec.md` |
| Design | 架构设计基线 | `design.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Marquee 不滚动 | SDK `start`/`src` 声明、`MarqueePattern` IsRunMarquee 谓词、布局算法文本宽度测量、Feat-01 |
| start 切 true 后不重启已完成滚动 | `MarqueePattern` StartMarqueeAnimation/ChangeAnimationPlayStatus、animation_ 生命周期、Feat-01 AC-2.4 |
| 字体颜色/字号/字重不生效或默认值异常 | SDK `MarqueeAttribute` 字体属性、`MarqueeLayoutProperty` 字体属性组、`UpdateTextNodeAttr` 取 TextTheme 默认、Feat-02 |
| allowScale 与系统字号缩放行为异常 | `SetAllowScale` 双写、`OnFontScaleConfigurationUpdate`、Feat-02 |
| marqueeUpdateStrategy 不保留位置 | `OnModifyDone` 分发、`GetTextOffset`/PRESERVE_POSITION 生效条件、Feat-03 |
| onStart/onBounce/onFinish/onStop 不触发或顺序异常 | `MarqueeEventHub`、`MarqueePattern` 触发点（ExecuteStopMarquee/OnAnimationFinish）、终态顺序、Feat-03 |
| spacing/delay 无缝双滚动异常 | `NeedSecondChild`、`PlayMarqueeDoubleAnimation`、`BuildAnimationKeyframes`、Feat-01 |
| 卡片场景滚动行为异常 | `IsFormRenderExceptDynamicComponent`、loop 强制 1、Feat-01 |
| Cangjie / 静态版属性缺失 | `cj_marquee_ffi.h`、`setMarqueeOptions` 解析但未 apply 的 spacing/delay、Feat-03 US-7 |

## 调试入口

- 创建链路：从前端 `ArkMarquee.ts` → `setInitialize` → `MarqueeBridge` → `MarqueeModelNG::Create` 确认节点与 Text 子节点是否建立。
- 属性链路：从 SDK 属性名定位 `MarqueeBridge::SetMarquee*` → `MarqueeModelNG::Set*` → `MarqueePaintProperty`/`MarqueeLayoutProperty` 的属性分组与 dirty flag。
- 滚动链路：从 `OnModifyDone` 分发确认走 measure/OnlyPlayStatusChange/StopMarqueeAnimation 哪条路径，再看 `IsRunMarquee` 谓词与 `PlayMarqueeAnimation` 时长公式。
- 事件链路：从 `MarqueeEventHub` 确认回调注册，从 `MarqueePattern` 触发点确认 onStart/onBounce/onFinish/onStop 触发条件（hasStart_、GetTextOffset==0）。
- 回归验证：优先运行 `test/unittest/core/pattern/marquee/` 下的定向用例。

## 相关主题

- `Text`：[docs/kb/components/basic/text.md](text.md)（Marquee 的文本渲染、字体默认值、跑马灯溢出模式均依赖 Text 组件）
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`