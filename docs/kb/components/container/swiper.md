# Swiper Context

> 文档版本：v1.0
> 更新时间：2026-07-08
> 来源：`docs/context_registry.json` 主题 `Swiper`

## 定位

Swiper 是 ArkUI 的轮播容器组件，面向应用侧提供自动播放、手势滑动、指示器、箭头导航、循环播放、自定义转场动画、弧形轮播等能力。Swiper 是 Tabs 标签页切换的底层滑动引擎。

本文档用于快速定位 Swiper 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、滑动、动画、手势 | `frameworks/core/components_ng/pattern/swiper/swiper_pattern.cpp` | Swiper 核心行为实现入口 |
| Pattern 类型和扩展接口 | `frameworks/core/components_ng/pattern/swiper/swiper_pattern.h` | `SwiperPattern` 类型声明 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/swiper/swiper_model_ng.cpp` | 动态前端 Swiper 创建和属性写入 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/swiper/swiper_model_static.cpp` | 静态前端 Swiper 属性写入 |
| 布局属性 | `frameworks/core/components_ng/pattern/swiper/swiper_layout_property.h` | Swiper 布局属性声明 |
| 布局算法 | `frameworks/core/components_ng/pattern/swiper/swiper_layout_algorithm.cpp` | Swiper 布局计算逻辑 |
| 绘制 | `frameworks/core/components_ng/pattern/swiper/swiper_paint_method.cpp` | Swiper 绘制逻辑 |
| 绘制属性 | `frameworks/core/components_ng/pattern/swiper/swiper_paint_property.cpp` | Swiper 绘制属性 |
| 事件存储 | `frameworks/core/components_ng/pattern/swiper/swiper_event_hub.cpp` | Swiper 事件回调 |
| Helper | `frameworks/core/components_ng/pattern/swiper/swiper_helper.cpp` | Swiper 辅助工具类 |
| 弧形 Swiper Pattern | `frameworks/core/components_ng/pattern/swiper/arc_swiper_pattern.cpp` | ArcSwiper 弧形轮播实现 |
| 转场代理 | `frameworks/core/components_ng/pattern/swiper/swiper_content_transition_proxy.h` | Swiper 转场动画代理 |
| UI 会话适配 | `frameworks/core/components_ng/pattern/swiper/swiper_ui_session_adapter.cpp` | Swiper UI 会话信息上报 |
| 主题 | `frameworks/core/components_ng/pattern/swiper/swiper_theme.cpp` | Swiper 主题实现 |
| C API Modifier 层 | `frameworks/core/interfaces/native/node/node_swiper_modifier.cpp` | C++ Set/Reset/Get，Bridge 和 C API 共用 |
| C API 选项 | `interfaces/native/node/swiper_option.cpp` | Swiper C API 选项实现 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/swiper.d.ts` | 动态 ArkTS Swiper 接口声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/swiper.static.d.ets` | 静态 ArkTS Swiper 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SwiperModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SwiperModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_SWIPER`、`NODE_SWIPER_*` 属性和事件枚举 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `SwiperAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `SwiperInterface` 或 `Swiper(`。
- Modifier：在 `SwiperModifier*.d.ts` 中确认继承或实现关系。
- C API：在 `native_node.h` 中搜索 `NODE_SWIPER_`、`ARKUI_NODE_SWIPER`。

### API 解析实现路径

Swiper 当前未完成组件化改造（无 `bridge/` 子目录、JSView 文件仍存在）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_swiper.cpp` | `JSSwiper::SetXxx()` → `SwiperModel::GetInstance()->SetXxx()` |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_swiper_bridge.cpp` | Bridge → node_modifier → ModelNG |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_swiper_modifier.cpp` | C++ Set/Reset/Get，Bridge 和 C API 共用 |
| C API（NDK） | `interfaces/native/native_node.h`、`interfaces/native/node/swiper_option.cpp` | 有 C API 枚举和选项，走通用 style_modifier 框架 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/swiper_modifier.ts` | ArkTS Swiper Modifier 类 |

组件化改造参考：改造后 JSView 和 Bridge 双路径将统一到 `pattern/swiper/bridge/`，并输出独立 so。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Swiper/ArcSwiper/指示器 单元测试 | `test/unittest/core/pattern/swiper/` | Swiper Pattern、Model、Layout、Animation、Accessibility、指示器测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-03-08 | Swiper | `specs/05-ui-components/03-scroll-container-components/08-swiper/` | active |

Design 文档：`specs/05-ui-components/03-scroll-container-components/08-swiper/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 创建与布局属性 | Swiper创建, loop, vertical, displayMode, displayCount, itemSpace, margins, index | Baselined |
| Feat-02 | 自动播放与指示器 | autoPlay, interval, indicator, DotIndicator/DigitIndicator, displayArrow | Baselined |
| Feat-03 | 动画与过渡 | duration, curve, effectMode, customContentTransition, pageFlipMode | Baselined |
| Feat-04 | 交互与控制器 | disableSwipe, nestedScroll, SwiperController, fakeDrag | Baselined |
| Feat-05 | 事件回调 | onChange, onAnimationStart/End, onGestureSwipe | Baselined |
| Feat-06 | C API 全量规格 | NODE_SWIPER_* 属性/事件, SwiperIndicator/DigitIndicator/ArrowStyle C API | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 滑动/手势不响应 | `swiper_pattern.cpp` 中手势识别和触摸处理逻辑 |
| 自动播放异常 | `swiper_pattern.cpp` 中定时器管理和动画触发 |
| 循环播放/无限循环异常 | `swiper_pattern.cpp` 中循环计算逻辑 |
| 指示器样式/布局异常 | `swiper_paint_method.cpp`、指示器布局算法 |
| 弧形轮播异常 | `arc_swiper_pattern.cpp` |
| 转场动画异常 | `swiper_content_transition_proxy.h` |
| C API 属性设置无效 | `node_swiper_modifier.cpp` 中 Set/Reset 逻辑 |
| 布局溢出/间距异常 | `swiper_layout_algorithm.cpp` |
| 多线程场景渲染 | `swiper_pattern_multi_thread.cpp` |

## 调试入口

- Swiper 属性搜索：在源码中 grep `SwiperPattern`、`SwiperModel`、`SwiperLayoutProperty`
- 指示器关键字：grep `SwiperIndicator`、`DotIndicator`、`DigitIndicator`
- 弧形轮播关键字：grep `ArcSwiperPattern`、`ArcSwiperIndicator`
- 事件关键字：grep `SwiperChangeEvent`、`SwiperEventHub`
- C API 关键字：grep `NODE_SWIPER_`、`ARKUI_NODE_SWIPER`

## 相关主题

- Tabs：Tabs 使用 Swiper 作为底层滑动引擎，详见 Tabs KB
- ArcSwiper：`frameworks/core/components_ng/pattern/swiper/arc_swiper_pattern.cpp`
