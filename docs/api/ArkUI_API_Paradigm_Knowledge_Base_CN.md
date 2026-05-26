# ArkUI API 范式与调用面知识库

> 文档版本：v1.1
> 更新时间：2026-05-25
> 源码版本：OpenHarmony ace_engine (master 分支)
> 适用仓库：`OpenHarmony/interface/sdk-js/api`
> 文档目标：按"类web (full/lite) / ArkTS Dynamic / ArkTS Static"四种范式口径，整理 API 目录、文档入口、导入方式和示例，回答"怎么写 import / 哪些全局可用 / lite vs full 怎么选"。

## 相关知识库

- SDK API ↔ ace_engine 源码实现映射：[docs/sdk/ArkUI_SDK_API_Knowledge_Base.md](../sdk/ArkUI_SDK_API_Knowledge_Base.md)
- 组件 API 范式速查：[docs/sdk/Component_API_Knowledge_Base_CN.md](../sdk/Component_API_Knowledge_Base_CN.md)
- IDL 接口定义：[docs/sdk/IDL_Knowledge_Base_CN.md](../sdk/IDL_Knowledge_Base_CN.md)

## 0. 前置知识与口径

### 0.1 ArkUI 组件 API（DSL，全局可用）

- ArkTS Dynamic 组件：`<openharmony_root>/interface/sdk-js/api/@internal/component/ets/*.d.ts`
- ArkTS Static 组件：`<openharmony_root>/interface/sdk-js/api/arkui/component/*.static.d.ets`
- arkui 公共声明：`<openharmony_root>/interface/sdk-js/api/arkui/`（含 `*Modifier.d.ts` 与 `*Modifier.static.d.ets`）
- 使用方式：组件名全局可写，无需 `import`

### 0.2 ArkUI 模块 API（`@ohos.arkui.*`，按需 import）

ArkUI 暴露的非 DSL 能力（节点、Modifier、Observer、Snapshot、Drag、Inspector、performanceMonitor 等）以模块形式发布在 `@ohos.arkui.*`：

- 动态声明：`<openharmony_root>/interface/sdk-js/api/@ohos.arkui.*.d.ts`（27 个）
- 静态声明：`<openharmony_root>/interface/sdk-js/api/@ohos.arkui.*.{d.ets,static.d.ets}`（含 `advanced/` 高级组件，约 61 个）
- 使用方式：`import xxx from '@ohos.arkui.xxx'`
- 代表模块：`@ohos.arkui.node`、`@ohos.arkui.modifier`、`@ohos.arkui.observer`、`@ohos.arkui.componentSnapshot`、`@ohos.arkui.dragController`、`@ohos.arkui.inspector`、`@ohos.arkui.performanceMonitor`、`@ohos.arkui.drawableDescriptor`

### 0.3 与 ArkUI 强相关的通用 `@ohos.*` 模块 API

部分通用 `@ohos.*` 模块（如 `router`、`promptAction`、`mediaquery`、`animator`、`font`、`measure` 等）在底层由 ArkUI 提供实现，对应用而言依然是按模块 import：

- 动态声明：`<openharmony_root>/interface/sdk-js/api/@ohos.<name>.d.ts`
- 静态声明：`<openharmony_root>/interface/sdk-js/api/@ohos.<name>.static.d.ets`（部分模块提供静态版本）
- 使用方式：`import name from '@ohos.<name>'`
- 实现侧（ace_engine 内部）：详见 [docs/sdk/ArkUI_SDK_API_Knowledge_Base.md](../sdk/ArkUI_SDK_API_Knowledge_Base.md) 的"ArkUI NAPI 模块"章节，本文档不展开

### 0.4 类web 历史范式

`<openharmony_root>/interface/sdk-js/api/common/{full,lite}/featureability.d.ts` — 详见第 1 节。

### 0.5 当前仓快照（2026-05-25）

| 类别 | 路径 | 数量 |
|------|------|------|
| Dynamic 组件 | `@internal/component/ets/*.d.ts` | 140 |
| Static 组件 | `arkui/component/*.static.d.ets` | 129 |
| `@ohos.arkui.*` 动态模块 | `api/@ohos.arkui.*.d.ts` | 27 |
| `@ohos.arkui.*` 静态/高级组件 | `api/@ohos.arkui.*.{d.ets,static.d.ets}` | 61 |

## 1. 类web（FeatureAbility，历史范式，仅作了解）

