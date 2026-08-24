# 多实例管理 Context

> 文档版本：v1.1
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `multi-instance-management`

## 定位

多实例管理是 ArkUI 引擎框架层的核心架构能力，归属 Func-03-06-01。管理多个 ACE 实例的创建、隔离、销毁和协同调度。每个实例拥有独立的 Container、PipelineContext、TaskExecutor 和前端运行环境；实例间通过 ContainerScope（thread_local RAII）切换活跃上下文，通过 AceEngine 全局注册表管理实例生命周期。

核心子能力：实例创建与销毁（AceContainer/PaContainer/DialogContainer）、实例隔离（ContainerScope + InstanceId 分区）、子实例管理（SubContainer/SubwindowManager）、跨实例任务调度（MultiThreadBuildManager/UITaskScheduler）、实例间协同（NotifyContainers）、全局管线管理（GlobalPipelineContextManager）、窗口抽象与绑定（RosenWindow/FormRenderWindow）、卡片多实例（FormRenderer/FormRendererGroup）。

行为事实来自源码实现和测试；本页仅提供路由入口，不重复 Spec 规格内容。

## 快速路由

### 源码入口

#### 全局注册与 ID 管理

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| Container 抽象基类 | `frameworks/core/common/container.h` | Container::GetInstanceId()/Initialize()/Destroy()/GetPipelineContext()；静态 Current()/GetContainer(id)/GetActive()/GetDefault()/GetByWindowId() |
| Container 类型常量 | `frameworks/core/common/container_consts.h` | ContainerType 枚举（STAGE/FA/PA_SERVICE/PA_DATA/PA_FORM/SUBWINDOW/DC/COMPONENT_SUBWINDOW/PLUGIN）+ InstanceId 分区常量 |
| AceEngine 全局注册表 | `frameworks/core/common/ace_engine.h/cpp` | containerMap_ 管理 instanceId → Container；AddContainer/RemoveContainer/NotifyContainers |
| ContainerScope 实例切换 | `frameworks/core/common/container_scope.h/cpp` | RAII thread_local 切换 currentId_；CurrentId()/DefaultId()/RecentActiveId()/MarkIsolatedThread() |
| InstanceId 生成 | `container.h` GenerateId 模板 | type * CONTAINER_ID_DIVIDE_SIZE + atomic counter |
| ContainerHandler | `frameworks/core/common/container_handler.h` | 跨容器数据通道基类；派生 PlatformContainerHandler 和 UIExtensionContainerHandler |

#### 生产容器实现

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| AceContainer（主运行实例） | `adapter/ohos/entrance/ace_container.h/cpp` | Stage/FA 模型主容器；CreateContainer()/RunPage()/DestroyContainer() |
| DialogContainer（弹窗子实例） | `adapter/ohos/entrance/dialog_container.h/cpp` | ShowToast/ShowDialog/ShowActionMenu 子窗口容器 |
| PaContainer（服务端实例） | `adapter/ohos/entrance/pa_container.h/cpp` | PA Service/Data/Form 后端容器（无 UI Pipeline） |
| WindowFreeContainer | `frameworks/core/common/window_free_container.h/cpp` | 静态工厂创建/销毁 |
| UIContentImpl（上层入口） | `adapter/ohos/entrance/ui_content_impl.h/cpp` | Ability Framework 调用的顶层入口；CommonInitialize 中创建 AceContainer 并注册到 AceEngine 和 SubwindowManager |

#### 窗口抽象与生产实现

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| Window（抽象基类） | `frameworks/core/common/window.h` | Window : enable_shared_from_this；RequestFrame/OnVsync/SetRootRenderNode/Destroy；子窗口注册 RegisterSubWindow |
| PlatformWindow | `frameworks/core/common/platform_window.h` | 窗口抽象接口；Vsync、渲染表面绑定 |
| RosenWindow（NG 生产窗口） | `frameworks/core/components_ng/render/adapter/rosen_window.h/cpp` | NG::RosenWindow : Window；包裹 Rosen::Window + RSUIDirector |
| FormRenderWindow | `frameworks/core/components_ng/render/adapter/form_render_window.h` | 卡片渲染窗口；使用 RSSurfaceNode，不创建完整 Rosen Window |
| WindowManager | `frameworks/core/pipeline/container_window_manager.h` | 窗口操作回调集；最小化/最大化/恢复/关闭/移动/方向/系统栏 |
| FoldableWindow / DragWindow | `frameworks/base/window/foldable_window.h`、`drag_window.h` | 折叠窗口和拖拽窗口抽象 |

