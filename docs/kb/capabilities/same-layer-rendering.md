# Same-Layer Rendering Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `SameLayerRendering`

## 定位

「同层渲染」（FuncID `04-18-01`，spec 域 `04-common-capability/18-on-device-rendering/01-same-layer-rendering`）指把一个 ArkUI 子树渲染为纹理、再以 buffer 生产者身份投递给持有 `surfaceId` 的消费者 surface 的机制。本页**严格限定在生产者侧**（与 spec Feat-01 一致）：

- **本页覆盖（生产者）**：`BuilderNode(uiContext, { surfaceId, type: NodeRenderType.RENDER_TYPE_TEXTURE })` 触发 → 子树 RSNode 以纹理导出节点身份创建 → 子树从主 RS 显示树分离 → 连同 `surfaceId` 交付 `Rosen::RSTextureExport`。**ace_engine 的职责到此为止**。
- **本页不覆盖（消费者 / 跨仓，仅作边界声明，不展开路由）**：① 消费者行为（开启 `NativeEmbedMode` 的 Web、应用开发者用 XComponent 自绘制并持有 surface）；② 跨仓 Rosen（graphic_2d）内部 `RSUIDirector` 渲染线程合成与 BufferQueue 生产/消费时序；③ XComponent 作为并行生产者宿主（与 NodeContainer 共享同一 `RSTextureExport` 机制，仅交叉引用）。

公开触发入口为存量补录（`@since 11 dynamic` / `@atomicservice 12`），无新增 API。行为事实以源码、SDK 声明、测试和 spec 为准；本页只作上下文导航，不重复规格与调用链。

## 快速路由

### 源码入口

生产者侧按职责分层，稳定路径如下（勿依赖行号，行号随 PR 漂移）：

| 层 | 职责 | 稳定路径 |
|----|------|----------|
| 触发入口（ArkTS） | 解析 `RenderOptions.{type,surfaceId}`；build 时置 `SetIsExportTexture`；build 后按 tag 白名单 attach `ExportTextureInfo` | `frameworks/bridge/declarative_frontend/jsview/js_base_node.cpp`、`js_base_node.h` |
| 触发入口（C-API） | 同上 C-API 等价路径；`IsSupportExportTexture` 资格判定；`SetParentLayoutConstraint`（`selfIdealSize`） | `frameworks/core/interfaces/native/implementation/builder_node_ops_accessor.cpp` |
| Native 枚举 | `enum class NodeRenderType { RENDER_TYPE_DISPLAY=0, RENDER_TYPE_TEXTURE }`（与 SDK 数值一致） | `frameworks/core/components/common/layout/constants.h` |
| 构建栈标志 | 仅持布尔 `isExportTexture_`（**不持 surfaceId**），标记当前 push 节点按纹理导出创建 | `frameworks/core/components_ng/base/view_stack_processor.cpp`、`view_stack_processor.h` |
| 嵌套传播 | 嵌套 build 时以 `parent‖self` 向下传播 `SetIsExportTexture` | `frameworks/core/components_ng/pattern/custom/custom_node.cpp` |
| 元数据载体 | `ExportTextureInfo` 仅持 `surfaceId_`/`curRenderType_`（**不持 surface/RSNode/生产者指针**） | `frameworks/core/components_ng/export_texture_info/export_texture_info.h` |
| UINode 持有 | `exportTextureInfo_` RefPtr 挂在子树根视图节点；`IsNeedExportTexture`/`CreateExportTextureInfoIfNeeded` 门控 | `frameworks/core/components_ng/base/ui_node.cpp`、`ui_node.h` |
| 宿主 Pattern | 检测 child0 导出态、解析 surfaceId、`HandleTextureExport`→`DoTextureExport`/`StopTextureExport`、嵌套去重、生命周期 | `frameworks/core/components_ng/pattern/node_container/node_container_pattern.cpp`、`node_container_pattern.h` |
| NodeContainer 入口桥 | `NodeController.makeNode` 包装 → `RemakeNode` → `AddBaseNode` 挂 child0 | `frameworks/bridge/declarative_frontend/jsview/js_node_container.cpp`、`frameworks/core/components_ng/pattern/node_container/node_container_model_ng.cpp` |
| 子树测量 | 导出子树与普通子树同等测量（无导出特例分支） | `frameworks/core/components_ng/pattern/node_container/node_container_layout_algorithm.cpp` |
| 渲染树分离 / 交付（ace_engine 边界） | `InitContext` 以 `isTextureExportNode` 创建 RSNode；`DoTextureExport`：`RemoveFromTree`+建 `RSTextureExport`+`SetTextureExport`；`SetIsNeedRebuildRSTree(false)` 守卫；`SyncGeometryFrame`→`UpdateBufferInfo`；`StopTextureExport` | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp`、`rosen_render_context.h` |
| 渲染上下文基线 | `DoTextureExport` 默认 no-op 返 false（仅 Rosen 后端实现真正分流） | `frameworks/core/components_ng/render/render_context.cpp` |
| surfaceId 解析 | `StringToLongUint` 十进制 `strtoull`，失败/溢出返 0 | `frameworks/base/utils/string_utils.cpp`、`string_utils.h` |
| embed 注册表 | surfaceId↔FrameNode 双向映射 `RegisterEmbedNode`/`UnregisterEmbedNode` | `frameworks/core/pipeline/base/element_register.cpp`、`element_register.h` |
| 生命周期触发 | FrameNode dtor → `Pattern::DetachFromFrameNode` → `OnDetachFromFrameNode`；`OnMountToParentDone`；`SetParentLayoutConstraint` | `frameworks/core/components_ng/base/frame_node.cpp`、`frameworks/core/components_ng/pattern/pattern.cpp` |

资格白名单：仅自定义视图根（`JS_VIEW_ETS_TAG`/`COMMON_VIEW_ETS_TAG`）+ `RENDER_TYPE_TEXTURE` 才会 attach `ExportTextureInfo` 并进入生产者路径；其余根不生产。

### API 入口

| 范式 | 声明 | 稳定路径 |
|------|------|----------|
| Dynamic（公开触发） | `enum NodeRenderType`、`interface RenderOptions { selfIdealSize?, type?, surfaceId? }`、`constructor(uiContext, options?)`，`@since 11 dynamic` / `@atomicservice 12`；`surfaceId` 仅 `type=RENDER_TYPE_TEXTURE` 时生效 | `<OH_ROOT>/interface/sdk-js/api/arkui/BuilderNode.d.ts` |
| SDK re-export | BuilderNode 经 `@ohos.arkui.node` / `@kit.ArkUI` 再导出 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.d.ts` |
| Native 枚举（框架内部） | `NodeRenderType` 与 SDK 数值一致 | `frameworks/core/components/common/layout/constants.h` |

