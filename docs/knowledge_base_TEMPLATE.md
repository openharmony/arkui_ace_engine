# Knowledge Base Template

用于新增知识库文档时快速复制。本模板对齐当前仓库规范：

- 文件命名：`XXX_Knowledge_Base.md` 或 `XXX_Knowledge_Base_CN.md`
- 存放目录：`docs/pattern/<component>/`、`docs/sdk/`、`docs/architecture/` 等
- 索引维护：同步更新 `docs/knowledge_base_INDEX.json`

---

## 1) 文档模板（复制后替换占位符）

```markdown
# <Component Name> <组件名>知识库

> 文档版本：v1.0
> 更新时间：YYYY-MM-DD
> 源码版本：OpenHarmony ace_engine (master 分支)

## 概述

- 组件定位：
- 典型使用场景：
- 与相近组件差异：

## 目录结构

```text
OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/<component>/
├── <component>_pattern.h/.cpp
├── <component>_model_ng.h/.cpp
├── <component>_layout_property.h/.cpp
└── ...
```

## 核心类继承关系

- `<Component>Pattern` 继承关系
- `<Component>ModelNG` 角色
- EventHub/LayoutAlgorithm/PaintMethod 关系

## Pattern层详解

- 生命周期入口（如 `OnAttachToFrameNode` / `OnModifyDone`）
- 关键状态变量
- 事件处理流程

示例（请替换为真实代码与行号）：
Source: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/<component>/<component>_pattern.cpp:123`

## Model层详解

- 对外接口
- 属性写入路径
- 与 Pattern/Property 的协作

## 完整API清单

- Static API:
  - `OpenHarmony/interface/sdk-js/api/arkui/component/<component>.static.d.ets`
- Modifier API:
  - `OpenHarmony/interface/sdk-js/api/arkui/<Component>Modifier.d.ts`

## 关键实现细节

- 布局/绘制关键路径
- 边界条件与异常分支
- 性能与缓存策略

## 使用示例

```ts
// 示例代码（请替换为可运行示例）
@Entry
@Component
struct Example {
  build() {
    // ...
  }
}
```

## 调试指南

- 关键日志点
- 常见断点位置
- 排查流程

## 常见问题

1. 问题：
   结论：
2. 问题：
   结论：
```

---

## 2) 索引条目模板（`knowledge_base_INDEX.json`）

将以下对象加入 `knowledge_bases` 数组：

```json
{
  "name": "<ComponentName>",
  "name_cn": "<组件中文名>",
  "category": "basic/container/selector/shape/media/data_display/rich_text/advanced/sdk/system",
  "type": "component/feature/sdk",
  "keywords": [
    "关键词1",
    "关键词2",
    "关键词3",
    "关键词4",
    "关键词5"
  ],
  "aliases": [
    "别名1",
    "别名2",
    "别名3"
  ],
  "file_path": "pattern/<component>/<Component>_Knowledge_Base[_CN].md",
  "source_paths": {
    "pattern": "OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/<component>/<component>_pattern.cpp",
    "model": "OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/<component>/<component>_model_ng.cpp"
  },
  "api_paths": {
    "static": "OpenHarmony/interface/sdk-js/api/arkui/component/<component>.static.d.ets",
    "modifier": "OpenHarmony/interface/sdk-js/api/arkui/<Component>Modifier.d.ts"
  },
  "last_updated": "YYYY-MM-DD"
}
```

---

## 3) 提交前检查

```bash
# 索引 JSON 校验
python3 -m json.tool docs/knowledge_base_INDEX.json > /dev/null && echo "Valid JSON"

# 文档计数
find docs -name "*_Knowledge_Base*.md" -type f | wc -l

# 检索冒烟
python3 docs/kb_search.py --list-all
python3 docs/kb_search.py <ComponentName> --field name
```

注意：

- 代码路径统一使用 `OpenHarmony/` 前缀。
- 不要写本地绝对路径（如 `/home/...`）。
- 代码片段必须来自实际源码，避免假设性实现。
