# Knowledge Base

此目录用于存放 ArkUI ACE Engine 开发过程中的各种知识库文档。

## 目录结构

```
knowledge_base/
├── README.md              # 本文件，知识库索引和说明
└── pattern/               # 组件模式知识库
    ├── menu/
    │   └── Menu_Knowledge_Base.md       # Menu 组件知识库
    ├── scroll/
    │   └── Scroll_Knowledge_Base.md     # Scroll 组件知识库
    ├── gauge/
    │   └── Gauge_Knowledge_Base.md      # Gauge 组件知识库
    └── waterflow/
        └── WaterFlow_Knowledge_Base.md  # WaterFlow 组件知识库
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
