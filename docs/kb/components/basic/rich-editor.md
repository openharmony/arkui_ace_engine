# RichEditor Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `RichEditor`

## 定位

RichEditor 是 ArkUI 的富文本编辑器组件，基于 TextPattern 扩展，支持双模式架构：旧框架模式（基于 SpanItem 列表的 Controller API）和属性字符串模式（基于 MutableSpanString 的 StyledStringController API）。提供文本/图片/符号/Builder Span 混合编排、撤销重做、光标管理、IME 输入、文本选择、自定义键盘、数据检测等能力。

本文档用于快速定位 RichEditor 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 核心（多继承 TextPattern + ScrollablePattern + TextInputClient + SpanWatcher） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp` | 生命周期、双模式分发、内容增删改、光标、选择、IME、事件触发 |
| Pattern 声明 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h` | 成员变量、方法声明、多继承结构 |
| ModelNG（动态版入口） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp` | 组件创建、Controller 绑定、属性 Set/Reset |
| ModelStatic（静态版入口） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_static.cpp` | 静态版组件创建、模式切换 |
| Model 接口 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h` | Model 抽象接口 |
| 布局算法 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.cpp` | 段落管理、LRU 缓存、多段落布局 |
| 布局属性 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_property.h` | 布局相关属性声明 |
| 事件中心 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.cpp` | 事件回调存储和触发 |
| 手势事件 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_gesture_event_hub.cpp` | 手势、点击、长按、双击事件 |
| 基础控制器（双模式共享） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_base_controller.cpp` | 光标、选择、编辑状态、打字样式等共享方法 |
| 旧框架模式控制器 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_controller.cpp` | Span 增删改查、跨模式转换 |
| 属性字符串模式控制器 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.cpp` | StyledString 设置/获取、内容变更监听 |
| 撤销/重做管理 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_undo_manager.cpp` | 双模式 undo/redo 栈管理 |
| 选择覆盖层 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_select_overlay.cpp` | 选择手柄、选择菜单、放大镜 |
| 滚动控制器 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_scroll_controller.cpp` | 滚动、惯性、可视区域 |
| 内容修饰符 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_content_modifier.cpp` | 内容绘制、光标渲染、滚动条 |
| 覆盖层修饰符 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.cpp` | 选择高亮、手柄覆盖层 |
| 绘制方法 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_paint_method.cpp` | Rosen + Skia 绘制入口 |
| 段落管理 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_paragraph_manager.h` | 段落信息收集和查询 |
| 主题 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_theme.h` | 默认颜色、尺寸、间距 |
| LRU 缓存 | `frameworks/core/components_ng/pattern/rich_editor/lru_cache.h` | 段落布局结果缓存 |
| 颜色模式处理 | `frameworks/core/components_ng/pattern/rich_editor/color_mode_processor.h` | 深浅色模式适配 |
| 样式管理 | `frameworks/core/components_ng/pattern/rich_editor/style_manager.h` | 样式属性管理 |
| StyledString 控制器 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.h` | 属性字符串模式控制器声明 |
| Span 结果抽象 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_abstract_span_result.h` | Span 查询结果类型 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/rich_editor.d.ts` | 动态 ArkTS `RichEditorAttribute`、`RichEditorOptions` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/richEditor.static.d.ets` | 静态 ArkTS RichEditor 组件、属性和 options 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/RichEditorModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/RichEditorModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h`、`interfaces/native/node/rich_editor_native_impl.h` | RichEditor C API 属性、事件枚举和 native 实现入口 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `RichEditorAttribute` 和具体属性名（如 `caretColor`、`maxLength`、`enableAutoSpacing`）。
- 构造参数：在 SDK 文件中搜索 `RichEditorOptions`、`RichEditorStyledStringOptions`。
- 事件回调：在 SDK 文件中搜索 `aboutToIMEInput`、`onWillChange`、`aboutToDelete`、`onSelectionChange`。
- Controller 方法：搜索 `RichEditorController`、`RichEditorStyledStringController`、`RichEditorBaseController`。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_RICH_EDITOR_` 或 `RICH_EDITOR_` 前缀枚举。

### API 解析实现路径

