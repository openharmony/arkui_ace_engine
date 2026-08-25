# 滚动组件下树误触发父组件 onScrollEnd Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-03
> 来源：`docs/context_registry.json` 主题 `ScrollEndNotifyOnDetach`
> 关联功能域：05-03-01（滚动公共能力/嵌套滚动基类）、05-03-06（Refresh）

## 问题概述

可滚动组件（List/Scroll/Grid/WaterFlow 等 `ScrollablePattern` 子类）**从未发生滚动**时从组件树移除（下树），仍会触发父组件 `OnScrollEndRecursive` 通知，导致父组件收到一次"虚假"的滚动结束回调。根因是滚动会话判定条件 `!scrollStop_` 存在默认值误判：`scrollStop_` 默认即为 `false`，从未滚动过的组件同样满足条件。

典型表现：
- 可滚动组件从未滚动，因条件渲染被移除/下树时，父组件 `onScrollEnd` 回调被错误触发
- Refresh 包裹的子列表从未滚动即被移除时，刷新状态被异常复位（`refreshStatus_` 被置回 INACTIVE）
- 通知携带的 `GetVelocity()` 为默认值而非真实滚动速度

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | ScrollablePattern 子类（List/Scroll/Grid/WaterFlow） | `scrollable_pattern.cpp` `OnDetachFromMainTree` | verified |
| capability | trigger | 嵌套滚动协调（NestableScrollContainer） | `nestable_scroll_container.h:92` `GetNestedScrollParent` | verified |
| architecture | root_cause_owner | 滚动会话状态机（`scrollStop_`/`isScrolling_`） | `scrollable_pattern.h:1097`（`scrollStop_=false` 默认值）、`:1316`（`isScrolling_=false`） | verified |
| component | fix_location | ScrollablePattern（`OnDetachFromMainTree`）+ RefreshPattern 白名单 | PR #87925 diff | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| A. 滚动会话判定条件错误（`!scrollStop_` 默认值误判） | 组件从未滚动（`isScrolling_=false`）且 `scrollStop_` 保持默认 `false`，下树时旧逻辑 `!scrollStop_` 成立 | 条件渲染移除一个从未滚动过的 List，父组件（尤其 Refresh）收到虚假 onScrollEnd |
| B. 通知白名单收窄的遗留风险（非 #80047 根因，修复引入的限制） | 滚动会话进行中（`isScrolling_=true`），子组件下树，父组件为 Swiper/Web/ContainerPicker/Sheet | List 嵌套在 Swiper/Web/Picker 中滚动过程中被下树，父组件收不到滚动结束收尾通知 |

> 覆盖范围说明：本页根因 A（#80047 主链路）已通过 0519aa6c9 → PR #87925 完整 diff 验证。类别 B 是 PR #87925 白名单方案引入的行为收窄，检视意见未闭环即合入（见 CHG-03），属于遗留风险记录而非已确认缺陷。

## 排查路径

### 快速判断

1. **确认场景**：可滚动组件（List/Scroll/Grid/WaterFlow）是否在**从未滚动**的情况下被移除/下树，且父组件随后收到意外 `onScrollEnd`
2. **检查滚动会话状态**：下树瞬间 `isScrolling_` 是否为 `false`（从未滚动）、`scrollStop_` 是否为默认 `false`（从未停止过滚动）
3. **检查父组件类型**：父组件是否为 `ScrollablePattern` 或 `RefreshPattern`（修复后仅这两类会收到通知）
4. **确认触发入口**：下树是否经由 `OnDetachFromMainTree`（条件渲染移除、页面销毁、IF/ForEach 节点移除）

### 详细排查

#### 类别 A 排查：滚动会话判定条件错误

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `ScrollablePattern::OnDetachFromMainTree` 下断点（`scrollable_pattern.cpp:1294`） | 下树时命中，且组件从未滚动 | 若组件滚动过，属正常通知场景 |
| 2 | 检查 `scrollStop_` 值 | 默认 `false`（组件从未滚动，`OnScrollEndCallback` 未把 `scrollStop_` 置 true） | 若为 true，旧逻辑本就不会通知 |
| 3 | 检查 `isScrolling_` 值 | `false`（从未进入 `FireOnScrollStart` 的 `isScrolling_ = true` 分支） | 若为 true，属滚动中下树，通知合理 |
| 4 | 复现到父组件回调 | 父组件 `onScrollEnd` 被触发，速度参数为默认值 | 确认命中根因 A |

关键代码定位：
- `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.cpp:1301-1307` `OnDetachFromMainTree()`（函数入口 :1294）：拟修复后条件 `if (!isScrolling_ || scrollStop_) return;` + 父组件白名单过滤（注：PR #87925 修复尚未合入，当前基线代码仍为 `if (!scrollStop_)`）
- `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.h:1097`：`bool scrollStop_ = false;` 默认值——旧逻辑 `!scrollStop_` 误判的根源
- `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.h:1316`：`bool isScrolling_ = false;`——滚动会话显式标志
- `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.cpp:3415` `FireOnScrollStart()`：滚动会话开始，`:3451` 置 `isScrolling_ = true`
- `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.cpp:3681` `OnScrollStop()`：滚动会话结束，`:3697` 置 `isScrolling_ = false`、`:3722` 复位 `scrollStop_ = false`
- `frameworks/core/components_ng/pattern/list/list_pattern.cpp:1420`（同 `scroll_pattern.cpp:345`、`grid_pattern.cpp:874`、`water_flow_pattern.cpp:800`）：`OnScrollEndCallback` 中动画停止后 `scrollStop_ = true`

