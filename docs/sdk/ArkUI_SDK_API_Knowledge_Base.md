# ArkUI SDK API 结构化分析文档

> **文档说明**: 本档位于 ace_engine 仓库，分析 OpenHarmony SDK API 与 ace_engine 实现层的映射关系。SDK API 定义文件位于 `OpenHarmony/interface/sdk-js/api/arkui/`，ace_engine 实现文件位于 `OpenHarmony/foundation/arkui/ace_engine/`。

**API 版本**: API 11 - API 23
**SDK API 路径**: `OpenHarmony/interface/sdk-js/api/arkui/`
**ace_engine 实现路径**: `OpenHarmony/foundation/arkui/ace_engine/`

---

## Claude 参考指南

### 文档用途
本文档是 Claude 的内部参考知识库，用于：
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
1. 查看"2.1 核心 Node API 类型"章节
2. 对比 FrameNode 和 BuilderNode 的核心特性
3. 查看"6.2 Node 层级关系"理解架构设计
4. 查看"常见问题解答"获取更多说明
```

#### 场景 3: 用户询问状态管理
```
用户问题: "@State 和 @Link 的区别是什么？"
查找步骤:
1. 查看"5. 状态管理 API"章节
2. 理解各装饰器的用途
3. 查看"常见问题解答"中的状态管理对比
```

### 快速查找指南

| 想查找什么 | 跳转到章节 |
|-----------|-----------|
| 组件列表和实现位置 | 第 3 章 "组件 API 分类清单" |
| 核心 API (FrameNode/BuilderNode) | 第 2.1 节 "核心 Node API 类型" |
| 组件属性设置方法 | 第 6.1 节 "Modifier 模式" |
| 状态管理装饰器 | 第 5 章 "状态管理 API" |
| SDK → ace_engine 映射 | 第 7 章 "与 ace_engine 的对应关系" |
| 常见问题解答 | 第 10 章 "常见问题解答" |
| 版本变更和兼容性 | 第 9 章 "版本演进" |
| API 快速参考 | 第 8 章 "API 快速参考" |

### 代码验证原则
根据 ace_engine 的 **CLAUDE.md** 原则，回答问题时：
1. **Always provide actual code** - 使用 Read/Grep 工具读取实际源码
2. **Never guess** - 如果代码未找到，明确说明"此代码在 ace_engine 中未找到"
3. **Verify before answering** - 用户建议可能有误，务必验证实际代码
4. **Provide evidence** - 给出文件路径和行号作为证据

---

## 1. 目录结构概览

```
OpenHarmony/interface/sdk-js/api/arkui/
├── [根目录]                           # 核心 Node API 和 Modifier 接口
│   ├── FrameNode.d.ts                # 框架节点定义
│   ├── BuilderNode.d.ts              # 构建器节点定义
│   ├── RenderNode.d.ts               # 渲染节点定义
│   ├── Graphics.d.ts                 # 图形绘制类型定义
│   ├── CommonModifier.d.ts           # 通用属性修饰器
│   ├── XComponentNode.d.ts           # XComponent 组件节点
│   ├── NodeContent.d.ts              # 节点内容封装
│   ├── ComponentContent.d.ts         # 组件内容封装
│   ├── [76个 *Modifier.d.ts 文件]    # 动态 API: Modifier 类定义
│   └── [74个 *Modifier.static.d.ets] # 静态 API: Component 定义
├── component/                        # 组件静态接口定义 (129 个文件)
│   ├── button.static.d.ets
│   ├── text.static.d.ets
│   ├── list.static.d.ets
│   ├── grid.static.d.ets
│   └── [... 126 个其他组件]
├── incremental/                      # 增量渲染 API
│   └── runtime/
│       └── state.static.d.ets        # 增量状态管理
└── stateManagement/                  # 状态管理 API
    ├── decorator.static.d.ets        # 状态装饰器
    ├── remember.static.d.ets         # 记忆函数
    ├── utils.static.d.ets            # 工具函数
    └── storage/                      # 存储相关
        ├── appStorage.static.d.ets
        ├── localStorage.static.d.ets
        └── [... 4 个存储相关文件]
```

**统计概览**:
- 根目录文件总数: 169 个
- component 目录文件: 129 个
- Modifier.d.ts 文件: 76 个
- Modifier.static.d.ets 文件: 74 个
- 总计 API 定义文件: **298 个**

---

## 2. API 类型分类说明

### 2.1 核心 Node API 类型

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

**主要接口**:
```typescript
class FrameNode {
  // 节点树操作
  appendChild(node: FrameNode): void
  insertChildAfter(child: FrameNode, sibling: FrameNode | null): void
  removeChild(node: FrameNode): void
  clearChildren(): void

  // 节点查询
  getChild(index: number): FrameNode | null
  getChildren(): Array<FrameNode>

  // 布局和几何
  getLayoutProperty(): LayoutProperty
  getLayoutConstraint(): LayoutConstraint
  getPositionToParent(): Position

  // 渲染节点访问
  getRenderNode(): RenderNode
  getRenderResult(): FinishEventType

  // 事件绑定
  on(event: string, callback: Function): void
  off(event: string, callback?: Function): void

  // 生命周期
  dispose(): void

  // 状态管理
  getUIStates(): number
  setUIStatesChangeHandler(handler: UIStatesChangeHandler): void
}
```

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

**主要接口**:
```typescript
class BuilderNode<Args extends Object[]> {
  constructor(uiContext: UIContext, options?: RenderOptions)

  // 构建和更新
  build(builder: WrappedBuilder<Args>, arg?: Object): void
  update(arg: Object): void

  // 节点访问
  getFrameNode(): FrameNode | null

  // 事件分发
  postTouchEvent(event: TouchEvent): boolean
  postInputEvent(event: InputEventType): boolean

  // 生命周期
  dispose(): void
  reuse(param?: Object): void
  recycle(): void
  updateConfiguration(): void
}

// API 12+ 新增
class ReactiveBuilderNode<Args extends Object[]> {
  build(builder: WrappedBuilder<Args>, config: BuildOptions, ...args: Args): void
  flushState(): void  // 强制同步更新
}
```

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

**主要接口**:
```typescript
class RenderNode {
  // 树操作
  appendChild(node: RenderNode): void
  insertChildAfter(child: RenderNode, sibling: RenderNode | null): void
  removeChild(node: RenderNode): void

  // 渲染属性
  backgroundColor: number
  opacity: number
  clipToFrame: boolean
  size: Size
  position: Position
  frame: Frame

  // 变换
  pivot: Pivot
  scale: Scale
  translation: Translation
  rotation: Rotation
  transform: Matrix4

  // 阴影
  shadowColor: number
  shadowOffset: Offset
  shadowAlpha: number
  shadowElevation: number
  shadowRadius: number

  // 边框
  borderStyle: Edges<BorderStyle>
  borderWidth: Edges<number>
  borderColor: Edges<number>
  borderRadius: BorderRadiuses

  // 形状遮罩和裁剪
  shapeMask: ShapeMask
  shapeClip: ShapeClip

  // 绘制
  draw(context: DrawContext): void
  invalidate(): void

  // 生命周期
  dispose(): void
}
```

#### NodeContent & ComponentContent

**文件**:
- `NodeContent.d.ts`
- `ComponentContent.d.ts`

**核心特性**:
- NodeContent: 节点内容的实体封装，可动态添加/删除 FrameNode
- ComponentContent: 组件内容的封装，通过 @Builder 创建，支持参数更新
- ReactiveComponentContent: API 22+ 新增，支持响应式状态管理

**主要接口**:
```typescript
class NodeContent extends Content {
  addFrameNode(node: FrameNode): void
  removeFrameNode(node: FrameNode): void
}

class ComponentContent<T> extends Content {
  constructor(uiContext: UIContext, builder: WrappedBuilder<...>)
  update(args: T): void
  reuse(param?: Object): void
  recycle(): void
  dispose(): void
  updateConfiguration(): void
}

class ReactiveComponentContent<T> extends Content {
  constructor(uiContext: UIContext, builder: WrappedBuilder<T>,
              config: BuildOptions, ...args: T)
  flushState(): void  // 强制同步更新状态
}
```

---

### 2.2 图形类型 (Graphics)

**文件**: `Graphics.d.ts`

#### 基础图形类型
```typescript
// 尺寸和位置
interface Size {
  width: number   // 单位: vp
  height: number  // 单位: vp
}

interface Offset {
  x: number
  y: number
}

interface Position {
  x: number
  y: number
}

interface Frame {
  x: number
  y: number
  width: number
  height: number
}

// 变换相关
interface Pivot {
  x: number  // [0.0, 1.0]
  y: number  // [0.0, 1.0]
}

interface Scale {
  x: number
  y: number
}

interface Translation {
  x: number  // 单位: px
  y: number
}

interface Rotation {
  x: number  // 单位: degree
  y: number
  z: number
}

type Matrix4 = [number, number, ..., number]  // 16 个数字

