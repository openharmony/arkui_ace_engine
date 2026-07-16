# 特性规格

> 固化用户可见行为和验收标准。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | RichEditor CAPI inputFilter & onInputFilterError |
| 特性编号 | FEAT-002 |
| 优先级 | P1 |
| 目标版本 | OpenHarmony-6.0-Release |
| SIG 归属 | ArkUI |
| 状态 | Draft |
| 复杂度 | 标准 |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Requirement | proposal.md | Approved (基线 v1.0) |
| Design | design.md | Draft |

## 用户故事

### US-1: NDK 开发者设置 RichEditor 正则输入约束

**作为** NDK 应用开发者,
**我想要** 通过 C API 设置 TextEditor 的正则输入约束(inputFilter),
**以便** 在单行富文本场景下过滤非法字符，与 TextInput/TextArea 的同功能对齐。

**验收标准：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-1 | WHEN 调用 `setAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER, {.string="^[a-z]*$"})` THEN TextEditor 的 inputFilter 正则设置为 "^[a-z]*$"，后续输入匹配该正则白名单 | 正常 |
| AC-2 | WHEN 调用 `getAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER)` THEN 返回当前设置的 inputFilter 正则字符串 | 正常 |
| AC-3 | WHEN 调用 `resetAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER)` THEN inputFilter 被清除，恢复为不设置状态，后续输入不再受正则约束 | 正常 |
| AC-10 | WHEN 调用 `setAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER, {.string=""})` THEN 设置空字符串等效于不设置，过滤不生效 | 边界 |

### US-2: NDK 开发者注册过滤失败回调

**作为** NDK 应用开发者,
**我想要** 通过 C API 注册过滤失败回调(onInputFilterError),
**以便** 获知被 inputFilter 过滤掉的字符内容，实现输入校验反馈。

**验收标准：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-4 | WHEN 调用 `registerNodeEvent(node, NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR, targetId, userData)` THEN 过滤失败回调注册成功，后续过滤事件可通过全局 eventReceiver 接收 | 正常 |
| AC-5 | WHEN 输入字符被 inputFilter 过滤掉 THEN 通过 `OH_ArkUI_NodeEvent_GetStringAsyncEvent(event)` 可获取被拒字符的 `ArkUI_StringAsyncEvent.pStr` | 正常 |
| AC-6 | WHEN 调用 `unregisterNodeEvent(node, NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR)` THEN 回调注销成功，后续过滤失败不再触发该回调 | 正常 |

### US-3: 单行+属性字符串模式下使用 inputFilter

**作为** NDK 应用开发者,
**我想要** 在单行+属性字符串模式下使用 inputFilter 控制输入行为,
**以便** 确保正则过滤和 maxLength 截断协同生效。

**验收标准：**

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-7 | WHEN isSpanStringMode_=true 且 isSingleLineMode_=true THEN inputFilter 过滤逻辑生效，输入内容受正则约束 | 正常 |
| AC-8 | WHEN isSpanStringMode_=false 或 isSingleLineMode_=false THEN inputFilter 设置被忽略，不执行过滤逻辑 | 边界 |
| AC-9 | WHEN inputFilter 正则生效且 maxLength 也设置 THEN 过滤优先级为 inputFilter → maxLength（先过滤再截断） | 正常 |
| AC-11 | WHEN 单行模式下 Enter 键输入 "\n" 且 inputFilter 不匹配 "\n" THEN "\n" 被过滤掉，不插入，不触发 onSubmit 的 NEW_LINE 分支 | 边界 |

## 验收追溯

