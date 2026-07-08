# 特性规格

> Func-05-02-01-Feat-07 Navigation 事件回调与Modifier：固化 onTitleModeChange、onNavBarStateChange、onNavigationModeChange、NavigationModifier（extends NavigationAttribute, implements AttributeModifier<NavigationAttribute>, applyNormalAttribute）的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Navigation 事件回调与Modifier |
| 特性编号 | Func-05-02-01-Feat-07 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P1 |
| 目标版本 | API 9 起支持事件回调，NavigationModifier API 9+ |
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
| Navigation Event Hub | `frameworks/core/components_ng/pattern/navigation/navigation_event_hub.h` | — |
| Navigation Modifier | `frameworks/bridge/declarative_frontend/ark_modifier/src/navigation_modifier.ts` | — |
| ArkTS Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.cpp/.h` | — |

---

## 用户故事

### US-1: 监听标题模式变化

**作为** 应用开发者,
**我想要** 通过 `onTitleModeChange()` 监听标题栏标题模式变化事件,
**以便** 在标题模式切换时执行自定义逻辑（如调整标题布局）。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.onTitleModeChange(callback: (titleMode: NavigationTitleMode) => void)` THEN 注册标题模式变化回调 | 正常 |
| AC-1.2 | WHEN 标题模式从 Free 切换为 Mini THEN 回调参数 titleMode 为 NavigationTitleMode.Mini | 正常 |
| AC-1.3 | WHEN 标题模式从 Mini 切换为 Full THEN 回调参数 titleMode 为 NavigationTitleMode.Full | 正常 |
| AC-1.4 | WHEN 未注册 onTitleModeChange THEN 标题模式切换时不触发回调 | 边界 |

### US-2: 监听导航栏状态变化

**作为** 应用开发者,
**我想要** 通过 `onNavBarStateChange()` 监听 NavBar 显示/隐藏状态变化事件,
**以便** 在导航栏状态变化时执行自定义逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.onNavBarStateChange(callback: (state: NavigationNavBarState) => void)` THEN 注册导航栏状态变化回调 | 正常 |
| AC-2.2 | WHEN NavBar 从显示切换为隐藏 THEN 回调触发，参数 state 表示隐藏状态 | 正常 |
| AC-2.3 | WHEN NavBar 从隐藏切换为显示 THEN 回调触发，参数 state 表示显示状态 | 正常 |
| AC-2.4 | WHEN 未注册 onNavBarStateChange THEN 导航栏状态变化时不触发回调 | 边界 |

### US-3: 监听导航模式变化

**作为** 应用开发者,
**我想要** 通过 `onNavigationModeChange()` 监听 NavigationMode 模式变化事件,
**以便** 在导航模式（Stack/Split/Auto）切换时执行自定义逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.onNavigationModeChange(callback: (mode: NavigationMode) => void)` THEN 注册导航模式变化回调 | 正常 |
| AC-3.2 | WHEN Navigation 从 Stack 模式切换为 Split THEN 回调参数 mode 为 NavigationMode.Split | 正常 |
| AC-3.3 | WHEN Navigation 从 Split 模式切换为 Stack THEN 回调参数 mode 为 NavigationMode.Stack | 正常 |
| AC-3.4 | WHEN Auto 模式自动切换 THEN 回调触发，参数 mode 为实际切换后的 NavigationMode | 正常 |
| AC-3.5 | WHEN 未注册 onNavigationModeChange THEN 模式切换时不触发回调 | 边界 |

### US-4: 使用 NavigationModifier

