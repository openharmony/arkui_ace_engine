# FolderStack Context

> 文档版本：v1.0
> 更新时间：2026-07-18
> 来源：`docs/context_registry.json` 主题 `FolderStack`

## 定位

FolderStack 是面向折叠设备悬停场景的布局容器。它复用 Stack 的基础布局能力，并通过内部 Group、上半区和控制区节点处理子项分区、折痕区域、折叠与悬停事件、过渡动画及窗口方向联动。

FolderStack 已完成组件化改造，运行时通过独立 SO `libarkui_folderstack.z.so` 提供统一 Bridge 和 Dynamic/Static modifier。本文档仅提供稳定路由；具体行为、默认值、设备适用条件和版本兼容性以当前 SDK、源码、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、折叠监听、动画和方向联动 | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_pattern.cpp`、`frameworks/core/components_ng/pattern/folder_stack/folder_stack_pattern.h` | `FolderStackPattern` 核心行为入口 |
| 布局与折痕区域处理 | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.cpp`、`frameworks/core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h` | 普通 Stack / 悬停分区布局和状态事件入口 |
| 布局属性 | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_layout_property.h` | FolderStack 属性以及 Stack 布局属性继承入口 |
| Dynamic Model | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_model_ng.cpp`、`frameworks/core/components_ng/pattern/folder_stack/folder_stack_model_ng.h` | Dynamic 创建、内部节点组织和属性 / 事件写入 |
| Static Model | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_model_ng_static.cpp`、`frameworks/core/components_ng/pattern/folder_stack/folder_stack_model_ng_static.h` | Static FrameNode 创建和属性 / 事件写入 |
| 容器 Group 节点 | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_group_node.cpp`、`frameworks/core/components_ng/pattern/folder_stack/folder_stack_group_node.h` | 应用子项和内部 Stack 节点的组织入口 |
| 上半区内部节点 | `frameworks/core/components_ng/pattern/folder_stack/hover_stack_node.cpp`、`frameworks/core/components_ng/pattern/folder_stack/hover_stack_node.h`、`frameworks/core/components_ng/pattern/folder_stack/hover_stack_pattern.h` | 悬停上半区节点入口 |
| 控制区内部节点 | `frameworks/core/components_ng/pattern/folder_stack/control_parts_stack_node.cpp`、`frameworks/core/components_ng/pattern/folder_stack/control_parts_stack_node.h`、`frameworks/core/components_ng/pattern/folder_stack/control_parts_stack_pattern.h` | 非 upperItems 子项承载入口 |
| 事件存储和 payload | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_event_hub.h`、`frameworks/core/components_ng/pattern/folder_stack/folder_stack_event_info.h` | 折叠与悬停事件入口 |
| 多线程生命周期适配 | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_multithread_pattern.cpp` | 多线程树生命周期注册与注销入口 |
| 组件化 Bridge | `frameworks/core/components_ng/pattern/folder_stack/bridge/` | 统一 Bridge、Dynamic/Static modifier 和 Dynamic Module |
| node modifier 委托 | `frameworks/core/interfaces/native/node/node_folder_stack_modifier.cpp`、`frameworks/core/interfaces/native/node/node_folder_stack_modifier.h` | 通过 DynamicModuleHelper 取得组件动态 modifier |
| 动态模块加载映射 | `adapter/ohos/osal/dynamic_module_helper.cpp` | FolderStack 到 `folderstack` 动态库名的映射 |
| 组件构建入口 | `frameworks/core/components_ng/pattern/folder_stack/BUILD.gn` | FolderStack 组件化源码和 Ark 源集 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/folder_stack.d.ts` | `FolderStackInterface`、options、属性和事件 payload |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/folderStack.static.d.ets` | Static FolderStack 组件、属性和 Builder 声明 |
| Modifier API (Dynamic) | 未提供 | 当前 SDK 中没有 `FolderStackModifier.d.ts`；不要据 Static 声明推断 Dynamic Modifier SDK |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/FolderStackModifier.static.d.ets` | Static `FolderStackModifier` 声明 |
| Native C API / NDK | 未提供独立公开节点类型 | `interfaces/native/native_node.h` 中没有 `ARKUI_NODE_FOLDER_STACK`；内部 node modifier 不等同于公开 C API |

API 检索建议：

- 构造参数：搜索 `FolderStackOptions` 和 `upperItems`。
- 属性与事件：搜索 `FolderStackAttribute`、`onFolderStateChange`、`onHoverStatusChange`、`enableAnimation`、`autoHalfFold`。
- 事件 payload：搜索 `OnFoldStatusChangeInfo`、`HoverEventParam` 和 `WindowStatusType`。
- Static Modifier：以 `FolderStackModifier.static.d.ets` 为准；Dynamic SDK 不存在同名 Modifier 文件。

### API 解析实现路径

FolderStack **已完成组件化改造**：旧 JSView 和旧 nativeModule Bridge 文件不存在，统一 Bridge 位于 `pattern/folder_stack/bridge/`，node modifier 通过 DynamicModuleHelper 加载独立组件模块。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 JS/TS 定义 | `frameworks/bridge/declarative_frontend/ark_component/components/arkfolderstack.js`、`ark_component/src/ArkFolderStack.ts` | 前端组件类、属性和事件 modifier 入口 |
| 统一 Bridge（声明式 + 动态属性） | `frameworks/core/components_ng/pattern/folder_stack/bridge/arkts_native_folder_stack_bridge.cpp` | 通过 `IsJsView()` 区分调用模式，统一处理构造、属性和事件 |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/folder_stack/bridge/folder_stack_dynamic_modifier.cpp` | Dynamic 属性、事件和创建委托入口 |
| Static Modifier | `frameworks/core/components_ng/pattern/folder_stack/bridge/folder_stack_static_modifier.cpp` | Static 构造、属性转换和事件回调包装入口 |
| Dynamic Module | `frameworks/core/components_ng/pattern/folder_stack/bridge/folder_stack_dynamic_module.cpp`、`frameworks/core/components_ng/pattern/folder_stack/bridge/folder_stack_dynamic_module.h` | `FolderStackDynamicModule` 及动态 / 静态 / CJ modifier 导出入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_folder_stack_modifier.cpp` | 通过 DynamicModuleHelper 加载模块并缓存 modifier |

独立 SO：`libarkui_folderstack.z.so`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准；只列出由当前源码调用和构建依赖确认的入口。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 窗口模式与方向请求 | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_pattern.cpp`、`frameworks/core/pipeline/container_window_manager.h`、`adapter/ohos/entrance/ace_container.cpp`、`adapter/ohos/entrance/ace_container.h` | `<OH_ROOT>/foundation/window/window_manager` | `window.h`、`wm_common.h`；`window_manager:libwm` | 读取窗口模式并向当前窗口提交方向请求 |
| 折叠状态、旋转与折痕区域 | `frameworks/core/common/display_info.h`、`adapter/ohos/osal/display_info_utils.cpp`、`adapter/ohos/entrance/ui_content_impl.cpp` | `<OH_ROOT>/foundation/window/window_manager` | `display_manager.h`、`display_info.h`；`window_manager:libdm` | 获取折叠状态、显示旋转、折痕区域并注册折叠状态监听 |
| 折叠产品类型参数 | `frameworks/base/utils/system_properties.h`、`adapter/ohos/osal/system_properties.cpp` | `<OH_ROOT>/base/startup/init` | `parameter.h`、`parameters.h`；`init:libbegetutil` | 读取产品折叠形态参数，供组件适用条件判断 |
| HiSysEvent 状态上报 | `frameworks/core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.cpp`、`frameworks/base/log/event_report.h`、`adapter/ohos/osal/event_report.cpp` | `<OH_ROOT>/base/hiviewdfx/hisysevent` | `hisysevent.h`；`hisysevent:libhisysevent` | 悬停状态变化经 EventReport 写入 HiSysEvent |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Pattern / Layout 单元测试 | `test/unittest/core/pattern/folder_stack/` | 分区布局、折痕、事件、动画、窗口方向和多线程生命周期回归 |
| Static modifier 测试 | `test/unittest/capi/modifiers/folder_stack_modifier_test.cpp` | 生成式 Static modifier、事件包装和属性转换回归 |
| 构建入口 | `test/unittest/core/pattern/folder_stack/BUILD.gn` | FolderStack 定向测试目标及源码清单 |

