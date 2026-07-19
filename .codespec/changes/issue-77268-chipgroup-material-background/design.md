# 架构设计

> ChipGroup/Chip/IconGroupSuffix 新增 `systemMaterial` 新材质背景配置能力

## 设计元数据

| 字段 | 内容 |
|------|------|
| Design ID | DESIGN-001 |
| 关联需求 | `.codespec/changes/draft-20260610-chipgroup-material-background/proposal.md` |
| 关联 Epic | N/A |
| 目标 Feature | 07-01-02 / Feat-01 |
| 复杂度 | 标准 |
| 目标版本 | OpenHarmony-7.0-Release（引用 manifest.target_release） |
| Owner | youzhi92 |
| 状态 | Approved |

## 需求基线

| 项 | 补充说明 |
|----|----------|
| 材质背景范围 | ChipGroup 容器材质仅负责传递给 Chip（ChipGroup 容器自身不渲染材质）；ChipGroup 在 Scroll 内插入 EffectComponent 子组件渲染主材质；Chip 条目渲染子材质；IconGroupSuffix 在 Row 内插入 EffectComponent 子组件渲染主材质，suffix item Button 渲染子材质 |
| 材质与纯色关系 | 材质叠加在纯色之上（纯色作为底层），不替代纯色 |
| 状态区分 | ChipGroup 区分选中/非选中态；Chip 区分激活/非激活态；IconGroupSuffix 单一材质 |
| 传递方式 | ChipGroup 通过 Scroll 内 EffectComponent `.systemMaterial(convertToECMaterial)` 渲染主材质 + `convertToECSubMaterial` 传递子材质到 Chip，不通过 ChipItemStyle 中间层 |
| 性能优化 | ChipGroup 在 Scroll 内插入 EffectComponent 子组件，多 Chip 共享同一材质渲染资源 |
| API 类型 | Public API 新增 5 个可选属性（SysCap: `SystemCapability.ArkUI.ArkUI.Full`） + System API 新增 2 个 uiMaterial 接口（`convertToECMaterial`/`convertToECSubMaterial`），需走 API 审批。新材质从 API 26 开始支持，使用 `deviceInfo.sdkApiVersion >= 26` 版本隔离 |

## 上下文和现状

### 涉及仓和模块

| 仓库 | 补充架构说明 |
|------|-------------|
| ace_engine | ChipGroup/Chip 为 ArkTS 高级组件（`advanced_ui_component/`），非 C++ NG pattern。ChipGroup 在 Scroll 内插入 EffectComponent 作为子组件，EffectComponent 上通过 `.systemMaterial()` 设置 `convertToECMaterial()` 主材质；传递给 Chip 的材质使用 `convertToECSubMaterial()` 子材质。`uiMaterial` namespace 需新增 2 个转换接口（尚未实现） |

### 调用链层级分析

| 层 | 模块 | 职责 | 修改类型 |
|----|------|------|----------|
| 应用层 | ArkTS 应用代码 | 调用 ChipGroup/Chip 构造函数传入 `systemMaterial` 属性 | 新增（开发者使用新属性） |
| 高级组件层 | ChipGroup `@Component` | 接收材质属性，在 Scroll 内插入 EffectComponent 子组件，EffectComponent 上通过 `.systemMaterial(uiMaterial.convertToECMaterial())` 设置主材质；传递给 Chip 的材质使用 `uiMaterial.convertToECSubMaterial()` | 修改 |
| 高级组件层 | Chip `@Component` | 接收 `backgroundSystemMaterial`/`activatedBackgroundSystemMaterial`（ECSubMaterial 类型），在 Button 上应用 `.systemMaterial()` | 修改 |
| 高级组件层 | IconGroupSuffix `@Component` | 接收 `iconBackgroundSystemMaterial`（Material 类型），在 Row 内插入 EffectComponent 子组件，EffectComponent 上 `.systemMaterial(convertToECMaterial())` 设置主材质；每个 suffix item Button 上 `.systemMaterial(convertToECSubMaterial())` 子材质 | 修改 |
| ArkUI 框架层 | `uiMaterial.convertToECMaterial()`/`convertToECSubMaterial()` | `uiMaterial` namespace 新增接口，将 `Material` 转换为 EffectComponent 主材质/子材质 | **新增**（尚未实现） |
| ArkUI 框架层 | `EffectComponent` | ArkUI 框架已有组件，作为 Scroll 子组件插入，通过 `.systemMaterial()` 设置主材质，子节点共享同一材质渲染资源 | 无修改（已有能力） |
| ArkUI 框架层 | `ViewAbstract.systemMaterial()` | ArkUI 框架提供的 `.systemMaterial()` 方法，将 Material 渲染为材质背景 | 无修改（已有能力） |
| 渲染层 | 渲染引擎 | 执行 `systemMaterial` 的实际渲染 | 无修改 |

