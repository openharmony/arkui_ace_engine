# Input Method Interaction Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `InputMethodInteraction`

## 定位

输入法交互（Input Method Interaction）是 ArkUI **输入框↔键盘（虚拟 IME + 实体）交互**的框架能力。**不是**焦点导航（Tab/Esc/Enter 激活属焦点机制，见相关主题）。本域覆盖：IME 弹出/收起控制、与 IME 框架的交互、输入框避让显示、实体键盘切换契约、键盘输入处理契约。关键架构事实：**SHOW 由输入框驱动**（`RequestKeyboard`→`inputMethod->Attach`），**HIDE 由框架驱动**（`InputMethodManager`）；仅 `onWillAttachIME` 已实现（无 Will-Detach/Did-Attach）；实体键盘检测经全仓检索确认不在本仓（属外部 IME 框架 `MiscServices::InputMethodController`）。行为事实以源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| IME 框架管理器（HIDE 编排） | `frameworks/core/common/ime/input_method_manager.h` + `adapter/ohos/osal/input_method_manager_ohos.cpp` | `InputMethodManager`：`OnFocusNodeChange`/`ManageFocusNode`/`ProcessKeyboard`/`ProcessKeyboardInWindowScene`/`CloseKeyboard*`(6)/`CloseCustomKeyboard`/`HideKeyboardAcrossProcesses`/`ProcessModalPageScene`/`NeedSoftKeyboard`；状态 `curFocusNode_`/`lastFocusNodeId_`/`lastTextInputSessionId_`/`lastKeep_`/`isLastFocusUIExtension_` |
| 跨平台 IME attach | `adapter/preview/osal/input_method_manager_preview.cpp` | `ShowKeyboard`/`Attach`/`SetEditingState`/`FinishComposing`/`CloseKeyboard(instanceId)`（CROSS_PLATFORM 面） |
| 输入框 attach/show（SHOW） | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.h/.cpp` | `RequestKeyboard`(OnTextChangedListenerImpl+GetIMEClientInfo+FireOnWillAttachIME+`inputMethod->Attach`，`attachOptions.isShowKeyboard`)/`CloseKeyboard`/`RequestCustomKeyboard`/`SetCustomKeyboardOption`(supportAvoidance)/`TriggerAvoidOnCaretChange` |
| RichEditor attach/show | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h/.cpp` | `RequestKeyboard`(FireOnWillAttachIME+Attach)/`CloseKeyboard`/`ForceTriggerAvoidOnCaretChange` |
| Search attach | `frameworks/core/components_ng/pattern/search/search_pattern.h/.cpp` | `RequestKeyboard`→委托 `textFieldPattern->SearchRequestKeyboard` |
| IME 回调 hub | `frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h`、`.../rich_editor/rich_editor_event_hub.h` | 仅 `SetOnWillAttachIME`/`FireOnWillAttachIME`/`onWillAttachIME_`+`IMEClient{nodeId,extraInfo}` |
| IME→输入框桥 | `frameworks/core/components_ng/pattern/text_field/on_text_changed_listener_impl.h/.cpp` | `InsertText`→`InsertValue(isIME)`/`DeleteBackward`/`Forward`/`MoveCursor(Direction→CaretMoveIntent)`/`HandleSelect(keyCode→CaretMoveIntent)`/`HandleSetSelection`/`HandleExtendAction`/`SetKeyboardStatus`/`NotifyKeyboardHeight`/`NotifyPanelStatusInfo`/`SetPreviewText`/`FinishTextPreview`/`ReceivePrivateCommand`/`OnDetach`，全 `PostTaskToUI` |
| 输入处理契约 | `frameworks/core/common/ime/text_input_client.h/.cpp` | `TextInputClient` 抽象（IME 与物理键共用：`UpdateEditingValue`/`InsertValue(isIME)`/`DeleteBackward`/`Forward`/`HandleSetSelection`/`HandleKeyEvent`/`CursorMove`/`HandleSelect`/`SetSelection`/`SetPreviewText`/`FinishTextPreview`） |
| 合成态 | `frameworks/core/common/ime/text_editing_value.h`、`text_compose.h` | IME 合成态；`FinishComposing` 仅 CROSS_PLATFORM `InputMethodManager` |
| 避让模式枚举 | `frameworks/core/components/common/layout/constants.h` | `KeyBoardAvoidMode`(OFFSET/RESIZE/OFFSET_WITH_CARET/RESIZE_WITH_CARET/NONE) |
| 避让机制（引用） | `frameworks/core/components_ng/manager/safe_area/safe_area_manager.h/.cpp` | `UpdateKeyboardSafeArea`/`GetKeyboardInset`(NONE-gated)/`keyboardInset_`/`GetKeyBoardAvoidMode`（机制归 04-02-01 Feat-05） |
| 公共 API bridge | `frameworks/bridge/declarative_frontend/ark_modifier/src/text_input_modifier.ts`、`rich_editor_modifier.ts` | `customKeyboard`/`keyboardAppearance`/`enableKeyboardOnFocus`/`onWillAttachIME`/`onEditChange` |
| Model 层 | `.../text_field/text_field_model.h`/`text_field_model_ng.h`、`.../rich_editor/rich_editor_model.h`、`.../search/search_model.h` | `SetOnWillAttachIME`/`SetCustomKeyboardWithNode` |
| ArkTS native bridge | `.../rich_editor/bridge/arkts_native_rich_editor_bridge.h` | `SetEnableKeyboardOnFocus`/`SetOnWillAttachIME` |

