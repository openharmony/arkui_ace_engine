# 特性规格

> Func-05-03-09-Feat-06 Tabs/TabContent 缓存与滚动控制：固化 cachedMaxCount（since 19，TabsCacheMode CACHE_BOTH_SIDE/CACHE_LATEST_SWITCHED）、nestedScroll（since 24，TabsNestedScrollMode SELF_ONLY/SELF_FIRST）、TabsController.preloadItems（since 12）、TabsController.setTabBarTranslate（since 13）、TabsController.setTabBarOpacity（since 13）、TabsCacheMode、TabsNestedScrollMode、TabContent.onWillShow、TabContent.onWillHide（since 12）的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Tabs/TabContent 缓存与滚动控制 (Tabs/TabContent Cache & Scroll Control) |
| 特性编号 | Func-05-03-09-Feat-06 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P1 |
| 目标版本 | API 12+ 支持预加载/可见性回调，API 13+ 支持标签栏动画控制，API 19+ 支持缓存配置，API 24+ 支持嵌套滚动 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 中 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。覆盖 cachedMaxCount/TabsCacheMode 缓存策略、nestedScroll/TabsNestedScrollMode 嵌套滚动、TabsController.preloadItems/setTabBarTranslate/setTabBarOpacity 控制器扩展、TabContent.onWillShow/onWillHide 可见性回调。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/09-tabs-tab-content/design.md` | Baselined |
| SDK API | `docs/sdk/ArkUI_SDK_API_Knowledge_Base.md` | — |
| SDK 组件 | `docs/sdk/Component_API_Knowledge_Base_CN.md` | — |

---

## 用户故事

### US-1: 配置标签页缓存策略

**作为** 应用开发者,
**我想要** 通过 cachedMaxCount 和 TabsCacheMode 配置标签页缓存策略（两侧缓存或最近切换缓存）,
**以便** 在标签页切换时减少内容区重新渲染开销，提升用户体验。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 调用 `.cachedMaxCount(count: number)` THEN TabsLayoutProperty::propCachedMaxCount_ 被设置 | 正常 |
| AC-6.2 | WHEN 设置 TabsCacheMode.CACHE_BOTH_SIDE THEN 缓存当前页两侧相邻页 | 正常 |
| AC-6.3 | WHEN 设置 TabsCacheMode.CACHE_LATEST_SWITCHED THEN 仅缓存最近切换过的页面 | 正常 |
| AC-6.4 | WHEN cachedMaxCount 为 0 THEN 不缓存任何 TabContent | 边界 |
| AC-6.5 | WHEN cachedMaxCount 仅 API >= 19 支持 THEN API < 19 设置不生效 | 边界 |

### US-2: 配置嵌套滚动模式

**作为** 应用开发者,
**我想要** 通过 nestedScroll 和 TabsNestedScrollMode 配置 Tabs 嵌套滚动行为（仅自身滚动或自身优先）,
**以便** 在 Tabs 嵌套在其他滚动容器中时精细控制滚动联动。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.6 | WHEN 调用 `.nestedScroll(value: TabsNestedScrollMode)` THEN TabsLayoutProperty 的嵌套滚动模式被设置 | 正常 |
| AC-6.7 | WHEN 设置 TabsNestedScrollMode.SELF_ONLY THEN Tabs 仅自身滚动，不与父滚动容器联动 | 正常 |
| AC-6.8 | WHEN 设置 TabsNestedScrollMode.SELF_FIRST THEN Tabs 自身先滚动，滚动到边缘后传递给父容器 | 正常 |
| AC-6.9 | WHEN nestedScroll 仅 API >= 24 支持 THEN API < 24 设置不生效 | 边界 |

### US-3: 预加载标签页

**作为** 应用开发者,
**我想要** 通过 TabsController.preloadItems 预加载指定索引的标签页内容,
**以便** 在用户切换前提前创建和渲染标签页内容，减少切换时的等待时间。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.10 | WHEN 调用 `tabsController.preloadItems(indexList: number[])` THEN 指定索引的 TabContent 被预加载 | 正常 |
| AC-6.11 | WHEN preloadItems 传入超出范围的索引 THEN 超出范围的索引被忽略 | 异常 |
| AC-6.12 | WHEN preloadItems 仅 API >= 12 支持 THEN API < 12 调用静默失败 | 边界 |

### US-4: 控制标签栏动画

**作为** 应用开发者,
**我想要** 通过 TabsController.setTabBarTranslate/setTabBarOpacity 控制标签栏的位移和透明度动画,
**以便** 在特定场景下动画控制标签栏的显示/隐藏效果。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.13 | WHEN 调用 `tabsController.setTabBarTranslate(offset: number)` THEN 标签栏水平位移被设置 | 正常 |
| AC-6.14 | WHEN 调用 `tabsController.setTabBarOpacity(opacity: number)` THEN 标签栏透明度被设置 | 正常 |
| AC-6.15 | WHEN setTabBarTranslate/setTabBarOpacity 仅 API >= 13 支持 THEN API < 13 调用静默失败 | 边界 |

### US-5: 监听 TabContent 可见性

**作为** 应用开发者,
**我想要** 通过 TabContent.onWillShow/onWillHide 监听内容区即将显示/隐藏的状态,
**以便** 在 TabContent 可见性变化前执行前置逻辑（如数据加载、状态恢复）。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.16 | WHEN TabContent 即将显示 THEN onWillShow 回调被触发 | 正常 |
| AC-6.17 | WHEN TabContent 即将隐藏 THEN onWillHide 回调被触发 | 正常 |
| AC-6.18 | WHEN onWillShow/onWillHide 仅 API >= 12 支持 THEN API < 12 设置不生效 | 边界 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-6.1 | US-1 | R-1 | 代码审查 tabs_model_ng.cpp |
| AC-6.2 | US-1 | R-2 | 代码审查 tabs_pattern.cpp |
| AC-6.3 | US-1 | R-3 | 代码审查 tabs_pattern.cpp |
| AC-6.4 | US-1 | R-4 | 代码审查 tabs_layout_property.h |
| AC-6.5 | US-1 | R-5 | 代码审查 tabs_model_ng.cpp |
| AC-6.6 | US-2 | R-6 | 代码审查 tabs_model_ng.cpp |
| AC-6.7 | US-2 | R-7 | 代码审查 tabs_pattern.cpp |
| AC-6.8 | US-2 | R-8 | 代码审查 tabs_pattern.cpp |
| AC-6.9 | US-2 | R-9 | 代码审查 tabs_model_ng.cpp |
| AC-6.10 | US-3 | R-10 | 单元测试 tabs_test_ng.cpp |
| AC-6.11 | US-3 | R-11 | 代码审查 tabs_controller.h |
| AC-6.12 | US-3 | R-12 | 代码审查 tabs_controller.h |
| AC-6.13 | US-4 | R-13 | 单元测试 tabs_test_ng.cpp |
| AC-6.14 | US-4 | R-14 | 单元测试 tabs_test_ng.cpp |
| AC-6.15 | US-4 | R-15 | 代码审查 tabs_controller.h |
| AC-6.16 | US-5 | R-16 | 单元测试 tabs_event_test_ng.cpp |
| AC-6.17 | US-5 | R-17 | 单元测试 tabs_event_test_ng.cpp |
| AC-6.18 | US-5 | R-18 | 代码审查 js_tabs.cpp |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | `tabs_model_ng.cpp` | cachedMaxCount 设置写入 TabsLayoutProperty::propCachedMaxCount_ | — | AC-6.1 |
| R-2 | 行为 | `tabs_pattern.cpp` | TabsCacheMode.CACHE_BOTH_SIDE → 缓存当前页两侧相邻页 | 缓存数量受 cachedMaxCount 限制 | AC-6.2 |
| R-3 | 行为 | `tabs_pattern.cpp` | TabsCacheMode.CACHE_LATEST_SWITCHED → 仅缓存最近切换过的页面 | 减少两侧同时缓存内存开销 | AC-6.3 |
| R-4 | 边界 | `tabs_layout_property.h` | cachedMaxCount 为 0 → 不缓存任何 TabContent | — | AC-6.4 |
| R-5 | 边界 | `tabs_model_ng.cpp` | cachedMaxCount 仅 API >= 19 支持 | Container::LessThanAPIVersion 门控 | AC-6.5 |
| R-6 | 行为 | `tabs_model_ng.cpp` | nestedScroll 设置写入 TabsLayoutProperty 嵌套滚动模式 | — | AC-6.6 |
| R-7 | 行为 | `tabs_pattern.cpp` | TabsNestedScrollMode.SELF_ONLY → Tabs 仅自身滚动 | 不与父滚动容器联动 | AC-6.7 |
| R-8 | 行为 | `tabs_pattern.cpp` | TabsNestedScrollMode.SELF_FIRST → Tabs 自身先滚动 | 滚动到边缘后传递给父容器 | AC-6.8 |
| R-9 | 边界 | `tabs_model_ng.cpp` | nestedScroll 仅 API >= 24 支持 | Container::LessThanAPIVersion 门控 | AC-6.9 |
| R-10 | 行为 | `tabs_controller.h` | preloadItems 预加载指定索引的 TabContent | — | AC-6.10 |
| R-11 | 异常 | `tabs_controller.h` | preloadItems 传入超出范围的索引 → 超出范围索引被忽略 | 不崩溃 | AC-6.11 |
| R-12 | 边界 | `tabs_controller.h` | preloadItems 仅 API >= 12 支持 | API < 12 调用静默失败 | AC-6.12 |
| R-13 | 行为 | `tabs_controller.h` | setTabBarTranslate 设置标签栏水平位移 | offset 类型为 number | AC-6.13 |
| R-14 | 行为 | `tabs_controller.h` | setTabBarOpacity 设置标签栏透明度 | opacity 类型为 number，范围 0~1 | AC-6.14 |
| R-15 | 边界 | `tabs_controller.h` | setTabBarTranslate/setTabBarOpacity 仅 API >= 13 支持 | API < 13 调用静默失败 | AC-6.15 |
| R-16 | 行为 | `js_tabs.cpp` | TabContent.onWillShow 回调在内容区即将显示时触发 | — | AC-6.16 |
| R-17 | 行为 | `js_tabs.cpp` | TabContent.onWillHide 回调在内容区即将隐藏时触发 | — | AC-6.17 |
| R-18 | 边界 | `js_tabs.cpp` | onWillShow/onWillHide 仅 API >= 12 支持 | Container::LessThanAPIVersion 门控 | AC-6.18 |
| R-19 | 行为 | `tab_content_pattern.cpp/.h` | TabContentPattern::OnActive/OnInactive 控制可见性 | — | — |
| R-20 | 恢复 | — | TabsController 丢失 TabsPattern 引用时 preloadItems/setTabBarTranslate/setTabBarOpacity 静默失败 | 不崩溃 | — |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-6.1 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-2 | AC-6.2 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-3 | AC-6.3 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-4 | AC-6.4 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_layout_property.h` |
| VM-5 | AC-6.5 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-6 | AC-6.6 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-7 | AC-6.7 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-8 | AC-6.8 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-9 | AC-6.9 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-10 | AC-6.10 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_test_ng.cpp` |
| VM-11 | AC-6.11 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_controller.h` |
| VM-12 | AC-6.12 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_controller.h` |
| VM-13 | AC-6.13 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_test_ng.cpp` |
| VM-14 | AC-6.14 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_test_ng.cpp` |
| VM-15 | AC-6.15 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_controller.h` |
| VM-16 | AC-6.16 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-17 | AC-6.17 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-18 | AC-6.18 | 代码审查 | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 签名基于现有 SDK 定义。