**检查项：**
- [x] 调用链每一层都已覆盖（应用层 → 高级组件层 → ArkUI 框架层 → 渲染层）
- [x] 每层职责边界清晰，无跨层违规调用
- [x] 每层修改类型明确（高级组件层修改 + uiMaterial 层新增接口，渲染层无改动）

### 适用架构规则

| Rule ID | 适用原因 | 设计结论 | 验证方式 |
|---------|----------|----------|----------|
| OH-ARCH-API-LEVEL | 涉及 Public API 新增 5 个组件属性（SysCap: SystemCapability.ArkUI.ArkUI.Full） + System API 新增 2 个 uiMaterial 接口 | 组件属性为 Public API，类型 `uiMaterial.Material?`，可选，SysCap 已确认。`convertToECMaterial`/`convertToECSubMaterial` 为**系统接口**（`@systemapi`），仅系统应用可调用 | API 评审（Public API + System API 分别审批） |
| OH-ARCH-COMPONENT-BUILD | 不涉及新部件或构建依赖 | 仅修改 ArkTS 源文件，无 BUILD.gn/bundle.json 变更 | 构建验证 |
| OH-ARCH-LAYERING | 高级组件层调用框架层 `.systemMaterial()` + `EffectComponent` | ChipGroup 在 Scroll 内插入 EffectComponent 子组件（框架已有组件），高级组件层 → 框架层，单向调用合规 | 代码评审 |

## 不涉及项承接

| 维度 | 设计结论 |
|------|----------|
| 性能（涉及） | 多 Chip/suffix item 同时渲染材质存在性能风险。ChipGroup 在 Scroll 内插入 EffectComponent 子组件渲染主材质，每个 Chip 用 `convertToECSubMaterial()` 共享资源；IconGroupSuffix 在 Row 内插入 EffectComponent 子组件渲染主材质，每个 suffix item Button 用 `convertToECSubMaterial()` 共享资源。两处 EffectComponent 各自独立渲染主材质，子节点共享同一材质渲染资源 |
| 兼容性（涉及） | 新增属性全部可选（默认 undefined），不设置时行为与当前版本完全一致。材质叠加在纯色之上，纯色渲染逻辑不变。新材质从 API 26 开始支持，低于 API 26 时材质属性被忽略，EffectComponent 子组件不插入，保持与当前版本完全一致的行为。版本隔离使用 `deviceInfo.sdkApiVersion >= 26`，与 `chip_v16.ets:499` 和 `segmentbuttonv2.ets:1369` 的隔离模式一致 |
| API/SDK（涉及） | ChipGroup 新增 `backgroundSystemMaterial` + `selectedBackgroundSystemMaterial`（d.ets: `@ohos.arkui.advanced.ChipGroup.d.ets`）；Chip 新增 `backgroundSystemMaterial` + `activatedBackgroundSystemMaterial`（d.ets: `@ohos.arkui.advanced.Chip.d.ets`）；IconGroupSuffix 新增 `iconBackgroundSystemMaterial`（d.ets: `@ohos.arkui.advanced.ChipGroup.d.ets`）。属性类型 `uiMaterial.Material?`，可选，SysCap: `SystemCapability.ArkUI.ArkUI.Full`。 `uiMaterial` namespace 新增 `convertToECMaterial`/`convertToECSubMaterial` 为**系统接口**（非 Public API，仅系统应用可调用），类型 `Material → Material`） |
| 安全与权限（N/A） | 纯 UI 视觉属性，无安全影响 |
| IPC/跨进程（N/A） | 无跨进程通信 |
| 构建与部件（N/A） | 无新增部件或构建依赖 |
| 国际化/无障碍（N/A） | 材质为纯视觉效果，不影响语义和国际化 |
| 数据迁移（N/A） | 无数据迁移 |

## 关键设计决策