// 边框和圆角
interface Edges<T> {
  left: T
  right: T
  top: T
  bottom: T
}

interface BorderRadiuses {
  topLeft: number
  topRight: number
  bottomLeft: number
  bottomRight: number
}
```

#### 形状类型
```typescript
interface Rect {
  left: number
  top: number
  right: number
  bottom: number
}

interface RoundRect {
  rect: Rect
  corners: CornerRadius
}

interface Circle {
  centerX: number
  centerY: number
  radius: number
}

interface CommandPath {
  commands: string
}

// 形状遮罩和裁剪
class ShapeMask {
  setRectShape(rect: Rect): void
  setRoundRectShape(roundRect: RoundRect): void
  setCircleShape(circle: Circle): void
  setOvalShape(oval: Rect): void
  setCommandPath(path: CommandPath): void
  fillColor: number
  strokeColor: number
  strokeWidth: number
}

class ShapeClip {
  setRectShape(rect: Rect): void
  setRoundRectShape(roundRect: RoundRect): void
  setCircleShape(circle: Circle): void
  setOvalShape(oval: Rect): void
  setCommandPath(path: CommandPath): void
}
```

#### 长度和颜色度量
```typescript
enum LengthUnit {
  PX = 0,       // 物理像素
  VP = 1,       // 密度无关像素
  FP = 2,       // 字体缩放像素
  PERCENT = 3,  // 百分比
  LPX = 4       // 逻辑像素
}

class LengthMetrics {
  constructor(value: number, unit?: LengthUnit)
  static px(value: number): LengthMetrics
  static vp(value: number): LengthMetrics
  static fp(value: number): LengthMetrics
  static percent(value: number): LengthMetrics
  static lpx(value: number): LengthMetrics
  static resource(value: Resource): LengthMetrics

  unit: LengthUnit
  value: number
}

class ColorMetrics {
  static numeric(value: number): ColorMetrics
  static rgba(red: number, green: number, blue: number, alpha?: number): ColorMetrics
  static colorWithSpace(colorSpace: ColorSpace, red: number,
                        green: number, blue: number, alpha?: number): ColorMetrics
  static resourceColor(color: ResourceColor): ColorMetrics

  blendColor(overlayColor: ColorMetrics): ColorMetrics

  color: string
  red: number
  green: number
  blue: number
  alpha: number
}
```

#### 绘制上下文
```typescript
class DrawContext {
  size: Size              // 画布尺寸
  sizeInPixel: Size       // 像素单位画布尺寸
  canvas: drawing.Canvas  // 绘制画布
}
```

---

### 2.3 Modifier 模式

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

### 3.1 基础组件 (15 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **Text** | TextModifier.d.ts | text.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_pattern.cpp` | [知识库](../pattern/text/Text_Knowledge_Base_CN.md) | 文本显示 |
| **Image** | ImageModifier.d.ts | image.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/image/image_pattern.cpp` | [知识库](../pattern/image/Image_Knowledge_Base.md) | 图片显示 |
| **TextInput** | TextInputModifier.d.ts | textInput.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text_input/text_input_pattern.cpp` | - | 文本输入 |
| **TextArea** | TextAreaModifier.d.ts | textArea.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text_area/text_area_pattern.cpp` | - | 多行文本输入 |
| **Button** | ButtonModifier.d.ts | button.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/button/button_pattern.cpp` | - | 按钮 |
| **Toggle** | ToggleModifier.d.ts | toggle.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/toggle/toggle_pattern.cpp` | - | 开关 |
| **Checkbox** | CheckboxModifier.d.ts | checkbox.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/checkbox/checkbox_pattern.cpp` | - | 复选框 |
| **Radio** | - | radio.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/radio/radio_pattern.cpp` | - | 单选框 |
| **Slider** | SliderModifier.d.ts | slider.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/slider/slider_pattern.cpp` | - | 滑块 |
| **Progress** | ProgressModifier.d.ts | progress.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/progress/progress_pattern.cpp` | - | 进度条 |
| **LoadingProgress** | LoadingProgressModifier.d.ts | loadingProgress.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.cpp` | - | 加载进度 |
| **Divider** | DividerModifier.d.ts | divider.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/divider/divider_pattern.cpp` | - | 分割线 |
| **Blank** | BlankModifier.d.ts | blank.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/blank/blank_pattern.cpp` | - | 空白占位 |
| **Span** | SpanModifier.d.ts | span.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/span/span_pattern.cpp` | - | 文本片段 |
| **ImageSpan** | - | imageSpan.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/image_span/image_span_pattern.cpp` | - | 图片片段 |
| **Counter** | CounterModifier.d.ts | counter.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/counter/counter_pattern.cpp` | [知识库](../pattern/counter/Counter_Knowledge_Base.md) | 计数器 |

### 3.2 容器组件 (27 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **Column** | ColumnModifier.d.ts | column.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/linear_col/linear_col_pattern.cpp` | - | 纵向布局 |
| **Row** | RowModifier.d.ts | row.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/linear_row/linear_row_pattern.cpp` | - | 横向布局 |
| **Stack** | StackModifier.d.ts | stack.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/stack/stack_pattern.cpp` | - | 堆叠布局 |
| **Flex** | FlexModifier.d.ts | flex.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/flex/flex_pattern.cpp` | - | 弹性布局 |
| **Grid** | GridModifier.d.ts | grid.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_pattern.cpp` | - | 网格布局 |
| **GridRow** | GridRowModifier.d.ts | gridRow.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid_row/grid_row_pattern.cpp` | - | 栅格行容器 |
| **GridCol** | GridColModifier.d.ts | gridCol.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid_col/grid_col_pattern.cpp` | - | 栅格列容器 |
| **GridItem** | GridItemModifier.d.ts | gridItem.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid_item/grid_item_pattern.cpp` | - | 栅格子项 |
| **List** | ListModifier.d.ts | list.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/list/list_pattern.cpp` | - | 列表 |
| **ListItem** | ListItemModifier.d.ts | listItem.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/list_item/list_item_pattern.cpp` | - | 列表项 |
| **ListItemGroup** | ListItemGroupModifier.d.ts | listItemGroup.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/list_item_group/list_item_group_pattern.cpp` | - | 列表分组 |
| **Scroll** | ScrollModifier.d.ts | scroll.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/scroll/scroll_pattern.cpp` | [知识库](../pattern/scroll/Scroll_Knowledge_Base.md) | 滚动容器 |
| **Swiper** | SwiperModifier.d.ts | swiper.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp` | - | 轮播容器 |
| **Tabs** | TabsModifier.d.ts | tabs.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` | - | 标签页容器 |
| **TabContent** | - | tabContent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/tab_content/tab_content_pattern.cpp` | - | 标签页内容 |
| **Navigator** | NavigatorModifier.d.ts | navigator.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/navigator/navigator_pattern.cpp` | - | 导航容器 |
| **NavRouter** | NavRouterModifier.d.ts | navRouter.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/nav_router/nav_router_pattern.cpp` | - | 路由导航 |
| **Navigation** | NavigationModifier.d.ts | navigation.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | - | 导航栏 |
| **NavDestination** | - | navDestination.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/nav_destination/nav_destination_pattern.cpp` | - | 导航目标页 |
| **SideBarContainer** | SideBarContainerModifier.d.ts | sideBarContainer.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/side_bar_container/side_bar_container_pattern.cpp` | - | 侧边栏容器 |
| **Refresh** | RefreshModifier.d.ts | refresh.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/refresh/refresh_pattern.cpp` | [知识库](../pattern/refresh/Refresh_Knowledge_Base.md) | 下拉刷新 |
| **WaterFlow** | WaterFlowModifier.d.ts | waterFlow.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/water_flow/water_flow_pattern.cpp` | [知识库](../pattern/waterflow/WaterFlow_Knowledge_Base.md) | 瀑布流 |
| **FlowItem** | - | flowItem.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/flow_item/flow_item_pattern.cpp` | - | 瀑布流子项 |
| **RelativeContainer** | RelativeContainerModifier.d.ts | relativeContainer.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/relative_container/relative_container_pattern.cpp` | - | 相对布局容器 |
| **ColumnSplit** | ColumnSplitModifier.d.ts | columnSplit.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/column_split/column_split_pattern.cpp` | - | 纵向分割容器 |
| **RowSplit** | RowSplitModifier.d.ts | rowSplit.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/row_split/row_split_pattern.cpp` | - | 横向分割容器 |
| **FolderStack** | FolderStackModifier.d.ts | folderStack.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/folder_stack/folder_stack_pattern.cpp` | - | 文件夹堆叠 |

### 3.3 选择器组件 (8 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **Select** | SelectModifier.d.ts | select.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/select/select_pattern.cpp` | - | 下拉选择 |
| **DatePicker** | DatePickerModifier.d.ts | datePicker.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/date_picker/date_picker_pattern.cpp` | [知识库](../pattern/picker/Date_Picker_Knowledge_Base.md) | 日期选择器 |
| **TimePicker** | TimePickerModifier.d.ts | timePicker.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/time_picker/time_picker_pattern.cpp` | [知识库](../pattern/time_picker/Time_Picker_Knowledge_Base.md) | 时间选择器 |
| **TextPicker** | TextPickerModifier.d.ts | textPicker.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text_picker/text_picker_pattern.cpp` | [知识库](../pattern/text_picker/Text_Picker_Knowledge_Base.md) | 文本选择器 |
| **CalendarPicker** | CalendarPickerModifier.d.ts | calendarPicker.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/calendar_picker/calendar_picker_pattern.cpp` | [知识库](../pattern/calendar_picker/Calendar_Picker_Knowledge_Base.md) | 日历选择器 |
| **ContainerPicker** | ContainerPickerModifier.d.ts | containerPicker.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/container_picker/container_picker_pattern.cpp` | [知识库](../pattern/container_picker/Container_Picker_Knowledge_Base.md) | 容器选择器 |
| **CheckboxGroup** | CheckboxGroupModifier.d.ts | checkboxgroup.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/checkbox/checkbox_group_pattern.cpp` | - | 复选框组 |
| **Rating** | RatingModifier.d.ts | rating.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/rating/rating_pattern.cpp` | - | 评分组件 |
| **UIPickerComponent** | UIPickerComponentModifier.d.ts | uiPickerComponent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/ui_picker/ui_picker_pattern.cpp` | - | UI 选择器 |

