# Text Context

> 文档版本：v1.3
> 更新时间：2026-06-27
> 来源：`docs/context_registry.json` 主题 `Text`

## 定位

Text 是 ArkUI 的基础文本显示组件，面向应用侧提供文本内容展示、文本样式配置、Span/StyledString 组合展示、符号文本、选择复制、数据检测、溢出截断和跑马灯等能力。

本文档用于快速定位 Text 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、选择、复制、拖拽、事件汇聚 | `frameworks/core/components_ng/pattern/text/text_pattern.cpp` | Text 组件核心行为实现入口 |
| Pattern 类型和扩展接口 | `frameworks/core/components_ng/pattern/text/text_pattern.h` | `TextPattern` 类型、控制器、选择、拖拽、布局相关接口 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/text/text_model_ng.cpp` | 动态前端 Text 创建和属性写入入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/text/text_model_static.cpp` | 静态前端 Text 属性写入入口 |
| 布局和段落构建 | `frameworks/core/components_ng/pattern/text/text_layout_algorithm.cpp` | 文本测量、段落构建、溢出处理、自适应字号等布局逻辑 |
| 布局算法声明 | `frameworks/core/components_ng/pattern/text/text_layout_algorithm.h` | Text 布局算法类型和成员声明 |
| 属性存储 | `frameworks/core/components_ng/pattern/text/text_layout_property.h` | 字体、行布局、内容、选择复制等属性声明 |
| 事件存储 | `frameworks/core/components_ng/pattern/text/text_event_hub.h` | Text 事件回调存储和触发入口 |
| 控制器 | `frameworks/core/components_ng/pattern/text/text_controller.h` | Text 控制器能力入口 |
| Span/StyledString | `frameworks/core/components_ng/pattern/text/span/` | SpanString、MutableSpanString 和 TLV 相关实现 |
| 选择覆盖层 | `frameworks/core/components_ng/pattern/text/text_select_overlay.*`、`frameworks/core/components_ng/pattern/text/base_text_select_overlay.*` | 选择菜单、手柄、选区覆盖层相关实现 |
| 内容绘制和跑马灯 | `frameworks/core/components_ng/pattern/text/text_content_modifier.*`、`frameworks/core/components_ng/pattern/text/text_paint_method.*` | 文本绘制、遮蔽、跑马灯和内容 modifier |
| Text C API 实现 | `interfaces/native/node/text_native_impl.h`、`interfaces/native/node/text_native_impl.cpp` | Text NDK/C API native impl |
| C API 枚举 | `interfaces/native/native_node.h` | `NODE_TEXT_*` 属性和事件枚举 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text.d.ts` | 动态 ArkTS `TextInterface`、`TextAttribute`、`TextOptions` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/text.static.d.ets` | 静态 ArkTS Text 组件、属性和 options 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/TextModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/TextModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h`、`interfaces/native/node/text_native_impl.h` | Text C API 属性、事件和 native 实现入口 |
| NAPI 相关能力 | `interfaces/napi/kits/font/`、`interfaces/napi/kits/measure/`、`interfaces/napi/kits/text_menu_controller/` | Text 无独立 `interfaces/napi/kits/text/`；相关能力由字体、测量和菜单控制模块承载 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `TextAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `TextInterface`、`TextOptions` 或 `Text(`。
- Modifier：在 `TextModifier*.d.ts` / `TextModifier*.d.ets` 中确认继承或实现关系。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_TEXT_`、`NODE_FONT_`、`NODE_TEXT_ON_`。

### API 解析实现路径

Text 组件**尚未进行组件化改造**，属性解析仍采用双路径架构，编译产物在主 `libace_compatible.z.so` 中。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **JSView（声明式组件）** | `frameworks/bridge/declarative_frontend/jsview/js_text.cpp` | `JSText::SetXxx()` → `TextModel::GetInstance()->SetXxx()` |
| **ArkTS Bridge（动态属性 / Modifier / FrameNode 命令式）** | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_bridge.cpp` | `TextBridge::SetXxx()` → `node_text_modifier` → `TextModelNG::SetXxx(frameNode, ...)` |
| **node_modifier 层** | `frameworks/core/interfaces/native/node/node_text_modifier.cpp` | C++ 属性 Set/Reset/Get 函数，由 bridge 和 C API 共用 |
| **C API（NDK）** | `interfaces/native/node/text_native_impl.cpp` | Text 专属 C API 实现（`NODE_TEXT_*`/`NODE_FONT_*` 枚举分发） |
| **前端 Modifier（ArkTS 侧）** | `frameworks/bridge/declarative_frontend/ark_modifier/src/text_modifier.ts` | ArkTS `TextModifier` 类定义 |

