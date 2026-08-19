# 键盘避让执行顺序变化 Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `KeyboardAvoidTimingChange`

## 定位

本页用于排查“键盘已弹出时，窗口占用区域更新与已排队 UI 任务的执行顺序变化”导致的布局与点击位置异常。行为结论应以当前源码、测试与对应历史提交为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 搜索词 |
|----------|----------|--------|
| 窗口占用区域与键盘避让调度 | `adapter/ohos/entrance/ui_content_impl.cpp` | `UpdateViewportConfigWithAnimation`、`KeyboardAvoid`、`OCCUPIED_AREA_CHANGE` |
| 任务排队与同步执行 | `frameworks/base/thread/task_executor.cpp` | `PostTask`、`PostSyncTask` |
| 键盘区域公共入口 | `frameworks/core/pipeline/pipeline_base.cpp` | `OnVirtualKeyboardAreaChange` |
| NG Pipeline 键盘避让 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | `OnVirtualKeyboardHeightChange`、`DoKeyboardAvoidFunc` |
| 键盘安全区状态 | `frameworks/core/components_ng/manager/safe_area/` | `SafeAreaManager`、`KeyboardAvoidMode` |

### API 入口

本主题是引擎内部调度与布局时序问题，不对应独立的 ArkUI 公共 API。排查应从上述窗口适配层和 Pipeline 入口开始。

### 测试入口

| 范围 | 稳定路径 | 用途 |
|------|----------|------|
| Pipeline 键盘避让 | `test/unittest/core/pipeline/pipeline_context_test_ng_two.cpp` | 搜索 `DoKeyboardAvoidFunc`、`PostKeyboardAvoidTask` |
| 自定义键盘避让分支 | `test/unittest/core/pipeline/pipeline_context_test_ng_five.cpp` | 搜索 `OnVirtualKeyboardHeightChange` |
| 安全区管理 | `test/unittest/core/manager/safe_area_manager_test_ng.cpp` | 验证键盘安全区状态 |
| 安全区补充用例 | `test/unittest/core/manager/safe_area_manager_test_ng_part_two.cpp` | 搜索 `KeyboardAvoid` |

### 历史证据

| 提交 | 用途 |
|------|------|
| `7a85ab9d715456a3ef0a643322bbfcd361655127` | 对比键盘避让从已排队 UI 任务中拆分为同步任务的改动 |
| `129496832094e1779b27cdf57b6de383bf41370e` | 对比恢复原任务顺序的回退改动 |

### 相关 Spec

- `specs/04-common-capability/02-safe-area/01-safe-area-mechanism/`（若 Spec 仓可用）
- `specs/03-engine-framework/05-window-mechanism/01-window-mechanism/`（若 Spec 仓可用）

## 常见问题定位

| 现象 | 优先检查 |
|------|----------|
| 键盘已弹出时，新出现的交互内容显示位置与点击生效位置不一致 | `UpdateViewportConfigWithAnimation` 中占用区域更新、已排队 UI 任务与 `KeyboardAvoid` 的实际顺序 |
| 改动前后键盘偏移不一致 | `OnVirtualKeyboardAreaChange`、`OnVirtualKeyboardHeightChange` 使用的键盘区域、输入区域位置和已有偏移 |
| 恢复调度顺序后仍异常 | 继续检查应用布局任务和事件坐标转换链路 |

## 调试入口

- 记录窗口占用区域回调、已排队 UI 任务和 `KeyboardAvoid` 的执行顺序。
- 对比改动前后键盘区域、输入区域位置、已有偏移和最终避让高度。
- 设备复测时保持键盘弹出，触发新的可交互内容，分别验证可见位置与实际命中位置。

## 相关主题

- `docs/kb/capabilities/safe-area.md`
- `docs/kb/architecture/window-mechanism.md`
- `docs/kb/architecture/layout-framework.md`