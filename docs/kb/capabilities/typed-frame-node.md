# TypedFrameNode Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `TypedFrameNode`

## 定位

本主题的主角是 **ArkTS 的 `TypedFrameNode` 接口/抽象类 + `typeNode` 工厂命名空间**——类型化的 FrameNode，通过 typeNode.createNode/createXxxNode 创建，提供类型化的 attribute/event/controller 句柄。它覆盖 40 个内置组件的类型化扩展，是功能域 `04-06-07` 的规格对象。

边界：`TypedFrameNode extends FrameNode`；FrameNode 基类方法属 04-06-02，本域只覆盖类型化扩展（initialize/attribute + typeNode 工厂）。

行为事实以 SDK（`FrameNode.d.ts`/`.static.d.ets` 的 TypedFrameNode + typeNode 部分）、ArkTS 实现（`frame_node.ts`）、测试与长期规格为准；本页仅作路由导航。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **ArkTS 运行时（主角）** | `frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts` | TypedFrameNode class（attribute 懒创建）+ typeNode class（createNode/getAttribute/getEvent/bindController 全 TS）+ 4 dispatch map（creator/attribute/event/bindController） |
| **JSI Bridge（创建路径）** | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.cpp` | CreateTypedFrameNode + HandleNodeParams（typeMap 40 组件）；getAttribute/getEvent/bindController 无独立 C++ bridge（纯 TS） |
| **C++ NG 底层（仅终端）** | `getBasicAPI()->createNode(nodeType)` | 按 nodeType 创建 NG FrameNode。深入时再查 |

> 注：getAttribute/getEvent/bindController 完全在 TS 实现（经 dispatch map + 各组件 native modifier），不经独立 C++ bridge。

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 动态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.d.ts` | TypedFrameNode 接口 + typeNode 命名空间（string-literal 重载，40 组件） |
| **SDK 静态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.static.d.ets` | TypedFrameNode 抽象类 + typeNode 命名空间（命名函数 createXxxNode，40 组件） |
| 模块入口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.d.ts` | re-export typeNode |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| C-API 单测 | `test/unittest/capi/accessors/frame_node_extended_accessor_test.cpp` | createTypedFrameNode（40 组件 tag 校验） |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/06-custom-node/07-typed-frame-node/design.md` | Baselined |
| Feat-01 TypedFrameNode 类型 | `specs/04-common-capability/06-custom-node/07-typed-frame-node/Feat-01-typedframenode-type-spec.md` | Baselined |
| Feat-02 typeNode 动态工厂 | `specs/04-common-capability/06-custom-node/07-typed-frame-node/Feat-02-typenode-dynamic-factory-spec.md` | Baselined |
| Feat-03 typeNode 静态工厂 | `specs/04-common-capability/06-custom-node/07-typed-frame-node/Feat-03-typenode-static-factory-spec.md` | Baselined |
| Feat-04 组件支持矩阵 | `specs/04-common-capability/06-custom-node/07-typed-frame-node/Feat-04-component-matrix-spec.md` | Baselined |


## 调试入口

- 核心断点：在 `frame_node` 的关键方法设置断点，观察状态变化
- 触发链路：从 `**ArkTS 运行时（主角）**` 入口追踪调用链到核心实现
- 回归验证：运行 `test/unittest/capi/accessors/frame_node_extended_accessor_test.cpp` 下定向用例

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| getAttribute 返回 undefined | nodeType 不匹配。见 Feat-02 R-4 |
| bindController 抛 401/100021/100023 | 非法 node/type/controller 或跨语言失败。见 Feat-02 R-7 |
| 40 组件 createNode 版本 | 分波 12/14/18。见 Feat-04 R-1..R-3 |
| accessor 版本分波 | 动态 15/19/20、静态 23/24/26。见 Feat-04 R-4..R-7 |
| XComponent 3 重载 | bare/options/parameters。见 Feat-04 R-8 |
| 动态/静态范式差异 | 动态 string-literal 重载，静态命名函数。见 Feat-02/03 |
| attribute 懒创建 | 首次访问构造 ArkComponent。见 Feat-01 R-3 |

## 相关主题

- [FrameNode](./frame-node.md) — TypedFrameNode 的基类（04-06-02）