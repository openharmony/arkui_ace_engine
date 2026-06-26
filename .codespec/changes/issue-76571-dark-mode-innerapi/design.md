# 架构设计

## 设计元数据

| 字段 | 内容 |
|------|------|
| Design ID | DESIGN-20260509-001 |
| 关联需求 | `proposal.md` |
| 关联 Epic | 不适用 |
| 目标 Feature | FEAT-20260509-001 |
| 复杂度 | 标准 |
| 目标版本 | 引用 manifest.target_release（OpenHarmony-7.0-Release） |
| Owner | 待确认 |
| 状态 | Approved |

## 需求基线摘要

| 项 | 内容 |
|----|------|
| 问题陈述 | 外部子系统需要通过 ace_kit inner API 独立完成深浅色模式适配，当前接口暴露不足 |
| 核心目标 | 暴露 ResourceParseUtils、UIContext 配置查询/反色能力、Tabs ResourceObject 热加载 |
| 不做范围 | Public/System API 变更、前端语法变更、新组件、4 个内部方法（SetNeedReload/NeedReload/MakeNativeNodeInfo/GetThemeConstants） |
| P0 AC | AC-1 ~ AC-15，共 15 条 |

## 上下文和现状

### 涉及仓和模块

| 仓库 | 模块/路径 | 当前职责 | 本 Feature 影响 |
|------|-----------|----------|-----------------|
| ace_engine | `interfaces/inner_api/ace_kit/include/ui/resource/` | 已有 resource_object.h、node_info.h、resource_configuration.h | **新增** resource_parse_utils.h（定义 `ResourceParseUtilsBase` 基类，排除 4 个内部方法） |
| ace_engine | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | UIContext 抽象基类，16 个纯虚方法 | **修改** — 新增 4 个纯虚方法 |
| ace_engine | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.h/cpp` | UIContext 实现，持有 PipelineContext* | **修改** — 新增 4 个实现方法 |
| ace_engine | `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs.h` | Tabs 组件 inner API | **修改** — 新增 8 个重载声明 |
| ace_engine | `interfaces/inner_api/ace_kit/src/view/components/tabs.cpp` | Tabs 实现层，委托 TabsModelNG | **修改** — 新增 8 个重载实现 |
| ace_engine | `frameworks/core/common/resource/resource_parse_utils.h` | 全量资源解析工具类 | **重写** — include ace_kit 头文件，定义 `ResourceParseUtils final : public ResourceParseUtilsBase`（含 4 个内部方法 + `ParseResInteger<T>` 模板体 + `ResourceType` 枚举） |
| ace_engine | `frameworks/core/common/resource/resource_parse_utils.cpp` | ResourceParseUtils 实现 | **修改** — 基类方法定义改为 `ResourceParseUtilsBase::`，派生类方法保持 `ResourceParseUtils::` |
| ace_engine | `interfaces/inner_api/ace_kit/BUILD.gn` | ace_kit 构建配置 | **可能修改** — 如需新增依赖 |

### 适用架构规则

| Rule ID | 适用原因 | 设计结论 | 验证方式 |
|---------|----------|----------|----------|
| OH-ARCH-LAYERING | ace_kit 是 inner API 层，依赖 frameworks/core 实现 | ace_kit src 可 include frameworks 头文件（BUILD.gn 已配置 `$ace_root/frameworks` 为 private include），ace_kit include 目录仅暴露公共接口 | 编译验证 |
| OH-ARCH-API-LEVEL | 新增 inner API 方法 | 仅 inner API，不涉及 Public/System API，无需 SysCap | 代码评审 |
| OH-ARCH-COMPONENT-BUILD | 头文件继承式迁移影响 174 个文件的 include | 采用继承架构：ace_kit 定义 `ResourceParseUtilsBase` 基类，frameworks 定义 `ResourceParseUtils` 派生类继承之，174 个消费者文件无需任何改动（`ResourceParseUtils::Xxx` 通过继承解析到基类方法） | 构建验证 |
| OH-ARCH-ERROR-LOG | UIContext 新方法需要容错 | 所有新方法对空指针和边界条件使用 CHECK_NULL_RETURN 宏 | 单元测试 |

## 不涉及项确认

| 维度 | 需求阶段结论 | 设计阶段处理方式 | 设计结论 |
|------|---------|-------------|----------|
| 性能 | N/A | 保持 N/A | 资源解析和配置查询为非热路径，无性能影响 |
| 安全与权限 | N/A | 保持 N/A | inner API 无权限变更 |
| 兼容性 | 是 | 展开设计 | 原方法不变 + 新增重载；ResourceParseUtils 采用继承式迁移（基类在 ace_kit，派生类在 frameworks），174 个消费者零改动 |
| API/SDK | N/A | 保持 N/A | 不涉及 Public/System API |
| IPC/跨进程 | N/A | 保持 N/A | 无跨进程 |
| 构建与部件 | 是 | 展开设计 | BUILD.gn 无需新增外部依赖；原头文件 include ace_kit 基类头文件（全局 `ace_config` 已包含 ace_kit public include 路径），174 个文件零改动 |

## 关键设计决策

| 决策 ID | 问题 | 推荐方案 | 探索过的替代方案 | 取舍理由 | 影响 |
|---------|------|----------|-----------------|------|------|
| ADR-1 | ResourceParseUtils 头文件迁移方式 | ace_kit 定义 `ResourceParseUtilsBase` 基类（去掉 `final`，排除 4 个内部方法，新增 `protected: needReload_` 和 3 个 private 方法），frameworks 定义 `ResourceParseUtils final : public ResourceParseUtilsBase` 派生类（含 4 个内部方法 + `ParseResInteger<T>` 模板体 + `ResourceType` 枚举）。原头文件 include ace_kit 头文件实现转发。.cpp 中基类方法定义改为 `ResourceParseUtilsBase::`。 | A. 两份共存裁剪版：维护两份独立类定义，易不一致，放弃。B. 纯转发头文件：C++ 不允许跨头文件拆分类定义，放弃。C. 全量移动到 ace_kit：`ParseResInteger<T>` 模板体依赖 `ResourceManager`/`ResourceWrapper`（框架层类型），外部子系统无法解析，放弃 | 外部消费者通过 `ui/resource/resource_parse_utils.h` 引用 `ResourceParseUtilsBase`；框架层内部 174 个文件通过 `core/common/resource/resource_parse_utils.h` 引用 `ResourceParseUtils`（继承基类所有方法），零改动 | 新增基类头文件 + 重写原头文件为继承版 + 更新 .cpp 方法定义命名空间 |
| ADR-2 | HasDarkResource 放在 UIContext 还是 ResourceParseUtils | 放在 UIContext（需求方原始要求），实现委托 ArkTSUtils::CheckDarkResource 逻辑 | A. 放在 ResourceParseUtils：语义上更贴近资源解析，但需求方明确要求在 UIContext。B. 独立工具函数：增加额外入口，无必要 | UIContext 已有 GetColorMode 等配置查询方法的惯例，HasDarkResource 属于同一类别 | UIContext 新增 1 个虚方法 |
| ADR-3 | GetInvertFunc 在 UIContext 层的实现方式 | UIContextImpl 直接调用 `ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag)` | A. 在 ace_kit include 层暴露 ColorInverter 类：违反 ace_kit 头文件不依赖框架内部实现的惯例。B. 通过 PipelineContext 间接获取：PipelineContext 无此接口，需先添加，过重 | ace_kit src 文件可 include 框架层头文件（`$ace_root/frameworks` 在 BUILD.gn private include_dirs 中），直接调用最简 | UIContextImpl 需新增 `#include "core/common/color_inverter.h"` |
| ADR-4 | GetInstanceId 实现方式 | 通过 UIContextImpl 持有的 `context_->GetInstanceId()` 获取 | A. 通过 Container::CurrentIdSafely()：可用但不直接，且与 UIContext 已有通过 context_ 获取信息的惯例不一致 | UIContextImpl 持有 PipelineContext* 指针，直接获取 instanceId 最自然 | 新增 1 个虚方法 |
| ADR-5 | Tabs ResourceObject 重载实现方式 | 每个 TabJsResType 枚举值映射到对应重载方法，内部委托 `TabsModelNG::CreateWithResourceObj` | A. 在 Tabs 层直接操作 pattern 的 AddResObj：跳过 Model 层，不符合分层。B. 通过 ViewStackProcessor 注入：与现有 Tabs 实现模式不一致 | 沿用现有 Tabs::Create → TabsModelNG 委托模式，保持一致性 | 8 个重载方法实现模式统一 |

