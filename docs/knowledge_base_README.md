# Knowledge Base

此目录用于存放 ArkUI ACE Engine 开发过程中的各种知识库文档。

## 📌 知识库检索索引

**元数据索引文件**: [`knowledge_base_INDEX.json`](./knowledge_base_INDEX.json)

此文件包含所有知识库的结构化元数据，便于 Claude 快速检索：

- **组件关键词** - 通过功能关键词快速定位相关组件
- **别名映射** - 通过别名/同义词查找组件
- **分类索引** - 按组件类型（基础/容器/选择器等）分类浏览
- **路径映射** - 快速定位源码和 SDK API 文件路径

**使用示例**：

- 用户询问"下拉刷新" → 搜索关键词 → 定位到 `Refresh_Knowledge_Base.md`
- 用户询问"滚动容器" → 搜索别名 → 定位到 `Scroll_Knowledge_Base.md`
- 用户询问"文本选择器" → 按分类查找 selector → 定位到 `Text_Picker_Knowledge_Base.md`

**统计数据**（截至 2026-02-26）：

- 总知识库文档: 41 个
- 组件知识库: 27 个
- SDK API 知识库: 2 个
- 系统功能知识库: 5 个（含 Layout 模块 3 个专题）
- CJ Frontend 知识库: 1 个
- Syntax 模块知识库: 7 个（1 架构总览 + 4 循环组件独立文档 + 2 专题文档）
- 架构文档: 1 个
- 覆盖组件: 26 个
- 检索关键词: 260+ 个

---

## 目录结构

```
knowledge_base/
 ├── README.md              # 本文件，知识库索引和说明
 ├── cj_frontend/           # CJ Frontend 桥接层知识库
 │   └── CJ_Frontend_Guide.md                   # 综合指南
 ├── sdk/                   # SDK 相关知识库
 │   ├── ArkUI_SDK_API_Knowledge_Base.md       # ArkUI SDK API 完整分析
 │   └── Component_API_Knowledge_Base_CN.md     # ArkUI 组件 API 知识库
  ├── common/                # 系统功能知识库
  │   └── interaction/
  │       ├── Gesture_Knowledge_Base_CN.md           # 手势系统知识库（基础层）
  │       └── Drag_Drop_Knowledge_Base_CN.md         # 拖拽系统知识库（基于手势扩展的进阶层）
 ├── architecture/          # 架构文档
 │   └── ThemeManager_Architecture_CN.md        # ThemeManager 主题系统架构
 ├── layout/                # 布局机制知识库
 │   ├── Layout_Framework_Knowledge_Base.md      # Layout 框架总览
 │   ├── Safe_Area_Mechanism_Knowledge_Base.md   # SafeArea 机制
 │   └── Ignore_Layout_Safe_Area_Knowledge_Base.md # ignoreLayoutSafeArea 机制
 ├── pattern/               # 组件模式知识库
 │   ├── badge/
 │   │   └── Badge_Knowledge_Base_CN.md         # Badge 组件知识库
 │   ├── calendar_picker/
 │   │   └── Calendar_Picker_Knowledge_Base.md  # CalendarPicker 组件知识库
 │   ├── counter/
 │   │   └── Counter_Knowledge_Base.md          # Counter 组件知识库
 │   ├── flex/
 │   │   └── Flex_Knowledge_Base.md             # Flex/Row/Column/Wrap 组件知识库
 │   ├── gauge/
 │   │   └── Gauge_Knowledge_Base.md             # Gauge 组件知识库
 │   ├── grid/
 │   │   └── Grid_Knowledge_Base.md          # Grid 组件知识库
 │   ├── image/
 │   │   └── Image_Knowledge_Base.md             # Image 组件知识库
 │   ├── container_picker/
 │   │   └── Container_Picker_Knowledge_Base.md # ContainerPicker 组件知识库
 │   ├── image_animator/
 │   │   └── Image_Animator_Knowledge_Base.md    # ImageAnimator 组件知识库
 │   ├── marquee/
 │   │   └── Marquee_Knowledge_Base.md           # Marquee 组件知识库
 │   ├── menu/
 │   │   └── Menu_Knowledge_Base.md              # Menu 组件知识库
 │   ├── picker/
 │   │   └── Date_Picker_Knowledge_Base.md        # DatePicker 组件知识库
 │   ├── refresh/
 │   │   └── Refresh_Knowledge_Base.md           # Refresh 组件知识库
 │   ├── sheet/
│   │   └── Sheet_Knowledge_Base_CN.md        # Sheet 组件知识库
│   ├── scroll/
│   │   └── Scroll_Knowledge_Base.md            # Scroll 组件知识库
│   ├── search/
│   │   └── Search_Knowledge_Base_CN.md         # Search 组件知识库
│   ├── lazy_layout/
│   │   └── LazyGrid_Knowledge_Base.md          # LazyGrid 组件知识库
│   ├── text/
│   │   └── Text_Knowledge_Base_CN.md            # Text 组件知识库
│   ├── text_clock/
│   │   └── TextClock_Knowledge_Base_CN.md       # TextClock 组件知识库
│   ├── text_picker/
│   │   └── Text_Picker_Knowledge_Base.md        # TextPicker 组件知识库
│   ├── texttimer/
│   │   └── TextTimer_Knowledge_Base_CN.md        # TextTimer 组件知识库
│   ├── time_picker/
│   │   └── Time_Picker_Knowledge_Base.md        # TimePicker 组件知识库
│   └── waterflow/
│       └── WaterFlow_Knowledge_Base.md         # WaterFlow 组件知识库
└── syntax/               # Syntax 语法模块知识库
    ├── Syntax_Architecture_Overview.md         # Syntax 模块架构总览
    ├── ForEach_Knowledge_Base.md               # ForEach 组件知识库
    ├── LazyForEach_Knowledge_Base.md           # LazyForEach 组件知识库
    ├── Repeat_Knowledge_Base.md                # Repeat 组件知识库
    ├── RepeatVirtualScroll_Knowledge_Base.md   # RepeatVirtualScroll 组件知识库
    ├── Conditional_Rendering_Guide.md          # 条件渲染专题（IfElse）
    └── Special_Syntax_Components.md            # 特殊语法组件（WithTheme/ContentSlot）
```

