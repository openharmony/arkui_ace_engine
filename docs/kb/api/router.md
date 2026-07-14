# Router 路由管理 Context

> 文档版本：v1.1
> 更新时间：2026-07-14
> 来源：`docs/context_registry.json` 主题 `Router`

## 定位

Router 是 ArkUI 早期提供的页面路由管理 NAPI 模块（`@ohos.router`），支持 pushUrl/replaceUrl/back/clear/getLength 等页面跳转与栈操作，以及命名路由（namedRouter）。**从 ArkUI 架构演进角度，Router 整体已经不推荐继续使用，推荐使用 Navigation + NavPathStack 作为现代路由导航方案**。Router 仅作为存量兼容和历史参考保留。行为事实以 SDK `.d.ts` 声明、源码、测试和 Spec 为准。

**废弃与不推荐标注**：
- **Router 整体不推荐使用** — 推荐替代为 Navigation + NavPathStack（详见 [Navigation KB](../components/container/navigation.md)）
- `@ohos.router` 模块虽未整体废弃声明，但多个方法自 API 18 起废弃（`@deprecated since 18`），推荐替代为 `ohos.arkui.UIContext.Router` 实例谬用法
- `@system.router` **整体废弃**（`@deprecated since 8`），推荐替代为 `@ohos.router`
- `push(options)` 方法废弃（`@deprecated since 9`），推荐替代为 `pushUrl`

**推荐替代方案**：Navigation + NavPathStack 提供更完善的导航能力——声明式路由栈管理、转场动画、分栏模式、生命周期回调、状态恢复等，是 ArkUI 架构演进的方向。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NAPI 桥接层 | `interfaces/napi/kits/router/js_router.cpp` | `@ohos.router` NAPI 模块主入口，JS → C++ 调用（不推荐，推荐 Navigation） |
| PageRouterManager | `frameworks/bridge/declarative_frontend/ng/page_router_manager_factory.h/cpp` | 页面路由管理器工厂 |
| ParallelPageRouterManager | `frameworks/bridge/declarative_frontend/ng/force_split/parallel_page_router_manager.cpp` | 系统强制分栏（平行视界）路由管理，通过系统配置接入；Navigation 同样支持此能力 |
| ManifestParser 路由 | `frameworks/bridge/common/manifest/manifest_router.h/cpp` | 页面路由表解析（config.json / module.json） |
| Router Recover | `frameworks/core/common/router_recover_record.h` | 路由恢复记录 |
| Router Extender (C API) | `frameworks/core/interfaces/native/implementation/router_extender_accessor.cpp` | Router C API Extender accessor（静态版路由扩展） |
| ArkTS 静态版 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/router/router_impl.ets` | ArkTS 静态版 Router 实现 |
| ArkTS 静态版索引 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/router/index.ets` | 静态版 Router 模块导出 |
| ArkTS 静态版 IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/router_extender.idl` | Router Extender IDL 定义 |
| ArkTS 静态版声明 | `frameworks/bridge/arkts_frontend/koala_projects/inner_api/@ohos.router.d.ets` | 静态版 Router API 声明 |
| UIContext | `frameworks/core/interfaces/native/implementation/iui_context_accessor.cpp` | UIContext accessor — API 18 推荐的 Router 实例谬用法入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic（不推荐） | `<OH_ROOT>/interface/sdk-js/api/@ohos.router.d.ts` | `@ohos.router` 公开 API — 整体不推荐，推荐替代 Navigation |
| Static（不推荐） | `<OH_ROOT>/interface/sdk-js/api/@ohos.router.static.d.ets` | ArkTS 静态版 Router API — 整体不推荐 |
| Legacy（已废弃） | `<OH_ROOT>/interface/sdk-js/api/@system.router.d.ts` | `@system.router` — 自 API 8 起整体废弃 |

### 测试入口

Router 为 NAPI kit，无独立单元测试目录。测试通过系统级 XTS 和应用测试覆盖。

### 相关 Spec

| Spec 域 | 路径 | 说明 |
|---------|------|------|
| 路由跳转与替换 | `specs/04-common-capability/15-router-mechanism/01-router-management/Feat-01-router-push-replace-back-spec.md` | Func-04-15-01-Feat-01 |
| 路由栈查询与弹窗拦截 | `specs/04-common-capability/15-router-mechanism/01-router-management/Feat-02-router-stack-query-alert-spec.md` | Func-04-15-01-Feat-02 |
| 路由管理 Design | `specs/04-common-capability/15-router-mechanism/01-router-management/design.md` | 路由管理架构设计 |
| 命名路由 | `specs/04-common-capability/15-router-mechanism/03-named-router/Feat-01-named-router-push-replace-spec.md` | Func-04-15-03-Feat-01 |
| 命名路由 Design | `specs/04-common-capability/15-router-mechanism/03-named-router/design.md` | 命名路由架构设计 |
| 分布式路由迁移 | `specs/04-common-capability/07-migration-recovery/01-distributed-router-migration/` | Func-04-07-01 |
| 路由栈恢复 | `specs/04-common-capability/07-migration-recovery/02-router-stack-recovery/` | Func-04-07-02 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 页面跳转应使用什么方案 | **推荐 Navigation + NavPathStack**，不推荐 Router |
| pushUrl/replaceUrl 页面跳转失败 | `js_router.cpp`（NAPI 参数解析）、`manifest_router.cpp`（路由表匹配） |
| 页面栈溢出（100003 错误） | `page_router_manager_factory.cpp`（栈深度限制逻辑） |
| 命名路由找不到页面 | `manifest_router.cpp`（命名路由表注册与匹配） |
| 路由恢复失败 | `router_recover_record.h`（恢复记录结构） |
| API 18 后 pushUrl 等静态谬用法不推荐 | **推荐 Navigation**，或 UIContext.Router 实例谬用法 |
| @system.router 方法不可用 | 已废弃，迁移到 Navigation |

## 调试入口

- NAPI 调用调试：`js_router.cpp` 中 NAPI 函数入口
- 路由表解析调试：`manifest_router.cpp` 中路由配置解析
- 路由栈管理调试：`page_router_manager_factory.cpp` 中栈创建与操作
- 静态版路由调试：`router_impl.ets` 中 ArkTS 静态版实现

## 相关主题

- [Navigation](../components/container/navigation.md) — Navigation + NavPathStack 是推荐的现代导航方案
- [NavDestination](../components/container/navdestination.md) — Navigation 子页面容器
