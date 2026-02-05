# 工具使用指南

## Glob 工具

文件模式匹配工具，用于按名称模式查找文件。

### 基本用法

```bash
# 查找所有 C++ 文件
Glob: "**/*.cpp"

# 查找特定组件文件
Glob: "**/text/**/*.cpp"

# 查找测试文件
Glob: "**/*_test.cpp"

# 查找头文件
Glob: "**/pattern/**/*.h"
```

### 常用模式

| 模式 | 说明 | 示例 |
|------|------|------|
| `**/*.cpp` | 所有 .cpp 文件 | 查找所有源文件 |
| `**/text/*` | text 目录下所有文件 | 查找 Text 组件文件 |
| `**/*pattern*` | 文件名包含 pattern | 查找 Pattern 层文件 |
| `**/*_test.cpp` | 测试文件 | 查找单元测试 |

### 实战示例

```bash
# 查找 Menu 组件的所有文件
Glob: "**/menu/*"

# 查找所有 Pattern 层实现
Glob: "**/pattern/*/*.cpp"

# 查找所有布局算法
Glob: "**/layout/*algorithm*.cpp"
```

---

## Grep 工具

强大的代码搜索工具，基于 ripgrep。

### 基本用法

```bash
# 搜索类定义
Grep: "class TextPattern" --type cpp

# 搜索方法调用
Grep: "OnModifyDone" --type cpp

# 搜索特定目录
Grep: "RefPtr" frameworks/core/components_ng/pattern/text/

# 不区分大小写
Grep: "border.*radius" --type cpp -i
```

### 高级用法

**带上下文搜索**：
```bash
# 显示匹配后 10 行
Grep: "OnModifyDone" --type cpp -A 10

# 显示匹配前 5 行和后 5 行
Grep: "class TextPattern" --type cpp -B 5 -A 5
```

**多模式搜索**：
```bash
# 搜索多个关键词
Grep: "OnModifyDone|OnAttachToMainTree|OnDetach" --type cpp
```

**正则表达式**：
```bash
# 搜索特定命名模式
Grep: "void.*Pattern::On[A-Z]" --type cpp
```

### 常见搜索场景

```bash
# 搜索生命周期方法
Grep: "On(ModifyDone|AttachToMainTree|DetachFromMainTree)" --type cpp

# 搜索智能指针使用
Grep: "AceType::(RefPtr|WeakClaim|DynamicCast)" --type cpp

# 搜索错误处理
Grep: "CHECK_NULL_VOID|LOGE|return.*nullptr" --type cpp

# 查找宏定义
Grep: "DEFINE.*_PROPERTY" frameworks/core/components_ng/property/
```

---

## Read 工具

读取文件内容，支持分页和偏移。

### 基本用法

```bash
# 读取整个文件
Read: frameworks/core/components_ng/pattern/text/text_pattern.cpp

# 读取特定行范围
Read: file.cpp (offset: 100, limit: 50)

# 读取头文件
Read: frameworks/core/components_ng/pattern/text/text_pattern.h
```

### 高级用法

**读取特定行**：
```bash
# 从第 200 行开始，读 100 行
Read: text_pattern.cpp (offset: 200, limit: 100)

# 读取文件开头
Read: text_pattern.cpp (offset: 0, limit: 50)
```

### 实战技巧

**先读头文件了解接口**：
```bash
Read: text_pattern.h
```

**再读实现了解细节**：
```bash
Read: text_pattern.cpp
```

**组合使用**：
1. 用 Grep 找到关键方法位置
2. 用 Read 读取该方法所在行范围
3. 分析代码逻辑

---

## 组合使用策略

### 场景 1：查找组件实现

```bash
# Step 1: 找到组件文件
Glob: "**/text/*.cpp"

# Step 2: 查看类定义
Grep: "class TextPattern" --type cpp

# Step 3: 读取完整实现
Read: text_pattern.cpp
```

### 场景 2：分析方法调用链

```bash
# Step 1: 找到方法定义
Grep: "void TextPattern::OnModifyDone" --type cpp

# Step 2: 查看调用者
Grep: "OnModifyDone\(\)" frameworks/core/components_ng/pattern/text/ -B 3

# Step 3: 读取相关代码
Read: text_pattern.cpp (offset: 200, limit: 50)
```

### 场景 3：查找测试覆盖

```bash
# Step 1: 找到测试文件
Glob: "**/text/*test*.cpp"

# Step 2: 搜索特定测试
Grep: "TEST.*TextPattern.*OnModifyDone" --type cpp

# Step 3: 读取测试代码
Read: text_pattern_test.cpp
```

### 场景 4：验证 API 使用

```bash
# Step 1: 查找 API 定义
Grep: "UpdateText\|SetText" frameworks/core/components_ng/pattern/text/

# Step 2: 查看实际调用
Grep: "pattern->(UpdateText|SetText)" frameworks/core/components_ng/

# Step 3: 对比规范
Read: interface/sdk-js/api/arkui/component/text.static.d.ets
```

---

## 工具使用最佳实践

### 1. 由粗到细
```
Glob (找到文件) → Grep (定位位置) → Read (读取代码)
```

### 2. 验证优先
```bash
# ❌ 不推荐：假设文件存在
Read: non_existent_file.cpp

# ✅ 推荐：先用 Glob 验证
Glob: "**/non_existent*.cpp"
```

### 3. 精确搜索
```bash
# ❌ 不推荐：搜索范围太广
Grep: "RefPtr" --type cpp

# ✅ 推荐：限定搜索目录
Grep: "RefPtr" frameworks/core/components_ng/pattern/text/
```

### 4. 上下文完整
```bash
# ❌ 不推荐：只看匹配行
Grep: "OnModifyDone" --type cpp

# ✅ 推荐：查看上下文
Grep: "void TextPattern::OnModifyDone" --type cpp -A 20
```

---

## 常见问题排查

### 问题：找不到文件

**排查步骤**：
```bash
# 1. 检查文件路径是否正确
Glob: "**/text/*.cpp"

# 2. 搜索类名
Grep: "class TextPattern" --type cpp

# 3. 列出目录
Bash: ls frameworks/core/components_ng/pattern/text/
```

### 问题：Grep 无结果

**排查步骤**：
```bash
# 1. 检查搜索关键词
Grep: "OnModifyDone" --type cpp -i  # 不区分大小写

# 2. 使用正则
Grep: "On.*Modify.*Done" --type cpp

# 3. 扩大搜索范围
Grep: "OnModifyDone" frameworks/core/
```

### 问题：Read 失败

**排查步骤**：
```bash
# 1. 确认文件存在
Bash: ls -la frameworks/core/components_ng/pattern/text/text_pattern.cpp

# 2. 检查路径拼写
Read: text_pattern.cpp  # 相对路径可能失败
Read: frameworks/core/components_ng/pattern/text/text_pattern.cpp  # 完整路径
```

---

## 工具参考速查表

| 工具 | 用途 | 典型场景 |
|------|------|---------|
| **Glob** | 文件查找 | 按名称模式找文件 |
| **Grep** | 代码搜索 | 查找类/函数/变量定义和调用 |
| **Read** | 文件读取 | 查看完整实现 |
| **Bash** | 命令执行 | 编译、测试、文件操作 |

### 组合使用流程

```
┌─────────┐
│  Glob   │  找到相关文件
└────┬────┘
     │
     ↓
┌─────────┐
│  Grep   │  定位关键代码
└────┬────┘
     │
     ↓
┌─────────┐
│  Read   │  阅读实现细节
└─────────┘
```
