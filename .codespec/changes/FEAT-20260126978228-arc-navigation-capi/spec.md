# 特性规格

> 固化用户可见行为和验收标准。本版为删除重跑后的版本。接口参数格式的权威定义见 interface_sdk_c PR #5447（`native_node.h`/`native_type.h`），本 spec 聚焦"行为/默认值/异常/边界/事件参数/兼容性"，不重复逐字段抄录头文件。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | ArcSwiper 与 ArcAlphabetIndexer C API（NDK）开放 |
| 特性编号 | `FEAT-20260126978228-arc-navigation-capi` |
| 所属 Epic | 无（独立特性；FuncID/FeatID 待 Owner 分配） |
| 优先级 | P0 |
| 目标版本 | OpenHarmony-6.1-Release（引用 `proposal.target_release`，待 Owner 终确认） |
| SIG 归属 | ArkUI SIG |
| 状态 | Draft（proposal 基线 Blocked 待 Owner，下游不得 Approved） |
| 复杂度 | 关键（critical） |

## 本次变更范围（Delta）

> lineage = new-on-legacy：组件 ArkTS/NG 实现已存在（legacy），本次为其新增 NDK C API（new）。

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | 2 NDK 节点类型 `ARKUI_NODE_ARC_ALPHABET_INDEXER`(=23)、`ARKUI_NODE_ARC_SWIPER`(=1022) | 可通过 `createNode` 创建，行为与 ArkTS 组件等价 |
| ADDED | 22 NDK 属性（ArcAlphabetIndexer 14 + ArcSwiper 8） | 每个支持 set/get/reset，默认值与 ArkTS 一致 |
| ADDED | 5 NDK 事件（ArcAlphabetIndexer 1 + ArcSwiper 4） | 每个支持 register/unregister，回调参数槽与 ArkTS 一致 |
| ADDED | 3 控制函数 `OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext/FinishAnimation` | 程序化翻页与动画终止 |
| ADDED | 枚举 `OH_ArkUI_ArcDirection`（3/6/9 点方向） | ArcSwiper 指示器方向参数 |
| MODIFIED | 无已有行为变更 | 仅追加，不修改/不删除/不重排既有枚举与符号 |
| REMOVED | 无 | — |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Requirement | `proposal.md` | Blocked（待 Owner Q-1~Q-4）；技术范围已闭合，允许并行起草下游 |

> 需求基线、不涉及项、受影响子系统与仓库详见 proposal.md。design.md 与本文档并行产出，互不依赖。

## 用户故事

### US-1: 以 C ABI 创建并配置组件

**作为** 手表 Native 应用开发者，**我想要** 以 `ArkUI_NodeHandle` 创建 ArcSwiper/ArcAlphabetIndexer 并通过属性 C API 配置，**以便** 在 Native 高性能路径使用两个导航组件。

### US-2: 注册并接收组件事件

**作为** 手表 Native 应用开发者，**我想要** 注册/解注册组件事件并得到与 ArkTS 一致的回调参数，**以便** 稳定处理选中、翻页、动画与手势。

### US-3: 程序化控制 ArcSwiper 翻页

**作为** 手表 Native 应用开发者，**我想要** 调用控制函数翻页与终止动画，**以便** 程序化驱动导航。

### US-4: C API 与 ArkTS 行为等价

**作为** ArkUI 维护者，**我想要** C API 与 ArkTS 共享同一套默认值/异常处理/事件参数，**以便** 避免语义分叉与双份维护。

## 规则定义

