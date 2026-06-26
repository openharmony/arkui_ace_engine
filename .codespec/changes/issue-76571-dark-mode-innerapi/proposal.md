# Proposal — 深浅色模式 Inner API 扩展

> 本文从 `.ai-specs/features/FEAT-20260509-dark-mode-innerapi/requirement.md` 迁移归档而来，保留原始需求基线内容。

> 一份文档，从原始需求到基线结论。按阶段追加内容，不拆成多份独立文件。

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | FEAT-20260509-001 |
| 需求名称 | 深浅色模式 Inner API 扩展 |
| 来源 | 子系统调用需求 |
| 提出人 | 待确认 |
| 目标发行版本 | OpenHarmony-7.0-Release |
| 候选 Profile | arkui |
| 优先级 | P1 |
| 状态 | Clarifying → Baselining |

### 原始描述

**原始问题：** 外部子系统需要在 `interfaces/inner_api/ace_kit` 下新增深浅色相关的 inner API，以便在外部子系统侧实现深浅色资源热加载、颜色反色和资源解析等能力。当前 ace_kit 的 inner API 暴露不够充分，外部子系统无法独立完成深浅色适配。

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| 外部子系统开发者 | 无法通过 ace_kit inner API 获取深浅色配置信息 | 子系统无法独立适配深浅色模式 |
| 外部子系统开发者 | 无法调用 ResourceParseUtils 全量接口解析资源 | 资源解析能力不对外暴露，子系统需自行实现 |
| 外部子系统开发者 | Tabs 组件无法接收 ResourceObject 进行资源热加载 | Tabs 属性不支持配置变更时的自动刷新 |
| 外部子系统开发者 | 无法获取反色方法（invertFunc） | 无法正确处理深色模式下的颜色反色 |

**期望结果：** 在 ace_kit inner API 层暴露完整的深浅色相关能力，包括资源解析、配置获取、颜色模式查询、反色方法和 Tabs 资源热加载，使外部子系统能够独立完成深浅色适配。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| 源码 | `frameworks/core/common/resource/resource_parse_utils.h` | 已有全量资源解析工具类，需对外暴露 |
| 源码 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | 现有 UIContext 已有 GetColorMode/GetLocalColorMode，需扩展 |
| 源码 | `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs.h` | 现有 Tabs 类需新增 ResourceObject 接收接口 |
| 源码 | `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp:1416-1470` | 已有 CreateWithResourceObj 实现，需在 ace_kit 层桥接 |

### 初始范围

**可能包含：**

1. **ResourceParseUtils 全量接口暴露**
   - 在 ace_kit 层暴露 `frameworks/core/common/resource/resource_parse_utils.h` 中的全量接口
   - 包括：ParseResColor、ParseResColorWithColorMode、ParseResString、ParseResInteger、ParseResDouble、ParseResBool、ParseResMedia、ParseResDimensionVpNG、ParseResDimensionFpNG、ParseResDimensionNG、ParseResResource、ParseResFontFamilies、ParseResStrArray、ParseResIntegerArray、ParseResourceToDouble、CompleteResourceObjectFromColor 等

2. **UIContext 新增接口**
   - `GetConfigPerform()` — 获取 `SystemProperties::ConfigPerform` 标志，判断系统是否启用配置变更热加载
   - `GetInstanceId()` — 获取 `UIContext::context_` 的 instanceId
   - `GetSystemColorMode()` — 获取当前系统的深浅色模式（非 Local，取系统级）
   - `HasDarkResource(ResourceObject)` — 判断 ResourceObject 是否配置了深色资源
   - `GetInvertFunc(instanceId, nodeTag)` — 根据 InstanceId 和节点类型（nodeTag）获取反色方法

3. **FrameNode 新增接口**
   - `GetLocalColorMode()` — 已存在于 ace_kit（`frame_node.h:116`），需确认是否满足需求或需扩展

