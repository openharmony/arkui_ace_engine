# 特性规格

> ChipGroup/Chip/IconGroupSuffix 新增 `systemMaterial` 新材质背景配置能力

## 规格元数据

| 字段 | 内容 |
|------|------|
| Spec ID | SPEC-001 |
| 关联需求 | `.codespec/changes/draft-20260610-chipgroup-material-background/proposal.md` |
| 关联设计 | `.codespec/changes/draft-20260610-chipgroup-material-background/design.md` |
| 目标 Feature | 07-01-02 / Feat-01 |
| 复杂度 | 标准 |
| 目标版本 | OpenHarmony-7.0-Release |
| Owner | youzhi92 |
| 状态 | Approved |

## 上下文收集

### 溉及子系统

| 子系统 | 职责 | 修改类型 | 关联源码路径 |
|--------|------|----------|------------|
| ChipGroup | 接收材质属性，Scroll 内插入 EffectComponent 子组件渲染主材质，传递子材质到 Chip | 修改 | `advanced_ui_component/chipgroup/source/chipgroup.ets` |
| Chip | 接收子材质属性（ECSubMaterial），在 Button 上应用 `.systemMaterial()` | 修改 | `advanced_ui_component/chip/source/chip.ets`, `chip_v16.ets` |
| IconGroupSuffix | 接收子材质属性（ECSubMaterial），在 Button 上应用 `.systemMaterial()` | 修改 | `chipgroup.ets` (IconGroupSuffix 部分) |
| uiMaterial | 新增 `convertToECMaterial`/`convertToECSubMaterial` 系统接口 | **新增** | `@ohos.arkui.uiMaterial.ets`, `@ohos.arkui.uiMaterial.d.ets` |
| EffectComponent | 框架已有组件，作为 Scroll 子组件插入 | 无修改 | 框架层 |
| 静态版本 | ChipGroup/Chip 静态组装组件同步修改 | 修改 | `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.ChipGroup.ets`, `@ohos.arkui.advanced.Chip.ets` |
| 接口声明 | ChipGroup/Chip d.ets 新增属性声明 | 修改 | `@ohos.arkui.advanced.ChipGroup.d.ets`, `@ohos.arkui.advanced.Chip.d.ets` |

### 依赖和约束

| 依赖项 | 类型 | 影响 | 处理方式 |
|--------|------|------|----------|
| `uiMaterial.convertToECMaterial`/`convertToECSubMaterial` 接口尚未实现 | **前置依赖** | 阻塞 TASK-1~4 | 与 uiMaterial 团队协调交付优先级 |
| `EffectComponent` 框架组件已存在 | 已有能力 | 无阻塞 | 直接使用 |
| `deviceInfo.sdkApiVersion` 版本隔离机制 | 已有能力 | 无阻塞 | 参照 `chip_v16.ets:499` 和 `segmentbuttonv2.ets:1369` |
| API 26 版本门槛 | 平台约束 | 低于 API 26 不渲染材质 | `deviceInfo.sdkApiVersion >= 26` 条件判断 |
| Public API + System API 审批流程 | 流程依赖 | 交付时间 | 提前准备审批材料，Public API 和 System API 分别推进 |

### 交叉引用设计决策

| ADR | Spec 影响 | 规格约束 |
|------|-----------|----------|
| ADR-1 | ChipGroup 直传 Chip 材质属性 | ChipGroup build() 中 Chip() 构造参数新增材质字段，不通过 ChipItemStyle |
| ADR-2 | ChipGroup Row 不渲染材质， Scroll 内 EffectComponent 渲染主材质 | ChipGroup 最外层 Row 不新增 `.systemMaterial()`；Scroll 内新增 EffectComponent 子组件 |
| ADR-3 | Chip 材质应用在 Button 节点 | Chip chipBuilder() Button 新增 `.systemMaterial()` |
| ADR-4 | IconGroupSuffix 材质应用在 Button 节点 | IconGroupSuffix build() Button 新增 `.systemMaterial()` |
| ADR-5 | 状态切换用独立属性 | ChipGroup 区分选中/非选中态，Chip 区分激活/非激活态 |
| ADR-6 | EffectComponent 性能优化 | ChipGroup Scroll 内 EffectComponent `.systemMaterial(convertToECMaterial)` 设置主材质；Chip/IconGroupSuffix 用 `convertToECSubMaterial` 接收子材质 |
| ADR-7 | API 26 版本隔离 | `deviceInfo.sdkApiVersion >= 26` 条件包裹材质相关逻辑 |

