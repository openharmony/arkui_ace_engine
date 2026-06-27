# ArkUI SDK API 结构化分析文档

> **文档说明**: 本档位于 ace_engine 仓库，分析 OpenHarmony SDK API 与 ace_engine 实现层的映射关系。SDK API 定义文件位于 `OpenHarmony/interface/sdk-js/api/arkui/`，ace_engine 实现文件位于 `OpenHarmony/foundation/arkui/ace_engine/`。

**API 版本**: API 11 - API 23
**SDK API 路径**: `OpenHarmony/interface/sdk-js/api/arkui/`
**ace_engine 实现路径**: `OpenHarmony/foundation/arkui/ace_engine/`

---

## Agent 参考指南

### 文档用途
本文档是 Agent 的内部参考知识库，用于：
1. **快速定位 SDK API 与实现层的映射关系** - 当用户询问组件功能时，能迅速找到源码位置
2. **理解 ArkUI 架构层次** - 区分 Static API、Dynamic API、ace_engine Pattern 的职责
3. **准确回答开发问题** - 提供基于实际代码的权威答案，避免猜测

### 如何使用此知识库

#### 场景 1: 用户询问组件功能或实现
```
用户问题: "Text 组件的字体大小是怎么设置的？"
查找步骤:
1. 在"3.1 基础组件"中找到 Text 组件
2. 查看 ace_engine Pattern 位置: text_pattern.cpp
3. 查看 Modifier 文件: TextModifier.d.ts
4. 读取源码验证实现
```

#### 场景 2: 用户询问 API 使用方法
```
用户问题: "FrameNode 和 BuilderNode 有什么区别？"
查找步骤:
1. 查看"2.2 Node API 核心节点类型"章节
2. 对比 FrameNode 和 BuilderNode 的核心特性
3. 查看"7.2 Node 层级关系"理解架构设计
4. 查看"常见问题解答"获取更多说明
```

#### 场景 3: 用户询问状态管理
```
用户问题: "@State 和 @Link 的区别是什么？"
查找步骤:
1. 查看"6. 状态管理 API"章节
2. 理解各装饰器的用途
3. 查看"常见问题解答"中的状态管理对比
```

### 快速查找指南

| 想查找什么 | 跳转到章节 |
|-----------|-----------|
| 组件列表和实现位置 | 第 3 章 "组件 API 分类清单" |
| 核心 API (FrameNode/BuilderNode) | 第 2.2 节 "Node API 核心节点类型" |
| 组件属性设置方法 | 第 2.4 节 "Modifier 模式" |
| 声明文件结构（Attribute/Options） | 第 4 章 "组件声明文件结构规范" |
| 状态管理装饰器 | 第 6 章 "状态管理 API" |
| SDK → ace_engine 映射 | 第 8 章 "与 ace_engine 的对应关系" |
| 命名规范与导入约定 | 第 9 章 "API 定义规范" |
| 常见问题解答 | 第 10 章 "常见问题解答" |

### 代码验证原则
根据 ace_engine 的 **AGENTS.md** 原则，回答问题时：
1. **Always provide actual code** - 使用 Read/Grep 工具读取实际源码
2. **Never guess** - 如果代码未找到，明确说明"此代码在 ace_engine 中未找到"
3. **Verify before answering** - 用户建议可能有误，务必验证实际代码
4. **Provide evidence** - 给出文件路径和行号作为证据

---

## 1. 目录结构概览

```
OpenHarmony/interface/sdk-js/api/
├── arkui/
│   ├── component/                         # 静态 API：组件+属性定义（*.static.d.ets）
│   │   ├── column.static.d.ets
│   │   ├── text.static.d.ets
│   │   ├── button.static.d.ets
│   │   └── [... 130 个静态组件定义文件]
│   ├── [76个 *Modifier.d.ts 文件]        # 动态 API：Modifier 定义
│   ├── [74个 *Modifier.static.d.ets 文件] # 静态 API：Modifier 定义
│   ├── FrameNode.d.ts / BuilderNode.d.ts / RenderNode.d.ts
│   ├── FrameNode.static.d.ets / BuilderNode.static.d.ets / RenderNode.static.d.ets
│   ├── stateManagement/                  # 状态管理静态 API
│   └── incremental/                      # 增量渲染静态 API
└── @internal/component/ets/
    ├── column.d.ts                       # 动态 API：组件+属性定义
    ├── text.d.ts
    ├── button.d.ts
    └── [... 140 个动态组件定义文件]
```

**统计概览（当前仓库快照）**:

组件 DSL 与 Modifier：

- `arkui/` 根目录文件: 172 个
- `arkui/component/*.static.d.ets`: 130 个
- `arkui/*Modifier.d.ts`: 76 个
- `arkui/*Modifier.static.d.ets`: 74 个
- `@internal/component/ets/*.d.ts`: 140 个

ArkUI 模块 API（`@ohos.arkui.*`，按需 `import`）：

- `@ohos.arkui.*.d.ts`（动态模块声明）: 27 个
- `@ohos.arkui.*.static.d.ets`（静态模块声明，含 `advanced/` 高级组件）: 61 个
- `@ohos.arkui.advanced.*.d.ets`（高级组件动态）: 36 个
- `@ohos.arkui.advanced.*.static.d.ets`（高级组件静态）: 34 个

相关通用 `@ohos.*` 模块（由 ArkUI 提供 NAPI 实现）：

- 代表模块均提供动态 + 静态双声明：`@ohos.router`、`@ohos.promptAction`、`@ohos.mediaquery`、`@ohos.animator`、`@ohos.font`、`@ohos.measure`、`@ohos.curves`、`@ohos.matrix4`
- ace_engine NAPI 实现根目录：`interfaces/napi/kits/`（31 个子目录），详见第 8.4 节

---

## 2. API 类型分类说明

ArkUI 对开发者暴露**两个正交维度**的 API，互为补充：

| 维度 | 范式 | 代表 API | 适用场景 | 主声明位置 |
|------|------|----------|----------|------------|
| **组件 API** | **声明式 DSL** | `Text(...)`、`Button(...)`、`Column(){...}` + `.attr()` 链 + `AttributeModifier<T>` | 页面 UI 描述、主流业务开发 | `@internal/component/ets/*.d.ts`（Dynamic）<br>`arkui/component/*.static.d.ets`（Static） |
| **Node API** | **命令式接口** | `FrameNode` / `BuilderNode` / `RenderNode` / `NodeContent` / `ComponentContent` | 自定义节点树、动态插拔、高性能列表项、跨场景复用 | `arkui/FrameNode.d.ts`、`arkui/BuilderNode.d.ts`、`arkui/RenderNode.d.ts`、`arkui/NodeContent.d.ts` |

两套维度通过 **Modifier 模式**（`AttributeModifier<T>` / `CommonModifier`）桥接：组件 API 用 `.attribute(modifier)` 接入 Modifier，Node API 用 `FrameNode` 同名机制接入同一份 Modifier 实例，最终都汇聚到 ace_engine 的 `Pattern` 实现。

后续小节按"组件 API → Node API → 配套类型 → 桥接模式"顺序展开：

- 2.1：组件 API（声明式 DSL）
- 2.2：Node API 核心节点类型（FrameNode / BuilderNode / RenderNode / NodeContent）
- 2.3：Node API 配套图形类型（Graphics）
- 2.4：组件 API ↔ Node API 共用的 Modifier 模式

### 2.1 组件 API（声明式 DSL）

组件 API 是 ArkUI 主流业务开发范式，以**全局可用的组件函数 + 链式属性 + 子组件块**形式描述 UI 树。

**调用形态：**

```ts
@Entry
@Component
struct Demo {
  @State count: number = 0
  build() {
    Column({ space: 8 }) {            // 容器组件 + Options
      Text(`Count: ${this.count}`)    // 叶子组件 + 文本参数
        .fontSize(20)                 // 链式属性
        .fontColor(Color.Blue)
      Button('+1')
        .onClick(() => { this.count++ })  // 事件回调
    }
    .width('100%')
    .padding(16)
  }
}
```

**两套声明并存：**

| 项 | Dynamic | Static |
|----|---------|--------|
| 组件声明 | `@internal/component/ets/<comp>.d.ts`（140 个） | `arkui/component/<comp>.static.d.ets`（130 个） |
| Modifier 声明 | `arkui/<Comp>Modifier.d.ts`（76 个） | `arkui/<Comp>Modifier.static.d.ets`（74 个） |
| 公共基座 | `@internal/component/ets/common.d.ts` | `arkui/component/common.static.d.ets` |
| 枚举/单位 | `@internal/component/ets/enums.d.ts` | `arkui/component/enums.static.d.ets`、`units.static.d.ets` |
| 调用方式 | 全局函数，无需 `import` | 同上 |
| 编译链路 | bridge 运行时分发 | koala 生成 → `components.abc` |

**典型组成（每个组件三段式）：**

- **构造函数**：`Component(options?: ComponentOptions): ComponentAttribute`
- **Attribute 接口**：`ComponentAttribute extends CommonMethod<ComponentAttribute>` — 暴露链式属性方法
- **Options 接口**：`ComponentOptions` — 初始化参数

**ace_engine 实现路径（双轨）：**

- Dynamic：`frameworks/bridge/declarative_frontend/jsview/js_<comp>.cpp` → `Pattern`
- Static：`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/<comp>.ets` → `Pattern`

> 完整组件清单按分类见第 3 节"组件 API 分类清单"；声明文件结构细节见第 4 节。

### 2.2 Node API 核心节点类型

#### FrameNode (框架节点)

**文件**: `FrameNode.d.ts`

**ace_engine 中的实现**:
- 文件：`OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp`
- 组件的 Pattern 对应一个组件的 FrameNode 实现

**设计理念**:
- FrameNode 是组件树的核心节点，代表一个完整的组件实例
- 每个组件都有对应的 FrameNode，它连接了 Pattern（业务逻辑）、Property（属性）、RenderNode（渲染）
- 支持命令式编程，可以动态创建、修改、删除组件树