| 决策 ID | 问题 | 推荐方案 | 探索过的替代方案 | 取舍理由 | 影响 |
|---------|------|----------|-----------------|----------|------|
| ADR-1 | 材质属性如何在 ChipGroup 和 Chip 之间传递？ | ChipGroup 新增 `@Prop` 材质属性，在 `build()` 中直接传入 Chip 构造函数的对应属性（参照当前纯色 `backgroundColor` 传递模式 `chipgroup.ets:584-586`） | A: 通过 ChipItemStyle 中间层传递 → 不符合需求方"直传不通过 ChipItemStyle"的要求；B: 通过 `@Provide/@Consume` 传递 → Chip 不使用 `@Consume`，且材质属性非全局共享属性 | 与现有纯色属性传递模式一致（直接在 Chip() 构造参数中传入），改动最小，语义清晰 | ChipGroup build() 方法需新增 2 个参数传递 |
| ADR-2 | ChipGroup 容器是否自身应用 `systemMaterial`？ | **否** — ChipGroup 的最外层 Row 不渲染材质。材质主渲染通过 Scroll 内的 EffectComponent 子组件实现（`.systemMaterial(uiMaterial.convertToECMaterial())`），ChipGroup 容器自身仅负责传递 | A: ChipGroup Row 容器渲染材质 → 不符合需求方"只负责传递"的要求；B: 参照 SegmentButtonV2 在容器上渲染 → SegmentButtonV2 容器是整体按钮面板，ChipGroup 容器仅是布局容器 | ChipGroup 最外层 Row 不新增 `.systemMaterial()`，材质主渲染在 Scroll 内的 EffectComponent 上，Chip 通过 `convertToECSubMaterial` 接收子材质 | ChipGroup 最外层 Row 不新增 `.systemMaterial()`，Scroll 内新增 EffectComponent 子组件 |
| ADR-3 | Chip 条目材质应用在哪个节点？ | 应用在 Chip 的外层 `Button` 节点上（`chip.ets:1183,1334`），与当前 `.backgroundColor()` 在同一节点，确保材质叠加在纯色之上 | A: 应用在 Row 节点 → Row 为内容容器，不承载背景；B: 新增包装容器 → 增加 DOM 层级，影响性能 | Button 节点已是 Chip 的背景承载节点，`.systemMaterial()` 和 `.backgroundColor()` 在同一节点上自然实现叠加效果 | Chip 外层 Button 新增 `.systemMaterial()` 调用 |
| ADR-4 | IconGroupSuffix 材质应用在哪个节点？ | IconGroupSuffix build() 中用 EffectComponent 包裹 Row(ForEach → Button)，EffectComponent 上设置 `.systemMaterial(uiMaterial.convertToECMaterial(this.iconBackgroundSystemMaterial))` 主材质；每个 suffix item Button 上设置 `.systemMaterial(uiMaterial.convertToECSubMaterial(this.iconBackgroundSystemMaterial))` 子材质，多 suffix item 共享同一材质渲染资源 | A: 每个 Button 独立设置 `systemMaterial` → 多 suffix item 同时渲染材质时各自创建独立渲染资源，性能开销大；B: 应用在 Row 节点 → Row 为容器 | 与 ChipGroup 的 EffectComponent 性能优化模式一致（ADR-6），EffectComponent 包裹 suffix item 区域，convertToECMaterial 主材质 + convertToECSubMaterial 子材质 | IconGroupSuffix build() Row 内新增 EffectComponent 包裹 + `.systemMaterial(convertToECMaterial)` 主材质；Button `.systemMaterial(convertToECSubMaterial)` 子材质 |
| ADR-5 | 材质属性的状态切换如何实现？ | ChipGroup 容器材质根据选中状态切换：非选中态使用 `backgroundSystemMaterial`，选中态使用 `selectedBackgroundSystemMaterial`；Chip 条目材质根据激活状态切换：非激活态使用 `backgroundSystemMaterial`，激活态使用 `activatedBackgroundSystemMaterial`。参照 Chip 当前纯色背景切换逻辑（`chip.ets:848-873` 的 `getChipNodeBackGroundColor()` 方法） | A: 单一材质属性，不区分状态 → 不符合需求方要求 | 与现有纯色背景状态切换模式一致（选中态/非选中态、激活态/非激活态各自有独立属性），扩展性好 | 需新增 getter 方法：`getBackgroundSystemMaterial()` / `getSelectedBackgroundSystemMaterial()` / `getActivatedBackgroundSystemMaterial()` |
| ADR-6 | 多 Chip/IconGroupSuffix 同时渲染材质的性能优化？ | ChipGroup 在 Scroll 内插入 EffectComponent 子组件，EffectComponent 上 `.systemMaterial(convertToECMaterial())` 渲染主材质，Chip 用 `convertToECSubMaterial()` 子材质共享资源。IconGroupSuffix 同样用 EffectComponent 包裹 Row(ForEach → Button)，EffectComponent 上 `.systemMaterial(convertToECMaterial(this.iconBackgroundSystemMaterial))` 渲染主材质，每个 suffix item Button 用 `convertToECSubMaterial()` 子材质共享资源 | A: 每个 Chip/suffix item 独立设置 `systemMaterial` → 多节点同时渲染材质时各自创建独立渲染资源，性能开销大 | EffectComponent + convertToECMaterial/SubMaterial 是 ArkUI 框架的材质渲染优化方案，ChipGroup Scroll 内 EffectComponent 和 IconGroupSuffix Row 内 EffectComponent 各自独立渲染主材质，子节点共享渲染资源 | ChipGroup Scroll 内 + IconGroupSuffix Row 内各自新增 EffectComponent 子组件 |
| ADR-7 | 新材质版本隔离？ | 使用 `deviceInfo.sdkApiVersion` 做版本隔离：新材质相关功能（EffectComponent 子组件插入、`convertToECMaterial`/`convertToECSubMaterial` 转换、`.systemMaterial()` 调用）仅在 `sdkApiVersion >= 26` 时生效；低于 API 26 时忽略材质属性，保持与当前版本完全一致的行为 | A: 无版本隔离 → 低版本设备上 EffectComponent/systemMaterial 可能不可用或行为异常；B: 编译时隔离 → 高级组件为运行时组件，不支持编译时版本裁剪 | 与 `chip_v16.ets:499`（`deviceInfo.sdkApiVersion < 26`）和 `segmentbuttonv2.ets:1369`（`deviceInfo.sdkApiVersion >= 26`）的版本隔离模式一致。ChipGroup/Chip 当前未 import `deviceInfo`，需新增 import | ChipGroup/Chip 新增 `import deviceInfo from '@ohos.deviceInfo'`；build() 中材质相关逻辑包裹 `if (deviceInfo.sdkApiVersion >= 26)` 条件 |

