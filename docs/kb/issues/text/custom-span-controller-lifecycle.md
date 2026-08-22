# CustomSpan Controller Lifecycle Issue Context

> 文档版本：v1.0
> 更新时间：2026-07-31
> 来源：`docs/context_registry.json` 主题 `CustomSpanControllerLifecycle`

## 定位

本页用于排查 Text 通过 `TextController` 设置 `MutableStyledString` 后，`CustomSpan` 的 `onMeasure`、`onDraw` 回调因 JS 对象提前释放而出现的稳定性问题。问题关键不在 CustomSpan 的绘制实现，而在 `JSTextController` 与 Text 宿主之间是否建立了同生命周期的强持有关系。行为结论应以当前源码、测试与对应历史提交为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 搜索词 |
|----------|----------|--------|
| Text 创建与 JS Controller 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_text.cpp` | `JSText::Create`、`BindJSTextController`、`controllerObj` |
| JSTextController 持有关系 | `frameworks/bridge/declarative_frontend/jsview/js_text.h` | `JSTextController`、`controllerWeak_`、`styledString_` |
| JS Controller 到 TextPattern 转发 | `frameworks/core/components_ng/pattern/text/text_model.h`、`text_model_ng.h/.cpp` | `BindJSTextController` |
| Text 宿主生命周期锚点 | `frameworks/core/components_ng/pattern/text/text_pattern.h` | `jsTextControllerBinder_`、`BindJSTextController` |
| CustomSpan JS 对象与回调包装 | `frameworks/bridge/declarative_frontend/style_string/js_span_object.h/.cpp` | `JSCustomSpan`、`customSpanObj_`、`onMeasure`、`onDraw` |
| StyledString 对 CustomSpan 的保存 | `frameworks/bridge/declarative_frontend/style_string/js_span_string.cpp` | `ParseJsCustomSpan`、`CUSTOM_STORE_KEY`、`SetPropertyObject` |
| JS 回调 this 对象持有方式 | `frameworks/bridge/declarative_frontend/engine/functions/js_function.h` | `jsThis_`、`JSWeak`、`This` |

### API 入口

| 范式 | 稳定路径 | 关注点 |
|------|----------|--------|
| StyledString 动态 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/styled_string.d.ts` | `CustomSpan`、`MutableStyledString`、`onMeasure`、`onDraw` |
| Text 动态 API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text.d.ts` | `TextController`、`setStyledString` |
| Text Controller 公共声明 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_common.d.ts` | `StyledStringController`、Controller 生命周期入口 |

### 测试入口

| 范围 | 稳定路径 | 用途 |
|------|----------|------|
| SpanString 与 CustomSpan | `test/unittest/core/pattern/text/span_string_test_ng.cpp` | CustomSpan 数据模型与 SpanString 行为 |
| TextPattern 与 Controller | `test/unittest/core/pattern/text/text_test_ng.cpp` | Text 创建、Pattern 和 Controller 相关行为 |
| Text 补充测试 | `test/unittest/core/pattern/text/` | 搜索 `CustomSpan`、`TextController`、`BindJSTextController` |

### 历史证据

| 提交 | 用途 |
|------|------|
| `d694594f4b2a26c84d96d233d6ba5a1123b4ae86` | 对比 `JSTextController` 未与 Text 生命周期绑定时的实现，以及通过 `TextPattern` 保存 JS 强引用后的修复 |

### 相关 Spec

- Text Spec：`specs/05-ui-components/09-text-components/04-text/`（若 Specs 仓中该目录可用）
- StyledString/CustomSpan 的独立 Spec 路由尚未在 `specs/registry/functions.yaml` 注册。

## 常见问题定位

| 现象 | 优先检查 |
|------|----------|
| `CustomSpan.onMeasure` 或 `onDraw` 偶现崩溃、回调对象失效 | `JSText::Create` 是否把 Controller 的 JS 对象绑定到当前 `TextPattern` |
| Controller 仍可访问，但其关联的 StyledString 或 CustomSpan 被提前回收 | 从 `TextPattern` 的生命周期锚点反向检查 `JSTextController`、`MutableStyledString`、`CustomSpan` 的 JS 强引用链 |
| 修复后担心形成循环引用 | 检查 `JSTextController::controllerWeak_` 是否仍为 `WeakPtr<TextControllerBase>`，不要把 Native Controller 反向改成强持有 |
| 仅修改 CustomSpan 回调包装后问题仍存在 | 检查缺失的宿主生命周期边，不要只关注 `JsFunction` 保存的函数对象 |

## 调试入口

- 在 `JSText::Create` 记录 Controller JS 对象绑定、TextPattern 创建和销毁的顺序。
- 在触发 GC 后分别验证 Text 仍在树上和 Text 已销毁两种场景，观察 `CustomSpan.onMeasure`、`onDraw` 是否只在宿主存活期间可调用。
- 对照 `JSTextController::controllerWeak_` 与 `TextPattern::jsTextControllerBinder_`，确认强引用只沿 TextPattern 到 JS Controller 单向建立。
- 使用 `git show d694594f4b2a26c84d96d233d6ba5a1123b4ae86` 对比生命周期绑定引入前后的源码。

## 相关主题

- [docs/kb/capabilities/styled-string.md](../../capabilities/styled-string.md)
- [docs/kb/components/basic/text.md](../../components/basic/text.md)
- [docs/kb/architecture/dfx/memory-management.md](../../architecture/dfx/memory-management.md)