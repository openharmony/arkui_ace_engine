# 执行计划

> ChipGroup/Chip/IconGroupSuffix 新增 `systemMaterial` 新材质背景配置能力

## 计划元数据

| 字段 | 内容 |
|------|------|
| Plan ID | PLAN-001 |
| 关联需求 | `.codespec/changes/draft-20260610-chipgroup-material-background/proposal.md` |
| 关联设计 | `.codespec/changes/draft-20260610-chipgroup-material-background/design.md` |
| 关联规格 | `.codespec/changes/draft-20260610-chipgroup-material-background/spec.md` |
| 目标 Feature | 07-01-02 / Feat-01 |
| 复杂度 | 标准 |
| 目标版本 | OpenHarmony-7.0-Release |
| Owner | youzhi92 |
| 状态 | Draft |

## 前置依赖

| 依赖项 | 类型 | 阻塞 Task | 处理方式 |
|--------|------|-----------|----------|
| uiMaterial `convertToECMaterial`/`convertToECSubMaterial` 接口尚未实现 | **前置依赖** | TASK-1~4 全部 | 与 uiMaterial 团队协调交付优先级，TASK-0 需先完成 |
| API 26 版本起始审批确认 | 流程依赖 | 审批流程 | 提前准备审批材料 |

## Task 执行序列

```
TASK-0 (uiMaterial 接口) ─┬─→ TASK-1 (ChipGroup 属性 + EffectComponent) ─→ TASK-2 (Chip 属性) ─→ TASK-4 (材质传递)
                          │                                                ─→ TASK-3 (IconGroupSuffix) ─→ TASK-4
                          │
                          └──────────────────────────────────────────────→ TASK-5 (静态版本) ─→ TASK-6 (SpecTest)
```

## Task 清单

### TASK-0: uiMaterial 新增 convertToECMaterial/convertToECSubMaterial 系统接口

| 字段 | 内容 |
|------|------|
| 目标 | 在 `uiMaterial` namespace 新增 2 个系统接口 |
| 类型 | **System API**（@systemapi） |
| 受影响文件 | `@ohos.arkui.uiMaterial.ets`（实现）、`@ohos.arkui.uiMaterial.d.ets`（声明） |
| 关联 AC | AC-8-ECM, AC-8-ECSM |
| 依赖 | design.md + spec.md Approved（已通过） |
| 验证方式 | 编译通过 + 接口调用 UT |

**实现要点：**
- `convertToECMaterial(material?: Material): Material` — 将 Material 转换为 EffectComponent 主材质
- `convertToECSubMaterial(material?: Material): Material` — 将 Material 转换为 EffectComponent 子材质
- 传入 undefined → 返回 undefined
- 接口声明标注 `@systemapi`

### TASK-1: ChipGroup 新增材质属性 + 版本隔离 + Scroll 内 EffectComponent 子组件

| 字段 | 内容 |
|------|------|
| 目标 | ChipGroup 新增 @Prop 材质属性 + Scroll 内 EffectComponent 子组件 + 版本隔离 |
| 受影响文件 | `advanced_ui_component/chipgroup/source/chipgroup.ets` |
| 关联 AC | AC-1, AC-1-V26, AC-1-UNDEF, AC-1-NONE, AC-6-V26-LOW |
| 依赖 | TASK-0 完成 |
| 验证方式 | 编译通过 + 版本隔离条件覆盖 |

**实现要点：**
- 新增 `import deviceInfo from '@ohos.deviceInfo'`
- 新增 `@Prop backgroundSystemMaterial?: uiMaterial.Material`
- 新增 `@Prop selectedBackgroundSystemMaterial?: uiMaterial.Material`
- build() Scroll 内条件插入 EffectComponent：
  - `if (deviceInfo.sdkApiVersion >= 26 && this.backgroundSystemMaterial)` → Scroll 内 EffectComponent 子组件 + `.systemMaterial(uiMaterial.convertToECMaterial(this.backgroundSystemMaterial))`
  - `else` → 原有 Scroll 结构不变
- Chip() 构造参数新增材质字段（`convertToECSubMaterial` 传入）

### TASK-2: Chip 条目材质属性新增 + build() 应用 + 版本隔离

| 字段 | 内容 |
|------|------|
| 目标 | Chip 新增材质属性 + Button 上 `.systemMaterial()` + 版本隔离 |
| 受影响文件 | `advanced_ui_component/chip/source/chip.ets`, `advanced_ui_component/chip/source/chip_v16.ets` |
| 关联 AC | AC-3, AC-3-OVERLAY, AC-3-V26, AC-4, AC-4-SWITCH, AC-4-UNDEF |
| 依赖 | TASK-1 完成 |
| 验证方式 | 编译通过 + 状态切换逻辑覆盖 |

**实现要点：**
- ChipOptions 新增 `backgroundSystemMaterial?: uiMaterial.Material` + `activatedBackgroundSystemMaterial?: uiMaterial.Material`
- ChipComponent 新增 `@Prop backgroundSystemMaterial` + `@Prop activatedBackgroundSystemMaterial`
- 新增 `import deviceInfo from '@ohos.deviceInfo'`
- 新增 `getBackgroundSystemMaterial()` / `getActivatedBackgroundSystemMaterial()` getter 方法（参照 `getChipNodeBackGroundColor()` 模式）
- chipBuilder() Button 新增 `.systemMaterial()` 调用，仅在 `deviceInfo.sdkApiVersion >= 26` 时生效
- chip_v16.ets 同步修改