### 3.4 形状组件 (7 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **Rect** | RectModifier.d.ts | rect.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/rect/rect_pattern.cpp` | - | 矩形 |
| **Circle** | - | circle.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/circle/circle_pattern.cpp` | - | 圆形 |
| **Ellipse** | EllipseModifier.d.ts | ellipse.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/ellipse/ellipse_pattern.cpp` | - | 椭圆 |
| **Path** | PathModifier.d.ts | path.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/path/path_pattern.cpp` | - | 路径 |
| **Polyline** | PolylineModifier.d.ts | polyline.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/polyline/polyline_pattern.cpp` | - | 折线 |
| **Polygon** | - | polygon.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/polygon/polygon_pattern.cpp` | - | 多边形 |
| **Shape** | ShapeModifier.d.ts | shape.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/shape/shape_pattern.cpp` | - | 形状 |

### 3.5 媒体组件 (4 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **Video** | VideoModifier.d.ts | video.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/video/video_pattern.cpp` | - | 视频播放器 |
| **ImageAnimator** | ImageAnimatorModifier.d.ts | imageAnimator.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/image_animator/image_animator_pattern.cpp` | [知识库](../pattern/image_animator/Image_Animator_Knowledge_Base.md) | 帧动画 |
| **Canvas** | - | canvas.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/canvas/canvas_pattern.cpp` | - | 画布 |
| **XComponent** | - | xcomponent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/xcomponent/xcomponent_pattern.cpp` | - | 原生组件容器 |

### 3.6 数据展示组件 (7 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **TextClock** | TextClockModifier.d.ts | textClock.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text_clock/text_clock_pattern.cpp` | [知识库](../pattern/text_clock/TextClock_Knowledge_Base_CN.md) | 文本时钟 |
| **TextTimer** | - | textTimer.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text_timer/text_timer_pattern.cpp` | [知识库](../pattern/texttimer/TextTimer_Knowledge_Base_CN.md) | 文本计时器 |
| **DataPanel** | DataPanelModifier.d.ts | dataPanel.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/data_panel/data_panel_pattern.cpp` | - | 数据面板 |
| **Gauge** | GaugeModifier.d.ts | gauge.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/gauge/gauge_pattern.cpp` | [知识库](../pattern/gauge/Gauge_Knowledge_Base.md) | 仪表盘 |
| **QRCode** | QRCodeModifier.d.ts | qrcode.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/qrcode/qrcode_pattern.cpp` | - | 二维码 |
| **Badge** | - | badge.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/badge/badge_pattern.cpp` | [知识库](../pattern/badge/Badge_Knowledge_Base_CN.md) | 徽章 |
| **AlphabetIndexer** | AlphabetIndexerModifier.d.ts | alphabetIndexer.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/alphabet_indexer/alphabet_indexer_pattern.cpp` | - | 字母索引 |

### 3.7 富文本组件 (4 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **RichEditor** | RichEditorModifier.d.ts | richEditor.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp` | - | 富文本编辑器 |
| **ContainerSpan** | ContainerSpanModifier.d.ts | containerSpan.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/container_span/container_span_pattern.cpp` | - | 容器片段 |
| **StyledString** | - | styledString.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/styled_string/styled_string_pattern.cpp` | - | 样式字符串 |
| **Hyperlink** | HyperlinkModifier.d.ts | hyperlink.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/hyperlink/hyperlink_pattern.cpp` | - | 超链接 |

### 3.8 弹窗和菜单组件 (9 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **AlertDialog** | - | alertDialog.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/dialog/alert_dialog_pattern.cpp` | - | 警告对话框 |
| **ActionSheet** | - | actionSheet.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/dialog/action_sheet_pattern.cpp` | - | 操作列表 |
| **Menu** | MenuModifier.d.ts | menu.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/menu/menu_pattern.cpp` | [知识库](../pattern/menu/Menu_Knowledge_Base.md) | 菜单 |
| **MenuItem** | MenuItemModifier.d.ts | menuItem.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/menu/menu_item_pattern.cpp` | - | 菜单项 |
| **CustomDialogController** | - | customDialogController.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/dialog/custom_dialog_pattern.cpp` | - | 自定义对话框控制器 |
| **BindSheet** | BindSheetModifier.d.ts | - | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/bind_sheet/bind_sheet_pattern.cpp` | - | 半模态转场 |
| **Panel** | PanelModifier.d.ts | panel.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/panel/panel_pattern.cpp` | - | 半屏弹窗 |
| **Popover** | PopoverModifier.d.ts | popover.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/popover/popover_pattern.cpp` | - | 气泡弹窗 |
| **Toast** | - | toast.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/toast/toast_pattern.cpp` | - | 提示条 |
| **Dialog** | - | dialog.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/dialog/dialog_pattern.cpp` | - | 对话框 |

### 3.9 高级组件 (19+ 个)

| 组件名 | Modifier 文件 | Static 文件 | ace_engine Pattern 位置 | 知识库 | 功能说明 |
|--------|---------------|-------------|-------------------------|--------|----------|
| **Web** | - | web.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/web/web_pattern.cpp` | - | Web 浏览器 |
| **FormComponent** | FormComponentModifier.d.ts | formComponent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/form/form_pattern.cpp` | - | 表单组件 |
| **PatternLock** | PatternLockModifier.d.ts | patternLock.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/pattern_lock/pattern_lock_pattern.cpp` | - | 图案锁 |
| **Stepper** | StepperModifier.d.ts | stepper.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/stepper/stepper_pattern.cpp` | - | 步骤条 |
| **StepperItem** | StepperItemModifier.d.ts | - | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/stepper/stepper_item_pattern.cpp` | - | 步骤条项 |
| **Search** | SearchModifier.d.ts | search.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/search/search_pattern.cpp` | [知识库](../pattern/search/Search_Knowledge_Base_CN.md) | 搜索框 |
| **ContentSlot** | - | contentSlot.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/content_slot/content_slot_pattern.cpp` | - | 内容插槽 |
| **RemoteWindow** | - | remoteWindow.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/remote_window/remote_window_pattern.cpp` | - | 远程窗口 |
| **GridTree** | - | gridTree.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid_tree/grid_tree_pattern.cpp` | - | 网格树 |
| **UIExtensionComponent** | - | uiExtensionComponent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/ui_extension/ui_extension_pattern.cpp` | - | UI 扩展组件 |
| **EmbeddedComponent** | - | embeddedComponent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/embedded_component/embedded_component_pattern.cpp` | - | 嵌入式组件 |
| **EffectComponent** | - | effectComponent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/effect_component/effect_component_pattern.cpp` | - | 效果组件 |
| **Component3D** | - | component3d.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/component3d/component3d_pattern.cpp` | - | 3D 组件 |
| **SecurityComponent** | - | securityComponent.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/security/security_component_pattern.cpp` | - | 安全组件 |
| **SymbolGlyph** | - | symbolglyph.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/symbol/symbol_glyph_pattern.cpp` | - | 符号图标 |
| **SymbolSpan** | SymbolSpanModifier.d.ts | symbolSpan.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/symbol/symbol_span_pattern.cpp` | - | 符号片段 |
| **Marquee** | MarqueeModifier.d.ts | marquee.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/marquee/marquee_pattern.cpp` | [知识库](../pattern/marquee/Marquee_Knowledge_Base.md) | 跑马灯 |
| **LazyGrid** | LazyGridModifier.d.ts | lazyGrid.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/grid/grid_pattern.cpp` | [知识库](../pattern/lazy_layout/LazyGrid_Knowledge_Base.md) | 懒加载网格 |
| **Particle** | ParticleModifier.d.ts | particle.static.d.ets | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/particle/particle_pattern.cpp` | - | 粒子效果 |

