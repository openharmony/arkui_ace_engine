---
target_release:
  id: OpenHarmony-6.0-Release
  status: proposed
---

# 需求文档

> 一份文档，从原始需求到基线结论。按阶段追加内容，不拆成多份独立文件。

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-002 |
| 需求名称 | RichEditor CAPI 添加 inputFilter 与 onInputFilterError 支持 |
| 来源 | NDK 开发者需求 + API 完整性对齐 |
| 提出人 | ArkUI NDK 团队 |
| 目标发行版本 | OpenHarmony-6.0-Release |
| 候选 Profile | arkui (subprofile: capi) |
| 优先级 | P1 |
| 状态 | Draft |

### 原始描述

**原始问题：** TextInput/TextArea 组件的 C API 已支持 `NODE_TEXT_INPUT_INPUT_FILTER`（正则白名单约束输入）和 `NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR`（过滤失败回调），但 RichEditor 组件（CAPI 中对应 `ARKUI_NODE_TEXT_EDITOR`）尚无对应能力。NDK 开发者在使用 TextEditor 创建富文本编辑节点时，无法通过 C API 对输入内容做正则过滤，与 TextInput/TextArea 的能力不对齐。

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| NDK 应用开发者 | 无法通过 C API 对 TextEditor 输入做正则约束 | 单行富文本场景下无法过滤非法字符 |
| 框架开发者 | C API 属性覆盖不一致（TextInput 有、RichEditor 无） | API 完整性缺口 |

**期望结果：** 在 TextEditor 的 C API 中新增 `NODE_TEXT_EDITOR_INPUT_FILTER` 属性和 `NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR` 事件，使 NDK 开发者能通过正则约束输入并获取过滤失败通知。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| 源码对照 | interfaces/native/native_node.h | TextInput 有 INPUT_FILTER 枚举(L4001)，TextEditor 无 |
| 源码对照 | interfaces/native/node/rich_editor_properties.def | 31 条 X-macro，无 InputFilter |
| 源码对照 | rich_editor_layout_property.h | 无 InputFilter 属性声明 |
| 源码对照 | rich_editor_model.h | 无 SetInputFilter 方法 |
| 源码对照 | content_controller.cpp | FilterWithRegex(L314) 仅服务于 TextField |
| 参考文档 | zhengze_feature_0715/RichEditor_InputFilter_CAPI_SDD.md | 全链路适配点清单 |

### 初始范围

**可能包含：**
- C API 新增 `NODE_TEXT_EDITOR_INPUT_FILTER` 属性枚举
- C API 新增 `NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR` 事件枚举
- .def X-macro 新增 InputFilter 条目
- style_modifier.cpp 新增 setter/getter/resetter
- arkoala_api.h 新增 Modifier 函数指针和事件子类型
- rich_editor_dynamic_modifier.cpp 新增桥接实现
- event_converter.cpp 新增事件转换
- Model 层新增 SetInputFilter/GetInputFilter/ResetInputFilter + 事件注册/注销
- LayoutProperty 新增 InputFilter 属性
- EventHub 新增 onInputFilterError 回调
- Pattern 层新增 FilterWithInputFilter 过滤逻辑
- 过滤工具提取/复用（FilterWithRegex 共享函数）
- C API 单元测试覆盖