#### TabsAttribute 缓存与滚动属性

```typescript
declare class TabsAttribute extends CommonMethod<TabsAttribute> {
  cachedMaxCount(value: number, mode?: TabsCacheMode): TabsAttribute;
  nestedScroll(value: TabsNestedScrollMode): TabsAttribute;
}
```

| 方法签名 | 返回类型 | 说明 | @since | 存储位置 |
|----------|----------|------|--------|----------|
| `cachedMaxCount(value: number, mode?: TabsCacheMode)` | TabsAttribute | 缓存最大数量和模式 | API 19 | TabsLayoutProperty::propCachedMaxCount_/propCacheMode_ |
| `nestedScroll(value: TabsNestedScrollMode)` | TabsAttribute | 嵌套滚动模式 | API 24 | TabsLayoutProperty |

#### TabsController 扩展方法

```typescript
declare class TabsController {
  preloadItems(indexList: number[]): void;
  setTabBarTranslate(offset: number): void;
  setTabBarOpacity(opacity: number): void;
}
```

| 方法签名 | 返回类型 | 说明 | @since |
|----------|----------|------|--------|
| `preloadItems(indexList: number[])` | void | 预加载指定标签页 | API 12 |
| `setTabBarTranslate(offset: number)` | void | 标签栏水平位移 | API 13 |
| `setTabBarOpacity(opacity: number)` | void | 标签栏透明度 | API 13 |