## 设计骨架

### 骨架范围

| 骨架项 | 目标 | 不包含 | 验证方式 |
|--------|------|--------|----------|
| API/接口骨架 | ChipGroup/Chip/IconGroupSuffix 新增 `@Prop` 属性签名；`uiMaterial` namespace 新增 `convertToECMaterial`/`convertToECSubMaterial` 接口签名 | 完整状态切换逻辑 | 编译通过 |
| 模块骨架 | ChipGroup build() Scroll 内新增 EffectComponent 子组件 + `.systemMaterial(convertToECMaterial())` 设置主材质 + Chip/IconGroupSuffix 传入 `convertToECSubMaterial()` | 完整渲染逻辑 | 编译通过 |
| 测试骨架 | Host Preview SpecTest suite 入口 | 全场景覆盖 | SpecTest 编译通过 |

### 骨架 Spec 拆分

| Task ID | 目标 | 受影响文件 | AC |
|---------|------|------------|-----|
| TASK-SKELETON-1 | ChipGroup 新增材质属性骨架 + Scroll 内 EffectComponent 子组件 + 版本隔离 | `chipgroup.ets`, `@ohos.arkui.advanced.ChipGroup.ets` | WHEN 设置 `backgroundSystemMaterial` AND `sdkApiVersion >= 26` THEN ChipGroup 在 Scroll 内插入 EffectComponent 子组件；WHEN `sdkApiVersion < 26` THEN 保持原有 build() 结构无材质 |
| TASK-SKELETON-2 | Chip 新增材质属性骨架（接收 ECSubMaterial） + 版本隔离 | `chip.ets`, `chip_v16.ets`, `@ohos.arkui.advanced.Chip.ets` | WHEN 设置 `backgroundSystemMaterial`（ECSubMaterial 类型）AND `sdkApiVersion >= 26` THEN Chip 条目渲染材质；`sdkApiVersion < 26` → 忽略材质 |
| TASK-SKELETON-3 | IconGroupSuffix 新增材质属性骨架（接收 ECSubMaterial） + 版本隔离 | `chipgroup.ets` (IconGroupSuffix 部分), `@ohos.arkui.advanced.ChipGroup.ets` | WHEN 设置 `iconBackgroundSystemMaterial`（ECSubMaterial 类型）AND `sdkApiVersion >= 26` THEN IconGroupSuffix 渲染材质；`sdkApiVersion < 26` → 忽略材质 |
| TASK-SKELETON-4 | uiMaterial 新增 `convertToECMaterial`/`convertToECSubMaterial` 接口骨架 | `@ohos.arkui.uiMaterial.ets` | WHEN 调用 `convertToECMaterial(Material)` THEN 返回 EffectComponent 主材质；WHEN 调用 `convertToECSubMaterial(Material)` THEN 返回 EffectComponent 子材质 |

