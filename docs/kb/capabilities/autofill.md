# 自动补全能力（AutoFill）Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `AutoFill`

## 定位

AutoFill 是跨组件通用能力，覆盖 TextInput（主载体）、TextArea、Search（Pattern 覆写禁用）、Web（独立管线，Feat-05）。本域基线补录 Feat-01 基础属性与类型枚举；Feat-02~05（动画修饰/触发管线/MSDP 与 Secure Paste/Web 管线）待后续补录。

属性基线：`enableAutoFill`（默认 true）、`contentType`（39 项内部枚举/33 项 NDK）、`passwordRules`（TextInput 独有）、`enableAutoFillAnimation`（TextInput 独有）。具体类型映射、偏移桥接、平台门控与兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| TextField Pattern（GetAutoFillType/IsShowAutoFill/CheckAutoFill） | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.h`、`text_field_pattern.cpp` | `contentTypeMap_` 39 条映射、`TextContentTypeToAceAutoFillType`、三重平台门控 |
| TextField Model（抽象/NG/Static） | `frameworks/core/components_ng/pattern/text_field/text_field_model.h`、`text_field_model_ng.h`/`text_field_model_ng.cpp`、`text_field_model_static.h`/`text_field_model_static.cpp` | 抽象接口 + NG（FrameNode 静态/非静态）+ Static（nullopt 处理） |
| TextField LayoutProperty（5 属性存储） | `frameworks/core/components_ng/pattern/text_field/text_field_layout_property.h` | EnableAutoFill/EnableAutoFillAnimation/TextContentType/TextContentTypeChanged/PasswordRules（PROPERTY_UPDATE_MEASURE） |
| 类型枚举（AceAutoFillType/AceAutoFillTriggerType/AceAutoFillError） | `frameworks/base/view_data/ace_auto_fill_type.h`、`frameworks/base/view_data/ace_auto_fill_error.h` | 39 项内部枚举 + 4 项触发类型 + 12 项错误码 |
| TextContentType 枚举 | `frameworks/core/components_ng/pattern/text_field/text_content_type.h` | 39 项内部枚举（含 5 项 time/date 未在 NDK 暴露） |
| ViewData 桥层 | `frameworks/base/view_data/view_data_wrap.h`、`page_node_info_wrap.h`、`hint_to_type_wrap.h` | ViewDataToType/HintToAutoFillType、SetAutoFillType/GetEnableAutoFill |
| AutoFill 动画控制器（Feat-02） | `frameworks/core/components_ng/pattern/text_field/auto_fill_controller.h`、`auto_fill_controller.cpp` | AutoFillAnimationStatus/ContentLengthMode/InsertStatus 状态机 |
| TextField Content Modifier（Feat-02 绘制/偏移） | `frameworks/core/components_ng/pattern/text_field/text_field_content_modifier.h` | AutoFill 动画绘制 API |
| TextField LayoutAlgorithm（CreateAutoFillParagraph） | `frameworks/core/components_ng/pattern/text_field/text_field_layout_algorithm.h` | AutoFill 段落创建 |
| Web Pattern（Feat-05 独立管线） | `frameworks/core/components_ng/pattern/web/web_pattern.h`、`web_pattern.cpp`、`web_model.h`、`web_model.cpp` | `RequestAutoFill`（3 重载）/`RequestPasswordAutoFill`/`RequestAutoSave`/`UpdateAutoFillPopup`/`CloseAutoFillPopup` |
| Search Pattern（覆写禁用 AutoFill） | `frameworks/core/components_ng/pattern/search/search_text_field.h`、`search_text_field.cpp` | `IsNeedProcessAutoFill()` 返回 false |
| JS Bridge | `frameworks/bridge/declarative_frontend/jsview/js_textinput.cpp`、`js_textarea.cpp`、`js_textfield.cpp` | `SetEnableAutoFill`/`SetEnableAutoFillAnimation`/`SetContentType`/`SetPasswordRules` |
| 静态 ArkTS TextArea 桥 | `frameworks/core/components_ng/pattern/text_area/bridge/arkts_native_text_area_bridge.cpp` | 静态前端 TextArea 桥 |
| TextFieldManager（触发管线 + MSDP，Feat-03/04） | `frameworks/core/components_ng/pattern/text_field/text_field_manager.h`、`text_field_manager.cpp` | `ParseMSDPAutoFillJsonValue` 等 + TextFieldInfo 结构 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态 TextInput/TextArea | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_input.d.ts`、`text_area.d.ts`（不在本仓，in-repo 镜像 `frameworks/bridge/declarative_frontend/ark_component/export/arkComponent.d.ts`） | enableAutoFill/contentType/passwordRules/enableAutoFillAnimation |
| C-API NDK 枚举 | `interfaces/native/native_node.h` | NODE_TEXT_INPUT_ENABLE_AUTO_FILL(7034)/CONTENT_TYPE(7035)/PASSWORD_RULES(7037)/ENABLE_FILL_ANIMATION(7036,@since 20)/NODE_TEXT_AREA_ENABLE_AUTO_FILL/CONTENT_TYPE |
| C-API NDK 类型枚举 | `interfaces/native/node_attributes/text_input.h` | ArkUI_TextInputContentType（33 项，21 @since 12 + 12 @since 18） |
| C-API 菜单项枚举 | `interfaces/native/node_attributes/text_common.h` | ARKUI_TEXT_MENU_ITEM_ID_AUTO_FILL(16)/PASSWORD_VAULT(17)（@since 24） |
| C-API 派发 | `interfaces/native/node/style_modifier.cpp` | `SetTextInputEnableAutoFill`/`SetTextInputContentType`(+CONVERT_CONTENT_TYPE=5 偏移)/`SetTextInputPasswordRules`/`SetTextInputEnableAutoFillAnimation`；TextArea 路由复用 TextInput dispatcher |
| C-API TextInput 实现 | `frameworks/core/interfaces/native/node/node_text_input_modifier.cpp` | u32→bool/int32→enum cast + clamp 超范围 |
| C-API TextArea 实现 | `frameworks/core/interfaces/native/node/node_text_area_modifier.cpp` | TextArea 属性处理 |
| Arkoala API | `frameworks/core/interfaces/arkoala/arkoala_api.h` | dedicated TextArea 指针（静态前端） |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| AbilityBase（AutoFill 类型） | `frameworks/base/view_data/` | `ability_base` | `AbilityBase::AutoFillType`/`AbilityBase::ViewData` | ViewDataWrap/PageNodeInfoWrap 桥接到 Ace 类型（桥接行为属 Feat-03） |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text_input/text_field_auto_fill_controller_test.cpp` | AutoFill 动画控制器 |
| 单元测试 | `test/unittest/core/pattern/text_input/text_field_content_modifier_test.cpp` | Content Modifier |
| 单元测试 | `test/unittest/core/pattern/text_input/text_field_model_static_test.cpp` | 静态 Model nullopt 行为 |
| 单元测试 | `test/unittest/core/pattern/text_input/text_field_manager_test_ng.cpp`、`text_field_manager_test_ng_two.cpp` | TextFieldManager 触发管线 |
| C-API 测试 | `test/unittest/capi/accessors/capi_all_modifiers_test` | NDK AutoFill 属性设置/查询/重置 |

### 相关 Spec

| Spec 域 | 路径 |
|---------|------|
| 功能域 design | `specs/04-common-capability/14-input-interaction/05-autofill/design.md` |
| Feat-01 TextInput/TextArea AutoFill 基础属性与类型枚举 | `specs/04-common-capability/14-input-interaction/05-autofill/Feat-01-textinput-textarea-base-attributes-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| NDK 与内部枚举值域不一致 | `style_modifier.cpp` 的 `CONVERT_CONTENT_TYPE=5` 偏移：set 路径 +5，get 路径 -5；源于内部 5 项 time/date 类型未在 NDK 暴露 |
| NDK 枚举名缺 `AUTO_`（NODE_TEXT_INPUT_ENABLE_FILL_ANIMATION） | NDK 公开 API 不可改名，下游需引用正确枚举名（无 AUTO_），dispatcher 函数名保留 `Auto` |
| TextContentType::VISIBLE_PASSWORD ↔ AceAutoFillType::ACE_PASSWORD 同值异名 | `contentTypeMap_` 唯一名称发散，跨边界按名称 switch 需显式处理 |
| ArkTS `.contentType(999)` 越界不 clamp，NDK 路径 clamp 不对称 | `js_textfield.cpp` raw `static_cast`；`node_text_input_modifier.cpp` 检测并 clamp 至 UNSPECIFIED |
| NDK 接受未定义值 33–37（校验缺口） | `style_modifier.cpp` 不触发偏移分支（>32），bridge 错误接受；源码现状 |
| TextContentType 不参与 ToJsonValue/Reset/Clone | Inspector dump 看不到 contentType；只有 PasswordRules/EnableAutoFill/EnableAutoFillAnimation 参与序列化 |
| enableAutoFill 默认值跨层不一致 | ArkTS/NDK/LayoutProperty=true，但 `PageNodeInfoWrap` 基类默认 false；静态桥 nullopt 始终委托 NG 设 true，永不 reset |
| TextArea NDK 路由复用 TextInput dispatcher | 结果等价但路由不对称，未来重命名 TextInput dispatcher 会静默破裂 |
| Search 组件不触发 AutoFill | `search_text_field.cpp` 的 `IsNeedProcessAutoFill()` 覆写返回 false |
| GetAutoFillType 解析优先级 | `text_field_pattern.cpp`：contentType > inputType(VISIBLE_PASSWORD/NUMBER_PASSWORD→ACE_PASSWORD) > hint > ACE_UNSPECIFIED |

## 调试入口

- ArkTS 设置链路：`.enableAutoFill(false)` → `JSTextField::SetEnableAutoFill`（非 boolean→默认 true）→ `TextFieldModel::SetEnableAutoFill` → `ACE_UPDATE_LAYOUT_PROPERTY` → `NearEqual` 同值不触发 dirty
- NDK 设置链路：`setAttribute(NODE_TEXT_INPUT_CONTENT_TYPE, {18})` → `SetTextInputContentType`（+5 偏移→23）→ `setTextInputContentType(handle, 23u)` → `SetContentType` + companion `UpdateTextContentTypeChanged(true)`
- 平台门控：`IsShowAutoFill()`：SceneBoardWindow / ScreenLockManager / SystemProperties::IsAutoFillSupport 三重门控，不查询字段级 enableAutoFill

## 相关主题

- `TextSelection`（文本选择）、`TextInteraction`（文本交互）— 边界功能域
- `TextInput`/`TextArea`、`Search`、`Web` 组件 — AutoFill 承载组件
