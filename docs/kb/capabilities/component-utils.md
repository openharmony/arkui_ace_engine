# ComponentUtils Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `ComponentUtils`

## 定位

ComponentUtils 提供组件几何信息查询，以及形状区域图像项筛选接口。几何查询由 UIContext/模块级 API 进入 NAPI、ANI 或 CJ 桥接，并复用 Inspector 和 FrameNode 几何信息；图像项筛选由 ComponentUtils NAPI 目标承载，并支持产品构建时替换实现。

本文档只提供稳定路由。返回字段、实例选择、异常、版本迁移和产品扩展行为，应以当前 SDK、源码、测试及 `04-11-01` Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dynamic UIContext | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | ComponentUtils 创建、缓存和实例路由入口 |
| Static UIContext | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | Static ArkTS ComponentUtils 实例路由 |
| NAPI 实现 | `interfaces/napi/kits/componentutils/js_component_utils.cpp` | 模块导出、参数转换和 Inspector 查询入口 |
| ANI 实现 | `interfaces/ets/ani/componentUtils/src/componentUtils.cpp` | Static ArkTS 几何查询桥接 |
| CJ FFI | `frameworks/bridge/cj_frontend/interfaces/cj_ffi/cj_component_utils_ffi.cpp` | CJ 几何查询与返回对象转换 |
| Frontend 代理 | `frameworks/bridge/js_frontend/frontend_delegate.cpp` | Dynamic 前端到 NG Inspector 的转发入口 |
| 查询核心 | `frameworks/core/components_ng/base/inspector.cpp` | 按 inspectorId 搜索节点和提取几何信息 |
| 默认形状筛选 | `interfaces/napi/kits/componentutils/js_mistouch_prevention.cpp` | 仓内默认 getItemsInShapePath 实现入口 |
| 构建替换边界 | `interfaces/napi/kits/componentutils/BUILD.gn`、`build/ace_ext.gni` | 默认实现与产品扩展 source list 的选择入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic ComponentUtils API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.componentUtils.d.ts` | 模块级几何查询、数据模型和图像筛选声明 |
| Static ComponentUtils API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.componentUtils.static.d.ets` | Static ArkTS 图像筛选契约 |
| UIContext API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | getComponentUtils 与实例级 ComponentUtils 声明 |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| Dynamic UIContext/NAPI | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js`、`interfaces/napi/kits/componentutils/js_component_utils.cpp` | 选择实例并进入 Inspector 查询 |
| Static UIContext/ANI | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets`、`interfaces/ets/ani/componentUtils/src/componentUtils.cpp` | Static ArkTS 实例路由和 native 查询 |
| CJ FFI | `frameworks/bridge/cj_frontend/interfaces/cj_ffi/cj_component_utils_ffi.cpp` | CJ 类型转换并复用 Inspector |
| 图像项筛选 NAPI | `interfaces/napi/kits/componentutils/js_component_utils.cpp`、`interfaces/napi/kits/componentutils/js_mistouch_prevention.cpp` | NAPI 导出和默认实现入口 |
| 产品扩展 | `interfaces/napi/kits/componentutils/BUILD.gn`、`build/ace_ext.gni` | 编译时以产品配置替换默认筛选实现 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 外部目标 | 说明 |
|----------|----------|-----------|----------|------|
| OpenCV（可选） | `interfaces/napi/kits/componentutils/BUILD.gn` | `<OH_ROOT>/third_party/opencv/` | `opencv:libopencv_core`、`libopencv_calib3d`、`libopencv_imgproc` | 仅产品配置启用替换实现时链接 |
| 图片框架（可选） | `interfaces/napi/kits/componentutils/BUILD.gn` | `<OH_ROOT>/foundation/multimedia/image_framework/` | `image_framework:image`、`image_native`、`pixelmap`、`pixelmap_ndk` | 仅产品配置启用替换实现时链接 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Inspector | `test/unittest/core/base/inspector_test_ng.cpp` | 节点查询、坐标、尺寸和变换信息验证 |
| NAPI 构建与实现 | `interfaces/napi/kits/componentutils/` | ComponentUtils 导出和默认筛选实现入口 |
| ArkUI-X XTS | `<OH_ROOT>/foundation/arkui/arkui_x/test/xts/arkui/crossplatform/componentutilsxts/` | 公开几何查询接口的跨平台验证入口 |

### 相关 Spec

功能域：`specs/04-common-capability/11-component-info/01-component-utils/`（功能 ID `04-11-01`）。

| Feat | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| Feat-01 | `Feat-01-component-geometry-query-spec.md` | 组件几何信息查询 |
| Feat-02 | `Feat-02-shape-path-image-filter-spec.md` | 形状区域图像项筛选 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 查询到了错误窗口或实例 | UIContext 实例路由、`js_component_utils.cpp` 和 ContainerScope |
| 节点 ID 存在但返回几何为空 | `inspector.cpp` 的主树/离屏节点搜索和 FrameNode 几何状态 |
| Dynamic、Static 或 CJ 返回字段不一致 | SDK 声明及对应 NAPI、ANI、CJ 桥接 |
| getItemsInShapePath 未执行预期筛选 | `BUILD.gn` 的产品配置分支与当前实际编译的实现源 |

## 调试入口

- API 检索：`getComponentUtils`、`getRectangleById`、`getItemsInShapePath`。
- 查询链路检索：`ComponentUtils`、`GetRectangleById`、`Inspector::GetFrameNodeByKey`。
- 构建分支检索：`ace_engine_mistouch_prevention`、`ace_engine_mistouch_prevention_mode`。

## 相关主题

- [UIContext。](ui-context.md)
- [FrameNode。](frame-node.md)
- [RenderNode。](render-node.md)