## 后续 Task 拆分

| Task ID | 目标 | 受影响文件 | 依赖 |
|---------|------|------------|------|
| TASK-0 | uiMaterial namespace 新增 `convertToECMaterial()`/`convertToECSubMaterial()` 接口 | `@ohos.arkui.uiMaterial.ets` | design.md + spec.md Approved |
| TASK-1 | ChipGroup 新增材质属性 + 版本隔离 + Scroll 内 EffectComponent 子组件 | `advanced_ui_component/chipgroup/source/chipgroup.ets`（新增 @Prop、新增 `import deviceInfo`）、`chipgroup.ets:565+`（`if (deviceInfo.sdkApiVersion >= 26)` 条件分支：API 26+ → Scroll 内 EffectComponent 子组件 + `.systemMaterial(convertToECMaterial)` + `convertToECSubMaterial` 传递；API <26 → 原有 build() 结构无材质） | TASK-0 完成 |
| TASK-2 | Chip 条目材质属性新增 + build() 应用 + 版本隔离 | `advanced_ui_component/chip/source/chip.ets:206-227`（ChipOptions 新增字段）、`chip.ets:1183-1334`（chipBuilder() 新增 `.systemMaterial()`，仅 `sdkApiVersion >= 26` 时调用）、`chip_v16.ets` 同步修改 | TASK-1 完成 |
| TASK-3 | IconGroupSuffix 材质属性新增 + build() 应用 + 版本隔离 | `advanced_ui_component/chipgroup/source/chipgroup.ets:209-213`（新增 @Prop）、`chipgroup.ets:261-297`（build() 新增 `.systemMaterial()`，仅 `sdkApiVersion >= 26` 时调用） | TASK-1 完成 |
| TASK-4 | ChipGroup 传递材质到 Chip（Scroll 内 EffectComponent → convertToECSubMaterial → Chip 参数） + 版本隔离 | `chipgroup.ets:565+`（`if (deviceInfo.sdkApiVersion >= 26)` 条件分支） | TASK-0, TASK-2 完成 |
| TASK-5 | 静态版本同步修改 | `@ohos.arkui.advanced.ChipGroup.ets`、`@ohos.arkui.advanced.Chip.ets` | TASK-1~4 完成 |
| TASK-6 | SpecTest 用例编写（含版本隔离场景） | `examples/SpecTest/` | TASK-5 完成 |

## API 签名、Kit 与权限

### 新增 API

| API 签名 | 类型 | Kit | d.ets 位置 | 权限要求 | SysCap | 起始版本 |
|----------|------|-----|-----------|----------|--------|----------|
| `ChipGroup.backgroundSystemMaterial?: uiMaterial.Material` | Public | ArkUI | `@ohos.arkui.advanced.ChipGroup.d.ets` | - | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| `ChipGroup.selectedBackgroundSystemMaterial?: uiMaterial.Material` | Public | ArkUI | `@ohos.arkui.advanced.ChipGroup.d.ets` | - | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| `Chip.backgroundSystemMaterial?: uiMaterial.Material` | Public | ArkUI | `@ohos.arkui.advanced.Chip.d.ets` | - | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| `Chip.activatedBackgroundSystemMaterial?: uiMaterial.Material` | Public | ArkUI | `@ohos.arkui.advanced.Chip.d.ets` | - | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| `IconGroupSuffix.iconBackgroundSystemMaterial?: uiMaterial.Material` | Public | ArkUI | `@ohos.arkui.advanced.ChipGroup.d.ets` | - | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| `uiMaterial.convertToECMaterial(material?: Material): Material` | **System** | ArkUI | `@ohos.arkui.uiMaterial.d.ets` | - | SystemCapability.ArkUI.ArkUI.Full | API 26 |
| `uiMaterial.convertToECSubMaterial(material?: Material): Material` | **System** | ArkUI | `@ohos.arkui.uiMaterial.d.ets` | - | SystemCapability.ArkUI.ArkUI.Full | API 26 |