**明确不包含：**
- ArkTS 1.2 强基(IDLize)路径适配
- ArkTS 1.1 动态(JSI Bridge)路径适配
- 属性字符串接口（仅提供组件属性接口）
- 多行模式下的 inputFilter 生效（仅 isSpanStringMode_ && isSingleLineMode_ 下生效）
- ArkTS 前端 inputFilter 行为变更

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| inputFilter 仅在 isSpanStringMode_ && isSingleLineMode_ 下生效 | 技术 | 源码确认 isSpanStringMode_ (TextPattern:667) 和 isSingleLineMode_ (RichEditorPattern:1487) | 已验证 |
| 事件数据提取方式与 TextInput 一致（OH_ArkUI_NodeEvent_GetStringAsyncEvent） | 技术 | 源码核对 ArkUI_StringAsyncEvent 结构体和提取函数 | 已验证 |
| RichEditor 属性路由使用 X-macro .def 驱动（非手写函数指针数组） | 技术 | 源码核对 rich_editor_properties.def 和 style_modifier.cpp 展开 | 已验证 |
| 过滤优先级：inputFilter → maxLength（与 TextInput 一致） | 技术 | 源码核对 ProcessInsertValue 和 ProcessTextTruncationOperation 顺序 | 已验证 |
| C API 属性与事件必须分两次独立调用（setAttribute + registerNodeEvent） | 架构 | C API 单体设计哲学 | 已验证 |
| 目标仓 AGENTS.md 存在且有约束 | 架构 | 已读取 AGENTS.md（code-first, evidence-first, 不修改 Public API 签名/语义） | 已验证 |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 | 单仓特性，涉及 System API 新增，涉及多模块层级（6层调用链），但不跨仓/SIG |
| 涉及仓数量 | 1 | ace_engine |
| 是否涉及 Public/System API | 是（System API 新增） | C API 新增 2 个枚举值 |
| 是否涉及安全/性能关键路径 | 否 | 纯属性/事件设置，无安全/性能风险 |
| 是否跨 SIG | 否 | 仅涉及 ArkUI SIG |

### 进入澄清条件

- [x] 原始问题和期望结果已记录
- [x] 需求来源和责任人已明确
- [x] 初始范围和不包含项已记录
- [x] 关键假设和待澄清问题已列出
- [x] 复杂度有判断（标准级）

---

## 二、澄清记录

> 标准级需求：按主题分组，每轮提出 3-5 个相关问题。

### 待澄清问题

| 编号 | 问题 | 为什么需要澄清 | 状态 |
|------|------|----------------|------|
| Q-1 | inputFilter 是否仅在属性字符串+单行模式下生效？是否考虑多行模式下的扩展场景？ | RichEditor 默认是多行组件，需要明确生效范围避免实现偏差 | 已澄清 |
| Q-2 | 过滤工具如何复用？提取共享函数还是 inline 复制？ | 影响架构整洁性和迁移风险 | 已澄清 |
| Q-3 | Enter 键在单行模式下的 "\n" 字符如何处理？是否被 inputFilter 过滤？ | TextInput 中 onSubmit 和 inputFilter 有交互关系，需确认 RichEditor 对齐策略 | 已澄清 |
| Q-4 | maxLength 和 inputFilter 的优先级关系是否与 TextInput 一致？ | 需确认过滤截断顺序一致性 | 已澄清 |
| Q-5 | onInputFilterError 回调的数据提取方式是否与 TextInput 一致？ | C API 事件数据提取机制统一性 | 已澄清 |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2026-07-15 | ArkUI NDK 团队 | 生效范围 | 仅 isSpanStringMode_ && isSingleLineMode_ 下生效 | 确认 |
| 2026-07-15 | ArkUI NDK 团队 | 复用方案 | 推荐 A（提取共享 FilterWithRegex），B（inline）为备选 | 后续 design.md 决策 |
| 2026-07-15 | ArkUI NDK 团队 | Enter键处理 | "\n" 被 inputFilter 过滤，过滤后文本为空则不插入 | 确认 |
| 2026-07-15 | ArkUI NDK 团队 | 优先级 | inputFilter → maxLength，与 TextInput 一致 | 确认 |
| 2026-07-15 | ArkUI NDK 团队 | 数据提取 | 与 TextInput 一致，使用 OH_ArkUI_NodeEvent_GetStringAsyncEvent | 确认 |

### 方案探索

| 编号 | 方案概述 | 优势 | 风险/代价 | 选择结论 |
|------|----------|------|-----------|----------|
| A-1 | 提取 FilterWithRegex 为共享工具函数 | 架构整洁、零重复 | 新增 2 个文件，需修改 content_controller.cpp 调用方式 | 推荐 |
| A-2 | inline 复制 FilterWithRegex 核心逻辑 | 最小侵入、零迁移风险 | 4 行 regex 逻辑重复 | 备选 |

