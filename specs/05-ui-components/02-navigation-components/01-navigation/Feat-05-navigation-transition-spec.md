# 特性规格

> Func-05-02-01-Feat-05 Navigation 转场动画与自定义过渡：固化 customNavContentTransition、NavigationAnimatedTransition、NavigationTransitionProxy（from/to/isInteractive/finishTransition/cancelTransition/updateTransition）、NavContentInfo 的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Navigation 转场动画与自定义过渡 |
| 特性编号 | Func-05-02-01-Feat-05 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P1 |
| 目标版本 | API 9 起支持 customNavContentTransition，NavigationTransitionProxy API 11 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 中 |

## 本次变更范围（Delta）

无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/02-navigation-components/01-navigation/design.md` | Baselined |
| SDK API | `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | — |
| Navigation Pattern | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | — |
| Navigation Model NG | `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp` | — |

---

## 用户故事

### US-1: 配置自定义转场过渡

**作为** 应用开发者,
**我想要** 通过 `customNavContentTransition()` 配置 NavDestination push/pop 时的自定义过渡动画,
**以便** 在页面切换时实现自定义的动画效果替代系统默认转场。

| AC编号 | 醉收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.customNavContentTransition(callback: NavigationAnimatedTransition)` THEN push/pop 时执行自定义过渡动画回调 | 正常 |
| AC-1.2 | WHEN NavigationAnimatedTransition.onTransitionEnd 返回 true THEN 过渡动画完成，正常结束 | 正常 |
| AC-1.3 | WHEN NavigationAnimatedTransition.onTransitionEnd 返回 false THEN 过渡动画中断，回到原始状态 | 边界 |
| AC-1.4 | WHEN NavigationAnimatedTransition.timeout > 0 THEN 超时后自动结束过渡动画 | 边界 |
| AC-1.5 | WHEN NavigationAnimatedTransition.transition 属性设置 THEN push/pop 过渡动画按自定义属性执行 | 正常 |
| AC-1.6 | WHEN 未设置 customNavContentTransition THEN 使用系统默认转场动画 | 正常 |

### US-2: 操作 TransitionProxy

**作为** 应用开发者,
**我想要** 通过 NavigationTransitionProxy 控制转场动画的完成、取消和更新,
**以便** 在交互式转场（如手势驱动）中动态控制过渡进度。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN NavigationTransitionProxy.finishTransition() 调用 THEN 自定义过渡动画完成，NavDestination 正常显示 | 正常 |
| AC-2.2 | WHEN NavigationTransitionProxy.cancelTransition() 调用 THEN 自定义过渡动画取消，NavDestination 回到原始状态 | 正常 |
| AC-2.3 | WHEN NavigationTransitionProxy.updateTransition(progress: number) 调用 THEN 自定义过渡动画进度更新为指定值 | 正常 |
| AC-2.4 | WHEN NavigationTransitionProxy.from 为 NavContentInfo THEN 过渡动画起始 NavDestination 信息可通过 from 获取 | 正常 |
| AC-2.5 | WHEN NavigationTransitionProxy.to 为 NavContentInfo THEN 过渡动画目标 NavDestination 信息可通过 to 获取 | 正常 |
| AC-2.6 | WHEN NavigationTransitionProxy.isInteractive 为 true THEN 过渡动画为交互式（手势驱动），可调用 updateTransition 更新进度 | 正常 |
| AC-2.7 | WHEN NavigationTransitionProxy.isInteractive 为 false THEN 过渡动画为非交互式，finishTransition/cancelTransition 直接结束 | 边界 |
| AC-2.8 | WHEN finishTransition 在动画完成后重复调用 THEN 无操作 | 边界 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-1.1 | US-1 | R-1 | 单元测试 customNavContentTransition callback |
| AC-1.2 | US-1 | R-2 | 单元测试 onTransitionEnd true |
| AC-1.3 | US-1 | R-2 | 单元测试 onTransitionEnd false |
| AC-1.4 | US-1 | R-3 | 单元测试 timeout |
| AC-1.5 | US-1 | R-1 | 单元测试 transition 属性设置 |
| AC-1.6 | US-1 | R-4 | 代码审查 NavigationPattern 默认转场动画 |
| AC-2.1 | US-2 | R-5 | 单元测试 finishTransition |
| AC-2.2 | US-2 | R-6 | 单元测试 cancelTransition |
| AC-2.3 | US-2 | R-7 | 单元测试 updateTransition progress |
| AC-2.4 | US-2 | R-8 | 单元测试 TransitionProxy from |
| AC-2.5 | US-2 | R-8 | 单元测试 TransitionProxy to |
| AC-2.6 | US-2 | R-9 | 单元测试 isInteractive true |
| AC-2.7 | US-2 | R-9 | 单元测试 isInteractive false |
| AC-2.8 | US-2 | R-5 | 单元测试 finishTransition repeat |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | customNavContentTransition 设置自定义转场过渡回调：回调函数返回 NavigationAnimatedTransition 对象，包含 transition（动画属性）、onTransitionEnd（结束回调）、timeout（超时时间） | NavigationAnimatedTransition 包含 transition、onTransitionEnd、timeout | AC-1.1, AC-1.5 |
| R-2 | 行为 | — | NavigationAnimatedTransition.onTransitionEnd 回调：返回 true 表示过渡动画正常完成，返回 false 表示过渡动画中断回退 | — | AC-1.2, AC-1.3 |
| R-3 | 边界 | — | NavigationAnimatedTransition.timeout 超时：超时后自动结束过渡动画，防止动画卡住 | timeout 单位为毫秒 | AC-1.4 |
| R-4 | 行为 | — | 未设置 customNavContentTransition 时使用系统默认转场动画：Stack 模式 push 为从右侧滑入，pop 为从左侧滑出 | — | AC-1.6 |
| R-5 | 行为 | — | NavigationTransitionProxy.finishTransition 完成过渡动画：动画完成后 NavDestination 正常显示；重复调用无操作 | — | AC-2.1, AC-2.8 |
| R-6 | 行为 | — | NavigationTransitionProxy.cancelTransition 取消过渡动画：动画取消后 NavDestination 回到原始状态 | — | AC-2.2 |
| R-7 | 行为 | — | NavigationTransitionProxy.updateTransition 更新过渡进度：progress 值 0~1 表示动画进度 | progress 范围 [0, 1] | AC-2.3 |
| R-8 | 行为 | — | NavigationTransitionProxy.from/to 包含 NavContentInfo：from 为过渡起始 NavDestination 信息，to 为过渡目标 NavDestination 信息 | NavContentInfo 包含 name 和 id | AC-2.4, AC-2.5 |
| R-9 | 行为 | — | NavigationTransitionProxy.isInteractive 标识交互式过渡：true 时为手势驱动交互式过渡，可调用 updateTransition；false 时为非交互式 | — | AC-2.6, AC-2.7 |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-1.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` customNavContentTransition callback |
| VM-2 | AC-1.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onTransitionEnd true |
| VM-3 | AC-1.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onTransitionEnd false |
| VM-4 | AC-1.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` timeout |
| VM-5 | AC-1.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` transition 属性 |
| VM-6 | AC-1.6 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认转场动画 |
| VM-7 | AC-2.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` finishTransition |
| VM-8 | AC-2.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` cancelTransition |
| VM-9 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` updateTransition |
| VM-10 | AC-2.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` TransitionProxy from |
| VM-11 | AC-2.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` TransitionProxy to |
| VM-12 | AC-2.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` isInteractive true |
| VM-13 | AC-2.7 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` isInteractive false |
| VM-14 | AC-2.8 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` finishTransition repeat |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 均为 Public 开放范围。

