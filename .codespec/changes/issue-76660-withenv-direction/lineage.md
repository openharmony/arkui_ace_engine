# Lineage

| 字段 | 值 |
|------|----|
| Lineage | new-on-legacy |
| Target Release | TBD |
| Source | existing code + new requirement |
| Original Docs | 32825.diff (API 定义) |
| Source Code Evidence | frameworks/core/components_ng/syntax/with_env_node.h/cpp, frameworks/core/pipeline_ng/environment_manager.h/cpp |
| Compatibility Boundary | WithEnv 初版 CustomEnv 行为必须保持源码兼容；@Env/@CustomEnv 装饰器签名扩展不可破坏现有用法 |
| Migration Status | migrated to `.codespec/changes/issue-76660-withenv-direction` on 2026-06-12; linked to GitCode issue 76660 |
| Supersedes | initial draft identity before GitCode issue binding |
| Superseded By | — |
