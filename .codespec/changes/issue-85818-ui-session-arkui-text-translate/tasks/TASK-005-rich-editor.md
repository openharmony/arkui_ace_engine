# TASK-005: RichEditor 只读展示内容翻译

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-005 |
| 标题 | RichEditor 只读展示内容可翻译和临时译文展示 |
| 关联 Feature | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 目标仓库 | ace_engine |
| 目标模块 | frameworks/core/components_ng/pattern/rich_editor |
| 分支 | dev |
| 优先级 | P0 |
| 复杂度 | 中 |
| 执行方式 | 主线程顺序执行 |

## 任务描述

### 做什么

1. RichEditor Pattern 仅在只读展示态提供可翻译文本提取。
2. 回填译文作为运行时临时展示状态参与布局，不修改原始 span/content。
3. 编辑态、输入态或不可展示内容排除翻译。
4. 提供实际文本绘制状态，支持占位布局不上报。
5. Reset/End/SA death 恢复原文展示。

### 不做什么

- 不翻译可编辑输入内容。
- 不改变 RichEditor 编辑行为、选区、输入法状态。
- 不向 SA 暴露 RichEditor 内部 span 结构。

## 规格映射与边界

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-1, AC-3 | spec.md | 只读/编辑态过滤单测 |
| AC-6, AC-7, AC-14a | spec.md | 增量和实际绘制过滤单测 |
| AC-10 至 AC-13 | spec.md | 回填、Reset、version 单测 |

| Rule ID | Must / Must Not |
|---------|-----------------|
| RUNTIME-ONLY | 临时译文不写回原模型 |
| DRAWN-TEXT-ONLY | 未实际绘制文本不上报 |
| DATA-MIN | 对 SA 只输出 `nodeId/text/version` |
| BUILD-MIN | 编译 RichEditor 所属 pattern/组件目标和 rich_editor unittest |
| TRANSLATE-NODE-IFACE | RichEditor 通过继承 TextPattern 复用 `PageTranslateNode` 接口语义，只覆盖只读展示态过滤和富文本提取/布局差异；不得在 `Pattern` 基类新增默认翻译虚函数 |
| SMALL-FUNCTION-REUSE | 只读展示态判断、展示文本提取、临时译文布局选择、version 校验和 Reset 恢复应抽成小函数复用，并尽量复用 Text 侧 `PageTranslateNode` 接口语义 |

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.*` | 提取、只读过滤、回填、Reset |
| 修改 | `frameworks/core/components_ng/pattern/rich_editor` 相关布局/内容文件 | 必要时让临时译文参与布局 |
| 测试 | `test/unittest/core/pattern/rich_editor` | RichEditor 翻译单测 |

## 完成判据

- readonly RichEditor 展示内容可提取并回填临时译文。
- RichEditor 通过 TextPattern 的 `PageTranslateNode` 接口链路接入 manager，manager 无需识别 RichEditor 具体类型。
- 编辑态 RichEditor 不进入翻译范围。
- 未实际绘制文本不上报。
- Reset/End/SA death 后恢复原文展示且不影响编辑状态。
- RichEditor 的提取、状态过滤、回填和恢复逻辑没有多入口复制；公共判断通过私有 helper 复用，且不引入新的独立小 manager。

## 停止条件

- RichEditor 当前代码无法稳定判断只读展示态。
- 临时译文布局会破坏编辑态状态管理。

## 验证检查清单

- [ ] RichEditor 单测覆盖只读提取、编辑态排除、回填、Reset、实际绘制过滤
- [ ] 编译 RichEditor 所属 pattern/组件目标；必要时补 rich_editor unittest 目标
