# etc 目录 ABC 文件加载失败 Issue Context

> 文档版本：v3.3
> 更新时间：2026-08-08
> 来源：`docs/context_registry.json` 主题 `EtcAbcLoadingFailure`
> 关联功能域：FuncID `06-01-02`

## 问题概述

在标准系统开启 `STATE_MGMT_USE_AOT` 的构建中，变更 `8f63bcc36fa` 扩大了
`ExecuteJsBinForAOT` 的使用范围，使 `jsPreload.abc` 从调用 `EvaluateJsCode` 改为调用 `ExecuteJsBinForAOT` 进行绝对路径执行。

`jsPreload.abc` 在 appspawn 中完成预加载后，其 `JSPandaFile` 可能因 SharedGC 清理无存活引用的共享常量池而
从 `loadedJSPandaFiles_` 移除。应用创建阶段再次触发该 `JSPandaFile` 加载时，`loadedJSPandaFiles_` 和 `AbcBufferCache` 均未命中，
运行时在 `EcmaVM::IsBundlePack()` 返回 `false`、`ModuleManager::GetExecuteMode()` 返回 `ModuleExecuteMode::ExecuteBufferMode`、
`EcmaVM::IsRestrictedWorkerThread()` 返回 `false` 的场景下进入 HSP 加载分支。由于
`/etc/abc/framework/jsPreload.abc` 不是合法 HAP/HSP 路径，最终触发
`Invalid input hsp path` 的 `LOG_FULL(FATAL)`。

典型表现：

- appspawn 阶段 `jsPreload.abc` 预加载成功，应用创建阶段却加载失败
- 失败前可能出现 `remove js pandafile by gc`，文件名为 `jsPreload.abc`
- 随后出现 `Invalid input hsp path: /etc/abc/framework/jsPreload.abc`
- 文件实际存在且可读，单纯检查部署路径和权限无法解释问题
- 回归范围包含 `8f63bcc36fa`、不包含 `e6c594f0c29` 时容易命中

当前覆盖范围：仅覆盖 `8f63bcc36fa` 引入的 `jsPreload.abc` 历史回归链路，不代表所有
`/etc/abc` 文件加载失败都由同一原因导致。

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | trigger | AppSpawn Runtime Preload | `<OH_ROOT>/base/startup/appspawn/modules/ace_adapter/ace_adapter.cpp` 设置 `loadAce=true`、`preload=true` 并保存预加载 Runtime | verified |
| architecture | symptom_surface | ArkUI Declarative Frontend Preload | `8f63bcc36fa:frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` | verified |
| architecture | dependency | AbilityRuntime 预加载 Runtime 复用 | `<OH_ROOT>/foundation/ability/ability_runtime/frameworks/native/runtime/js_runtime.cpp` | verified |
| architecture | root_cause_owner | ArkTS Runtime SharedGC 与 JSPandaFile 管理 | `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/runtime.cpp`、`ecmascript/jspandafile/js_pandafile_manager.cpp` | verified |
| capability | fix_location | ArkUI `EvaluateAbcFile` | `e6c594f0c29` 将 `EvaluateAbcFile` 恢复为读取文件后调用 `EvaluateJsCode` | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| A. 绝对路径加载范围被扩大 | 标准系统开启 `STATE_MGMT_USE_AOT`，`EvaluateAbcFile` 的所有调用统一进入 `ExecuteJsBinForAOT` | 原本通过 `EvaluateJsCode` 执行的系统 ABC 文件被改为绝对路径执行 |
| B. appspawn 预加载 JSPandaFile 被 SharedGC 移除 | 预加载文件的共享常量池已无存活引用，SharedGC 清空对应常量池后调用 `RemoveJSPandaFile` | appspawn 已执行系统 ABC 文件，但应用创建前后 `loadedJSPandaFiles_` 中已不存在对应 `JSPandaFile` |
| C. 缓存未命中后进入 HSP 路径校验 | `loadedJSPandaFiles_` 和 `AbcBufferCache` 均未命中，同时 `EcmaVM::IsBundlePack()` 返回 `false`、`ModuleManager::GetExecuteMode()` 返回 `ModuleExecuteMode::ExecuteBufferMode`、`EcmaVM::IsRestrictedWorkerThread()` 返回 `false` | 位于 `/etc/abc/framework/` 的系统 ABC 文件被传入 `ModulePathHelper::ParseHapPath`，返回空路径并触发 `LOG_FULL(FATAL)` |

## 排查路径

### 快速判断

1. 使用 `git show 8f63bcc36fa` 和 `git show e6c594f0c29` 确认代码是否位于回归区间。
2. 确认失败文件是否为 `/etc/abc/framework/jsPreload.abc`。
3. 检查 appspawn 与应用进程日志中是否依次出现预加载、`remove js pandafile by gc` 和
   `Invalid input hsp path`。
4. 确认失败时 `EcmaVM::IsBundlePack()` 和 `EcmaVM::IsRestrictedWorkerThread()` 是否均返回 `false`，`ModuleManager::GetExecuteMode()` 是否返回 `ModuleExecuteMode::ExecuteBufferMode`。
5. 若加载表未被 SharedGC 清理，或没有进入 HSP 分支，则不属于本历史根因。

