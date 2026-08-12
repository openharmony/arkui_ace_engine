# NamedRouter Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `NamedRouter`

## 定位

ArkUI 命名路由通过 `@ohos.router.pushNamedRoute` / `replaceNamedRoute` 接口实现命名路由跳转。NAPI 入口 js_router.cpp 将请求委托到 FrontendDelegate → PageRouterManager，由后者管理页面栈和转场动画。

本文档用于快速定位 Named Router 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| js_router | `interfaces/napi/kits/router/js_router.cpp` | |
| frontend_delegate | `frameworks/bridge/declarative_frontend/frontend_delegate_declarative.cpp` | |
| frontend_delegate_ng | `frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.cpp` | |
| page_router_manager | `frameworks/bridge/declarative_frontend/ng/page_router_manager.cpp` | |
| page_router_manager_static | `frameworks/bridge/declarative_frontend/ng/page_router_manager_static.cpp` | |
| js_ui_context | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| router | `<OH_ROOT>/interface/sdk-js/api/@ohos.router.d.ts` | |
| system_router | `<OH_ROOT>/interface/sdk-js/api/@system.router.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/navigation/navigation_pattern_test_ten_ng.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/04-common-capability/15-router-mechanism/02-named-router/` | 命名路由机制，pushNamedRoute/replaceNamedRoute 通过 PageRouterManager 管理页面栈。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 命名路由找不到页面 | 确认 namedRoute 已在页面中通过 `routerNamedRoute` 注册 |
| 路由参数丢失 | 检查 PageRouterManager::PushNamedRoute 的 params 传递 |

## 调试入口

- 跳转链路：js_router.cpp → FrontendDelegate → PageRouterManager::PushNamedRoute
- 页面栈：PageRouterManager 管理页面栈和转场

## 相关主题

- Router 路由管理
- Navigation 导航容器
- NavDestination
