# 嵌套滚动偏移量不响应 Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `NestedScrollOffsetNoResponse`
> 关联功能域：05-03-05（List/ListItem/ListItemGroup）、05-03-07（Scroll/嵌套滚动基类）

## 问题概述

List（父）内嵌套 WaterFlow（子）以 PARENT_FIRST 嵌套滚动模式运行时，当 List 尾部存在一个高度为 0 的子节点（如占位 ListItem），上滑手势概率性无法触发任何滚动——页面不跟随手指移动，松手后也不移动。进程本身未卡死或崩溃，纯粹是滚动偏移量未被正确分发处理。

典型表现：
- 进入含 List 嵌套 WaterFlow 的页面后，上滑手势无响应，内容不跟随移动
- 概率性触发，与 List 当前布局停在倒数第二个子节点、尾部 height-0 子节点未实际放置有关
- 松手后无回弹、无惯性滑动，界面静止但进程正常运行

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| A. 布局状态内部不一致（posMap 缓存 vs endIndex_） | List 尾部 height-0 子节点曾被布局过，其 `mainSize` 信息残留在 `posMap_` 缓存中；但当前布局轮次 `endIndex_` 未记录该节点 index | List 最后一个 ListItem 高度为 0，某轮布局曾放置过它，后续轮次布局停在倒数第二个节点 |
| B. 嵌套滚动偏移量分发断裂 | PARENT_FIRST 模式下，`IsAtBottom()` 基于 posMap 缓存推进 endIndex 判定到底，`GetOverScrollOffset()` 用实际 `endIndex_` 判定未到底，两者不一致导致父组件返回 `{remain=0, reachEdge=false}` | List 认为已消费全部偏移量，子组件 WaterFlow 收到 0 偏移量，偏移量不处理 |

> 覆盖范围说明：当前仅覆盖上述单一根因链路（posMap 缓存与 endIndex_ 内部不一致 → 偏移量分发断裂），该链路已通过 3 个 PR 的完整 diff 验证。其他嵌套滚动不响应场景（如属性循环 dirty、GeometryTransition 互锁）不在本页范围。

## 排查路径

### 快速判断

1. **确认页面结构**：检查是否存在 List 内嵌套 WaterFlow（或其他可滚动子容器）的 PARENT_FIRST 嵌套滚动场景
2. **检查 List 尾部子节点**：List 最后一个 ListItem 的 `mainSize` 是否为 0（高度为 0 的占位项）
3. **确认手势方向**：不响应是否发生在上滑（向末尾滚动）方向，下滑是否正常
4. **检查 posMap 缓存与 endIndex_ 一致性**：`IsAtBottom()` 是否基于 posMap 缓存推进 endIndex 判定到底，但 `endIndex_` 实际小于 `maxListItemIndex_`（内部不一致）
5. **检查偏移量分发**：在 `HandleScrollSelfOnly` 中 `remainOffset` 是否为 0，`ScrollResult.remain` 是否为 0

### 详细排查

#### 类别 A 排查：布局状态内部不一致（posMap 缓存 vs endIndex_）

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查 List 最后一个子节点高度 | `mainSize == 0`（占位/空节点） | 若非 0，排查其他滚动不响应原因 |
| 2 | 检查布局后 `endIndex_` 值 | `endIndex_ < maxListItemIndex_`（当前轮次未含尾部 height-0 节点） | 若 `endIndex_ == maxListItemIndex_`，排查其他原因 |
| 3 | 检查 `posMap_` 是否含该 height-0 节点的缓存 | `posMap_->GetPositionInfo(endIndex_ + 1).mainSize == 0`（残留自上一轮布局） | 若 posMap 无此缓存，while 循环不会跳过，排查其他 |
| 4 | 检查 `IsAtBottom` 内 while 循环是否基于 posMap 缓存推进 endIndex | 若循环用 `posMap_->GetPositionInfo(endIndex + 1).mainSize` 跳过 height-0 节点 → 命中根因 A | 若无跳过逻辑，排查其他原因 |

