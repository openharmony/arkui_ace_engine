# ArkUI Entrance 入口层完整知识库

> **文档版本**：v1.1
> **更新时间**：2026-02-06
> **源码版本**：OpenHarmony ace_engine
> **作者**：基于 CLAUDE.md 规范自动生成

---

## 目录
1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Ability 系统详解](#ability-系统详解)
5. [View 系统详解](#view-系统详解)
6. [Container 系统详解](#container-系统详解)
7. [Dialog/Toast 系统详解](#dialogtoast-系统详解)
8. [子窗口管理详解](#子窗口管理详解)
9. [动态组件系统详解](#动态组件系统详解)
10. [Rosen Render 适配层详解](#rosen-render-适配层详解)
11. [事件系统详解](#事件系统详解)
12. [PA Engine 详解](#pa-engine-详解)
13. [工具类层详解](#工具类层详解)
14. [完整API清单](#完整api清单)
15. [初始化流程](#初始化流程)
16. [使用示例](#使用示例)
17. [调试指南](#调试指南)
18. [常见问题](#常见问题)

---

## 概述

### 模块定位

Entrance（入口层）是 ACE Engine 与 OpenHarmony 系统服务交互的桥梁层。它负责：

| 功能 | 说明 |
|------|------|
| **Ability 生命周期** | 管理 Ability、Service、Form 等系统能力 |
| **窗口管理** | 创建、显示、隐藏系统窗口 |
| **事件分发** | 接收系统输入事件并分发到 ACE 引擎 |
| **资源加载** | 管理资源文件和资源提供者 |
| **插件系统** | 动态加载和管理插件 |
| **子窗口支持** | 支持对话框、Toast 等子窗口类型 |
| **渲染适配** | 与 Rosen Render System 交互 |

### 功能特性

#### 官方架构图

```
┌────────────────────────────────────────────────────────────────────────────┐
│                         Application Layer                                  │
│  ┌──────────────┬──────────────┬──────────────┬──────────────┐            │
│  │   Ability    │   Service    │     Form     │   Data       │            │
│  │   (UI)       │   (BG)      │   (Card)     │  Ability     │            │
│  └──────┬───────┴──────┬───────┴──────┬───────┴──────┬───────┘            │
└─────────┼──────────────────┼──────────────────┼──────────────────┼─────────┘
          │                  │                  │                  │
          ↓                  ↓                  ↓                  ↓
┌────────────────────────────────────────────────────────────────────────────┐
│                    Entrance Layer (adapter/ohos/entrance/)                │
│  ┌──────────────┬──────────────┬──────────────┬──────────────┐            │
│  │ AceAbility    │ AceService    │ AceForm      │ AceData      │            │
│  │ Ability       │ Ability       │ Ability      │ Ability      │            │
│  │ (FA Model)    │ (Service)     │ (Card)       │ (Share)      │            │
│  └──────┬───────┴──────┬───────┴──────┬───────┴──────┬───────┘            │
│         │               │               │               │                   │
│  ┌──────┴──────┬────────┴───────┬───────┴───────┬───────┴────────┐        │
│  │AceWindow    │ DialogContainer│ SubwindowOhos │ PA Engine      │        │
│  │Listener     │ (Toast/Dialog)│ (SubWindow)   │ (Lightweight)  │        │
│  └─────────────┴────────────────┴───────────────┴────────────────┘        │
└──────────────────────────────────┬─────────────────────────────────────────┘
                                   ↓
┌────────────────────────────────────────────────────────────────────────────┐
│                         View & Container Layer                             │
│  ┌──────────────┬──────────────┬──────────────┬──────────────┐            │
│  │ AceViewOhos  │ AceContainer │ Dialog       │ Subwindow     │            │
│  │ (View)       │ (Container)  │ Container    │ Manager       │            │
│  └──────────────┴──────────────┴──────────────┴──────────────┘            │
└──────────────────────────────────┬─────────────────────────────────────────┘
                                   ↓
┌────────────────────────────────────────────────────────────────────────────┐
│                       Core Framework Layer                                 │
│  ┌──────────────────┬──────────────────┬──────────────────┐                │
│  │ Frontend         │ Pipeline         │ Pattern/Render   │                │
│  │ (ArkTS 1.1/1.2)  │ (Layout/Draw)    │ (Components)     │                │
│  └──────────────────┴──────────────────┴──────────────────┘                │
└────────────────────────────────────────────────────────────────────────────┘
                                   ↓
┌────────────────────────────────────────────────────────────────────────────┐
│                      Adapter Layer (adapter/ohos/)                         │
│  ┌──────────────┬──────────────┬──────────────┬──────────────┐            │
│  │ Rosen        │ Event        │ Resource     │ OSAL         │            │
│  │ Render       │ System       │ Manager      │ (Platform)   │            │
│  └──────────────┴──────────────┴──────────────┴──────────────┘            │
└────────────────────────────────────────────────────────────────────────────┘
```

### 设计模式

1. **适配器模式**：`AceViewOhos` 作为平台视图的适配器
2. **监听器模式**：`AceWindowListener` 实现多个 Rosen 接口
3. **工厂模式**：`ArktsDynamicRendererLoader` 动态加载渲染器
4. **单例模式**：`SubwindowManager`、`DialogContainer` 等使用单例
5. **策略模式**：不同类型的 Ability 使用不同的处理策略

### 架构演进

- **旧架构**：基于 WebView/传统渲染
- **新架构 (NG)**：基于 Rosen Render System
- **混合架构**：`AceContainerHybridImpl` 支持两种模式共存

---

## 目录结构

```
adapter/ohos/entrance/
├── 核心入口文件 (FA 模型入口)
│   ├── ace_ability.h/cpp              # FeatureAbility - 带界面的 FA 实现类
│   ├── ace_form_ability.h/cpp         # Form Ability - 卡片 Ability 实现
│   ├── ace_service_ability.h/cpp      # Service Ability - 后台服务实现
│   ├── ace_data_ability.h/cpp         # Data Ability - 数据共享实现
│   ├── ace_container.h/cpp            # 容器基类
│   ├── ace_container_hybrid_impl.cpp  # ArkTS 1.1 & 1.2 混合实例
│   ├── ui_content_impl.h/cpp          # UI 内容实现
│   └── capability_registry.h/cpp      # 能力注册表
│
├── View 系统
│   ├── ace_view_ohos.h/cpp            # OHOS 平台视图实现
│   └── ace_viewport_config.h          # 视口配置
│
├── Dialog/Toast 系统 (系统能力 Dialog 子实例)
│   ├── dialog_container.h/cpp         # 对话框容器
│   ├── dialog_container_static.cpp    # 静态对话框实现
│   └── subwindow/
│       ├── subwindow_ohos.h/cpp       # 子窗口基类实现
│       ├── subwindow_ohos_static.cpp  # 静态子窗口 (Toast/Dialog)
│       └── subwindow_ohos.cpp         # 完整子窗口实现 (117KB+)
│
├── 动态组件系统
│   ├── arkts_dynamic_renderer_loader.h/cpp       # ArkTS 动态渲染器加载器
│   ├── arkts_dynamic_component_renderer_impl.h/cpp # 动态组件渲染器
│   ├── arkts_dynamic_uicontent_impl.h/cpp        # 动态 UI 内容
│   ├── dynamic_component_renderer_impl.h/cpp     # 通用动态组件渲染器
│   ├── eaworker_task_wrapper_impl.h/cpp          # EA Worker 包装器
│   └── uv_task_wrapper_impl.h/cpp                # UV 任务包装器
│
├── PA Engine (Particle Ability - 轻量级引擎)
│   ├── pa_engine/
│   │   ├── pa_backend.h/cpp             # PA 后端实现
│   │   └── engine/
│   │       ├── common/
│   │       │   ├── js_backend_engine.h          # JS 后端引擎
│   │       │   ├── js_backend_asset_manager.h/cpp # 资产管理器
│   │       │   └── js_backend_timer_module.h/cpp  # 计时器模块
│   │       └── jsi/
│   │           ├── jsi_pa_engine.h               # JSI PA 引擎
│   │           └── jsi_pa_engine_loader.h        # JSI 加载器
│   ├── cj_utils/
│   │   └── cj_utils.h/cpp               # Cangjie (仓颉) 语言工具
│   └── pa_container.h/cpp               # PA 容器实现
│
├── 窗口管理
│   ├── window/
│   │   ├── drag_window_ohos.h/cpp      # 拖拽窗口实现
│   │   └── foldable_window_ohos.h/cpp  # 可折叠窗口实现
│   └── window_free_container.cpp       # 窗口释放容器
│
├── Picker 系统 (选择器震动反馈)
│   ├── picker_haptic_interface.h       # 震动接口定义
│   ├── picker_haptic_factory.h/cpp     # 震动工厂
│   ├── picker_haptic_impl.h/cpp        # 震动实现
│   └── picker_haptic_controller.h/cpp  # 震动控制器
│
├── 振动系统
│   └── vibrator/
│       └── vibrator_utils.cpp          # 震动工具
│
├── Rosen 适配层
│   ├── rs_adapter.h/cpp                # RS 适配器
│   ├── ace_rosen_sync_task.h           # Rosen 同步任务
│   └── ui_session/                     # UI 会话管理
│       └── ui_session_json_util.cpp    # JSON 工具
│
├── 事件系统
│   ├── ui_event_impl.h/cpp             # UI 事件实现
│   ├── mmi_event_convertor.h/cpp       # MMI 事件转换器 (57KB)
│   ├── touch_event_convertor.cpp       # 触摸事件转换
│   ├── event_pass_through_subscriber.h/cpp # 事件透传订阅器
│   ├── platform_event_callback.h       # 平台事件回调接口
│   └── ace_extra_input_data.h/cpp      # 额外输入数据
│
├── 工具类
│   ├── utils.h/cpp                     # 通用工具
│   ├── plugin_utils_impl.h/cpp         # 插件工具实现
│   ├── data_ability_helper_standard.h/cpp # 数据能力助手
│   ├── file_asset_provider_impl.h/cpp  # 文件资产提供者
│   ├── hap_asset_provider_impl.h/cpp   # HAP 资产提供者
│   ├── form_utils_impl.h/cpp           # Form 工具实现
│   └── reporter_impl.h/cpp             # 报告器实现
│
├── 其他功能
│   ├── ace_application_info.h/cpp      # 应用信息
│   ├── ace_translate_manager.cpp       # 翻译管理器
│   ├── ace_new_pipe_judgement.h/cpp    # 新管道判断
│   ├── distributed_ui_manager.h        # 分布式 UI 管理
│   ├── global_pipeline_context_manager.h/cpp # 全局管道上下文管理
│   ├── high_contrast_observer.h/cpp    # 高对比度观察者
│   ├── navigation_controller_helper.h/cpp # 导航控制器助手
│   ├── aps_monitor_impl.h/cpp          # APS 监控器
│   ├── image_task_pool_impl.h/cpp      # 图片任务池
│   ├── form_module_preloader.h/cpp     # 表单模块预加载器
│   └── tsa_advanced_feature.h          # TSA 高级特性
│
└── BUILD.gn                            # GN 编译配置
```

### 目录结构说明

#### 1. FA 模型入口 - FeatureAbility 实现

**ace_ability.h/cpp** 是 FA (FeatureAbility) 模型的入口实现类，提供带界面的 Ability 能力：

```cpp
// ace_ability.h:69
class AceAbility final : public OHOS::AppExecFwk::Ability {
public:
    // Ability 生命周期
    void OnStart(const OHOS::AAFwk::Want& want,
        sptr<AAFwk::SessionInfo> sessionInfo = nullptr) override;
    void OnActive() override;          // 激活
    void OnInactive() override;        // 去激活
    void OnForeground(...) override;   // 前台
    void OnBackground() override;      // 后台
    void OnBackPressed() override;     // 返回键
    // ... 更多生命周期方法
};
```

**关键特性**：
- 继承自 `OHOS::AppExecFwk::Ability`
- 实现完整的 Ability 生命周期
- 通过 `AceWindowListener` 处理窗口事件
- 支持跨设备迁移（Continuation）

#### 2. ArkTS 1.1 & 1.2 混合实例

**ace_container_hybrid_impl.cpp** 实现了 ArkTS 1.1 和 1.2 的混合模式：

```cpp
// ace_container_hybrid_impl.cpp:61-109
void AceContainer::InitializeStaticHybridDynamic(
    std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility)
{
    // 1.2 初始化 - 创建 ArkTS 1.2 前端
    auto arktsFrontend = ArktsFrontendLoader::GetInstance().CreatArkTsFrontend(sharedRuntime_);
    frontend_ = arktsFrontend;
    // 打开状态管理互操作
    frontend_->OpenStateMgmtInterop();

    // 1.1 初始化 - 创建声明式前端
#ifdef NG_BUILD
    subFrontend_ = AceType::MakeRefPtr<DeclarativeFrontendNG>();
#else
    subFrontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
#endif
    frontend_->SetSubFrontend(subFrontend_);

    // 创建 JS 引擎并配置
    auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
    // ... 引擎初始化
}
```

**混合模式支持**：
- **STATIC_HYBRID_DYNAMIC**: 主前端是 ArkTS 1.2，子前端是 ArkTS 1.1
- **DYNAMIC_HYBRID_STATIC**: 主前端是 ArkTS 1.1，子前端是 ArkTS 1.2
- 状态管理互操作 (`OpenStateMgmtInterop`)

#### 3. 系统能力 Dialog 子实例

**dialog_container.cpp** 和 **subwindow/** 目录实现了 Dialog 系统能力：

```cpp
// dialog_container.cpp:35-52
void DialogContainer::ShowToast(int32_t instanceId, const NG::ToastInfo& toastInfo,
    std::function<void(int32_t)>&& callback)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    auto frontend = AceType::DynamicCast<DeclarativeFrontend>(container->GetFrontend());
    auto delegate = frontend->GetDelegate();

    delegate->SetToastStopListenerCallback([instanceId]() {
        if (ContainerScope::CurrentId() >= 0) {
            AceContainer::HideWindow(instanceId);
        }
    });
    delegate->ShowToast(toastInfoNew, std::move(callback));
}
```

**Dialog/Toast 系统架构**：
- `DialogContainer`: 对话框容器基类
- `SubwindowOhos`: 子窗口实现，支持 Toast/Dialog/Menu
- `dialog_container_static.cpp`: 静态方法实现（ArkTS 1.2）
- `subwindow_ohos_static.cpp`: 静态子窗口实现

**支持的功能**：
- Toast 提示消息
- Dialog 对话框
- ActionMenu 操作菜单
- Popup 弹窗
- BindSheet 半模态转场

### 代码规模统计

| 分类 | 数量 | 说明 |
|------|--------|------|
| Ability 实现 | 4 | UI、Service、Form、Data Ability |
| 核心容器 | 3 | AceContainer、DialogContainer、PAContainer |
| View 系统 | 2 | AceViewOhos、ViewportConfig |
| 子窗口系统 | 3 | SubwindowOhos、Dialog、Static |
| 动态组件 | 8 | 动态加载器、渲染器、Worker |
| PA Engine | ~10 | 轻量级引擎支持 |
| 事件系统 | 6 | UI事件、MMI转换、触摸、键盘 |
| 窗口管理 | 4 | 拖拽、折叠、释放容器 |
| Picker/震动 | 7 | 震动反馈系统 |
| 工具类 | ~15 | 资产管理、助手、工具 |
| 总文件数 | ~75+ | 完整的入口层模块 |

---

## 核心类继承关系

```
AppExecFwk::Ability (系统基类)
├── AceAbility (UI Ability - FA 模型入口)
│   └── AceWindowListener (窗口事件监听器)
│       ├── Rosen::IWindowDragListener
│       ├── Rosen::IWindowChangeListener
│       ├── Rosen::IOccupiedAreaChangeListener
│       ├── Rosen::IAceAbilityHandler
│       ├── Rosen::IInputEventConsumer
│       └── Rosen::IAvoidAreaChangedListener
│
├── AceFormAbility (Form Ability)
│   └── IRemoteObject (远程对象)
│
├── AceServiceAbility (Service Ability)
│   └── IRemoteObject (远程对象)
│
└── AceDataAbility (Data Ability)
    └── AppExecFwk::DataAbility

AceContainer (容器基类)
├── DialogContainer (对话框容器)
├── AceContainerHybridImpl (混合容器 - ArkTS 1.1 & 1.2)
└── SubwindowOhos (子窗口)

AceView (视图基类)
└── AceViewOhos (OHOS 平台视图)

PluginUtils (插件工具基类)
└── PluginUtilsImpl (实现)

Subwindow (子窗口基类)
└── SubwindowOhos (OHOS 子窗口实现)
```

---

## Ability 系统详解

### AceAbility

位置：`adapter/ohos/entrance/ace_ability.h`

**FA 模型入口实现类**，是应用 UI 页面的入口点。

#### AceWindowListener

窗口事件监听器，实现了多个 Rosen 接口。

```cpp
class AceWindowListener : public OHOS::Rosen::IWindowDragListener,
                          public OHOS::Rosen::IWindowChangeListener,
                          public OHOS::Rosen::IOccupiedAreaChangeListener,
                          public OHOS::Rosen::IAceAbilityHandler,
                          public OHOS::Rosen::IInputEventConsumer,
                          public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    // 窗口拖拽事件
    void OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event) override;

    // 窗口大小变化事件
    void OnSizeChange(OHOS::Rosen::Rect rect, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr) override;

    // 窗口模式变化事件
    void OnModeChange(OHOS::Rosen::WindowMode mode, bool hasDeco = true) override;

    // 占用区域变化事件
    void OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr) override;

    // 输入事件消费
    bool OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const override;
    bool OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const override;
    bool OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const override;

    // 避让区域变化事件
    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type,
        const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info = nullptr) override;

    // Ace Ability 处理器
    void SetBackgroundColor(uint32_t color) override;
    uint32_t GetBackgroundColor() override;

private:
    std::shared_ptr<AceAbility> callbackOwner_;
};
```

#### AceAbility 生命周期

位置：`adapter/ohos/entrance/ace_ability.h:69-131`

```cpp
class AceAbility final : public OHOS::AppExecFwk::Ability {
public:
    // Ability 生命周期
    void OnStart(const OHOS::AAFwk::Want& want,
        sptr<AAFwk::SessionInfo> sessionInfo = nullptr) override;
    void OnStop() override;
    void OnActive() override;          // 激活
    void OnInactive() override;        // 去激活
    void OnForeground(const OHOS::AAFwk::Want& want) override;  // 前台
    void OnBackground() override;       // 后台
    void OnBackPressed() override;     // 返回键

    // 新 Want 处理
    void OnNewWant(const OHOS::AAFwk::Want& want) override;

    // 状态保存和恢复
    void OnRestoreAbilityState(const OHOS::AppExecFwk::PacMap& inState) override;
    void OnSaveAbilityState(OHOS::AppExecFwk::PacMap& outState) override;

    // 配置更新
    void OnConfigurationUpdated(const OHOS::AppExecFwk::Configuration& configuration) override;

    // Ability 结果
    void OnAbilityResult(int requestCode, int resultCode,
        const OHOS::AAFwk::Want& resultData) override;

    // 跨设备迁移
    bool OnStartContinuation() override;
    bool OnSaveData(OHOS::AAFwk::WantParams& saveData) override;
    bool OnRestoreData(OHOS::AAFwk::WantParams& restoreData) override;
    void OnCompleteContinuation(int result) override;
    void OnRemoteTerminated() override;

    // 窗口事件委托
    void OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event);
    void OnSizeChange(const OHOS::Rosen::Rect& rect, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr);
    void OnModeChange(OHOS::Rosen::WindowMode mode, bool hasDeco = true);

    // 输入事件处理
    bool OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const;
    bool OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const;
    bool OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const;

    // 其他事件
    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea& avoidArea,
        OHOS::Rosen::AvoidAreaType type,
        const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info = nullptr);

    void Dump(const std::vector<std::string>& params, std::vector<std::string>& info) override;

private:
    static const std::string START_PARAMS_KEY;
    static const std::string PAGE_URI;
    static const std::string CONTINUE_PARAMS_KEY;

    int32_t abilityId_ = -1;
    float density_ = 1.0f;
    std::string remotePageUrl_;
    std::string remoteData_;
    std::string pageUrl_;
    bool isFirstActive_ = true;
};
```

### AceFormAbility

位置：`adapter/ohos/entrance/ace_form_ability.h`

Form（卡片）Ability 实现，用于服务卡片。

### AceServiceAbility

位置：`adapter/ohos/entrance/ace_service_ability.h`

Service Ability 实现，用于后台服务。

### AceDataAbility

位置：`adapter/ohos/entrance/ace_data_ability.h`

Data Ability 实现，用于数据共享。

### CapabilityRegistry

位置：`adapter/ohos/entrance/capability_registry.h`

能力注册表，用于注册和管理应用能力。

```cpp
class CapabilityRegistry {
public:
    CapabilityRegistry() = delete;
    ~CapabilityRegistry() = delete;

    // 注册能力
    static void Register();
};
```

---

## View 系统详解

### AceViewOhos

位置：`adapter/ohos/entrance/ace_view_ohos.h`

OHOS 平台的视图实现，是连接 ACE 引擎和 Rosen 窗口的桥梁。

#### 核心属性

```cpp
class ACE_FORCE_EXPORT AceViewOhos : public AceView {
public:
    explicit AceViewOhos(int32_t id, std::unique_ptr<ThreadModelImpl> threadModelImpl);
    ~AceViewOhos() override = default;

    // 静态工厂方法
    static RefPtr<AceViewOhos> CreateView(
        int32_t instanceId, bool useCurrentEventRunner = false, bool usePlatformThread = false);
    static void SurfaceCreated(const RefPtr<AceViewOhos>& view,
        OHOS::sptr<OHOS::Rosen::Window> window);
    static void ChangeViewSize(const RefPtr<AceViewOhos>& view, int32_t width, int32_t height);
    static void SurfaceChanged(const RefPtr<AceViewOhos>& view, int32_t width, int32_t height,
        int32_t orientation, WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    static void SurfacePositionChanged(const RefPtr<AceViewOhos>& view, int32_t posX, int32_t posY);
    static void SetViewportMetrics(const RefPtr<AceViewOhos>& view, const ViewportConfig& config);
    static void TransformHintChanged(const RefPtr<AceViewOhos>& view, uint32_t transform);

    // 事件处理方法
    static void HandleMouseEvent(const RefPtr<AceViewOhos>& view,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node,
        int32_t pointerAction, bool isInjected, int32_t toolType);
    static void DispatchTouchEvent(const RefPtr<AceViewOhos>& view,
        const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr,
        const std::function<void()>& callback = nullptr, bool isInjected = false);
    static bool DispatchKeyEvent(
        const RefPtr<AceViewOhos>& view,
        const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool isPreIme = false);
    static bool DispatchRotationEvent(const RefPtr<AceViewOhos>& view, float rotationValue);

    // 性能监控
    static void DispatchEventToPerf(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    static void DispatchEventToPerf(const std::shared_ptr<MMI::KeyEvent>& keyEvent);

    static uint32_t GetBackgroundColor();

    // 启动视图
    void Launch() override;

    // 事件注册
    void RegisterTouchEventCallback(TouchEventCallback&& callback) override;
    void RegisterDragEventCallback(DragEventCallBack&& callback) override;
    void RegisterKeyEventCallback(KeyEventCallback&& callback) override;
    void RegisterNonPointerEventCallback(NonPointerEventCallback&& callback) override;
    void RegisterMouseEventCallback(MouseEventCallback&& callback) override;
    void RegisterAxisEventCallback(AxisEventCallback&& callback) override;
    void RegisterRotationEventCallback(RotationEventCallBack&& callback) override;
    void RegisterCrownEventCallback(CrownEventCallback&& callback) override;
    void RegisterTouchpadInteractionBeginCallback(TouchpadInteractionBeginCallback&& callback) override;

    // 视图变化回调
    void RegisterViewChangeCallback(ViewChangeCallback&& callback) override;
    void RegisterViewPositionChangeCallback(ViewPositionChangeCallback&& callback) override;
    void RegisterDensityChangeCallback(DensityChangeCallback&& callback) override;
    void RegisterTransformHintChangeCallback(TransformHintChangeCallback&& callback) override;
    void RegisterSystemBarHeightChangeCallback(SystemBarHeightChangeCallback&& callback) override;
    void RegisterSurfaceDestroyCallback(SurfaceDestroyCallback&& callback) override;

    // 获取实例 ID
    int32_t GetInstanceId() const override { return instanceId_; }

    // 平台资源注册
    void SetPlatformResRegister(const RefPtr<PlatformResRegister>& resRegister);
    const RefPtr<PlatformResRegister>& GetPlatformResRegister() const override;

    // 获取视图类型
    ViewType GetViewType() const override { return AceView::ViewType::SURFACE_VIEW; }

    // Dump 接口
    bool Dump(const std::vector<std::string>& params) override;
    const void* GetNativeWindowById(uint64_t textureId) override;

    // 获取线程模型
    ThreadModelImpl* GetThreadModelImpl() const { return threadModelImpl_.get(); }

private:
    // 内部处理方法
    void ProcessTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr,
        const std::function<void()>& callback = nullptr, bool isInjected = false);
    void ProcessMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr, bool isInjected = false);
    void ProcessAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr, bool isInjected = false);
    bool ProcessKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool isPreIme);

    bool ProcessFocusAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    void ProcessDigitalCrownEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        bool isInjected = false);
    bool ProcessRotationEvent(float rotationValue);
    void ProcessDragEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr);
    void ProcessDragEvent(int32_t x, int32_t y, const DragEventAction& action,
        const RefPtr<OHOS::Ace::NG::FrameNode>& node = nullptr);
    void ProcessTouchpadInteractionBegin(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);

    // 通知方法
    void NotifySurfaceChanged(int width, int height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    void NotifySurfacePositionChanged(int32_t posX, int32_t posY);
    void NotifyDensityChanged(double density) const;
    void NotifyTransformHintChanged(uint32_t transform);
    void NotifySystemBarHeightChanged(double statusBar, double navigationBar) const;
    void NotifySurfaceDestroyed() const;

    // 事件处理状态
    enum class EventState { INITIAL_STATE, HORIZONTAL_STATE, VERTICAL_STATE };

    struct TouchPointInfo {
        Offset offset_;
        EventState eventState_ = EventState::INITIAL_STATE;
        TouchPointInfo() = default;
        explicit TouchPointInfo(const Offset& offset) : offset_(offset) {}
        ~TouchPointInfo() = default;
    };

private:
    // 回调成员
    TouchEventCallback touchEventCallback_;
    MouseEventCallback mouseEventCallback_;
    AxisEventCallback axisEventCallback_;
    RotationEventCallBack rotationEventCallBack_;
    ViewChangeCallback viewChangeCallback_;
    ViewPositionChangeCallback viewPositionChangeCallback_;
    DensityChangeCallback densityChangeCallback_;
    TransformHintChangeCallback transformHintChangeCallback_;
    SystemBarHeightChangeCallback systemBarHeightChangeCallback_;
    SurfaceDestroyCallback surfaceDestroyCallback_;
    DragEventCallBack dragEventCallback_;
    KeyEventCallback keyEventCallback_;
    NonPointerEventCallback nonPointerEventCallback_;
    CrownEventCallback crownEventCallback_;
    TouchpadInteractionBeginCallback touchpadInteractionBeginCallback_;

    int32_t instanceId_ = -1;
    RefPtr<PlatformResRegister> resRegister_;
    KeyEventRecognizer keyEventRecognizer_;
    std::unordered_map<int32_t, TouchPointInfo> touchPointInfoMap_;
    std::unique_ptr<ThreadModelImpl> threadModelImpl_;
    OHOS::Ace::PointerEvent axisFakePntEvt_;

    ACE_DISALLOW_COPY_AND_MOVE(AceViewOhos);
};
```

---

## Container 系统详解

### AceContainerHybridImpl

位置：`adapter/ohos/entrance/ace_container_hybrid_impl.cpp`

**ArkTS 1.1 & 1.2 混合容器实现**，支持静态和动态两种模式。

#### 初始化流程

```cpp
// 1.2 初始化 - 静态混合模式 (STATIC_HYBRID_DYNAMIC)
void AceContainer::InitializeStaticHybridDynamic(
    std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility)
{
    // 1.2 初始化 - 创建 ArkTS 前端
    auto arktsFrontend = ArktsFrontendLoader::GetInstance().CreatArkTsFrontend(sharedRuntime_);
    if (arktsFrontend == nullptr) {
        LOGE("Create arktsFrontend failed.");
        return;
    }
    frontend_ = arktsFrontend;

    // 打开状态管理互操作
    frontend_->OpenStateMgmtInterop();

    // 1.1 初始化 - 创建声明式前端
#ifdef NG_BUILD
    subFrontend_ = AceType::MakeRefPtr<DeclarativeFrontendNG>();
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(subFrontend_);
#else
    subFrontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(subFrontend_);
#endif

    frontend_->SetSubFrontend(subFrontend_);

    // 创建 JS 引擎
    auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
    RefPtr<Framework::JsEngine> jsEngine;
    if (GetSettings().usingSharedRuntime) {
        jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, nullptr);
    } else {
        jsEngine = loader.CreateJsEngine(instanceId_);
    }

    // 添加额外的原生对象
    jsEngine->AddExtraNativeObject("ability", aceAbility.get());

    // 设置页面 URL 检查函数
    auto pageUrlCheckFunc = [id = instanceId_](...) { ... };
    jsEngine->SetPageUrlCheckFunc(std::move(pageUrlCheckFunc));

    // 注册引擎
    EngineHelper::AddEngine(instanceId_, jsEngine);
    declarativeFrontend->SetJsEngine(jsEngine);
    declarativeFrontend->SetPageProfile(pageProfile_);
    declarativeFrontend->SetNeedDebugBreakPoint(
        AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
    declarativeFrontend->SetDebugVersion(
        AceApplicationInfo::GetInstance().IsDebugVersion());
}

// 1.2 初始化 - 动态混合模式 (DYNAMIC_HYBRID_STATIC)
void AceContainer::InitializeDynamicHybridStatic(
    std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility)
{
    // 1.2 initialization
    auto preloadArkTSRuntime = ArkTSModulePreloader::GetArkTSRuntime();
    auto arktsFrontend = ArktsFrontendLoader::GetInstance().CreatArkTsFrontend(preloadArkTSRuntime);
    if (arktsFrontend == nullptr) {
        LOGE("Create arktsFrontend failed.");
        return;
    }
    subFrontend_ = arktsFrontend;
    // open statemanagement interop
    subFrontend_->OpenStateMgmtInterop();

    // 1.1 initialization
    if (isFormRender_) {
        // Form Frontend for cards
        frontend_ = AceType::MakeRefPtr<FormFrontendDeclarative>();
        // ... form specific initialization
    } else if (!isSubContainer_) {
        frontend_ = AceType::MakeRefPtr<DeclarativeFrontendNG>();
        frontend_->SetSubFrontend(subFrontend_);
        // ... main container initialization
    } else {
        frontend_ = OHOS::Ace::Platform::AceContainer::GetContainer(parentId_)->GetFrontend();
        frontend_->SetSubFrontend(subFrontend_);
    }
}
```

**混合模式类型**：
1. **STATIC_HYBRID_DYNAMIC**: ArkTS 1.2 为主 + ArkTS 1.1 为子
2. **DYNAMIC_HYBRID_STATIC**: ArkTS 1.1 为主 + ArkTS 1.2 为子

---

## Dialog/Toast 系统详解

### DialogContainer

位置：`adapter/ohos/entrance/dialog_container.h`

**系统能力 Dialog 子实例**，负责管理 Toast 和 Dialog 的显示。

#### 接口方法

```cpp
class DialogContainer : public AceContainer {
public:
    explicit DialogContainer(int32_t instanceId, FrontendType type = FrontendType::DECLARATIVE_JS);
    ~DialogContainer() override = default;

    bool IsDialogContainer() const override { return true; }

    // Toast 显示
    static void ShowToast(int32_t instanceId, const NG::ToastInfo& toastInfo,
        std::function<void(int32_t)>&& callback);
    static void CloseToast(int32_t instanceId, const int32_t toastId,
        std::function<void(int32_t)>&& callback);

    // Dialog 显示
    static void ShowDialog(int32_t instanceId, const std::string& title,
        const std::string& message, const std::vector<ButtonInfo>& buttons,
        bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);
    static void ShowDialog(int32_t instanceId, const PromptDialogAttr& dialogAttr,
        const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string> callbacks);

    // 操作菜单
    static void ShowActionMenu(int32_t instanceId, const std::string& title,
        const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);

    // 窗口管理
    static bool ShowToastDialogWindow(int32_t instanceId, int32_t posX, int32_t posY,
        int32_t width, int32_t height, bool isToast = false);
    static bool OnBackPressed(int32_t instanceId);

    // ArkTS 1.2 静态方法
    static void ShowToastStatic(int32_t instanceId, const NG::ToastInfo& toastInfo,
        std::function<void(int32_t)>&& callback);
    static void CloseToastStatic(int32_t instanceId, const int32_t toastId,
        std::function<void(int32_t)>&& callback);
    static void ShowDialogStatic(int32_t instanceId, const DialogProperties& dialogProps,
        std::function<void(int32_t, int32_t)>&& callback);
    static void ShowActionMenuStatic(int32_t instanceId, const DialogProperties& dialogProps,
        std::function<void(int32_t, int32_t)>&& callback);

private:
    ACE_DISALLOW_COPY_AND_MOVE(DialogContainer);
};
```

### SubwindowOhos

位置：`adapter/ohos/entrance/subwindow/subwindow_ohos.h`

子窗口基类，支持 Toast、Dialog、Menu、Popup 等多种子窗口类型。

#### Toast 显示流程

```
ShowToastStatic()
        ↓
┌─────────────────────────────┐
│ 判断服务类型              │
│ PA Service: MIN_PA_SERVICE_ID │
│ Ability: 其他               │
└─────────────────────────────┘
        ↓
┌──────────────┬──────────────┐
│ Service 路径 │ Ability 路径  │
└──────────────┴──────────────┘
        ↓
Service: ShowToastForServiceStatic()
Ability: ShowToastForAbilityStatic()
        ↓
┌─────────────────────────────────┐
│ 设置 Toast 窗口属性       │
│ 创建窗口                    │
│ 初始化视图                 │
│ 配置服务                   │
│ 显示窗口                    │
└─────────────────────────────────┘
        ↓
NG::DialogManagerStatic::ShowToastStatic()
```

---

## 子窗口管理详解

### SubwindowManager

子窗口管理器，负责管理所有子窗口（Toast、Dialog 等）的创建、显示和销毁。

### 窗口类型

| 类型 | 说明 |
|------|------|
| **Toast** | 提示消息窗口 |
| **Dialog** | 对话框窗口 |
| **ActionMenu** | 操作菜单窗口 |
| **Picker** | 选择器窗口 |
| **Drag Window** | 拖拽窗口 |
| **Foldable Window** | 可折叠窗口 |

---

## 动态组件系统详解

### ArktsDynamicRendererLoader

位置：`adapter/ohos/entrance/dynamic_component/arkts_dynamic_renderer_loader.h`

ArkTS 动态渲染器加载器，用于动态加载组件渲染器。

#### 接口方法

```cpp
class ACE_FORCE_EXPORT ArktsDynamicRendererLoader {
public:
    // 单例获取
    static ArktsDynamicRendererLoader& GetInstance() {
        static ArktsDynamicRendererLoader instance;
        return instance;
    }

    // 创建 EA Worker 任务包装器
    TaskWrapper* CreatEaWorkerTaskWrapper(int32_t hostInstanceId, int32_t workerId);

    // 获取当前线程 JSI 环境
    void* GetCurrentThreadAniEnv();

private:
    ArktsDynamicRendererLoader() {
        DynamicLoadLibrary();
    }

    ~ArktsDynamicRendererLoader() {
        CloseLibrary();
    }

    void CloseLibrary();
    void* LoadSymbol(const char* symName);
    bool DynamicLoadLibrary();

private:
    LIBHANDLE handle_ = nullptr;
    CreatEaWorkerTaskWrapperFunc creatEaWorkerTaskWrapperFunc_ = nullptr;
    GetCurrentThreadAniEnvFunc getCurrentThreadAniEnvFunc_ = nullptr;
};
```

---

## Rosen Render 适配层详解

### RsAdapter

位置：`adapter/ohos/entrance/rs_adapter.h`

Rosen Render System 适配器，用于与 RS 渲染系统交互。

```cpp
class RsAdapter {
public:
    RsAdapter() = default;
    ~RsAdapter() = default;

    // RS UI Director 初始化
    static void RsUIDirectorInit(
        std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
        const OHOS::sptr<OHOS::Rosen::Window>& window,
        std::string cacheDir);

    // RS 隐式事务刷新
    static void RsFlushImplicitTransaction(
        std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
        const OHOS::sptr<OHOS::Rosen::Window>& dragWindow,
        std::shared_ptr<OHOS::Rosen::RSSurfaceNode>& surfaceNode);

    static void RsFlushImplicitTransactionWithRoot(
        std::shared_ptr<OHOS::Rosen::RSUIDirector>& rsUiDirector,
        const OHOS::sptr<OHOS::Rosen::Window>& dragWindow,
        std::shared_ptr<OHOS::Rosen::RSSurfaceNode>& surfaceNode,
        std::shared_ptr<Rosen::RSNode>& rootNode);

    // 获取 RS UI 上下文
    static std::shared_ptr<Rosen::RSUIContext> GetRSUIContext(
        const RefPtr<PipelineBase>& pipeline);

private:
    static void FlushImplicitTransaction();
};
```

---

## 事件系统详解

### UiEventImpl

位置：`adapter/ohos/entrance/ui_event_impl.h`

UI 事件实现。

### MmiEventConvertor

位置：`adapter/ohos/entrance/mmi_event_convertor.h`

MMI 事件转换器，用于将系统输入事件转换为 ACE 引擎可以识别的事件格式。

### TouchEventConvertor

位置：`adapter/ohos/entrance/touch_event_convertor.cpp`

触摸事件转换器，专门处理触摸事件转换。

### PlatformEventCallback

位置：`adapter/ohos/entrance/platform_event_callback.h`

平台事件回调接口。

---

## PA Engine 详解

### 概述

PA (Particle Ability) Engine 是为特殊场景（如手表、物联网设备）设计的轻量级引擎。

### 目录结构

```
pa_engine/
├── pa_backend.h/cpp                  # PA 后端
├── engine/
│   ├── common/
│   │   ├── js_backend_engine.h          # JS 后端引擎
│   │   ├── js_backend_asset_manager.h/cpp # 资产管理器
│   │   └── js_backend_timer_module.h/cpp  # 计时器模块
│   └── jsi/
│       ├── jsi_pa_engine.h            # JSI PA 引擎
│       ├── jsi_pa_engine_loader.h     # JSI 加载器
│       └── paMgmt.js                   # PA 管理 JS
```

### JsBackendEngine

JS 后端引擎，为 PA 场景提供 JavaScript 运行时支持。

---

## 工具类层详解

### PluginUtilsImpl

位置：`adapter/ohos/entrance/plugin_utils_impl.h`

插件工具实现。

### DataAbilityHelperStandard

位置：`adapter/ohos/entrance/data_ability_helper_standard.h`

数据能力助手，用于简化 Data Ability 的调用。

### FileAssetProviderImpl

位置：`adapter/ohos/entrance/file_asset_provider_impl.h`

文件资产提供者实现。

### Utils

位置：`adapter/ohos/entrance/utils.h`

通用工具类。

---

## 完整API清单

### AceAbility API

| 分类 | 方法 |
|------|------|
| **生命周期** | `OnStart`, `OnStop`, `OnActive`, `OnInactive`, `OnForeground`, `OnBackground`, `OnBackPressed` |
| **Want 处理** | `OnNewWant` |
| **状态保存** | `OnRestoreAbilityState`, `OnSaveAbilityState` |
| **配置更新** | `OnConfigurationUpdated` |
| **Ability 结果** | `OnAbilityResult` |
| **跨设备迁移** | `OnStartContinuation`, `OnSaveData`, `OnRestoreData`, `OnCompleteContinuation`, `OnRemoteTerminated` |
| **窗口事件** | `OnDrag`, `OnSizeChange`, `OnModeChange`, `OnAvoidAreaChanged` |
| **输入事件** | `OnInputEvent` (KeyEvent, PointerEvent, AxisEvent) |
| **Ace Ability 处理** | `SetBackgroundColor`, `GetBackgroundColor` |
| **调试** | `Dump` |

### DialogContainer API

| 分类 | 方法 |
|------|------|
| **Toast** | `ShowToast`, `CloseToast`, `ShowToastStatic`, `CloseToastStatic` |
| **Dialog** | `ShowDialog`, `ShowDialogStatic` |
| **ActionMenu** | `ShowActionMenu`, `ShowActionMenuStatic` |
| **窗口管理** | `ShowToastDialogWindow`, `OnBackPressed` |
| **类型判断** | `IsDialogContainer` |

---

## 初始化流程

### Ability 启动流程

```
┌──────────────────────────────────────────────────────┐
│ OpenHarmony System                      │
│ AbilityManager::StartAbility(want)         │
└──────────────────┬───────────────────────────┘
                   ↓
┌──────────────────────────────────────────────────────┐
│ AceAbility::OnStart(want, sessionInfo)       │
└──────────────────┬───────────────────────────┘
                   ↓
┌──────────────────────────────────────────────────────┐
│ 1. 创建 AceWindowListener                  │
│ 2. 创建 Rosen 窗口                     │
│ 3. 创建 AceViewOhos                     │
│ 4. 初始化 AceContainer                  │
└──────────────────┬───────────────────────────┘
                   ↓
┌──────────────────────────────────────────────────────┐
│ AceContainer::InitializeStaticHybridDynamic()    │
└──────────────────┬───────────────────────────┘
                   ↓
┌──────────────────────────────────────────────────────┐
│ 1.2 初始化                              │
│   - 创建 ArkTS 前端                   │
│   - 打开状态管理互操作                   │
│                                           │
│ 1.1 初始化                              │
│   - 创建声明式前端                     │
│   - 加载 JS 引擎                        │
│   - 添加原生对象                        │
│   - 注册引擎到 Helper                  │
└──────────────────┬───────────────────────────┘
                   ↓
┌──────────────────────────────────────────────────────┐
│ Frontend 初始化完成                        │
│ - 设置页面配置                            │
│ - 设置调试选项                            │
└──────────────────┬───────────────────────────┘
                   ↓
┌──────────────────────────────────────────────────────┐
│ 管道准备完成                              │
│ - Ready to process UI content               │
└──────────────────────────────────────────────┘
```

---

## 常见问题

### Q1: Ability 启动后没有显示 UI？

**可能原因**：
1. 页面 URI 配置错误
2. 窗口创建失败
3. 前端初始化失败
4. 资源加载失败

**解决方法**：
```bash
# 1. 检查 Ability 配置
cat config.json

# 2. 检查日志
hdc shell "hilog -T AbilityManager | grep MyAbility"

# 3. 使用 Dump 检查状态
hdc shell "aa dump -a com.example.app -c"
```

### Q2: Toast 不显示？

**可能原因**：
1. 父容器 ID 错误
2. 窗口大小计算错误
3. 显示模式配置不正确

**解决方法**：
```cpp
// 检查容器 ID
auto aceContainer = Platform::AceContainer::GetContainer(childContainerId_);
if (!aceContainer) {
    LOGE("Get container failed, child containerId : %{public}d", childContainerId_);
    return;
}

// 检查显示模式
if (toastInfo.showMode == NG::ToastShowMode::TOP_MOST) {
    // TOP_MOST 需要特殊处理
    ResizeWindow();
}
```

---

## 附录

### 参考文档

- [ACE Engine 项目文档](../CLAUDE.md)
- [Accessibility 知识库](../accessibility/accessibility_base_README.md)
- [OpenHarmony Ability 文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-guides-V5/ability-start-V5)
- [Rosen Render 文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/graphics-rosen-V5)

### 源码索引

| 模块 | 路径 |
|--------|--------|
| Ability 系统 | `adapter/ohos/entrance/ace_ability.h`, `ace_form_ability.h`, `ace_service_ability.h` |
| View 系统 | `adapter/ohos/entrance/ace_view_ohos.h` |
| Dialog/Toast | `adapter/ohos/entrance/dialog_container.h`, `subwindow/` |
| 动态组件 | `adapter/ohos/entrance/dynamic_component/` |
| PA Engine | `adapter/ohos/entrance/pa_engine/` |
| Rosen 适配 | `adapter/ohos/entrance/rs_adapter.h` |
| 事件系统 | `adapter/ohos/entrance/ui_event_impl.h`, `mmi_event_convertor.h` |
| 工具类 | `adapter/ohos/entrance/plugin_utils_impl.h`, `utils.h` |

### 更新日志

| 日期 | 版本 | 更新内容 |
|------|--------|----------|
| 2026-02-06 | v1.1 | 更新架构图为官方版本；完善目录结构说明；添加 FA 模型入口、ArkTS 混合实例、Dialog 子实例详解 |
| 2026-02-03 | v1.0 | 初始版本，完整分析 Entrance 模块 |

---

> 本文档基于 `master` 分支源码分析生成，遵循 [CLAUDE.md](../CLAUDE.md) 规范。如有疑问，请参考实际源码。