组件化改造参考：`./组件化重构通用方案.md`。改造后上述 JSView 和 Bridge 双路径将统一到 `pattern/text/bridge/arkts_native_text_bridge.cpp`，并输出独立 so。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；相对路径列仅记录外部仓内的头文件、目录或 GN 目标。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图形绘制抽象 | `frameworks/core/components_ng/render/drawing.h`、`frameworks/core/components_ng/render/drawing_forward.h` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/*`、`rosen/modules/2d_graphics/src/drawing/engine_adapter/*` | Text 绘制侧使用的 Canvas、Brush、Path、Rect、Image 等 Drawing/Rosen 类型入口 |
| Rosen / RenderService | `frameworks/core/components_ng/render/adapter/rosen_render_context.*`、`frameworks/core/components_ng/components.gni` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/*`、`rosen/modules/render_service_base/include/*`、`rosen/modules/render_service_client:librender_service_client_static` | 渲染上下文、RenderService 客户端和后端渲染依赖入口 |
| 排版抽象 | `frameworks/core/components_ng/render/paragraph.h` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | ArkUI 对段落构建、测量、绘制、命中测试的抽象接口 |
| Rosen Text / Typography 适配 | `frameworks/core/components_ng/render/adapter/txt_paragraph.*`、`frameworks/core/components_ng/render/adapter/txt_font_collection.*` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h`、`frameworks/text/interface/export/rosen_text/export/rosen_text/text_style.h`、`frameworks/text/interface/export/rosen_text/export/rosen_text/font_collection.h` | Text 到 Rosen Text、Typography 和 FontCollection 的适配层 |
| 段落管理 | `frameworks/core/components_ng/pattern/rich_editor/paragraph_manager.h`、`frameworks/core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.*` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | 多段落布局、选区矩形、命中检测等段落管理能力入口 |
| 字体管理 | `frameworks/core/common/font_manager.h`、`frameworks/core/components_ng/render/font_collection.h` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/font_collection.h` | 字体注册、字体集合、字体变化通知和字体加载相关入口 |
| 图片 / PixelMap Span | `frameworks/core/components_ng/render/adapter/pixelmap_image.*`、`frameworks/core/components_ng/render/adapter/animated_image.*` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h`、`interfaces/kits/js/common/include/pixel_map_napi.h` | ImageSpan、拖拽预览、leading margin 图片等图像内容入口 |
| 剪贴板 | `frameworks/core/common/clipboard/`、`adapter/ohos/capability/clipboard/`、`adapter/preview/entrance/clipboard/` | `foundation/distributeddatamgr/pasteboard` | `framework/innerkits/include/pasteboard_client.h` | 选择复制、富文本复制和平台剪贴板适配入口 |
| UDMF / 拖拽数据 | `frameworks/core/common/udmf/udmf_client.h`、`adapter/ohos/capability/udmf/`、`adapter/preview/entrance/udmf/` | `foundation/distributeddatamgr/udmf` | `interfaces/innerkits/client/udmf_client.h`、`adapter/framework/innerkitsimpl/client/udmf_client.h` | 文本拖拽和跨应用数据交换入口 |
| 震感反馈 | `frameworks/core/common/vibrator/vibrator_utils.h`、`adapter/ohos/entrance/vibrator/`、`adapter/preview/entrance/vibrator/` | `base/sensors/miscdevice` | `interfaces/inner_api/vibrator/vibrator_agent.h` | 选择、拖动等文本交互中的震感反馈入口 |
| AI 数据检测 / 翻译 | `frameworks/core/common/ai/`、`interfaces/inner_api/ace/ai/`、`adapter/ohos/osal/data_detector_*`、`adapter/ohos/osal/text_translation_*` | 系统运行时动态库 | `system/lib*/libai_text_analyzer_innerapi.z.so`、`system/lib*/libai_text_translation_innerapi.z.so` | 数据检测、实体识别、选中文本检测和文本翻译入口 |
| 构建依赖聚合 | `frameworks/core/components_ng/components.gni`、`frameworks/core/components_ng/render/BUILD.gn` | `foundation/graphic/graphic_2d`、`foundation/multimedia/image_framework` | `graphic_2d:*`、`image_framework:*`、`rosen/modules/2d_graphics:*`、`interfaces/kits/napi/graphic/drawing:drawing_napi_impl` | 图形、排版、渲染适配和 render adapter 源文件的构建依赖入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text/` | Pattern、布局、选择复制、空指针、滚动条、多线程等 Text 行为回归 |
| Spec 功能域 | `specs/05-ui-components/09-text-components/04-text/` | Text 功能域设计、验收和验证契约 |
| Spec 总索引 | `specs/index.md` | `05-09-04 Text` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | Text 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Text 功能域：`specs/05-ui-components/09-text-components/04-text/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 字体属性与自适应字体 | `Feat-01-font-properties-spec.md` |
| Feat-02 | 行/段落布局 | `Feat-02-line-paragraph-layout-spec.md` |
| Feat-03 | 溢出与截断 | `Feat-03-overflow-truncation-spec.md` |
| Feat-04 | 装饰与样式 | `Feat-04-decoration-styles-spec.md` |
| Feat-05 | 选择与复制 | `Feat-05-selection-copy-spec.md` |
| Feat-06 | 系统能力 | `Feat-06-system-capabilities-spec.md` |
| Feat-07 | 事件回调 | `Feat-07-event-callbacks-spec.md` |

若某个 Feat 在 `specs/index.md` 中仍为占位状态，应以源码、SDK 声明和测试为事实源，补齐 Spec 后再引用行为结论。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Text 创建后内容不显示 | Model 创建入口、`TextLayoutProperty` 内容属性、布局算法入口 |
| 字体大小、颜色、字重不生效 | SDK `TextAttribute` 字体属性、Model 属性写入入口、`TextLayoutProperty` 字体属性组 |
| 省略号、换行、最大行数异常 | SDK 溢出/行数属性、布局算法、Feat-03 |
| Span 或 StyledString 表现异常 | `span/` 目录、Model SpanString 创建路径、Feat-01/Feat-02 |
| 选择、复制、菜单异常 | `TextPattern`、选择覆盖层、`TextEventHub`、Feat-05 |
| onCopy/onWillCopy/onTextSelectionChange 不触发 | SDK 事件声明、`TextEventHub`、C API Text 事件枚举、Feat-07 |
| 数据检测、AI 实体识别异常 | SDK 数据检测属性、C API Text 数据检测枚举、Feat-06 |
| 跑马灯不启动或状态异常 | SDK `textOverflow` / `marqueeOptions` 声明、布局算法、内容 modifier、Feat-03/Feat-07 |

## 调试入口

- 创建链路：从 Model 创建入口确认 Text 节点、Pattern 和内容属性是否建立。
- 属性链路：从 SDK 属性名定位 Model 写入，再看 `TextLayoutProperty` 的属性分组和更新标记。
- 测量链路：从布局算法入口确认约束、样式、段落构建和溢出结果。
- 交互链路：选择复制问题优先看 Pattern、事件 Hub、选择覆盖层和 C API 事件枚举。
- 回归验证：优先运行或补充 `test/unittest/core/pattern/text/` 下的定向用例。

## 相关主题

- `TextDrag`：`docs/pattern/text_drag/TextDrag_Knowledge_Base_CN.md`
- `RichEditor`：`docs/pattern/rich_editor/RichEditor_Knowledge_Base_CN.md`
- `TextInput`：`docs/pattern/text_input/TextInput_Knowledge_Base_CN.md`
- `TextArea`：`docs/pattern/text_area/TextArea_Knowledge_Base_CN.md`
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`
