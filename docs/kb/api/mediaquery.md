# MediaQuery Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `MediaQuery`

## 定位

MediaQuery 是 ArkUI 提供的 `@ohos.mediaquery` 模块能力，用于创建媒体条件监听对象；UIContext 也提供与当前 UI 实例绑定的访问入口。条件解析和当前媒体特征由 declarative frontend 的公共 media_query 子系统提供，Dynamic 与 Static 分别通过 NAPI 和 ANI 接入。

本文档覆盖 `@ohos.mediaquery`、UIContext 入口、兼容 `@system.mediaquery` 声明，以及当前实现和测试路由。条件语法、支持特征、版本边界和回调语义以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 条件解析与匹配 | `frameworks/bridge/common/media_query/media_queryer.cpp`、`frameworks/bridge/common/media_query/media_queryer.h` | MediaQuery 条件规则、解析和匹配入口 |
| 媒体特征收集 | `frameworks/bridge/common/media_query/media_query_info.cpp`、`frameworks/bridge/common/media_query/media_query_info.h` | 尺寸、方向、设备和颜色模式等当前媒体信息入口 |
| Dynamic NAPI 模块 | `interfaces/napi/kits/mediaquery/js_media_query.cpp` | `mediaquery` NAPI 导出、监听对象和回调管理入口 |
| Static ANI 模块 | `interfaces/ets/ani/mediaquery/src/mediaquery.cpp`、`interfaces/ets/ani/mediaquery/ets/@ohos.mediaquery.ets` | Static ArkTS 模块、ANI 对象和回调绑定入口 |
| Static ArkTS 声明实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.mediaquery.ts` | Static 前端类型和模块声明入口 |
| UIContext Dynamic 入口 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | UIContext 的 MediaQuery 对象创建和 NAPI 模块获取入口 |
| 前端更新调度 | `frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.cpp`、`frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` | 媒体信息更新到前端回调的调度入口 |
| 构建入口 | `interfaces/napi/kits/mediaquery/BUILD.gn`、`interfaces/ets/ani/mediaquery/BUILD.gn` | NAPI 模块、ANI 库和 Static ABC 构建入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.mediaquery.d.ts` | `mediaquery`、MediaQueryResult、MediaQueryListener 和模块函数声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/@ohos.mediaquery.static.d.ets` | Static `mediaquery` 模块与监听对象声明 |
| UIContext Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | UIContext MediaQuery 对象入口声明 |
| UIContext Static API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | Static UIContext MediaQuery 对象入口声明 |
| 兼容 System API | `<OH_ROOT>/interface/sdk-js/api/@system.mediaquery.d.ts`、`<OH_ROOT>/interface/sdk-js/api/@system.mediaquery.static.d.ets` | 兼容 `@system.mediaquery` 的声明入口 |
| Native Node API | 未提供 | MediaQuery 是 NAPI/ANI 模块能力，不提供专属 ArkUI Native Node C API |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 条件解析与匹配测试 | `test/unittest/bridge/common/media_query/media_query_test.cpp` | MediaQueryer 规则、媒体特征和匹配回归 |
| 测试构建入口 | `test/unittest/bridge/common/media_query/BUILD.gn` | media_query 定向单元测试目标与源码清单 |
| 测试支持文件 | `test/unittest/bridge/common/media_query/media_query_test_core.cpp`、`test/unittest/bridge/common/media_query/media_query_test_min.cpp` | 定向测试的公共支持入口 |
| Context registry | `docs/context_registry.json` | MediaQuery 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

MediaQuery 功能 ID 为 `04-20-01`，规划功能域为 `specs/04-common-capability/20-media-query/01-media-query/`。

当前 functions registry 已登记该主题，但目标 Spec 目录尚未建立，因此 registry 使用 `spec_status: pending`；实际 Feat 或设计文档补齐后再更新本页路由。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `@ohos.mediaquery` 模块或 `matchMediaSync` 不可用 | SDK 声明、NAPI BUILD、`js_media_query.cpp` 和 UIContext Dynamic 入口 |
| Static ArkTS 调用或回调异常 | Static SDK、`@ohos.mediaquery.ets`、ANI 实现、Static 前端声明和 ANI BUILD |
| 条件匹配结果异常 | `MediaQueryer`、`MediaQueryInfo` 和 media_query 单元测试 |
| 媒体信息变化后未触发监听 | NAPI/ANI 监听对象、FrontendDelegate 的更新调度和 JSI 回调入口 |
| UIContext 与模块直调结果不一致 | UIContext API、`jsUIContext.js`、实例作用域和对应 NAPI/ANI 实现 |
| 查找 Native Node C API | 当前没有专属节点属性或 C API；应从 NAPI/ANI 与 SDK 模块入口排查 |

## 调试入口

- 先确认调用使用 `@ohos.mediaquery`、UIContext 还是兼容 System API，并从相应 SDK 声明进入。
- Dynamic 路径优先检查 NAPI 模块导出、MediaQueryListener 和 UIContext 的 `requireNapi` 入口。
- Static 路径优先检查 Static 声明、ANI ETS、ANI 实现和 `mediaquery_ani` 构建入口。
- 条件问题从 MediaQueryer 规则和 MediaQueryInfo 当前特征开始，而不是从应用侧字符串推断。
- 回归优先运行 `test/unittest/bridge/common/media_query/media_query_test.cpp`。

## 相关主题

- [UIContext：`docs/kb/capabilities/ui-context.md`](../capabilities/ui-context.md)
- [Layout Attributes：`docs/kb/capabilities/layout-attributes.md`](../capabilities/layout-attributes.md)
- [Router：`docs/kb/api/router.md`](router.md)