## 设计骨架

### 骨架范围

| 骨架项 | 目标 | 不包含 | 验证方式 |
|--------|------|--------|----------|
| 新头文件 `ui/resource/resource_parse_utils.h` | 定义 `ResourceParseUtilsBase` 基类（排除 4 个内部方法） | 内部方法的实现代码（仍在原 .cpp 中） | 编译通过 |
| 原头文件 `core/common/resource/resource_parse_utils.h` | 重写为继承版：include ace_kit 头文件 + 定义 `ResourceParseUtils final : public ResourceParseUtilsBase` | 无 | 174 个框架层文件无需改动 |
| 原 .cpp `frameworks/core/common/resource/resource_parse_utils.cpp` | 基类方法定义改为 `ResourceParseUtilsBase::`，派生类方法保持 `ResourceParseUtils::` | 无 | 编译通过 + 现有测试通过 |
| Mock 文件 `test/mock/.../mock_resource_parse_utils.cpp` | `needReload_` 定义改为 `ResourceParseUtilsBase::needReload_` | 无 | 编译通过 |
| UIContext 新增 4 个虚方法声明 | GetConfigPerform、GetInstanceId、HasDarkResource、GetInvertFunc | 完整实现 | 编译通过 |
| UIContextImpl 新增 4 个实现 | 委托到 PipelineContext / SystemProperties / ColorInverter / ResourceManager | 无 | 单元测试 |
| Tabs 新增 8 个重载声明和实现 | 每个 TabJsResType 对应一个重载 | 非需求方要求的 Tabs 属性 | 编译通过 + 单元测试 |