## 现有文档

### CJ Frontend 知识库

**位置**: `cj_frontend/CJ_Frontend_Guide.md`

**综合指南** - Cangjie 语言桥接层的知识库

**文档内容**：

- **概述**: CJ Frontend 定位、与其他 Frontend 对比、适用场景
- **四层架构**: Frontend、FFI Interface、CppView、Runtime 层详解
- **FFI 设计模式**: extern "C" 边界、命名规范、数据类型转换
- **134 个组件**: 完整的 FFI 接口覆盖（布局、基础、高级组件）
- **双架构支持**: 经典架构 vs NG 架构对比与迁移指南
- **数据流与生命周期**: 组件创建流程、页面生命周期、数据流向分析
- **最佳实践**: 内存管理、线程安全、性能优化、常见陷阱与解决方案
- **调试指南**: 日志系统、DumpInfo、常见问题排查、性能分析工具

**适用场景**：

- 使用 Cangjie 语言开发 ArkUI 应用
- 理解 CJ Frontend 桥接层架构
- 查找组件 FFI 接口定义
- 学习 FFI 设计模式和最佳实践
- 排查 CJ Frontend 相关问题

**代码规模**：

- 359+ 个源文件
- 2067+ 个 FFI 导出函数
- 134 个 ArkUI 组件支持

---

### ArkUI SDK API Knowledge Base

**位置**: `sdk/ArkUI_SDK_API_Knowledge_Base.md`

**完整指南** - OpenHarmony ArkUI SDK API 对外接口的完整分析文档

**包含内容**：

- **目录结构概览**: 298 个 API 定义文件的完整分类
- **核心 Node API**: FrameNode、BuilderNode、RenderNode 的详细说明和实现位置
- **图形类型系统**: Graphics.d.ts 中的所有绘图类型（Size、Position、Matrix4 等）
- **组件 API 分类**: 96 个组件按功能分类（基础、容器、选择器、形状、媒体等）
- **Static vs Dynamic API**: 声明式 vs 命令式 API 的对比和使用场景
- **状态管理**: @State、@Prop、@Link 等装饰器和存储系统详解
- **与 ace_engine 的对应关系**: SDK API 到实现层的完整映射（含文件路径对照表）
- **组件知识库索引**: 26 个组件的知识库快速跳转链接