### API 入口

无独立公共 API（框架内部）。文本组件输入法交互公共 API（`customKeyboard`/`keyboardAppearance`/`enableKeyboardOnFocus`/`onWillAttachIME`/`onEditChange`/`stopEditing`+`IMEClient` 类型）经文本组件 `CommonMethod` 暴露，`@since 8–12`（动态）/`@since 23`（静态），属本域输入法交互语义。Window/UIContext `setKeyboardAvoidMode`+`KeyboardAvoidMode`（@since 11）在 `@ohos.arkui.UIContext.d.ts`（外部 SDK 仓），C-API 镜像 `frameworks/core/interfaces/arkoala/arkoala_api.h`。键事件类型 `KeyCode`/`KeyEvent` 属未来 04-04-02（引用）。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| IME 框架 | `RequestKeyboard`→`Attach`、`InputMethodManager`→`Close` | `miscservices_inputmethod` | `input_method_controller.h`（外部 SDK 头） | `MiscServices::InputMethodController` 附挂/关闭/跨进程隐藏；**软硬切换决策与实体键盘检测在外部仓**（本仓仅传 `isShowKeyboard`+消费面板状态，经全仓检索确认无 IsPhysicalKeyboard/InputDeviceManager） |
| 避让机制 | `TriggerAvoidOnCaretChange`→`textFieldManager` | ace_engine 内 04-02-01 | `safe_area_manager.*` | inset 同步/Page offset/resize/OverlayManager 归 04-02-01 Feat-05 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测（IME 管理器） | `test/mock/frameworks/core/common/ime/mock_input_method_manager.cpp`、`test/unittest/core/pipeline/mock_input_method_manager.cpp` | InputMethodManager mock |
| 单测（输入框 attach/避让） | `test/unittest/core/pattern/text_input/`、`.../text_field/` | RequestKeyboard/CloseKeyboard/TriggerAvoidOnCaretChange |
| 单测（RichEditor） | `test/unittest/core/pattern/rich_editor/` | RequestKeyboard/ForceTriggerAvoidOnCaretChange |
| 单测（IME 桥） | `test/unittest/core/pattern/text_field/`（on_text_changed_listener 相关） | OnTextChangedListenerImpl 桥 |

### 相关 Spec