### 详细排查

#### A. 绝对路径加载范围被扩大排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 查看 `8f63bcc36fa` 中 `EvaluateAbcFile` | `STATE_MGMT_USE_AOT` 下调用 `ExecuteJsBinForAOT(filePath)` | 不存在该分支则不在本回归区间 |
| 2 | 查看同一版本的 `PreloadUIContent` | 标准系统通过 `EvaluateAbcFile(...jsPreload.abc)` 加载 | 若仍为二进制嵌入或调用 `EvaluateJsCode` 则不属于类别 A |
| 3 | 查看 `PreloadAceModule` | appspawn 预加载流程调用 `PreloadUIContent` | 未调用则定位实际加载 `jsPreload.abc` 的调用入口 |
| 4 | 检查编译宏 | 标准系统构建开启 `STATE_MGMT_USE_AOT` | 未开启时 `EvaluateAbcFile` 仍读取文件并调用 `EvaluateJsCode` |

关键代码定位：

- `8f63bcc36fa:frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp`：
  `EvaluateAbcFile` 的 AOT 分支
- 同文件：`PreloadUIContent` 加载 `jsPreload.abc`
- 同文件：`PreloadAceModule` 在 appspawn 阶段调用 `PreloadUIContent`
- `frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.cpp`：
  `ExecuteJsBinForAOT` 转入 `JSNApi::ExecuteForAbsolutePath`

#### B. appspawn 预加载 JSPandaFile 被 SharedGC 移除排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查 appspawn 加载参数 | `loadAce=true` 且 `preload=true` | 参数不符则不是标准 appspawn 预加载链路 |
| 2 | 搜索 `remove js pandafile by gc` | 文件名命中 `jsPreload.abc` | 未命中时增加 SharedGC 和 `JSPandaFile` 生命周期日志后复现 |
| 3 | 检查 SharedGC 清理逻辑 | 共享常量池为空后调用 `RemoveJSPandaFile` | 若 `JSPandaFile` 仍在 `loadedJSPandaFiles_` 中，`LoadJSPandaFile` 会直接返回该对象，不进入本文的 HSP 分支 |
| 4 | 检查应用创建的 Runtime 来源 | Stage 应用取得 appspawn 保存的预加载 Runtime，并执行 `PostPreload` | 未复用预加载 Runtime 时检查新建 Runtime 链路 |
| 5 | 在再次加载前检查两个缓存 | `loadedJSPandaFiles_` 与 AbcBufferCache 均未命中 | 任一命中时不应进入后续 HSP 分支 |

关键代码定位：

- `<OH_ROOT>/base/startup/appspawn/modules/ace_adapter/ace_adapter.cpp`：
  appspawn 创建并保存预加载 Runtime
- `<OH_ROOT>/foundation/ability/ability_runtime/frameworks/native/runtime/js_runtime.cpp`：
  Stage 应用获取预加载 Runtime
- 同文件：应用初始化执行 `PostPreload` 并配置 Bundle、Buffer Tracker 等运行时状态
- `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/runtime.cpp`：
  SharedGC 清理共享常量池并移除 JSPandaFile
- `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/jspandafile/abc_buffer_cache.h`：
  源码明确记录 SharedGC 删除加载表缓存后，后续加载可能因无法取得 Buffer 而失败

#### C. 缓存未命中后进入 HSP 路径校验排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查 `LoadJSPandaFile` 的加载表查询 | `FindJSPandaFileUnlocked` 返回空 | 命中时不应进入 HSP 分支 |
| 2 | 检查 `AbcBufferCache` 回退 | `GenerateJSPandafileFromBufferCache` 返回空 | 命中时应从 `AbcBufferInfo` 重建 `JSPandaFile` |
| 3 | 检查 HSP 分支条件 | `EcmaVM::IsBundlePack()` 返回 `false`、`ModuleManager::GetExecuteMode()` 返回 `ModuleExecuteMode::ExecuteBufferMode`、`EcmaVM::IsRestrictedWorkerThread()` 返回 `false` | 任一条件不满足时，不进入本文的 HSP 分支 |
| 4 | 检查 `ParseHapPath` 输入 | 输入为 `/etc/abc/framework/jsPreload.abc`，解析结果为空 | 若能解析出 HAP/HSP 路径则不是本问题 |
| 5 | 检查最终日志 | 主线程执行 `LOG_FULL(FATAL) << "Invalid input hsp path: " << filename` | 错误不同则按实际失败点继续定位 |

关键代码定位：

- `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/jspandafile/js_pandafile_manager.cpp`：
  加载表与 AbcBufferCache 查询顺序
- 同文件：进入 HSP 分支的条件及 `Invalid input hsp path`
- `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/jspandafile/js_pandafile_executor.cpp`：
  `JSPandaFileExecutor::ExecuteFromAbsolutePathAbcFile` 调用 `ExecuteFromFile`
