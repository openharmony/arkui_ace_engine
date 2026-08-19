# ContainerSpan Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `ContainerSpan`

## 定位

ContainerSpan 是 ArkUI 文本类的容器片段组件，作为 `Text`/`RichEditor` 的子节点包裹多个子 Span/ImageSpan/SymbolSpan 形成逻辑分组，并可共享背景样式。ContainerSpanNode 继承 `UINode`+`BaseSpan`（非 FrameNode，非原子，可持有子 span），不存在独立 `ContainerSpanPattern`。ContainerSpan 唯一属性为 `textBackgroundStyle`，不支持任何通用事件，也无独立 NDK 节点类型。

ContainerSpan 属于 Span 类（FuncID 05-09-06）。行为事实以 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ContainerSpanNode（UINode+BaseSpan） | `frameworks/core/components_ng/pattern/text/span_node.h` | `ContainerSpanNode`（tag `V2::CONTAINER_SPAN_ETS_TAG`，非原子） |
| BaseSpan 基类 | `frameworks/core/components_ng/pattern/text/span_node.h` | `BaseSpan` 持有 `TextBackgroundStyle`、`MarkTextDirty` 委托 |
| Model façade | `frameworks/core/components_ng/pattern/text/span_model.h`、`span_model_ng.h`、`span_model_static.h` | `SpanModel::CreateContainSpan`/`SpanModelNG::CreateContainSpan`/`SetTextBackgroundStyle`/`SetTextBackgroundStyleByBaseSpan` |
| TextBackgroundStyle 定义 | `interface/sdk-js/api/@internal/component/ets/span.d.ts`、`interface/sdk-js/api/arkui/component/span.static.d.ets` | `color` + `radius` 共享接口 |
| C API 生成实现 | `frameworks/core/interfaces/native/implementation/container_span_modifier.cpp` | `ContainerSpanModifier::ConstructImpl` → `SpanModelStatic::CreateContainerSpanNode` |
| C API node 层 | `frameworks/core/interfaces/native/node/node_container_span_modifier.h`、`node_container_span_modifier.cpp` | `NodeModifier::GetContainerSpanModifier()` |
| C API 枚举 | `interfaces/native/native_node.h` | 无 `ARKUI_NODE_CONTAINER_SPAN`（ContainerSpan 无独立 NDK 节点类型） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/container_span.d.ts` | 动态 `ContainerSpanInterface`、`ContainerSpanAttribute`（独立类，不继承 CommonMethod）声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/containerSpan.static.d.ets` | 静态 `ContainerSpanAttribute`（独立 interface，不继承） |
| Modifier (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ContainerSpanModifier.d.ts` | `ContainerSpanModifier extends ContainerSpanAttribute implements AttributeModifier` |
| Modifier (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ContainerSpanModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | 无独立 NDK 节点类型 | `ARKUI_NODE_CONTAINER_SPAN` 不存在；仅经 ArkTS 组件或 styled-string 暴露 |

API 检索建议：

- 属性声明：搜索 `ContainerSpanAttribute` 与 `textBackgroundStyle`（唯一属性，继承自 `span` 的 `TextBackgroundStyle`）。
- 事件：ContainerSpan **不支持任何通用事件**（onClick/onHover/onTouch 均不支持）。
- 版本演进：dynamic 自 API 11，attributeModifier @since 12；static 全量 @since 23。
- Static/Dynamic 继承分野：dynamic/static 均不继承 `CommonMethod`/`BaseSpan`，无通用属性/事件继承；唯一属性 `textBackgroundStyle` 直接声明。
- ContainerSpan 不支持 `baselineOffset`（与 Span/ImageSpan 不同）。

### API 解析实现路径

ContainerSpan **尚未进行组件化改造**，属性解析采用 JSView + 直连 C-API 双路径，编译产物在主 `libace_compatible.z.so` 中。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_container_span.cpp` | `JSContainerSpan::Create` → `SpanModel::GetInstance()->CreateContainSpan()`；`ParseTextBackgroundStyle` → `SetTextBackgroundStyle` |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_container_span_modifier.cpp` | C++ 属性 Set/Reset/Get，由 C API 共用 |
| C API（NDK）生成实现 | `frameworks/core/interfaces/native/implementation/container_span_modifier.cpp` | `ContainerSpanModifier::ConstructImpl` → `SpanModelStatic::CreateContainerSpanNode`；非动态模块桩 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/container_span_modifier.ts` | ArkTS `ContainerSpanModifier` 类定义 |

ContainerSpan 无独立 `arkts_native_container_span_bridge`（ArkTS 属性经 JSView 路径）；C-API 实现为真实代码（非动态模块桩）。


### 外部依赖入口

ContainerSpan 无独立布局/渲染层，外部依赖经父级 Text/RichEditor 段落管线承载，与 Span 共享：

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 排版/段落构建 | `frameworks/core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.*` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | ContainerSpan 及其子 span 经父级 Paragraph 排版 |
| 背景绘制 | `frameworks/core/components_ng/render/adapter/drawing_decoration_painter.*` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/*` | textBackgroundStyle 圆角矩形背景绘制 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text/` | `span_*_test_ng.cpp` 覆盖 ContainerSpan 节点/属性行为 |
| Spec 功能域 | `specs/05-ui-components/09-text-components/06-span-components/` | Span 类功能域设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `05-09-06 Span类` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | ContainerSpan 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Span 类功能域：`specs/05-ui-components/09-text-components/06-span-components/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-04 | ContainerSpan 容器片段组件 | `Feat-04-container-span-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ContainerSpan 不渲染 | 父级是否为 `Text`/`RichEditor`；`MultipleParagraphLayoutAlgorithm` 是否消费 |
| 子 span 未分组挂载 | `ContainerSpanNode` 非原子，确认子 span 挂为子节点 |
| 背景样式不生效 | `JSContainerSpan::ParseTextBackgroundStyle`、`SpanModelNG::SetTextBackgroundStyleByBaseSpan`、`TextBackgroundStyle` color/radius |
| onClick/onHover 等事件无效 | ContainerSpan 不支持任何通用事件（文档明确） |
| baselineOffset 无效 | ContainerSpan 不支持 baselineOffset（与 Span/ImageSpan 不同） |
| NDK 无法创建 ContainerSpan | ContainerSpan 无独立 NDK 节点类型；需经 styled-string 或 ArkTS 组件 |

## 调试入口

- 创建链路：从 `JSContainerSpan::Create` → `SpanModelNG::CreateContainSpan` → `ContainerSpanNode`（UINode+BaseSpan，非原子）。
- 属性链路：`ParseTextBackgroundStyle` → `SetTextBackgroundStyleByBaseSpan` 写入 `BaseSpan` 的 `TextBackgroundStyle`。
- dirty 传播：`ContainerSpanNode::MarkTextDirty` 委托 `SpanNode::RequestTextFlushDirty` 传播至父级。
- 回归验证：`test/unittest/core/pattern/text/` 下 `span_*_test_ng.cpp`。

## 相关主题

- `Text`：`docs/kb/components/basic/text.md`
- `Span`：`docs/kb/components/basic/span.md`
- `ImageSpan`：`docs/kb/components/basic/image-span.md`
- `SymbolSpan`：`docs/kb/components/basic/symbol-span.md`