4. **Tabs 新增 ResourceObject 接口**
   - 在 ace_kit Tabs 类上新增接收 ResourceObject 的接口
   - 底层调用 `TabsModel::GetInstance()->CreateWithResourceObj` 注册 ResourceObject
   - 涉及属性方法：SetTabBarWidth、SetTabBarHeight、SetDivider、SetScrollableBarModeOptions、SetEffectNodeOption、SetBarBackgroundBlurStyle、SetBarBackgroundColor、SetBarBackgroundEffect

**明确不包含：**

- 不涉及 Public API / SDK API 变更
- 不涉及 ArkTS 前端声明式语法变更
- 不涉及新增组件或新渲染能力

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| ResourceParseUtils 的全量接口可安全暴露给外部子系统 | 技术 | 头文件移动到 ace_kit include 路径，实现不移动 | **已验证** |
| 外部子系统通过 ace_kit include 路径消费 inner API | 技术 | 确认现有 ace_kit 使用方式 | **已验证** |
| `SystemProperties::ConfigChangePerform()` 可在 ace_kit 层桥接暴露 | 技术 | UIContextImpl 持有 PipelineContext 指针，可通过其获取 instanceId 并桥接 SystemProperties | **已验证** |
| `CreateWithResourceObj` 的所有 TabJsResType 枚举值都需要在 Tabs 层暴露 | 业务 | 需求方确认仅 8 个属性方法 | **已验证** |
| ResourceObject 的 `HasDarkResource()` 能力已在框架层实现 | 技术 | `resource_object.h:129` 有 `HasDarkResource()` getter，但实际查询需通过 ResourceManager（参考 `ArkTSUtils::CheckDarkResource`） | **已验证** |
| FrameNode::GetLocalColorMode() 已存在于 ace_kit（`frame_node.h:116`），可能不需要新增 | 技术 | 源码确认 | **已验证** |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 | 单仓修改，涉及 ace_kit 层 3 个类的接口扩展和 1 个工具类的暴露，不跨仓 |
| 涉及仓数量 | 1 | 仅 ace_engine |
| 是否涉及 Public/System API | 否 | 仅涉及 inner_api |
| 是否涉及安全/性能关键路径 | 否 | 资源解析和配置查询，非关键路径 |
| 是否跨 SIG | 否 | arkui 子系统内部 |

### 进入澄清条件

- [x] 原始问题和期望结果已记录
- [ ] 需求来源和责任人已明确
- [x] 初始范围和不包含项已记录
- [x] 关键假设和待澄清问题已列出
- [x] 复杂度有判断或明确为待定

---

## 二、澄清记录

> 澄清是逐轮对话，不是一次性填表。先从"待澄清问题"出发，一次只讨论一个问题，结论确认后再写入本记录。
> 全部澄清完成后，向需求方输出总结确认："我的理解是 [一句话]。范围含 X，不含 Y，涉及 Z 个子系统。正确？"

### 待澄清问题

> 从原始需求的模糊点中提炼，逐项澄清后填入结论。

