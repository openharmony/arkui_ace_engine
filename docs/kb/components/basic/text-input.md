# TextInput Context

> 文档版本：v2.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `TextInput`

## 定位

TextInput 是单行文本编辑组件，与 TextArea **共享** `TextFieldPattern`/`TextFieldModelNG`；单行差异化在 `TextInputLayoutAlgorithm`（继承 `TextFieldLayoutAlgorithm`）。支持 IME/键盘、自动填充、光标/选择、will/did 拦截事件。公共 API 自 API 7 起步，11/12 atomicservice 大扩，13–26 持续增量。行为事实以 SDK 声明、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 共享 Model（Create/Set 全量） | `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.h` | `CreateTextInput` 静态工厂 + ~150 Set*/Reset*/Get* |
| Model 抽象 | `frameworks/core/components_ng/pattern/text_field/text_field_model.h` | `TextFieldModel` 虚接口 + `RichEditorStyledStringControllerBase` |
| 静态范式 Model | `frameworks/core/components_ng/pattern/text_field/text_field_model_static.h/.cpp` | 静态 ArkTS |
| 兼容 legacy | `frameworks/compatible/components/text_field/text_field_model_impl.h/.cpp` | legacy pipeline |
| 共享 Pattern（编辑/光标/选择/IME/自动填充） | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.h` | ~2637 行，与 TextArea 共享 |
| 单行布局算法 | `frameworks/core/components_ng/pattern/text_input/text_input_layout_algorithm.h` | 继承 `TextFieldLayoutAlgorithm`，MeasureContent/Layout/GetDefaultHeightByType/MeasureCounterWithPolicy/MeasureAutoFillIcon |
| 属性存储 | `frameworks/core/components_ng/pattern/text_field/text_field_layout_property.h` | Value/Placeholder/Type/ContentType/InputFilter/ShowCounter/ShowUnderline/CleanNodeStyle/FontStyle 组/TextLineStyle 组(含 MaxLength/LineHeight/WordBreak/TextOverflow/EllipsisMode/OrphanCharOptimization 等)/CopyOptions |
| Paint 属性 | `frameworks/core/components_ng/pattern/text_field/text_field_paint_property.h` | PlaceholderColor/CursorColor/CursorWidth/SelectedBackgroundColor/InputStyle/各 *FlagByUser |
| 内容类型枚举 | `frameworks/core/components_ng/pattern/text_field/text_content_type.h` | 38 值 TextContentType |
| 键盘类型 | `frameworks/core/components_ng/pattern/text_field/text_keyboard_common_type.h` | KeyboardAppearanceConfig/KeyboardGradientMode/KeyboardFluidLightMode |
| 事件 Hub | `frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h` | 编辑/内容事件 |
| 控制器 | `frameworks/core/components_ng/pattern/text_field/text_field_controller.h` | caretPosition/setTextSelection/stopEditing |
| 无障碍 | `frameworks/core/components_ng/pattern/text_field/text_field_accessibility_property.h` | + `userAccessibilityText` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_input.d.ts` | 公共契约 `TextInputAttribute`(~63)、`InputType`(14)/`ContentType`(38)/`EnterKeyType`/`TextInputStyle`/`PasswordIcon`/`UnderlineColor`/`SubmitEvent`/回调类型 |
| Static | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/typedNode/ArkTextInputNode.ets` | 静态 typed node |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/TextInputModifier.d.ts` | 动态 Modifier |
| C API | `interfaces/native/native_node.h`（`ARKUI_NODE_TEXT_INPUT=7`；attrs `NODE_TEXT_INPUT_*`；events `NODE_TEXT_INPUT_ON_*`） | NDK 面 |
| C API 枚举 | `interfaces/native/node_attributes/text_input.h` | `ArkUI_TextInputType`/`ArkUI_CancelButtonStyle`/`ArkUI_TextInputContentType`/`ArkUI_TextInputStyle` |
| C API modifier | `frameworks/core/interfaces/native/node/node_text_input_modifier.h` | `GetTextInputModifier()`/`GetCJUITextInputModifier()`/`GetTextInputCustomModifier()` |

### API 解析实现路径

