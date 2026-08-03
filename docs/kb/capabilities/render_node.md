# RenderNode Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `RenderNode`

## 定位

本主题的主角是 **ArkTS 的 `RenderNode` 类**——通过 `new RenderNode()` 创建、对外经 `@ohos.arkui.node` 模块暴露的轻量绘制节点。它承载自定义绘制：帧几何、背景阴影、边框、形状遮罩/裁剪、变换、透明度/绘制优先级、draw 回调、子节点树、模糊效果，是功能域 `04-06-03` 的规格对象。

ArkTS `RenderNode` 持有对底层节点的强引用，属性 setter 经 JSI bridge 下沉到 native 修饰器。**C++ `NG::RenderNode`/Rosen 仅为底层能力提供者**——深入底层度量/布局/绘制实现时再查 C++。

行为事实以 SDK（`RenderNode.d.ts`/`.static.d.ets`）、ArkTS 实现（`render_node.ts`）、测试与长期规格为准；本页仅作路由导航。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **ArkTS 运行时类（主角）** | `frameworks/bridge/declarative_frontend/ark_node/src/render_node.ts` | `RenderNode` 类：属性 setter 缓存+下发 native（getter 返回缓存非 native 往返）、子树操作、dispose、draw 声明、shapeMask/Clip 形状分支 |
| 共享基类 | `frameworks/bridge/declarative_frontend/ark_node/src/base_node.ts` | `BaseNode`：强引用生命周期、instanceId 同步（FrameNode/BuilderNode/RenderNode 共享） |
| **JSI Bridge（ArkTS→native 边界）** | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.cpp` | `RenderNodeBridge::*`：Create/SetOnDraw/FireDrawCallback（构建 DrawContext{size,sizeInPixel,canvas}）/AppendChild/各属性 setter；100025 adopt 映射 |
| NDK Modifier | `frameworks/core/interfaces/native/node/node_render_node_modifier.cpp` | ArkTS 调用的 native 修饰器函数表（~90 函数：tree/geometry/shadow/border/mask/blur/animatable property） |
| **C++ NG 底层（仅作来源）** | `frameworks/core/components_ng/pattern/render_node/render_node_pattern.h` | 底层绘制能力（RenderNodePattern 持 draw 回调）。深入时再查 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 动态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/RenderNode.d.ts` | ArkTS `RenderNode` 类全部公开 API + DrawContext |
| **SDK 静态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/RenderNode.static.d.ets` | 静态 `RenderNode`（`@stagemodelonly`，`@since 23 static`） |
| 图形类型 | `<OH_ROOT>/interface/sdk-js/api/arkui/Graphics.d.ts` | Size/Position/Frame/Edges/Matrix4/ShapeMask/ShapeClip/Blur 等类型 |
| 模块入口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.node.d.ts` | re-export `RenderNode` |

### API 解析实现路径

ArkTS `RenderNode` API 解析自上而下：ArkTS 类 → JSI bridge → NDK modifier →（下沉）NG。**主轴在 ArkTS 层**。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **ArkTS 运行时** | `frameworks/bridge/declarative_frontend/ark_node/src/render_node.ts` | API 行为主轴：属性 setter 校验+缓存+下发 native、getter 返回缓存、draw 声明、子树操作、dispose 幂等、100025 adopt 映射 |
| ArkTS → native 边界 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.cpp` | `RenderNodeBridge::*` 转 native；FireDrawCallback 构建 DrawContext |
| native 修饰器 | `frameworks/core/interfaces/native/node/node_render_node_modifier.cpp` | ArkTS 调用的 native 实现（~90 函数） |
| C++ NG 终端 | `frameworks/core/components_ng/pattern/render_node/render_node_pattern.h` | 下沉到底层绘制；**非规格对象，深入时再查** |

**错误码**：appendChild/insertChildAfter 对已 adopt child 抛 100025（"FrameNode cannot be adopted"）。详见 Feat-01 规格风险表。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| C-API 单测 | `test/unittest/interfaces/native_render_node_test.cpp` | create/dispose/树/属性/mask/blur（128 用例） |
| C-API 属性单测 | `test/unittest/interfaces/native_render_node_property_test.cpp` | animatable property（19 用例） |
| NG pattern 单测 | `test/unittest/core/pattern/render_node/render_node_test_ng.cpp` | RenderNodePattern/PaintMethod/blur |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/06-custom-node/03-render-node/design.md` | Baselined（`DESIGN-Func-04-06-03`） |
| Feat-01 RenderNode 全量规格 | `specs/04-common-capability/06-custom-node/03-render-node/Feat-01-render-node-full-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| getter 返回值与 native 不一致 | getter 返回 TS 缓存（非 native 往返）；setter 同步缓存，正常一致。见 Feat-01 R-1 |
| frame/position/size 优先级 | 后设置的胜出。见 Feat-01 R-5 |
| appendChild 抛 100025 | child 已 adopt。见 Feat-01 R-20 |
| clipToFrame 默认随版本 | API12 前默认 false，后 true。见 Feat-01 R-12 |
| shadowRadius API26 哨兵 -1 | 默认值版本差异。见 Feat-01 风险项 |
| 无事件/动画 API | ArkTS RenderNode 无公开事件/动画 API；事件在 BaseNode，动画经属性隐式。见 Feat-01 风险项 |
| draw 调用两次 | 初始化时调两次（FrameNode 创建+modifier 首设）；后续由 modifier 触发。见 Feat-01 R-17 |

## 调试入口

- **Inspector 标签**：`set label` 设置调试标签（仅 `new` 创建节点显示）。
- **invalidate**：触发重绘。
- **DrawContext**：draw 回调获 size(vp)/sizeInPixel(px)/canvas。

## 相关主题

- [FrameNode](./frame_node.md) — `getRenderNode()` 返回的节点类型；RenderNode 可挂载到 FrameNode
- BuilderNode（`04-06-04`）— 可将 RenderNode 嵌入；嵌入时 selfIdealSize 须显式
- Shape/Mask 类型（Graphics.d.ts）— ShapeMask/ShapeClip 形状定义
