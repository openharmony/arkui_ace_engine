# 特性规格

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 深浅色模式 Inner API 扩展 |
| 特性编号 | FEAT-20260509-001 |
| 所属 Epic | 无 |
| 优先级 | P0 |
| 目标版本 | 引用 manifest.target_release（OpenHarmony-7.0-Release） |
| SIG 归属 | SIG_ArkUI |
| 状态 | Draft |
| 复杂度 | 标准 |

## 本次变更范围（Delta）

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | `ui/resource/resource_parse_utils.h`（定义 `ResourceParseUtilsBase` 基类） | 对外暴露，排除 SetNeedReload/NeedReload/MakeNativeNodeInfo/GetThemeConstants |
| MODIFIED | `frameworks/core/common/resource/resource_parse_utils.h`（重写为继承版） | 定义 `ResourceParseUtils final : public ResourceParseUtilsBase`，含 4 个内部方法 + `ParseResInteger<T>` 模板体 |
| MODIFIED | `frameworks/core/common/resource/resource_parse_utils.cpp` | 基类方法定义改为 `ResourceParseUtilsBase::`，派生类方法保持 `ResourceParseUtils::` |
| MODIFIED | `test/mock/.../mock_resource_parse_utils.cpp` | `needReload_` 归属改为 `ResourceParseUtilsBase::` |
| ADDED | UIContext::GetConfigPerform() | 新增虚方法，返回 SystemProperties::ConfigChangePerform() |
| ADDED | UIContext::GetInstanceId() | 新增虚方法，返回 PipelineContext 的 instanceId |
| ADDED | UIContext::HasDarkResource(resObj) | 新增虚方法，检查单个 ResourceObject 是否有深色资源变体 |
| ADDED | UIContext::GetInvertFunc(instanceId, nodeTag) | 新增虚方法，返回 ColorInvertFunc |
| ADDED | Tabs 8 个 ResourceObject 重载方法 | 新增重载，不替换原方法 |
| MODIFIED | UIContextImpl | 新增 4 个 override 实现 |
| MODIFIED | tabs.cpp | 新增 8 个重载实现 |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Proposal | `proposal.md` | Approved |
| Design | `design.md` | Approved |

## 用户故事

### US-1: 资源解析接口对外暴露

**作为** 外部子系统开发者,
**我想要** 通过 ace_kit 调用 ResourceParseUtils 全量资源解析接口,
**以便** 解析 $r() 引用的各类资源（颜色、字符串、整数、维度、布尔、媒体等）.

**验收标准：**

- **AC-1:** WHEN 通过 `#include "ui/resource/resource_parse_utils.h"` 引用 THEN 可正常调用 `ResourceParseUtilsBase` 类的以下 static 方法且编译通过：ParseResColor、ParseResColorWithColorMode、ParseResString（两个重载）、ParseResInteger（三个重载）、ParseResDouble（两个重载）、ParseResBool、ParseResMedia、ParseResDimensionVpNG、ParseResDimensionFpNG、ParseResDimensionNG、ParseResDimension（四个重载）、ParseResResource、ParseResFontFamilies、ParseResStrArray、ParseResIntegerArray、ParseResourceToDouble、CompleteResourceObjectFromColor、ConvertFromResObjNG、ConvertFromResObj、IsNumberType
- **AC-2:** WHEN 外部子系统查看 `ui/resource/resource_parse_utils.h` THEN 不包含 SetNeedReload、NeedReload、MakeNativeNodeInfo、GetThemeConstants 四个方法声明
- **AC-3:** WHEN 框架层现有文件通过 `#include "core/common/resource/resource_parse_utils.h"` 引用 THEN 引用到 `ResourceParseUtils`（继承 `ResourceParseUtilsBase`），所有现有编译目标（174 个文件）编译通过，行为无回归

### US-2: UIContext 深浅色配置查询与反色能力

