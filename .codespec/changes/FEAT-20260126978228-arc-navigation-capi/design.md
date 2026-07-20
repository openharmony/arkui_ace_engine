# 架构设计

> 确认架构约束、关键设计决策、模块影响。本版为删除重跑后的版本，所有行号引用均经当次会话核验（ace_engine `OpenHarmony-6.1-Release`）。design 引用 spec AC，不发明行为。

## 设计元数据

| 字段 | 内容 |
|------|------|
| Design ID | `DESIGN-20260126978228` |
| 关联需求 | `proposal.md` |
| 关联 Epic | 无（独立特性） |
| 目标 Feature | `FEAT-20260126978228-arc-navigation-capi` |
| 复杂度 | 关键（critical） |
| 目标版本 | OpenHarmony-6.1-Release（引用 `proposal.target_release`） |
| Owner | ArkUI Owner（待确认） |
| 状态 | Draft（上游 proposal 基线 Blocked 待 Owner；下游不得 Approved） |

## 需求基线

> 需求基线详见 proposal.md。以下为设计阶段需强调的要点。

| 项 | 补充说明 |
|----|----------|
| 接口真相源 | interface_sdk_c PR #5447；ace_engine `interfaces/native/native_node.h` 为头文件源头，与 interface_sdk_c 同步 |
| 行为等价 | C API 必须复用 NG 实现，默认值/异常/事件参数与 ArkTS 一致（spec R-1~R-13） |
| 不新建状态机 | 复用 `ArcSwiperPattern`/`ArcIndexerPattern`（NG 层已存在） |

## 上下文和现状

### 涉及仓和模块

| 仓库 | 补充架构说明 |
|------|-------------|
| `arkui_ace_engine` | NDK C API 实现主仓；NDK 层当前对两组件**完全空白**；NG 层与 ArkTS 层已存在（legacy） |
| `interface_sdk_c` | 接口声明仓（PR #5447）；头文件源头实际由 ace_engine 拥有，本仓同步 |

> 仓、模块、当前职责、影响类型详见 proposal.md「影响范围」。

### 调用链层级分析

> 从最上层（C 调用方）到最底层（NG Pattern）逐层。NDK 层是本次新增重点；NG 层为复用。

| 层 | 模块 | 职责 | 修改类型 | 核验锚点 |
|----|------|------|----------|----------|
| C ABI 头 | `interfaces/native/native_node.h`、`native_type.h` | NDK 枚举/函数声明（真相源） | 新增 | `ARKUI_NODE_PICKER=1018`(行153) 之后追加 23/1022 |
| 控制函数 | `interfaces/native/node/swiper_option.cpp`（或新 `arc_swiper_option.cpp`） | `OH_ArkUI_ArcSwiper_*` 实现 | 新增 | 模板 `swiper_option.cpp:24/94/108` |
| 节点路由 | `interfaces/native/node/node_model.cpp` | NodeType↔Tag 映射、createNode 白名单 | 修改 | 映射 `node_model.cpp:1415/1467` |
| 属性分发 | `interfaces/native/node/style_modifier.cpp` | 22 属性 Set/Reset/Get 三件套 + switch 派发 + reset 表 | 新增/修改 | reset 表 `style_modifier.cpp:20987` |
| 安全包装 | `interfaces/native/node/node_model_safely.cpp` | 安全创建/校验白名单 | 修改 | — |
| Modifier 注册 | `frameworks/core/interfaces/native/node/node_modifiers.cpp` | 全局 modifier 注册表 | 修改 | `.getSwiperModifier`(行232) 模式 |
| Modifier 实现 | `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.cpp/h` | `ArkUIArcSwiperModifier` 结构体 + set/reset/get | 新建 | 参照 `node_swiper_modifier.cpp/h` |
| 事件路由 | `frameworks/core/interfaces/native/node/node_api.cpp` | 事件 register/unregister/reset 表 | 新增/修改 | reset 表 `node_api.cpp:923`、分发 `:1480/1486` |
| NG Pattern（复用） | `frameworks/core/components_ng/pattern/swiper/arc_swiper_pattern.*`、`pattern/indexer/arc_indexer_pattern.*` | 组件业务逻辑/状态机 | 不改（复用） | `arc_swiper_pattern.h:25`、`arc_indexer_pattern.h:27` |
| ABI/SDK | `build/libace.map`、`interfaces/native/libace.ndk.json`、`build_check_for_c.c` | 导出符号 + 版本元数据 + ABI 编译检查 | 修改 | 当前 ArcSwiper 符号计数=0 |
| 测试 | `test/unittest/capi/modifiers/` | CAPI UT | 新增 | `capi_all_modifiers_test` |

