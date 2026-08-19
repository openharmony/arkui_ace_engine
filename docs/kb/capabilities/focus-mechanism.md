# Focus Mechanism Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `FocusMechanism`

## 定位

焦点机制是 ArkUI 的焦点树、请求事务、键盘导航、焦点域、FocusView 恢复以及激活与视觉指示框架。核心状态集中在 FocusHub、FocusManager 和 FocusView，并由 FrameNode、Pipeline、按键管理及 ArkTS/Native 入口共同驱动。

本文档只提供稳定路由。焦点准入、导航算法、恢复顺序、视觉选择和版本差异，应以当前 SDK、源码、测试及 `04-09-01` Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 焦点类型与状态 | `frameworks/core/components_ng/event/focus_type.h`、`frameworks/core/components_ng/event/focus_state.h` | FocusType、FocusPattern、FocusState 等基础模型 |
| 焦点节点核心 | `frameworks/core/components_ng/event/focus_hub.cpp` | 焦点树、请求、遍历、域属性、默认节点和视觉状态入口 |
| 按键意图与路由 | `frameworks/core/components_ng/event/focus_event_handler.cpp` | 按键意图、导航与点击处理入口 |
| 焦点事务管理 | `frameworks/core/components_ng/manager/focus/focus_manager.cpp` | FocusGuard、焦点域注册、激活状态和 View 栈管理 |
| FocusView | `frameworks/core/components_ng/manager/focus/focus_view.cpp` | ViewRoot、显示隐藏和焦点恢复边界 |
| 焦点框 | `frameworks/core/components_ng/event/focus_box.cpp` | 焦点框样式、参数和绘制数据入口 |
| Pipeline 调度 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | dirty focus、帧末提交和窗口焦点接入 |
| 按键管理 | `frameworks/core/common/key_event_manager.cpp` | Tab、tabIndex 和按键事件生产分发 |
| FrameNode 所有权 | `frameworks/core/components_ng/base/frame_node.cpp` | FocusHub 创建、树关系和主树生命周期入口 |
| Native Focus API | `interfaces/native/node/native_interface_focus.cpp` | Native 焦点请求、清除与激活接口实现 |
| NAPI FocusController | `interfaces/napi/kits/focus_controller/js_focus_controller.cpp` | Dynamic ArkTS 焦点控制接口 |
| ANI FocusController | `interfaces/ets/ani/focuscontroller/src/focusController.cpp` | Static ArkTS 焦点控制接口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | focusable、nextFocus、tabIndex、defaultFocus、focusScope 和 focusBox 等声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 公共焦点属性契约 |
| Native Focus API | `interfaces/native/native_interface_focus.h` | 焦点请求、清除、激活和结果接口 |
| Native Node API | `interfaces/native/native_node.h` | 焦点公共属性、Style Modifier 和节点事件入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 焦点核心 | `test/unittest/core/event/focus_core/` | 焦点树、请求、导航、域、默认焦点和恢复验证 |
| 焦点管理器 | `test/unittest/core/manager/focus_manager_test_ng.cpp` | FocusManager 事务、域和激活状态验证 |
| FocusView | `test/unittest/core/manager/focus_view_test_ng.cpp` | View 栈和恢复验证 |
| 按键导航 | `test/unittest/core/common/key_event_manager/`、`test/unittest/core/event/focus_event_handler_test_ng.cpp` | 按键意图、Tab 和事件路由验证 |
| 焦点框 | `test/unittest/core/event/focus_box_test_ng.cpp` | 视觉参数与焦点框验证 |
| Native Focus | `test/unittest/capi/accessors/focus_controller_accessor_test.cpp` | Native 焦点控制接口验证 |

### 相关 Spec

功能域：`specs/04-common-capability/09-focus-framework/01-focus-mechanism/`（功能 ID `04-09-01`）。

| Feat | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| Feat-01 | `Feat-01-focus-tree-node-state-model-spec.md` | 焦点树与节点状态模型 |
| Feat-02 | `Feat-02-focus-request-clear-switch-transaction-spec.md` | 焦点请求、清除与切换事务 |
| Feat-03 | `Feat-03-focus-navigation-traversal-algorithm-spec.md` | 焦点导航与遍历算法 |
| Feat-04 | `Feat-04-focus-scope-group-priority-spec.md` | 焦点域、分组与优先级 |
| Feat-05 | `Feat-05-default-focus-focusview-recovery-spec.md` | 默认焦点、FocusView 与焦点恢复 |
| Feat-06 | `Feat-06-focus-activation-visual-indicator-spec.md` | 焦点激活与视觉指示 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 节点无法获得焦点 | `focus_hub.cpp`、FrameNode 生命周期和 Feat-01/02 |
| Tab、方向键或自定义导航异常 | `focus_event_handler.cpp`、`key_event_manager.cpp` 和 Feat-03 |
| focusScope 或优先节点未生效 | `focus_manager.cpp`、`focus_hub.cpp` 和 Feat-04 |
| 页面、弹窗或窗口切换后焦点未恢复 | `focus_view.cpp`、`focus_manager.cpp`、Pipeline 和 Feat-05 |
| 焦点框不显示或未清理 | `focus_box.cpp`、`focus_hub.cpp` 和 Feat-06 |
| ArkTS 与 Native 请求结果不一致 | SDK 声明、FocusController、`native_interface_focus.cpp` |

## 调试入口

- 核心类型检索：`FocusHub`、`FocusManager`、`FocusView`、`FocusGuard`。
- 请求检索：`RequestFocus`、`RequestFocusImmediately`、`LostFocus`、`SwitchFocus`。
- 导航检索：`FocusStep`、`FocusIntension`、`tabIndex`、`nextFocus`、`PROJECT_AREA`。
- 视觉检索：`FocusActiveReason`、`FocusStyleType`、`FocusPaintParam`、`FocusBoxStyle`。

## 相关主题

- 样式属性：`docs/kb/capabilities/style-attributes.md`。
- [交互归一化：`docs/kb/capabilities/interaction-normalization.md`。](interaction-normalization.md)
- [输入法交互：`docs/kb/capabilities/input-method-interaction.md`。](input-method-interaction.md)