### 3.10 工具和辅助类 (27+ 个)

| 类名 | Static 文件 | 功能说明 |
|------|-------------|----------|
| **Common** | common.static.d.ets | 通用属性和方法 |
| **Units** | units.static.d.ets | 单位类型定义 |
| **Enums** | enums.static.d.ets | 枚举类型定义 |
| **Resources** | resources.static.d.ets | 资源管理 |
| **Gesture** | gesture.static.d.ets | 手势识别 |
| **Focus** | focus.static.d.ets | 焦点控制 |
| **Animation** | animation.static.d.ets | 动画 |
| **Screen** | screen.static.d.ets | 屏幕信息 |
| **CustomComponent** | customComponent.static.d.ets | 自定义组件 |
| **ExtendableComponent** | extendableComponent.static.d.ets | 可扩展组件 |
| **Builder** | builder.static.d.ets | 构建器函数 |
| **ForEach** | forEach.static.d.ets | 循环渲染 |
| **If** | if.static.d.ets | 条件渲染 |
| **LazyForEach** | - | 懒加载循环渲染 |
| **Repeat** | repeat.static.d.ets | 重复渲染 |
| **WithTheme** | withTheme.static.d.ets | 主题切换 |
| **ScrollBar** | scrollBar.static.d.ets | 滚动条 |
| **IndicatorComponent** | indicatorcomponent.static.d.ets | 指示器 |
| **RootScene** | rootScene.static.d.ets | 根场景 |
| **WindowScene** | windowScene.static.d.ets | 窗口场景 |
| **FormLink** | formLink.static.d.ets | 卡片链接 |
| **SaveButton** | saveButton.static.d.ets | 保存按钮 |
| **PasteButton** | pasteButton.static.d.ets | 粘贴按钮 |

---

## 4. Component Static API 详解

本章详细说明 `interface/sdk-js/api/arkui/component` 目录中的 Static API 定义文件结构、模式和规范。

### 4.1 Static API 文件结构

每个 `.static.d.ets` 文件定义了一个组件或功能的完整 Static API。文件包含以下类型的定义：

#### 4.1.1 枚举定义 (`export declare enum`)

用于定义组件特定的枚举值。

**示例**（Button 组件）:
```typescript
// 文件: button.static.d.ets
export declare enum ButtonType {
    Capsule,        // 胶囊按钮（默认圆角为高度的一半）
    Circle,         // 圆形按钮
    Normal,         // 普通按钮（默认无圆角）
    ROUNDED_RECTANGLE = 3  // 圆角矩形按钮
}

export declare enum ButtonStyleMode {
    NORMAL = 0,     // 普通按钮
    EMPHASIZED = 1, // 强调按钮
    TEXTUAL = 2     // 文本按钮
}
```

**示例**（List 组件）:
```typescript
// 文件: list.static.d.ets
export declare enum ScrollState {
    Idle,           // 空闲状态
    Scroll,         // 滚动状态
    Fling           // 惯性滚动状态
}

export declare enum ListItemAlign {
    Start,          // 列表项交叉轴起始对齐
    Center,         // 列表项交叉轴居中对齐
    End             // 列表项交叉轴末尾对齐
}
```

#### 4.1.2 接口定义 (`export declare interface`)

组件的 Static API 定义包含多种接口类型：

| 接口类型 | 命名模式 | 用途 | 示例 |
|---------|---------|------|------|
| **Attribute** | `{ComponentName}Attribute` | 组件属性接口（继承自 CommonMethod） | `TextAttribute`, `ButtonAttribute` |
| **Configuration** | `{ComponentName}Configuration` | 组件配置接口（用于 Modifier 模式） | `ButtonConfiguration` |
| **Options** | `{ComponentName}Options` | 组件选项接口（参数配置） | `CalendarOptions` |
| **Param** | `{ComponentName}Param` | 组件参数接口（对话框等特殊组件） | `AlertDialogParam` |

**Attribute 接口示例**（Text 组件）:
```typescript
// 文件: text.static.d.ets
export declare interface TextAttribute extends CommonMethod {
    // 字体相关（8个属性）
    default font(fontValue: Font | undefined, options?: FontSettingOptions | undefined): this;
    default fontColor(value: ResourceColor | undefined): this;
    default fontSize(value: double | string | Resource | undefined): this;
    default minFontSize(value: double | string | Resource | undefined): this;
    default maxFontSize(value: double | string | Resource | undefined): this;

    // 文本布局（12个属性）
    default textAlign(value: TextAlign | undefined): this;
    default lineHeight(value: string | number | Resource | undefined): this;
    default lineSpacing(value: string | number | Length[] | undefined): this;
    default maxLines(value: number | undefined): this;
    default textOverflow(value: TextOverflow | undefined): this;

    // 文本行为（10个属性）
    default textSelectable(value: boolean | undefined): this;
    default copyOption(value: CopyOptions | undefined): this;
    default draggable(value: boolean | undefined): this;

    // 事件回调（5个事件）
    default onCopy(callback: Callback<TextRange> | undefined): this;
    default onTextSelectionChange(callback: Callback<TextRange> | undefined): this;
}

// TextOptions 接口定义
export declare interface TextOptions {
    controller: TextController;
}
```
`TextOptions` 只有一个 `controller` 属性，用于控制 Text 组件。

---

**函数声明**：
```typescript
// 文件: text.static.d.ets
/**
 * Defines Text Component.
 *
 * @param { string | Resource } [content]
 * @param { TextOptions } [value]
 * @param { CustomBuilder } [content_]
 * @returns { TextAttribute }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23 static
 */
@ComponentBuilder
export declare function Text(
    content?: string | Resource,
    value?: TextOptions,
    content_?: CustomBuilder
): TextAttribute;
```

**Configuration 接口示例**（Button 组件）:
```typescript
// 文件: button.static.d.ets
export declare interface ButtonConfiguration extends CommonConfiguration<ButtonConfiguration> {
    label: string;              // 按钮文本标签
    stateEffect?: boolean;      // 是否启用按下效果
    type?: ButtonType;          // 按钮类型
    role?: ButtonRole;          // 按钮角色
}
```

#### 4.1.3 类型定义 (`export type`)

用于定义回调函数类型等复杂类型。

**示例**:
```typescript
// 文件: button.static.d.ets
export type ButtonTriggerClickCallback = (xPos: double, yPos: double) => void;

// 文件: list.static.d.ets
export type OnScrollCallback = (scrollOffset: number, scrollState: ScrollState) => void;
export type OnItemDragStartCallback = (item: ListItem, index: number) => ItemDragInfo;
```

#### 4.1.4 函数声明 (`export declare function`)

组件的构造函数声明。

**示例**:
```typescript
// 文件: text.static.d.ets
/**
 * Defines Text Component.
 *
 * @param { string | Resource } [content]
 * @param { TextOptions } [value]
 * @param { CustomBuilder } [content_]
 * @returns { TextAttribute }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23 static
 */
@ComponentBuilder
export declare function Text(
    content?: string | Resource,
    value?: TextOptions,
    content_?: CustomBuilder
): TextAttribute;

// 文件: button.static.d.ets
export declare function Button(value: string | Resource | undefined): ButtonAttribute;

// 文件: list.static.d.ets
export declare function List(value: { (item: ListItem, index: number) => void } | undefined): ListAttribute;
```

### 4.2 文档注释规范

Static API 文件使用标准的 JSDoc 注释格式：

#### 4.2.1 文件头注释

```typescript
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @kit ArkUI
 */
```

#### 4.2.2 方法注释

```typescript
/**
 * Called when the font size is set.
 * 设置字体大小
 *
 * <p><strong>NOTE</strong>:
 * <br>If fontSize is of the number type, the unit fp is used.
 * <br>如果 fontSize 是 number 类型，则使用 fp 单位
 * </p>
 *
 * @param { double | string | Resource } value - Font size value. Default value is 16fp.
 * @returns { TextAttribute } The attribute of the text.
 * @default 16
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23 static
 */
default fontSize(value: double | string | Resource | undefined): this;
```

#### 4.2.3 常用 JSDoc 标签说明

| 标签 | 用途 | 示例 |
|------|------|------|
| `@file` | 文件标识 | `@file` |
| `@kit` | 所属 Kit | `@kit ArkUI` |
| `@param` | 参数说明 | `@param { string } value - 参数描述` |
| `@returns` | 返回值说明 | `@returns { this } 返回自身，支持链式调用` |
| `@default` | 默认值 | `@default 16` |
| `@syscap` | 系统能力 | `@syscap SystemCapability.ArkUI.ArkUI.Full` |
| `@since` | 起始版本 | `@since 23 static` |
| `@systemapi` | 系统API标识 | `@systemapi` |