> 类web 是 OpenHarmony 早期遗留的 API 范式，核心是全局对象 `FeatureAbility`。所有方法均已 `@deprecated since 8`，新业务不应继续使用。本节仅作存档了解，详细字段见源码声明文件。

- 声明文件：
  - full：`<openharmony_root>/interface/sdk-js/api/common/full/featureability.d.ts`
  - lite：`<openharmony_root>/interface/sdk-js/api/common/lite/featureability.d.ts`
- 调用方式：全局 `FeatureAbility.xxx(...)`，无需 import
- 替代方案（`@useinstead` 指向）：`@ohos.ability.featureAbility`、`@ohos.app.ability.*` 等模块化 API

能力分布速览：

| 能力组 | 方法 | full | lite |
|--------|------|:----:|:----:|
| 设备消息 | `sendMsg` / `subscribeMsg` / `unsubscribeMsg` | ✅ | ✅ |
| 启动 Ability | `startAbility` / `startAbilityForResult` / `finishWithResult` | ✅ | ❌ |
| 调用 Ability | `callAbility` / `continueAbility` | ✅ | ❌ |
| 事件订阅 | `subscribeAbilityEvent` / `unsubscribeAbilityEvent` | ✅ | ❌ |
| 设备列表 | `getDeviceList` | ✅ | ❌ |

要点：

- **lite 是 full 的子集**：只保留设备消息三方法
- 两者均标注 `@syscap SystemCapability.ArkUI.ArkUI.Lite`、`@since 5 dynamiconly`、`@deprecated since 8`
- 新代码使用 `@ohos.*` 模块 API 与现代组件 DSL，不要再扩大 `FeatureAbility` 依赖

## 2. ArkTS Dynamic

### 涉及API目录

- ArkTS Dynamic组件 TypeScript 目录：`<openharmony_root>/interface/sdk-js/api/@internal/component/ets`（`*.d.ts`）
- ArkUI 公共目录：`<openharmony_root>/interface/sdk-js/api/arkui`
- 模块 API 目录：`<openharmony_root>/interface/sdk-js/api/@ohos.*.d.ts`

推荐关注的ArkTS Dynamic模块文档：

- 路由：`<openharmony_root>/interface/sdk-js/api/@ohos.router.d.ts`
- 弹窗提示：`<openharmony_root>/interface/sdk-js/api/@ohos.promptAction.d.ts`
- Ability：`<openharmony_root>/interface/sdk-js/api/@ohos.ability.featureAbility.d.ts`
- 上下文：`<openharmony_root>/interface/sdk-js/api/@ohos.app.ability.*.d.ts`

当前快照说明：

- `@internal/component/ets` 下 `*.d.ts` 文件数为 `140`（ArkTS Dynamic 组件声明文件）
- ArkTS Dynamic 模块 API（`@ohos.*`）配套完整

### 文档

ArkTS Dynamic需要区分两类调用面：

- 组件构建：`Text/Button/Column/...` 这类 DSL 组件
- 系统 API：通过 `import xxx from '@ohos.xxx'` 模块导入

`@ohos.router.d.ts` 可见结构：

- `declare namespace router`
- 末尾 `export default router`
- 常见方法包括 `pushUrl`、`replaceUrl`、`back`

`@ohos.promptAction.d.ts` 可见结构：

- `declare namespace promptAction`
- 含 `ShowToastOptions` 等配置类型
- ArkTS Dynamic场景里常用于轻提示

ArkTS Dynamic文档编写要点：

- 组件调用写法按“全局组件函数”描述
- 模块能力按“模块默认导出对象”描述
- 对同名能力要区分“组件 API”和“系统模块 API”

### 组件是全局导入的API API是按模块导入的

组件（全局使用，不写 import）示例：

- `Text`
- `Button`
- `Column`
- `Row`
- `List`
- `Image`
- `Web`
- `Navigation`

系统 API（按模块 import）示例：

- `router` from `@ohos.router`
- `promptAction` from `@ohos.promptAction`
- `mediaquery` from `@ohos.mediaquery`
- `hilog` from `@ohos.hilog`
- `intl` from `@ohos.intl`

导入规则总结：

- 组件：默认全局可用
- API：必须按模块名导入
- 模块签名以 `@ohos.*.d.ts` 为准

常见误区：

- 误区1：把 `router` 当全局对象直接使用
- 误区2：给 `Text`、`Button` 写模块导入
- 误区3：把ArkTS Static声明文件路径当成ArkTS Dynamic模块导入路径

