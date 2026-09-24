# OH Platform Adapter Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `OHPlatformAdapter`

## 定位

OH 平台适配层是 ArkUI 引擎面向 OpenHarmony 标准系统的适配边界，涵盖 Container 容器体系（AceContainer/DialogContainer/PaContainer 双继承）、UIContentImpl 系统入口委托、PlatformWindow 渲染窗口工厂、AceApplicationInfo 链接时选择和 OSAL 平台抽象桥接。它不是对外公共 API，而是引擎内部平台适配架构，调用方向为 NG→Adapter→RS，不可反向。

本文档只提供稳定的源码、测试和 Spec 路由。具体容器生命周期、宏选择、VSync 委托细节应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Container 抽象基类 | `frameworks/core/common/container.h` | Container 纯虚基类；Initialize/Destroy/GetFrontend/GetPipelineContext 等接口 |
| AceContainer 双继承容器 | `adapter/ohos/entrance/ace_container.h` | Container+JsMessageDispatcher 双继承；FA/Stage/Card 四构造函数变体；生命周期 CreateContainer→Initialize→SetView→RunPage |
| DialogContainer | `adapter/ohos/entrance/dialog_container.h` | 继承 AceContainer；Toast/Dialog/ActionMenu 容器；IsDialogContainer=true |
| PaContainer | `adapter/ohos/entrance/pa_container.h` | 继承 Container（无 JsMessageDispatcher）；无 UI，仅数据/服务 |
| ContainerScope RAII | `frameworks/core/common/container_scope.h` | RAII 实例 ID 管理；CurrentId/DefaultId/SafelyId；隔离线程支持 |
| UIContentImpl 系统入口 | `adapter/ohos/entrance/ui_content_impl.h` | OHOS Ability→AceContainer 委托；Initialize/RunPage/Destroy/Foreground/Background |
| PlatformWindow 抽象 | `frameworks/core/common/platform_window.h` | PlatformWindow 工厂 Create(AceView*)；RequestFrame/RegisterVsyncCallback |
| RSWindow（旧管线） | `frameworks/core/common/rosen/rosen_window.h` | Platform::RSWindow；VsyncThreadMain；旧管线 VSync 线程渲染 |
| RosenWindow（NG 管线） | `frameworks/core/components_ng/render/adapter/rosen_window.h` | NG::RosenWindow；rsWindow_+rsUIDirector_；NG 管线主渲染窗口 |
| PlatformResRegister | `frameworks/core/common/platform_res_register.h` | 抽象基类；OnMethodCall/CreateResource/ReleaseResource |
| JsMessageDispatcher | `frameworks/core/common/js_message_dispatcher.h` | 抽象基类；Dispatch/DispatchSync |
| AceApplicationInfoImpl（OHOS） | `adapter/ohos/entrance/ace_application_info.h` | OHOS 实现；ResourceManager locale；链接时选择（同名类） |
| AceApplicationInfoImpl（Preview） | `adapter/preview/entrance/ace_application_info.h` | Preview 实现；同名类链接时选择 |
| PlatformEventCallback | `adapter/ohos/entrance/platform_event_callback.h` | 抽象回调；OnFinish/OnStartAbility/OnStatusBarBgColorChanged |
| AceViewOhos | `adapter/ohos/entrance/ace_view_ohos.h` | OHOS View；SetPlatformResRegister 外部注入 |
| OSAL 目录 | `adapter/ohos/osal/` | 115 文件；资源/显示/图片/输入/可访问性/AI/性能/网络等平台桥接 |
| 构建配置（适配宏） | `adapter/ohos/build/common.gni` | OHOS 宏定义（OHOS_PLATFORM/ENABLE_ROSEN_BACKEND/NG_BUILD 等） |

### API 入口