#### 4.2.4 @ComponentBuilder 装饰器

`@ComponentBuilder` 是组件构造函数的标记装饰器，表示该函数可以接受：
- 普通参数（如 `content`, `value`）
- 尾随闭包参数（通常命名为 `xxx_`，类型为 `CustomBuilder`）

**示例**：
```typescript
@ComponentBuilder
export declare function Text(
    content?: string | Resource,
    value?: TextOptions,
    content_?: CustomBuilder  // 尾随闭包参数
): TextAttribute;
```

##### CustomBuilder 类型

**定义**: `export type CustomBuilder = @Builder (() => void);`

`CustomBuilder` 是 `@Builder` 装饰的函数类型，用于组件的尾随闭包。

**示例**:
```typescript
@Builder
function MyBuilder() {
  Text('Child Text')
}

// 使用
Text() {  // content_ 参数
  MyBuilder()
}
```

##### 尾随闭包 (Trailing Closure)

尾随闭包是 ArkUI 的语法特性，允许在组件调用后直接写子组件。

**参数命名约定**: 通常在原参数名后加下划线 `_`，如 `content_`

**完整示例**:
```typescript
// 定义
@ComponentBuilder
export declare function Column(
    space?: Length | Resource,
    value?: ColumnOptions,
    content_?: CustomBuilder  // 尾随闭包参数
): ColumnAttribute;

// 使用
Column({ space: 10 }) {  // value 参数
  Text('Hello')          // content_ 尾随闭包
  Text('World')
}
```

### 4.3 文件规模统计

| 文件名 | 行数 | 类型 | 说明 |
|--------|------|------|------|
| **common.static.d.ets** | 14,174 | 核心支持 | 定义所有组件通用的属性方法 |
| **web.static.d.ets** | 6,935 | 组件 | Web 组件（最大组件文件） |
| **enums.static.d.ets** | 4,329 | 核心支持 | 定义所有枚举类型 |
| **richEditor.static.d.ets** | 2,428 | 组件 | 富文本编辑器 |
| **gesture.static.d.ets** | 2,318 | 核心支持 | 手势识别定义 |
| **navigation.static.d.ets** | 1,955 | 组件 | 导航组件 |
| **textInput.static.d.ets** | 1,947 | 组件 | 文本输入框 |
| **canvas.static.d.ets** | 1,925 | 组件 | 画布组件 |
| **styledString.static.d.ets** | 1,696 | 组件 | 样式字符串 |
| **units.static.d.ets** | 1,609 | 核心支持 | 单位类型定义 |
| **text.static.d.ets** | 1,240 | 组件 | 文本组件 |
| **list.static.d.ets** | 1,060 | 组件 | 列表组件 |

---

## 5. 核心支持文件详解

本章详细说明 `component` 目录中的核心支持文件，这些文件被所有组件依赖使用。

### 5.1 common.static.d.ets - 通用属性定义

**文件路径**: `interface/sdk-js/api/arkui/component/common.static.d.ets`
**文件规模**: 14,174 行
**作用**: 定义所有组件通用的属性方法（CommonMethod 接口）

#### 5.1.1 CommonMethod 接口结构

CommonMethod 是所有组件 Attribute 接口的基类，定义了约 100+ 个通用方法：

```typescript
export declare interface CommonMethod {
    // ========== 尺寸属性 (15个) ==========
    default width(value: Length | undefined): this;
    default height(value: Length | undefined): this;
    default size(value: SizeOptions | undefined): this;
    default constraintSize(value: ConstraintSizeOptions | undefined): this;

    // ========== 位置属性 (8个) ==========
    default position(value: Position | undefined): this;
    default offset(value: Offset | undefined): this;
    default markAnchor(value: Offset | undefined): this;
    default pivot(value: Pivot | undefined): this;

    // ========== 布局属性 (12个) ==========
    default padding(value: Padding | Length | undefined): this;
    default margin(value: Margin | Length | undefined): this;
    default layoutWeight(value: number | string | undefined): this;
    default align(alignment: Alignment | undefined): this;

    // ========== 背景和边框 (25个) ==========
    default backgroundColor(value: ResourceColor | undefined): this;
    default borderRadius(value: BorderRadiuses | Length | undefined): this;
    default borderStyle(value: EdgeStyles | BorderStyle | undefined): this;
    default borderWidth(value: EdgeWidths | Length | undefined): this;
    default borderColor(value: EdgeColors | LocalizedEdgeColors | undefined): this;

    // ========== 显示和透明度 (8个) ==========
    default visibility(value: Visibility | undefined): this;
    default opacity(value: number | Resource | undefined): this;
    default alpha(value: number | undefined): this;

    // ========== 事件处理 (20+个) ==========
    default onClick(callback: Callback | undefined): this;
    default onTouch(callback: Callback | undefined): this;
    default onHover(callback: Callback | undefined): this;

    // ========== 动画相关 (10个) ==========
    default animateTo(value: AnimateParam | undefined): this;
    default transition(value: AnimateParam | undefined): this;

    // ... 更多方法
}
```

#### 5.1.2 主要分类统计

| 分类 | 方法数量 | 说明 |
|------|---------|------|
| **尺寸属性** | 15 | width, height, size, constraintSize 等 |
| **位置属性** | 8 | position, offset, markAnchor, pivot 等 |
| **布局属性** | 12 | padding, margin, layoutWeight, align 等 |
| **背景和边框** | 25 | backgroundColor, borderRadius, border 等 |
| **显示相关** | 8 | visibility, opacity, alpha 等 |
| **事件处理** | 20+ | onClick, onTouch, onHover 等 |
| **动画相关** | 10 | animateTo, transition 等 |
| **其他** | 30+ | id, key, enabled, focusable 等 |
| **总计** | **100+** | 所有组件通用的属性方法 |

### 5.2 enums.static.d.ets - 枚举类型定义

**文件路径**: `interface/sdk-js/api/arkui/component/enums.static.d.ets`
**文件规模**: 4,329 行
**作用**: 定义所有组件使用的枚举类型

#### 5.2.1 主要枚举分类

| 分类 | 枚举示例 | 数量 |
|------|---------|------|
| **对齐相关** | `HorizontalAlign`, `VerticalAlign`, `Alignment` | ~10 |
| **布局相关** | `Axis`, `Direction`, `ItemAlign`, `FlexAlign` | ~15 |
| **样式相关** | `BorderStyle`, `FontStyle`, `FontWeight`, `Color` | ~20 |
| **文本相关** | `TextOverflow`, `EllipsisMode`, `TextAlign` | ~15 |
| **动画相关** | `Curve`, `PlayMode`, `FillMode` | ~10 |
| **交互相关** | `TouchType`, `MouseButton`, `MouseAction` | ~15 |
| **手势相关** | `GestureType`, `GestureMask` | ~10 |
| **滚动相关** | `EdgeEffect`, `ScrollState`, `BarState` | ~15 |
| **显示相关** | `Visibility`, `RenderStrategy`, `HoverEffect` | ~10 |
| **其他** | `ResponseType`, `FocusPriority`, `ItemType` 等 | ~80 |
| **总计** | **~200+** | 所有枚举类型 |

### 5.3 units.static.d.ets - 单位类型定义

**文件路径**: `interface/sdk-js/api/arkui/component/units.static.d.ets`
**文件规模**: 1,609 行
**作用**: 定义长度、颜色、尺寸等单位类型

#### 5.3.1 主要类型定义

```typescript
// ========== 长度类型 ==========
type Length = string | number | Resource;

// ========== 颜色类型 ==========
type ResourceColor = Color | string | Resource | LinearGradient;

// ========== 尺寸和位置 ==========
interface SizeOptions {
    width?: Length;
    height?: Length;
}

interface Padding {
    top?: Length; right?: Length; bottom?: Length; left?: Length;
}

interface Margin {
    top?: Length; right?: Length; bottom?: Length; left?: Length;
}

// ========== 圆角 ==========
interface BorderRadiuses {
    topLeft?: Length; topRight?: Length;
    bottomLeft?: Length; bottomRight?: Length;
}
```

### 5.4 gesture.static.d.ets - 手势识别定义

**文件路径**: `interface/sdk-js/api/arkui/component/gesture.static.d.ets`
**文件规模**: 2,318 行
**作用**: 定义手势识别相关类型和接口

#### 5.4.1 主要内容

```typescript
// ========== 手势类型 ==========
enum GestureType {
    Tap,        // 点击
    LongPress,  // 长按
    Pan,        // 拖动
    Pinch,      // 捏合
    Rotation,   // 旋转
    Swipe       // 滑动
}

// ========== 手势识别器 ==========
class GestureRecognizer {
    gestureID: number;
    priority: GesturePriority;
}

class TapGestureRecognizer extends GestureRecognizer {
    count: number;          // 点击次数
    fingers: number;        // 手指数量
}
```

### 5.5 builder.static.d.ets - 构建器定义