RichEditor **已完成组件化改造**，`bridge/` 子目录存在于 pattern 目录下。同时旧 JSView 文件仍保留（过渡状态）。编译产物为独立 so。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/components/arkricheditor.js`、`frameworks/bridge/declarative_frontend/ark_component/src/ArkRichEditor.ts` | 前端组件类、属性入口定义 |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/rich_editor/bridge/arkts_native_rich_editor_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析和 Modifier 调用 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp` | 动态属性路径，`GetRichEditorDynamicModifier()` 暴露 |
| Static Modifier | `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_static_modifier.cpp` | 静态编译路径，`RichEditorInterfaceModifier` / `RichEditorAttributeModifier` 命名空间 |
| Dynamic Module | `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_module.cpp` | `DynamicModule` 派生类，独立 so 入口 |
| Model 实现桥接 | `frameworks/core/components_ng/pattern/rich_editor/bridge/richeditor_model_impl.cpp` | Model 实现委托 |
| Custom Modifier | `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_custom_modifier.h` | 自定义 modifier 支持 |
| 旧 JSView（过渡保留） | `frameworks/bridge/declarative_frontend/jsview/js_richeditor.cpp` | 旧版声明式组件入口，仍保留但优先走 Bridge 路径 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/rich_editor_modifier.ts` | ArkTS `RichEditorModifier` / `LazyArkRichEditorComponent` 类定义 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图形绘制 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_paint_method.cpp`、`rich_editor_content_modifier.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/*`、`rosen/modules/render_service_base/include/*` | Rosen + Skia 绘制、Canvas 绑定 |
| 排版引擎 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.cpp` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | 段落排版、文本测量、命中检测 |
| IME 输入法 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp`（TextInputClient 实现） | `foundation/multimodalinput/input` | `interfaces/innerkits/include/` | IME 连接、文本插入/删除、预上屏 |
| 剪贴板 | `frameworks/core/common/clipboard/`、`adapter/ohos/capability/clipboard/` | `foundation/distributeddatamgr/pasteboard` | `framework/innerkits/include/pasteboard_client.h` | 复制/剪切/粘贴、富文本剪贴板 |
| UDMF / 拖拽数据 | `frameworks/core/common/udmf/udmf_client.h`、`adapter/ohos/capability/udmf/` | `foundation/distributeddatamgr/udmf` | `interfaces/innerkits/client/udmf_client.h` | 文本拖拽、跨应用数据交换 |
| 图片 / PixelMap | `frameworks/core/components_ng/render/adapter/pixelmap_image.*` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h` | ImageSpan 图片内容、拖拽预览 |
| 振动反馈 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp`（enableHapticFeedback） | `foundation/multimodalinput/input` | `interfaces/innerkits/include/vibrator_agent.h` | 长按/滑动触觉反馈 |
| AI 数据检测 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp`（DataDetectorAdapter） | AI 服务适配层 | — | 电话/邮箱/网址实体识别 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试目录 | `test/unittest/core/pattern/rich_editor/` | RichEditor 全量单元测试 |
| 基础测试 | `rich_editor_base_test_ng.cpp` | 基础创建、属性、模式 |
| Span 测试 | `rich_editor_add_span_test_ng.cpp`、`rich_editor_span_test.cpp`、`rich_editor_span_amend_test_ng.cpp` | Span 增删改查 |
| 光标测试 | `rich_editor_caret_test_ng.cpp`、`rich_editor_cursor_test_ng.cpp` | 光标位置、亲和性、可见性 |
| 选择测试 | `rich_editor_selection_test_ng.cpp`、`rich_editor_select_overlay_test_ng.cpp`、`rich_editor_select_action_test_ng.cpp` | 选区、选择菜单、手柄 |
| 事件测试 | `rich_editor_event_test_ng.cpp`、`rich_editor_change_callback_test_ng.cpp` | 事件回调、will/did 变化 |
| 键盘测试 | `rich_editor_keyboard_test_ng.cpp`、`rich_editor_keyboard_shortcut_test_ng.cpp` | IME 交互、快捷键 |
| 样式测试 | `rich_editor_style_test_ng.cpp`、`rich_editor_text_style_test_ng.cpp`、`rich_editor_style_change_test_ng.cpp` | 样式设置、更新 |
| 撤销测试 | `rich_editor_undo_redo_test.cpp`、`rich_editor_styled_undo_test_ng.cpp`、`rich_editor_string_undo_test_ng.cpp` | 撤销/重做 |
| StyledString 测试 | `rich_editor_styled_string_test_ng.cpp`、`rich_editor_styled_string_extend_test_ng.cpp` | 属性字符串模式 |
| 拖拽测试 | `rich_editor_drag_test_ng.cpp` | 拖拽交互 |
| 滚动测试 | `rich_editor_scroll_test_ng.cpp`、`rich_editor_free_scroll_test_ng.cpp`、`rich_editor_scroll_controller_test.cpp` | 滚动、惯性、可视区域 |
| 菜单测试 | `rich_editor_menu_test_ng.cpp` | 选择菜单定制 |
| 剪贴板测试 | `rich_editor_copy_cut_paste_test_ng.cpp` | 复制/剪切/粘贴 |
| AI 测试 | `rich_editor_ai_test_ng.cpp` | 数据检测 |
| 预览文本测试 | `rich_editor_preview_text_test_ng.cpp` | 预上屏 |
| 多线程测试 | `rich_editor_multi_thread_test_ng.cpp` | 线程安全 |
| 布局测试 | `rich_editor_layout_test_ng.cpp` | 布局、段落 |
| 无障碍测试 | `rich_editor_accessibility_test_ng.cpp` | 无障碍属性 |
| 颜色模式测试 | `rich_editor_color_mode_test_ng.cpp` | 深浅色适配 |
| BUILD.gn | `test/unittest/core/pattern/rich_editor/BUILD.gn` | 测试构建配置 |

### 相关 Spec

RichEditor 长期规格位于 `specs/05-ui-components/09-text-components/02-rich-editor/`，包含 1 个 design.md 和 9 个 Feat spec：

| Feat | 标题 | 覆盖范围 |
|------|------|----------|
| Feat-01 | 组件初始化与双模式架构 | 构造函数、Controller 绑定、attributeModifier、双模式架构 |
| Feat-02 | Span 内容管理 | addTextSpan/addImageSpan/addBuilderSpan/addSymbolSpan/deleteSpans/getSpans/updateSpanStyle/updateParagraphStyle/fromStyledString/toStyledString |
| Feat-03 | 属性字符串模式管理 | setStyledString/getStyledString/onContentChanged/setStyledPlaceholder |
| Feat-04 | 文本排版与显示优化 | enableAutoSpacing/compressLeadingPunctuation/punctuationOverflow/includeFontPadding/fallbackLineSpacing/orphanCharOptimization/horizontalScrolling/singleLine/undoStyle/maxLength/maxLines |
| Feat-05 | 视觉样式与交互反馈 | caretColor/selectedBackgroundColor/scrollBarColor/barState/placeholder/selectedDragPreviewStyle/stopBackPress/enableHapticFeedback |
| Feat-06 | 键盘与输入法交互 | customKeyboard/enableKeyboardOnFocus/enterKeyType/keyboardAppearance/enablePreviewText/aboutToIMEInput/onDidIMEInput/onIMEInputComplete/onWillAttachIME |
| Feat-07 | 编辑生命周期与内容变化事件 | onReady/onEditingChange/onSubmit/aboutToDelete/onDeleteComplete/onWillChange/onDidChange/onSelect/onSelectionChange |
| Feat-08 | 光标选择与编辑状态控制 | getCaretOffset/setCaretOffset/getCaretRect/setSelection/getSelection/closeSelectionMenu/isEditing/stopEditing/scrollToVisible/getTypingStyle/setTypingStyle/setTypingParagraphStyle/getLayoutManager/getPreviewText |
| Feat-09 | 剪贴板、数据检测与菜单定制 | onPaste/onCut/onCopy/copyOptions/enableDataDetector/dataDetectorConfig/enableSelectedDataDetector/bindSelectionMenu/editMenuOptions |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 组件创建后无法编辑 | `rich_editor_pattern.cpp` `OnAttachToFrameNode`、`OnModifyDone`；确认 Controller 是否正确绑定 |
| 双模式选择错误 | `rich_editor_model_ng.cpp` `InitRichEditorModel`；检查 `isStyledStringMode` 参数；`text_pattern.h` `isSpanStringMode_` |
| Span 添加后 maxLength 截断异常 | `rich_editor_pattern.cpp` 搜索 `CalculateTruncationLength`、`SYMBOL_SPAN_LENGTH`；不同 Span 类型字符长度约定不同 |
| onContentChanged 不触发 | `rich_editor_pattern.cpp` 搜索 `ReportAfterContentChangeEvent`、`AfterStyledStringChange`；`setStyledString` 不触发 `onContentChanged` |
| selectedBackgroundColor 不透明度异常 | `rich_editor_pattern.cpp` 搜索 `selectedBackgroundColor_`；Alpha=255 时自动降为 0.2 不透明度 |
| 光标/选区操作在预览态失效 | `rich_editor_pattern.cpp` 搜索 `IsPreviewTextInputting`；预览态拒绝光标/选区操作 |
| copyOption 默认值不一致 | `text_pattern.h` 基类默认 None；`rich_editor_pattern.cpp` `OnModifyDone` 缺省值 Local |
| getSelection 返回类型不同 | 旧框架模式返回 `RichEditorSelection`（含 spans）；属性字符串模式返回 `RichEditorRange`（仅 start/end） |
| 模式切换不生效 | 动态路径不支持创建后切换；静态路径通过 `RichEditorModelStatic::SetStyledStringMode` 切换 |

## 调试入口

- **Dump 机制**：通过 `hilog` 搜索 `RichEditor` 标签，或使用 `hidumper` 查看组件树中的 RichEditor 节点状态。
- **Inspector**：通过 DevTools Inspector 查看组件树结构，确认 RichEditorContentPattern 子节点是否存在。
- **Trace**：在 `rich_editor_pattern.cpp` 中搜索 `ACE_TRACE_*` 宏定位性能瓶颈。
- **Layout**：通过布局边界显示功能检查段落布局和选区矩形。

## 相关主题

- [Text](text.md) — 基础文本组件，RichEditor 继承自 TextPattern
- [SpanString / 属性字符串] — MutableSpanString 和 StyledString 实现
- [Scroll](../../capabilities/) — 滚动能力，RichEditor 继承 ScrollablePattern
- [TextInput / TextArea] — 文本输入组件，共享 TextInputClient 接口
- [Drag & Drop](../../capabilities/) — 拖拽框架，RichEditor 集成拖拽能力
- [Safe Area](../../capabilities/safe-area.md) — 安全区机制，RichEditor 集成键盘避让