**检查项：**
- [x] 调用链每一层都已覆盖（C ABI → 控制函数 → 节点路由 → 属性分发 → Modifier → 事件路由 → NG Pattern）
- [x] 每层职责边界清晰，无跨层违规（NDK 层 → NG 层单向；NG 层不被 NDK 反向依赖）
- [x] 每层修改类型明确

### 适用架构规则

| Rule ID | 适用原因 | 设计结论 | 验证方式 |
|---------|----------|----------|----------|
| OH-ARCH-LAYERING | NDK → NG 单向调用 | C API 经 modifier/option 桥接 NG Pattern，不跨层 | 代码评审/依赖检查 |
| OH-ARCH-SUBSYSTEM | 仅 ArkUI 子系统内 | 不跨子系统调用 | 依赖检查 |
| OH-ARCH-API-LEVEL | 新增 NDK C API | 开放级别待 Q-3；`@since 26.1.0`；SysCap 声明同步 | API 评审/XTS |
| OH-ARCH-COMPONENT-BUILD | 新增源文件/ABI 符号 | `interfaces/native/node/BUILD.gn` 增源文件；`libace.map`/`ndk.json` 增符号 | 构建验证 |
| OH-ARCH-ERROR-LOG | null/错误 NodeType 错误码 | 统一 `ARKUI_ERROR_CODE_PARAM_INVALID`/`NO_ERROR` | CAPI UT/hilog |

## 不涉及项承接

> proposal 标记"涉及"且需展开设计的维度。

| 维度 | 设计结论 |
|------|----------|
| 性能 | 复用 NG 既有事件/翻页路径，不新增 IPC/线程切换/锁；`ON_GESTURE_SWIPE` 复用 Swiper 逐帧回调路径，避免每帧堆分配（阈值 Q-4） |
| 兼容性 | 仅追加枚举/符号，不改既有；NDK 新 NodeType 不破坏既有 ABI |
| API/SDK | 头文件单源头（ace_engine），interface_sdk_c 同步；`libace.ndk.json` `first_introduced=26.1.0` |
| 构建与部件 | 复用 `ace_ndk` 部件，不新增部件/头文件基座 |

> 安全与权限 = N/A（proposal 已判定）→ 「安全基础检查」整节省略。

## 关键设计决策

> 标准及以上：每决策 ≥2 替代方案 + 取舍理由。

| 决策 ID | 问题 | 推荐方案 | 探索过的替代方案 | 取舍理由 | 影响 |
|---------|------|----------|-----------------|------|------|
| ADR-001 | C API 如何获得组件行为 | **复用 NG Model/Pattern/Theme + modifier 桥接**（与 Swiper NDK 一致） | B：为 C API 建独立状态机（放弃：语义分叉、双份维护、性能风险）；C：仅 ArkTS/NAPI 包装（放弃：跨语言开销，不满足手表高性能） | 单一真相源：与 ArkTS 同一套默认值/异常/事件，从结构上保证等价；与既有 NDK 组件模式一致，维护成本最低 | 决定 7 点暴露路径；不新建状态机 |
| ADR-002 | 事件 unregister 安全性 | **register/unregister 严格配对 + 补齐 reset 表** | B：仅 register 不提供 reset（放弃：EventHub 回调残留 → UAF，node_api.cpp:923 既有 nullptr 缺口即此问题）；C：弱引用包装回调（放弃：额外开销，NDK 不适用） | NDK 回调为裸指针，unregister 必须清空底层 EventHub 槽；既有 ALPHABET_INDEXER reset 表全 nullptr 是已知 UAF 缺口，本次必须闭合 | 新增 ARC_SWIPER reset 表 + 补齐 ALPHABET_INDEXER；P0 风险项 |
| ADR-003 | Modifier 文件组织 | **新建 `node_arc_swiper_modifier.cpp/h`**，ArcAlphabetIndexer 复用既有 `alphabet_indexer_modifier` 并扩展 | B：合并进 `node_swiper_modifier.cpp`（放弃：职责混杂、diff 膨胀）；C：单一 arc modifier 文件（放弃：两组件语义不同） | ArcSwiper 控制函数/事件与 Swiper 同源但独立类型，独立文件清晰；ArcAlphabetIndexer 已有 modifier 注册（node_modifiers.cpp:222），仅需扩展属性与暴露节点类型 | 影响文件清单与 Task 拆分 |
| ADR-004 | 头文件源头归属 | **ace_engine `interfaces/native/native_node.h` 为源头**，interface_sdk_c 同步 | B：以 interface_sdk_c 为源头（放弃：ace_engine 才是子系统实现主仓，头文件随实现演进） | 符合"子系统拥有其接口"的 OpenHarmony 约定；避免双源头漂移 | 决定同步方向与 ABI 复核范围 |

