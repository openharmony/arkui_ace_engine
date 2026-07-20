# Safe Area Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `SafeArea`

## 定位

Safe Area 是 ArkUI NG 中处理系统安全区域、键盘避让和组件级安全区 padding 的通用布局能力。应用侧主要通过 `expandSafeArea`、`ignoreLayoutSafeArea` 和 `safeAreaPadding` 接入；三者共享安全区数据与布局设施，但进入渲染扩展、布局调度或 padding 约束的路径不同。

本文档合并原 Safe Area Mechanism 与 Ignore Layout Safe Area 两个旧主题，作为唯一的新 KB 路由入口。具体行为、优先级、默认值、API 版本和设备差异应以当前 SDK、源码和测试为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 安全区数据结构 | `frameworks/core/components_ng/property/safe_area_insets.h`、`frameworks/core/components_ng/property/safe_area_insets.cpp` | 系统、导航栏、键盘等安全区数据及选项类型入口 |
| 安全区管理 | `frameworks/core/components_ng/manager/safe_area/safe_area_manager.h`、`frameworks/core/components_ng/manager/safe_area/safe_area_manager.cpp` | Pipeline 范围内的安全区更新、组合和查询入口 |
| 属性存储 | `frameworks/core/components_ng/layout/layout_property.h`、`frameworks/core/components_ng/layout/layout_property.cpp` | SafeAreaExpandOpts、IgnoreLayoutSafeAreaOpts 和 safeAreaPadding 存储入口 |
| 测量与扩展 | `frameworks/core/components_ng/layout/layout_wrapper.h`、`frameworks/core/components_ng/layout/layout_wrapper.cpp` | 安全区参与约束、测量与扩展处理的入口 |
| 忽略布局安全区节点流程 | `frameworks/core/components_ng/base/frame_node.h`、`frameworks/core/components_ng/base/frame_node.cpp` | PreMeasure、ignore layout 标记及节点测量/布局入口 |
| 忽略布局安全区调度 | `frameworks/core/pipeline_ng/ui_task_scheduler.h`、`frameworks/core/pipeline_ng/ui_task_scheduler.cpp` | 延迟任务、遍历、补充测量和布局调度入口 |
| 管线上下文 | `frameworks/core/pipeline_ng/pipeline_context.h`、`frameworks/core/pipeline_ng/pipeline_context.cpp` | 安全区数据更新和调度器接入入口 |
| Dynamic JSView 解析 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | 三类 ArkTS Common 属性的动态声明式解析入口 |
| ArkTS Common Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | AttributeModifier 和 FrameNode 动态属性解析入口 |
| Common node modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Common Bridge 的 native 设置、重置和查询入口 |
| Static Common modifier | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static ArkTS 的 safeAreaPadding、expandSafeArea 和 ignoreLayoutSafeArea 类型转换与属性写入入口 |
| Native 公共接口 | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/native_node.h` | 已公开 Node 属性的枚举与分发入口 |
| OHOS 窗口接入 | `adapter/ohos/entrance/ui_content_impl.cpp`、`adapter/ohos/osal/page_viewport_config_ohos.h`、`adapter/ohos/osal/page_viewport_config_ohos.cpp` | 窗口避让区、键盘区域和 viewport 配置进入 ArkUI 的平台入口 |

按能力分流：

| 能力 | 优先检索 |
|------|----------|
| 渲染安全区扩展 | `expandSafeArea`、`SafeAreaExpandOpts`、`ExpandSafeArea` |
| 忽略布局安全区 | `ignoreLayoutSafeArea`、`IgnoreLayoutSafeAreaOpts`、`PreMeasure`、`TraverseForIgnore`、`PostponedTaskForIgnore` |
| 组件安全区 padding | `safeAreaPadding`、`SafeAreaPadding`、`safeAreaPadding_` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `expandSafeArea`、`ignoreLayoutSafeArea`、`safeAreaPadding` 及相关枚举声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 ArkTS 对应属性和枚举声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Common Modifier 类型入口；具体方法回到 CommonAttribute 核实 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Common Modifier 类型入口；具体方法回到静态 Common API 核实 |
| Node C API | `interfaces/native/native_node.h`、`interfaces/native/node/style_modifier.cpp` | 已核实公开 `NODE_EXPAND_SAFE_AREA` 与 `NODE_IGNORE_LAYOUT_SAFE_AREA`；未核实 `safeAreaPadding` 的同等公开枚举 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口避让区和显示信息 | `adapter/ohos/entrance/ui_content_impl.cpp`、`adapter/ohos/osal/page_viewport_config_ohos.cpp`、`adapter/ohos/osal/page_viewport_config_ohos.h` | `<OH_ROOT>/foundation/window/window_manager/` | `<OH_ROOT>/foundation/window/window_manager/interfaces/innerkits/wm/`、`window_manager:libwm`、`window_manager:libdm` | 消费窗口 AvoidArea、键盘矩形和显示配置并更新 ArkUI 安全区 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Safe Area 布局测试 | `test/unittest/core/layout/safe_area/` | expand、ignore、延迟调度与安全区布局回归 |
| SafeAreaManager 测试 | `test/unittest/core/manager/safe_area_manager_test_ng.cpp`、`test/unittest/core/manager/safe_area_manager_test_ng_part_two.cpp` | 安全区管理、合并和更新回归 |
| Common 属性测试 | `test/unittest/core/layout/`、`test/unittest/capi/modifiers/` | safeAreaPadding 与已公开 native 属性的相关回归入口 |
| Context registry | `docs/context_registry.json` | `SafeArea` 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

功能注册为 `04-02-01`，目标功能域为 `specs/04-common-capability/02-safe-area/01-safe-area-mechanism/`。当前 Spec 目录尚未建立，因此 registry 标记为 `pending`；在 Spec 补齐前，行为事实以 SDK、源码和测试为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 系统栏或键盘安全区没有更新 | OHOS 窗口接入、`PipelineContext`、`SafeAreaManager` 和 manager 测试 |
| expandSafeArea 未扩展显示区域 | SDK 声明、JSView/Common Bridge、LayoutProperty、LayoutWrapper 与 expand 测试 |
| ignoreLayoutSafeArea 未改变布局范围 | `IgnoreLayoutSafeAreaOpts`、FrameNode PreMeasure、UITaskScheduler ignore 调度与 ignore 测试 |
| safeAreaPadding 未进入约束 | Common API、Dynamic Common Bridge 或 Static Common modifier、LayoutProperty 和通用布局测试 |
| ArkTS 与 C API 能力不对称 | 回到 `native_node.h` 核实具体枚举；不得由 ArkTS API 推断存在公开 Node C API |
| 不同窗口或折叠设备表现不同 | 平台 viewport/窗口适配入口、Window Manager 数据和目标设备测试 |
| 与普通 padding、position 同时使用时异常 | 分别核对 Layout Attributes、Safe Area 属性存储和组件布局算法，不在 KB 中假定统一优先级 |

## 调试入口

- 先确认窗口侧 AvoidArea、键盘矩形和 viewport 配置是否进入 `PipelineContext`。
- 在 `SafeAreaManager` 检查当前安全区数据，再进入节点 `LayoutProperty` 确认具体选项是否写入。
- ignoreLayoutSafeArea 问题沿 FrameNode PreMeasure 和 UITaskScheduler 的 ignore 调度关键字定位。
- 布局现场同时观察父约束、safe area insets、safeAreaPadding 与 GeometryNode 结果。
- 回归优先运行 `test/unittest/core/layout/safe_area/` 和 SafeAreaManager 定向用例。

## 相关主题

- 布局框架：`docs/kb/architecture/layout-framework.md`
- 布局属性：`docs/kb/capabilities/layout-attributes.md`
- 安全区功能域（待补）：`specs/04-common-capability/02-safe-area/01-safe-area-mechanism/`