| 编号 | 问题 | 为什么需要澄清 | 状态 |
|------|------|----------------|------|
| Q-1 | ResourceParseUtils 全量暴露是指完整复制该类到 ace_kit include 路径，还是在 ace_kit 层新增包装类？ | 影响实现方案、维护成本和 ABI 稳定性 | **已澄清：将 resource_parse_utils.h 头文件移动到 `interfaces/inner_api/ace_kit/include/ui/resource/`，实现仍保持在原 `resource_parse_utils.cpp` 中不移动** |
| Q-2 | UIContext::GetInvertFunc 的返回类型是什么？是 std::function 还是函数指针？是否有现有实现可直接桥接？ | 源码中未找到现成的 invertFunc 提取接口，需确认具体行为 | **已澄清：与 `ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag)` 保持一致，返回类型为 `ColorInvertFunc` 即 `std::function<uint32_t(uint32_t)>`，签名为 `(int32_t instanceId, const std::string& nodeTag)`，底层直接桥接 `ColorInverter`** |
| Q-3 | UIContext::HasDarkResource(ResourceObject) — 是检查单个 ResourceObject 实例是否配置了深色资源变体，还是检查全局？ | ResourceObject 有 `GetColorMode()` 方法，但"是否配置深色资源"可能是 `HasDarkResource()` 方法，需确认语义 | **已澄清：检查单个 ResourceObject 实例是否有深色资源变体，实现参考 `ArkTSUtils::CheckDarkResource`（`arkts_utils.cpp:231-251`）：通过 ResourceManager 查询 `ExistDarkResById` 或 `ExistDarkResByName`** |
| Q-4 | Tabs 的 8 个属性方法（SetTabBarWidth 等）新增 ResourceObject 版本，是新增重载（如 `SetTabBarWidth(const RefPtr<ResourceObject>&)`）还是替换现有接口？ | 影响向后兼容性和 API 设计 | **已澄清：新增重载，在现有方法签名基础上追加 `const RefPtr<ResourceObject>&` 参数，保留原方法不变，向后兼容** |
| Q-5 | 目标发行版本是哪个？ | manifest.target_release 需要明确 | **已澄清：OpenHarmony 7.0** |
| Q-6 | "ResourceParseUtils 中的全量接口"是否确指该头文件中所有 static 方法？是否有不需要暴露的？ | 某些方法如 `SetNeedReload`、`MakeNativeNodeInfo` 可能不需要暴露给外部子系统 | **已澄清：排除 SetNeedReload、NeedReload、MakeNativeNodeInfo、GetThemeConstants 四个内部方法，其余 Parse/Convert 方法全部暴露** |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2026-05-09 | 需求方 | Q-1 ResourceParseUtils 暴露方式 | 将 `resource_parse_utils.h` 头文件移动到 `interfaces/inner_api/ace_kit/include/ui/resource/`，实现仍保持在原 `.cpp` 中不移动。属于头文件路径迁移，不是包装类。 | 更新假设"ResourceParseUtils 可安全暴露"为已验证 |
| 2026-05-09 | 需求方 | Q-6 全量接口边界 | 排除 `SetNeedReload`、`NeedReload`、`MakeNativeNodeInfo`、`GetThemeConstants` 四个内部方法，其余 Parse/Convert/CompleteResourceObject 系列方法全部移动暴露 | 更新范围说明 |
| 2026-05-09 | 需求方 | Q-2 GetInvertFunc 返回类型与语义 | 与 `ColorInverter::GetInstance().GetInvertFunc` 一致：返回 `ColorInvertFunc`（`std::function<uint32_t(uint32_t)>`），参数 `(int32_t instanceId, const std::string& nodeTag)`，UIContext 层直接桥接 `ColorInverter` | 确认 `color_inverter.h` 依赖关系 |
| 2026-05-09 | 需求方 | Q-3 HasDarkResource 语义 | 检查单个 ResourceObject 是否有深色资源变体，实现参考 `ArkTSUtils::CheckDarkResource`（`arkts_utils.cpp:231-251`），通过 ResourceManager 查询 ExistDarkResById/ExistDarkResByName | 确认放在 UIContext 还是 ResourceParseUtils |
| 2026-05-09 | 需求方 | Q-4 Tabs 接口设计 | 新增重载版本，在现有方法签名基础上追加 `const RefPtr<ResourceObject>&` 参数，保留原方法不变，向后兼容 | 8 个方法均适用 |
| 2026-05-09 | 需求方 | Q-5 目标发行版本 | OpenHarmony 7.0 | 更新 manifest.target_release |

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心功能包含哪些？ | 4 大模块：ResourceParseUtils 头文件迁移、UIContext 5 个新方法、FrameNode GetLocalColorMode（已存在）、Tabs 8 个 ResourceObject 重载 | 需求方 | 已确认 |
| 明确不包含哪些？ | Public API / SDK 变更、前端语法变更、新组件、ResourceParseUtils 4 个内部方法（SetNeedReload/NeedReload/MakeNativeNodeInfo/GetThemeConstants） | 需求方 | 已确认 |
| 是否有分期策略？ | 否，一次性交付 | 需求方 | 已确认 |

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | 仅 arkui (ace_engine) | 需求方 | 已确认 |
| 是否需要新增子系统或部件？ | 否 | 需求方 | 已确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增/修改 Public API？ | 否，仅 inner API | 需求方 | 已确认 |
| 是否需要新增 System API？ | 否 | 需求方 | 已确认 |
| 是否会废弃已有 API？ | 否，纯新增 | 需求方 | 已确认 |
| 是否需要新增权限声明？ | 否 | 需求方 | 已确认 |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | 向后兼容要求？ | 纯新增接口，不影响现有 API；Tabs 新增重载而非替换 | 需求方 | 已确认 |
| 性能 | 响应时间/内存要求？ | N/A — 资源解析类操作，无特殊性能要求 | 需求方 | 已确认 |
| 安全 | 权限/隐私要求？ | N/A — inner API，无额外权限需求 | 需求方 | 已确认 |
| 可靠性 | 崩溃率/容错要求？ | N/A — 无特殊可靠性要求，跟随框架层既有容错 | 需求方 | 已确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| ResourceParseUtils 头文件依赖链 | 编译 | 头文件迁移到 ace_kit include 路径，原 include 引用需更新 | 已确认 |
| SystemProperties::ConfigChangePerform | 编译 | UIContext 层桥接，通过 PipelineContext 访问 | 已确认 |
| ColorInverter 单例 | 编译 | UIContext::GetInvertFunc 桥接 `color_inverter.h` | 已确认 |
| ResourceManager | 编译 | UIContext::HasDarkResource 通过 ResourceManager 查询 | 已确认 |
| TabsModelNG::CreateWithResourceObj | 编译 | Tabs 重载方法桥接 `tabs_model_ng.cpp:1416` | 已确认 |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| ResourceParseUtils 头文件迁移影响现有 include 引用 | 技术 | 中 | 更新所有 `#include` 引用路径 | 已确认 |
| CreateWithResourceObj 受 ConfigChangePerform 门控 | 技术 | 低 | 调用前需检查 GetConfigPerform() | 已确认 |

