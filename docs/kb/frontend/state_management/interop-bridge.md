# State Management — Interop 桥接 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtInterop`

## 定位

Interop 桥接是动态前端（ArkTS1.1 / declarative_frontend）与静态前端（ArkTS1.2 / arkoala / Panda VM，`libarkts_frontend.z.so`）之间的状态管理互操作层。关键设计是**控制反转**：动态侧从不直接 import 静态侧，而是暴露一组 `register*` 函数，由静态运行时在绑定时填充回调。覆盖范围：存储（`AppStorage`/`LocalStorage`/`AppStorageV2` 双向可见）、视图（`@Provider`/`@Consumer` 跨世界查找）、Builder（`BuilderViewV2` 宿主 + `createCompatibleNodeWithFunc1..10` 严格类型重载）。共 8 个文件（`interop/`）。静态侧的状态对象是 Panda STValue 代理（`isStaticProxy` 检测），动态侧通过 `deepCopyStaticProxy` 拷贝为普通 JS 对象后使用（不应持有静态代理引用）。

本文档用于快速定位 Interop 相关源码和测试入口。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 全局 Interop 开关 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/interop_configure.ts` | `InteropConfigureStateMgmt`（`needsInterop`/`openInterop`/`closeInterop`） |
| 回调注册表 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/interop_module.ts` | `InteropExtractorModule`（约 13 个回调槽：`createWatchFunc`、`makeObserved`、`compatibleStaticComponent` 等） + `StaticInteropHook` |
| 核心检测/拷贝/订阅 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/interop.ts` | `isStaticProxy`、`deepCopyStaticProxy`、`SubscribeInterop`、`createStateVariable`、`staticStateBindObservedObject`、`__Interop_*_Internal` 入口函数 |
| V1 存储桥 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/interop_storage.ts` | `InteropStorage extends Map`（origin 优先、static 兜底）；`bindStaticAppStorage`/`bindStaticLocalStorage` 替换内部 Map |
| V2 存储桥 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/v2_interop_storage.ts` | `InteropStorageV2 extends StorageHelper`（单例）；`bindStaticAppStorageV2` |
| 跨世界视图桩 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/interop_view.ts` | `ViewInterop extends PUV2ViewBase`（`@Consumer` 跨世界查找中转站）、`findProviderForInterop`、`createLocalStorage` |
| Builder 桥（V1） | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/interop_builder.ts` | `__makeBuilderParameterStaticProxy_Interop_Internal`、`createDynamicBuilder`、`createDynamicUpdatableBuilder`、`enableCompatibleObservedV2ForStatic`、`staticBuilderUpdate`、`isDynamicBuilderProxy`、`getBuilderParamProxyEntries`、`startStaticHook` |
| Builder 桥（V2） | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/v2_builder.ts` | `BuilderViewV2 extends ViewV2`（最小 ViewV2 壳承载动态 `@Builder`）；`createCompatibleNodeWithFuncVoid` + `createCompatibleNodeWithFunc1..10`（11 重载）；`__Interop_BindingProxyHandler_Internal`（Binding 代理参与 V2 依赖）；`createCompatibleNodeWithFuncHelper` |
| V1 消费点（`needsInterop` 调用） | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view.ts`、`pu_observed_property.ts`、`pu_synced_property_*.ts`、`pu_builder_proxy.ts` | 多处 `needsInterop()` 分支 |
| V2 消费点 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_view.ts`、`v2_decorators.ts`、`v2_decorated_variables.ts`、`v2_change_observation.ts` | 多处 `needsInterop()` 分支 |
| SDK 消费点 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/local_storage.ts` | `needsInterop()` 分支 |
| 反向调用接口 | `frameworks/core/common/frontend.h` | `OpenStateMgmtInterop` 虚函数（启用 Interop 模式） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| 控制反转 | `interop_module.ts` `InteropExtractorModule` 字段默认 undefined；静态运行时启动时调 `register*`；`__Interop_*_Internal` 未注册时抛 `NOT_IMPLEMENT` |
| `needsInterop()` 消费方 | V1（`pu_view.ts`、`pu_observed_property.ts`、`pu_synced_property_*.ts`、`pu_builder_proxy.ts`），V2（`v2_view.ts`、`v2_decorators.ts`、`v2_decorated_variables.ts`、`v2_change_observation.ts`），SDK（`local_storage.ts`） |
| `InteropStorage` 替换内部 Map | `get`（origin 优先 → static 兜底）、`set`（origin + `addKeyFunc_`）、`keys`（合并迭代器）；反向回调（`setGetValueFunc` 等）让静态侧查动态侧；删除检查 `numberOfSubscrbers() > 0`（源码拼写） |
| `ViewInterop` 桩设计 | 几乎所有 `IView`/`PUV2ViewBase` 方法抛 `NOT_IMPLEMENT`，唯一目的是经注入的 `findProvideV2` 回调为 `@Consumer` 跨世界查找中转 |
| `deepCopyStaticProxy` | `interop.ts` — 递归拷贝静态代理为普通 JS（Array/Map/Set/Date/object）；实际环检测在调用方 `pu_synced_property_one_way.ts`（`@Prop` 赋值） |
| `createCompatibleNodeWithFunc1..10` | ArkTS1.2 严格静态类型需精确参数数量重载；`createCompatibleNodeWithFuncHelper` 创建 `BuilderViewV2`，绑定参数（Binding/MutableBinding 经 `__Interop_MakeObservedInteropBinding_Internal`），装 `initialRender`/`rerender` |
| `__Interop_BindingProxyHandler_Internal` | 使静态侧 Builder `Binding` 参数参与 V2 依赖追踪（get `value` → `addRef`，set → `fireChange`） |
| `staticStateBindObservedObject` | 兼容模式 → `SubscribeInterop` + `addOwningProperty`；`@Track` 模式 → `ObservedPropertyObjectPU` + `registerPropertyReadCb` |
| `isStaticProxy` 检测 | Panda STValue 代理，prototype 标记 `_isStaticProxy`/`isStaticArrayProxy_` 等 |
| 存储删除订阅者保护 | `numberOfSubscrbers() > 0` 拒绝删除（源码拼写缺 `i`） |

### API 入口

Interop 是引擎内部桥接层，不对外暴露 SDK 声明。其上层消费方为 `BuilderNode.build(WrappedBuilder)` 和 `ComponentContent`（用 `wrapBuilder` 结果）。

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| NAPI / Dynamic / Static / CAPI | 不涉及 | Interop 是内部桥接，无独立对外 API |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 通用测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/common_tests/` | `InteropStorage`、`ViewInterop`、Builder 桥 |
| 端到端场景 | 需动态+静态双运行时 | Interop 场景通常需两种运行时，纯单元覆盖有限 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtInterop` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-14` | `specs/07-frontend/02-state-management/14-state-management-interop` | active（5 Feat 待补充） |
## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `needsInterop()` 何时为 true | 静态运行时加载并调用 `openInterop()`（`InteropConfigureStateMgmt`） |
| `isStaticProxy` 检测什么 | Panda STValue 代理，prototype 标记 `_isStaticProxy`/`isStaticArrayProxy_` 等 |
| `deepCopyStaticProxy` 用在哪 | `@Prop` 赋值（静态父→动态子），动态侧不应持有静态代理引用 |
| `InteropStorage` 双向可见原理 | 替换内部 Map，origin 优先 + static 兜底 + 反向回调 |
| `createCompatibleNodeWithFunc` 为何 10 个重载 | ArkTS1.2 严格静态类型需精确参数数量签名 |
| `ViewInterop` 为何是桩 | 唯一目的：`@Consumer` 查找链跨世界中转站 |
| 存储删除失败 | `numberOfSubscrbers() > 0` 拒绝（源码拼写缺 `i`） |
| `deepCopyStaticProxy` 循环处理 | 函数内仅 `.set()`，实际 `.get()` 缓存查找在调用方 |
| `NOT_IMPLEMENT` BusinessError | 静态运行时未注册对应回调（`InteropExtractorModule` 槽 undefined） |
| `@Prop` 报 "Illegal usage of Static object assignment" | `deepCopyStaticProxy` 失败 |
| 跨世界 `@Consumer` 找不到 `@Provider` | `findProviderForInterop` 父链遍历，ViewInterop 边界未注入 `findProvideV2` |

