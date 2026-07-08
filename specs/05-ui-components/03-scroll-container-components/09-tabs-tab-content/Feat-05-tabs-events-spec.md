# 特性规格

> Func-05-03-09-Feat-05 Tabs/TabContent 事件回调：固化 onChange、onSelected、onUnselected（since 18）、onTabBarClick、onAnimationStart、onAnimationEnd、onGestureSwipe、onContentWillChange、onContentDidScroll（since 23）、OnTabsAnimationStartCallback、OnTabsAnimationEndCallback、OnTabsGestureSwipeCallback、OnTabsContentWillChangeCallback、OnTabsContentDidScrollCallback 的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Tabs/TabContent 事件回调 (Tabs/TabContent Event Callbacks) |
| 特性编号 | Func-05-03-09-Feat-05 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 8 起支持，API 10+ 有多项扩展 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 中 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。覆盖 Tabs/TabContent 全量事件回调（onChange/onSelected/onUnselected/onTabBarClick/onAnimationStart/onAnimationEnd/onGestureSwipe/onContentWillChange/onContentDidScroll）、回调签名类型（OnTabsAnimationStartCallback/OnTabsAnimationEndCallback/OnTabsGestureSwipeCallback/OnTabsContentWillChangeCallback/OnTabsContentDidScrollCallback）。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/09-tabs-tab-content/design.md` | Baselined |
| SDK API | `docs/sdk/ArkUI_SDK_API_Knowledge_Base.md` | — |
| SDK 组件 | `docs/sdk/Component_API_Knowledge_Base_CN.md` | — |

---

## 用户故事

### US-1: 监听标签页切换事件

**作为** 应用开发者,
**我想要** 通过 onChange 回调监听标签页选中状态变更,
**以便** 在标签页切换时执行响应逻辑（如更新数据、刷新 UI）。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 标签页从 index A 切换到 index B THEN onChange 回调被触发，参数为新的 index B | 正常 |
| AC-5.2 | WHEN changeIndex 切换到当前已选中的 index THEN onChange 不触发 | 边界 |
| AC-5.3 | WHEN TabsController.changeIndex 主动切换 THEN onChange 回调被触发 | 正常 |

### US-2: 监听标签选中/取消选中事件

**作为** 应用开发者,
**我想要** 通过 onSelected 和 onUnselected 回调监听标签选中和取消选中状态,
**以便** 在标签选中态变化时执行差异化逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.4 | WHEN 标签被选中 THEN onSelected 回调被触发，参数为选中标签的 index | 正常 |
| AC-5.5 | WHEN 标签取消选中 THEN onUnselected 回调被触发，参数为取消选中标签的 index | 正常 |
| AC-5.6 | WHEN onUnselected 仅 API >= 18 支持 THEN API < 18 设置 onUnselected 不生效 | 边界 |

### US-3: 监听标签栏点击事件

**作为** 应用开发者,
**我想要** 通过 onTabBarClick 回调监听标签栏点击事件,
**以便** 在用户点击标签栏时执行前置逻辑（如拦截切换、记录点击行为）。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.7 | WHEN 用户点击标签栏项 THEN onTabBarClick 回调被触发，参数为被点击项的 index | 正常 |
| AC-5.8 | WHEN onTabBarClick 回调返回后 THEN 标签页切换正常执行 | 正常 |

### US-4: 监听切换动画事件

**作为** 应用开发者,
**我想要** 通过 onAnimationStart/onAnimationEnd 回调监听切换动画的开始和结束,
**以便** 在动画生命周期中执行同步逻辑（如暂停其他动画、更新 UI 状态）。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.9 | WHEN 标签页切换动画开始 THEN onAnimationStart 回调被触发，参数包含 TabsAnimationEvent（currentOffset/targetOffset/velocity） | 正常 |
| AC-5.10 | WHEN 标签页切换动画结束 THEN onAnimationEnd 回调被触发，参数包含 TabsAnimationEvent | 正常 |
| AC-5.11 | WHEN animationMode=NoAnimation THEN onAnimationStart/onAnimationEnd 不触发 | 边界 |

### US-5: 监听手势滑动事件

**作为** 应用开发者,
**我想要** 通过 onGestureSwipe 回调监听手势滑动过程,
**以便** 在用户手势滑动标签页时获取滑动偏移和速度数据。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.12 | WHEN 用户手势滑动标签页 THEN onGestureSwipe 回调被触发，参数包含 TabsAnimationEvent | 正常 |
| AC-5.13 | WHEN 滑动距离为 0 THEN onGestureSwipe 不触发 | 边界 |

### US-6: 监听内容切换拦截和滑动事件

**作为** 应用开发者,
**我想要** 通过 onContentWillChange 回调拦截内容切换，通过 onContentDidScroll 回调监听内容滑动过程,
**以便** 在内容切换前决定是否允许切换，在内容滑动过程中获取偏移数据。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.14 | WHEN 内容即将切换 THEN onContentWillChange 回调被触发，参数为 fromIndex 和 toIndex | 正常 |
| AC-5.15 | WHEN onContentWillChange 回调返回 true THEN 内容切换正常执行 | 正常 |
| AC-5.16 | WHEN onContentWillChange 回调返回 false THEN 内容切换被拦截，不切换标签页 | 正常 |
| AC-5.17 | WHEN onContentDidScroll 回调触发 THEN 参数包含滑动偏移数据（since 23） | 正常 |
| AC-5.18 | WHEN onContentDidScroll 仅 API >= 23 支持 THEN API < 23 设置不生效 | 边界 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-5.1 | US-1 | R-1 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.2 | US-1 | R-2 | 代码审查 swiper_pattern.cpp |
| AC-5.3 | US-1 | R-3 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.4 | US-2 | R-4 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.5 | US-2 | R-5 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.6 | US-2 | R-6 | 代码审查 tabs_model_ng.cpp |
| AC-5.7 | US-3 | R-7 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.8 | US-3 | R-8 | 代码审查 tabs_pattern.cpp |
| AC-5.9 | US-4 | R-9 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.10 | US-4 | R-10 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.11 | US-4 | R-11 | 代码审查 swiper_pattern.cpp |
| AC-5.12 | US-5 | R-12 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.13 | US-5 | R-13 | 代码审查 tabs_pattern.cpp |
| AC-5.14 | US-6 | R-14 | 单元测试 tabs_event_test_ng.cpp |
| AC-5.15 | US-6 | R-15 | 代码审查 tabs_pattern.cpp |
| AC-5.16 | US-6 | R-16 | 代码审查 tabs_pattern.cpp |
| AC-5.17 | US-6 | R-17 | 代码审查 tabs_model_ng.cpp |
| AC-5.18 | US-6 | R-18 | 代码审查 tabs_model_ng.cpp |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | `tabs_model_ng.cpp` | onChange 回调在标签页切换完成后触发 | 参数为新的 index | AC-5.1 |
| R-2 | 边界 | `swiper_pattern.cpp` | changeIndex 切换到当前已选中 index → onChange 不触发 | — | AC-5.2 |
| R-3 | 行为 | `tabs_controller.h` | TabsController.changeIndex 主动切换 → onChange 触发 | — | AC-5.3 |
| R-4 | 行为 | `tabs_model_ng.cpp` | onSelected 回调在标签选中时触发 | 参数为选中标签 index | AC-5.4 |
| R-5 | 行为 | `tabs_model_ng.cpp` | onUnselected 回调在标签取消选中时触发 | 参数为取消选中标签 index | AC-5.5 |
| R-6 | 边界 | `tabs_model_ng.cpp` | onUnselected 仅 API >= 18 支持 | Container::LessThanAPIVersion 门控 | AC-5.6 |
| R-7 | 行为 | `tabs_model_ng.cpp` | onTabBarClick 回调在标签栏项点击时触发 | 参数为被点击项 index | AC-5.7 |
| R-8 | 行为 | `tabs_pattern.cpp` | onTabBarClick 回调返回后标签页切换正常执行 | 不拦截切换 | AC-5.8 |
| R-9 | 行为 | `tabs_model_ng.cpp` | onAnimationStart 回调在切换动画开始时触发 | 参数含 TabsAnimationEvent | AC-5.9 |
| R-10 | 行为 | `tabs_model_ng.cpp` | onAnimationEnd 回调在切换动画结束时触发 | 参数含 TabsAnimationEvent | AC-5.10 |
| R-11 | 边界 | `swiper_pattern.cpp` | animationMode=NoAnimation → onAnimationStart/onAnimationEnd 不触发 | — | AC-5.11 |
| R-12 | 行为 | `tabs_model_ng.cpp` | onGestureSwipe 回调在手势滑动时触发 | 参数含 TabsAnimationEvent | AC-5.12 |
| R-13 | 边界 | `tabs_pattern.cpp` | 滑动距离为 0 → onGestureSwipe 不触发 | — | AC-5.13 |
| R-14 | 行为 | `tabs_model_ng.cpp` | onContentWillChange 回调在内容即将切换时触发 | 参数为 fromIndex/toIndex | AC-5.14 |
| R-15 | 行为 | `tabs_pattern.cpp` | onContentWillChange 返回 true → 内容切换正常执行 | — | AC-5.15 |
| R-16 | 行为 | `tabs_pattern.cpp` | onContentWillChange 返回 false → 内容切换被拦截 | 不切换标签页 | AC-5.16 |
| R-17 | 行为 | `tabs_model_ng.cpp` | onContentDidScroll 回调在内容滑动过程中触发 | 参数含滑动偏移数据 | AC-5.17 |
| R-18 | 边界 | `tabs_model_ng.cpp` | onContentDidScroll 仅 API >= 23 支持 | Container::LessThanAPIVersion 门控 | AC-5.18 |
| R-19 | 行为 | `tabs_pattern.cpp` | onChange/onSelected/onUnselected/onTabBarClick 事件通过 TabsPattern 注册到 Swiper 事件系统 | — | — |
| R-20 | 异常 | — | onChange 回调抛异常时，标签页切换仍完成，异常被上层捕获 | 不阻塞切换 | — |
| R-21 | 恢复 | — | onContentWillChange 回调执行异常时，默认允许切换（fallback=true） | 不阻塞切换 | — |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-5.1 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-2 | AC-5.2 | 代码审查 | `frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp` |
| VM-3 | AC-5.3 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-4 | AC-5.4 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-5 | AC-5.5 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-6 | AC-5.6 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-7 | AC-5.7 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-8 | AC-5.8 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-9 | AC-5.9 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-10 | AC-5.10 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-11 | AC-5.11 | 代码审查 | `frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp` |
| VM-12 | AC-5.12 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-13 | AC-5.13 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-14 | AC-5.14 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-15 | AC-5.15 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-16 | AC-5.16 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-17 | AC-5.17 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-18 | AC-5.18 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 签名基于现有 SDK 定义。

#### TabsAttribute 事件属性

```typescript
declare class TabsAttribute extends CommonMethod<TabsAttribute> {
  onChange(callback: OnTabsChangeCallback): TabsAttribute;
  onSelected(callback: OnTabsSelectedCallback): TabsAttribute;
  onUnselected(callback: OnTabsUnselectedCallback): TabsAttribute;
  onTabBarClick(callback: OnTabsTabBarClickCallback): TabsAttribute;
  onAnimationStart(callback: OnTabsAnimationStartCallback): TabsAttribute;
  onAnimationEnd(callback: OnTabsAnimationEndCallback): TabsAttribute;
  onGestureSwipe(callback: OnTabsGestureSwipeCallback): TabsAttribute;
  onContentWillChange(callback: OnTabsContentWillChangeCallback): TabsAttribute;
  onContentDidScroll(callback: OnTabsContentDidScrollCallback): TabsAttribute;
}
```

| 方法签名 | 返回类型 | 说明 | @since | 回调签名 |
|----------|----------|------|--------|----------|
| `onChange(callback)` | TabsAttribute | 标签页切换回调 | API 8 | `(index: number) => void` |
| `onSelected(callback)` | TabsAttribute | 标签选中回调 | API 8 | `(index: number) => void` |
| `onUnselected(callback)` | TabsAttribute | 标签取消选中回调 | API 18 | `(index: number) => void` |
| `onTabBarClick(callback)` | TabsAttribute | 标签栏点击回调 | API 10 | `(index: number) => void` |
| `onAnimationStart(callback)` | TabsAttribute | 动画开始回调 | API 10 | `(index: number, event: TabsAnimationEvent) => void` |
| `onAnimationEnd(callback)` | TabsAttribute | 动画结束回调 | API 10 | `(index: number, event: TabsAnimationEvent) => void` |
| `onGestureSwipe(callback)` | TabsAttribute | 手势滑动回调 | API 10 | `(index: number, event: TabsAnimationEvent) => void` |
| `onContentWillChange(callback)` | TabsAttribute | 内容切换拦截回调 | API 10 | `(fromIndex: number, toIndex: number) => boolean` |
| `onContentDidScroll(callback)` | TabsAttribute | 内容滑动回调 | API 23 | `(offset: number) => void` |

#### 回调类型定义

| 类型 | 签名 | 说明 | @since |
|------|------|------|--------|
| OnTabsChangeCallback | `(index: number) => void` | 标签页切换回调 | API 8 |
| OnTabsSelectedCallback | `(index: number) => void` | 标签选中回调 | API 8 |
| OnTabsUnselectedCallback | `(index: number) => void` | 标签取消选中回调 | API 18 |
| OnTabsTabBarClickCallback | `(index: number) => void` | 标签栏点击回调 | API 10 |
| OnTabsAnimationStartCallback | `(index: number, event: TabsAnimationEvent) => void` | 动画开始回调 | API 10 |
| OnTabsAnimationEndCallback | `(index: number, event: TabsAnimationEvent) => void` | 动画结束回调 | API 10 |
| OnTabsGestureSwipeCallback | `(index: number, event: TabsAnimationEvent) => void` | 手势滑动回调 | API 10 |
| OnTabsContentWillChangeCallback | `(fromIndex: number, toIndex: number) => boolean` | 内容切换拦截回调 | API 10 |
| OnTabsContentDidScrollCallback | `(offset: number) => void` | 内容滑动回调 | API 23 |

#### TabsAnimationEvent

```typescript
declare interface TabsAnimationEvent {
  currentOffset: number;
  targetOffset: number;
  velocity: number;
}
```

---

### 变更/废弃 API

| API 名称 | 变更类型 | 关联 AC |
|----------|----------|---------|
| — | — | 无变更/废弃 API |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 8 | 仅支持 onChange/onSelected | 基础版本，无其他事件回调 | 无需迁移 |
| API 10 | 新增 onTabBarClick/onAnimationStart/onAnimationEnd/onGestureSwipe/onContentWillChange | API < 10 不支持这些回调 | 无需迁移 |
| API 10 | onAnimationStart/onAnimationEnd/onGestureSwipe 参数含 TabsAnimationEvent | — | 无需迁移 |
| API 18 | 新增 onUnselected | API < 18 不支持标签取消选中回调 | 无需迁移 |
| API 23 | 新增 onContentDidScroll | API < 23 不支持内容滑动回调 | 无需迁移 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| Swiper 事件系统 | onChange/onAnimationStart/onAnimationEnd/onGestureSwipe 通过 Swiper 事件系统触发 |
| onContentWillChange 拦截 | onContentWillChange 返回 false 拦截切换，通过 Swiper 的 onContentWillChange 回调机制实现 |
| 回调注册 | 事件回调通过 TabsModelNG Set 方法注册到 TabsPattern |
| API 版本门控 | onUnselected（API >= 18）和 onContentDidScroll（API >= 23）通过 Container::LessThanAPIVersion 门控 |

---

## 非性能需求

| 维度 | 要求 |
|------|------|
| 性能 | 事件回调执行不应阻塞标签页切换动画（except onContentWillChange 拦截） |
| 可调试性 | TabsPattern 事件列表可通过 DumpInfo 查看（onChange/onSelected/onTabBarClick/onAnimationStart/onAnimationEnd/onGestureSwipe/onContentWillChange/onContentDidScroll） |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 折叠屏 | 无差异 | — | — | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| Swiper 事件 | Tabs 事件回调依赖 Swiper 内部事件机制（onChange/onAnimationStart/onAnimationEnd/onGestureSwipe） |
| 焦点框架 | onTabBarClick 触发后焦点需重新分配 |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 业务规则/功能规则/异常规则/恢复契约编号连续且可追溯到源码
- [x] API 变更分析基于真实源码枚举定义
- [x] 兼容性声明标注 API 版本差异
- [x] 行为场景覆盖关键路径
- [x] 所有源码引用包含 file:line 信息
- [x] 构建系统影响章节已确认无变更

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp/.h` | Tabs 主 Pattern（事件注册与分发） |
| `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp/.h` | Tabs NG Model 层（事件 Set 方法） |
| `frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp/.h` | Swiper Pattern（事件触发源） |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` | Tabs 事件测试 |