### AC 完整性

- [x] 每个用户故事有验收标准
- [x] AC 全部使用 WHEN/THEN 格式
- [x] 覆盖正常流程、异常流程、边界条件
- [x] AC 可测试、可度量

### 澄清结论

- [x] 功能范围已完全明确
- [x] 子系统影响已识别
- [x] API 变更已评估
- [x] 兼容性和非功能需求已确认
- [x] 依赖和风险已识别且有缓解方案
- [x] AC 完整可测试

**结论:** 通过

---

## 三、需求基线

> 澄清完成后固化。manifest.md 是事实源，此处为审批结论。

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2026-05-09 |
| Owner | 待确认 |
| 确认人 | 需求方 |
| 复杂度 | 标准 |
| Profile | arkui |
| 目标发行版本 | OpenHarmony-7.0-Release（引用 manifest.target_release） |
| 版本状态 | proposed |

### 问题陈述

外部子系统需要通过 ace_kit inner API 独立完成深浅色模式适配，但当前 ace_kit 层暴露的深浅色相关接口不足：资源解析工具类未对外暴露、UIContext 缺少配置查询和反色能力、Tabs 组件不支持 ResourceObject 资源热加载。受影响用户为需要适配深浅色的外部子系统开发者。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| 外部子系统可通过 ace_kit 调用全量资源解析接口 | ResourceParseUtils 所有暴露方法可通过 ace_kit include 路径正常调用 | 编译通过 + 单元测试 |
| 外部子系统可查询深浅色配置和反色能力 | UIContext 新增 5 个方法均可正常调用并返回正确结果 | 单元测试 |
| Tabs 组件支持 ResourceObject 资源热加载 | 8 个属性方法的 ResourceObject 重载可注册资源并在配置变更时自动刷新 | 单元测试 |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为外部子系统开发者，我想要通过 ace_kit 调用资源解析接口，以便解析 $r() 引用的各类资源 | P0 |
| US-2 | 作为外部子系统开发者，我想要通过 UIContext 查询深浅色配置信息（ConfigPerform、InstanceId、ColorMode、HasDarkResource、InvertFunc），以便正确适配深浅色模式 | P0 |
| US-3 | 作为外部子系统开发者，我想要在 Tabs 组件上设置带 ResourceObject 的属性，以便属性值在配置变更时自动刷新 | P0 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN 将 `resource_parse_utils.h` 移动到 `ace_kit/include/ui/resource/` THEN 外部子系统通过 `#include` 新路径可正常调用 ParseResColor、ParseResColorWithColorMode、ParseResString、ParseResInteger、ParseResDouble、ParseResBool、ParseResMedia、ParseResDimensionVpNG、ParseResDimensionFpNG、ParseResDimensionNG、ParseResResource、ParseResFontFamilies、ParseResStrArray、ParseResIntegerArray、ParseResourceToDouble、ParseResDouble、CompleteResourceObjectFromColor、ConvertFromResObjNG、ConvertFromResObj 等方法且编译通过 | 正常 | US-1 |
| AC-2 | WHEN 外部子系统调用 ResourceParseUtils 的内部方法（SetNeedReload、NeedReload、MakeNativeNodeInfo、GetThemeConstants）THEN 这些方法不可通过 ace_kit include 路径访问 | 边界 | US-1 |
| AC-3 | WHEN 原有 `#include "core/common/resource/resource_parse_utils.h"` 的引用更新为新路径 THEN 所有现有编译目标（框架层、bridge 层）编译通过 | 正常 | US-1 |
| AC-4 | WHEN 调用 `UIContext::GetConfigPerform()` THEN 返回值与 `SystemProperties::ConfigChangePerform()` 一致 | 正常 | US-2 |
| AC-5 | WHEN 调用 `UIContext::GetInstanceId()` THEN 返回当前 UIContext 关联的 PipelineContext 的 instanceId | 正常 | US-2 |
| AC-6 | WHEN 调用 `UIContext::GetColorMode()`（现有接口）THEN 返回当前系统级深浅色模式（Light/Dark） | 正常 | US-2 |
| AC-7 | WHEN 调用 `UIContext::HasDarkResource(resObj)` 且该 ResourceObject 有深色资源变体 THEN 返回 true；无深色资源变体 THEN 返回 false | 正常 | US-2 |
| AC-8 | WHEN 调用 `UIContext::HasDarkResource(resObj)` 且 resObj 为空 THEN 返回 false 且不崩溃 | 异常 | US-2 |
| AC-9 | WHEN 调用 `UIContext::GetInvertFunc(instanceId, nodeTag)` THEN 返回类型为 `ColorInvertFunc`（`std::function<uint32_t(uint32_t)>`），行为与 `ColorInverter::GetInstance().GetInvertFunc` 一致 | 正常 | US-2 |
| AC-10 | WHEN 调用 `UIContext::GetInvertFunc` 时无对应反色函数注册 THEN 返回空 function（转换为 false） | 边界 | US-2 |
| AC-11 | WHEN `FrameNode::GetLocalColorMode()` 在已有 ace_kit 接口上调用 THEN 返回值正确反映该节点的局部颜色模式 | 正常 | US-2 |
| AC-12 | WHEN 调用 `Tabs::SetTabBarWidth(dim, resObj)`（重载版本）THEN 底层调用 `TabsModelNG::CreateWithResourceObj` 注册 ResourceObject，资源变更时自动刷新 | 正常 | US-3 |
| AC-13 | WHEN 对 SetTabBarHeight、SetDivider、SetScrollableBarModeOptions、SetEffectNodeOption、SetBarBackgroundBlurStyle、SetBarBackgroundColor、SetBarBackgroundEffect 7 个方法传入 ResourceObject THEN 行为与 AC-12 一致 | 正常 | US-3 |
| AC-14 | WHEN 调用 Tabs 的原方法（不带 ResourceObject 参数）THEN 行为与迁移前完全一致，无任何回归 | 正常 | US-3 |
| AC-15 | WHEN `SystemProperties::ConfigChangePerform()` 返回 false THEN `CreateWithResourceObj` 为空操作（与现有框架行为一致） | 边界 | US-3 |

