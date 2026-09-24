# DrawModifier Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `DrawModifier`

## 定位

本主题的主角是 **ArkTS 的 `DrawModifier` 类**——通过 `.drawModifier(modifier)` 绑定到组件、对外经通用属性方法暴露的自定义绘制扩展。它提供 5 个绘制回调（drawBehind/drawContent/drawFront/drawForeground/drawOverlay）+ `invalidate()` 主动刷新，按五层固定顺序分发，drawContent 等替换原生绘制、其余叠加，并与原生绘制经 InnerDraw 互为回退。

ArkTS `DrawModifier` 是一层回调容器：底层 `NG::DrawModifier`（C++，`frameworks/core/components_ng/base/modifier.h`，5 个 `DrawModifierFunc` 成员）+ `ExtensionHandler`（`extension_handler.h`，三段式 Draw/ForegroundDraw/OverlayDraw 分发）是 ArkTS 回调的中转与底层能力提供者。**C++ 的 `NG::DrawModifier`/`ExtensionHandler` 不是本主题的主角**——如需分发/回退/刷新链实现细节，再深入 C++ 层。

行为事实以 SDK 类型声明（`common.d.ts`/`common.static.d.ets`/`Graphics.d.ts`）、ArkTS 实现（`js_view_abstract.cpp`/`ArkComponent.ts`）、测试与长期规格为准；本页仅作路由导航，不重复行为矩阵。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **JS Bridge（主角入口）** | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `JsDrawModifier` 装配入口、`AddInvalidateFunc` 挂 invalidate、`GetDrawCallback`/`GetDrawOverlayCallback` 构造 DrawContext（ClipCanvas 裁剪） |
| C++ 回调容器 | `frameworks/core/components_ng/base/modifier.h` | `NG::DrawModifier`：5 个 `DrawModifierFunc` 成员（drawBehind/Content/Front/Foreground/OverlayFunc）；`DrawingContext`={canvas,width,height} |
| C++ 分发核心 | `frameworks/core/components_ng/base/extension_handler.h/cpp` | `ExtensionHandler`：Draw/ForegroundDraw/OverlayDraw 三段式、OnDraw 五层顺序、InvalidateRender/ForegroundRender、NeedRender API20 门控 |
| 挂载载体 | `frameworks/core/components_ng/base/frame_node.cpp` | `FrameNode::SetDrawModifier`：无 ExtensionHandler 则新建+AttachFrameNode；`IsSupportDrawModifier` Pattern 门控 |
| 管线衔接 | `frameworks/core/components_ng/render/paint_wrapper.cpp` | extensionHandler 存在时替换 Flush*DrawFunction 回调为 ExtensionHandler 调用 + 注入原生 draw 为 InnerImpl |
| Pattern 门控 | `frameworks/core/components_ng/pattern/pattern.h` | `IsSupportDrawModifier` 默认 true（opt-out）；6 组件重写 false（canvas/effect/distortion/video/video_state_machine/union_effect_container） |
| C-API(Arkoala) | `frameworks/core/interfaces/native/implementation/draw_modifier_accessor.cpp` | 仅暴露 drawBehind/drawContent/invalidate |
| C-API(ANI) | `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | 全部 5 回调 + invalidate |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 动态（主角）** | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `DrawModifier` 类 + `drawModifier()` 方法；DrawContext 在 `arkui/Graphics.d.ts`(@since 11) |
| **SDK 静态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 `DrawModifier` + `drawModifier()`；DrawContext 在 `Graphics.static.d.ets` |
| 五层顺序文档 | `common.static.d.ets` / `common.d.ts` | Behind→Content→Front→Foreground→Overlay；Overlay 可越界 |

### API 解析实现路径

ArkTS `DrawModifier` 的解析自上而下：JS Bridge → Model → FrameNode → ExtensionHandler →（下沉）PaintWrapper/RenderContext。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JS Bridge | `js_view_abstract.cpp` | JsDrawModifier 解析 modifier 对象、校验 IsSupportDrawModifier、新建 NG::DrawModifier 填充 5 回调、API20 移除语义 |
| Model/API | `view_abstract_model_static.cpp`/`view_abstract.cpp` | SetDrawModifier 转调 FrameNode |
| 挂载 | `frame_node.cpp` | SetDrawModifier 创建 ExtensionHandler + AttachFrameNode |
| 分发 | `extension_handler.cpp` | Draw/ForegroundDraw/OverlayDraw 三段 + OnDraw 五层顺序 + NeedRender 门控 |
| 管线 | `paint_wrapper.cpp` | FlushRender 衔接 + InnerImpl 注入 + !contentModifier 守卫 |

**关键门控/版本**（详见各 Feat 规格风险表）：`IsSupportDrawModifier` opt-out 6 组件；API20 移除语义分界（非对象入参执行移除）；NeedRender/needRerender API20 门控（<20 挂载即重画，≥20 引入 skippedMeasure）；invalidate() JS 路径刷两段(InvalidateRender+ForegroundRender)、C-API 仅 InvalidateRender——路径不一致(风险 R-3)。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测 | `test/unittest/core/base/` | ExtensionHandler/FrameNode DrawModifier 挂载与分发 |
| C-API 单测 | `test/unittest/capi/` | draw_modifier_accessor / common_ani_modifier |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/05-custom-extension/01-draw-modifier/design.md` | Baselined（`DESIGN-Func-04-05-01`） |
| Feat-01 装配与组件门控 | `specs/04-common-capability/05-custom-extension/01-draw-modifier/Feat-01-draw-modifier-mounting-gating-spec.md` | Baselined |
| Feat-02 五层绘制回调分发 | `specs/04-common-capability/05-custom-extension/01-draw-modifier/Feat-02-draw-modifier-layered-dispatch-spec.md` | Baselined |
| Feat-03 主动刷新机制 | `specs/04-common-capability/05-custom-extension/01-draw-modifier/Feat-03-draw-modifier-invalidate-refresh-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| drawModifier 设置后组件无自定义绘制 | 检查组件是否在 6 个 opt-out 列表（Canvas/Video/Effect 等）——IsSupportDrawModifier=false 静默拒绝。见 Feat-01 R-15 |
| invalidate() 后未重绘 | NeedRender/needRerender API20 门控；<20 挂载即重画，≥20 需 !skippedMeasure。见 Feat-03 R-10/R-12 |
| drawOverlay 无法越界绘制 | SDK 声明可越界，但 GetDrawOverlayCallback 同样 ClipCanvas——JS 层未体现越界机制(风险 R-2)。见 Feat-02 R-18 |
| drawContent 设了但原生内容仍绘制 | drawContent 无回调才回退 InnerDraw；有回调即替换。检查回调是否正确赋值。见 Feat-02 R-2 |
| 同一 DrawModifier 实例设到多组件 | SDK 契约禁止，但源码 SetDrawModifier 仅赋值未校验(风险 R-1)。见 Feat-01 R-6 |
| C-API invalidate 刷新范围小于 JS | C-API 仅 InvalidateRender，JS 调 InvalidateRender+ForegroundRender(风险 R-3)。见 Feat-03 R-16/R-17 |

## 调试入口

- **ExtensionHandler 状态**：`extension_handler.cpp` 的 `needRender_`/`drawModifier_`/`innerDrawImpl_` 为分发与回退状态来源。
- **画布裁剪**：`js_view_abstract.cpp/13023` 的 ClipCanvas 裁剪到组件 bounds（drawOverlay 同样裁剪——越界机制存疑）。
- **Pattern 门控**：6 个 opt-out Pattern 重写 `IsSupportDrawModifier=false`。

## 相关主题

- [Attribute Modifier](./attribute-modifier.md) — `AttributeModifier<T>` 动态属性通路（04-05-02）
- [Component Modifier](./component-modifier.md) — 命令式 `CommonModifier`/`XxxModifier` 类体系（04-05-06）
- [Custom Property](./custom-property.md) — `customProperty` 自定义属性（04-05-05）
- [Layout Framework](../architecture/layout-framework.md) — DrawModifier 经 PaintWrapper 衔接的渲染管线