**主要用途**:
- 动态创建和管理组件树（命令式 UI）
- 跨语言调用（从 C++/Cangjie 等操作 ArkUI 组件）
- 获取和修改组件布局属性
- 绑定事件监听器

**关键限制**:
- FrameNode 必须依附于有效的 UIContext
- 需要在 UI 线程上操作
- 子节点操作需要保证父子关系正确

**使用建议**:
- 优先使用声明式 API（@Builder）而非 FrameNode 命令式操作
- 仅在需要动态操作组件树时使用 FrameNode
- 使用完毕后调用 dispose() 释放资源

**核心特性**:
- FrameNode 是组件树的核心节点类型
- 支持动态创建和管理组件树
- 提供完整的树操作接口（添加、删除、移动子节点）
- 支持跨语言访问控制（CrossLanguageOptions）
- 提供 UI 状态管理和交互事件绑定

**API 定义位置**: `OpenHarmony/interface/sdk-js/api/arkui/FrameNode.d.ts`

**常用方法速查**:

| 分组 | 方法 | 说明 |
|------|------|------|
| 树操作 | `appendChild(node)` / `insertChildAfter(child, sibling)` / `removeChild(node)` / `clearChildren()` | 动态增删子节点 |
| 树查询 | `getChild(index)` / `getChildren()` | 按索引或全量获取子节点 |
| 布局 | `getLayoutProperty()` / `getLayoutConstraint()` / `getPositionToParent()` | 读取布局属性与位置 |
| 渲染 | `getRenderNode()` / `getRenderResult()` | 获取关联 RenderNode 与渲染结果 |
| 事件 | `on(event, callback)` / `off(event, callback?)` | 注册/移除事件监听 |
| 生命周期 | `dispose()` | 销毁节点，释放资源（调用后不可再用） |

#### BuilderNode (构建器节点)

**文件**: `BuilderNode.d.ts`

**ace_engine 中的实现**:
- 文件：`OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_view_builder_node.cpp`
- 通过 @Builder 方法创建组件树的 Bridge 层实现

**设计理念**:
- BuilderNode 是声明式 UI 的命令式封装，结合了 @Builder 的简洁性和 FrameNode 的灵活性
- 允许将 @Builder 方法包装为可复用的组件节点
- 支持参数化构建和更新，适合动态内容场景

**主要用途**:
- 将 @Builder 方法转换为 FrameNode 以便动态操作
- 实现组件复用和参数化
- 构建可嵌入其他组件的独立 UI 片段
- 支持组件的创建、更新、复用、回收生命周期管理

**关键限制**:
- 需要 UIContext 才能创建
- build() 只能调用一次，后续更新使用 update()
- 参数类型必须与 @Builder 定义匹配

**使用建议**:
- 适合需要复用 @Builder 并动态操作的场景
- 使用 reuse()/recycle() 实现组件池，提升性能
- API 12+ 优先使用 ReactiveBuilderNode 获得更好的状态同步

**核心特性**:
- 通过 @Builder 方法创建组件树
- 支持无状态 UI 构建
- 可嵌套在其他 FrameNode 中使用
- 提供参数更新和事件分发能力

**API 定义位置**:
- `OpenHarmony/interface/sdk-js/api/arkui/BuilderNode.d.ts`
- API 12+ 新增 `ReactiveBuilderNode` 同文件

**典型生命周期**:

```ts
const builderNode = new BuilderNode(uiContext)
builderNode.build(wrappedBuilder, args)   // 仅可调用一次
const frameNode = builderNode.getFrameNode()
builderNode.update(newArgs)               // 参数更新
builderNode.reuse(param)                  // 复用
builderNode.recycle()                     // 回收
builderNode.dispose()                     // 销毁
```

要点：`build()` 重复调用会报错；`reuse()/recycle()` 用于组件池；API 12+ 优先使用 `ReactiveBuilderNode.flushState()` 强制同步状态。

#### RenderNode (渲染节点)

**文件**: `RenderNode.d.ts`

**ace_engine 中的实现**:
- 文件：`OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/render/render_node.cpp`
- 负责组件的绘制和渲染属性管理

**核心特性**:
- 用于直接绘制和渲染控制
- 提供变换矩阵、透明度、阴影等渲染属性
- 支持自定义绘制回调
- 可独立于 FrameNode 使用

**API 定义位置**: `OpenHarmony/interface/sdk-js/api/arkui/RenderNode.d.ts`

#### NodeContent & ComponentContent

**文件**:
- `NodeContent.d.ts`
- `ComponentContent.d.ts`

**核心特性**:
- NodeContent: 节点内容的实体封装，可动态添加/删除 FrameNode
- ComponentContent: 组件内容的封装，通过 @Builder 创建，支持参数更新
- ReactiveComponentContent: API 22+ 新增，支持响应式状态管理

**API 定义位置**:
- `OpenHarmony/interface/sdk-js/api/arkui/NodeContent.d.ts`
- `OpenHarmony/interface/sdk-js/api/arkui/ComponentContent.d.ts`
- API 22+ 新增 `ReactiveComponentContent` 同 `ComponentContent.d.ts`

---

### 2.3 图形类型 (Graphics)

**API 定义位置**: `OpenHarmony/interface/sdk-js/api/arkui/Graphics.d.ts`

提供 Node API 配套的几何、变换、形状、度量、绘制上下文等类型，主要分四类：

| 分组 | 能力 | 代表类型 |
|------|------|----------|
| 基础几何 | 尺寸、位置、变换参数 | `Size` / `Offset` / `Position` / `Frame` / `Pivot` / `Scale` / `Translation` / `Rotation` / `Matrix4` / `Edges<T>` / `BorderRadiuses` |
| 形状与遮罩 | 矩形/圆/路径形状，节点裁剪和遮罩 | `Rect` / `RoundRect` / `Circle` / `CommandPath` / `ShapeMask` / `ShapeClip` |
| 长度与颜色度量 | 多单位长度、颜色构造与混合 | `LengthUnit`（PX/VP/FP/PERCENT/LPX）/ `LengthMetrics` / `ColorMetrics` |
| 绘制上下文 | `RenderNode.draw()` 回调参数 | `DrawContext`（含 `drawing.Canvas`） |

> 完整字段与方法签名详见 `Graphics.d.ts` 源文件。

---

### 2.4 Modifier 模式

#### CommonModifier (通用修饰器)

**文件**: `CommonModifier.d.ts`

```typescript
class CommonModifier extends CommonAttribute
  implements AttributeModifier<CommonAttribute> {
  applyNormalAttribute?(instance: CommonAttribute): void
}
```

#### 组件特定 Modifier

所有组件都有对应的 Modifier 类，命名模式: `[ComponentName]Modifier.d.ts`

**示例**:
```typescript
// TextModifier
class TextModifier extends TextAttribute
  implements AttributeModifier<TextAttribute> {
  applyNormalAttribute?(instance: TextAttribute): void
}

// ButtonModifier
class ButtonModifier extends ButtonAttribute
  implements AttributeModifier<ButtonAttribute> {
  applyNormalAttribute?(instance: ButtonAttribute): void
}
```

**Modifier 模式说明**:
- Modifier 类用于创建声明式配置对象，支持属性复用和动态修改
- 继承自对应的 Attribute 基类
- 实现 AttributeModifier<T> 接口
- 提供链式调用能力（通过返回 this）
- 可在运行时动态修改属性值，影响所有使用该 Modifier 的组件

---

## 3. 组件 API 分类清单

> 每个分类下分别给出 **Dynamic 视图** 与 **Static 视图**：
>
> - Dynamic 视图：组件声明（`@internal/component/ets/<comp>.d.ts`）+ Modifier 声明（`arkui/<Comp>Modifier.d.ts`）
> - Static 视图：组件声明（`arkui/component/<comp>.static.d.ets`）+ Modifier 声明（`arkui/<Comp>Modifier.static.d.ets`）
>
> ace_engine Pattern 与功能说明在两种范式间共享，列在分类后的"实现与知识库"小节中。

### 3.1 基础组件 (15 个)

**Dynamic 视图**

| 组件名 | 组件声明 | Modifier 声明 |
|--------|----------|---------------|
| Text | text.d.ts | TextModifier.d.ts |
| Image | image.d.ts | ImageModifier.d.ts |
| TextInput | text_input.d.ts | TextInputModifier.d.ts |
| TextArea | text_area.d.ts | TextAreaModifier.d.ts |
| Button | button.d.ts | ButtonModifier.d.ts |
| Toggle | toggle.d.ts | ToggleModifier.d.ts |
| Checkbox | checkbox.d.ts | CheckboxModifier.d.ts |
| Radio | radio.d.ts | RadioModifier.d.ts |
| Slider | slider.d.ts | SliderModifier.d.ts |
| Progress | progress.d.ts | ProgressModifier.d.ts |
| LoadingProgress | loading_progress.d.ts | LoadingProgressModifier.d.ts |
| Divider | divider.d.ts | DividerModifier.d.ts |
| Blank | blank.d.ts | BlankModifier.d.ts |
| Span | span.d.ts | SpanModifier.d.ts |
| ImageSpan | image_span.d.ts | ImageSpanModifier.d.ts |
| Counter | counter.d.ts | CounterModifier.d.ts |

**Static 视图**