### 接口签名设计

#### UIContext 新增方法（`ui_context.h`）

```cpp
// 配置查询
virtual bool GetConfigPerform() = 0;
virtual int32_t GetInstanceId() = 0;

// 深色资源检查
virtual bool HasDarkResource(const RefPtr<ResourceObject>& resObj) = 0;

// 反色方法
using ColorInvertFunc = std::function<uint32_t(uint32_t)>;
virtual ColorInvertFunc GetInvertFunc(int32_t instanceId, const std::string& nodeTag) = 0;
```

#### UIContextImpl 实现（`ui_context_impl.h/cpp`）

```cpp
bool GetConfigPerform() override {
    return SystemProperties::ConfigChangePerform();
}

int32_t GetInstanceId() override {
    CHECK_NULL_RETURN(context_, -1);
    return context_->GetInstanceId();
}

bool HasDarkResource(const RefPtr<ResourceObject>& resObj) override {
    if (!SystemProperties::GetResourceDecoupling() || !resObj) {
        return false;
    }
    auto resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
    CHECK_NULL_RETURN(resourceAdapter, false);
    int32_t resId = resObj->GetId();
    auto params = resObj->GetParams();
    if (resId == -1 && !params.empty() && params.back().value.has_value()) {
        std::vector<std::string> splitter;
        StringUtils::StringSplitter(params.back().value.value(), '.', splitter);
        return resourceAdapter->ExistDarkResByName(splitter.back(),
            std::to_string(resObj->GetType()));
    }
    return resourceAdapter->ExistDarkResById(std::to_string(resId));
}

ColorInvertFunc GetInvertFunc(int32_t instanceId, const std::string& nodeTag) override {
    return ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag);
}
```

#### Tabs 重载方法签名（`tabs.h`）

