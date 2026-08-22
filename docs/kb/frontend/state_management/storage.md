# State Management — 存储体系 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtStorage`

## 定位

存储体系提供跨组件树、跨页面、跨进程生命周期的状态承载与持久化能力，分 V1 和 V2 两套并存。V1：`AppStorage`（应用级全局单例，继承 `LocalStorage`）、`LocalStorage`（页面级，可多实例）、`PersistentStorage`（磁盘持久化，经 `IStorage` 后端）、`Environment`（设备环境变量写入 `AppStorage`）。V2：`AppStorageV2`（内存全局存储，仅 `@ObservedV2`）、`PersistenceV2`（磁盘持久化，经可配置 `IStorage` 后端 + `DataCoder` 序列化保持原型链）。V1 的存储逻辑主体在 `LocalStorage`，`AppStorage` 只增加单例和静态 API 委托。V2 持久化通过 `ObserveV2` 依赖图自动追踪 `@Trace` 变化，无需手动通知。

本文档用于快速定位存储体系相关源码和测试入口。装饰器 `@StorageLink`/`@StorageProp`/`@LocalStorageLink`/`@LocalStorageProp` 见「V1 装饰器」子页面；`@Env`/`@CustomEnv` 见「V2 装饰器」子页面。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 页面级存储基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/local_storage.ts` | `LocalStorage extends NativeLocalStorage`（`storage_: Map<string, ObservedPropertyAbstract>`）；V1 存储逻辑主体 |
| 应用级存储单例 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/app_storage.ts` | `AppStorage extends LocalStorage` — 全局单例 + 静态 API 委托 |
| V1 磁盘持久化 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/persistent_storage.ts` | `PersistentStorage implements IMultiPropertiesChangeSubscriber` — 持久化管理、Map/Set/Date 序列化 |
| V1 设备环境 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/environment.ts` | `Environment`（单例）— 6 个固定 key 触发后端查询，写入 `AppStorage` |
| 持久化后端抽象 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/i_storage.ts` | `IStorage` 接口（不支持增量更新，`write()` 写所有属性） |
| 环境后端抽象 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/i_environment_backend.ts` | `IEnvironmentBackend`（6 个 getter 接口） |
| 环境原生声明 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/environment_setting.d.ts` | `EnvironmentSetting`（由 C++ `JSEnvironment` 注入） |
| V2 存储/持久化 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/v2_persistence.ts` | `AppStorageV2Impl`、`PersistenceV2Impl`（`MIN_PERSISTENCE_ID = 0x1020000000000`）、`StorageHelper`（key 校验） |
| V2 序列化 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_data_coder/` | `DataCoder.stringify/parse/restoreTo`、`JSONCoder`、`JSON2`、`Meta`（`@Type`）— 保持原型链 |
| LocalStorage C++ 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_local_storage.cpp`、`.h` | `JSLocalStorage`（`storages_` thread_local，多 containerId） |
| PersistentStorage C++ 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_persistent.cpp`、`.h` | `JSPersistent::JSBind`（"Storage"）→ `StorageProxy` |
| Environment C++ 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_environment.cpp`、`.h` | `JSEnvironment::JSBind`（"EnvironmentSetting"） |
| 环境后端平台实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/env_base/` | `system_env.ts`、`env_factory.ts`、`i_env_breakpoint.ts`、`i_env_value.ts`、`customEnv_key.ts` |
| Interop 存储桥接 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/interop_storage.ts`、`v2_interop_storage.ts` | `InteropStorage`、`InteropStorageV2` — 跨动态/静态前端存储可见 |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| PU/FU 属性创建分支 | `sdk/local_storage.ts` `addNewPropertyInternal` — `ViewStackProcessor.UsesNewPipeline()` 决定 `ObservedPropertyPU` vs FU |
| `link()`/`prop()` 双向/单向 | `sdk/local_storage.ts` `link()`/`prop()` |
| 装饰器同步工厂入口 | `sdk/local_storage.ts` `__createSync`（`@StorageLink`/`@StorageProp` 编译产物） |
| `AppStorage` 单例委托 | `sdk/app_storage.ts` — 静态 API 委托到内部 `LocalStorage` 实例 |
| `persistProp` 决策逻辑 | `sdk/persistent_storage.ts` `persistProp1` — 先 `AppStorage.link`；不在 AppStorage 则查磁盘 `storage_.has` → 读或用默认 → `AppStorage.setAndLink` |
| Map/Set/Date 序列化标记 | `sdk/persistent_storage.ts` `MapInfo`/`SetInfo`/`DateInfo` + `replacer`（NewVersion/CompatibleVersion 检测） |
| 嵌套对象持久化（V1） | 需手动 `PersistentStorage.notifyHasChanged('data')` |
| `delete`/`clear` 订阅者保护 | `sdk/local_storage.ts` — `numberOfSubscrbers()` > 0 时返回 false |
| `Environment` 扇出 | `sdk/environment.ts` `envProp` → `AppStorage.setAndProp`；`onValueChanged` → `AppStorage.set` 扇出 |
| Environment 6 固定 key | `accessibilityEnabled`/`colorMode`/`fontScale`/`fontWeightScale`/`layoutDirection`/`languageCode` |
| PersistenceV2 自动持久化 | `sdk/v2_persistence.ts` `connect` 分配 PersistenceV2 ID → `startRecordDependencies`/`stopRecordDependencies` 注册依赖图 → `@Trace` change → `fireChange` → `onChangeObserved` → `writeAllChangedToFile` |
| `PersistenceV2.connect` defaultCreator 时机 | 仅首次 connect（内存+磁盘都不存在） |
| PersistenceV2 不支持的类型 | WeakSet/WeakMap/Boolean/Number/String/Symbol/BigInt/RegExp/Function/Promise/ArrayBuffer |
| AppStorageV2 全局扁平 Map | 不支持 UIContext 隔离，需 `@Env`/`@CustomEnv` 按 instanceId 隔离 |
| `DataCoder.restoreTo` 保持原型链 | 将解析数据恢复到已有 `@ObservedV2` 实例（区别于 `JSON.parse`） |
| `IStorage.write()` 写所有属性 | 后端不支持增量更新 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `@StorageLink`/`@StorageProp`/`@LocalStorageLink`/`@LocalStorageProp` 声明 |
| StateManagement 模块 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.StateManagement.d.ts` | `AppStorageV2`、`PersistenceV2`、`PersistenceV2.configureBackend(IStorage)`、`IStorage`、`DataType` |
| V1 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | 静态 ArkTS 侧存储装饰器声明 |

具体 API（`AppStorage.Set/Get/Has/Delete`、`LocalStorage` 构造与方法、`PersistentStorage.persistProp`、`Environment.envProp`）的签名、错误码以 SDK 声明为准。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 通用测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/common_tests/` | `AppStorage`、`LocalStorage`、`PersistentStorage`、`Environment` 行为回归 |
| V2 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v2_tests/` | `AppStorageV2`、`PersistenceV2`、`DataCoder`、`@Type` 序列化 |
| Env 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/env_tests/` | `Environment`、`@Env`/`@CustomEnv` |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStorage` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-03` | `specs/07-frontend/02-state-management/03-v1-app-state` | Baselined（V1 存储 4 Feat） |
| `07-02-06` | `specs/07-frontend/02-state-management/06-v2-app-state` | Baselined（V2 存储 2 Feat） |
## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `delete`/`clear` 返回 false | 属性仍有订阅者（`numberOfSubscrbers() > 0`，注意源码拼写缺 `i`） |
| `AppStorage` vs `LocalStorage` | 前者全局单例，后者可多实例（页面级）；`AppStorage` 继承 `LocalStorage` |
| `@StorageLink` 与 `AppStorage.link()` 关系 | 前者是编译器糖 → `__createSync` → `SynchedPropertyTwoWayPU` |
| 嵌套对象变化未持久化（V1） | 需手动 `PersistentStorage.notifyHasChanged('data')` |
| `persistProp` defaultValue 何时用 | `AppStorage` 和磁盘都不存在时 |
| `write()` 写所有属性 | `IStorage` 不支持增量更新 |
| PersistenceV2 反序列化类型失败 | 嵌套对象缺 `@Type` 抛 `PERSISTENCE_V2_LACK_TYPE` |
| PersistenceV2 不支持的类型 | WeakSet/WeakMap/Boolean/Number/String/Symbol/BigInt/RegExp/Function/Promise/ArrayBuffer |
| AppStorageV2 不支持 UIContext 隔离 | 全局单例扁平 Map；需 `@Env`/`@CustomEnv` 按 instanceId 隔离 |
| `PersistenceV2.connect` defaultCreator 调用时机 | 仅首次 connect（内存+磁盘都不存在） |
| `Environment` 写入 AppStorage | `envProp` → `AppStorage.setAndProp`；`onValueChanged` → `AppStorage.set` 扇出 |
| 持久化恢复异常 | V1 检查 Map/Set/Date 序列化标记版本；V2 检查 `DataCoder.restoreTo` 原型链 |