| AC | 关联规则 | 关联 Task | 验证方式 | 证据 |
|----|----------|-----------|----------|------|
| AC-1 | R-1 | TASK-1 | C API 单测 | evidence/ |
| AC-2 | R-1 | TASK-1 | C API 单测 | evidence/ |
| AC-3 | R-2 | TASK-1 | C API 单测 | evidence/ |
| AC-4 | R-4 | TASK-2 | C API 单测 | evidence/ |
| AC-5 | R-3 | TASK-2 | C API 单测 + UI交互 | evidence/ |
| AC-6 | R-5 | TASK-2 | C API 单测 | evidence/ |
| AC-7 | R-6, R-10 | TASK-3 | C API 单测 | evidence/ |
| AC-8 | R-7 | TASK-3 | C API 单测 | evidence/ |
| AC-9 | R-8 | TASK-3 | C API 单测 | evidence/ |
| AC-10 | R-2 | TASK-1 | C API 单测 | evidence/ |
| AC-11 | R-9 | TASK-3 | C API 单测 | evidence/ |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | setAttribute(NODE_TEXT_EDITOR_INPUT_FILTER, {.string=regex}) 且 regex 非空 | inputFilter 正则设置为 regex 值，后续输入受正则白名单约束 | regex 格式为合法正则表达式字符串 | AC-1, AC-2 |
| R-2 | 边界 | setAttribute(NODE_TEXT_EDITOR_INPUT_FILTER, {.string=""}) 或 resetAttribute(NODE_TEXT_EDITOR_INPUT_FILTER) | inputFilter 清除，恢复为不设置状态 | 空字符串等效于不设置 | AC-3, AC-10 |
| R-3 | 行为 | 输入字符不匹配 inputFilter 正则白名单 | 被拒字符通过 `OH_ArkUI_NodeEvent_GetStringAsyncEvent` 的 `.pStr` 回传给用户 | 仅在已注册 onInputFilterError 回调时触发；pStr 为被拒字符的 UTF-8 字符串 | AC-5 |
| R-4 | 行为 | registerNodeEvent(NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR, ...) | 回调注册成功，过滤事件可通过全局 eventReceiver 接收 | 回调与正则设置是两次独立调用；注销回调不会清除正则 | AC-4 |
| R-5 | 行为 | unregisterNodeEvent(NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR) | 回调注销成功，后续过滤失败不再触发回调 | 注销后正则仍然生效，仅不再通知 | AC-6 |
| R-6 | 条件 | isSpanStringMode_=true 且 isSingleLineMode_=true 且 inputFilter 非空 | 过滤逻辑生效，输入内容受正则约束 | 两个模式条件缺一不可 | AC-7 |
| R-7 | 条件 | isSpanStringMode_=false 或 isSingleLineMode_=false | inputFilter 设置被忽略，不执行过滤逻辑 | 设置值仍可通过 getAttribute 获取，但不生效 | AC-8 |
| R-8 | 顺序 | inputFilter 非空且 maxLength 有值 | 过滤优先级: inputFilter → maxLength（先过滤再截断） | 与 TextInput 的优先级一致 | AC-9 |
| R-9 | 边界 | 单行模式下 Enter 键输入 "\n" 且 inputFilter 不匹配 "\n" | "\n" 被过滤掉，不插入，不触发 onSubmit(NEW_LINE) 分支 | 过滤后文本为空则不插入 | AC-11 |
| R-10 | 顺序 | inputFilter 过滤执行时，aboutToIMEInput/onWillChange/onDidChange 等回调尚未触发 | 回调拿到的值是过滤+截断后的值，而非原始输入值 | 与 TextInput 的回调值顺序一致（参考文档3.3） | AC-7 |

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | R-1 / AC-1 | C API 单测 | setAttribute 正则设置生效 |
| VM-2 | R-1 / AC-2 | C API 单测 | getAttribute 返回一致 |
| VM-3 | R-2 / AC-3 | C API 单测 | resetAttribute 清除设置 |
| VM-4 | R-4 / AC-4 | C API 单测 | registerNodeEvent 回调注册 |
| VM-5 | R-3 / AC-5 | C API 单测 + UI交互 | 过滤失败回调触发，pStr 正确 |
| VM-6 | R-5 / AC-6 | C API 单测 | unregisterNodeEvent 回调注销 |
| VM-7 | R-6, R-10 / AC-7 | C API 单测 | spanString+singleLine 模式生效 + 回调拿到过滤后值 |
| VM-8 | R-7 / AC-8 | C API 单测 | 非 spanString/singleLine 模式不生效 |
| VM-9 | R-8 / AC-9 | C API 单测 | inputFilter → maxLength 优先级 |
| VM-10 | R-2 / AC-10 | C API 单测 | 空字符串等效于不设置 |
| VM-11 | R-9 / AC-11 | C API 单测 | "\n" 被过滤不插入 |