### 变更/废弃 API

无变更或废弃 API。

## 构建系统影响

### BUILD.gn 变更

无 BUILD.gn 变更。仅修改 ArkTS 源文件，不新增源文件或依赖。

### bundle.json 变更

无 bundle.json 变更。

---

## 可选设计扩展

### 数据模型设计

> 涉及 Public API 变更时必填。

```typescript
// uiMaterial namespace 新增接口（@ohos.arkui.uiMaterial.ets）
namespace uiMaterial {
  enum MaterialType { NONE = 0, SEMI_TRANSPARENT = 1 }
  interface MaterialOptions { type?: MaterialType }
  class Material {
    constructor(options?: MaterialOptions)
    getNativeObject(): long
  }
  // 新增：将 Material 转换为 EffectComponent 主材质
  function convertToECMaterial(material?: Material): Material
  // 新增：将 Material 转换为 EffectComponent 子材质（用于 EffectComponent 内子节点）
  function convertToECSubMaterial(material?: Material): Material
}

// ChipGroup 新增属性（chipgroup.ets）
@Prop backgroundSystemMaterial?: uiMaterial.Material;
@Prop selectedBackgroundSystemMaterial?: uiMaterial.Material;

// ChipGroup build() EffectComponent 作为 Scroll 子组件（chipgroup.ets:563+）
// 版本隔离：API 26+ 才生效
build() {
  Row() {
    Stack() {
      if (deviceInfo.sdkApiVersion >= 26 && this.backgroundSystemMaterial) {
        Scroll(this.scroller) {
          EffectComponent() {
            Row({ space: this.getChipGroupItemSpace() }) {
              ForEach(this.items || [], (chipItem, index) => {
                Chip({
                  // ... 现有参数 ...
                  backgroundSystemMaterial: uiMaterial.convertToECSubMaterial(this.backgroundSystemMaterial),
                  selectedBackgroundSystemMaterial: uiMaterial.convertToECSubMaterial(this.selectedBackgroundSystemMaterial),
                })
              })
            }
          }
          .systemMaterial(uiMaterial.convertToECMaterial(this.backgroundSystemMaterial)) // 主材质
        }
        // ... Scroll 原有属性 ...
      } else {
        // 原有 build() 结构（无 EffectComponent，无材质）
        Scroll(this.scroller) {
          Row({ space: this.getChipGroupItemSpace() }) {
            ForEach(this.items || [], (chipItem, index) => {
              Chip({
                // ... 现有参数（无材质） ...
              })
            })
          }
        }
        // ... Scroll 原有属性 ...
      }
    }
    // ... Stack 原有属性 ...
  }
}

// ChipOptions 新增字段（chip.ets:206-227）
interface ChipOptions {
  // ... 现有字段 ...
  backgroundSystemMaterial?: uiMaterial.Material;     // 新增：非激活态材质（ECSubMaterial）
  activatedBackgroundSystemMaterial?: uiMaterial.Material; // 新增：激活态材质（ECSubMaterial）
}

// ChipComponent 新增属性（chip.ets:425+）
@Prop backgroundSystemMaterial?: uiMaterial.Material;
@Prop activatedBackgroundSystemMaterial?: uiMaterial.Material;

// IconGroupSuffix 新增属性（chipgroup.ets:210+）
@Prop iconBackgroundSystemMaterial?: uiMaterial.Material;

// IconGroupSuffix build() EffectComponent 包裹 + 版本隔离（chipgroup.ets:264+）
build() {
  if (deviceInfo.sdkApiVersion >= 26 && this.iconBackgroundSystemMaterial) {
    EffectComponent() {
      Row({ space: 8 }) {
        ForEach(this.items || [], (suffixItem) => {
          Button() { ... }
          .backgroundColor(iconGroupSuffixTheme.backgroundColor)
          .systemMaterial(uiMaterial.convertToECSubMaterial(this.iconBackgroundSystemMaterial))
          ...
        })
      }
    }
    .systemMaterial(uiMaterial.convertToECMaterial(this.iconBackgroundSystemMaterial))
  } else {
    Row({ space: 8 }) {
      ForEach(this.items || [], (suffixItem) => {
        Button() { ... }
        .backgroundColor(iconGroupSuffixTheme.backgroundColor)
        ...
      })
    }
  }
}  // ECSubMaterial 类型
```

