# Knowledge Base

此目录用于存放 ArkUI ACE Engine 的知识库文档，并通过索引文件支持快速检索。

> 更新时间：2026-05-23
> 适用仓库：`OpenHarmony/foundation/arkui/ace_engine/docs`

## 1. 检索入口

- 元数据索引：`docs/knowledge_base_INDEX.json`
- 推荐检索脚本：`docs/kb_search.py`
- 新增文档模板：`docs/knowledge_base_TEMPLATE.md`

常用命令：

```bash
# 全字段模糊检索（name/name_cn/keywords/aliases/category/type）
python3 docs/kb_search.py <关键字>

# 限定字段
python3 docs/kb_search.py <关键字> --field name

# 列出全部已索引知识库
python3 docs/kb_search.py --list-all

# 列出分类
python3 docs/kb_search.py --list-categories
```

兜底检索：

```bash
rg -n "<关键字>" docs
```

## 2. 当前统计（按仓库实际）

### 2.1 文件系统统计

- `docs/` 下 Markdown 文档总数：73
- 命名符合 `*_Knowledge_Base*.md` 的知识库文档：58
- `docs/syntax/` 下语法专题文档：7
  - 其中知识库命名文档 4 个：`ForEach/LazyForEach/Repeat/RepeatVirtualScroll`
  - 其他专题文档 3 个：`Syntax_Architecture_Overview/Conditional_Rendering_Guide/Special_Syntax_Components`

### 2.2 索引统计（`knowledge_base_INDEX.json`）

- 索引条目总数：59
- 索引路径有效性：59/59（全部存在）
- 类型分布：
  - `component`: 36
  - `sdk`: 4
  - `feature`: 19
- 分类分布：
  - `basic`: 5
  - `advanced`: 5
  - `container`: 7
  - `data_display`: 8
  - `media`: 2
  - `selector`: 7
  - `rich_text`: 3
  - `shape`: 1
  - `sdk`: 6
  - `system`: 15
- 关键词总数（索引内）：521
- 别名总数（索引内）：185

### 2.3 覆盖现状

- 命名符合 `*_Knowledge_Base*` 的 58 个文档已全部纳入索引（58/58）。
- 另有 1 个非 `*_Knowledge_Base*` 命名文档在索引中：
  - `docs/architecture/ThemeManager_Architecture_CN.md`

## 3. 目录结构（按当前实际）

```text
docs/
├── knowledge_base_README.md
├── knowledge_base_INDEX.json
├── kb_search.py
├── accessibility/ (1 KB)
├── api/ (2 KB)
├── architecture/ (1 KB + 其他架构文档)
├── cj_frontend/ (1 KB)
├── common/ (4 KB)
├── layout/ (3 KB)
├── pattern/ (38 KB)
├── sdk/ (3 KB)
├── svg/ (1 KB)
└── syntax/ (7 MD, 其中 4 KB)
```

说明：

- `pattern/` 是组件知识库主目录（数量最多）。
- `syntax/` 同时包含知识库文档与专题/总览文档，不全是 `*_Knowledge_Base*` 命名。

## 4. 索引维护规则（执行版）

新增或更新知识库时，至少同步以下内容：

1. 更新文档本体（建议遵循 `*_Knowledge_Base[_CN].md` 命名规范）。
   - 可直接复制模板：`docs/knowledge_base_TEMPLATE.md`
2. 更新 `docs/knowledge_base_INDEX.json`：
   - 必填：`name/name_cn/category/type/keywords/aliases/file_path/last_updated`
   - 推荐：`source_paths/api_paths`
3. 更新本文件统计与目录快照。

校验命令：

```bash
# JSON 格式校验
python3 -m json.tool docs/knowledge_base_INDEX.json > /dev/null && echo "Valid JSON"

# 命名规范文档计数
find docs -name "*_Knowledge_Base*.md" -type f | wc -l

# 索引检索冒烟
python3 docs/kb_search.py --list-all
```

## 5. 索引缺口

- 当前 `*_Knowledge_Base*` 命名文档未索引数量：0
- 若后续新增文档，请同步更新索引并执行第 4 节校验命令。

## 6. 变更记录

- 2026-05-23：补齐未索引知识库条目（+25），索引覆盖 `*_Knowledge_Base*` 文档达到 100%。
- 2026-05-23：按当前仓库实际重刷本文件，更新统计、目录快照和维护命令。