#### 子窗口管理

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| Subwindow | `frameworks/base/subwindow/subwindow.h` | 子窗口抽象；SubwindowType 枚举（Toast/Menu/Popup/Dialog/Sheet 等） |
| SubwindowManager（单例） | `frameworks/base/subwindow/subwindow_manager.h/cpp` | SubwindowKey 含 instanceId/displayId/windowType/nodeId；管理菜单/对话框/Toast 子窗口；映射 windowId→containerId 和 containerId→parentContainerId |

#### 窗口场景 Pattern（UIExtension / SceneBoard）

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| WindowPattern | `frameworks/core/components_ng/pattern/window_scene/scene/window_pattern.h` | WindowPattern : StackPattern；OnForeground/OnBackground、Session 管理 |
| WindowScene | `frameworks/core/components_ng/pattern/window_scene/scene/window_scene.h` | WindowScene : WindowPattern；OnActivation/OnConnect/OnDisconnect/OnRemoveBlank；快照管理 |
| SystemWindowScene / PanelScene / MirrorWindowScene / InputScene | `frameworks/core/components_ng/pattern/window_scene/scene/` | 各场景 Pattern 派生类 |
| WindowSceneHelper | `frameworks/core/components_ng/pattern/window_scene/helper/window_scene_helper.h` | 工具类 |

#### Form 多实例

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| FormRenderer | `interfaces/inner_api/form_render/include/form_renderer.h` | 单卡片 UIContent 生命周期；AddForm/RunFormPage/UpdateForm/Destroy；Surface 生命周期 OnSurfaceCreate/Reuse/Detach |
| FormRendererGroup | `interfaces/inner_api/form_render/include/form_renderer_group.h` | 1:1 运行时卡片组管理；AddForm/DeleteForm/UpdateForm/RecycleForm/RecoverRenderer |
| SubContainer（进程内嵌入式卡片） | `frameworks/core/components/form/sub_container.h` | 父 PipelineContext 内嵌卡片渲染；独立 Frontend 和 PipelineContext |

