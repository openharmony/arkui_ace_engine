# 需求文档

> 一份文档，从原始需求到基线结论。按阶段追加内容，不拆成多份独立文件。

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-001 |
| 需求名称 | 高级组件ChipGroup 新增支持新材质的背景配置能力 |
| 来源 | PRD / 设计规格文档 |
| 提出人 | UX |
| 目标发行版本 | OpenHarmony-7.0-Release |
| 候选 Profile | arkui (子 profile: arkui/component) |
| 优先级 | P0 |
| 状态 | Baselined |

### 原始描述

**原始问题：** 高级组件ChipGroup 新增支持新材质的背景配置能力

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| 应用开发者 | ChipGroup 当前仅支持纯色背景（`backgroundColor` / `selectedBackgroundColor`），无法配置 `systemMaterial` 新材质背景 | 无法实现与新设计语言一致的视觉效果，与其它已支持新材质的组件视觉风格不统一 |
| 最终用户 | ChipGroup 组件视觉效果单一，缺少新材质带来的高级视觉体验 | 界面观感与系统其它组件存在割裂感 |

**期望结果：** ChipGroup、Chip、IconGroupSuffix 组件支持 `systemMaterial` 新材质背景配置，材质效果叠加在纯色背景之上，且区分不同状态（选中/非选中、激活/非激活）。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| 源码事实 | `advanced_ui_component/chipgroup/source/chipgroup.ets` | ChipGroup 当前无任何材质背景相关代码 |
| 源码事实 | `advanced_ui_component/chip/source/chip.ets` / `chip_v16.ets` | Chip 组件当前也无材质背景支持 |
| 参考实现 | `advanced_ui_component/segmentbuttonv2/source/segmentbuttonv2.ets:294,834` | SegmentButtonV2 已实现 `.systemMaterial(this.backgroundSystemMaterial)` |
| API 定义 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.uiMaterial.ets` | `uiMaterial.Material` 类型定义（`MaterialType.NONE` / `SEMI_TRANSPARENT`） |
| 系统材质示例 | `examples/NewMaterial/` / `examples/Select/` | 新材质背景配置的示例应用 |

### 初始范围

**可能包含：**
- ChipGroup 容器新增 `backgroundSystemMaterial` + `selectedBackgroundSystemMaterial`
- Chip 条目新增 `backgroundSystemMaterial` + `activatedBackgroundSystemMaterial`
- IconGroupSuffix 新增 `iconBackgroundSystemMaterial`
- ChipGroup 将材质属性直接传递到 Chip（不通过 ChipItemStyle 中间层）
- 静态版本组件同步更新
- Public API 新增属性需走 API 审批流程

**明确不包含：**
- ChipGroup 组件已有纯色背景行为的变更或删除（材质叠加在纯色之上，纯色行为不变）
- ChipItemStyle 接口新增材质属性（材质由 ChipGroup 直接传递到 Chip）
- 不涉及 ChipGroup 其它已有属性（选中、间距等）的改动
- 不涉及 C++ native pattern 层的实现
- 不涉及其它高级组件的材质背景改动
- 不涉及 SDK `.d.ts` / `.d.ets` API 定义文件的创建

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| ChipGroup 为 ArkTS 高级组件，材质背景通过 `.systemMaterial()` 方法实现 | 技术 | 源码核对 chipgroup.ets、segmentbuttonv2.ets:834 | 已验证 |
| `systemMaterial` 接口使用 `uiMaterial.Material` 类型（`MaterialType.NONE` / `SEMI_TRANSPARENT`） | 技术 | 源码核对 @ohos.arkui.uiMaterial.ets | 已验证 |
| 材质效果叠加在纯色背景之上（Q-2 结论） | 业务 | 需求方确认 | 已验证 |
| ChipGroup 直接传递材质属性到 Chip，不通过 ChipItemStyle 中间层 | 业务 | 需求方确认 | 已验证 |
| ChipGroup/Chip 为 Public API，新增属性需走 API 审批（Q-3 结论） | 业务 | 需求方确认 | 已验证 |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 | 单仓特性增强，涉及 ChipGroup、Chip、IconGroupSuffix 三个关联组件的 ArkTS 层改动 |
| 涉及仓数量 | 1 | 仅 ace_engine 仓 |
| 是否涉及 Public/System API | 是（Public API） | 需求方确认 ChipGroup/Chip 为 Public API |
| 是否涉及安全/性能关键路径 | 否 | 纯 UI 视觉属性扩展 |
| 是否跨 SIG | 否 | 仅涉及 ArkUI SIG |

---

## 二、澄清记录

### 待澄清问题（已澄清）

| 编号 | 问题 | 澄清结论 | 确认来源 |
|------|------|----------|----------|
| Q-1 | 材质背景配置范围？ | **C：两者均支持** — ChipGroup 容器 + Chip 条目均支持材质背景 | 需求方确认 |
| Q-2 | 材质与纯色背景优先级？ | **B：材质叠加** — 材质效果叠加在纯色背景之上，纯色作为底层 | 需求方确认 |
| Q-3 | ChipGroup/Chip API 分类？ | **是 Public API** — 新增属性需走 API 审批流程 | 需求方确认 |
| Q-4 | 目标发行版本？ | **OpenHarmony-7.0-Release** | 需求方确认 |
| Q-5 | 新材质接口类型？ | **`systemMaterial`**（使用 `uiMaterial.Material` 类型），不使用 `backgroundBlurStyle`/`backgroundEffect` 组合 | 需求方确认 |
| Q-6 | 是否区分状态态？ | **是** — ChipGroup 区分选中态/非选中态；Chip 区分激活态/非激活态 | 需求方确认 |
| Q-7 | 属性命名和传递方式？ | ChipGroup 容器：`backgroundSystemMaterial` + `selectedBackgroundSystemMaterial`；Chip 条目：`backgroundSystemMaterial` + `activatedBackgroundSystemMaterial`；IconGroupSuffix：`iconBackgroundSystemMaterial`；ChipGroup 直接传递到 Chip，不通过 ChipItemStyle | 需求方确认 |
| Q-8 | 需求来源？ | **PRD / 设计规格文档** | 需求方确认 |
| Q-9 | FuncID 和 FeatID？ | **07-01-02 / Feat-01** — Owner (youzhi92) 已确认分配 | 需求方确认 |
| Q-10 | 无障碍/国际化/多形态影响？ | **无特殊影响** — 材质为纯视觉效果，不影响无障碍语义；无国际化问题；多形态下材质自适应 | 需求方确认 |

**第二轮澄清（Q-11~Q-14）：**

| 编号 | 问题 | 澄清结论 | 确认来源 |
|------|------|----------|----------|
| Q-11 | FuncID？ | **07-01-02** | Owner (youzhi92) |
| Q-12 | FeatID？ | **Feat-01** | Owner (youzhi92) |
| Q-13 | Owner / 责任人？ | **youzhi92** | Owner |
| Q-14 | 优先级和提出人？ | **P0 / UX** | Owner |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2026-06-10 | AI Agent + 需求方 | Q-1 材质范围 | ChipGroup 容器 + Chip 条目均支持 | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-2 优先级关系 | 材质叠加在纯色之上 | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-3 API 分类 | Public API，需 API 审批 | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-4 目标版本 | OpenHarmony-7.0-Release | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-5/Q-6 接口和状态 | `systemMaterial`，区分选中态/激活态 | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-7 属性命名 | ChipGroup: backgroundSystemMaterial + selectedBackgroundSystemMaterial; Chip: backgroundSystemMaterial + activatedBackgroundSystemMaterial; IconGroupSuffix: iconBackgroundSystemMaterial; 直传不通过 ChipItemStyle | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-8 需求来源 | PRD / 设计规格文档 | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-9 FuncID/FeatID | 07-01-02 / Feat-01 | 已确认 |
| 2026-06-10 | AI Agent + 需求方 | Q-10 无障碍等 | 无特殊影响 | 已确认 |
| 2026-06-10 | AI Agent + Owner | Q-11~Q-14 元数据 | FuncID=07-01-02, FeatID=Feat-01, Owner=youzhi92, P0, 提出人=UX | 已确认 |

### 澄清总结确认

**已向需求方输出总结确认并获得肯定答复：**

> ChipGroup 和 Chip 高级组件新增 `systemMaterial` 类型的新材质背景配置能力，材质效果叠加在已有纯色背景之上，ChipGroup 容器和 Chip 条目均支持，且区分不同状态的材质配置。
>
> 范围含：ChipGroup 容器新增 `backgroundSystemMaterial` + `selectedBackgroundSystemMaterial`；Chip 条目新增 `backgroundSystemMaterial` + `activatedBackgroundSystemMaterial`；IconGroupSuffix 新增 `iconBackgroundSystemMaterial`；ChipGroup 直接传递到 Chip（不通过 ChipItemStyle）；Public API 新增属性需走 API 审批。
>
> 不含：已有纯色背景行为变更；ChipItemStyle 新增属性；C++ pattern 层改动；其它组件改动。
>
> 涉及子系统：ArkUI（1 仓：ace_engine）。
>
> 待补齐项：无（所有阻塞项已解除）

**需求方确认：正确**

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心功能包含哪些？ | ChipGroup/Chip/IconGroupSuffix 新增 `systemMaterial` 类型材质背景属性，区分状态态 | 需求方 | 已确认 |
| 明确不包含哪些？ | ChipItemStyle 新增属性；纯色背景行为变更；C++ pattern 层；其它组件 | 需求方 | 已确认 |
| 是否有分期策略？ | 无分期 | 需求方 | 已确认 |

### 方案探索

| 编号 | 方案概述 | 优势 | 风险/代价 | 选择结论 |
|------|----------|------|-----------|----------|
| A-1 | ChipGroup 容器、Chip 条目、IconGroupSuffix 各层独立新增 `systemMaterial` 属性，ChipGroup 直传 Chip，参照 SegmentButtonV2 `.systemMaterial()` 实现模式 | 与系统已有组件材质模式一致；各层独立配置灵活；向后兼容 | 需同步修改 ChipGroup、Chip、IconGroupSuffix 及其静态版本 | 推荐（已确认） |
| A-2 | 仅 ChipGroup 容器层级新增材质背景，不修改 Chip/IconGroupSuffix | 改动范围更小 | ChipGroup 容器与 Chip 条目视觉不一致；不符合需求方"两者均支持"的要求 | 已放弃 |

**取舍理由：** A-1 方案符合需求方确认的范围（ChipGroup 容器 + Chip 条目 + IconGroupSuffix 均支持，材质叠加，区分状态态），与 SegmentButtonV2 的 `.systemMaterial()` 实现模式保持一致。

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | ArkUI 子系统（ace_engine 仓） | 需求方 | 已确认 |
| 是否需要新增子系统或部件？ | 否 | 需求方 | 已确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增/修改 Public API？ | 是，新增 `systemMaterial` 类型属性（ChipGroup: 2 个; Chip: 2 个; IconGroupSuffix: 1 个） | 需求方 | 已确认 |
| 是否需要新增 System API？ | 否 | 需求方 | 已确认 |
| 是否会废弃已有 API？ | 否（纯新增可选属性） | 需求方 | 已确认 |
| 是否需要新增权限声明？ | 否 | 需求方 | 已确认 |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | 向前/向后兼容？ | 向后兼容 — 新增可选属性，材质叠加在纯色之上不破坏已有行为 | 需求方 | 已确认 |
| 性能 | 渲染性能影响？ | `systemMaterial` 为系统固有能力，预期可控 | 需求方 | 已确认 |
| 安全 | 安全要求？ | 无特殊安全要求 | 需求方 | 已确认 |
| 可靠性 | 异常值处理？ | 默认值为 undefined（不设置材质时保持原行为） | 需求方 | 已确认 |
| 无障碍 | 无障碍影响？ | 无影响 — 材质为纯视觉效果，不影响语义 | 需求方 | 已确认 |
| 国际化 | 国际化影响？ | 无影响 | 需求方 | 已确认 |
| 多形态 | 多形态适配？ | 无特殊影响 — 材质自适应 | 需求方 | 已确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| ArkUI 框架 `.systemMaterial()` 方法 | 运行 | 框架已提供，高级组件可直接调用 | 已确认 |
| `uiMaterial.Material` 类型 | 运行 | 系统提供 `MaterialType.NONE` / `SEMI_TRANSPARENT` | 已确认 |
| SegmentButtonV2 实现模式 | 设计参考 | `.systemMaterial(this.backgroundSystemMaterial)` 模式 | 已确认 |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| ChipGroup/Chip/IconGroupSuffix 三组件需同步修改 | 进度 | 低 | 同一仓，改动可控 | 已确认 |
| Public API 新增属性需走 API 审批 | 流程 | 中 | 提前准备 API 审批材料 | 已确认 |

### AC 完整性

- [x] 每个用户故事有验收标准（见下方）
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
- [x] 标准及以上复杂度已完成方案探索

**阻塞项已解除：**
- FuncID/FeatID：07-01-02 / Feat-01（Owner youzhi92 已确认）
- Owner：youzhi92（已确认）

**结论:** 通过 — 功能范围、AC、方案、FuncID/FeatID、Owner 已全部确认，基线稳定

---

## 三、需求基线

> 澄清完成后固化。manifest.md 是事实源，此处为审批结论。

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2026-06-10 |
| Owner | youzhi92 |
| 确认人 | youzhi92（澄清确认已获得） |
| 复杂度 | 标准 |
| Profile | arkui (子 profile: arkui/component) |
| 目标发行版本 | OpenHarmony-7.0-Release（引用 manifest.target_release） |
| 版本状态 | proposed |

### 问题陈述

ChipGroup、Chip、IconGroupSuffix 高级组件当前仅支持纯色背景配置，无法设置 `systemMaterial` 新材质背景，导致与系统其它已支持新材质的组件（如 SegmentButtonV2、Select）视觉风格不统一。需要在 OpenHarmony 7.0 中为这三个组件新增 `systemMaterial` 类型的新材质背景配置能力，材质效果叠加在纯色背景之上，并区分不同交互状态（ChipGroup: 选中/非选中; Chip: 激活/非激活; IconGroupSuffix: 单一材质）。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| ChipGroup/Chip/IconGroupSuffix 支持新材质背景配置 | 新增 5 个 `systemMaterial` 属性均可设置且生效 | Host Preview SpecTest + 设备验证 |
| 材质叠加在纯色之上不影响向后兼容 | 不设置新属性时行为与当前完全一致 | 向后兼容 AC 测试 |
| 不同状态态材质正确切换 | 选中/非选中、激活/非激活态材质正确渲染 | 状态切换 AC 测试 |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为应用开发者，想要为 ChipGroup 容器设置新材质背景，以便与系统新设计语言对齐 | P0 |
| US-2 | 作为应用开发者，想要为 ChipGroup 容器区分选中态和非选中态的材质背景，以便在不同交互状态下呈现不同视觉效果 | P0 |
| US-3 | 作为应用开发者，想要为 Chip 条目设置新材质背景，以便 Chip 具有新材质的视觉体验 | P0 |
| US-4 | 作为应用开发者，想要为 Chip 条目区分激活态和非激活态的材质背景 | P0 |
| US-5 | 作为应用开发者，想要为 IconGroupSuffix 设置新材质背景，以便 suffix 区域与 ChipGroup 整体风格统一 | P1 |
| US-6 | 作为应用开发者，想要在不设置新材质属性时保持原有纯色背景行为不变（向后兼容） | P0 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN 开发者设置 ChipGroup 的 `backgroundSystemMaterial` THEN ChipGroup 容器渲染对应的 `systemMaterial` 新材质背景 | 正常 | US-1 |
| AC-2 | WHEN 开发者设置 ChipGroup 的 `selectedBackgroundSystemMaterial` THEN ChipGroup 容器在选中状态下渲染对应的材质背景 | 正常 | US-2 |
| AC-3 | WHEN 开发者设置 Chip 的 `backgroundSystemMaterial` THEN Chip 条目渲染对应的材质背景 | 正常 | US-3 |
| AC-4 | WHEN 开发者设置 Chip 的 `activatedBackgroundSystemMaterial` THEN Chip 条目在激活状态下渲染对应的材质背景 | 正常 | US-4 |
| AC-5 | WHEN 开发者设置 IconGroupSuffix 的 `iconBackgroundSystemMaterial` THEN IconGroupSuffix 区域渲染对应的材质背景 | 正常 | US-5 |
| AC-6 | WHEN 开发者不设置任何新材质属性 THEN ChipGroup/Chip/IconGroupSuffix 保持原有纯色背景行为，视觉表现与当前版本完全一致 | 正常 | US-6 |
| AC-7 | WHEN 开发者同时设置纯色背景和新材质 THEN 新材质效果叠加在纯色背景之上，纯色作为底层 | 正常 | US-1, US-3 |
| AC-8 | WHEN 开发者设置 `MaterialType.NONE` THEN 组件不渲染材质效果，行为等同于不设置 | 边界 | US-1 |
| AC-9 | WHEN ChipGroup 传递材质属性到 Chip THEN Chip 条目正确接收并渲染 ChipGroup 传入的材质属性 | 正常 | US-3 |
| AC-10 | WHEN ChipGroup/Chip 状态发生切换（选中→非选中 / 激活→非激活）THEN 材质背景正确切换到对应状态的材质配置 | 正常 | US-2, US-4 |
| AC-11 | WHEN 开发者设置材质属性为 undefined THEN 组件不渲染材质效果，等同于不设置 | 边界 | US-6 |

### 范围边界

**包含：** ChipGroup 容器材质背景（非选中态 + 选中态）；Chip 条目材质背景（非激活态 + 激活态）；IconGroupSuffix 材质背景；ChipGroup 直传 Chip；Public API 新增属性审批；动态版本和静态版本同步更新

**不包含：** ChipItemStyle 新增属性；纯色背景行为变更；C++ pattern 层改动；其它组件改动；SDK `.d.ts` 文件创建

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 当前职责 | 影响类型 | Owner |
|--------|------|-----------|----------|----------|-------|
| ArkUI | ace_engine | `advanced_ui_component/chipgroup/source/chipgroup.ets` | ChipGroup 组件实现 | 修改（新增属性） | youzhi92 |
| ArkUI | ace_engine | `advanced_ui_component/chip/source/chip.ets` / `chip_v16.ets` | Chip 组件实现 | 修改（新增属性） | youzhi92 |
| ArkUI | ace_engine | `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.ChipGroup.ets` | ChipGroup 静态版本 | 修改（同步新增属性） | youzhi92 |
| ArkUI | ace_engine | `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.Chip.ets` | Chip 静态版本 | 修改（同步新增属性） | youzhi92 |

### API 变更项清单

| API 名称 | 变更类型 | 开放范围 | 概要说明 |
|----------|----------|----------|----------|
| ChipGroup.backgroundSystemMaterial | 新增 | Public | ChipGroup 容器非选中态新材质背景 |
| ChipGroup.selectedBackgroundSystemMaterial | 新增 | Public | ChipGroup 容器选中态新材质背景 |
| Chip.backgroundSystemMaterial | 新增 | Public | Chip 条目非激活态新材质背景 |
| Chip.activatedBackgroundSystemMaterial | 新增 | Public | Chip 条目激活态新材质背景 |
| IconGroupSuffix.iconBackgroundSystemMaterial | 新增 | Public | IconGroupSuffix 新材质背景 |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 是 | 新材质渲染需评估热路径预算 | design.md |
| 安全与权限 | 否/N/A | 纯 UI 视觉属性，无安全影响 | N/A |
| 兼容性 | 是 | 新增可选属性向后兼容，材质叠加需 spec 约束 | spec.md |
| API/SDK | 是 | Public API 新增 5 个属性 | design.md / spec.md |
| IPC/跨进程 | 否/N/A | 无跨进程通信 | N/A |
| 构建与部件 | 否/N/A | 无新增部件或构建依赖 | N/A |
| 国际化/无障碍 | 否/N/A | 材质为纯视觉效果，不影响语义和国际化 | N/A |
| 数据迁移 | 否/N/A | 无数据迁移 | N/A |

### 变更控制

| 变更类型 | 触发条件 | 处理规则 |
|----------|----------|----------|
| 范围新增 | 新增用户故事或组件 | 重新评估复杂度和设计影响 |
| AC 变更 | 修改可观察行为 | 重新审批基线和 Spec |
| API 变更 | 新增/修改 Public API | 触发 API 审批 |
| 目标版本变更 | 交付版本调整 | 更新 manifest.target_release |

### 进入设计/Spec 条件

- [x] 所有 P0/P1 用户故事有 AC
- [x] 每条 AC 可测试、可度量
- [x] 范围内/外已确认
- [x] `manifest.target_release` 已确认（OpenHarmony-7.0-Release）
- [x] `manifest.profile` 已确认（arkui/component）
- [x] 涉及仓、模块、SIG 的 Owner 已识别（Owner = youzhi92）
- [x] 不涉及项已标记 N/A
- [x] 变更控制规则已确认
- [x] FuncID/FeatID 已由 Owner/SIG 分配（07-01-02 / Feat-01 已确认）

**阻塞项已解除：**
- FuncID/FeatID：07-01-02 / Feat-01（Owner youzhi92 已确认）
- Owner：youzhi92（已确认）

**基线结论:** 通过 — 所有阻塞项已由 Owner (youzhi92) 解除，FuncID=07-01-02, FeatID=Feat-01 已确认，需求范围、AC、方案稳定，可进入 Stage 2