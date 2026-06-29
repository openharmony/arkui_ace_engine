# 应用级快捷键：去实例绑定 + 回调暴露 UIContext 方案

## Context

原方案 A（按 Container ID 隔离）虽然解决了 UIExtensionAbility 之间的快捷键污染问题，但本质上仍是**与实例绑定**的实现：注册时内部记录 `containerId`，分发时只匹配同 Container 的快捷键。这导致：

- 接口仍是 "per-Instance" 语义，不是真正的全局接口
- 同一提供方的多个 Extension 必须各自注册一遍相同组合，前者会被后者覆盖
- 开发者无法用一个"全局回调"统一处理所有实例触发的快捷键

新方向：**注册接口不与实例绑定**；当快捷键在不同实例的窗口中被按下时，**在回调参数中带上当前触发实例的 UIContext**，由开发者自行根据 UIContext 决定执行什么逻辑、是否忽略、路由到哪个上下文。这样接口是真正全局的，同时开发者仍能区分"是哪个实例触发的"。

本方案基于已有代码与 `UIObserver::GetContextValue()` 先例（`interfaces/napi/kits/observer/ui_observer.cpp:2333`），在不破坏现有 ArkUI 隔离模型的前提下实现该语义。

---

## 一、关键发现（来自代码调研）

| 主题 | 结论 | 引用 |
|------|------|------|
| 当前回调签名 | 无参数 `() => void` | `interfaces/napi/kits/application_shortcut/js_application_shortcut.cpp:98` |
| 当前回调执行机制 | 注册时捕获 `containerId_`，Post 回该 Container 的 JS 线程 | `js_application_shortcut.cpp:34-80` |
| 快捷键存储 | 进程级单例 vector，相同组合覆盖 | `frameworks/core/common/ace_application_info.h:41-50, 429-430` |
| 分发时能拿到触发实例 ID | 是，`KeyEventManager::GetInstanceId()` 返回当前焦点 Container | `frameworks/core/common/key_event_manager.cpp:488-490` |
| 取当前实例 UIContext JS 对象的现成方法 | `Container::CurrentSafely() → Frontend::GetContextValue()` | `interfaces/napi/kits/observer/ui_observer.cpp:2333-2340` |
| Frontend::GetContextValue 是公共虚函数 | 是，各 frontend 均已实现 | `frameworks/core/common/frontend.h:387`、`frameworks/bridge/declarative_frontend/declarative_frontend.cpp:971` |
| UIObserver 回调中传 UIContext 的先例 | listener 接口签名带 `napi_value context` | `interfaces/napi/kits/observer/ui_observer_listener.h:45, 60, 62` |

**跨引擎前提**：ArkUI 进程内通常共享同一 ArkTS/JS runtime，多个 Container 共享同一 `napi_env`，因此注册时的 `napi_ref` 在触发实例的 JS 线程上也可用（与 UIObserver 既有行为一致）。

---

## 二、设计要点

### 2.1 接口语义变更

| 维度 | 现状 | 新方案 |
|------|------|--------|
| 注册接口作用域 | 隐式绑定注册者 Container | 真正全局，不存任何实例信息 |
| 回调签名 | `() => void` | `(info: ApplicationShortcutCallbackInfo) => void`，info 含 `uiContext` |
| 回调执行线程 | 注册者 Container 的 JS 线程 | **触发实例**的 JS 线程（与 UIContext 参数所属实例保持一致） |
| 相同组合覆盖策略 | 后注册覆盖前注册 | 保持（全局语义） |
| Extension session 销毁 | 无清理逻辑 | 不自动清理（开发者自行 `unregister`） |

### 2.2 回调执行线程的选择

**决定**：回调在**触发实例**的 JS 线程上执行（而非注册者线程）。

理由：
1. 回调参数中的 UIContext 必须在它归属的 JS 引擎/Container 上下文里取到（`Frontend::GetContextValue()` 取的是 `Container::CurrentSafely()`，只有在触发实例的 `ContainerScope` 下才返回触发实例的 UIContext）。
2. 开发者拿到 UIContext 后，自然期望"当前回调运行的上下文 == UIContext 对应的实例"——若回调跑在另一个实例线程，开发者引用 UIContext 的 API（如 `getRouter()`、`runScopedTask`）会落到错的实例上。
3. ArkUI 进程内共享同一 ArkTS runtime，注册时的 `napi_ref` 在触发实例线程也能调用，不引入跨引擎风险。

### 2.3 开发者使用模式