```cpp
void SetTabBarWidth(const Dimension& tabBarWidth, const RefPtr<ResourceObject>& resObj);
void SetTabBarHeight(const Dimension& tabBarHeight, const RefPtr<ResourceObject>& resObj);
void SetDivider(const TabsItemDivider& divider, const RefPtr<ResourceObject>& resObj);
void SetScrollableBarModeOptions(const ScrollableBarModeOptions& option,
    const RefPtr<ResourceObject>& resObj);
void SetEffectNodeOption(const TabsEffectNodeOption& option,
    const RefPtr<ResourceObject>& resObj);
void SetBarBackgroundBlurStyle(const BlurStyleOption& styleOption,
    const RefPtr<ResourceObject>& resObj);
void SetBarBackgroundColor(const Color& backgroundColor,
    const RefPtr<ResourceObject>& resObj);
void SetBarBackgroundEffect(const EffectOption& effectOption,
    const RefPtr<ResourceObject>& resObj);
```

#### Tabs 重载实现模式（`tabs.cpp`）

每个重载方法的实现模式统一：

```cpp
void Tabs::SetTabBarWidth(const Dimension& tabBarWidth, const RefPtr<ResourceObject>& resObj)
{
    SetTabBarWidth(tabBarWidth);  // 调用原方法设置值
    CHECK_NULL_VOID(resObj);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node_);
    CHECK_NULL_VOID(frameNode);
    NG::TabsModelNG::CreateWithResourceObj(NG::TabJsResType::BAR_WIDTH, resObj);
}
```

TabJsResType 枚举映射：

| Tabs 方法 | TabJsResType 枚举值 |
|-----------|---------------------|
| SetTabBarWidth | BAR_WIDTH |
| SetTabBarHeight | BAR_HEIGHT |
| SetDivider | DIVIDER_STROKE_WIDTH |
| SetScrollableBarModeOptions | SCROLLABLE_BAR_MARGIN |
| SetEffectNodeOption | BAR_GRID_GUTTER |
| SetBarBackgroundBlurStyle | BlurStyle_INACTIVE_COLOR |
| SetBarBackgroundColor | BAR_BACKGROUND_COLOR |
| SetBarBackgroundEffect | INACTIVE_COLOR |

> **注：** SetDivider 涉及 TabsItemDivider 的 4 个子属性（strokeWidth, color, startMargin, endMargin），当前映射为 DIVIDER_STROKE_WIDTH。实现阶段需对照 `tabs_model_ng.cpp` 的 HandleDivider 系列方法确认是否需要传入多个 resObj。

#### ResourceParseUtils 继承式迁移

**ace_kit 基类**（`interfaces/inner_api/ace_kit/include/ui/resource/resource_parse_utils.h`）：

定义 `ResourceParseUtilsBase` 类（去掉 `final`），对外暴露。外部消费者引用方式：`#include "ui/resource/resource_parse_utils.h"`

变更内容：
1. 类名 `ResourceParseUtils` → `ResourceParseUtilsBase`
2. 去掉 `final`
3. 删除 `SetNeedReload`、`NeedReload` 方法声明
4. 删除 `MakeNativeNodeInfo` 方法声明
5. 删除 `GetThemeConstants` 方法声明
6. 删除 `ParseResInteger<T>` 模板（移至派生类，因其 body 依赖 `ResourceManager`/`ResourceWrapper`）
7. 新增 `protected: static bool needReload_;`
8. 新增 `class ResourceWrapper;` 前向声明
9. 原有 3 个 private 方法改为 `protected`
10. `DECLARE_ACE_TYPE(ResourceParseUtilsBase, AceType)`

**frameworks 派生类**（`frameworks/core/common/resource/resource_parse_utils.h`）：

定义 `ResourceParseUtils final : public ResourceParseUtilsBase`，include ace_kit 基类头文件。框架层内部继续通过 `#include "core/common/resource/resource_parse_utils.h"` 引用。

