# 执行计划

> 标准级变更：3 张 Task Card，覆盖 CAPI 属性、事件、Pattern 过滤三层。

## Plan 元数据

| 字段 | 内容 |
|------|------|
| Plan ID | PLAN-002 |
| 关联 Feature | FEAT-002 |
| 关联文档 | proposal.md / design.md / spec.md |
| 复杂度 | 标准 |
| 状态 | Draft |
| Owner | ace_engine-dev |

## 输入状态

| 输入 | 路径 | 要求状态 |
|------|------|----------|
| Requirement | proposal.md | Approved (基线 v1.0) |
| Design | design.md | Draft |
| Spec | spec.md | Draft |

## 受影响文件全量清单

- interfaces/native/native_node.h — 修改：追加 NODE_TEXT_EDITOR_INPUT_FILTER(22031) + NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR(22009) 枚举值
- interfaces/native/node/rich_editor_properties.def — 修改：末尾追加 X(1,1,1,RichEditorInputFilter) 条目(行34后)
- interfaces/native/node/style_modifier.cpp — 修改：X-macro自动展开新增 Set/Get/ResetRichEditorInputFilter
- frameworks/core/interfaces/arkoala/arkoala_api.h — 修改：追加 ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR(67009)枚举(行1768后) + 5个Modifier函数指针(行9209后)
- frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp — 修改：5个桥接函数 + GetEventSetHandler[9] + GetEventResetHandler[9] + modifier初始化5条(行2187后)
- interfaces/native/node/event_converter.cpp — 修改：ConvertOriginEventType + ConvertToNodeEventType + IsStringEvent追加
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h — 修改：5个虚方法
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h — 修改：5个override + 5个static声明
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp — 修改：10个方法实现
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_property.h — 修改：追加 InputFilter属性声明
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_property.cpp — 修改：属性实现(ACE宏自动)
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.h — 修改：3个方法声明+1个成员(行329后+行350后)
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.cpp — 修改：3个方法实现
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h — 修改：追加 FilterWithInputFilter 声明
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp — 修改：FilterWithInputFilter 实现 + 2处插入点(L6840前 + L451前)
- frameworks/core/components_ng/pattern/text_field/text_filter_utils.h — 新建：TextFilterUtils namespace 下 FilterWithRegex + ContentToWstring + ContentToU16string + RemoveErrorTextFromValue 函数声明
- frameworks/core/components_ng/pattern/text_field/text_filter_utils.cpp — 新建：上述 4 个函数实现（从 content_controller.cpp 迁移）
- frameworks/core/components_ng/pattern/text_field/content_controller.h — 修改：删除 RemoveErrorTextFromValue 静态成员声明(L103)；保留 FilterWithRegex 声明(L104) 作为 wrapper
- frameworks/core/components_ng/pattern/text_field/content_controller.cpp — 修改：(1)删除匿名namespace块(L30-64)内 ContentToWstring(L41)/ContentToU16string(L53)；(2)删除 RemoveErrorTextFromValue 定义(L289-308)；(3)FilterWithRegex 定义(L314-324) 改为 wrapper 调用 TextFilterUtils::FilterWithRegex
- frameworks/core/components_ng/pattern/text_field/BUILD.gn — 修改：sources 列表中 content_controller.cpp 之后新增 text_filter_utils.cpp

## AC 到 Task 追溯

| AC | 来源 | Task | 验证方式 | 覆盖？ |
|----|------|------|----------|--------|
| AC-1 | spec.md | TASK-1 | C API 单测 | 是 |
| AC-2 | spec.md | TASK-1 | C API 单测 | 是 |
| AC-3 | spec.md | TASK-1 | C API 单测 | 是 |
| AC-10 | spec.md | TASK-1 | C API 单测 | 是 |
| AC-4 | spec.md | TASK-2 | C API 单测 | 是 |
| AC-5 | spec.md | TASK-2 | C API 单测 + UI交互 | 是 |
| AC-6 | spec.md | TASK-2 | C API 单测 | 是 |
| AC-7 | spec.md | TASK-3 | C API 单测 | 是 |
| AC-8 | spec.md | TASK-3 | C API 单测 | 是 |
| AC-9 | spec.md | TASK-3 | C API 单测 | 是 |
| AC-11 | spec.md | TASK-3 | C API 单测 | 是 |

