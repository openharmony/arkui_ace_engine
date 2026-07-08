#!/usr/bin/env python3
"""Generate the Docusaurus site inputs from the ArkUI spec registry."""

from __future__ import annotations

import argparse
import json
import shutil
from collections import Counter, defaultdict
from pathlib import Path
from typing import Any

import yaml


ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS_FILE = ROOT / "registry" / "functions.yaml"
FEATURES_FILE = ROOT / "registry" / "features.yaml"
SITE_DIR = ROOT / "site"
DOCS_DIR = SITE_DIR / "docs"
SIDEBAR_FILE = SITE_DIR / "sidebars.js"
DATA_DIR = SITE_DIR / "src" / "data"
REGISTRY_JSON = DATA_DIR / "registry.json"


def load_yaml(path: Path) -> dict[str, Any]:
    with path.open("r", encoding="utf-8") as fp:
        data = yaml.safe_load(fp)
    if not isinstance(data, dict):
        raise ValueError(f"{path} must contain a YAML mapping")
    return data


def doc_id(path: str) -> str:
    raw = Path(path)
    return str(raw.with_suffix(""))


def copy_markdown(source: Path, destination: Path) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, destination)


def sidebar_doc(path: str, label: str | None = None) -> dict[str, str]:
    item = {"type": "doc", "id": doc_id(path)}
    if label:
        item["label"] = label
    return item


def sort_features(features: list[dict[str, Any]]) -> list[dict[str, Any]]:
    return sorted(features, key=lambda item: str(item["id"]))


def build_sidebar(
    top_levels: list[dict[str, Any]], functions: list[dict[str, Any]], features: list[dict[str, Any]]
) -> dict[str, list[dict[str, Any]]]:
    features_by_func: defaultdict[str, list[dict[str, Any]]] = defaultdict(list)
    for feature in features:
        features_by_func[str(feature["func_id"])].append(feature)

    functions_by_l1_l2: defaultdict[tuple[str, str, str], list[dict[str, Any]]] = defaultdict(list)
    for func in functions:
        func_id = str(func["id"])
        has_design = bool(func.get("design"))
        has_specs = any(feature.get("spec") for feature in features_by_func.get(func_id, []))
        if not has_design and not has_specs:
            continue
        key = (str(func["l1"]["id"]), str(func["l2"]["id"]), str(func["l2"]["title"]))
        functions_by_l1_l2[key].append(func)

    l1_lookup = {str(item["id"]): item for item in top_levels}
    docs_items: list[dict[str, Any]] = [
        {
            "type": "category",
            "label": "Overview",
            "collapsed": False,
            "items": [
                sidebar_doc("index.md", "Spec Index"),
                sidebar_doc("registry/README.md", "Registry Guide"),
            ],
        }
    ]

    for top in top_levels:
        l1_id = str(top["id"])
        l2_categories: list[dict[str, Any]] = []
        l2_keys = sorted(key for key in functions_by_l1_l2 if key[0] == l1_id)
        for _, l2_id, l2_title in l2_keys:
            func_items: list[dict[str, Any]] = []
            funcs = sorted(functions_by_l1_l2[(l1_id, l2_id, l2_title)], key=lambda item: str(item["id"]))
            for func in funcs:
                func_id = str(func["id"])
                items: list[dict[str, Any]] = []
                if func.get("design"):
                    items.append(sidebar_doc(str(func["design"]), "Design"))
                for feature in sort_features(features_by_func.get(func_id, [])):
                    if feature.get("spec"):
                        items.append(sidebar_doc(str(feature["spec"]), f"{feature['id']} {feature['title']}"))
                if items:
                    func_items.append(
                        {
                            "type": "category",
                            "label": f"{func_id} {func['l3']['title']}",
                            "collapsed": True,
                            "items": items,
                        }
                    )
            if func_items:
                l2_categories.append(
                    {
                        "type": "category",
                        "label": f"{l2_id} {l2_title}",
                        "collapsed": True,
                        "items": func_items,
                    }
                )
        if l2_categories:
            title = l1_lookup[l1_id]["title"]
            docs_items.append(
                {
                    "type": "category",
                    "label": f"{l1_id} {title}",
                    "collapsed": True,
                    "items": l2_categories,
                }
            )

    return {"docs": docs_items}


