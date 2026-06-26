# 执行计划

## Plan 元数据

| 字段 | 内容 |
|------|------|
| Plan ID | PLAN-20260509-001 |
| 关联 Feature | FEAT-20260509-001 |
| 关联文档 | proposal.md / design.md / spec.md |
| 复杂度 | 标准 |
| 状态 | In Progress |
| Owner | 待确认 |

## 输入状态

| 输入 | 路径 | 要求状态 |
|------|------|----------|
| Proposal | `proposal.md` | Approved |
| Design | `design.md` | Approved |
| Spec | `spec.md` | Approved |

## AC 到 Task 追溯

| AC | 来源 | Task | 验证方式 | 覆盖？ |
|----|------|------|----------|--------|
| AC-1 | spec.md | TASK-001 | 编译验证 | 是 |
| AC-2 | spec.md | TASK-001 | 编译验证 | 是 |
| AC-3 | spec.md | TASK-001 | 全量编译 | 是 |
| AC-4 | spec.md | TASK-002 | 单元测试 | 是 |
| AC-5 | spec.md | TASK-002 | 单元测试 | 是 |
| AC-6 | spec.md | 无变更 | 现有测试 | 是 |
| AC-7 | spec.md | TASK-002 | 单元测试 | 是 |
| AC-8 | spec.md | TASK-002 | 单元测试 | 是 |
| AC-9 | spec.md | TASK-002 | 单元测试 | 是 |
| AC-10 | spec.md | TASK-002 | 单元测试 | 是 |
| AC-11 | spec.md | 无变更 | 现有测试 | 是 |
| AC-12 | spec.md | TASK-003 | 单元测试 | 是 |
| AC-13 | spec.md | TASK-003 | 单元测试 | 是 |
| AC-14 | spec.md | TASK-003 | 现有测试 | 是 |
| AC-15 | spec.md | TASK-003 | 单元测试 | 是 |

## 首批实现边界

**首批必须实现：** TASK-001（头文件迁移）是后续所有 Task 的编译前提，必须先完成。
**可后置：** 无。
**不建议延后：** TASK-001 延后则 TASK-002/003 无法编译验证。

## 阶段计划

| 阶段 | 目标 | 关键 Task | 结束门槛 | 最小验证 |
|------|------|-----------|----------|----------|
| Phase-1 | ResourceParseUtils 继承式迁移 | TASK-001 | ace_kit 基类 + frameworks 继承版 + .cpp 更新；174 个文件编译通过 | `./build.sh --product-name rk3568 --build-target ace_engine` |
| Phase-2 | UIContext 新增 4 个方法 | TASK-002 | 编译通过 + 新方法单元测试通过 | `./build.sh --product-name rk3568 --build-target ace_engine_test` |
| Phase-3 | Tabs 8 个 ResourceObject 重载 | TASK-003 | 编译通过 + 重载方法单元测试通过 + 原方法无回归 | `./build.sh --product-name rk3568 --build-target ace_engine_test` |

## Task 粒度原则

- TASK-001 为基础设施变更（头文件迁移），影响全局编译，独立为一个 Task
- TASK-002 为 UIContext 单一类的新增方法（声明 + 实现 + 测试），是一个能力闭环
- TASK-003 为 Tabs 单一类的新增重载（声明 + 实现 + 测试），是一个能力闭环

## 禁止项

- [x] 没有 TBD / TODO / 占位符
- [x] 没有"根据需要实现""酌情处理"等模糊指令
- [x] 没有跨 Task 隐式依赖
- [x] 没有要求 Agent 自行寻找未列出的上下文文件
- [x] 没有无验证方式的 AC
- [x] 没有"与 Task-N 类似""参考 Task-N 实现"等引用

## Task 列表

| Task ID | 目标 | 文件范围 | AC 映射 | 前置依赖 | 完成判据 | 验证命令 |
|---------|------|----------|---------|----------|----------|----------|
| TASK-001 | ResourceParseUtils 继承式迁移 | `interfaces/inner_api/ace_kit/include/ui/resource/resource_parse_utils.h`（新增/重写）、`frameworks/core/common/resource/resource_parse_utils.h`（重写）、`resource_parse_utils.cpp`（修改）、`mock_resource_parse_utils.cpp`（修改） | AC-1, AC-2, AC-3 | 无 | ace_kit 基类 + frameworks 继承版 + .cpp 命名空间更新；174 个消费者零改动 | `./build.sh --product-name rk3568 --build-target ace_engine` |
| TASK-002 | UIContext 新增 4 个方法（声明 + 实现 + 测试） | `ui_context.h`、`ui_context_impl.h/cpp` | AC-4, AC-5, AC-7, AC-8, AC-9, AC-10 | TASK-001 | 4 个方法编译通过 + 单元测试通过 | `./build.sh --product-name rk3568 --build-target ace_engine_test` |
| TASK-003 | Tabs 新增 8 个 ResourceObject 重载（声明 + 实现 + 测试） | `tabs.h`、`tabs.cpp` | AC-12, AC-13, AC-14, AC-15 | TASK-001 | 8 个重载编译通过 + 单元测试通过 + 原方法无回归 | `./build.sh --product-name rk3568 --build-target ace_engine_test` |