## Task 列表

| Task ID | 目标 | 文件范围 | AC 映射 | 前置依赖 | 完成判据 | 验证命令 |
|---------|------|----------|---------|----------|----------|----------|
| TASK-1 | CAPI 属性链路：inputFilter 设置/获取/重置 | native_node.h, rich_editor_properties.def, style_modifier.cpp, arkoala_api.h, rich_editor_dynamic_modifier.cpp, rich_editor_model.h/ng, rich_editor_layout_property.h/.cpp | AC-1, AC-2, AC-3, AC-10 | TASK-0 | 4 条 AC 通过单测 | linux_unittest_capi 构建 + capi_all_modifiers_test |
| TASK-2 | CAPI 事件链路：onInputFilterError 注册/触发/注销 | event_converter.cpp, arkoala_api.h(事件部分), rich_editor_dynamic_modifier.cpp(事件部分), rich_editor_model.h/ng(事件部分), rich_editor_event_hub.h/.cpp | AC-4, AC-5, AC-6 | TASK-1 | 3 条 AC 通过单测 | linux_unittest_capi 构建 + capi_all_modifiers_test |
| TASK-3 | Pattern 过滤逻辑 + 共享工具提取 | rich_editor_pattern.h/.cpp, text_filter_utils.h/.cpp(新建), content_controller.cpp | AC-7, AC-8, AC-9, AC-11 | TASK-1, TASK-2 | 4 条 AC 通过单测 + TextField 回归 | linux_unittest_capi + TextField 单测回归 |

## Task 详情

### TASK-0: 共享过滤工具提取（前置依赖）

| 字段 | 内容 |
|------|------|
| 任务目标 | 提取 FilterWithRegex 为共享自由函数，为 TASK-3 的 Pattern 过滤提供工具基础 |
| AC 映射 | 间接支撑 AC-7, AC-9 |
| 前置依赖 | 无 |
| 非目标 | 不修改 FilterWithRegex 逻辑本身 |
| 完成判据 | text_filter_utils.h/.cpp 编译通过；content_controller.cpp 改用共享调用后 TextField 单测回归通过 |
| 停止条件 | 发现 ContentToWstring/RemoveErrorTextFromValue 无法独立提取（依赖 ContentController 上下文），改为方案 B |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Create | frameworks/core/components_ng/pattern/text_field/text_filter_utils.h | TextFilterUtils namespace 下 FilterWithRegex + ContentToWstring + ContentToU16string + RemoveErrorTextFromValue 函数声明 |
| Create | frameworks/core/components_ng/pattern/text_field/text_filter_utils.cpp | 从 content_controller.cpp 提取：(1)匿名namespace块内 ContentToWstring(L41) + ContentToU16string(L53)；(2)RemoveErrorTextFromValue(L289-308)；(3)FilterWithRegex 核心逻辑(L314-324) |
| Modify | frameworks/core/components_ng/pattern/text_field/content_controller.h | 删除 RemoveErrorTextFromValue 静态成员声明(L103)；保留 FilterWithRegex 声明(L104) 作为 wrapper |
| Modify | frameworks/core/components_ng/pattern/text_field/content_controller.cpp | (1)删除匿名namespace块(L30-64)内 ContentToWstring(L41)/ContentToU16string(L53)；(2)删除 RemoveErrorTextFromValue 定义(L289-308)；(3)FilterWithRegex 定义(L314-324) 改为 wrapper `return TextFilterUtils::FilterWithRegex(filter, result)` |
| Modify | frameworks/core/components_ng/pattern/text_field/BUILD.gn | sources 列表中 content_controller.cpp 之后新增 text_filter_utils.cpp |

**Spec Context**

无直接 AC，但支撑 TASK-3 的 R-6/R-7/R-8 规则实现。

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| design.md D-1 | Must 提取为共享函数（方案 A-1） |
| AGENTS.md | Must not 新增对其他 OpenHarmony 系统模块的依赖 |

**Steps**

