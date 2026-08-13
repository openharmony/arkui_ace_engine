# Preview Platform Adaptation Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `PreviewPlatformAdaptation`

## 定位

Preview Platform Adaptation 是 ArkUI 面向 IDE Previewer 的宿主平台适配层。它为预览运行时提供入口容器、视图与输入转换、资源和设备信息、窗口/能力框架替身、Inspector，以及对应的 SDK 打包配置；它不是应用侧独立组件或公共 SDK。

本文档仅保留稳定的源码、构建、测试和 Spec 路由。Previewer 与真机平台的差异、功能可用性和运行参数应以当前实现、构建配置和实际 Previewer 环境为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 平台选择 | `adapter/preview/build/config.gni`、`adapter/preview/build/platform.gni` | 选择 Windows、macOS 或 Linux 的预览构建配置。 |
| 预览公共配置 | `adapter/preview/build/preview_common.gni` | 汇集 Preview 构建开关和入口、外部能力、Inspector、OSAL 四组 source set。 |
| 平台差异配置 | `adapter/preview/build/config_windows.gni`、`adapter/preview/build/config_mac.gni`、`adapter/preview/build/config_linux.gni` | 平台专属编译定义与编译选项。 |
| 入口适配 | `adapter/preview/entrance/BUILD.gn` | `preview_entrance_source` 组织预览容器、视图、输入、资源、子窗口和能力接入。 |
| UIContent 预览实现 | `adapter/preview/entrance/ui_content_impl.h`、`adapter/preview/entrance/ui_content_impl.cpp` | `UIContent` 的 Previewer 实现，承接文档加载、设备配置、视口、输入和 Inspector 操作。 |
| 预览容器与视图 | `adapter/preview/entrance/ace_container.h`、`adapter/preview/entrance/ace_container.cpp`、`adapter/preview/entrance/ace_view_preview.h`、`adapter/preview/entrance/ace_view_preview.cpp` | `AceContainer` 与 `AceViewPreview` 的预览变体；视图接收触摸、鼠标、按键和轴事件。 |
| OSAL 适配 | `adapter/preview/osal/BUILD.gn` | `preview_osal_source` 汇集设备、显示、资源、输入法、任务、图像、系统属性等平台实现。 |
| 外部能力桩 | `adapter/preview/external/BUILD.gn`、`adapter/preview/external/ability/`、`adapter/preview/external/multimodalinput/` | Previewer 使用的 Ability 和多模输入声明及实现替身。 |
| Inspector 与快速预览 | `adapter/preview/inspector/BUILD.gn`、`adapter/preview/inspector/inspector_client.cpp`、`adapter/preview/inspector/js_inspector_manager.cpp` | Inspector 客户端和 JS 树更新入口。 |
| Previewer SDK 打包 | `adapter/preview/sdk/BUILD.gn` | 组织系统资源、ArkTS 字节码、NAPI 模块和预览运行所需共享库的打包。 |
| 本地示例 | `adapter/preview/entrance/samples/BUILD.gn` | `previewer_demo` 及各设备形态的示例可执行目标。 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的目标路径 | 说明 |
|----------|----------|------------|----------------------|------|
| Previewer 窗口 | `adapter/preview/entrance/BUILD.gn`、`adapter/preview/osal/BUILD.gn` | `foundation/window/window_manager` | `previewer:previewer_window` | 预览窗口适配依赖。 |
| RenderService | `adapter/preview/entrance/BUILD.gn`、`adapter/preview/external/BUILD.gn` | `foundation/graphic/graphic_2d` | `librender_service_client` | 启用 Rosen 后端时的渲染服务客户端依赖。 |
| IDE Previewer | `adapter/preview/entrance/samples/BUILD.gn`、`adapter/preview/sdk/sharedlib_config.gni` | `ide/tools/previewer` | `ide_extension`、`ide_util` | Previewer 示例及 SDK 打包引用的 IDE 侧库。 |
| 资源管理 | `adapter/preview/entrance/BUILD.gn`、`adapter/preview/osal/BUILD.gn` | `base/global/resource_management` | `frameworks/resmgr:global_resmgr_win`、`global_resmgr_mac`、`global_resmgr_linux` | 各宿主平台的资源管理实现。 |

