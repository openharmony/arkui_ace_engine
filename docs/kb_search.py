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
知识库索引检索工具。通过关键字搜索 docs/knowledge_base_INDEX.json，
返回匹配的知识库条目（名称、路径、关键词、源码路径等）。

用法:
  python3 docs/kb_search.py <关键字>              # 模糊搜索（name/name_cn/keywords/aliases/category）
  python3 docs/kb_search.py <关键字> --field name  # 限定搜索字段
  python3 docs/kb_search.py --category component   # 按分类过滤
  python3 docs/kb_search.py --list-categories      # 列出所有分类
  python3 docs/kb_search.py --list-all             # 列出所有知识库名称

脚本位于仓根目录执行，或通过相对路径 docs/kb_search.py 调用。
"""

import json
import sys
import argparse
from pathlib import Path


def load_index(script_path: str) -> list:
    """加载知识库索引 JSON。"""
    index_path = Path(script_path).resolve().parent / "knowledge_base_INDEX.json"
    if not index_path.exists():
        print(f"错误: 索引文件不存在 {index_path}", file=sys.stderr)
        sys.exit(1)
    with open(index_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    return data.get("knowledge_bases", [])


def match_entry(entry: dict, keyword: str, field: str = None) -> bool:
    """判断条目是否匹配关键字。"""
    keyword_lower = keyword.lower()

    src = entry.get("source_paths", {})
    api = entry.get("api_paths", {})
    search_fields = {
        "name": [entry.get("name", "")],
        "name_cn": [entry.get("name_cn", "")],
        "keywords": entry.get("keywords", []),
        "aliases": entry.get("aliases", []),
        "category": [entry.get("category", "")],
        "type": [entry.get("type", "")],
        "source_paths": list(src.keys()) + list(src.values()),
        "api_paths": list(api.keys()) + list(api.values()),
    }

    if field:
        targets = search_fields.get(field, [])
        return any(keyword_lower in str(v).lower() for v in targets)

    # 全字段模糊搜索
    all_values = []
    for values in search_fields.values():
        all_values.extend(values)
    return any(keyword_lower in str(v).lower() for v in all_values)


def format_entry(entry: dict, index: int) -> str:
    """格式化输出单个条目。"""
    lines = []
    lines.append(f"--- [{index}] {entry.get('name', 'N/A')} ({entry.get('name_cn', 'N/A')}) ---")
    lines.append(f"  分类: {entry.get('category', 'N/A')} | 类型: {entry.get('type', 'N/A')}")
    lines.append(f"  知识库: docs/{entry.get('file_path', 'N/A')}")

    src = entry.get("source_paths", {})
    if src:
        src_items = [f"{k}: {v}" for k, v in src.items()]
        lines.append(f"  源码: {', '.join(src_items)}")

    api = entry.get("api_paths", {})
    if api:
        api_items = [f"{k}: {v}" for k, v in api.items()]
        lines.append(f"  API: {', '.join(api_items)}")

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
    parser.add_argument("--field", help="限定搜索字段 (name/name_cn/keywords/aliases/category/type/source_paths/api_paths)")
    parser.add_argument("--category", help="按分类过滤（如 component, layout）")
    parser.add_argument("--list-categories", action="store_true", help="列出所有分类")
    parser.add_argument("--list-all", action="store_true", help="列出所有知识库名称")
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

    results = []
    for entry in entries:
        if args.category and entry.get("category", "").lower() != args.category.lower():
            continue
        if match_entry(entry, args.keyword, args.field):
            results.append(entry)

    if not results:
        print(f"未找到匹配 '{args.keyword}' 的知识库条目。")
        print("提示: 使用 --list-all 查看所有条目，或使用 --list-categories 查看分类。")
        return

    print(f"找到 {len(results)} 个匹配条目:\n")
    for i, entry in enumerate(results, 1):
        print(format_entry(entry, i))
        print()


if __name__ == "__main__":
    main()