**统计数据**：
- 总 API 定义文件: 298 个
- Modifier 类: 76 个
- Component 接口: 129 个
- 基础组件: 15 个
- 容器组件: 27 个
- 选择器组件: 9 个
- 形状组件: 7 个
- 媒体组件: 4 个
- 数据展示组件: 7 个
- 富文本组件: 4 个
- 高级组件: 19+ 个

**适用场景**：
- 理解 ArkUI SDK 的对外 API 结构和分类体系
- 查找组件对应的 ace_engine 实现位置和源码
- 学习 Static API 和 Dynamic API 的使用方法和区别
- 掌握 SDK API 到实现层的完整映射关系
- 快速跳转到组件知识库进行深入学习
- ace_engine 开发者理解 SDK API 设计和组件开发指导

**相关资源**：
- SDK API 目录: `OpenHarmony/interface/sdk-js/api/arkui/`
- ace_engine 实现层: `OpenHarmony/foundation/arkui/ace_engine/`

---

### Component API Knowledge Base

**位置**: `sdk/Component_API_Knowledge_Base_CN.md`

**组件 API 指南** - OpenHarmony ArkUI 组件 API (`@internal/component/ets`) 的完整分析文档

**包含内容**：

- **概述**：组件 API 定位、与公开 API 的区别、代码规模统计
- **公开 API vs 组件 API**：目录结构对比、文件命名对比、使用场景对比
- **组件 API 分类**：120+ 个组件按功能分类（基础、容器、选择器、形状、媒体等）
- **特殊文件说明**：通用类型文件、通用 API 文件、系统组件文件
- **类型定义规范**：JSDoc 标签说明（@since、@crossplatform、@form、@atomicservice）、版本兼容性处理
- **使用指南**：查找组件类型定义、理解类型定义、版本兼容性检查
- **常见问题**：公开 API 和组件 API 的关系、为什么需要组件 API、动态导入说明

**统计数据**：
- 总文件数: 137 个 `.d.ts` 文件
- 总代码行数: 184,823 行
- 组件类型定义: 120+ 个
- 版本范围: API 7 - API 23

**适用场景**：
- 理解 ArkUI 框架内部的类型定义组织方式
- 区分公开 API 与组件 API 的差异
- 查找组件和接口的类型定义文件
- 查询 API 从哪个版本开始支持
- 框架内部开发和维护参考

**相关资源**：
- 组件 API 目录: `OpenHarmony/interface/sdk-js/api/@internal/component/ets/`
- ArkUI SDK API 知识库: [ArkUI_SDK_API_Knowledge_Base.md](./sdk/ArkUI_SDK_API_Knowledge_Base.md)

---

### Gesture System Knowledge Base

**位置**: `common/interaction/Gesture_Knowledge_Base_CN.md`

**完整指南** - 手势识别系统的基础层知识库

**包含内容**：

- **概述**: 手势系统定位、技术架构、与拖拽系统的关系
- **系统架构**: 完整的调用链（输入事件 → 手势识别器 → 手势仲裁 → 回调触发）
- **核心类继承关系**: NGGestureRecognizer、MultiFingersRecognizer、各种识别器
- **手势识别器详解**:
  - 基础手势: ClickRecognizer、TapRecognizer、LongPressRecognizer
  - 滑动手势: PanRecognizer、SwipeRecognizer
  - 缩放旋转: PinchRecognizer、RotationRecognizer
  - 手势组合: ParallelRecognizer、SequencedRecognizer、ExclusiveRecognizer
- **手势仲裁器**: GestureReferee、GestureScope、仲裁流程
- **完整 API 清单**: 基础手势、滑动手势、缩放旋转手势、手势组合 API
- **核心实现细节**: 速度追踪算法（最小二乘法）、距离计算算法、手势仲裁机制
- **使用示例**: 点击、长按、滑动、捏合、手势组合等 6+ 完整示例
- **调试指南**: 手势识别调试、手势冲突解决、性能优化

