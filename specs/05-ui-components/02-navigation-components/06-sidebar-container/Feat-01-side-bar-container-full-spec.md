# 特性规格

## 概述

| 字段 | 内容 |
|------|------|
| 特性名称 | SideBarContainer 组件全量规格 |
| 特性编号 | Feat-01 |
| FuncID | 05-02-06 |
| 所属 Epic | 无 |
| 优先级 | P0 |
| 目标版本 | API 8 ~ API 26+ |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 标准 |
| lineage | new-on-legacy（已有实现的规格补录） |

## 本次变更范围（Delta）

> 本特性为已有实现补录，非增量变更。以下列出自 API 8 以来的关键变更里程碑。

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | SideBarContainer 组件入口 + SideBarContainerType 四种模式 | @since 8，Embed/Overlay/AUTO/DISPLACE |
| ADDED | showSideBar, showControlButton, controlButton, sideBarPosition 属性 | @since 8 |
| ADDED | sideBarWidth, minSideBarWidth, maxSideBarWidth, minContentWidth 属性 | @since 8 |
| ADDED | divider, autoHide 属性 | @since 8 |
| ADDED | onChange 事件 | @since 8 |
| MODIFIED | API 10+ 默认侧边栏宽度从 200vp 变为 240vp，最小侧边栏宽度同步变更 | API 10 行为变更 |
| MODIFIED | API 10+ 最小内容宽度从 0vp 变为 360vp | API 10 行为变更 |
| MODIFIED | API 10+ 控制按钮尺寸从 32vp 变为 24vp | API 10 行为变更 |
| ADDED | onChangeEvent 事件 | @since 9 |
| ADDED | onSideBarWidthChangeEvent 事件 | @since 11 |
| ADDED | showSideBarWithGesture 属性 | @since 26 |
| ADDED | SideBarContainerModifier (Dynamic + Static + C API) | 组件化 Modifier |
| ADDED | 组件化 bridge/ 子目录 + libarkui_side_bar_container.z.so | 组件化输出 |

## 输入文档

- **需求基线**: 已有能力补录（无独立 requirement.md / proposal.md）
- **设计文档**: `specs/05-ui-components/02-navigation-components/06-sidebar-container/design.md`
- **SDK 类型定义**:
  - Dynamic: `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/sidebar.d.ts`
  - Static: `<OH_ROOT>/interface/sdk-js/api/arkui/component/sidebar.static.d.ets`

> 需求基线、不涉及项、受影响子系统与仓库详见 proposal.md，本文档不重复摘录。design.md 与本文档并行产出，互不依赖。

## 用户故事

### US-1: 创建 SideBarContainer 并选择侧边栏类型

**角色**: 应用开发者
**期望**: 我想要创建 SideBarContainer 并选择侧边栏类型（Embed/Overlay/AUTO/DISPLACE）
**价值**: 以便在不同布局场景中灵活展示侧边栏内容

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 创建 `SideBarContainer(SideBarContainerType.Embed)` THEN 侧边栏与内容并列显示，侧边栏宽度从容器宽度中扣除 | 正常 |
| AC-1.2 | WHEN 创建 `SideBarContainer(SideBarContainerType.Overlay)` THEN 侧边栏覆盖在内容之上，隐藏时内容全宽显示 | 正常 |
| AC-1.3 | WHEN 创建 `SideBarContainer(SideBarContainerType.DISPLACE)` THEN 侧边栏显示时推挤内容区域，隐藏时内容恢复全宽 | 正常 |
| AC-1.4 | WHEN 创建 `SideBarContainer(SideBarContainerType.AUTO)` THEN 根据容器宽度自动选择 Embed 或 Overlay 模式 | 正常 |
| AC-1.5 | WHEN SideBarContainerType 运行时变更 THEN LayoutAlgorithm 根据新类型重新布局，typeUpdateWidth 记录变更前的宽度 | 边界 |

### US-2: 控制侧边栏显示/隐藏