> 公开 API 仅触发生产者模式；真正的 buffer 生产发生在跨仓 Rosen，不在公开 API 表达范围。无新增/变更/废弃 API（存量补录）。

### 测试入口

| 类型 | 稳定路径 | 覆盖要点 |
|------|----------|----------|
| NodeContainer UT | `test/unittest/core/pattern/node_container/`（`node_container_test_ng.cpp` 等） | `HandleTextureExport`/生产注册/生命周期/嵌套去重 |
| RosenRenderContext UT | `test/unittest/core/rosen/rosen_render_context_test.cpp`、`rosen_render_context_test_new.cpp` | `DoTextureExport`/`StopTextureExport`/`UpdateBufferInfo` 分流 |
| Mock 后端 | `test/unittest/core/pipeline/mock_rosen_render_context.cpp` | 单测中替换 Rosen 后端 |

> 当前**无**独立的 `export_texture` / `texture_export` / `builder_node` 专项测试文件，生产者侧由 NodeContainer 与 RosenRenderContext 用例覆盖；C-API `node_container_ops_accessor_test` 不覆盖纹理导出。

### 相关 Spec

| 文档 | 路径 | 状态 |
|------|------|------|
| 长期设计 | `specs/04-common-capability/18-on-device-rendering/01-same-layer-rendering/design.md` | Baselined |
| 特性规格（生产者 Feat-01） | `specs/04-common-capability/18-on-device-rendering/01-same-layer-rendering/Feat-01-texture-export-producer-spec.md` | Baselined |
| Spec 总索引 | `specs/index.md` | `04-18-01` 注册入口 |

### 外部依赖入口

ace_engine 边界止于 `RosenRenderContext::DoTextureExport` → 交付 `Rosen::RSTextureExport`。真正 buffer 生产在跨仓 Rosen（graphic_2d），**不在本仓控管**，下列为跨仓参考路径（变更不在 ace_engine 评审范围）：