**取舍理由：** 方案 A-1 架构更整洁，长期可维护性好；方案 A-2 适合快速验证。最终选择取决于 Owner 对新增文件的接受度。

### 上下文与知识源检索日志

| 编号 | 来源 | 查询/读取内容 | 关键发现 | 可信度 | 用于 | 命中/原因 |
|------|------|---------------|----------|--------|------|-----------|
| K-1 | 源码 | native_node.h TEXT_EDITOR 枚举 | 31 属性 + 10 事件枚举，无 INPUT_FILTER | 高 | 范围/API | 命中 |
| K-2 | 源码 | rich_editor_properties.def | 31 条 X-macro，无 InputFilter 条目 | 高 | 架构/API | 命中 |
| K-3 | 源码 | rich_editor_layout_property.h | 无 InputFilter 属性 | 高 | 架构 | 命中 |
| K-4 | 源码 | rich_editor_model.h | 无 SetInputFilter 方法 | 高 | 架构 | 命中 |
| K-5 | 源码 | arkoala_api.h ArkUIRichEditorModifier | ~170 函数指针，无 InputFilter 相关 | 高 | 架构 | 命中 |
| K-6 | 源码 | content_controller.cpp FilterWithRegex(L314) | 4 行核心逻辑可提取复用 | 高 | 设计 | 命中 |
| K-7 | 源码 | rich_editor_pattern.h isSingleLineMode_(L1487) | 存在 | 高 | 设计 | 命中 |
| K-8 | 源码 | text_pattern.h isSpanStringMode_(L667) | 存在于父类 TextPattern | 高 | 设计 | 命中 |
| K-9 | AGENTS.md | 项目规则 | code-first, 不修改 Public API 签名/语义/错误码 | 高 | 约束 | 命中 |
| K-10 | 参考文档 | zhengze_feature_0715/RichEditor_InputFilter_CAPI_SDD.md | 全链路 18 文件适配点清单 | 中 | 参考 | 命中（仅参考，以源码为准） |
| K-11 | 参考文档 | zhengze_feature_0715/CAPI相关.txt | TextInput CAPI inputFilter 调用链梳理 | 中 | 参考 | 命中（仅参考，以源码为准） |

**上下文结论：**
- 高可信结论：RichEditor 全链路缺失 inputFilter；TextInput/TextArea 已有完整实现可作为参考基准；X-macro 驱动属性路由；FilterWithRegex 可复用
- 待确认结论：方案 A-1 vs A-2 最终选择需 Owner 确认；枚举值编号范围需确认当前最大值后确定
- 未使用来源：多仓知识库（本需求仅涉及 ace_engine 单仓）

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心功能包含哪些？ | inputFilter 正则设置/获取/重置 + onInputFilterError 回调注册/触发/注销 | ArkUI NDK 团队 | 已确认 |
| 明确不包含哪些？ | 属性字符串接口、1.2强基/1.1动态路径、多行模式生效 | ArkUI NDK 团队 | 已确认 |
| 是否有分期策略？ | 无，一次性交付 | ArkUI NDK 团队 | 已确认 |

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | ArkUI (ace_engine) | ArkUI NDK 团队 | 已确认 |
| 是否需要新增子系统或部件？ | 否 | ArkUI NDK 团队 | 已确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增/修改 Public API？ | 否 | — | — |
| 是否需要新增 System API？ | 是，2 个枚举值 | ArkUI NDK 团队 | 已确认 |
| 是否会废弃已有 API？ | 否 | — | — |
| 是否需要新增权限声明？ | 否 | — | — |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | 向后兼容？ | 是，纯新增接口 | ArkUI NDK 团队 | 已确认 |
| 性能 | 正则过滤性能？ | regex_replace 已在 TextField 验证，RichEditor 仅单行模式生效，影响可控 | ArkUI NDK 团队 | 已确认 |
| 安全 | 权限/数据安全？ | 无新权限、不存储敏感数据 | ArkUI NDK 团队 | 已确认 |
| 可靠性 | 过滤误拒/误放？ | regex 为白名单模式，逻辑与 TextInput 一致 | ArkUI NDK 团队 | 已确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| TextInput FilterWithRegex 核心逻辑 | 技术 | 复用或提取共享函数 | 已确认 |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| RichEditor 过滤逻辑与 TextInput 存在差异（无 ContentController 两阶段机制） | 技术 | 中 | Pattern 层直接执行，仅作用于插入值 | 已确认 |
| 枚举值编号需在现有范围末尾追加 | 技术 | 低 | 紧跟现有最大值编号 | 已确认 |