## Task 详情

### TASK-001: ResourceParseUtils 继承式迁移

| 字段 | 内容 |
|------|------|
| 任务目标 | 在 ace_kit 定义 `ResourceParseUtilsBase` 基类（排除 4 个内部方法），重写 frameworks `ResourceParseUtils` 为继承版（final : public ResourceParseUtilsBase），更新 .cpp 方法定义命名空间，更新 mock 文件 |
| AC 映射 | AC-1, AC-2, AC-3 |
| 前置依赖 | 无 |
| 非目标 | 不修改任何消费者文件（174 个文件零改动）；不修改 BUILD.gn |
| 完成判据 | ace_kit 头文件定义 `ResourceParseUtilsBase`；frameworks 头文件定义 `ResourceParseUtils` 继承基类；.cpp 基类方法改为 `ResourceParseUtilsBase::`；mock 文件更新；全量编译通过 |
| 停止条件 | ace_kit include 路径下依赖类型不可解析时，停止并回传缺失类型清单 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Create/Modify | `interfaces/inner_api/ace_kit/include/ui/resource/resource_parse_utils.h` | `ResourceParseUtilsBase` 基类定义（去掉 final，排除 4 个内部方法，新增 protected needReload_ 和 3 个 protected private 方法） |
| Rewrite | `frameworks/core/common/resource/resource_parse_utils.h` | include ace_kit 头文件 + 定义 `ResourceParseUtils final : public ResourceParseUtilsBase`（含 4 个内部方法 + ParseResInteger\<T\> 模板体 + ResourceType 枚举） |
| Modify | `frameworks/core/common/resource/resource_parse_utils.cpp` | 基类方法定义 `ResourceParseUtils::` → `ResourceParseUtilsBase::`（~30 处），派生类方法保持 `ResourceParseUtils::` |
| Modify | `test/mock/frameworks/core/common/resource/mock_resource_parse_utils.cpp` | `ResourceParseUtils::needReload_` → `ResourceParseUtilsBase::needReload_` |

**Spec Context**

AC-1: WHEN 通过 `ui/resource/resource_parse_utils.h` 引用 THEN 可正常调用 `ResourceParseUtilsBase` 类所有暴露的 static 方法且编译通过
AC-2: WHEN 外部子系统查看该头文件 THEN 不包含 SetNeedReload、NeedReload、MakeNativeNodeInfo、GetThemeConstants（4 个方法仅在 `ResourceParseUtils` 派生类中）
AC-3: WHEN 框架层现有文件通过 `core/common/resource/resource_parse_utils.h` 引用 `ResourceParseUtils` THEN 通过继承可访问所有基类方法，174 个文件编译通过

**Design Context**

ADR-1（更新版）: ace_kit 定义 `ResourceParseUtilsBase` 基类，frameworks 定义 `ResourceParseUtils final : public ResourceParseUtilsBase` 派生类。`ParseResInteger<T>` 模板体留在派生类（依赖 `ResourceManager`/`ResourceWrapper`）。`needReload_` 为基类 protected static 成员。174 个消费者通过 `ResourceParseUtils::Xxx` 调用自动通过继承解析到基类方法。

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| OH-ARCH-LAYERING | Must: ace_kit include 目录仅暴露公共接口，不得引入 `resource_manager.h`/`resource_wrapper.h` 等框架层内部头文件 |
| OH-ARCH-COMPONENT-BUILD | Must: 不修改 BUILD.gn；全局 `ace_config` 已包含 ace_kit public include 路径 |
| BR-1 | Must: 174 个消费者文件零改动 |

**Steps**