## 设计骨架

### 骨架范围

| 骨架项 | 目标 | 不包含 | 验证方式 |
|--------|------|--------|----------|
| API/接口骨架 | 2 NodeType + 22 属性 + 5 事件 + 3 控制函数 + 枚举声明 | 完整分发实现 | SDK 编译 + ABI 检查（build_check_for_c.c） |
| 模块骨架 | `node_arc_swiper_modifier.*`、注册项、路由映射 | 复杂校验策略 | 构建通过 |
| 测试骨架 | `arc_swiper_modifier_test.cpp`、`arc_alphabet_indexer_modifier_test.cpp` fixture | 全场景 | 最小 set/get/reset 用例通过 |

### 骨架 Spec 拆分

| Task ID | 目标 | 受影响文件 | AC |
|---------|------|------------|-----|
| TASK-001 | ArcSwiper NDK（节点类型 + 8 属性 + 4 事件 + 3 控制函数 + modifier） | 见调用链表 ArcSwiper 行 | WHEN createNode(ARC_SWIPER) + 属性 set/get/reset THEN 与 ArkTS 等价（AC-1.1/3.1） |

## 后续 Task 拆分

| Task ID | 目标 | 受影响文件 | 依赖 |
|---------|------|------------|------|
| TASK-001 | ArcSwiper CAPI（节点 + 8 属性 + 4 事件 + 3 控制函数） | native_node.h、swiper_option.cpp/arc_swiper_option.cpp、node_model.cpp、style_modifier.cpp、node_arc_swiper_modifier.*、node_modifiers.cpp、node_api.cpp、BUILD.gn、libace.map、ndk.json、arc_swiper_modifier_test.cpp | design + spec |
| TASK-002 | ArcAlphabetIndexer CAPI（节点 + 14 属性 + 1 事件） | native_node.h、node_model.cpp、style_modifier.cpp、alphabet_indexer_modifier.*、node_modifiers.cpp、node_api.cpp、BUILD.gn、libace.map、ndk.json、arc_alphabet_indexer_modifier_test.cpp | TASK-001 模式确立 |
| TASK-003 | 事件生命周期 + ABI/SDK + 验证闭环 | node_api.cpp（reset 表 + 配对）、libace.map、ndk.json、build_check_for_c.c、SDK 编译、validate | TASK-001/002 |

## API 签名、Kit 与权限

### 新增 API

> 权威签名见 PR #5447；Kit = ArkUI NDK；d.ts 无（C 头文件）；无权限；SysCap = ArkUI。