> 横向规则覆盖所有属性/事件的共性行为；逐属性默认值见"接口规格"。类型：行为/边界/异常/恢复。

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | 对任一 22 属性以合法参数调用 set | 属性生效，随后 get 返回所设值（与 ArkTS 等价语义） | 参数格式见 PR #5447 各属性 `.value[]/.object/.string` 约定 | AC-1.1 |
| R-2 | 行为 | 对任一 22 属性调用 reset | 属性回退到 ArkTS 等价默认值，随后 get 返回该默认值 | 默认值见接口规格表 | AC-1.1 |
| R-3 | 行为 | 对任一 22 属性调用 get（未 set 过） | 返回 ArkTS 等价默认值 | — | AC-1.1 |
| R-4 | 边界 | 数值型属性输入边界值（=0、负数、最大值） | 与 ArkTS 等价处理：合法者生效，非法者按 ArkTS 口径忽略或钳制，不崩溃 | 见逐属性约束 | AC-1.3 |
| R-5 | 异常 | set/get/reset 传入 null 节点指针 | 返回 `ARKUI_ERROR_CODE_PARAM_INVALID`，不崩溃 | — | AC-1.2 |
| R-6 | 异常 | 对错误 NodeType 的节点调用本组件属性/事件/控制函数 | 返回 `ARKUI_ERROR_CODE_PARAM_INVALID` 或按 ArkTS 口径忽略，不崩溃 | — | AC-1.2 |
| R-7 | 异常 | 枚举型属性传入越界值（如 ArcDirection 非 0/1/2、BlurStyle 非法） | 与 ArkTS 等价处理（忽略并保持默认或报错），不崩溃 | — | AC-1.2 |
| R-8 | 行为 | 对任一 5 事件注册回调后触发对应交互 | 回调被调用，次数、顺序与参数槽与 ArkTS 事件一致 | 参数槽见接口规格事件表 | AC-2.1 |
| R-9 | 恢复 | 对任一 5 事件 unregister（含重复 unregister） | 底层 EventHub 回调槽清空，后续触发不再回调；无 use-after-free | 必须闭合 node_api.cpp 既有 ALPHABET_INDEXER reset 表 nullptr 缺口 | AC-2.2 |
| R-10 | 行为 | 对 ArcSwiper 有效节点调用 ShowPrevious/ShowNext | 复用既有 Pattern 翻到上一/下一页，返回 `ARKUI_ERROR_CODE_NO_ERROR` | 边界页（首/末页）行为与 ArkTS 一致 | AC-3.1 |
| R-11 | 行为 | 对 ArcSwiper 有效节点调用 FinishAnimation | 终止当前切换动画，返回 `ARKUI_ERROR_CODE_NO_ERROR` | 无动画时为 no-op，与 ArkTS 一致 | AC-3.1 |
| R-12 | 异常 | 控制函数传入 null 或错误 NodeType 节点 | 返回 `ARKUI_ERROR_CODE_PARAM_INVALID`，不崩溃 | — | AC-3.2 |
| R-13 | 行为 | 创建 `ARKUI_NODE_ARC_SWIPER`/`ARKUI_NODE_ARC_ALPHABET_INDEXER` 节点 | 返回有效 `ArkUI_NodeHandle`，挂载后渲染与对应 ArkTS 组件一致 | — | AC-1.1 |

## 验收标准（AC）

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1.1 | WHEN 对任一 22 属性执行合法 set/get/reset THEN get 分别返回所设值与 ArkTS 等价默认值 | 正常 | US-1/US-4 |
| AC-1.2 | WHEN 输入 null/错误 NodeType/越界枚举/负值/空数组/缺省字段 THEN 与 ArkTS 等价处理且返回正确错误码、不崩溃 | 异常 | US-1 |
| AC-1.3 | WHEN 数值型属性输入边界值(=0/负/最大) THEN 按 ArkTS 口径生效/钳制/忽略，不崩溃 | 边界 | US-1 |
| AC-2.1 | WHEN 注册并触发任一 5 事件 THEN 回调次数、顺序与参数槽与 ArkTS 事件一致 | 正常 | US-2 |
| AC-2.2 | WHEN 解注册或重复解注册任一 5 事件 THEN EventHub 槽清空、后续不再回调、无 UAF | 异常/恢复 | US-2 |
| AC-3.1 | WHEN 对有效 ArcSwiper 节点调用 3 个控制函数 THEN 复用既有 Pattern 翻页/终止动画，返回 NO_ERROR | 正常 | US-3 |
| AC-3.2 | WHEN 控制函数传入 null/错误 NodeType THEN 返回 PARAM_INVALID，不崩溃 | 异常 | US-3 |
| AC-4.1 | WHEN 交付验证 THEN 枚举值/符号/SDK 元数据/构建/CAPI UT 与 PR #5447 接口基线一致 | 边界 | US-4 |

## 验收追溯

| AC | 关联规则 | 关联 Task | 验证方式 | 证据 |
|----|----------|-----------|----------|------|
| AC-1.1 | R-1/R-2/R-3/R-13 | TASK-001/002 | CAPI UT（capi_all_modifiers_test，逐属性 set/get/reset） | `evidence/checks/` |
| AC-1.2 | R-5/R-6/R-7 | TASK-001/002 | CAPI UT（null/错误 NodeType/越界枚举用例） | `evidence/checks/` |
| AC-1.3 | R-4 | TASK-001/002 | CAPI UT（边界值用例） | `evidence/checks/` |
| AC-2.1 | R-8 | TASK-003 | CAPI UT（事件注册/触发/参数槽断言） | `evidence/checks/` |
| AC-2.2 | R-9 | TASK-003 | CAPI UT（unregister/重复 unregister + UAF 检测） | `evidence/checks/` |
| AC-3.1 | R-10/R-11 | TASK-001 | CAPI accessor UT（控制函数有效路径） | `evidence/checks/` |
| AC-3.2 | R-12 | TASK-001 | CAPI accessor UT（null/错误 NodeType） | `evidence/checks/` |
| AC-4.1 | — | TASK-003 | SDK 编译 + libace.map/ndk.json 复核 + validate | `evidence/checks/` |

