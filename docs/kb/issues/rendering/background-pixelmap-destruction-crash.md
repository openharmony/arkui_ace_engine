# Background 截图场景 FrameNode 析构崩溃 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `BackgroundPixelmapDestructionCrash`
> 关联功能域：04-10-01、04-03-10

## 问题概述

背景截图（`CreateBackgroundPixelMap`）流程中，截图完成回调在外层 lambda 提前将 `WeakPtr` Upgrade 为强 `RefPtr<FrameNode>` 并按值捕获进投递到 UI 线程的 task。task 在投递与执行之间持有了本应下树销毁的 FrameNode 强引用，导致节点析构时序错乱，在 UI 线程执行 task 时触发析构异常崩溃。

典型表现：
- 触发组件背景截图（`createFromBuilder`/`createFromComponent` 等）后，目标节点被移除时出现崩溃
- 崩溃堆栈指向 `RosenRenderContext::CreateBackgroundPixelMap` 的 task 回调，伴随 FrameNode 析构/RenderContext 访问
- 节点已下树、但截图异步回调未完成时概率性触发

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | symptom_surface | RosenRenderContext 背景截图回调（CreateBackgroundPixelMap） | task 内访问 frameNode->GetRenderContext() 触发崩溃 | verified |
| architecture | root_cause_owner | 截图完成回调的强引用捕获方式 | commit diff：外层 lambda 提前 Upgrade 并按值捕获 frameNode | verified |
| architecture | fix_location | RosenRenderContext::CreateBackgroundPixelMap | commit c9e05079d058c6f78c90d18f86c5ec5dcb6ceb7a diff | verified |

kind: `component` / `capability` / `architecture`
role: `symptom_surface` / `trigger` / `root_cause_owner` / `fix_location` / `dependency`

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 异步回调提前 Upgrade 并按值捕获强引用 | 外层回调在快照完成线程 `weak.Upgrade()` 得到强 RefPtr，并按值捕获进投递到 UI 线程的 task | FrameNode 在截图完成前已下树，task 的强引用使节点延后到 UI 线程 task 执行点才析构，析构时序与状态非预期，导致析构异常崩溃 |

## 排查路径

### 快速判断

1. 确认崩溃堆栈是否位于 `RosenRenderContext::CreateBackgroundPixelMap` 的 task 回调（标签 `ArkUICreateBackgroundPixelMap`）
2. 确认崩溃前是否触过组件背景截图 / 组件截图，且目标节点在截图完成前被下树/销毁
3. 检查 `CreateBackgroundPixelMap` 内层 task 捕获的是 `weak`（WeakPtr）还是 `frameNode`（强 RefPtr）
4. 若 task 捕获强 RefPtr，即命中根因

### 详细排查

#### 异步回调提前 Upgrade 并按值捕获强引用 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 查看 `CreateBackgroundPixelMap` 外层 JsCallback 中 `weak.Upgrade()` 的位置 | 应在投递到 UI 线程的 task 内部执行 Upgrade | 若在外层 lambda 执行，则强引用被 task 捕获 |
| 2 | 查看内层 task 的捕获列表 | 应捕获 `weak`（WeakPtr），不应捕获 `frameNode`（RefPtr） | 捕获 `frameNode` 即强引用跨异步边界 |
| 3 | task 内 Upgrade 后是否有 `CHECK_NULL_VOID(frameNode)` | 节点已销毁时应安全返回 | 缺失则继续访问已析构节点 |
| 4 | 复现时确认节点是否在 task 投递后、执行前被下树 | task 不应延长节点生命周期 | 命中即此根因 |

关键代码定位：
- `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`：`RosenRenderContext::CreateBackgroundPixelMap`，外层 JsCallback + 内层 task
- `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`：修复后 task 捕获 `weak`（WeakPtr），原修复前捕获 `frameNode`（强 RefPtr）
- `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`：修复后将 `weak.Upgrade()` + `CHECK_NULL_VOID` 移入 task 内部
- `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`：task 经 `TaskExecutor::TaskType::UI` 投递，标签 `ArkUICreateBackgroundPixelMap`

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 异步回调提前 Upgrade 并按值捕获强引用 | 将 `weak.Upgrade()` + 空指针检查从外层 lambda 下沉到内层 task；task 捕获 `weak`（WeakPtr）而非 `frameNode`（强 RefPtr） | `rosen_render_context.cpp` CreateBackgroundPixelMap 的 task 捕获与 Upgrade 位置 | c9e05079d058c6f78c90d18f86c5ec5dcb6ceb7a (fixed) | commit diff：`auto frameNode = weak.Upgrade()` 从外层移入 task，捕获列表 `frameNode` 改为 `weak` |

修复前（问题代码）：
```cpp
[weak = WeakPtr(GetHost()), containerId, backgroundTaskId](
    ..., std::function<void()> finishCallback) {
    CHECK_NULL_VOID(pixmap);
    auto frameNode = weak.Upgrade();          // 外层提前 Upgrade
    CHECK_NULL_VOID(frameNode);               // 外层判空
    ...
    auto task = [pixelmap, frameNode, containerId, backgroundTaskId]() {  // 按值捕获强 RefPtr
        ContainerScope scope(containerId);
        auto context = frameNode->GetRenderContext();   // task 执行时访问
        ...
    };
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, ...);  // 跨线程投递
};
```

修复后：
```cpp
[weak = WeakPtr(GetHost()), containerId, backgroundTaskId](
    ..., std::function<void()> finishCallback) {
    CHECK_NULL_VOID(pixmap);
    ...
    auto task = [pixelmap, weak, containerId, backgroundTaskId]() {  // 捕获 WeakPtr
        ContainerScope scope(containerId);
        auto frameNode = weak.Upgrade();     // 在 task 内 Upgrade
        CHECK_NULL_VOID(frameNode);          // 节点已销毁则安全返回
        auto context = frameNode->GetRenderContext();
        ...
    };
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, ...);
};
```

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | CreateBackgroundPixelMap 的 task 改为捕获 WeakPtr 并在内部延迟 Upgrade | 异步回调提前 Upgrade 并按值捕获强引用 | fixed | commit c9e05079d058c6f78c90d18f86c5ec5dcb6ceb7a diff | verified |

## 预防措施

- 跨异步任务边界（`PostTask`）传递节点引用时，统一捕获 `WeakPtr`，在 task 内部 `Upgrade()` + 空指针检查，禁止按值捕获强 `RefPtr<FrameNode>`
- 截图/快照类异步回调（`ComponentSnapshot`）涉及节点生命周期时，遵循"延迟 Upgrade"模式，避免延长节点生命周期到非预期线程/时序
- 代码审查重点：任何 `PostTask` 的 lambda 捕获列表中是否出现 `RefPtr`/`FrameNode` 强引用
- FrameNode 析构异常类崩溃，优先排查异步回调中的强引用捕获与时序竞态

## 相关主题

- [docs/kb/capabilities/component-screenshot.md](../../capabilities/component-screenshot.md)：组件截图代码型 KB（FuncID 04-10-01，含 ComponentSnapshot）
- [docs/kb/capabilities/background-image.md](../../capabilities/background-image.md)：背景图片通用属性代码型 KB（FuncID 04-03-10，含 background pixelmap/render context）
- [docs/kb/architecture/render-tree-sync.md](../../architecture/render-tree-sync.md)：渲染树同步架构 KB（FrameNode 生命周期与上下树）