# Knowledge Base

此目录用于存放 ArkUI ACE Engine 的知识库文档，并通过索引文件支持快速检索。

> 更新时间：2026-07-31
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

- `docs/` 下 Markdown 文档总数：252
- 命名符合 `*_Knowledge_Base*.md` 的旧版知识库文档：19
- `docs/syntax/` 下语法专题文档：3
  - 知识库命名文档：0 个（ForEach/LazyForEach/Repeat/RepeatVirtualScroll 已迁移到 `docs/kb/syntax/`）
  - 其他专题文档 3 个：`Syntax_Architecture_Overview/Conditional_Rendering_Guide/Special_Syntax_Components`

### 2.2 索引统计

- `context_registry.json` 新版条目数：215
- `knowledge_base_INDEX.json` 旧 KB 索引条目总数：22
- 旧 KB 索引路径有效性：20/22（2 个上游遗留路径待修复）

- 类型分布：
  - `component`: 6
  - `sdk`: 4
  - `feature`: 12
- 分类分布：
  - `advanced`: 2
  - `basic`: 1
  - `container`: 2
  - `rich_text`: 2
  - `sdk`: 6
  - `selector`: 1
  - `system`: 8
- 关键词总数（索引内）：240
- 别名总数（索引内）：75

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
├── kb/ (216 MD，215 个新版 KB 主题 + README)
├── accessibility/ (0 KB)
├── api/ (2 KB)
├── architecture/ (2 KB + 3 非 `*_Knowledge_Base*` 命名架构文档)
├── cj_frontend/ (1 KB)
├── common/ (4 KB)
├── entrance/ (1 MD)
├── focus/ (2 MD)
├── layout/ (0 KB)
├── pattern/ (7 KB + 6 非 `*_Knowledge_Base*` 命名文档)
├── sdk/ (3 KB)
├── svg/ (0 KB，SVG 已迁移)
└── syntax/ (3 MD，旧语法 KB 已迁移到 `docs/kb/syntax/`)
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
- 2026-07-28：按 9 个长期规格（04-06-01、04-06-06、04-19-01、05-12-02、05-16-01、05-16-02、07-05-01、07-05-02、07-05-03）新增 9 个新版 KB，`context_registry.json` 条目更新至 27。
- 新增能力/架构/组件 KB：`capabilities/placeholder_component.md`、`capabilities/node_adapter.md`、`architecture/component_reuse_framework.md`、`components/embedded/ability_component.md`、`components/custom-node/node_container.md`、`components/custom-node/content_slot.md`。
- 迁移旧语法 KB 到 `docs/kb/syntax/`：`render_control.md`（合并 ForEach + if/else + 共享框架，旧 `ForEach` KB 已移除）、`lazy_for_each.md`、`repeat.md`（合并 Repeat + RepeatVirtualScroll）。
- 旧 `ForEach/LazyForEach/Repeat/RepeatVirtualScroll_Knowledge_Base.md` 已删除，旧索引移除对应 4 条（53 → 49 条）。
- 2026-07-10：ImageAnimator 迁移到 `docs/kb/components/media/image_animator.md`，旧 KB 已移除，旧索引已更新（57 条）。
- 2026-07-10：新增 DrawableDescriptor 通用能力 KB：`docs/kb/capabilities/drawable_descriptor.md`。
- 2026-07-11：TextPicker、DatePicker、TimePicker、UIPickerComponent 迁移到 `docs/kb/components/selector/`，旧 KB 已移除，旧索引已更新（53 条）。
- 2026-07-18：基于当前源码、SDK、测试和基础渲染管线 Spec 重建 Layout Framework 新版 KB，旧 KB 与旧索引入口已移除（旧索引 52 条）。
- 2026-07-18：新增 Layout Attributes、Blank、Divider、Column、GridCol、GridRow、Row、Stack、FolderStack；重建 Flex（含 Wrap）并合并 Safe Area 两个旧主题。新版 registry 增至 34 条，旧 Flex/Safe Area 文件及索引入口移除，旧索引减至 49 条。
- 2026-07-24：新增 ImageLoading、BackgroundImage、ImageAnalyzer 和四个 PickerDialog 新版 KB；迁移 SVG 到 `docs/kb/capabilities/svg.md` 并移除旧文件及旧索引入口。新版 registry 增至 42 条，旧索引减至 48 条。
- 2026-07-29：基于 05-09-06 Span 类长期规格与源码新增 Span、ImageSpan、SymbolSpan、ContainerSpan 四个新版 KB（`docs/kb/components/basic/`）。新版 registry 增至 90 条；无旧 KB 迁移。
- 2026-07-30：依据 05-03-01 与 05-03-10 Spec 重建滚动公共能力、迁移 WaterFlow/FlowItem；移除旧 WaterFlow KB 与索引入口，并与上游 Scroll/List/Refresh/ScrollBar 等迁移结果合并。新版 registry 共 143 条，旧索引减至 33 条；同步修复 Swiper 组件化路由。