> 每条 AC 至少映射 1 条规则与 1 个 CAPI unittest；UI 可见行为（R-13 渲染一致性、R-8 事件触发）如 Host Preview 无法直达 C API，转入组件 unittest/ArkTS 工程回归（capi 子 profile 替代验证）。

## API 变更分析

### 新增 API

| API 名称 | 开放范围 | 入参概要 | 返回值 | 错误码范围 | 功能描述 | 关联 AC |
|----------|----------|----------|--------|------------|----------|---------|
| `ARKUI_NODE_ARC_ALPHABET_INDEXER`(=23) | NDK Public（待 Q-3） | — | — | — | 索引器节点类型 | AC-1.1 |
| `ARKUI_NODE_ARC_SWIPER`(=1022) | NDK Public（待 Q-3） | — | — | — | 弧形轮播节点类型 | AC-1.1 |
| `NODE_ARC_ALPHABET_INDEXER_*`(14 枚举) | NDK Public | `ArkUI_AttributeItem` | get 返回 `ArkUI_AttributeItem` | — | 索引数组/颜色/字体/选中/弹出/blur/itemSize/autoCollapse | AC-1.1 |
| `NODE_ARC_SWIPER_*`(8 枚举) | NDK Public | `ArkUI_AttributeItem` | get 返回 `ArkUI_AttributeItem` | — | index/indicator/duration/vertical/disableSwipe/crown/effect/transition | AC-1.1 |
| `NODE_ARC_ALPHABET_INDEXER_EVENT_ON_SELECT` | NDK Public | 注册 `ArkUI_NodeEventHandle` 回调 | — | — | 选中索引变化事件 | AC-2.1 |
| `NODE_ARC_SWIPER_EVENT_ON_CHANGE/ANIMATION_START/ANIMATION_END/GESTURE_SWIPE` | NDK Public | 注册回调 | — | — | 翻页/动画起止/逐帧手势事件 | AC-2.1 |
| `OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext/FinishAnimation` | 待 Q-3 | `ArkUI_NodeHandle node` | `int32_t` | NO_ERROR / PARAM_INVALID | 翻页与终止动画 | AC-3.1/3.2 |
| `OH_ArkUI_ArcDirection`(enum) | NDK Public | — | — | — | 指示器方向（3/6/9 点 = 0/1/2） | AC-1.1 |

### 变更/废弃 API

无。仅追加，不变更/不废弃既有 API。

> 参数格式的权威定义见 PR #5447；ABI/导出符号等实现细节见 design.md。

## 接口规格

> 行为语义层。参数格式的逐字段权威定义见 PR #5447；本节定义默认值、异常口径与行为场景。

### 节点创建

| # | 触发条件 | 预期行为 | 关联 AC |
|---|----------|----------|---------|
| 1 | `createNode(ARKUI_NODE_ARC_SWIPER)` | 返回有效句柄，挂载后渲染弧形轮播 | AC-1.1 |
| 2 | `createNode(ARKUI_NODE_ARC_ALPHABET_INDEXER)` | 返回有效句柄，挂载后渲染弧形索引器 | AC-1.1 |

### ArcAlphabetIndexer 属性默认值与约束（14）

