# SymbolGlyph Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `SymbolGlyph`

## 定位

SymbolGlyph 是 HMSymbol 矢量符号字体渲染组件，支持多色/多层透明度/动效。它**不拥有独立 Pattern**：节点以 `"SymbolGlyph"` tag 创建，但复用 `TextPattern` 的排版/绘制/选择/拖拽能力；SymbolGlyph 专属逻辑经 `SymbolType`/`SymbolSourceInfo`/`SymbolStyle` 字段组在共享 `TextLayoutProperty` 上分支。行为事实以 SDK 声明、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Model（Create/Set 全量） | `frameworks/core/components_ng/pattern/symbol/symbol_model_ng.cpp` | Create 经 `FrameNode::GetOrCreateFrameNode("SymbolGlyph", ...TextPattern)` |
| Model 抽象 | `frameworks/core/components_ng/pattern/symbol/symbol_model.h` | `SymbolModel` 虚接口 |
| 静态范式 Model | `frameworks/core/components_ng/pattern/symbol/symbol_model_static.h/.cpp` | 静态 ArkTS |
| 常量/枚举/struct | `frameworks/core/components_ng/pattern/symbol/constants.h` | `SymbolEffectType`/`SymbolType`/`SymbolGradientType`/`SDKGradientDirection`/`SymbolGradient`/`SymbolShadow` |
| 符号源信息 | `frameworks/core/components_ng/pattern/symbol/symbol_source_info.h` | `SymbolSourceInfo`(unicode) |
| 动效选项 | `frameworks/core/components_ng/pattern/symbol/symbol_effect_options.h` | `SymbolEffectOptions` |
| 属性存储（共享） | `frameworks/core/components_ng/pattern/text/text_layout_property.h` | `SymbolStyle` 字段组（SymbolSourceInfo/SymbolColorList/SymbolRenderingStrategy/SymbolEffectStrategy/SymbolEffectOptions/SymbolShadow/ShaderStyle/FontColorResource 等）+ FontStyle 组 |
| 共享 Pattern | `frameworks/core/components_ng/pattern/text/text_pattern.cpp` | 排版/绘制/选择/拖拽分支 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/symbolglyph.d.ts` | 公共契约 `SymbolGlyphAttribute`、7 个 `SymbolEffect` 子类、枚举 |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/SymbolGlyph.static.d.ets` | 静态 ArkTS |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/SymbolGlyphModifier.d.ts` | 动态 Modifier |
| C API | `frameworks/core/interfaces/arkoala/arkoala_api.h`（`ArkUISymbolGlyphModifier` 函数指针表） | NDK Modifier 面，无独立 `NODE_SYMBOL*` 节点类型 |
| C API accessor | `frameworks/core/interfaces/native/node/node_symbol_glyph_modifier.h` | `GetSymbolGlyphModifier()`/`GetCJUISymbolGlyphModifier()`/`GetSymbolGlyphCustomModifier()` |
| CJ FFI | `frameworks/bridge/cj_frontend/interfaces/cj_ffi/cj_symbol_glyph_ffi.h` | CJ 前端 |

### API 解析实现路径

SymbolGlyph 已完成组件化改造（在 `adapter/ohos/osal/dynamic_module_helper.cpp` 动态模块列表中，键 `"SymbolGlyph"`→模块 `"symbol"`，独立 so `libarkui_symbol.z.so`）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_modifier/src/symbol_glyph_modifier.ts` + `frameworks/bridge/declarative_frontend/ark_component/src/arkSymbolGlyph.ts`（若存在） | ArkTS Modifier 类，经 `applySymbolGlyphModifierToNode` 挂接 |
| 统一 Bridge（声明式+动态属性） | `frameworks/core/components_ng/pattern/symbol/bridge/arkts_native_symbol_glyph_bridge.cpp` | `SymbolGlyphBridge`，`RegisterSymbolGlyphAttributes` |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/symbol/bridge/symbol_glyph_dynamic_modifier.cpp` | `GetSymbolGlyphDynamicModifier` 动态属性表 |
| Static Modifier | `frameworks/core/components_ng/pattern/symbol/bridge/symbol_glyph_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/symbol/bridge/symbol_glyph_dynamic_module.cpp` | `SymbolGlyphDynamicModule`，`libarkui_symbol.z.so` 入口 `OHOS_ACE_DynamicModule_Create_SymbolGlyph` |
| Custom Modifier | `frameworks/core/components_ng/pattern/symbol/bridge/symbol_glyph_custom_modifier.h` | 自定义字形/扩展 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_symbol_glyph_modifier.h` | 经 `DynamicModuleHelper` 转发到动态模块 |

组件化改造参考：`./组件化重构通用方案.md`（如存在）。改造后 JSView 与 Bridge 双路径统一到 `pattern/symbol/bridge/`，输出独立 so。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 矢量符号字体 | `symbol_model_ng.cpp`/共享 `text_pattern.cpp` | HMSymbol 字体资源 | — | HMSymbol 矢量字形加载与绘制 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测 | `test/unittest/core/pattern/symbol/` | SymbolGlyph Pattern/Model 单测 |
| C-API 单测 | `test/unittest/capi/modifiers/symbol_glyph_modifier_test.cpp` | NDK Modifier 面 |

### 相关 Spec

| Spec 域 | 路径 | 状态 |
|---------|------|------|
| SymbolGlyph 长期规格 | `specs/05-ui-components/09-text-components/07-symbol-glyph/` | active（8 个 Feat：字形选择/字体/颜色渐变/渲染策略/动效策略/Effect 子类/阴影/多范式接口） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 符号不显示/字形错 | `symbol_source_info.h` + `SetSymbolGlyphInitialize`/`SetSymbolFontFamilies` |
| 颜色/渐变不生效 | `text_layout_property.h` SymbolStyle 组（SymbolColorList MEASURE_SELF/ShaderStyle） |
| 动效不触发 | `symbol_effect_options.h` + `UpdateSymbolEffect(type, isActive, isTxtActiveSource)` |
| 公共 ArkTS 缺 symbolColor/shaderStyle/shadow | 仅 C-API/koala 内部面，非公共 .d.ts（见 Spec 兼容性风险表） |

## 调试入口

Dump：共享 `TextPattern` dump 路径；属性经 `TextLayoutProperty` SymbolStyle 组查询。

## 相关主题

- [Text](./text.md)（SymbolGlyph 复用 TextPattern）
- [StyledString](../capabilities/styled-string.md)（属性字符串，TextSpan 体系）