## 用户故事与验收标准

### US-1: ChipGroup 非选中态材质背景

 作为应用开发者， 想为 ChipGroup 设置非选中态的材质背景， 使 ChipGroup 中的 Chip 条目渲染半透明材质效果

 **验收标准：**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-1 | WHEN 开发者设置 ChipGroup 的 `backgroundSystemMaterial` 为 `new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })` 且 `deviceInfo.sdkApiVersion >= 26` THEN ChipGroup 在 Scroll 内插入 EffectComponent 子组件，EffectComponent 上 `.systemMaterial(uiMaterial.convertToECMaterial(backgroundSystemMaterial))` 渲染主材质，每个 Chip 条目接收 `convertToECSubMaterial(backgroundSystemMaterial)` 子材质并渲染半透明材质背景 | 正常 |
| AC-1-V26 | WHEN `deviceInfo.sdkApiVersion < 26` THEN ChipGroup 不插入 EffectComponent 子组件，不传递材质到 Chip，保持原有纯色背景行为 | 版本隔离 |
| AC-1-UNDEF | WHEN 开发者不设置 `backgroundSystemMaterial`（undefined）THEN ChipGroup 不插入 EffectComponent，Chip 条目保持原有纯色背景 | 边界 |
| AC-1-NONE | WHEN 开发者设置 `backgroundSystemMaterial` 为 `Material({ type: MaterialType.NONE })` THEN EffectComponent 不渲染材质效果，Chip 条目不渲染材质效果，等同于不设置 | 边界 |

### US-2: ChipGroup 选中态材质背景
 作为应用开发者， 想为 ChipGroup 设置选中态的材质背景， 使 Chip 条目在选中状态下渲染不同的材质效果

 **验收标准:**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-2 | WHEN 开发者设置 ChipGroup 的 `selectedBackgroundSystemMaterial` 且 Chip 条目处于选中状态 THEN Chip 条目渲染 `convertToECSubMaterial(selectedBackgroundSystemMaterial)` 子材质背景，替换非选中态材质 | 正常 |
| AC-2-SWITCH | WHEN Chip 条目从非选中切换为选中 THEN 材质从 `backgroundSystemMaterial` 切换为 `selectedBackgroundSystemMaterial` | 正常 |
| AC-2-BACK | WHEN Chip 条目从选中切换为非选中 THEN 材质从 `selectedBackgroundSystemMaterial` 切换回 `backgroundSystemMaterial` | 正常 |
| AC-2-UNDEF | WHEN 开发者不设置 `selectedBackgroundSystemMaterial`（undefined）THEN 选中态 Chip 条目使用 `backgroundSystemMaterial` 材质（与非选中态一致） | 边界 |

### US-3: Chip 非激活态材质背景
 作为应用开发者， 想为 Chip 条目设置非激活态的材质背景

 **验收标准:**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-3 | WHEN 开发者设置 Chip 的 `backgroundSystemMaterial`（由 ChipGroup 通过 `convertToECSubMaterial` 传入）THEN Chip 外层 Button 节点渲染 `.systemMaterial(backgroundSystemMaterial)` 材质效果 | 正常 |
| AC-3-OVERLAY | WHEN 开发者同时设置 Chip `backgroundColor` 和 `backgroundSystemMaterial` THEN 材质效果叠加在纯色之上，纯色作为底层 | 正常 |
| AC-3-V26 | WHEN `deviceInfo.sdkApiVersion < 26` THEN Chip 不渲染材质，保持原有纯色背景 | 版本隔离 |

### US-4: Chip 激活态材质背景
 作为应用开发者， 想为 Chip 条目设置激活态的材质背景

 **验收标准:**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-4 | WHEN 开发者设置 Chip 的 `activatedBackgroundSystemMaterial` 且 Chip 条目处于激活状态 THEN Chip 外层 Button 渲染 `.systemMaterial(activatedBackgroundSystemMaterial)` 材质背景 | 正常 |
