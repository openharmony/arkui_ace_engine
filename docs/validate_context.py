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
Validate ArkUI KB/Spec context routing.

The script checks docs/context_registry.json, the KB index,
registered Spec links, existing Feat specs, and lightweight KB pages. It is
designed for the migration period: confirmed invalid data is reported as an
error; legacy placeholders such as "待补充" are reported as warnings.
If the optional specs repository is not cloned at ./specs, Spec checks are
skipped with a warning.

Usage:
  python3 docs/validate_context.py
  python3 docs/validate_context.py --quiet
  python3 docs/validate_context.py --all-specs
  python3 docs/validate_context.py --warnings-as-errors
"""

import argparse
import json
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable


ALLOWED_CONTEXT_KINDS = {"component", "feature", "sdk", "architecture", "common_capability"}
ALLOWED_CONTEXT_STATUS = {"active", "draft", "deprecated"}
ALLOWED_SPEC_STATUS = {"Draft", "Baselined", "Deprecated"}
ALLOWED_REGISTRY_SPEC_STATUS = {"active", "pending"}
PLACEHOLDER_STATUS = {"待补充", "*待补充*"}
REQUIRED_CONTEXT_FIELDS = {
    "id",
    "name",
    "name_cn",
    "kind",
    "category",
    "keywords",
    "aliases",
    "kb",
    "spec_status",
    "status",
    "last_verified",
}

REQUIRED_KB_SECTIONS = [
    "## 定位",
    "## 快速路由",
    "### 源码入口",
    "### API 入口",
    "### 测试入口",
    "## 常见问题定位",
    "## 调试入口",
    "## 相关主题",
]

REQUIRED_KB_SECTIONS_COMPONENT = [
    "### API 解析实现路径",
    "### 相关 Spec",
]


@dataclass
class Finding:
    level: str
    path: str
    message: str


class Validator:
    def __init__(self, root: Path, quiet: bool = False, all_specs: bool = False) -> None:
        self.root = root
        self.docs_dir = root / "docs"
        self.specs_dir = root / "specs"
        self.quiet = quiet
        self.all_specs = all_specs
        self.findings: list[Finding] = []
        self.registry_ids: set[str] = set()
        self.registry_data: dict[str, Any] = {}
        self._missing_specs_reported = False

    def error(self, path: str | Path, message: str) -> None:
        self.findings.append(Finding("ERROR", str(path), message))

    def warn(self, path: str | Path, message: str) -> None:
        self.findings.append(Finding("WARN", str(path), message))

    def load_json(self, path: Path) -> Any:
        try:
            with path.open("r", encoding="utf-8") as file:
                return json.load(file)
        except FileNotFoundError:
            self.error(path, "file does not exist")
        except json.JSONDecodeError as exc:
            self.error(path, f"invalid JSON: {exc}")
        return None

    def repo_path_exists(self, path_text: str) -> bool:
        return (self.root / path_text).exists()

    def specs_available(self) -> bool:
        return self.specs_dir.is_dir() and (self.specs_dir / "index.md").is_file()

    def warn_missing_specs_once(self) -> None:
        if self._missing_specs_reported:
            return
        self.warn(
            self.specs_dir,
            "specs repository is not available; clone the specs repo separately at ./specs. "
            "Skipping Spec index, spec_domain, and Feat spec checks.")
        self._missing_specs_reported = True

    def validate(self) -> tuple[int, int]:
        self.validate_registry()
        self.validate_kb_index()
        if self.specs_available():
            self.validate_specs_index()
            self.validate_feat_specs()
        else:
            self.warn_missing_specs_once()
        self.validate_kb_content()
        return self.print_summary()

    def validate_registry(self) -> None:
        registry_path = self.docs_dir / "context_registry.json"
        data = self.load_json(registry_path)
        if not isinstance(data, dict):
            return
        self.registry_data = data
        contexts = data.get("contexts")
        if not isinstance(contexts, list):
            self.error(registry_path, "`contexts` must be a list")
            return

        seen: set[str] = set()
        for index, entry in enumerate(contexts):
            entry_path = f"docs/context_registry.json:contexts[{index}]"
            if not isinstance(entry, dict):
                self.error(entry_path, "context entry must be an object")
                continue

            missing = sorted(REQUIRED_CONTEXT_FIELDS - set(entry.keys()))
            if missing:
                self.error(entry_path, f"missing required fields: {', '.join(missing)}")

            context_id = entry.get("id")
            if not isinstance(context_id, str) or not context_id.strip():
                self.error(entry_path, "`id` must be a non-empty string")
                continue
            if context_id in seen:
                self.error(entry_path, f"duplicate id `{context_id}`")
            seen.add(context_id)
            self.registry_ids.add(context_id)

            self.validate_registry_entry(entry_path, entry)

    def validate_registry_entry(self, entry_path: str, entry: dict[str, Any]) -> None:
        kind = entry.get("kind")
        if kind not in ALLOWED_CONTEXT_KINDS:
            self.error(entry_path, f"`kind` must be one of {sorted(ALLOWED_CONTEXT_KINDS)}")

        status = entry.get("status")
        if status not in ALLOWED_CONTEXT_STATUS:
            self.error(entry_path, f"`status` must be one of {sorted(ALLOWED_CONTEXT_STATUS)}")

        self.validate_string_list(entry_path, entry, "keywords", min_count=1)
        self.validate_string_list(entry_path, entry, "aliases", min_count=1)

        kb = entry.get("kb")
        if kb is not None:
            if not isinstance(kb, str) or not kb.startswith("docs/"):
                self.error(entry_path, "`kb` must be null or a docs/ relative path")
            elif not self.repo_path_exists(kb):
                self.error(entry_path, f"`kb` path does not exist: {kb}")

        legacy_kb = entry.get("legacy_kb")
        if legacy_kb:
            if not isinstance(legacy_kb, str) or not legacy_kb.startswith("docs/"):
                self.error(entry_path, "`legacy_kb` must be a docs/ relative path")
            elif not self.repo_path_exists(legacy_kb):
                self.error(entry_path, f"`legacy_kb` path does not exist: {legacy_kb}")

        spec_domain = entry.get("spec_domain")
        func_id = entry.get("func_id")
        spec_status = entry.get("spec_status")
        if spec_status and spec_status not in ALLOWED_REGISTRY_SPEC_STATUS:
            self.error(entry_path, f"`spec_status` must be one of {sorted(ALLOWED_REGISTRY_SPEC_STATUS)}")
        if spec_domain:
            if not isinstance(spec_domain, str) or not spec_domain.startswith("specs/"):
                self.error(entry_path, "`spec_domain` must be a specs/ relative path")
            elif self.specs_available():
                if not self.repo_path_exists(spec_domain):
                    if spec_status == "pending":
                        self.warn(entry_path, f"`spec_domain` path not yet created (spec_status=pending): {spec_domain}")
                    else:
                        self.error(entry_path, f"`spec_domain` path does not exist: {spec_domain}")
                else:
                    self.validate_spec_domain_registered(entry_path, spec_domain, func_id)
                    if spec_status == "pending":
                        self.warn(entry_path, "`spec_status` is 'pending' but `spec_domain` path exists; consider updating to 'active'")
            else:
                self.warn_missing_specs_once()

        if kind == "component":
            if not spec_domain:
                self.warn(entry_path, "component entry is missing `spec_domain`")
            if not func_id:
                self.warn(entry_path, "component entry is missing `func_id`")
        else:
            if spec_domain and not func_id:
                self.warn(entry_path, "`spec_domain` is set but `func_id` is missing; they should be paired")
            if func_id and not spec_domain:
                self.warn(entry_path, "`func_id` is set but `spec_domain` is missing; they should be paired")

        for key in ("source_paths", "api_paths"):
            paths = entry.get(key, {})
            if paths is not None and not isinstance(paths, dict):
                self.error(entry_path, f"`{key}` must be an object")
                continue
            for name, value in paths.items():
                if not isinstance(value, str) or not value:
                    self.error(entry_path, f"`{key}.{name}` must be a non-empty string")
                    continue
                self.validate_routed_path(entry_path, key, name, value, require_internal=(key == "source_paths"))

        test_paths = entry.get("test_paths", [])
        if test_paths is not None and not isinstance(test_paths, list):
            self.error(entry_path, "`test_paths` must be a list")
        else:
            for idx, value in enumerate(test_paths or []):
                if not isinstance(value, str) or not value:
                    self.error(entry_path, f"`test_paths[{idx}]` must be a non-empty string")
                elif value.startswith("<OH_ROOT>/"):
                    self.warn(entry_path, f"`test_paths[{idx}]` points outside ace_engine and is not existence-checked")
                elif not self.repo_path_exists(value):
                    self.error(entry_path, f"`test_paths[{idx}]` path does not exist: {value}")

    def validate_string_list(self, entry_path: str, entry: dict[str, Any], key: str, min_count: int) -> None:
        values = entry.get(key)
        if not isinstance(values, list):
            self.error(entry_path, f"`{key}` must be a list")
            return
        if len(values) < min_count:
            self.error(entry_path, f"`{key}` must contain at least {min_count} item(s)")
        for index, value in enumerate(values):
            if not isinstance(value, str) or not value:
                self.error(entry_path, f"`{key}[{index}]` must be a non-empty string")

    def validate_routed_path(self, entry_path: str, group: str, name: str, value: str, require_internal: bool) -> None:
        if value.startswith("<OH_ROOT>/"):
            if len(value) <= len("<OH_ROOT>/"):
                self.error(entry_path, f"`{group}.{name}` has an empty <OH_ROOT> path")
            return
        if value.startswith("/"):
            self.error(entry_path, f"`{group}.{name}` must not use host absolute paths: {value}")
            return
        if require_internal and not self.repo_path_exists(value):
            self.error(entry_path, f"`{group}.{name}` path does not exist: {value}")
        if not require_internal and not self.repo_path_exists(value) and not value.startswith("interfaces/"):
            self.warn(entry_path, f"`{group}.{name}` is not <OH_ROOT> and was not found: {value}")

    def validate_spec_domain_registered(self, entry_path: str, spec_domain: str, func_id: Any) -> None:
        index_path = self.specs_dir / "index.md"
        if not index_path.exists():
            self.error(entry_path, "spec_domain is set but specs/index.md does not exist")
            return
        index_text = index_path.read_text(encoding="utf-8")
        domain_without_prefix = spec_domain.removeprefix("specs/").rstrip("/") + "/"
        if domain_without_prefix not in index_text:
            self.error(entry_path, f"`spec_domain` is not registered in specs/index.md: {spec_domain}")
        if func_id and str(func_id) not in index_text:
            self.error(entry_path, f"`func_id` is not registered in specs/index.md: {func_id}")

    def validate_kb_index(self) -> None:
        index_path = self.docs_dir / "knowledge_base_INDEX.json"
        data = self.load_json(index_path)
        if not isinstance(data, dict):
            return
        entries = data.get("knowledge_bases")
        if not isinstance(entries, list):
            self.error(index_path, "`knowledge_bases` must be a list")
            return

        for index, entry in enumerate(entries):
            entry_path = f"docs/knowledge_base_INDEX.json:knowledge_bases[{index}]"
            if not isinstance(entry, dict):
                self.error(entry_path, "entry must be an object")
                continue
            file_path = entry.get("file_path")
            if not isinstance(file_path, str) or not file_path:
                self.error(entry_path, "`file_path` must be a non-empty string")
            elif not (self.docs_dir / file_path).exists():
                self.error(entry_path, f"`file_path` does not exist: docs/{file_path}")

    def validate_specs_index(self) -> None:
        if not self.specs_available():
            self.warn_missing_specs_once()
            return
        index_path = self.specs_dir / "index.md"
        text = index_path.read_text(encoding="utf-8")

        for link_target in sorted(set(re.findall(r"\]\(([^)]+\.md)\)", text))):
            target = self.specs_dir / link_target
            if not target.exists():
                self.error(index_path, f"registered Spec link does not exist: {link_target}")

        for line_no, line in enumerate(text.splitlines(), 1):
            if not line.startswith("| Feat-"):
                continue
            cells = [cell.strip() for cell in line.strip().strip("|").split("|")]
            if len(cells) < 4:
                self.error(f"specs/index.md:{line_no}", "Feat row must have at least 4 columns")
                continue
            status = cells[3]
            spec_cell = cells[2]
            if status in PLACEHOLDER_STATUS or "待补充" in spec_cell:
                self.warn(f"specs/index.md:{line_no}", "Feat row is still a placeholder")
                continue
            if status not in ALLOWED_SPEC_STATUS:
                self.error(f"specs/index.md:{line_no}", f"invalid Spec status `{status}`")

    def validate_feat_specs(self) -> None:
        if not self.specs_available():
            self.warn_missing_specs_once()
            return
        for spec_path in self.feat_spec_paths():
            rel_path = spec_path.relative_to(self.root)
            text = spec_path.read_text(encoding="utf-8")
            status, raw_status = self.extract_status(text)
            if not status:
                self.error(rel_path, "missing status row, expected `| 状态 | <status> |`")
            elif status not in ALLOWED_SPEC_STATUS:
                self.error(rel_path, f"invalid status `{raw_status}`")
            elif raw_status and raw_status != status:
                self.warn(rel_path, f"status `{raw_status}` contains annotation; normalized to `{status}`")

            if "## context-references" not in text:
                self.error(rel_path, "missing `## context-references` section")
            if not re.search(r"\bAC-\d+", text):
                self.error(rel_path, "missing AC entries")
            if not re.search(r"\bVM-\d+", text):
                self.error(rel_path, "missing VM entries")
            if status == "Baselined":
                self.validate_no_baselined_placeholders(rel_path, text)
            self.validate_registry_id_references(rel_path, text)

    def feat_spec_paths(self) -> list[Path]:
        if self.all_specs:
            return sorted(self.specs_dir.rglob("Feat-*.md"))
        roots: list[Path] = []
        for entry in self.registry_data.get("contexts", []):
            if not isinstance(entry, dict):
                continue
            spec_domain = entry.get("spec_domain")
            if isinstance(spec_domain, str) and spec_domain.startswith("specs/"):
                root = self.root / spec_domain
                if root.exists():
                    roots.append(root)
        paths: set[Path] = set()
        for root in roots:
            paths.update(root.rglob("Feat-*.md"))
        return sorted(paths)

    def extract_status(self, text: str) -> tuple[str | None, str | None]:
        match = re.search(r"^\|\s*状态\s*\|\s*([^|]+?)\s*\|", text, flags=re.MULTILINE)
        if match:
            raw_status = match.group(1).strip()
            return self.normalize_status(raw_status), raw_status
        match = re.search(r"^\s*status\s*:\s*([A-Za-z]+)\s*$", text, flags=re.MULTILINE)
        if match:
            raw_status = match.group(1).strip()
            return self.normalize_status(raw_status), raw_status
        return None, None

    def normalize_status(self, raw_status: str) -> str | None:
        for status in ALLOWED_SPEC_STATUS:
            if raw_status == status or raw_status.startswith(status):
                return status
        return raw_status

    def validate_no_baselined_placeholders(self, rel_path: Path, text: str) -> None:
        for line_no, line in enumerate(text.splitlines(), 1):
            if not re.search(r"TODO|TBD|待定", line):
                continue
            # Self-check lines document the absence of placeholders and are not placeholders.
            if "无" in line and "占位符" in line:
                continue
            if "不允许存在" in line:
                continue
            self.error(f"{rel_path}:{line_no}", "Baselined spec contains placeholder text")

    def validate_registry_id_references(self, rel_path: Path, text: str) -> None:
        # Supported explicit forms: registry id: Text, registry-id: Text,
        # registry_id: Text, context id: Text, context-id: Text.
        pattern = re.compile(r"\b(?:registry|context)[-_ ]id\s*:\s*`?([A-Za-z0-9_.:-]+)`?", re.IGNORECASE)
        for match in pattern.finditer(text):
            context_id = match.group(1)
            if context_id not in self.registry_ids:
                self.error(rel_path, f"references unknown registry id `{context_id}`")

    def validate_kb_content(self) -> None:
        kb_map = self.registry_kb_map()
        kb_paths = self.registry_kb_paths()
        if not kb_paths:
            kb_paths = sorted((self.docs_dir / "kb").rglob("*.md")) if (self.docs_dir / "kb").exists() else []
        for kb_path in kb_paths:
            if not kb_path.exists() or kb_path.suffix != ".md":
                continue
            rel_path = kb_path.relative_to(self.root)
            text = kb_path.read_text(encoding="utf-8")
            behavior_markers = len(re.findall(r"\b(?:AC|BR|FR)-\d+", text))
            if behavior_markers >= 5:
                self.warn(rel_path, f"KB contains {behavior_markers} AC/BR/FR markers; move behavior rules to Spec")
            self.validate_registry_id_references(rel_path, text)
            entry = kb_map.get(str(rel_path))
            kind = entry.get("kind") if entry else None
            self.validate_kb_sections(rel_path, text, kind)

    def registry_kb_map(self) -> dict[str, dict[str, Any]]:
        result: dict[str, dict[str, Any]] = {}
        for entry in self.registry_data.get("contexts", []):
            if not isinstance(entry, dict):
                continue
            kb = entry.get("kb")
            if isinstance(kb, str):
                result[kb] = entry
        return result

    def validate_kb_sections(self, rel_path: Path, text: str, kind: str | None) -> None:
        for section in REQUIRED_KB_SECTIONS:
            if section not in text:
                self.warn(rel_path, f"missing required section `{section}`")
        if kind == "component":
            for section in REQUIRED_KB_SECTIONS_COMPONENT:
                if section not in text:
                    self.warn(rel_path, f"missing required section `{section}` for component KB")

    def registry_kb_paths(self) -> list[Path]:
        paths: list[Path] = []
        for entry in self.registry_data.get("contexts", []):
            if not isinstance(entry, dict):
                continue
            kb = entry.get("kb")
            if isinstance(kb, str) and kb.startswith("docs/"):
                paths.append(self.root / kb)
        return paths

    def print_summary(self) -> tuple[int, int]:
        errors = sum(1 for finding in self.findings if finding.level == "ERROR")
        warnings = sum(1 for finding in self.findings if finding.level == "WARN")
        if not self.quiet:
            for finding in self.findings:
                print(f"{finding.level}: {finding.path}: {finding.message}")
        print(f"validate_context: {errors} error(s), {warnings} warning(s)")
        return errors, warnings


def find_repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def main(argv: Iterable[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Validate ArkUI KB/Spec context routing")
    parser.add_argument("--quiet", action="store_true", help="Only print the final summary")
    parser.add_argument("--all-specs", action="store_true", help="Validate every specs/**/Feat-*.md file")
    parser.add_argument("--warnings-as-errors", action="store_true", help="Return non-zero when warnings exist")
    args = parser.parse_args(argv)

    validator = Validator(find_repo_root(), quiet=args.quiet, all_specs=args.all_specs)
    errors, warnings = validator.validate()
    if errors or (args.warnings_as_errors and warnings):
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