| Spec 域 | 路径 | 状态 |
|---------|------|------|
| 输入法交互长期规格（重定范围：输入框↔键盘交互） | `specs/04-common-capability/14-input-interaction/04-input-method-interaction/` | active（5 个 Feat：IME 框架交互与弹出收起控制/输入框避让显示/实体键盘切换/键盘输入处理契约/输入法交互公共 API） |
| 边界：文本编辑快捷键 | `specs/04-common-capability/14-input-interaction/02-text-shortcuts/` | active（04-14-02 拥有快捷键表；本域拥有 HandleKeyEvent 契约面） |
| 边界：编辑拦截回调 | `specs/04-common-capability/14-input-interaction/03-text-interaction/` | active（Feat-04 拥有 onWillInsert/onDidInsert 等消费本域契约；onWillAttachIME 等输入法交互语义归本域） |
| 边界：避让机制 | `specs/04-common-capability/02-safe-area/01-safe-area-mechanism/` | active（Feat-05 键盘避让机制；本域仅输入框侧响应） |
| 边界：焦点导航 | 未来 `04-04-02 key-events`/`04-09-01 focus-mechanism` | 未建（Tab 遍历/Enter 激活/Esc 关闭属焦点机制，不在此域） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 键盘不弹出 | `RequestKeyboard`(`showKeyBoardOnFocus_`+`HasFocus`+`NeedSoftKeyboard`)→`Attach`；检查 `enableKeyboardOnFocus` |
| 键盘不收起 | `InputMethodManager` `OnFocusNodeChange`→`ManageFocusNode`→`ProcessKeyboard`/`CloseKeyboard(focusNode)`；`NeedSoftKeyboard` 判定 |
| 自定义键盘异常 | `RequestCustomKeyboard` + `SetCustomKeyboardOption(supportAvoidance)`→`keyboardAvoidance_` |
| 输入框被键盘遮挡 | `KeyBoardAvoidMode`(默认 OFFSET)；`TriggerAvoidOnCaretChange`；自定义键盘 `supportAvoidance`；`setKeyboardAvoidMode`(@since 11) |
| IME 文本不插入 | `OnTextChangedListenerImpl::InsertText`→`PostTaskToUI`→`InsertValue(isIME=true)` |
| IME 删除/光标异常 | `DeleteBackward`/`Forward`/`MoveCursor(Direction→CaretMoveIntent)`/`HandleSelect(keyCode→CaretMoveIntent)` |
| onWillAttachIME 不触发 | `FireOnWillAttachIME`(attach 前 fire，仅 Will-attach 实现，无 Will-Detach/Did-Attach) |
| 实体键盘软键盘切换异常 | 检测不在本仓（无 IsPhysicalKeyboard/InputDeviceManager），决策属外部 IME；本仓仅传 `isShowKeyboard`+消费 `NotifyPanelStatusInfo`/`SetKeyboardStatus` |
| 跨进程键盘不隐藏 | `HideKeyboardAcrossProcesses`(UIExtension) |

## 调试入口

Dump：`InputMethodManager` 状态（`curFocusNode_`/`lastFocusNodeId_`/`lastTextInputSessionId_`/`lastKeep_`/`isLastFocusUIExtension_`/`windowFocus_`）；`SafeAreaManager::GetKeyBoardAvoidMode`/`keyboardInset_`；`OnTextChangedListenerImpl` 跨线程 `PostTaskToUI`。`NotifyKeyboardHeight` 追踪键盘高度。

## 相关主题

- [Text Shortcuts](./text-shortcuts.md)（文本编辑快捷键分发；共用 HandleKeyEvent 契约，本域拥有契约面，04-14-02 拥有快捷键表）
- [TextInput](../components/basic/text-input.md)（输入框 attach/show/close 宿主）
- [Safe Area Mechanism](./safe-area.md)（键盘避让机制，若存在）
- [Window Mechanism](../architecture/window-mechanism.md)（窗口场景键盘焦点交接）