# AttributeModifier Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `AttributeModifier`

## 定位

本主题的主角是 **ArkTS 的 `AttributeModifier<T>` 接口**——通过 `.attributeModifier(modifier)` 绑定到组件的动态属性更新通路。开发者实现该接口的 6 个 `apply*Attribute` 回调（Normal/Pressed/Focused/Disabled/Selected/Hovered），由框架按组件 UI 状态位掩码分发：`applyNormalAttribute` 始终调用，其余按 `currentUIState & UI_STATE_*` 位与方法定义双条件调用。

ArkTS `AttributeModifier<T>` 的实现在 ark_component TS 层（`ArkComponent.ts` 的 `applyUIAttributes`/`applyUIAttributesInit`）+ 原生模块（`setSupportedUIState`/`getUIState`）。**不在 declarative_frontend C++**（`js_view_abstract.cpp` 仅注册 drawModifier/gestureModifier，无 attributeModifier）。命令式 `CommonModifier`/`XxxModifier` 类是 AttributeModifier 的一种"实现者"，但属 04-05-06 组件Modifier 域，非本主题。

行为事实以 SDK 类型声明（`common.d.ts`/`common.static.d.ets`/`enums.static.d.ets`）、ArkTS 实现（`ArkComponent.ts`/`ArkCommonModifier.ets`）、测试与长期规格为准；本页仅作路由导航，不重复行为矩阵。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **动态分发（主角）** | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts` | `applyUIAttributesInit`(:40-56) 按方法存在性 OR 状态位→`setSupportedUIState`；`applyUIAttributes`(:59-81) getUIState→按位调 6 个 apply |
| 静态分发 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-preprocessed/arkui/hooks/modifiers/ArkCommonModifier.ets` | `applyUIAttributes`(:36)/`applyUIAttributesUpdate`(:55)，UI_STATE_* 常量(:29-34) |
| 原生状态机 | `getUINativeModule().setSupportedUIState/getUIState` | 注册/查询 UI 状态位掩码 |
| C-API 类型 | `frameworks/core/interfaces/native/generated/interface/arkoala_api_generated.h` | `Ark_AttributeModifier` peer(:307)、`Ark_AttributeModifierState` 枚举(:4106) |
| C-API 实现 | `frameworks/core/interfaces/native/implementation/*_modifier.cpp` | GeneratedModifier `*AttributeModifier::SetXxxImpl` 每属性 setter |
| 命令式类(边界) | `frameworks/bridge/declarative_frontend/ark_modifier/src/*_modifier.ts` | 命令式 Modifier 实现 AttributeModifier（属 04-05-06） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 动态（主角）** | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `AttributeModifier<T>` 接口(:18450，@since 11/@atomicservice 12) + `attributeModifier()` 方法(:25179) |
| **SDK 静态（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 `AttributeModifier<T>`(:10787，@since 23) + `monitoredStates()`(:10858，staticonly) |
| 状态枚举 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/enums.static.d.ets` | `AttributeModifierState` 位掩码(:4781，@since 23；HOVERED @since 26.0.0) |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 动态装配 | `ArkComponent.ts` peer | `.attributeModifier(m)` 绑定到 peer |
| 动态状态注册 | `ArkComponent.ts:40-56` | applyUIAttributesInit 按方法存在性 OR UI_STATE_* → setSupportedUIState |
| 动态分发 | `ArkComponent.ts:59-81` | getUIState → applyNormalAttribute 始终 + 5 状态态按位条件 |
| 静态分发 | `ArkCommonModifier.ets:36/55` | applyUIAttributes(state=monitoredStates) + applyUIAttributesUpdate 状态变化重应用 |
| C-API 落地 | `implementation/*_modifier.cpp` | *AttributeModifier::SetXxxImpl → ModelStatic::SetXxx |

**关键版本**（详见 Feat 规格风险表）：动态 @since 11/@atomicservice 12、静态 @since 23；`applyHoveredAttribute` 动态/静态 @since 26.0.0（后增）；`ModifierUpdateStage` 不存在（实际为 `AttributeModifierState`，风险 R-2）；动态 attributeModifier 无 undefined 重载（风险 R-3）。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测 | `test/unittest/core/` | ArkComponent apply 分发、状态位推断 |
| C-API 单测 | `test/unittest/capi/` | *AttributeModifier setter accessor |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/05-custom-extension/02-dynamic-attributes/design.md` | Baselined（`DESIGN-Func-04-05-02`） |
| Feat-01 装配与状态监听 | `specs/04-common-capability/05-custom-extension/02-dynamic-attributes/Feat-01-attribute-modifier-mounting-state-spec.md` | Baselined |
| Feat-02 多状态应用与按位分发 | `specs/04-common-capability/05-custom-extension/02-dynamic-attributes/Feat-02-attribute-modifier-multi-state-dispatch-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| applyPressedAttribute 不触发 | 检查方法是否定义（!==undefined 才注册 UI_STATE_PRESSED 监听）。见 Feat-01 R-5 |
| applyNormalAttribute 在所有状态都调 | 设计如此：Normal 始终调建立基线，状态态叠加。见 Feat-02 R-1 |
| applyHoveredAttribute 编译/运行报错 | @since 26.0.0 后增，API<26 不可用。见 Feat-02 R-12 |
| 静态 monitoredStates 未生效 | 静态范式用 monitoredStates() 显式声明，非方法存在性推断。见 Feat-01 R-9 |
| attributeModifier 不在 js_view_abstract.cpp | 动态范式经 ark_component TS + 原生模块，非 declarative_frontend C++(风险 R-1)。见 Feat-01 R-2 |

## 调试入口

- **状态位**：`setSupportedUIState`/`getUIState` 原生模块调用为状态注册/查询来源。
- **方法存在性推断**：`ArkComponent.ts:40-56` 检查 `apply*Attribute !== undefined` 决定监听集。
- **命令式类边界**：`CommonModifier`/`XxxModifier` 的 applyNormalAttribute 转发 ModifierUtils（属 04-05-06）。

## 相关主题

- [DrawModifier](./draw_modifier.md) — 自定义绘制回调（04-05-01）
- [Component Modifier](./component_modifier.md) — 命令式 Modifier 类实现 AttributeModifier（04-05-06）
- [Custom Property](./custom_property.md) — customProperty 自定义属性（04-05-05）