### 范围边界

**包含：**
- ResourceParseUtils 头文件迁移到 `ace_kit/include/ui/resource/`（排除 4 个内部方法）
- UIContext 新增 5 个虚方法：GetConfigPerform、GetInstanceId、HasDarkResource、GetInvertFunc + 已有 GetColorMode
- UIContextImpl 新增 5 个对应实现
- FrameNode::GetLocalColorMode — 已存在，确认满足需求
- Tabs 新增 8 个 ResourceObject 重载方法
- Tabs 实现层桥接 TabsModelNG::CreateWithResourceObj
- 更新所有现有 `#include "resource_parse_utils.h"` 引用路径
- BUILD.gn 更新（如有必要）

**不包含：**
- Public API / SDK API 变更
- ArkTS 前端声明式语法变更
- 新增组件或新渲染能力
- ResourceParseUtils 的 SetNeedReload、NeedReload、MakeNativeNodeInfo、GetThemeConstants 方法

**分期策略：** 无，一次性交付。

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 影响类型 | Owner |
|--------|------|-----------|----------|-------|
| arkui | ace_engine | `interfaces/inner_api/ace_kit/include/ui/resource/` | 新增（头文件迁移） | 待确认 |
| arkui | ace_engine | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | 修改（新增 5 个虚方法） | 待确认 |
| arkui | ace_engine | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.h/cpp` | 修改（新增 5 个实现） | 待确认 |
| arkui | ace_engine | `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs.h` | 修改（新增 8 个重载声明） | 待确认 |
| arkui | ace_engine | `interfaces/inner_api/ace_kit/src/view/components/tabs.cpp` | 修改（新增 8 个重载实现） | 待确认 |
| arkui | ace_engine | `frameworks/core/common/resource/resource_parse_utils.h` | 删除（移动到 ace_kit） | 待确认 |
| arkui | ace_engine | 所有 `#include "resource_parse_utils.h"` 的文件 | 修改（更新 include 路径） | 待确认 |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 否/N/A | 资源解析和配置查询操作，无性能敏感路径 | N/A |
| 安全与权限 | 否/N/A | inner API 层，无权限变更 | N/A |
| 兼容性 | 是 | Tabs 新增重载不替换原方法，头文件迁移需更新 include 路径 | design.md |
| API/SDK | 否/N/A | 仅 inner API，不涉及 Public/System API | N/A |
| IPC/跨进程 | 否/N/A | 无跨进程通信 | N/A |
| 构建与部件 | 是 | BUILD.gn 可能需调整，头文件路径变更 | design.md |
| 国际化/无障碍 | 否/N/A | 深浅色模式不涉及国际化 | N/A |
| 数据迁移 | 否/N/A | 无数据迁移 | N/A |

### 变更控制

| 变更类型 | 触发条件 | 处理规则 |
|----------|----------|----------|
| 范围新增 | 新增需暴露的接口或 Tabs 方法 | 重新评估复杂度和设计影响 |
| AC 变更 | 修改可观察行为 | 重新审批基线和 Spec |
| API 变更 | 新增/修改 inner API 签名 | 触发设计审批 |
| 非功能指标变更 | 性能/安全/兼容性阈值变化 | 重新确认测试计划 |
| 目标版本变更 | 交付版本调整 | 更新 manifest.target_release |

### 进入设计/Spec 条件

- [x] 所有 P0/P1 用户故事有 AC
- [x] 每条 AC 可测试、可度量
- [x] 范围内/外已确认
- [x] `manifest.target_release` 已确认（OpenHarmony-7.0-Release）
- [x] `manifest.profile` 已确认（arkui）
- [x] 涉及仓、模块、SIG 已识别
- [x] 不涉及项已标记 N/A
- [x] 变更控制规则已确认

**基线结论:** 通过