## API 变更分析

### 新增枚举

| 枚举名称 | 所属枚举类型 | 枚举值 | 开放范围 | 功能描述 | 关联 AC |
|----------|-------------|--------|----------|----------|---------|
| NODE_TEXT_EDITOR_INPUT_FILTER | ArkUI_NodeAttributeType | 22031 | System API | TextEditor inputFilter 正则属性 | AC-1, AC-2, AC-3, AC-10 |
| NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR | ArkUI_NodeEventType | 22009 | System API | TextEditor 过滤失败事件 | AC-4, AC-5, AC-6 |

### 新增 arkoala 子类型枚举

| 枚举名称 | 所属枚举类型 | 枚举值 | 功能描述 | 关联 AC |
|----------|-------------|--------|----------|---------|
| ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR | ArkUIEventSubKind | 67009 | RichEditor 过滤失败事件子类型 | AC-5 |

### 新增 Modifier 函数指针

| 函数指针名称 | 所属结构体 | 功能描述 | 关联 AC |
|--------------|-----------|----------|---------|
| setRichEditorInputFilter | ArkUIRichEditorModifier | 设置 inputFilter 正则 | AC-1 |
| getRichEditorInputFilter | ArkUIRichEditorModifier | 获取 inputFilter 正则 | AC-2 |
| resetRichEditorInputFilter | ArkUIRichEditorModifier | 重置 inputFilter | AC-3 |
| setRichEditorOnInputFilterError | ArkUIRichEditorModifier | 注册过滤失败回调 | AC-4 |
| resetRichEditorOnInputFilterError | ArkUIRichEditorModifier | 注销过滤失败回调 | AC-6 |

## 接口规格

### NODE_TEXT_EDITOR_INPUT_FILTER (属性接口)

| 属性 | 值 |
|------|-----|
| 枚举值 | 22031 |
| 参数格式 | ArkUI_AttributeItem.string = 正则表达式字符串 |
| 获取返回 | ArkUI_AttributeItem.string = 当前正则字符串 |
| 开放范围 | System API |
| 关联 AC | AC-1, AC-2, AC-3, AC-10 |

**行为场景**

| # | 操作 | 参数 | 预期行为 | 关联 AC |
|---|------|------|----------|---------|
| 1 | setAttribute | {.string="^[a-z]*$"} | inputFilter 设置为 "^[a-z]*$" | AC-1 |
| 2 | getAttribute | — | 返回当前 inputFilter 字符串 | AC-2 |
| 3 | resetAttribute | — | inputFilter 清除 | AC-3 |
| 4 | setAttribute | {.string=""} | 空字符串等效于不设置 | AC-10 |

### NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR (事件接口)

| 属性 | 值 |
|------|-----|
| 枚举值 | 22009 |
| 回调数据类型 | ArkUI_StringAsyncEvent |
| 数据提取函数 | OH_ArkUI_NodeEvent_GetStringAsyncEvent |
| ArkUI_StringAsyncEvent.pStr | 被过滤掉的字符内容(UTF-8) |
| 开放范围 | System API |
| 关联 AC | AC-4, AC-5, AC-6 |

**行为场景**