```typescript
import { UIContext, registerApplicationShortcut } from '@ohos.arkui.applicationShortcut';

// 在任意一个 Extension（或主应用）中注册一次即可
registerApplicationShortcut('s', [ModifierKey.CTRL], (info) => {
  const uiContext: UIContext = info.uiContext;
  const triggerInstanceId = uiContext.getInstanceId(); // 用于区分实例

  if (uiContext === myExtAContext) {
    uiContext.getRouter().pushUrl({ url: 'save-a' });
  } else if (uiContext === myExtBContext) {
    // 焦点在 ExtB 时按 Ctrl+S 走这条分支
    doExtBSave();
  }
  // 也可以选择忽略非自己关心的实例
});
```

---

## 三、C++ 层改动清单

### 3.1 `frameworks/core/common/ace_application_info.h`

`ApplicationKeyboardShortcut` 结构不再需要实例字段（确认无需新增 containerId，与原方案 A 反向）：

```cpp
struct ApplicationKeyboardShortcut {
    std::string value;
    uint8_t keys = 0;
    std::function<void(int32_t)>&& onKeyboardShortcutAction = nullptr;  // 参数=触发 instanceId
};
```

`TryTriggerApplicationShortcut` 签名增加触发 instanceId 参数：

```cpp
bool TryTriggerApplicationShortcut(const KeyEvent& event, int32_t triggerInstanceId);
```

注册接口 `RegisterApplicationShortcut` 签名同步把 callback 改为 `std::function<void(int32_t)>`。

### 3.2 `frameworks/core/common/ace_application_info.cpp`

`TryTriggerApplicationShortcut(event, triggerInstanceId)` 中匹配命中后调用 `shortcut.onKeyboardShortcutAction(triggerInstanceId)`，把触发 instanceId 透传下去（参考现有实现 `ace_application_info.cpp:228` 附近）。

### 3.3 `frameworks/core/common/key_event_manager.cpp`

在 `DispatchKeyboardShortcut` 调用应用级快捷键处（参考 `key_event_manager.cpp:524-527`）传入触发实例 ID：

```cpp
auto& appInfo = AceApplicationInfo::GetInstance();
if (appInfo.TryTriggerApplicationShortcut(event, GetInstanceId())) {
    return true;
}
```

**SECURITY_UI_EXTENSION 屏蔽保留**（`key_event_manager.cpp:491`），其他 UIContentType 不再特殊处理（全局快捷键设计上就要跨实例生效）。

### 3.4 `interfaces/napi/kits/application_shortcut/js_application_shortcut.h`

`ApplicationShortcutCallback` 改造：

```cpp
class ApplicationShortcutCallback {
public:
    ApplicationShortcutCallback(napi_env env, napi_value callback);
    ~ApplicationShortcutCallback();
    // 新签名：传入触发实例 ID
    void Execute(int32_t triggerInstanceId);
    bool NapiEqual(napi_env env, napi_value cb);
private:
    // 移除 containerId_ 字段
    void ExecuteInner(int32_t triggerInstanceId);
    napi_env env_ = nullptr;
    napi_ref callback_ = nullptr;
};
```

### 3.5 `interfaces/napi/kits/application_shortcut/js_application_shortcut.cpp`

**构造函数去掉 `containerId_` 捕获**（替换 `js_application_shortcut.cpp:34-42`）：

```cpp
ApplicationShortcutCallback::ApplicationShortcutCallback(napi_env env, napi_value callback)
    : env_(env), callback_(nullptr)  // 不再记录 Container::CurrentIdSafely()
{
    napi_create_reference(env, callback, 1, &callback_);
}
```

**`Execute(int32_t triggerInstanceId)` 改为路由到触发实例的 JS 线程**（替换 `js_application_shortcut.cpp:52-80`）：

```cpp
void ApplicationShortcutCallback::Execute(int32_t triggerInstanceId)
{
    auto container = AceEngine::Get().GetContainer(triggerInstanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::JS)) {
        ContainerScope scope(triggerInstanceId);
        ExecuteInner(triggerInstanceId);
        return;
    }
    taskExecutor->PostTask(
        [this, triggerInstanceId]() {
            ContainerScope scope(triggerInstanceId);
            ExecuteInner(triggerInstanceId);
        },
        TaskExecutor::TaskType::JS, "ArkUIAppShortcutCallback");
}
```

**`ExecuteInner` 构造回调参数对象并调用 JS 回调**（替换 `js_application_shortcut.cpp:82-112`）：