**代码规模**：

- 核心文件: 约 40 个文件
- 核心代码: 约 15,000+ 行 C++ 代码
- 手势识别器: 7 种基础手势 + 3 种组合模式

**与拖拽系统的关系**:

- **拖拽启动**: 基于 Pan 手势识别,当滑动距离超过阈值时触发拖拽
- **拖拽移动**: 延续 Pan 手势的 Move 事件处理
- **拖拽释放**: 对应 Pan 手势的 Up 事件

**适用场景**：手势系统开发、手势识别实现、手势仲裁调试时参考

**相关文档**: [拖拽系统知识库](./Drag_Drop_Knowledge_Base_CN.md)（基于手势扩展的进阶层）

---

### Drag & Drop System Knowledge Base

**位置**: `common/interaction/Drag_Drop_Knowledge_Base_CN.md`

**完整指南** - 拖拽系统的进阶层知识库（基于手势系统）

**包含内容**：

- **概述**: 拖拽系统定位、与手势系统的关系、技术架构
- **系统架构**: 完整的拖拽流程（启动 → 创建预览 → 移动 → 释放）
- **拖拽管理器**: DragDropManager、拖拽事件处理
- **拖拽状态机**: DragDropInitiatingStateMachine（Idle→Press→Ready→Lifting→Moving）
- **拖拽预览系统**: DragPreviewOption、PixelMap 截图、自定义预览、拖拽动画
- **拖拽代理**: DragDropProxy、OverlayWindow 管理
- **UDMF 数据传递**: 统一数据管理框架、跨应用拖拽
- **Spring Loading**: 弹性加载检测、边缘自动滚动
- **完整 API 清单**: 基础拖拽、拖拽预览、UDMF 数据 API
- **核心实现细节**: 拖拽启动检测、拖拽预览生成、UDMF 数据传递、Spring Loading 机制
- **使用示例**: 简单文本拖拽、自定义预览、列表拖拽排序、跨应用拖拽等 4+ 完整示例
- **调试指南**: 拖拽调试、常见问题排查、性能优化

**代码规模**：

- 核心文件: 约 20 个文件
- 核心代码: 约 10,000+ 行 C++ 代码
- 拖拽状态: 6 个主要状态

**依赖关系**:

- **前置知识**: 手势系统（[Gesture_Knowledge_Base_CN.md](./Gesture_Knowledge_Base_CN.md)）
- **基础**: Pan 手势识别
- **扩展**: 拖拽预览、拖拽状态机、UDMF 数据传递

**适用场景**：拖拽系统开发、拖拽功能实现、跨应用拖拽时参考

**相关文档**: [手势系统知识库](./Gesture_Knowledge_Base_CN.md)（拖拽系统的基础）

---

### Menu Component Knowledge Base

**位置**: `pattern/menu/Menu_Knowledge_Base.md`

**完整指南** - Menu 组件的开发、测试和调试参考文档

**包含内容**：

- Legacy Menu vs NG Menu 架构对比
- JS bridge 集成（JsBindMenu, JsBindContextMenu）
- Pattern/Model/Property/Algorithm 层分析
- 生命周期管理和事件处理
- 布局算法和绘制方法
- 测试覆盖和调试指南

**适用场景**：Menu 组件开发、测试、问题排查时参考

---

### Grid Component Knowledge Base

**位置**: `pattern/grid/Grid_Knowledge_Base_CN.md`

**完整指南** - Grid 网格布局组件的开发、测试和调试参考文档

**包含内容**：

- **概述**: Grid 组件定位、五种布局算法模式、技术架构
- **核心类详解**: GridPattern、GridLayoutInfo、GridModelNG 类结构与职责
- **布局算法体系**: 自适应/静态/自定义/不规则/可滚动五种算法详解
- **GridLayoutInfo**: 网格矩阵、行高映射、项目位置等核心数据结构
- **GridItem 子组件**: 行列跨度、生效规则、性能优化建议
- **完整 API 清单**: ArkTS 和 C++ API 完整列表
- **事件系统**: 滚动事件、拖拽事件、焦点管理
- **滚动控制**: Scroller 接口、ScrollAlign 枚举
- **使用示例**: 5 种布局模式完整示例代码
- **性能优化**: 虚拟滚动、行跳跃、预加载机制
- **测试覆盖**: 测试基类、测试目录结构、运行方法
- **调试指南**: DumpInfo、常见问题排查