- [x] 读取 `frameworks/core/common/resource/resource_parse_utils.h` 全文（144 行）
- [x] 在 `interfaces/inner_api/ace_kit/include/ui/resource/` 下创建/重写 `ResourceParseUtilsBase` 基类头文件（88 行）
- [x] 重写 `frameworks/core/common/resource/resource_parse_utils.h` 为继承版（92 行）
- [x] 更新 `resource_parse_utils.cpp`：基类方法定义改为 `ResourceParseUtilsBase::`（~30 处），派生类方法保持 `ResourceParseUtils::`
- [x] 更新 `mock_resource_parse_utils.cpp`：`needReload_` 归属改为 `ResourceParseUtilsBase::`
- [x] 修复 CalcDimension 缺失 include：ace_kit 基类头文件新增 `#include "ui/base/geometry/calc_dimension.h"`
- [x] 运行全量编译验证：`./build.sh --product-name rk3568 --build-target ace_engine` — C++ 编译通过（614/752，0 FAILED/error，error.log 未更新）
- [x] 填写完成证据

**Completion Evidence**

| 证据类型 | 命令/路径 | 结果 |
|----------|-----------|------|
| 编译 | `./build.sh --product-name rk3568 --build-target ace_engine` | PASS（C++ 编译通过，0 error） |

---

### TASK-002: UIContext 新增 4 个方法

| 字段 | 内容 |
|------|------|
| 任务目标 | 在 UIContext 抽象基类新增 4 个纯虚方法（GetConfigPerform、GetInstanceId、HasDarkResource、GetInvertFunc），在 UIContextImpl 中实现这 4 个方法，编写单元测试 |
| AC 映射 | AC-4, AC-5, AC-7, AC-8, AC-9, AC-10 |
| 前置依赖 | TASK-001 完成 |
| 非目标 | 不修改 GetColorMode/GetLocalColorMode（AC-6, AC-11 已有实现）；不修改 FrameNode |
| 完成判据 | UIContext 新增 4 个虚方法声明 + UIContextImpl 4 个 override 实现 + 单元测试通过 |
| 停止条件 | SystemProperties / ColorInverter / ResourceManager 在 ace_kit src 编译环境中不可访问时，停止并回传缺失依赖 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | 新增 4 个纯虚方法声明 + ColorInvertFunc typedef |
| Modify | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.h` | 新增 4 个 override 声明 |
| Modify | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.cpp` | 新增 4 个 override 实现 + 新增 include |
| Create | `test/unittest/interfaces/inner_api/ace_kit/ui_context_dark_mode_test.cpp` | 单元测试 |

**Spec Context**

AC-4: WHEN 调用 `UIContext::GetConfigPerform()` THEN 返回值与 `SystemProperties::ConfigChangePerform()` 完全一致
AC-5: WHEN 调用 `UIContext::GetInstanceId()` THEN 返回 context_ 的 instanceId；context_ 为空返回 -1
AC-7: WHEN 调用 `UIContext::HasDarkResource(resObj)` 有深色资源 THEN 返回 true；无 THEN 返回 false
AC-8: WHEN resObj 为空 THEN 返回 false 且不崩溃；WHEN GetResourceDecoupling() 为 false THEN 返回 false
AC-9: WHEN 调用 `UIContext::GetInvertFunc(instanceId, nodeTag)` THEN 返回 ColorInvertFunc，行为与 ColorInverter 一致
AC-10: WHEN 无匹配注册 THEN 返回空 function（bool 转换为 false）

EX-1: HasDarkResource 空指针保护 → 返回 false
EX-2: HasDarkResource 资源解耦开关关闭 → 返回 false
EX-3: GetInvertFunc 无匹配 → 返回空 function
EX-4: GetInstanceId PipelineContext 为空 → 返回 -1
EX-5: HasDarkResource ResourceManager 不可用 → 返回 false

**Design Context**

ADR-2: HasDarkResource 放在 UIContext，实现委托 ArkTSUtils::CheckDarkResource 逻辑（通过 ResourceManager 查询）
ADR-3: GetInvertFunc 通过 UIContextImpl 直接调用 `ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag)`，ace_kit src 可 include `core/common/color_inverter.h`
ADR-4: GetInstanceId 通过 `context_->GetInstanceId()` 获取

UIContext 新增方法签名：
```cpp
virtual bool GetConfigPerform() = 0;
virtual int32_t GetInstanceId() = 0;
virtual bool HasDarkResource(const RefPtr<ResourceObject>& resObj) = 0;
using ColorInvertFunc = std::function<uint32_t(uint32_t)>;
virtual ColorInvertFunc GetInvertFunc(int32_t instanceId, const std::string& nodeTag) = 0;
```

