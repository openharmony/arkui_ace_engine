# 文本交互 Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextInteraction`

## 定位

文本交互覆盖文本组件（Text/TextInput/TextArea/Search/RichEditor）的光标、上下文菜单、拖拽剪贴板、编辑拦截、交互触发与状态回调、长按选择与实体识别等能力。本域基线补录 Feat-01 光标（Caret）交互；Feat-02~06（菜单/拖拽剪贴板/编辑拦截/状态回调/长按实体识别）待后续补录。RichText 与放大镜（Magnifier）无公共 API，仅内部实现。

具体光标语义、版本分支、跨组件不对称与兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Text Pattern（光标颜色派发 + 选择宿主） | `frameworks/core/components_ng/pattern/text/text_pattern.h`、`text_pattern.cpp` | `UpdateCursorColor`/`GetCaretColor` |
| Text 布局属性（CursorColor） | `frameworks/core/components_ng/pattern/text/text_layout_property.h` | PROPERTY_UPDATE_MEASURE_SELF |
| Text 选择浮层 Modifier（消费 cursorColor） | `frameworks/core/components_ng/pattern/text/text_overlay_modifier.h`、`text_overlay_modifier.cpp` | 绘制光标颜色 |
| Text 选择浮层（句柄颜色） | `frameworks/core/components_ng/pattern/text/text_select_overlay.h`、`text_select_overlay.cpp` | `GetHandleColor` |
| TextField Pattern（光标位置/闪烁/绘制） | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.h`、`text_field_pattern.cpp` | `SetCaretPosition`/`StartTwinkling`/主题响应 |
| TextField 绘制属性（CursorColor/CursorWidth/CaretColorFlagByUser） | `frameworks/core/components_ng/pattern/text_field/text_field_paint_property.h` | PROPERTY_UPDATE_RENDER |
| TextField 浮层 Modifier（PaintCursor） | `frameworks/core/components_ng/pattern/text_field/text_field_overlay_modifier.h`、`text_field_overlay_modifier.cpp` | 光标绘制与闪烁 |
| TextField 控制器（CaretPosition/GetCaretPosition） | `frameworks/core/components_ng/pattern/text_field/text_field_controller.h`、`text_field_controller.cpp` | 控制器方法 |
| TextField 选择控制器（光标位置钳位） | `frameworks/core/components_ng/pattern/text_field/text_select_controller.h`、`text_select_controller.cpp` | `MoveCaretToContentRect`/`UpdateCaretIndex` clamp [0,length] |
| TextField ModelNG（SetCaretColor/SetCaretStyle/SetCaretPosition） | `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp`、`text_field_model_static.cpp` | 属性设置入口 |
| TextField 主题包装（cursorColor_=colors->Brand()） | `frameworks/core/components_ng/pattern/text_field/text_field_theme_wrapper.h` | token 默认值 |
| RichEditor Pattern（caretColor_/caretPosition_/GetCaretRelativeRect） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h`、`rich_editor_pattern.cpp` | 成员变量存储，无 dirty flag |
| RichEditor 控制器（GetCaretOffset/GetCaretRect/SetCaretOffset） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_base_controller.cpp` | 控制器方法 |
| RichEditor 浮层 Modifier（PaintCaret/PaintFloatingCaret） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h`、`rich_editor_overlay_modifier.cpp` | 光标绘制与闪烁 |
| RichEditor 动态 Modifier（C-API 桥接） | `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp` | `SetRichEditorCaretColor` 等 |
| RichEditor 主题（caret_color #007DFF） | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_theme.h`、`rich_editor_theme.cpp` | 默认值 |
| Text 主题（text_care_color fallback #006CDE） | `frameworks/core/components/text/text_theme.h`、`text_theme.cpp` | legacy 主题 fallback |
| Text 主题包装 | `frameworks/core/components_ng/pattern/text/text_theme_wrapper.h` | 主题包装 |
| JS Bridge（Text/TextField/Controller/RichEditor） | `frameworks/bridge/declarative_frontend/jsview/js_text.cpp`、`js_textfield.cpp`、`js_text_editable_controller.cpp`、`js_richeditor.cpp` | 参数解析、API 12 版本分支 |
| 静态 Modifier（RichEditor） | `frameworks/bridge/declarative_frontend/ark_component/src/ArkRichEditor.ts` | RichEditorCaretColorModifier |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态 Text/TextInput/TextArea/RichEditor | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text.d.ts`、`text_input.d.ts`、`text_area.d.ts`、`rich_editor.d.ts` | caretColor（@since 7/9/12/14 不一致）/caretStyle/caretPosition |
| 静态 Text/TextInput/TextArea/RichEditor | `<OH_ROOT>/interface/sdk-js/api/arkui/component/text.static.d.ets`、`textInput.static.d.ets`、`textArea.static.d.ets`、`richEditor.static.d.ets` | @since 23 static |
| 共享类型（CaretStyle/TextEditControllerEx/TextRange/RectResult） | `<OH_ROOT>/interface/sdk-js/api/arkui/component/textCommon.static.d.ets`、`common.static.d.ets` | CaretStyle{width,color} @since 23 static |
| C-API 枚举（NODE_TEXT_*_CARET_*） | `interfaces/native/native_node.h` | NODE_TEXT_INPUT_CARET_COLOR/STYLE/OFFSET、NODE_TEXT_AREA_CARET_COLOR、NODE_TEXT_EDITOR_CARET_COLOR（@since 24） |
| C-API 派发 | `interfaces/native/node/style_modifier.cpp` | `SetCaretColor`/`SetCaretStyle`/`SetTextInputCaretOffset` |
| C-API TextInput 实现 | `frameworks/core/interfaces/native/node/node_text_input_modifier.cpp` | `SetTextInputCaretColor`/`SetTextInputCaretStyle`（仅 width） |
| C-API TextArea 实现 | `frameworks/core/interfaces/native/node/node_text_area_modifier.cpp` | `SetTextAreaCaretColor`/`SetTextAreaCaretStyle`（width+color，但 caretStyle 未接入 NDK 派发表） |
| C-API RichEditor 实现 | `interfaces/native/node/rich_editor_native_impl.cpp` | `OH_ArkUI_TextEditorStyledStringController_SetCaretOffset/GetCaretOffset/GetCaretRect`（@since 24） |
| C-API 类型 | `interfaces/native/native_type.h` | RichEditor 光标 NDK 函数签名 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/rich_editor/rich_editor_caret_test_ng.cpp` | RichEditor 光标 |
| 单元测试 | `test/unittest/core/pattern/text_input/` | TextInput 光标位置/控制器 |

