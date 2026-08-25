# Canvas 绘制任务堆积导致 AppFreeze Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `CanvasDrawingTaskBacklogAppFreeze`
> 关联功能域：05-14-02

## 问题概述

本文是基于高频应用问题咨询形成的排查经验。当应用在单帧内调用过多 Canvas 绘制接口，或者进入后台后仍持续执行 Canvas 动画绘制时，待执行的绘制任务可能大量堆积；后续集中执行这些任务会长时间阻塞 UI 线程，并可能触发 AppFreeze。

典型表现：
- Canvas 调用绘制接口时应用出现卡死或 AppFreeze。
- 调用栈中出现 `FlushTask`；仅凭该函数名不能确定是 UI 调度器还是 Canvas 内部刷新函数。
- 应用恢复前台或 Canvas 恢复渲染时出现明显卡顿，之前持续提交的绘制任务被集中执行。
- UI 线程阻塞达到 6 秒后，上报 `UI_BLOCK_6S` 冻结事件。

Canvas 延迟任务队列及 `FlushTask` 调用链用于解释问题发生机制，不表示 Canvas 底座存在实现缺陷。本文的根因和整改均位于应用侧，不涉及 ace_engine 问题修复提交；也不覆盖图片解码、业务死锁或其他非 Canvas 绘制量问题导致的 AppFreeze。

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | Canvas | 高频应用问题咨询中，AppFreeze 在调用 Canvas 绘制接口时出现 | user_claimed |
| capability | trigger | CanvasRenderingContext2D 绘制接口 | 绘制操作最终通过 `CanvasPaintMethod::PushTask` 提交到 CanvasRenderContext | verified |
| architecture | root_cause_owner | 应用绘制循环与生命周期控制 | 单帧绘制量失控，或应用进入后台后仍继续调用绘制接口 | user_claimed |
| architecture | dependency | CanvasRenderContextDeferred 延迟任务队列 | `PushTask` 将任务加入 `tasks_`，`FlushTask` 遍历执行全部待处理任务 | verified |
| architecture | dependency | CanvasPaintMethod 内容更新 | `UpdateContentModifier` 在 `NeedRender()` 为 true 时调用 `FlushTask` | verified |
| architecture | dependency | UITaskScheduler 与 ArkUI WatchDog | 渲染任务进入 Canvas 内容更新；线程冻结阶段映射为 `UI_BLOCK_6S` | verified |
| capability | fix_location | 应用绘制逻辑、动画与生命周期管理 | 整改发生在应用侧：限制单帧绘制量，并在后台等无效绘制阶段停止提交任务 | user_claimed |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 应用单帧绘制指令过多 | 应用在一个渲染帧内高频、循环调用大量 Canvas 绘制接口 | 单帧生成大量路径、文本、图片或重复绘制操作，待处理任务在一次 `FlushTask` 中集中执行 |
| 应用后台仍持续绘制 | 应用进入后台后，Canvas 动画、定时器或绘制回调未停止 | 后台期间仍持续提交绘制任务，恢复前台后集中执行，UI 线程耗时达到冻结判定边界 |

延迟渲染模式下，`CanvasRenderContextDeferred::PushTask` 会将每条绘制任务加入 `tasks_`。任务数达到 100000 的整数倍时，框架会记录 `Canvas task size` 日志并上报 `CANVAS_TASKS_OVERFLOW` 统计事件；该数值只用于诊断，不是队列容量限制，也不会自动限流或丢弃任务。

立即渲染模式具有不同的不可见处理逻辑：`CanvasRenderContextImmediate::PushTask` 检测到 Canvas 不可见时会清理 RecordingCanvas 并跳过当前任务。排查时应先区分立即渲染和延迟渲染，不能将两种模式的行为混为一谈。

## 排查路径

### 快速判断

1. 获取 AppFreeze 完整调用栈，确定 `FlushTask` 的所属类，并确认调用链是否进入 Canvas 内容更新。
2. 查看 `Canvas tasks count` Trace、`Canvas task size` 日志及 `CommandSize` Dump 信息，判断绘制任务是否异常增多。
3. 统计一个 VSync 周期内应用调用 Canvas 绘制接口的次数，检查循环、重复绘制和数据量是否无上限增长。
4. 检查应用进入后台后，Canvas 动画、定时器和绘制回调是否仍在运行。
5. 对齐 Canvas 大任务执行时间与 `UI_BLOCK_6S` 事件，排除同一时段的其他 UI 线程长任务。

### 详细排查

