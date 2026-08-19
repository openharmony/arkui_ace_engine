# DynamicComponent 弹窗避让不正确 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-07
> 来源：`docs/context_registry.json` 主题 `DynamicComponentAvoidanceIncorrect`
> 关联功能域：05-12-07（DynamicComponent）、04-17-05（DynamicComponent 机制）、04-02-01（安全区域机制）、03-05-01（窗口机制）

## 问题概述

DynamicComponent 内部创建弹窗或其他浮层时，若宿主窗口的安全区和键盘占用区没有转换并同步到 DynamicComponent 的独立子 UIContent，浮层可能使用错误的可用区域计算位置，表现为系统区域避让或键盘避让不正确。

典型表现：
- DynamicComponent 内弹窗与状态栏、导航指示区域等系统避让区域重叠。
- 输入法弹出后，DynamicComponent 内弹窗或输入内容未避让、避让不足或偏移量异常。
- 宿主页面避让正常，但同一页面中的 DynamicComponent 子内容避让结果不同。

> 覆盖范围说明：当前仅覆盖 DynamicComponent 独立子 UIContent 的安全区与键盘占用区传播链路，不覆盖 Dialog、Popup、Menu 等浮层自身的通用布局算法，也不据此判断所有键盘避让时序问题。

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | DynamicComponent 内部弹窗与浮层 | Issue #74965、Issue #80570 及 DynamicComponent 子 UIContent 结构 | inferred |
| capability | trigger | 宿主窗口安全区与输入法占用区变化 | `UIContentImpl` 的避让区域和 `OCCUPIED_AREA_CHANGE` 处理入口 | verified |
| architecture | root_cause_owner | 宿主 Pipeline 与 DynamicComponent 子 Pipeline 的避让信息传播 | PR #83046 和 `DynamicComponentSafeManager` | verified |
| capability | fix_location | DynamicComponent 视口、安全区求交和键盘高度换算 | `dynamic_component_manager.cpp`、`dynamic_pattern.cpp` | verified |
| architecture | dependency | 窗口视口配置与子 UIContent 更新 | `ui_content_impl.cpp`、`dynamic_component_renderer_impl.cpp` | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| A. 安全区未传播到 DynamicComponent 子管线 | 宿主窗口安全区发生变化，DynamicComponent 使用独立子 UIContent | 子内容中的弹窗仍按完整子视口布局，与宿主系统避让区域重叠 |
| B. 键盘占用区未转换并转发给目标子管线 | DynamicComponent 开启 `allowOccupied`、获得当前焦点且输入法占用区域变化 | 子内容中的输入控件或弹窗未按自身窗口和显示区域换算键盘高度，产生错误偏移 |

## 排查路径

### 快速判断

1. 确认异常内容位于 DynamicComponent 的独立子 UIContent，而不是宿主 Pipeline 直接创建的浮层。
2. 对比宿主页面和 DynamicComponent 子内容收到的系统、导航指示、挖孔等避让区域。
3. 检查当前 DynamicComponent 的视口位置和尺寸是否已按 host node ID 登记。
4. 键盘场景检查 `allowOccupied` 是否为 `true`，以及 DynamicComponent host 是否获得当前焦点。
5. 确认转换后的避让区域和键盘占用信息最终传入子 UIContent 的 `UpdateViewportConfig`。

### 详细排查

#### A. 安全区未传播到 DynamicComponent 子管线排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查宿主 `UIContentImpl` 收到的 `avoidAreas` | 包含当前窗口系统区域、导航指示区域或挖孔区域 | 若为空，先排查窗口避让区监听和平台输入 |
| 2 | 检查宿主 `DynamicComponentSafeManager::SetAvoidArea` | 保存最新宿主避让区域 | 若未更新，检查 `AvoidAreasUpdateOnDynamicComponent` 调用链 |
| 3 | 检查 DynamicComponent 的 viewport config | host node ID 对应的配置包含子组件实际位置和尺寸 | 若缺失，检查 renderer 的 `SetDynamicViewportConfig` |
| 4 | 检查 `GetAvoidAreaIntersection` | 只保留与当前 DynamicComponent 视口相交的矩形 | 若仍使用宿主全局区域，子管线坐标可能错误 |
| 5 | 检查 `UpdateAllDCAvoidArea` | 在子 Pipeline UI 线程调用子 UIContent 的 `UpdateViewportConfig` | 若未调用，检查 DynamicComponent 注册、实例和任务执行器 |

关键代码定位：
- `adapter/ohos/entrance/ui_content_impl.cpp`，`AvoidAreasUpdateOnDynamicComponent`、`AvoidAreaChangedListener::OnAvoidAreaChanged`：捕获并转发宿主避让区状态。
- `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.cpp`，`IntersectRect`、`GetAvoidAreaIntersection`：将宿主避让区域与 DynamicComponent 视口求交。
- `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.cpp`，`UpdateAllDCAvoidArea`：向存活的 DynamicComponent 子 UIContent 分发避让区域。
- `adapter/ohos/entrance/dynamic_component/dynamic_component_renderer_impl.cpp`，`SetDynamicViewportConfig` 调用点：按 host node ID 保存子组件视口。

