---
target_release:
  id: OpenHarmony-6.1-Release
  status: proposed
---

# 需求文档

> 编号 `20260126978228`。一份文档，从原始需求到基线结论。本版为删除重跑后的版本，所有行号引用均经当次会话核验。

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | `20260126978228` |
| 需求名称 | ArcSwiper 与 ArcAlphabetIndexer C API（NDK）开放 |
| 来源 | 用户需求（手表高性能场景）；接口范围 = `interface_sdk_c` PR #5447 |
| 提出人 | ArkUI / 手表业务方（待 Owner 确认） |
| 目标发行版本 | OpenHarmony-6.1-Release（依据当前工作分支 `OpenHarmony-6.1-Release` 与 PR `@since 26.1.0`；待 Owner 终确认） |
| 候选 Profile | `arkui`（主）/ 子 profile `capi`、`component` |
| 优先级 | P0 |
| 状态 | Clarifying |

### 原始描述

**原始问题：** ArcSwiper 和 ArcAlphabetIndexer 已通过 ArkTS（`component_ext/`）在手表上提供导航能力，其底层 NG 实现复用 `SwiperPattern`/`IndexerPattern`（`ArcSwiperPattern : SwiperPattern`、`ArcIndexerPattern : IndexerPattern`）。手表部分特性需要高性能 Native 实现，因此需要把这两个组件以稳定 C ABI（NDK，`ArkUI_NodeHandle` 体系）开放出来，供 C/C++ Native 调用方直接使用。

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| 手表 Native 应用开发者 | 两个组件仅有 ArkTS 入口，无 C/NDK 入口 | 无法在 Native 高性能路径使用，跨语言开销不满足手表交互预算 |
| ArkUI 组件维护者 | NDK 层对这两个组件完全空白，无节点类型、无属性分发、无事件/控制函数 | 接口与 ArkTS 形成两套入口，长期维护成本高、语义易漂移 |

**期望结果：** Native 调用方能以 `ArkUI_NodeHandle` + `OH_ArkUI_*` C ABI 使用两个组件；PR #5447 定义范围内的属性均支持 set/get/reset，事件均支持 register/unregister，控制函数可用；默认值、非法值、状态、事件参数与 ArkTS 等价，不产生第二套语义。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| 接口定义（真相源） | https://gitcode.com/openharmony/interface_sdk_c/pull/5447 | PR 改 2 文件：`arkui/ace_engine/native/native_node.h`(+462)、`native_type.h`(+27)；当次会话经 gitcode API 完整读取 |
| 本地实现现状 | `foundation/arkui/ace_engine`（分支 `OpenHarmony-6.1-Release`） | NDK 层空白，详见检索日志 |
| ArkTS 既有实现 | `component_ext/arc_swiper/`、`component_ext/arc_alphabet_indexer/` | NAPI + JS 抽象层，属性/事件/控制器已存在 |

### 初始范围

**可能包含：**
- 新增 2 个 NDK 节点类型：`ARKUI_NODE_ARC_ALPHABET_INDEXER`(=23)、`ARKUI_NODE_ARC_SWIPER`(=1022)
- 新增 22 个属性枚举（ArcAlphabetIndexer 14 + ArcSwiper 8），含三向 set/get/reset 分发
- 新增 5 个事件枚举（ArcAlphabetIndexer 1 + ArcSwiper 4），含 register/unregister/reset 配对
- 新增 3 个控制函数：`OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext/FinishAnimation`
- 新增 1 个枚举类型 `OH_ArkUI_ArcDirection`（3/6/9 点方向）
- ABI/SDK 元数据同步（`libace.map`、`libace.ndk.json`）
- 专项 CAPI 单元测试

