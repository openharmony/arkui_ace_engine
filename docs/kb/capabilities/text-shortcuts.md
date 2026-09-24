# Text Shortcuts Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `TextShortcuts`

## 定位

文本快捷键（Text Shortcuts）是 ArkUI 文本编辑的**框架内部能力**（无公共 API）。键盘组合键经统一分发器 `TextInputClient::HandleKeyEvent` 查两静态加速表 `functionKeys_`/`keyboardShortCuts_`（~70 组合键→~20 handler）派发到各文本组件 handler。跨 Text(只读子集)/TextField(全量+undo 队列)/RichEditor(全量+三策略 undo+字体样式)/Search(委托 TextField) 四组件复用。行为事实以源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 分发器（核心） | `frameworks/core/common/ime/text_input_client.h/.cpp` | `KeyComb`/`CaretMoveIntent`(12 值)/`functionKeys_`/`keyboardShortCuts_` 两静态加速表/`HandleKeyEvent` 五级分发顺序 |
| 键事件基础 | `frameworks/core/event/key_code.h`、`key_event.h/.cpp`、`key_event_recognizer.h/.cpp` | `KeyCode` 枚举、`KeyEvent`、`HasKey`/`IsCtrlWith`/`IsShiftWith`/`IsDirectionalKey`/`ConvertCodeToString`、长按/重复识别 |
| TextField handler | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.h/.cpp` | `OnKeyEvent`/`CursorMove`/`HandleSelect`/`HandleOnUndoAction`/`HandleOnRedoAction`/`HandleOnCopy`/`HandleOnPaste`/`HandleOnCut`/`HandleOnDelete`/`HandleOnDeleteComb`/`HandleOnPageUp/Down`/`operationRecords_` |
| RichEditor handler | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h/.cpp` | 同上 + `HandleSelectFontStyle`(Ctrl+B/I/U) + `HandleOnExtendUndoAction` |
| RichEditor undo 子系统 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h` | `RichEditorUndoManager` 三策略(StyledString/Spans/StringUndoManager)/`UndoRedoRecord` |
| Text（只读子集） | `frameworks/core/components_ng/pattern/text/text_pattern.cpp` | `InitKeyEvent`/`UpdateShiftFlag`/`Ctrl+C`/`Ctrl+A`/`Shift+dir` |
| Search（委托） | `frameworks/core/components_ng/pattern/search/search_pattern.h/.cpp` | `OnKeyEvent` 委托 `textFieldPattern->OnKeyEvent` |
| IME 侧路径 | `frameworks/core/components_ng/pattern/text_field/on_text_changed_listener_impl.cpp` | 软键盘方向选择 `HandleSelect`(DPAD→CaretMoveIntent) |

### API 入口

无公共 API（框架内部）。键事件类型 `KeyCode`/`KeyEvent` 定义于 `frameworks/core/event/key_code.h`、`key_event.h`（属未来 `04-04-02 key-events` 域）。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 剪贴板/UDMF | `HandleOnCopy/Cut/Paste` | UDMF | — | 复制/剪切/粘贴剪贴板传递 |
| 排版引擎 | `CursorMove`/`HandleSelect` 经宿主 layout | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | 词边界/段落/行测量 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测（TextField） | `test/unittest/core/pattern/text_input/` | 文本编辑快捷键/undo 队列 |
| 单测（RichEditor） | `test/unittest/core/pattern/rich_editor/` | 三策略 undo/字体样式 |
| 单测（Text/Search） | `test/unittest/core/pattern/text/`、`test/unittest/core/pattern/search/` | 只读子集/委托 |
| 单测（事件） | `test/unittest/core/event/` | 键事件识别 |

### 相关 Spec

| Spec 域 | 路径 | 状态 |
|---------|------|------|
| 文本快捷键长期规格 | `specs/04-common-capability/14-input-interaction/02-text-shortcuts/` | active（6 个 Feat：分发基础设施/导航光标/选择/剪贴板删除/撤销重做/字体样式） |
| 边界：选择状态机制 | `specs/04-common-capability/14-input-interaction/01-text-selection/` | active |
| 边界：剪贴板/编辑回调 | `specs/04-common-capability/14-input-interaction/03-text-interaction/` | active（design + Feat-01） |
| 边界：输入框↔键盘交互 | `specs/04-common-capability/14-input-interaction/04-input-method-interaction/` | active（输入法交互，非焦点导航） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 组合键不响应 | `text_input_client.cpp` 两加速表 + `IsShortCutBlocked` 门控 |
| Ctrl+V 粘贴异常 | Ctrl+V `msg` 特殊路径 `InsertValue(msg)` |
| Shift 选择方向不连续 | `RecordOriginCaretPosition`/`ResetOriginCaretPosition` + `UpdateShiftFlag` 同步 `SelectionContainer` |
| Mac 组合键不响应 | `KEY_META` 镜像 Ctrl 分支 |
| 小键盘行为异常 | numLock-off 小键盘 0-9/DOT 重映射 |
| Ctrl+Shift+Home/End 选择异常 | 既有异常：派发 `CursorMove(Home/End)` 而非 `HandleSelect`（按实现记录，见 Spec Feat-03） |
| RichEditor undo 异常 | `rich_editor_undo_manager.h` 三策略(StyledString/Spans/String) + `UndoRedoRecord` |
| Tab/Esc/Enter 在文本框的拦截 vs 输入法交互 | 文本拦截归本域 Feat-01；输入框↔键盘交互（IME 弹出收起/避让/契约）归 `04-input-method-interaction` |

## 调试入口

Dump：宿主 Pattern dump（TextField/RichEditor）；快捷键命中可经 `HandleKeyEvent` 返回值（bool 消费）与 `IsShortCutBlocked` 查询。

## 相关主题

- [Input Method Interaction](./input-method-interaction.md)（输入框↔键盘交互：IME 弹出收起/避让/输入处理契约/公共 API）
- [Text](../components/basic/text.md)（只读快捷键子集宿主）
- [TextInput](../components/basic/text-input.md)（全量快捷键宿主）
- [RichEditor](../components/basic/rich-editor.md)（三策略 undo + 字体样式宿主，若存在）