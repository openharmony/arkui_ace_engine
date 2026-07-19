# 使用UIExtension控件与ArkUI无障碍指南文档示例（静态模式版本）

### 介绍

本示例是[UIExtensionAndAccessibility](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/DocsSample/ArkUISample-Sta/UIExtensionAndAccessibility)项目的ArkTS静态编译模式（Static Mode）改造版本。通过使用[ArkUI指南文档](https://gitcode.com/openharmony/docs/tree/OpenHarmony_feature_sta_20260331/zh-cn/application-dev/ui)中各场景的开发示例，展示在静态编译模式下UIExtension控件与ArkUI无障碍属性的用法，帮助开发者理解静态模式的接口差异与适配方法。该工程中展示的代码详细描述可查如下链接：

1. [跨进程应用能力扩展（UIExtension，仅对系统应用开放）](https://gitcode.com/openharmony/docs/blob/OpenHarmony_feature_sta_20260331/zh-cn/application-dev/ui/arkts-ui-extension-components-sys.md)。
2. [同应用进程嵌入式组件 (EmbeddedComponent)](https://gitcode.com/openharmony/docs/blob/OpenHarmony_feature_sta_20260331/zh-cn/application-dev/ui/arkts-embedded-components.md)。
3. [全屏启动原子化服务组件（FullScreenLaunchComponent）](https://gitcode.com/openharmony/docs/blob/OpenHarmony_feature_sta_20260331/zh-cn/application-dev/ui/arkts-FullScreenComponent.md)。
4. [支持无障碍](https://gitcode.com/openharmony/docs/blob/OpenHarmony_feature_sta_20260331/zh-cn/application-dev/ui/arkts-universal-attributes-accessibility.md)。
5. [通过C-API构建嵌入式组件（EmbeddedComponent）](https://gitcode.com/openharmony/docs/blob/OpenHarmony_feature_sta_20260331/zh-cn/application-dev/ui/ndk-embedded-component.md)。

### 与动态模式版本的主要差异

| 项目 | ArkTS-Dyn | ArkTS-Static |
|------|-----------|--------------|
| 编译模式 | `'use dynamic'` 或无声明 | `'use static'` |
| 导入方式 | `import { xxx } from '@kit.ArkUI'` | `import { xxx } from '@ohos.arkui.component'` |
| 页面导航 | NavPathStack + NavDestination | Button + router.pushUrl |
| Native调用 | NAPI (`napi_module_register`) | ANI (`ANI_Constructor` + `loadLibrary`) |
| 返回类型 | 可省略 | `build()` 等方法需显式标注 `: void` |
| 导出变量 | 可省略类型 | 需显式类型注解 |

### 使用说明

1. 在主界面，通过Button按钮选择需要参考的组件类别。
2. 在组件目录页面选择详细的示例参考。
3. 进入示例界面，查看参考示例。

### 工程目录
```
entry/src/main/
|---cpp/
|   |---ani_init.cpp                        // ANI模式Native初始化（EmbeddedComponent C-API节点创建）
|   |---CMakeLists.txt
|   |---embedded/                           // 旧NAPI模式代码（仅供参考，未参与编译）
|---ets/
|   |---common/
|   |   |---Card.ets                        // 卡片UI组件
|   |   |---Route.ets                       // 路由数据结构定义
|   |   |---resource.ets                    // 资源管理工具类
|   |---entryability/
|   |   |---EntryAbility.ets                // 应用入口Ability
|   |---entrybackupability/
|   |   |---EntryBackupAbility.ets          // 备份ExtensionAbility
|   |---extensionability/
|   |   |---ExampleEmbeddedAbility.ets      // EmbeddedComponent的ExtensionAbility
|   |---uiextensionability/
|   |   |---UIExtensionProvider.ets         // UIExtensionComponent的ExtensionAbility
|   |---pages/
|   |   |---Index.ets                       // 应用主页面（Button导航）
|   |   |---UIExtensionComponent/           // UIExtensionComponent 组件
|   |   |   |---Index.ets
|   |   |   |---UIExtension.ets
|   |   |   |---Extension.ets
|   |   |---EmbeddedComponent/              // EmbeddedComponent 组件
|   |   |   |---Index.ets
|   |   |   |---Embedded.ets
|   |   |   |---Extension.ets
|   |   |---FullScreenLaunchComponent/      // FullScreenLaunchComponent 组件
|   |   |   |---Index.ets
|   |   |   |---FullScreenLaunch.ets
|   |   |---ShowEmbeddedComponent/          // 通过C-API创建EmbeddedComponent（ContentSlot + ANI）
|   |   |   |---ShowPage.ets
|   |   |---UniversalAttributesAccessibility/  // ArkUI 无障碍能力
|   |   |   |---Index.ets
|   |   |   |---AccessibilityText.ets
|   |   |   |---AccessibilityGroup.ets
|   |   |   |---AccessibilityFocusDrawLevel.ets
|   |   |   |---AccessibilityTextCase01.ets
|   |   |   |---AccessibilityTextCase02.ets
|   |   |   |---AccessibilityDescriptionCase01.ets
|   |   |   |---AccessibilityDescriptionCase02.ets
|   |   |   |---AccessibilityGroupCase01.ets
|   |   |   |---AccessibilityGroupCase02.ets
|   |   |   |---AccessibilityLevelCase01.ets
|   |   |   |---VirtualNodeExample.ets
|   |---workers/
```

### 具体实现

1. **UIExtensionComponent**：在静态模式下通过 `import { UIExtensionComponent } from '@ohos.arkui.component'` 引入，使用 `UIExtensionComponent(want)` 创建组件，绑定 `onReceive`、`onTerminated`、`onError` 回调。
2. **EmbeddedComponent**：通过 `import { EmbeddedComponent, EmbeddedType } from '@ohos.arkui.component'` 引入，使用 `EmbeddedComponent(want, EmbeddedType.EMBEDDED_UI_EXTENSION)` 嵌入同应用Extension页面。
3. **FullScreenLaunchComponent**：通过 `import { FullScreenLaunchComponent } from '@ohos.arkui.advanced.FullScreenLaunchComponent'` 引入，全屏启动原子化服务。
4. **ShowEmbeddedComponent（C-API + ContentSlot）**：展示静态模式下通过ANI机制调用Native C-API创建 `ARKUI_NODE_EMBEDDED_COMPONENT` 节点，并通过 `ContentSlot` 渲染到ArkTS页面。Native侧使用 `ANI_Constructor` 注册，ArkTS侧通过 `NativeMethods` 类配合 `loadLibrary("entry")` 调用。
5. **UniversalAttributesAccessibility**：展示无障碍属性（accessibilityText、accessibilityGroup、accessibilityLevel、accessibilityDescription、accessibilityChecked、accessibilitySelected、accessibilityFocusDrawLevel、accessibilityVirtualNode）的静态模式用法。
6. **页面导航**：所有页面使用 `Button` + `router.pushUrl` 导航模式，适配静态编译要求。

### 相关权限

允许系统方舟运行时引擎在受限模式下执行动态下发的方舟字节码。

[ohos.permission.RUN_DYN_CODE](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/security/AccessToken/permissions-for-all.md#ohospermissionrun_dyn_code)

### 依赖

不涉及。

### 约束与限制

1.本示例仅支持标准系统上运行，支持设备：default、tablet。

2.本示例为Stage模型静态编译模式，支持API26版本SDK，版本号：6.0.0.0，镜像版本号：OpenHarmony_6.0.0.0。

3.本示例需要使用DevEco Studio 6.0.0 Release及以上版本才可编译运行。

4.本示例类型为系统应用，需要使用Full SDK，使用Full SDK时需要手动从镜像站点获取，并在DevEco Studio中替换，具体操作可参考[替换指南](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/faqs/full-sdk-switch-guide.md)。

5.本示例涉及相关权限为system_core级别(相关权限级别可通过[权限定义列表](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/security/AccessToken/permissions-for-all.md)查看)，需要手动配置对应级别的权限签名(具体操作可查看[应用包签名工具概述](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/security/hapsigntool-overview.md#%E5%BA%94%E7%94%A8%E5%8C%85%E7%AD%BE%E5%90%8D%E5%B7%A5%E5%85%B7%E6%A6%82%E8%BF%B0))。

6.本示例类型为系统应用，需要手动配置对应级别的应用类型("app-feature": "hos_system_app")。具体可参考profile配置文件[bundle-info对象内部结构](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/security/app-provision-structure.md#bundle-info%E5%AF%B9%E8%B1%A1%E5%86%85%E9%83%A8%E7%BB%93%E6%9E%84)。

### 下载

如需单独下载本工程，执行如下命令：

````
git init
git config core.sparsecheckout true
echo examples/Accessibility_sta/UIExtensionAndAccessibility > .git/info/sparse-checkout
git remote add origin https://gitcode.com/openharmony/ace_engine.git
git pull origin master
````
