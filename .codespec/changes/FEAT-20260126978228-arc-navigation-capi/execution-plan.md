# 执行计划

> 将 design 拆成可独立执行、可验证、可审查的 Task。本版为删除重跑后的版本。上游 proposal 基线 Blocked 待 Owner，plan 状态为 Draft，不得据此修改生产代码。

## Plan 元数据

| 字段 | 内容 |
|------|------|
| Plan ID | `PLAN-20260126978228` |
| 关联 Feature | `FEAT-20260126978228-arc-navigation-capi` |
| 关联文档 | proposal.md / spec.md / design.md |
| 复杂度 | 关键（critical） |
| 状态 | Draft（上游 Blocked 待 Owner） |
| Owner | ArkUI Owner（待确认） |

## 输入状态

| 输入 | 路径 | 要求状态 | 当前状态 |
|------|------|----------|----------|
| Requirement | `proposal.md` | Approved | Blocked（待 Owner Q-1~Q-4） |
| Design | `design.md` | Approved | Draft（条件通过） |
| Spec | `spec.md` | Approved | Draft |

> 依据硬规则"计划之前不得实现"：在上游转 Approved 前，本 plan 仅作设计与实现映射的草案，不得启动生产代码修改。

## 受影响文件全量清单

> 对照 design.md 调用链层级分析，逐层列出具体文件。所有路径相对 `foundation/arkui/ace_engine/`。行号为当次会话核验锚点。

| 仓 | 层 | 文件路径 | 修改类型 | 说明 | 归属 Task |
|----|----|----------|----------|------|-----------|
| ace_engine | C ABI 头 | `interfaces/native/native_node.h` | 修改 | 追加 2 NodeType(23/1022)、22 属性、5 事件枚举； NodeType 现止于 `ARKUI_NODE_PICKER=1018`(行153) | 001/002 |
| ace_engine | C ABI 头 | `interfaces/native/native_type.h` | 修改 | 新增 `OH_ArkUI_ArcDirection` 枚举；核验 `ArkUI_CrownSensitivity` 存在性 | 001 |
| ace_engine | 控制函数 | `interfaces/native/node/swiper_option.cpp`（或新建 `arc_swiper_option.cpp`） | 修改/新增 | 3 个 `OH_ArkUI_ArcSwiper_*`；模板 `swiper_option.cpp:24/94/108` | 001 |
| ace_engine | 节点路由 | `interfaces/native/node/node_model.cpp` | 修改 | NodeType↔Tag 映射(`:1415/1467`)、createNode 白名单 | 001/002 |
| ace_engine | 安全包装 | `interfaces/native/node/node_model_safely.cpp` | 修改 | 安全创建白名单 | 001/002 |
| ace_engine | 属性分发 | `interfaces/native/node/style_modifier.cpp` | 修改 | 22 属性 Set/Reset/Get 三件套 + switch 派发 + reset 表(`:20987`) | 001/002 |
| ace_engine | Modifier 注册 | `frameworks/core/interfaces/native/node/node_modifiers.cpp` | 修改 | 追加 `.getArcSwiperModifier`(`:232` 模式)；ArcAlphabetIndexer 已注册(`:222`) | 001 |
| ace_engine | Modifier 实现 | `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.cpp` | 新增 | `ArkUIArcSwiperModifier` 结构体 + set/reset/get；参照 `node_swiper_modifier.cpp` | 001 |
| ace_engine | Modifier 实现 | `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.h` | 新增 | modifier 声明 + `GetArcSwiperModifier()`；参照 `node_swiper_modifier.h` | 001 |
| ace_engine | Modifier 实现 | `frameworks/core/interfaces/native/node/alphabet_indexer_modifier.cpp/h` | 修改 | 扩展 14 属性 set/reset/get（已注册，仅需补属性 + 暴露节点类型） | 002 |
| ace_engine | 事件路由 | `frameworks/core/interfaces/native/node/node_api.cpp` | 修改 | 新增 `ARC_SWIPER_NODE_RESET_ASYNC_EVENT_HANDLERS`；补齐 `ALPHABET_INDEXER` 表(`:923`)；分发(`:1480/1486`) | 003 |
| ace_engine | 构建 | `interfaces/native/node/BUILD.gn` | 修改 | 新增 `node_arc_swiper_modifier.cpp`（及 `arc_swiper_option.cpp` 若新建） | 001 |
| ace_engine | ABI | `build/libace.map` | 修改 | 追加 `OH_ArkUI_ArcSwiper_*` 导出符号（当前计数=0） | 003 |
| ace_engine | SDK 元数据 | `interfaces/native/libace.ndk.json` | 修改 | 新增符号 `first_introduced=26.1.0`（当前计数=0） | 003 |
| ace_engine | ABI 检查 | `interfaces/native/build_check_for_c.c` | 修改 | ABI 编译检查引用新符号 | 003 |
| ace_engine | 测试 | `test/unittest/capi/modifiers/arc_swiper_modifier_test.cpp` | 新增 | ArcSwiper 8 属性 + 4 事件 + 3 控制函数 CAPI UT | 001 |
| ace_engine | 测试 | `test/unittest/capi/modifiers/arc_alphabet_indexer_modifier_test.cpp` | 新增 | ArcAlphabetIndexer 14 属性 + 1 事件 CAPI UT | 002 |
| ace_engine | 测试 | `test/unittest/capi/modifiers/BUILD.gn` | 修改 | sources 追加两个测试文件 | 001/002 |