### 举例

示例1：组件 + 路由 + toast。

```ts
import router from '@ohos.router'
import promptAction from '@ohos.promptAction'

@Entry
@Component
struct Index {
  build() {
    Column() {
      Text('Dynamic JS Pattern')
      Button('Go Detail').onClick(() => {
        router.pushUrl({ url: 'pages/Detail' })
        promptAction.showToast({ message: 'navigating...' })
      })
    }
  }
}
```

示例2：`pushUrl` Promise 风格。

```ts
import router from '@ohos.router'

router.pushUrl({ url: 'pages/Profile' })
  .then(() => {
    console.info('pushUrl success')
  })
  .catch((err: Error) => {
    console.error(`pushUrl failed: ${JSON.stringify(err)}`)
  })
```

示例3：`replaceUrl` 与 `back`。

```ts
import router from '@ohos.router'

function goHome() {
  router.replaceUrl({ url: 'pages/Home' })
}

function goBack() {
  router.back()
}
```

示例4：仅组件 DSL（不导入组件）。

```ts
@Entry
@Component
struct PlainComponentPage {
  build() {
    Column() {
      Text('Components are global')
      Button('OK')
      Row() {
        Text('Left')
        Text('Right')
      }
    }
  }
}
```

示例5：模块 API 统一收口写法。

```ts
import router from '@ohos.router'
import promptAction from '@ohos.promptAction'

export function openPage(url: string) {
  router.pushUrl({ url }).then(() => {
    promptAction.showToast({ message: `opened ${url}` })
  })
}
```

## 3. ArkTS Static

### 涉及API目录

- ArkTS Static组件 TypeScript：`<openharmony_root>/interface/sdk-js/api/arkui/component`（文件名含 `static.d.ets`）
- ArkTS Static的ArkUI 公共声明：`<openharmony_root>/interface/sdk-js/api/arkui/*.static.d.ets`
- 代表文件：
- `<openharmony_root>/interface/sdk-js/api/arkui/component/button.static.d.ets`
- `<openharmony_root>/interface/sdk-js/api/arkui/component/common.static.d.ets`
- `<openharmony_root>/interface/sdk-js/api/arkui/component/enums.static.d.ets`
- `<openharmony_root>/interface/sdk-js/api/arkui/component/units.static.d.ets`

ArkTS Static目录快照（2026-02-06）：

- `*.static.d.ets` 数量：`129`
- 文件头常见标记：`"use static"` 或 `'use static'`

### 文档

ArkTS Static声明的主结构：

- 组件函数：`export declare function ComponentName(...)`
- Attribute：`ComponentNameAttribute extends CommonMethod`
- Options：`ComponentNameOptions`
- 事件/回调：`OnXxx`、`XxxEvent`、`XxxCallback`
- 枚举：`XxxMode`、`XxxType`、`XxxAlign`

`button.static.d.ets` 可见的关键声明：

- `ButtonConfiguration`
- `ButtonOptions`
- `ButtonLabelStyle`
- `ButtonAttribute`
- `Button(...)`（重载）

`common.static.d.ets` 提供全局基座：

- `CommonMethod`
- `AttributeModifier<T>`
- `ContentModifier<T>`
- `CommonConfiguration<T>`
- `UICommonEvent`
- `UIGestureEvent`
- `UIScrollableCommonEvent`
- `ScrollableCommonMethod`

`common.static.d.ets` 可见全局函数：

- `postCardAction(component: Object, action: Object): void`
- `$r(value: string, ...params): Resource`
- `$rawfile(value: string): Resource`
- `animateToImmediately(value: AnimateParam, processor: VoidCallback): void`
- `makeBindable<T>(value: T, onChange: Callback<T>): Bindable<T>`
- `$$<T>(value: T): Bindable<T>`
- `applyStyles<T extends CommonMethod>(this: T, customStyles: CustomStyles): T`

ArkTS Static组件样例分组（按文件名）：

- 布局：`row`、`column`、`stack`、`flex`、`relativeContainer`、`grid`
- 列表滚动：`list`、`listItem`、`listItemGroup`、`scroll`、`waterFlow`
- 文本输入：`text`、`span`、`textInput`、`textArea`、`search`
- 选择器：`datePicker`、`timePicker`、`textPicker`、`calendarPicker`
- 媒体：`image`、`video`、`canvas`、`web`
- 导航：`navigation`、`navDestination`、`tabs`、`tabContent`
- 图形：`line`、`rect`、`circle`、`ellipse`、`path`、`shape`