- [ ] 创建 text_filter_utils.h：声明 FilterWithRegex 自由函数 + 内部辅助函数
- [ ] 创建 text_filter_utils.cpp：从 content_controller.cpp 提取 6 行核心逻辑 + 3 个辅助函数
- [ ] 修改 content_controller.cpp：FilterWithRegex 改为调用 text_filter_utils::FilterWithRegex
- [ ] 更新 BUILD.gn：新增 text_filter_utils.cpp 到编译列表
- [ ] 构建 ace_engine 验证编译通过
- [ ] 运行 TextField 单测回归验证行为不变

**Completion Evidence**

| 证据类型 | 命令/路径 | 结果 |
|----------|-----------|------|
| 编译 | `./build.sh --product-name rk3568 --build-target ace_engine` | PASS |
| 回归 | TextField 相关单测 | PASS |

---

### TASK-1: CAPI 属性链路：inputFilter 设置/获取/重置

| 字段 | 内容 |
|------|------|
| 任务目标 | 实现 inputFilter 正则属性的 CAPI 全链路：枚举→.def→style_modifier→arkoala→dynamic_modifier→Model→LayoutProperty |
| AC 映射 | AC-1, AC-2, AC-3, AC-10 |
| 前置依赖 | TASK-0 |
| 非目标 | 不涉及事件链路（TASK-2）；不涉及过滤逻辑（TASK-3） |
| 完成判据 | 4 条属性 AC 通过 C API 单测 |
| 停止条件 | 发现 X-macro 展开机制与预期不符（如 subTypeId 计算方式不一致），停止并回传 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | interfaces/native/native_node.h | 追加 NODE_TEXT_EDITOR_INPUT_FILTER = 22031 枚举值(行6898后) |
| Modify | interfaces/native/node/rich_editor_properties.def | 追加 X(1,1,1,RichEditorInputFilter) 条目(行34后) |
| Modify | frameworks/core/interfaces/arkoala/arkoala_api.h | 追加 set/get/resetRichEditorInputFilter 3个函数指针(行9209后) |
| Modify | frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp | 追加 Set/Get/ResetRichEditorInputFilter 3个桥接函数 + modifier初始化3条(行2187后) |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h | 追加 SetInputFilter/ResetInputFilter/GetInputFilter 3个虚方法 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h | 追加 3个override + 3个static声明 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp | 实现 6个方法 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_property.h | 追加 ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InputFilter, std::string, PROPERTY_UPDATE_MEASURE) |

**Spec Context**

AC-1: WHEN setAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER, {.string="^[a-z]*$"}) THEN inputFilter 设置为 "^[a-z]*$"
AC-2: WHEN getAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER) THEN 返回当前正则字符串
AC-3: WHEN resetAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER) THEN inputFilter 清除
AC-10: WHEN setAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER, {.string=""}) THEN 空字符串等效于不设置

R-1: 正则设置生效；R-2: 空字符串/重置清除

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| design.md D-2 | Must 枚举值 22031 紧跟 22030 |
| design.md D-4 | Must X-macro 追加在末尾 |
| AGENTS.md | Must not 修改已有 Public API 签名/语义/错误码 |

**Steps**

- [ ] native_node.h 追加 NODE_TEXT_EDITOR_INPUT_FILTER = 22031 枚举值
- [ ] rich_editor_properties.def 追加 X(1,1,1,RichEditorInputFilter) 条目
- [ ] arkoala_api.h 追加 3 个函数指针 (set/get/resetRichEditorInputFilter)
- [ ] rich_editor_dynamic_modifier.cpp 追加 3 个桥接实现 + modifier 初始化 3 条
- [ ] rich_editor_model.h 追加 3 个虚方法
- [ ] rich_editor_model_ng.h 追加 3 个 override + 3 个 static
- [ ] rich_editor_model_ng.cpp 实现 6 个方法
- [ ] rich_editor_layout_property.h 追加 InputFilter 属性声明
- [ ] 构建 linux_unittest_capi 验证编译通过
- [ ] 编写 C API 单测用例覆盖 AC-1/AC-2/AC-3/AC-10
- [ ] 运行 capi_all_modifiers_test 验证 4 条 AC

**Completion Evidence**

