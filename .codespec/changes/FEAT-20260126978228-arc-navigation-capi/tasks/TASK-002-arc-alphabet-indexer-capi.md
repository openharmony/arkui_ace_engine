# 任务规格

> 最小可执行单元。本 Task 为 ArcAlphabetIndexer NDK C API 实现。

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-002-arc-alphabet-indexer-capi |
| 标题 | ArcAlphabetIndexer C API（NDK）实现 |
| 关联 Feature | FEAT-20260126978228-arc-navigation-capi |
| 目标仓库 | arkui_ace_engine |
| 目标模块 | `interfaces/native/`、`frameworks/core/interfaces/native/node/` |
| 分支 | OpenHarmony-6.1-Release |
| 优先级 | P0 |
| 复杂度 | 中 |
| 执行方式 | 可独立执行（前置 TASK-001 模式确立） |

## 任务描述

### 做什么

1. `interfaces/native/native_node.h`：NodeType 枚举追加 `ARKUI_NODE_ARC_ALPHABET_INDEXER = 23`（位于 `ARKUI_NODE_TEXT_EDITOR=22` 之后、`ARKUI_NODE_STACK` 之前）；属性枚举追加 14 个 `NODE_ARC_ALPHABET_*`（ARRAY/COLOR/SELECTED_COLOR/POPUP_COLOR/SELECTED_BACKGROUND_COLOR/POPUP_BACKGROUND_COLOR/USE_POPUP/SELECTED_FONT/POPUP_FONT/FONT/ITEM_SIZE/SELECTED/AUTO_COLLAPSE/POPUP_BACKGROUND_BLUR_STYLE）；事件枚举追加 `NODE_ARC_ALPHABET_INDEXER_EVENT_ON_SELECT`。参数格式权威定义见 PR #5447。
2. `frameworks/core/interfaces/native/node/alphabet_indexer_modifier.cpp/h`：**扩展**（非新建，ADR-003）—— modifier 已注册（`node_modifiers.cpp:222 getAlphabetIndexerModifier`），补齐 14 个 Arc 属性 set/reset/get；声明/暴露 `ARKUI_NODE_ARC_ALPHABET_INDEXER` 节点类型（当前该 modifier 注册但无对应 NodeType，属"半成品"）。
3. `interfaces/native/node/style_modifier.cpp`：14 属性 Set/Reset/Get 三件套 + switch 派发 + reset 表（行20987 模式）+ 类型名表（`{ARC_ALPHABET_INDEXER,"ArcAlphabetIndexer"}`）。
4. `interfaces/native/node/node_model.cpp`：NodeType↔Tag 映射双向追加（行1415/1467 模式，Tag 用 ArcAlphabetIndexer 既有 ETS tag）；createNode 白名单。
5. `interfaces/native/node/node_model_safely.cpp`：安全创建白名单同步。
6. `test/unittest/capi/modifiers/arc_alphabet_indexer_modifier_test.cpp`（新建）+ `BUILD.gn` sources：14 属性 set/get/reset + 默认值 + 边界/异常 + 1 事件 register/fire/参数槽（[0].i32 索引）。

### 不做什么

- 不改 ArkTS/NG 行为与 `ArcIndexerPattern`（仅复用）。
- 不在本 Task 改 libace.map/ndk.json（TASK-003）。
- 不手改 Arkoala 生成层。

## 规格映射与边界

### AC 映射

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-1.1/1.2/1.3 | spec.md | CAPI UT 逐属性 set/get/reset + 默认值 + 边界/异常 |
| AC-2.1 | spec.md | CAPI UT ON_SELECT register/fire/参数槽 |

### 规则映射

| Rule ID | Must / Must Not |
|---------|-----------------|
| ADR-001 | Must：复用 ArcIndexerPattern |
| ADR-003 | Must：扩展既有 alphabet_indexer_modifier，不新建 |
| 错误码 | Must：null/错误 NodeType 返回 PARAM_INVALID |

### 前置依赖

| 类型 | 编号 | 原因 |
|------|------|------|
| Task | TASK-001 | NDK 暴露模式（modifier 注册/属性分发/createNode）须先确立 |
| Context | PR #5447 | 参数格式真相源 |