**`uiMaterial.Material` 类型及新增接口**（源码核验 `@ohos.arkui.uiMaterial.ets:19-61`，新增接口尚未实现）：

```typescript
namespace uiMaterial {
  enum MaterialType { NONE = 0, SEMI_TRANSPARENT = 1 }
  interface MaterialOptions { type?: MaterialType }
  class Material {
    constructor(options?: MaterialOptions)
    getNativeObject(): long
  }
  // 新增接口（ADR-6 性能优化）—— 系统接口（@systemapi）
  function convertToECMaterial(material?: Material): Material   // 主材质 → EffectComponent 渲染
  function convertToECSubMaterial(material?: Material): Material // 子材质 → EffectComponent 内子节点
}
```

**EffectComponent 材质渲染原理**：EffectComponent 作为 Scroll 子组件插入 ChipGroup build() 中，通过 `.systemMaterial(convertToECMaterial())` 设置主材质。其子节点（Chip）通过 `convertToECSubMaterial` 共享同一材质渲染资源，避免多 Chip 重复创建材质渲染管线。EffectComponent 继承 CommonMethod，`.systemMaterial()` 为框架已有属性方法。

**版本隔离（ADR-7）**：新材质从 API 26 开始支持。低于 API 26 时，材质属性被忽略，EffectComponent 子组件不插入，保持与当前版本完全一致的行为。版本隔离使用 `deviceInfo.sdkApiVersion >= 26` 条件判断，与 `chip_v16.ets:499` 和 `segmentbuttonv2.ets:1369` 的隔离模式一致。

### 接口参数规约

> 涉及 Public API 变更时必填。

| 接口 | 参数 | 类型 | 合法范围 | 非法处理 | 边界说明 |
|------|------|------|----------|----------|----------|
| uiMaterial.convertToECMaterial | material | `uiMaterial.Material?` | `Material` 实例或 undefined | undefined → 返回 undefined，EffectComponent 不渲染材质 | **系统接口**（@systemapi），仅系统应用可调用；API 26+ 生效 |
| uiMaterial.convertToECSubMaterial | material | `uiMaterial.Material?` | `Material` 实例或 undefined | undefined → 返回 undefined，子节点不渲染材质 | **系统接口**（@systemapi），仅系统应用可调用；API 26+ 生效 |
| ChipGroup.backgroundSystemMaterial | value | `uiMaterial.Material?` | `Material` 实例或 undefined | undefined → EffectComponent 不渲染材质，保持原行为；`sdkApiVersion < 26` → 属性被忽略，不插入 EffectComponent | 传入后通过 `convertToECMaterial` 转换；仅 API 26+ 生效 |
| ChipGroup.selectedBackgroundSystemMaterial | value | `uiMaterial.Material?` | 同上 | 同上 | 同上 |
| Chip.backgroundSystemMaterial | value | `uiMaterial.Material?`（ECSubMaterial） | ChipGroup 传入的 `convertToECSubMaterial` 结果或 undefined | undefined → Chip 不渲染材质；`sdkApiVersion < 26` → ChipGroup 不传入材质 | 由 ChipGroup Scroll 内 EffectComponent 子组件传入；仅 API 26+ 生效 |
| Chip.activatedBackgroundSystemMaterial | value | `uiMaterial.Material?`（ECSubMaterial） | 同上 | 同上 | 同上 |
| IconGroupSuffix.iconBackgroundSystemMaterial | value | `uiMaterial.Material?`（ECSubMaterial） | ChipGroup 传入的 `convertToECSubMaterial` 结果或 undefined | undefined → IconGroupSuffix 不渲染材质 | 同上 |

### 测试性设计

| 测试层级 | 测试目标 | Mock 策略 | 验证方式 |
|----------|----------|-----------|----------|
| SpecTest Host Preview | 材质属性设置后组件渲染可观测 + 版本隔离条件分支可验证 | Mock `deviceInfo.sdkApiVersion`（26+ 和 <26 两种场景） | `run_feature.sh --suite-id chipgroup-systemMaterial` |
| Host UT | ChipGroup/Chip 属性赋值和状态切换逻辑 | Mock ChipComponent | `./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/test/unittest:unittest` |
| 设备验证 | 真实材质渲染效果（视觉回归） | 真实设备 | 设备截图比对 |

