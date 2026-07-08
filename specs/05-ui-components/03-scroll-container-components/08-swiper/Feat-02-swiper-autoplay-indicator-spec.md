# 特性规格

> Func-05-03-08-Feat-02 自动播放与指示器：固化 Swiper autoPlay/autoPlayOptions/interval、DotIndicator/DigitIndicator/IndicatorComponent、displayArrow/ArrowStyle、indicatorInteractive 等指示器与自动播放行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 自动播放与指示器 (AutoPlay & Indicator) |
| 特性编号 | Func-05-03-08-Feat-02 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 7 起支持（部分属性 @since 12/15/18/19） |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 复杂 |

## 本次变更范围（Delta）

> 无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/03-scroll-container-components/08-swiper/design.md` | Baselined |

---

## 用户故事

### US-1: 配置自动播放

**作为** 应用开发者,
**我想要** 配置 Swiper 自动播放行为（间隔、触摸停止、反向播放）,
**以便** 实现广告轮播、自动翻页等场景。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.autoPlay(value: boolean)` THEN 设置是否自动播放，默认 false，存储在 SwiperPaintProperty SwiperAnimationStyle 组 | 正常 |
| AC-1.2 | WHEN 调用 `.autoPlayInterval(value: number)` THEN 设置自动播放间隔，默认 3000ms，存储在 SwiperPaintProperty | 正常 |
| AC-1.3 | WHEN autoPlay 为 true THEN SwiperPattern 内 Timer 驱动自动翻页，OnModifyDone 中启动定时器 | 正常 |
| AC-1.4 | WHEN 调用 `.autoPlayOptions(value: SwiperAutoPlayOptions)` THEN 设置自动播放选项，含 stopWhenTouch（默认 true）和 reverse（默认 false） | 正常 |
| AC-1.5 | WHEN SwiperAutoPlayOptions.stopWhenTouch 为 true（默认）THEN 触摸时暂停自动播放，触摸结束后恢复 | 正常 |
| AC-1.6 | WHEN SwiperAutoPlayOptions.stopWhenTouch 为 false（@since 18）THEN 触摸时不暂停自动播放 | 正常 |
| AC-1.7 | WHEN SwiperAutoPlayOptions.reverse 为 true THEN 自动播放反向翻页 | 正常 |
| AC-1.8 | WHEN autoPlay/autoPlayInterval/autoPlayOptions 变更 THEN 触发 PROPERTY_UPDATE_RENDER | 正常 |

> autoPlay/autoPlayInterval 存储在 SwiperPaintProperty SwiperAnimationStyle 组：`swiper_paint_property.h:69-70`。Timer 驱动逻辑：`swiper_pattern.cpp` OnModifyDone。

### US-2: 配置圆点指示器