### API 入口

Preview Platform Adaptation 没有独立的应用侧 ArkTS、Modifier 或 Native Node API。预览运行时复用引擎的 `UIContent` 内部接口，并由 Previewer 宿主加载应用产物。

| 类型 | 稳定路径 | 说明 |
|------|----------|------|
| 引擎内部接口 | `interfaces/inner_api/ace/ui_content.h` | Preview `UIContentImpl` 实现的内部 UI 内容接口。 |
| 预览实现 | `adapter/preview/entrance/ui_content_impl.h` | Previewer 变体的 `UIContent` 实现入口。 |
| SDK 产物配置 | `adapter/preview/sdk/BUILD.gn` | 将运行所需模块和资源组织到 Previewer SDK 产物。 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 组件测试宿主 | `test/component_test/tools/previewer_host/` | 组件测试使用的 Previewer 宿主工具。 |
| Previewer 示例 | `adapter/preview/entrance/samples/BUILD.gn` | 各设备形态的预览示例可执行目标。 |
| Spec HostPreview 框架 | `specs/spec-test/tools/host_preview/`、`specs/spec-test/docs/HostPreview_Test_Framework_Design.md` | 启动 Previewer、采集 Inspector 并对规格用例断言的工具与设计说明。 |

未发现仅覆盖 `adapter/preview/` 平台适配层的 ace_engine 单元测试目录；对某个能力的验证应继续进入其组件测试或 HostPreview 用例。

### 相关 Spec

预览器平台适配功能域：`specs/02-cross-platform/01-platform-adapter/04-previewer-platform-adapter/`（功能 ID `02-01-04`）。当前已有 `design.md`，registry 标记为 `spec_status: active`；Feature 规格的补录状态应以该功能域的 registry 为准。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 预览构建未选择预期宿主平台 | `adapter/preview/build/config.gni`、`adapter/preview/build/platform.gni` 及相应 `config_*.gni`。 |
| 页面未加载或容器未建立 | `UIContentImpl`、`AceContainer`、`AceViewPreview` 及 `preview_entrance_source`。 |
| 预览输入或视口更新异常 | `AceViewPreview`、`UIContentImpl`、`event_dispatcher.cpp`、`touch_event_convertor.cpp`、`mmi_event_convertor.cpp`。 |
| 资源、设备或系统能力差异 | `adapter/preview/osal/` 与 `adapter/preview/external/` 下相应适配或替身。 |
| Inspector 或快速预览更新异常 | `InspectorClient`、`JSInspectorManager` 和 `UIContentImpl` 的 Inspector 操作入口。 |
| Previewer 产物缺少模块或资源 | `adapter/preview/sdk/BUILD.gn` 的资源、字节码、NAPI 模块和共享库复制目标。 |

## 调试入口

- 先确认 GN 配置所选的宿主平台与 `preview_common.gni` 汇集的 source set。
- 容器或页面问题从 `UIContentImpl` 的初始化和文档加载入口进入，再查看 `AceContainer` 与 `AceViewPreview`。
- 输入问题按事件类型进入 `AceViewPreview` 的处理入口和对应事件转换文件。
- 预览显示或资源问题分别检查 `preview_osal_source`、`preview_external_source` 和 SDK 打包目标。
- Inspector/快速预览问题从 `InspectorClient`、`JSInspectorManager` 与 `UIContentImpl` 的操作入口交叉核对。

## 相关主题

- 窗口机制：`docs/kb/architecture/window-mechanism.md`
- UI 上下文：`docs/kb/capabilities/ui-context.md`
- 布局框架：`docs/kb/architecture/layout-framework.md`
- 预览器平台适配 Spec：`specs/02-cross-platform/01-platform-adapter/04-previewer-platform-adapter/`