**适用场景**：Grid 组件开发、网格布局实现、不规则跨行列项目处理时参考

**代码规模**：

- 核心文件: 约 70 个
- 核心代码: 约 25,000+ 行 C++ 代码
- 测试文件: 约 30 个

---

### Flex Component Knowledge Base

**位置**: `pattern/flex/Flex_Knowledge_Base.md`

**完整指南** - Flex 弹性布局组件（Row/Column/Wrap）的开发、测试和调试参考文档

**包含内容**：

- Flex 布局架构（Pattern、Algorithm、Model 三层）
- Flex 弹性容器与 Linear 线性容器（Row/Column）分类体系
- FlexDirection 方向枚举（Row/Column/RowReverse/ColumnReverse）及 RTL/LTR 支持
- FlexAlign 对齐方式（Start/Center/End/SpaceBetween/SpaceAround/SpaceEvenly/Baseline/Stretch）
- FlexItem 属性（flex-grow、flex-shrink、flex-basis、align-self）
- layoutWeight 权重分配机制（FirstMeasure/SecondMeasure/FinalMeasure）
- constraintSize 约束尺寸（LayoutConstraintF、minSize、maxSize）
- 二次布局机制（Two-Pass Measure）详解
- 主轴和交叉轴空间分配算法
- Flex Grow/Shrink 机制及默认值差异（Flex vs Linear）
- Baseline 对齐实现
- Blank 空白元素特殊处理
- 显示优先级（Display Priority）机制
- Measure-Layout 配对验证
- 完整布局流程 Mermaid 序列图（Measure/Layout/二次测量）
- Wrap 换行布局（Horizontal/Vertical）
- 完整的 ArkTS 和 C++ API 清单
- 性能优化（二次布局影响分析、嵌套布局性能对比）
- 常见问题和调试工具

**适用场景**：Flex/Row/Column/Wrap 组件开发、弹性布局实现、布局算法优化时参考

---

### Refresh Component Knowledge Base

**位置**: `pattern/refresh/Refresh_Knowledge_Base.md`

**完整指南** - Refresh 组件的开发、测试和调试参考文档

**包含内容**：

- 下拉刷新手势处理和状态转换
- 嵌套滚动协调机制
- 自定义刷新 UI（Custom Builder）支持
- 弹簧动画和 FRC 性能优化
- API 10- 和 API 11+ 版本兼容处理
- 键盘快捷键支持（F5 / Ctrl+R）
- 完整的 ArkTS 和 C++ API 清单
- 6 个实用使用示例和调试指南

**适用场景**：Refresh 组件开发、下拉刷新功能实现、嵌套滚动问题排查时参考

---

### Sheet Component Knowledge Base

**位置**: `pattern/sheet/Sheet_Knowledge_Base_CN.md`

**完整指南** - Sheet 半模态组件的开发、测试和调试参考文档

**包含内容**：

- 9 种半模态类型（底部、居中、侧边、气泡、内容覆盖等）
- 状态模式 + 桥接模式架构设计
- 自动类型选择（根据屏幕尺寸和方向）
- 拖拽交互和弹簧动画
- 多档位高度（Detents）支持
- 嵌套滚动协调机制
- 键盘避让策略（5 种模式）
- 完整的生命周期回调
- 6 个实用使用示例和调试指南

**适用场景**：Sheet 组件开发、半模态面板实现、表单输入场景、键盘避让问题排查时参考

---

### Counter Component Knowledge Base

**位置**: `pattern/counter/Counter_Knowledge_Base.md`

**完整指南** - Counter 组件的开发、测试和调试参考文档

**包含内容**：

- 计数器状态管理
- 增减按钮处理
- 输入验证和边界控制
- 事件回调机制

**适用场景**：Counter 组件开发、表单输入场景参考

---

### Gauge Component Knowledge Base

**位置**: `pattern/gauge/Gauge_Knowledge_Base.md`

**完整指南** - Gauge 仪表盘组件的开发、测试和调试参考文档