| 证据类型 | 命令/路径 | 结果 |
|----------|-----------|------|
| 构建 | `./build.sh --product-name rk3568 --build-target linux_unittest_capi` | PASS |
| 单测 | `capi_all_modifiers_test --gtest_filter=*TextEditor*InputFilter*` | PASS |

---

### TASK-2: CAPI 事件链路：onInputFilterError 注册/触发/注销

| 字段 | 内容 |
|------|------|
| 任务目标 | 实现 onInputFilterError 过滤失败回调的 CAPI 全链路：枚举→event_converter→arkoala→dynamic_modifier→Model→EventHub |
| AC 映射 | AC-4, AC-5, AC-6 |
| 前置依赖 | TASK-1 (LayoutProperty 中 InputFilter 属性需先存在) |
| 非目标 | 不涉及过滤触发逻辑（TASK-3） |
| 完成判据 | 3 条事件 AC 通过 C API 单测 |
| 停止条件 | 发现 event_converter.cpp 中 ConvertEvent 不支持 TEXT_INPUT kind 的 STRING_ASYNC_EVENT 映射（与 design.md D-3 不符），停止并回传 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | interfaces/native/native_node.h | 追加 NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR = 22009 事件枚举值(行11259后) |
| Modify | frameworks/core/interfaces/arkoala/arkoala_api.h | 追加 ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR = 67009 子类型枚举(行1768后) + set/resetRichEditorOnInputFilterError 2个函数指针 |
| Modify | interfaces/native/node/event_converter.cpp | ConvertOriginEventType追加 + ConvertToNodeEventType追加 + IsStringEvent追加 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp | 追加 Set/ResetOnRichEditorInputFilterError 2个桥接函数 + GetEventSetHandler[9] + GetEventResetHandler[9] + modifier初始化2条 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h | 追加 SetOnInputFilterError/ResetOnInputFilterError 2个虚方法 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h | 追加 2个override + 2个static声明 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp | 实现 4个方法 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.h | 追加 SetOnInputFilterError/FireOnInputFilterError/ResetOnInputFilterError + onInputFilterError_成员 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.cpp | 实现 3个方法 |

**Spec Context**

AC-4: WHEN registerNodeEvent(node, NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR, targetId, userData) THEN 回调注册成功
AC-5: WHEN 输入被拒字符 THEN OH_ArkUI_NodeEvent_GetStringAsyncEvent 可获取 .pStr（事件内部构造使用 kind=TEXT_INPUT + textInputEvent.nativeStringPtr，详见 design.md D-3 方案 B）
AC-6: WHEN unregisterNodeEvent THEN 回调注销成功

R-3: 被拒字符通过 pStr 回传；R-4: 回调注册成功；R-5: 注销后不再触发

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| design.md D-3 | Must 事件 kind 使用 TEXT_INPUT (ARKUI_TEXT_INPUT) |
| design.md D-2 | Must 事件枚举值 22009 紧跟 22008 |
| design.md C-5 | Must 使用 OH_ArkUI_NodeEvent_GetStringAsyncEvent 提取数据 |
| design.md C-6 | Must 属性与事件分两次独立调用 |

**Steps**

- [ ] native_node.h 追加 NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR = 22009 事件枚举值
- [ ] arkoala_api.h 追加 ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR = 67009 子类型枚举 + 2个函数指针
- [ ] event_converter.cpp 3处追加
- [ ] rich_editor_dynamic_modifier.cpp 追加 2个桥接函数 + handler数组2条 + modifier初始化2条
- [ ] rich_editor_model.h 追加 2个虚方法
- [ ] rich_editor_model_ng.h/.cpp 追加 4个方法实现
- [ ] rich_editor_event_hub.h/.cpp 追加 3个方法 + 1个成员
- [ ] 构建 linux_unittest_capi 验证编译通过
- [ ] 编写 C API 单测用例覆盖 AC-4/AC-5/AC-6
- [ ] 运行 capi_all_modifiers_test 验证 3 条 AC

**Completion Evidence**

| 证据类型 | 命令/路径 | 结果 |
|----------|-----------|------|
| 构建 | `./build.sh --product-name rk3568 --build-target linux_unittest_capi` | PASS |
| 单测 | `capi_all_modifiers_test --gtest_filter=*TextEditor*InputFilterError*` | PASS |