TextInput 已完成组件化改造（在 `adapter/ohos/osal/dynamic_module_helper.cpp` 动态模块列表中，键 `"TextInput"`→模块 `"textfield"`，独立 so `libarkui_textfield.z.so`）。`js_textinput.cpp` 仅保留 `JSTextInputController`（Controller binding），无 `JSTextInput::Create`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arktextinput.ts`（动态）+ `ArkTextInputNode.ets`（静态） | 前端组件类 |
| 统一 Bridge | `frameworks/core/components_ng/pattern/text_input/bridge/arkts_native_text_input_bridge.cpp` | `TextInputBridge`，`RegisterTextInputAttributes` |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/text_input/bridge/text_input_dynamic_modifier.cpp` | `ArkUI_AttributeItem`→`TextFieldModelNG::Set*` 派发 |
| Static Modifier | `frameworks/core/components_ng/pattern/text_input/bridge/text_input_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/text_input/bridge/text_input_dynamic_module.cpp` | `TextInputDynamicModule`，`libarkui_textfield.z.so` 入口 |
| Custom Modifier | `frameworks/core/components_ng/pattern/text_input/bridge/text_input_custom_modifier.h` | `setKeyboardAppearanceConfig` 等 |
| Controller binding | `frameworks/bridge/declarative_frontend/jsview/js_textinput.cpp` | `JSTextInputController`（委托 `JSTextEditableControllerBinding`） |
| 键盘外观 helper | `frameworks/bridge/declarative_frontend/jsview/js_textfield.cpp` | `ParseKeyboardAppearanceConfig`/`SetKeyboardAppearanceConfig`/`SetSearchKeyboardAppearanceConfig` |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_text_input_modifier.h` | Set/Reset/Get + event Set/Reset |

组件化改造参考：`./组件化重构通用方案.md`（如存在）。改造后 JSView 与 Bridge 双路径统一到 `pattern/text_input/bridge/`，输出独立 so。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 输入法（IME） | `text_field_pattern.cpp`/`text_input_custom_modifier.h` | IME 适配 | — | IME attach/键盘拉起/keyboardAppearance |
| 自动填充 | `text_field_pattern.cpp` + `text_input_layout_algorithm.cpp`(MeasureAutoFillIcon) | 自动填充服务 | — | contentType 驱动自动填充 |
| 剪贴板/UDMF | `text_field_pattern.cpp`(onCopy/onCut/onPaste) | UDMF | — | 复制/剪切/粘贴 |
| 排版引擎 | `text_input_layout_algorithm.cpp`/`text_field_layout_algorithm.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | Typography 段落排版/测量 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测（单行） | `test/unittest/core/pattern/text_input/` | TextInput 单行 + onTextChangeListener |
| 单测（共享 Pattern） | `test/unittest/core/pattern/text_field/` | TextFieldPattern 共享逻辑 |
| C-API 单测 | `test/unittest/capi/modifiers/text_input_modifier_test.cpp`、`text_input_modifier_test2.cpp` | NDK 属性/事件 |

### 相关 Spec

| Spec 域 | 路径 | 状态 |
|---------|------|------|
| TextInput 长期规格 | `specs/05-ui-components/09-text-components/08-text-input/` | active（10 个 Feat：基础显示/Placeholder/输入类型/筛选计数器/光标选择/事件/键盘IME/密码自动填充/取消按钮/C-API 桥） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 输入不生效/IME 未拉起 | `type`/`enableKeyboardOnFocus`/`keyboardAppearance` + `text_field_pattern` IME attach |
| 光标/选择异常 | `text_field_paint_property.h`(CursorColor/CursorWidth) + `TextInputController` caretPosition/setTextSelection |
| maxLength/inputFilter 行为 | `text_field_layout_property.h` + `onInputFilterError` |
| 事件 will 拦截不生效 | `onWillChange`/`onWillInsert`/`onWillDelete` 返回 bool 管道（`OH_ArkUI_NodeEvent_SetReturnNumberValue`） |
| C-API 属性 id 跳号 @since 混排 | `native_node.h` `NODE_TEXT_INPUT_*`，id 7032+ 为增量（@since 15/16/18/20/22/23/24/26），见 Spec Feat-10 |
| `onEditChanged` 已废弃 | 改用 `onEditChange`（@deprecated since 8） |

## 调试入口

Dump：`TextFieldPattern` dump；属性经 `TextFieldLayoutProperty`/`PaintProperty` 查询。

## 相关主题

- [Text](./text.md)（共享排版基础）
- [StyledString](../capabilities/styled-string.md)（`SetPlaceholderStyledString`）
- [TextArea](./text-area.md)（共享 TextFieldPattern，若存在）