> NG 层（`arc_swiper_pattern.*`、`arc_indexer_pattern.*`）**不改**（复用），故不在清单内。Arkoala 层（`frameworks/core/interfaces/native/implementation/arc_*`）与本 NDK 层是两套独立 native，本计划不涉及。

**生成文件声明（生成源 + 生成命令）：**
- 本计划涉及的新增/修改文件**均非生成器产出**。`node_arc_swiper_modifier.*`、style_modifier 三件套、control 函数、事件 reset 表均为**手写**，按既有 `node_swiper_modifier.cpp/h`、`swiper_option.cpp`、`node_api.cpp` 的 1:1 模式编写（design ADR-003）。
- Arkoala 生成层（`frameworks/core/interfaces/native/implementation/`，由 IDL/Arkoala codegen 产出）**不在本计划范围**；如实施中发现某变更点实际属于生成层，停止并回传（不得手改生成文件作为最终方案）。

**检查项：**
- [x] design.md 调用链每一层都有对应文件列出
- [x] 每个文件修改类型和职责说明明确
- [x] 无映射行的层（NG 层为复用不改，已注明）

## AC 到 Task 追溯

| AC | 来源 | Task | 验证方式 | 覆盖？ |
|----|------|------|----------|--------|
| AC-1.1 | spec.md | TASK-001/002 | CAPI UT（逐属性 set/get/reset） | 是 |
| AC-1.2 | spec.md | TASK-001/002 | CAPI UT（null/错误 NodeType/越界枚举） | 是 |
| AC-1.3 | spec.md | TASK-001/002 | CAPI UT（边界值） | 是 |
| AC-2.1 | spec.md | TASK-001/002 | CAPI UT（事件 register/fire/参数槽） | 是 |
| AC-2.2 | spec.md | TASK-003 | CAPI UT（unregister/重复 unregister + UAF 检测） | 是 |
| AC-3.1 | spec.md | TASK-001 | CAPI accessor UT（控制函数有效路径） | 是 |
| AC-3.2 | spec.md | TASK-001 | CAPI accessor UT（null/错误 NodeType） | 是 |
| AC-4.1 | spec.md | TASK-003 | SDK 编译 + libace.map/ndk.json 复核 + validate | 是 |

## 首批实现边界

**首批必须实现：** ArcSwiper 节点类型 + 属性分发骨架 + 控制函数（TASK-001 主体）；事件 reset 表 UAF 闭合（TASK-003 的 ADR-002，P0 可靠性底线）。
**可后置：** ArcAlphabetIndexer 全量 14 属性（TASK-002，可按组件分期）。
**不建议延后：** 事件 register/unregister 配对与 reset 表（延后则主交互链存在 UAF，不闭合）。

## 阶段计划（如适用）

| 阶段 | 目标 | 关键 Task | 结束门槛 | 最小验证 |
|------|------|-----------|----------|----------|
| Phase-1 | ArcSwiper CAPI 骨架 + 控制函数 | TASK-001 | createNode(ARC_SWIPER) 可用、8 属性三向、3 控制函数、4 事件 register/unregister | `capi_all_modifiers_test` ArcSwiper 用例 PASS |
| Phase-2 | 事件生命周期 + ABI/SDK 闭环 | TASK-003 | UAF 闭合、符号导出、SDK 编译 | SDK 编译 PASS + UAF UT PASS |
| Phase-3 | ArcAlphabetIndexer CAPI | TASK-002 | 14 属性三向、1 事件 | `capi_all_modifiers_test` Indexer 用例 PASS |

## Task 粒度原则

- 按"组件 × 能力闭环"拆分：ArcSwiper（含控制函数，与 Swiper 同源）/ ArcAlphabetIndexer（复用既有 modifier）/ 事件生命周期+ABI（横切，UAF 闭合为独立可靠性闭环）。
- 单 Task 上下文（spec+design+代码+测试）估算：TASK-001 ≈ 8 属性+4 事件+3 控制函数，未超 3000 行阈值，不拆。

## 禁止项