**角色**: 应用开发者
**期望**: 我想要通过属性和交互控制侧边栏的显示与隐藏
**价值**: 以便在应用运行时动态控制侧边栏可见性

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 设置 `showSideBar(true)` THEN 侧边栏展开显示，动画过渡从隐藏到显示 | 正常 |
| AC-2.2 | WHEN 设置 `showSideBar(false)` THEN 侧边栏收起隐藏，动画过渡从显示到隐藏 | 正常 |
| AC-2.3 | WHEN 点击控制按钮 THEN 侧边栏显示/隐藏状态翻转，onChange 回调触发 | 正常 |
| AC-2.4 | WHEN 设置 `autoHide(true)` 且容器宽度小于 minContentWidth THEN Overlay 模式下自动隐藏侧边栏 | 正常 |
| AC-2.5 | WHEN 设置 `autoHide(false)` THEN 不自动隐藏，容器宽度小于 minContentWidth 时侧边栏保持当前状态 | 正常 |
| AC-2.6 | WHEN 窗口尺寸变化且 autoHide=true THEN `OnWindowSizeChanged()` 检测宽度变化，自动调整侧边栏状态 | 正常 |

### US-3: 配置侧边栏宽度和位置

**角色**: 应用开发者
**期望**: 我想要配置侧边栏的宽度范围和位置
**价值**: 以便精确控制侧边栏在界面中的空间占比

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 设置 `sideBarWidth(280)` THEN 侧边栏宽度为 280vp，受 minSideBarWidth/maxSideBarWidth 约束 | 正常 |
| AC-3.2 | WHEN 设置 `minSideBarWidth(200)` 和 `maxSideBarWidth(400)` THEN 侧边栏宽度在 200~400vp 范围内 | 正常 |
| AC-3.3 | WHEN 拖拽分隔线调整侧边栏宽度 THEN 宽度实时更新，受 min/max 约束，onSideBarWidthChangeEvent 回调触发 | 正常 |
| AC-3.4 | WHEN 设置 `sideBarPosition(SideBarPosition.Start)` THEN 侧边栏在容器左侧 | 正常 |
| AC-3.5 | WHEN 设置 `sideBarPosition(SideBarPosition.End)` THEN 侧边栏在容器右侧 | 正常 |
| AC-3.6 | WHEN 设置 `minContentWidth(360)` THEN 内容区域最小宽度为 360vp，影响自动隐藏判定 | 正常 |

### US-4: 配置控制按钮样式

**角色**: 应用开发者
**期望**: 我想要自定义控制按钮的图标、尺寸和位置
**价值**: 以便控制按钮视觉风格与应用设计语言一致

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 设置 `controlButton({ shown: $r('app.media.icon_shown'), hidden: $r('app.media.icon_hidden'), switching: $r('app.media.icon_switching') })` THEN 控制按钮按侧边栏状态显示对应图标 | 正常 |
| AC-4.2 | WHEN 设置 `controlButton({ width: 24, height: 24, left: 16, top: 48 })` THEN 控制按钮尺寸为 24vp×24vp，位置偏移 left=16vp, top=48vp | 正常 |
| AC-4.3 | WHEN 控制按钮图标加载失败 THEN 通过 InitImageErrorCallback 回退到 SideBarTheme 默认图标 | 异常 |
| AC-4.4 | WHEN 设置 `showControlButton(false)` THEN 控制按钮不显示 | 正常 |

### US-5: 配置分隔线和自动隐藏

**角色**: 应用开发者
**期望**: 我想要配置侧边栏与内容之间的分隔线外观，以及自动隐藏行为
**价值**: 以便精确控制分隔线视觉效果和容器自适应行为

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 设置 `divider({ strokeWidth: 1, startMargin: 16, endMargin: 16, color: '#33000000' })` THEN 分隔线宽度 1vp、起始边距 16vp、末尾边距 16vp、颜色 #33000000 | 正常 |
| AC-5.2 | WHEN 设置 `divider(null)` THEN 分隔线不显示 | 正常 |
| AC-5.3 | WHEN 鼠标悬停在分隔线上 THEN 分隔线显示阴影效果（`UpdateDividerShadow`） | 正常 |
| AC-5.4 | WHEN 未设置 divider THEN 使用默认值：strokeWidth=1vp, startMargin=0vp, endMargin=0vp, color=0x08000000 | 正常 |

### US-6: 监听侧边栏状态变化

**角色**: 应用开发者
**期望**: 我想要监听侧边栏显示/隐藏状态变化和宽度变化
**价值**: 以便在侧边栏状态或宽度变化时执行联动逻辑

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 侧边栏显示/隐藏状态变化 THEN onChange 回调触发，参数为 boolean isShow | 正常 |
| AC-6.2 | WHEN 侧边栏宽度变化（拖拽分隔线或属性设置）THEN onSideBarWidthChangeEvent 回调触发，参数为 Dimension sideBarWidth | 正常 |
| AC-6.3 | WHEN 设置 `showSideBarWithGesture(true)` THEN Overlay 模式下允许手势滑动显示/隐藏侧边栏（API 26） | 正常 |