---

### TASK-3: Pattern 过滤逻辑实现 + 生效条件

| 字段 | 内容 |
|------|------|
| 任务目标 | 在 RichEditorPattern 中实现 FilterWithInputFilter 过滤方法，含生效条件检查、正则过滤调用、错误回调触发，并在 ProcessInsertValue 和 InsertValueInStyledString 中插入过滤调用 |
| AC 映射 | AC-7, AC-8, AC-9, AC-11 |
| 前置依赖 | TASK-0 (共享工具) + TASK-1 (LayoutProperty InputFilter) + TASK-2 (EventHub onInputFilterError) |
| 非目标 | 不修改 TextField 过滤逻辑；不实现两阶段过滤机制 |
| 完成判据 | 4 条过滤逻辑 AC 通过 C API 单测 + TextField 单测回归 |
| 停止条件 | 发现 ProcessInsertValue/InsertValueInStyledString 插入点位置与预期不符，停止并回传 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h | 追加 FilterWithInputFilter 私有方法声明 |
| Modify | frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp | 实现 FilterWithInputFilter + ProcessInsertValue(L6840前)插入 + InsertValueInStyledString(L451前)插入 |

**Spec Context**

AC-7: WHEN isSpanStringMode_=true && isSingleLineMode_=true THEN 过滤生效
AC-8: WHEN isSpanStringMode_=false || isSingleLineMode_=false THEN 不生效
AC-9: WHEN inputFilter + maxLength THEN 过滤优先级 inputFilter→maxLength
AC-11: WHEN "\n" 不匹配 regex THEN "\n" 被过滤不插入

R-6: spanString+singleLine 条件；R-7: 条件不满足时忽略；R-8: 过滤→截断顺序；R-9: "\n"过滤

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| design.md C-1 | Must 仅 isSpanStringMode_ && isSingleLineMode_ 生效 |
| design.md C-2 | Must 过滤优先级 inputFilter → maxLength |
| design.md C-7 | Must inputFilter 过滤在所有内容回调之前执行，回调拿过滤+截断后的值 |
| design.md C-8 | Must 仅单阶段过滤（仅过滤插入值，不对全量二次过滤） |
| design.md D-5 | Must 过滤插入点在 ProcessTextTruncationOperation 之前 |
| design.md D-1 | Must 使用 text_filter_utils::FilterWithRegex（方案 A-1） |

**Steps**

- [ ] rich_editor_pattern.h 追加 FilterWithInputFilter 私有方法声明
- [ ] rich_editor_pattern.cpp 实现 FilterWithInputFilter：
  - ① 检查 isSpanStringMode_ && isSingleLineMode_
  - ② 从 LayoutProperty 读取 InputFilter 正则
  - ③ 调用 text_filter_utils::FilterWithRegex
  - ④ 有被拒字符 → FireOnInputFilterError
  - ⑤ 修改传入 text
- [ ] ProcessInsertValue (行6840前) 插入 `if (!FilterWithInputFilter(text)) { return; }`
- [ ] InsertValueInStyledString (行451前) 插入 `if (!FilterWithInputFilter(subValue)) { return; }`
- [ ] 构建 linux_unittest_capi 验证编译通过
- [ ] 编写 C API 单测用例覆盖 AC-7/AC-8/AC-9/AC-11
- [ ] 运行 TextField 单测回归验证 FilterWithRegex 改用共享函数后行为不变

**Completion Evidence**

| 证据类型 | 命令/路径 | 结果 |
|----------|-----------|------|
| 构建 | `./build.sh --product-name rk3568 --build-target linux_unittest_capi` | PASS |
| 单测 | `capi_all_modifiers_test --gtest_filter=*TextEditor*InputFilter*` | PASS |
| 回归 | TextField 相关单测 | PASS |

## Plan 自审清单

- [x] 每个 P0/P1 AC 至少映射到一个 Task
- [x] 每个 Task 文件范围明确
- [x] 每个 Task 明确前置依赖、非目标、完成判据和停止条件
- [x] 每个 Task 有验证命令
- [x] 没有 TBD/TODO/占位符
- [x] 交接信息自包含（spec context + required rules）