- 2026-07-23：新增 8 个 overlay 类组件 KB（Menu/Dialog/Toast/Select/bindPopup/PopupAdvanced/Sheet/bindTips），补齐弹窗类组件 Spec 路由；迁移 Menu 和 Sheet 旧 KB 到新版路径。
- 2026-07-27：新增 Pixel Rounding 与 MediaQuery 新版 KB；新版 registry 增至 66 条，旧索引保持 46 条。
- 2026-07-27：新增 Preview Platform Adaptation 新版 KB；对应架构设计已存在，新版 registry 增至 67 条，旧索引保持 46 条。
- 2026-07-29：新增 Custom Measure/Layout 新版 KB；补充自定义组件现行回调与已废弃 API 的兼容实现边界。新版 registry 增至 68 条，旧索引保持 46 条。
- 2026-07-29：迁移 RichEditor 到 `docs/kb/components/basic/rich_editor.md`，旧 KB 已移除，旧索引入口及 rich_text 分类已移除（旧索引 47 条）。新版 registry 增至 43 条，关联 Spec `05-09-02`（9 个 Feat spec + 1 个 design.md）。
- 2026-07-29：迁移 Grid 到 `docs/kb/components/container/grid.md`，旧 KB 已移除，旧索引入口已移除（旧索引减至 45 条）；新增 GridItem KB `docs/kb/components/container/grid_item.md`。registry 增至 70 条。
- 2026-07-29：迁移 Scroll/List/Refresh/ScrollBar 四个滚动容器旧 KB 到 `docs/kb/components/container/`，补齐 Spec 路由（func_id 05-03-03/05/06/07）。旧 KB 文件删除、旧 INDEX 条目移除（减至 37 条）、context_registry 增至 135 条；rebase 到最新 origin/master 后解决与 Grid 迁移等的冲突（grid 旧 KB 按上游删除处理）。

- 2026-07-29：基于已补录的长期规格与源码新增/迁移 4 个文本类主题 KB。新建 `docs/kb/components/basic/symbol-glyph.md`（SymbolGlyph，复用 TextPattern）与 `docs/kb/capabilities/styled-string.md`（属性字符串，common_capability/api，非组件）；迁移 TextInput 旧 KB 到 `docs/kb/components/basic/text-input.md`、Hyperlink 旧 KB 到 `docs/kb/components/basic/hyperlink.md`，旧文件及旧索引入口移除。新版 registry 增至 88 条，旧索引减至 44 条。

- 2026-07-30：基于已补录的长期规格与源码新增 2 个输入交互框架内部能力 KB。新建 `docs/kb/capabilities/text-shortcuts.md`（文本快捷键，common_capability/system，TextInputClient 加速表）与 `docs/kb/capabilities/keyboard-control.md`（键盘控制，common_capability/system，**重定范围为输入框↔键盘交互**：IME 弹出收起/避让/输入处理契约/公共 API，非焦点导航）。两域均补齐 Spec 路由。顺带修复若干遗留 registry/index 失效（Swiper jsview→controller_binding、PreviewPlatformAdaptation host_preview test_path 拼写、移除 List/Hyperlink 旧 INDEX 失效条目）。

- 2026-07-30：04-14-04 特性整体更名 zh「键盘控制」→「输入法交互」、目录 `04-keyboard-control/`→`04-input-method-interaction/`。同步更新 functions.yaml/functions.yaml 路径与标题、5 个 Feat spec 路径、design.md 与 Feat 内部引用、KB 文件 `keyboard-control.md`→`input-method-interaction.md`、context_registry 条目（id/name/name_cn/spec_domain/kb）及 text-shortcuts 交叉链接。

- 2026-07-30：新增触摸事件、按键事件、事件分发和拦截、组件组合键、鼠标事件、手势能力、事件基础框架、交互归一化、手写笔能力、组件相关事件、可见区域机制、焦点机制、ComponentUtils 13 个新版 KB 主题；新版 registry 增至 214 条，旧索引保持 22 条。
- 2026-07-31：新增 Gesture Modifier 通用能力 KB，关联 Func-04-05-07；新版 registry 增至 215 条，旧索引保持 22 条。
