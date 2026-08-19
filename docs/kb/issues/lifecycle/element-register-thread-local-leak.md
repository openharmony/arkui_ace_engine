# ElementRegister 线程局部单例内存泄漏与 VM 生命周期稳定性风险 Issue Context

> 文档版本：v2.4
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `ElementRegisterThreadLocalLeak`
> 关联功能域：FuncID `03-06-01`

## 问题概述

历史实现中，`ElementRegister` 的线程局部单例存在两个生命周期问题：

1. `thread_local` 裸指针通过 `new` 创建实例，但没有对应析构释放路径，线程退出后堆对象仍未释放。
2. 长生命周期的 `ElementRegister` 单例保存了依赖 `EcmaVM` 的清理回调。`ElementRegister` 的持有周期可能长于关联 `EcmaVM`，使回调捕获的 `JSRef<JSFunc>` 和 `JSRef<JSObject>` 在 `ArkJSRuntime::Reset()` 后仍由单例持有，形成潜在稳定性风险。

当前实现使用 `ElementRegisterHolder` 管理 `ElementRegisterImpl` 的线程级生命周期，并将 JS 清理调用链迁移至 `Frontend` 和 `JsiDeclarativeEngineInstance`。`ElementRegister` 已不再保存该回调；`JsiDeclarativeEngineInstance` 通过 `uiNodeCleanUpIdleFunc_` 缓存 JS 函数，并在调用前检查 `runtime_` 和 global 对象。

线程退出内存泄漏已由 `ElementRegisterHolder` 建立释放路径。回调所有权迁移已经源码验证，但当前 `JsiDeclarativeEngineInstance` 析构函数在成员自动析构前调用 `ArkJSRuntime::Reset()`；`uiNodeCleanUpIdleFunc_` 持有的 `ArkJSValue::value_`（`panda::Global<panda::JSValueRef>`）是否始终在 `EcmaVM` 销毁前释放仍需专项验证，因此不能将稳定性风险标记为完全修复。具体故障表现由源码生命周期关系推导，暂无专项故障用例直接验证。

典型表现：

- 调用 `ElementRegister::GetInstance()` 的短生命周期线程退出后，历史实现创建的实例未释放
- 重复创建和退出相关线程时，泄漏量随调用线程数量增长
- `ArkJSRuntime::Reset()` 后，历史线程局部 `ElementRegister` 仍可能持有捕获该 `EcmaVM` 对象的回调
- 回调释放时，捕获的 `JSRef` 会通过 `JsiRef::Reset()` 释放 `panda::CopyableGlobal`，其持有周期不得超过关联 `EcmaVM`
- 此专项线程退出泄漏及 VM 关联回调生命周期回归测试在 `ace_engine` 中未找到

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | symptom_surface | ElementRegister | `frameworks/core/pipeline/base/element_register.cpp` | verified |
| architecture | root_cause_owner | ElementRegister 线程局部实例生命周期 | 历史 `thread_local ElementRegister*` 与 `new ElementRegister()` 实现 | verified |
| architecture | root_cause_owner | VM 关联回调所有权 | 历史 `jsCleanUpIdleTaskCallback_` 保存捕获 `JSRef` 对象的回调 | verified |
| capability | trigger | PipelineContext Idle 清理 | 历史 `PipelineContext::OnIdle` 直接调用 ElementRegister 回调 | verified |
| architecture | dependency | JSI Runtime / EcmaVM | `uiNodeCleanUpIdleTask` 依赖 `ArkJSRuntime`、global 对象和 JS 函数对象 | verified |
| architecture | fix_location | ElementRegisterHolder / ElementRegisterImpl | 当前线程级 RAII 析构路径 | verified |
| architecture | fix_location | Frontend / JsiDeclarativeEngineInstance | 当前清理调用链以及 `runtime_`、global 对象的空指针检查 | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| A. `new` 创建的线程局部实例无释放路径 | `thread_local T*` 保存通过 `new T()` 创建的对象，未建立拥有者或析构逻辑 | 调用 `GetInstance()` 的线程结束后，指针变量销毁但堆对象未释放 |
| B. 回调持有者生命周期长于关联 EcmaVM | 线程级单例保存捕获 `JSRef<JSFunc>` 和 `JSRef<JSObject>` 的回调，而 `ArkJSRuntime::Reset()` 可在线程结束前销毁 `EcmaVM` | `ElementRegister` 在 `EcmaVM` 销毁后仍持有该回调对象 |

## 排查路径

