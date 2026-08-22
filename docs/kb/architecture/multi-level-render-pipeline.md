# Multi-Level Render Pipeline Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `MultiLevelRenderPipeline`

## 定位

多级渲染管线是 ArkUI 引擎子管线与多容器 VSync 协调机制，涵盖子管线创建注册（isSubPipeline/parentPipeline/AttachSubPipelineContext）、多实例 VSync fan-out 分发、跨管线 Touch 坐标偏移、后台 RequestFrame 门控、7 类子管线进程/线程/渲染/事件模型分类差异。它不是对外公共 API，而是引擎内部渲染架构，所有源码路径和实现细节均应回到当前源码、测试和 Spec 核实。

本文档只提供稳定的源码、测试和 Spec 路由。具体子管线生命周期、VSync 协调细节、IPC Session 通信流程应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| PipelineBase 子管线标记 | `frameworks/core/pipeline/pipeline_base.h` | isSubPipeline_/parentPipeline_（WeakPtr）标记与父管线引用 |
| NG 主管线编排 | `frameworks/core/pipeline_ng/pipeline_context.h` | PipelineContext::FlushVsync、windowSceneNode_、SetFocusedWindowSceneNode |
| Frontend 子管线注册 | `frameworks/core/common/frontend.h` | AttachSubPipelineContext 注册子管线到 Frontend 列表 |
| RenderSubContainer 桥接 | `frameworks/core/pipeline/base/render_sub_container.h` | GetSubPipelineContext 桥接 Form/Plugin 子管线实例 |
| Form 子管线容器 | `frameworks/core/components/form/sub_container.h` | SubContainer：宿主 UI 线程创建独立 PipelineContext |
| Form NG Pattern | `frameworks/core/components_ng/pattern/form/form_pattern.h` | FormPattern：NG Form/Card 嵌入 Pattern |
| Plugin 子管线容器 | `frameworks/core/components/plugin/plugin_sub_container.h` | PluginSubContainer：宿主 UI 线程创建独立 PipelineContext |
| Plugin NG Pattern | `frameworks/core/components_ng/pattern/plugin/plugin_pattern.h` | PluginPattern：NG Plugin 嵌入 Pattern |
| UIExtension Pattern | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h` | UIExtensionPattern：跨进程 IPC，无本地 PC |
| UIExtension Node | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_node.h` | UIExtensionNode：跨进程嵌入节点 |
| SessionWrapper 抽象 | `frameworks/core/components_ng/pattern/ui_extension/session_wrapper.h` | SessionWrapper 抽象基类，IPC Session 通信桥接 |
| SessionWrapperFactory | `frameworks/core/components_ng/pattern/ui_extension/session_wrapper_factory.h` | SessionWrapperFactory：按 SessionType 创建 SessionWrapper |
| SessionWrapperImpl | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.h` | SessionWrapperImpl：UIExtension IPC Session 实现 |
| SecurityUE Pattern | `frameworks/core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h` | SecurityUIExtensionPattern：安全跨进程 Pattern |
| SecuritySessionWrapper | `frameworks/core/components_ng/pattern/ui_extension/security_ui_extension_component/security_session_wrapper_impl.h` | SecuritySessionWrapperImpl：安全 IPC Session 实现 |
| DynamicPattern | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h` | DynamicPattern：隔离线程子管线 Pattern |
| DynamicNode | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_node.h` | DynamicNode：隔离线程嵌入节点 |
| DynamicComponentManager | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h` | DynamicComponentManager 单例：管理动态组件生命周期 |
| IsolatedPattern | `frameworks/core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h` | IsolatedPattern：受限线程子管线 Pattern |
| DynamicComponentRendererImpl | `adapter/ohos/entrance/dynamic_component/dynamic_component_renderer_impl.h` | DC/Isolated UIContent 创建，Worker 线程 |
| ArkTsDynamicPattern | `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern.h` | ArkTsDynamicPattern：ArkTS 隔离线程 Pattern |
| DynamicComponentRenderer 抽象 | `frameworks/core/common/dynamic_component_renderer.h` | DynamicComponentRenderer 抽象接口 |
| RosenWindow VSync（旧管线） | `frameworks/core/common/rosen/rosen_window.h` | 旧管线 VSync 注册 + multi-instance fan-out |
| RosenWindow VSync（NG 管线） | `frameworks/core/components_ng/render/adapter/rosen_window.h` | NG RosenWindow：ForceFlushVsync、FlushVsync fan-out |
| DetachedRsNodeManager | `frameworks/core/components_ng/render/detached_rs_node_manager.h` | DetachedRsNodeManager 单例：FlushInstance 迭代 ForceFlushVsync |
| Touch 坐标偏移 | `frameworks/core/event/touch_event.h` | SetSubPipelineGlobalOffset 跨管线 Touch 坐标偏移转换 |
| Container 类型标记 | `frameworks/core/common/container.h` | IsSubContainer()/IsDynamicRender()/IsUIExtensionWindow()/IsFormRender() |
| ContainerScope RAII | `frameworks/core/common/container_scope.h` | MarkIsolatedThread() 隔离线程标记 |
| AceContainer 子容器 | `adapter/ohos/entrance/ace_container.h` | IsSubContainer override、IsUIExtensionWindow override |
| WindowSceneHelper | `frameworks/core/components_ng/pattern/window_scene/helper/window_scene_helper.h` | FindWindowScene 查找窗口场景 |
| GlobalPipelineContextManager | `adapter/ohos/entrance/global_pipeline_context_manager.h` | 全局多实例管线注册表 |
| ContainerWindowManager | `frameworks/core/pipeline/container_window_manager.h` | 容器窗口管理 |
| UIExtensionTouchDelegate | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_touch_delegate.h` | 跨进程 Touch 事件委托 |

### API 入口

多级渲染管线是引擎内部架构，没有独立 SDK API。子管线机制通过 PipelineBase/Frontend/Container 内部接口暴露，不在公共 API 列表中。

### 子管线类型分类

| 类型 | 进程模型 | 线程模型 | PipelineContext | 渲染挂载 | 事件模型 | Container 标记 |
|------|---------|---------|---------------|---------|---------|---------------|
| Form/Card | 进程内 | 宿主 UI 线程 | SubContainer 创建 | DrawDelegate/RSSurfaceNode | Touch dispatch | IsSubContainer=true |
| Plugin | 进程内 | 宿主 UI 线程 | PluginSubContainer 创建 | DrawDelegate/RSSurfaceNode | Touch dispatch | IsSubContainer=true |
| UIExtension | 跨进程 IPC | 宿主 UI 线程 | 无（SessionWrapper） | RSSurfaceNode via Session | IPC session forward | Normal |
| SecurityUIExtension | 跨进程 IPC | 宿主 UI 线程 | 无（SecuritySessionWrapper） | RSSurfaceNode via Session | IPC session forward | Normal |
| DynamicComponent | 进程内隔离 | Worker 线程 | UIContent 创建（有 AbilityContext） | RenderContext attach | PointerEvent + Key transfer | IsDynamicRender=true |
| IsolatedComponent | 进程内受限 | 受限 Worker 线程 | UIContent 创建（无 AbilityContext） | RenderContext attach | PointerEvent + Key transfer | IsDynamicRender=true |
| PreviewUIExtension | 跨进程 IPC | 宿主 UI 线程 | 无（PreviewSessionWrapper） | RSSurfaceNode via Session | 继承 SecurityUE | Normal |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 说明 |
|----------|----------|------------|------|
| Rosen 渲染服务 | `frameworks/core/components_ng/render/adapter/rosen_window.cpp` | `foundation/graphic/graphic_2d` | RSUIDirector IPC；RS Surface Node/Transaction/SyncTransactionController |
| Ability 运行时 | `adapter/ohos/entrance/dynamic_component/dynamic_component_renderer_impl.cpp` | `application/ability_runtime` | AbilityContext/AceAbility UIExtension 能力加载 |
| 窗口管理 | `frameworks/core/components_ng/pattern/ui_extension/ui_extension_component/session_wrapper_impl.cpp` | `foundation/window_manager` | ExtensionSession/Session/SceneSession IPC 通信 |
| MMI 输入 | `frameworks/core/event/touch_event.cpp` SetSubPipelineGlobalOffset | `multimodalinput/input` | libmmi-client 触控事件坐标偏移 |
| IPC | `frameworks/core/components_ng/pattern/ui_extension/session_wrapper_factory.cpp` | `foundation/communication/ipc` | ipc_single/ipc_core IPC Session 管理 |
| Form 框架 | `frameworks/core/components/form/sub_container.cpp` | `application/form_fwk` | fmskit_native/form_render_info Form 管理与渲染 |
| Bundle 框架 | `frameworks/core/components/form/sub_container.cpp` | `application/bundle_framework` | appexecfwk_core Bundle 信息 |
| HiLog | `adapter/ohos/entrance/dynamic_component/` | `base/hiviewdfx/hilog` | libhilog 日志 |
| Init 设备信息 | `adapter/ohos/entrance/ace_container.cpp` | `base/startup/init` | libbegetutil 参数/设备信息 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Form Pattern 测试 | `test/unittest/core/pattern/form/form_pattern_test.cpp` | FormPattern NG 功能测试 |
| Form SubContainer Mock | `test/unittest/core/pattern/form/mock/mock_sub_container.h` | SubContainer 测试替身 |
| Plugin Pattern 测试 | `test/unittest/core/pattern/plugin/plugin_pattern_test_ng.cpp` | PluginPattern NG 测试 |
| Plugin SubContainer Mock | `test/unittest/core/pattern/plugin/mock/mock_plugin_sub_container.cpp` | PluginSubContainer 替身 |
| UIExtension 测试 | `test/unittest/core/pattern/ui_extension/ui_extension_component/ui_extension_component_test.cpp` | UIExtensionPattern 功能测试 |
| SessionWrapperImpl 测试 | `test/unittest/core/pattern/ui_extension/session_wrapper_impl_test_ng.cpp` | SessionWrapperImpl IPC 测试 |
| SecurityUE 测试 | `test/unittest/core/pattern/ui_extension/security_ui_extension_component_test.cpp` | SecurityUIExtensionPattern 测试 |
| DynamicComponent 测试 | `test/unittest/core/pattern/ui_extension/dynamic_component/dynamic_component_manager_tdd_test.cpp` | DynamicComponentManager TDD |
| IsolatedPattern 测试 | `test/unittest/core/pattern/ui_extension/isolated_pattern_test_ng.cpp` | IsolatedPattern NG 测试 |
| 隔离线程 Pipeline 测试 | `test/unittest/core/pipeline/pipeline_context_isolated_thread_test.cpp` | 隔离线程 PipelineContext 测试 |
| 隔离线程 UINode 测试 | `test/unittest/core/base/ui_node_isolated_thread_test.cpp` | 隔离线程 UI 节点测试 |
| PipelineContext NG 测试 | `test/unittest/core/pipeline/pipeline_context_test_ng.cpp` | 主管线 FlushVsync 测试 |
| Container 测试 | `test/unittest/base/container_test.cpp` | Container 基类测试 |
| ContainerScope 测试 | `test/unittest/frameworks/core/common/container_scope_test.cpp` | ContainerScope RAII/隔离线程标记 |

### 相关 Spec

多级渲染管线功能域：`specs/03-engine-framework/01-render-pipeline/02-multi-level-render-pipeline/`（功能 ID `03-01-02`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 设计文档 | `specs/03-engine-framework/01-render-pipeline/02-multi-level-render-pipeline/design.md` | 子管线分类、VSync 协调、Touch 偏移、后台门控、ADR |
| 子管线与多容器 VSync 协调规格 | `specs/03-engine-framework/01-render-pipeline/02-multi-level-render-pipeline/Feat-01-sub-pipeline-multi-container-vsync-coordination-spec.md` | 子管线创建注册、VSync fan-out、Touch 坐标偏移、后台门控、7 类分类 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 子管线创建失败 | PipelineBase isSubPipeline_/parentPipeline_ 标记 + SubContainer/PluginSubContainer 构造 |
| VSync 不分发到子管线 | RosenWindow multi-instance fan-out + DetachedRsNodeManager FlushInstance |
| Touch 坐标偏移错误 | SetSubPipelineGlobalOffset 偏移计算 + 子管线 localOffset |
| 后台子管线浪费 VSync | window_->Lock/Unlock 门控 + FindWindowScene 可见窗口查找 |
| UIExtension IPC Session 断开 | SessionWrapper OnDisconnect + RSSurfaceNode 清理 + placeholder 恢复 |
| DC/Isolated 嵌套约束 | CheckConstraint 防止 DC→DC/Isolated→Isolated 嵌套 |
| 隔离线程不一致 | PipelineContext isIsolatedThread_ 验证 + ContainerScope MarkIsolatedThread |
| 子管线窗口场景查找失败 | WindowSceneHelper FindWindowScene + WINDOW_SCENE_ETS_TAG |

## 调试入口

- 子管线注册断点：Frontend::AttachSubPipelineContext → subPipelineContexts_ 列表
- VSync fan-out 断点：RosenWindow::OnVsync → forEach registeredInstance → ForceFlushVsync
- Touch 坏管线偏移断点：TouchEvent::SetSubPipelineGlobalOffset → globalOffset_ 累加
- 后台门控断点：RosenWindow::RequestFrame → isLocked_ 检查 → Lock/Unlock
- 子管线类型判定断点：Container::IsSubContainer()/IsDynamicRender()/IsUIExtensionWindow()
- IPC Session 断点：SessionWrapperImpl → ExtensionSession → Session → forward event

## 相关主题

- 基本渲染管线：[docs/kb/architecture/layout-framework.md](layout-framework.md)（Layout/Measure/Render 基础管线流程）
- OH 平台适配层：[docs/kb/architecture/oh-platform-adapter.md](oh-platform-adapter.md)（Container/AceContainer 容器体系）
- [窗口机制：[docs/kb/architecture/window-mechanism.md](window-mechanism.md)（Rosen Window 窗口管理）](window-mechanism.md)
- [基础渲染管线：[docs/kb/architecture/basic-render-pipeline.md](basic-render-pipeline.md)（NG 管线帧编排 + 旧管线三层架构兼容性）](basic-render-pipeline.md)