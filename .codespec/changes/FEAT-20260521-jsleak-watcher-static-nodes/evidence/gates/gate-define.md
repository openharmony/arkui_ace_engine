# Gate: Define 阶段

## 信息检索手段记录

| 手段 | 检索内容 | 结果 |
|------|----------|------|
| 参考规格复用 | 基于用户提供的已验证规格产物 | 内容完全有效，用户确认 |
| 源码核对 | 动态语言: `frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts:1233` | 确认动态语言已有 fireArkUIObjectLifecycleCallback 调用 |
| 源码核对 | 静态语言: `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/FrameNode.ets:534` | 确认静态语言缺失 lifecycle callback 调用 |

## 入口检查表（arkui-define-entry）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| FuncID | 通过 | 04-06-02 (primary), also 04-06-03/04/05 | Owner 对话确认 | 无 |
| FeatID | 通过 | 各域均为 Feat-01 | Owner 对话确认 | 无 |
| specs/index.md 注册 | 通过 | 04-06-01~05 已注册 | Owner 确认 | 无 |
| Profile / subprofiles | 通过 | profile=arkui, 无子 profile, lineage=new-on-legacy | Owner 确认 | 无 |
| .codespec 目录已创建 | 通过 | .codespec/changes/FEAT-20260521-jsleak-watcher-static-nodes/ 已创建 | 文件系统验证 | 无 |
| long_term_spec_path | 通过 | specs/04-common-capability/06-custom-node-capability/ | Owner 确认 | 无 |
| spectest_feature_path | 通过 | N/A — 回调注册仅 InnerApi，外部无法注册带 UI 逻辑的回调 | Owner 确认 | 无 |
| 交互开始/结束判定 | 通过 | N/A — 内部桥接层变更，无用户交互 | Owner 确认 | 无 |
| 合法延迟状态 | 通过 | N/A — dispose 为同步调用 | Owner 确认 | 无 |
| 异常状态边界 | 通过 | N/A — PipelineContext::CHECK_NULL_VOID 保护 | Owner 确认 | 无 |
| 异常豁免规则 | 通过 | N/A — 无用户可见异常 | Owner 确认 | 无 |
| 维测合同 | 通过 | UT（断言 PipelineContext::FireArkUIObjectLifecycleCallback 被调用） | Owner 确认 | 无 |
| 热路径预算 | 通过 | N/A — dispose 非热路径 | Owner 确认 | 无 |
| 前端/API/依赖/跨平台影响 | 通过 | N/A — 纯内部桥接 | Owner 确认 | 无 |
| 无障碍/国际化/多形态 | 通过 | N/A — 无 UI 行为、无用户可见字符串 | Owner 确认 | 无 |
| Host 可测项 | 通过 | N/A — 回调注册仅 InnerApi，Host 无法注入 UI 逻辑 | Owner 确认 | 无 |
| SpecTest 可测项 | 通过 | N/A — 无公开方式注册回调触发 UI 变化 | Owner 确认 | 无 |
| 设备补验项 | 通过 | N/A — UT 可覆盖 | Owner 确认 | 无 |

## 出口检查表（arkui-define-exit）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| 所有 P0/P1 用户故事有 AC | 通过 | US-1~US-5 均有 WHEN/THEN 格式 AC | proposal.md | 无 |
| 每条 AC 可测试、可度量 | 通过 | AC-1~AC-7 均可验证 | proposal.md | 无 |
| manifest.target_release 已确认 | 通过 | TBD（明确标记） | manifest.md | 无 |
| manifest.profile 已确认 | 通过 | arkui | manifest.md | 无 |
| 不涉及项已显式标记 N/A | 通过 | proposal.md 不涉及项确认表 | proposal.md | 无 |
| baseline_approval.approved=true | 通过 | approver=sunbees, evidence 非空 | manifest.md | 无 |
| 信息检索手段已记录 | 通过 | 本文件顶部 | 本文件 | 无 |
| 证据/缺口列包含完整来源链路 | 通过 | 每条检查项均有来源链路 | 本文件 | 无 |
| 源码核验已记录路径和行号 | 通过 | frame_node.ts:1233, FrameNode.ets:534 | 源码核对 | 无 |

## 总结论

**通过** — 所有入口和出口检查项均有明确结论和证据，Owner 已批准基线。