**明确不包含：**
- 新增或改变 ArkTS 行为、默认值或动画/手势/布局算法（仅复用现有 NG 实现）
- 新增权限、IPC、跨进程、持久化、网络
- 扩展 PR #5447 之外的组件能力或属性
- 安全/隐私敏感数据处理（无 → 不产 threat-model）

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| 两个组件底层 NG 实现可被 C API 直接复用，无需新建状态机 | 技术 | 源码核验 `arc_swiper_pattern.h:25`、`arc_indexer_pattern.h:27` | 已验证 |
| NDK 层当前对两组件完全空白 | 技术 | `native_node.h` grep 无命中，NodeType 止于 `ARKUI_NODE_PICKER=1018`(行153) | 已验证 |
| PR #5447 是接口真相源，ace_engine 实现 | 兼容性 | gitcode API 读取 PR 全量 diff | 已验证 |
| `ArkUI_CrownSensitivity` 枚举已存在（INDICATOR 灵敏度依赖） | 技术 | 待 spec 阶段核验 native_type.h | 待验证 |
| 控制函数开放级别（Public / System API） | 业务 | PR 头文件注释未见 `@systemapi`，待 Owner 终确认 | 待验证 |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 关键（critical） | C ABI + 事件生命周期 + 手表热路径（帧级 `ON_GESTURE_SWIPE`） |
| 涉及仓数量 | 2 仓 | `interface_sdk_c`（接口声明）+ `ace_engine`（实现） |
| 是否涉及 Public/System API | 是 | 新增 NDK 节点 C API（`@since 26.1.0`）；控制函数开放级别待确认 |
| 是否涉及安全/性能关键路径 | 性能=是 / 安全=否 | 手表交互热路径；无权限/隐私边界 |
| 是否跨 SIG | 否 | 仅 ArkUI 子系统内 |

### 进入澄清条件

- [x] 原始问题和期望结果已记录
- [ ] 需求来源和责任人已明确（Owner/提出人待确认）
- [x] 初始范围和不包含项已记录
- [x] 关键假设和待澄清问题已列出
- [x] 复杂度有判断（critical）

---

## 二、澄清记录

### 待澄清问题

| 编号 | 问题 | 为什么需要澄清 | 状态 |
|------|------|----------------|------|
| Q-1 | FuncID、FeatID、功能域与长期 `specs/` 路径 | ArkUI profile 要求 Define gate 前由 Owner 分配；当前缺失 → Define gate 阻塞 | 待 Owner 确认 |
| Q-2 | 目标发行版本终确认 | 当前按分支推断 `OpenHarmony-6.1-Release`（对应 API 26.1.0），需 Owner 终确认 | 待 Owner 确认 |
| Q-3 | 控制函数开放级别（Public / System API）与 PR #5447 合入 commit | 影响导出符号、`libace.ndk.json` 版本标注与可见性；PR 注释未见 `@systemapi` | 待 Owner 确认（接口范围已可读） |
| Q-4 | 手表性能验收阈值与设备最小矩阵 | `ON_GESTURE_SWIPE` 帧级事件在手表上的预算需明确 | 待性能 Owner 确认 |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2026-07-14 | AI 起草 | 接口范围与实现现状核验 | PR #5447 全量可读；ace_engine NDK 层空白 | Owner 确认 Q-1~Q-4 |

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心功能包含哪些？ | 2 节点类型 + 22 属性 + 5 事件 + 3 控制函数 + 1 枚举 | AI 起草（依据 PR #5447） | 待确认 |
| 明确不包含哪些？ | 不改 ArkTS 行为/算法；无权限/IPC/持久化 | AI 起草 | 待确认 |
| 是否有分期策略？ | 可按组件分期（ArcSwiper 优先，ArcAlphabetIndexer 次之）；待 Owner 定 | AI 建议 | 待确认 |

### 方案探索

> 标准及以上必填。列出技术路线级方案选型。