## 验收追溯

| AC编号 | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1 ~ AC-1.5 | R-1, R-2 | TASK-SIDEBAR-01 | UT | `test/unittest/core/pattern/side_bar/` |
| AC-2.1 ~ AC-2.6 | R-3, R-4, R-5, R-6 | TASK-SIDEBAR-01 | UT + 手工 | side_bar 单测 |
| AC-3.1 ~ AC-3.6 | R-7, R-8, R-9 | TASK-SIDEBAR-01 | UT | layout 单测 |
| AC-4.1 ~ AC-4.4 | R-10, R-11, R-12 | TASK-SIDEBAR-01 | UT | model 单测 |
| AC-5.1 ~ AC-5.4 | R-13, R-14 | TASK-SIDEBAR-01 | UT | side_bar 单测 |
| AC-6.1 ~ AC-6.3 | R-15, R-16 | TASK-SIDEBAR-01 | UT | event 单测 |

## 规则定义

> **统一规则表，取消 FR/BR/EX/RC 四分类。** 类型标签：**行为**（正常路径下的系统行为）、**边界**（输入/状态的临界点）、**异常**（非法输入或异常状态的处理）、**恢复**（系统异常后的恢复策略）。

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | `side_bar_container_layout_algorithm.cpp` | Embed 模式下侧边栏与内容并列，侧边栏宽度从容器宽度中扣除 | — | AC-1.1 |
| R-2 | 行为 | `side_bar_container_layout_algorithm.cpp` | Overlay 模式下侧边栏覆盖内容，使用 maskColor 遮罩 | — | AC-1.2 |
| R-3 | 行为 | `side_bar_container_pattern.cpp` | showSideBar=true 展开、false 收起，切换时 Animator+CurveAnimation 过渡动画 | — | AC-2.1, AC-2.2 |
| R-4 | 行为 | `side_bar_container_pattern.cpp` | 控制按钮点击翻转 showSideBar 状态，触发 onChange 回调 | — | AC-2.3 |
| R-5 | 行为 | `side_bar_container_pattern.cpp` | autoHide=true 且容器宽度 < minContentWidth 时自动隐藏侧边栏（Overlay 模式） | — | AC-2.4, AC-2.5 |
| R-6 | 行为 | `side_bar_container_pattern.cpp` | OnWindowSizeChanged() 监听窗口尺寸变化，autoHide 时自动调整 | — | AC-2.6 |
| R-7 | 行为 | `side_bar_container_layout_property.h` | sideBarWidth 受 minSideBarWidth/maxSideBarWidth 约束，超出范围时截断 | — | AC-3.1, AC-3.2 |
| R-8 | 行为 | `side_bar_container_pattern.cpp` | 分隔线拖拽实时调整侧边栏宽度，HandleDragUpdate 更新，HandleDragEnd 完成 | minSideBarWidth/maxSideBarWidth 约束 | AC-3.3 |
| R-9 | 行为 | `constants.h:699` | SideBarPosition.Start 侧边栏在左侧，End 在右侧；RTL 布局下 GetSideBarPositionWithRtl 反转 | — | AC-3.4, AC-3.5 |
| R-10 | 行为 | `side_bar_container_layout_property.h:30-38` | ControlButtonStyle 存储 width/height/left/top 和 ShowIconInfo/HiddenIconInfo/SwitchingIconInfo | — | AC-4.1, AC-4.2 |
| R-11 | 行为 | `side_bar_container_layout_property.h` | 控制按钮默认值：API<10 width=32vp, API>=10 width=24vp；left=16vp, top=48vp | — | AC-4.2 |
| R-12 | 异常 | `side_bar_container_pattern.cpp` | 控制按钮图标加载失败时通过 InitImageErrorCallback 回退到 SideBarTheme 默认图标 | — | AC-4.3 |
| R-13 | 行为 | `side_bar_container_layout_property.h:40-45` | DividerStyle 存储 strokeWidth/startMargin/endMargin/color | — | AC-5.1 |
| R-14 | 行为 | `side_bar_container_layout_property.h` | divider=null 隐藏分隔线；默认值 strokeWidth=1vp, startMargin=0vp, endMargin=0vp, color=0x08000000 | — | AC-5.2, AC-5.4 |
| R-15 | 行为 | `side_bar_container_event_hub.h` | onChange/onChangeEvent 回调参数为 boolean isShow | — | AC-6.1 |
| R-16 | 行为 | `side_bar_container_event_hub.h` | onSideBarWidthChangeEvent 回调参数为 Dimension sideBarWidth；showSideBarWithGesture 在 Overlay 模式下支持手势 | — | AC-6.2, AC-6.3 |
| R-17 | 边界 | `arkts_native_side_bar_container_bridge.cpp` | API 10+ 侧边栏默认宽度从 200vp 变为 240vp，最小侧边栏宽度同步变更，最小内容宽度从 0vp 变为 360vp | — | — |
| R-18 | 边界 | `side_bar_container_layout_algorithm.cpp` | AUTO 模式根据容器宽度自动选择 Embed 或 Overlay，切换不触发 onChange | — | AC-1.4 |
| R-19 | 边界 | `side_bar_container_pattern.cpp` | sideBarWidth 超出 maxSideBarWidth 时截断为 maxSideBarWidth，低于 minSideBarWidth 时截断为 minSideBarWidth | — | AC-3.1, AC-3.2 |
| R-20 | 异常 | `side_bar_container_pattern.cpp` | 动画过程中再次设置 showSideBar THEN 中断当前动画，以新状态为目标重新开始 | — | — |
| R-21 | 恢复 | `side_bar_container_layout_property.h` | 属性 Reset 时恢复默认值：showSideBar=true, showControlButton=true, autoHide=true, sideBarPosition=START | — | — |