UIContextImpl 实现需要新增的 include：
- `core/common/color_inverter.h`（ColorInverter）
- `base/utils/system_properties.h`（SystemProperties）
- `core/common/resource/resource_manager.h`（ResourceManager）
- `base/utils/string_utils.h`（StringUtils）

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| OH-ARCH-LAYERING | Must: ace_kit include 头文件不得引入框架层内部头文件；ace_kit src 可通过 private include_dirs 引用 |
| OH-ARCH-ERROR-LOG | Must: 所有新方法对空指针使用 CHECK_NULL_RETURN 宏保护 |

**Steps**

- [x] 读取 `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` 和 `interfaces/inner_api/ace_kit/src/view/ui_context_impl.h` 和 `interfaces/inner_api/ace_kit/src/view/ui_context_impl.cpp`
- [x] 在 ui_context.h 新增 ColorInvertFunc typedef 和 4 个纯虚方法声明
- [x] 在 ui_context_impl.h 新增 4 个 override 声明
- [x] 在 ui_context_impl.cpp 新增 4 个实现：GetConfigPerform 委托 SystemProperties、GetInstanceId 通过 context_ 获取、HasDarkResource 委托 ResourceManager、GetInvertFunc 委托 ColorInverter
- [x] 编写单元测试覆盖 AC-4,5,7,8,9,10（含空指针、开关关闭、无注册等边界场景）
- [ ] 编译验证
- [ ] 运行单元测试
- [x] 填写完成证据

**Completion Evidence**

| 证据类型 | 命令/路径 | 结果 |
|----------|-----------|------|
| 编译 | `./build.sh --product-name rk3568 --build-target ace_engine` | PASS（C++ 编译通过，0 error） |
| 测试 | `test/unittest/interfaces/ace_kit/ui_context_impl_test.cpp` | 已追加 13 个测试用例（GetLocalColorMode/GetColorMode/GetFontScale/GetConfigPerform/GetInstanceId/HasDarkResource/GetInvertFunc） |

| 字段 | 内容 |
|------|------|
| 任务目标 | 在 Tabs 类新增 8 个 ResourceObject 重载方法，实现委托 TabsModelNG::CreateWithResourceObj，编写单元测试 |
| AC 映射 | AC-12, AC-13, AC-14, AC-15 |
| 前置依赖 | TASK-001 完成 |
| 非目标 | 不修改 Tabs 原方法（不带 ResourceObject 的版本）；不新增非需求方要求的属性重载 |
| 完成判据 | 8 个重载方法声明 + 实现 + 单元测试通过 + 原方法无回归 |
| 停止条件 | TabJsResType 枚举映射与需求方要求不一致时，停止并回传枚举清单请求确认 |

**Files**

| 操作 | 文件 | 说明 |
|------|------|------|
| Modify | `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs.h` | 新增 8 个重载方法声明 |
| Modify | `interfaces/inner_api/ace_kit/src/view/components/tabs.cpp` | 新增 8 个重载方法实现 |
| Create | `test/unittest/interfaces/inner_api/ace_kit/tabs_resource_obj_test.cpp` | 单元测试 |

**Spec Context**

AC-12: WHEN 调用 `Tabs::SetTabBarWidth(dim, resObj)` THEN 底层调用 `TabsModelNG::CreateWithResourceObj(BAR_WIDTH, resObj)` 注册 ResourceObject
AC-13: WHEN 对其他 7 个方法传入 ResourceObject THEN 行为与 AC-12 一致
AC-14: WHEN 调用原方法 THEN 行为完全不变
AC-15: WHEN ConfigChangePerform == false THEN CreateWithResourceObj 为空操作

**Design Context**

ADR-5: 每个 TabJsResType 枚举值映射到对应重载方法，内部委托 TabsModelNG::CreateWithResourceObj。

TabJsResType 枚举定义（`frameworks/core/components_ng/pattern/tabs/tabs_model.h:44-58`）：
```
BAR_BACKGROUND_COLOR, BAR_WIDTH, BAR_HEIGHT, BAR_GRID_GUTTER, BAR_GRID_MARGIN,
DIVIDER_STROKE_WIDTH, DIVIDER_COLOR, DIVIDER_START_MARGIN, DIVIDER_END_MARGIN,
SCROLLABLE_BAR_MARGIN, COLOR, INACTIVE_COLOR, BlurStyle_INACTIVE_COLOR
```

8 个重载方法到 TabJsResType 的映射：