### AC 完整性

- [x] 每个用户故事有验收标准
- [x] AC 全部使用 WHEN/THEN 格式
- [x] 覆盖正常流程、异常流程、边界条件
- [x] AC 可测试、可度量

### 澄清结论

- [x] 功能范围已完全明确
- [x] 子系统影响已识别
- [x] API 变更已评估
- [x] 兼容性和非功能需求已确认
- [x] 依赖和风险已识别且有缓解方案
- [x] AC 完整可测试
- [x] 标准级已完成方案探索（2 个方案 + 取舍理由）

**结论:** 通过

---

## 三、需求基线

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2026-07-15 |
| Owner | 待确认 |
| 确认人 | ArkUI NDK 团队 |
| 复杂度 | 标准 |
| Profile | arkui (subprofile: capi) |
| 目标发行版本 | OpenHarmony-6.0-Release |
| 版本状态 | proposed |

### 问题陈述

RichEditor 组件（CAPI 中对应 ARKUI_NODE_TEXT_EDITOR）缺少 inputFilter 正则约束输入和 onInputFilterError 过滤失败回调能力，与 TextInput/TextArea 已有的同功能不对齐。需要补齐 CAPI 路径的 inputFilter 全链路支持，仅在属性字符串+单行模式下生效。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| CAPI 支持 inputFilter 设置/获取/重置 | setter/getter/resetter 函数可用 | C API 单元测试 |
| CAPI 支持 onInputFilterError 回调注册/触发/注销 | 回调可注册、过滤失败可触发、可注销 | C API 单元测试 + UI 交互验证 |
| 过滤行为与 TextInput 一致 | inputFilter → maxLength 优先级、正则白名单语义、事件数据格式 | 对比测试 |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为 NDK 开发者，我想要通过 C API 设置 TextEditor 的正则输入约束，以便过滤非法字符 | P0 |
| US-2 | 作为 NDK 开发者，我想要通过 C API 注册过滤失败回调，以便获知被过滤掉的字符内容 | P0 |
| US-3 | 作为 NDK 开发者，我想要在单行+属性字符串模式下使用 inputFilter 控制输入行为 | P1 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN setAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER, {.string="^[a-z]*$"}) THEN TextEditor 的正则约束设置为 "^[a-z]*$" | 正常 | US-1 |
| AC-2 | WHEN getAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER) THEN 返回当前设置的 inputFilter 正则字符串 | 正常 | US-1 |
| AC-3 | WHEN resetAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER) THEN inputFilter 被清除，恢复为不设置状态 | 正常 | US-1 |
| AC-4 | WHEN registerNodeEvent(node, NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR, targetId, userData) THEN 过滤失败回调注册成功 | 正常 | US-2 |
| AC-5 | WHEN 输入字符被 inputFilter 过滤掉 THEN 通过 OH_ArkUI_NodeEvent_GetStringAsyncEvent 可获取被拒字符的 pStr | 正常 | US-2 |
| AC-6 | WHEN unregisterNodeEvent(node, NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR) THEN 回调注销成功，后续过滤失败不再触发回调 | 正常 | US-2 |
| AC-7 | WHEN isSpanStringMode_=true 且 isSingleLineMode_=true THEN inputFilter 过滤逻辑生效 | 正常 | US-3 |
| AC-8 | WHEN isSpanStringMode_=false 或 isSingleLineMode_=false THEN inputFilter 设置被忽略，不执行过滤 | 边界 | US-3 |
| AC-9 | WHEN inputFilter 正则生效且 maxLength 也设置 THEN 过滤优先级为 inputFilter → maxLength（先过滤再截断） | 正常 | US-3 |
| AC-10 | WHEN inputFilter 正则为空字符串 THEN 过滤不生效，等同于不设置 | 边界 | US-1 |
| AC-11 | WHEN 单行模式下 Enter 键输入 "\n" 且 inputFilter 不匹配 "\n" THEN "\n" 被过滤掉，不插入 | 边界 | US-3 |