关键代码定位：
- `frameworks/core/components_ng/pattern/list/list_pattern.cpp` `ListPattern::IsAtBottom()`：while 循环通过 `posMap_->GetPositionInfo(endIndex + 1)` 查找下一节点 mainSize，若 posMap 残留 height-0 节点缓存则推进 endIndex 超出当前 `endIndex_` 实际范围
- `frameworks/core/components_ng/pattern/list/list_pattern.cpp` `ListPattern::GetOverScrollOffset()`：使用实际 `endIndex_`（未含 height-0 节点）计算 over-scroll，与 IsAtBottom 推进后的 endIndex 不一致

#### 类别 B 排查：嵌套滚动偏移量分发断裂

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `ScrollablePattern::HandleScrollSelfOnly` 断点 | `remainOffset == 0` | 若非 0，排查其他分发问题 |
| 2 | 检查 `GetOverScrollOffset(offset)` 返回 | `overOffset.end == 0`（因 `endIndex_ != maxListItemIndex`） | 若非 0，说明实际到底，排查其他 |
| 3 | 检查 `ScrollResult` 返回值 | `{0, false}`（声称消费全部偏移量） | 若 remain 非 0，排查父组件其他原因 |
| 4 | 在子组件 `HandleScrollParentFirst` 中检查 `result.remain` | `remain == 0`（子组件收到 0 偏移量，不处理） | 命中根因 B |