---

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|-----------|----------|----------|
| VM-1 | AC-1.1 ~ AC-1.5 | UT | 四种 SideBarContainerType 正确布局 |
| VM-2 | AC-2.1 ~ AC-2.6 | UT + 手工 | showSideBar 切换 + 控制按钮 + autoHide |
| VM-3 | AC-3.1 ~ AC-3.6 | UT | 侧边栏宽度约束 + 位置配置 |
| VM-4 | AC-4.1 ~ AC-4.4 | UT | 控制按钮样式与图标 |
| VM-5 | AC-5.1 ~ AC-5.4 | UT | 分隔线配置与默认值 |
| VM-6 | AC-6.1 ~ AC-6.3 | UT | 事件回调 + showSideBarWithGesture |

## API 变更分析

### 新增 API

| API 名称 | 类型 | 功能描述 | 关联 AC | @since |
|----------|------|----------|---------|--------|
| SideBarContainer(type: SideBarContainerType) | Public | 创建 SideBarContainer 组件 | AC-1.1 ~ AC-1.4 | 8 |
| SideBarContainerType (Embed/Overlay/AUTO/DISPLACE) | Public | 侧边栏类型枚举 | AC-1.1 ~ AC-1.4 | 8 |
| SideBarPosition (Start/End) | Public | 侧边栏位置枚举 | AC-3.4, AC-3.5 | 8 |
| SideBarContainerAttribute.showSideBar(show: boolean) | Public | 控制侧边栏显示/隐藏 | AC-2.1, AC-2.2 | 8 |
| SideBarContainerAttribute.showControlButton(show: boolean) | Public | 控制按钮是否显示 | AC-4.4 | 8 |
| SideBarContainerAttribute.controlButton(style: ButtonStyle) | Public | 控制按钮样式配置（含 ButtonIconOptions） | AC-4.1, AC-4.2 | 8 |
| ButtonIconOptions (shown/hidden/switching) | Public | 控制按钮三种状态图标 | AC-4.1 | 8 |
| SideBarContainerAttribute.sideBarPosition(position: SideBarPosition) | Public | 侧边栏位置 | AC-3.4, AC-3.5 | 8 |
| SideBarContainerAttribute.sideBarWidth(value: Length) | Public | 侧边栏宽度 | AC-3.1 | 8 |
| SideBarContainerAttribute.minSideBarWidth(value: Length) | Public | 最小侧边栏宽度 | AC-3.2 | 8 |
| SideBarContainerAttribute.maxSideBarWidth(value: Length) | Public | 最大侧边栏宽度 | AC-3.2 | 8 |
| SideBarContainerAttribute.minContentWidth(value: Length) | Public | 最小内容宽度 | AC-3.6 | 8 |
| SideBarContainerAttribute.divider(value: DividerStyle \| null) | Public | 分隔线样式（null 隐藏） | AC-5.1, AC-5.2 | 8 |
| DividerStyle (strokeWidth/startMargin/endMargin/color) | Public | 分隔线样式结构 | AC-5.1 | 8 |
| SideBarContainerAttribute.autoHide(autoHide: boolean) | Public | 自动隐藏（Overlay 模式） | AC-2.4, AC-2.5 | 8 |
| SideBarContainerAttribute.onChange(callback: (isShow: boolean) => void) | Public | 侧边栏状态变化回调 | AC-6.1 | 8 |
| SideBarContainerAttribute.onChangeEvent(callback: (isShow: boolean) => void) | Public | 侧边栏状态变化回调（v9） | AC-6.1 | 9 |
| SideBarContainerAttribute.onSideBarWidthChangeEvent(callback: (width: Dimension) => void) | Public | 侧边栏宽度变化回调 | AC-6.2 | 11 |
| SideBarContainerAttribute.showSideBarWithGesture(show: boolean) | Public | 手势显示/隐藏侧边栏 | AC-6.3 | 26 |
| SideBarContainerModifier | Public | Dynamic Modifier | — | — |
| ArkUISideBarContainerModifier | NDK/Public | C API Modifier | — | — |