| 组件名 | 组件声明 | Modifier 声明 |
|--------|----------|---------------|
| Text | text.static.d.ets | TextModifier.static.d.ets |
| Image | image.static.d.ets | ImageModifier.static.d.ets |
| TextInput | textInput.static.d.ets | TextInputModifier.static.d.ets |
| TextArea | textArea.static.d.ets | TextAreaModifier.static.d.ets |
| Button | button.static.d.ets | ButtonModifier.static.d.ets |
| Toggle | toggle.static.d.ets | ToggleModifier.static.d.ets |
| Checkbox | checkbox.static.d.ets | CheckboxModifier.static.d.ets |
| Radio | radio.static.d.ets | RadioModifier.static.d.ets |
| Slider | slider.static.d.ets | SliderModifier.static.d.ets |
| Progress | progress.static.d.ets | ProgressModifier.static.d.ets |
| LoadingProgress | loadingProgress.static.d.ets | LoadingProgressModifier.static.d.ets |
| Divider | divider.static.d.ets | DividerModifier.static.d.ets |
| Blank | blank.static.d.ets | BlankModifier.static.d.ets |
| Span | span.static.d.ets | SpanModifier.static.d.ets |
| ImageSpan | imageSpan.static.d.ets | ImageSpanModifier.static.d.ets |
| Counter | counter.static.d.ets | CounterModifier.static.d.ets |

**实现与知识库**

| 组件 | ace_engine Pattern | 知识库 | 功能 |
|------|--------------------|--------|------|
| Text | `pattern/text/text_pattern.cpp` | [Text](../pattern/text/Text_Knowledge_Base_CN.md) | 文本显示 |
| Image | `pattern/image/image_pattern.cpp` | [Image](../pattern/image/Image_Knowledge_Base.md) | 图片显示 |
| TextInput | `pattern/text_input/text_input_pattern.cpp` | - | 单行文本输入 |
| TextArea | `pattern/text_area/text_area_pattern.cpp` | - | 多行文本输入 |
| Button | `pattern/button/button_pattern.cpp` | - | 按钮 |
| Toggle | `pattern/toggle/toggle_pattern.cpp` | - | 开关 |
| Checkbox | `pattern/checkbox/checkbox_pattern.cpp` | - | 复选框 |
| Radio | `pattern/radio/radio_pattern.cpp` | - | 单选框 |
| Slider | `pattern/slider/slider_pattern.cpp` | - | 滑块 |
| Progress | `pattern/progress/progress_pattern.cpp` | - | 进度条 |
| LoadingProgress | `pattern/loading_progress/loading_progress_pattern.cpp` | - | 加载进度 |
| Divider | `pattern/divider/divider_pattern.cpp` | - | 分割线 |
| Blank | `pattern/blank/blank_pattern.cpp` | - | 空白占位 |
| Span | `pattern/text/span_node.cpp` | - | 文本片段 |
| ImageSpan | `pattern/text/span/image_span_view.cpp` | - | 图片片段 |
| Counter | `pattern/counter/counter_pattern.cpp` | [Counter](../pattern/counter/Counter_Knowledge_Base.md) | 计数器 |

> Pattern 路径前缀为 `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/`。

### 3.2 容器组件 (27 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Column | column.d.ts | ColumnModifier.d.ts |
| Row | row.d.ts | RowModifier.d.ts |
| Stack | stack.d.ts | StackModifier.d.ts |
| Flex | flex.d.ts | - |
| Grid | grid.d.ts | GridModifier.d.ts |
| GridRow | grid_row.d.ts | GridRowModifier.d.ts |
| GridCol | grid_col.d.ts | GridColModifier.d.ts |
| GridItem | gridItem.d.ts | GridItemModifier.d.ts |
| List | list.d.ts | ListModifier.d.ts |
| ListItem | list_item.d.ts | ListItemModifier.d.ts |
| ListItemGroup | list_item_group.d.ts | ListItemGroupModifier.d.ts |
| Scroll | scroll.d.ts | ScrollModifier.d.ts |
| Swiper | swiper.d.ts | SwiperModifier.d.ts |
| Tabs | tabs.d.ts | TabsModifier.d.ts |
| TabContent | tab_content.d.ts | - |
| Navigator | navigator.d.ts | NavigatorModifier.d.ts |
| NavRouter | nav_router.d.ts | NavRouterModifier.d.ts |
| Navigation | navigation.d.ts | NavigationModifier.d.ts |
| NavDestination | nav_destination.d.ts | NavDestinationModifier.d.ts |
| SideBarContainer | sidebar.d.ts | SideBarContainerModifier.d.ts |
| Refresh | refresh.d.ts | RefreshModifier.d.ts |
| WaterFlow | water_flow.d.ts | WaterFlowModifier.d.ts |
| FlowItem | flow_item.d.ts | - |
| RelativeContainer | relative_container.d.ts | RelativeContainerModifier.static.d.ets 对应 |
| ColumnSplit | column_split.d.ts | ColumnSplitModifier.d.ts |
| RowSplit | row_split.d.ts | RowSplitModifier.d.ts |
| FolderStack | folder_stack.d.ts | FolderStackModifier.d.ts |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Column | column.static.d.ets | ColumnModifier.static.d.ets |
| Row | row.static.d.ets | RowModifier.static.d.ets |
| Stack | stack.static.d.ets | StackModifier.static.d.ets |
| Flex | flex.static.d.ets | FlexModifier.static.d.ets |
| Grid | grid.static.d.ets | GridModifier.static.d.ets |
| GridRow | gridRow.static.d.ets | GridRowModifier.static.d.ets |
| GridCol | gridCol.static.d.ets | GridColModifier.static.d.ets |
| GridItem | gridItem.static.d.ets | GridItemModifier.static.d.ets |
| List | list.static.d.ets | ListModifier.static.d.ets |
| ListItem | listItem.static.d.ets | ListItemModifier.static.d.ets |
| ListItemGroup | listItemGroup.static.d.ets | ListItemGroupModifier.static.d.ets |
| Scroll | scroll.static.d.ets | ScrollModifier.static.d.ets |
| Swiper | swiper.static.d.ets | SwiperModifier.static.d.ets |
| Tabs | tabs.static.d.ets | TabsModifier.static.d.ets |
| TabContent | tabContent.static.d.ets | - |
| Navigation | navigation.static.d.ets | NavigationModifier.static.d.ets |
| NavDestination | navDestination.static.d.ets | NavDestinationModifier.static.d.ets |
| SideBarContainer | sidebar.static.d.ets | SideBarContainerModifier.static.d.ets |
| Refresh | refresh.static.d.ets | RefreshModifier.static.d.ets |
| WaterFlow | waterFlow.static.d.ets | WaterFlowModifier.static.d.ets |
| RelativeContainer | relativeContainer.static.d.ets | RelativeContainerModifier.static.d.ets |
| ColumnSplit | columnSplit.static.d.ets | ColumnSplitModifier.static.d.ets |
| RowSplit | rowSplit.static.d.ets | RowSplitModifier.static.d.ets |
| FolderStack | folderStack.static.d.ets | FolderStackModifier.static.d.ets |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| Column | `pattern/linear_layout/linear_layout_pattern.cpp` | - | 纵向布局 |
| Row | `pattern/linear_layout/linear_layout_pattern.cpp` | - | 横向布局 |
| Stack | `pattern/stack/stack_pattern.cpp` | - | 堆叠布局 |
| Flex | `pattern/flex/flex_layout_pattern.cpp` | - | 弹性布局 |
| Grid | `pattern/grid/grid_pattern.cpp` | - | 网格布局 |
| GridRow | `pattern/grid_row/grid_row_pattern.cpp` | - | 栅格行 |
| GridCol | `pattern/grid_col/grid_col_pattern.cpp` | - | 栅格列 |
| GridItem | `pattern/grid_item/grid_item_pattern.cpp` | - | 栅格子项 |
| List | `pattern/list/list_pattern.cpp` | - | 列表 |
| ListItem | `pattern/list/list_item_pattern.cpp` | - | 列表项 |
| ListItemGroup | `pattern/list/list_item_group_pattern.cpp` | - | 列表分组 |
| Scroll | `pattern/scroll/scroll_pattern.cpp` | [Scroll](../pattern/scroll/Scroll_Knowledge_Base.md) | 滚动容器 |
| Swiper | `pattern/swiper/swiper_pattern.cpp` | - | 轮播 |
| Tabs | `pattern/tabs/tabs_pattern.cpp` | - | 标签页 |
| TabContent | `pattern/tabs/tab_content_pattern.cpp` | - | 标签页内容 |
| Navigator | (legacy `components/navigator/`) | - | 导航跳转 |
| NavRouter | `pattern/navrouter/nav_router_pattern.cpp` | - | 路由导航 |
| Navigation | `pattern/navigation/navigation_pattern.cpp` | - | 导航栏 |
| NavDestination | `pattern/navigation/nav_destination_pattern.cpp` | - | 导航目标页 |
| SideBarContainer | `pattern/side_bar/side_bar_container_pattern.cpp` | - | 侧边栏 |
| Refresh | `pattern/refresh/refresh_pattern.cpp` | [Refresh](../pattern/refresh/Refresh_Knowledge_Base.md) | 下拉刷新 |
| WaterFlow | `pattern/waterflow/water_flow_pattern.cpp` | [WaterFlow](../pattern/waterflow/WaterFlow_Knowledge_Base.md) | 瀑布流 |
| FlowItem | `pattern/waterflow/water_flow_item_pattern.cpp` | - | 瀑布流子项 |
| RelativeContainer | `pattern/relative_container/relative_container_pattern.cpp` | - | 相对布局 |
| ColumnSplit | `pattern/linear_split/linear_split_pattern.cpp` | - | 纵向分割 |
| RowSplit | `pattern/linear_split/linear_split_pattern.cpp` | - | 横向分割 |
| FolderStack | `pattern/folder_stack/folder_stack_pattern.cpp` | - | 文件夹堆叠 |

