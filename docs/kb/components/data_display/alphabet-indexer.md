# AlphabetIndexer Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `AlphabetIndexer`

## 定位

AlphabetIndexer 是 ArkUI 的字母索引组件，提供按字母快速定位列表内容的能力，支持自定义字母列表、弹窗样式、多语言索引、ArcIndexer（弧形索引）等。组件**未废弃**（仅方法级 `onSelected` 自 API 8 起废弃，推荐使用 `onSelect` 替代）。行为事实以 SDK `.d.ts` 声明、源码、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 主逻辑 | `frameworks/core/components_ng/pattern/indexer/indexer_pattern.h/cpp` | 生命周期、字母列表管理、弹窗控制、触摸/滑动交互 |
| Model 层 | `frameworks/core/components_ng/pattern/indexer/indexer_model_ng.h/cpp` | 动态版属性设置入口 |
| Model 静态版 | `frameworks/core/components_ng/pattern/indexer/indexer_model_static.h/cpp` | ArkTS 静态版 Model |
| Model 桥接 | `frameworks/core/components_ng/pattern/indexer/indexer_model_impl.h/cpp` | Model 声明/实现分层 |
| Layout 属性 | `frameworks/core/components_ng/pattern/indexer/indexer_layout_property.h/cpp` | 字母列表、弹窗样式、颜色等布局属性 |
| Layout 算法 | `frameworks/core/components_ng/pattern/indexer/indexer_layout_algorithm.h/cpp` | AlphabetIndexer 布局计算 |
| Paint 属性 | `frameworks/core/components_ng/pattern/indexer/indexer_paint_property.h` | 绘制相关属性 |
| Event Hub | `frameworks/core/components_ng/pattern/indexer/indexer_event_hub.h` | onSelect/onRequestPopupData 等事件 |
| Theme | `frameworks/core/components_ng/pattern/indexer/indexer_theme.h` | 主题资源配置 |
| ArcIndexer Pattern | `frameworks/core/components_ng/pattern/indexer/arc_indexer_pattern.h/cpp` | 弧形索引专用 Pattern |
| ArcIndexer Layout | `frameworks/core/components_ng/pattern/indexer/arc_indexer_layout_algorithm.h/cpp` | 弧形索引布局算法 |
| ArcIndexer Layout 属性 | `frameworks/core/components_ng/pattern/indexer/arc_indexer_layout_property.h/cpp` | 弧形索引布局属性 |
| ArcIndexer Paint | `frameworks/core/components_ng/pattern/indexer/arc_indexer_paint_method.h` | 弧形索引绘制 |
| ArcIndexer Content Modifier | `frameworks/core/components_ng/pattern/indexer/arc_indexer_content_modifier.h/cpp` | 弧形索引内容修饰器 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/alphabet_indexer.d.ts` | AlphabetIndexer 公开 API（含 ArcIndexer） |
| Static | `<OH_ROOT>/interface/sdk-js/api/arkui/component/alphabetIndexer.static.d.ets` | 静态版 API 定义 |
| Modifier Dynamic | `<OH_ROOT>/interface/sdk-js/api/arkui/AlphabetIndexerModifier.d.ts` | 属性修改器动态版 |
| Modifier Static | `<OH_ROOT>/interface/sdk-js/api/arkui/AlphabetIndexerModifier.static.d.ets` | 属性修改器静态版 |
| C API enums | `interfaces/native/native_node.h` | ArkUI AlphabetIndexer 相关枚举值 |

### API 解析实现路径

AlphabetIndexer **已组件化**（有 `bridge/` 子目录、DynamicModule、统一 Bridge，旧 JSView 已移除）。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端组件类 | `frameworks/bridge/declarative_frontend/ark_component/components/arkalphabetindexer.js` | ArkTS 前端组件定义 |
| 统一 Bridge | `frameworks/core/components_ng/pattern/indexer/bridge/arkts_native_alphabet_indexer_bridge.cpp` | 通过 `IsJsView()` 区分模式，统一参数解析 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/indexer/bridge/indexer_dynamic_modifier.cpp` | 动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/indexer/bridge/indexer_static_modifier.cpp` | 静态编译路径 |
| Dynamic Module | `frameworks/core/components_ng/pattern/indexer/bridge/indexer_dynamic_module.cpp` | DynamicModule 派生类 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/alphabet_indexer_modifier.cpp` | C API 属性设置 |
| 前端 Modifier | `frameworks/bridge/declarative_frontend/ark_modifier/src/alphabet_indexer_modifier.ts` | ArkTS Modifier 类 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/indexer/` | Pattern/Model/Layout 单元测试 |
| C API 测试 | `test/unittest/capi/modifiers/alphabet_indexer_modifier_test.cpp` | Modifier C API 测试 |

### 相关 Spec

| Spec 域 | 路径 | 说明 |
|---------|------|------|
| 创建与基础样式 | `specs/05-ui-components/03-scroll-container-components/02-alphabet-indexer/Feat-01-alphabet-indexer-creation-basic-style-spec.md` | Func-05-03-02-Feat-01 |
| Popup 样式与交互 | `specs/05-ui-components/03-scroll-container-components/02-alphabet-indexer/Feat-02-alphabet-indexer-popup-style-interaction-spec.md` | Func-05-03-02-Feat-02 |
| Design | `specs/05-ui-components/03-scroll-container-components/02-alphabet-indexer/design.md` | 架构设计文档 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 字母索引不响应触摸/滑动 | `indexer_pattern.cpp`（触摸事件处理逻辑） |
| 弹窗样式异常 | `indexer_layout_property.h`（popup 相关属性） |
| ArcIndexer 弧形布局计算错误 | `arc_indexer_layout_algorithm.cpp` |
| 属性设置未生效（动态版） | `arkts_native_alphabet_indexer_bridge.cpp` → `indexer_dynamic_modifier.cpp` |
| 属性设置未生效（静态版） | `arkts_native_alphabet_indexer_bridge.cpp` → `indexer_static_modifier.cpp` |
| onSelect 回调不触发 | `indexer_event_hub.h`、`indexer_pattern.cpp`（事件注册与触发） |
| C API Modifier 编译/链接错误 | `alphabet_indexer_modifier.cpp`、`alphabet_indexer_modifier.h` |

## 调试入口

- Pattern 状态调试：`indexer_pattern.cpp` 中 `OnModifyDone` / `OnAttachToMainTree`
- 弧形索引绘制调试：`arc_indexer_paint_method.h` / `arc_indexer_content_modifier.cpp`
- 弹窗显示调试：`indexer_pattern.cpp` 中 popup 相关方法
- 组件化 Bridge 调试：`arkts_native_alphabet_indexer_bridge.cpp` 中 `IsJsView()` 分流判断

## 相关主题

- [List](../container/list.md) — AlphabetIndexer 通常配合 List 组件使用
- [Swiper](../container/swiper.md) — 同属滚动容器类组件