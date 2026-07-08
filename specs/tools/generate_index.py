#!/usr/bin/env python3
"""Generate index.md from the ArkUI spec registry."""

from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path
from typing import Any

import yaml


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS_FILE = ROOT / "registry" / "functions.yaml"
FEATURES_FILE = ROOT / "registry" / "features.yaml"
INDEX_FILE = ROOT / "index.md"


def load_yaml(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as fp:
        data = yaml.safe_load(fp)
    if not isinstance(data, dict):
        raise ValueError(f"{path} must contain a YAML mapping")
    return data


def link_or_pending(path: str | None, label: str) -> str:
    if not path:
        return "*待补充*"
    return f"[{label}]({path})"


def validate(top_levels: list[dict[str, Any]], functions: list[dict[str, Any]], features: list[dict[str, Any]]) -> None:
    errors: list[str] = []

    top_ids = [str(item["id"]) for item in top_levels]
    duplicate_top_ids = [item for item, count in Counter(top_ids).items() if count > 1]
    if duplicate_top_ids:
        errors.append(f"duplicate top-level ids: {', '.join(duplicate_top_ids)}")

    func_ids = [str(item["id"]) for item in functions]
    duplicate_func_ids = [item for item, count in Counter(func_ids).items() if count > 1]
    if duplicate_func_ids:
        errors.append(f"duplicate FuncID values: {', '.join(duplicate_func_ids)}")

    top_id_set = set(top_ids)
    func_id_set = set(func_ids)
    for func in functions:
        func_id = str(func["id"])
        for key in ("l1", "l2", "l3"):
            node = func.get(key)
            if not isinstance(node, dict) or "id" not in node or "title" not in node:
                errors.append(f"{func_id}: {key} must contain id and title")
        if str(func.get("l1", {}).get("id")) not in top_id_set:
            errors.append(f"{func_id}: l1 id is not declared in top_levels")
        if not func.get("path"):
            errors.append(f"{func_id}: path is required")

    feature_keys: set[tuple[str, str]] = set()
    feature_ids_by_func: defaultdict[str, list[str]] = defaultdict(list)
    for feature in features:
        func_id = str(feature.get("func_id", ""))
        feat_id = str(feature.get("id", ""))
        if func_id not in func_id_set:
            errors.append(f"{func_id}/{feat_id}: feature references unknown FuncID")
        if not re.fullmatch(r"Feat-\d{2}", feat_id):
            errors.append(f"{func_id}/{feat_id}: FeatID must match Feat-NN")
        key = (func_id, feat_id)
        if key in feature_keys:
            errors.append(f"{func_id}/{feat_id}: duplicate feature key")
        feature_keys.add(key)
        feature_ids_by_func[func_id].append(feat_id)
        if not feature.get("title"):
            errors.append(f"{func_id}/{feat_id}: title is required")
        if not feature.get("status"):
            errors.append(f"{func_id}/{feat_id}: status is required")

    for func_id, feat_ids in feature_ids_by_func.items():
        numbers = sorted(int(item.split("-")[1]) for item in feat_ids)
        expected = list(range(1, len(numbers) + 1))
        if numbers != expected:
            errors.append(f"{func_id}: FeatID sequence is not contiguous from Feat-01")

    if errors:
        raise ValueError("\n".join(errors))


def render_index(top_levels: list[dict[str, Any]], functions: list[dict[str, Any]], features: list[dict[str, Any]]) -> str:
    features_by_func: defaultdict[str, list[dict[str, Any]]] = defaultdict(list)
    for feature in features:
        features_by_func[str(feature["func_id"])].append(feature)
    for items in features_by_func.values():
        items.sort(key=lambda item: item["id"])

    lines: list[str] = []
    lines.append("# ArkUI 特性规格索引")
    lines.append("")
    lines.append("> 本文件是 ArkUI ace_engine 特性规格（Spec）体系的总入口。所有功能域和特性必须在此注册后才能生成规格文档。")
    lines.append("")
    lines.append("## 功能域层级树")
    lines.append("")
    lines.append("### 一级域（L1）")
    lines.append("")
    lines.append("| 编号 | 目录名（英文 slug） | 中文名 | 说明 |")
    lines.append("|------|---------------------|--------|------|")
    for top in top_levels:
        lines.append(f"| {top['id']} | `{top['slug']}` | {top['title']} | {top['description']} |")
    lines.append("")
    lines.append("### 二级域（L2）→ 三级域（L3）→ 功能域")
    lines.append("")
    lines.append("| L1 | L2 | L3 | FuncID | 目录路径 | design.md | 特性数 |")
    lines.append("|----|----|----|--------|----------|-----------|--------|")
    for func in functions:
        func_id = str(func["id"])
        l1 = func["l1"]
        l2 = func["l2"]
        l3 = func["l3"]
        design = link_or_pending(func.get("design"), "design.md")
        feature_count = len(features_by_func.get(func_id, []))
        lines.append(
            f"| {l1['id']} {l1['title']} | {l2['id']} {l2['title']} | {l3['id']} {l3['title']} | "
            f"`{func_id}` | `{func['path']}` | {design} | {feature_count} |"
        )
    lines.append("")
    lines.append("> 新增功能域时请在此表中按编号顺序添加行；未创建的设计文档以 `待补充` 标记。")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("## 已注册特性清单")
    for func in functions:
        func_id = str(func["id"])
        lines.append("")
        lines.append(f"### {func_id} {func['l3']['title']}")
        lines.append("")
        lines.append("| FeatID | 特性名称 | Spec 文件 | 状态 |")
        lines.append("|--------|----------|-----------|------|")
        for feature in features_by_func.get(func_id, []):
            spec = link_or_pending(feature.get("spec"), Path(str(feature.get("spec", ""))).name if feature.get("spec") else "spec.md")
            lines.append(f"| {feature['id']} | {feature['title']} | {spec} | {feature['status']} |")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.extend(STATIC_TAIL)
    return "\n".join(lines) + "\n"


STATIC_TAIL = [
    "## 注册规则",
    "",
    "1. **新增功能域**：在 `registry/functions.yaml` 中添加 FuncID 记录；如 `design.md` 尚未创建，`design` 字段置空；重新生成 `index.md`。",
    "2. **新增特性**：仅在具体规格补录开始、功能点/特性范围明确后，在 `registry/features.yaml` 中追加 FeatID 记录，包含 FuncID、FeatID、特性名称、Spec 文件、状态（`待补充`/`Draft`/`Baselined`/`Deprecated`）。",
    "3. **排序规则**：功能域按 FuncID 数值升序排列（`03-01-01` < `04-03-01` < `05-01-01`）；同一功能域内 FeatID 按 `Feat-01, Feat-02, ...` 顺序递增。",
    "4. **状态流转**：待补充 → Draft → Baselined（经评审通过后）→ Deprecated（被新特性替代）。",
    "5. **目录命名**：使用英文 slug（小写 + 短横线分隔），编号使用两位数字（`01-`, `02-`, ...）。",
    "6. **FeatID 编号**：同一功能域内从 `Feat-01` 顺序递增；历史功能域导入时不根据 Excel `一级功能点` 自动生成 FeatID。",
    "",
    "---",
    "",
    "## 术语表",
    "",
    "### 规格文档结构",
    "",
    "| 缩写 | 全称 | 中文 | 说明 |",
    "|------|------|------|------|",
    "| **US** | User Story | 用户故事 | 以“作为...我想要...以便...”格式描述用户需求。每个 US 包含多个 AC |",
    "| **AC** | Acceptance Criterion | 验收标准 | 每个 US 下的可验证行为描述。编号格式 `AC-<US号>.<序号>`，如 `AC-1.3` |",
    "| **BR** | Business Rule | 业务规则 | 领域语义约束，描述跨多个 US 的业务级规则 |",
    "| **FR** | Functional Rule | 功能规则 | 具体行为规则，描述单个可观察的功能行为 |",
    "| **ER** | Exception/Exemption Rule | 异常/豁免规则 | 边界条件、异常输入的处理规则 |",
    "| **RC** | Recovery Contract | 恢复契约 | 错误恢复路径和重置行为的契约描述 |",
    "",
    "### 设计文档结构",
    "",
    "| 缩写 | 全称 | 中文 | 说明 |",
    "|------|------|------|------|",
    "| **ADR** | Architecture Decision Record | 架构决策记录 | 记录关键设计决策，包含问题、推荐方案、替代方案、取舍理由、影响。格式：基线用 `ADR-N`（首个特性），后续特性用 `ADR-FX-N`（如 `ADR-F3-1`） |",
    "| **FuncID** | Functional Domain ID | 功能域编号 | 3 段数字标识（如 `04-03-01`），唯一标识一个功能域 |",
    "| **FeatID** | Feature ID | 特性编号 | `Feat-NN` 格式，功能域内唯一 |",
    "",
    "### 验证/测试",
    "",
    "| 缩写 | 全称 | 中文 | 说明 |",
    "|------|------|------|------|",
    "| **XTS** | X Test Suite | 兼容性测试套件 | OpenHarmony 兼容性测试，位于 `test/xts/` 目录 |",
    "| **Gherkin** | — | Gherkin 语法 | 行为驱动开发（BDD）的场景描述语言：`Given/When/Then` |",
    "| **VM** | Verification Mapping | 验证映射 | 每个 AC 到验证手段的映射表 |",
    "",
    "---",
    "",
    "## 文件命名规范",
    "",
    "| 文件类型 | 命名格式 | 示例 |",
    "|----------|----------|------|",
    "| 设计文档 | `design.md` | `04-common-capability/03-common-attributes/01-layout-attributes/design.md` |",
    "| 特性规格 | `Feat-NN-<name>-spec.md` | `04-common-capability/03-common-attributes/01-layout-attributes/Feat-03-flex-properties-spec.md` |",
    "| 索引文件 | `index.md` | `index.md`（本文件） |",
    "",
    "## 流程关联",
    "",
    "```",
    "新特性补录流程:",
    "  1. 在 registry/functions.yaml 中确认/创建 FuncID",
    "  2. 具体规格补录开始、功能点/特性范围明确后，在 registry/features.yaml 中追加 FeatID 记录；未生成规格时状态为待补充",
    "  3. 创建 <func-domain>/ 目录（如不存在）",
    "  4. 生成/更新 design.md，并将 functions.yaml 的 design 字段从空值改为路径",
    "  5. 生成 Feat-NN-<name>-spec.md，并将 features.yaml 的 spec 字段从空值改为路径",
    "  6. 更新 features.yaml 特性状态为 Draft 或 Baselined",
    "  7. 运行 tools/generate_index.py 重新生成 index.md",
    "```",
]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="fail if index.md is not up to date")
    parser.add_argument("--output", type=Path, default=INDEX_FILE, help="output path, defaults to index.md")
    args = parser.parse_args()

    try:
        functions_data = load_yaml(FUNCTIONS_FILE)
        features_data = load_yaml(FEATURES_FILE)
        top_levels = functions_data.get("top_levels", [])
        functions = functions_data.get("functions", [])
        features = features_data.get("features", [])
        validate(top_levels, functions, features)
        text = render_index(top_levels, functions, features)
    except Exception as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1

    output = args.output
    if args.check:
        if not output.exists():
            print(f"error: {output} does not exist", file=sys.stderr)
            return 1
        current = output.read_text(encoding="utf-8")
        if current != text:
            print(f"error: {output} is out of date; run tools/generate_index.py", file=sys.stderr)
            return 1
        print(f"{output.relative_to(ROOT)} is up to date")
        return 0

    output.write_text(text, encoding="utf-8")
    print(f"generated {output.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
