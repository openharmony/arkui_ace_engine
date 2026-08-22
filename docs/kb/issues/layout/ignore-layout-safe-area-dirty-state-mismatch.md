# ignoreLayoutSafeArea 布局脏状态异常导致页面白屏 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `IgnoreLayoutSafeAreaDirtyStateMismatch`
> 关联功能域：04-02-01、05-02-01、05-03-08

## 问题概述

当深层节点设置 `ignoreLayoutSafeArea` 时，延迟布局任务可能与祖先节点已有的正常布局任务交错，或者在预测量提前返回后遗留布局脏状态，导致后续布局被错误跳过或标脏异常。典型结果是目标内容未获得有效尺寸，页面表现为白屏。

典型表现：
- 页面跳转后，待布局的 `NavigationContent` 没有完成布局，尺寸保持为 0。
- `Navigation` 的一个分支需要正常布局，另一个设置了 `ignoreLayoutSafeArea` 的分支同时产生延迟布局任务。
- `Swiper` 等启用子节点预测量的容器提前结束测量后，`LayoutDirty` 未恢复，后续标脏和布局调度异常。

当前覆盖两个连续变更形成的根因：深层 ignore 节点独立任务干扰祖先正常布局，以及修复该问题时引入的 `LayoutDirty` 设置与清理不对称。本文不覆盖其他原因导致的 Navigation、Swiper 或通用页面白屏。

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | Navigation / NavigationContent | 特定应用中 NavigationContent 最终尺寸为 0；关联变更修复深层 ignore 任务顺序 | user_claimed |
| component | symptom_surface | Swiper | 特定应用中 Swiper 场景出现后续布局异常 | user_claimed |
| capability | trigger | ignoreLayoutSafeArea | `FrameNode::TraverseForIgnore` 和延迟安全区布局任务仅在子树存在有效 ignore 配置时触发 | verified |
| architecture | root_cause_owner | FrameNode 布局脏状态与预测量流程 | `FrameNode::Measure` 可在 `PreMeasure` 返回 true 时提前结束，早于正常脏状态清理 | verified |
| architecture | fix_location | UITaskScheduler ignore 安全区任务调度 | PR 77404 调整 Traverse 任务类型和调度对象；PR 78728 删除额外的 LayoutDirty 置位 | verified |
| component | trigger | SwiperPattern 预测量机制 | `SwiperPattern::ChildPreMeasureHelperEnabled()` 返回 true | verified |
| architecture | dependency | LayoutProperty 变更标志 | `PROPERTY_UPDATE_MEASURE` 用于保证 Traverse 任务不被 Measure/Layout 剪枝 | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 深层 ignore 独立任务干扰祖先布局 | 祖先约束未变化并进入 Measure 剪枝；深层后代设置 `ignoreLayoutSafeArea`；共享祖先同时存在其他待布局分支 | `NavigationContent` 向上标脏 `Navigation`，而设置 ignore 的 `NavBar` 分支产生包含共享祖先的延迟布局任务；共享祖先脏状态提前被消费，正常任务随后被跳过 |
| Traverse 任务遗留 LayoutDirty | Traverse 调度显式设置 `LayoutDirtyMarked(true)`；ignore 节点的父容器启用预测量；`PreMeasure` 判定需要延迟测量并提前返回 | `Swiper` 等容器在完整 Measure 执行前返回，没有进入正常的 `LayoutDirty` 清理位置，导致该标志长期为 true 并影响后续标脏与布局 |

## 排查路径

### 快速判断

1. 确认白屏节点的 `GeometryNode` 尺寸是否为 0，并检查其本轮是否真正执行了 Measure 和 Layout。
2. 检查节点祖先或兄弟分支中是否存在有效的 `ignoreLayoutSafeArea` 配置。
3. 打开 Measure 调试 Trace，观察 `TraverseForIgnore`、`FlushPostponedLayoutTask`、`CreateLayoutTask`、`SkipMeasure` 和 `SkipLayout` 的执行顺序。
4. 如果共享祖先在 ignore 延迟任务后跳过正常布局，优先排查“深层 ignore 独立任务干扰祖先布局”。
5. 如果容器经过预测量提前返回后持续保持 `LayoutDirty`，优先排查“Traverse 任务遗留 LayoutDirty”。

