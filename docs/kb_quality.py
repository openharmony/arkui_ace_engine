#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ArkUI KB 质量评分脚本（docs/kb_quality.py）。

对 docs/kb/ 下所有 KB 按检查项分维度打分（满分 100），输出得分与不达标清单。
与 docs/validate_context.py 互补：validate_context 做硬约束（error/warn，CI gate），
本脚本做质量评分与格式一致性检查（不阻断，供各模块责任人认领修复）。

评分维度（满分 100）：
  A 结构完整性 30分  必填章节齐全（知识型/issue型/component型各有必填集）
  B 元数据头部 10分  文档版本/更新时间/来源、标题格式
  C 路径规范   25分  无绝对路径/无行号引用/无旧OpenHarmony前缀/相关主题链接可达
  D 内容质量   20分  定位段充实/表格说明列非空/常见问题≥3行/组件化结论/issue模块取值
  E 索引一致性 10分  registry有对应条目/仓内源码路径存在(智能豁免通配符/外部仓/外部依赖入口章节)
  F 命名规范    5分  文件名 kebab-case

Usage:
  python3 docs/kb_quality.py                  # 评分总览 + 扣分排行 + 失效链接统计
  python3 docs/kb_quality.py --detail         # 每个 KB 的扣分明细（定位修复项）
  python3 docs/kb_quality.py --min 90         # 仅列出 <90 分的待修 KB
  python3 docs/kb_quality.py --links         # 输出失效 .md 引用明细（链接检查）
  python3 docs/kb_quality.py --report <path>  # 导出 markdown 报告到文件

责任人使用：
  1. 跑 `python3 docs/kb_quality.py --min 90` 查看本人负责的低分 KB
  2. 跑 `python3 docs/kb_quality.py --detail` 看扣分明细，按维度认领修复
  3. 修后重跑确认分数提升；`python3 docs/validate_context.py` 确认无硬约束 error
  4. 失效链接用 `--links` 查看（区分"specs仓未同步"与"路径错"）
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

REPO = Path(__file__).resolve().parents[1]
DOCS = REPO / "docs"
KB_DIR = DOCS / "kb"
REGISTRY = DOCS / "context_registry.json"

# 知识型必填章节
KB_SECTIONS = [
    "## 定位", "## 快速路由", "### 源码入口", "### API 入口",
    "### 测试入口", "## 常见问题定位", "## 调试入口", "## 相关主题",
]
KB_SECTIONS_COMPONENT = ["### API 解析实现路径", "### 相关 Spec"]
KB_SECTIONS_ISSUE = [
    "## 问题概述", "## 关联模块", "## 根因分类", "## 排查路径",
    "## 修复方案", "## 关联变更", "## 预防措施", "## 相关主题",
]

ALLOWED_ISSUE_KIND = {"component", "capability", "architecture"}
ALLOWED_ISSUE_ROLE = {"symptom_surface", "trigger", "root_cause_owner", "fix_location", "dependency"}

# 已知外部仓路径前缀（ace_engine 仓内不存在，属合法跨仓引用）
EXTERNAL_PREFIXES = (
    "frameworks/text/", "frameworks/resmgr", "interfaces/innerkits/",
    "interfaces/api/", "interfaces/kits/", "frameworks/native/",
)
# 仓内路径前缀（需存在性检查）
INTERNAL_PREFIXES = ("frameworks/", "interfaces/", "adapter/", "test/")


@dataclass
class Score:
    kb_path: str
    kind: str
    got: int = 0
    total: int = 100
    deductions: list[tuple[str, int, str]] = field(default_factory=list)

    @property
    def score(self) -> float:
        return round(self.got / self.total * 100, 1) if self.total else 0.0


def load_registry() -> dict:
    try:
        with REGISTRY.open(encoding="utf-8") as f:
            return json.load(f)
    except Exception:
        return {}


def kb_to_registry_map(reg: dict) -> dict[str, dict]:
    m = {}
    for c in reg.get("contexts", []):
        kb = c.get("kb")
        if isinstance(kb, str):
            m[kb] = c
    return m


def is_kebab(name: str) -> bool:
    stem = name.rsplit(".", 1)[0]
    return bool(re.fullmatch(r"[a-z0-9]+(-[a-z0-9]+)*", stem))