**作为** 外部子系统开发者,
**我想要** 通过 UIContext 查询深浅色配置信息（ConfigPerform、InstanceId、ColorMode、HasDarkResource、InvertFunc）,
**以便** 正确适配深浅色模式.

**验收标准：**

- **AC-4:** WHEN 调用 `UIContext::GetConfigPerform()` THEN 返回值与 `SystemProperties::ConfigChangePerform()` 完全一致（true/false）
- **AC-5:** WHEN 调用 `UIContext::GetInstanceId()` THEN 返回当前 UIContext 关联的 PipelineContext 的 instanceId（int32_t）；WHEN context_ 为空 THEN 返回 -1
- **AC-6:** WHEN 调用 `UIContext::GetColorMode()`（现有接口）THEN 返回当前系统级深浅色模式（ColorMode::LIGHT / ColorMode::DARK / ColorMode::COLOR_MODE_UNDEFINED）
- **AC-7:** WHEN 调用 `UIContext::HasDarkResource(resObj)` 且该 ResourceObject 有深色资源变体 THEN 返回 true；无深色资源变体 THEN 返回 false
- **AC-8:** WHEN 调用 `UIContext::HasDarkResource(resObj)` 且 resObj 为空指针 THEN 返回 false 且不崩溃；WHEN SystemProperties::GetResourceDecoupling() 返回 false THEN 返回 false
- **AC-9:** WHEN 调用 `UIContext::GetInvertFunc(instanceId, nodeTag)` THEN 返回类型为 `ColorInvertFunc`（`std::function<uint32_t(uint32_t)>`），行为与 `ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag)` 完全一致
- **AC-10:** WHEN 调用 `UIContext::GetInvertFunc` 时无对应 instanceId 或 nodeTag 的反色函数注册 THEN 返回的 function 转换为 bool 为 false
- **AC-11:** WHEN 在已有 ace_kit 接口上调用 `FrameNode::GetLocalColorMode()` THEN 返回值正确反映该节点的局部颜色模式（已存在，无变更）

### US-3: Tabs ResourceObject 资源热加载

**作为** 外部子系统开发者,
**我想要** 在 Tabs 组件上设置带 ResourceObject 的属性,
**以便** 属性值在系统配置变更（深浅色切换等）时自动刷新.

**验收标准：**

- **AC-12:** WHEN 调用 `Tabs::SetTabBarWidth(dim, resObj)`（重载版本）THEN 底层调用 `TabsModelNG::CreateWithResourceObj(BAR_WIDTH, resObj)` 注册 ResourceObject；WHEN 系统配置变更 THEN 资源自动重新解析并更新 TabBarWidth 值
- **AC-13:** WHEN 对 SetTabBarHeight、SetDivider、SetScrollableBarModeOptions、SetEffectNodeOption、SetBarBackgroundBlurStyle、SetBarBackgroundColor、SetBarBackgroundEffect 7 个方法分别传入 ResourceObject THEN 行为与 AC-12 一致：先调用原方法设值，再注册 ResourceObject
- **AC-14:** WHEN 调用 Tabs 的原方法（不带 ResourceObject 参数）THEN 行为与变更前完全一致，无任何回归
- **AC-15:** WHEN `SystemProperties::ConfigChangePerform()` 返回 false THEN `TabsModelNG::CreateWithResourceObj` 为空操作（`tabs_model_ng.cpp:1418` 的 guard），与现有框架行为一致

## 验收追溯