| 属性 | 类型/槽 | 默认值（与 ArkTS 等价） | 边界/异常口径 |
|------|---------|------------------------|---------------|
| `NODE_ARC_ALPHABET_INDEXER_ARRAY` | .object 字符串数组 | 无（须由调用方设置） | 空数组：与 ArkTS 一致处理 |
| `NODE_ARC_ALPHABET_INDEXER_COLOR` | .value[0].u32 ARGB | `0xFFFFFFFF` | 非法颜色按 ArkTS 口径 |
| `NODE_ARC_ALPHABET_INDEXER_SELECTED_COLOR` | .value[0].u32 | `0xFFFFFFFF` | 同上 |
| `NODE_ARC_ALPHABET_INDEXER_POPUP_COLOR` | .value[0].u32 | `0xFFFFFFFF` | 同上 |
| `NODE_ARC_ALPHABET_INDEXER_SELECTED_BACKGROUND_COLOR` | .value[0].u32 | `0xFF1F71FF` | 同上 |
| `NODE_ARC_ALPHABET_INDEXER_POPUP_BACKGROUND_COLOR` | .value[0].u32 | `0xD8404040` | 同上 |
| `NODE_ARC_ALPHABET_INDEXER_USE_POPUP` | .value[0].i32 | `0`（不弹） | 0/1 之外按 ArkTS 口径 |
| `NODE_ARC_ALPHABET_SELECTED_FONT` | .string+.value[0..2] | family `HarmonyOS Sans`/size `13`/weight `W500`/style `NORMAL` | 缺省字段用默认值 |
| `NODE_ARC_ALPHABET_INDEXER_POPUP_FONT` | .string+.value[0..2] | size `19`/weight `W500`/style `NORMAL` | 同上 |
| `NODE_ARC_ALPHABET_FONT` | .string+.value[0..2] | size `13`/weight `W500`/style `NORMAL` | 同上 |
| `NODE_ARC_ALPHABET_INDEXER_ITEM_SIZE` | .value[0].f32 vp | `24` | 负值/0 按 ArkTS 口径 |
| `NODE_ARC_ALPHABET_INDEXER_SELECTED` | .value[0].i32 | `0` | 越界索引按 ArkTS 口径 |
| `NODE_ARC_ALPHABET_AUTO_COLLAPSE` | .value[0].i32 | `1`（折叠） | 0/1 之外按 ArkTS 口径 |
| `NODE_ARC_ALPHABET_POPUP_BACKGROUND_BLUR_STYLE` | .value[0].i32 `ArkUI_BlurStyle` | `ARKUI_BLUR_STYLE_NONE` | 越界枚举按 ArkTS 口径 |

### ArcSwiper 属性默认值与约束（8）

| 属性 | 类型/槽 | 默认值（与 ArkTS 等价） | 边界/异常口径 |
|------|---------|------------------------|---------------|
| `NODE_ARC_SWIPER_INDEX` | .value[0].i32 | `0` | 越界按 ArkTS 口径 |
| `NODE_ARC_SWIPER_INDICATOR` | .value[0..4]+.object | show `1`/direction `SIX_CLOCK`/未选 `0xA9FFFFFF`/已选 `0xFF5EA1FF`/长按背景 `0xFF5EA1FF`/mask 渐变可选 | 方向越界/非法颜色按 ArkTS 口径 |
| `NODE_ARC_SWIPER_DURATION` | .value[0].i32 ms | `400` | 负值/0 按 ArkTS 口径 |
| `NODE_ARC_SWIPER_VERTICAL` | .value[0].i32 | `0`（水平） | 0/1 之外按 ArkTS 口径 |
| `NODE_ARC_SWIPER_DISABLE_SWIPE` | .value[0].i32 | `0` | 同上 |
| `NODE_ARC_SWIPER_DIGITAL_CROWN_SENSITIVITY` | .value[0].i32 `ArkUI_CrownSensitivity` | `ARKUI_CROWN_SENSITIVITY_MEDIUM` | 依赖该枚举存在（design 核验）；越界按 ArkTS 口径 |
| `NODE_ARC_SWIPER_EFFECT_MODE` | .value[0].i32 `ArkUI_EdgeEffect` | `ARKUI_EDGE_EFFECT_SPRING` | 越界枚举按 ArkTS 口径 |
| `NODE_ARC_SWIPER_DISABLE_TRANSITION_ANIMATION` | .value[0].i32 | `0` | 0/1 之外按 ArkTS 口径 |

### 事件参数槽（5）

| 事件 | 参数槽（`ArkUI_NodeComponentEvent.data[]`） | 关联 AC |
|------|---------------------------------------------|---------|
| `NODE_ARC_ALPHABET_INDEXER_EVENT_ON_SELECT` | [0].i32 = 当前显示元素索引 | AC-2.1 |
| `NODE_ARC_SWIPER_EVENT_ON_CHANGE` | [0].i32 = 当前显示元素索引 | AC-2.1 |
| `NODE_ARC_SWIPER_EVENT_ON_ANIMATION_START` | [0].i32 当前 / [1].i32 目标 / [2].f32 当前偏移 / [3].f32 目标偏移 / [4].f32 速度 | AC-2.1 |
| `NODE_ARC_SWIPER_EVENT_ON_ANIMATION_END` | [0].i32 当前 / [1].f32 当前偏移 | AC-2.1 |
| `NODE_ARC_SWIPER_EVENT_ON_GESTURE_SWIPE` | [0].i32 当前 / [1].f32 当前偏移 | AC-2.1 |

### 控制函数行为场景

