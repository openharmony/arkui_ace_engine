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

**统计数据**（截至 2026-02-05）：

- 总知识库文档: 24 个
- 组件知识库: 22 个
- SDK API 知识库: 1 个
- CJ Frontend 知识库: 1 个
- 覆盖组件: 22 个
- 检索关键词: 220+ 个

---

## 目录结构

```
knowledge_base/
├── README.md              # 本文件，知识库索引和说明
├── cj_frontend/           # CJ Frontend 桥接层知识库
│   └── CJ_Frontend_Guide.md                   # 综合指南
├── sdk/                   # SDK 相关知识库
│   └── ArkUI_SDK_API_Knowledge_Base.md  # ArkUI SDK API 完整分析
└── pattern/               # 组件模式知识库
    ├── badge/
    │   └── Badge_Knowledge_Base_CN.md         # Badge 组件知识库
    ├── calendar_picker/
    │   └── Calendar_Picker_Knowledge_Base.md  # CalendarPicker 组件知识库
    ├── container_picker/
    │   └── Container_Picker_Knowledge_Base.md # ContainerPicker 组件知识库
    ├── counter/
    │   └── Counter_Knowledge_Base.md        # Counter 组件知识库
    ├── gauge/
    │   └── Gauge_Knowledge_Base.md           # Gauge 组件知识库
    ├── image/
    │   └── Image_Knowledge_Base.md           # Image 组件知识库
    ├── image_animator/
    │   └── Image_Animator_Knowledge_Base.md  # ImageAnimator 组件知识库
    ├── marquee/
    │   └── Marquee_Knowledge_Base.md         # Marquee 组件知识库
    ├── menu/
    │   └── Menu_Knowledge_Base.md            # Menu 组件知识库
    ├── picker/
    │   └── Date_Picker_Knowledge_Base.md     # DatePicker 组件知识库
    ├── refresh/
    │   └── Refresh_Knowledge_Base.md         # Refresh 组件知识库
    ├── sheet/
    │   └── Sheet_Knowledge_Base_CN.md        # Sheet 组件知识库
    ├── scroll/
    │   └── Scroll_Knowledge_Base.md          # Scroll 组件知识库
    ├── search/
    │   └── Search_Knowledge_Base_CN.md       # Search 组件知识库
    ├── lazy_layout/
    │   └── LazyGrid_Knowledge_Base.md       # LazyGrid 组件知识库
    ├── text/
    │   └── Text_Knowledge_Base_CN.md          # Text 组件知识库
    ├── text_clock/
    │   └── TextClock_Knowledge_Base_CN.md     # TextClock 组件知识库
    ├── text_picker/
    │   └── Text_Picker_Knowledge_Base.md      # TextPicker 组件知识库
    ├── texttimer/
    │   └── TextTimer_Knowledge_Base_CN.md      # TextTimer 组件知识库
    ├── time_picker/
    │   └── Time_Picker_Knowledge_Base.md      # TimePicker 组件知识库
    └── waterflow/
        └── WaterFlow_Knowledge_Base.md       # WaterFlow 组件知识库
    └── qrcode/
        └── QRCode_Knowledge_Base.md          # QRCode 组件知识库
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

### Counter Component Knowledge Base

**位置**: `pattern/counter/Counter_Knowledge_Base.md`

**完整指南** - Counter 组件的开发、测试和调试参考文档

**包含内容**：

- 计数器状态管理
- 增减按钮处理
- 输入验证和边界控制
- 事件回调机制

**适用场景**：Counter 组件开发、表单输入场景参考

### Gauge Component Knowledge Base

**位置**: `pattern/gauge/Gauge_Knowledge_Base.md`

**完整指南** - Gauge 仪表盘组件的开发、测试和调试参考文档

**包含内容**：

- 仪表盘绘制算法
- 数据类型支持（Value、Gradient、DataGauge）
- 颜色配置和主题
- 指针动画效果

**适用场景**：Gauge 组件开发、数据可视化场景参考

### Marquee Component Knowledge Base

**位置**: `pattern/marquee/Marquee_Knowledge_Base.md`

**完整指南** - Marquee 跑马灯组件的开发、测试和调试参考文档

**包含内容**：

- 文本滚动实现
- 速度控制机制
- 方向配置（横向/纵向）
- 动画循环处理

**适用场景**：Marquee 组件开发、文本动画场景参考

### Scroll Component Knowledge Base

**位置**: `pattern/scroll/Scroll_Knowledge_Base.md`

**完整指南** - Scroll 滚动组件的开发、测试和调试参考文档

**包含内容**：

- 滚动位置计算
- 边缘效果（EdgeEffect）
- 嵌套滚动协调
- 滚动条渲染

**适用场景**：Scroll 组件开发、滚动容器实现参考

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

### WaterFlow Component Knowledge Base

**位置**: `pattern/waterflow/WaterFlow_Knowledge_Base.md`

**完整指南** - WaterFlow 瀑布流组件的开发、测试和调试参考文档

**包含内容**：

- 瀑布流布局算法
- 列数动态调整
- Item 排列策略
- 性能优化方案

**适用场景**：WaterFlow 组件开发、不规则网格布局参考

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
- **组件知识库索引**: 22 个组件的知识库快速跳转链接

**统计数据**：
- 总 API 定义文件: 298 个
- Modifier 类: 76 个
- Component 接口: 129 个
- 基础组件: 15 个（3 个有知识库）
- 容器组件: 27 个（4 个有知识库）
- 选择器组件: 9 个（6 个有知识库）
- 形状组件: 7 个
- 媒体组件: 4 个（2 个有知识库）
- 数据展示组件: 7 个（4 个有知识库）
- 富文本组件: 4 个
- 高级组件: 19+ 个（3 个有知识库）

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

## 文档分类

### 架构设计类

- **CJ Frontend 知识库** (`cj_frontend/CJ_Frontend_Guide.md`) - Cangjie 桥接层完整架构（综合指南）
  - 四层架构设计（Frontend、FFI、CppView、Runtime）
  - FFI 设计模式和接口规范
  - 双架构支持（经典 vs NG）
  - 组件 FFI 接口参考（134 个组件快速查找）
  - 数据流与生命周期分析
  - 最佳实践与调试指南
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