**包含内容**：

- 仪表盘绘制算法
- 数据类型支持（Value、Gradient、DataGauge）
- 颜色配置和主题
- 指针动画效果

**适用场景**：Gauge 组件开发、数据可视化场景参考

---

### Marquee Component Knowledge Base

**位置**: `pattern/marquee/Marquee_Knowledge_Base.md`

**完整指南** - Marquee 跑马灯组件的开发、测试和调试参考文档

**包含内容**：

- 文本滚动实现
- 速度控制机制
- 方向配置（横向/纵向）
- 动画循环处理

**适用场景**：Marquee 组件开发、文本动画场景参考

---

### Scroll Component Knowledge Base

**位置**: `pattern/scroll/Scroll_Knowledge_Base.md`

**完整指南** - Scroll 滚动组件的开发、测试和调试参考文档

**包含内容**：

- 滚动位置计算
- 边缘效果（EdgeEffect）
- 嵌套滚动协调
- 滚动条渲染

**适用场景**：Scroll 组件开发、滚动容器实现参考

---

### LazyGrid Component Knowledge Base

**位置**: `pattern/lazy_layout/LazyGrid_Knowledge_Base.md`

**完整指南** - LazyGrid 懒加载网格布局组件的开发、测试和调试参考文档

**包含内容**：

- 懒加载机制（仅渲染可见区域+预测区域）
- 位置缓存机制（快速滚动定位）
- 预测性渲染（利用空闲时间预渲染）
- 网格列计算（LanesFloor/LanesCeil）
- 正向/反向布局方向
- WaterFlow 父容器验证
- 焦点管理（ScopeFocus）
- 完整的 ArkTS 和 C++ API 清单

**适用场景**：LazyGrid 组件开发、大数据量网格布局实现、性能优化时参考

---

### WaterFlow Component Knowledge Base

**位置**: `pattern/waterflow/WaterFlow_Knowledge_Base.md`

**完整指南** - WaterFlow 瀑布流组件的开发、测试和调试参考文档

**包含内容**：

- 瀑布流布局算法
- 列数动态调整
- Item 排列策略
- 性能优化方案

**适用场景**：WaterFlow 组件开发、不规则网格布局参考

---

### QRCode Component Knowledge Base

**位置**: `pattern/qrcode/QRCode_Knowledge_Base.md`

**完整指南** - QRCode 组件的开发、测试和调试参考文档

**包含内容**：

- 组件概述和核心功能
- 目录结构和架构设计
- Pattern/Model/Property/Modifier 四层架构详解
- 生命周期管理（OnAttachToFrameNode、OnModifyDone、OnDirtyLayoutWrapperSwap、OnColorConfigurationUpdate）
- 布局算法（正方形布局约束、API 11 差异处理）
- 绘制流程（qrcodegen 库集成、位图生成、Canvas 绘制）
- Bridge 层集成（动态加载、NAPI 接口）
- 测试覆盖和常见问题

**适用场景**：QRCode 组件开发、测试、问题排查时参考

---

### Syntax Module Knowledge Base

**位置**: `syntax/`

**Syntax 模块知识库** - ArkUI 语法结构和控制流组件的完整知识库

Syntax 模块是 ACE Engine 中处理 UI 语法特性的核心模块，包含循环组件、条件渲染、主题作用域、内容插槽等多个子组件。

#### 1. Syntax Architecture Overview

**位置**: `syntax/Syntax_Architecture_Overview.md`

**架构总览** - Syntax 模块的导航入口文档

**包含内容**：

- **模块概述**：Syntax 模块定位、职责、核心特性
- **组件分类体系**：按功能、性能、数据驱动方式分类
- **核心基类详解**：UINode、ForEachBaseNode、SyntaxItem 继承关系
- **循环组件对比**：ForEach、LazyForEach、Repeat、RepeatVirtualScroll 独立对比
- **前端桥接层集成**：声明式前端和 CJ 前端的桥接实现
- **设计模式总结**：模板方法、策略、观察者、Builder、享元模式
- **性能特性对比**：内存占用、初始化速度、滚动性能、更新性能
- **快速导航**：按场景、性能、数据特性选择组件的决策树
- **源码规模统计**：21 个文件，6000 行代码的详细统计

