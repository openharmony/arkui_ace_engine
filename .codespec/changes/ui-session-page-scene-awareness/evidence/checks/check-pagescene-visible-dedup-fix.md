# PageScene Visible/Dedup Scope Verification

## 2026-08-22

| 检查项 | 结果 | 证据 |
|--------|------|------|
| Host TDD 编译 | 通过 | `ninja -C out/host/host_product page_scene_rule_manager_test_ng content_change_manager_test_ng` 退出码 0。 |
| Host 二进制架构 | 通过 | 两个测试产物均为 Linux ELF 64-bit x86-64。 |
| PageScene 单测 | 通过 | `PageSceneRuleManagerTestNg.*` 共 11 个用例，11/11 通过。 |
| ContentChangeManager 回归 | 通过 | `content_change_manager_test_ng` 共 45 个用例，45/45 通过。 |
| 完整 ace_engine 构建 | 通过 | 从 OpenHarmony 根目录执行 `./build.sh --product-name rk3568 --build-target ace_engine --ccache`，Ninja 完成 5888/5888，输出 `rk3568 build success` 和 `build successful`。 |
| 差异格式检查 | 通过 | `git diff --check` 退出码 0。 |
| 过滤与通知规格检查 | 通过 | `onlyVisible`、`rectCulling`、opacity 过滤、父子树 dirty、按需 rect 计算和 nodeId 去重均已同步到规格与测试设计。 |

## 覆盖说明

- `onlyVisible=true`：过滤 visible/active 不通过、transform 后宽高为 0、或自身/祖先最终 opacity 为 0 的输入框；不因屏外而排除。
- `rectCulling=true`：仅统计与 pageRoot viewport 有交集的输入框；缺省为 false。
- `onlyVisible=false && rectCulling=true`：透明、隐藏或零尺寸属性不作为过滤条件，仅执行 rect 相交过滤。
- `includeRect=true` 时无论过滤开关如何均需计算并输出 rect。
- 同一命中节点 ID 列表仅发生坐标变化时，由 `deduplicate` 抑制重复上报。
- 输入框上下树、可见属性/opacity 变化或 rectCulling 结果导致命中节点 ID 列表变化时，重新应用规则并形成新的命中/退出状态。
- 父节点 visibility 变化只产生一次 PageScene dirty，稳定点从 pageRoot 重算父子树；pending 规则层去重保证同一规则不重复匹配。
- 候选索引、增量计数、多 UIContext 路由和延迟 JSON 构造等性能优化已退出本阶段范围；规则检测允许全量扫描当前页面树。

## Fresh 验证命令

```bash
# OpenHarmony 根目录
./build.sh --product-name rk3568 --build-target ace_engine --ccache

file out/host/host_product/tests/unittest/ace_engine/TextSet-Text/page_scene_rule_manager_test_ng
out/host/host_product/tests/unittest/ace_engine/TextSet-Text/page_scene_rule_manager_test_ng

file out/host/host_product/tests/unittest/ace_engine/TextSet-Text/content_change_manager_test_ng
out/host/host_product/tests/unittest/ace_engine/TextSet-Text/content_change_manager_test_ng

# ace_engine 仓目录
git diff --check
```

## ArkUI Profile 验证分流

- SpecTest Host Preview：N/A。本变更验证的是 UISession 系统侧规则匹配、稳定点调度和上报去重，不是可由 Inspector 稳定断言的组件布局或交互属性；替代验证为 Linux x86-64 Host manager 单测、ContentChangeManager 稳定点回归和完整 rk3568 `ace_engine` 构建。
- 真实设备交互/视觉回归：本次范围不改变组件视觉、布局、主题或用户交互；PageScene sample/hidumper 设备 E2E 仍作为整体特性的后续验证项，不作为本次过滤与去重收缩的 Host 验证证据。
- 构建期间 generated 文件仍各保持一处既有缩进差异，本次未识别、修改或回退这些 generated 内容。