| API 签名 | 类型 | d.ts 位置 | @since | 开放范围 | 功能描述 |
|----------|------|-----------|--------|----------|----------|
| `customNavContentTransition(callback: (transition: NavigationTransitionProxy) => NavigationAnimatedTransition): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置自定义转场过渡回调 |

**关联类型定义**：

| 类型 | 定义 | @since |
|------|------|--------|
| `NavigationAnimatedTransition` | `{ transition: TransitionEffect, onTransitionEnd: (isTransitionDone: boolean) => boolean, timeout?: number }` | API 9 |
| `NavigationTransitionProxy` | `{ from: NavContentInfo, to: NavContentInfo, isInteractive: boolean, finishTransition: () => void, cancelTransition: () => void, updateTransition: (progress: number) => void }` | API 11 |
| `NavContentInfo` | `{ name: string, id: string }` | API 11 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 9 | customNavContentTransition 基础接口 | 自定义过渡动画 | 无需迁移 |
| API 11 | NavigationTransitionProxy 新增 finishTransition/cancelTransition/updateTransition | 交互式转场控制 | 未使用 TransitionProxy 时默认非交互式 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| 过渡动画触发时机 | Stack 模式下 NavDestination push/pop 时触发转场动画 |
| TransitionProxy 生命周期 | NavigationTransitionProxy 在过渡动画期间有效，动画完成后失效 |
| 交互式过渡 | isInteractive=true 时需配合手势事件驱动 updateTransition |
| timeout 保护 | NavigationAnimatedTransition.timeout 防止自定义过渡动画卡住 |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | 自定义过渡动画不增加额外帧延迟，transition 属性直接应用于动画管线 |
| 可调试性 | NavigationPattern 支持 DumpInfo 输出 customNavContentTransition 配置 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 系统默认 push/pop 滑动动画适合竖屏 | — | 单元测试 | — |
| 平板 | Split 模式下仅 Content 区域播放过渡动画 | — | 单元测试 | — |
| 折叠屏 | 交互式过渡配合手势在折叠/展开时更自然 | isInteractive=true 配合手势 | 单元测试 | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| 转场动画管线 | customNavContentTransition 参与全局渲染管线动画调度 |
| NavDestination 生命周期 | 过渡动画期间 NavDestination 生命周期受 TransitionProxy 控制 |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 规则编号连续且可追溯到源码
- [x] API 变更分析基于真实 SDK 定义文件（navigation.d.ts）
- [x] 兼容性声明标注 API 版本差异（NavigationTransitionProxy API 11）
- [x] 所有源码引用包含 file 信息
- [x] 无 TBD/TODO 占位符
- [x] 变更范围 Delta 明确标注为已有实现补录

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp/.h` | Pattern 层，转场动画管理 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp/.h` | NG Model 层，customNavContentTransition 属性设置 |
| `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp/.h` | JS 桥接层，转场动画属性解析 |
| `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | SDK 公开 API 定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/navigation/` | Navigation 单元测试目录
