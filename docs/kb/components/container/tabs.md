# Tabs Context

> 文档版本：v1.0
> 更新时间：2026-07-08
> 来源：`docs/context_registry.json` 主题 `Tabs`

## 定位

Tabs 是 ArkUI 的标签页容器组件，面向应用侧提供 TabBar/TabContent 页签切换、自定义标签栏样式、标签动画、子标签管理和控制器等能力。Tabs 与 TabContent 构成标签页体系的核心组件组合。

本文档用于快速定位 Tabs 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、标签切换、动画 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.cpp` | Tabs 核心行为实现入口 |
| Pattern 类型和扩展接口 | `frameworks/core/components_ng/pattern/tabs/tabs_pattern.h` | `TabsPattern` 类型声明 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp` | 动态前端 Tabs 创建和属性写入 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/tabs/tabs_model_static.cpp` | 静态前端 Tabs 属性写入 |
| 布局属性 | `frameworks/core/components_ng/pattern/tabs/tabs_layout_property.h` | Tabs 布局属性声明 |
| 布局算法 | `frameworks/core/components_ng/pattern/tabs/tabs_layout_algorithm.cpp` | Tabs 布局计算逻辑 |
| 控制器 | `frameworks/core/components_ng/pattern/tabs/tabs_controller.h` | Tabs 控制器能力入口 |
| Tabs Node | `frameworks/core/components_ng/pattern/tabs/tabs_node.cpp` | Tabs FrameNode 定义 |
| TabBar Pattern | `frameworks/core/components_ng/pattern/tabs/tab_bar_pattern.cpp` | TabBar 核心行为 |
| TabBar Layout | `frameworks/core/components_ng/pattern/tabs/tab_bar_layout_algorithm.cpp` | TabBar 布局计算 |
| TabBar Modifier/Paint | `frameworks/core/components_ng/pattern/tabs/tab_bar_modifier.cpp`、`tab_bar_paint_method.cpp` | TabBar 绘制和内容修改器 |
| TabContent Pattern | `frameworks/core/components_ng/pattern/tabs/tab_content_pattern.cpp` | TabContent 核心行为 |
| TabContent Model | `frameworks/core/components_ng/pattern/tabs/tab_content_model_ng.cpp` | TabContent 动态前端创建 |
| TabContent Static Model | `frameworks/core/components_ng/pattern/tabs/tab_content_model_static.cpp` | TabContent 静态前端属性写入 |
| TabContent 事件 | `frameworks/core/components_ng/pattern/tabs/tab_content_event_hub.h` | TabContent 事件回调 |
| TabContent Transition | `frameworks/core/components_ng/pattern/tabs/tab_content_transition_proxy.h` | TabContent 转场代理 |
| 主题 | `frameworks/core/components_ng/pattern/tabs/tab_theme_wrapper.h` | Tabs 主题包装 |
| 多线程 Pattern 扩展 | `frameworks/core/components_ng/pattern/tabs/tab_bar_pattern_multi_thread.cpp` | 多线程场景 TabBar 实现 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/tabs.d.ts` | 动态 ArkTS Tabs/TabContent 接口声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/tabs.static.d.ets` | 静态 ArkTS Tabs/TabContent 声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/TabsModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/TabsModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | 无 | Tabs 当前无独立 C API 节点类型 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `TabsAttribute`、`TabContentAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `TabsInterface`、`TabContentInterface`。
- Modifier：在 `TabsModifier*.d.ts` 中确认继承或实现关系。

### API 解析实现路径

Tabs 当前未完成组件化改造（无 `bridge/` 子目录、JSView 文件仍存在）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_tabs.cpp` | `JSTabs::SetXxx()` → `TabsModel::GetInstance()->SetXxx()` |
| JSView（TabContent） | `frameworks/bridge/declarative_frontend/jsview/js_tab_content.cpp` | `JSTabContent::SetXxx()` → `TabContentModel::GetInstance()->SetXxx()` |
| JSView（Controller） | `frameworks/bridge/declarative_frontend/jsview/js_tabs_controller.cpp` | TabsController JS 侧桥接 |
| JSView（Feature） | `frameworks/bridge/declarative_frontend/jsview/js_tabs_feature.cpp` | TabsFeature JS 侧桥接 |
| ArkTS Bridge（动态属性） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_tabs_bridge.cpp` | Bridge → ModelNG |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/tabs_modifier.ts` | ArkTS Tabs Modifier 类 |

组件化改造参考：改造后 JSView 和 Bridge 双路径将统一到 `pattern/tabs/bridge/`，并输出独立 so。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Tabs/TabBar/TabContent 单元测试 | `test/unittest/core/pattern/tabs/` | Tabs 组件族 Pattern、Model、Layout、Event、Accessibility 测试 |

### 相关 Spec

| ID | 主题 | Spec 路径 | 状态 |
|----|------|-----------|------|
| 05-03-09 | Tabs/TabContent | `specs/05-ui-components/03-scroll-container-components/09-tabs-tab-content/` | active |

Design 文档：`specs/05-ui-components/03-scroll-container-components/09-tabs-tab-content/design.md`

| Feat-ID | 标题 | 覆盖范围 | 状态 |
|---------|------|----------|------|
| Feat-01 | 创建与基础属性 | Tabs/TabContent/TabsController 创建, vertical, scrollable, barMode, barWidth/Height, animationDuration, animationMode | Baselined |
| Feat-02 | 标签栏样式 | SubTabBarStyle, BottomTabBarStyle, TabBarSymbol, indicator/board/labelStyle | Baselined |
| Feat-03 | 侧边栏模式 | barStyle, sidebarWidth, sidebarBackgroundColor, showSideBar | Baselined |
| Feat-04 | 动画与自定义过渡 | customContentTransition, TabContentAnimatedTransition | Baselined |
| Feat-05 | 事件回调 | onChange, onSelected, onAnimationStart/End | Baselined |
| Feat-06 | 缓存与滚动控制 | cachedMaxCount, nestedScroll, preloadItems | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 标签切换动画异常 | `tabs_pattern.cpp` 中动画触发逻辑，`tab_content_transition_proxy.h` |
| TabBar 布局/样式异常 | `tab_bar_layout_algorithm.cpp`、`tab_bar_modifier.cpp`、`tab_bar_paint_method.cpp` |
| TabContent 内容不显示 | `tab_content_pattern.cpp` 中内容绑定逻辑 |
| 控制器切换不生效 | `tabs_controller.h`、`tabs_pattern.cpp` 中控制器联动 |
| 滑动切换与 Swiper 联动 | Tabs 内嵌 Swiper 实现，`tabs_pattern.cpp` 中 Swiper 交互 |
| 多线程场景标签渲染 | `tab_bar_pattern_multi_thread.cpp` |

## 调试入口

- Tabs 属性搜索：在源码中 grep `TabsPattern`、`TabsModel`、`TabsLayoutProperty`
- TabBar 属性搜索：grep `TabBarPattern`、`TabBarLayoutAlgorithm`、`TabBarModifier`
- TabContent 属性搜索：grep `TabContentPattern`、`TabContentModel`、`TabContentEventHub`
- 事件关键字：grep `TabsEventHub`、`TabContentEventHub`

## 相关主题

- TabContent：`frameworks/core/components_ng/pattern/tabs/tab_content_pattern.cpp`
- TabBar：`frameworks/core/components_ng/pattern/tabs/tab_bar_pattern.cpp`
- Swiper：Tabs 内嵌 Swiper 实现标签页滑动切换，详见 Swiper KB
- Divider：TabBar 使用 Divider 布局属性
