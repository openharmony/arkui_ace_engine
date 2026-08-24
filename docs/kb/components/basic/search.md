# Search Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Search`

## 定位

Search 是 ArkUI 的基础搜索输入框组件，面向应用侧提供文本输入、搜索按钮、搜索图标、取消按钮、占位符、自适应字号、键盘控制、选区光标、事件回调和 SearchController 等能力。Search 内部以组合模式创建 TextField 子节点（slot 0），复用 TextField 的文本输入/选择/复制能力，同时叠加搜索按钮、图标、取消按钮、分割线等 Search 专有子节点。

本文档用于快速定位 Search 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、子节点管理、事件、颜色配置 | `frameworks/core/components_ng/pattern/search/search_pattern.cpp` | Search 组件核心行为实现入口 |
| Pattern 类型和接口 | `frameworks/core/components_ng/pattern/search/search_pattern.h` | `SearchPattern` 类型声明 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/search/search_model_ng.cpp` | 动态前端 Search 创建和属性写入入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/search/search_model_static.cpp` | 静态前端 Search 属性写入入口 |
| 组合节点结构 | `frameworks/core/components_ng/pattern/search/search_node.cpp`、`search_node.h` | `SearchNode`(GroupNode) 六槽位子节点管理、`IconOptions` 值对象 |
| 布局算法 | `frameworks/core/components_ng/pattern/search/search_layout_algorithm.cpp`、`search_layout_algorithm.h` | 子节点测量/定位、搜索按钮/分割线/图标/取消按钮布局 |
| 属性存储 | `frameworks/core/components_ng/pattern/search/search_layout_property.h` | `SearchButton`/`CancelButtonStyle`/`FontFeature`/`StrokeWidth`/`StrokeColor` 等 Search 专有属性 |
| 事件存储 | `frameworks/core/components_ng/pattern/search/search_event_hub.h`、`search_event_hub.cpp` | `onSubmit`/`onChange`/`onCopy`/`onCut`/`onPaste` 存储与触发 |
| 手势事件 | `frameworks/core/components_ng/pattern/search/search_gesture_event_hub.h`、`search_gesture_event_hub.cpp` | 并行点击手势组合 |
| 子文本框 | `frameworks/core/components_ng/pattern/search/search_text_field.cpp`、`search_text_field.h` | `SearchTextFieldPattern`(extends TextFieldPattern) 子节点 |
| 主题 | `frameworks/core/components/search/search_theme.h`、`frameworks/core/components_ng/pattern/search/search_theme_wrapper.h` | 颜色/尺寸/间距默认值 |
| 多线程创建 | `frameworks/core/components_ng/pattern/search/search_pattern_multi_thread.cpp`、`search_model_ng_multi_thread.cpp` | 线程安全创建路径 |
| C API 枚举 | `interfaces/native/native_node.h` | Search C API 属性和事件枚举 |
| C API 修饰符声明 | `frameworks/core/interfaces/native/node/search_modifier.h` | `NodeModifier::GetSearchModifier` 等声明 |
| C API 修饰符实现 | `frameworks/core/interfaces/native/implementation/search_modifier.cpp`、`search_ops_accessor.cpp` | 动态模块加载入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/search.d.ts` | 动态 ArkTS `SearchInterface`、`SearchOptions`、`SearchAttribute`、`SearchController`、`SearchType`、`CancelButtonStyle` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/search.static.d.ets` | 静态 ArkTS Search 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SearchModifier.d.ts` | 动态 `SearchModifier` 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SearchModifier.static.d.ets` | 静态 `SearchModifier` 声明 |
| CAPI / NDK | `interfaces/native/native_node.h`、`frameworks/core/interfaces/native/node/search_modifier.h` | Search C API 属性、事件和修饰符入口 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `SearchAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `SearchInterface`、`SearchOptions` 或 `Search(`。
- Modifier：在 `SearchModifier*.d.ts` / `SearchModifier*.d.ets` 中确认继承或实现关系。
- C API：在 `interfaces/native/native_node.h` 中搜索 Search 相关枚举。
- 排版属性大部分存于子 `TextFieldLayoutProperty`，仅 `FontFeature`/`StrokeWidth`/`StrokeColor` 存于 `SearchLayoutProperty`。

### API 解析实现路径

Search 组件**已完成组件化改造**，属性解析统一到 `pattern/search/bridge/`，编译产物为独立 so。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/search/bridge/arkts_native_search_bridge.cpp` | `SearchBridge::RegisterSearchAttributes` 注册 `search` 对象；`JsCreate`/`SetSearchButton`/`SetCaretStyle` 等；通过 `IsJsView()` 区分模式 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/search/bridge/search_dynamic_modifier.cpp` | C-ABI 函数指针表 `ArkUISearchModifier`/`CJUISearchModifier`/`ArkUISearchCustomModifier` |
| Static Modifier | `frameworks/core/components_ng/pattern/search/bridge/search_static_modifier.cpp` | Arkoala 生成式 API（`ConstructImpl`/`SetSearchOptionsImpl`/`SetSearchButtonImpl`） |
| Dynamic Module | `frameworks/core/components_ng/pattern/search/bridge/search_dynamic_module.cpp` | `SearchDynamicModule`(`DynamicModule`)，`libarkui_search.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/implementation/search_modifier.cpp` | 通过 `DynamicModuleHelper` 转发到动态模块的 `GetStaticModifier`/`GetDynamicModifier` |
| Custom Modifier | `frameworks/core/components_ng/pattern/search/bridge/search_custom_modifier.h` | `ArkUISearchCustomModifier` 结构（createNormalSearch/setUserMargin/setTextValue 等） |
| 遗留 JSView | `frameworks/bridge/declarative_frontend/jsview/js_search.cpp` | 旧路径，仅注册 `SearchController`（`JSTextEditableController` 别名）；属性绑定已迁移到 bridge/ |

独立 so 名称：`libarkui_search.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 震感反馈 | `adapter/ohos/entrance/vibrator/vibrator_utils.cpp`、`frameworks/core/common/vibrator/vibrator_utils.h` | `base/sensors/miscdevice` | `interfaces/inner_api/vibrator/vibrator_agent.h` | `enableHapticFeedback` 门控 `VibratorUtils::StartVibraFeedback` → `Sensors::StartVibrator`；需 `ohos.permission.VIBRATE` |
| 图形绘制 / 排版 | 经子 `TextFieldPattern` 间接依赖 | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/`、`frameworks/text/interface/export/rosen_text/` | Search 将文本渲染委托给子 TextField，间接依赖 Rosen 绘制和排版 |
| 剪贴板 / UDMF | 经子 `TextFieldPattern` 间接依赖 | `foundation/distributeddatamgr/pasteboard`、`foundation/distributeddatamgr/udmf` | — | 复制/剪切/粘贴/拖拽经子 TextField 间接依赖 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/search/` | Pattern、布局、Model、装饰等 Search 行为回归 |
| C-API Modifier 测试 | `test/unittest/capi/modifiers/search_modifier_test*.cpp`、`search_modifier_resources_test.cpp`、`search_modifier_callbacks_test.cpp` | C-API 修饰符表测试 |
| C-API Accessor 测试 | `test/unittest/capi/accessors/search_modifier_impl_accessor_test.cpp`、`search_controller_test.cpp` | Accessor 和 Controller 测试 |
| Mock | `test/mock/frameworks/core/components_ng/pattern/search/bridge/mock_search_modifier.cpp` | Bridge mock |
| Spec 功能域 | `specs/05-ui-components/09-text-components/03-search/` | Search 功能域设计、验收和验证契约 |
| Spec 总索引 | `specs/index.md` | `05-09-03 Search` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | Search 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Search 功能域：`specs/05-ui-components/09-text-components/03-search/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 组件构建与搜索按钮 | `Feat-01-search-construction-and-button-spec.md` |
| Feat-02 | 搜索图标与取消按钮 | `Feat-02-search-icon-and-cancel-button-spec.md` |
| Feat-03 | 文本与占位排版 | `Feat-03-text-and-placeholder-typography-spec.md` |
| Feat-04 | 自适应字号与文本描边着色 | `Feat-04-adaptive-font-and-stroke-shader-spec.md` |
| Feat-05 | 键盘与输入控制 | `Feat-05-keyboard-and-input-control-spec.md` |
| Feat-06 | 选择、光标与菜单 | `Feat-06-selection-caret-and-menu-spec.md` |
| Feat-07 | 事件回调与控制器 | `Feat-07-events-and-controller-spec.md` |

若某个 Feat 在 `specs/index.md` 中仍为占位状态，应以源码、SDK 声明和测试为事实源，补齐 Spec 后再引用行为结论。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Search 创建后文本框不显示 | `SearchModelNG::Create`/`CreateSearchNode` 创建链、`SearchNode` 六槽位子节点 |
| 搜索按钮/分割线不显示 | `SearchLayoutProperty.SearchButton`、`SearchPattern::OnModifyDone` visibility 联动、`UpdateDivider` |
| 搜索图标/取消图标样式不生效 | `CreateSearchIcon`/`CreateCancelIcon` Symbol/Image 分派、`IconOptions`、`*ColorSetByUser` 标志 |
| CancelButtonStyle 行为异常 | `IsEventEnabled`、`UpdateCancelButtonStatus`、CONSTANT/INVISIBLE/INPUT 语义 |
| 排版属性不生效 | 子 `TextFieldLayoutProperty`（大部分存于子节点非 SearchLayoutProperty）、`fontFeature`（唯一存于 Search） |
| 键盘/输入行为异常 | 子 `TextFieldPattern`/`TextFieldLayoutProperty`、`SearchType` 值重映射、`inputFilter` 覆盖 `type` |
| enableHapticFeedback 无效 | `ohos.permission.VIBRATE` 声明、`vibrator_utils.cpp`、`isEnableHapticFeedback_` 标志 |
| stopBackPress 行为不符 | `TextFieldPattern::OnBackPressed` 返回值语义、`IsStopBackPress` |
| onSubmit 不触发 | `SearchEventHub::FireOnSubmit`、`OnClickButtonAndImage`；@since 8 重载在 NG no-op |
| 事件回调不触发 | 大部分事件委托子 `TextFieldEventHub`（仅 `onSubmit` 存于 `SearchEventHub`） |
| Controller 方法无效 | `InitSearchController` Handle* 委托、子 `TextFieldPattern` |

## 调试入口

- 创建链路：从 `SearchModelNG::Create` → `CreateSearchNode` 确认六槽位子节点建立。
- 属性链路：从 SDK 属性名定位 Model 写入，区分 `SearchLayoutProperty`（Search 专有）与子 `TextFieldLayoutProperty`（大部分排版/键盘/选择属性）。
- 布局链路：从 `SearchLayoutAlgorithm::Measure`/`Layout` 确认子节点测量顺序与定位。
- 交互链路：事件问题优先看 `SearchEventHub`（onSubmit/onCopy/onCut/onPaste）和子 `TextFieldEventHub`（其余 15 事件）。
- 组件化链路：bridge/ 子目录的 `arkts_native_search_bridge.cpp`/`search_dynamic_modifier.cpp`/`search_static_modifier.cpp` 是统一入口。
- 回归验证：优先运行 `test/unittest/core/pattern/search/` 和 `test/unittest/capi/modifiers/search_modifier_test*.cpp`。

## 相关主题

- [Text](text.md)
- [TextArea](text-area.md)
- [Marquee](marquee.md)
- [TextInput](text-input.md)（未迁移）
- [RichEditor](rich-editor.md)（未迁移）
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`