#### 应用单帧绘制指令过多排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 展开 AppFreeze 栈中 `FlushTask` 的完整符号和上层调用 | 调用链可定位到具体类；Canvas 场景通常会进入 `CanvasPaintMethod::UpdateContentModifier` | 如果只有通用 `UITaskScheduler::FlushTask`，继续展开 RenderTask 和 PaintWrapper 栈帧 |
| 2 | 查看 `Canvas tasks count` Trace 和 `Canvas task size` 日志 | 每次刷新任务数处于稳定、可解释的范围 | 数量异常增大时继续统计应用绘制调用 |
| 3 | 统计一个 VSync 周期内的 Canvas 绘制接口调用次数 | 调用次数有明确上限，不随循环或数据规模无限增长 | 排查重复刷新、嵌套循环和多个动画源叠加 |
| 4 | 检查是否每帧重复生成未变化的绘制内容 | 静态内容不应每帧重复生成完整指令集 | 缓存静态结果或只更新发生变化的内容 |
| 5 | 限制单帧绘制量后复测 | 单帧耗时和任务数量下降，不再触发 `UI_BLOCK_6S` | 继续排查单条指令复杂度及其他 UI 线程耗时 |

关键代码定位：
- `frameworks/core/components_ng/pattern/canvas/canvas_render_context_deferred.cpp:30-38`：`PushTask` 将绘制任务加入 `tasks_`，并在任务数达到 100000 的整数倍时记录诊断信息。
- `frameworks/core/components_ng/pattern/canvas/canvas_render_context_deferred.cpp:41-53`：`NeedRender` 判断队列是否非空，`FlushTask` 遍历执行全部任务后清空队列。
- `frameworks/core/components_ng/pattern/canvas/canvas_paint_method.cpp:59-69`：`CanvasPaintMethod::PushTask` 提交任务并将 Canvas 标记为需要渲染。
- `frameworks/core/components_ng/pattern/canvas/canvas_paint_method.cpp:84-104`：`UpdateContentModifier` 检测到待渲染任务后调用 `FlushTask`。
- `frameworks/core/components_ng/pattern/canvas/canvas_modifier.cpp:120`：Dump 信息中的 `CommandSize` 可辅助判断绘制命令规模。

#### 应用后台仍持续绘制排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查应用生命周期回调中的 Canvas 动画启停逻辑 | 应用进入后台后停止动画和绘制任务提交 | 补充后台停止逻辑，并覆盖全部动画源和定时器 |
| 2 | 在后台期间统计 Canvas 绘制接口调用次数 | 进入后台后调用计数不再增长 | 定位仍在触发绘制的回调、定时器或状态监听 |
| 3 | 检查 Canvas 不可见期间是否仍执行不需要展示的绘制 | 无展示需求时不继续生成绘制任务 | 增加可见性判断并停止相应绘制入口 |
| 4 | 检查 CanvasRenderingContext2D 的 `onDetach` 回调 | 上下文解绑后停止与原 Canvas 关联的绘制 | 注册解绑回调并停止相应动画或绘制任务 |
| 5 | 恢复前台并检查首次渲染耗时和任务数量 | 不出现积压任务集中执行 | 排查遗漏的后台绘制入口或其他长任务 |

`onDetach` 表示 CanvasRenderingContext2D 与 Canvas 解绑，典型触发场景包括 Canvas 销毁或上下文重新绑定到其他 Canvas；它不等同于应用进入后台。因此应用需要分别处理：
- 应用进入后台：停止动画循环、定时器和绘制接口调用。
- Canvas 不可见：停止没有展示价值的绘制。
- CanvasRenderingContext2D 解绑：通过 `onDetach` 停止与原 Canvas 关联的绘制。
- 应用恢复前台或上下文重新绑定：重新检查状态后再恢复绘制。

