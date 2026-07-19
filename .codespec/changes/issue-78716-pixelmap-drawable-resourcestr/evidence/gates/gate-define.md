# gate-define.md

> 阶段：Stage 1 Define | FuncID: 04-01-03 | FeatID: Feat-02 | 变更 ID: issue-78716-pixelmap-drawable-resourcestr

## 信息检索手段记录

| 手段 | 检索内容 | 结果 |
|------|----------|------|
| 源码核对 | `frameworks/core/drawable/pixel_map_drawable_descriptor.h` — 检查是否已有 ResourceStr 支持 | 确认无 ResourceStr 构造，仅有 `PixelMap` 构造 + `SetRawData` |
| 源码核对 | `frameworks/bridge/arkts_frontend/koala_projects/.../drawableDescriptor.ets:138-159` — 检查静态前端 PixelMapDrawableDescriptor | 确认仅有 `constructor(src?: image.PixelMap)`，无 ResourceStr 重载 |
| 源码核对 | `AnimatedDrawableDescriptor` ResourceStr 模式: `drawableDescriptor.ets:302-325` | 确认参考模式已存在，使用 `SystemOps.createResourceObject` + `ArkUIAniModule._Drawable_CreateAnimatedDrawableByString/ByResource` |
| 历史规格 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md` | Feat-01 Baselined，已读取作为上下文 |
| 历史规格 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md` | 已读取 ADR-5（资源加载三路径），确认 Loader/Info 基础设施可用 |
| SDK 核对 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts:350-362` | 确认动态 API 已声明 `constructor(src?: image.PixelMap \| ResourceStr)` @since 26.0.0 |
| SDK 核对 | `interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets:227-235` | 确认静态 API 已声明 `constructor(src?: image.PixelMap \| ResourceStr)` @since 26.0.0 |

---

## arkui-define-entry（入口检查）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| FuncID 确认 | 通过 | `04-01-03` — Owner 明确确认 | Owner 对话确认（第1轮） | 无 |
| FeatID 确认 | 通过 | `Feat-02` — DrawableDescriptor 功能域第2个特性，Feat-01 已 Baselined | Owner 对话确认（第1轮） | 无 |
| specs/index.md FuncID 注册 | 通过 | `04-01-03` 已在"功能域层级树"注册，特性清单已有 Feat-01 (Baselined) + Feat-02 (Draft) | `specs/index.md` 写入验证 | 无 |
| specs/index.md FeatID 注册 | 通过 | Feat-02 行已添加至 `04-01-03 DrawableDescriptor` 特性清单，状态 Draft | `specs/index.md` 写入验证 | 无 |
| profile 选择 | 通过 | `arkui/sdk-api` — 核心变更为 SDK API 实现补全 | Owner 对话确认（第2轮） | 无 |
| subprofiles 选择 | 通过 | 无子 profile — 不涉及 C API 或 render | Owner 对话确认（第2轮） | 无 |
| lineage 选择 | 通过 | `new-on-legacy` — 在已有 PixelMapDrawableDescriptor 上扩展新构造器 | Owner 对话确认（第2轮） | 无 |
| .codespec/changes/{id} 创建 | 通过 | `issue-78716-pixelmap-drawable-resourcestr/` 已创建，含 manifest.md + proposal.md | 文件系统验证 | 无 |
| long_term_spec_path | 通过 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-02-pixelmap-drawable-resourcestr-spec.md` — Stage 2 产出 | manifest.md | Stage 2 创建 |
| long_term_design_path | 通过 | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md` — 已存在（Feat-01 已建立），Stage 2 增量合并 | manifest.md | Stage 2 增量合并 |
| spectest_feature_path | 通过 (N/A) | DrawableDescriptor 为数据对象，无直接 UI 行为变更，不适用 SpecTest | 源码分析 | N/A 理由已记录 |
| 交互开始/结束判定 | N/A | 数据对象构造，无交互 | — | — |
| 合法延迟状态 | N/A | 无异步状态机 | — | — |
| 异常状态边界 | 通过 | 分析完成：无效路径→nullptr，与已有模式一致 | 源码分析参考 AC-4 | — |
| 异常豁免规则 | 通过 | 不抛异常，返回 null/undefined，与 AnimatedDrawableDescriptor 一致 | 源码分析 | — |
| 维测合同 | 通过 | 沿用已有 HILOGE 日志模式 | 源码分析 | — |
| 热路径预算 | N/A | 构造为一次性操作 | — | — |
| 前端/API/依赖/跨平台 | 通过 | 仅影响 ace_engine 内部，无新增外部依赖 | 源码分析 | — |
| 无障碍/国际化/多形态 | N/A | 数据对象 | — | — |
| Host/SpecTest/设备验证分流 | 通过 | C API unittest 为主；SpecTest N/A（数据对象无 UI 变更） | 分析 | — |

**入口结论：通过**（所有必检项可通过源码或 Owner 确认完成）

---

## arkui-define-exit（出口检查）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| Owner 已审阅 proposal.md 并批准基线 | **通过** | Owner 明确表态"批准" | Owner 对话确认 | 无 |
| 信息检索手段已记录 | 通过 | 本文件顶部"信息检索手段记录"完整 | — | 无 |
| 证据/缺口列含完整来源链路 | 通过 | 每条检查项含路径或源码引用 | — | 无 |
| 确认来源列标注获取途径 | 通过 | Owner 对话 / 源码核对 / 文件系统验证 | — | 无 |
| 源码核验已记录路径和行号 | 通过 | 已记录 `pixel_map_drawable_descriptor.h`, `drawableDescriptor.ets:138-159`, `drawableDescriptor.ets:302-325` | — | 无 |
| 未核验项不得标记为"通过" | 通过 | 无未核验项标记为"通过" | — | 无 |

**出口结论：通过** — Owner 已批准基线。

---

## 总结论

**状态：通过 (Approved)** — 入口和出口检查全部通过。可进入 Stage 2 (Specify)。

## 审批记录

| 阶段 | 决策 | 审批人 | 证据 | 下一阶段 |
|------|------|--------|------|----------|
| Define | Approved | Owner (liyujie43) | 当前会话明确批准 | Stage 2 Specify |
