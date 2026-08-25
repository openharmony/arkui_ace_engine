# Progress Context

> 文档版本：v1.1
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Progress`

## 定位

Progress 是 ArkUI 信息展示类组件中的进度条组件（FuncID 05-10-05），用于显示操作完成比例。当前源码按组件化路径组织，公共契约以 SDK 声明为准，行为定位需要继续回读 ace_engine 的 Pattern、Model、Layout、Paint、bridge、C API 和测试。

本页只提供路由入口，不复制长期规格中的 AC/规则矩阵。具体行为基线见 `specs/05-ui-components/10-information-display-components/05-progress/Feat-01-progress-full-spec.md`。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern | `frameworks/core/components_ng/pattern/progress/progress_pattern.cpp` | 生命周期、交互、可见区动画、主题/语言更新、隐私文本遮蔽、Inspector/Dump。 |
| Model NG | `frameworks/core/components_ng/pattern/progress/progress_model_ng.cpp` | 动态范式创建和属性写入。 |
| Model Static | `frameworks/core/components_ng/pattern/progress/progress_model_static.cpp` | 静态范式 options、style、Text 子节点和属性写入。 |
| Layout | `frameworks/core/components_ng/pattern/progress/progress_layout_algorithm.cpp` | 各类型尺寸测量、API 版本分支、Capsule 文本布局。 |
| Paint Method | `frameworks/core/components_ng/pattern/progress/progress_paint_method.cpp` | PaintWrapper 到 ProgressModifier 的绘制态同步。 |
| Modifier | `frameworks/core/components_ng/pattern/progress/progress_modifier.cpp` | Linear/Ring/ScaleRing/Eclipse/Capsule 绘制、渐变、扫光、loading、RTL。 |
| Properties | `frameworks/core/components_ng/pattern/progress/progress_layout_property.h`、`progress_paint_property.h` | 布局态和绘制态字段。 |
| Data types | `frameworks/core/components_ng/pattern/progress/progress_date.h` | ProgressType、ProgressStatus、ProgressConfiguration 等内部类型。 |
| Accessibility | `frameworks/core/components_ng/pattern/progress/progress_accessibility_property.h` | range/value/text 无障碍入口。 |
| Theme | `frameworks/core/components_ng/pattern/progress/progress_theme_wrapper.h` | Progress token/theme 映射。 |
| Build | `frameworks/core/components_ng/pattern/progress/BUILD.gn` | 组件化构建和 bridge 源文件收口。 |
| C API option | `interfaces/native/node/progress_option.h`、`interfaces/native/node/progress_option.cpp` | `OH_ArkUI_ProgressLinearStyleOption_*`。 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/progress.d.ts` | 动态 `Progress`、`ProgressType`、`ProgressStatus`、style options、`contentModifier`、`privacySensitive`。 |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/progress.static.d.ets` | 静态 `Progress`、Builder 形式、`setProgressOptions`。 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/ProgressModifier.d.ts` | 动态 AttributeModifier 声明。 |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/ProgressModifier.static.d.ets` | 静态 AttributeModifier 声明。 |
| C API | `interfaces/native/node/progress_option.h` | Linear style option NDK 接口。 |

### API 解析实现路径

Progress 已完成组件化改造，优先走 `frameworks/core/components_ng/pattern/progress/bridge/` 下的统一解析路径。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 组件化标记 | `frameworks/core/components_ng/pattern/progress/BUILD.gn` | `progress_pattern_ng` 使用组件化构建。 |
| 动态模块加载 | `adapter/ohos/osal/dynamic_module_helper.cpp` | Progress 注册到动态模块映射。 |
| 统一 Bridge | `frameworks/core/components_ng/pattern/progress/bridge/arkts_native_progress_bridge.cpp` | 声明式和动态属性解析入口。 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/progress/bridge/progress_dynamic_modifier.cpp` | 动态属性转发到 Model/Property。 |
| Static Modifier | `frameworks/core/components_ng/pattern/progress/bridge/progress_static_modifier.cpp` | 静态编译范式属性转换。 |
| Dynamic Module | `frameworks/core/components_ng/pattern/progress/bridge/progress_dynamic_module.cpp` | `OHOS_ACE_DynamicModule_Create_Progress` 模块入口。 |
| Custom Modifier | `frameworks/core/components_ng/pattern/progress/bridge/progress_custom_modifier.h` | contentModifier 自定义内容路径。 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 主题系统 | `frameworks/core/components_ng/pattern/progress/progress_theme_wrapper.h` | ace_engine 内部主题模块 | `frameworks/core/components/progress/progress_theme.h` | Progress 默认颜色、尺寸、Capsule 交互色。 |
| Text 子节点 | `frameworks/core/components_ng/pattern/progress/progress_model_static.cpp` | ace_engine Text 组件 | `frameworks/core/components_ng/pattern/text/` | Capsule 内部文本内容和字体样式。 |
| 资源解析 | `frameworks/core/components_ng/pattern/progress/bridge/arkts_native_progress_bridge.cpp` | ace_engine 资源系统 | `frameworks/core/common/resource/` | ResourceColor、ResourceStr、Length 资源转换。 |
| 无障碍 | `frameworks/core/components_ng/pattern/progress/BUILD.gn` | accessibility | `accessibility_common` | 条件依赖，用于无障碍能力。 |
| UI 事件上报 | `frameworks/core/components_ng/pattern/progress/progress_pattern.cpp` | inner_api | `interfaces/inner_api/ui_session/` | Progress value 到达状态相关上报。 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Core unit | `test/unittest/core/pattern/progress/` | Pattern、Layout、Paint、Modifier、ContentModifier、Builder、ToJson。 |
| C API modifier | `test/unittest/capi/modifiers/progress_modifier_test.cpp` | Native/静态 modifier 入参和属性写入。 |
| C API generated modifier | `test/unittest/capi/modifiers/generated/progress_modifier_test.cpp` | generated modifier 覆盖。 |
| C API accessor | `test/unittest/capi/accessors/progress_content_modifier_accessor_test.cpp`、`progress_mask_accessor_test.cpp` | content modifier 和隐私/遮蔽相关 accessor。 |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 长期规格 | `specs/05-ui-components/10-information-display-components/05-progress/Feat-01-progress-full-spec.md` | 本次补录的 Progress 全量长期规格。 |
| 设计基线 | `specs/05-ui-components/10-information-display-components/05-progress/design.md` | Progress 功能域共享设计基线。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| value/total 截断或百分比文本异常 | `progress_model_ng.cpp`、`progress_model_static.cpp`、`progress_paint_property.h` |
| Linear/Ring/Capsule 样式不生效 | `arkts_native_progress_bridge.cpp`、`progress_dynamic_modifier.cpp`、`progress_static_modifier.cpp` |
| Capsule 文本、焦点、悬停、按压异常 | `progress_pattern.cpp`、`progress_model_static.cpp` |
| 渐变、扫光、loading 或 RTL 绘制异常 | `progress_modifier.cpp`、`progress_paint_method.cpp` |
| 隐私模式遮蔽异常 | `progress_pattern.cpp`、`progress_paint_method.h`、`progress_mask_accessor_test.cpp` |
| C API Linear style option 异常 | `interfaces/native/node/progress_option.cpp`、`test/unittest/capi/modifiers/progress_modifier_test.cpp` |
| 静态 Progress 或 Builder 异常 | `progress.static.d.ets`、`progress_static_modifier.cpp`、generated modifier 单测 |

## 调试入口

- Inspector/ToJson：查看 Progress type、value、style、ringStyle、linearStyle、capsuleStyle、enableSmoothEffect、privacySensitive 等字段。
- Dump：查看 Progress value、maxValue、color、strokeWidth、scaleCount、scaleWidth、smooth/scan 相关字段。
- Accessibility：查看 range、current value 和 text。
- 构建定位：从 `frameworks/core/components_ng/pattern/progress/BUILD.gn` 确认组件化源文件是否纳入目标。

## 相关主题

- [LoadingProgress：独立加载进度组件，和 Progress 同属信息展示但源码路径不同。](loading-progress.md)
- [Gauge：独立仪表盘组件，不应与 Progress 内部 Eclipse/Moon 命名混淆。](gauge.md)
- [Text：Capsule 内部 Text 子节点的文本布局和样式承载方。](../basic/text.md)
- ContentModifier：Progress 自定义内容机制所在的通用扩展能力。
- Theme/TokenTheme：Progress 默认颜色、尺寸和交互态取值来源。