| AC-4-SWITCH | WHEN Chip 条目从非激活切换为激活 THEN 材质从 `backgroundSystemMaterial` 切换为 `activatedBackgroundSystemMaterial` | 正常 |
| AC-4-BACK | WHEN Chip 条目从激活切换为非激活 THEN 材质从 `activatedBackgroundSystemMaterial` 切换回 `backgroundSystemMaterial` | 正常 |
| AC-4-UNDEF | WHEN 开发者不设置 `activatedBackgroundSystemMaterial`（undefined）THEN 激活态 Chip 条目使用 `backgroundSystemMaterial` 材质（与非激活态一致） | 边界 |

### US-5: IconGroupSuffix 材质背景
 作为应用开发者， 想为 IconGroupSuffix 设置材质背景

 **验收标准:**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-5 | WHEN 开发者设置 ChipGroup 的 `iconBackgroundSystemMaterial` 且 `deviceInfo.sdkApiVersion >= 26` THEN IconGroupSuffix 在 Row 内插入 EffectComponent 子组件，EffectComponent 上 `.systemMaterial(uiMaterial.convertToECMaterial(iconBackgroundSystemMaterial))` 渲染主材质；每个 suffix item Button 渲染 `.systemMaterial(uiMaterial.convertToECSubMaterial(iconBackgroundSystemMaterial))` 子材质背景 | 正常 |
| AC-5-OVERLAY | WHEN 开发者同时设置 IconGroupSuffix `backgroundColor` 和 `iconBackgroundSystemMaterial` THEN 材质效果叠加在纯色之上，纯色作为底层 | 正常 |
| AC-5-V26 | WHEN `deviceInfo.sdkApiVersion < 26` THEN IconGroupSuffix 不渲染材质，保持原有纯色背景 | 版本隔离 |
| AC-5-UNDEF | WHEN 开发者不设置 `iconBackgroundSystemMaterial`（undefined）THEN IconGroupSuffix 保持原有纯色背景 | 边界 |

### US-6: 兼容性保障
 作为应用开发者， 想在不设置新材质属性时保持原有行为不变

 **验收标准:**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-6 | WHEN 开发者不设置任何新材质属性 THEN ChipGroup/Chip/IconGroupSuffix 保持原有纯色背景行为，视觉表现与当前版本完全一致 | 正常 |
| AC-6-V26-LOW | WHEN `deviceInfo.sdkApiVersion < 26` THEN 所有新材质属性被忽略，ChipGroup/Chip/IconGroupSuffix 保持原有纯色背景行为 | 版本隔离 |

### US-7: EffectComponent 性能优化
 作为系统开发者， 想确保多 Chip 同时渲染材质时不出现性能问题

 **验收标准:**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-7 | WHEN ChipGroup 设置 `backgroundSystemMaterial` 且包含 N 个 Chip THEN Scroll 内 EffectComponent 渲染 1 次主材质（`convertToECMaterial`），N 个 Chip 共享同一材质渲染资源（`convertToECSubMaterial`），不各自独立创建材质渲染管线 | 正常 |

### US-8: uiMaterial 系统接口
 作为系统开发者， 想使用 `convertToECMaterial`/`convertToECSubMaterial` 接口将 Material 转换为 EffectComponent 主/子材质

 **验收标准:**

| AC 编号 | 验收标准 | 类型 |
|---------|----------|------|
| AC-8-ECM | WHEN 调用 `uiMaterial.convertToECMaterial(material)` THEN 返回 EffectComponent 主材质（Material 类型），可设置在 EffectComponent `.systemMaterial()` 上 | 正常 |
| AC-8-ECSM | WHEN 调用 `uiMaterial.convertToECSubMaterial(material)` THEN 返回 EffectComponent 子材质（Material 类型），可设置在 Chip/IconGroupSuffix Button `.systemMaterial()` 上 | 正常 |
| AC-8-UNDEF | WHEN 传入 `undefined` THEN `convertToECMaterial`/`convertToECSubMaterial` 返回 `undefined` | 边界 |

## API 影响

### 新增 API