def classify_path(p: str) -> str:
    """分类路径：WILDCARD/PLACEHOLDER/COMBINED/DIRECTORY/EXTERNAL/SPEC/INTERNAL。"""
    if "*" in p:
        return "WILDCARD"
    if "<" in p or ">" in p:
        return "PLACEHOLDER"
    # .h/.cpp、.h/cpp 合并形式
    if re.search(r"\.(?:h|cpp|ts|ets|js)/\.(?:h|cpp|ts|ets|js)$", p):
        return "COMBINED"
    if p.endswith("/"):
        return "DIRECTORY"
    last = p.rsplit("/", 1)[-1]
    if "/" in p and "." not in last:
        return "DIRECTORY"
    if p.startswith("specs/"):
        return "SPEC"
    if any(p.startswith(x) for x in EXTERNAL_PREFIXES):
        return "EXTERNAL"
    return "INTERNAL"


def extract_table_rows(text: str, section: str) -> list[list[str]]:
    idx = text.find(section)
    if idx < 0:
        return []
    sub = text[idx:]
    lines = sub.splitlines()
    rows = []
    header_seen = False
    for ln in lines[1:]:
        s = ln.strip()
        if s.startswith("#"):
            break
        if s.startswith("|") and s.endswith("|"):
            if not header_seen:
                header_seen = True
                continue
            if re.fullmatch(r"\|[\s:|-]+\|", s):
                continue
            rows.append([c.strip() for c in s.strip("|").split("|")])
    return rows


def count_empty_explain(rows: list[list[str]]) -> tuple[int, int]:
    total = empty = 0
    for r in rows:
        if len(r) < 2:
            continue
        total += 1
        last = r[-1]
        if last in ("", "-", "—", "N/A", "n/a"):
            empty += 1
    return empty, total


def find_internal_paths(text: str, in_external_section: bool) -> list[str]:
    """提取需存在性检查的仓内路径（排除通配符/占位符/合并/目录/外部仓/specs）。"""
    paths = set()
    for m in re.finditer(r"(?<![A-Za-z0-9/-])`?((?:frameworks|interfaces|adapter|test)/[^\s`:：|,，)（]+)`?", text):
        p = m.group(1)
        if p.startswith("docs/"):
            continue
        cat = classify_path(p)
        if cat in ("WILDCARD", "PLACEHOLDER", "COMBINED", "DIRECTORY", "EXTERNAL", "SPEC"):
            continue
        # 外部依赖入口章节内的路径豁免
        if in_external_section:
            continue
        paths.add(p)
    return list(paths)


def section_text(text: str, section: str) -> str:
    """提取某 ##/### 章节正文（到下一章节为止）。"""
    idx = text.find(section)
    if idx < 0:
        return ""
    sub = text[idx:]
    parts = re.split(r"\n(#{2,3} )", sub, maxsplit=1)
    return parts[0] if len(parts) >= 1 else ""