OH 平台适配层是引擎内部架构，没有独立 SDK API。Container/UIContentImpl/PlatformWindow 等接口均为内部调用，不在公共 API 列表中。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 说明 |
|----------|----------|------------|------|
| Rosen 渲染服务 | `adapter/ohos/entrance/ace_container.cpp` SetView/SetViewNew | `foundation/graphic/graphic_2d` | RSUIDirector IPC 通信；Rosen::Window 窗口绑定 |
| Ability 框架 | `adapter/ohos/entrance/ui_content_impl.cpp` | `application/ability_runtime` | AbilityContext/AceAbility/AceFormAbility 系统入口 |
| 窗口管理 | `adapter/ohos/entrance/ace_container.cpp` | `foundation/window_manager` | Rosen::Window 创建/销毁/SceneSession |
| 输入管理 | `adapter/ohos/osal/` MMI 事件转换 | `multimodalinput/input` | libmmi-client 触控/按键/鼠标事件 |
| 资源管理 | `adapter/ohos/osal/resource_adapter_impl.cpp` | `global/i18n`, `global/resource_management` | ResourceManager locale + 资源适配 |
| HiLog/HiTrace/HiSysEvent | `adapter/ohos/osal/log_wrapper.cpp`, `event_report.cpp`, `ace_trace.cpp` | `base/hiviewdfx/hilog`, `hitrace`, `hisysevent` | 日志/打点/事件上报 |
| HiCollie | `adapter/ohos/osal/perf_interfaces.cpp` | `base/hiviewdfx/hicollie` | Watchdog/ANR 检测 |
| FFRT | `adapter/ohos/osal/` 条件编译 | `foundation/resourceschedule/ffrt` | 异步任务调度 |
| 图片框架 | `adapter/ohos/osal/image_source_ohos.cpp` | `multimedia/image_framework` | ImageSource/PixelMap 解码 |
| dlopen 动态加载 | `adapter/ohos/osal/dynamic_module_helper.cpp` 等 | 各独立 .so（libai_adapter/libimage_analyzer/libace_network 等） | 组件模块/AI/网络等延迟加载 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Container 自动填充 | `test/unittest/adapter/ohos/entrance/container_test.cpp` | AceContainer autofill 接口测试（MockContainer） |
| ContainerScope RAII | `test/unittest/frameworks/core/common/container_scope_test.cpp` | CurrentId/Add/Remove/隔离线程 |
| UIContent 接口 | `test/unittest/interfaces/ui_content_test.cpp` | UIContent 接口测试 |
| UIContent TDD | `test/unittest/interfaces/ui_content_tdd_test.cpp` | UIContent TDD 测试 |
| System Properties | `test/unittest/adapter/ohos/osal/system_properties/system_properties_test.cpp` | OHOS 系统属性查询 |
| Feature Manager | `test/unittest/adapter/ohos/osal/feature_manager/feature_manager_test.cpp` | Feature flag 管理 |
| RS Adapter | `test/unittest/adapter/ohos/entrance/rs_adapter_test.cpp` | Rosen 渲染适配 |
| Layout Inspector | `test/unittest/adapter/ohos/entrance/layout_inspector_test.cpp` | 布局 Inspector |
| MockContainer | `test/mock/frameworks/core/common/mock_container.h/.cpp` | 全局测试替身 |
| MockAceApplicationInfo | `test/mock/frameworks/core/common/mock_ace_application_info.cpp` | 应用信息替身 |

### 相关 Spec

OH 平台适配功能域：`specs/02-cross-platform/01-platform-adapter/01-oh-platform-adapter/`（功能 ID `02-01-01`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 平台抽象基类与构建适配规格 | `specs/02-cross-platform/01-platform-adapter/01-oh-platform-adapter/Feat-01-platform-abstraction-build-spec.md` | Container/AceApplicationInfo/PlatformWindow/构建宏/UIContentImpl |
| 设计文档 | `specs/02-cross-platform/01-platform-adapter/01-oh-platform-adapter/design.md` | 整体架构设计、ADR、容器体系、宏体系 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 容器初始化失败 | AceContainer CreateContainer→Initialize→CommonInitialize 编排链 |
| VSync 不回调 | PlatformWindow::RequestFrame / RosenWindow::RegisterVsyncCallback / RSUIDirector VSync |
| 窗口创建失败 | AceContainer::SetView / Rosen::Window 创建 / SceneSessionManager |
| 容器 ID 冲突 | ContainerType ID 分区（每种 100000）/ ContainerScope::CurrentId |
| 应用信息获取错误 | AceApplicationInfoImpl 链接时选择 / ResourceManager locale |
| OHOS 宏不生效 | adapter/ohos/build/common.gni ENABLE_ROSEN_BACKEND / CROSS_PLATFORM / NG_BUILD |
| Preview 构建不匹配 | adapter/preview/ 同名类链接时选择 vs adapter/ohos/ |
| OSAL dlopen 加载失败 | dynamic_module_helper.cpp dlopen 错误 / .so 路径 / 符号导出 |

## 调试入口

- 容器生命周期断点：AceContainer::CreateContainer→Initialize→SetView→RunPage
- 系统入口断点：UIContentImpl::Initialize→CommonInitialize 编排链
- VSync 断点：RosenWindow::RequestFrame→OnVsync→RSUIDirector FlushTasks
- 容器 ID 断点：ContainerScope 构造/析构→CurrentId→线程局部存储
- 应用信息断点：AceApplicationInfoImpl::SetLocale→ResourceManager locale 更新

## 相关主题

- [编译构建（适配宏体系与构建变体）](build-system.md)
- [窗口机制（Rosen Window 窗口管理）](window-mechanism.md)
- [DFX 日志（HiLog/HiSysEvent OSAL 桥接）](dfx/logging.md)
- [DFX Trace（HiTrace/PerfMonitor OSAL 桥接）](dfx/trace.md)
- [UISession](uisession-service.md)（UIContentImpl 回调注册与 IPC 通道）