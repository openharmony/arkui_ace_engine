# Scroller 非法数值偏移校验 Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `ScrollerNaNOffsetValidation`
> 关联功能域：滚动通用能力（FuncID `05-03-01`）

## 问题概述

动态声明式前端调用 `Scroller.scrollTo` 时，如果 `xOffset` 或 `yOffset` 传入数值型 `NaN`，
旧版字符串条件校验会被绕过，非法偏移可能继续进入维度转换和滚动控制流程，典型现象为页面不显示。

当前仅覆盖 `JSScrollerBinding::ScrollTo` 的数值型 `NaN` 单一根因和公开案例；静态前端、
其他 Scroller 方法及其他非法数值的行为需要独立验证后补充。

典型表现：
- `Scroller.scrollTo({ xOffset: NaN, yOffset: 0 })` 或对应的 `yOffset: NaN` 调用后页面不显示。
- 正常数值或合法尺寸字符串可以通过校验，问题集中在数值型 `NaN`。
- 问题发生在动态声明式前端桥接层，不能直接泛化为所有 ArkUI 前端和所有数值型 API。

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | Scroller 与滚动类组件 | [GitCode Issue #66910](https://gitcode.com/openharmony/arkui_ace_engine/issues/66910) 的问题现象 | user_claimed |
| capability | trigger | `Scroller.scrollTo` 编程式滚动 | `JSScrollerBinding::JSBind` 将 `scrollTo` 绑定到 `JSScrollerBinding::ScrollTo` | verified |
| architecture | root_cause_owner | 动态声明式前端维度参数转换 | `ConvertFromJSValue<Dimension>` 与 `JSViewAbstract::ParseJsDimension` | verified |
| architecture | fix_location | `JSScrollerBinding::ScrollTo` 入参校验 | [GitCode PR #74844](https://gitcode.com/openharmony/arkui_ace_engine/pull/74844) 与提交 `99ba2e6e1a1` | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 数值型 `NaN` 绕过字符串条件校验 | `xOffset` 或 `yOffset` 是 JavaScript Number 类型的 `NaN`；旧逻辑仅在 `IsString()` 为真时执行 `DIMENSION_REGEX` | 调用 `Scroller.scrollTo` 传入计算结果为 `NaN` 的偏移量 |

## 排查路径

### 快速判断

1. 确认问题只在 `Scroller.scrollTo` 的 `xOffset` 或 `yOffset` 为 `NaN` 时出现，并用合法数值做对照。
2. 确认调用经过动态声明式前端的 `JSScrollerBinding::ScrollTo`，不要与静态 ArkTS 前端实现混为一谈。
3. 检查 `DIMENSION_REGEX` 是否无条件作用于两个偏移参数的 `ToString()` 结果。
4. 确认校验失败后在取得滚动控制器之前直接返回，非法 `Dimension` 不会进入 `FreeScrollTo` 或 `AnimateTo`。

### 详细排查

#### 数值型 `NaN` 绕过字符串条件校验

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 分别以合法数值和 `NaN` 调用 `Scroller.scrollTo` | 合法值正常滚动；`NaN` 调用被忽略且页面状态保持稳定 | 继续确认实际调用的前端范式和 Scroller 实例 |
| 2 | 检查 `JSScrollerBinding::ScrollTo` 的 `convertFail` 条件 | `xOffsetStr->ToString()` 与 `yOffsetStr->ToString()` 均无条件执行 `DIMENSION_REGEX` | 若仍受 `IsString()` 限制，则可能处于修复前版本 |
| 3 | 检查 `ConvertFromJSValue<Dimension>` | 该转换进入 `JSViewAbstract::ParseJsDimensionVp` | 若调用链不同，按实际转换入口重新定位 |
| 4 | 检查 `JSViewAbstract::ParseJsDimension` 的 Number 分支 | Number 会直接构造 `CalcDimension`，因此上游必须阻止非有限值进入 | 若已有显式有限性检查，重新验证当前根因是否仍成立 |
| 5 | 检查校验失败后的控制流 | 在取得控制器及调用 `FreeScrollTo`/`AnimateTo` 前返回 | 若非法值仍到达控制器，继续排查其他调用入口 |

关键代码定位：
- `frameworks/bridge/declarative_frontend/jsview/js_scroller.cpp`，`JSScrollerBinding::ScrollTo`：读取偏移参数、执行格式校验并决定是否进入滚动控制流程。
- `frameworks/bridge/declarative_frontend/jsview/js_view_common_def.inl`，`ConvertFromJSValue<Dimension>`：把 JS 值路由到维度解析。
- `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp`，`JSViewAbstract::ParseJsDimension`：Number 分支直接以数值构造 `CalcDimension`。

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 数值型 `NaN` 绕过字符串条件校验 | 移除正则校验外层的 `IsString()` 条件，对数值和字符串参数的 `ToString()` 结果统一执行 `DIMENSION_REGEX`；校验失败立即返回 | `frameworks/bridge/declarative_frontend/jsview/js_scroller.cpp`，`JSScrollerBinding::ScrollTo` | [PR #74844](https://gitcode.com/openharmony/arkui_ace_engine/pull/74844) / `99ba2e6e1a1` (`fixed`) | PR diff 显示移除两个 `IsString()` 门控；`"NaN"` 不符合数值尺寸正则 |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 提交 `1558cce7eae2` 在尺寸正则校验外增加 `IsString()` 条件 | 数值型 `NaN` 绕过字符串条件校验 | introduced | 修复前版本 `git blame` 指向该提交，且提交 diff 包含门控条件 | verified |
| CHG-02 | [Issue #66910](https://gitcode.com/openharmony/arkui_ace_engine/issues/66910) 报告 `ScrollTo(NaN)` 后页面不显示 | 数值型 `NaN` 绕过字符串条件校验 | related | 公开 Issue 提供触发参数和问题现象，但期望行为与复现信息不完整 | user_claimed |
| CHG-03 | [PR #74844](https://gitcode.com/openharmony/arkui_ace_engine/pull/74844) / `99ba2e6e1a1` 移除 `IsString()` 门控 | 数值型 `NaN` 绕过字符串条件校验 | fixed | PR 仅修改 `JSScrollerBinding::ScrollTo`，当前源码保留该修复 | verified |

## 预防措施

- 为动态前端 `Scroller.scrollTo` 增加参数化回归测试，至少覆盖合法 Number、合法尺寸字符串、
  数值型 `NaN` 和字符串 `"NaN"`，并验证非法调用不会到达滚动控制器。
- 数值到 `Dimension` 的公共转换入口应明确评估 `NaN`/无穷值策略；不能仅凭 JavaScript
  `IsNumber()` 判定数值可用于布局或动画。
- 修改桥接层类型判断时，同时检查不同 JavaScript 类型是否会绕过后续格式、范围和有限性校验。
- PR 页面声明 TDD 自验通过，但 PR 未提交对应回归测试；后续补测时将测试变更标记为 `follow_up`。

## 相关主题

- `frameworks/bridge/declarative_frontend/jsview/js_scroller.cpp`
- `frameworks/bridge/declarative_frontend/jsview/js_view_common_def.inl`
- `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp`
- `docs/kb/capabilities/scroll-common-capability.md`（滚动通用能力，FuncID `05-03-01`）
- `specs/05-ui-components/03-scroll-container-components/01-scroll-common-capability/`