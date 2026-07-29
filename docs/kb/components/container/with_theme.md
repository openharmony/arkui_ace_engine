# WithTheme Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `WithTheme`

## 定位

ArkUI WithTheme 是主题作用域语法组件，通过 WithThemeNode 管理子树的主题覆盖。WithThemeNode 是 Syntax 节点（非 Pattern 组件），在子树构建时注入 ThemeApply 上下文。C API 暴露为 with_theme_modifier。

本文档用于快速定位 WithTheme 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| with_theme_node | `frameworks/core/components_ng/syntax/with_theme_node.cpp` | |
| with_theme_node_h | `frameworks/core/components_ng/syntax/with_theme_node.h` | |
| node_modifier | `frameworks/core/interfaces/native/implementation/with_theme_modifier.cpp` | |
| js_with_theme | `frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_with_theme.cpp` | |
| js_with_theme_h | `frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_with_theme.h` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/with_theme.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/pattern/withtheme/withtheme_test_ng.cpp | |
| test/unittest/core/pattern/withtheme/withtheme_test_core.cpp | |

### API 解析实现路径

WithTheme 是语法节点，不涉及 Pattern/Bridge/Modifier 路径。通过 WithThemeNode 管理主题作用域。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 语法节点 | `frameworks/core/components_ng/syntax/with_theme_node.cpp` | WithThemeNode 语法节点实现 |
| 声明式前端 | `frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_with_theme.cpp` | JS WithTheme 组件 |
| C API | `frameworks/core/interfaces/native/implementation/with_theme_modifier.cpp` | with_theme_modifier |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/05-ui-components/15-theme-components/01-with-theme/` | WithTheme 主题作用域组件，语法节点 WithThemeNode 管理主题覆盖范围。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 主题覆盖不生效 | 确认 WithThemeNode 的 ThemeApply 上下文注入 |
| 子组件主题不更新 | 检查 WithThemeNode 的通知机制和子树刷新 |

## 调试入口

- 构建链路：WithThemeNode → 子树构建时注入 ThemeApply
- C API 链路：with_theme_modifier.cpp

## 相关主题

- Theme框架
- 主题分层访问
- UIAppearance
