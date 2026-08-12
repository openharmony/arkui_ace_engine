# Menu 滑动被误判为点击导致菜单异常关闭 Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `MenuSwipeMisrecognizedAsClick`
> 关联功能域：05-06-01

## 问题概述

用户对菜单内容进行上下滑动（scroll）时，菜单被直接关闭；预期行为是仅菜单内容滑动，菜单本身不关闭。其根因是 Menu 的触摸关闭判定条件被放宽，导致"手指全程未离开菜单边界"的滑动也被识别为点击（click），触发了菜单关闭逻辑。

典型表现：
- 对 Menu / bindMenu 弹出的菜单内容进行上下滑动，手指抬起后菜单立即关闭
- 滑动过程中手指始终保持在菜单边界内，但仍触发了 onClick / HideMenu
- 现象在 API12+ 版本上出现（受 `Container::GreatOrEqualAPITargetVersion(VERSION_TWELVE)` 分支控制）

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 点击判定条件过宽 | Menu 的触摸关闭逻辑将"手指全程未出边界"直接等同于点击，未区分钟点与滑动手势 | 用户上下滑动菜单内容，手指未离开菜单边界，抬起即被判定为点击，菜单关闭 |
| Menu 自定义触摸处理与 ClickRecognizer 判定不一致 | MenuPattern/CustomMenuItemPattern 自行实现 OnTouch 关闭逻辑，与系统 ClickRecognizer 的判定标准不完全一致 | Menu 的 IsOffsetInNodeBounds 仅做边界判定，而 ClickRecognizer::IsPointInRegion 还含距离阈值与响应区域判定，两者口径不同导致边界场景行为偏差 |

## 排查路径

### 快速判断

1. 复现：弹出 Menu / bindMenu，在菜单内容区域做上下滑动（非点击），观察菜单是否在手指抬起后关闭。若关闭，命中本问题。
2. 检查源码 `MenuPattern::OnTouchEvent` 与 `CustomMenuItemPattern::OnTouch` 中是否存在 `movedOutOfRegion_` / `IsOffsetInNodeBounds` 逻辑（PR #86305 引入）。若存在，说明采用了"边界内即点击"的放宽判定。
3. 确认 API 版本：该逻辑受 `Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)` 分支保护，API12+ 生效。
4. 对比修复 PR #86878 是否已合入：该 PR 完整回退 #86305，恢复 `DEFAULT_CLICK_DISTANCE`（15px）距离判定。

### 详细排查

#### 点击判定条件过宽 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 查阅 `menu_pattern.cpp` 的 `OnTouchEvent`，确认 TouchType::UP 分支的判定条件 | 若为 `!movedOutOfRegion_ && IsOffsetInNodeBounds(...)` 则命中根因 A | 若仍为 `(touchUpOffset - lastTouchOffset_).GetDistance() <= DEFAULT_CLICK_DISTANCE` 则未命中，转根因 B |
| 2 | 查阅 `menu_item_pattern.cpp` 的 `OnTouch`，确认 UP 分支判定 | 同上，CustomMenuItem 使用相同模式 | — |
| 3 | 确认 `DEFAULT_CLICK_DISTANCE` 常量是否存在于 `menu_pattern.h` | PR #86305 删除了该常量；若不存在则说明采用了新逻辑 | — |

关键代码定位：
- `frameworks/core/components_ng/pattern/menu/menu_pattern.cpp:677` `MenuPattern::OnTouchEvent`：TouchType::UP 分支使用 `IsOffsetInNodeBounds` + `!movedOutOfRegion_` 判定点击
- `frameworks/core/components_ng/pattern/menu/menu_pattern.cpp:669` `MenuPattern::IsOffsetInNodeBounds`：仅判断坐标是否在 frameSize 范围内，无距离阈值
- `frameworks/core/components_ng/pattern/menu/menu_item/menu_item_pattern.cpp:1555` `CustomMenuItemPattern::OnTouch`：同样的边界判定逻辑
- `frameworks/core/components_ng/pattern/menu/menu_pattern.h:973` / `menu_item_pattern.h:736`：`movedOutOfRegion_` 成员声明