ArkTS Static范式写文档时建议表达：

- 组件是全局可用入口
- 类型定义以 `Component + Attribute + Options` 三段式为主
- 通用能力优先引用 `common/enums/units`
- 文件中 `@syscap` 和 `@since` 是能力边界依据

### 全局导入的API

ArkTS Static范式常见全局组件 API：

- `Text`
- `Button`
- `Column`
- `Row`
- `Stack`
- `List`
- `ListItem`
- `Grid`
- `Image`
- `Video`
- `Canvas`
- `Web`
- `Navigation`
- `NavDestination`
- `Tabs`
- `TabContent`
- `TextInput`
- `TextArea`
- `Search`
- `DatePicker`
- `TimePicker`
- `TextPicker`
- `Slider`
- `Toggle`
- `Progress`
- `LoadingProgress`

ArkTS Static范式常见全局函数 API：

- `$r`
- `$rawfile`
- `postCardAction`
- `animateToImmediately`
- `makeBindable`
- `$$`
- `applyStyles`

ArkTS Static范式常见全局命名空间 API：

- `focusControl`
- `cursorControl`
- `GestureControl`

### 举例

示例1：最小ArkTS Static页面。

```ts
@Entry
@Component
struct StaticDemo {
  build() {
    Column() {
      Text($r('app.string.app_name'))
      Button('Click Me')
    }
  }
}
```

示例2：按钮 + 属性链。

```ts
@Entry
@Component
struct ButtonPage {
  build() {
    Column() {
      Button('Submit')
        .width(160)
        .height(44)
        .fontSize(18)
        .onClick(() => {
          console.info('submit clicked')
        })
    }
  }
}
```

示例3：资源文件与资源字符串。

```ts
@Entry
@Component
struct ResourcePage {
  build() {
    Column() {
      Text($r('app.string.app_name'))
      Image($rawfile('images/logo.png'))
    }
  }
}
```

示例4：立即动画。

```ts
@Entry
@Component
struct AnimatePage {
  @State value: number = 0

  build() {
    Column() {
      Text(`value=${this.value}`)
      Button('Animate').onClick(() => {
        animateToImmediately({ duration: 300 }, () => {
          this.value = this.value + 1
        })
      })
    }
  }
}
```

示例5：列表页面。

```ts
@Entry
@Component
struct ListPage {
  private data: Array<string> = ['A', 'B', 'C']

  build() {
    List() {
      ForEach(this.data, (item: string) => {
        ListItem() {
          Text(item)
        }
      })
    }
  }
}
```

示例6：导航骨架。

```ts
@Entry
@Component
struct NavPage {
  build() {
    Navigation() {
      Text('Content')
    }
  }
}
```

示例7：Web 组件占位示例。

```ts
@Entry
@Component
struct WebPage {
  build() {
    Column() {
      Web({ src: 'https://example.com' })
    }
  }
}
```

## 4. 快速对照清单

类web（FeatureAbility，已 deprecated，仅作了解）：

- `common/full/featureability.d.ts` / `common/lite/featureability.d.ts`
- lite 是 full 子集（仅消息三方法 `sendMsg/subscribeMsg/unsubscribeMsg`）

ArkTS Dynamic看这里：

- `@internal/component/ets/*.d.ts`（组件声明，140 个）
- 组件全局调用习惯
- `@ohos.*.d.ts` 模块导入习惯
- `@ohos.router.d.ts`、`@ohos.promptAction.d.ts`

ArkTS Static看这里：

- `arkui/component/*.static.d.ets`
- `common.static.d.ets` / `enums.static.d.ets` / `units.static.d.ets`
- 组件 + Attribute + Options 三段式

## 5. 维护建议

- 每次 SDK 升级后，分别核对 `@internal/component/ets/*.d.ts`（Dynamic）与 `arkui/component/*.static.d.ets`（Static）的组件数量变化
- 若 Dynamic 与 Static 组件清单出现增减或重命名，同步更新第 2、3 节的组件声明清单
- 若 `featureability.d.ts` 的 `@deprecated` 状态变化，更新第 1 节能力分布表
- 若 `common.static.d.ets` 新增全局函数，更新第 3 节"全局导入的API"
- 在示例中优先使用当前声明中存在的接口名，避免历史接口名混入