def build_registry_data(
    top_levels: list[dict[str, Any]], functions: list[dict[str, Any]], features: list[dict[str, Any]]
) -> dict[str, Any]:
    features_by_func: defaultdict[str, list[dict[str, Any]]] = defaultdict(list)
    for feature in features:
        features_by_func[str(feature["func_id"])].append(feature)

    function_cards: list[dict[str, Any]] = []
    for func in functions:
        func_id = str(func["id"])
        func_features = sort_features(features_by_func.get(func_id, []))
        has_docs = bool(func.get("design")) or any(item.get("spec") for item in func_features)
        status_counts = Counter(str(item.get("status", "unknown")) for item in func_features)
        function_cards.append(
            {
                "id": func_id,
                "l1": {"id": str(func["l1"]["id"]), "title": str(func["l1"]["title"])},
                "l2": {"id": str(func["l2"]["id"]), "title": str(func["l2"]["title"])},
                "l3": {"id": str(func["l3"]["id"]), "title": str(func["l3"]["title"])},
                "path": str(func["path"]),
                "design": str(func["design"]) if func.get("design") else None,
                "designDocId": doc_id(str(func["design"])) if func.get("design") else None,
                "status": str(func.get("status", "unknown")),
                "featureCount": len(func_features),
                "documentedFeatureCount": sum(1 for item in func_features if item.get("spec")),
                "statusCounts": dict(sorted(status_counts.items())),
                "hasDocs": has_docs,
                "features": [
                    {
                        "id": str(feature["id"]),
                        "title": str(feature["title"]),
                        "status": str(feature["status"]),
                        "spec": str(feature["spec"]) if feature.get("spec") else None,
                        "docId": doc_id(str(feature["spec"])) if feature.get("spec") else None,
                    }
                    for feature in func_features
                ],
            }
        )

    documented_functions = [item for item in function_cards if item["hasDocs"]]
    feature_status_counts = Counter(str(item.get("status", "unknown")) for item in features)
    return {
        "summary": {
            "topLevelCount": len(top_levels),
            "functionCount": len(functions),
            "documentedFunctionCount": len(documented_functions),
            "featureCount": len(features),
            "documentedFeatureCount": sum(1 for item in features if item.get("spec")),
            "functionWithDesignCount": sum(1 for item in functions if item.get("design")),
            "featureStatusCounts": dict(sorted(feature_status_counts.items())),
        },
        "topLevels": [
            {
                "id": str(item["id"]),
                "slug": str(item["slug"]),
                "title": str(item["title"]),
                "description": str(item["description"]),
                "functionCount": sum(1 for func in functions if str(func["l1"]["id"]) == str(item["id"])),
                "documentedFunctionCount": sum(
                    1 for func in documented_functions if str(func["l1"]["id"]) == str(item["id"])
                ),
            }
            for item in top_levels
        ],
        "functions": function_cards,
    }


def write_sidebar(sidebar: dict[str, Any]) -> None:
    SIDEBAR_FILE.write_text(
        "// This file is generated by tools/generate_site.py. Do not edit by hand.\n"
        "module.exports = "
        + json.dumps(sidebar, ensure_ascii=False, indent=2)
        + ";\n",
        encoding="utf-8",
    )


def generate() -> None:
    functions_data = load_yaml(FUNCTIONS_FILE)
    features_data = load_yaml(FEATURES_FILE)
    top_levels = functions_data.get("top_levels", [])
    functions = functions_data.get("functions", [])
    features = features_data.get("features", [])

    shutil.rmtree(DOCS_DIR, ignore_errors=True)
    DOCS_DIR.mkdir(parents=True, exist_ok=True)
    DATA_DIR.mkdir(parents=True, exist_ok=True)

    docs_to_copy = {"index.md", "registry/README.md"}
    for func in functions:
        if func.get("design"):
            docs_to_copy.add(str(func["design"]))
    for feature in features:
        if feature.get("spec"):
            docs_to_copy.add(str(feature["spec"]))

    missing: list[str] = []
    for rel_path in sorted(docs_to_copy):
        source = ROOT / rel_path
        if not source.is_file():
            missing.append(rel_path)
            continue
        copy_markdown(source, DOCS_DIR / rel_path)
    if missing:
        raise FileNotFoundError("registered docs are missing: " + ", ".join(missing))

    write_sidebar(build_sidebar(top_levels, functions, features))
    REGISTRY_JSON.write_text(
        json.dumps(build_registry_data(top_levels, functions, features), ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )

    print(f"generated {DOCS_DIR.relative_to(ROOT)}")
    print(f"generated {SIDEBAR_FILE.relative_to(ROOT)}")
    print(f"generated {REGISTRY_JSON.relative_to(ROOT)}")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()
    generate()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