**文件路径**: `interface/sdk-js/api/arkui/component/builder.static.d.ets`
**文件规模**: 146 行
**作用**: 定义构建器相关类型

```typescript
// 自定义构建器装饰器
declare function CustomBuilder(type: FunctionType): void;

// 包装构建器
declare class WrappedBuilder<T> {
    initialize(...args: T): void;
}

// 包装构建器函数以便复用
declare function wrapBuilder<T>(builder: T): WrappedBuilder<T>;
```

---

## 6. 增量渲染 API

**文件**: `incremental/runtime/state.static.d.ets`

### 4.1 增量状态管理

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

## 7. 状态管理 API

### 7.1 状态装饰器

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

### 7.2 存储管理

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

### 7.3 记忆函数

**文件**: `stateManagement/remember.static.d.ets`

```typescript
// 记忆函数
@Remember        // 缓存计算结果
```

---

## 8. 关键概念说明

### 8.1 Modifier 模式

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

### 8.2 Node 层级关系

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

### 8.3 单位系统

| 单位 | 名称 | 说明 |
|------|------|------|
| **vp** | Virtual Pixel | 密度无关像素（推荐） |
| **fp** | Font Pixel | 字体缩放像素 |
| **px** | Physical Pixel | 物理像素 |
| **lpx** | Logical Pixel | 逻辑像素 |
| **%** | Percent | 百分比 |
| **Resource** | Resource | 资源引用 |

---

## 9. 与 ace_engine 的对应关系

### 9.1 SDK API → ace_engine 层次映射

| SDK API 类型 | ace_engine 层次 | 路径示例 |
|-------------|-----------------|----------|
| **Static API (.static.d.ets)** | Bridge 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/` |
| **Dynamic API (*.d.ts)** | Core 层 (Pattern + Property) | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/` |
| **FrameNode** | Base 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.h` |
| **BuilderNode** | Bridge 层 + Core 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_view_builder_node.cpp` |
| **RenderNode** | Render 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/render/render_node.h` |
| **Modifier** | Property 层 | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/*_property.cpp` |
| **状态管理** | Bridge 层 State Management | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/state_mgmt/` |

### 9.2 组件从 SDK 到 ace_engine 的完整路径

**示例**: Text 组件

```
应用层 (App)
  ↓
SDK API 层 (OpenHarmony/interface/sdk-js/api/arkui/)
  ├── text.static.d.ets          (Static API - 声明式语法)
  └── TextModifier.d.ts           (Dynamic API - 声明式配置对象)
  ↓
ace_engine 层 (OpenHarmony/foundation/arkui/ace_engine/)
  ├── Bridge 层
  │   ├── frameworks/bridge/declarative_frontend/jsview/node_text_modifier.cpp  (Static API 实现)
  │   └── frameworks/bridge/declarative_frontend/jsview/js_text.cpp             (Dynamic API 实现)
  └── Core 层
      ├── Pattern 层
      │   ├── frameworks/core/components_ng/pattern/text/text_pattern.h
      │   └── frameworks/core/components_ng/pattern/text/text_pattern.cpp
      ├── Property 层
      │   ├── frameworks/core/components_ng/property/text_property.h
      │   └── frameworks/core/components_ng/property/text_property.cpp
      └── Render 层
          └── frameworks/core/components_ng/render/text_render_property.cpp
```

### 9.3 关键文件路径对照表

| SDK API 文件 | ace_engine 实现文件 |
|-------------|-------------------|
| `OpenHarmony/interface/sdk-js/api/arkui/FrameNode.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/base/frame_node.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/BuilderNode.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_view_builder_node.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/RenderNode.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/render/render_node.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/TextModifier.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/text_property.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/ButtonModifier.d.ts` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/button_property.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/component/text.static.d.ets` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/node_text_modifier.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/component/button.static.d.ets` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/node_button_modifier.cpp` |
| `OpenHarmony/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/state_mgmt/` |

---

## 10. API 定义规范

本章说明 ArkUI Component Static API 的定义规范和命名约定。

### 10.1 文件命名规范

**Static API 文件命名**: `{componentName}.static.d.ets`
- 使用小写开头的小驼峰命名：`text.static.d.ets`, `button.static.d.ets`
- 多个单词合并：`textInput.static.d.ets`, `imageAnimator.static.d.ets`

**支持文件命名**: `{category}.static.d.ets`
- `common.static.d.ets` (14,174行) - 通用属性方法
- `enums.static.d.ets` (4,329行) - 枚举类型
- `units.static.d.ets` (1,609行) - 单位类型
- `gesture.static.d.ets` (2,318行) - 手势识别

### 10.2 接口命名规范

| 接口类型 | 命名模式 | 示例 |
|---------|---------|------|
| **Attribute** | `{ComponentName}Attribute` | `TextAttribute`, `ButtonAttribute` |
| **Configuration** | `{ComponentName}Configuration` | `ButtonConfiguration` |
| **Options** | `{ComponentName}Options` | `CalendarOptions` |
| **Param** | `{ComponentName}Param` | `AlertDialogParam` |

### 10.3 枚举命名规范

使用大驼峰命名（PascalCase）：
```typescript
export declare enum ButtonType {
    Capsule,
    Circle,
    Normal,
    ROUNDED_RECTANGLE = 3
}
```

### 10.4 函数命名规范

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

### 10.5 事件方法规范

**命名模式**: `on` + 事件名称（首字母大写）
```typescript
default onClick(callback: Callback | undefined): this;
default onTouch(callback: Callback<TouchEvent> | undefined): this;
default onScroll(callback: OnScrollCallback | undefined): this;
```

### 10.6 导入依赖规范

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

## 11. API 快速参考

### 11.1 FrameNode 常用方法和属性

#### 树操作
| 方法 | 说明 | 使用场景 |
|------|------|----------|
| `appendChild(node: FrameNode)` | 添加子节点到末尾 | 动态添加组件 |
| `insertChildAfter(child, sibling)` | 在指定节点后插入 | 精确控制子节点位置 |
| `removeChild(node: FrameNode)` | 移除子节点 | 删除组件 |
| `clearChildren()` | 清空所有子节点 | 批量清理 |
| `getChild(index: number)` | 获取指定索引的子节点 | 访问特定子组件 |
| `getChildren(): Array<FrameNode>` | 获取所有子节点 | 遍历子组件 |

#### 布局和几何
| 方法 | 说明 | 返回类型 |
|------|------|----------|
| `getLayoutProperty()` | 获取布局属性 | LayoutProperty |
| `getLayoutConstraint()` | 获取布局约束 | LayoutConstraint |
| `getPositionToParent()` | 获取相对父节点的位置 | Position |
| `getRenderNode()` | 获取渲染节点 | RenderNode |
| `getRenderResult()` | 获取渲染结果 | FinishEventType |

#### 事件绑定
| 方法 | 说明 | 示例 |
|------|------|------|
| `on(event: string, callback)` | 注册事件监听 | `frameNode.on('touch', callback)` |
| `off(event: string, callback?)` | 移除事件监听 | `frameNode.off('touch', callback)` |

#### 生命周期
| 方法 | 说明 | 注意事项 |
|------|------|----------|
| `dispose()` | 销毁节点，释放资源 | 调用后节点不可再用 |

### 11.2 BuilderNode 使用要点

#### 创建和构建
```typescript
// 1. 创建 BuilderNode
const builderNode = new BuilderNode(uiContext)

// 2. 构建（只能调用一次）
builderNode.build(wrappedBuilder, args)

// 3. 获取 FrameNode
const frameNode = builderNode.getFrameNode()

// 4. 后续更新
builderNode.update(newArgs)  // 参数更新
builderNode.reuse(param)     // 复用
builderNode.recycle()        // 回收
builderNode.dispose()        // 销毁
```

#### 关键注意事项
- build() 只能调用一次，重复调用会报错
- update() 参数类型必须与 @Builder 定义匹配
- reuse()/recycle() 用于性能优化，实现组件复用
- ReactiveBuilderNode（API 12+）提供 flushState() 强制同步状态

### 11.3 组件命名规则

#### SDK API 文件命名
| 类型 | 命名规则 | 示例 |
|------|----------|------|
| Static API | `{componentName}.static.d.ets` | `text.static.d.ets` |
| Dynamic API (Modifier) | `{ComponentName}Modifier.d.ts` | `TextModifier.d.ts` |
| 状态管理 | `{category}/{name}.static.d.ets` | `stateManagement/decorator.static.d.ets` |

#### ace_engine 源码命名
| 层次 | 命名规则 | 示例 |
|------|----------|------|
| Pattern | `{component}_pattern.{h\|cpp}` | `text_pattern.cpp` |
| Layout Property | `{component}_layout_property.{h\|cpp}` | `text_layout_property.cpp` |
| Paint Property | `{component}_paint_property.{h\|cpp}` | `text_paint_property.cpp` |
| Event Hub | `{component}_event_hub.{h\|cpp}` | `text_event_hub.cpp` |
| Model | `{component}_model_ng.{h\|cpp}` | `text_model_ng.cpp` |

