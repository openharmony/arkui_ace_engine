# 任务规格

> 最小可执行单元。本 Task 闭合事件生命周期 UAF + ABI/SDK 元数据 + 验证闭环。

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-003-event-lifecycle-and-validation |
| 标题 | 事件生命周期（UAF 闭合）+ ABI/SDK + 验证闭环 |
| 关联 Feature | FEAT-20260126978228-arc-navigation-capi |
| 目标仓库 | arkui_ace_engine |
| 目标模块 | `frameworks/core/interfaces/native/node/`、`interfaces/native/`、`build/` |
| 分支 | OpenHarmony-6.1-Release |
| 优先级 | P0 |
| 复杂度 | 中 |
| 执行方式 | 可独立执行（前置 TASK-001/002） |

## 任务描述

### 做什么

1. **事件 reset 表 UAF 闭合（ADR-002，P0）：**
   - `frameworks/core/interfaces/native/node/node_api.cpp`：新增 `ARC_SWIPER_NODE_RESET_ASYNC_EVENT_HANDLERS[]` 表，按 `ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS`(行923) 模式填入 4 事件（ON_CHANGE/ANIMATION_START/ANIMATION_END/GESTURE_SWIPE）的 reset 实现；接入分发点（行1480/1486）。
   - **补齐** `ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS`(行923) 当前全 `nullptr` 的缺口：为 ArcAlphabetIndexer ON_SELECT 提供真实 reset 实现，使 unregister 清空底层 EventHub 回调槽。
   - 保证 register/unregister 严格配对，重复 unregister 幂等。
2. **ABI/SDK 元数据同步：**
   - `build/libace.map`：`global:` 段追加 `OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext/FinishAnimation`（当前 ArcSwiper 符号计数=0）。
   - `interfaces/native/libace.ndk.json`：新增符号 `first_introduced=26.1.0`；开放级别按 Q-3（未定则按 Public，待 Owner 终确认后回填）。
   - `interfaces/native/build_check_for_c.c`：ABI 编译检查引用新符号。
3. **验证闭环：**
   - 事件 UT：unregister / 重复 unregister 后再触发 → 不回调；UAF 检测（如 ASAN/重复释放断言）。
   - SDK 编译：`ohos-sdk` 产 NDK 头与符号。
   - `ohos-sdd validate --level all` 无 broken edge。

### 不做什么

- 不改组件业务行为（仅事件回调生命周期与元数据）。
- 不新增权限/IPC。
- 不手改 Arkoala 生成层。

## 规格映射与边界

### AC 映射

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-2.2 | spec.md | CAPI UT（unregister/重复 unregister + UAF 检测） |
| AC-4.1 | spec.md | SDK 编译 + libace.map/ndk.json 复核 + validate |

### 规则映射

| Rule ID | Must / Must Not |
|---------|-----------------|
| ADR-002 | Must：register/unregister 配对，清空 EventHub 槽；Must Not：unregister 后残留回调（UAF） |
| OH-ARCH-COMPONENT-BUILD | Must：libace.map/ndk.json 同步新符号 |
| OH-ARCH-API-LEVEL | Must：`@since 26.1.0`；开放级别随 Q-3 |

### 前置依赖

| 类型 | 编号 | 原因 |
|------|------|------|
| Task | TASK-001/002 | 事件与符号产生自前两 Task |
| Context | Q-3 | 控制函数开放级别决定 ndk.json 可见性 |

### 完成判据

- 事件 unregister/重复 unregister UT PASS，UAF 检测无报错。
- `ohos-sdk` 编译 PASS，libace.map/ndk.json 含全部新增符号。
- `ohos-sdd validate --level all` 无 broken edge。

### 停止条件

- Q-3（控制函数开放级别）未定，导致 ndk.json 可见性无法确定（停止，回传 Owner）。
- UAF 检测发现 reset 表补齐后仍残留（回传修订 ADR-002）。

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `frameworks/core/interfaces/native/node/node_api.cpp` | 新增 ARC_SWIPER reset 表 + 补齐 ALPHABET_INDEXER 表 + 分发接入 |
| 修改 | `build/libace.map` | 追加 3 控制函数导出符号 |
| 修改 | `interfaces/native/libace.ndk.json` | 新增符号 first_introduced=26.1.0 |
| 修改 | `interfaces/native/build_check_for_c.c` | ABI 编译检查 |
| 测试 | `test/unittest/capi/modifiers/`（事件用例并入 TASK-001/002 测试或新增） | unregister/重复 unregister + UAF |

## AC

- **AC-2.2:** WHEN 解注册或重复解注册任一 5 事件 THEN EventHub 槽清空、后续触发不再回调、无 UAF
- **AC-4.1:** WHEN 交付验证 THEN 枚举/符号/SDK 元数据/构建/CAPI UT 与 PR #5447 基线一致；validate 无 broken edge

## 代码变更摘要

### 修改文件: `frameworks/core/interfaces/native/node/node_api.cpp`

**变更原因：** 既有 `ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS`(行923) 全 nullptr，unregister 后回调残留 → UAF。
**变更摘要：** 新增 ARC_SWIPER reset 表（4 事件）；补齐 ALPHABET_INDEXER 表项为真实 reset；接入分发（行1480/1486）。
**定位锚点：** `ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS[]`(行923)；分发点 subKind 判断(行1480)。
**设计引用：** ADR-002（design §关键设计决策 + §资源所有权矩阵）。

**条件编译：** N/A。

### 修改文件: `build/libace.map` / `interfaces/native/libace.ndk.json`

**变更摘要：** 追加 `OH_ArkUI_ArcSwiper_*` 符号 + first_introduced=26.1.0。
**定位锚点：** libace.map `global:` 段（行2 起）；ndk.json 既有符号条目模式。

## BUILD.gn 变更

无（本 Task 不新增源文件，仅改 node_api.cpp 与元数据/检查文件）。

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "node_api.cpp ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS 与 IMAGE_ANIMATOR reset 表（有实现）对照；libace.map/ndk.json 既有 Swiper 符号条目"
```

## 验证检查清单

- [ ] 5 事件 unregister/重复 unregister + UAF 均有 UT 覆盖
- [ ] SDK 编译通过
- [ ] libace.map/ndk.json 含全部新增符号
- [ ] `ohos-sdd validate --level all` 无 broken edge
- [ ] 完成证据当次会话生成（fresh）

**完成证据：**

| 证据 | 命令/路径 | 结果 |
|------|-----------|------|
| 事件 UAF UT | `./build.sh --product-name rk3568 --ccache --build-target //foundation/arkui/ace_engine/test/unittest/capi/modifiers:capi_all_modifiers_test` | PASS/FAIL |
| Linux host UT | `./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/test/unittest:linux_unittest_capi` | PASS/FAIL |
| SDK 编译 | `./build.sh --product-name ohos-sdk --build-target ace_engine` | PASS/FAIL |
| ABI 检查 | `interfaces/native/build_check_for_c.c` 编译 | PASS/FAIL |
| 一致性 | `ohos-sdd validate --change FEAT-20260126978228-arc-navigation-capi --level all` | 无 broken edge |