派生类新增：
1. `using ResourceParseUtilsBase::ParseResInteger;`（引入基类重载）
2. `SetNeedReload()` / `NeedReload()` — inline 方法，操作基类 `needReload_`
3. `MakeNativeNodeInfo()` — 声明，实现在 .cpp
4. `GetThemeConstants()` — 声明，实现在 .cpp（0 个外部调用者）
5. `ParseResInteger<T>` 模板 — 带 body（依赖 `ResourceManager`/`ResourceWrapper`/`ResourceType`）
6. `ResourceType` 枚举
7. `NG::UINode` 前向声明
8. `#include "core/common/resource/resource_manager.h"` 和 `"resource_wrapper.h"`

**.cpp 更新**（`frameworks/core/common/resource/resource_parse_utils.cpp`）：

- 所有基类方法定义：`ResourceParseUtils::` → `ResourceParseUtilsBase::`（约 30 处）
- 派生类方法（`GetThemeConstants`、`MakeNativeNodeInfo`）保持 `ResourceParseUtils::`
- `needReload_` 定义：`ResourceParseUtils::` → `ResourceParseUtilsBase::`
- 显式模板实例化：`ResourceParseUtils::` → `ResourceParseUtilsBase::`
- 自由函数中对 `ResourceParseUtils::GetThemeConstants(...)` 的调用保持不变（通过继承解析）

**Mock 更新**（`test/mock/.../mock_resource_parse_utils.cpp`）：

- `ResourceParseUtils::needReload_` → `ResourceParseUtilsBase::needReload_`

**消费者影响：**

| 消费者类型 | 引用头文件 | 看到的类名 | 方法调用方式 | 改动量 |
|-----------|-----------|-----------|-------------|--------|
| 外部子系统 | `ui/resource/resource_parse_utils.h` | `ResourceParseUtilsBase` | `ResourceParseUtilsBase::ParseResColor(...)` | 新代码 |
| 框架层 174 个文件 | `core/common/resource/resource_parse_utils.h` | `ResourceParseUtils`（继承版） | `ResourceParseUtils::ParseResColor(...)` 通过继承解析到基类 | **0 改动** |
| `SetNeedReload` 等调用者（10 文件） | 同上 | `ResourceParseUtils` | `ResourceParseUtils::SetNeedReload(...)` 在派生类中定义 | **0 改动** |
| `MakeNativeNodeInfo` 调用者（22 文件） | 同上 | `ResourceParseUtils` | `ResourceParseUtils::MakeNativeNodeInfo(...)` 在派生类中定义 | **0 改动** |

### 骨架 Spec 拆分

| Task ID | 目标 | 受影响文件 | AC |
|---------|------|------------|-----|
| TASK-001 | ResourceParseUtils 继承式迁移 | `ui/resource/resource_parse_utils.h`（新增基类）、`frameworks/core/common/resource/resource_parse_utils.h`（重写为继承版）、`resource_parse_utils.cpp`（命名空间更新）、`mock_resource_parse_utils.cpp` | AC-1, AC-2, AC-3 |
| TASK-002 | UIContext 新增 4 个方法 | `ui_context.h`（修改）、`ui_context_impl.h/cpp`（修改） | AC-4 ~ AC-11 |
| TASK-003 | Tabs 新增 8 个 ResourceObject 重载 | `tabs.h`（修改）、`tabs.cpp`（修改） | AC-12 ~ AC-15 |

## 后续 Spec 拆分

| Spec | 目的 | 依赖 | 输出 |
|------|------|------|------|
| spec.md | 固化用户可见行为和 AC | 需求基线 + 本 Design | Feature 规格 |
| TASK-001 | ResourceParseUtils 继承式迁移 | 本 Design | 基类头文件 + 继承版头文件 + .cpp 命名空间更新 + 编译验证 |
| TASK-002 | UIContext 新增方法 | 本 Design | 接口声明 + 实现 + 单元测试 |
| TASK-003 | Tabs ResourceObject 重载 | 本 Design | 8 个重载声明 + 实现 + 单元测试 |

---

## 数据流/控制流

### UIContext 新增方法调用流

