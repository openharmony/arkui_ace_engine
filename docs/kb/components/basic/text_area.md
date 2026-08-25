# TextArea Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextArea`

## 定位

TextArea 是 ArkUI 的多行文本输入组件，面向应用侧提供多行文本输入、占位文本、光标/选区控制、键盘/IME 交互、自动填充、输入过滤与计数、编辑事件回调等能力。

TextArea 与 TextInput 共用 `TextFieldPattern`，通过 `TEXTAREA_ETS_TAG` 标签与 `PlaceholderMaxLines=Infinity` 配置使 `IsTextArea()` 返回 true，在运行时区分多行行为。TextArea 没有独立的 Pattern/Model/Controller 类实例，全部复用 `text_field` 模块。

本文档用于快速定位 TextArea 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、光标、选区、IME、编辑事件 | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.cpp` | TextArea 实际使用的 Pattern（含 IsTextArea/SetCaretPosition/SetSelectionFlag/StopEditing） |
| Pattern 类型和扩展接口 | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.h` | `TextFieldPattern` 类型、`IsTextArea()` 判别、控制器相关接口 |
| Controller（caretPosition/setTextSelection/stopEditing） | `frameworks/core/components_ng/pattern/text_field/text_field_controller.cpp` | `TextFieldController` 实现，TextArea 与 TextInput 共用 |
| Controller 基类（= TS TextContentControllerBase） | `frameworks/core/components_ng/pattern/text_field/text_field_model.h` | `TextFieldControllerBase` 抽象基类、`SelectionOptions`/`MenuPolicy` 定义 |
| Dynamic Model（创建入口） | `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp` | `CreateTextArea`/`CreateTextAreaNode` 创建节点 |
| Static Model | `frameworks/core/components_ng/pattern/text_field/text_field_model_static.cpp` | 静态版 Model 代理 |
| 属性存储 | `frameworks/core/components_ng/pattern/text_field/text_field_layout_property.h` | 字体、行布局、占位、输入类型等属性声明 |
| Paint 属性 | `frameworks/core/components_ng/pattern/text_field/text_field_paint_property.h` | 光标颜色、选区背景色、占位颜色 flag 等 paint 属性 |
| 事件存储和触发 | `frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h` | onChange/onEditChange/onWillChange/onWillInsert/onDidInsert/onWillDelete/onDidDelete/onCopy/onWillCopy/onCut/onWillCut/onPaste 回调 |
| 布局算法 | `frameworks/core/components_ng/pattern/text_field/text_field_layout_algorithm.cpp` | 文本测量、溢出截断、自适应字号、行布局等 |
| 多线程变体 | `frameworks/core/components_ng/pattern/text_field/text_field_pattern_multi_thread.cpp` | SetCaretPositionMultiThread/SetSelectionFlagMultiThread/StopEditingMultiThread |
| 内容绘制 | `frameworks/core/components_ng/pattern/text_field/text_field_content_modifier.cpp` | textValue_/placeholderValue_ 渲染属性 |
| 绘制方法 | `frameworks/core/components_ng/pattern/text_field/text_field_paint_method.cpp` | 光标/选区/占位推送、滚动偏移报告 |
| 选区覆盖层 | `frameworks/core/components_ng/pattern/text_field/text_field_select_overlay.cpp` | 手柄、菜单、放大镜管理 |
| 文本选择控制器 | `frameworks/core/components_ng/pattern/text_field/text_select_controller.cpp` | 选区手柄移动、选区变化报告 |
| 内容控制器 | `frameworks/core/components_ng/pattern/text_field/content_controller.cpp` | text 值运行时存储、inputFilter 正则过滤、maxLength 截断 |
| 主题默认值 | `frameworks/core/components/text_field/textfield_theme.h` | 字体颜色、字号、字重、占位色、光标色等主题默认值 |
| TextArea Pattern 头文件（死代码/脚手架） | `frameworks/core/components_ng/pattern/text_area/text_area_pattern.h` | `TextAreaPattern` 声明但从未实例化，TextArea 复用 `TextFieldPattern` |
| 标签定义 | `frameworks/core/components_v2/inspector/inspector_constants.h` | `TEXTAREA_ETS_TAG` 常量 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_area.d.ts` | 动态 ArkTS `TextAreaInterface`、`TextAreaAttribute`、`TextAreaOptions`、`TextAreaController`、`TextAreaType` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/textArea.static.d.ets` | 静态 ArkTS TextArea 组件、属性、options、`setTextAreaOptions` 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/TextAreaModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/TextAreaModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | `NODE_TEXT_AREA_*` 属性和事件枚举（`ARKUI_NODE_TEXT_AREA = 8`） |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `TextAreaAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `TextAreaOptions` 或 `TextArea(`。
- 控制器：在 SDK 文件中搜索 `TextAreaController`（`caretPosition`/`setTextSelection`/`stopEditing`）。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_TEXT_AREA`。
- 动态版与静态版差异：动态版 `text_area.d.ts` 保留各 API 历史 `@since`（7/8/10/12/...）；静态版 `textArea.static.d.ets` 统一标注 `@since 23 static`，新属性按 24 static/26.0.0 static 标注。`setTextAreaOptions` 为静态专属未发布 API（`@since 26.1.0 staticonly @unpublished`）。

### API 解析实现路径

TextArea **已完成组件化改造**，拥有独立的 `pattern/text_area/bridge/` 子目录和动态模块。编译产物为独立 `libarkui_text_area.z.so`。旧 JSView `js_textarea.cpp` 仅保留为 39 行控制器别名桩。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arktextarea.ts` | `JSTextArea` 前端组件类、`ArkTextAreaComponent`、`TextAreaInitializeModifier` |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/text_area/bridge/arkts_native_text_area_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析；`CheckRegexValid` 校验 inputFilter 正则 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/text_area/bridge/text_area_dynamic_modifier.cpp` | 动态属性路径，`CreateTextArea` 入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/text_area/bridge/text_area_static_modifier.cpp` | 静态编译路径，`ConstructImpl`/`SetTextAreaOptionsImpl`/`ProcessBindableText`/全部 `SetXxxImpl` |
| Dynamic Module | `frameworks/core/components_ng/pattern/text_area/bridge/text_area_dynamic_module.cpp` | `TextAreaDynamicModule` 派生类，`OHOS_ACE_DynamicModule_Create_TextArea` 入口 |
| Dynamic Module 声明 | `frameworks/core/components_ng/pattern/text_area/bridge/text_area_dynamic_module.h` | 动态模块类型声明 |
| 模型加载器 | `frameworks/core/components_ng/pattern/text_area/bridge/text_area_model_common.h` | `GetTextFieldModelImpl` 动态模型加载 |
| 自定义 Modifier | `frameworks/core/components_ng/pattern/text_area/bridge/text_area_custom_modifier.h` | 自定义 Modifier 辅助 |
| C API 实现层 | `frameworks/core/interfaces/native/implementation/text_area_modifier.cpp` | Arkoala 静态版 C++ 桥接实现 |
| C API 控制器对端 | `frameworks/core/interfaces/native/implementation/text_area_controller_peer.h` | `TextAreaControllerPeer`（C-API 控制器对端） |
| C API 控制器访问器 | `frameworks/core/interfaces/native/implementation/text_area_controller_accessor.cpp` | `CaretPositionImpl`/`SetTextSelectionImpl`/`StopEditingImpl` |
| C API 基类对端 | `frameworks/core/interfaces/native/implementation/text_content_controller_base_peer.h` | `TextContentControllerBasePeer` 基类 |
| C API 枚举 | `interfaces/native/native_node.h` | `NODE_TEXT_AREA_*` 属性和事件枚举 |
| C API 事件转换 | `interfaces/native/node/event_converter.cpp` | `NODE_TEXT_AREA_ON_CHANGE`/`ON_EDIT_CHANGE`/`ON_SUBMIT`/`ON_INPUT_FILTER_ERROR` 等事件转换 |
| C++ JS 控制器桩 | `frameworks/bridge/declarative_frontend/jsview/js_textarea.cpp` | 39 行桩，别名 `JSTextEditableController` 为 `"TextAreaController"` |
| 共享控制器实现 | `frameworks/bridge/declarative_frontend/jsview/js_text_editable_controller.cpp` | `CaretPosition`/`SetTextSelection`/`StopEditing` 实现（含 API 12 负值钳制 guard） |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/text_area_modifier.ts` | `TextAreaModifier` 类，lazy-load `arkui.components.arktextarea` |

独立 so 名称：`libarkui_text_area.z.so`。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 输入法（IME） | `frameworks/core/common/ime/input_method_manager.h` | `inputmethod_imf` | `interfaces/inner_api/` | `InputMethodManager`/`InputMethodController` 键盘 attach/detach |
| 剪贴板 | `frameworks/core/common/clipboard/clipboard_proxy.h` | `miscservices_pasteboard` | `interfaces/innerkits/` | `ClipboardProxy` 复制/剪切/粘贴数据 |
| 振动反馈 | `frameworks/core/common/vibrator/vibrator_utils.h` | `sensors_miscservices` | `interfaces/innerkits/` | `VibratorUtils` 长按/手柄拖动振动（需 `ohos.permission.VIBRATE`） |
| 排版引擎 | `frameworks/core/components_ng/render/adapter/txt_paragraph.cpp`、`frameworks/core/components/font/constants_converter.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | Rosen Typography 段落排版、断词/断行/省略 |
| 图形渲染 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `graphic_2d` | `rosen/modules/render_service_base/include/` | RSNode/RSCanvas 绘制 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 组件测试 | `test/component_test/test_cases/components/text_and_input/entry/src/main/ets/pages/text_area` | TextArea 组件级 UI/交互测试 |
| Pattern 单测（共享） | `test/unittest/core/pattern/text_input/` | TextArea 与 TextInput 共用 Pattern 单测 |

### 相关 Spec

| Spec | 路径 | 覆盖范围 |
|------|------|----------|
| Design | `specs/05-ui-components/09-text-components/05-text-area/design.md` | 架构设计基线（DESIGN-Func-05-09-05） |
| Feat-01 | `specs/05-ui-components/09-text-components/05-text-area/Feat-01-content-creation-controller-spec.md` | 内容创建与控制器 |
| Feat-02 | `specs/05-ui-components/09-text-components/05-text-area/Feat-02-font-text-styles-spec.md` | 字体与文本样式 |
| Feat-03 | `specs/05-ui-components/09-text-components/05-text-area/Feat-03-layout-overflow-spec.md` | 行布局与溢出截断 |
| Feat-04 | `specs/05-ui-components/09-text-components/05-text-area/Feat-04-keyboard-ime-spec.md` | 键盘与输入法交互 |
| Feat-05 | `specs/05-ui-components/09-text-components/05-text-area/Feat-05-caret-selection-clipboard-spec.md` | 光标选择与剪贴板 |
| Feat-06 | `specs/05-ui-components/09-text-components/05-text-area/Feat-06-editing-events-spec.md` | 编辑事件回调 |

Spec 检索建议：在 `specs/registry/features.yaml` 中搜索 `05-09-05` 获取 Feat 列表与状态。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| TextArea 行为与 TextInput 不一致 | 搜索 `IsTextArea()` 在 `text_field_pattern.cpp` 中的分支；`TEXTAREA_ETS_TAG` 创建路径 |
| TextArea 为何没有独立 Pattern | `text_area_pattern.h` 为死代码/脚手架；`CreateTextAreaNode` 创建 `TextFieldPattern` |
| `caretPosition` 负值行为差异 | `js_text_editable_controller.cpp` 中 `GreatOrEqualTargetAPIVersion(VERSION_TWELVE)` guard；C-API 访问器始终钳制 |
| `setTextSelection` 不立即生效 | `text_field_controller.cpp` `SetTextSelection` 使用 `ScheduleTaskWithLayoutDeferral` 延迟 |
| `stopEditing` 不关闭键盘 | `text_field_pattern.cpp` `StopEditing` 在 `!HasFocus()` 时幂等返回 |
| `text` Bindable 双向绑定不生效 | `text_area_static_modifier.cpp` `ProcessBindableText`；`Bindable<Resource>` 为 no-op（SDK 注释"应删除"） |
| `placeholderColor` 双存储 | `SetPlaceholderColor` 写 LayoutProperty `PlaceholderTextColor` + paint `PlaceholderColorFlagByUser`；paint `PlaceholderColor` 字段为 inspector-only |
| `strokeWidth` 负值渲染异常 | `constants_converter.cpp` 负值切换 RSBrush fill 模式（用 textColor） |
| `shaderStyle` gradient/color 冲突 | `text_field_model_ng.cpp` 互斥 reset；color shader 仅 `strokeWidth=0` 时构造 brush |
| `maxLines` 拆写为多属性 | `text_area_static_modifier.cpp` `SetMaxLinesImpl` 拆写 `MaxViewLines`/`NormalMaxViewLines`/`OverflowMode` |
| `horizontalScrolling` 静态版不生效 | `text_area_static_modifier.cpp` `SetHorizontalScrollingImpl` 为 no-op 桩，实际经动态桥 |
| `textDirection` 不生效 | algorithm 成员 `direction_`/`textDirection_` 不重赋；主段落方向由内容推导 |
| `style(INLINE)` 不生效 | `IsNormalInlineState()` 需 `InputStyle==INLINE` 且 `TextInputType` 为 `UNSPECIFIED`/`TEXT` |
| `enablePreviewText` 预览不触发 Will/Did 回调 | 预览走 `SET_PREVIEW_TEXT`/`SET_PREVIEW_FINISH` 独立操作队列，绕过 `ExecuteInsertValueCommand` |
| `onWillInsert`/`onDidInsert` 不触发 | 仅 `isIMEOrAutoFill=true` 触发；编程式插入不触发 |
| `maxLength` 超限不抖动 | `showCountBorderStyle_` + `HandleCountStyle` + `UltralimitShake`；需配合 `showCounter` |
| `copyOption(None)` 仍可拖拽 | `InitDragEvent` 检查 `GetCopyOptionsValue != None`；None 应禁用拖拽 |
| `caretColor` 手柄颜色不一致 | API12 起手柄颜色=光标颜色；API<12 手柄用主题色 |
| `selectedBackgroundColor` 透明度异常 | 不透明输入(alpha=255) 自动 `ChangeOpacity(0.2)` |
| `customKeyboard` 返回键不关闭 | `stopBackPress=false` 时警告；需 `stopBackPress=true` |
| `voiceButton` 不显示 | `IsShowVoiceButtonMode()` 需非 INLINE + type=UNSPECIFIED/TEXT + 无自定义键盘 |
| `setTextAreaOptions` 动态版不存在 | 静态专属未发布 `@since 26.1.0 staticonly @unpublished` |

## 调试入口

- **Inspector/Dump**：TextArea 节点 tag 为 `"TextArea"`，可通过 `Inspector` 或 `dump` 命令验证 tag、`IsTextArea()`、属性值。
- **日志 tag**：`ACE_TEXT_FIELD`（`text_field_pattern.cpp` 中 `TAG_LOGI`）。
- **API 版本边界**：搜索 `GreatOrEqualTargetAPIVersion` / `LessThanAPITargetVersion` 在 `text_field` 模块中的 guard。
- **组件化验证**：`grep '"TextArea"' adapter/ohos/osal/dynamic_module_helper.cpp` 确认已组件化。
- **C API 枚举**：在 `interfaces/native/native_node.h` 中搜索 `NODE_TEXT_AREA`。

## 相关主题

| 主题 | 关系 |
|------|------|
| [Text](text.md) | 文本显示组件，与 TextArea 共享排版引擎属性（fontColor/fontSize/letterSpacing 等）但 Pattern 独立 |
| TextInput | 单行文本输入组件，与 TextArea 共用 `TextFieldPattern`/`TextFieldController`/`TextFieldModelNG`，靠 `IsTextArea()` 区分 |
| RichEditor | 富文本编辑器，独立 Pattern，不与 TextArea 共用 |
| Search | 搜索框组件，独立 Pattern |
| 字体注册 | TextArea `fontFamily` 支持注册自定义字体 |
| 文本测量 | TextArea 布局经 Rosen Typography 段落排版 |
| 输入交互 | TextArea 光标/选区/键盘/IME 经 `text_field` 模块共享能力 |
