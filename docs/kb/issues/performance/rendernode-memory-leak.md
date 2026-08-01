# RenderNode 内存泄漏 Issue Context

> 文档版本：v1.1
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `RenderNodeMemoryLeak`
> 关联功能域：C API RenderNode

## 问题概述

C API RenderNode 采用双层内存模型（外层 `ArkUI_RenderNode` + 内层 `RenderNodeStruct`），`OH_ArkUI_RenderNodeUtils_DisposeNode` 只释放了外层结构体，未释放内层 `RenderNodeStruct`，导致每次创建-销毁 RenderNode 都会泄漏一个 `RenderNodeStruct` 对象（含 `shared_ptr<RSNode>` 及相关字段）。长期运行或频繁创建/销毁 RenderNode 的场景下，内存持续增长。

双层内存模型说明：
- 外层 `ArkUI_RenderNode`（`render_node.h:27-29`）：仅含 `ArkUIRenderNodeHandle renderNodeHandle` 字段，`ArkUIRenderNodeHandle` 即 `RenderNodeStruct*` 的类型别名
- 内层 `RenderNodeStruct`（`node_render_node_modifier.cpp:65-70`）：含 `shared_ptr<RSNode> rsNode`、`int32_t nodeId`、`bool getFromAdoptedFrameNode`、`bool getFromNativeFrameNode`，通过 `new RenderNodeStruct` 创建

典型表现：
- 频繁调用 `OH_ArkUI_RenderNodeUtils_CreateNode` / `DisposeNode` 后内存持续增长
- 通过 `GetChild`/`GetFirstChild`/`GetNextSibling` 等方法获取子节点后调用 `DisposeNode`，内存不回收
- 长时间运行的 C API 应用中，RenderNode 相关内存占用量单调递增

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| DisposeNode 未释放内层 RenderNodeStruct | 调用 `OH_ArkUI_RenderNodeUtils_DisposeNode` 销毁 RenderNode | `DisposeNode` 只 `delete` 了外层 `ArkUI_RenderNode`，内层 `renderNodeHandle` 指向的 `RenderNodeStruct`（通过 `new RenderNodeStruct` 创建）未被释放 |
| GetChild/GetFirstChild 等返回的 RenderNodeStruct 泄漏 | 通过 C API 获取子节点/兄弟节点后调用 `DisposeNode` | 与上条同根因（`DisposeNode` 未释放内层），触发入口不同：`GetChild`、`GetFirstChild`、`GetNextSibling`、`GetPreviousSibling`、`GetChildren` 等方法内部调用 `CreateRenderNodeStruct` 创建内层结构体，`DisposeNode` 同样未释放 |

所有创建 `RenderNodeStruct` 的泄漏入口（`render_node.cpp`）：

| API 方法 | 行号 | 泄漏机制 |
|----------|------|----------|
| `OH_ArkUI_RenderNodeUtils_CreateNode` | 134-146 | `new ArkUI_RenderNode({ renderNode })`，`renderNode` 由 `CreateRenderNodeStruct` 创建 |
| `OH_ArkUI_RenderNodeUtils_GetChild` | 238-264 | `*child = new ArkUI_RenderNode({ renderNode })`，`renderNode` 由 modifier 的 `getChild` 返回（内部调用 `CreateRenderNodeStruct`） |
| `OH_ArkUI_RenderNodeUtils_GetFirstChild` | 266-287 | 同上模式 |
| `OH_ArkUI_RenderNodeUtils_GetNextSibling` | 289-308 | 同上模式 |
| `OH_ArkUI_RenderNodeUtils_GetPreviousSibling` | 312-333 | 同上模式 |
| `OH_ArkUI_RenderNodeUtils_GetChildren` | 335-368 | 批量创建：`childrenList[i] = new ArkUI_RenderNode({ renderNode[i] })`，每个都泄漏内层 |

## 排查路径

### 快速判断

1. 确认应用是否使用 C API RenderNode（`OH_ArkUI_RenderNodeUtils_*`）
2. 检查是否存在 CreateNode/DisposeNode 的频繁调用循环
3. 通过内存分析工具（如 `hidumper`、`DevEco Profiler`）观察 `RenderNodeStruct` 对象数量是否持续增长
4. 检查 `DisposeNode` 调用后内存是否未回收

### 详细排查

