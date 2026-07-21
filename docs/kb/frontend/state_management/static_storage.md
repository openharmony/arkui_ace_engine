# Static State Management — 存储体系 Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `StateMgmtStaticStorage`

## 定位

静态前端（ArkTS 1.2 / arkoala）的应用级存储与持久化体系，分 V1 和 V2 两套并存。V1：`LocalStorage`（页面级，可多实例）、`AppStorage`（应用级全局单例，等价于 `InteropAppStorage` 实例）、`PersistentStorage`（磁盘持久化，经 ANI 桥）、`Environment`（设备环境变量写入 AppStorage）。V2：`AppStorageV2`（内存全局存储，跨前端经 `InteropAppStorageV2`）、`PersistenceV2`（磁盘持久化 + `V2CollectionCoder` 序列化 + EL1-EL5 加密级别）。

与动态侧（`declarative_frontend/state_mgmt/src/lib/sdk/`）不同，静态侧存储主体在 `stateManagement/storage/`，且跨前端可见性由 `interop/interopStorage.ts`/`interopStorageV2.ts` 桥接。

本域覆盖 FuncID `07-02-10`（静态V1应用内状态管理）和 `07-02-13`（静态V2应用内状态管理）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 存储源码根 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/` | V1/V2 存储类实现 |
| `LocalStorage` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/localStorage.ts` | `LocalStorage` — 由 `InteropStorageBase` 支撑；支持 Record 与 class 类型初始属性；`ref`/`setAndRef`/`link`/`setAndLink`/`set`/`get`/`setOrCreate`/`delete`/`clear`/`keys`/`size`/`has` |
| `AppStorage` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/appStorage.ts` | `AppStorage: LocalStorage` — 单例 `new InteropAppStorage()`，全部行为继承自 `LocalStorage` + `InteropAppStorage` |
| `PersistentStorage` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/persistentStorage.ts` | `PersistentStorage` — 静态门面，经 `AniStorage` 桥调 `ArkUIAniModule._PersistentStorage_{Get,Set,Has,Delete,Clear}`；`TypedMap` 类型化；`persistProp`/`persistProps`/`deleteProp`/`keys`；`AreaMode` EL1-EL5 |
| `Environment` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/environment.ts` | `Environment` — 单例经 `AniEnvironment` 调 `ArkUIAniModule._Env_*`；注入 6 个 key（`accessibilityEnabled`/`layoutDirection`/`languageCode`/`colorMode`/`fontScale`/`fontWeightScale`）到 AppStorage |
| `AppStorageV2` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/appStorageV2.ts` | `AppStorageV2` — 静态门面，经 `InteropAppStorageV2.instance()` 跨前端互操作；`connect(ttype, key?, defaultCreator?)`/`remove(keyOrType)`/`keys()`；拒绝 primitive 类型 |
| `PersistenceV2` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/persistenceV2.ts` | `PersistenceV2`/`PersistenceV2Impl`/`StorageHelper` — `connect`/`save`/`notifyOnError`/`onChangeObserved`/`remove`/`keys`/`globalConnect`（EL1-EL5） |
| V2 序列化 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/v2CollectionCoder.ts` | `V2CollectionCoder` — 保持原型链的序列化/反序列化 |
| 存储基础类型 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/storageBase.ts` | `StorageProperty<T>`/`StorageBase`/`IStorageProperty`/`IPropRefCounter` |
| `AbstractProperty` 类型 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/storageProperty.ts` | `AbstractProperty<T>`/`SubscribedAbstractProperty<T>`/`OnChangeType<T>`/`ColorMode`/`LayoutDirection` 枚举 |
| 互操作存储桥（V1） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/interop/interopStorage.ts` | `InteropStorageBase`/`InteropAppStorageBase`/`InteropAppStorage` — 静态侧半桥，经 `bindStaticLocalStorage`/`bindStaticAppStorage` 注册到动态侧 |
| 互操作存储桥（V2） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/interop/interopStorageV2.ts` | `InteropAppStorageV2` — 经 `bindStaticAppStorageV2` 注册到动态侧；`connect` 静态 miss 时回退动态存储 |
| ANI 原生桥 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/stateMgmt/stateMgmt_module.cpp` | `PersistentStorage_{Get,Set,Has,Clear,Delete}` + `Env_{ColorMode,FontScale,FontWeightScale,AccessibilityEnabled,LayoutDirection,LanguageCode}` 共 11 个原生方法 |
| 自动生成后端 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/stateManagement/internal.ets` | `EnvironmentBackend`/`PersistentStorageBackend` — `ArkUIGeneratedNativeModule._EnvironmentBackend_*`/`_PersistentStorageBackend_*`（ANI 替代路径） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| 跨前端存储双向可见 | `interop/interopStorage.ts` `InteropStorageBase` — `getDynamicValue_`/`removeDynamicValue_`/`clearDynamicValue_` 回调由动态侧经 `bindStaticLocalStorage`/`bindStaticAppStorage` 注入 |
| V2 跨前端存储 | `interop/interopStorageV2.ts` `InteropAppStorageV2` — 经 `ESValue.getGlobal().getProperty('bindStaticAppStorageV2')` 注册静态侧访问器到动态侧 |
| 类型化持久化 | `storage/persistentStorage.ts` `TypedMap` — key → Class + IStorageProperty 映射 |
| `Environment` 扇出 | `storage/environment.ts` `envPropInternal` — 6 个固定 key 经 `aniEnvironment.getXxx()` 读取后调 `AppStorage.setAndRef` 注入 |
| `PersistenceV2` 自动追踪 | `storage/persistenceV2.ts` `PersistenceV2Impl.instance().onChangeObserved` — 经 `observeSingleton.ts` 注册依赖图 |
| `PersistenceV2.globalConnect` EL1-EL5 | `storage/persistenceV2.ts` `ConnectOptions.areaMode` — 默认 `El2`，支持 EL1-EL5 加密级别 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 存储联动装饰器 | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `@StorageLink`/`@StoragePropRef`/`@LocalStoragePropRef`/`@LocalStorageLink` + `@since 23 static` |
| V1 存储类 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.stateManagement.static.d.ets` | 重导出 `storage/localStorage.static.d.ets`（`LocalStorage`）/`storage/appStorage.static.d.ets`（`AppStorage: LocalStorage`）/`storage/persistentStorage.static.d.ets`（`PersistentStorage`）/`storage/environment.static.d.ets`（`Environment`）/`storage/storageProperty.static.d.ets`（`AbstractProperty`/`SubscribedAbstractProperty`） |
| V2 存储类 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.stateManagement.static.d.ets` | 重导出 `storage/appStorageV2.static.d.ets`（`AppStorageV2.connect/remove/keys`）/`storage/persistenceV2.static.d.ets`（`PersistenceV2.connect/globalConnect/save/remove/keys/notifyOnError` + `ConnectOptions`/`BaseConnectOptions`/`StorageDefaultCreator`/`PersistenceErrorCallback`） |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 存储测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/storage/` 同目录测试 | V1/V2 存储类行为回归 |
| 互操作测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/mock/` | `interopStorageV2.ts` 测试桩 |
| ANI 桥测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/stateMgmt/` 同目录 | 原生桥行为 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStaticStorage` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-10` | `specs/07-frontend/02-state-management/10-static-v1-app-state/` | active（Feat-01~05 待补充） |
| `07-02-13` | `specs/07-frontend/02-state-management/13-static-v2-app-state/` | active（Feat-01~02 待补充） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 跨前端存储值不可见 | `interop/interopStorage.ts` `bindStaticLocalStorage`/`bindStaticAppStorage` — 确认动态侧是否注册了 `getDynamicValue_`/`removeDynamicValue_` 回调 |
| `PersistentStorage` 类型丢失 | `storage/persistentStorage.ts` `TypedMap` + `ToJSONType`/`FromJSONType` — 确认 key → Class 映射与自定义序列化函数 |
| `AppStorageV2` 拒绝 primitive | `storage/appStorageV2.ts` `connect` — 仅接受 class 类型，primitive 报错 |
| `PersistenceV2.globalConnect` 加密级别错误 | `storage/persistenceV2.ts` `ConnectOptions.areaMode` — 默认 `El2`，需更高级别时显式指定 |
| `Environment` key 不扇出 | `storage/environment.ts` — 仅 6 个固定 key 触发后端查询写入 AppStorage |
| V2 持久化序列化失败 | `storage/v2CollectionCoder.ts` `V2CollectionCoder` — 检查 `toJson`/`fromJson` 配置 |

## 调试入口

- **日志关键字**：`LocalStorage`、`InteropAppStorage`、`PersistentStorage`、`AniStorage`、`Environment`、`AniEnvironment`、`AppStorageV2`、`InteropAppStorageV2`、`PersistenceV2`、`PersistenceV2Impl`、`V2CollectionCoder`。
- **跨前端存储排查**：`InteropStorageBase.proxy` 是否指向动态侧 `ObservedPropertyPU`；`bindStaticLocalStorage`/`bindStaticAppStorage`/`bindStaticAppStorageV2` 是否在启动时调用。
- **持久化排查**：`persistPropInternal` 三分支（existing-in-storage / read-from-disk / create-new）；`AniStorage` 桥调用是否返回正确值。
- **V2 持久化排查**：`PersistenceV2Impl.instance().onChangeObserved` 依赖图注册；`StorageHelper.isKeyValid` key 校验；`V2CollectionCoder` 输入输出对比。

## 相关主题

- 总览：`docs/kb/frontend/state_management.md`
- 静态 V1 核心（`StateDecoratedVariable` 是存储 `link()` 返回基础）：`docs/kb/frontend/state_management/static_v1_core.md`
- 静态 V1 装饰器（存储联动装饰器 `@StorageLink`/`@StoragePropRef` 等）：`docs/kb/frontend/state_management/static_v1_decorators.md`
- 跨前端互操作（存储桥完整机制）：`docs/kb/frontend/state_management/static_interop_bridge.md`
- 动态侧存储体系（对照参考）：`docs/kb/frontend/state_management/storage.md`