## 调试入口

- **Interop 模式确认**：`InteropConfigureStateMgmt.needsInterop()`。
- **回调注册检查**：`InteropExtractorModule` 各回调槽（undefined = 未注册）。
- **代理检测**：`isStaticProxy(obj)`、`isStaticArrayProxy`、`isStaticMapProxy`、`isStaticSetProxy`、`isDynamicBuilderProxy(value)`（查 `__builder_param_get_target`）。
- **日志关键字**：`Illegal usage of Static object assignment to @Prop is not allowed.`（`deepCopy` 失败）、`NOT_IMPLEMENT`（BusinessError）。
- **断点建议**：`openInterop`、`register*` 系列、`__Interop_*_Internal` 入口、`deepCopyStaticProxy`、`createCompatibleNodeWithFuncHelper`、`__Interop_BindingProxyHandler_Internal`。

## 相关主题

- 总览：[docs/kb/frontend/state-management.md](../state-management.md)
- V1/V2 核心（Interop 消费 `needsInterop` 分支）：[docs/kb/frontend/state_management/v1-core.md](v1-core.md)、`v2-core.md`
- 存储体系（`InteropStorage`/`InteropStorageV2` 桥接对象）：[docs/kb/frontend/state_management/storage.md](storage.md)
- [自定义组件机制（`BuilderViewV2`/Builder 桥）：[docs/kb/frontend/state_management/custom-component.md](custom-component.md)](custom-component.md)
- C++ 绑定（`OpenStateMgmtInterop` 入口）：[docs/kb/frontend/state_management/cpp-bindings.md](cpp-bindings.md)
- 静态前端总体架构：`frameworks/bridge/arkts_frontend/`（`AGENTS.md` 的「Frontend Support」）
- 静态 Interop 桥（arkoala 侧另一半）：[docs/kb/frontend/state_management/static-interop-bridge.md](static-interop-bridge.md)