#### DisposeNode 未释放内层 RenderNodeStruct 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `DisposeNode` 中确认是否调用了 `deleteInnerRenderNodeStruct` | 修复后应调用 | 如果未调用，说明使用的是修复前的版本 |
| 2 | 检查 `ArkUINDKRenderNodeModifier` 结构体中是否注册了 `deleteInnerRenderNodeStruct` 字段 | 修复后应有该字段 | 缺失则说明 arkoala_api.h 未更新 |
| 3 | 检查 `DisposeNode` 中 `renderNodeHandle` 是否在释放后置空 | 修复后应置空 | 未置空可能导致 use-after-free |

关键代码定位：
- `interfaces/native/node/render_node.cpp:148-168`：`OH_ArkUI_RenderNodeUtils_DisposeNode` 实现
- `frameworks/core/interfaces/native/node/node_render_node_modifier.cpp:65-70`：`RenderNodeStruct` 定义（含 `shared_ptr<RSNode>`、`nodeId`、`getFromAdoptedFrameNode`、`getFromNativeFrameNode`）
- `frameworks/core/interfaces/native/node/node_render_node_modifier.cpp:242-257`：`CreateRenderNodeStruct` 通过 `new RenderNodeStruct` 创建内层结构体
- `frameworks/core/interfaces/native/node/node_render_node_modifier.cpp:2462-2467`：`DeleteInnerRenderNodeStruct` 释放内层结构体
- `interfaces/native/node/render_node.h:27-29`：`ArkUI_RenderNode` 外层结构体定义（仅含 `renderNodeHandle` 字段）

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| DisposeNode 未释放内层 RenderNodeStruct | 新增 `deleteInnerRenderNodeStruct` 函数，在 `DisposeNode` 中先释放内层再释放外层 | `arkoala_api.h` 新增函数指针字段；`node_render_node_modifier.cpp` 新增 `DeleteInnerRenderNodeStruct` 实现；`render_node.cpp` 在 `DisposeNode` 中调用 | d452e978454bc8838c5d7e5b09eb2793877d0057 (fixed) | commit diff: 3 文件 +13 行 |

核心修复代码：
```cpp
// node_render_node_modifier.cpp:2462-2467 — 新增释放函数
void DeleteInnerRenderNodeStruct(ArkUIRenderNodeHandle node)
{
    auto* nodeStruct = reinterpret_cast<RenderNodeStruct*>(node);
    CHECK_NULL_VOID(nodeStruct);
    delete nodeStruct;
}

// render_node.cpp:148-168 — DisposeNode 中调用
int32_t OH_ArkUI_RenderNodeUtils_DisposeNode(ArkUI_RenderNodeHandle node)
{
    // ...参数校验...
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->deleteInnerRenderNodeStruct(node->renderNodeHandle);
    // deleteInnerRenderNodeStruct does not set node->renderNodeHandle to nullptr  (render_node.cpp:162)
    node->renderNodeHandle = nullptr;  // 防止 use-after-free
    delete node;
    node = nullptr;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}
```

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 新增 deleteInnerRenderNodeStruct 并在 DisposeNode 中调用 | DisposeNode 未释放内层 RenderNodeStruct | fixed | commit d452e978 diff: +13 行 | verified |

## 预防措施

- C API 中新增双层内存模型时，`Dispose` 函数必须同时释放内层和外层结构体
- 代码审查时重点检查 C API 中 `new`/`delete` 的配对，特别是跨层结构体（外层持有内层指针）
- 建议对 C API RenderNode 的生命周期管理增加内存泄漏自动化测试
- `GetChild`/`GetFirstChild`/`GetNextSibling`/`GetPreviousSibling`/`GetChildren` 返回的 `ArkUI_RenderNode` 均需通过 `DisposeNode` 释放，且 `DisposeNode` 必须调用 `deleteInnerRenderNodeStruct` 释放内层
- 注意 `render_node.cpp:162` 的注释：`deleteInnerRenderNodeStruct` 不会将 `renderNodeHandle` 置空，调用方必须在 `deleteInnerRenderNodeStruct` 后手动置空 `node->renderNodeHandle` 以防止 use-after-free

## 相关主题

- [基础渲染管线](../../architecture/basic-render-pipeline.md)：基础渲染管线 KB
- [RenderNode](../../capabilities/render_node.md)：RenderNode 绘制节点，与 FrameNode 共享 RS 节点树重建机制