**作为** 应用开发者,
**我想要** 配置 Swiper 圆点指示器（DotIndicator）样式和位置,
**以便** 显示当前页码指示和导航。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.showIndicator(value: boolean \| DotIndicator \| DigitIndicator)` THEN 设置指示器类型，默认显示 DOT 圆点指示器 | 正常 |
| AC-2.2 | WHEN showIndicator 为 true THEN 显示默认 DotIndicator（圆点指示器） | 正常 |
| AC-2.3 | WHEN showIndicator 为 false THEN 不显示任何指示器 | 正常 |
| AC-2.4 | WHEN showIndicator 为 DotIndicator 对象 THEN 显示圆点指示器并应用自定义样式 | 正常 |
| AC-2.5 | WHEN DotIndicator.itemWidth 设置 THEN 圆点未选中宽度生效，默认 4vp | 正常 |
| AC-2.6 | WHEN DotIndicator.itemHeight 设置 THEN 圆点未选中高度生效，默认 4vp | 正常 |
| AC-2.7 | WHEN DotIndicator.selectedItemWidth 设置 THEN 圆点选中宽度生效，默认 12vp | 正常 |
| AC-2.8 | WHEN DotIndicator.selectedItemHeight 设置 THEN 圆点选中高度生效，默认 12vp | 正常 |
| AC-2.9 | WHEN DotIndicator.mask 设置 THEN 圆点指示器蒙版生效，默认 false | 正常 |
| AC-2.10 | WHEN DotIndicator.color 设置 THEN 圆点未选中颜色生效，默认 Color.White | 正常 |
| AC-2.11 | WHEN DotIndicator.selectedColor 设置 THEN 圆点选中颜色生效，默认 0xD9D9D9 | 正常 |
| AC-2.12 | WHEN DotIndicator.maxDisplayCount 设置（@since 12）THEN 圆点最大显示数量生效，默认 10 | 正常 |
| AC-2.13 | WHEN DotIndicator.space 设置（@since 19）THEN 圆点间距生效 | 正常 |
| AC-2.14 | WHEN DotIndicator.ignoreSize 设置 THEN 圆点指示器忽略尺寸标志生效 | 边界 |
| AC-2.15 | WHEN 指示器类型为 DOT THEN SwiperIndicatorType = DOT(0)，由 IndicatorComponent 绘制 | 正常 |

> SwiperIndicatorType 枚举：`swiper_constants.h:25-29`。IndicatorComponent 绘制：`indicator_component.cpp`。DotIndicator 属性映射：`swiper_model_ng.cpp` SetDotIndicatorStyle。

### US-3: 配置数字指示器

**作为** 应用开发者,
**我想要** 配置 Swiper 数字指示器（DigitIndicator）样式和位置,
**以便** 显示页码数字指示。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN showIndicator 为 DigitIndicator 对象 THEN 显示数字指示器，SwiperIndicatorType = DIGIT(1) | 正常 |
| AC-3.2 | WHEN DigitIndicator.digitFontColor 设置 THEN 数字未选中字体颜色生效 | 正常 |
| AC-3.3 | WHEN DigitIndicator.selectedDigitFontColor 设置 THEN 数字选中字体颜色生效 | 正常 |
| AC-3.4 | WHEN DigitIndicator.digitFontSize 设置 THEN 数字未选中字体大小生效 | 正常 |
| AC-3.5 | WHEN DigitIndicator.selectedDigitFontSize 设置 THEN 数字选中字体大小生效 | 正常 |
| AC-3.6 | WHEN DigitIndicator.digitFontWeight 设置 THEN 数字未选中字体粗细生效 | 正常 |
| AC-3.7 | WHEN DigitIndicator.selectedDigitFontWeight 设置 THEN 数字选中字体粗细生效 | 正常 |
| AC-3.8 | WHEN DigitIndicator.space 设置 THEN 数字指示器间距生效 | 正常 |
| AC-3.9 | WHEN DigitIndicator.hide 设置 THEN 数字指示器隐藏标志生效 | 边界 |

> DigitIndicator 属性映射：`swiper_model_ng.cpp` SetDigitIndicatorStyle。

### US-4: 配置指示器位置

**作为** 应用开发者,
**我想要** 配置 Swiper 指示器的位置（左/右/上/下/起始/结束）,
**以便** 适配不同布局方向和 RTL 场景。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 DotIndicator/DigitIndicator `.left(value: Length)` THEN 指示器左偏移生效 | 正常 |
| AC-4.2 | WHEN 调用 DotIndicator/DigitIndicator `.top(value: Length)` THEN 指示器上偏移生效 | 正常 |
| AC-4.3 | WHEN 调用 DotIndicator/DigitIndicator `.right(value: Length)` THEN 指示器右偏移生效 | 正常 |
| AC-4.4 | WHEN 调用 DotIndicator/DigitIndicator `.bottom(value: Length)` THEN 指示器下偏移生效 | 正常 |
| AC-4.5 | WHEN 调用 DotIndicator/DigitIndicator `.start(value: Length)` THEN 指示器起始偏移生效（RTL 适配） | 正常 |
| AC-4.6 | WHEN 调用 DotIndicator/DigitIndicator `.end(value: Length)` THEN 指示器结束偏移生效（RTL 适配） | 正常 |

> 指示器位置属性映射到 IndicatorComponent 的布局属性。C API 对应 OH_ArkUI_SwiperIndicator_SetStartPosition/SetTopPosition/SetEndPosition/SetBottomPosition。

### US-5: 配置导航箭头

**作为** 应用开发者,
**我想要** 配置 Swiper 导航箭头（displayArrow/ArrowStyle）,
**以便** 提供前后翻页的视觉导航。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 调用 `.displayArrow(value: boolean \| ArrowStyle)` THEN 显示导航箭头，默认 false | 正常 |
| AC-5.2 | WHEN displayArrow 为 true THEN 显示默认样式导航箭头（左右箭头按钮） | 正常 |
| AC-5.3 | WHEN displayArrow 为 ArrowStyle 对象 THEN 显示自定义样式导航箭头 | 正常 |
| AC-5.4 | WHEN ArrowStyle.showBackground 设置 THEN 箭头背景显示标志生效，默认 false | 正常 |
| AC-5.5 | WHEN ArrowStyle.isSidebarMiddle 设置 THEN 箭头是否居中显示标志生效，默认 false | 正常 |
| AC-5.6 | WHEN ArrowStyle.backgroundSize 设置 THEN 箭头背景尺寸生效 | 正常 |
| AC-5.7 | WHEN ArrowStyle.backgroundColor 设置 THEN 箭头背景颜色生效 | 正常 |
| AC-5.8 | WHEN ArrowStyle.arrowSize 设置 THEN 箭头图标尺寸生效 | 正常 |
| AC-5.9 | WHEN ArrowStyle.arrowColor 设置 THEN 箭头图标颜色生效 | 正常 |
| AC-5.10 | WHEN isHoverShow 设置 THEN 悬停时才显示箭头 | 边界 |

> ArrowStyle 属性映射：`swiper_model_ng.cpp` SetDisplayArrow。箭头绘制：`arrow_element.cpp`。C API ArkUI_SwiperArrowStyle 对应：`native_type.h:2856-2986`。

### US-6: 配置指示器交互和独立指示器组件

**作为** 应用开发者,
**我想要** 配置指示器可交互性和使用独立 IndicatorComponent 组件,
**以便** 实现点击指示器跳转和自定义指示器场景。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 调用 `.indicatorInteractive(value: boolean)` THEN 设置指示器是否可交互（点击跳转），默认 true（@since 12） | 正常 |
| AC-6.2 | WHEN indicatorInteractive 为 true THEN 点击圆点/数字指示器可跳转到对应页 | 正常 |
| AC-6.3 | WHEN indicatorInteractive 为 false THEN 点击指示器不触发跳转 | 正常 |
| AC-6.4 | WHEN 使用 IndicatorComponent（@since 15）独立组件 THEN 可创建与 Swiper 分离的指示器 | 正常 |
| AC-6.5 | WHEN IndicatorComponent 设置 IndicatorComponentController THEN 可通过控制器设置 initialIndex、count、style、loop、vertical | 正常 |
| AC-6.6 | WHEN IndicatorComponentController.initialIndex 设置 THEN 独立指示器初始索引生效 | 正常 |
| AC-6.7 | WHEN IndicatorComponentController.count 设置 THEN 独立指示器显示数量生效 | 正常 |
| AC-6.8 | WHEN IndicatorComponent 设置 style THEN 独立指示器样式生效（DotIndicator/DigitIndicator） | 正常 |
| AC-6.9 | WHEN IndicatorComponent 设置 onChange THEN 独立指示器页码切换回调生效 | 正常 |

> indicatorInteractive 映射：`swiper_model.h:179`。IndicatorComponent：`indicator_component.cpp`, `indicator_component_controller.h`。

### US-7: C API 指示器与箭头对象

**作为** NDK 开发者,
**我想要** 通过 C API 配置 Swiper 指示器和箭头样式,
**以便** 在 NDK 应用中使用指示器和箭头功能。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-7.1 | WHEN 调用 `OH_ArkUI_SwiperIndicator_Create(ArkUI_SwiperIndicatorType type)` THEN 创建 Swiper 指示器对象 | 正常 |
| AC-7.2 | WHEN 调用 `OH_ArkUI_SwiperIndicator_Dispose(indicator)` THEN 释放指示器对象 | 正常 |
| AC-7.3 | WHEN 调用 OH_ArkUI_SwiperIndicator_Set* THEN 设置指示器属性（StartPosition/TopPosition/EndPosition/BottomPosition/ItemWidth/ItemHeight/SelectedItemWidth/SelectedItemHeight/Mask/Color/SelectedColor/MaxDisplayCount/Space） | 正常 |
| AC-7.4 | WHEN 调用 OH_ArkUI_SwiperIndicator_Get* THEN 获取指示器属性值 | 正常 |
| AC-7.5 | WHEN 调用 `OH_ArkUI_SwiperDigitIndicator_Create()` THEN 创建数字指示器对象（@since 19） | 正常 |
| AC-7.6 | WHEN 调用 OH_ArkUI_SwiperDigitIndicator_Set* THEN 设置数字指示器属性（StartPosition/TopPosition/EndPosition/BottomPosition/FontColor/SelectedFontColor/FontSize/SelectedFontSize/FontWeight/SelectedFontWeight） | 正常 |
| AC-7.7 | WHEN 调用 `OH_ArkUI_SwiperArrowStyle_Create()` THEN 创建箭头样式对象 | 正常 |
| AC-7.8 | WHEN 调用 OH_ArkUI_SwiperArrowStyle_Set* THEN 设置箭头样式属性（ShowBackground/ShowSidebarMiddle/BackgroundSize/BackgroundColor/ArrowSize/ArrowColor） | 正常 |
| AC-7.9 | WHEN 调用 `OH_ArkUI_SwiperArrowStyle_Destroy(arrowStyle)` THEN 释放箭头样式对象 | 正常 |
| AC-7.10 | WHEN 调用 OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom THEN 设置指示器是否忽略底部尺寸 | 边界 |

> C API 指示器函数：`native_type.h:2368-2632`。C API 数字指示器函数：`native_type.h:2640-2848`。C API 箭头样式函数：`native_type.h:2856-2986`。结构体定义：`node_extened.h:128-168`。

---

## 验收追溯

| AC编号 | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1~1.8 | R-1, R-2 | — | 代码审查 + XTS | `swiper_paint_property.h:69-70`, `swiper_pattern.cpp` |
| AC-2.1~2.15 | R-3, R-4 | — | 代码审查 + XTS | `indicator_component.cpp`, `swiper_model_ng.cpp` |
| AC-3.1~3.9 | R-3, R-5 | — | 代码审查 + XTS | `swiper_model_ng.cpp` SetDigitIndicatorStyle |
| AC-4.1~4.6 | R-6 | — | 代码审查 | `indicator_component.cpp` |
| AC-5.1~5.10 | R-7 | — | 代码审查 + XTS | `arrow_element.cpp`, `swiper_model_ng.cpp` |
| AC-6.1~6.9 | R-8, R-9 | — | 代码审查 + XTS | `indicator_component.cpp`, `indicator_component_controller.h` |
| AC-7.1~7.10 | R-10 | — | C API 单元测试 | `native_type.h:2368-2986`, `node_extened.h:128-168` |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | autoPlay/autoPlayInterval 存储在 SwiperPaintProperty SwiperAnimationStyle 组，变更触发 PROPERTY_UPDATE_RENDER | — | AC-1.1~1.8 |
| R-2 | 行为 | — | autoPlay 为 true 时 SwiperPattern 内 Timer 驱动自动翻页，stopWhenTouch 默认 true（触摸暂停），reverse 默认 false（正向） | — | AC-1.3~1.7 |
| R-3 | 行为 | — | SwiperIndicatorType 枚举三种：DOT(0)、DIGIT(1)、ARC_DOT(2)；DOT/DIGIT 由 IndicatorComponent 绘制，ARC_DOT 由 ArcSwiperPattern 绘制 | — | AC-2.15, AC-3.1 |
| R-4 | 行为 | — | DotIndicator 属性：itemWidth/itemHeight/selectedItemWidth/selectedItemHeight/mask/color/selectedColor/maxDisplayCount(@since 12)/space(@since 19)/ignoreSize | — | AC-2.5~2.14 |
| R-5 | 行为 | — | DigitIndicator 属性：digitFontColor/selectedDigitFontColor/digitFontSize/selectedDigitFontSize/digitFontWeight/selectedDigitFontWeight/space/hide | — | AC-3.2~3.9 |
| R-6 | 行为 | — | 指示器位置支持 .left/.top/.right/.bottom/.start/.end 六个方向偏移，start/end 用于 RTL 适配 | — | AC-4.1~4.6 |
| R-7 | 行为 | — | ArrowStyle 属性：showBackground/isSidebarMiddle/backgroundSize/backgroundColor/arrowSize/arrowColor；isHoverShow 控制悬停显示 | — | AC-5.4~5.10 |
| R-8 | 行为 | — | indicatorInteractive 默认 true，指示器可点击跳转；设为 false 时禁止跳转 | — | AC-6.1~6.3 |
| R-9 | 行为 | — | IndicatorComponent（@since 15）为独立指示器组件，通过 IndicatorComponentController 设置 initialIndex/count/style/loop/vertical/onChange | — | AC-6.4~6.9 |
| R-10 | 行为 | — | C API 提供 OH_ArkUI_SwiperIndicator_*（指示器对象）、OH_ArkUI_SwiperDigitIndicator_*（数字指示器对象 @since 19）、OH_ArkUI_SwiperArrowStyle_*（箭头样式对象）三组函数 | — | AC-7.1~7.10 |
| R-11 | 边界 | — | indicatorStyle 已废弃，由 DotIndicator/DigitIndicator 对象替代 | — | — |
| R-12 | 异常 | — | showIndicator 为 boolean 时，true 显示默认 DOT 指示器，false 不显示指示器 | — | AC-2.2, AC-2.3 |

---

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|-----------|----------|----------|
| VM-1 | AC-1.1~1.8 (自动播放) | XTS + 代码审查 | Timer 驱动、stopWhenTouch/reverse 选项 |
| VM-2 | AC-2.1~2.15 (圆点指示器) | XTS + 代码审查 | DotIndicator 各属性映射和绘制 |
| VM-3 | AC-3.1~3.9 (数字指示器) | XTS + 代码审查 | DigitIndicator 各属性映射和绘制 |
| VM-4 | AC-4.1~4.6 (指示器位置) | XTS + 代码审查 | 指示器位置偏移属性 |
| VM-5 | AC-5.1~5.10 (导航箭头) | XTS + 代码审查 | ArrowStyle 属性和悬停显示 |
| VM-6 | AC-6.1~6.9 (指示器交互与独立组件) | XTS + 代码审查 | indicatorInteractive 和 IndicatorComponent |
| VM-7 | AC-7.1~7.10 (C API 指示器与箭头) | C API 单元测试 | SwiperIndicator/DigitIndicator/ArrowStyle 对象函数 |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC |
|----------|------|----------|---------|
| `autoPlay(value: boolean)` | Public | 设置是否自动播放 | AC-1.1 |
| `autoPlayInterval(value: number)` | Public | 设置自动播放间隔（ms） | AC-1.2 |
| `autoPlayOptions(value: SwiperAutoPlayOptions)` | Public | 设置自动播放选项 | AC-1.4 |
| `showIndicator(value: boolean \| DotIndicator \| DigitIndicator)` | Public | 设置指示器类型和样式 | AC-2.1~2.4 |
| `indicatorStyle(value: SwiperIndicatorStyle)` | Public（废弃） | 设置指示器样式（已废弃） | R-11 |
| `indicatorInteractive(value: boolean)` | Public | 设置指示器是否可交互 | AC-6.1 |
| `displayArrow(value: boolean \| ArrowStyle)` | Public | 设置导航箭头 | AC-5.1 |
| `IndicatorComponent` | Public | 独立指示器组件 | AC-6.4 |
| `IndicatorComponentController` | Public | 独立指示器控制器 | AC-6.5 |
| `OH_ArkUI_SwiperIndicator_Create/Dispose/Set*/Get*` | System | C API 指示器对象 | AC-7.1~7.4 |
| `OH_ArkUI_SwiperDigitIndicator_Create/Set*/Get*/Destroy` | System | C API 数字指示器对象 | AC-7.5~7.6 |
| `OH_ArkUI_SwiperArrowStyle_Create/Set*/Get*/Destroy` | System | C API 箭头样式对象 | AC-7.7~7.9 |

### 变更/废弃 API

| API 签名 | 变更类型 | 说明 | 关联 Feat |
|----------|----------|------|----------|
| `indicatorStyle(value)` | 废弃 | 由 DotIndicator/DigitIndicator 对象替代 | Feat-02 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

- **已有 API 行为变更:** 否
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** API 7
- **API 版本号策略:** autoPlay @since 7；autoPlayOptions @since 18；DotIndicator.maxDisplayCount @since 12；DotIndicator.space @since 19；indicatorInteractive @since 12；displayArrow @since 10；IndicatorComponent @since 15；C API DigitIndicator @since 19；C API ArrowStyle @since 12

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|---------|----------|---------|
| 指示器体系三种类型 | DOT/DIGIT/ARC_DOT 三种指示器，DOT/DIGIT 由 IndicatorComponent 绘制，ARC_DOT 由 ArcSwiperPattern 绘制 | AC-2.15, AC-3.1 |
| 指示器样式替代 | indicatorStyle 已废弃，由 DotIndicator/DigitIndicator 对象替代 | R-11 |
| C API 对象生命周期 | OH_ArkUI_SwiperIndicator/DigitIndicator/ArrowStyle 对象需手动 Create/Dispose | AC-7.1~7.9 |
| 未组件化 | Swiper 未组件化，JSView + Bridge 双路径共存 | — |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|----------|----------|------|
| 性能 | 指示器绘制不影响 Swiper 主轴布局性能 | 代码审查 | `indicator_component.cpp` |

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | DotIndicator/DigitIndicator 标准指示器 | — | — | — |
| 平板 | 无差异 | — | — | — |
| 穿戴 | ArcSwiper 使用 ARC_DOT 弧形指示器 | SUPPORT_DIGITAL_CROWN 宏守卫 | 构建验证 | `arc_swiper_pattern.cpp` |

---

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 是 | 指示器支持 aria-label | 桥接层处理 |
| 大字体 | 否 | 指示器尺寸由 DotIndicator/DigitIndicator 属性控制 | — |
| 深色模式 | 否 | 指示器颜色由 color/selectedColor 属性控制 | — |
| 多窗口/分屏 | 否 | 无特殊处理 | — |
| 版本升级 | 是 | DotIndicator.maxDisplayCount @since 12，DotIndicator.space @since 19，autoPlayOptions @since 18 | AC-1.4, AC-2.12, AC-2.13 |

## 行为场景（可选，Gherkin）

```gherkin
Feature: Swiper 自动播放与指示器

  Scenario: 设置自动播放和间隔
    Given 一个 Swiper 组件，包含 5 个子项
    When 调用 .autoPlay(true) 和 .autoPlayInterval(5000)
    Then Swiper 每 5000ms 自动翻页

  Scenario: 设置 stopWhenTouch 为 true（默认）
    Given 一个自动播放的 Swiper
    When 用户触摸 Swiper 区域
    Then 自动播放暂停
    When 用户松开触摸
    Then 自动播放恢复

  Scenario: 设置 DotIndicator 自定义样式
    Given 一个 Swiper 组件
    When 调用 .showIndicator(new DotIndicator({ itemWidth: 8, itemHeight: 8, selectedItemWidth: 16, selectedItemHeight: 8, color: '#CCCCCC', selectedColor: '#FFFFFF' }))
    Then 圆点指示器显示自定义样式

  Scenario: 设置 DigitIndicator
    Given 一个 Swiper 组件
    When 调用 .showIndicator(new DigitIndicator({ digitFontColor: '#CCCCCC', selectedDigitFontColor: '#FFFFFF' }))
    Then 数字指示器显示页码数字

  Scenario: 设置导航箭头
    Given 一个 Swiper 组件
    When 调用 .displayArrow(new ArrowStyle({ showBackground: true, arrowColor: '#FFFFFF' }))
    Then 显示带背景的导航箭头
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（自动播放与指示器，不含动画/事件/C API 全量）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper autoPlay autoPlayInterval SwiperAutoPlayOptions stopWhenTouch reverse and Timer drive"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper DotIndicator DigitIndicator IndicatorComponent and SwiperIndicatorType indicator style"
  - repo: "openharmony/arkui_ace_engine"
    query: "Swiper displayArrow ArrowStyle isHoverShow and C API SwiperIndicator SwiperArrowStyle"
```

**关键文档：** `design.md`（同目录）