#### 类别 B 排查：白名单收窄的遗留风险识别

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 判断父组件类型是否命中白名单 | `AceType::InstanceOf<ScrollablePattern>` 或 `AceType::InstanceOf<RefreshPattern>` | 若为其他 NestableScrollContainer 子类，收不到通知（本类别风险） |
| 2 | 检查父组件是否重写 `OnScrollEndRecursive` | Swiper/Web/ContainerPicker/Sheet 均有实际实现 | 无实现则无影响 |
| 3 | 检查嵌套滚动状态是否残留 | 如 Swiper 的 `childScrolling_`、`isNestedInterrupt_` 等收尾状态 | 残留则确认命中类别 B 风险 |

关键代码定位：
- `frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp:6492` `OnScrollEndRecursive()`：重置 `childScrolling_ = false`、`SetIsNestedInterrupt(false)`、`HandleDragEnd`
- `frameworks/core/components_ng/pattern/web/web_pattern.cpp:8138`、`container_picker_pattern.cpp:1194`、`sheet_presentation_pattern.cpp:3289`：同类收尾实现，均被白名单排除
- `frameworks/core/components_ng/pattern/refresh/refresh_pattern.cpp:1391` `OnScrollEndRecursive()`：`HandleDragEnd` 复位 `refreshStatus_` 至 INACTIVE（白名单内，正常收尾）

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| A（#80047） | 将"滚动进行中"判定从 `!scrollStop_` 收紧为显式会话标志：`isScrolling_==true && scrollStop_==false`，并将父组件通知范围限制为 Scrollable/Refresh 白名单 | `scrollable_pattern.cpp` `OnDetachFromMainTree`：`if (!isScrolling_ || scrollStop_) return;` + `InstanceOf<ScrollablePattern> \|\| InstanceOf<RefreshPattern>`；新增 `#include "refresh_pattern.h"` | [PR #87925](https://gitcode.com/openharmony/arkui_ace_engine/pull/87925) (fixed) | PR diff + Issue [#80047](https://gitcode.com/openharmony/arkui_ace_engine/issues/80047)，测试 OnDetachFromMainTree003-008（`scrollable_pattern_test_ng.cpp:2191-2324`）Host x86_64 实测通过 |
| B（遗留风险） | 需产品确认 Swiper/Web/Picker/Sheet 作为父组件是否也需要下树收尾通知；若需要，白名单需扩展或改为反向排除 | 待定（当前未闭环） | 无（检视意见未落地） | PR #87925 diff 评论（guozejun，blocking，resolved: false） |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 引入下树通知：`OnDetachFromMainTree` 中 `if (!scrollStop_) { parent->OnScrollEndRecursive(GetVelocity()); }`，意图是嵌套滚动中子组件下树时正确结束父组件滚动 | A（引入） | introduced | commit `0519aa6c9`（"嵌套滚动过程中子组件下树，会正确触发父组件onScrollEnd"）diff：`!scrollStop_` 条件 + 无父组件类型过滤；`scrollStop_` 默认 false 导致从未滚动误通知 | verified |
| CHG-02 | 修复：收紧判定为 `isScrolling_ && !scrollStop_`，父组件限定 ScrollablePattern/RefreshPattern 白名单；新增 Refresh 场景测试 6 例 | A（修复） | fixed | [PR #87925](https://gitcode.com/openharmony/arkui_ace_engine/pull/87925) diff + Issue [#80047](https://gitcode.com/openharmony/arkui_ace_engine/issues/80047)；测试 OnDetachFromMainTree003-008 | verified |
| CHG-03 | 白名单范围争议：排除 SwiperPattern/WebPattern/ContainerPickerPattern/SheetPresentationPattern 的检视意见（blocking），未解决即合入 | B（遗留） | related | [PR #87925](https://gitcode.com/openharmony/arkui_ace_engine/pull/87925) diff 评论（guozejun，resolved: false）；`swiper_pattern.cpp:6492` 等收尾实现被排除 | verified |

## 预防措施

- **滚动会话状态判定应使用显式会话标志**（如 `isScrolling_`），避免依赖默认值为 `false` 的布尔位（`scrollStop_`）推导"从未滚动"语义
- **下树/销毁路径的父组件通知必须覆盖"从未滚动"用例**：新增/修改 `OnDetachFromMainTree` 类逻辑时，回归 `scrollable_pattern_test_ng.cpp` OnDetachFromMainTree 用例族（003-008）
- **白名单类过滤需评估全部 `NestableScrollContainer` 子类**：Swiper/Web/ContainerPicker/Sheet 均重写 `OnScrollEndRecursive`，新增子类会静默失去下树通知，建议使用虚函数钩子或反向排除
- **blocking 检视意见应闭环后合入**：CHG-03 意见未解决即合并，后续如有 Swiper/Web/Picker 嵌套下树场景异常，优先回查此白名单

## 相关主题

- `docs/kb/capabilities/scroll-common-capability.md` — 滚动公共能力 KB（ScrollablePattern/嵌套滚动源码路由，Spec 05-03-01）
- `docs/kb/components/container/scroll.md` — Scroll 组件 KB（含嵌套滚动基类）
- `docs/kb/components/container/refresh.md` — Refresh 组件 KB（下拉刷新状态机）
- `docs/kb/issues/interaction/nested-scroll-offset-no-response.md` — 嵌套滚动偏移量不响应问题 KB（同类嵌套滚动协调主题）
- `specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability` — 滚动公共能力 Spec 域
- `specs/05-ui-components/03-scroll-container-components/06-refresh` — Refresh Spec 域
