# ThemeLayeredAccess Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ThemeLayeredAccess`

## 定位

ArkUI 主题分层访问通过 ThemeManager 单例管理四级主题解析：TokenTheme scope → Kit 主题 → Origin 主题 → ResourceAdapter 回退。ThemeConstants 提供颜色/字号缓存，TokenThemeStorage 为全局单例。

本文档用于快速定位 Theme Layered Access 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| theme_manager | `frameworks/core/components/theme/theme_manager.h` | |
| theme_manager_impl | `frameworks/core/components/theme/theme_manager_impl.cpp` | |
| theme_constants | `frameworks/core/components/theme/theme_constants.h` | |
| theme_constants_impl | `frameworks/core/components/theme/theme_constants.cpp` | |
| theme_attributes | `frameworks/core/components/theme/theme_attributes.h` | |
| theme_style | `frameworks/core/components/theme/theme_style.h` | |
| token_theme_storage | `frameworks/core/components_ng/token_theme/token_theme_storage.cpp` | |
| token_theme_wrapper | `frameworks/core/components_ng/token_theme/token_theme_wrapper.h` | |
| token_theme | `frameworks/core/components_ng/token_theme/token_theme.h` | |
| token_colors | `frameworks/core/components_ng/token_theme/token_colors.h` | |
| inner_api_token_theme | `interfaces/inner_api/ace_kit/include/ui/view/theme/token_theme.h` | |
| inner_api_token_theme_wrapper | `interfaces/inner_api/ace_kit/include/ui/view/theme/token_theme_wrapper.h` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| resource_manager | `<OH_ROOT>/interface/sdk-js/api/@ohos.resourceManager.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/manager/theme_manager_test_ng.cpp | |
| test/unittest/core/manager/theme_test.cpp | |
| test/unittest/interfaces/ace_kit/token_theme_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/03-engine-framework/03-resource-theme/02-theme-layered-access/` | 主题分层访问机制，四级主题解析链路（TokenTheme → Kit → Origin → ResourceAdapter），支持深色/浅色模式。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 主题颜色不生效 | 确认 ThemeManager::GetTheme() 返回的 ThemeConstants 链路；检查 TokenThemeStorage 缓存 |
| 深色模式颜色不切换 | 查看 ColorMode 通知链路和 ThemeConstants 的 dark/light 缓存 |

## 调试入口

- 主题链路：ThemeManager → GetThemeKit/GetThemeOrigin/GetThemeNormal
- Token 缓存：TokenThemeStorage::themeCache_ 单例

## 相关主题

- [资源访问](resource-access.md)
- [Theme框架](theme-framework.md)
- [资源动态切换](resource-dynamic-switching.md)