### TASK-3: IconGroupSuffix 材质属性新增 + build() 应用 + 版本隔离

| 字段 | 内容 |
|------|------|
| 目标 | IconGroupSuffix 新增材质属性 + Button 上 `.systemMaterial()` + 版本隔离 |
| 受影响文件 | `advanced_ui_component/chipgroup/source/chipgroup.ets` (IconGroupSuffix 部分) |
| 关联 AC | AC-5, AC-5-OVERLAY, AC-5-V26, AC-5-UNDEF |
| 依赖 | TASK-1 完成 |
| 验证方式 | 编译通过 |

**实现要点：**
- IconGroupSuffix 新增 `@Prop iconBackgroundSystemMaterial?: uiMaterial.Material`
- build() 每个 suffix item Button 新增 `.systemMaterial()` 调用，仅在 `deviceInfo.sdkApiVersion >= 26` 时生效
- 材质叠加在纯色之上（与 `.backgroundColor()` 同节点）

### TASK-4: ChipGroup 传递材质到 Chip + 版本隔离完善

| 字段 | 内容 |
|------|------|
| 目标 | 完善 ChipGroup build() 中 EffectComponent → convertToECSubMaterial → Chip 参数传递链路 |
| 受影响文件 | `advanced_ui_component/chipgroup/source/chipgroup.ets` |
| 关联 AC | AC-1, AC-2, AC-2-SWITCH, AC-7 |
| 依赖 | TASK-0 + TASK-2 完成 |
| 验证方式 | 编译通过 + 状态切换覆盖 |

**实现要点：**
- ChipGroup build() Chip() 构造参数新增 `backgroundSystemMaterial: uiMaterial.convertToECSubMaterial(this.backgroundSystemMaterial)` + `selectedBackgroundSystemMaterial: uiMaterial.convertToECSubMaterial(this.selectedBackgroundSystemMaterial)`
- 版本隔离：仅在 `deviceInfo.sdkApiVersion >= 26` 时传入材质参数
- 选中/非选中态切换逻辑完善

### TASK-5: 静态版本同步修改 + d.ets 声明

| 字段 | 内容 |
|------|------|
| 目标 | 静态组装组件和 d.ets 声明文件同步修改 |
| 受影响文件 | `@ohos.arkui.advanced.ChipGroup.ets`, `@ohos.arkui.advanced.Chip.ets`, `@ohos.arkui.advanced.ChipGroup.d.ets`, `@ohos.arkui.advanced.Chip.d.ets` |
| 关联 AC | 全部 AC（静态版本需与动态版本行为一致） |
| 依赖 | TASK-1~4 完成 |
| 验证方式 | 编译通过 |

**实现要点：**
- 静态组装组件同步新增材质属性、EffectComponent 子组件、版本隔离条件
- d.ets 新增属性声明（含 SysCap: `SystemCapability.ArkUI.ArkUI.Full`，起始版本: API 26）

### TASK-6: SpecTest 用例编写（含版本隔离场景）

| 字段 | 内容 |
|------|------|
| 目标 | Host Preview SpecTest suite 覆盖材质属性 + 版本隔离场景 |
| 受影响文件 | `examples/SpecTest/` |
| 关联 AC | AC-1~AC-7 |
| 依赖 | TASK-5 完成 |
| 验证方式 | SpecTest 编译通过 + 运行通过 |

**实现要点：**
- SpecTest suite 覆盖：材质属性设置/不设置、版本隔离（Mock `deviceInfo.sdkApiVersion` 26+ 和 <26）、状态切换
- Inspector 断言：检查节点是否具有 `systemMaterial` 属性
- 覆盖版本隔离测试矩阵（spec.md 中定义的 4 种条件组合）

## 执行检查点

| 检查点 | 条件 | 验证方式 |
|--------|------|----------|
| TASK-0 完成 | uiMaterial 接口编译通过 + UT 通过 | `./build.sh --product-name rk3568 --build-target ace_engine` |
| TASK-1 完成 | ChipGroup 编译通过 + 版本隔离条件覆盖 | 编译验证 |
| TASK-2 完成 | Chip 编译通过 + 状态切换逻辑覆盖 | 编译验证 |
| TASK-3 完成 | IconGroupSuffix 编译通过 | 编译验证 |
| TASK-4 完成 | 材质传递链路编译通过 | 编译验证 |
| TASK-5 完成 | 静态版本 + d.ets 编译通过 | 编译验证 |
| TASK-6 完成 | SpecTest 编译通过 + 运行通过 | SpecTest 执行 |
| 全量完成 | 全部 Task 完成 + review.md 通过 | 代码评审 + 测试验证 |

## 交接说明

本计划完成后，需交付以下产物：

1. 7 个新增 API 的完整实现代码
2. 版本隔离逻辑（`deviceInfo.sdkApiVersion >= 26`）
3. EffectComponent + convertToECMaterial/convertToECSubMaterial 性能优化方案实现
4. d.ets 声明文件更新
5. SpecTest 用例
6. review.md 审查记录