### 详细排查

#### 深层 ignore 独立任务干扰祖先布局排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查白屏内容节点的 GeometryNode 和 Measure/Layout Trace | 内容节点尺寸有效，且本轮执行了 Measure 和 Layout | 尺寸为 0 或缺少调用时继续步骤 2 |
| 2 | 沿父链检查正常布局标脏是否到达共享祖先 | 共享祖先进入正常脏节点队列 | 未进入时转查普通 MarkDirty 传播 |
| 3 | 检查共享祖先其他分支是否包含有效 `ignoreLayoutSafeArea` 节点 | 不应由后代独立任务提前消费共享祖先的布局状态 | 存在时继续步骤 4 |
| 4 | 对照 PR 77404 前后的 `TraverseForIgnore` 和调度器行为 | Traverse 应投递容器自身，并执行成对的 Measure/Layout | 如果仍直接投递深层后代，说明未包含对应修复 |
| 5 | 检查已需要强制布局的子树是否被重复加入 Traverse 流程 | `CheckNeedForceMeasureAndLayout()` 为 true 的子树应跳过额外 Traverse 投递 | 未跳过时检查修复版本及后续改动 |

关键代码定位：
- `frameworks/core/components_ng/base/frame_node.cpp` / `FrameNode::TraverseForIgnore`：约束未变化时继续发现深层 ignore 节点，并投递当前容器。
- `frameworks/core/components_ng/base/frame_node.cpp` / `FrameNode::TraverseSubtreeToPostBundle`：过滤已经需要强制 Measure/Layout 的子树。
- `frameworks/core/components_ng/base/frame_node.cpp` / `FrameNode::CreateLayoutTask`：`TRAVERSE_FOR_IGNORE` 下执行成对的 Measure 和 Layout。
- `frameworks/core/pipeline_ng/ui_task_scheduler.cpp` / `UITaskScheduler::FlushPostponedLayoutTask`：执行 Traverse 容器任务和普通 ignore 延迟任务。

#### Traverse 任务遗留 LayoutDirty 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查 ignore 节点父容器是否启用 `ChildPreMeasureHelperEnabled` | 普通容器通常不进入预测量延迟分支；Swiper 等容器可能进入 | 未启用时排查其他 Measure 提前返回路径 |
| 2 | 检查 `FrameNode::PreMeasure` 是否返回 true | 返回 true 表示本次子节点 Measure 被延迟 | 返回 false 时排查其他脏状态遗留原因 |
| 3 | 检查调度器在创建 Traverse 任务前是否显式调用 `SetLayoutDirtyMarked(true)` | 修复后不应存在该调用，只应更新 `PROPERTY_UPDATE_MEASURE` | 若仍存在，说明未包含 PR 78728 |
| 4 | 检查提前返回前后 `IsLayoutDirtyMarked()` 的值 | 不应因 Traverse 辅助任务永久遗留 true | 持续为 true 时确认清理路径及后续标脏行为 |
| 5 | 检查后续正常 MarkDirty 是否能重新进入布局队列 | 后续标脏应正常触发 Measure/Layout | 未触发时继续沿 PipelineContext 和 UITaskScheduler 排查 |