### 3.3 选择器组件 (9 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Select | select.d.ts | SelectModifier.d.ts |
| DatePicker | date_picker.d.ts | DatePickerModifier.d.ts |
| TimePicker | time_picker.d.ts | TimePickerModifier.d.ts |
| TextPicker | text_picker.d.ts | TextPickerModifier.d.ts |
| CalendarPicker | calendar_picker.d.ts | CalendarPickerModifier.d.ts |
| CheckboxGroup | checkboxgroup.d.ts | CheckboxGroupModifier.d.ts |
| Rating | rating.d.ts | RatingModifier.d.ts |
| UIPickerComponent | ui_picker_component.d.ts | UIPickerComponentModifier.d.ts |
| ContainerPicker | - | - |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Select | select.static.d.ets | SelectModifier.static.d.ets |
| DatePicker | datePicker.static.d.ets | DatePickerModifier.static.d.ets |
| TimePicker | timePicker.static.d.ets | TimePickerModifier.static.d.ets |
| TextPicker | textPicker.static.d.ets | TextPickerModifier.static.d.ets |
| CalendarPicker | calendarPicker.static.d.ets | CalendarPickerModifier.static.d.ets |
| CheckboxGroup | checkboxgroup.static.d.ets | CheckboxGroupModifier.static.d.ets |
| Rating | rating.static.d.ets | RatingModifier.static.d.ets |
| UIPickerComponent | uiPickerComponent.static.d.ets | UIPickerComponentModifier.static.d.ets |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| Select | `pattern/select/select_pattern.cpp` | - | 下拉选择 |
| DatePicker | `pattern/picker/date_picker_pattern.cpp` | [DatePicker](../pattern/picker/Date_Picker_Knowledge_Base.md) | 日期选择器 |
| TimePicker | `pattern/time_picker/time_picker_pattern.cpp` | [TimePicker](../pattern/time_picker/Time_Picker_Knowledge_Base.md) | 时间选择器 |
| TextPicker | `pattern/text_picker/text_picker_pattern.cpp` | [TextPicker](../pattern/text_picker/Text_Picker_Knowledge_Base.md) | 文本选择器 |
| CalendarPicker | `pattern/picker/calendar_picker_pattern.cpp` | [CalendarPicker](../pattern/calendar_picker/Calendar_Picker_Knowledge_Base.md) | 日历选择器 |
| CheckboxGroup | `pattern/checkboxgroup/checkboxgroup_pattern.cpp` | - | 复选框组 |
| Rating | `pattern/rating/rating_pattern.cpp` | - | 评分 |
| UIPickerComponent | `pattern/picker/picker_pattern.cpp` | - | UI 选择器 |

### 3.4 形状组件 (7 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Rect | rect.d.ts | RectModifier.d.ts |
| Circle | circle.d.ts | - |
| Ellipse | ellipse.d.ts | - |
| Path | path.d.ts | PathModifier.d.ts |
| Line | line.d.ts | LineModifier.d.ts |
| Polyline | polyline.d.ts | PolylineModifier.d.ts |
| Polygon | polygon.d.ts | PolygonModifier.d.ts |
| Shape | shape.d.ts | ShapeModifier.d.ts |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Rect | rect.static.d.ets | RectModifier.static.d.ets |
| Circle | circle.static.d.ets | - |
| Ellipse | ellipse.static.d.ets | - |
| Path | path.static.d.ets | PathModifier.static.d.ets |
| Line | line.static.d.ets | LineModifier.static.d.ets |
| Polyline | polyline.static.d.ets | PolylineModifier.static.d.ets |
| Polygon | polygon.static.d.ets | PolygonModifier.static.d.ets |
| Shape | shape.static.d.ets | ShapeModifier.static.d.ets |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| Rect | `pattern/shape/rect_pattern.cpp` | - | 矩形 |
| Circle | `pattern/shape/circle_pattern.cpp` | - | 圆形 |
| Ellipse | `pattern/shape/ellipse_pattern.cpp` | - | 椭圆 |
| Path | `pattern/shape/path_pattern.cpp` | - | 路径 |
| Line | `pattern/shape/line_pattern.cpp` | - | 线 |
| Polyline | `pattern/shape/polyline_pattern.cpp` | - | 折线 |
| Polygon | `pattern/shape/polygon_pattern.cpp` | - | 多边形 |
| Shape | `pattern/shape/shape_pattern.cpp` | - | 形状容器 |

### 3.5 媒体组件 (4 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Video | video.d.ts | VideoModifier.d.ts |
| ImageAnimator | image_animator.d.ts | ImageAnimatorModifier.d.ts |
| Canvas | canvas.d.ts | - |
| XComponent | xcomponent.d.ts | - |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Video | video.static.d.ets | VideoModifier.static.d.ets |
| ImageAnimator | imageAnimator.static.d.ets | ImageAnimatorModifier.static.d.ets |
| Canvas | canvas.static.d.ets | - |
| XComponent | xcomponent.static.d.ets | - |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| Video | `pattern/video/video_pattern.cpp` | - | 视频 |
| ImageAnimator | `pattern/image_animator/image_animator_pattern.cpp` | [ImageAnimator](../pattern/image_animator/Image_Animator_Knowledge_Base.md) | 帧动画 |
| Canvas | `pattern/canvas/canvas_pattern.cpp` | - | 画布 |
| XComponent | `pattern/xcomponent/xcomponent_pattern.cpp` | - | 原生组件容器 |

### 3.6 数据展示组件 (7 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| TextClock | text_clock.d.ts | TextClockModifier.d.ts |
| TextTimer | text_timer.d.ts | TextTimerModifier.d.ts |
| DataPanel | data_panel.d.ts | DataPanelModifier.d.ts |
| Gauge | gauge.d.ts | GaugeModifier.d.ts |
| QRCode | qrcode.d.ts | QRCodeModifier.d.ts |
| Badge | badge.d.ts | - |
| AlphabetIndexer | alphabet_indexer.d.ts | AlphabetIndexerModifier.d.ts |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| TextClock | textClock.static.d.ets | TextClockModifier.static.d.ets |
| TextTimer | textTimer.static.d.ets | TextTimerModifier.static.d.ets |
| DataPanel | dataPanel.static.d.ets | DataPanelModifier.static.d.ets |
| Gauge | gauge.static.d.ets | GaugeModifier.static.d.ets |
| QRCode | qrcode.static.d.ets | QRCodeModifier.static.d.ets |
| Badge | badge.static.d.ets | - |
| AlphabetIndexer | alphabetIndexer.static.d.ets | AlphabetIndexerModifier.static.d.ets |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| TextClock | `pattern/text_clock/text_clock_pattern.cpp` | [TextClock](../pattern/text_clock/TextClock_Knowledge_Base_CN.md) | 文本时钟 |
| TextTimer | `pattern/text_timer/text_timer_pattern.cpp` | [TextTimer](../pattern/texttimer/TextTimer_Knowledge_Base_CN.md) | 文本计时器 |
| DataPanel | `pattern/data_panel/data_panel_pattern.cpp` | - | 数据面板 |
| Gauge | `pattern/gauge/gauge_pattern.cpp` | [Gauge](../pattern/gauge/Gauge_Knowledge_Base.md) | 仪表盘 |
| QRCode | `pattern/qrcode/qrcode_pattern.cpp` | - | 二维码 |
| Badge | `pattern/badge/badge_pattern.cpp` | [Badge](../pattern/badge/Badge_Knowledge_Base_CN.md) | 徽章 |
| AlphabetIndexer | `pattern/indexer/indexer_pattern.cpp` | - | 字母索引 |

### 3.7 富文本组件 (4 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| RichEditor | rich_editor.d.ts | RichEditorModifier.d.ts |
| ContainerSpan | container_span.d.ts | ContainerSpanModifier.d.ts |
| StyledString | styled_string.d.ts | - |
| Hyperlink | hyperlink.d.ts | HyperlinkModifier.d.ts |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| RichEditor | richEditor.static.d.ets | RichEditorModifier.static.d.ets |
| ContainerSpan | containerSpan.static.d.ets | ContainerSpanModifier.static.d.ets |
| StyledString | styledString.static.d.ets | - |
| Hyperlink | hyperlink.static.d.ets | HyperlinkModifier.static.d.ets |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| RichEditor | `pattern/rich_editor/rich_editor_pattern.cpp` | - | 富文本编辑器 |
| ContainerSpan | `pattern/text/span_node.cpp` | - | 容器片段 |
| StyledString | `pattern/text/styled_string/styled_string.cpp` | - | 样式字符串 |
| Hyperlink | `pattern/hyperlink/hyperlink_pattern.cpp` | - | 超链接 |

### 3.8 弹窗和菜单组件 (10 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| AlertDialog | alert_dialog.d.ts | - |
| ActionSheet | action_sheet.d.ts | - |
| Menu | menu.d.ts | MenuModifier.d.ts |
| MenuItem | menu_item.d.ts | MenuItemModifier.d.ts |
| MenuItemGroup | menu_item_group.d.ts | - |
| CustomDialogController | custom_dialog_controller.d.ts | - |
| Panel | panel.d.ts | PanelModifier.d.ts |
| ContextMenu | context_menu.d.ts | - |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| AlertDialog | alertDialog.static.d.ets | - |
| ActionSheet | actionSheet.static.d.ets | - |
| Menu | menu.static.d.ets | MenuModifier.static.d.ets |
| MenuItem | menuItem.static.d.ets | MenuItemModifier.static.d.ets |
| MenuItemGroup | menuItemGroup.static.d.ets | - |
| CustomDialogController | customDialogController.static.d.ets | - |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| AlertDialog | `pattern/dialog/alert_dialog_pattern.cpp` | - | 警告对话框 |
| ActionSheet | `pattern/dialog/action_sheet_pattern.cpp` | - | 操作列表 |
| Menu | `pattern/menu/menu_pattern.cpp` | [Menu](../pattern/menu/Menu_Knowledge_Base.md) | 菜单 |
| MenuItem | `pattern/menu/menu_item/menu_item_pattern.cpp` | - | 菜单项 |
| MenuItemGroup | `pattern/menu/menu_item_group/menu_item_group_pattern.cpp` | - | 菜单分组 |
| CustomDialogController | `pattern/dialog/dialog_pattern.cpp` | - | 自定义对话框控制器 |
| Panel | `pattern/panel/sliding_panel_pattern.cpp` | - | 半屏弹窗 |
| ContextMenu | `pattern/menu/menu_pattern.cpp` | - | 上下文菜单 |

