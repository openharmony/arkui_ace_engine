# PageScene Visible/Dedup Scope Verification

## 2026-07-21

| 检查项 | 结果 | 证据 |
|--------|------|------|
| Host TDD 编译 | 通过 | `ninja -C out/host/host_product page_scene_rule_manager_test_ng content_change_manager_test_ng` 退出码 0。 |
| Host 二进制架构 | 通过 | 两个测试产物均为 Linux ELF 64-bit x86-64。 |
| PageScene 单测 | 通过 | `PageSceneRuleManagerTestNg.*` 共 11 个用例，11/11 通过。 |
| ContentChangeManager 回归 | 通过 | `content_change_manager_test_ng` 共 45 个用例，45/45 通过。 |
| 完整 ace_engine 构建 | 通过 | 从 OpenHarmony 根目录执行 `./build.sh --product-name rk3568 --build-target ace_engine --ccache`，Ninja 完成 5888/5888，输出 `rk3568 build success` 和 `build successful`。 |
| 差异格式检查 | 通过 | `git diff --check` 退出码 0。 |
| 回退项残留检查 | 通过 | 生产代码和测试中不存在候选索引、`PageSceneOperation`、`forceFullScan`、节点变化独立回调等已退出范围的标识；CodeSpec 仅保留范围收缩和历史说明。 |

## 覆盖说明

- `onlyVisible=true`：不可见或与当前页面窗口范围无交集的输入框不计数；不覆盖滚动容器逐层裁剪。
- `onlyVisible=false`：屏幕外输入框仍参与规则匹配。
- 同一命中节点 ID 列表仅发生坐标变化时，由 `deduplicate` 抑制重复上报。
- 输入框上下树或移出屏幕导致命中节点 ID 列表变化时，重新应用规则并形成新的命中/退出状态。
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
