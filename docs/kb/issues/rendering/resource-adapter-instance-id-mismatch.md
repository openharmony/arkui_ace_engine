# 资源适配器实例ID缓存不匹配 Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-30
> 来源：`docs/context_registry.json` 主题 `ResourceAdapterInstanceIdMismatch`
> 关联功能域：03-03-01, 03-03-04, 04-16-01

## 问题概述

深浅色切换后，跨包（HSP）资源因缓存键实例 ID 与实际创建适配器的容器实例 ID 不一致，导致取回无效适配器，资源获取失败返回默认黑色。

典型表现：
- 切换深色模式后，应用卡片背景色和文本色显示为黑色
- 某应用创建系统级 Toast 弹窗后，页面间切换触发概率复现
- 仅在涉及 HSP 包资源的场景下出现，本包资源不受影响


## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| capability | symptom_surface | resource_manager | frameworks/core/common/resource/resource_manager.cpp | verified |
| capability | root_cause_owner | resource_adapter | frameworks/core/components/theme/resource_adapter.h | verified |
| architecture | root_cause_owner | resource_adapter_impl_v2 | adapter/ohos/osal/resource_adapter_impl_v2.cpp | verified |
| architecture | root_cause_owner | subwindow_manager | frameworks/base/subwindow/subwindow_manager.cpp | verified |
| architecture | root_cause_owner | ace_container | adapter/ohos/entrance/ace_container.cpp | verified |

kind: `component` / `capability` / `architecture`
role: `symptom_surface` / `trigger` / `root_cause_owner` / `fix_location` / `dependency`

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 实例 ID 缓存键不匹配 | `GetOrCreateResourceAdapter` 用调用方 instanceId 做缓存键，但 `CreateNewResourceAdapter` 实际用当前容器的 instanceId 创建适配器 | 深浅色切换时主页面与系统级 Toast 弹窗并发刷新资源 |
| 多实例并发刷新竞争 | 多个容器实例（主页面 + 系统级弹窗）同时触发资源配置更新，后者覆盖前者缓存 | 深浅色切换、字体大小变更等全局配置变更场景 |
| 跨包 HSP 资源上下文缺失 | 系统级弹窗实例不支持跨包获取 HSP 包资源上下文（`GetAbilityContextByModule` 返回空），创建的适配器无效 | 系统级弹窗触发 `CreateNewResourceAdapter` 创建 HSP 包适配器 |

## 排查路径

### 快速判断

1. 确认问题是否仅在深浅色/字体/语言等全局配置切换后出现
2. 确认问题是否仅在涉及 HSP 跨包资源的组件上出现（本包资源正常）
3. 确认是否存在系统级 Toast 弹窗 / 子窗弹窗与主页面同时活跃的场景
4. 查看日志中是否有 `Context is null, create resAdapter by resInfo` 警告（`resource_adapter_impl_v2.cpp`）
5. 确认 `ResourceManager` 缓存中是否存在 instanceId 不匹配的适配器条目

### 详细排查

#### 实例 ID 缓存键不匹配排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `GetOrCreateResourceAdapter` 入口处打印 `resourceObject->GetInstanceId()` 与 `actualInstanceId` | 两者一致 | 若不一致，说明缓存键与创建实例不匹配，命中本根因 |
| 2 | 检查 `CreateNewResourceAdapter` 是否将 `aceContainer->GetInstanceId()` 写入 `actualInstanceId` 出参 | 出参被正确赋值 | 若未赋值，说明缺少 PR #81929 修复 |
| 3 | 检查 `AddResourceAdapter` 调用是否使用 `actualInstanceId` 而非原始 `instanceId` | 使用 `actualInstanceId` | 若使用原始 `instanceId`，说明缺少修复 |

关键代码定位：
- `frameworks/core/common/resource/resource_manager.cpp`：`GetOrCreateResourceAdapter`，缓存入口，修复点在此
- `frameworks/core/common/resource/resource_manager.cpp`：`AddResourceAdapter`，缓存写入，使用 `actualInstanceId` 做 key
- `frameworks/core/components/theme/resource_adapter.h`：`CreateNewResourceAdapter` 声明，含 `int32_t& actualInstanceId` 出参
- `adapter/ohos/osal/resource_adapter_impl_v2.cpp`：`CreateNewResourceAdapter` 实现，line 106 设置 `actualInstanceId = aceContainer->GetInstanceId()`

#### 多实例并发刷新竞争排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `UpdateColorMode` 入口打印 `instanceId` 与当前 `Container::CurrentSafelyWithCheck()->GetInstanceId()` | 两者一致 | 若不一致，说明并发场景下容器上下文切换 |
| 2 | 确认是否存在多个容器实例（主页面 + 系统级弹窗）同时调用 `GetOrCreateResourceAdapter` | 同一 HSP bundle/module 对应同一 instanceId | 若不同实例写入同一缓存键，命中并发竞争 |
| 3 | 检查 `UpdateColorMode` 是否能通过 `GetCacheKeyInstanceId` 正确匹配缓存条目 | 匹配到的适配器与创建时一致 | 若不匹配，说明色彩模式更新被跳过 |

