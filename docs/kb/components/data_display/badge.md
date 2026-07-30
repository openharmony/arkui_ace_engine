# Badge Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Badge`

## 定位

Badge 是 ArkUI 的标记组件，用于在子组件上附加数字标记、文字标记或圆点标记，常用于显示通知数量、状态标记等场景。行为事实以源码、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主逻辑 | `frameworks/core/components_ng/pattern/badge/badge_pattern.h/cpp` | OnModifyDone、主题更新、Text 子节点管理 |
| Model 层 | `frameworks/core/components_ng/pattern/badge/badge_model_ng.h/cpp` | 动态版属性设置入口 |
| Model 基类 | `frameworks/core/components_ng/pattern/badge/badge_model.h` | Model 声明/实现分层 |
| Layout 属性 | `frameworks/core/components_ng/pattern/badge/badge_layout_property.h/cpp` | 全部属性定义、ToJsonValue |
| Layout 算法 | `frameworks/core/components_ng/pattern/badge/badge_layout_algorithm.h/cpp` | 尺寸计算、位置计算、RTL |
| 数据结构 | `frameworks/core/components_ng/pattern/badge/badge_data.h` | BadgeParameters 定义 |
| Accessibility | `frameworks/core/components_ng/pattern/badge/badge_accessibility_property.h/cpp` | 无障碍 GetText |
| Theme | `frameworks/core/components/badge/badge_theme.h` | 主题资源配置（默认值、老年模式） |
| Theme Wrapper | `frameworks/core/components_ng/pattern/badge/badge_theme_wrapper.h` | TokenTheme 适配 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/badge.d.ts` | Badge 公开 API |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/badge.static.d.ets` | 静态版 API 定义 |
| C API | `interfaces/native/node/native_node_napi.cpp` | 注册为 "arkui.components.arkbadge" |

### API 解析实现路径

Badge **已组件化**（有 `bridge/` 子目录、DynamicModule、统一 Bridge，旧 JSView 已移除）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge | `frameworks/core/components_ng/pattern/badge/bridge/arkts_native_badge_bridge.cpp` | ArkTS Native Bridge，CreateBadge/SetBadgeParamWithNumber/SetBadgeParamWithString |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/badge/bridge/badge_dynamic_modifier.cpp` | 动态属性路径，ArkUIBadgeModifier |
| Static Modifier | `frameworks/core/components_ng/pattern/badge/bridge/badge_static_modifier.cpp` | 静态编译路径，Converter + GENERATED_ArkUIBadgeModifier |
| Custom Modifier | `frameworks/core/components_ng/pattern/badge/bridge/badge_custom_modifier.h` | ArkUIBadgeCustomModifier |
| Dynamic Module | `frameworks/core/components_ng/pattern/badge/bridge/badge_dynamic_module.cpp` | DynamicModule 派生类，入口 OHOS_ACE_DynamicModule_Create_Badge |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/badge/badge_test_ng.cpp` | Pattern/Model 单元测试 |
| 布局测试 | `test/unittest/core/pattern/badge/badge_layout_algorithm_test_ng.cpp` | 布局算法测试 |
| 主题测试 | `test/unittest/core/pattern/badge/badge_withtheme_test_ng.cpp` | 主题更新测试 |
| 序列化测试 | `test/unittest/core/pattern/badge/badge_test_tojson.cpp` | ToJsonValue 测试 |
| 核心测试 | `test/unittest/core/pattern/badge/badge_test_core.cpp` | 核心功能测试 |

### 相关 Spec

- Spec: `specs/05-ui-components/10-information-display-components/09-badge/`
- Design: `specs/05-ui-components/10-information-display-components/09-badge/design.md`
- arkui-specs Specs: `Feat-01-content-modes-spec.md`, `Feat-02-position-layout-spec.md`, `Feat-03-style-theme-aging-spec.md`, `Feat-04-accessibility-componentization-spec.md`
- FuncID: 05-10-09

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Badge 不显示 | badge_pattern.cpp 的 count > 0 和 value 非空判断 |
| 位置偏移 | badge_layout_algorithm.cpp 的位置计算和 RTL 逻辑 |
| 老年模式尺寸不对 | badge_layout_algorithm.cpp 的 fontSizeScale >= 1.75 判断 |
| 主题切换后样式丢失 | badge_pattern.cpp 的 *Byuser 标志判断 |

## 调试入口

- 显示/隐藏调试：`badge_pattern.cpp` 的 `OnModifyDone` 中 count/value 判断
- 位置计算调试：`badge_layout_algorithm.cpp` 的 `Measure` 和 `Layout`
- 主题更新调试：`badge_pattern.cpp` 的 `OnThemeUpdate` 和 *Byuser 标志

## 相关主题

- **Text**: Badge 内部创建 Text 子节点渲染标记内容
- **BadgeTheme**: 提供默认值和老年模式尺寸
- **DynamicModuleHelper**: 组件化动态加载
- **Progress/QRCode/TextClock/TextTimer**: 同属信息展示组件
