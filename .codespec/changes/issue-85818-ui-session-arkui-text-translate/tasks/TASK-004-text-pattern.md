# TASK-004: Text/Span/styled string 运行时译文展示

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-004 |
| 标题 | Text/Span/styled string 可翻译文本提取、临时译文布局和恢复 |
| 关联 Feature | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 目标仓库 | ace_engine |
| 目标模块 | frameworks/core/components_ng/pattern/text |
| 分支 | dev |
| 优先级 | P0 |
| 复杂度 | 高 |
| 执行方式 | 主线程顺序执行 |

## 任务描述

### 做什么

1. 新增/使用 `PageTranslateNode` 抽象接口承载 ArkUI 可翻译节点的 nodeId、文本提取、译文回填和 Reset；`Pattern` 基类不增加默认翻译虚函数。
2. Text Pattern 实现 `PageTranslateNode`，提供可翻译文本提取接口，覆盖 Text、子 Span、styled string 展示文本。
3. Text Pattern 保存运行时临时译文和 version，layout paragraph 构建时优先使用译文。
4. Reset/End/SA death 清理临时译文并 MarkDirty，恢复原文展示。
5. 原始 Text/Span/styled string 属性保持不变。
6. 提供实际文本绘制状态给 `ContentChangeManager` 过滤占位布局。

### 不做什么

- 不处理 TextInput/TextArea 用户可编辑文本；空内容 TextInput 当前实际展示的 placeholder 翻译由 TextFieldPattern 同期实现并复用本任务的运行时译文/Reset/实际绘制过滤原则。
- 不修改应用原始属性。
- 不实现 RichEditor。

## 规格映射与边界

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-1, AC-6, AC-7, AC-14a | spec.md | Text 提取/增量单测 |
| AC-10, AC-11, AC-12, AC-13 | spec.md | 回填/Reset/version 单测 |

| Rule ID | Must / Must Not |
|---------|-----------------|
| RUNTIME-ONLY | 临时译文不写回原属性 |
| DRAWN-TEXT-ONLY | 未实际绘制文本不上报 |
| DATA-MIN | 回填按 nodeId/version 校验 |
| TRANSLATE-NODE-IFACE | Text/TextField 按需继承 `PageTranslateNode`，不得把翻译默认虚函数加到 `Pattern` 基类 |
| BUILD-MIN | 编译 Text 所属 pattern/组件目标和 text unittest |
| SMALL-FUNCTION-REUSE | Text、Span、styled string 的文本提取、临时译文选择、version 校验、dirty 标记和 Reset 恢复应通过小函数复用，不在布局、绘制变化和回填入口重复实现 |

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 新增 | `frameworks/core/components_ng/pattern/page_translate/page_translate_node.h` | 可翻译节点抽象接口；ArkUI 方法为纯虚，Web hook 为默认空实现 |
| 修改 | `frameworks/core/components_ng/pattern/text/text_pattern.*` | 提取、回填、Reset、dirty |
| 修改 | `frameworks/core/components_ng/pattern/text/text_content_modifier.cpp` | 文本变化触发点接入 |
| 测试 | `test/unittest/core/pattern/text` | Text/Span/styled string 翻译单测 |

## 完成判据

- Text/Span/styled string 可提取当前实际绘制文本。
- Text Pattern 通过 `PageTranslateNode` 接口接入，`Pattern` 基类不承载默认翻译虚函数。
- 回填译文后布局展示译文，原属性仍为原文。
- version 不匹配、nodeId 不存在或节点离树时单条忽略。
- Reset/End/SA death 后恢复原文展示。
- Text Pattern 内公共逻辑已收敛为小函数，例如提取展示文本、判断实际绘制、选择布局文本、应用/清理临时译文；不得在不同生命周期入口复制同一段分支。

## 停止条件

- styled string 文本结构无法无损提取或临时替换，需要拆分补充设计。
- 译文参与布局导致现有 Text 布局测试大量非预期回归。

## 验证检查清单

- [ ] Text Pattern 单测覆盖提取、回填、Reset、version mismatch、实际绘制过滤
- [ ] `./build.sh --product-name rk3568 --build-target //arkui/ace_engine/frameworks/core/components_ng/pattern/text:text_pattern`