### 相关 Spec

| Spec 域 | 路径 |
|---------|------|
| 功能域 design | `specs/04-common-capability/14-input-interaction/03-text-interaction/design.md` |
| Feat-01 光标(Caret)交互 | `specs/04-common-capability/14-input-interaction/03-text-interaction/Feat-01-caret-interaction-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| caretColor 默认值跨组件不一致 | Text fallback #006CDE（`text_theme.cpp`）；TextField token `colors->Brand()`；RichEditor #007DFF（与 SDK 文档一致） |
| caretStyle.color 与 caretColor 写同一字段无优先级 | last-write-wins；C-API NODE_TEXT_INPUT_CARET_STYLE 仅设宽不设色（与 ArkTS 不对称） |
| caretPosition 负值行为 API 12 变更 | `js_textfield.cpp` VERSION_TWELVE 分支：API<12 早退不操作；API>=12 负值钳为 0 |
| setCaretOffset 超范围返回 false 不移动（RichEditor） vs caretPosition 超范围钳位到末尾（TextInput） | 语义源于返回类型：RichEditor 返 boolean 有诊断价值；TextInput 返 void 只能钳位 |
| getCaretOffset 动态返 -1 哨兵 vs 静态返 undefined | 动态 API 历史更久用 -1；静态 API 后设计用 undefined 类型安全 |
| getCaretRect 未聚焦返回 undefined | 依赖 `caretTwinkling_` 状态，未闪烁无可见光标 |
| TextArea 缺 caretStyle C-API | `node_text_area_modifier.cpp` 实现完整但未接入 `style_modifier.cpp` 派发表 |
| 光标颜色变更不触发重绘 | Text=PROPERTY_UPDATE_MEASURE_SELF；TextField=PROPERTY_UPDATE_RENDER；RichEditor 无 dirty flag 直接 UpdateHandleColor |

## 调试入口

- 光标颜色链路：`.caretColor(color)` → JS Bridge `ParseJsColor`（失败：Text fallback theme，TextField reset）→ Model → Property/Pattern → 绘制阶段 `OverlayModifier::PaintCursor` + 选择浮层 `handlerColor` 派发
- 光标位置链路（TextInput）：`.caretPosition(value)`/`controller.caretPosition(value)` → `TextFieldController::CaretPosition` → `TextFieldPattern::SetCaretPosition` → `MoveCaretToContentRect`（clamp）→ `UpdateCaretInfoToController` → `HasFocus()` 时 `StartTwinkling`
- 光标偏移链路（RichEditor）：`setCaretOffset` → `RichEditorBaseController::SetCaretOffset` → `RichEditorPattern::SetCaretOffset`（预览文本态守卫→AdjustSelector→SetCaretPosition clamp 失败返 false）

## 相关主题

- `TextSelection`（文本选择）— 选区状态模型与编程式选区
- `Text`、`TextInput`/`TextArea`、`RichEditor` 组件 — 光标承载组件