关键代码定位：
- `frameworks/core/common/resource/resource_manager.cpp`：`UpdateColorMode`，按 instanceId 过滤刷新适配器
- `frameworks/core/common/resource/resource_manager.cpp`：`GetCacheKeyInstanceId` 过滤逻辑
- `frameworks/base/subwindow/subwindow_manager.cpp`：`serviceToastSubwindows` 系统级 Toast 子窗收集逻辑

#### 跨包 HSP 资源上下文缺失排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|----------|--------|
| 1 | 在 `CreateNewResourceAdapter` 中检查 `GetAbilityContextByModule` 返回值 | 非 null（HSP 上下文获取成功） | 若返回 null，说明当前容器实例不支持跨包资源上下文 |
| 2 | 确认当前容器是否为系统级 Toast 弹窗 / 子窗弹窗实例 | 非弹窗实例（正常容器） | 若为弹窗实例，说明该实例无依赖包信息，不支持跨包 |
| 3 | 检查 `GetAbilityContextByModule` 实现中 `runtimeContext_` 是否有效 | 有效 | 若无效，说明容器未初始化 AbilityRuntime 上下文 |

关键代码定位：
- `adapter/ohos/osal/resource_adapter_impl_v2.cpp`：`GetAbilityContextByModule` 调用点
- `adapter/ohos/entrance/ace_container.cpp`：`AceContainer::GetAbilityContextByModule` 实现（约 line 3473），依赖 `runtimeContext_`
- `adapter/ohos/entrance/ace_container.cpp`：`isDynamicUIContent` 判断逻辑（约 line 3478，`GetUIContentType() == UIContentType::DYNAMIC_COMPONENT`）

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 典型 PR / Commit 参考 |
|----------|----------|---------------|----------------------|
| 实例 ID 缓存键不匹配 | 为 `CreateNewResourceAdapter` 增加 `int32_t& actualInstanceId` 出参，在函数内部获取真实容器实例 ID，`GetOrCreateResourceAdapter` 使用该值做缓存键 | `resource_manager.cpp`：声明 `actualInstanceId` 并传给工厂函数，`AddResourceAdapter` 使用 `actualInstanceId` | PR #81929 |
| 多实例并发刷新竞争 | 修复后缓存键与创建实例一致，`UpdateColorMode` 能正确匹配并刷新对应实例的适配器 | `resource_adapter_impl_v2.cpp`：`actualInstanceId = aceContainer->GetInstanceId()` | PR #81929 |
| 跨包 HSP 资源上下文缺失 | 修复后即使系统级弹窗实例创建的无效适配器也会以其自身 instanceId 缓存，不会污染主实例的缓存条目 | `resource_adapter.h`：签名增加 `int32_t& actualInstanceId` | PR #81929 |

## 关联案例

| 案例编号 | 问题简述 | 根因类别 | 修复方式 | 关联 PR / Issue |
|----------|----------|----------|----------|----------------|
| CASE-01 | 深浅色切换后应用卡片背景色和文本色变黑 | 实例 ID 缓存键不匹配 + 跨包 HSP 上下文缺失 | 增加 `actualInstanceId` 出参，缓存键使用真实容器实例 ID | [PR #81929](https://gitcode.com/openharmony/arkui_ace_engine/pull/81929) / [Issue #74062](https://gitcode.com/openharmony/arkui_ace_engine/issues/74062) |
| CASE-02 | 系统级 Toast 弹窗触发 `GetOrCreateResourceAdapter` 创建 HSP 适配器，因 `GetAbilityContextByModule` 返回 null 创建无效适配器，污染主实例缓存 | 多实例并发刷新竞争 + 跨包 HSP 上下文缺失 | 修复后无效适配器以其自身 instanceId 缓存，不影响主实例 | PR #81929 |

## 预防措施

- 新增任何通过 `Container::Current*()` 获取容器并缓存资源的逻辑时，必须使用 `aceContainer->GetInstanceId()` 作为缓存键，而非调用方传入的 instanceId
- 全局配置变更（深浅色、字体、语言等）触发多实例并发刷新时，应确保缓存键与实际创建容器一致
- 系统级 Toast 弹窗等无依赖包信息的实例不应承担跨包资源上下文创建职责，可通过 instanceId 隔离缓存
- 单元测试应覆盖 `CreateNewResourceAdapter` 返回的 instanceId 与传入 instanceId 不一致的场景（参考 `ResourceManagerTest007`）

## 相关主题

- [resource-access](../../architecture/resource-access.md) — 资源访问（FuncID 03-03-01）
- [resource-dynamic-switching](../../architecture/resource-dynamic-switching.md) — 资源动态切换（FuncID 03-03-04）
- [theme-layered-access](../../architecture/theme-layered-access.md) — 主题分层访问（FuncID 03-03-02）
- [ui-appearance](../../capabilities/ui-appearance.md) — 色彩模式管理（FuncID 04-16-01）
- [subwindow-mechanism](../../architecture/subwindow-mechanism.md) — 子窗机制
- [multi-instance-management](../../architecture/multi-instance-management.md) — 多实例管理