关键代码定位：
- `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.cpp:2813` `HandleScrollSelfOnly()`：`remainOffset = (allOffset - offset) + overOffset`，当两者均为 0 时返回 `{0, false}`
- `frameworks/core/components_ng/pattern/scrollable/scrollable_pattern.cpp:2722` `HandleScrollParentFirst()`：子组件调用 `parent->HandleScroll()`，若父返回 `remain=0` 则子组件获得 0 偏移量，不处理
- `frameworks/core/components_ng/pattern/list/list_pattern.cpp:1261` `GetOverScrollOffset()`：`endIndex == GetMaxIndexByRepeat()` 判定决定 `offset.end`，使用实际 `endIndex_`

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| A+B（首次修复） | 在 `IsAtBottom` 加 `fromController` 参数，仅公共 API 路径跳过 height-0 节点，内部滚动用准确 `endIndex_` | `list_pattern.cpp` `IsAtBottom` while 循环由 `fromController` 门控；`scrollable_controller.cpp` `IsAtEnd` 传 `fromController=true` | [PR #74036](https://gitcode.com/openharmony/arkui_ace_engine/pull/74036) (fixed) | git show diff：`while (fromController && endIndex < maxListItemIndex_)` |
| A+B（根治修复） | 回退 `fromController` 方案，改为在布局算法层正确处理 height-0 尾节点，使 `endIndex_` 本身正确 | `list_layout_algorithm.cpp` 新增 `LayoutReachEnd()`；`list_pattern.cpp` 删除 while 循环和 `fromController` 参数；删除布局后回收循环 | [PR #74604](https://gitcode.com/openharmony/arkui_ace_engine/pull/74604) (follow_up) | git show diff：`LayoutReachEnd()` 替换 `LayoutForward` 循环条件 + 删除 `itemPosition_.erase` 回收循环 |

### 根治方案详解（PR #74604）

**1. 新增 `LayoutReachEnd()`**（`list_layout_algorithm.cpp`）——在布局阶段正确判定是否到底：

```cpp
bool ListLayoutAlgorithm::LayoutReachEnd(float currentEndPos, float endMainPos, int32_t currentIndex)
{
    if (LessNotEqual(currentEndPos, endMainPos)) return true;   // 未到底，继续布局
    if (GreatNotEqual(currentEndPos, endMainPos)) return false;  // 超出，停止
    return (posMap_ && NearZero(posMap_->GetPositionInfo(currentIndex + 1).mainSize));
    // 相等时：检查下一项是否 height-0，是则视为到底（正确收束布局）
}
```

替换 `LayoutForward` 的 do-while 循环条件，使布局算法在 height-0 尾节点场景下正确收束。

**2. 删除布局后回收循环**——原本会错误移除 height-0 尾节点导致 `endIndex_` 不含它：

```cpp
// PR #74604 删除（曾把 height-0 尾节点从 itemPosition_ 移除）：
while (itemPosition_.size() > 1 && !targetIndex_) {
    auto pos = itemPosition_.rbegin();
    if (GreatNotEqual(pos->second.endPos + chainDelta, endMainPos) &&
        GreatOrEqual(pos->second.startPos + chainDelta, endMainPos)) {
        itemPosition_.erase(pos->first);  // ← 导致 endIndex_ 不含 height-0 节点
    } else { break; }
}
```

删除后 `endIndex_` 正确包含 height-0 尾节点，`IsAtBottom()` 与 `GetOverScrollOffset()` 对 `endIndex` 判断一致，偏移量分发恢复正常。

**3. 回退 `IsAtBottom` 到原始签名**（删除 `fromController` 参数和 while 循环），公共 API `ScrollableController::IsAtEnd()` 回到 `IsAtBottom(true)`。

### 与首次修复（PR #74036）的差异

| 维度 | PR #74036（首次修复） | PR #74604（根治） |
|------|----------------------|-------------------|
| 修复层 | Pattern 层（IsAtBottom 打补丁） | LayoutAlgorithm 层（布局阶段根治） |
| 策略 | 分叉 API 与内部路径（fromController） | 统一路径（endIndex_ 本身正确） |
| IsAtBottom | 保留 while 循环，由 fromController 门控 | 删除 while 循环，回退原始 |
| 布局算法 | 不涉及 | 新增 LayoutReachEnd + 删除回收循环 |
| 根因 | 绕过（API 跳过、内部不跳过） | 根治（布局正确设置 endIndex_） |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | `IsAtBottom` 加无条件 while 循环跳过尾部 `mainSize==0` 子节点，使 `endIndex` 推进到 `maxListItemIndex_` | A（引入） | introduced | [PR #73713](https://gitcode.com/openharmony/arkui_ace_engine/pull/73713) diff：`while (endIndex < maxListItemIndex_) { ... endIndex++; }`，Issue [#65923](https://gitcode.com/openharmony/arkui_ace_engine/issues/65923) | verified |
| CHG-02 | `IsAtBottom` 加 `fromController` 参数门控 while 循环；`ScrollableController::IsAtEnd` 传 `fromController=true` | A+B（修复） | fixed | [PR #74036](https://gitcode.com/openharmony/arkui_ace_engine/pull/74036) diff：`while (fromController && ...)` + `IsAtBottom(true, true)`，Issue [#66194](https://gitcode.com/openharmony/arkui_ace_engine/issues/66194) | verified |
| CHG-03 | 回退 `fromController`+while 循环；新增 `LayoutReachEnd()` 在布局算法层正确处理 height-0 尾节点；删除布局后回收循环 | A+B（根治） | follow_up | [PR #74604](https://gitcode.com/openharmony/arkui_ace_engine/pull/74604) diff：`LayoutReachEnd()` 替换循环条件 + 删除 `itemPosition_.erase` 回收 | verified |

## 预防措施

- **避免在 List 尾部放置 height-0 的 ListItem**：占位节点应设置最小高度或使用其他方式实现占位语义
- **嵌套滚动场景回归测试**：List 嵌套可滚动子容器（WaterFlow/Grid/Scroll）时，必须覆盖尾部 height-0 子节点 + 上滑到底的用例
- **IsAtBottom 与 GetOverScrollOffset 一致性检查**：两者对 `endIndex` 的判断必须一致，任何修改其中一个时须同步审查另一个
- **边界判定函数不应在 Pattern 层绕过布局状态**：如需特殊处理 height-0 节点，应在布局算法层（LayoutAlgorithm）正确设置 `endIndex_`，而非在 Pattern 层事后跳过

## 相关主题

- `docs/kb/components/container/list.md` — List 组件 KB（源码/SDK/Spec 路由）
- `docs/kb/components/container/scroll.md` — Scroll 组件 KB（含嵌套滚动基类 ScrollablePattern 路由）
- `docs/kb/architecture/layout-framework.md` — 布局框架 KB（`NeedAdditionalLayout`、`FlushTask` 布局回溯调度）
- `specs/05-ui-components/03-scroll-container-components/05-list-list-item-list-item-group` — List Spec 域
- `specs/05-ui-components/03-scroll-container-components/07-scroll` — Scroll Spec 域（嵌套滚动）
