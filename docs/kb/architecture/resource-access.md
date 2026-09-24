# ResourceAccess Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ResourceAccess`

## 定位

ArkUI 资源访问机制负责 `$r` / `$rawfile` 表达式解析、资源查找与缓存。核心链路：JS 层 `$r` → ResourceObject 构建 → ResourceManager::GetOrCreateResourceAdapter → ResourceAdapter 实现资源查找。

本文档用于快速定位 Resource Access 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| resource_manager | `frameworks/core/common/resource/resource_manager.h` | |
| resource_manager_impl | `frameworks/core/common/resource/resource_manager.cpp` | |
| resource_object | `frameworks/core/common/resource/resource_object.h` | |
| resource_parse_utils | `frameworks/core/common/resource/resource_parse_utils.h` | |
| pattern_resource_manager | `frameworks/core/common/resource/pattern_resource_manager.h` | |
| resource_configuration | `frameworks/core/common/resource/resource_configuration.h` | |
| resource_adapter | `frameworks/core/components/theme/resource_adapter.h` | |
| resource_adapter_impl | `adapter/ohos/osal/resource_adapter_impl.cpp` | |
| resource_adapter_impl_v2 | `adapter/ohos/osal/resource_adapter_impl_v2.cpp` | |
| resource_adapter_preview | `adapter/preview/osal/resource_adapter_impl.cpp` | |
| inner_api_resource_object | `interfaces/inner_api/ace_kit/include/ui/resource/resource_object.h` | |
| inner_api_resource_parser | `interfaces/inner_api/ace_kit/include/ui/resource/resource_parser.h` | |
| bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_resource_bridge.cpp` | |
| arkts_utils | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.cpp` | |
| js_view_abstract | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/units.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/core/common/resource/resource_manager_test.cpp | |
| test/unittest/core/common/resource/resource_parse_utils_test_ng.cpp | |
| test/unittest/core/common/resource/pattern_resource_manager_test.cpp | |
| test/unittest/interfaces/ace_kit/resource_parser_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/03-engine-framework/03-resource-theme/01-resource-access/` | 资源访问内部机制，包括 `$r`/`$rawfile` 解析、ResourceManager 单例、ResourceAdapter 适配层和 PatternResourceManager。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 资源不生效 | 确认 `$r` 路径与 resources 目录结构匹配；检查 ResourceAdapter 实现 |
| 暗色模式资源未切换 | 查看 ResourceManager 配置更新链路和 ColorMode 通知 |

## 调试入口

- 资源链路：从 `js_view_abstract.cpp` 的 `$r` 解析跟踪到 ResourceManager → ResourceAdapter
- 缓存链路：查看 CountLimitLRU 缓存策略

## 相关主题

- [主题分层访问](theme-layered-access.md)
- [资源动态切换](resource-dynamic-switching.md)