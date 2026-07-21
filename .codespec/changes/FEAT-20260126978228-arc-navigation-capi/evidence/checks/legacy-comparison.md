# legacy-comparison

> 与历史/存量资产的对比记录，避免混淆真相源。

## 历史资产（非真相源，仅对比）

| 资产 | 位置 | 性质 |
|------|------|------|
| 旧版 SDD | `.specs/features/FEAT-20260126978228-arc-navigation-capi/`（如存在）、`/home/master/workspace/.specs/` | 历史，非 `ohos-sdd/v1` 真相源 |
| 前次 SDD 草案 | 已于本次重跑删除 | 含行号误标缺陷，已废弃 |
| Arkoala 生成层 | `frameworks/core/interfaces/native/implementation/arc_swiper_*`、`arc_alphabet_indexer_*` | ArkTS-static native，**非** NDK C ABI；不可复用为 CAPI，仅映射参考 |

## 真相源（本变更）

| 真相源 | 位置 |
|--------|------|
| 接口定义 | interface_sdk_c PR #5447（`native_node.h`/`native_type.h`） |
| 头文件源头 | ace_engine `interfaces/native/native_node.h`（ADR-004） |
| SDD 实例 | `.codespec/changes/FEAT-20260126978228-arc-navigation-capi/` |

## 关键澄清：两套 native 层

| 层 | 命名空间 | 面向 | 本变更是否涉及 |
|----|----------|------|----------------|
| NDK/CAPI | `ArkUI_NodeHandle`/`OH_ArkUI_*` | C 开发者 | **是**（本次新增，当前空白） |
| Arkoala | `Ark_NativePointer`/`GeneratedModifier` | ArkTS 静态前端 | 否（已存在，独立） |

前次 SDD 误将 Arkoala 层既有文件当作"NDK 已有候选实现"，本次已纠正。