### 3.9 高级组件 (19 个)

**Dynamic 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Web | web.d.ts | - |
| FormComponent | form_component.d.ts | FormComponentModifier.d.ts |
| PatternLock | pattern_lock.d.ts | PatternLockModifier.d.ts |
| Stepper | stepper.d.ts | StepperModifier.d.ts |
| StepperItem | stepper_item.d.ts | StepperItemModifier.d.ts |
| Search | search.d.ts | SearchModifier.d.ts |
| ContentSlot | content_slot.d.ts | - |
| RemoteWindow | remote_window.d.ts | - |
| UIExtensionComponent | ui_extension_component.d.ts | - |
| EmbeddedComponent | embedded_component.d.ts | - |
| EffectComponent | effect_component.d.ts | - |
| Component3D | component3d.d.ts | - |
| SecurityComponent | security_component.d.ts | - |
| SymbolGlyph | symbolglyph.d.ts | SymbolGlyphModifier.d.ts |
| SymbolSpan | symbol_span.d.ts | SymbolSpanModifier.d.ts |
| Marquee | marquee.d.ts | MarqueeModifier.d.ts |
| LazyGridLayout | lazy_grid_layout.d.ts | - |
| Particle | particle.d.ts | ParticleModifier.d.ts |
| PluginComponent | plugin_component.d.ts | - |

**Static 视图**

| 组件 | 组件声明 | Modifier 声明 |
|------|----------|---------------|
| Web | web.static.d.ets | - |
| FormComponent | formComponent.static.d.ets | FormComponentModifier.static.d.ets |
| PatternLock | patternLock.static.d.ets | PatternLockModifier.static.d.ets |
| Search | search.static.d.ets | SearchModifier.static.d.ets |
| ContentSlot | contentSlot.static.d.ets | - |
| RemoteWindow | remoteWindow.static.d.ets | - |
| UIExtensionComponent | uiExtensionComponent.static.d.ets | - |
| EmbeddedComponent | embeddedComponent.static.d.ets | - |
| EffectComponent | effectComponent.static.d.ets | - |
| Component3D | component3d.static.d.ets | - |
| SecurityComponent | securityComponent.static.d.ets | - |
| SymbolGlyph | symbolglyph.static.d.ets | SymbolGlyphModifier.static.d.ets |
| SymbolSpan | symbolSpan.static.d.ets | SymbolSpanModifier.static.d.ets |
| Marquee | marquee.static.d.ets | MarqueeModifier.static.d.ets |
| LazyGridLayout | lazyGridLayout.static.d.ets | - |
| Particle | particle.static.d.ets | ParticleModifier.static.d.ets |
| PluginComponent | pluginComponent.static.d.ets | - |
| UnionEffectContainer | unionEffectContainer.static.d.ets | - |
| MediaCachedImage | mediaCachedImage.static.d.ets | - |

**实现与知识库**

| 组件 | Pattern | 知识库 | 功能 |
|------|---------|--------|------|
| Web | `pattern/web/web_pattern.cpp` | - | Web 浏览器 |
| FormComponent | `pattern/form/form_pattern.cpp` | - | 卡片组件 |
| PatternLock | `pattern/patternlock/patternlock_pattern.cpp` | - | 图案锁 |
| Stepper | `pattern/stepper/stepper_pattern.cpp` | - | 步骤条 |
| StepperItem | `pattern/stepper/stepper_item_pattern.cpp` | - | 步骤项 |
| Search | `pattern/search/search_pattern.cpp` | [Search](../pattern/search/Search_Knowledge_Base_CN.md) | 搜索框 |
| ContentSlot | `pattern/content_slot/content_slot_pattern.cpp` | - | 内容插槽 |
| RemoteWindow | `pattern/remote_window/remote_window_pattern.cpp` | - | 远程窗口 |
| UIExtensionComponent | `pattern/ui_extension/ui_extension_pattern.cpp` | - | UI 扩展 |
| EmbeddedComponent | `pattern/ui_extension/embedded_component_pattern.cpp` | - | 嵌入式组件 |
| EffectComponent | `pattern/effect_component/effect_component_pattern.cpp` | - | 效果组件 |
| Component3D | `pattern/model/model_pattern.cpp` | - | 3D 组件 |
| SecurityComponent | `pattern/security_component/security_component_pattern.cpp` | - | 安全组件 |
| SymbolGlyph | `pattern/symbol/symbol_pattern.cpp` | - | 符号图标 |
| SymbolSpan | `pattern/text/span_node.cpp` | - | 符号片段 |
| Marquee | `pattern/marquee/marquee_pattern.cpp` | [Marquee](../pattern/marquee/Marquee_Knowledge_Base.md) | 跑马灯 |
| LazyGridLayout | `pattern/grid/grid_pattern.cpp` | [LazyGrid](../pattern/lazy_layout/LazyGrid_Knowledge_Base.md) | 懒加载网格 |
| Particle | `pattern/particle/particle_pattern.cpp` | - | 粒子效果 |
| PluginComponent | `pattern/plugin/plugin_pattern.cpp` | - | 插件组件 |

### 3.10 工具和辅助类 (24 个)

> 此类条目大多是声明式语法基座或通用类型/容器，无需 Modifier；下表同时给出 Dynamic 与 Static 声明文件位置（`-` 表示未提供）。

| 名称 | Dynamic 声明 | Static 声明 | 功能说明 |
|------|--------------|-------------|----------|
| Common | common.d.ts | common.static.d.ets | 通用属性和方法 |
| Units | units.d.ts | units.static.d.ets | 单位类型定义 |
| Enums | enums.d.ts | enums.static.d.ets | 枚举类型定义 |
| Resources | - | resources.static.d.ets | 资源管理 |
| Gesture | gesture.d.ts | gesture.static.d.ets | 手势识别 |
| Focus | focus.d.ts | focus.static.d.ets | 焦点控制 |
| Animation | - | animation.static.d.ets | 动画 |
| Screen | screen.d.ts | screen.static.d.ets | 屏幕信息 |
| CustomComponent | - | customComponent.static.d.ets | 自定义组件基类 |
| ExtendableComponent | - | extendableComponent.static.d.ets | 可扩展组件 |
| Builder | - | builder.static.d.ets | 构建器函数 |
| ForEach | for_each.d.ts | forEach.static.d.ets | 循环渲染 |
| If | - | if.static.d.ets | 条件渲染 |
| LazyForEach | lazy_for_each.d.ts | lazyForEach.static.d.ets | 懒加载循环渲染 |
| Repeat | repeat.d.ts | repeat.static.d.ets | 重复渲染 |
| WithTheme | with_theme.d.ts | withTheme.static.d.ets | 主题切换 |
| ScrollBar | scroll_bar.d.ts | scrollBar.static.d.ets | 滚动条 |
| IndicatorComponent | indicatorcomponent.d.ts | indicatorcomponent.static.d.ets | 指示器 |
| RootScene | root_scene.d.ts | rootScene.static.d.ets | 根场景 |
| WindowScene | window_scene.d.ts | windowScene.static.d.ets | 窗口场景 |
| FormLink | form_link.d.ts | - | 卡片链接 |
| SaveButton | save_button.d.ts | saveButton.static.d.ets | 保存按钮 |
| PasteButton | paste_button.d.ts | pasteButton.static.d.ets | 粘贴按钮 |
| Inspector | inspector.d.ts | inspector.static.d.ets | 检查器 |
| NodeContainer | node_container.d.ts | nodeContainer.static.d.ets | 节点容器 |
| TextCommon | text_common.d.ts | textCommon.static.d.ets | 文本通用类型 |
| Matrix2D | matrix2d.d.ts | matrix2d.static.d.ets | 2D 变换矩阵 |
| Toolbar | toolbar.d.ts | toolbar.static.d.ets | 工具栏 |
| Interop | - | interop.static.d.ets | 互操作 |
| PageTransition | page_transition.d.ts | pageTransition.static.d.ets | 页面转场 |
| MenuItemGroup | menu_item_group.d.ts | menuItemGroup.static.d.ets | 菜单分组 |

---

## 4. 组件声明文件结构规范

本章统一说明 Dynamic 与 Static 两种范式下组件声明文件（`*.d.ts` / `*.static.d.ets`）的共同结构与差异，并给出通用基座文件（common / enums / units / gesture / builder）的入口。

> 路径前缀均省略 `OpenHarmony/interface/sdk-js/api/`。`-` 表示该范式无对应概念。

### 4.1 三段式约定

两种范式都采用「Interface / Attribute / Options」三段式描述一个组件，只是命名和导出方式不同：

| 段 | 角色 | Dynamic（`@internal/component/ets/<comp>.d.ts`） | Static（`arkui/component/<comp>.static.d.ets`） |
|---|---|---|---|
| 构造入口 | 组件可被全局调用 | `interface {Comp}Interface { (...): {Comp}Attribute; }` | `export declare function {Comp}(...): {Comp}Attribute;`（带 `@ComponentBuilder`） |
| 属性链 | 链式样式/事件方法 | `interface {Comp}Attribute extends CommonMethod<...>` | `export declare interface {Comp}Attribute extends CommonMethod` |
| 参数选项 | 构造参数对象 | `interface {Comp}Options { ... }` | `export declare interface {Comp}Options { ... }` |
| 模式配置 | Modifier/自定义渲染 | `-`（少数组件有） | `export declare interface {Comp}Configuration extends CommonConfiguration<T>` |

**Dynamic 示例**（`text.d.ts`）：
```ts
interface TextInterface {
  (content?: string | Resource, value?: TextOptions): TextAttribute;
}
interface TextAttribute extends CommonMethod<TextAttribute> {
  fontSize(value: number | string | Resource): TextAttribute;
  // ...
}
declare const Text: TextInterface;   // 暴露为全局
```