| # | 操作 | 预期行为 | 关联 AC |
|---|------|----------|---------|
| 1 | registerNodeEvent(NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR, targetId, userData) | 回调注册成功 | AC-4 |
| 2 | 输入被拒字符触发事件 | eventReceiver 收到事件，pStr 包含被拒字符 | AC-5 |
| 3 | unregisterNodeEvent(NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR) | 回调注销 | AC-6 |

### FilterWithInputFilter (Pattern 层过滤方法)

| 属性 | 值 |
|------|-----|
| 函数签名 | `bool FilterWithInputFilter(std::u16string& text)` |
| 返回值 | true: 过滤完成（可能有字符被移除）；false: 不应继续插入（如条件不满足） |
| 关联 AC | AC-7, AC-8, AC-9, AC-11 |

**行为场景**

| # | 触发条件 | 预期行为 | 关联 AC |
|---|----------|----------|---------|
| 1 | isSpanStringMode_=true 且 isSingleLineMode_=true 且 InputFilter 非空 | 对 text 执行正则过滤，移除不匹配字符；有被拒字符时 FireOnInputFilterError；修改 text 返回 true | AC-7 |
| 2 | isSpanStringMode_=false 或 isSingleLineMode_=false | 不执行过滤，返回 true（不阻止后续 maxLength 检查） | AC-8 |
| 3 | InputFilter 为空或未设置 | 不执行过滤，返回 true | AC-8 |
| 4 | 过滤后 text 为空（如 "\n" 全被过滤） | text 为空，返回 true；后续 ProcessTextTruncationOperation 处理空文本 | AC-11 |

## 兼容性声明

- **已有 API 行为变更:** 否，纯新增枚举和接口
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** OpenHarmony 6.0
- **API 版本号策略:** @since 标注目标发行版本

## 架构约束

| 关键约束 | 约束说明 | 来源 | 影响 AC |
|----------|----------|------|---------|
| 遵循 C API X-macro 属性路由模式 | 新增条目追加在 .def 末尾 | design.md D-4 | AC-1, AC-2, AC-3 |
| 遵循 C API 事件提取机制 | 使用 OH_ArkUI_NodeEvent_GetStringAsyncEvent | design.md C-5 | AC-5 |
| 属性与事件必须分两次独立调用 | setAttribute + registerNodeEvent 分别操作 | design.md C-6 | AC-4 |
| 仅 spanString+singleLine 模式生效 | FilterWithInputFilter 内部条件检查 | design.md C-1 | AC-7, AC-8 |
| 过滤优先级 inputFilter → maxLength | 插入点在 ProcessTextTruncationOperation 之前 | design.md C-2 | AC-9 |
| 遵循 AGENTS.md 约束 | 不修改 Public API 签名/语义/错误码 | AGENTS.md | 全部 |
| inputFilter 过滤在回调之前 | 回调拿到的值是过滤+截断后的值 | design.md C-7 | AC-7 |
| RichEditor 仅单阶段过滤 | 仅过滤插入值，不对全量二次过滤 | design.md C-8 | AC-7 |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 可测试性 | 所有 11 条 AC 可通过 C API 单测覆盖 | linux_unittest_capi | evidence/ |
| 性能 | FilterWithRegex 正则过滤耗时 ≤ TextField 同函数耗时 | benchmark 对比 | evidence/ |
| 向后兼容 | 不影响现有 TextInput/TextArea inputFilter 行为 | 回归单测 | evidence/ |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | 正则过滤非内容属性 | N/A |
| 大字体 | 否 | N/A | N/A |
| 深色模式 | 否 | N/A | N/A |
| 多窗口/分屏 | 否 | N/A | N/A |

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（仅 CAPI、仅 spanString+singleLine、不涉及 1.2/1.1 路径）
- [x] 无语义模糊表述
- [x] AC 与规则表交叉一致（11 AC ↔ 10 规则，全覆盖）
- [x] 规则表每条有触发条件、预期行为、边界/约束
- [x] API 变更分析包含枚举值、参数格式、数据提取方式
- [x] 兼容性声明明确（纯新增接口、向后兼容）
