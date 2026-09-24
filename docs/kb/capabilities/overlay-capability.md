# OverlayCapability Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `OverlayCapability`

## 定位

ArkUI 浮层能力（OverlayManager）提供 Page 之上的常驻悬浮内容管理。开发者通过 `UIContext.getOverlayManager()` 获取 OverlayManager 实例，调用 `addComponentContent` / `removeComponentContent` / `showComponentContent` / `hideComponentContent` / `addComponentContentWithOrder` / `openOrderOverlay` / `setOverlayManagerOptions` 等 API 管理浮层节点。OverlayManager 维护 OVERLAY_ETS_TAG 透明全尺寸容器，通过 nodeIdOrderMap_ / orderNodesMap_ 双 map 管理 z-index 层级。支持 LevelMode（OVERLAY/EMBEDDED）路由到全局或页面级 OverlayManager。

本文档用于快速定位浮层能力相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| OverlayManager 核心 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.h` | OverlayManager 类声明，AddFrameNodeToOverlay/ShowNodeOnOverlay/OpenOrderOverlay 等 API |
| OverlayManager 实现 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | 7514 行实现，CreateOverlayNode/PutLevelOrder/GetNextNodeWithOrder 等 |
| OrderOverlayOptions | `frameworks/core/components_ng/pattern/overlay/overlay_options.h` | OrderOverlayOptions（levelOrder/levelMode/levelUniqueId） |
| LevelMode 枚举 | `frameworks/core/components_ng/pattern/overlay/level_mode.h` | LevelMode::OVERLAY / LevelMode::EMBEDDED |
| LevelOrder 类 | `frameworks/core/components_ng/pattern/overlay/level_order.h` | 精确 z-index，clamp 范围 [-100000, 100000] |
| OverlayContainerPattern | `frameworks/core/components_ng/pattern/overlay/overlay_container_pattern.cpp` | overlay/orderOverlay 容器节点 Pattern |
| DialogManagerStatic | `frameworks/core/components_ng/pattern/overlay/dialog_manager_static.cpp` | OpenOrderOverlayStatic、ShowInEmbeddedOverlay（EMBEDDED 路由） |
| DialogManager | `frameworks/core/components_ng/pattern/overlay/dialog_manager.cpp` | ShowInEmbeddedOverlay 页面级挂载 |
| JS 桥接 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | OverlayManagerImpl 类，addComponentContent → addFrameNode NAPI 委托 |
| NAPI 绑定 | `interfaces/napi/kits/overlay/js_overlay.cpp` | @ohos.overlayManager 模块导出 addFrameNode/showNode/hideNode 等 |
| InnerAPI OverlayManager | `interfaces/inner_api/ace_kit/include/ui/view/overlay/overlay_manager.h` | Kit::OverlayManager 抽象基类 |
| InnerAPI 实现 | `interfaces/inner_api/ace_kit/src/view/overlay/overlay_manager_impl.cpp` | OverlayManagerImpl 委托到 NG::OverlayManager |
| ANI 桥接 | `interfaces/ets/ani/overlayManager/src/overlayManager.cpp` | ArkTS Native Interface C++ 绑定 |
| ANI 参数 | `interfaces/ets/ani/overlayManager/src/overlay_params.h` | OverlayAsyncContext、GetLevelMode、GetOrderOverlayOptions |
| LevelOrder Peer | `frameworks/core/interfaces/native/implementation/level_order_extender_accessor.cpp` | LevelOrderExtenderAccessor（Construct/Clamp/GetOrder） |
| Tag 常量 | `frameworks/core/components_v2/inspector/inspector_constants.h` | OVERLAY_ETS_TAG="overlay"、ORDER_OVERLAY_ETS_TAG="OrderOverlay" |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | UIContext.getOverlayManager()、OverlayManager 类、OverlayManagerOptions |
| Static API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | 静态前端 OverlayManager 声明 |
| ANI | `interfaces/ets/ani/overlayManager/ets/@ohos.overlayManager.ets` | @ohos.overlayManager ANI 声明 |

API 检索建议：

- OverlayManager 类：在 SDK 文件中搜索 `OverlayManager`、`addComponentContent`、`openOrderOverlay`。
- LevelOrder/LevelMode：在 SDK 文件中搜索 `LevelOrder`、`LevelMode`。

### API 解析实现路径

OverlayManager 通过 JS→NAPI→C++ 三层桥接实现，不涉及独立 Pattern/Bridge/Modifier 路径。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 动态前端桥接 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | OverlayManagerImpl 类，getOverlayManager → addComponentContent → @ohos.overlayManager.addFrameNode |
| NAPI 底层 | `interfaces/napi/kits/overlay/js_overlay.cpp` | @ohos.overlayManager 模块，addFrameNode/showNode/hideNode/setOverlayManagerOptions |
| C++ 核心 | `frameworks/core/components_ng/pattern/overlay/overlay_manager.cpp` | OverlayManager::CreateOverlayNode/AddFrameNodeToOverlay/PutLevelOrder/OpenOrderOverlay |
| ANI 桥接 | `interfaces/ets/ani/overlayManager/src/overlayManager.cpp` | 静态前端 ANI 绑定 |
| 静态前端 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | OverlayManagerImpl 委托到 @ohos/overlayManager |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| `test/unittest/core/pattern/overlay/overlay_manager_test_ng.cpp` | OverlayManager 核心 API 回归测试 |
| `test/unittest/core/pattern/overlay/overlay_manager_test_core.cpp` | 测试基类和公共逻辑 |
| `test/unittest/core/pattern/overlay/overlay_manager_testone_ng.cpp` | 添加/删除节点测试 |
| `test/unittest/core/pattern/overlay/overlay_manager_content_test_ng.cpp` | Content 节点测试 |
| `test/unittest/core/pattern/overlay/overlay_manager_extend_test_ng.cpp` | 扩展 API 测试 |
| `test/unittest/core/pattern/overlay/overlay_manager_test_update_ng.cpp` | 更新操作测试 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 浮层能力功能域 | `specs/04-common-capability/08-root-view/03-overlay-capability/` | OverlayManager 挂载与管理规格目录 |
| Feat-01 | `specs/04-common-capability/08-root-view/03-overlay-capability/Feat-01-overlay-capability-spec.md` | 浮层能力全量规格 |
| 架构设计 | `specs/04-common-capability/08-root-view/03-overlay-capability/design.md` | 浮层能力架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 浮层节点不显示 | `OverlayManager::CreateOverlayNode` 确认 OVERLAY_ETS_TAG 容器创建；检查 rootNode->AddChildAfter |
| 有序添加层级不对 | `PutLevelOrder` 注册到 nodeIdOrderMap_ + orderNodesMap_；`GetNextNodeWithOrder` 插入位置 |
| EMBEDDED 模式不生效 | 确认 `levelUniqueId` 设置；查看 `DialogManagerStatic::ShowInEmbeddedOverlay` 路由逻辑 |
| 返回键不响应 | 检查 `setOverlayManagerOptions({ enableBackPressedEvent: true })`；API < 19 不支持侧滑 |
| 事件被浮层拦截 | 设置 `hitTestBehavior = HitTestMode.Transparent` 透传事件至底层 |
| 同一 ComponentContent 重复添加 | 只保留最后一次添加的节点，调用一次 remove 即可移除 |

## 调试入口

- 创建链路：从 `OverlayManager::CreateOverlayNode` 确认 OVERLAY_ETS_TAG 透明容器插入到 stage 之后
- 添加链路：`jsUIContext.js addComponentContent` → `@ohos.overlayManager.addFrameNode` → `OverlayManager::AddFrameNodeToOverlay`
- 有序添加：`AddFrameNodeWithOrder` → `PutLevelOrder` → `GetNextNodeWithOrder` 确定插入位置
- 层级路由：`OpenOrderOverlay` → `OrderOverlayOptions.levelMode` → OVERLAY（全局）或 EMBEDDED（页面级 levelUniqueId 查找）

## 相关主题

- [Dialog 弹窗组件（OverlayManager 管理 Dialog/Menu/Toast/Sheet 等）](../components/overlay/dialog.md)
- [模态属性（bindSheet/bindContentCover 也通过 OverlayManager 挂载）](modal-attributes.md)
- [子窗机制（子窗弹窗与 OverlayManager 的关系）](../architecture/subwindow-mechanism.md)
- [UIContext（getOverlayManager 入口）](ui-context.md)
- [渲染树同步](../architecture/render-tree-sync.md) — OverlayManager 通过 RebuildRenderContextTree 同步浮层节点
- [UIContext 实例 ID 泄漏](../issues/lifecycle/uicontext-instance-id-leak.md) — JS 前端历史配对问题（已修复）与浮层实例路由排查