**SpecTest 适用性评估：**

- 布局/尺寸/位置：N/A（材质为视觉效果，不影响布局）
- 可 Inspector 断言的属性：部分适用（可通过 Inspector 检查节点是否具有 `systemMaterial` 属性）
- 状态切换后的视觉效果：N/A（需要视觉判断，SpecTest 不适用，转入设备补验）

### Performance & Memory Budget

> 涉及热路径时必填。

| 热路径 | 预期额外开销 | 预算依据 |
|--------|-------------|----------|
| render 热路径 | ChipGroup 在 Scroll 内插入 EffectComponent 子组件渲染 1 次主材质（`convertToECMaterial()`），N 个 Chip 共享 `convertToECSubMaterial()` 子材质资源；IconGroupSuffix 在 Row 内插入 EffectComponent 子组件渲染 1 次主材质，M 个 suffix item Button 共享子材质资源。两处 EffectComponent 各自独立，不引入额外 layout/paint pass | EffectComponent 为 ArkUI 框架已有组件（`effect_component_pattern.h`），`.systemMaterial()` 为框架已有属性方法 |

**内存分配：** `uiMaterial.Material` 对象由开发者创建并通过 `@Prop` 传入 ChipGroup。ChipGroup 内部通过 `convertToECMaterial()`/`convertToECSubMaterial()` 转换后传递给 EffectComponent 和 Chip/IconGroupSuffix。转换后的材质对象共享同一渲染资源（EffectComponent 主材质），子材质（`convertToECSubMaterial`）不独立创建渲染管线。`Material` 内部持有 `long` 类型 native 指针（`@ohos.arkui.uiMaterial.ets:44`），通过 `FinalizationRegistry` 管理生命周期（`uiMaterial.ets:41`）。组件不负责 Material 的创建和销毁，所有权归开发者。

## 风险和开放问题

| 项 | 类型 | 影响 | 处理方式 | Owner |
|----|------|------|----------|-------|
| `uiMaterial.convertToECMaterial`/`convertToECSubMaterial` 接口尚未实现，需 uiMaterial 团队先交付 | **依赖** | **高** | 需与 uiMaterial 团队协调交付优先级，TASK-0 为前置依赖，阻塞 TASK-1~4 | youzhi92 |
| 版本隔离 `deviceInfo.sdkApiVersion` 在 Host Preview 环境下的取值可能与真机不同 | 测试 | 中 | SpecTest 需 Mock `deviceInfo.sdkApiVersion`，真机验证转入设备补验 | youzhi92 |
| Chip v16 版本（`chip_v16.ets`）需同步修改，改动面较大 | 进度 | 低 | v16 与 v1 结构一致，同步修改可控 | youzhi92 |
| Public API 审批流程可能影响交付时间（新增 5 个组件属性 + 2 个系统接口） | 流程 | 中 | 提前准备 API 审批材料，组件属性（Public API）和 uiMaterial 接口（System API）需分别推进审批 | youzhi92 |

## 设计审批

- [x] 需求基线已确认，设计覆盖 P0/P1 AC
- [x] 不涉及项已承接，N/A 和展开项都有结论
- [x] 涉及仓和模块职责清楚
- [x] 调用链层级分析完整，每层覆盖到位（含 uiMaterial 新增接口层）
- [x] 适用架构规则已识别并形成设计结论
- [x] 分层和子系统边界合规
- [x] API 变更有签名、权限、错误码和兼容性说明（含 uiMaterial 系统接口 @systemapi 标注）
- [x] BUILD.gn/bundle.json 影响明确（无变更）
- [x] 设计输出和后续 Task 拆分明确（含 TASK-0 uiMaterial 接口前置依赖）
- [x] 关键设计决策有理由和影响说明（含 ADR-6 EffectComponent 性能优化 + ADR-7 版本隔离）
- [x] 风险和开放问题有 Owner（含 uiMaterial 接口依赖风险 + 版本隔离 Mock 风险）
- [ ] uiMaterial `convertToECMaterial`/`convertToECSubMaterial` 接口交付依赖已与 uiMaterial 团队确认
- [ ] 版本隔离 API 26 起始版本已与 API 审批团队确认

**结论:** Draft — 待审阅