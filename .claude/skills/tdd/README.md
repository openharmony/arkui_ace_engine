# TDD Writing Skill

用于编写高质量 TDD 测试用例的 Claude Code Skill，专注于 NG Component Pattern 方法的测试驱动开发。

## 功能特性

- ✅ 直接方法调用测试（避免间接触发）
- ✅ 状态重置最佳实践
- ✅ API 名称验证（使用 Grep/Read 工具）
- ✅ 分支覆盖测试（if/else 成对测试）
- ✅ 无魔鬼数字规范（使用命名常量）
- ✅ 逻辑描述注释（避免行号引用）
- ✅ 强制自检清单

## 核心原则

### 1. Direct Method Invocation
直接调用目标方法，而非通过间接触发

### 2. State Reset
在调用目标方法前重置干扰状态

### 3. API Verification
使用 Grep/Read 工具验证方法名，禁止猜测

### 4. Branch Coverage
为 if/else 分支编写成对测试用例

### 5. No Line Numbers in Comments
注释描述逻辑行为，不使用物理行号

### 6. No Documentation-Only Tests
每个测试用例必须有实际测试逻辑

### 7. No Magic Numbers
使用命名常量替代硬编码数字

## 目录结构

```
tdd/
├── SKILL.md                              # Skill 主文件
├── README.md                             # 本文件
├── examples/
│   └── menu-pattern-test.md              # Menu Pattern 测试示例
├── references/
│   ├── test-template.md                 # 测试用例模板
│   ├── common-pitfalls.md               # 常见陷阱及解决方案
│   └── self-checklist.md                # 强制自检清单
└── scripts/                              # 辅助脚本（预留）
```

## 使用方法

### 与 Claude 对话

直接向 Claude 提出请求：

```
"为 MenuPattern 的 OnModifyDone 方法编写 TDD 测试"
"为 MenuItemPattern 添加单元测试"
"检查这个测试用例是否符合 TDD 规范"
"为 XXX 方法编写分支覆盖测试"
```

### 适用场景

- ✅ NG Component Pattern 方法测试
- ✅ OnModifyDone() 测试
- ✅ OnDirtyLayoutWrapperSwap() 测试
- ✅ 布局算法测试
- ✅ 事件处理测试

### 不适用场景

- ❌ 集成测试（使用其他测试框架）
- ❌ 性能测试（使用 benchmark）
- ❌ UI 自动化测试（使用 UI 测试框架）

## 测试模板

完整的测试用例模板请参考：[references/test-template.md](references/test-template.md)

## 参考文档

- **测试模板** - `references/test-template.md`
- **常见陷阱** - `references/common-pitfalls.md`
- **自检清单** - `references/self-checklist.md`
- **Menu 示例** - `examples/menu-pattern-test.md`

## Skill 特性

### 渐进式加载

1. **Metadata** - 始终加载（本 README）
2. **SKILL.md** - 触发时加载（核心原则）
3. **References** - 按需加载（详细文档）

### 触发条件

当用户提出以下请求时触发此 Skill：
- "编写 TDD 测试"
- "为 XXX 方法写单元测试"
- "测试覆盖率"
- "分支测试"
- "Pattern 方法测试"
- "OnModifyDone 测试"

## 开发者信息

- **位置**: `ace_engine/.claude/skills/tdd/`
- **版本**: 1.0.0
- **依赖**: gtest 测试框架
- **参考**: CLAUDE.md TDD Writing Guidelines

## 更新日志

### v1.0.0 (2025-01-27)
- ✅ 初始版本
- ✅ 7 条核心原则
- ✅ 测试用例模板
- ✅ 常见陷阱及解决方案
- ✅ 强制自检清单
- ✅ Menu Pattern 测试示例

## 待办事项

- [ ] 添加更多组件 Pattern 测试示例
- [ ] 创建测试辅助脚本
- [ ] 添加测试覆盖率分析工具
