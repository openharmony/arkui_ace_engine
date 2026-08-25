# Navigation Transition ID Cleanup Verification

## 2026-08-07

## 缺陷与修复范围

- 转场开始由 `NavigationPattern::ContentChangeOnTransitionStart` 使用实际
  `NavDestination` 节点 ID 调用 `ContentChangeManager::OnTransitionAdded`。
- 修复前 `NavigationPattern::ContentChangeByDetaching` 使用 Navigation host ID 调用
  `OnTransitionRemoved`，登记键与清理键不一致；Navigation 整体下树时可能遗留
  destination ID，使 `ContentChangeManager::IsTransitioning()` 持续为 `true`。
- 修复后 `NavigationPattern` 保存本实例登记过的 destination ID：正常转场完成时清理对应
  ID，单个 `NavDestination` 下树时只清理自身 ID，Navigation 整体下树时清理全部剩余 ID，
  交互转场取消时释放本次 ID 且不触发页面切换上报。
- 本修复不修改 `ContentChangeManager` API、公开 ArkUI API、布局、绘制或默认组件行为。

## 源码与测试映射

| 场景 | 实现入口 | 定向用例 | 预期结果 |
|------|----------|----------|----------|
| 两个 destination 转场并存 | `NavigationPattern::ContentChangeOnTransitionStart` | `NavigationPatternTestFiveNg.ContentChangeTransitionDetach001` | Manager 与 NavigationPattern 均保存两个 ID |
| 单个 NavDestination 下树 | `NavDestinationPattern::ContentChangeByDetaching` | `NavigationPatternTestFiveNg.ContentChangeTransitionDetach001` | 只移除自身 ID，另一个 ID 仍保持转场态 |
| Navigation 整体下树 | `NavigationPattern::ContentChangeByDetaching` | `NavigationPatternTestFiveNg.ContentChangeTransitionDetach001` | 清理全部剩余 ID，`IsTransitioning()` 为 `false` |
| 正常转场结束 | `NavigationGroupNode::ContentChangeReport` -> `NavigationPattern::ContentChangeReport` | `NavigationPatternTestFiveNg.ContentChangeTransitionReport001` | Manager 与本地集合同时移除对应 ID |
| 交互转场取消 | `NavigationPattern::TriggerCustomAnimation` 取消分支 | `NavigationAnimationTest.NavigationCancelAnimation003` | 释放本次 ID，不生成成功 PageTransition 上报 |

## 当前检查状态

| 检查项 | 状态 | 说明 |
|--------|------|------|
| CodeSpec 一致性校验 | Pass | 在 change 目录执行 `ohos-sdd validate . --level all --json`：33 项通过，`broken=0`，`warnings=[]`。 |
| 差异格式检查 | Pass | `git diff --check` 退出码 0。 |
| Navigation 定向编译 | Pending | 按 Owner 要求由 Owner 手工执行。 |
| Navigation 定向用例 | Pending | 按 Owner 要求由 Owner 手工执行并回填结果。 |
| SpecTest Host Preview | N/A | 该缺陷是 Native 转场状态集合的生命周期清理，无法通过 Inspector 稳定断言；替代验证为组件 unittest。 |
| 真实设备视觉/交互回归 | N/A | 不改变布局、绘制、主题及用户交互结果；只修复内部转场状态释放。 |

## Owner 手工验证命令

```bash
# OpenHarmony 根目录：构建 Navigation 定向 unittest
./build.sh --product-name rk3568 --ccache \
  --build-target //foundation/arkui/ace_engine/test/unittest/core/pattern/navigation:navigation_test_ng

# 按实际产物路径执行以下过滤用例
navigation_test_ng \
  --gtest_filter='NavigationPatternTestFiveNg.ContentChangeTransition*:NavigationAnimationTest.NavigationCancelAnimation003'
```

通过标准：上述三个定向用例全部通过；正常完成、单节点下树、整体下树及交互取消后均不存在
不应保留的 destination ID，最后一个活跃 ID 被释放后 `IsTransitioning()` 返回 `false`。