| AC | 关联规则 | 关联 Task | 验证方式 | 证据 |
|----|----------|-----------|----------|------|
| AC-1 | FR-1, FR-2 | TASK-001 | 编译验证 + 单元测试 | `test/unittest/` |
| AC-2 | FR-2 | TASK-001 | 编译验证（方法声明不存在） | `test/unittest/` |
| AC-3 | BR-1 | TASK-001 | 全量编译 | `out/rk3568/` |
| AC-4 | FR-3 | TASK-002 | 单元测试 | `test/unittest/` |
| AC-5 | FR-4 | TASK-002 | 单元测试 | `test/unittest/` |
| AC-6 | FR-5 | 无变更 | 现有测试 | `test/unittest/` |
| AC-7 | FR-6 | TASK-002 | 单元测试 | `test/unittest/` |
| AC-8 | EX-1, EX-2 | TASK-002 | 单元测试 | `test/unittest/` |
| AC-9 | FR-7 | TASK-002 | 单元测试 | `test/unittest/` |
| AC-10 | EX-3 | TASK-002 | 单元测试 | `test/unittest/` |
| AC-11 | FR-5 | 无变更 | 现有测试 | `test/unittest/` |
| AC-12 | FR-8 | TASK-003 | 单元测试 | `test/unittest/` |
| AC-13 | FR-8 | TASK-003 | 单元测试 | `test/unittest/` |
| AC-14 | BR-1 | TASK-003 | 现有测试全部通过 | `test/unittest/` |
| AC-15 | FR-9 | TASK-003 | 单元测试 | `test/unittest/` |

## 业务规则

| 编号 | 规则描述 | 约束条件 | 关联 AC |
|------|----------|----------|---------|
| BR-1 | 所有现有 API 行为不可变 | 纯新增接口和重载，不修改/删除任何现有方法 | AC-3, AC-14 |
| BR-2 | ResourceParseUtilsBase 基类仅对外暴露（不含 4 个内部方法），ResourceParseUtils 派生类在 frameworks 层定义（含 4 个内部方法） | 框架层内部继续通过 `ResourceParseUtils` 访问所有方法（基类+派生类） | AC-2, AC-3 |
| BR-3 | ConfigChangePerform 为全局特性开关 | 由系统属性 `persist.sys.arkui.configchangeperform` 控制 | AC-4, AC-15 |

## 功能规则

| 编号 | 规则描述 | 触发条件 | 作用对象 | 关联 AC |
|------|----------|----------|----------|---------|
| FR-1 | `ResourceParseUtilsBase` 对外方法可通过 `ui/resource/resource_parse_utils.h` 正常调用 | 外部子系统 include 该头文件 | ResourceParseUtilsBase static 方法 | AC-1 |
| FR-2 | 对外头文件不含 SetNeedReload、NeedReload、MakeNativeNodeInfo、GetThemeConstants（这 4 个方法仅在 `ResourceParseUtils` 派生类中定义） | 编译期强制 | ace_kit 头文件 | AC-2 |
| FR-3 | GetConfigPerform() 返回 SystemProperties::ConfigChangePerform() 的当前值 | 调用时 | UIContext | AC-4 |
| FR-4 | GetInstanceId() 返回 context_->GetInstanceId()；context_ 为空时返回 -1 | 调用时 | UIContext | AC-5 |
| FR-5 | GetColorMode() 和 GetLocalColorMode() 已有实现不变 | 调用时 | UIContext / FrameNode | AC-6, AC-11 |
| FR-6 | HasDarkResource 通过 ResourceManager 查询：resId != -1 时用 ExistDarkResById；resId == -1 时解析 params 取最后一段用 ExistDarkResByName | 调用时 | UIContext | AC-7 |
| FR-7 | GetInvertFunc 直接委托 ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag) | 调用时 | UIContext | AC-9 |
| FR-8 | Tabs 重载方法先调用原方法设值，再调用 TabsModelNG::CreateWithResourceObj 注册 ResourceObject | 调用带 resObj 参数的重载 | Tabs | AC-12, AC-13 |
| FR-9 | CreateWithResourceObj 受 ConfigChangePerform guard 门控，返回 false 时为空操作 | ConfigChangePerform == false | TabsModelNG | AC-15 |

## 异常/豁免规则