公开 API 示例参见：[CanvasRenderingContext2D onDetach/off(onDetach)](https://developer.huawei.com/consumer/cn/doc/harmonyos-references/ts-canvasrenderingcontext2d#offondetach13)。

关键代码定位：
- `frameworks/core/components_ng/pattern/canvas/canvas_pattern.cpp:1113-1123`：Canvas 可见性变化传递给 PaintMethod。
- `frameworks/core/components_ng/pattern/canvas/canvas_pattern.cpp:1151-1166`：在立即渲染与延迟渲染上下文之间切换。
- `frameworks/core/components_ng/pattern/canvas/canvas_render_context_immediate.cpp:21-30`：立即渲染模式在不可见时跳过当前绘制任务。
- `frameworks/core/components_ng/pattern/canvas/canvas_pattern.cpp:95-110`：设置和触发 CanvasRenderingContext2D 解绑回调。

#### 6 秒 AppFreeze 判定排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查故障事件是否为 `UI_BLOCK_6S` | 确认属于 UI 线程冻结事件 | 按实际故障事件重新分类 |
| 2 | 对齐 AppFreeze 时间段与 Canvas Trace | 冻结时间段内存在 Canvas 大任务刷新 | 如果时间不重合，排查其他 UI 线程任务 |
| 3 | 展开 `FlushTask` 完整符号 | 能定位到具体类和调用链 | 符号不足时不能仅凭函数名判定 Canvas 是根因 |
| 4 | 完成应用侧绘制量和生命周期整改后复测 | UI 线程阻塞时间下降且不再达到 6 秒 | Canvas 绘制可能不是唯一或主要耗时来源 |

关键代码定位：
- `frameworks/core/common/watch_dog.cpp:28-30`：WatchDog 使用 3 秒、2 秒和 1 秒的分阶段检查周期。
- `frameworks/core/common/watch_dog.cpp:240-260`：线程持续无响应时由 WARNING 进入 FREEZE 状态。
- `adapter/ohos/osal/event_report.cpp:425-443`：FREEZE 状态映射为 `UI_BLOCK_6S`。
- `adapter/ohos/build/hisysevent.yaml:145-151`：`UI_BLOCK_6S` 定义为线程阻塞 6 秒。

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 应用单帧绘制指令过多 | 为每帧绘制量设置业务上限，减少重复指令，拆分或合并复杂绘制 | 应用 Canvas 绘制循环和数据遍历逻辑 | 应用侧整改 | 减少进入 Canvas 待处理队列的任务数量，从根源降低一次 `FlushTask` 的执行量 |
| 应用后台仍持续绘制 | 进入后台时停止 Canvas 动画；Canvas 不可见或上下文解绑时停止相应绘制；恢复有效状态后再启动 | 应用生命周期回调、可见性控制和 `onDetach` 回调 | 应用侧整改 | 停止无效绘制任务继续产生，避免恢复前台后集中执行 |

验证方法：
1. 为 Canvas 绘制接口增加按帧计数，确认整改后单帧指令数量受控。
2. 长时间保持应用在后台，确认 Canvas 绘制调用计数不再增长。
3. 恢复前台后检查 `Canvas tasks count`，确认没有积压任务突增。
4. 重复前后台切换、页面离开和 Canvas 销毁场景，确认动画能够正确停止和恢复。
5. 检查 UI 线程耗时及故障事件，确认不再出现 `UI_BLOCK_6S`。
6. 复核正常前台绘制结果，确保减少或拆分指令没有造成画面缺失。

仓内现有测试验证了延迟任务入队、批量刷新、立即模式可见性和上下文解绑回调等基础机制，但没有覆盖完整的应用 AppFreeze 场景：
- `test/unittest/core/pattern/canvas/canvas_render_context_test.cpp:66-76`：延迟任务入队后不会立即执行。
- `test/unittest/core/pattern/canvas/canvas_render_context_test.cpp:84-95`：多个延迟任务可以连续入队。
- `test/unittest/core/pattern/canvas/canvas_render_context_test.cpp:103-120`：`FlushTask` 执行全部任务并清空队列。
- `test/unittest/core/pattern/canvas/canvas_render_context_test.cpp:642-656`：立即渲染模式下不可见时不执行绘制任务。
- `test/unittest/core/pattern/canvas/canvas_test_ng.cpp:466-488`：CanvasRenderingContext2D 解绑回调。

## 关联变更

本问题是高频应用问题咨询的经验总结，整改全部发生在应用侧，不对应 ace_engine 底座 Issue、PR 或 Commit。

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| — | 不适用：无底座变更 | 应用单帧绘制过多、应用后台持续绘制 | 不适用 | 用户确认整改均发生在应用侧 | user_claimed |

## 预防措施

- 为每帧 Canvas 绘制接口调用次数和处理的数据规模设置明确上限。
- 避免在动画循环中重复绘制没有变化的静态内容。
- 将复杂绘制拆分到多个渲染帧，或合并能够批处理的绘制操作。
- 应用进入后台时停止定时器、动画回调和 Canvas 绘制。
- Canvas 不可见、页面离开或 CanvasRenderingContext2D 解绑时停止关联绘制任务。
- 恢复绘制前重新检查应用前台状态、Canvas 可见性和上下文绑定状态。
- 性能回归测试覆盖长时间动画、前后台切换、页面销毁重建及大数据量绘制。
- 采集 AppFreeze 时保留完整符号栈，不能仅根据 `FlushTask` 函数名判断根因。
- 监控 `Canvas tasks count`、`Canvas task size`、`CommandSize` 和 `CANVAS_TASKS_OVERFLOW`，及时发现绘制任务异常增长。
- 将 `UI_BLOCK_6S` 作为框架冻结判定边界，不把它误写为 Canvas 自身的绘制超时。

## 相关主题

- `docs/kb/components/shape/canvas.md`
- Canvas 功能域：`05-14-02`
- Canvas Spec：`specs/05-ui-components/14-drawing-components/02-canvas/`（当前目录尚未建立，行为以源码、测试及公开 API 文档为准）
- [CanvasRenderingContext2D onDetach/off(onDetach)](https://developer.huawei.com/consumer/cn/doc/harmonyos-references/ts-canvasrenderingcontext2d#offondetach13)
