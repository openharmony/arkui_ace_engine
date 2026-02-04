# Knowledge Base

此目录用于存放 ArkUI ACE Engine 开发过程中的各种知识库文档。

## 目录结构

```
knowledge_base/
├── README.md              # 本文件，知识库索引和说明
└── pattern/               # 组件模式知识库
    ├── counter/
    │   └── Counter_Knowledge_Base.md   # Counter 组件知识库
    ├── gauge/
    │   └── Gauge_Knowledge_Base.md      # Gauge 组件知识库
    ├── marquee/
    │   └── Marquee_Knowledge_Base.md    # Marquee 组件知识库
    ├── menu/
    │   └── Menu_Knowledge_Base.md       # Menu 组件知识库
    ├── refresh/
    │   └── Refresh_Knowledge_Base.md    # Refresh 组件知识库
    ├── scroll/
    │   └── Scroll_Knowledge_Base.md     # Scroll 组件知识库
    ├── lazy_layout/
    │   └── LazyGrid_Knowledge_Base.md   # LazyGrid 组件知识库
    └── waterflow/
        └── WaterFlow_Knowledge_Base.md  # WaterFlow 组件知识库
    └── qrcode/
        └── QRCode_Knowledge_Base.md  # QRCode 组件知识库
```

## 现有文档

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

## 文档分类

### 组件知识类

- 组件深度分析文档
- 组件对比研究
- 组件最佳实践

### 架构设计类

- 组件分层设计
- 框架核心概念
- 设计模式应用

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