```cpp
void ApplicationShortcutCallback::ExecuteInner(int32_t triggerInstanceId)
{
    CHECK_NULL_VOID(callback_);

    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env_, &scope);

    // 1) 取触发实例的 UIContext JS 对象（复用 UIObserver 先例）
    napi_value uiContext = nullptr;
    auto container = Container::CurrentSafely();  // ContainerScope 已经切到 triggerInstanceId
    if (container != nullptr && container->GetFrontend() != nullptr) {
        uiContext = container->GetFrontend()->GetContextValue();
    }

    // 2) 组装 ApplicationShortcutCallbackInfo = { uiContext }
    napi_value infoObj = nullptr;
    napi_create_object(env_, &infoObj);
    if (uiContext != nullptr) {
        napi_set_named_property(env_, infoObj, "uiContext", uiContext);
    } else {
        napi_value undefined = nullptr;
        napi_get_undefined(env_, &undefined);
        napi_set_named_property(env_, infoObj, "uiContext", undefined);
    }

    // 3) 调用回调
    napi_value undefined = nullptr;
    napi_get_undefined(env_, &undefined);
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value result = nullptr;
    (void)napi_call_function(env_, undefined, callback, 1, &infoObj, &result);
    // 异常处理保留
    // ...
    napi_close_handle_scope(env_, scope);
}
```

**`RegisterApplicationShortcut` 改为传入 `std::function<void(int32_t)>`**（替换 `js_application_shortcut.cpp:126-221` 注册部分）：

```cpp
auto callback = std::make_shared<ApplicationShortcutCallback>(env, argv[ARG_INDEX_TWO]);
appInfo.RegisterApplicationShortcut(value, keysValue,
    [callback](int32_t triggerInstanceId) {
        callback->Execute(triggerInstanceId);
    });
```

### 3.6 d.ts 接口声明

新增回调信息对象类型，回调签名升级（d.ts 由 interface_sdk 仓库统一管理，本仓库内只做 C++ 实现，d.ts 变更走接口评审流程）：

```typescript
interface ApplicationShortcutCallbackInfo {
  uiContext: UIContext;
}
function registerApplicationShortcut(
  value: string,
  keys: Array<ModifierKey>,
  callback: (info: ApplicationShortcutCallbackInfo) => void
): void;
```

---

## 四、关键文件列表

| 文件 | 改动 |
|------|------|
| `frameworks/core/common/ace_application_info.h:41-50, 374-382` | 数据结构与接口签名调整 |
| `frameworks/core/common/ace_application_info.cpp:179-237` | `TryTriggerApplicationShortcut` 透传 triggerInstanceId |
| `frameworks/core/common/key_event_manager.cpp:488-530` | 调用处传入 `GetInstanceId()` |
| `interfaces/napi/kits/application_shortcut/js_application_shortcut.h:30-57` | `ApplicationShortcutCallback` 类签名改造 |
| `interfaces/napi/kits/application_shortcut/js_application_shortcut.cpp:34-112, 126-221` | 去实例绑定 + 构造 UIContext 参数 |
| `interfaces/napi/kits/observer/ui_observer.cpp:2333-2340` | **仅参考**，复用 `GetContextValue` 模式 |

---

## 五、边界与限制

1. **相同组合覆盖**：全局语义，多个 Extension 注册同一组合时后者覆盖前者。建议应用层约定由统一模块注册。
2. **Extension 销毁不自动清理**：因为接口不再绑定实例。若注册者销毁后回调内引用的 UIContext 不属于它，开发者需自行判断。`Execute(triggerInstanceId)` 中拿不到 Container 时静默丢弃。
3. **跨 ArkTS runtime 不支持**：方案依赖进程内共享同一 ArkTS runtime（ArkUI 默认行为）。独立 worker 引擎场景下不保证回调 `napi_ref` 可用。
4. **SECURITY_UI_EXTENSION**：继续屏蔽（保留 `key_event_manager.cpp:491` 现有过滤）。
5. **API 兼容**：回调签名由无参变为带 `info` 参数，属不兼容变更。需走接口评审，建议在新 API 版本上声明。

---

## 六、验证方式

1. **跨实例触发路由**：
   - 同一提供方起 3 个 UIExtensionAbility（ExtA/B/C），分别在 3 个宿主中嵌入。
   - 仅在 ExtA 中调用 `registerApplicationShortcut('s', [CTRL], cb)`。
   - 在 ExtA/ExtB/ExtC 三处分别按 Ctrl+S，断言 cb 都被触发且 `info.uiContext` 分别等于 ExtA/ExtB/ExtC 的 UIContext。
2. **回调线程正确性**：cb 中读取 `info.uiContext.getRouter()` 等实例相关 API，验证落在触发实例上下文（不串到 ExtA）。
3. **生命周期**：ExtA session 销毁后，ExtB 按 Ctrl+S 仍触发 cb；cb 内若试图用 ExtA 的资源应被开发者自行保护。
4. **覆盖语义**：ExtB 后注册相同组合，验证 ExtA/ExtB/ExtC 触发都走 ExtB 的回调。
5. **主窗口不受影响**：主应用注册的快捷键在主窗口与 Extension 中都能触发，UIContext 对应实际焦点实例。
6. **安全扩展屏蔽**：SECURITY_UI_EXTENSION 焦点下按 Ctrl+S 不触发应用级快捷键。