### 变更/废弃 API

| API 名称 | 变更类型 | 关联 AC |
|----------|----------|---------|
| 无 | — | — |

> 截至当前版本，SideBarContainer 未发现任何 @deprecated 或 @useinstead 标注的 API。

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

- **已有 API 行为变更:** 是
  - API 10+: 侧边栏默认宽度从 200vp 变为 240vp（R-17）
  - API 10+: 最小侧边栏宽度从 200vp 变为 240vp（R-17）
  - API 10+: 最小内容宽度从 0vp 变为 360vp（R-17）
  - API 10+: 控制按钮尺寸从 32vp 变为 24vp（R-11）
  - API 26: 新增 showSideBarWithGesture 属性（R-16）
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** API 8
- **API 版本号策略:** 基础 API @since 8，onChangeEvent @since 9，onSideBarWidthChangeEvent @since 11，showSideBarWithGesture @since 26

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|----------|----------|---------|
| 四种类型单入口 | SideBarContainerType 四种模式共用 SIDE_BAR_ETS_TAG，LayoutAlgorithm 分发不同布局策略 | AC-1.1 ~ AC-1.4 |
| 组件化独立 SO | bridge/ 子目录统一路径，输出 libarkui_side_bar_container.z.so | — |
| AUTO 模式内部切换 | AUTO 模式根据容器宽度自动选择 Embed/Overlay，切换不触发 onChange | AC-1.4 |
| Overlay 手势限制 | showSideBarWithGesture 仅在 Overlay 模式下生效 | AC-6.3 |

> 本节列出本特性 AC 验证必须满足的约束。架构规则适用性及设计方案见 design.md。

## 非性能需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | 侧边栏动画帧率 ≥ 60fps | 手工 + Trace | Trace 打点 |
| 内存 | 分隔线拖拽无内存泄漏 | UT + Dump | 节点树 Dump |
| 安全 | 无安全相关接口 | N/A | — |
| 可靠性 | SideBarContainerType 运行时变更不崩溃 | UT | side_bar 单测 |
| 问题定位 | hilog 标签覆盖关键路径（显示控制、宽度约束） | 代码审查 | — |

> N/A 判定见 proposal.md 不涉及项确认。本节仅为适用项填写具体指标。

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | 无差异 | — | — | — |
| 平板 | AUTO 模式可能选择 Embed（宽度更大） | — | — | — |
| 折叠屏 | 窗口尺寸变化触发 autoHide | OnWindowSizeChanged | UT | — |

---

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 是 | 控制按钮支持焦点导航，SetAccessibilityEvent 注册无障碍事件 | AC-2.3 |
| 大字体 | 否 | SideBarContainer 无字体相关属性 | — |
| 深色模式 | 是 | 颜色属性通过 ResourceColor/Color 支持主题跟随 | AC-5.1 |
| 多窗口/分屏 | 是 | 窗口尺寸变化触发 autoHide | AC-2.6 |
| 多用户 | 否 | 无用户相关状态 | — |
| 版本升级 | 是 | API 10/26 默认值和行为变更需要兼容性处理 | AC-2.4, AC-3.6 |
| 生态兼容 | 是 | C API Modifier 子集需在 NDK 文档中明确 | — |