### 快速判断

1. 检查线程局部变量是否为裸指针，并通过 `new` 创建对象。
2. 检查线程退出时是否存在对应的 `delete`、Holder 或智能指针析构路径。
3. 检查单例是否保存 `JSRef`、`ArkJSRuntime`、`EcmaVM` 或依赖这些对象的回调。
4. 对比回调持有者、线程、Frontend、JS Engine 和 `EcmaVM` 的销毁顺序。
5. 检查 `JsiRef::Reset()`、`panda::CopyableGlobal<T>::Reset()` 或 `panda::Global<panda::JSValueRef>::FreeGlobalHandleAddr()` 是否在 `ArkJSRuntime::Reset()` 前执行。
6. 检查 `ArkJSRuntime::Reset()` 销毁 `EcmaVM` 前是否可靠清除所有外部保存的 VM 关联对象。

### 详细排查

#### A. `new` 内存泄漏排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查 `GetInstance()` 使用的线程局部变量类型 | 使用具有析构语义的 Holder 或智能指针 | 裸指针配合 `new` 存在泄漏风险 |
| 2 | 检查实例的唯一拥有者 | 实例具有明确且唯一的线程级拥有者 | 无拥有者则无法随线程退出释放 |
| 3 | 检查 Holder 析构函数 | 析构时释放实例并将指针置空 | 未释放则泄漏仍然存在 |
| 4 | 检查是否存在多个 Holder | 每个线程只应有一个 Holder 管理实例 | 多个 Holder 可能覆盖指针或造成重复生命周期管理 |
| 5 | 使用线程创建、调用和退出场景进行检测 | 线程退出后实例相关内存被释放 | 仍有残留则继续检查线程局部析构路径 |

关键代码定位：

- `frameworks/core/pipeline/base/element_register.cpp::ElementRegisterHolder`
- `frameworks/core/pipeline/base/element_register.cpp::ElementRegister::GetInstance`
- `frameworks/core/pipeline/base/element_register.cpp::g_instance`
- commit `0dda403c541`：引入线程局部裸指针和 `new ElementRegister()`
- commit `23feb939a8f`：引入 `ElementRegisterImpl` 和函数局部 Holder 生命周期管理，建立线程退出释放路径
- commit `4e76ac91de8`：移除未引用的命名空间级重复 Holder，保留函数局部 Holder

#### B. 回调持有者生命周期长于关联 EcmaVM 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查清理回调的捕获对象 | 不应由线程级单例长期保存 `EcmaVM` 关联对象 | 捕获 `JSRef`、global 对象或 `ArkJSRuntime` 时继续检查持有周期 |
| 2 | 检查回调持有者 | 持有者的销毁和显式清理应早于关联 `EcmaVM` 销毁 | 持有者生命周期更长时存在 VM 关联对象超期持有风险 |
| 3 | 检查 `ArkJSRuntime::Reset()` 前的清理流程 | `uiNodeCleanUpIdleFunc_` 等 VM 关联对象在 `DestroyJSVM` 前完成 Reset 或析构 | `ArkJSRuntime::Reset()` 后仍保留 VM 关联对象时需要继续验证句柄释放顺序 |
| 4 | 检查句柄释放路径 | `JsiRef::Reset()` 或 `ArkJSValue::~ArkJSValue()` 在所属 `EcmaVM` 有效期间释放 global handle | `EcmaVM` 销毁后才执行 `ArkJSValue::~ArkJSValue()` 中的 `value_.FreeGlobalHandleAddr()` 时存在稳定性风险 |
| 5 | 覆盖 `ArkJSRuntime::Reset()` 与线程退出顺序 | `ElementRegister` 不再持有该 `EcmaVM` 的回调，EngineInstance 的缓存对象在 VM 销毁前释放 | 仅完成所有权迁移但未确认释放顺序时，不能判定风险已完全修复 |

历史风险路径：

- `jsi_view_register_impl.cpp::JsUINodeRegisterCleanUp`：回调捕获 `JSRef<JSFunc>` 和 `JSRef<JSObject>`
- `element_register.h::RegisterJSCleanUpIdleTaskFunc`：将回调保存在 ElementRegister 中
- `jsi_ref.h::JsiRef::~JsiRef`：销毁 `JSRef` 时调用 `JsiRef::Reset()`，进而释放 `panda::CopyableGlobal`
- `JsiDeclarativeEngineInstance` 析构：VM Runtime 可在线程退出前完成 Reset

当前修复路径：