def score_kb(rel_path: str, text: str, kind: str | None, reg_entry: dict | None) -> Score:
    sc = Score(kb_path=rel_path, kind=kind or "unknown")
    is_issue = kind == "issue"
    is_component = kind == "component"

    # A. 结构完整性 30分
    A_MAX = 30
    a_got = A_MAX
    required = KB_SECTIONS_ISSUE if is_issue else KB_SECTIONS
    for s in required:
        if s not in text:
            sc.deductions.append(("A 结构", 3, f"缺章节 {s}"))
            a_got -= 3
    if is_component:
        for s in KB_SECTIONS_COMPONENT:
            if s not in text:
                sc.deductions.append(("A 结构", 3, f"缺组件章节 {s}"))
                a_got -= 3
    sc.got += max(0, a_got)

    # B. 元数据与头部 10分
    B_MAX = 10
    b_got = B_MAX
    head = "\n".join(text.splitlines()[:10])
    for marker in ["文档版本", "更新时间", "来源"]:
        if marker not in head:
            sc.deductions.append(("B 元数据", 2, f"头部缺 {marker}"))
            b_got -= 2
    title = text.splitlines()[0] if text else ""
    if not title.startswith("# "):
        sc.deductions.append(("B 元数据", 2, "无一级标题"))
        b_got -= 2
    elif "知识库" in title:
        sc.deductions.append(("B 元数据", 2, "标题用旧'知识库'命名"))
        b_got -= 2
    elif not (title.endswith("Context") or "Issue Context" in title):
        sc.deductions.append(("B 元数据", 1, "标题不以 Context 结尾"))
        b_got -= 1
    sc.got += max(0, b_got)

    # C. 路径规范 25分(知识型) / 15分(issue)
    C_MAX = 15 if is_issue else 25
    c_got = C_MAX
    if re.search(r"/home/\S+|/Users/\S+|/root/\S+", text):
        sc.deductions.append(("C 路径", 5, "含本机绝对路径"))
        c_got -= 5
    # 行号引用（含冒号/逗号/同文件三种格式，issue 不豁免）
    line_refs = re.findall(r"\.(?:cpp|h|ts|ets|js|yaml|gn|gni|json|py)[:,]\d+|`:\d+(?:-\d+)?|\(:\d+[^)]*\)", text)
    if line_refs:
        sc.deductions.append(("C 路径", 8, f"正文带行号引用({len(line_refs)}处)，违反 README 规范"))
        c_got -= 8
    if re.search(r"`OpenHarmony/", text):
        sc.deductions.append(("C 路径", 4, "用旧 OpenHarmony/ 前缀路径"))
        c_got -= 4
    # 相关主题链接可达性
    related_idx = text.rfind("## 相关主题")
    if related_idx >= 0:
        related_text = text[related_idx:]
        for lk in re.findall(r"\]\(([^)]+\.md)\)", related_text):
            if lk.startswith(("http", "#")):
                continue
            target = (REPO / lk) if lk.startswith("docs/") else (KB_DIR / rel_path.replace("docs/kb/", "")).parent.resolve() / lk
            if not target.exists():
                sc.deductions.append(("C 路径", 2, f"相关主题链接失效: {lk}"))
                c_got -= 2
        for ln in related_text.splitlines()[1:]:
            s = ln.strip()
            if not s.startswith(("-", "*")) or ".md" in s or "http" in s:
                continue
            item = re.sub(r'^[-*]\s+', '', s, count=1).strip()
            # 豁免：代码路径/spec 路径引用项（非 KB 链接）
            if "`frameworks/" in s or "`specs/" in s or "<OH_ROOT>" in s or "`interface" in s or "`docs/" in s:
                continue
            # 豁免：已有说明文字的概念项（含 ：/ — / - 分隔说明）或加粗概念名
            if any(sep in item for sep in ["：", " — ", " - ", "（", "(", "功能域", "见上方", "子系统"]) or item.startswith("**"):
                continue
            sc.deductions.append(("C 路径", 1, f"相关主题项无路径: {s[:40]}"))
            c_got -= 1
    sc.got += max(0, c_got)

    # D. 内容质量 20分(知识型) / 25分(issue)
    D_MAX = 25 if is_issue else 20
    d_got = D_MAX
    loc = section_text(text, "## 定位")
    if loc:
        clean = re.sub(r"[#|`>*\-\s]", "", loc)
        if len(clean) < 60:
            sc.deductions.append(("D 内容", 4, "定位段过短(<60字)"))
            d_got -= 4
    for sec, dim, pt in [("### 测试入口", "测试入口", 4), ("### 源码入口", "源码入口", 3)]:
        rows = extract_table_rows(text, sec)
        if rows:
            empty, total = count_empty_explain(rows)
            if total and empty / total > 0.5:
                sc.deductions.append(("D 内容", pt, f"{dim}说明列空率{empty}/{total}"))
                d_got -= pt
    if not is_issue:
        faq_rows = extract_table_rows(text, "## 常见问题定位")
        if len(faq_rows) < 3:
            sc.deductions.append(("D 内容", 3, f"常见问题定位仅{len(faq_rows)}行(<3)"))
            d_got -= 3
    if is_component:
        api_impl = text.find("### API 解析实现路径")
        if api_impl >= 0 and "组件化" not in text[api_impl:api_impl + 800]:
            sc.deductions.append(("D 内容", 2, "API解析实现路径缺组件化结论"))
            d_got -= 2
    if is_issue:
        mod_rows = extract_table_rows(text, "## 关联模块")
        bad_kind = sum(1 for r in mod_rows if len(r) >= 2 and r[0] and r[0] not in ALLOWED_ISSUE_KIND)
        bad_role = sum(1 for r in mod_rows if len(r) >= 3 and r[1] and r[1] not in ALLOWED_ISSUE_ROLE)
        if bad_kind:
            sc.deductions.append(("D 内容", 2, f"关联模块 kind 违规 {bad_kind}处"))
            d_got -= 2
        if bad_role:
            sc.deductions.append(("D 内容", 2, f"关联模块 role 违规 {bad_role}处"))
            d_got -= 2
    sc.got += max(0, d_got)

    # E. 索引一致性 10分
    E_MAX = 10
    e_got = E_MAX
    if not reg_entry:
        sc.deductions.append(("E 索引", 5, "registry 无对应条目(孤儿文档)"))
        e_got -= 5
    else:
        # 仓内路径存在性（智能分类：跳过合法简写与外部依赖入口章节内）
        ext_section = section_text(text, "### 外部依赖入口")
        paths = find_internal_paths(text, in_external_section=False)
        # 外部依赖入口章节内的路径单独豁免
        ext_paths = set(find_internal_paths(ext_section, in_external_section=False))
        missing = [p for p in paths if p not in ext_paths and not (REPO / p).exists()]
        if missing:
            sc.deductions.append(("E 索引", 3, f"仓内源码路径不存在({len(missing)}条): {missing[0]}"))
            e_got -= 3
    sc.got += max(0, e_got)

    # F. 命名规范 5分
    F_MAX = 5
    f_got = F_MAX
    if not is_kebab(Path(rel_path).name):
        sc.deductions.append(("F 命名", 5, f"文件名非 kebab-case: {Path(rel_path).name}"))
        f_got -= 5
    sc.got += f_got

    sc.total = A_MAX + B_MAX + C_MAX + D_MAX + E_MAX + F_MAX
    return sc


# 失效链接豁免项：这些引用指向 spec/概念文档，属 spec 作者或决策责任，不计 KB 扣分
LINK_EXEMPT = ("组件化重构通用方案", "AGENTS.md")


def find_broken_links() -> list[tuple[str, str, str]]:
    """扫描所有 KB 的 .md 引用，返回 (kb, ref, 类别) 失效清单。
    路径解析：specs/ docs/ 用仓库根；纯文件名先相对当前目录再 spec_domain；有斜杠相对当前目录。"""
    import os
    LINK_RE_LOCAL = re.compile(r"\[([^\]]*)\]\(([^)]+\.md)\)")
    BACKTICK_RE_LOCAL = re.compile(r"`([^`]*\.md)`")
    broken: list[tuple[str, str, str]] = []
    for f in sorted(KB_DIR.rglob("*.md")):
        if f.name == "README.md":
            continue
        rel = str(f.relative_to(REPO))
        text = f.read_text(encoding="utf-8")
        src_dir = f.parent
        entry = kb_to_registry_map(load_registry()).get(rel)
        spec_domain = entry.get("spec_domain") if entry else None
        refs: set[str] = set()
        for m in LINK_RE_LOCAL.finditer(text):
            refs.add(m.group(2))
        for m in BACKTICK_RE_LOCAL.finditer(text):
            refs.add(m.group(1))
        for ref in refs:
            if ref.startswith(("http", "#", "mailto:")):
                continue
            if any(x in ref for x in LINK_EXEMPT):
                continue  # 概念文档，豁免
            if ref.startswith(("specs/", "docs/")):
                target = REPO / ref
            elif "/" not in ref:
                t1 = src_dir / ref
                if t1.exists():
                    continue
                if spec_domain and (REPO / spec_domain / ref).exists():
                    continue
                target = t1
            else:
                target = (src_dir / ref).resolve()
            if not target.exists():
                cat = "specs仓未同步或KB文件名写错" if ref.startswith(("specs/", "Feat-", "arkui-specs/")) or ref == "design.md" else "路径错"
                broken.append((rel, ref, cat))
    return broken


def run(min_score: float = 0, detail: bool = False, report: str | None = None,
        links: bool = False) -> int:
    reg = load_registry()
    kmap = kb_to_registry_map(reg)
    kb_files = [f for f in sorted(KB_DIR.rglob("*.md")) if f.name != "README.md"]
    scores: list[Score] = []
    for f in kb_files:
        rel = str(f.relative_to(REPO))
        try:
            text = f.read_text(encoding="utf-8")
        except Exception as e:
            scores.append(Score(rel, "error", 0, 100, [("Z", 100, f"读取失败 {e}")]))
            continue
        entry = kmap.get(rel)
        kind = entry.get("kind") if entry else None
        scores.append(score_kb(rel, text, kind, entry))

    scores.sort(key=lambda s: s.score)
    total = len(scores)
    avg = sum(s.score for s in scores) / total if total else 0
    by_kind: dict[str, list[Score]] = {}
    for s in scores:
        by_kind.setdefault(s.kind, []).append(s)

    out: list[str] = []
    out.append("=" * 70)
    out.append("ArkUI KB 质量评分报告")
    out.append("=" * 70)
    out.append(f"\n【总览】KB 数: {total}  平均分: {avg:.1f}")
    out.append(f"  >=90: {sum(1 for s in scores if s.score >= 90)}  "
               f"80-89: {sum(1 for s in scores if 80 <= s.score < 90)}  "
               f"70-79: {sum(1 for s in scores if 70 <= s.score < 80)}  "
               f"<70: {sum(1 for s in scores if s.score < 70)}")
    out.append("\n【按 kind 分组】")
    for k in sorted(by_kind):
        ss = by_kind[k]
        a = sum(s.score for s in ss) / len(ss)
        out.append(f"  {k or 'unknown':<18} 数量 {len(ss):>3}  平均 {a:>5.1f}  最低 {min(s.score for s in ss):>5.1f}")

    # 检查项命中统计
    hit: dict[str, list[tuple[int, str]]] = {}
    for s in scores:
        for dim, pt, reason in s.deductions:
            key = reason.split("(")[0].split("：")[0].split("缺")[0].split("率")[0].strip()
            key = f"{dim}: {key}"
            hit.setdefault(key, []).append((pt, s.kb_path))
    out.append("\n【检查项命中统计 - 扣分最多的项】")
    for key, items in sorted(hit.items(), key=lambda kv: sum(p[0] for p in kv[1]), reverse=True)[:20]:
        total_pt = sum(p[0] for p in items)
        out.append(f"  [{total_pt:>4}分/{len(items):>3}处] {key}")

    # 失效链接检查
    broken_links = find_broken_links()
    out.append(f"\n【失效 .md 引用检查】共 {len(broken_links)} 处")
    from collections import Counter
    lcat = Counter(c for _, _, c in broken_links)
    for c, n in lcat.most_common():
        out.append(f"  {n:>3}  {c}")
    if links:
        out.append("\n  失效链接明细：")
        for kb, ref, cat in sorted(broken_links):
            out.append(f"    [{cat}] {kb}  ->  {ref}")

    filtered = [s for s in scores if s.score < min_score] if min_score else scores
    if detail or min_score:
        out.append(f"\n【得分明细{'(<' + str(min_score) + ')' if min_score else ''}】")
        for s in filtered:
            out.append(f"\n  {s.score:>5.1f}  {s.kb_path}  [{s.kind}]")
            for dim, pt, reason in s.deductions:
                out.append(f"          - [{dim}-{pt}] {reason}")

    text_out = "\n".join(out)
    print(text_out)

    if report:
        rp = Path(report)
        with rp.open("w", encoding="utf-8") as f:
            f.write("# ArkUI KB 质量评分报告\n\n")
            f.write(f"KB 总数: {total}  平均分: {avg:.1f}\n\n")
            f.write("## 按 kind 分组\n\n| kind | 数量 | 平均分 | 最低分 | <70数 |\n|---|---|---|---|---|\n")
            for k in sorted(by_kind):
                ss = by_kind[k]
                a = sum(s.score for s in ss) / len(ss)
                low = sum(1 for s in ss if s.score < 70)
                f.write(f"| {k or 'unknown'} | {len(ss)} | {a:.1f} | {min(s.score for s in ss):.1f} | {low} |\n")
            f.write("\n## 全量得分明细\n\n| 得分 | kind | KB路径 | 扣分明细 |\n|---|---|---|---|\n")
            for s in scores:
                reasons = "<br>".join(f"[{d[0]}-{d[1]}] {d[2]}" for d in s.deductions)
                f.write(f"| {s.score} | {s.kind} | `{s.kb_path}` | {reasons} |\n")
        print(f"\n详细报告已写入: {rp}")
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="ArkUI KB 质量评分")
    parser.add_argument("--detail", action="store_true", help="打印每个 KB 的扣分明细")
    parser.add_argument("--report", help="输出 markdown 报告到文件")
    parser.add_argument("--min", type=float, default=0, help="仅列出低于此分数的 KB")
    parser.add_argument("--links", action="store_true", help="输出失效 .md 引用明细")
    args = parser.parse_args(argv)
    return run(min_score=args.min, detail=args.detail, report=args.report, links=args.links)


if __name__ == "__main__":
    sys.exit(main())
