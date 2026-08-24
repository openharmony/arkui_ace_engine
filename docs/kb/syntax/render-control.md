# Render Control Syntax Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `RenderControl`

## 定位

渲染控制语法（FuncID `07-05-01`）覆盖 ArkUI 声明式渲染控制中的 `if/else` 条件渲染、`ForEach` 循环渲染，以及这两类与 `LazyForEach`/`Repeat` 共享的语法节点框架（`ForEachBaseNode`）。`LazyForEach`（07-05-02）与 `Repeat`（07-05-03）为独立功能域，本页不展开它们的懒渲染细节。

关键要点：`if/else` 在 dynamic 范式为**纯语法**（无公开 callable，由 ArkTS 编译器转译），仅 static `@since26` 暴露 `If/ElseIf/Else` callable。`ForEach` 为 id-based diff（`@since7`）。所有循环节点继承 `ForEachBaseNode`，`IfElseNode` 直接继承 `UINode`（仅共享 `IsSyntaxNode` 标记）。具体行为、默认值以对应 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| if/else 节点 | `frameworks/core/components_ng/syntax/if_else_node.cpp`、`.h` | `IfElseNode : UINode`；`SetBranchId` / `branchIdChanged_` / `Clean` / `CollectCleanedChildren` / `TryRetake` |
| ForEach 节点 | `frameworks/core/components_ng/syntax/for_each_node.cpp`、`.h` | `ForEachNode`：id-based diff（`CompareAndUpdateChildren` / `MappingChildWithId`）、`FlushUpdateAndMarkDirty` no-op 守卫、`MoveData` |
| 共享基类 | `frameworks/core/components_ng/syntax/for_each_base_node.h` | `ForEachBaseNode : UINode`（纯虚 `MoveData` / `GetFrameNode`、onMove/drag virtuals、`DisableRecycle`、`IsSyntaxNode`）；`UINode::IsSyntaxNode` 标记 |
| if/else Model | `frameworks/core/components_ng/syntax/if_else_model_ng.cpp`、`if_else_model.h` | Create / Pop / `SetBranchId` / `CanRetake` |
| ForEach Model | `frameworks/core/components_ng/syntax/for_each_model_ng.cpp` | Create / `SetNewIds` / `CreateNewChildStart/Finish` / `OnMove` |
| JS 桥接 | `frameworks/bridge/declarative_frontend/jsview/js_if_else.cpp`（`JSIfElse`）、`js_foreach.cpp`（`JSForEach`） | 绑定 + NG/legacy 管线选择 |
| TS 分支/diff 驱动 | `frameworks/bridge/declarative_frontend/state_mgmt/.../puv2_view_buildnode_base.ts`（`ifElseBranchUpdateFunction`）、`puv2_view_base.ts`（ForEach diff / keyGen） | TS 侧分支选择 / id diff |
| C-API（Arkoala）节点 | `frameworks/core/components_ng/syntax/arkoala_condition_scope.*`（if/else `ConditionScopeNode`）、`arkoala_for_each_node.*`（`ArkoalaForEachNode`） | Arkoala / C-API 对应节点（不做 C++ 分支 diff，分支由 Arkoala 侧先决） |
| 父容器 | `frameworks/core/components_ng/base/frame_node.cpp`（`ChildrenUpdatedFrom` / dirty） | 分支 / 列表变更通知父重测量 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Static if/else callable | `<OH_ROOT>/interface/sdk-js/api/arkui/component/if.static.d.ets` | `If` / `IfAttribute.ElseIf` / `Else`（`@since26`）；dynamic if 无公开 callable |
| Dynamic ForEach | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/for_each.d.ts` | `ForEach(arr, itemGen, keyGen?)`（`@since7`） |
| Static ForEach | `<OH_ROOT>/interface/sdk-js/api/arkui/component/forEach.static.d.ets` | `@since23`，`@since26 staticonly` style-builder |

API 检索建议：在 SDK 中搜索 `ForEach`、`ForEachAttribute`、`If`、`IfAttribute`、`ElseIf`；dynamic if 仅在 ArkTS 语言层，SDK 无 callable 声明。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/syntax/for_each_syntax_test_ng.cpp`、`for_each_test_ng_ai.cpp` | ForEach id-diff / MoveData / 脏标记 |
| UT | `test/unittest/core/syntax/arkoala_for_each_test_ng.cpp`、`arkoala_for_each_test_ng_ai.cpp` | C-API（Arkoala）ForEach 节点 |
| TS 单测 | state-mgmt 单测（`ifElseBranchUpdateFunction` / ForEach diff） | TS 分支 / diff |
| XTS | `test/xts` | static 范式 If/ElseIf/Else、ForEach 端到端 |
| Spec 功能域 | `specs/07-frontend/05-render-control/01-render-control-syntax/` | 设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `07-05-01` 功能域注册入口 |

### 相关 Spec

渲染控制语法功能域：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | if/else 条件渲染语法（基线） | `Feat-01-if-else-conditional-rendering-spec.md` |
| Feat-02 | ForEach 循环渲染语法 | `Feat-02-foreach-loop-rendering-spec.md` |
| Feat-03 | 渲染控制语法共享框架 | `Feat-03-shared-syntax-node-framework-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| if/else 分支切换未重测量 | `if_else_node.cpp` `FlushUpdateAndMarkDirty`（仅 `BY_CHILD_REQUEST`，经 `ChildrenUpdatedFrom(0)` 间接触发父重测量） |
| 跨分支状态未保留 | `if_else_node.cpp` `TryRetake`（按 (id, 当前 branchId_) 查 disappearing 子） |
| ForEach 重排/交换渲染错位 | `for_each_node.cpp` id-based diff；`keyGen` 须唯一稳定（重复 key 抛 applicationError） |
| ForEach 脏标记与 if/else 不同 | ForEach 用 `MEASURE_SELF_AND_PARENT\|BY_CHILD_REQUEST`，if/else 仅 `BY_CHILD_REQUEST` |
| C-API（Arkoala）if/else 分支未切换 | `arkoala_condition_scope.cpp`（不做 C++ 分支 diff，分支由 Arkoala 侧先决） |
| ForEach / Repeat 共用类问题 | 历史 `isThisRepeatNode_` 共用机制**已废弃**，勿基于此新开发（详见 07-05-03） |

## 调试入口

- if/else 链路：ArkTS 编译器转译 → TS `ifElseBranchUpdateFunction` → `If.branchId` → `IfElseNode::SetBranchId` → `Clean` + `CollectCleanedChildren`。
- ForEach 链路：TS `forEachUpdateFunction` → `ForEach.setIdArray` → `ForEachNode` id-diff（新/重排/移除三态）。
- 多管线选择：`*Model::GetInstance()` 经 `NG_BUILD` / `IsCurrentUseNewPipeline()` 选 NG `*ModelNG` 或 legacy `*ModelImpl`。

## 相关主题

- [LazyForEach](lazy-for-each.md)
- [Repeat](repeat.md)
- [组件复用框架（`ForEachBaseNode::DisableRecycle`）：component-reuse-framework](../architecture/component-reuse-framework.md)