# Placeholder Component Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `PlaceholderComponent`

## 定位

「占位组件」（FuncID `04-06-01`）是 04-06 自定义节点族的**概念入口**，指在声明式节点树中为命令式 / custom 节点提供挂载位置的组件。本功能域在 `ace_engine` 中**无独立实现**，实际能力由组件层两个功能域承载：

- `05-16-01 NodeContainer`：基于 FrameNode 的渲染宿主 + 纯 TS `NodeController` + 命令式节点桥接。
- `05-16-02 ContentSlot`：基于 UINode 的轻量语法节点 + `NodeContent` 多子节点管理。

本页仅作 SDD 路由转跳，不重复规格。具体行为、API 契约、AC/规则以两个引用域的 design.md / Feat-*.md 及对应源码、SDK 声明、测试为准。

## 快速路由

### 源码入口

占位组件无独立 04-06 源码；按使用场景转跳：

| 场景 | 实现域 | 稳定路径 |
|------|--------|----------|
| 单根命令式节点（FrameNode）宿主 | NodeContainer（05-16-01） | `frameworks/core/components_ng/pattern/node_container/` |
| 多子节点命令式内容管理 | ContentSlot（05-16-02） | `frameworks/core/components_ng/syntax/content_slot_node.*`、`frameworks/core/components_ng/syntax/node_content.*` |

### API 入口

| 范式 | 实现域 | 稳定路径 |
|------|--------|----------|
| Dynamic `NodeContainer` / `NodeController` | 05-16-01 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/node_container.d.ts`、`<OH_ROOT>/interface/sdk-js/api/arkui/NodeController.d.ts` |
| Dynamic `ContentSlot` / `NodeContent` | 05-16-02 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/content_slot.d.ts`、`<OH_ROOT>/interface/sdk-js/api/arkui/NodeContent.d.ts` |
| Static 对应声明 | 05-16-01 / 05-16-02 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/nodeContainer.static.d.ets`、`contentSlot.static.d.ets`、`NodeController.static.d.ets`、`NodeContent.static.d.ets` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| NodeContainer UT | `test/unittest/core/pattern/node_container/` | NodeContainer Pattern/NodeController 桥接/NodeAdapter |
| ContentSlot UT | `test/unittest/core/syntax/content_slot_syntax_test_ng.cpp` | ContentSlotNode / NodeContent 内容管理 |
| Spec 功能域 | `specs/05-ui-components/16-custom-placeholder-components/01-node-container/`、`specs/05-ui-components/16-custom-placeholder-components/02-content-slot/` | 引用域设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `04-06-01` 概念入口 + `05-16-01/02` 实现域注册 |

### 相关 Spec

占位组件功能域（交叉引用域，不重复规格）：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 占位组件交叉引用 | `specs/04-common-capability/06-custom-node/01-placeholder-component/Feat-01-placeholder-component-cross-reference-spec.md` |

实现域规格分别见 `05-16-01` 与 `05-16-02`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 需要单根命令式节点挂载 | 转跳 05-16-01 NodeContainer |
| 需要多子节点命令式内容管理 | 转跳 05-16-02 ContentSlot |
| 想了解概念边界（FrameNode vs UINode 宿主） | 两域 design.md「与 NodeContainer/ContentSlot 边界」 |

## 调试入口

- 概念入口与转跳依据见本域 design.md「需求基线」「不涉及项承接」。
- 实际行为调试请进入 NodeContainer（`05-16-01`）或 ContentSlot（`05-16-02`）KB。

## 相关主题

- [NodeContainer：[docs/kb/components/custom-node/node-container.md](../components/custom-node/node-container.md)](../components/custom-node/node-container.md)
- [ContentSlot：[docs/kb/components/custom-node/content-slot.md](../components/custom-node/content-slot.md)](../components/custom-node/content-slot.md)
- [NodeAdapter：[docs/kb/capabilities/node-adapter.md](node-adapter.md)](node-adapter.md)
- [组件复用框架：[docs/kb/architecture/component-reuse-framework.md](../architecture/component-reuse-framework.md)](../architecture/component-reuse-framework.md)