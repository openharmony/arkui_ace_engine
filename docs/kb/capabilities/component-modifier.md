# ComponentModifier Context

> 文档版本：v2.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `ComponentModifier`

## 定位

本主题的主角是 **ArkTS 的命令式 Modifier 类体系**——`CommonModifier` 基类 + 60+ 具体组件命令式 Modifier 类（`ButtonModifier`/`TextModifier`/…），经 `@ohos.arkui.modifier` 模块 barrel 导出。这些类实现 `AttributeModifier<T>` 接口，可传给 `.attributeModifier()` 复用；其 `applyNormalAttribute` 经 `ModifierUtils` 把 `ModifierWithKey` 属性 merge 到目标组件并调原生 setter。

`CommonModifier extends ArkComponent`（持有 nativePtr 组件代理）`implements AttributeModifier<CommonAttribute>`，使命令式类既是组件代理（可链式调属性方法）又是 AttributeModifier。属性应用经 ModifierUtils.applyAndMergeModifier merge `_modifiersWithKeys` → applyPeer 调原生 setter。**AttributeModifier 通路本身（装配/状态分发）属 04-05-02，非本主题**。

> **边界说明**：ModifierWithKey 装配机制（stageValue/applyPeer/ModifierMap）与原生 setter 落地链属框架内部实现，方案见 `specs/04-common-capability/05-custom-extension/06-component-modifier/design.md`；spec（Feat-02）仅固化 ModifierUtils 对外接口（applyAndMergeModifier/applySetOnChange/putDirtyModifier/isInstanceOf）的可观测行为。行为事实以 SDK 类型声明、ArkTS 实现、测试与长期规格为准；本页仅作路由导航。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 命令式基类 | `frameworks/bridge/declarative_frontend/ark_modifier/src/common_modifier.ts` | CommonModifier extends ArkComponent implements AttributeModifier；applyNormalAttribute 转发 ModifierUtils |
| 具体类 | `frameworks/bridge/declarative_frontend/ark_modifier/src/` | 60+ 组件 Modifier（*_modifier.ts），extends 组件 Ark 基类 implements AttributeModifier<T> |
| 装配 | `frameworks/bridge/declarative_frontend/ark_modifier/src/modifier_utilities.ts` | ModifierUtils：applyAndMergeModifier/applySetOnChange/applyPeer/putDirtyModifier |
| 静态类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-preprocessed/arkui/` | 生成式 *Modifier.ets（applyModifierPatch0 按 flagArray 调 peer setter） |
| 静态基类边界 | 同上 `CommonMethodModifier.ets` | attributeModifier 占位 throw Not implemented（真实挂接由 hooks/peer） |
| C-API setter | `frameworks/core/components_ng/pattern/<comp>/bridge/` | 各组件 *AttributeModifier::SetXxxImpl 每属性 setter |
| C-API 实现 | `frameworks/core/interfaces/native/implementation/` | GeneratedModifier 原生实现 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| SDK 基类 | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | CommonModifier extends CommonAttribute implements AttributeModifier |
| SDK 基类静态 | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | 静态 CommonModifier |
| SDK barrel | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.modifier.d.ts` | re-export CommonModifier + 60+ XxxModifier + ModifierUtils |
| SDK ModifierUtils | `<OH_ROOT>/interface/sdk-js/api/arkui/ModifierUtils.d.ts` | ModifierUtils 类 + isInstanceOf（@since 26.0.0 dynamiconly） |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测 | `test/unittest/core/` | CommonModifier/ModifierUtils 属性装配与落地 |
| C-API 单测 | `test/unittest/capi/` | *AttributeModifier setter accessor |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/05-custom-extension/06-component-modifier/design.md` | Baselined（DESIGN-Func-04-05-06） |
| Feat-01 命令式 Modifier 基类与类体系 | `specs/04-common-capability/05-custom-extension/06-component-modifier/Feat-01-common-modifier-class-system-spec.md` | Baselined |
| Feat-02 ModifierUtils.isInstanceOf | `specs/04-common-capability/05-custom-extension/06-component-modifier/Feat-02-modifier-utils-api-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| modifier 属性设置后组件未更新 | applyNormalAttribute 经 ModifierUtils.applyAndMergeModifier → applyPeer 调原生 setter；检查 nativePtr 是否有效 |
| ModifierUtils.isInstanceOf 报不可用 | @since 26.0.0 dynamiconly，API<26 或静态范式不可用 |
| 静态范式 attributeModifier 抛 Not implemented | 静态基类占位，真实挂接由 hooks/peer |
| 命令式类与 AttributeModifier 通路关系 | 命令式类是 AttributeModifier 的实现者；装配/状态分发属 04-05-02 |
| 同属性多次设置行为 | 内部装配行为（stageValue/ModifierMap），属框架实现，见 design.md |

## 调试入口

- 命令式类状态：`common_modifier.ts` 的 nativePtr + _modifiersWithKeys（ModifierMap）为属性装配来源。
- ModifierUtils：`modifier_utilities.ts`/`arkModifier.js` 的 applyAndMergeModifier/applyPeer/putDirtyModifier 为落地链。
- 静态 flagArray：`*Modifier.ets` 的 _Xxx_flagArray 标志位驱动静态范式 peer setter。

## 相关主题

- [Attribute Modifier](./attribute-modifier.md) — AttributeModifier<T> 动态属性通路（04-05-02），命令式类是其实现者
- [DrawModifier](./draw-modifier.md) — 自定义绘制回调（04-05-01）
- [Custom Property](./custom-property.md) — customProperty 自定义属性（04-05-05）