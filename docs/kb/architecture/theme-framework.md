# ThemeFramework Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ThemeFramework`

## 定位

ArkUI Theme 框架以 ThemeManager 为核心，采用双轨注册（THEME_BUILDERS 静态 + THEME_BUILDERS_KIT 动态）和三级缓存（themes_ + themeWrappersLight_/Dark_ + TokenThemeStorage::themeCache_）。AppTheme 和 ThemeFactory 提供主题创建与样式管理。

本文档用于快速定位 Theme Framework 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| theme_manager | `frameworks/core/components/theme/theme_manager.h` | |
| theme_manager_impl | `frameworks/core/components/theme/theme_manager_impl.cpp` | |
| theme_constants | `frameworks/core/components/theme/theme_constants.h` | |
| app_theme | `frameworks/core/components/theme/app_theme.h` | |
| app_theme_impl | `frameworks/core/components/theme/app_theme.cpp` | |
| theme_utils | `frameworks/core/components/theme/theme_utils.h` | |
| theme_utils_impl | `frameworks/core/components/theme/theme_utils.cpp` | |
| ui_material_theme | `frameworks/core/components/theme/ui_material_theme.h` | |
| ui_material_theme_impl | `frameworks/core/components/theme/ui_material_theme.cpp` | |
| icon_theme | `frameworks/core/components/theme/icon_theme.h` | |
| inner_api_theme | `interfaces/inner_api/ace_kit/include/ui/view/theme/theme.h` | |
| inner_api_theme_factory | `interfaces/inner_api/ace_kit/include/ui/view/theme/theme_factory.h` | |
| inner_api_theme_style | `interfaces/inner_api/ace_kit/include/ui/view/theme/theme_style.h` | |
| theme_factory_impl | `interfaces/inner_api/ace_kit/src/view/theme/theme_factory.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 无 | — | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/manager/theme_manager_test_ng.cpp | |
| test/unittest/core/manager/theme_test.cpp | |
| test/unittest/interfaces/ace_kit/token_theme_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/03-engine-framework/03-resource-theme/03-theme-framework/` | Theme 框架核心，包括 ThemeManager 双轨注册（静态 + Kit 动态）、三级缓存、AppTheme 和 ThemeFactory。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 自定义主题不生效 | 确认 ThemeManager 注册链路 THEME_BUILDERS / THEME_BUILDERS_KIT |
| 主题缓存不一致 | 查看三级缓存 themes_ / themeWrappers_ / themeCache_ 的刷新逻辑 |

## 调试入口

- 注册链路：ThemeManager 的 THEME_BUILDERS 和 THEME_BUILDERS_KIT map
- 缓存链路：三级缓存刷新策略

## 相关主题

- 主题分层访问
- 资源访问
- WithTheme 组件
