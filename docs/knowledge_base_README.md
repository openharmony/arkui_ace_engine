# Knowledge Base

此目录用于存放 ArkUI ACE Engine 的知识库文档，并通过索引文件支持快速检索。

> 更新时间：2026-07-18
> 适用仓库：`OpenHarmony/foundation/arkui/ace_engine/docs`

## 1. 检索入口

- 上下文索引：`docs/context_registry.json`
- 旧 KB 兼容索引：`docs/knowledge_base_INDEX.json`
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

- `docs/` 下 Markdown 文档总数：101
- 命名符合 `*_Knowledge_Base*.md` 的旧版知识库文档：48
- `docs/syntax/` 下语法专题文档：7
  - 其中知识库命名文档 4 个：`ForEach/LazyForEach/Repeat/RepeatVirtualScroll`
  - 其他专题文档 3 个：`Syntax_Architecture_Overview/Conditional_Rendering_Guide/Special_Syntax_Components`

### 2.2 索引统计

- `context_registry.json` 新版条目数：34
- `knowledge_base_INDEX.json` 旧 KB 索引条目总数：49
- 旧 KB 索引路径有效性：49/49（全部存在）

- 类型分布：
  - `component`: 28
  - `sdk`: 4
  - `feature`: 17
- 分类分布：
  - `advanced`: 5
  - `basic`: 4
  - `container`: 6
  - `data_display`: 8
  - `rich_text`: 3
  - `sdk`: 6
  - `selector`: 3
  - `shape`: 1
  - `system`: 13
- 关键词总数（索引内）：458
- 别名总数（索引内）：159

### 2.3 覆盖现状

- 已迁移到新版 `docs/kb/` 的主题不再保留在旧 `knowledge_base_INDEX.json` 中。
- 旧索引中仍保留尚未迁移的旧 KB 条目。

## 3. 目录结构（按当前实际）

```text
docs/
├── context_registry.json
├── knowledge_base_README.md
├── knowledge_base_INDEX.json
├── kb_search.py
├── kb/ (35 MD，34 个新版 KB 主题 + README)
├── accessibility/ (1 KB)
├── api/ (2 KB)
├── architecture/ (2 KB + 3 非 `*_Knowledge_Base*` 命名架构文档)
├── cj_frontend/ (1 KB)
├── common/ (4 KB)
├── entrance/ (1 MD)
├── focus/ (2 MD)
├── layout/ (0 KB)
├── pattern/ (30 KB + 7 非 `*_Knowledge_Base*` 命名文档)
├── sdk/ (3 KB)
├── svg/ (1 KB)
└── syntax/ (7 MD, 其中 4 KB)
```

说明：

- `kb/` 是新版知识库专区，新 KB 优先进入该目录。
- `pattern/` 是旧版组件知识库主目录（数量最多）；单个主题迁移到 `docs/kb/` 后，应同步删除对应旧 KB 文件。
- `syntax/` 同时包含知识库文档与专题/总览文档，不全是 `*_Knowledge_Base*` 命名。

## 4. 索引维护规则（执行版）

新增或更新知识库时，至少同步以下内容：

1. 更新文档本体。
   - 新版 KB 按 `docs/kb/README.md` 的轻量上下文规范放入 `docs/kb/`。
   - `*_Knowledge_Base[_CN].md` 是尚未迁移的旧 KB 命名；迁移完成后删除对应旧文件。
2. 更新 `docs/context_registry.json`：
   - 必填：`id/name/name_cn/kind/category/keywords/aliases/kb/status/last_verified`
   - 推荐：`spec_domain/func_id/source_paths/api_paths/test_paths`