| API | 签名 | 类型 | d.ets 位置 | SysCap | 起始版本 |
|-----|------|------|-----------|--------|----------|
| ChipGroup.backgroundSystemMaterial | `backgroundSystemMaterial?: uiMaterial.Material` | Public | `@ohos.arkui.advanced.ChipGroup.d.ets` | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| ChipGroup.selectedBackgroundSystemMaterial | `selectedBackgroundSystemMaterial?: uiMaterial.Material` | Public | `@ohos.arkui.advanced.ChipGroup.d.ets` | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| Chip.backgroundSystemMaterial | `backgroundSystemMaterial?: uiMaterial.Material` | Public | `@ohos.arkui.advanced.Chip.d.ets` | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| Chip.activatedBackgroundSystemMaterial | `activatedBackgroundSystemMaterial?: uiMaterial.Material` | Public | `@ohos.arkui.advanced.Chip.d.ets` | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| IconGroupSuffix.iconBackgroundSystemMaterial | `iconBackgroundSystemMaterial?: uiMaterial.Material` | Public | `@ohos.arkui.advanced.ChipGroup.d.ets` | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| uiMaterial.convertToECMaterial | `convertToECMaterial(material?: Material): Material` | **System** | `@ohos.arkui.uiMaterial.d.ets` | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| uiMaterial.convertToECSubMaterial | `convertToECSubMaterial(material?: Material): Material` | **System** | `@ohos.arkui.uiMaterial.d.ets` | SystemCapability.ArkUI.ArkUI.Full | API 26 |

### 变更/废弃 API

无变更或废弃 API。

### API 错误码

无新增错误码。材质属性为可选属性，非法值处理： undefined → 不渲染材质。

## 规格规则

### 规则一览

| 规则 ID | 规则名称 | 规则描述 | 关联 AC |
|---------|----------|----------|----------|
| R-1 | 版本隔离规则 | 所有材质相关逻辑（EffectComponent 插入、convertToECMaterial/convertToECSubMaterial 转换、.systemMaterial() 调用）仅在 `deviceInfo.sdkApiVersion >= 26` 时执行；低于 API 26 时全部忽略，保持原有行为 | AC-1-V26, AC-3-V26, AC-5-V26, AC-6-V26-LOW |
| R-2 | EffectComponent 主材质规则 | ChipGroup Scroll 内 EffectComponent 子组件通过 `.systemMaterial(uiMaterial.convertToECMaterial(this.backgroundSystemMaterial))` 设置主材质 | AC-1, AC-7 |
| R-3 | 子材质传递规则 | ChipGroup Scroll 内 EffectComponent `.systemMaterial(convertToECMaterial())` 设置主材质，Chip 用 `convertToECSubMaterial()` 子材质共享资源；IconGroupSuffix Row 内 EffectComponent `.systemMaterial(convertToECMaterial(iconBackgroundSystemMaterial))` 设置主材质，suffix item Button 用 `convertToECSubMaterial()` 子材质共享资源 | AC-1, AC-3, AC-5, AC-7 |
| R-4 | 材质叠加规则 | `.systemMaterial()` 和 `.backgroundColor()` 在同一 Button 节点上调用时，材质叠加在纯色之上，纯色作为底层 | AC-3-OVERLAY, AC-5-OVERLAY |
| R-5 | 状态切换规则 | ChipGroup 区分选中/非选中态（`selectedBackgroundSystemMaterial`/`backgroundSystemMaterial`）；Chip 区分激活/非激活态（`activatedBackgroundSystemMaterial`/`backgroundSystemMaterial`）；参照纯色背景切换逻辑 `getChipNodeBackGroundColor()` | AC-2, AC-2-SWITCH, AC-4, AC-4-SWITCH |
| R-6 | undefined 等同不设置规则 | 所有材质属性为可选（`uiMaterial.Material?`），undefined 时不渲染材质，保持原有纯色背景行为 | AC-1-UNDEF, AC-2-UNDEF, AC-4-UNDEF, AC-5-UNDEF |
| R-7 | MaterialType.NONE 不渲染规则 | `Material({ type: MaterialType.NONE })` 等同不设置，不渲染材质效果 | AC-1-NONE |
| R-8 | 系统接口规则 | `convertToECMaterial`/`convertToECSubMaterial` 为系统接口（`@systemapi`），仅系统应用可调用 | AC-8-ECM, AC-8-ECSM |

## 测试策略

### 测试层级

| 测试层级 | 测试目标 | 覌盖 AC | 验证方式 |
|----------|----------|----------|----------|
| SpecTest Host Preview | 材质属性设置后组件渲染可观测（Inspector 断言） | AC-1~AC-7 | `run_feature.sh --suite-id chipgroup-systemMaterial` |
| Host UT | ChipGroup/Chip 属性赋值、版本隔离、状态切换逻辑 | AC-1~AC-6 | Mock ChipComponent + `deviceInfo` |
| 设备验证 | 真实材质渲染效果（视觉回归） | AC-1~AC-7 | 设备截图比对 |

