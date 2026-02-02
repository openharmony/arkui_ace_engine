# 强制自检清单

本文档提供编写 TDD 测试用例后的强制自检清单，确保测试用例质量。

## 自检清单

### 方法验证

- [ ] **所有调用的方法都存在**
  - 使用 Grep/Read 工具验证方法名
  - 禁止猜测方法名称
  - 示例：`grep -rn "ResetOuterBorder" frameworks/core/components_ng/render/`

- [ ] **方法签名与源码定义一致**
  - 返回值类型匹配
  - 入参类型、数量、默认值匹配
  - const 修饰符匹配

### 状态管理

- [ ] **状态已重置**
  - 在调用目标方法前重置所有干扰属性
  - 使用 `ResetXxx()` 方法重置整个属性组
  - 确保测试从干净状态开始

- [ ] **测试数据触发正确的分支**
  - HasPercentUnit() 等条件返回预期值
  - 测试数据配置正确
  - 数据类型符合方法要求

### 测试逻辑

- [ ] **断言符合分支行为**
  - Branch True: EXPECT_TRUE / EXPECT_TRUE(has_value)
  - Branch False: EXPECT_FALSE / EXPECT_FALSE(has_value)
  - 断言类型正确（EXPECT_EQ, EXPECT_GT 等）

- [ ] **测试用例独立**
  - 不依赖其他测试的执行顺序
  - 每个测试创建自己的测试数据
  - 无共享状态污染

### 代码规范

- [ ] **注释描述逻辑行为**
  - ✅ 使用 "when X happens, Y should occur"
  - ❌ 不使用 "at line 299"
  - 描述条件而非物理位置

- [ ] **无魔鬼数字**
  - 所有数值使用命名常量
  - 常量定义在匿名 namespace 中
  - 常量名称有明确语义

- [ ] **遵循测试文件结构和命名**
  - 测试类名：`XxxPatternTestNg`
  - 测试用例名：`XxxPattern_TestMethod_BranchName`
  - TestSize 使用正确（Level1/Level2/Level3）

### 测试完整性

- [ ] **每个测试用例有实际测试逻辑**
  - ❌ 禁止只有注释和 `EXPECT_TRUE(true)`
  - ✅ 必须包含真实的断言和验证

- [ ] **分支覆盖完整**
  - if/else 分支都编写了测试
  - 边界条件有测试覆盖
  - 异常路径有测试覆盖

## 快速检查脚本

```bash
# 检查测试文件中是否有魔鬼数字
grep -n "EXPECT_.*[^a-zA-Z_][0-9]\+" test_file.cpp

# 检查是否有 EXPECT_TRUE(true) 空测试
grep -n "EXPECT_TRUE(true)" test_file.cpp

# 检查注释中是否包含行号
grep -n "at line [0-9]" test_file.cpp
```

## 常见问题排查

### 问题 1：测试失败，返回意外值

**可能原因**：
1. 未重置状态
2. 测试数据配置错误
3. 调用了错误的方法（间接方法）

**解决方案**：
1. 添加 `renderContext->ResetXxx()` 调用
2. 验证测试数据的 HasPercentUnit() 等方法返回值
3. 直接调用目标方法

### 问题 2：编译错误，方法未找到

**可能原因**：
1. API 名称拼写错误
2. 方法不存在（猜测的名称）

**解决方案**：
1. 使用 Grep 搜索方法定义
2. 查阅头文件确认方法签名
3. 使用宏生成的方法名（如 ACE_DEFINE_PROPERTY_GROUP）

### 问题 3：测试相互干扰

**可能原因**：
1. 测试共享状态
2. 未在 SetUp/TearDown 中清理状态

**解决方案**：
1. 每个测试创建独立的测试数据
2. 在测试结束后清理状态
3. 避免使用静态成员变量存储测试状态

## 参考文档

- **测试模板** - `test-template.md`
- **常见陷阱** - `common-pitfalls.md`
- **示例代码** - `examples/menu-pattern-test.md`
- **完整指南** - `../SKILL.md`