| 编号 | 方案概述 | 优势 | 风险/代价 | 选择结论 |
|------|----------|------|-----------|----------|
| A-1 | C API 复用现有 NG Model/Pattern/Theme，通过 modifier + 属性三向分发桥接 | 与 ArkTS 同一套状态机与默认值，无语义分叉；与 Swiper 参照一致 | 需补齐 NDK 路由、校验和测试（约 14 文件） | 推荐 |
| A-2 | 为 C API 建独立状态与默认值 | 局部实现直接 | 语义分叉、双份维护、性能与一致性风险 | 放弃 |
| A-3 | 仅做 ArkTS/NAPI 包装给 Native | 实现量小 | 仍有跨语言开销，不满足手表高性能目标 | 放弃 |

**取舍理由：** A-1 与本仓既有 NDK 组件（以 Swiper 为参照）完全一致，能从结构上保证 C API 与 ArkTS 行为等价；A-2/A-3 引入分叉或跨语言开销，违背"高性能 + 不产生第二套语义"的期望结果。

### 上下文与知识源检索日志

> 当次会话逐条记录。命中和未命中都写。

| 编号 | 来源 | 查询/读取内容 | 关键发现 | 可信度 | 用于 | 命中/原因 |
|------|------|---------------|----------|--------|------|-----------|
| K-1 | 仓 `CLAUDE.md` / `AGENTS.md` | 仓级 Agent 规则 | KB-first、真实源码为准（code-first）、禁止伪造/假设、CAPI UT 约定 | 高 | 流程/验证 | 命中 |
| K-2 | `interface_sdk_c` PR #5447（gitcode API） | 全量 diff（2 文件） | 接口真相源：2 NodeType(23/1022)、22 属性、5 事件、3 控制函数、新枚举 `OH_ArkUI_ArcDirection`；`@since 26.1.0` | 高 | 范围/API | 命中（当次会话首读成功） |
| K-3 | `ace_engine/interfaces/native/native_node.h` | grep `ARC_SWIPER\|ARC_ALPHABET\|NODE_ARC_*` | 无任何命中；文件 12558 行；NodeType 止于 `ARKUI_NODE_PICKER=1018`(行153) | 高 | 范围/风险 | 命中：NDK 层空白 |
| K-4 | `component_ext/arc_swiper/`、`component_ext/arc_alphabet_indexer/` | ArkTS 既有实现 | `arkui_arcswiper.js`、`arc_swiper_napi.cpp`(780)、controller/indicator；`arkui_arcalphabetindexer.js`(276)、napi(115)；属性/事件/控制器齐备 | 高 | 复用参照 | 命中 |
| K-5 | `frameworks/core/components_ng/pattern/` | Arc NG 类 | `arc_swiper_pattern.h:25 ArcSwiperPattern:SwiperPattern`、`arc_indexer_pattern.h:27 ArcIndexerPattern:IndexerPattern` | 高 | 设计/复用 | 命中 |
| K-6 | `frameworks/core/interfaces/native/node/node_modifiers.cpp` | 全局 modifier 注册表 | `.getSwiperModifier`(行232)、`.getAlphabetIndexerModifier`(行222)；CJUI 变体(行388/397) | 高 | 设计 | 命中 |
| K-7 | `interfaces/native/node/swiper_option.cpp` | Swiper 控制函数模板 | `OH_ArkUI_Swiper_FinishAnimation`(行24)/`ShowPrevious`(行94)/`ShowNext`(行108) | 高 | 设计/实现 | 命中 |
| K-8 | `interfaces/native/node/node_model.cpp` | NodeType↔Tag 映射 | Tag→NodeType(行1415)、NodeType→Tag(行1467) | 高 | 设计/实现 | 命中 |
| K-9 | `frameworks/core/interfaces/native/node/node_api.cpp` | 事件 reset 表 | `ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS`(行923)、分发点(行1480/1486)；当前全 `nullptr`（UAF 风险） | 高 | 风险/任务 | 命中 |
| K-10 | `interfaces/native/node/style_modifier.cpp` | 属性三向分发表 | `ResetSwiperVertical`(行9928)/`ResetSwiperDuration`(行9954)、reset 表(行20987) | 高 | 设计/测试 | 命中 |
| K-11 | `build/libace.map`、`interfaces/native/libace.ndk.json`、`build_check_for_c.c` | ABI/SDK 元数据 | 三文件均存在；当前 `ArcSwiper/ArcAlphabet` 符号计数=0 | 高 | ABI/交付 | 命中 |
| K-12 | `frameworks/core/interfaces/native/implementation/arc_swiper_*` | Arkoala/ArkTS-static 层 | `arc_swiper_extender_accessor.cpp`(361)、controller accessor/peer、`arc_alphabet_indexer_extender_accessor.cpp`(桩) 存在；命名空间 `Ark_NativePointer/GeneratedModifier`，非 NDK C ABI | 高 | 边界澄清 | 命中：不可直接复用为 CAPI，仅作映射参考 |
| K-13 | `interface/sdk_c` 本地工作树 | manifest/worktree | 本 checkout 无该仓工作树 | 高 | 阻塞记录 | 未命中：接口真相源以 PR #5447（K-2）为准 |