#### 渲染管线与任务调度（Per-Container）

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| PipelineContext（NG） | `frameworks/core/pipeline_ng/pipeline_context.h/cpp` | NG::PipelineContext : PipelineBase；每个 Container 持有一个；GetCurrentContext/GetMainPipelineContext/GetContextByContainerId |
| GlobalPipelineContextManager | `adapter/ohos/entrance/global_pipeline_context_manager.h/cpp` | modal UIExtension overlay 管线注册 |
| MultiThreadBuildManager | `frameworks/core/common/multi_thread_build_manager.h/cpp` | 跨实例 PostUITask/PostAsyncUITask + 线程安全节点作用域 |
| TaskExecutor（单实例任务） | `frameworks/base/thread/task_executor.h/cpp` | 每个 Container 持有独立 TaskExecutor（UI/JS/PLATFORM/IO/GPU 线程） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|---------|------|
| Stage 模型入口 | `adapter/ohos/entrance/ui_content_impl.h/cpp` | UIContentImpl 每个 UIAbility 创建 AceContainer |
| FA 模型入口 | `adapter/ohos/entrance/ace_ability.h/cpp` | AceAbility 每个 FA Ability 创建 AceContainer |
| Form 入口 | `adapter/ohos/entrance/ace_form_ability.h/cpp` | Form Ability 创建 PaContainer |
| Inner API（UIContent） | `interfaces/inner_api/ace/ui_content.h/cpp` | UIContent 抽象接口；Initialize/RunPage/Destroy 触发 AceContainer 创建与注册 |
| Inner API（FormRenderer） | `interfaces/inner_api/form_render/include/form_renderer.h` | 卡片创建/更新/删除；Surface 生命周期 |
| C-API 实例绑定 | `interfaces/native/native_type.h` + `native_node.h` | ArkUI_ContextHandle；OH_ArkUI_GetContextByNode/RunTaskInScope/PostUITask |
| C-API NAPI 桥接 | `interfaces/native/native_node_napi.h` | OH_ArkUI_GetContextFromNapiValue；PostFrameCallback/PostIdleCallback |
| C-API ANI 桥接 | `interfaces/native/native_node_ani.h` | OH_ArkUI_NativeModule_GetContextFromAniValue |
| C-API 多线程桥接 | `frameworks/core/interfaces/native/node/node_api_multi_thread.h/cpp` | GetMultiThreadManagerAPI() |
| C-API Accessibility 实例 | `interfaces/native/native_interface_accessibility.h` | OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓 | 说明 |
|----------|----------|--------|------|
| AbilityRuntime 上下文 | `adapter/ohos/entrance/ace_container.h/cpp` | `ability_runtime` | UIExtensionContext / Configuration / AbilityContext 获取 |
| Rosen 渲染窗口 | `rosen_window.h`、`ace_container.cpp` | `graphic_2d` | Rosen::Window 创建、RSUIDirector 渲染表面绑定 |
| 图形渲染 | `adapter/ohos/entrance/ace_container.h/cpp` | `graphic_2d` | DisplayManager（display 信息）；RSSurfaceNode（渲染表面） |
| Window Manager Service | `ace_container.cpp`、`window_free_container.cpp` | `window_manager` | 系统窗口创建、焦点、模式切换 |
| Bundle 框架 | `adapter/ohos/entrance/ace_container.cpp` | `bundle_framework` | BundleMgrProxy 查询应用信息 |
| 系统能力注册 | `adapter/ohos/entrance/ace_container.cpp` | `samgr` | ISystemAbilityManager / IServiceRegistry / SystemAbilityDefinition 查找系统服务 |
| ETS 运行时 | `adapter/ohos/entrance/ace_container.h` | `ets_runtime` | NativeReference / NativeValue 用于 JS 对象生命周期管理 |
| 并发调度 | `frameworks/core/common/multi_thread_build_manager.cpp` | `ffrt` | ffrt_inner.h 用于跨实例任务调度 |
| 输入事件 | `adapter/ohos/entrance/ace_container.cpp` | `multimodalinput` | PointerEvent 类型定义 |
| 卡片数据 | `adapter/ohos/entrance/ace_container.cpp` | `form_fwk` | FormAshmem 卡片共享内存数据 |
| Form Render Service | `form_renderer.h` | `appexecfwk_standard` (form) | 卡片创建/更新/删除回调 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|---------|------|
| ContainerScope 单测 | `test/unittest/frameworks/core/common/container_scope_test.cpp` | 实例切换 RAII、多容器场景、隔离线程模式 |
| AceEngine 注册表单测 | `test/unittest/frameworks/core/common/ace_engine_test.cpp` | AddContainer/RemoveContainer/NotifyContainers/LRU |
| Container 基础设施 | `test/unittest/base/container_test.cpp` | Container 抽象基类回归 |
| Container 单测 | `test/unittest/adapter/ohos/entrance/container_test.cpp` | MockContainer 行为验证 |
| SubwindowManager | `test/unittest/base/subwindow_manager_test.cpp` | 子窗口管理器回归 |
| Window Pattern | `test/unittest/core/pattern/window_scene/window_pattern_test.cpp`、`window_scene_test.cpp` | 窗口场景 Pattern 回归 |
| PipelineContext | `test/unittest/core/pipeline/pipeline_context_test_ng.cpp`（多文件） | Per-Container 渲染管线回归；覆盖全局管线和多实例场景 |
| Pipeline 隔离线程单测 | `test/unittest/core/pipeline/pipeline_context_isolated_thread_test.cpp` | DC/卡片多实例隔离线程 |
| MultiThreadBuildManager 单测 | `test/unittest/core/common/multi_thread_build_manager/multi_thread_build_manager_test.cpp` | 跨实例任务调度 |
| MockContainer 基础设施 | `test/mock/frameworks/core/common/mock_container.h` | 几乎所有 NG 单测依赖的 MockContainer |

### 相关 Spec

窗口机制功能域：`specs/03-engine-framework/05-window-mechanism/01-window-mechanism/`（功能 ID `03-05-01`）。

多实例管理功能域：`specs/03-engine-framework/06-multi-instance-management/01-multi-instance-management/`（功能 ID `03-06-01`）。

子窗机制：`specs/03-engine-framework/05-window-mechanism/02-subwindow-mechanism/`（功能 ID `03-05-02`，spec_status `pending`）。