#### 命名转换规则
- SDK API: 小写开头，驼峰命名 → `textInput`
- Modifier: 大写开头，驼峰命名 + Modifier → `TextInputModifier`
- Pattern: 全小写，下划线连接 + _pattern → `text_input_pattern`

### 11.4 文件路径快速查询

#### 从组件名查找实现
```
Text 组件
├── SDK API (Static):     OpenHarmony/interface/sdk-js/api/arkui/component/text.static.d.ets
├── SDK API (Dynamic):    OpenHarmony/interface/sdk-js/api/arkui/TextModifier.d.ts
├── Bridge 层 (Static):   OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/node_text_modifier.cpp
├── Bridge 层 (Dynamic):  OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_text.cpp
├── Pattern 层:           OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_pattern.cpp
├── Property 层:          OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/text_property.cpp
└── Render 层:            OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/render/text_render_property.cpp
```

#### 特殊组件路径
| 组件类型 | Pattern 路径模式 | 示例 |
|----------|-----------------|------|
| 基础组件 | `pattern/{component}/` | `pattern/text/` |
| 容器组件 | `pattern/{component}/` | `pattern/list/` |
| 对话框 | `pattern/dialog/{dialog}_pattern.cpp` | `pattern/dialog/alert_dialog_pattern.cpp` |
| 选择器 | `pattern/{name}_picker/` | `pattern/date_picker/` |

---

## 12. 版本演进

### 12.1 API 11 - API 23 重要变更

#### API 11 (初始版本)
- 引入 FrameNode/BuilderNode/RenderNode 核心 API
- 基础组件库（Text、Image、Button、List 等）
- 状态管理装饰器（@State、@Prop、@Link）
- Modifier 模式属性设置

#### API 12 (性能优化)
- **ReactiveBuilderNode**: 新增响应式构建器节点，支持 flushState() 强制同步
- **LazyForEach 性能增强**: 优化大数据列表渲染
- **新的动画接口**: 更灵活的动画控制
- **组件生命周期增强**: 更精确的生命周期回调

#### API 13 - API 15 (功能扩展)
- **新增组件**: SymbolGlyph、Particle、Marquee 等
- **状态管理 V2**: AppStorage V2、LocalStorage V2
- **增强的手势识别**: 更丰富的手势类型
- **无障碍增强**: 更好的辅助功能支持

#### API 16 - API 19 (平台能力)
- **多窗口增强**: WindowScene、RemoteWindow
- **3D 组件**: Component3D 支持
- **安全组件**: SecurityComponent
- **嵌入式组件**: EmbeddedComponent、UIExtensionComponent

#### API 20 - API 23 (现代化)
- **声明式 UI 增强**: 更简洁的语法
- **性能优化**: LazyGrid、LazyForEach 进一步优化
- **新的状态管理**: @ObservedV2、@TraceV2
- **渲染性能提升**: 增量渲染改进

### 12.2 兼容性注意事项

#### 废弃的 API
| API | 废弃版本 | 替代方案 |
|-----|----------|----------|
| 旧的组件生命周期方法 | API 12 | 新的 onWillAppear/onWillDisappear |
| 某些动画接口 | API 14 | 新的 animateTo 接口 |
| 旧的状态存储方式 | API 16 | AppStorage V2 / LocalStorage V2 |

#### 不兼容变更
1. **FrameNode 创建方式**: API 12+ 必须传入 UIContext
2. **Builder 构建方式**: API 12+ 支持参数化构建
3. **事件回调签名**: 部分组件的事件参数类型有变化

### 12.3 新旧 API 迁移指南

#### 从 API 11 迁移到 API 12+
```typescript
// ❌ 旧方式 (API 11)
const builderNode = new BuilderNode()
builderNode.build(builder)

// ✅ 新方式 (API 12+)
const builderNode = new BuilderNode(uiContext, options)
builderNode.build(builder, config, ...args)
builderNode.flushState()  // 强制同步状态
```

#### 状态管理迁移
```typescript
// ❌ 旧方式
@State count: number = 0

// ✅ 新方式 (API 20+)
@Local count: number = 0  // 更精确的语义
```

---

## 13. 常见问题解答

### 13.1 SDK API 和 ace_engine 的关系

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
│  - Bridge 层 (Static API 实现)      │
│  - Core 层 (Pattern + Property)     │
│  - Render 层 (绘制)                 │
└─────────────────────────────────────┘
```

**关键要点**:
- SDK API 定义接口契约（TypeScript/ETS）
- ace_engine 提供实际实现（C++）
- Static API 通过 Bridge 层连接到 Core 层
- Dynamic API 直接操作 Core 层

### 10.2 Static API 和 Dynamic API 的区别

**Q: Static API (.static.d.ets) 和 Dynamic API (*.d.ts) 有什么区别？**

A:

| 特性 | Static API | Dynamic API |
|------|-----------|-------------|
| **文件类型** | `.static.d.ets` | `*.d.ts` |
| **使用方式** | 声明式 `Text().width(100)` | 声明式 `new TextModifier().width(100)` |
| **实现位置** | Modifier 层 | Bridge 层 |
| **性能** | 编译时优化 | 运行时动态设置 |
| **灵活性** | 较低，编译时确定 | 高，可动态修改 |
| **适用场景** | 常规 UI 开发 | 动态属性修改、复用 |

**说明**：两者都是声明式 API，Dynamic API 的 "Dynamic" 指的是支持运行时动态修改属性值，而非使用方式是命令式的。

**示例对比**:
```typescript
// Static API (推荐用于常规开发)
Text('Hello')
  .fontSize(20)
  .fontColor(Color.Red)

// Dynamic API (推荐用于动态属性修改和复用)
const modifier = new TextModifier()  // 声明式创建配置对象
modifier.fontSize(20)                // 声明式设置属性
modifier.fontColor(Color.Red)
Text().attribute(modifier)           // 应用配置
// modifier 可以复用，动态修改属性
```

**Q: 什么时候用 Dynamic API？**

A: 以下场景优先使用 Dynamic API：
- 需要复用属性配置
- 动态切换组件属性
- 与 C++/Cangjie 等其他语言交互
- 需要精细控制属性更新时机

### 13.3 如何查找组件实现

**Q: 如何从 SDK API 快速找到 ace_engine 的实现代码？**

A: 按以下步骤操作：

1. **确定组件名** (如 `Text`)
2. **查找 Pattern 文件**:
   - 路径: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/{component}/`
   - 文件: `{component}_pattern.cpp`
3. **查找 Property 文件**:
   - 路径: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/`
   - 文件: `{component}_property.cpp`
4. **查找 Bridge 实现** (Static API):
   - 路径: `OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/`
   - 文件: `js_{component}.cpp`

**快捷工具**: 使用本知识库"第 3 章 组件 API 分类清单"快速查找

### 13.4 API 版本兼容性问题

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
4. 使用本知识库"第 9 章 版本演进"

### 13.5 常见错误和陷阱

#### 陷阱 1: FrameNode 未附加到 UIContext
```typescript
// ❌ 错误
const frameNode = FrameNode.create('Text')  // 缺少 UIContext

// ✅ 正确
const frameNode = FrameNode.create(uiContext, 'Text')
```

#### 陷阱 2: BuilderNode 重复调用 build()
```typescript
// ❌ 错误
builderNode.build(builder, arg1)
builderNode.build(builder, arg2)  // 报错：build 只能调用一次

// ✅ 正确
builderNode.build(builder, arg1)
builderNode.update(arg2)  // 使用 update 更新参数
```

#### 陷阱 3: 忘记释放资源
```typescript
// ❌ 错误：内存泄漏
const builderNode = new BuilderNode(uiContext)
// 使用后未释放

// ✅ 正确
const builderNode = new BuilderNode(uiContext)
try {
  // 使用 builderNode
} finally {
  builderNode.dispose()  // 释放资源
}
```

#### 陷阱 4: 在错误的线程操作 FrameNode
```typescript
// ❌ 错误：在非 UI 线程操作
setTimeout(() => {
  frameNode.appendChild(childNode)  // 可能崩溃
}, 1000)

// ✅ 正确：在 UI 线程操作
uiContext.runTask(() => {
  frameNode.appendChild(childNode)
})
```

#### 陷阱 5: Static 和 Dynamic API 混用不当
```typescript
// ❌ 可能的问题
const text = Text('Hello')
const modifier = new TextModifier()
modifier.fontSize(20)
text.fontSize(30)  // Static 设置覆盖了 Dynamic，行为不确定

// ✅ 明确使用一种方式
// 方式 1: 纯 Static
Text('Hello').fontSize(20)

