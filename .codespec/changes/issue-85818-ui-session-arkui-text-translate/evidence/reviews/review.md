# 统一审查记录

## 审查元数据

| 项 | 内容 |
|----|------|
| Review ID | REV-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 审查阶段 | 设计/Spec 审批 |
| 关联文档 | proposal.md / design.md / spec.md / execution-plan.md |
| 复杂度 | 标准 + 安全/性能专项 |
| 涉及仓 | ace_engine |
| Reviewer | 用户 + Codex |
| 日期 | 2026-05-15 |
| Base SHA | 1c2d1a89fbd |
| Head SHA | a04c35841ed |

## 审查输入

| 输入 | 路径 | 说明 |
|------|------|------|
| Proposal | `proposal.md` | 需求基线 |
| Design | `design.md` | 架构设计 |
| Spec | `spec.md` | 特性规格 |
| Plan | `execution-plan.md` | 执行计划，已 Approved |
| Diff | MR 86308 review fix | `a04c35841ed Fix UI session translate review issues` |

## 零、设计/Spec 审批

| 检查项 | 结论 | 证据 |
|--------|------|------|
| 设计决策已记录并有取舍理由 | PASS | `design.md` ADR-1 至 ADR-9 |
| Spec 规则覆盖全部 P0/P1 AC | PASS | `spec.md` AC、BR、FR、EX、RC、VM 映射 |
| 豁免规则明确无误伤风险 | PASS | 非范围控件、占位布局未绘制、SA death、timeout、译文等待 watchdog 均已明确 |
| 不涉及项已显式确认 | PASS | 不新增 Public API、不覆盖输入类控件用户可编辑文本/Canvas/自绘/OCR；TextInput 仅覆盖空内容实际展示的 placeholder；不重写 Web 注入、不改原属性 |

**审批决策：**
- [x] Stage 2 通过，进入 Stage 3
- [ ] 需要修改，修改后重审

**审批人：** 用户　**日期：** 2026-05-15

## 后续审查入口

Stage 3 实现完成后需继续补充：

| 审查项 | 当前状态 | 后续证据 |
|--------|----------|----------|
| Plan 审批 | Approved | 用户于 2026-05-16 明确 approve；允许进入 Stage 3 实现 |
| 规范符合性审查 | 未开始 | 代码实现和测试结果 |
| 代码质量审查 | 未开始 | diff、构建、单测 |
| 最终验证 | 未开始 | unittest、真机 dump、hilog |

## 一、MR 86308 检视问题处理记录

| 检视项 | 处理结论 | 证据 |
|--------|----------|------|
| translate pid 生命周期清理不完整 | 已补强 | 参数失败、End、单次获取完成、timeout 清理均要求移除调用方 pid，避免后续 death 误判 |
| 连续翻译死亡恢复依赖 process map size | 已修正 | 设计改为保存连续翻译 owner pid；owner death 或 started 状态不一致时走全量恢复，不依赖集合大小为 1 |
| Start 初始无文本被 timeout End | 已修正 | 连续 Start 不因初始无实际绘制文本或 empty 哨兵自动 End，后续新增/变化节点仍上报 |
| 单次 snapshot 固定 version / 缺少源文本校验 | 已修正 | 单次 snapshot 使用独立 snapshot version 和 source hash；迟到译文在 source hash 变化时忽略 |
| 单次 snapshot cache 未清理 | 已修正 | 新请求开始、完成、失败、timeout、End/Reset/SA death 均清理隔离 snapshot cache |
| `SendPageTranslateResult` 非法 payload 容忍过宽 | 已修正 | 缺失 nodeId/version、`nodeId < 0`、译文为空、全批无合法项返回 `PARAM_INVALID`；批量合法项仍可独立处理 |
| `nodeId < 0` 哨兵触发 result watchdog | 已修正 | `nodeId < 0` 只作为控制/空结果哨兵，不启动译文等待 watchdog，不允许作为合法回填结果 |
| DFX 文档与实现口径不一致 | 已同步 | `spec.md`、`design.md`、`execution-plan.md`、TASK-001/002/003/007 和 verification 模板已统一为单次 Get timeout、连续 Start 保活、result watchdog 只告警 |

**验证记录：**

| 命令 | 结果 |
|------|------|
| `./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ui_content_stub_unittest_linux --ccache` | PASS |
| `/home/l00441630/OpenHarmony/out/rk3568/clang_x64/tests/unittest/ace_engine/ace_engine/adapter/ui_content_stub_unittest` | PASS，50/50 |
| `./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target content_change_manager_translate_test_ng --ccache` | PASS |
| `./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ui_session --ccache` | PASS |