3. 更新 `docs/knowledge_base_INDEX.json`：
   - 必填：`name/name_cn/category/type/keywords/aliases/file_path/last_updated`
   - 推荐：`source_paths/api_paths`
   - 分类取值：`basic/container/selector/shape/media/data_display/rich_text/advanced/sdk/system`
   - 旧索引用于尚未迁移的 KB；已迁移到 `docs/kb/` 的主题应从旧索引中移除。
   - 新版 KB 路径规范：
     - **源码引用**（正文及 `source_paths`）：ace_engine 仓内文件使用仓根目录相对路径（如 `frameworks/core/components_ng/pattern/text/text_model_ng.cpp`），仓外文件使用 `<OH_ROOT>` 稳定占位路径。
     - **API 引用**（正文及 `api_paths`）：SDK 仓路径统一写为 `<OH_ROOT>/interface/sdk-js/...`，ace_engine 自身公开接口仍使用仓根目录相对路径。
     - 不附带行号，不使用仅文件名加行号或本机绝对路径。
4. 更新本文件统计与目录快照。

校验命令：

```bash
# JSON 格式校验
python3 -m json.tool docs/context_registry.json > /dev/null && echo "Valid registry JSON"
python3 -m json.tool docs/knowledge_base_INDEX.json > /dev/null && echo "Valid JSON"

# 上下文路由校验
python3 docs/validate_context.py

# 命名规范文档计数
find docs -name "*_Knowledge_Base*.md" -type f | wc -l

# 索引检索冒烟
python3 docs/kb_search.py --list-all

# 分类统计冒烟
python3 docs/kb_search.py --list-categories
```

统计复算（用于刷新本节数字）：

```bash
python3 - << 'PY'
import json
from collections import Counter
from pathlib import Path
idx = json.loads(Path("docs/knowledge_base_INDEX.json").read_text(encoding="utf-8"))["knowledge_bases"]
print("index_entries", len(idx))
print("types", dict(sorted(Counter(i["type"] for i in idx).items())))
print("categories", dict(sorted(Counter(i["category"] for i in idx).items())))
print("keywords", sum(len(i.get("keywords", [])) for i in idx))
print("aliases", sum(len(i.get("aliases", [])) for i in idx))
PY
```

## 5. 索引缺口

- 当前 `*_Knowledge_Base*` 命名文档未索引数量：0
- 若后续迁移新版 KB，请从旧索引中删除对应旧 KB 项，并执行第 4 节校验命令。

## 6. 变更记录

- 2026-05-23：补齐未索引知识库条目（+25），索引覆盖 `*_Knowledge_Base*` 文档达到 100%。
- 2026-05-23：按当前仓库实际重刷本文件，更新统计、目录快照和维护命令。
- 2026-06-01：修正统计漂移（索引 60 条、selector=8、system 分类保留），补充路径规范与统计复算命令。
- 2026-06-12：新增 UISession 知识库，索引更新至 61 条，系统功能分类更新至 16 条。
- 2026-06-26：新增 `docs/context_registry.json` 与 `docs/kb/` 试点结构，迁移 Text 路由到新版 KB。
- 2026-06-27：Text 迁移完成后移除旧 KB 文件和 `legacy_kb` 入口。
- 2026-06-27：Text 迁移完成后从旧 `knowledge_base_INDEX.json` 移除，未迁移旧 KB 仍保留。
- 2026-06-27：Image 迁移到 `docs/kb/components/media/image.md`，旧 KB 已移除，旧索引已更新（59 条）。
- 2026-07-10：ImageAnimator 迁移到 `docs/kb/components/media/image_animator.md`，旧 KB 已移除，旧索引已更新（57 条）。
- 2026-07-10：新增 DrawableDescriptor 通用能力 KB：`docs/kb/capabilities/drawable_descriptor.md`。
- 2026-07-11：TextPicker、DatePicker、TimePicker、UIPickerComponent 迁移到 `docs/kb/components/selector/`，旧 KB 已移除，旧索引已更新（53 条）。
- 2026-07-18：基于当前源码、SDK、测试和基础渲染管线 Spec 重建 Layout Framework 新版 KB，旧 KB 与旧索引入口已移除（旧索引 52 条）。
- 2026-07-18：新增 Layout Attributes、Blank、Divider、Column、GridCol、GridRow、Row、Stack、FolderStack；重建 Flex（含 Wrap）并合并 Safe Area 两个旧主题。新版 registry 增至 34 条，旧 Flex/Safe Area 文件及索引入口移除，旧索引减至 49 条。
