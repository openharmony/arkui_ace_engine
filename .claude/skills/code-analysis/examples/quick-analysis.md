# 快速分析示例

## 示例：TextPattern OnModifyDone 快速分析

### 用户请求
```
请快速分析 TextPattern 的 OnModifyDone 方法的内存管理
```

### 分析过程

#### 1. 代码定位
使用 Grep 工具搜索相关文件：
```bash
Grep: "class TextPattern" --type cpp
```

找到文件：`frameworks/core/components_ng/pattern/text/text_pattern.h`

#### 2. 读取源代码
使用 Read 工具读取实现：
```bash
Read: frameworks/core/components_ng/pattern/text/text_pattern.cpp
```

#### 3. 分析 OnModifyDone 方法
定位到 `text_pattern.cpp:234-256`

```cpp
void TextPattern::OnModifyDone()
{
    TextLayoutProperty::DirtySwapCallback dirtySwapCallback = [weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnDirtyLayoutWrapperSwap();
        }
    };
    textLayoutProperty_->SetDirtySwapCallback(dirtySwapCallback);

    // Measure text content
    MeasureFromParagraph();
    OnLanguageChange();
}
```

### 分析结论

**核心发现**（带代码引用）：
- ✅ 使用 `AceType::WeakClaim(this)` 创建弱引用，避免循环引用导致的内存泄漏
  - 位置：`text_pattern.cpp:235`
- ✅ 在回调中使用 `weak.Upgrade()` 尝试提升为强引用，并检查提升结果
  - 位置：`text_pattern.cpp:236-238`
- ✅ 智能指针使用符合 NG 架构规范
  - 参考知识库：`docs/pattern/text/Text_Knowledge_Base_CN.md`

**潜在问题**：无

**改进建议**：当前实现已遵循最佳实践，无需改进

---

## 示例：Menu 生命周期管理快速分析

### 用户请求
```
快速查看 Menu 组件的生命周期管理是否完整
```

### 分析过程

#### 1. 查找 Menu Pattern
```bash
Glob: "**/menu/menu_pattern.cpp"
```

#### 2. 读取关键方法
```bash
Read: frameworks/core/components_ng/pattern/menu/menu_pattern.cpp
```

#### 3. 检查生命周期方法
使用 Grep 搜索生命周期方法：
```bash
Grep: "OnModifyDone\|OnDetachFromMainTree\|OnAttachToMainTree" frameworks/core/components_ng/pattern/menu/
```

### 分析结论

**核心发现**（带代码引用）：
- ✅ `OnAttachToMainTree` 实现完整：`menu_pattern.cpp:145-167`
- ✅ `OnDetachFromMainTree` 实现完整：`menu_pattern.cpp:169-189`
- ✅ `OnModifyDone` 实现完整：`menu_pattern.cpp:191-245`

**潜在问题**：无

**改进建议**：生命周期管理完整，符合 NG 架构规范

---

## 快速分析要点总结

### 必须包含
1. **代码位置引用**：所有发现都标注 `file:line`
2. **实际代码片段**：关键实现摘录
3. **简明结论**：直接回答用户问题

### 时间控制
- 代码定位：2-3 分钟
- 代码阅读：3-5 分钟
- 分析总结：2-3 分钟
- **总计**：5-15 分钟

### 输出格式
```
### 分析标题

**核心发现**（带代码引用）：
- 发现点1：文件位置:行号
- 发现点2：文件位置:行号

**潜在问题**：
- 问题1（如有）

**改进建议**：
- 建议1（如有）
```