#### B. 键盘占用区未转换并转发给目标子管线排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 检查 DynamicComponent 创建参数 | `allowOccupied` 按预期设置并传入 `DynamicPattern` | 若为默认 `false`，该组件不会消费键盘占用区 |
| 2 | 检查 DynamicComponent host 的焦点状态 | 目标组件的 `FocusHub::IsCurrentFocus()` 为 `true` | 若未聚焦，继续确认实际输入焦点归属 |
| 3 | 检查 `DynamicKeyboardAvoid` | 宿主 `OCCUPIED_AREA_CHANGE` 已进入 `UpdateDynamicKeyBoardAvoid` | 若未进入，检查 `KeyboardAvoid` 分发顺序和 Pipeline 类型 |
| 4 | 对比子 Pipeline 的 current window 与 display area bottom | 键盘高度按二者差值换算到子 UIContent 使用的坐标范围 | 若直接使用宿主高度，避让量可能过大或不足 |
| 5 | 检查子 UIContent 的 `UpdateViewportConfig` | 收到换算后的 `OccupiedAreaChangeInfo` 和当前子视口配置 | 若未收到，检查子实例、任务执行器及存活组件登记 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/jsview/js_dynamic_component.cpp`，`JSDynamicComponent::Create`：解析 `allowOccupied`。
- `adapter/ohos/entrance/ui_content_impl.cpp`，`DynamicKeyboardAvoid`、`KeyboardAvoid`：从宿主键盘避让链路路由到 DynamicComponent。
- `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.cpp`，`UpdateDynamicKeyBoardAvoid`：执行 `allowOccupied`、焦点判断和键盘高度换算。
- `frameworks/core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.cpp`，`OnAttachContext`、`OnDetachContext`：维护存活 DynamicComponent；`OnDirtyLayoutWrapperSwap` 使用安全区感知的全局偏移更新子视口。

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| A. 安全区未传播到 DynamicComponent 子管线 | 新增 DynamicComponent 安全区管理，保存宿主避让区域和每个组件的视口；求交后更新对应子 UIContent | `ui_content_impl.cpp`、`dynamic_component_manager.cpp`、`dynamic_pattern.cpp`、`dynamic_component_renderer_impl.cpp` | [PR #83046](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/83046) (`fixed`) | PR 关联 Issue #74965，diff 新增避让区传播、视口记录和求交逻辑 |
| B. 键盘占用区未转换并转发给目标子管线 | 仅向开启 `allowOccupied` 且当前聚焦的 DynamicComponent 转发键盘信息，并按子窗口与显示区域差异换算键盘高度 | `js_dynamic_component.cpp`、`ui_content_impl.cpp`、`dynamic_component_manager.cpp` | [PR #83046](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/83046) (`fixed`) | PR diff 新增 `allowOccupied`、焦点门控、键盘高度换算及子 UIContent 更新 |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | [Issue #74965](https://gitcode.com/openharmony/arkui_ace_engine/issues/74965) 记录 DynamicComponent 安全区和键盘避让问题 | A、B | related | 公开 Issue 标题和关联修复 PR | verified |
| CHG-02 | 增加宿主到 DynamicComponent 子 UIContent 的安全区、视口和键盘占用区传播链路 | A、B | fixed | [PR #83046](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/83046)、提交 `251244b55f3` 及当前源码 | verified |
| CHG-03 | 调整同配置键盘避让任务的执行时序 | B 的关联时序 | related | [PR #83724](https://gitcode.com/openharmony/arkui_ace_engine/merge_requests/83724) 修改宿主键盘避让调度，但没有证据表明其专门修复 Issue #74965 | inferred |
| CHG-04 | [Issue #80570](https://gitcode.com/openharmony/arkui_ace_engine/issues/80570) 请求沉淀 DynamicComponent 弹窗避让问题型 KB | A、B | follow_up | 公开 Issue 标题 | verified |

## 预防措施

- 新增独立 UIContent 或子 Pipeline 时，逐项检查窗口尺寸、安全区、键盘占用区、显示区域和坐标原点是否需要从宿主传播。
- 宿主全局避让矩形不能直接作为子视口本地避让数据，应先按子组件实际 viewport 求交或完成坐标转换。
- 多个 DynamicComponent 并存时，以 host node ID 维护各自视口，并仅把键盘占用区分发给获得焦点且明确允许占用区处理的目标组件。
- 单元测试同时覆盖无交集、部分交集、多组件、未聚焦、`allowOccupied=false` 和不同窗口 bottom 差值。
- 补充端到端回归测试，验证 DynamicComponent 内弹窗最终位置；现有测试主要覆盖管理器状态和分发条件，未直接断言浮层最终几何位置。
- 键盘避让任务时序发生变化时，分别验证宿主 Pipeline 和 DynamicComponent 子 Pipeline，避免只覆盖宿主页面。

## 相关主题

- `docs/kb/components/container/dynamic-component.md` — DynamicComponent 组件，FuncID `05-12-07`
- `docs/kb/components/container/dynamic-component.md` — DynamicComponent 机制，FuncID `04-17-05`
- `docs/kb/capabilities/safe-area.md` — 安全区域和键盘避让机制，FuncID `04-02-01`
- `docs/kb/architecture/window-mechanism.md` — 窗口视口、避让区与输入法事件桥接，FuncID `03-05-01`
- `docs/kb/issues/layout/keyboard-avoid-timing-change.md` — 键盘避让调度时序的关联问题
- `specs/05-ui-components/12-embedded-display-components/07-dynamic-component/`
- `specs/04-common-capability/17-embedded-display/05-dynamic-component/`
- `specs/04-common-capability/02-safe-area/01-safe-area-mechanism/`
- `specs/03-engine-framework/05-window-mechanism/01-window-mechanism/`