#### TabContent 可见性回调

```typescript
declare class TabContentAttribute extends CommonMethod<TabContentAttribute> {
  onWillShow(callback: () => void): TabContentAttribute;
  onWillHide(callback: () => void): TabContentAttribute;
}
```

| 方法签名 | 返回类型 | 说明 | @since |
|----------|----------|------|--------|
| `onWillShow(callback: () => void)` | TabContentAttribute | 内容区即将显示回调 | API 12 |
| `onWillHide(callback: () => void)` | TabContentAttribute | 内容区即将隐藏回调 | API 12 |

#### 枚举类型

| 枚举名 | 值 | 说明 | @since |
|--------|-----|------|--------|
| TabsCacheMode | CACHE_BOTH_SIDE, CACHE_LATEST_SWITCHED | 缓存模式枚举 | API 19 |
| TabsNestedScrollMode | SELF_ONLY, SELF_FIRST | 嵌套滚动模式枚举 | API 24 |

#### 枚举映射

| ArkTS 枚举 | C++ 枚举 | 文件 |
|------------|----------|------|
| TabsCacheMode.CACHE_BOTH_SIDE | TabsCacheMode::CACHE_BOTH_SIDE | `tabs_constants.h` |
| TabsCacheMode.CACHE_LATEST_SWITCHED | TabsCacheMode::CACHE_LATEST_SWITCHED | `tabs_constants.h` |
| TabsNestedScrollMode.SELF_ONLY | TabsNestedScrollMode::SELF_ONLY | `tabs_constants.h` |
| TabsNestedScrollMode.SELF_FIRST | TabsNestedScrollMode::SELF_FIRST | `tabs_constants.h` |

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
| API < 12 | 无预加载、无可见性回调 | 基础版本 | 无需迁移 |
| API 12 | 新增 preloadItems/onWillShow/onWillHide | API < 12 不支持这些能力 | 无需迁移 |
| API 13 | 新增 setTabBarTranslate/setTabBarOpacity | API < 13 不支持标签栏动画控制 | 无需迁移 |
| API 19 | 新增 cachedMaxCount/TabsCacheMode | API < 19 不支持缓存配置 | 无需迁移 |
| API 24 | 新增 nestedScroll/TabsNestedScrollMode | API < 24 不支持嵌套滚动配置 | 无需迁移 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| Swiper 缓存 | Tabs 缓存策略通过 Swiper 的 OnActive/OnInactive 机制实现，TabContentPattern 控制可见性 |
| 嵌套滚动 | nestedScroll 模式通过 Swiper 的 NestedScroll 机制透传 |
| 控制器扩展 | TabsControllerNG 继承 SwiperController，preloadItems/setTabBarTranslate/setTabBarOpacity 为 Tabs 独有扩展 |
| API 版本门控 | cachedMaxCount（API >= 19）、nestedScroll（API >= 24）、preloadItems/onWillShow/onWillHide（API >= 12）、setTabBarTranslate/setTabBarOpacity（API >= 13）均通过 Container::LessThanAPIVersion 门控 |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | 缓存策略应在切换动画开始前完成预加载，避免切换等待 |
| 内存 | cachedMaxCount 应合理设置，避免过多 TabContent 同时缓存导致内存开销 |
| 可调试性 | TabsLayoutProperty 提供 DumpInfo（cachedMaxCount/cacheMode/nestedScrollMode）用于 Inspector 诊断 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 折叠屏 | 折叠/展开时嵌套滚动行为不变 | — | — | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| Swiper | 缓存策略和嵌套滚动通过 Swiper 内部机制实现 |
| TabContentPattern | OnActive/OnInactive 控制缓存可见性，onWillShow/onWillHide 在 OnActive/OnInactive 前触发 |

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
| `frameworks/core/components_ng/pattern/tabs/tabs_layout_property.h` | Tabs 布局属性（缓存/嵌套滚动） |
| `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp/.h` | Tabs 主 Pattern（缓存逻辑） |
| `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp/.h` | Tabs NG Model 层 |
| `frameworks/core/components_ng/pattern/tabs/tabs_controller.h` | TabsControllerNG（preloadItems/setTabBarTranslate/setTabBarOpacity） |
| `frameworks/core/components_ng/pattern/tabs/tab_content_pattern.cpp/.h` | TabContent Pattern（onWillShow/onWillHide） |
| `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp/.h` | JS 桥接层 |
| `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs_constants.h` | 枚举定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/tabs/tabs_test_ng.cpp` | Tabs NG 单元测试 |
| `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` | Tabs 事件测试 |