**作为** 应用开发者,
**我想要** 通过 NavigationModifier 设置 Navigation 属性,
**以便** 使用 AttributeModifier 机制动态修改 Navigation 的属性。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN NavigationModifier extends NavigationAttribute THEN NavigationModifier 继承 NavigationAttribute 的所有属性方法 | 正常 |
| AC-4.2 | WHEN NavigationModifier implements AttributeModifier<NavigationAttribute> THEN NavigationModifier 符合 AttributeModifier 接口规范 | 正常 |
| AC-4.3 | WHEN NavigationModifier.applyNormalAttribute(instance: NavigationAttribute) 调用 THEN NavigationModifier 的属性应用到 NavigationAttribute 实例 | 正常 |
| AC-4.4 | WHEN 通过 NavigationModifier 设置 mode/title/hideTitleBar 等属性 THEN 属性值通过 C API 桥接层写入 NavigationLayoutProperty | 正常 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-1.1 | US-1 | R-1 | 单元测试 onTitleModeChange 注册 |
| AC-1.2 | US-1 | R-1 | 单元测试 onTitleModeChange Mini 回调 |
| AC-1.3 | US-1 | R-1 | 单元测试 onTitleModeChange Full 回调 |
| AC-1.4 | US-1 | R-1 | 代码审查 NavigationEventHub 默认无回调 |
| AC-2.1 | US-2 | R-2 | 单元测试 onNavBarStateChange 注册 |
| AC-2.2 | US-2 | R-2 | 单元测试 onNavBarStateChange hidden 回调 |
| AC-2.3 | US-2 | R-2 | 单元测试 onNavBarStateChange shown 回调 |
| AC-2.4 | US-2 | R-2 | 代码审查 NavigationEventHub 默认无回调 |
| AC-3.1 | US-3 | R-3 | 单元测试 onNavigationModeChange 注册 |
| AC-3.2 | US-3 | R-3 | 单元测试 onNavigationModeChange Split 回调 |
| AC-3.3 | US-3 | R-3 | 单元测试 onNavigationModeChange Stack 回调 |
| AC-3.4 | US-3 | R-3 | 单元测试 onNavigationModeChange Auto 切换回调 |
| AC-3.5 | US-3 | R-3 | 代码审查 NavigationEventHub 默认无回调 |
| AC-4.1 | US-4 | R-4 | 单元测试 NavigationModifier extends |
| AC-4.2 | US-4 | R-4 | 单元测试 NavigationModifier implements AttributeModifier |
| AC-4.3 | US-4 | R-5 | 单元测试 NavigationModifier applyNormalAttribute |
| AC-4.4 | US-4 | R-5 | 单元测试 NavigationModifier 属性桥接 |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | onTitleModeChange 注册标题模式变化回调：回调参数为 NavigationTitleMode（Free/Full/Mini），在标题模式切换时触发；未注册时不触发 | 回调在 UI 线程执行 | AC-1.1~AC-1.4 |
| R-2 | 行为 | — | onNavBarStateChange 注册导航栏状态变化回调：回调参数为 NavigationNavBarState（显示/隐藏），在 NavBar 显示/隐藏切换时触发；未注册时不触发 | 回调在 UI 线程执行 | AC-2.1~AC-2.4 |
| R-3 | 行为 | — | onNavigationModeChange 注册导航模式变化回调：回调参数为 NavigationMode（Stack/Split/Auto/AUTO_WITH_ASPECT_RATIO），在模式切换时触发；Auto 模式自动切换时也触发；未注册时不触发 | 回调在 UI 线程执行 | AC-3.1~AC-3.5 |
| R-4 | 行为 | — | NavigationModifier extends NavigationAttribute 继承所有属性方法，implements AttributeModifier<NavigationAttribute> 符合接口规范 | NavigationModifier 在 ArkTS Modifier 层定义 | AC-4.1, AC-4.2 |
| R-5 | 行为 | — | NavigationModifier.applyNormalAttribute 将 NavigationModifier 的属性应用到 NavigationAttribute 实例：属性值通过 C API 桥接层（arkts_native_navigation_bridge.cpp）写入 NavigationLayoutProperty | — | AC-4.3, AC-4.4 |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-1.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onTitleModeChange 注册 |
| VM-2 | AC-1.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onTitleModeChange Mini |
| VM-3 | AC-1.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onTitleModeChange Full |
| VM-4 | AC-1.4 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_event_hub.h` 默认无回调 |
| VM-5 | AC-2.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onNavBarStateChange 注册 |
| VM-6 | AC-2.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onNavBarStateChange hidden |
| VM-7 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onNavBarStateChange shown |
| VM-8 | AC-2.4 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_event_hub.h` 默认无回调 |
| VM-9 | AC-3.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onNavigationModeChange 注册 |
| VM-10 | AC-3.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onNavigationModeChange Split |
| VM-11 | AC-3.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onNavigationModeChange Stack |
| VM-12 | AC-3.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` onNavigationModeChange Auto |
| VM-13 | AC-3.5 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_event_hub.h` 默认无回调 |
| VM-14 | AC-4.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationModifier extends |
| VM-15 | AC-4.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationModifier implements |
| VM-16 | AC-4.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationModifier applyNormalAttribute |
| VM-17 | AC-4.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` NavigationModifier 属性桥接 |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 均为 Public 开放范围。

| API 签名 | 类型 | d.ts 位置 | @since | 开放范围 | 功能描述 |
|----------|------|-----------|--------|----------|----------|
| `onTitleModeChange(callback: (titleMode: NavigationTitleMode) => void): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 注册标题模式变化回调 |
| `onNavBarStateChange(callback: (state: NavigationNavBarState) => void): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 注册导航栏状态变化回调 |
| `onNavigationModeChange(callback: (mode: NavigationMode) => void): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 注册导航模式变化回调 |
| `NavigationModifier` | Public | navigation_modifier.d.ts | API 9 | Public | Navigation 属性修改器 |