#### Menu 自定义触摸处理与 ClickRecognizer 判定不一致 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 查阅 `click_recognizer.cpp` 的 `IsPointInRegion` | ClickRecognizer 同时校验距离阈值（distanceThreshold_）与响应区域（responseRegionBuffer_） | 若 Menu 的判定与之完全一致则未命中 |
| 2 | 对比 Menu 的 `IsOffsetInNodeBounds` 与 ClickRecognizer 判定 | Menu 仅做 frameSize 边界判定，缺少距离阈值维度，口径更宽 | — |
| 3 | 确认 Menu 注释中是否声明"mirroring ClickRecognizer::IsPointInRegion" | 源码注释明确声明镜像 ClickRecognizer，但实际实现仅做了边界判定子集 | — |

关键代码定位：
- `frameworks/core/components_ng/gestures/recognizers/click_recognizer.cpp:67` `ClickRecognizer::IsPointInRegion`：含 distanceThreshold_ 距离校验 + responseRegionBuffer_ 响应区域校验
- `frameworks/core/components_ng/pattern/menu/menu_pattern.cpp:695` 注释声明"mirroring ClickRecognizer::IsPointInRegion"

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 典型 PR / Commit 参考 |
|----------|----------|---------------|----------------------|
| 点击判定条件过宽 | 回退 PR #86305，恢复基于按下↔抬起直线距离（DEFAULT_CLICK_DISTANCE=15px）的点击判定，使长距离滑动不被误判为点击 | `menu_pattern.cpp` OnTouchEvent UP 分支恢复 `GetDistance() <= DEFAULT_CLICK_DISTANCE`；`menu_item_pattern.cpp` OnTouch 同步恢复；删除 `movedOutOfRegion_`、`IsOffsetInNodeBounds`，恢复 `DEFAULT_CLICK_DISTANCE` 常量 | PR #86878（完整回退 #86305） |
| Menu 自定义触摸处理与 ClickRecognizer 判定不一致 | 若需保留放宽判定，应使 Menu 的点击判定与 ClickRecognizer 口径完全对齐（含距离阈值），而非仅做边界判定 | `menu_pattern.cpp` IsOffsetInNodeBounds 增加距离阈值校验，或直接复用 ClickRecognizer 判定 | 待后续优化 |

## 关联案例

| 案例编号 | 问题简述 | 根因类别 | 修复方式 | 关联 PR / Issue |
|----------|----------|----------|----------|----------------|
| CASE-01 | 上下滑动菜单内容时菜单异常关闭 | 点击判定条件过宽 | 回退 PR #86305，恢复距离判定 | 引入 PR [#86305](https://gitcode.com/openharmony/arkui_ace_engine/pull/86305)；修复 PR [#86878](https://gitcode.com/openharmony/arkui_ace_engine/pull/86878)；关联 Issue [#79067](https://gitcode.com/openharmony/arkui_ace_engine/issues/79067) |
| CASE-02 | 手指按下与抬起位置距离较远时 onClick 不触发，导致菜单无法关闭（#86305 试图修复的历史问题） | Menu 自定义触摸处理与 ClickRecognizer 判定不一致 | #86305 将距离判定改为边界判定试图对齐 ClickRecognizer，但矫枉过正导致滑动误判；最终由 #86878 回退 | 引入 PR [#86305](https://gitcode.com/openharmony/arkui_ace_engine/pull/86305)；原始 Issue [#78531](https://gitcode.com/openharmony/arkui_ace_engine/issues/78531) |

## 预防措施

- Menu 的触摸关闭判定不应仅依赖"手指是否出边界"，必须同时区分点按（tap）与滑动手势；引入 MOVE 距离阈值或复用 ClickRecognizer 完整判定口径。
- 修改 Menu 自定义 OnTouch 的点击判定时，须同步验证"滑动菜单内容不关闭"与"远距离抬起可关闭"两个场景，避免顾此失彼。
- MenuPattern 与 CustomMenuItemPattern 共享同一套判定逻辑（IsOffsetInNodeBounds），修改时两处必须同步，并补充对应单元测试（见 `test/unittest/core/pattern/menu/`）。

## 相关主题

- `docs/kb/components/overlay/menu.md` — Menu 菜单组件代码型 KB
- `frameworks/core/components_ng/pattern/menu/` — Menu 模式源码目录
- `frameworks/core/components_ng/gestures/recognizers/click_recognizer.cpp` — ClickRecognizer 点击识别器（判定口径参考）