// 方式 2: 纯 Dynamic
const modifier = new TextModifier()
modifier.fontSize(20)
const frameNode = FrameNode.create(uiContext, 'Text')
frameNode.appendChild(modifier)
```

### 13.6 性能优化建议

**Q: 如何优化 ArkUI 应用性能？**

A: 关键优化点：

1. **使用 LazyForEach 替代 ForEach** (大数据列表)
2. **合理使用 BuilderNode 复用** (reuse/recycle)
3. **避免频繁的属性更新** (批量更新)
4. **使用 ReactiveBuilderNode** (API 12+，更好的状态同步)
5. **减少不必要的嵌套** (简化组件树)
6. **使用 key 参数** (帮助 ForEach/LazyForEach 识别节点)

---

## 14. 开发调试指南

### 14.1 从 SDK API 追踪到源码

**步骤 1: 确定入口点**
```
应用代码 → SDK API (.static.d.ets / *.d.ts)
```

**步骤 2: 找到 Bridge 实现**
```
SDK API → frameworks/bridge/declarative_frontend/jsview/js_*.cpp
```

**步骤 3: 定位 Pattern 实现**
```
Bridge → frameworks/core/components_ng/pattern/*/*_pattern.cpp
```

**步骤 4: 查看 Property 和 Render**
```
Pattern → frameworks/core/components_ng/property/*_property.cpp
Pattern → frameworks/core/components_ng/render/*_render_property.cpp
```

**示例追踪 Text 组件**:
```bash
# 1. 从 SDK API 开始
OpenHarmony/interface/sdk-js/api/arkui/component/text.static.d.ets

# 2. Bridge 层实现 (Static API)
OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/node_text_modifier.cpp

# 3. Bridge 层实现 (Dynamic API)
OpenHarmony/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview/js_text.cpp

# 4. Pattern 层实现
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_pattern.cpp

# 5. Property 层
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/property/text_property.cpp

# 6. Render 层
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/render/text_render_property.cpp
```

### 14.2 常用调试技巧

#### 查看 FrameNode 树结构
```typescript
// 递归打印 FrameNode 树
function printFrameTree(node: FrameNode, indent: number = 0) {
  const prefix = '  '.repeat(indent)
  const info = node.getChildren()
  console.log(`${prefix}Node: ${node.getType()}`)
  info.forEach(child => printFrameTree(child, indent + 1))
}
```

#### 监听布局变化
```typescript
frameNode.on('layout', () => {
  const layout = frameNode.getLayoutProperty()
  console.log('Layout changed:', layout)
})
```

#### 跟踪属性更新
```cpp
// 在 C++ Pattern 层添加日志
// text_pattern.cpp
void TextPattern::OnModifyDone() {
  LOGI("TextPattern::OnModifyDone - text: %{public}s", text_.c_str());
  // ... 实现代码
}
```

### 14.3 日志分析方法

#### 启用详细日志
```bash
# 设置日志级别
export ACE_LOG_LEVEL=DEBUG

# 查看组件生命周期日志
hilog -t ACE | grep "TextPattern"
```

#### 常用日志标签
| 标签 | 说明 |
|------|------|
| `ACE` | ACE Engine 主标签 |
| `JSApp` | JavaScript 应用层 |
| `Pattern` | Pattern 层日志 |
| `Render` | 渲染层日志 |
| `Layout` | 布局计算日志 |

#### 性能分析
```bash
# 使用 hdc 工具抓取性能数据
hdc shell hilog -b D -T ACE,Pattern,Render > performance.log

# 分析布局耗时
grep "Layout" performance.log | awk '{print $1, $2, $NF}'
```

---

## 15. 实战示例

本章通过实际示例帮助开发者深入理解 ArkUI Component Static API 的使用方法和最佳实践。

### 15.1 从 Static API 追溯到实现代码

#### 15.1.1 Static API vs Dynamic API 调用路径

**Static API（声明式语法）**：
```typescript
Text('Hello').fontSize(20)
```
- **实现路径**: `node_text_modifier.cpp` (Modifier 层）
- **说明**: Static API 的 "Static" 指的是声明式语法（Declarative Syntax），不是"静态"的意思

**Dynamic API（Modifier 模式）**：
```typescript
const modifier = new TextModifier()
modifier.fontSize(20)
Text().attribute(modifier)
```
- **实现路径**: `js_text.cpp` (Bridge 层）
- **说明**: Dynamic API 的 "Dynamic" 指的是命令式动态修改（Imperative Dynamic Modification）

#### 15.1.2 Static API 完整调用链

**完整调用链示例 - Text 组件**：

```
应用层: Text('Hello').fontSize(20)
  ↓
Static API: text.static.d.ets (TextAttribute 接口)
  ↓
Modifier 层: node_text_modifier.cpp (SetTextFontSize)
  ↓
Property 层: text_property.cpp (TextProperty::SetFontSize)
  ↓
Pattern 层: text_pattern.cpp (TextPattern::OnModifyDone)
  ↓
Render 层: text_render_property.cpp (Paint 方法)
  ↓
屏幕显示
```

**快速查找实现代码的路径**：
- **Static API**: `interface/sdk-js/api/arkui/component/text.static.d.ets`
- **Modifier 层**: `ace_engine/frameworks/bridge/declarative_frontend/jsview/node_text_modifier.cpp`
- **Property 层**: `ace_engine/frameworks/core/components_ng/property/text_property.cpp`
- **Pattern 层**: `ace_engine/frameworks/core/components_ng/pattern/text/text_pattern.cpp`
- **Render 层**: `ace_engine/frameworks/core/components_ng/render/text_render_property.cpp`

### 15.2 理解 Attribute 接口

**核心特性**：

1. **继承 CommonMethod** - 所有通用属性（width, height, padding等）自动可用
2. **链式调用** - 所有方法返回 `this`，支持 `.fontSize(20).fontColor(Color.Red)`
3. **可选参数** - 支持 `undefined` 恢复为默认值
4. **default 关键字** - 属性方法使用 `default` 修饰

**使用示例**：
```typescript
// 基础使用
Text('Hello World')
  .fontSize(20)
  .fontColor(Color.Red)
  .textAlign(TextAlign.Center)

// 结合状态管理
@Component
struct Example {
  @State fontSize: number = 16
  build() {
    Text('Hello')
      .fontSize(this.fontSize)
      .onClick(() => { this.fontSize = 24 })
  }
}
```

### 15.3 Configuration vs Options vs Attribute

| 特性 | Attribute | Configuration | Options |
|------|-----------|----------------|---------|
| **API 模式** | 声明式 | 声明式 | 初始化参数 |
| **链式调用** | ✅ | ❌ | ❌ |
| **配置复用** | ❌ | ✅ | ⚠️ |
| **动态修改** | ⚠️ | ✅ | ❌ |
| **推荐场景** | 常规 UI 开发 | 属性复用 | 组件初始化 |

**说明**：

- **三者都是声明式的**：
  - **Attribute**: 声明式属性设置（`.fontSize(20)`）
  - **Configuration**: 声明式配置对象（`new TextModifier().fontSize(20)`）
  - **Options**: 初始化参数（`Text({ controller: this.controller })`）

- **Configuration 不是"命令式"**：
  - Configuration 对象本身是声明式创建的
  - 用于配置复用、动态属性修改、条件属性应用

**Configuration 的实际作用**：

```typescript
// 1. 配置复用
const myStyle = new TextModifier()
myStyle.fontSize(20).fontColor(Color.Red)

Text('H1').attribute(myStyle)
Text('H2').attribute(myStyle)

// 2. 动态修改
myStyle.fontSize(24)  // 所有使用 myStyle 的地方都会更新
```

---

## 16. 总结

### 16.1 统计数据

| 类别 | 数量 |
|------|------|
| **总 API 定义文件** | 298 个 |
| **核心 Node API** | 6 个 |
| **Modifier 类** | 76 个 |
| **Component 接口** | 129 个 |
| **基础组件** | 14 个 |
| **容器组件** | 27 个 |
| **选择器组件** | 9 个 |
| **形状组件** | 6 个 |
| **媒体组件** | 4 个 |
| **高级组件** | 17 个 |
| **辅助工具** | 27+ 个 |

### 16.2 API 特点

1. **完整的组件库**: 涵盖基础、容器、选择器、形状、媒体等全场景
2. **强大的状态管理**: @State, @Prop, @Link, @Provide 等多种装饰器
3. **灵活的节点操作**: FrameNode/BuilderNode/RenderNode 三层架构
4. **类型安全**: TypeScript 完整类型定义
5. **增量渲染**: 支持性能优化的增量更新机制
6. **跨语言支持**: 支持 Cangjie 等其他语言调用

---

**文档维护**: 本文档应随着 SDK API 的演进定期更新。当添加新组件或新 API 时，请及时更新相关章节。

**相关资源**:
- [README.md](README.md) - SDK API 文档索引
- [OpenHarmony/interface/sdk-js/api/arkui/](OpenHarmony/interface/sdk-js/api/arkui/) - ArkUI SDK API 目录
- [OpenHarmony 官方文档](https://docs.openharmony.cn/)