| uiMaterial 接口 UT | `convertToECMaterial`/`convertToECSubMaterial` 转换正确性 | AC-8-ECM, AC-8-ECSM | Mock native pointer |

### 版本隔离测试矩阵

| 条件 | ChipGroup | Chip | IconGroupSuffix | 预期行为 |
|------|----------|------|-----------------|----------|
| API >= 26 + 设置材质 | EffectComponent 插入 + 主材质渲染 | 子材质渲染 | 子材质渲染 | 材质叠加在纯色上 |
| API >= 26 + 不设置材质 | 无 EffectComponent | 无 `.systemMaterial()` | 无 `.systemMaterial()` | 保持原有纯色行为 |
| API < 26 + 设置材质 | 无 EffectComponent | 无 `.systemMaterial()` | 无 `.systemMaterial()` | 材质属性被忽略，保持原有纯色行为 |
| API < 26 + 不设置材质 | 无 EffectComponent | 无 `.systemMaterial()` | 无 `.systemMaterial()` | 保持原有纯色行为 |

## 受影响文件清单

| 文件 | 修改内容 | 关联 Task |
|------|----------|----------|
| `advanced_ui_component/chipgroup/source/chipgroup.ets` | 新增 @Prop 材质属性 + Scroll 内 EffectComponent + import deviceInfo + 版本隔离条件 | TASK-1, TASK-3, TASK-4 |
| `advanced_ui_component/chip/source/chip.ets` | ChipOptions 新增字段 + chipBuilder() Button .systemMaterial() + import deviceInfo + 版本隔离条件 | TASK-2 |
| `advanced_ui_component/chip/source/chip_v16.ets` | 同步 chip.ets 修改 + 版本隔离条件 | TASK-2 |
| `@ohos.arkui.advanced.ChipGroup.d.ets` | 新增 3 个属性声明 | TASK-5 |
| `@ohos.arkui.advanced.Chip.d.ets` | 新增 2 个属性声明 | TASK-5 |
| `@ohos.arkui.uiMaterial.ets` | 新增 `convertToECMaterial`/`convertToECSubMaterial` 系统接口实现 | TASK-0 |
| `@ohos.arkui.uiMaterial.d.ets` | 新增 2 个系统接口声明 | TASK-0 |
| `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.ChipGroup.ets` | 静态版本同步修改 | TASK-5 |
| `advanced_ui_component_static/assembled_advanced_ui_component/@ohos.arkui.advanced.Chip.ets` | 静态版本同步修改 | TASK-5 |

## design ↔ spec 交叉校验

| 校验项 | design.md | spec.md | 一致？ |
|--------|----------|----------|------|
| 材质传递方式 | ChipGroup 直传 Chip（ADR-1） | ChipGroup build() Chip() 构造参数新增材质字段 | ✅ |
| ChipGroup 不自身渲染 | Row 不渲染材质（ADR-2） | Row 不新增 `.systemMaterial()` | ✅ |
| EffectComponent 位置 | Scroll 子组件（ADR-6） | Scroll 内 EffectComponent 子组件 `.systemMaterial(convertToECMaterial)` | ✅ |
| Chip 材质节点 | Button 节点（ADR-3） | Chip Button `.systemMaterial()` | ✅ |
| IconGroupSuffix 材质节点 | EffectComponent 包裹 Row + Button 子材质（ADR-4） | IconGroupSuffix EffectComponent + suffix item Button `.systemMaterial(convertToECSubMaterial)` | ✅ |
| 状态切换 | 选中/非选中、激活/非激活（ADR-5） | 独立属性 + getter 方法 | ✅ |
| 性能优化 | EffectComponent + convertToECMaterial/SubMaterial（ADR-6） | EffectComponent 主材质 + 子材质共享 | ✅ |
| 版本隔离 | `deviceInfo.sdkApiVersion >= 26`（ADR-7） | API >= 26 条件包裹 | ✅ |
| SysCap | `SystemCapability.ArkUI.ArkUI.Full` | 所有 7 个 API SysCap 一致 | ✅ |
| 系统接口 | `convertToECMaterial`/`convertToECSubMaterial` @systemapi | AC-8 标注系统接口 | ✅ |