### 相关 Spec

FolderStack 功能域：`specs/05-ui-components/01-layout-components/12-folder-stack/`

| Feat | 主题 | 文件 | 状态 |
|------|------|------|------|
| Feat-01 | FolderStack 创建、分区与折痕避让 | `Feat-01-folder-stack-partition-crease-avoidance-spec.md` | Baselined |
| Feat-02 | FolderStack 折叠与悬停状态事件 | `Feat-02-folder-stack-fold-hover-events-spec.md` | Baselined |
| Feat-03 | FolderStack 过渡动画、自动旋转与接口兼容 | `Feat-03-folder-stack-animation-auto-rotation-spec.md` | Baselined |

设计入口：`specs/05-ui-components/01-layout-components/12-folder-stack/design.md`。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `upperItems` 子项分区不符合预期 | Dynamic/Static SDK、两个 Model、`FolderStackGroupNode`、Feat-01 |
| 设备半折后未进入预期布局 | `FolderStackPattern`、布局算法、DisplayInfo 适配、窗口模式、Feat-01 |
| 折痕区域或上下分区尺寸异常 | `FolderStackLayoutAlgorithm`、`DisplayInfoUtils`、Pattern / Layout 测试、Feat-01 |
| 折叠或悬停回调未触发 / payload 异常 | EventInfo、EventHub、统一 Bridge、Static modifier、Feat-02 |
| 过渡动画异常 | `FolderStackPattern`、`FolderStackLayoutProperty`、Feat-03 |
| `autoHalfFold` 方向联动或恢复异常 | `FolderStackPattern`、`ContainerWindowManager`、AceContainer 窗口适配、Feat-03 |
| 组件动态模块加载失败 | DynamicModuleHelper 映射、`folder_stack_dynamic_module.*`、node modifier、组件 BUILD |
| 查找 Dynamic FolderStackModifier SDK | 当前无该文件；核对 Dynamic 组件声明和 Static Modifier 声明，避免推断不存在的接口 |

## 调试入口

- 创建链路：从前端 FolderStack 定义进入统一 Bridge，再检查 Dynamic/Static Model 和内部 Group 节点。
- 布局链路：先确认窗口模式、FoldStatus、Rotation 和折痕区域，再检查布局算法选择的普通 Stack 或分区入口。
- 事件链路：从 Pipeline 折叠监听进入 Pattern，随后检查 EventInfo、EventHub 和 Bridge 回调包装。
- 方向链路：从 Pattern 的窗口方向操作定位 `ContainerWindowManager` 和 AceContainer 平台适配。
- 组件化链路：从 `node_folder_stack_modifier.cpp` 跟踪 DynamicModuleHelper、`FolderStackDynamicModule` 和独立 SO。
- 回归验证：优先运行 `test/unittest/core/pattern/folder_stack/` 和 FolderStack modifier 定向测试。

## 相关主题

- Stack：`docs/kb/components/container/stack.md`
- Layout Framework：`docs/kb/architecture/layout-framework.md`
- Layout Attributes：`docs/kb/capabilities/layout-attributes.md`
- Safe Area：`docs/kb/capabilities/safe-area.md`