### 范围边界

**包含：** CAPI inputFilter 属性/事件全链路实现、过滤工具复用、C API 单元测试
**不包含：** 属性字符串接口、1.2强基/1.1动态路径、多行模式生效、ArkTS 前端行为变更

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 当前职责 | 影响类型 | Owner |
|--------|------|-----------|----------|----------|-------|
| ArkUI | ace_engine | interfaces/native/ | C API 枚举+属性路由+事件转换 | 新增 | ace_engine-dev |
| ArkUI | ace_engine | frameworks/core/interfaces/arkoala/ | Modifier 函数指针桥接 | 新增 | ace_engine-dev |
| ArkUI | ace_engine | frameworks/core/components_ng/pattern/rich_editor/ | Model/LayoutProperty/EventHub/Pattern | 新增+修改 | ace_engine-dev |
| ArkUI | ace_engine | frameworks/core/components_ng/pattern/text_field/ | FilterWithRegex 共享提取 | 修改 | ace_engine-dev |

### API 变更项清单

| API 名称 | 变更类型 | 开放范围 | 概要说明 |
|----------|----------|----------|----------|
| NODE_TEXT_EDITOR_INPUT_FILTER | 新增 | System API | TextEditor inputFilter 正则属性枚举 |
| NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR | 新增 | System API | TextEditor 过滤失败事件枚举 |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 否 | 正则过滤已在 TextField 验证，RichEditor 仅单行模式生效 | N/A |
| 安全与权限 | 否 | 无新权限/无数据访问 | N/A |
| 兼容性 | 否 | 纯新增接口，不修改已有接口行为 | N/A |
| API/SDK | 是 | 新增 System API 2 个枚举值 | design.md / spec.md |
| IPC/跨进程 | 否 | 纯框架内属性和事件 | N/A |
| 构建与部件 | 否 | 无新部件/依赖（方案 A 新增 2 个源文件在现有目录下） | N/A |
| 国际化/无障碍 | 否 | 正则过滤非文本内容 | N/A |
| 数据迁移 | 否 | 无持久化数据 | N/A |

### 变更控制

| 变更类型 | 触发条件 | 处理规则 |
|----------|----------|----------|
| 范围新增 | 新增用户故事或仓/模块 | 重新评估复杂度和设计影响 |
| AC 变更 | 修改可观察行为或错误码 | 重新审批基线和 Spec |
| API 变更 | 新增/修改 Public/System API | 触发设计审批 |

### 进入设计/Spec 条件

- [x] 所有 P0/P1 用户故事有 AC
- [x] 每条 AC 可测试、可度量
- [x] 范围内/外已确认
- [x] `proposal.target_release` 已确认
- [x] `manifest.profile` 已确认 (arkui/capi)
- [x] 涉及仓、模块、SIG 已识别
- [x] 不涉及项已标记 N/A
- [x] 变更控制规则已确认
- [x] 标准级澄清问题已逐项关闭
- [x] 上下文与知识源检索日志已填写
- [x] 目标仓 AGENTS.md 已检查并记录关键约束

**基线结论:** 通过