**上下文结论：**
- 高可信结论（可直接进入 spec/design）：接口范围 = PR #5447（K-2）；ace_engine NDK 层空白（K-3）；NG 层可复用（K-5）；Swiper 是 1:1 参照（K-6~K-10）；ABI 元数据空白待补（K-11）；Arkoala 层与 NDK 层是两套独立 native（K-12）。
- 待确认结论：`ArkUI_CrownSensitivity` 枚举是否存在（spec 阶段核验 K-2 依赖类型）；控制函数开放级别（Q-3）；Owner 元数据（Q-1/Q-2）。
- 未使用来源及原因：`interface/sdk_c` 本地工作树缺失（K-13），以 PR 远端 diff 作为真相源替代，不阻塞。

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | ArkUI（ace_engine）；接口侧 interface_sdk_c | AI 起草 | 待确认 |
| 是否需要新增子系统或部件？ | 否；复用既有 `ace_ndk` 部件（`bundle.json:215-226`，头文件基座 `interfaces/native`） | AI 起草 | 待确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增/修改 Public API？ | 是；新增 NDK 节点 C API（2 类型 + 22 属性 + 5 事件 + 3 控制函数 + 1 枚举），`@since 26.1.0` | AI 起草 | 待确认 |
| 是否需要新增 System API？ | 待确认；控制函数开放级别见 Q-3 | AI 起草 | 待确认 |
| 是否会废弃已有 API？ | 否；仅追加枚举值与符号，不删除/不重排 | AI 起草 | 待确认 |
| 是否需要新增权限声明？ | 否 | AI 起草 | 待确认 |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | 向前/向后兼容？破坏性变更？ | 仅追加枚举/符号，不改 ArkTS 行为；NDK 新节点类型不破坏既有 ABI | AI 起草 | 待确认 |
| 性能 | 响应时间/内存/并发？ | 复用 NG 实现，不新增 IPC/线程切换/锁；`ON_GESTURE_SWIPE` 帧级事件需控制回调开销；阈值见 Q-4 | AI 起草 | 条件确认 |
| 安全 | 权限/隐私/加密/审计？ | 不涉及（无权限/敏感数据/网络） | AI 起草 | 已确认 N/A |
| 可靠性 | 崩溃率/容错/恢复？ | null/错误 NodeType/越界枚举需与 ArkTS 等价处理不崩溃；事件 unregister 后须清空 EventHub 槽（K-9 UAF 风险） | AI 起草 | 待确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| `interface_sdk_c` PR #5447 | 接口 | 接口真相源；需与 ace_engine 头文件同步（ace_engine 拥有 `interfaces/native/native_node.h` 源头） | 待确认同步方式 |
| `Swiper`/`Indexer` NG 实现 | 实现 | 复用 ArcSwiperPattern/ArcIndexerPattern | 已确认 |
| `ArkUI_CrownSensitivity` 枚举 | 接口 | `NODE_ARC_SWIPER_DIGITAL_CROWN_SENSITIVITY` 依赖；待核验存在性 | 待验证 |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| 事件 unregister 后 EventHub 回调残留 → UAF | 技术 | 高（崩溃） | 补齐 ARC_SWIPER 与 ALPHABET_INDEXER reset 表（node_api.cpp:923 模式），register/unregister 配对 | 待确认 |
| ArkTS 与 C API 默认值/参数槽不一致 | 技术 | 中（语义漂移） | 以 ArkTS 实现为单一真相源逐项对齐，逐属性 set/get/reset UT 覆盖 | 待确认 |
| 接口头文件双源头漂移（interface_sdk_c vs ace_engine） | 工程 | 中 | 明确 ace_engine 为头文件源头，interface_sdk_c 同步；交付前 ABI/SDK 复核 | 待确认 |
| `ON_GESTURE_SWIPE` 帧级回调影响手表帧率 | 性能 | 中 | 复用 Swiper 既有事件路径，避免每帧分配；Q-4 阈值验证 | 待确认 |