| API 签名 | 类型 | Kit | 头文件位置 | 权限 | SysCap |
|----------|------|-----|-----------|------|--------|
| `ARKUI_NODE_ARC_ALPHABET_INDEXER = 23`（enum） | NDK Public（待 Q-3） | ArkUI NDK | `interfaces/native/native_node.h` | - | ArkUI |
| `ARKUI_NODE_ARC_SWIPER = 1022`（enum） | NDK Public（待 Q-3） | ArkUI NDK | `interfaces/native/native_node.h` | - | ArkUI |
| `NODE_ARC_ALPHABET_INDEXER_*`(14)、`NODE_ARC_SWIPER_*`(8)（enum） | NDK Public | ArkUI NDK | `interfaces/native/native_node.h` | - | ArkUI |
| `NODE_ARC_*_EVENT_*`(5)（enum） | NDK Public | ArkUI NDK | `interfaces/native/native_node.h` | - | ArkUI |
| `int32_t OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext/FinishAnimation(ArkUI_NodeHandle)` | 待 Q-3 | ArkUI NDK | `interfaces/native/native_node.h` | - | ArkUI |
| `OH_ArkUI_ArcDirection`(enum，3/6/9 点=0/1/2) | NDK Public | ArkUI NDK | `interfaces/native/native_type.h` | - | ArkUI |

### 变更/废弃 API

无。

## 构建系统影响

### BUILD.gn 变更

```
文件路径: interfaces/native/node/BUILD.gn
变更说明: 新增 sources node_arc_swiper_modifier.cpp；如新增 arc_swiper_option.cpp 一并加入
文件路径: test/unittest/capi/modifiers/BUILD.gn
变更说明: sources 追加 arc_swiper_modifier_test.cpp、arc_alphabet_indexer_modifier_test.cpp
```

### bundle.json 变更

无新增 component/头文件基座。NDK 声明已在 `bundle.json:215-226`（`ace_ndk` 部件，headers 含 `native_node.h`/`native_type.h`）；新枚举/符号追加在既有头文件内，无需改 bundle.json。

---

## 可选设计扩展

### 架构图

```
C/NDK 调用方
   │  ArkUI_NodeHandle / OH_ArkUI_ArcSwiper_* / setAttribute(NODE_ARC_*)
   ▼
[NDK C ABI]  interfaces/native/native_node.h (枚举/声明)  ──同步── interface_sdk_c PR #5447
   │
   ├─ 控制函数  swiper_option.cpp / arc_swiper_option.cpp
   ├─ 节点路由  node_model.cpp (NodeType↔Tag, createNode)
   ├─ 属性分发  style_modifier.cpp (Set/Reset/Get + switch + reset 表)
   └─ 事件路由  node_api.cpp (register/unregister/reset 表)
   │
   ▼  getNodeModifiers()->getArcSwiperModifier()->setXxx(uiNodeHandle)
[Modifier]  node_arc_swiper_modifier.* / alphabet_indexer_modifier.*
   │
   ▼  SwiperModelStatic / IndexerModelNG
[NG Pattern 复用]  ArcSwiperPattern : SwiperPattern  /  ArcIndexerPattern : IndexerPattern
```

### 数据流/控制流（属性 set 为例）

| 步骤 | 调用方 | 被调用方 | 数据/接口 | 说明 |
|------|--------|----------|-----------|------|
| 1 | C 调用方 | NDK | `setAttribute(node, NODE_ARC_SWIPER_DURATION, item)` | 进 style_modifier switch |
| 2 | style_modifier | modifier | `getArcSwiperModifier()->setDuration(handle, item)` | 路由到 ArcSwiper modifier |
| 3 | modifier | NG Model | `SwiperModelStatic::SetDuration(frameNode, ms)` | 复用 NG |
| 4 | NG Pattern | 渲染 | ArcSwiperPattern 更新 | 与 ArkTS 同路径 |

### 资源所有权矩阵（事件回调 — UAF 闭合核心）

| 资源 | 创建方 | 持有方 | 销毁触发 | 实际释放 | 异常回收 |
|------|--------|--------|----------|----------|----------|
| NDK 事件回调（裸指针） | C 调用方 register | node_api 注册表 + NG EventHub 槽 | C 调用方 unregister / 节点销毁 | reset 表清空 EventHub 槽（node_api.cpp:923 模式） | 重复 unregister 幂等清空，不残留 |

