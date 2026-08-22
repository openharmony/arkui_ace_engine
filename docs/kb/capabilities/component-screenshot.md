# Component Screenshot Context

> 文档版本：v1.0
> 更新时间：2026-08-01
> 来源：`docs/context_registry.json` 主题 `ComponentScreenshot`

## 定位

组件截图是将已挂载或离屏构建的 ArkUI 节点捕获为 PixelMap 的通用能力。它包含独立 `@ohos.arkui.componentSnapshot` 模块、`UIContext.ComponentSnapshot` 服务以及 NDK 节点截图接口。

该主题是服务型能力，不对应独立可视组件 Pattern/Model。公开接口、错误码、资源所有权及动态/静态前端差异应以各自 SDK 声明和 C header 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 核心截图服务 | `frameworks/core/components_ng/render/adapter/component_snapshot.*` | 已挂载节点、离屏节点、同步/异步截图及渲染后端调用入口。 |
| 截图参数模型 | `frameworks/core/components_ng/render/snapshot_param.h` | SnapshotOptions、离屏延迟和图片状态检查参数。 |
| 声明式前端委托 | `frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.cpp` | Builder/ComponentContent 与核心截图服务之间的路由。 |
| 独立动态模块 | `interfaces/napi/kits/component_snapshot/` | `@ohos.arkui.componentSnapshot` NAPI 导出和参数解析。 |
| 静态 ArkTS 路由 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | UIContext 静态前端服务入口。 |
| 静态 ANI 桥 | `frameworks/core/interfaces/native/ani/component_snapshot_ani_modifier.*` | 静态前端与核心截图服务的绑定。 |
| NDK 节点截图 | `interfaces/native/node/node_component_snapshot.*` | SnapshotOptions 与 NodeHandle 同步截图实现。 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 独立动态 ArkTS 模块 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.componentSnapshot.d.ts` | 旧 `get`、`getSync`、`createFromBuilder` API；迁移信息也在此声明。 |
| 动态 UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | ComponentSnapshot 服务、已挂载、范围和离屏截图的主契约。 |
| 静态 UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | 静态前端对应签名及其可空返回差异。 |
| 静态独立模块 | `interfaces/ets/ani/componentSnapshot/ets/@ohos.arkui.componentSnapshot.ets` | ANI 模块的静态 ArkTS 入口。 |
| NDK 头文件 | `interfaces/native/native_node.h`、`interfaces/native/native_type.h` | Node Snapshot、Options 创建/销毁、色彩/HDR 和尺寸限制契约。 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|----------|----------|------|
| 图形捕获 | `frameworks/core/components_ng/render/adapter/component_snapshot.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/transaction/rs_interfaces.h`、`rosen/modules/render_service_client/core/ui/rs_ui_context.h`；GN 目标 `graphic_2d:librender_service_base`、`graphic_2d:librender_service_client` | 核心截图服务通过 Rosen Surface Capture 获得 PixelMap。 |
| 图像对象 | `interfaces/napi/kits/component_snapshot/js_component_snapshot.cpp`、`interfaces/native/node/node_component_snapshot.cpp` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h`、`interfaces/kits/js/common/include/pixel_map_napi.h`、`frameworks/kits/js/common/ndk/include/pixelmap_native_impl.h`；GN 目标 `image_framework:image`、`image_framework:image_native` | PixelMap 的创建、封装、返回和后续消费由图像接口负责。 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| NDK 节点截图测试 | `test/unittest/interfaces/node_component_snapshot_test.cpp` | NodeHandle 截图和参数覆盖。 |
| C API accessor 测试 | `test/unittest/capi/accessors/component_snapshot_accessor_test.cpp` | C API Options/访问器覆盖。 |
| C API mock | `test/unittest/capi/stubs/mock_component_snapshot.*` | 原生接口 mock 入口。 |
| 渲染上下文测试 | `test/unittest/core/rosen/` | 查找与 Rosen/渲染上下文相关的截图测试。 |

### 相关 Spec

| 功能域 | Spec 路径 | 说明 |
|--------|-----------|------|
| 组件截图 | `specs/04-common-capability/10-component-screenshot/01-offscreen-screenshot/` | 独立模块、UIContext、离屏 Builder/Content、Options 与 C API 规格。 |
| UIContext | `specs/04-common-capability/12-ui-context/` | UIContext 服务对象通用路由。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 找不到独立截图接口页面 | 先检查 `@ohos.arkui.componentSnapshot.d.ts`；它是独立模块，不只是 UIContext 迁移注记。 |
| 新旧 ArkTS 截图 API 选择 | 检查独立模块的弃用信息和 UIContext 声明，再按目标 API 版本选择。 |
| Builder 或 ComponentContent 离屏截图失败 | 检查 FrontendDelegate、SnapshotParam、ComponentSnapshot 和 Options 约束。 |
| 离屏色彩/HDR 配置失败 | 检查 colorMode/dynamicRangeMode 的 `isAuto` 约束以及 NAPI/ANI 参数解析。 |
| C API 返回空 PixelMap 或错误码 | 检查 NodeHandle 是否已挂树/渲染、Options 生命周期和 native_node/native_type 契约。 |
| 截图尺寸或同步等待问题 | 检查 ComponentSnapshot 核心服务及 NDK 尺寸限制查询接口。 |

## 调试入口

- 使用 `rg -n "ComponentSnapshot|createFromBuilder|createFromComponent|getWithRange" <OH_ROOT>/interface/sdk-js/api` 检索 ArkTS 契约。
- 使用 `rg -n "ComponentSnapshot|TakeSurfaceCapture|SnapshotParam" frameworks/core frameworks/bridge interfaces/napi` 回溯核心和桥接入口。
- 使用 `rg -n "OH_ArkUI_.*Snapshot" interfaces/native` 检索 NDK 截图和 Options API。

## 相关主题

- [docs/kb/capabilities/ui-context.md](ui-context.md)
- [docs/kb/capabilities/image-loading.md](image-loading.md)
- [docs/kb/architecture/basic-render-pipeline.md](../architecture/basic-render-pipeline.md)