### AC 完整性

- [x] 每个用户故事有验收标准（见三、需求基线）
- [x] AC 全部使用 WHEN/THEN 格式
- [x] 覆盖正常流程、异常流程、边界条件
- [x] AC 可测试、可度量（映射到 CAPI UT）

### 澄清结论

- [x] 功能范围已明确（依据 PR #5447）
- [ ] 子系统影响已识别（待 Owner 确认）
- [x] API 变更已评估（新增 NDK C API；开放级别 Q-3）
- [x] 兼容性和非功能需求已确认（条件）
- [x] 依赖和风险已识别且有缓解方案
- [x] AC 完整可测试
- [x] 标准及以上复杂度已完成方案探索（3 方案 + 取舍理由）

**结论:** 条件通过。技术范围与实现路径清晰、可形成下游草案；但 Owner 元数据（Q-1/Q-2）、控制函数开放级别（Q-3）、性能阈值（Q-4）未闭合，所有下游交付件不得标记 Approved。

---

## 三、需求基线

> 澄清完成后固化。manifest.md 是事实源，此处为审批结论。当前为 Blocked（待 Owner）。

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0（草案） |
| 基线日期 | 2026-07-14 |
| Owner | ArkUI Owner（待确认） |
| 确认人 | 需求方/模块 Owner/SIG 代表（待确认） |
| 复杂度 | 关键（critical） |
| Profile | `arkui` / 子 profile `capi`、`component` |
| 目标发行版本 | OpenHarmony-6.1-Release（引用 `proposal.target_release`，待 Owner 终确认） |
| 版本状态 | proposed |

### 问题陈述

