# 文本选择 Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextSelection`

## 定位

文本选择是跨组件通用能力，覆盖 Text、TextInput、TextArea、Search、RichEditor、SelectionContainer（@since 26）六个组件。选区状态为运行时态（ephemeral），不持久化到 LayoutProperty，仅在 Pattern 层维护；`textSelectableMode`/`copyOption` 则持久化。本域聚焦选区状态模型与编程式选区，光标/菜单/剪贴板/事件/拦截/长按触发属 04-14-03（TextInteraction）。

具体选区语义、门控策略、C-API 不对称与兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 选区状态结构（方向无关 base/destination） | `frameworks/core/components_ng/pattern/text_field/text_selector.h` | `TextSelector`：GetTextStart/End 有序化、IsValid、aiStart/aiEnd、highlightStart/End |
| 选区/光标控制器 | `frameworks/core/components_ng/pattern/text_field/text_select_controller.h` | `TextSelectController` |
| TextBase Mixin（选区混入基类，继承 SelectOverlayClient） | `frameworks/core/components_ng/pattern/text/text_base.h` | 持有 `textSelector_`、GetGraphemeClusterLength 字形步进、CalculateSelectedRect |
| SelectOverlayClient 接口 | `frameworks/core/components_ng/manager/select_overlay/select_overlay_client.h` | 选择浮层客户端接口 |
| Text 控制器 | `frameworks/core/components_ng/pattern/text/text_controller.cpp` | `SetTextSelection`（@since 23 携带 MenuPolicy） |
| TextField 控制器 | `frameworks/core/components_ng/pattern/text_field/text_field_controller.cpp` | `SetTextSelection` + `ScheduleTaskWithLayoutDeferral` |
| RichEditor 控制器 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_base_controller.cpp` | `SetSelection`/`GetSelection` |
| Text ModelNG | `frameworks/core/components_ng/pattern/text/text_model_ng.cpp` | `SetTextSelection` |
| TextField ModelNG | `frameworks/core/components_ng/pattern/text_field/text_field_model_ng.cpp` | `SetTextSelection` |
| RichEditor ModelNG | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp` | 选区分发 |
| Text Pattern 门控 + overlay 调度 | `frameworks/core/components_ng/pattern/text/text_pattern.cpp` | `SetSelectionFlag` 四重门控（textSelectable+copyOption+marquee+textEffect） |
| TextField Pattern | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.cpp` | `SetSelectionFlag` |
| RichEditor Pattern | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp` | `SetSelection` + HasFocus 前置检查 |
| C-API Accessor（控制器→C++ 桥接） | `frameworks/core/interfaces/native/implementation/*_controller_accessor.cpp` | `TextControllerAccessor::SetTextSelectionImpl` 等 |
| JS Bridge | `frameworks/bridge/declarative_frontend/jsview/js_text.cpp`、`js_textfield.cpp`、`js_text_editable_controller.cpp` | JS 方法→C++ 绑定 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态 TextAttribute.selection/textSelectable | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text.d.ts` | selection(start,end)/setTextSelection/textSelectable/copyOption |
| 动态 TextInput/TextArea/Search/RichEditor | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_input.d.ts`、`text_area.d.ts`、`search.d.ts`、`rich_editor.d.ts` | `*Controller.setTextSelection` / `getSelection` |
| 共享类型（SelectionOptions/MenuPolicy/CopyOptions/TextSelectableMode） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | MenuPolicy DEFAULT/HIDE/SHOW（@since 12） |
| C-API NDK 枚举 NODE_TEXT_TEXT_SELECTION（=1046） | `interfaces/native/native_node.h` | Text 支持 `.object` 传 ArkUI_SelectionOptions |
| C-API OH_ArkUI_SelectionOptions 生命周期 | `interfaces/native/node/native_node_extented.cpp`、`interfaces/native/native_type.h` | Create/Dispose/SetMenuPolicy/GetMenuPolicy |
| C-API RichEditor 选区 | `interfaces/native/node/rich_editor_native_impl.cpp` | `OH_ArkUI_TextEditorStyledStringController_SetSelection/GetSelection` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text_input/text_select_controller_test.cpp` | 选区/光标控制器 |
| 单元测试 | `test/unittest/core/pattern/web/web_context_select_overlay_test.cpp` | 选择浮层（Web 参考） |

### 相关 Spec

| Spec 域 | 路径 |
|---------|------|
| 功能域 design | `specs/04-common-capability/14-input-interaction/01-text-selection/design.md` |
| Feat-01 选区状态模型与编程式选区 | `specs/04-common-capability/14-input-interaction/01-text-selection/Feat-01-selection-state-programmatic-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Text 编程式选区静默失败无错误码 | `text_pattern.cpp` 的 `SetSelectionFlag` 四重门控：textSelectableMode!=UNSELECTABLE && copyOption!=None && textOverflow!=MARQUEE && !textEffect_ |
| C-API MenuPolicy 支持不对称 | Text 支持 `.object` 传 ArkUI_SelectionOptions；TextInput/TextArea 不支持 `.object`，MenuPolicy 仅经控制器方法可达 |
| copyOption 语义因组件不同 | Text 的 None 禁用选区；TextField 不门控（选区用于编辑）；RichEditor 仅门控命令 |
| 三种 SelectionOptions 类型混淆 | 运行时 SelectionOptions（text_field_model.h，含 MenuPolicy+HandlePolicy+forceShowHandle）/ 缓存态 TextSelectionOptions（text_model.h）/ C-API ArkUI_SelectionOptions（仅 MenuPolicy） |
| 选区不持久化跨渲染恢复 | 选区是运行时态，`TextLayoutProperty` 仅存 `TextSelectableMode`/`CopyOption`，选区范围在 Pattern 层维护 |
| 代理对 emoji 选区步进异常 | `text_base.cpp` 的 `GetGraphemeClusterLength`：代理对=2，否则=1；索引单位为 UTF-16 码元 |
| C-API getter 堆分配生命周期 | `native_node_extented.cpp` 的 `OH_ArkUI_SelectionOptions` 在静态全局缓冲区，调用方注意生命周期 |
| CopyOptions 枚举值命名差异 | SDK `LocalDevice`/`CrossDevice` vs C++ `Local`/`Distributed` |

## 调试入口

- Text 编程式选区链路：`js_text.cpp` → `TextModel::SetTextSelection` → `TextModelNG::SetTextSelection` → `TextPattern::SetTextSelection` → 门控 → `SetSelectionFlag` → `TextSelector::Update` + `ShowSelectOverlay`
- C-API 选区：`style_modifier.cpp` 的 `SetTextTextSelection`（start>=end→reset+ERROR_CODE_PARAM_INVALID）
- 无障碍选区驱动：`TextPattern::SetAccessibilityAction` 注册 ACTION_SET_SELECTION/CLEAR_SELECTION，`TextSelector::FireAccessibilityCallback` 在 Update 时触发

## 相关主题

- `TextInteraction`（文本交互）— 光标/菜单/剪贴板/编辑拦截/长按触发
- `Text` 组件、`TextInput`/`TextArea`、`RichEditor` 组件 — 选区承载组件