| 步骤 | 调用方 | 被调用方 | 数据/接口 | 说明 |
|------|--------|----------|-----------|------|
| 1 | 外部子系统 | UIContext::GetConfigPerform() | 无参数 → bool | UIContextImpl 委托 SystemProperties::ConfigChangePerform() |
| 2 | 外部子系统 | UIContext::GetInstanceId() | 无参数 → int32_t | UIContextImpl 从 context_->GetInstanceId() 获取 |
| 3 | 外部子系统 | UIContext::HasDarkResource(resObj) | ResourceObject → bool | UIContextImpl 委托 ResourceManager 查询 ExistDarkResById/ExistDarkResByName |
| 4 | 外部子系统 | UIContext::GetInvertFunc(id, tag) | (int32_t, string) → function | UIContextImpl 委托 ColorInverter::GetInstance().GetInvertFunc() |

### Tabs ResourceObject 重载调用流

| 步骤 | 调用方 | 被调用方 | 数据/接口 | 说明 |
|------|--------|----------|-----------|------|
| 1 | 外部子系统 | Tabs::SetXxx(value, resObj) | (原参数, ResourceObject) → void | 调用原方法设值，然后注册 ResourceObject |
| 2 | Tabs 重载 | TabsModelNG::CreateWithResourceObj(type, resObj) | (TabJsResType, ResourceObject) | 注册资源更新回调到 TabsPattern |
| 3 | 配置变更时 | TabsPattern::ReloadResources() | 无 → 自动刷新 | 回调重新解析 ResourceObject 并更新属性值 |

## 测试性设计

| 测试层级 | 测试目标 | Mock 策略 | 验证方式 |
|----------|----------|-----------|----------|
| 单元测试 | UIContext 新增 4 个方法 | Mock PipelineContext、ResourceManager、ColorInverter | gtest |
| 单元测试 | Tabs 8 个 ResourceObject 重载 | Mock TabsModelNG、FrameNode | gtest |
| 单元测试 | ResourceParseUtils 头文件路径可达性 | 直接 include 编译 | 编译通过 |
| 单元测试 | 兼容性（原方法不回归） | 无 Mock | gtest 现有用例全部通过 |

## 风险和开放问题

| 项 | 类型 | 影响 | 处理方式 | Owner |
|----|------|------|----------|-------|
| TabJsResType 枚举映射未完全确认 | API | 低 | SetDivider 映射为 DIVIDER_STROKE_WIDTH，实现时对照 HandleDivider 系列方法确认子属性处理 | 待确认 |
| HasDarkResource 的 ResourceManager 依赖是否在 ace_kit src 编译环境中可用 | 构建 | 中 | 验证 BUILD.gn 依赖链，确认 `frameworks/core/common/resource/resource_manager.h` 可通过 private include 访问 | 待确认 |
| 174 个 include 引用文件的兼容性 | 构建 | 低 | 采用继承架构，`ResourceParseUtils` 继承 `ResourceParseUtilsBase`，所有 `ResourceParseUtils::Xxx` 调用通过继承解析到基类方法，174 个文件零改动。已验证：`MakeNativeNodeInfo`（22 个调用者）、`SetNeedReload`/`NeedReload`（10 个调用者）均通过 `ResourceParseUtils` 派生类访问 | 已解决 |

## 设计审批

- [x] 需求基线已确认，设计覆盖 P0/P1 AC（15 条 AC 全部有对应设计方案）
- [x] 不涉及项已承接，N/A 和展开项都有结论
- [x] 涉及仓和模块职责清楚（仅 ace_engine，6 个影响模块）
- [x] 适用架构规则已识别并形成设计结论（4 条规则）
- [x] 分层和子系统边界合规（ace_kit src 可 include frameworks，ace_kit include 仅暴露公共接口）
- [x] API 变更有签名和兼容性说明（纯新增，不破坏现有 API）
- [x] BUILD.gn/bundle.json 影响明确（可能需微调，无需新增外部依赖）
- [x] 骨架 Spec 和后续 Spec 拆分明确（3 个 Task）
- [x] 关键设计决策有理由和影响说明（5 个 ADR）
- [x] ADR-1 已更新为继承式迁移方案（原"两份共存"方案已废弃）
- [x] 风险和开放问题有 Owner

**结论:** 通过