- [x] 没有 TBD / TODO / 占位符（Owner 待确认项以 Q-x 标注，非占位）
- [x] 没有"根据需要实现"等模糊指令
- [x] 没有跨 Task 隐式依赖（前置依赖显式声明）
- [x] 没有要求 Agent 自行寻找未列出的上下文文件
- [x] 没有无验证方式的 AC
- [x] 没有"参考 Task-N 实现"等引用（每 Task 卡自包含）

## Task 列表

| Task ID | 目标 | 文件范围 | AC 映射 | 前置依赖 | 完成判据 | 验证命令 |
|---------|------|----------|---------|----------|----------|----------|
| TASK-001 | ArcSwiper CAPI（节点+8属性+4事件+3控制函数） | 见受影响清单 ArcSwiper 行 | AC-1.1/1.2/1.3/2.1/3.1/3.2 | design+spec | createNode/属性三向/控制函数/事件 register 均 UT PASS | `capi_all_modifiers_test` |
| TASK-002 | ArcAlphabetIndexer CAPI（节点+14属性+1事件） | 见受影响清单 Indexer 行 | AC-1.1/1.2/1.3/2.1 | TASK-001 模式确立 | 节点+14属性三向+1事件 UT PASS | `capi_all_modifiers_test` |
| TASK-003 | 事件生命周期(UAF 闭合)+ABI/SDK+验证闭环 | node_api.cpp、libace.map、ndk.json、build_check_for_c.c | AC-2.2/4.1 | TASK-001/002 | UAF UT PASS + SDK 编译 PASS + 符号导出 | SDK 编译 + UAF UT |

## Task 详情

> 详细可执行 Task 卡见 `tasks/TASK-001-arc-swiper-capi.md`、`tasks/TASK-002-arc-alphabet-indexer-capi.md`、`tasks/TASK-003-event-lifecycle-and-validation.md`。以下为摘要。

### TASK-001: ArcSwiper CAPI

| 字段 | 内容 |
|------|------|
| 任务目标 | 为 ArcSwiper 补齐 NDK 层：节点类型 + 8 属性三向分发 + 4 事件 register/unregister + 3 控制函数，复用 ArcSwiperPattern |
| AC 映射 | AC-1.1/1.2/1.3/2.1/3.1/3.2 |
| 前置依赖 | design + spec（Approved 后启动） |
| 非目标 | 不改 ArkTS/NG 行为；不实现 ArcAlphabetIndexer（TASK-002） |
| 完成判据 | `capi_all_modifiers_test` 中 ArcSwiper 用例全 PASS |
| 停止条件 | 发现 `ArkUI_CrownSensitivity` 枚举缺失 / 某变更点属于 Arkoala 生成层 |

### TASK-002: ArcAlphabetIndexer CAPI

| 字段 | 内容 |
|------|------|
| 任务目标 | 为 ArcAlphabetIndexer 补齐 NDK 层：节点类型 + 14 属性三向 + 1 事件，复用 ArcIndexerPattern 与既有 alphabet_indexer_modifier |
| AC 映射 | AC-1.1/1.2/1.3/2.1 |
| 前置依赖 | TASK-001（模式确立） |
| 非目标 | 不改 ArkTS/NG 行为 |
| 完成判据 | `capi_all_modifiers_test` 中 Indexer 用例全 PASS |
| 停止条件 | 既有 alphabet_indexer_modifier 结构不支持扩展（回传修订 ADR-003） |

### TASK-003: 事件生命周期 + ABI/SDK + 验证闭环

| 字段 | 内容 |
|------|------|
| 任务目标 | 闭合事件 register/unregister UAF（ADR-002，新增 ARC_SWIPER reset 表 + 补齐 ALPHABET_INDEXER 表）；同步 ABI/SDK 元数据；验证闭环 |
| AC 映射 | AC-2.2/4.1 |
| 前置依赖 | TASK-001/002 |
| 非目标 | 不新增权限/IPC |
| 完成判据 | UAF UT PASS + `ohos-sdk` 编译 PASS + libace.map/ndk.json 含新符号 + validate 无 broken edge |
| 停止条件 | 控制函数开放级别（Q-3）未定导致 ndk.json 可见性无法确定 |

## Plan 自审清单

- [x] 每个 P0/P1 AC 至少映射到一个 Task
- [x] 每个 Task 文件范围明确
- [x] 每个 Task 明确前置依赖、非目标、完成判据和停止条件
- [x] 每个 Task 有验证命令
- [x] Task 粒度形成能力闭环
- [x] 没有 TBD/TODO/占位符
- [x] 没有要求 Agent 自行寻找未列出的上下文
- [x] 交接信息自包含（Task 卡 Handoff Summary 完整）
- [x] 每个 Task 验证在完成时立即执行并记录证据
- [x] 未超 3000 行阈值的 Task 已说明不拆分理由