手表 ArcSwiper 与 ArcAlphabetIndexer 仅有 ArkTS 入口，无法满足手表高性能 Native 场景。需在 ace_engine NDK 层为二者补齐节点类型、属性分发、事件与控制函数，复用既有 NG 实现，使 Native 调用方以稳定 C ABI 获得与 ArkTS 等价的能力，且不引入第二套语义。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| 属性完整可用 | 22 个属性均通过 `set → get → reset → get(default)` | CAPI UT（capi_all_modifiers_test） |
| 事件完整可用 | 5 个事件均通过 `register → fire → unregister → fire(无回调)` | CAPI UT + 事件生命周期验证 |
| 控制函数可用 | 3 个 ArcSwiper 控制函数对 有效/null/错误 NodeType 行为符合声明 | CAPI accessor UT |
| 行为等价 | C API 与 ArkTS 在默认值、非法值、状态、事件参数上无未解释差异 | 逐属性 UT + ArkTS 对照 |
| 工程闭环 | 枚举/符号/SDK 元数据/构建/CAPI UT 一致 | SDK 编译 + libace.map/ndk.json 复核 + validate |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为手表 Native 应用开发者，我想要以 C ABI 创建并配置 ArcSwiper/ArcAlphabetIndexer，以便在 Native 高性能路径使用 | P0 |
| US-2 | 作为手表 Native 应用开发者，我想要注册/解注册组件事件并获得与 ArkTS 一致的回调参数，以便稳定处理交互 | P0 |
| US-3 | 作为手表 Native 应用开发者，我想要调用 ArcSwiper 控制函数翻页，以便程序化控制导航 | P1 |
| US-4 | 作为 ArkUI 维护者，我想要 C API 与 ArkTS 共享同一套 NG 实现，以便避免语义分叉 | P0 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN 对任一 22 个属性执行合法 set/get/reset THEN get 分别返回设置值与 ArkTS 等价默认值 | 正常 | US-1 |
| AC-2 | WHEN 输入 null/错误 NodeType/越界枚举/负值/空数组/缺省字段 THEN 与 ArkTS 等价处理且不崩溃 | 异常/边界 | US-1 |
| AC-3 | WHEN 注册并触发任一 5 个事件 THEN 回调次数、顺序与参数槽与 ArkTS 事件一致 | 正常 | US-2 |
| AC-4 | WHEN 解注册或重复解注册任一事件 THEN EventHub 槽位清空且后续不再回调（无 UAF） | 异常 | US-2 |
| AC-5 | WHEN 调用 3 个 ArcSwiper 控制函数 THEN 有效节点复用既有 Pattern，非法/null 节点返回 `ARKUI_ERROR_CODE_PARAM_INVALID` | 正常/异常 | US-3 |
| AC-6 | WHEN 完成交付验证 THEN 枚举、符号、SDK 元数据、构建与 CAPI UT 与 PR #5447 接口基线一致 | 边界 | US-4 |

### 范围边界

**包含：** 2 NDK 节点类型、22 属性、5 事件、3 控制函数、`OH_ArkUI_ArcDirection` 枚举、ABI/SDK 元数据、CAPI UT。
**不包含：** ArkTS 行为/算法变更、权限/IPC/持久化/网络、PR #5447 之外能力、安全威胁建模。

**分期策略（如适用，待 Owner 定）：**

| 阶段 | 范围 | 不做 | 进入条件 |
|------|------|------|----------|
| 阶段一 | ArcSwiper（8 属性 + 4 事件 + 3 控制函数 + 节点类型） | ArcAlphabetIndexer | 基线 Approved |
| 阶段二 | ArcAlphabetIndexer（14 属性 + 1 事件 + 节点类型） | — | 阶段一验证通过 |

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 当前职责 | 影响类型 | Owner |
|--------|------|-----------|----------|----------|-------|
| ArkUI | interface_sdk_c | `arkui/ace_engine/native/native_node.h`、`native_type.h` | NDK C 接口声明 | 新增（PR #5447） | 待确认 |
| ArkUI | ace_engine | `interfaces/native/native_node.h`、`native_type.h` | NDK 头文件源头 | 新增枚举/函数 | 待确认 |
| ArkUI | ace_engine | `interfaces/native/node/node_model.cpp` | NodeType↔Tag 映射、createNode | 新增映射 | 待确认 |
| ArkUI | ace_engine | `interfaces/native/node/style_modifier.cpp` | 属性三向分发 | 新增 22 组 set/get/reset | 待确认 |
| ArkUI | ace_engine | `interfaces/native/node/swiper_option.cpp`（或新文件） | 控制函数 | 新增 3 函数 | 待确认 |
| ArkUI | ace_engine | `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.*` | modifier 结构体 | 新建 | 待确认 |
| ArkUI | ace_engine | `frameworks/core/interfaces/native/node/node_modifiers.cpp` | 全局 modifier 注册 | 追加注册 | 待确认 |
| ArkUI | ace_engine | `frameworks/core/interfaces/native/node/node_api.cpp` | 事件 reset 表 | 新增表 + 配对 | 待确认 |
| ArkUI | ace_engine | `build/libace.map`、`interfaces/native/libace.ndk.json` | ABI/SDK 元数据 | 新增符号 | 待确认 |
| ArkUI | ace_engine | `test/unittest/capi/modifiers/` | CAPI UT | 新增测试 | 待确认 |

