# 特性规格

> Func-05-03-09-Feat-04 Tabs/TabContent 动画与自定义过渡：固化 customContentTransition、TabContentAnimatedTransition（timeout/transition）、TabContentTransitionProxy（from/to/finishTransition）、animationMode（CONTENT_FIRST/ACTION_FIRST/NO_ANIMATION/CONTENT_FIRST_WITH_JUMP/ACTION_FIRST_WITH_JUMP）、animationCurve、pageFlipMode、TabsAnimationEvent（currentOffset/targetOffset/velocity）的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Tabs/TabContent 动画与自定义过渡 (Tabs/TabContent Animation & Custom Transition) |
| 特性编号 | Func-05-03-09-Feat-04 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 10+ 支持动画模式，API 12+ 支持自定义过渡 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 高 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。覆盖 customContentTransition 自定义过渡机制（TabContentAnimatedTransition/TabContentTransitionProxy）、animationMode 五种动画模式（CONTENT_FIRST/ACTION_FIRST/NO_ANIMATION/CONTENT_FIRST_WITH_JUMP/ACTION_FIRST_WITH_JUMP）、animationCurve/pageFlipMode 动画参数、TabsAnimationEvent 动画事件数据（currentOffset/targetOffset/velocity）。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/09-tabs-tab-content/design.md` | Baselined |
| SDK API | `docs/sdk/ArkUI_SDK_API_Knowledge_Base.md` | — |
| SDK 组件 | `docs/sdk/Component_API_Knowledge_Base_CN.md` | — |

---

## 用户故事

### US-1: 配置切换动画模式

**作为** 应用开发者,
**我想要** 通过 animationMode 配置标签页切换动画模式（内容优先/标签栏优先/无动画/带跳跃的内容优先/带跳跃的标签栏优先）,
**以便** 精细控制切换动画时内容区和标签栏指示器的动画顺序。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `.animationMode(AnimationMode.ContentFirst)` THEN SwiperPaintProperty 的 TabAnimateMode 被设置为 CONTENT_FIRST，内容区先切换 | 正常 |
| AC-4.2 | WHEN 调用 `.animationMode(AnimationMode.ActionFirst)` THEN SwiperPaintProperty 的 TabAnimateMode 被设置为 ACTION_FIRST，标签栏指示器先移动 | 正常 |
| AC-4.3 | WHEN 调用 `.animationMode(AnimationMode.NoAnimation)` THEN SwiperPaintProperty 的 TabAnimateMode 被设置为 NO_ANIMATION，无动画直接切换 | 正常 |
| AC-4.4 | WHEN 调用 `.animationMode(AnimationMode.ContentFirstWithJump)` THEN 内容区先切换+跳动画 | 正常 |
| AC-4.5 | WHEN 调用 `.animationMode(AnimationMode.ActionFirstWithJump)` THEN 标签栏指示器先移动+跳动画 | 正常 |
| AC-4.6 | WHEN 未设置 animationMode THEN 默认动画模式为同步切换（无 AnimationMode 约束） | 边界 |

### US-2: 配置自定义过渡动画

**作为** 应用开发者,
**我想要** 通过 customContentTransition 注册自定义过渡动画，使用 TabContentAnimatedTransition 定义过渡参数和回调，使用 TabContentTransitionProxy 控制过渡生命周期,
**以便** 实现标签页切换时的自定义动画效果（如淡入淡出、缩放等）。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.7 | WHEN 调用 `.customContentTransition(handler)` THEN SetIsCustomAnimation(true) 被设置，自定义过渡动画被启用 | 正常 |
| AC-4.8 | WHEN handler 返回 TabContentAnimatedTransition THEN transition 回调被注册，timeout 超时时间被设置 | 正常 |
| AC-4.9 | WHEN TabContentAnimatedTransition.timeout 指定超时时间 THEN 过渡动画在超时后强制结束 | 边界 |
| AC-4.10 | WHEN TabContentTransitionProxy.finishTransition() 被调用 THEN 过渡动画正常结束，切换完成 | 正常 |
| AC-4.11 | WHEN TabContentTransitionProxy.from 和 .to 被访问 THEN 返回过渡起始和目标 TabContent 索引 | 正常 |
| AC-4.12 | WHEN 自定义过渡动画超时 THEN 自动结束过渡并完成切换 | 边界 |
| AC-4.13 | WHEN 自定义过渡动画不调用 finishTransition THEN 超时后自动完成 | 异常 |

### US-3: 配置动画曲线和翻页模式

**作为** 应用开发者,
**我想要** 通过 animationCurve 和 pageFlipMode 配置切换动画曲线和翻页模式,
**以便** 控制标签页切换动画的缓动曲线和翻页行为。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.14 | WHEN 调用 `.animationCurve(Curve.EaseInOut)` THEN SwiperPattern 的 animationCurve 被设置为 EaseInOut | 正常 |
| AC-4.15 | WHEN 调用 `.animationCurve(ICurve)` THEN SwiperPattern 的 animationCurve 支持自定义曲线 | 正常 |
| AC-4.16 | WHEN 调用 `.pageFlipMode(PageFlipMode.Continue)` THEN SwiperPaintProperty 的 pageFlipMode 被设置 | 正常 |

### US-4: 获取动画事件数据

**作为** 应用开发者,
**我想要** 通过 TabsAnimationEvent 获取标签页切换动画过程中的偏移量和速度数据,
**以便** 在动画回调中获取细粒度的动画状态信息。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.17 | WHEN onAnimationStart 回调触发 THEN TabsAnimationEvent 包含 currentOffset/targetOffset/velocity 数据 | 正常 |
| AC-4.18 | WHEN onAnimationEnd 回调触发 THEN TabsAnimationEvent 包含当前偏移量数据 | 正常 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-4.1 | US-1 | R-1 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-4.2 | US-1 | R-2 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-4.3 | US-1 | R-3 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-4.4 | US-1 | R-4 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-4.5 | US-1 | R-5 | 单元测试 tabs_attr_test_two_ng.cpp |
| AC-4.6 | US-1 | R-6 | 代码审查 swiper_pattern.cpp |
| AC-4.7 | US-2 | R-7 | 单元测试 tabs_event_test_ng.cpp |
| AC-4.8 | US-2 | R-8 | 代码审查 tabs_model_ng.cpp |
| AC-4.9 | US-2 | R-9 | 代码审查 tabs_pattern.cpp |
| AC-4.10 | US-2 | R-10 | 代码审查 tabs_pattern.cpp |
| AC-4.11 | US-2 | R-11 | 代码审查 tabs_pattern.cpp |
| AC-4.12 | US-2 | R-9 | 代码审查 tabs_pattern.cpp |
| AC-4.13 | US-2 | R-12 | 代码审查 tabs_pattern.cpp |
| AC-4.14 | US-3 | R-13 | 代码审查 tabs_model_ng.cpp |
| AC-4.15 | US-3 | R-14 | 代码审查 tabs_model_ng.cpp |
| AC-4.16 | US-3 | R-15 | 代码审查 tabs_model_ng.cpp |
| AC-4.17 | US-4 | R-16 | 单元测试 tabs_event_test_ng.cpp |
| AC-4.18 | US-4 | R-17 | 单元测试 tabs_event_test_ng.cpp |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | `tabs_model_ng.cpp` | animationMode(ContentFirst) → SwiperPaintProperty TabAnimateMode=CONTENT_FIRST | — | AC-4.1 |
| R-2 | 行为 | `tabs_model_ng.cpp` | animationMode(ActionFirst) → SwiperPaintProperty TabAnimateMode=ACTION_FIRST | — | AC-4.2 |
| R-3 | 行为 | `tabs_model_ng.cpp` | animationMode(NoAnimation) → SwiperPaintProperty TabAnimateMode=NO_ANIMATION | — | AC-4.3 |
| R-4 | 行为 | `tabs_model_ng.cpp` | animationMode(ContentFirstWithJump) → SwiperPaintProperty TabAnimateMode=CONTENT_FIRST_WITH_JUMP | — | AC-4.4 |
| R-5 | 行为 | `tabs_model_ng.cpp` | animationMode(ActionFirstWithJump) → SwiperPaintProperty TabAnimateMode=ACTION_FIRST_WITH_JUMP | — | AC-4.5 |
| R-6 | 行为 | `swiper_pattern.cpp` | 未设置 animationMode 时默认同步切换 | — | AC-4.6 |
| R-7 | 行为 | `tabs_model_ng.cpp` | customContentTransition(handler) → SetIsCustomAnimation(true) | — | AC-4.7 |
| R-8 | 行为 | `tabs_model_ng.cpp` | handler 返回 TabContentAnimatedTransition → 注册 transition 回调和 timeout | timeout 默认值参考 Swiper 配置 | AC-4.8 |
| R-9 | 边界 | `tabs_pattern.cpp` | TabContentAnimatedTransition.timeout 指定超时时间 → 过渡动画超时后强制结束 | 超时单位为 ms | AC-4.9, AC-4.12 |
| R-10 | 行为 | `tabs_pattern.cpp` | TabContentTransitionProxy.finishTransition() → 过渡动画正常结束 | 切换完成后触发 onChange | AC-4.10 |
| R-11 | 行为 | `tabs_pattern.cpp` | TabContentTransitionProxy.from/.to → 返回过渡起始和目标索引 | 从 Swiper 联动获取 | AC-4.11 |
| R-12 | 异常 | `tabs_pattern.cpp` | 自定义过渡不调用 finishTransition → 超时后自动完成 | 不阻塞后续切换 | AC-4.13 |
| R-13 | 行为 | `tabs_model_ng.cpp` | animationCurve 透传到 SwiperPattern 的 animationCurve | 支持 Curve/ICurve | AC-4.14 |
| R-14 | 行为 | `tabs_model_ng.cpp` | animationCurve(ICurve) 支持自定义曲线 | ICurve 类型 | AC-4.15 |
| R-15 | 行为 | `tabs_model_ng.cpp` | pageFlipMode 透传到 SwiperPaintProperty | — | AC-4.16 |
| R-16 | 行为 | `tabs_model_ng.cpp` | onAnimationStart 回调触发 → TabsAnimationEvent 包含 currentOffset/targetOffset/velocity | 数据从 Swiper 动画状态获取 | AC-4.17 |
| R-17 | 行为 | `tabs_model_ng.cpp` | onAnimationEnd 回调触发 → TabsAnimationEvent 包含当前偏移量数据 | — | AC-4.18 |
| R-18 | 行为 | `tabs_pattern.cpp` | animationMode 透传到 Swiper PaintProperty 在 OnModifyDone 中同步设置 | — | — |
| R-19 | 行为 | `swiper_pattern.cpp` | CONTENT_FIRST 模式下内容区先完成动画，标签栏指示器后跟随 | — | — |
| R-20 | 行为 | `swiper_pattern.cpp` | ACTION_FIRST 模式下标签栏指示器先移动，内容区后切换 | — | — |
| R-21 | 恢复 | — | 自定义过渡动画中断（如快速连续切换）时，上一个过渡被强制结束 | 不崩溃 | — |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-4.1 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-2 | AC-4.2 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-3 | AC-4.3 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-4 | AC-4.4 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-5 | AC-4.5 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` |
| VM-6 | AC-4.6 | 代码审查 | `frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp` |
| VM-7 | AC-4.7 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-8 | AC-4.8 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-9 | AC-4.9 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-10 | AC-4.10 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-11 | AC-4.11 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-12 | AC-4.12 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-13 | AC-4.13 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` |
| VM-14 | AC-4.14 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-15 | AC-4.15 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-16 | AC-4.16 | 代码审查 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` |
| VM-17 | AC-4.17 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |
| VM-18 | AC-4.18 | 单元测试 | `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 签名基于现有 SDK 定义。

#### TabsAttribute 动画属性

```typescript
declare class TabsAttribute extends CommonMethod<TabsAttribute> {
  animationMode(value: AnimationMode): TabsAttribute;
  animationCurve(value: Curve | ICurve): TabsAttribute;
  pageFlipMode(value: PageFlipMode): TabsAttribute;
  customContentTransition(handler: (from: number, to: number) => TabContentAnimatedTransition): TabsAttribute;
}
```

| 方法签名 | 返回类型 | 说明 | @since | 存储位置 |
|----------|----------|------|--------|----------|
| `animationMode(value: AnimationMode)` | TabsAttribute | 动画模式 | API 10 | SwiperPaintProperty::TabAnimateMode |
| `animationCurve(value: Curve \| ICurve)` | TabsAttribute | 动画曲线 | API 8 | SwiperPattern::animationCurve |
| `pageFlipMode(value: PageFlipMode)` | TabsAttribute | 翻页模式 | API 11 | SwiperPaintProperty::pageFlipMode |
| `customContentTransition(handler)` | TabsAttribute | 自定义过渡动画 | API 12 | TabsPattern::isCustomAnimation_ |

#### TabContentAnimatedTransition

```typescript
declare class TabContentAnimatedTransition {
  timeout: number;
  transition: (proxy: TabContentTransitionProxy) => void;
}
```

| 属性 | 类型 | 说明 | @since |
|------|------|------|--------|
| timeout | number | 过渡动画超时时间(ms) | API 12 |
| transition | (proxy: TabContentTransitionProxy) => void | 过渡动画回调 | API 12 |

#### TabContentTransitionProxy

```typescript
declare class TabContentTransitionProxy {
  from: number;
  to: number;
  finishTransition(): void;
}
```

| 属性/方法 | 类型 | 说明 | @since |
|-----------|------|------|--------|
| from | number | 过渡起始 TabContent 索引 | API 12 |
| to | number | 过渡目标 TabContent 索引 | API 12 |
| finishTransition() | void | 结束过渡动画 | API 12 |

#### TabsAnimationEvent

```typescript
declare interface TabsAnimationEvent {
  currentOffset: number;
  targetOffset: number;
  velocity: number;
}
```

| 属性 | 类型 | 说明 | @since |
|------|------|------|--------|
| currentOffset | number | 当前偏移量 | API 10 |
| targetOffset | number | 目标偏移量 | API 10 |
| velocity | number | 滑动速度 | API 10 |

#### AnimationMode 枚举映射

| ArkTS 枚举 | C++ 枚举 | 文件 |
|------------|----------|------|
| AnimationMode.ContentFirst | TabAnimateMode::CONTENT_FIRST | `constants.h:655` |
| AnimationMode.ActionFirst | TabAnimateMode::ACTION_FIRST | `constants.h:656` |
| AnimationMode.NoAnimation | TabAnimateMode::NO_ANIMATION | `constants.h:657` |
| AnimationMode.ContentFirstWithJump | TabAnimateMode::CONTENT_FIRST_WITH_JUMP | `constants.h:658` |
| AnimationMode.ActionFirstWithJump | TabAnimateMode::ACTION_FIRST_WITH_JUMP | `constants.h:659` |

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
| API 8 | 仅支持 animationDuration/animationCurve | 基础版本，无 animationMode/customContentTransition | 无需迁移 |
| API 10 | 新增 animationMode（AnimationMode 枚举五种模式） | API < 10 不支持 animationMode | 无需迁移（新属性默认不设置） |
| API 10 | TabsAnimationEvent 提供 currentOffset/targetOffset/velocity | API < 10 onAnimationStart/onAnimationEnd 仅提供 index | 无需迁移 |
| API 11 | 新增 pageFlipMode | API < 11 不支持 pageFlipMode | 无需迁移 |
| API 12 | 新增 customContentTransition（TabContentAnimatedTransition/TabContentTransitionProxy） | API < 12 不支持自定义过渡 | 无需迁移 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| Swiper 内嵌 | animationMode/animationCurve/pageFlipMode 通过 Swiper PaintProperty/LayoutProperty 透传 |
| 自定义过渡 | customContentTransition 通过 SetIsCustomAnimation(true) 启用，TabsPattern 持有 isCustomAnimation_ 状态 |
| 过渡生命周期 | TabContentTransitionProxy 管理 from/to/finishTransition，超时自动结束 |
| 动画同步 | OnModifyDone 中同步设置 Swiper 的 animationMode/animationCurve/pageFlipMode |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | 自定义过渡动画应在 timeout 内完成，避免阻塞后续切换 |
| 可调试性 | TabsPattern 提供 DumpInfo（animationMode/animationCurve/isCustomAnimation/customAnimationTimeout）用于 Inspector 诊断 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 折叠屏 | 折叠/展开时动画模式不变 | — | — | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| Swiper | animationMode/animationCurve/pageFlipMode/customContentTransition 均依赖 Swiper 动画引擎 |
| onContentWillChange | 自定义过渡前 onContentWillChange 回调决定是否允许切换 |

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
| `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp/.h` | Tabs 主 Pattern（自定义过渡/动画模式） |
| `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp/.h` | Tabs NG Model 层 |
| `frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp/.h` | Swiper Pattern（动画引擎） |
| `frameworks/core/components/common/layout/constants.h` | TabAnimateMode 枚举定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/tabs/tabs_attr_test_two_ng.cpp` | Tabs 属性测试 |
| `test/unittest/core/pattern/tabs/tabs_event_test_ng.cpp` | Tabs 事件测试 |