**适用场景**：
- 快速了解 Syntax 模块全貌
- 根据场景选择合适的循环组件
- 查找特定功能的实现位置

**代码规模**：
- 21 个源文件
- 6000+ 行 C++ 代码
- 4 个循环组件 + 2 个特殊组件

---

#### 2. ForEach Component Knowledge Base

**位置**: `syntax/ForEach_Knowledge_Base.md`

**ForEach 组件知识库** - 数据驱动的循环渲染组件

**包含内容**：

- **概述**：ForEach 组件定位、核心功能、适用场景
- **完整调用链**：ArkTS → JS Bridge → Pattern Node
- **类继承关系**：ForEachNode 类结构
- **核心功能**：数据驱动更新、差分算法、ID 管理、拖拽排序
- **布局算法**：Measure/Layout 流程
- **事件处理**：滚动事件、点击事件
- **完整 API 清单**：ArkTS 和 C++ API
- **使用示例**：基本用法、数据更新、拖拽示例（5+ 完整示例）
- **调试指南**：日志系统、常见问题排查
- **最佳实践**：性能优化、keyGenerator 设计

**代码规模**：
- ForEach: 16,144 行

---

#### 3. LazyForEach Component Knowledge Base

**位置**: `syntax/LazyForEach_Knowledge_Base.md`

**LazyForEach 组件知识库** - 懒加载循环渲染组件

**包含内容**：

- **概述**：LazyForEach 组件定位、懒加载原理、适用场景
- **完整调用链**：ArkTS → JS Bridge → Pattern Node → Builder
- **类继承关系**：LazyForEachNode 类结构
- **核心功能**：IDataSource 接口、按需渲染、缓存策略
- **懒加载机制**：仅渲染可见区域、预测性渲染
- **布局算法**：LazyForEachBuilder 算法
- **完整 API 清单**：ArkTS 和 C++ API
- **IDataSource 接口定义**：完整接口文档
- **使用示例**：基本用法、自定义数据源、缓存配置（5+ 完整示例）
- **调试指南**：缓存分析、性能调优
- **最佳实践**：数据源设计、缓存策略、内存管理

**代码规模**：
- LazyForEach: 35,568 行
- LazyForEachBuilder: 62,289 行

---

#### 4. Repeat Component Knowledge Base

**位置**: `syntax/Repeat_Knowledge_Base.md`

**Repeat 组件知识库** - 简单重复渲染组件

**包含内容**：

- **概述**：Repeat 组件定位、核心功能、适用场景
- **完整调用链**：ArkTS → JS Bridge → Pattern Node
- **类继承关系**：RepeatNode 类结构
- **核心功能**：简单重复渲染、数值参数驱动
- **布局算法**：Measure/Layout 流程
- **完整 API 清单**：ArkTS 和 C++ API
- **使用示例**：基本用法、嵌套 Repeat（3+ 完整示例）
- **调试指南**：常见问题排查
- **最佳实践**：性能优化、使用场景选择

**代码规模**：
- Repeat: 10,656 行

---

#### 5. RepeatVirtualScroll Component Knowledge Base

**位置**: `syntax/RepeatVirtualScroll_Knowledge_Base.md`

**RepeatVirtualScroll 组件知识库** - 虚拟滚动组件

**包含内容**：

- **概述**：RepeatVirtualScroll 组件定位、核心功能、适用场景
- **完整调用链**：ArkTS → JS Bridge → Pattern Node → Cache System
- **类继承关系**：RepeatVirtualScrollNode 类结构
- **核心功能**：虚拟滚动、L1/L2 缓存、懒加载机制、API 16+ 特性
- **缓存系统详解**：L1 缓存、L2 缓存、缓存置换策略
- **布局算法**：Measure/Layout 流程、位置计算
- **版本兼容性**：API 15 vs API 16+ 差异
- **完整 API 清单**：ArkTS 和 C++ API
- **使用示例**：基本用法、缓存配置、性能优化（5+ 完整示例）
- **调试指南**：缓存分析、性能分析工具
- **最佳实践**：缓存策略、性能优化、大数据量处理