## 调试入口

- **存储状态检查**：`AppStorage.keys()`、`size()`、`has(key)`、`get(key)`。
- **订阅者计数**：`ref.numberOfSubscrbers()`（注意源码拼写）。
- **日志关键字**：`Creating AppStorage instance`、`PersistentStorage: persistProp1 ...`、`writing 'X' to storage`、`property changed`、`sync peer X has changed`。
- **持久化恢复验证**：`persistProp` → 修改 → 重启 → 检查恢复值。
- **V2 持久化排查**：`PersistenceV2.connect` 的 `keyItemName`/`type`、`StorageHelper.isKeyValid`、`DataCoder` 输入输出对比。

## 相关主题

- 总览：[docs/kb/frontend/state-management.md](../state-management.md)
- V1 核心（`ObservedPropertyPU` 是存储 `link()` 的返回基础）：[docs/kb/frontend/state_management/v1-core.md](v1-core.md)
- V2 核心（`PersistenceV2` 经 `ObserveV2` 依赖图自动追踪）：[docs/kb/frontend/state_management/v2-core.md](v2-core.md)
- V1 装饰器（`@StorageLink`/`@StorageProp`/`@LocalStorageLink`/`@LocalStorageProp`）：[docs/kb/frontend/state_management/v1-decorators.md](v1-decorators.md)
- V2 装饰器（`@Env`/`@CustomEnv`/`@Type`）：[docs/kb/frontend/state_management/v2-decorators.md](v2-decorators.md)
- C++ 绑定（`JSLocalStorage`/`JSPersistent`/`JSEnvironment`）：[docs/kb/frontend/state_management/cpp-bindings.md](cpp-bindings.md)
- Interop（跨前端存储可见）：[docs/kb/frontend/state_management/interop-bridge.md](interop-bridge.md)
- [静态存储体系（arkoala 侧）：[docs/kb/frontend/state_management/static-storage.md](static-storage.md)](static-storage.md)