> ADR-002 核心：既有 `ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS`(node_api.cpp:923) 当前全 `nullptr`，导致 unregister 后 EventHub 回调残留 → UAF。本次新增 `ARC_SWIPER_NODE_RESET_ASYNC_EVENT_HANDLERS` 并补齐 ALPHABET_INDEXER 表项，闭合该缺口。

### 接口参数规约（控制函数）

| 接口 | 参数 | 类型 | 合法范围 | 非法处理 | 边界说明 |
|------|------|------|----------|----------|----------|
| `OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext` | node | `ArkUI_NodeHandle` | 非 null 且 type=ARC_SWIPER | null/错误 type → `PARAM_INVALID` | 首/末页与 ArkTS 一致 |
| `OH_ArkUI_ArcSwiper_FinishAnimation` | node | `ArkUI_NodeHandle` | 非 null 且 type=ARC_SWIPER | null/错误 type → `PARAM_INVALID` | 无动画时 no-op |

### 测试性设计

| 测试层级 | 测试目标 | Mock 策略 | 验证方式 |
|----------|----------|-----------|----------|
| CAPI UT（modifier） | 22 属性 set/get/reset + 默认值 + 边界/异常 | `modifier_test_base.h` fixture | `capi_all_modifiers_test`（`test/unittest/capi/modifiers/`） |
| CAPI UT（accessor） | 3 控制函数有效/null/错误 NodeType | `accessor_test_base.h` | 同上目标 |
| CAPI UT（事件） | 5 事件 register/fire/unregister + UAF 检测 | 事件 fixture | 同上目标 |
| ABI/SDK | 符号导出 + 版本元数据 | — | SDK 编译 + `build_check_for_c.c` + libace.map/ndk.json 复核 |
| UI 可见行为 | 渲染一致性/事件触发 | Host Preview 无法直达 C API | 转入组件 unittest + ArkTS 工程回归（capi 子 profile 替代验证，记录 N/A 理由） |

## 风险和开放问题

| 项 | 类型 | 影响 | 处理方式 | Owner |
|----|------|------|----------|-------|
| 事件 reset 表 nullptr → UAF（node_api.cpp:923） | 架构/可靠 | 高 | ADR-002：新增 ARC_SWIPER 表 + 补齐 ALPHABET_INDEXER；UT 含 UAF 检测 | ArkUI Owner |
| `ArkUI_CrownSensitivity` 枚举存在性 | API | 中 | design/plan 核验 native_type.h；缺失则需先补枚举 | ArkUI Owner |
| 头文件双源头漂移 | 工程 | 中 | ADR-004：ace_engine 为源头，interface_sdk_c 同步；交付前 ABI 复核 | ArkUI Owner |
| 控制函数开放级别（Public/System） | API | 中 | Q-3 待 Owner；影响 ndk.json 可见性 | ArkUI Owner |
| `ON_GESTURE_SWIPE` 手表帧率影响 | 性能 | 中 | 复用 Swiper 逐帧路径；Q-4 阈值 + 设备矩阵 | 性能 Owner |

## 设计审批

- [x] 需求基线已确认（Blocked 待 Owner，技术范围闭合），设计覆盖 P0/P1 AC（AC-1.1~4.1）
- [x] 不涉及项已承接，N/A（安全/IPC/数据迁移）与展开项（性能/兼容/API/构建）都有结论
- [x] 涉及仓和模块职责清楚
- [x] 调用链层级分析完整，每层覆盖到位
- [x] 适用架构规则已识别并形成设计结论
- [x] 分层和子系统边界合规（NDK→NG 单向，不跨子系统）
- [x] API 变更有签名、权限、错误码和兼容性说明
- [x] BUILD.gn/bundle.json 影响明确（仅 BUILD.gn 增源文件，bundle.json 不变）
- [x] 设计输出和后续 Task 拆分明确（TASK-001/002/003）
- [x] 关键设计决策有理由和影响说明（ADR-001~004）
- [x] 风险和开放问题有 Owner

**结论:** 条件通过。设计路径与决策清晰、与 spec 交叉一致；上游 proposal 基线 Blocked 待 Owner，design 不得标记 Approved。开放问题（Q-3/Q-4、CrownSensitivity 枚举、UAF 闭合）须在 Plan/实现阶段逐项闭合。