| 编号 | 规则描述 | 触发条件 | 处理结果 | 关联 AC |
|------|----------|----------|----------|---------|
| EX-1 | HasDarkResource 空指针保护 | resObj 为 nullptr | 返回 false，不崩溃 | AC-8 |
| EX-2 | HasDarkResource 资源解耦开关 | SystemProperties::GetResourceDecoupling() 返回 false | 返回 false | AC-8 |
| EX-3 | GetInvertFunc 无匹配注册 | 指定 instanceId 或 nodeTag 无对应 ColorInvertFuncManager | 返回空 function（bool 转换为 false） | AC-10 |
| EX-4 | GetInstanceId PipelineContext 为空 | UIContextImpl 的 context_ 为 nullptr | 返回 -1 | AC-5 |
| EX-5 | HasDarkResource ResourceManager 不可用 | GetOrCreateResourceAdapter 返回 nullptr | 返回 false | AC-7 |

## 恢复契约

| 编号 | 触发条件 | 恢复策略 | 恢复结果 | 约束 |
|------|----------|----------|----------|------|
| RC-1 | PipelineContext 被销毁后 UIContext 方法被调用 | UIContextImpl 通过 CHECK_NULL_RETURN 宏保护 | 返回安全默认值（-1/false/nullptr） | 无超时 |
| RC-2 | Tabs ResourceObject 注册后配置变更触发刷新 | TabsPattern 通过 AddResObj 注册的回调重新解析资源 | 属性值更新为新资源值 | 仅在 ConfigChangePerform == true 时生效 |

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | FR-1 / AC-1 | 编译验证 | 通过 `ui/resource/resource_parse_utils.h` 可编译调用 `ResourceParseUtilsBase` 所有暴露方法 |
| VM-2 | FR-2 / AC-2 | 编译验证 | 4 个内部方法不存在于 ace_kit 头文件（仅在 `ResourceParseUtils` 派生类中） |
| VM-3 | BR-1 / AC-3 | 全量编译 | 174 个现有文件通过 `ResourceParseUtils`（继承 `ResourceParseUtilsBase`）编译通过 |
| VM-4 | FR-3, FR-4 / AC-4, AC-5 | 单元测试 | Mock PipelineContext 验证返回值正确性 |
| VM-5 | FR-6, EX-1, EX-2, EX-5 / AC-7, AC-8 | 单元测试 | 正常/空指针/开关关闭/适配器不可用 4 种场景 |
| VM-6 | FR-7, EX-3 / AC-9, AC-10 | 单元测试 | 有注册/无注册两种场景 |
| VM-7 | FR-8, FR-9 / AC-12, AC-13, AC-15 | 单元测试 | 8 个重载方法 + ConfigChangePerform 开关 |
| VM-8 | BR-1 / AC-14 | 现有测试 | Tabs 原方法全部现有测试通过 |

## API 变更分析

### 新增 API

| API 签名 | 类型 | 功能 | 头文件 | 权限要求 |
|----------|------|------|--------|----------|
| `virtual bool GetConfigPerform() = 0` | Internal | 返回配置变更热加载开关 | `ui/view/ui_context.h` | - |
| `virtual int32_t GetInstanceId() = 0` | Internal | 返回 PipelineContext 的 instanceId | `ui/view/ui_context.h` | - |
| `virtual bool HasDarkResource(const RefPtr<ResourceObject>&) = 0` | Internal | 检查 ResourceObject 是否有深色资源变体 | `ui/view/ui_context.h` | - |
| `virtual ColorInvertFunc GetInvertFunc(int32_t, const std::string&) = 0` | Internal | 获取反色函数 | `ui/view/ui_context.h` | - |
| `void SetTabBarWidth(const Dimension&, const RefPtr<ResourceObject>&)` | Internal | 设置 TabBarWidth 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |
| `void SetTabBarHeight(const Dimension&, const RefPtr<ResourceObject>&)` | Internal | 设置 TabBarHeight 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |
| `void SetDivider(const TabsItemDivider&, const RefPtr<ResourceObject>&)` | Internal | 设置 Divider 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |
| `void SetScrollableBarModeOptions(const ScrollableBarModeOptions&, const RefPtr<ResourceObject>&)` | Internal | 设置 ScrollableBarModeOptions 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |
| `void SetEffectNodeOption(const TabsEffectNodeOption&, const RefPtr<ResourceObject>&)` | Internal | 设置 EffectNodeOption 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |
| `void SetBarBackgroundBlurStyle(const BlurStyleOption&, const RefPtr<ResourceObject>&)` | Internal | 设置 BarBackgroundBlurStyle 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |
| `void SetBarBackgroundColor(const Color&, const RefPtr<ResourceObject>&)` | Internal | 设置 BarBackgroundColor 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |
| `void SetBarBackgroundEffect(const EffectOption&, const RefPtr<ResourceObject>&)` | Internal | 设置 BarBackgroundEffect 并注册 ResourceObject | `ui/view/components/tabs/tabs.h` | - |