### API 变更项清单

> design.md 与 spec.md 并行产出的共享锚点。两者引用同一份清单。

| API 名称 | 变更类型 | 开放范围 | 概要说明 |
|----------|----------|----------|----------|
| `ARKUI_NODE_ARC_ALPHABET_INDEXER`(=23) | 新增 | NDK Public（待 Q-3） | ArcAlphabetIndexer 节点类型 |
| `ARKUI_NODE_ARC_SWIPER`(=1022) | 新增 | NDK Public（待 Q-3） | ArcSwiper 节点类型 |
| `NODE_ARC_ALPHABET_INDEXER_*`(14) | 新增 | NDK Public | 索引数组/颜色/字体/选中/弹出/blur/itemSize/autoCollapse |
| `NODE_ARC_SWIPER_*`(8) | 新增 | NDK Public | index/indicator/duration/vertical/disableSwipe/crown/effect/transition |
| `NODE_ARC_ALPHABET_INDEXER_EVENT_ON_SELECT` | 新增 | NDK Public | 选中索引变化事件 |
| `NODE_ARC_SWIPER_EVENT_ON_CHANGE/ANIMATION_START/ANIMATION_END/GESTURE_SWIPE` | 新增 | NDK Public | 4 个翻页/动画/手势事件 |
| `OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext/FinishAnimation` | 新增 | 待 Q-3（Public/System） | 3 个控制函数 |
| `OH_ArkUI_ArcDirection`(enum) | 新增 | NDK Public | 指示器方向（3/6/9 点） |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 是 | 手表热路径 + 帧级事件 | design.md / spec.md |
| 安全与权限 | N/A | 无权限/敏感数据/网络；不产 threat-model | — |
| 兼容性 | 是 | C ABI 与 ArkTS 行为兼容 | spec.md |
| API/SDK | 是 | NDK C API 26.1.0 | design.md / spec.md |
| IPC/跨进程 | N/A | 仅 UI 框架进程内调用 | — |
| 构建与部件 | 是 | ace_ndk 部件导出、libace.map、ndk.json、CAPI UT | design.md |
| 国际化/无障碍 | N/A | 不改组件可见语义/语义树；回归验证即可 | spec.md（回归项） |
| 数据迁移 | N/A | 无持久化数据 | — |

### 变更控制

| 变更类型 | 触发条件 | 处理规则 |
|----------|----------|----------|
| 范围新增 | 新增属性/事件/控制函数或仓/模块 | 重新评估复杂度和设计影响 |
| AC 变更 | 修改可观察行为或错误码 | 重新审批基线和 spec |
| API 变更 | 新增/修改 NDK 符号 | 触发设计审批 + ABI/SDK 复核 |
| 非功能指标变更 | 性能阈值变化（Q-4） | 重新确认测试计划 |
| 目标版本变更 | 交付版本调整 | 更新 proposal.target_release |

### 进入设计/Spec 条件

- [x] 所有 P0/P1 用户故事有 AC
- [x] 每条 AC 可测试、可度量
- [x] 范围内/外已确认
- [ ] `proposal.target_release` 已确认或明确 TBD（当前推断 6.1-Release，待 Owner）
- [ ] `manifest.profile` 已确认或明确 none（profile=arkui 已定；FuncID/FeatID 待 Owner）
- [x] 涉及仓、模块、SIG 已识别
- [x] 不涉及项已标记 N/A
- [x] 变更控制规则已确认
- [ ] 标准及以上复杂度的澄清问题已逐项关闭（Q-1~Q-4 待 Owner；技术项已闭合）
- [x] 上下文与知识源检索日志已填写；未查询关键来源的原因已记录（K-13）
- [x] 目标仓 Agent 指南已检查并记录关键约束（K-1）

**基线结论:** Blocked（待 Owner 确认 Q-1~Q-4 后转 Approved）。技术范围与实现路径已充分明确，可并行推进下游草案，但下游交付件在 proposal 转 Approved 前不得标记 Approved。