| 跨仓模块 | 职责 | 参考路径（graphic_2d） |
|----------|------|------------------------|
| `RSTextureExport` | 专用 `RSUIDirector` + 虚拟 `RSSurfaceNode`（携 surfaceId）；逐帧合成 | `foundation/graphic/graphic_2d/rosen/modules/render_service_client/core/ui/rs_texture_export.cpp` |
| `RSSurfaceNode::CreateNodeAndSurface` | surfaceId≠0 时不新建 surface，经 `SurfaceUtils::GetSurface(surfaceId)` 取消费者已注册 surface 包成生产者 | `.../render_service_client/core/ui/rs_surface_node.cpp` |
| `RSUIDirector` | 渲染线程生产/合成 | `.../render_service_client/core/ui/rs_ui_director.cpp` |

## 常见问题定位

> 仅指向 spec 风险条目与源码位置，不复述矩阵。

| 问题 | 优先查看 |
|------|----------|
| 「为何子树不渲染/无纹理」：非法 surfaceId（空/非数字/溢出）经 `StringToLongUint` 解析为 0，生产循环因 `surfaceId_ != 0U` 不进入，**ace_engine 侧静默禁用、无错误无日志** | spec Feat-01 RISK-1 / R-17；`node_container_pattern.cpp` 生产门控；Rosen 侧非法 surfaceId 有 `ROSEN_LOGE` |
| 「8000px / GPU 上限是否适用生产者」：**不适用**。生产者经 `SyncGeometryFrame→UpdateBufferInfo` 直接透传 paintRect 无 clamp；仓内 8000 常量仅 Web 消费者侧 | spec Feat-01 RISK-2 / R-14；`rosen_render_context.cpp` 几何同步 |
| 「嵌套 NodeContainer 不生产」：祖先 child 已 TEXTURE 时当前容器让步、提前 return（祖先优先去重） | spec Feat-01 RISK-6 / R-18；`node_container_pattern.cpp` `SetExportTextureInfoIfNeeded` |
| 「销毁后是否残留生产者」：显式停/注销依赖 `OnDetachFromFrameNode` 经 FrameNode dtor 先跑；`~RosenRenderContext` 不显式 Stop，`rsTextureExport_` 由 shared_ptr 释放 | spec Feat-01 RISK-3 / R-16；`frame_node.cpp`、`pattern.cpp`、`rosen_render_context.cpp` |
| 「纹理尺寸如何确定」：= 导出节点 paint/frame 矩形（布局派生），无显式宽高参数；`selfIdealSize` 经测量约束影响 paintRect | spec Feat-01 R-13/R-14；`rosen_render_context.cpp` `SyncGeometryFrame` |
| 「生产何时首次发生」：不在构造期，延迟到 NodeContainer 首次脏布局的 after-layout task | spec Feat-01 R-8 / AC-5.1；`node_container_pattern.cpp` `OnDirtyLayoutWrapperSwap` |

## 调试入口

- 关键搜索词（全仓 `rg`）：`SetIsExportTexture`、`IsExportTexture`、`IsNeedExportTexture`、`CreateExportTextureInfoIfNeeded`、`HandleTextureExport`、`DoTextureExport`、`StopTextureExport`、`rsTextureExport_`、`RegisterEmbedNode`、`EXPORT_TEXTURE_SUPPORT_TYPES`。
- 生产者身份落点：`RosenRenderContext::InitContext` 的 `isTextureExportNode` 透传，与 `DoTextureExport` 的 `RemoveFromTree`+`RSTextureExport` 构造。
- 跨仓 Rosen 行为须在 graphic_2d 侧定位（`RSTextureExport`/`RSSurfaceNode::CreateNodeAndSurface`/`RSUIDirector`/`SurfaceUtils`），ace_engine 不控管其内部。
- 设计取舍与替代方案见 spec design.md「关键设计决策 ADR-1~6」；调用链层级见 design.md「调用链层级分析」。

## 相关主题

- [NodeContainer（生产者宿主）：[docs/kb/components/custom-node/node-container.md](../components/custom-node/node-container.md)](../components/custom-node/node-container.md)
- [ContentSlot（命令式节点占位）：[docs/kb/components/custom-node/content-slot.md](../components/custom-node/content-slot.md)](../components/custom-node/content-slot.md)
- [占位组件（自定义节点概念入口）：[docs/kb/capabilities/placeholder-component.md](placeholder-component.md)](placeholder-component.md)
- [组件复用框架：[docs/kb/architecture/component-reuse-framework.md](../architecture/component-reuse-framework.md)](../architecture/component-reuse-framework.md)