**Static 示例**（`text.static.d.ets`）：
```ts
@ComponentBuilder
export declare function Text(
  content?: string | Resource,
  value?: TextOptions,
  content_?: CustomBuilder            // 尾随闭包
): TextAttribute;

export declare interface TextAttribute extends CommonMethod {
  default fontSize(value: double | string | Resource | undefined): this;
}
```

**关键差异**：
- Dynamic 把组件名注册为 `declare const`/`interface`，Static 用 `export declare function` + `@ComponentBuilder` 装饰器；
- Static 的 Attribute 方法返回 `this`、参数允许 `undefined`，与静态类型系统兼容；
- Static 通过 `Configuration + ContentModifier` 提供命令式渲染入口，Dynamic 对应的是 `arkui/*Modifier.d.ts` 系列附加文件。

### 4.2 @ComponentBuilder 与尾随闭包（Static 专有）

`@ComponentBuilder` 标记 Static 组件构造函数，告诉编译器最后一个 `CustomBuilder` 参数可写成 DSL 闭包：

```ts
export type CustomBuilder = @Builder (() => void);

@ComponentBuilder
export declare function Column(
  space?: Length | Resource,
  value?: ColumnOptions,
  content_?: CustomBuilder            // 尾随闭包参数
): ColumnAttribute;

// 调用
Column({ space: 10 }) {
  Text('Hello')
  Text('World')
}
```

Dynamic 范式没有该装饰器，子组件由 `declarative_frontend` 在 transformer 阶段插桩，写法上对开发者是相同的 `Column() { ... }`。

### 4.3 通用基座 `CommonMethod`

`CommonMethod` 是所有 `{Comp}Attribute` 的父接口，定义全部组件共享的样式 / 布局 / 事件 / 动画方法。

**API 定义位置**：
- Dynamic：`@internal/component/ets/common.d.ts`（38,611 行）
- Static：`arkui/component/common.static.d.ets`（14,174 行）

主要分类（两个范式方法集基本一致，Static 在签名上更严格）：

| 分类 | 方法数（量级） | 代表方法 |
|---|---|---|
| 尺寸 | 15 | `width` / `height` / `size` / `constraintSize` |
| 位置 | 8 | `position` / `offset` / `markAnchor` / `pivot` |
| 布局 | 12 | `padding` / `margin` / `layoutWeight` / `align` |
| 背景与边框 | 25 | `backgroundColor` / `border*` / `borderRadius` |
| 显示与透明度 | 8 | `visibility` / `opacity` / `alpha` |
| 事件 | 20+ | `onClick` / `onTouch` / `onHover` / `onAreaChange` |
| 动画与转场 | 10 | `animation` / `transition` / `animateTo` |
| 其他 | 30+ | `id` / `key` / `enabled` / `focusable` / `accessibility*` |
| **合计** | **100+** | 所有组件公共属性方法 |

Static 的 `common.static.d.ets` 同时导出全局函数 `postCardAction / $r / $rawfile / animateToImmediately / makeBindable / $$ / applyStyles`，Dynamic 范式下这些由前端运行时注入而非声明文件导出。

### 4.4 通用枚举 / 单位 / 手势 / 构建器

| 文件主题 | Dynamic 路径 | Static 路径 | 主要内容 |
|---|---|---|---|
| 枚举（对齐/布局/字体/颜色/动画…） | `@internal/component/ets/enums.d.ts`（12,599 行） | `arkui/component/enums.static.d.ets`（4,329 行） | `Alignment` / `Axis` / `FontWeight` / `Color` / `Curve` / `TouchType` 等 200+ 枚举 |
| 单位类型（长度/颜色/盒模型） | `@internal/component/ets/units.d.ts`（4,117 行） | `arkui/component/units.static.d.ets`（1,609 行） | `Length` / `ResourceColor` / `SizeOptions` / `Padding` / `Margin` / `BorderRadiuses` |
| 手势识别 | `@internal/component/ets/gesture.d.ts`（5,127 行） | `arkui/component/gesture.static.d.ets`（2,318 行） | `GestureType` / `TapGesture` / `LongPressGesture` / `PanGesture` / `GestureRecognizer` |
| 构建器 | 由 `common.d.ts` / 状态管理装饰器共同提供 | `arkui/component/builder.static.d.ets`（146 行） | `CustomBuilder` / `WrappedBuilder<T>` / `wrapBuilder` |

要点：
- Dynamic 行数远大于 Static，源于 Dynamic 文件累积多版本 `@since` JSDoc 注释；实际声明数量相近。
- 新组件优先在两套文件中保持枚举/单位一致，并通过 `common` 复用样式 API，不应在组件文件里重复定义。
- 若 Static 缺少某个 Dynamic 已有的枚举（或反之），需在第 3 章对应组件行标注 `-`，并同步更新本表。

### 4.5 文档注释与版本标签

两个范式的 JSDoc 标签约定相同（`@param` / `@returns` / `@default` / `@syscap` / `@since` / `@systemapi` / `@crossplatform` / `@form` / `@atomicservice` 等），区别只在 `@since` 后缀：

- Dynamic：`@since 11 dynamic`
- Static：`@since 23 static`

跨范式追踪一个 API 时，以 `@since` 后缀区分；缺失后缀的为历史遗留写法，应在新增 API 时补齐。

---
---

## 5. 增量渲染 API

**文件**: `incremental/runtime/state.static.d.ets`

### 5.1 增量状态管理

```typescript
// 可读状态接口
interface ReadableState<T> {
  readonly value: T
}

// 增量作用域接口
interface IncrementalScope<Value> {
  unchanged: boolean      // 状态是否改变
  cached: Value          // 缓存的值
  recache(newValue?: Value): Value
  param<T>(index: int, value: T): ReadableState<T>
}

// 状态上下文
interface StateContext {
  scope<T>(id: int, paramCount: int): IncrementalScope<T>
}

// 类型别名
type __memo_context_type = StateContext
type __memo_id_type = int
```

**用途**:
- 提供增量渲染的状态追踪能力
- 支持状态缓存和按需更新
- 用于优化性能，避免不必要的重新渲染

---

## 6. 状态管理 API

### 6.1 状态装饰器

**文件**: `stateManagement/decorator.static.d.ets`

```typescript
// 状态装饰器
@State          // 组件内部状态
@Prop           // 父组件传递的只读属性
@PropRef        // 可变的父组件属性引用
@Link           // 双向数据绑定
@Observed       // 观察类对象
@Track          // 追踪对象属性变化
@ObjectLink     // 嵌套对象的双向绑定
@StorageProp    // AppStorage 只读属性
@StoragePropRef // AppStorage 可变属性引用
@StorageLink    // AppStorage 双向绑定
@Provide        // 提供数据给后代组件
@Consume        // 消费祖先组件提供的数据
@Watch          // 监听状态变化
@LocalStorageProp    // LocalStorage 只读属性
@LocalStorageLink    // LocalStorage 双向绑定
```

### 6.2 存储管理

**文件目录**: `stateManagement/storage/`

| 文件 | 功能 |
|------|------|
| `appStorage.static.d.ets` | 应用级状态存储 |
| `appStorageV2.static.d.ets` | 应用级状态存储 V2 |
| `localStorage.static.d.ets` | 页面级状态存储 |
| `persistentStorage.static.d.ets` | 持久化存储 |
| `environment.static.d.ets` | 环境变量 |
| `storageProperty.static.d.ets` | 存储属性定义 |

**示例**:
```typescript
// AppStorage
AppStorage.setOrCreate('count', 0)
let count = AppStorage.get('count')

// LocalStorage
let storage = new LocalStorage()
storage.setOrCreate('pageData', { key: 'value' })

// PersistentStorage
PersistentStorage.persistProp('userSettings', 'defaultSettings')
```

### 6.3 记忆函数

**文件**: `stateManagement/remember.static.d.ets`

```typescript
// 记忆函数
@Remember        // 缓存计算结果
```

---

## 7. 关键概念说明

### 7.1 Modifier 模式

**定义**:
Modifier 是一种属性修改器模式，用于链式设置组件属性。

**实现方式**:
```typescript
// 每个 Modifier 类都实现 AttributeModifier<T> 接口
class CommonModifier extends CommonAttribute
  implements AttributeModifier<CommonAttribute> {
  applyNormalAttribute?(instance: CommonAttribute): void
}

// 使用时返回 this，支持链式调用
class TextAttribute {
  fontSize(value: number): this {
    // 设置字体大小
    return this
  }

  fontColor(value: ResourceColor): this {
    // 设置字体颜色
    return this
  }
}

// 链式调用
Text('Hello')
  .fontSize(20)
  .fontColor(Color.Red)
  .fontWeight(FontWeight.Bold)
```

### 7.2 Node 层级关系

```
Content (抽象基类)
├── NodeContent
│   └── addFrameNode(FrameNode)
│   └── removeFrameNode(FrameNode)
├── ComponentContent<T>
│   └── constructor(uiContext, builder)
│   └── update(args: T)
│   └── reuse(param?)
│   └── recycle()
│   └── dispose()
└── ReactiveComponentContent<T>
    └── constructor(uiContext, builder, config, ...args)
    └── flushState()

FrameNode (组件节点)
├── getRenderNode(): RenderNode
├── getLayoutProperty(): LayoutProperty
├── appendChild(FrameNode)
├── removeChild(FrameNode)
└── dispose()

RenderNode (渲染节点)
├── appendChild(RenderNode)
├── backgroundColor
├── opacity
├── transform
├── draw(context: DrawContext)
└── dispose()

BuilderNode<Args> (构建器节点)
├── build(builder, arg?)
├── update(arg)
├── getFrameNode(): FrameNode
├── postTouchEvent(event)
└── dispose()
```

### 7.3 单位系统

| 单位 | 名称 | 说明 |
|------|------|------|
| **vp** | Virtual Pixel | 密度无关像素（推荐） |
| **fp** | Font Pixel | 字体缩放像素 |
| **px** | Physical Pixel | 物理像素 |
| **lpx** | Logical Pixel | 逻辑像素 |
| **%** | Percent | 百分比 |
| **Resource** | Resource | 资源引用 |

