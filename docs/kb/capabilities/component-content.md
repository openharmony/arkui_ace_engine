# ComponentContent Context

> 文档版本：v1.1
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ComponentContent`

## 定位

本主题的主角是 **ArkTS 的 `ComponentContent` 类**——组件内容实体封装（`extends Content`），底层实现用 BuilderNode。它承载创建（constructor 3 重载）、释放、更新、复用回收、ReactiveComponentContent 响应式变体、Transfer 转换变体（只读，抛 100031），是功能域 `04-06-05` 的规格对象。

> 边界说明：`NodeContent` 与 `ComponentContent` 是兄弟（均 `extends Content`），不属于本功能域，本页不覆盖。

行为事实以 SDK（`ComponentContent.d.ts`/`.static.d.ets`/`Content.d.ts`）、ArkTS 实现（`component_content.ts`）、测试与长期规格为准；本页仅作路由导航。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **ArkTS 运行时（主角）** | `frameworks/bridge/declarative_frontend/ark_node/src/component_content.ts` | ComponentContent/ComponentContentCommonBase/ReactiveComponentContent：创建(内部建 BuilderNode)、dispose、update、reuse/recycle、isDisposed/isTransferred |
| Content 基类 | `frameworks/bridge/declarative_frontend/ark_node/src/content.ts` | `Content` 抽象基类（ComponentContent/ReactiveComponentContent 的父类） |
| Transfer 变体 | `frameworks/bridge/declarative_frontend/ark_node/src/trans_component_content.ts` | Trans 变体：isTransferred=true，变更 API 抛 100031 |

> 注：ComponentContent 无独立 native modifier，native ops 折叠进 frame_node native module（fireArkUIObjectLifecycleCallback 等），创建/更新/复用/释放均委托内部 BuilderNode（见 [BuilderNode KB](./builder-node.md)）。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 动态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/ComponentContent.d.ts` | ComponentContent + ReactiveComponentContent |
| **SDK 静态** | `<OH_ROOT>/interface/sdk-js/api/arkui/ComponentContent.static.d.ets` | 静态 ComponentContent + ComponentContentBase |
| Content 基类 | `<OH_ROOT>/interface/sdk-js/api/arkui/Content.d.ts` | `Content` 抽象基类 |
| 模块入口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.d.ts` | re-export Content/ComponentContent/ReactiveComponentContent |

### 测试入口

> 无独立 component_content 单测；ComponentContent 行为经内部 BuilderNode 间接覆盖（见 BuilderNode/node_container 测试）。

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/06-custom-node/05-component-content/design.md` | Baselined |
| Feat-01 创建与释放 | `specs/04-common-capability/06-custom-node/05-component-content/Feat-01-creation-dispose-spec.md` | Baselined |
| Feat-02 更新配置冻结 | `specs/04-common-capability/06-custom-node/05-component-content/Feat-02-update-config-freeze-spec.md` | Baselined |
| Feat-03 复用回收 | `specs/04-common-capability/06-custom-node/05-component-content/Feat-03-reuse-recycle-spec.md` | Baselined |
| Feat-04 ReactiveComponentContent | `specs/04-common-capability/06-custom-node/05-component-content/Feat-04-reactive-component-content-spec.md` | Baselined |
| Feat-05 Transfer 转换变体 | `specs/04-common-capability/06-custom-node/05-component-content/Feat-05-transfer-dynamic-static-conversion-spec.md` | Baselined |


## 调试入口

- 核心断点：在 `component_content` 的关键方法设置断点，观察状态变化
- 触发链路：从 `**ArkTS 运行时（主角）**` 入口追踪调用链到核心实现

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Trans 变体抛 100031 | 转换产生节点只读。见 Feat-05 |
| 静态无 inheritFreezeOptions | 动态/静态差异。见 Feat-02 |
| 静态 ReactiveCC 无 update + ctor 不同 | 动态/静态差异。见 Feat-04 |
| 内部用 BuilderNode | update/reuse/recycle/dispose 委托。见 Feat-01..04 |
| 未释放前端引用泄漏 | SDK 警告。见 Feat-01 |

## 相关主题

- [BuilderNode](./builder-node.md) — ComponentContent 内部用 BuilderNode 实现
- [FrameNode](./frame-node.md) — getFrameNode 关联的节点类型