- `frameworks/core/pipeline_ng/pipeline_context.cpp::PipelineContext::OnIdle`
- `frameworks/core/common/frontend.h::CallStateMgmtCleanUpIdleTaskFunc`
- `frameworks/bridge/declarative_frontend/declarative_frontend.cpp::CallStateMgmtCleanUpIdleTaskFunc`
- `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp::CallStateMgmtCleanUpIdleTaskFunc`
- `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp::JsiDeclarativeEngineInstance::~JsiDeclarativeEngineInstance`
- `frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h::ArkJSValue::~ArkJSValue`
- `frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.cpp::ArkJSRuntime::Reset`

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| A. `new` 内存泄漏 | 使用唯一的线程局部 Holder 管理实现对象，在线程退出时执行析构释放 | `element_register.cpp` 中的 `ElementRegisterHolder`、`g_instance` 和 `GetInstance` | `23feb939a8f` (`fixed`)、`4e76ac91de8` (`follow_up`) | `23feb939a8f` 已引入函数局部 Holder 及析构释放；后续提交移除未引用的重复 Holder |
| B. 回调持有者生命周期长于关联 EcmaVM | 将 VM 关联回调从 `ElementRegister` 迁移至 Frontend/JS Engine，并确保 `uiNodeCleanUpIdleFunc_` 等缓存对象在 `ArkJSRuntime::Reset()` 前释放 | `frontend.h`、`declarative_frontend.cpp`、`jsi_declarative_engine.cpp`、`pipeline_context.cpp` | `23feb939a8f` (`mitigated`)；释放顺序待后续闭环 | 提交已删除 `ElementRegister` 回调成员和注册入口，改由 EngineInstance 保存 JS 函数；当前析构顺序尚不能证明 VM 关联句柄始终先于 `DestroyJSVM` 释放 |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 引入线程局部裸指针，通过 `new` 创建 ElementRegister | A | introduced | commit `0dda403c541` diff | verified |
| CHG-02 | 将捕获 `JSRef<JSFunc>` 和 `JSRef<JSObject>` 的 JS 清理回调保存至 ElementRegister | B | introduced | commit `ef53352261b` diff | verified |
| CHG-03 | 将已有回调合并为 Idle 清理回调，并由 PipelineContext::OnIdle 直接调用 | B | related | commit `6744b0a3b76` diff | verified |
| CHG-04 | 引入 ElementRegisterImpl 和函数局部 Holder，在线程退出时析构释放实例 | A | fixed | commit `23feb939a8f` diff | verified |
| CHG-05 | 将清理回调迁移至 Frontend 和 JsiDeclarativeEngineInstance，移除 ElementRegister 对 VM 关联回调的持有 | B | mitigated | commit `23feb939a8f` diff 证明所有权迁移；EngineInstance 析构中的句柄释放顺序仍需验证 | verified |
| CHG-06 | 移除未引用的命名空间级重复 Holder，保留函数局部 Holder | A | follow_up | commit `4e76ac91de8` diff | verified |

## 预防措施

- 禁止使用无拥有者的 `thread_local` 裸指针配合 `new` 创建单例。
- 线程局部堆对象必须由唯一的 Holder、`unique_ptr` 或其他 RAII 对象管理。
- `EcmaVM` 关联的 JS 函数、global 对象、`ArkJSRuntime` 和回调应由对应 Frontend 或 JS Engine 实例持有。
- 回调持有者不得长于其关联 `EcmaVM`；确需跨生命周期持有时，必须在 `ArkJSRuntime::Reset()` 前显式 Reset VM 关联对象。
- 异步、Idle 和延迟任务执行 VM 回调前必须验证 Frontend、JS Engine、`runtime_` 和 global 对象。
- 新增短生命周期线程退出后的内存释放测试。
- 新增 `uiNodeCleanUpIdleFunc_`、`ArkJSRuntime::Reset()` 和 `ArkJSValue::~ArkJSValue()` 释放顺序的回归测试。
- 故障现象未经测试或问题单验证时，应标记为“推断”，不得写成已发生的确定性崩溃。

## 相关主题

- `docs/kb/architecture/multi-instance-management.md`
- `docs/kb/frontend/state_management/cpp-bindings.md`
- `docs/kb/capabilities/frame-node.md`
- `frameworks/core/pipeline/base/element_register.cpp`
- `frameworks/core/common/frontend.h`
- `frameworks/core/pipeline_ng/pipeline_context.cpp`
- `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp`