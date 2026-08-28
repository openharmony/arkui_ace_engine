#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2026 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
知识库索引检索工具。搜索 docs/context_registry.json，
返回匹配的知识库条目。

默认搜索字段: name / name_cn / keywords / aliases（精简搜索，减少噪声）
默认输出: 一行一个结果，最多 10 条（按相关度排序）

  --detail   查看完整路由信息（源码/API/测试/Spec 等）
  --all      显示全部结果（不限 10 条）
  --field    限定搜索单个字段（含 source_paths/api_paths/test_paths 等扩展字段）

用法:
  python3 docs/kb_search.py <关键字>              # 精简搜索，最多 10 条
  python3 docs/kb_search.py <关键字> --detail     # 完整路由信息
  python3 docs/kb_search.py <关键字> --all        # 显示全部结果
  python3 docs/kb_search.py <关键字> --field name # 限定搜索字段
  python3 docs/kb_search.py <关键字> --category component
  python3 docs/kb_search.py --list-categories
  python3 docs/kb_search.py --list-all

脚本位于仓根目录执行，或通过相对路径 docs/kb_search.py 调用。
"""

import json
import sys
import argparse
from pathlib import Path


DEFAULT_LIMIT = 10


def normalize_registry_entry(entry: dict) -> dict:
    """将 context_registry 条目转换为检索结构。"""
    kb_path = entry.get("kb")
    file_path = ""
    if kb_path:
        file_path = kb_path[5:] if kb_path.startswith("docs/") else kb_path
    return {
        "name": entry.get("name", entry.get("id", "")),
        "name_cn": entry.get("name_cn", ""),
        "category": entry.get("category", ""),
        "type": entry.get("kind", entry.get("type", "")),
        "keywords": entry.get("keywords", []),
        "aliases": entry.get("aliases", []),
        "file_path": file_path,
        "spec_domain": entry.get("spec_domain"),
        "func_id": entry.get("func_id"),
        "source_paths": entry.get("source_paths", {}),
        "api_paths": entry.get("api_paths", {}),
        "test_paths": entry.get("test_paths", []),
        "last_updated": entry.get("last_verified", entry.get("last_updated", "")),
        "_source": "context_registry",
    }


def load_registry(script_path: str) -> list:
    """加载新版上下文 registry。"""
    registry_path = Path(script_path).resolve().parent / "context_registry.json"
    if not registry_path.exists():
        return []
    with open(registry_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    return [normalize_registry_entry(e) for e in data.get("contexts", [])]


def load_index(script_path: str) -> list:
    """加载 context_registry 条目。"""
    entries = load_registry(script_path)
    if not entries:
        print("错误: 未找到 docs/context_registry.json 或文件为空", file=sys.stderr)
        sys.exit(1)
    return entries


def _get_field_values(entry: dict, field: str) -> list:
    """获取指定字段的所有值列表。"""
    if field in ("source_paths", "api_paths"):
        d = entry.get(field, {})
        return list(d.keys()) + list(d.values())
    if field == "test_paths":
        return entry.get(field, [])
    if field == "spec_domain":
        return [entry.get("spec_domain", ""), entry.get("func_id", "")]
    if field in ("keywords", "aliases"):
        return entry.get(field, [])
    return [entry.get(field, "")]


def _score_string(value: str, keyword: str, exact: int, prefix: int, contains: int) -> int:
    """对单个字符串做模糊匹配打分。"""
    vl = str(value).lower()
    if vl == keyword:
        return exact
    if vl.startswith(keyword):
        return prefix
    if keyword in vl:
        return contains
    return 0


def score_entry(entry: dict, keyword: str, field: str = None) -> int:
    """计算条目与关键字的相关度得分，0 表示不匹配。

    默认仅搜索 identity 字段（name/name_cn/keywords/aliases/category/type）。
    指定 field 时只搜索该字段（可覆盖 source_paths/api_paths/test_paths 等扩展字段）。
    """
    kw = keyword.lower()

    if field:
        values = _get_field_values(entry, field)
        best = 0
        for v in values:
            best = max(best, _score_string(str(v), kw, exact=100, prefix=70, contains=40))
        return best

    best = 0
    name = str(entry.get("name", ""))
    best = max(best, _score_string(name, kw, exact=100, prefix=85, contains=65))

    name_cn = str(entry.get("name_cn", ""))
    best = max(best, _score_string(name_cn, kw, exact=75, prefix=55, contains=40))

    for v in entry.get("keywords", []):
        best = max(best, _score_string(str(v), kw, exact=70, prefix=55, contains=35))

    for v in entry.get("aliases", []):
        best = max(best, _score_string(str(v), kw, exact=50, prefix=40, contains=30))

    for key in ("category", "type"):
        best = max(best, _score_string(str(entry.get(key, "")), kw, exact=20, prefix=15, contains=10))

    return best


def format_compact(entry: dict, index: int) -> str:
    """一行精简格式。"""
    name = entry.get("name", "N/A")
    name_cn = entry.get("name_cn", "")
    fp = entry.get("file_path", "N/A")
    cn = f" ({name_cn})" if name_cn else ""
    return f"  {index:2d}. {name}{cn} -> docs/{fp}"


def format_detail(entry: dict, index: int, score: int = 0) -> str:
    """完整路由信息格式。"""
    lines = []
    score_tag = f" [score:{score}]" if score else ""
    lines.append(f"--- [{index}] {entry.get('name', 'N/A')} ({entry.get('name_cn', 'N/A')}){score_tag} ---")
    lines.append(f"  分类: {entry.get('category', 'N/A')} | 类型: {entry.get('type', 'N/A')}")
    lines.append(f"  知识库: docs/{entry.get('file_path', 'N/A')}")
    if entry.get("spec_domain"):
        lines.append(f"  Spec: {entry.get('func_id', 'N/A')} -> {entry.get('spec_domain')}")

    src = entry.get("source_paths", {})
    if src:
        src_items = [f"{k}: {v}" for k, v in src.items()]
        lines.append(f"  源码: {', '.join(src_items)}")

    api = entry.get("api_paths", {})
    if api:
        api_items = [f"{k}: {v}" for k, v in api.items()]
        lines.append(f"  API: {', '.join(api_items)}")

    tests = entry.get("test_paths", [])
    if tests:
        lines.append(f"  测试: {', '.join(tests)}")

    kw = entry.get("keywords", [])
    if kw:
        lines.append(f"  关键词: {', '.join(kw[:8])}{'...' if len(kw) > 8 else ''}")

    aliases = entry.get("aliases", [])
    if aliases:
        lines.append(f"  别名: {', '.join(aliases)}")

    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description="知识库索引检索工具")
    parser.add_argument("keyword", nargs="?", help="搜索关键字")
    parser.add_argument(
        "--field",
        help="限定搜索字段 (name/name_cn/keywords/aliases/category/type/spec_domain/test_paths/source_paths/api_paths)")
    parser.add_argument("--category", help="按分类过滤（如 component, layout）")
    parser.add_argument("--list-categories", action="store_true", help="列出所有分类")
    parser.add_argument("--list-all", action="store_true", help="列出所有知识库名称")
    parser.add_argument("--detail", action="store_true", help="显示完整路由信息（源码/API/测试等）")
    parser.add_argument("--all", action="store_true", help="显示全部结果（默认最多 %d 条）" % DEFAULT_LIMIT)
    args = parser.parse_args()

    entries = load_index(__file__)

    if args.list_categories:
        cats = sorted(set(e.get("category", "unknown") for e in entries))
        for c in cats:
            count = sum(1 for e in entries if e.get("category") == c)
            print(f"  {c} ({count} 个)")
        return

    if args.list_all:
        for i, e in enumerate(entries, 1):
            print(f"  {i:2d}. {e.get('name', 'N/A'):20s} | {e.get('name_cn', 'N/A'):15s} | {e.get('category', 'N/A')}")
        return

    if not args.keyword:
        parser.print_help()
        return

    scored = []
    for entry in entries:
        if args.category and entry.get("category", "").lower() != args.category.lower():
            continue
        score = score_entry(entry, args.keyword, args.field)
        if score > 0:
            scored.append((score, entry))

    if not scored:
        print(f"未找到匹配 '{args.keyword}' 的知识库条目。")
        print("提示: 使用 --list-all 查看所有条目，或使用 --list-categories 查看分类。")
        if not args.field:
            print("      使用 --field source_paths 按源码路径搜索。")
        return

    scored.sort(key=lambda x: (-x[0], x[1].get("name", "")))

    total = len(scored)
    limit = total if args.all else min(DEFAULT_LIMIT, total)
    shown = scored[:limit]
    formatter = format_detail if args.detail else format_compact

    if total > limit:
        print(f"找到 {total} 个匹配条目（显示前 {limit}，用 --all 查看全部）:\n")
    else:
        print(f"找到 {total} 个匹配条目:\n")

    for i, (score, entry) in enumerate(shown, 1):
        if args.detail:
            print(formatter(entry, i, score))
        else:
            print(formatter(entry, i))
        if args.detail:
            print()


if __name__ == "__main__":
    main()