**NavigationModifier 结构**：

| 属性 | 类型 | 说明 |
|------|------|------|
| extends | NavigationAttribute | 继承 NavigationAttribute 所有属性方法 |
| implements | AttributeModifier<NavigationAttribute> | 符合 AttributeModifier 接口规范 |
| applyNormalAttribute(instance: NavigationAttribute) | void | 将 Modifier 属性应用到 NavigationAttribute 实例 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 9 | onTitleModeChange/onNavBarStateChange/onNavigationModeChange 新增 | 事件回调完善 | 无需迁移 |
| API 9 | NavigationModifier 新增 | ArkTS Modifier 属性修改器 | 无需迁移 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| 事件回调存储 | NavigationEventHub 存储事件回调，NavigationPattern 在状态变化时触发回调 |
| 回调线程 | 所有事件回调在 UI 线程执行 |
| NavigationModifier 桥接 | NavigationModifier 通过 C API 桥接层（arkts_native_navigation_bridge.cpp）将属性写入 NavigationLayoutProperty |
| NavigationModelStatic | NavigationModelStatic 提供静态版 Model 实现，与 NavigationModelNG 并行 |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | 事件回调注册/触发无额外开销，回调直接在 Pattern 层触发 |
| 可调试性 | NavigationEventHub 支持 DumpInfo 输出已注册的回调信息 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | onNavigationModeChange 在 Auto 模式切换时触发 | Stack ↔ Split 切换回调 | 单元测试 | — |
| 平板 | onNavigationModeChange 在 Split 模式下一般不触发 | 持续 Split 模式 | 单元测试 | — |
| 折叠屏 | onNavigationModeChange 在折叠/展开时频繁触发 | Auto 模式动态切换 | 单元测试 | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| AttributeModifier 体系 | NavigationModifier 参与全局 AttributeModifier 属性修改体系 |
| C API 桥接层 | NavigationModifier 属性通过 arkts_native_navigation_bridge.cpp 桥接 |
| 事件回调体系 | onTitleModeChange/onNavBarStateChange/onNavigationModeChange 参与 NavigationEventHub 事件体系 |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 规则编号连续且可追溯到源码
- [x] API 变更分析基于真实 SDK 定义文件（navigation.d.ts）
- [x] 兼容性声明标注 API 版本差异
- [x] 所有源码引用包含 file 信息
- [x] 无 TBD/TODO 占位符
- [x] 变更范围 Delta 明确标注为已有实现补录

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/navigation/navigation_event_hub.h` | 事件回调定义 |
| `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp/.h` | Pattern 层，回调触发 |
| `frameworks/bridge/declarative_frontend/ark_modifier/src/navigation_modifier.ts` | ArkTS Modifier 定义 |
| `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.cpp/.h` | ArkTS 桥接层 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_static.cpp/.h` | 静态版 Model 层 |
| `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | SDK 公开 API 定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/navigation/` | Navigation 单元测试目录