**代码规模**：
- RepeatVirtualScroll: 48,573 行
- RepeatVirtualScrollCaches: 27,695 行

---

#### 6. Conditional Rendering Guide

**位置**: `syntax/Conditional_Rendering_Guide.md`

**条件渲染专题** - IfElse 组件完整指南

**包含内容**：

- **IfElse 组件详解**：组件定位、核心数据结构、SetBranchId 流程、TryRetake 机制
- **分支管理机制**：branchId 标识、分支切换流程、节点复用策略
- **状态保留与复用**：TryRetake 详解、CollectRetakenNodes、几何过渡支持
- **使用示例**：基本用法、多分支条件、状态保留示例（5 个完整示例）
- **性能优化**：分支切换性能、节点复用优化、动画优化建议
- **常见问题**：切换不生效、状态丢失、性能问题、动画问题排查
- **与 if-else 语法对比**：ArkTS vs JavaScript、与其他条件渲染方案对比

**适用场景**：
- 条件渲染功能开发
- 多分支切换场景
- 状态保留需求
- 动画过渡优化

**代码规模**：
- IfElseNode: 7,321 行

---

#### 7. Special Syntax Components

**位置**: `syntax/Special_Syntax_Components.md`

**特殊语法组件指南** - WithTheme/ContentSlot 完整指南

**包含内容**：

- **WithTheme 组件**：主题作用域管理、作用域隔离原理、销毁回调机制
- **ContentSlot 组件**：内容插槽管理、动态内容附加/分离、生命周期管理
- **工具类说明**：NodeContent、SyntaxItem、ShallowBuilder、NodeContentPeer
- **使用场景**：主题切换、动态内容切换、懒加载优化、生命周期管理
- **最佳实践**：WithTheme 性能优化、ContentSlot 内容复用、ShallowBuilder 延迟渲染
- **常见问题排查**：主题切换、嵌套作用域、内容显示、状态丢失等问题

**适用场景**：
- 多主题共存场景
- 动态内容切换
- 大列表性能优化
- 精确资源控制

**代码规模**：
- WithThemeNode: 4,387 行
- ContentSlotNode: 4,143 行

---

## 文档分类

### 架构设计类

- **CJ Frontend 知识库** (`cj_frontend/CJ_Frontend_Guide.md`) - Cangjie 桥接层完整架构（综合指南）
  - 四层架构设计（Frontend、FFI、CppView、Runtime）
  - FFI 设计模式和接口规范
  - 双架构支持（经典 vs NG）
  - 组件 FFI 接口参考（134 个组件快速查找）
  - 数据流与生命周期分析
  - 最佳实践与调试指南

- **Syntax 模块知识库** (`syntax/Syntax_Architecture_Overview.md`) - Syntax 语法模块架构总览
  - 模块定位和职责
  - 组件分类体系
  - 核心基类详解
  - 前端桥接层集成
  - 设计模式总结
  - 性能特性对比

- **ArkUI SDK API 知识库** (`sdk/ArkUI_SDK_API_Knowledge_Base.md`) - SDK API 完整分析
  - 298 个 API 定义文件分类
  - 核心 Node API 详解
  - 图形类型系统
  - Static vs Dynamic API 对比
  - 状态管理机制
  - SDK 到 ace_engine 映射

- 组件分层设计
- 框架核心概念
- 设计模式应用

### 组件知识类

- 组件深度分析文档
- 组件对比研究
- 组件最佳实践

### 最佳实践类

- 常见问题解决方案
- 性能优化建议
- 调试技巧

## 贡献指南

添加新的知识库文档时，请遵循以下原则：

1. **文件命名**：使用清晰的英文文件名，如 `XXX_Knowledge_Base.md`
2. **文档格式**：使用 Markdown 格式
3. **内容组织**：提供清晰的目录结构和导航
4. **示例代码**：包含可运行的示例代码，并标注源码位置
5. **维护更新**：定期更新文档以保持与代码同步

## 相关资源

- [CLAUDE.md](../CLAUDE.md) - Claude Code 项目级指导文档
- [docs/](../docs/) - 项目文档目录
- [TDD Skill](../skills/tdd/) - TDD 测试驱动开发指南