---

## 8. 与 ace_engine 的对应关系

### 8.1 SDK API → ace_engine 层次映射

| SDK API 类型 | ace_engine 层次 | 路径示例 |
|-------------|-----------------|----------|
| **Static API 组件/属性定义 (`component/*.static.d.ets`)** | Bridge 层（ArkTS Static 前端） | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/` |
| **Static API Modifier (`*Modifier.static.d.ets`)** | Bridge 层（ArkTS Static 前端） | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/` |
| **Dynamic API 组件/属性定义 (`@internal/component/ets/*.d.ts`)** | Bridge 层（Declarative 前端） | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/` |
| **Dynamic API Modifier (`*Modifier.d.ts`)** | Bridge 层（Declarative 前端） | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/ark_modifier/` |
| **FrameNode** | Base 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.h` |
| **BuilderNode** | Bridge 层 + Core 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_view_builder_node.cpp` |
| **RenderNode** | Render 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/render/render_node.h` |
| **Native Node Modifier 实现汇聚点** | Core Native Node 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/interfaces/native/node/node_modifiers.cpp` |
| **状态管理** | Bridge 层 State Management | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/state_mgmt/` |

### 8.2 组件从 SDK 到 ace_engine 的完整路径（双轨）

**示例 A：Dynamic API（Column）**

```
应用层 (App)
  ↓
SDK API 层
  ├── OpenHarmony/interface/sdk-js/api/@internal/component/ets/column.d.ts
  └── OpenHarmony/interface/sdk-js/api/arkui/ColumnModifier.d.ts
  ↓
Bridge 层（declarative_frontend）
  ├── frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register_impl_ng.cpp
  ├── frameworks/bridge/declarative_frontend/jsview/js_column.cpp
  ├── frameworks/bridge/declarative_frontend/ark_component/src/ArkColumn.ts
  ├── frameworks/bridge/declarative_frontend/ark_modifier/src/column_modifier.ts
  └── frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_bridge.cpp
  ↓
Core Native Node Modifier
  └── frameworks/core/interfaces/native/node/column_modifier.cpp
  ↓
Core Pattern / Layout / Render
  └── frameworks/core/components_ng/pattern/linear_layout/
```

**示例 B：Static API（Column）**

```
应用层 (App)
  ↓
SDK API 层
  ├── OpenHarmony/interface/sdk-js/api/arkui/component/column.static.d.ets
  └── OpenHarmony/interface/sdk-js/api/arkui/ColumnModifier.static.d.ets
  ↓
Bridge 层（arkts_frontend）
  ├── frameworks/bridge/arkts_frontend/arkoala_generator/BUILD.gn
  │   └── --input: ${ohos_ets_api_path}
  ├── frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/column.ets
  ├── frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/ColumnModifier.ets
  └── frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/BUILD.gn
      └── generate_static_abc(...)-> modules_static.abc -> components.abc
  ↓
Native Node Modifier
  └── frameworks/core/interfaces/native/node/column_modifier.cpp
```

### 8.3 关键文件路径对照表

| SDK API 文件 | ace_engine 关联实现 |
|-------------|-------------------|
| `OpenHarmony/interface/sdk-js/api/@internal/component/ets/column.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_column.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/ColumnModifier.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/ark_modifier/src/column_modifier.ts` |
| `OpenHarmony/interface/sdk-js/api/arkui/component/column.static.d.ets` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/column.ets` |
| `OpenHarmony/interface/sdk-js/api/arkui/ColumnModifier.static.d.ets` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/ColumnModifier.ets` |
| `OpenHarmony/interface/sdk-js/api/@internal/component/ets/text.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_text.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/TextModifier.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/ark_modifier/src/text_modifier.ts` |
| `OpenHarmony/interface/sdk-js/api/arkui/component/text.static.d.ets` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/text.ets` |
| `OpenHarmony/interface/sdk-js/api/arkui/TextModifier.static.d.ets` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/ColumnModifier.ets` |

**Pattern 路径速查（按组件类别）**:

| 组件类型 | Pattern 路径模式 | 示例 |
|----------|-----------------|------|
| 基础组件 | `pattern/{component}/` | `pattern/text/` |
| 容器组件 | `pattern/{component}/` | `pattern/list/` |
| 对话框 | `pattern/dialog/{dialog}_pattern.cpp` | `pattern/dialog/alert_dialog_pattern.cpp` |
| 选择器 | `pattern/{name}_picker/` | `pattern/date_picker/` |

### 8.4 ArkUI NAPI 模块（`@ohos.arkui.*` 与相关通用 `@ohos.*`）

ArkUI 暴露的非 DSL 能力（路由、弹窗、节点、Modifier、媒体查询、字体度量、组件快照、拖拽、Inspector 等）以**模块**形式发布，应用通过 `import xxx from '@ohos.xxx'` 使用。这些模块在 ace_engine 内部由 NAPI 实现，集中在：

- 实现根目录：`OpenHarmony/foundation/arkui/ace_engine/interfaces/napi/kits/`（34 个子目录）
- 模块注册：`interfaces/napi/kits/BUILD.gn`、`interfaces/napi/kits/napi_lib.gni`

> 应用侧的导入与签名口径详见 [docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md](../api/ArkUI_API_Paradigm_Knowledge_Base_CN.md) 第 0.2/0.3 节，本节仅做 SDK ↔ ace_engine 映射。

| 模块 API（声明） | 静态版本 | ace_engine NAPI 实现目录 |
|------------------|----------|--------------------------|
| `@ohos.router.d.ts` | `@ohos.router.static.d.ets`（如有） | `interfaces/napi/kits/router/` |
| `@ohos.promptAction.d.ts` | `@ohos.promptAction.static.d.ets`（如有） | `interfaces/napi/kits/promptaction/`（legacy `prompt/`） |
| `@ohos.mediaquery.d.ts` | — | `interfaces/napi/kits/mediaquery/` |
| `@ohos.animator.d.ts` | `@ohos.animator.static.d.ets` | `interfaces/napi/kits/animator/` |
| `@ohos.font.d.ts` | — | `interfaces/napi/kits/font/` |
| `@ohos.measure.d.ts` | — | `interfaces/napi/kits/measure/` |
| `@ohos.arkui.componentSnapshot.d.ts` | — | `interfaces/napi/kits/component_snapshot/` |
| `@ohos.arkui.componentUtils.d.ts` | — | `interfaces/napi/kits/componentutils/` |
| `@ohos.arkui.observer.d.ts` | — | `interfaces/napi/kits/observer/` |
| `@ohos.arkui.inspector.d.ts` | — | `interfaces/napi/kits/inspector/` |
| `@ohos.arkui.dragController.d.ts` | — | `interfaces/napi/kits/drag_controller/` |
| `@ohos.arkui.drawableDescriptor.d.ts` | — | `interfaces/napi/kits/drawabledescriptor/` |
| `@ohos.arkui.performanceMonitor.d.ts` | — | `interfaces/napi/kits/performancemonitor/` |
| `@ohos.arkui.UIContext.d.ts`（Overlay 等） | — | `interfaces/napi/kits/overlay/` |
| `@ohos.arkui.focusController.d.ts`（如有） | — | `interfaces/napi/kits/focus_controller/` |
| `@ohos.arkui.atomicServiceTabs.d.ts` 等 | — | `interfaces/napi/kits/atomic_service_bar/` |
| `@ohos.arkui.pluginComponent.d.ts` | — | `interfaces/napi/kits/plugincomponent/` |
| `@ohos.arkui.displaySync.d.ts` | — | `interfaces/napi/kits/display_sync/` |
| `@ohos.arkui.intelligence.*` | — | `interfaces/napi/kits/intelligence/` |
| `@ohos.arkui.smartGesture.*`（如有） | — | `interfaces/napi/kits/smart_gesture_controller/` |
| `@ohos.arkui.textMenuController.*`（如有） | — | `interfaces/napi/kits/text_menu_controller/` |

其他 NAPI 子目录：`atomic_service_bar/`、`color_sampler/`、`component_test/`、`configuration/`、`container_utils/`、`device/`、`grid/`、`luminance_sampler/`、`ui_material/`、`utils/`。

**典型对应示例：**

| SDK API 声明 | NAPI 实现文件 |
|--------------|---------------|
| `OpenHarmony/interface/sdk-js/api/@ohos.router.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/interfaces/napi/kits/router/js_router.cpp` |

**调用链概述：**

```
应用：import router from '@ohos.router'
       └─→ NAPI 入口注册（interfaces/napi/kits/napi_lib.gni 列出模块）
            └─→ kits/<module>/js_<module>.cpp 解析参数
                 └─→ 调用 ace_engine 内部能力（Pattern / Pipeline / DragManager 等）