- `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/jspandafile/abc_buffer_cache.h`：
  `AbcBufferCache` 回退缓存的用途和查询接口

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| A | 撤销 `EvaluateAbcFile` 中扩大后的 AOT 绝对路径分支，使系统 ABC 文件恢复为读取内容后调用 `EvaluateJsCode` | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` 的 `EvaluateAbcFile` | `e6c594f0c29` (fixed) | diff 删除 `ExecuteJsBinForAOT(filePath)` 分支并保留 `EvaluateJsCode(content, filePath)` |
| B | 对 `EvaluateAbcFile` 恢复文件读取和 `EvaluateJsCode` 调用，使系统 ABC 文件不再依赖绝对路径加载得到的 `JSPandaFile` 持续存在于 `loadedJSPandaFiles_` | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` 的 `EvaluateAbcFile` | `e6c594f0c29` (mitigated) | 历史案例中，该提交规避了 `jsPreload.abc` 的失败调用路径，但 SharedGC 仍会调用 `RemoveJSPandaFile` |
| C | 对 `EvaluateAbcFile` 恢复调用 `EvaluateJsCode`，使系统 ABC 文件不再通过 `JSNApi::ExecuteForAbsolutePath` 到达 HSP 路径校验 | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` 的 `EvaluateAbcFile` | `e6c594f0c29` (mitigated) | 历史案例中，该提交规避了 `jsPreload.abc` 的调用路径，但 `LoadJSPandaFile` 中的 `ModulePathHelper::ParseHapPath` 及错误处理仍存在 |

修复边界：

- `e6c594f0c29` 只撤销 `EvaluateAbcFile` 的统一 AOT 分支。
- 该提交未修改 SharedGC 调用 `RemoveJSPandaFile` 的逻辑，因此类别 B 的底层行为未被直接修复。
- 该提交未修改 `LoadJSPandaFile` 的 HSP 分支条件、`ModulePathHelper::ParseHapPath` 或 `Invalid input hsp path` 错误处理，因此类别 C 为调用路径规避。
- `PreloadStateManagement` 中对 `stateMgmt.abc` 的显式 `ExecuteJsBinForAOT` 调用未随该修复移除。
- 本文的修复关系由回归区间、源码控制流和正反 diff 验证；当前仓库未发现针对该历史时序的专项自动化回归用例。

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | `EvaluateAbcFile` 在 `STATE_MGMT_USE_AOT` 下统一改用绝对路径执行，并让标准系统的 `PreloadUIContent` 加载 `jsPreload.abc` | A | introduced | `8f63bcc36fa` diff 及回归区间 | verified |
| CHG-02A | 撤销 `EvaluateAbcFile` 的 AOT 绝对路径分支，恢复文件读取和 `EvaluateJsCode` 调用 | A | fixed | `e6c594f0c29` 与类别 A 的引入变更构成直接反向 diff | verified |
| CHG-02B | `EvaluateAbcFile` 加载 `jsPreload.abc` 时不再调用 `JSNApi::ExecuteForAbsolutePath`，规避 SharedGC 移除 `JSPandaFile` 后的绝对路径重新加载和 HSP 路径校验链路 | B+C | mitigated | `e6c594f0c29` 只修改 `EvaluateAbcFile`；`RemoveJSPandaFile` 与 HSP 路径校验仍保留 | verified |
| CHG-03 | SharedGC 在共享常量池无存活项后从全局加载表移除对应 JSPandaFile | B | related | `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/runtime.cpp` | verified |

## 预防措施

- 修改公共 ABC 加载辅助函数时，必须枚举全部调用者，避免以单一文件需求扩大所有调用场景的加载语义。
- 对 appspawn 预加载文件同时验证预加载、PreFork、PostFork、SharedGC 和应用创建阶段再次加载五个时点。
- `/etc/abc` 等系统文件不是 HAP/HSP 路径，不应依赖 HSP 路径解析作为缓存未命中后的兜底。
- 排查该类问题时同时观察 `loadedJSPandaFiles_`、`AbcBufferCache` 和 `ModuleManager::GetExecuteMode()`，不能只检查文件是否存在。
- 建议增加专项回归场景：appspawn 预加载系统 ABC 文件后触发 SharedGC，再创建应用并使用预加载能力，验证不出现 `Invalid input hsp path`。
- 对 SharedGC 清理日志保留文件描述符或规范化文件名，便于关联预加载和应用创建阶段的同一 `JSPandaFile`。
- 评审绝对路径 ABC 加载变更时，应确认路径是否属于 HAP/HSP；若不是，必须验证缓存失效后的重新加载行为。

## 相关主题

- `docs/kb/frontend/state_management/cpp-bindings.md`
- `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp`
- `frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.cpp`
- `interfaces/inner_api/ace/declarative_module_preloader.cpp`
- `<OH_ROOT>/base/startup/appspawn/modules/ace_adapter/ace_adapter.cpp`
- `<OH_ROOT>/foundation/ability/ability_runtime/frameworks/native/runtime/js_runtime.cpp`
- `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/runtime.cpp`
- `<OH_ROOT>/arkcompiler/ets_runtime/ecmascript/jspandafile/js_pandafile_manager.cpp`