关键代码定位：
- `frameworks/core/components_ng/base/frame_node.cpp` / `FrameNode::PreMeasure`：父容器预测量判定和延迟任务收集入口。
- `frameworks/core/components_ng/base/frame_node.cpp` / `FrameNode::Measure`：`PreMeasure` 提前返回与正常 `isLayoutDirtyMarked_ = false` 的相对位置。
- `frameworks/core/components_ng/pattern/swiper/swiper_pattern.h` / `SwiperPattern::ChildPreMeasureHelperEnabled`：Swiper 启用预测量机制的入口。
- `frameworks/core/pipeline_ng/ui_task_scheduler.cpp` / `UITaskScheduler::FlushPostponedLayoutTask`：修复后仅更新 Measure 属性标志，不再额外设置 LayoutDirty。

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 深层 ignore 独立任务干扰祖先布局 | 将 Traverse 发现的任务改为投递容器自身，新增专用 `TRAVERSE_FOR_IGNORE` 流程，确保 Measure/Layout 成对执行；跳过本就需要强制布局的子树 | `frame_node.cpp`、`ui_task_scheduler.cpp`、`pipeline_context.cpp`、`constants.h` | [PR 77404](https://gitcode.com/openharmony/arkui_ace_engine/pull/77404) / `1e1ff2667ab491c2f6a94cb780feb58e5d8f6f4b` (fixed) | PR 描述明确要求 Measure/Layout 成对出现；diff 将后代投递改为容器 Traverse 任务 |
| Traverse 任务遗留 LayoutDirty | 删除 Traverse 调度前多余的 `SetLayoutDirtyMarked(true)`；保留 `PROPERTY_UPDATE_MEASURE` 作为本次任务的强制测量依据 | `frameworks/core/pipeline_ng/ui_task_scheduler.cpp` | [PR 78728](https://gitcode.com/openharmony/arkui_ace_engine/pull/78728) / `898dcf960d5fd0fd58695ddd957e6451721791c7` (fixed) | diff 精确删除 LayoutDirty 置位；`TRAVERSE_FOR_IGNORE` 不受普通任务入口的 dirty bool 限制 |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 新增 ignore 子树计数、`TraverseForIgnore` 和约束剪枝后的深层任务投递 | 深层 ignore 独立任务干扰祖先布局 | introduced | `8c599c96de71241cdff8783b34d66d7a330e0eb9` diff 新增遍历和后代 `PostBundle` 路径 | verified |
| CHG-02 | 将 Traverse 任务改为容器自身执行，并保证 Measure/Layout 配对 | 深层 ignore 独立任务干扰祖先布局 | fixed | PR 77404；`1e1ff2667ab491c2f6a94cb780feb58e5d8f6f4b` diff 及公开合并描述 | verified |
| CHG-03 | 在 Traverse 容器任务前显式设置 `LayoutDirtyMarked(true)` | Traverse 任务遗留 LayoutDirty | introduced | PR 77404 diff 在调度器中新增该置位；该行随后被 PR 78728 精确删除 | verified |
| CHG-04 | 删除 Traverse 任务的额外 LayoutDirty 置位 | Traverse 任务遗留 LayoutDirty | fixed | PR 78728；`898dcf960d5fd0fd58695ddd957e6451721791c7` 单行删除 diff | verified |

## 预防措施

- 布局任务新增状态位时，应明确状态的设置者、消费位置和所有退出路径，确保设置与清理对称。
- 特殊布局任务应优先复用 `LayoutProperty` 的 Measure/Layout 变更标志，避免同时修改普通脏节点队列使用的状态位。
- 调整布局剪枝或穿透逻辑时，应验证同一祖先下“正常脏分支 + ignore 分支”的任务顺序。
- 为 `PreMeasure`、不可见节点、SkipMeasure 等提前返回路径增加脏状态不变量检查。
- 增加至少两类直接回归：Navigation 共享祖先多分支场景，以及 Swiper 父容器预测量提前返回场景。
- 调试时区分“节点进入过任务”和“节点完成了成对的 Measure/Layout”，不能仅凭任务已创建判断布局完成。

## 相关主题

- [docs/kb/capabilities/safe-area.md](../../capabilities/safe-area.md)
- [docs/kb/architecture/layout-framework.md](../../architecture/layout-framework.md)
- 安全区域机制功能域：`04-02-01`
- [Navigation 功能域：`05-02-01`](../../components/container/navigation.md)
- [Swiper 功能域：`05-03-08`](../../components/container/swiper.md)