## 行为场景（Gherkin）

```gherkin
Feature: SideBarContainer 组件
  作为应用开发者
  我想要使用 SideBarContainer 组件实现侧边栏导航
  以便在不同布局场景中展示侧边栏内容

  Scenario: Embed 模式创建
    Given SideBarContainer 以 type=Embed 创建
    When 侧边栏显示 (showSideBar=true)
    Then 侧边栏与内容并列显示
    And 侧边栏宽度从容器宽度中扣除

  Scenario: Overlay 模式创建
    Given SideBarContainer 以 type=Overlay 创建
    When 侧边栏显示 (showSideBar=true)
    Then 侧边栏覆盖在内容之上

  Scenario: DISPLACE 模式创建
    Given SideBarContainer 以 type=DISPLACE 创建
    When 侧边栏显示 (showSideBar=true)
    Then 侧边栏推挤内容区域

  Scenario: AUTO 模式自动切换
    Given SideBarContainer 以 type=AUTO 创建
    When 容器宽度足够大
    Then 使用 Embed 模式
    When 容器宽度不够大
    Then 使用 Overlay 模式

  Scenario: 控制按钮点击切换
    Given SideBarContainer 侧边栏当前为显示状态
    When 用户点击控制按钮
    Then 侧边栏隐藏
    And onChange 回调触发，参数为 false

  Scenario: 分隔线拖拽调整宽度
    Given SideBarContainer 侧边栏宽度为 200vp
    And minSideBarWidth=200, maxSideBarWidth=400
    When 用户拖拽分隔线向右 80vp
    Then 侧边栏宽度变为 280vp
    And onSideBarWidthChangeEvent 回调触发

  Scenario: 分隔线拖拽受约束
    Given SideBarContainer minSideBarWidth=200, maxSideBarWidth=400
    When 用户拖拽分隔线使侧边栏宽度超过 400vp
    Then 侧边栏宽度截断为 400vp

  Scenario: autoHide 自动隐藏
    Given SideBarContainer type=Overlay, autoHide=true, minContentWidth=360
    When 容器宽度变为 300vp (< minContentWidth)
    Then 侧边栏自动隐藏

  Scenario: divider null 隐藏
    Given SideBarContainer 设置 divider=null
    Then 分隔线不显示

  Scenario: 控制按钮图标配置
    Given SideBarContainer 设置 controlButton({ shown: icon_shown, hidden: icon_hidden, switching: icon_switching })
    When 侧边栏显示时
    Then 控制按钮显示 shown 图标
    When 侧边栏隐藏时
    Then 控制按钮显示 hidden 图标

  Scenario Outline: API 版本默认值差异
    Given SideBarContainer 以 <api_version> 创建且未设置侧边栏宽度
    Then 侧边栏默认宽度为 <default_width>

    Examples:
      | api_version | default_width |
      | API 9       | 200vp         |
      | API 10      | 240vp         |

  Scenario: showSideBarWithGesture (API 26)
    Given SideBarContainer type=Overlay, showSideBarWithGesture=true
    When 用户在内容区域滑动手势
    Then 侧边栏显示或隐藏

  Scenario: sideBarPosition RTL 反转
    Given SideBarContainer sideBarPosition=Start 且布局方向为 RTL
    Then 侧边栏位置判定反转
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（做什么/不做什么清晰）
- [x] 无语义模糊表述（"快速""稳定""尽可能"等）
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/ace_engine"
    query: "SideBarContainer 四种类型布局算法分发机制"
  - repo: "openharmony/ace_engine"
    query: "SideBarContainer 控制按钮交互和图标配置"
  - repo: "openharmony/ace_engine"
    query: "SideBarContainer 分隔线拖拽和宽度约束实现"
```

**关键文档:**
- SDK 类型定义: `interface/sdk-js/api/@internal/component/ets/sidebar.d.ts`
- 源码入口: `frameworks/core/components_ng/pattern/side_bar/side_bar_container_pattern.cpp`
- C API 入口: `frameworks/core/interfaces/arkoala/arkoala_api.h:7732`
