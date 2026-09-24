# 文本测量 Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextMeasurement`

## 定位

文本测量提供 standalone（独立）文本测量能力：模块级 `@ohos.measure`、UI 上下文绑定 `UIContext.MeasureUtils`、静态 ArkTS `@ohos.measure` 三入口必须落到同一 `MeasureUtil::MeasureText/MeasureTextSize`，共享同一 `RosenFontCollection` 单例。`measureText` 仅测单行宽度（布局约束参数被静默忽略），`measureTextSize` 测多行宽高。

具体测量语义、单位修正、废弃迁移与兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。组件级排版测量（`getParagraphs`+`@ohos.graphics.text.Paragraph`）与组件级行级度量查询（`LayoutManager`）属后续 Feat，不在本域基线。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 内核工具层（单行/多行测量） | `frameworks/base/utils/measure_util.h`、`measure_util.cpp` | `MeasureUtil::MeasureText`→`MeasureTextInner`（单行，INFINITE_SIZE）；`MeasureUtil::MeasureTextSize`→`MeasureTextSizeInner`（多行） |
| 委托层（动态，API 12 fontSize 单位修正） | `frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.cpp` | `FrontendDelegateDeclarativeNG::MeasureText/MeasureTextSize`，API<12 改写 FP→VP |
| 字体集合层（共享单例） | `frameworks/core/components/font/rosen_font_collection.h`、`rosen_font_collection.cpp` | `GetInstance().GetFontCollection()` 与 NG TxtFontCollection 共享 shared_ptr |
| NG 字体集合 | `frameworks/core/components_ng/render/adapter/txt_font_collection.h`、`txt_font_collection.cpp` | form 场景 per-env 集合 |
| 字体集合抽象 | `frameworks/core/components_ng/render/font_collection.h` | NG 字体集合 |
| 字体加载回调（standalone 不注册） | `frameworks/core/common/font_manager.h`、`font_loader.h` | `RegisterCallbackNG` 仅 NG 组件注册；standalone 不自动重跑 |
| inner_api 镜像（仅 2 字段） | `interfaces/inner_api/ace_kit/include/ui/base/utils/measure_utils.h`、`interfaces/inner_api/ace_kit/src/utils/measure_utils.cpp` | `Kit::MeasureUtils::GetMeasureTextSize` 仅 data+fontSize |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态模块级（@since 18 弃用） | `<OH_ROOT>/interface/sdk-js/api/@ohos.measure.d.ts` | `MeasureText.measureText/measureTextSize`，`@useinstead`→UIContext.MeasureUtils |
| 动态 UIContext | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | `getMeasureUtils().measureText/measureTextSize` |
| 静态 ArkTS（@since 23 static，未弃用） | `<OH_ROOT>/interface/sdk-js/api/@ohos.measure.static.d.ets`、`@ohos.arkui.UIContext.static.d.ets` | 返回 double 而非 number |
| 共享类型（MeasureOptions/SizeOptions） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_common.d.ts`、`units.d.ts` | SizeOptions 定义 |
| NAPI 绑定（动态） | `interfaces/napi/kits/measure/js_measure.cpp` | measureText 解析 6 属性、measureTextSize 解析 15 属性；非对象入参返回 null |
| 薄 JS 包装 | `interfaces/napi/kits/measure/measure.js` | `requireInternal("measure")` |
| ANI 桥（静态，不经委托直调内核） | `frameworks/core/interfaces/native/implementation/global_scope_ohos_measure_utils_accessor.cpp` | 反序列化 options → 直接调 MeasureUtil，含 API 12 单位门控 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 排版引擎 | `measure_util.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/`（Rosen::Typography/TypographyCreate/TextStyle/FontCollection） | 实际排版计算，非本仓代码 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/base/measure_util_test.cpp` | 内核测量 |
| 单元测试 | `test/unittest/core/property/measure_utils_test_ng.cpp` | NG 属性测量 |

### 相关 Spec

| Spec 域 | 路径 |
|---------|------|
| 功能域 design | `specs/04-common-capability/13-font-text/02-text-measurement/design.md` |
| Feat-01 独立文本测量能力 | `specs/04-common-capability/13-font-text/02-text-measurement/Feat-01-standalone-text-measurement-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| measureText 注入 constraintWidth/maxLines 返回值不变 | `measure_util.cpp` 的 `MeasureTextInner`：恒用 `Layout(INFINITE_SIZE)`，仅解析 6 属性，不读布局参数 |
| measureTextSize 设 constraintWidth 返回约束本身而非实际宽度 | `measure_util.cpp` 的 `MeasureTextSizeInner`：设约束即返 `constraintWidth.px` |
| 跨版本测量结果差异（API 12） | `frontend_delegate_declarative_ng.cpp` 的单位修正：API<12 裸数字 fontSize 按 VP，API≥12 按 FP |
| 非对象入参无错误码返回 null | `js_measure.cpp`：`napi_typeof` 非 object 直接 `return nullptr`，整个 measure 表面零 `@throws` |
| 字体加载后测量不自动更新 | standalone `MeasureUtil` 不注册回调；需调用方在字体加载完成事件后重新调用 |
| inner_api 测量能力受限 | `Kit::MeasureContext` 仅镜像 2 字段（data+fontSize），其余 16 字段保持默认 |
| 字体集合 null 返回 0 | `measure_util.cpp`：`GetFontCollection()` 返 null 时 `LOGW` 后返 0.0/Size(0,0) |

## 调试入口

- 测量链路：`measure.js` → `js_measure.cpp`（解析）→ `EngineHelper::GetCurrentDelegateSafely()` → `FrontendDelegateDeclarativeNG::MeasureText`（单位修正）→ `MeasureUtil::MeasureText` → `RosenFontCollection::GetInstance().GetFontCollection()` → `Rosen::TypographyCreate::Create` → `Layout` → `GetActualWidth()`/`GetHeight()`
- 多窗口下模块级 API 错配：`js_measure.cpp` 经 `EngineHelper` 取当前 UI 上下文委托，多窗口下可能取错上下文（ADR-5 废弃根因）

## 相关主题

- `FontRegistration`（字体注册）— 共享同一 RosenFontCollection 单例，注册后测量可见
- `TextCommonAttributes`（文本通用属性）— 测量使用的 fontSize/fontStyle/fontWeight/fontFamily/letterSpacing 等样式定义