# SDD Validate Check

| 字段 | 内容 |
|------|------|
| Change | drawable-descriptor-release-state |
| 日期 | 2026-07-23 |
| 命令 | `/home/huawei/.codex/plugins/cache/personal/ohos-sdd/0.3.1/bin/ohos-sdd validate --level all .` |
| 结论 | BLOCKED：39 checks，1 broken，0 warn；`spec-for-test.md` 专项检查已 PASS，但 D 级归档门禁要求开发/Spec Owner 与测试 Owner 双审批并将状态改为 Approved。当前按 Profile 规则保持 ReadyForReview，等待 Owner 审批。 |

## 输出摘要

```text
level 语义: A=结构存在 B=锚点标题 C=依赖边一致 D=归档就绪 E=profile 命中
[FAIL] validate level=all (39 checks, 1 broken, 0 warn)
  - D spec-for-test (): spec-for-test.md 必须满足命中 Profile 的审批要求、状态为 Approved，当前 Profile 完整检查通过，且 check-spec-for-test.md 结论为 PASS -> ohos-validate
```