### 完成判据

- `capi_all_modifiers_test` 中 ArcAlphabetIndexer 用例全 PASS（14 属性 + 1 事件）。
- 构建通过。

### 停止条件

- 既有 `alphabet_indexer_modifier` 结构不支持扩展 14 属性（回传修订 ADR-003）。
- 任一变更点属于 Arkoala 生成层。

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `interfaces/native/native_node.h` | NodeType+14属性+1事件枚举 |
| 修改 | `frameworks/core/interfaces/native/node/alphabet_indexer_modifier.cpp/h` | 扩展 14 属性 + 暴露节点类型 |
| 修改 | `interfaces/native/node/style_modifier.cpp` | 14 属性三向 + switch + reset 表 + 类型名表 |
| 修改 | `interfaces/native/node/node_model.cpp` | NodeType↔Tag + createNode 白名单 |
| 修改 | `interfaces/native/node/node_model_safely.cpp` | 安全白名单 |
| 新增 | `test/unittest/capi/modifiers/arc_alphabet_indexer_modifier_test.cpp` | CAPI UT |
| 修改 | `test/unittest/capi/modifiers/BUILD.gn` | 测试 sources |

## AC

- **AC-1.1:** WHEN 对 14 属性执行合法 set/get/reset THEN get 返回所设值与 ArkTS 等价默认值（COLOR/SELECTED_COLOR/POPUP_COLOR=0xFFFFFFFF；SELECTED_BG=0xFF1F71FF；POPUP_BG=0xD8404040；USE_POPUP=0；SELECTED=0；ITEM_SIZE=24；AUTO_COLLAPSE=1；POPUP_BLUR=NONE；各 FONT 见 spec）
- **AC-1.2:** WHEN null/错误 NodeType/越界枚举/空数组/缺省字段 THEN 返回 PARAM_INVALID 或按 ArkTS 口径忽略，不崩溃
- **AC-1.3:** WHEN ITEM_SIZE 负值/0、SELECTED 越界 THEN 按 ArkTS 口径处理，不崩溃
- **AC-2.1:** WHEN 注册并触发 ON_SELECT THEN 回调 [0].i32 = 当前显示元素索引

## 代码变更摘要

### 修改文件: `frameworks/core/interfaces/native/node/alphabet_indexer_modifier.cpp/h`

**变更原因：** modifier 已注册但无 NodeType、缺 Arc 属性（半成品）。
**变更摘要：** 扩展 14 个 set/reset/get，声明可创建 `ARKUI_NODE_ARC_ALPHABET_INDEXER`。
**定位锚点：** 参照 `node_swiper_modifier.cpp` 的结构体构造模式（ADR-003）。
**设计引用：** ADR-001/ADR-003（design §关键设计决策）。

**条件编译：** N/A。

## BUILD.gn 变更

```
文件路径: test/unittest/capi/modifiers/BUILD.gn
变更说明: sources 追加 arc_alphabet_indexer_modifier_test.cpp
（alphabet_indexer_modifier.cpp 已在 interfaces/native/node/BUILD.gn，无需改）
```

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "alphabet_indexer_modifier 现状；node_modifiers.cpp:222 注册；indexer_dynamic_modifier.cpp isArc 分支"
  - repo: "openharmony/interface_sdk_c"
    query: "PR #5447 NODE_ARC_ALPHABET_* 参数格式"
```

## 验证检查清单

- [ ] 14 属性 + 1 事件均有 CAPI UT 覆盖
- [ ] 测试通过（fresh evidence）
- [ ] 构建通过
- [ ] 未修改文件范围外内容
- [ ] 完成证据已记录

**完成证据：**

| 证据 | 命令/路径 | 结果 |
|------|-----------|------|
| Modifier UT | `./build.sh --product-name rk3568 --ccache --build-target //foundation/arkui/ace_engine/test/unittest/capi/modifiers:capi_all_modifiers_test` | PASS/FAIL |
| CAPI UT（全量） | `./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/test/unittest/capi:capi_unittest` | PASS/FAIL |