#### 窗口机制 Spec

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 窗口抽象与 Rosen Window 初始化 | `specs/03-engine-framework/05-window-mechanism/01-window-mechanism/Feat-01-window-abstraction-rosen-window-init-spec.md` |
| Feat-02 | 窗口生命周期状态转换 | `specs/03-engine-framework/05-window-mechanism/01-window-mechanism/Feat-02-window-lifecycle-state-transition-spec.md` |
| Feat-03 | 多实例全局管线 | `specs/03-engine-framework/05-window-mechanism/01-window-mechanism/Feat-03-multi-instance-global-pipeline-spec.md` |
| Feat-04 | 特殊窗口类型 | `specs/03-engine-framework/05-window-mechanism/01-window-mechanism/Feat-04-special-window-types-spec.md` |

#### 多实例管理 Spec

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 多实例管理 | `Feat-01-multi-instance-management-spec.md` |

架构决策和模块边界见同目录 `design.md`。行为结论以对应 Feat、当前源码和测试的交叉证据为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Container 创建失败或崩溃 | `ace_container.cpp` CreateContainer、AceEngine 注册、Rosen::Window 初始化、Feat-01 |
| 多实例间 ContainerScope 切换不正确 | `container_scope.h/cpp` — thread_local currentId_ push/pop RAII；ContainerScope 构造/析构 |
| 实例 ID 冲突或溢出 | `container.h` GenerateId 模板 + `container_consts.h` CONTAINER_ID_DIVIDE_SIZE 分区 |
| 实例销毁后缓存泄漏 | `ace_engine.cpp` — destroyedUIContextCache_ + RemoveContainer 缓存逻辑 |
| 子窗口弹窗找不到父实例 | `subwindow_manager.h/cpp` — AddParentContainerId/GetParentContainerId |
| 子窗口未正确关联 | `SubwindowManager` 的 windowId→containerId 映射、SubwindowKey 构造 |
| 窗口生命周期异常（未触发 foreground/background） | `ace_container.cpp` OnShow/OnHide/ActiveWindow、RosenWindow Vsync/RequestFrame、Feat-02 |
| 卡片多实例渲染异常 | `FormRenderer` Surface 生命周期、`FormRendererGroup` 回收恢复、SubContainer PipelineContext |
| UIExtension 窗口嵌入异常 | `UIExtensionContainerHandler`、`PlatformContainerHandler`、SessionWrapper |
| 全局管线调度冲突 | `PipelineContext::GetMainPipelineContext`、AceEngine NotifyContainers、Feat-03 |
| 隔离线程模式下实例隔离失效 | `container_scope.h` MarkIsolatedThread + localContainerSet_ |
| 跨实例 UI 任务投递死锁 | `multi_thread_build_manager.h/cpp` — PostUITaskAndWait 需避免同线程递归 |
| PipelineContext 初始化顺序错误 | `ace_container.cpp` Initialize → InitializeFrontend → InitializeTask → AttachView |
| 系统栏或窗口模式异常 | `WindowManager` 回调、系统栏样式设置、窗口模式查询 |

## 调试入口

- AceEngine 注册表可通过 `AceEngine::Get().containerMap_` 遍历查看活跃实例
- ContainerScope 可通过 `ContainerScope::CurrentId()` 确认当前线程活跃实例
- InstanceId 生成可通过 `Container::GenerateId<type>()` atomic counter 确认分区
- destroyedUIContextCache_ 可通过 `AceEngine::Get()` 查看已销毁实例缓存
- 窗口创建：从 `UIContentImpl::CommonInitialize` 追踪 CreateContainer→AceContainer 构造→Rosen::Window 绑定
- 子窗口：从 `SubwindowManager::GetOrCreateMenuSubWindow/GetDialogSubwindow` 追踪子窗口查找和创建
- 窗口场景：从 `WindowScene::OnConnect/OnActivation` 追踪 Session 连接和激活
- 卡片实例：从 `FormRenderer::AddForm/RunFormPage` 追踪卡片 UIContent 初始化
- 回归验证：运行 `test/unittest/adapter/ohos/entrance/container_test.cpp` 和 `test/unittest/base/subwindow_manager_test.cpp`

## 相关主题

- [渲染管线](layout-framework.md)
- [基础渲染管线](basic-render-pipeline.md)
- [UIContext 接口](../capabilities/ui-context.md)
- [窗口机制](window-mechanism.md)
- [[UIContext 实例 ID 泄漏](../issues/lifecycle/uicontext-instance-id-leak.md) — 动态前端历史配对问题（已修复）与多路径实例栈排查
- UISession](uisession-service.md)（跨进程 UI 会话通道）