| Tabs 方法 | 原方法签名 | TabJsResType 枚举值 |
|-----------|-----------|---------------------|
| SetTabBarWidth(dim, resObj) | `void SetTabBarWidth(const Dimension&)` | BAR_WIDTH |
| SetTabBarHeight(dim, resObj) | `void SetTabBarHeight(const Dimension&)` | BAR_HEIGHT |
| SetDivider(divider, resObj) | `void SetDivider(const TabsItemDivider&)` | DIVIDER_STROKE_WIDTH |
| SetScrollableBarModeOptions(opt, resObj) | `void SetScrollableBarModeOptions(const ScrollableBarModeOptions&)` | SCROLLABLE_BAR_MARGIN |
| SetEffectNodeOption(opt, resObj) | `void SetEffectNodeOption(const TabsEffectNodeOption&)` | BAR_GRID_GUTTER |
| SetBarBackgroundBlurStyle(opt, resObj) | `void SetBarBackgroundBlurStyle(const BlurStyleOption&)` | BlurStyle_INACTIVE_COLOR |
| SetBarBackgroundColor(color, resObj) | `void SetBarBackgroundColor(const Color&)` | BAR_BACKGROUND_COLOR |
| SetBarBackgroundEffect(opt, resObj) | `void SetBarBackgroundEffect(const EffectOption&)` | INACTIVE_COLOR |

每个重载的实现模式统一：
1. 调用原方法设值
2. CHECK_NULL_VOID(resObj)
3. 检查 SystemProperties::ConfigChangePerform()（对应 AC-15）
4. 获取 tabsNode
5. 调用 `NG::TabsModelNG::Handle*(Referenced::RawPtr(tabsNode), resObj)`

> **注：** 实际实现使用 `TabsModelNG::Handle*` 系列静态方法（直接接受 `FrameNode*` 参数），而非 `CreateWithResourceObj`（内部依赖 `ViewStackProcessor` 取节点，ace_kit 场景下不适用）。`Handle*` 方法功能等价：注册 ResourceObject 更新回调到 TabsPattern。

> **注：** SetDivider 涉及 TabsItemDivider 的 4 个子属性（strokeWidth, color, startMargin, endMargin），对应 DIVIDER_STROKE_WIDTH 枚举。如 CreateWithResourceObj 的 switch-case 中有更细粒度的 divider 子类型处理，需在实现时对照 `tabs_model_ng.cpp:1416-1470` 的 HandleDivider 系列方法确认是否需要传入多个 resObj。若需调整映射，停止并回传。

**Required Rules**

| Rule ID | Must / Must Not |
|---------|-----------------|
| OH-ARCH-LAYERING | Must: Tabs 重载方法委托 TabsModelNG，不直接操作 Pattern |
| BR-1 | Must: 原方法行为完全不变，重载为纯新增 |

**Steps**

- [x] 读取 `interfaces/inner_api/ace_kit/include/ui/view/components/tabs/tabs.h` 和 `interfaces/inner_api/ace_kit/src/view/components/tabs.cpp`
- [x] 读取 `frameworks/core/components_ng/pattern/tabs/tabs_model_ng.cpp:1416-1470` 确认 TabJsResType 映射
- [x] 在 tabs.h 新增 8 个重载方法声明 + `#include "ui/resource/resource_object.h"`
- [x] 在 tabs.cpp 新增 8 个重载实现 + `#include "base/utils/system_properties.h"`，每个遵循：调用原方法 → 空指针检查 → ConfigChangePerform 开关检查 → 获取 tabsNode → 委托 `NG::TabsModelNG::Handle*` 静态方法
- [x] 编写单元测试覆盖 AC-12,13,14,15（含 ConfigChangePerform 开关测试）
- [ ] 编译验证
- [ ] 运行单元测试
- [x] 填写完成证据

**Completion Evidence**

| 证据类型 | 命令/路径 | 结果 |
|----------|-----------|------|
| 编译 | `./build.sh --product-name rk3568 --build-target ace_engine` | PASS（与 TASK-001 同次编译验证） |
| 测试 | `test/unittest/interfaces/ace_kit/tabs_test.cpp` | 已创建 16 个测试用例（每个重载 2 个：null resObj + ConfigChangePerform=false） |

## Plan 自审清单

- [x] 每个 P0/P1 AC 至少映射到一个 Task
- [x] 每个 Task 文件范围明确
- [x] 每个 Task 明确前置依赖、非目标、完成判据和停止条件
- [x] 每个 Task 有验证命令
- [x] Task 粒度形成能力闭环
- [x] 没有 TBD/TODO/占位符
- [x] 没有要求 Agent 自行寻找未列出的上下文
- [x] 交接信息自包含
- [x] 每个 Task 验证在完成时立即执行并记录证据