### 变更/废弃 API

| 原有 API | 变更类型 | 新 API | 迁移说明 |
|----------|----------|--------|----------|
| 无 | - | - | 无变更/废弃 |

## 构建系统影响

### BUILD.gn 变更

```
文件路径: interfaces/inner_api/ace_kit/BUILD.gn
变更说明: 无需修改。新头文件位于 public include 目录下自动可见；
         原头文件 include ace_kit 头文件通过全局 ace_config 的
         $ace_root/interfaces/inner_api/ace_kit/include include 路径可访问；
         UIContextImpl 新增的 #include（color_inverter.h、system_properties.h）
         通过已有 private include_dirs（$ace_root/frameworks）可访问。
```

### bundle.json 变更

无。

## 兼容性声明

- **已有 API 行为变更:** 否 — 所有现有方法签名和行为完全不变
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** OpenHarmony 7.0
- **API 版本号策略:** inner API，无 @since 标注

## 架构约束

| 关键约束 | 设计结论 | 影响 AC |
|----------|----------|---------|
| ace_kit include 目录仅暴露公共接口，不依赖框架内部头文件 | 基类头文件 `ResourceParseUtilsBase` 自包含；UIContext 新方法用 typedef 而非直接 include ColorInverter | AC-1, AC-2 |
| ace_kit src 可 include frameworks 头文件（BUILD.gn private include_dirs） | UIContextImpl 通过 private include 访问 SystemProperties、ColorInverter、ResourceManager | AC-4 ~ AC-10 |
| Tabs 实现委托 TabsModelNG（分层一致性） | 重载方法沿用现有 Tabs → TabsModelNG::Handle* 静态方法委托模式 | AC-12, AC-13 |
| ResourceParseUtils 继承式迁移，原头文件 include ace_kit 基类 | 174 个框架层文件通过 `ResourceParseUtils`（继承版）访问所有方法，零改动 | AC-3 |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | N/A | N/A | N/A |
| 内存 | N/A | N/A | N/A |
| 安全 | N/A | N/A | N/A |
| 可靠性 | 所有新方法对空指针安全 | 单元测试（空指针场景） | `test/unittest/` |
| 问题定位 | 使用 CHECK_NULL_RETURN 宏和框架现有日志机制 | 代码评审 | 源码 |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | N/A | inner API 层，不涉及无障碍 | - |
| 大字体 | N/A | 资源解析支持字体维度解析但不直接处理大字体 | - |
| 深色模式 | 是 | 本 Feature 的核心目的即为深浅色适配提供 inner API | AC-1 ~ AC-15 |
| 多窗口/分屏 | N/A | 不涉及 | - |
| 多用户 | N/A | 不涉及 | - |
| 版本升级 | N/A | inner API 无版本迁移 | - |
| 生态兼容 | N/A | 仅 inner API，不影响生态 | - |

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（做什么/不做什么清晰）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则/恢复契约交叉一致

## context-references

```yaml
context-queries:
  - repo: "openharmony/ace_engine"
    query: "TabJsResType 枚举到 8 个 Tabs 方法的具体映射，需在实现阶段确认 tabs_model_ng.cpp:1416-1470 switch-case 分支"
```

**关键文档：** design.md ADR-1 ~ ADR-5，proposal.md 基线 v1.0