```

调试时若发现 `import '@ohos.arkui.xxx'` 报错或行为异常，先到 `interfaces/napi/kits/<对应子目录>/` 中定位实现入口，再向 Pattern/Pipeline 层追溯。

---

## 9. API 定义规范

本章说明 ArkUI Component Static API 的定义规范和命名约定。

### 9.1 文件命名规范

**Static API 文件命名**: `{componentName}.static.d.ets`
- 使用小写开头的小驼峰命名：`text.static.d.ets`, `button.static.d.ets`
- 多个单词合并：`textInput.static.d.ets`, `imageAnimator.static.d.ets`

**支持文件命名**: `{category}.static.d.ets`
- `common.static.d.ets` (14,174行) - 通用属性方法
- `enums.static.d.ets` (4,329行) - 枚举类型
- `units.static.d.ets` (1,609行) - 单位类型
- `gesture.static.d.ets` (2,318行) - 手势识别

**跨范式命名转换**：

| 层 | 命名风格 | 示例（TextInput） |
|----|----------|-------------------|
| Dynamic 文件名 | 小驼峰 + `.d.ts` | `text_input.d.ts`（snake_case 例外）/ `textInput` 概念 |
| Static 文件名 | 小驼峰 + `.static.d.ets` | `textInput.static.d.ets` |
| Modifier | 大驼峰 + `Modifier` | `TextInputModifier` |
| ace_engine Pattern | 全小写 + 下划线 + `_pattern` | `text_input_pattern.cpp` |

### 9.2 接口命名规范

| 接口类型 | 命名模式 | 示例 |
|---------|---------|------|
| **Attribute** | `{ComponentName}Attribute` | `TextAttribute`, `ButtonAttribute` |
| **Configuration** | `{ComponentName}Configuration` | `ButtonConfiguration` |
| **Options** | `{ComponentName}Options` | `CalendarOptions` |
| **Param** | `{ComponentName}Param` | `AlertDialogParam` |

### 9.3 枚举命名规范

使用大驼峰命名（PascalCase）：
```typescript
export declare enum ButtonType {
    Capsule,
    Circle,
    Normal,
    ROUNDED_RECTANGLE = 3
}
```

### 9.4 函数命名规范

**组件构造函数**: 与组件名相同（首字母大写）
```typescript
export declare function Text(value: ResourceStr | undefined): TextAttribute;
export declare function Button(value: string | Resource | undefined): ButtonAttribute;
```

**属性方法**: 小驼峰命名，返回 `this`
```typescript
default fontSize(value: number | undefined): this;
default fontColor(value: ResourceColor | undefined): this;
```

### 9.5 事件方法规范

**命名模式**: `on` + 事件名称（首字母大写）
```typescript
default onClick(callback: Callback | undefined): this;
default onTouch(callback: Callback<TouchEvent> | undefined): this;
default onScroll(callback: OnScrollCallback | undefined): this;
```

### 9.6 导入依赖规范

标准导入顺序：
```typescript
// 1. 通用接口（必需）
import { CommonMethod, Callback, AttributeModifier } from "./common";

// 2. 枚举类型
import { TextAlign, FontStyle, FontWeight } from "./enums";

// 3. 单位类型
import { Resource, ResourceColor, Font, Length } from "./units";

// 4. 相关组件类型
import { TextRange } from "./textCommon";
```


---

## 10. 常见问题解答

### 10.1 SDK API 和 ace_engine 的关系

**Q: SDK API 和 ace_engine 是什么关系？**

A: SDK API 是应用开发者使用的接口，ace_engine 是底层实现：

```
┌─────────────────────────────────────┐
│  应用层 (ArkTS 应用)                │
│  使用 SDK API 开发                  │
└─────────────────────────────────────┘
              ↓
┌─────────────────────────────────────┐
│  SDK API 层                         │
│  OpenHarmony/interface/sdk-js/api/arkui/
│  - Static API (.static.d.ets)       │
│  - Dynamic API (*.d.ts)             │
└─────────────────────────────────────┘
              ↓
┌─────────────────────────────────────┐
│  ace_engine 实现层                  │
│  OpenHarmony/foundation/arkui/ace_engine/
│  - Dynamic: declarative_frontend    │
│  - Static:  arkts_frontend          │
│  - Core: Pattern/Layout/Render      │
└─────────────────────────────────────┘
```

**关键要点**:
- SDK API 定义接口契约（TypeScript/ETS）
- ace_engine 提供实际实现（C++）
- Dynamic API（组件/属性 + Modifier）主要走 `frameworks/bridge/declarative_frontend/`
- Static API（组件/属性 + Modifier）主要走 `frameworks/bridge/arkts_frontend/`
- 两条路径最终都汇聚到 Core Native Node Modifier 和 NG Pattern

### 13.2 Static API 和 Dynamic API 的区别

本节聚焦于 **SDK API ↔ ace_engine 实现映射**。Static / Dynamic / 类web (full/lite) 等**前端范式与调用面**（import 路径、全局可用 API、范式选择依据、跨范式对照清单）已统一收敛到：

- [docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md](../api/ArkUI_API_Paradigm_Knowledge_Base_CN.md)

本文档保留的层面：

- 两套 API 在 ace_engine 源码侧的实现入口：
  - Static API → [frameworks/bridge/arkts_frontend/](../../frameworks/bridge/arkts_frontend/)（koala 生成 → `components.abc`）
  - Dynamic API → [frameworks/bridge/declarative_frontend/](../../frameworks/bridge/declarative_frontend/)（bridge 运行时分发）
- 两套 API 在组件层最终汇聚到同一份 `components_ng/pattern/<component>/` Pattern 实现（详见本文档第 8 章 ace_engine 对应关系）。

### 10.3 如何查找组件实现

**Q: 如何从 SDK API 快速找到 ace_engine 的实现代码？**

A: 按以下步骤操作：

1. **确定组件名** (如 `Text`)
2. **查找 Pattern 文件**:
   - 路径: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/{component}/`
   - 文件: `{component}_pattern.cpp`
3. **查找 Property 文件**:
   - 路径: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/`
   - 文件: `{component}_property.cpp`
4. **查找 Bridge 实现**:
   - Dynamic API 路径: `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/`
   - Static API 路径: `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/`

**快捷工具**: 使用本知识库"第 3 章 组件 API 分类清单"快速查找

### 10.4 API 版本兼容性问题

**Q: 不同 API 版本之间有哪些常见兼容性问题？**

A: 主要问题及解决方案：

| 问题 | 影响 | 解决方案 |
|------|------|----------|
| **FrameNode 构造函数参数** | API 12+ 必须传 UIContext | 检查文档，传入正确参数 |
| **生命周期方法变更** | 旧方法可能不调用 | 迁移到新的生命周期方法 |
| **事件参数类型变化** | 事件回调参数类型不匹配 | 更新回调函数签名 |
| **废弃的 API** | 编译警告或运行时错误 | 使用推荐的替代 API |

**Q: 如何判断某个 API 是否可用？**

A:
1. 查看文件顶部的 `@since` 标签（如 `@since API 12`）
2. 查看接口定义中的版本注释
3. 参考官方文档的 API Reference

### 10.5 性能优化建议

**Q: 如何优化 ArkUI 应用性能？**

A: 关键优化点：

1. **使用 LazyForEach 替代 ForEach** (大数据列表)
2. **合理使用 BuilderNode 复用** (reuse/recycle)
3. **避免频繁的属性更新** (批量更新)
4. **使用 ReactiveBuilderNode** (API 12+，更好的状态同步)
5. **减少不必要的嵌套** (简化组件树)
6. **使用 key 参数** (帮助 ForEach/LazyForEach 识别节点)

---

## 11. 开发调试指南

### 11.1 从 SDK API 追踪到源码

**步骤 1: 确定入口点**
```
应用代码 → SDK API（先区分 Static 还是 Dynamic）
```

**步骤 2: 找到 Bridge 实现**
```
Dynamic API  → frameworks/bridge/declarative_frontend/
Static API   → frameworks/bridge/arkts_frontend/
```

**步骤 3: 定位 Pattern 实现**
```
Bridge/NativeNodeModifier → frameworks/core/components_ng/pattern/*/*_pattern.cpp
```

**步骤 4: 查看 Property 和 Render**
```
Pattern → frameworks/core/components_ng/property/*_property.cpp
Pattern → frameworks/core/components_ng/render/*_render_property.cpp
```

**示例追踪 Text 组件（Dynamic + Static）**:
```bash
# 1) Dynamic API 定义
OpenHarmony/interface/sdk-js/api/@internal/component/ets/text.d.ts
OpenHarmony/interface/sdk-js/api/arkui/TextModifier.d.ts

# 2) Dynamic Bridge 层实现
OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_text.cpp
OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/ark_modifier/src/text_modifier.ts
OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_bridge.cpp

# 3) Static API 定义
OpenHarmony/interface/sdk-js/api/arkui/component/text.static.d.ets
OpenHarmony/interface/sdk-js/api/arkui/TextModifier.static.d.ets

# 4) Static Bridge 层实现
OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/text.ets
OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/TextModifier.ets

# 5) Native Node Modifier
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/interfaces/native/node/node_text_modifier.cpp

# 6) Pattern 层实现
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_pattern.cpp

# 7) Property 层
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/text_property.cpp

# 8) Render 层
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/render/text_render_property.cpp
```

---

## 12. 总结

本文按以下脉络组织 ArkUI SDK API：

- **第 1 章** 给出文件分布与统计快照（动态/静态组件、Modifier、`@ohos.arkui.*` 模块及相关 NAPI 模块）。
- **第 2~3 章** 说明组件 / Node / 图形 / Modifier 四类 API 的角色，并按基础、容器、选择器、形状、媒体、高级等分类列出全部组件。
- **第 4 章** 明确 Dynamic 与 Static 两种范式下组件声明文件的三段式结构、`@ComponentBuilder` 与 `CommonMethod` 基座。
- **第 5~6 章** 覆盖增量渲染（`@memo` / `@param`）与状态管理（`@State` / `@Prop` / `@Link` 等）装饰器。
- **第 7~9 章** 解释 Modifier 桥接机制、与 ace_engine 源码（`components_ng` / `interfaces/native/node` / NAPI 实现）的对应关系，以及跨范式命名转换规则。
- **第 10~11 章** 汇总常见问题与从 SDK API 追踪到源码的调试路径。

后续维护时应同步更新第 1 章的统计、第 3 章的组件清单及第 8 章的源码映射，确保声明文件与 ace_engine 实现保持一致。

---

**文档维护**: 本文档应随着 SDK API 的演进定期更新。当添加新组件或新 API 时，请及时更新相关章节。

**相关资源**:
- [README.md](README.md) - SDK API 文档索引
- [OpenHarmony/interface/sdk-js/api/arkui/](OpenHarmony/interface/sdk-js/api/arkui/) - ArkUI SDK API 目录
- [OpenHarmony 官方文档](https://docs.openharmony.cn/)