**`OH_ArkUI_ArcSwiper_ShowPrevious(ArkUI_NodeHandle node)` / `ShowNext` / `FinishAnimation`**

| # | 触发条件 | 预期行为 | 关联 AC |
|---|----------|----------|---------|
| 1 | node 为有效 ArcSwiper 节点 | ShowPrevious/ShowNext 翻到上/下一页；FinishAnimation 终止动画；返回 NO_ERROR | AC-3.1 |
| 2 | node 为 null | 返回 PARAM_INVALID | AC-3.2 |
| 3 | node 为错误 NodeType | 返回 PARAM_INVALID | AC-3.2 |

## 兼容性声明

- **已有 API 行为变更:** 否。仅追加 NDK 节点类型/属性/事件/控制函数/枚举，不修改既有符号。
- **配置文件格式变更:** 否。
- **数据存储格式变更:** 否。
- **最低支持版本:** API 26.1.0（`@since 26.1.0`）。
- **API 版本号策略:** 所有新增符号标注 `@since 26.1.0`；`libace.ndk.json` 中 `first_introduced` = 26.1.0；不删除/不重排既有枚举值，保证向前/向后兼容。

## 架构约束

> 本节列出 AC 验证必须满足的约束；设计方案见 design.md。

| 关键约束 | 约束说明 | 影响 AC |
|----------|----------|---------|
| 复用既有 NG 实现 | ArcSwiper/ArcAlphabetIndexer 的 C API 必须复用 `ArcSwiperPattern`/`ArcIndexerPattern`，不得新建状态机 | AC-1.1/4.1 |
| 事件 register/unregister 配对 | 事件 unregister 必须清空底层 EventHub 回调槽，闭合既有 nullptr reset 表缺口 | AC-2.2 |
| 头文件单源头 | `interfaces/native/native_node.h` 为 ace_engine 拥有的源头，与 interface_sdk_c 同步 | AC-4.1 |
| 错误码统一 | null/错误 NodeType 统一返回 `ARKUI_ERROR_CODE_PARAM_INVALID` | AC-1.2/3.2 |

## 非功能性需求

> proposal 不涉及项确认：安全 N/A、IPC N/A、数据迁移 N/A。本节仅适用项。

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | `ON_GESTURE_SWIPE` 帧级事件不引入每帧堆分配/线程切换；手表帧率不下降（阈值待 Q-4） | benchmark + 设备矩阵 | `evidence/reviews/` |
| 可靠性 | 事件 unregister 后无 UAF；null/错误输入不崩溃 | CAPI UT + 压力测试 | `evidence/checks/` |
| 可测试性 | 22 属性 + 5 事件 + 3 控制函数均有专项 CAPI unittest | capi_all_modifiers_test | `evidence/checks/` |
| 定界定位 | 错误码 PARAM_INVALID/NO_ERROR 可区分调用方误用 | hilog/错误码 | `evidence/checks/` |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手表 | 主目标 | 表冠（digital crown）灵敏度属性生效 | 设备矩阵/UT | `evidence/reviews/` |
| 手机/平板/折叠屏 | 无差异（行为一致，控件形态由组件自身决定） | — | 回归 | — |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | N/A | 不改组件语义树/可见语义，回归即可 | — |
| 大字体 | N/A | 字体属性由调用方设置，组件自身处理 | — |
| 深色模式 | N/A | 颜色属性由调用方设置 | — |
| 多窗口/分屏 | N/A | 进程内 UI 调用 | — |
| 多用户 | N/A | — | — |
| 版本升级 | 否 | 仅追加 API | — |
| 生态兼容 | 是 | 新增 NDK C ABI，需文档/示例/声明同步 | 交付 gate |

## Spec 自审清单

- [x] 无"待定/TBD/TODO"占位符（Owner 待确认项明确标注为 Q-x，非占位）
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（做什么/不做什么清晰）
- [x] 无语义模糊表述（默认值/错误码均为可度量值）
- [x] AC 与规则表交叉一致（每个 AC 至少关联一条规则，每条规则至少关联一个 AC）
- [x] 规则表每条通过 5 项质量检查（可复现/可观测/边界值/关联AC/无冲突）

## context-references

```yaml
context-queries:
  - repo: "openharmony/interface_sdk_c"
    query: "PR #5447 ArcSwiper/ArcAlphabetIndexer NDK 接口定义（native_node.h/native_type.h）"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper NDK modifier/option 参照实现（node_swiper_modifier.cpp、swiper_option.cpp）"
```

**关键文档：** interface_sdk_c PR #5447（接口真相源）；proposal.md（基线/不涉及项/影响范围）。
