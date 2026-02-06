# ArkUI API Knowledge Base（按范式）

> 更新时间：2026-02-06
> 适用仓库：`../../../interface/sdk-js/api`
> 文档目标：按“类web / lite / ArkTS Dynamic / ArkTS Static”四种口径，整理 API 目录、文档入口、导入方式和示例

## 0. 前置知识与口径

- ArkTS Dynamic 的ArkUI组件：`../../../interface/sdk-js/api/arkui/component`，文件名不含 `static.d.ets`
- ArkTS Static 的ArkUI组件：`../../../interface/sdk-js/api/arkui/component`，文件名含 `static.d.ets`
- arkui 公共：`../../../interface/sdk-js/api/arkui`
- FutureAbility（类web）full：`../../../interface/sdk-js/api/common/full/featureability.d.ts`
- FutureAbility（类web）lite：`../../../interface/sdk-js/api/common/lite/featureability.d.ts`

当前仓快照结论（2026-02-06）：

- `arkui/component` 中非 `static.d.ets` 文件数为 `0`
- `arkui/component` 中 `static.d.ets` 文件数为 `129`
- 因此“ArkTS Dynamic组件目录”在本分支下是空集，ArkTS Dynamic能力主要体现在 `@ohos.*.d.ts` 模块 API

## 1. 类web

### 涉及API目录

- `full` 声明入口：`../../../interface/sdk-js/api/common/full/featureability.d.ts`
- 组件共用目录：`../../../interface/sdk-js/api/arkui/component`
- 模块化替代入口（注解 `@useinstead` 指向）：`ohos.ability.featureAbility.FeatureAbility`

建议把“类web”理解为历史兼容层：

- 核心类是 `FeatureAbility`
- 关键能力是“启动 Ability / 调 Ability / 订阅事件 / 设备消息”
- 文件内存在大量 `@deprecated since 8`

### 文档

`featureability.d.ts`（full）中的主要类型与职责：

- `Result`
- `SubscribeMessageResponse`
- `CallAbilityParam`
- `SubscribeAbilityEventParam`
- `SendMessageOptions`
- `SubscribeMessageOptions`
- `RequestParams`
- `FinishWithResultParams`
- `FeatureAbility`

`FeatureAbility`（full）方法清单：

- `startAbility(request: RequestParams): Promise<Result>`
- `startAbilityForResult(request: RequestParams): Promise<Result>`
- `finishWithResult(param: FinishWithResultParams): Promise<Result>`
- `getDeviceList(flag: number): Promise<Result>`
- `callAbility(param: CallAbilityParam): Promise<string>`
- `continueAbility(): Promise<Result>`
- `subscribeAbilityEvent(param: SubscribeAbilityEventParam, func: Function): Promise<string>`
- `unsubscribeAbilityEvent(param: SubscribeAbilityEventParam): Promise<string>`
- `sendMsg(options: SendMessageOptions): void`
- `subscribeMsg(options: SubscribeMessageOptions): void`
- `unsubscribeMsg(): void`

`RequestParams` 常用字段：

- `bundleName?: string`
- `abilityName?: string`
- `entities?: Array<string>`
- `action?: string`
- `deviceType?: number`
- `data?: object`
- `flag?: number`
- `url?: string`

`CallAbilityParam` 常用字段：

- `bundleName: string`
- `abilityName: string`
- `messageCode: number`
- `abilityType: number`
- `data?: object`
- `syncOption?: number`

解读要点：

- full 文件虽然名字是 `full`，但注解中大量能力标注为 `SystemCapability.ArkUI.ArkUI.Lite`
- full/lite 的差异主要体现在“是否包含 start/call/event 这组能力”，不是 `syscap` 字面不同
- 文档层面应明确其“历史兼容”属性，避免在新代码中继续扩大依赖

### 全局导入的API

类web范式中，常见使用方式是直接使用全局对象 `FeatureAbility`：

- `FeatureAbility.startAbility`
- `FeatureAbility.startAbilityForResult`
- `FeatureAbility.finishWithResult`
- `FeatureAbility.getDeviceList`
- `FeatureAbility.callAbility`
- `FeatureAbility.continueAbility`
- `FeatureAbility.subscribeAbilityEvent`
- `FeatureAbility.unsubscribeAbilityEvent`
- `FeatureAbility.sendMsg`
- `FeatureAbility.subscribeMsg`
- `FeatureAbility.unsubscribeMsg`

建议：

- 若业务在迁移期，保留 `FeatureAbility` 调用面
- 新增能力优先使用替代模块 API（`@useinstead` 指向）

### 举例

示例1：启动目标 Ability。

```ts
FeatureAbility.startAbility({
  bundleName: 'com.example.demo',
  abilityName: 'EntryAbility',
  url: 'pages/Index'
}).then((ret) => {
  console.info(`startAbility code=${ret.code}`)
})
```

示例2：带返回结果启动。

```ts
FeatureAbility.startAbilityForResult({
  bundleName: 'com.example.demo',
  abilityName: 'DetailAbility',
  data: { from: 'home' }
}).then((ret) => {
  console.info(`result code=${ret.code}`)
  console.info(JSON.stringify(ret.data))
})
```

示例3：调用 AA 能力。

```ts
FeatureAbility.callAbility({
  bundleName: 'com.example.service',
  abilityName: 'RemoteServiceAbility',
  messageCode: 1001,
  abilityType: 0,
  data: { op: 'query' }
}).then((json) => {
  console.info(`callAbility result=${json}`)
})
```

示例4：订阅与取消订阅 Ability 事件。

```ts
const eventParam = {
  bundleName: 'com.example.service',
  abilityName: 'RemoteServiceAbility',
  messageCode: 2001,
  abilityType: 0
}

FeatureAbility.subscribeAbilityEvent(eventParam, (event: object) => {
  console.info(`event=${JSON.stringify(event)}`)
})

FeatureAbility.unsubscribeAbilityEvent(eventParam)
```

示例5：跨设备消息收发。

```ts
FeatureAbility.subscribeMsg({
  success: (msg) => {
    console.info(`recv ${msg.message} from ${msg.deviceId}`)
  },
  fail: (data, code) => {
    console.error(`subscribeMsg fail code=${code} data=${data}`)
  }
})

FeatureAbility.sendMsg({
  deviceId: 'device-001',
  bundleName: 'com.example.demo',
  abilityName: 'EntryAbility',
  message: 'ping'
})
```

## 2. 轻量是full的子集

### 涉及API目录

- `lite` 声明入口：`../../../interface/sdk-js/api/common/lite/featureability.d.ts`
- `full` 对照入口：`../../../interface/sdk-js/api/common/full/featureability.d.ts`
- 组件共用目录：`../../../interface/sdk-js/api/arkui/component`

子集关系（按当前声明）：

- lite 仅保留消息相关接口
- full 包含 lite 的消息接口，并额外包含 start/call/event/continue 能力

### 文档

`lite/featureability.d.ts` 类型构成：

- `SubscribeMessageResponse`
- `SendMessageOptions`
- `SubscribeMessageOptions`
- `FeatureAbility`

`FeatureAbility`（lite）方法清单：

- `sendMsg(options: SendMessageOptions): void`
- `subscribeMsg(options: SubscribeMessageOptions): void`
- `unsubscribeMsg(): void`

关键字段口径：

- `SendMessageOptions.deviceId`
- `SendMessageOptions.bundleName`
- `SendMessageOptions.abilityName`
- `SendMessageOptions.message?`
- `SendMessageOptions.success?`
- `SendMessageOptions.fail?`
- `SendMessageOptions.complete?`
- `SubscribeMessageOptions.success?`
- `SubscribeMessageOptions.fail?`

共同注解特征：

- `@syscap SystemCapability.ArkUI.ArkUI.Lite`
- `@since 5 dynamiconly`
- `@deprecated since 8`

和 full 的差异矩阵：

- `startAbility`：full 有，lite 无
- `startAbilityForResult`：full 有，lite 无
- `finishWithResult`：full 有，lite 无
- `getDeviceList`：full 有，lite 无
- `callAbility`：full 有，lite 无
- `continueAbility`：full 有，lite 无
- `subscribeAbilityEvent`：full 有，lite 无
- `unsubscribeAbilityEvent`：full 有，lite 无
- `sendMsg`：full 有，lite 有
- `subscribeMsg`：full 有，lite 有
- `unsubscribeMsg`：full 有，lite 有

### 全局导入的API

轻量子集可用的全局 API：

- `FeatureAbility.sendMsg`
- `FeatureAbility.subscribeMsg`
- `FeatureAbility.unsubscribeMsg`

工程建议：

- 若仅需“设备消息收发”，优先使用 lite 子集口径描述
- 若需要“启动 Ability / 结果回传 / 订阅 AA 事件”，必须转到 full 口径
- 文档里要明确“lite 是 full 子集”，避免功能预期超出

### 举例

示例1：注册消息监听。

```ts
FeatureAbility.subscribeMsg({
  success: (resp) => {
    console.info(`deviceId=${resp.deviceId}`)
    console.info(`bundleName=${resp.bundleName}`)
    console.info(`abilityName=${resp.abilityName}`)
    console.info(`message=${resp.message}`)
  },
  fail: (data, code) => {
    console.error(`subscribe fail code=${code}, data=${data}`)
  }
})
```

示例2：发送轻量消息。

```ts
FeatureAbility.sendMsg({
  deviceId: 'remote-device-id',
  bundleName: 'com.example.target',
  abilityName: 'EntryAbility',
  message: 'hello-lite',
  success: () => {
    console.info('sendMsg success')
  },
  complete: () => {
    console.info('sendMsg complete')
  }
})
```

示例3：退出时取消监听。

```ts
aboutToDisappear() {
  FeatureAbility.unsubscribeMsg()
}
```

## 3. ArkTS Dynamic

### 涉及API目录

- ArkTS Dynamic组件 TypeScript 目录：`../../../interface/sdk-js/api/arkui/component`
- ArkUI 公共目录：`../../../interface/sdk-js/api/arkui`
- 模块 API 目录：`../../../interface/sdk-js/api/@ohos.*.d.ts`

推荐关注的ArkTS Dynamic模块文档：

- 路由：`../../../interface/sdk-js/api/@ohos.router.d.ts`
- 弹窗提示：`../../../interface/sdk-js/api/@ohos.promptAction.d.ts`
- Ability：`../../../interface/sdk-js/api/@ohos.ability.featureAbility.d.ts`
- 上下文：`../../../interface/sdk-js/api/@ohos.app.ability.*.d.ts`

当前快照说明：

- `arkui/component` 下非 `static.d.ets` 文件数为 `0`
- 因此“ArkTS Dynamic组件声明文件”在当前分支为空
- 但ArkTS Dynamic模块 API（`@ohos.*`）是完整存在的

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

## 4. ArkTS Static

### 涉及API目录

- ArkTS Static组件 TypeScript：`../../../interface/sdk-js/api/arkui/component`（文件名含 `static.d.ets`）
- ArkTS Static的ArkUI 公共声明：`../../../interface/sdk-js/api/arkui/*.static.d.ets`
- 代表文件：
- `../../../interface/sdk-js/api/arkui/component/button.static.d.ets`
- `../../../interface/sdk-js/api/arkui/component/common.static.d.ets`
- `../../../interface/sdk-js/api/arkui/component/enums.static.d.ets`
- `../../../interface/sdk-js/api/arkui/component/units.static.d.ets`

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

## 5. 快速对照清单

类web（full）看这里：

- `common/full/featureability.d.ts`
- 关注 `FeatureAbility` 全量方法

lite（full 子集）看这里：

- `common/lite/featureability.d.ts`
- 关注消息三方法：`sendMsg/subscribeMsg/unsubscribeMsg`

ArkTS Dynamic看这里：

- 组件全局调用习惯
- `@ohos.*.d.ts` 模块导入习惯
- `@ohos.router.d.ts`、`@ohos.promptAction.d.ts`

ArkTS Static看这里：

- `arkui/component/*.static.d.ets`
- `common.static.d.ets` / `enums.static.d.ets` / `units.static.d.ets`
- 组件 + Attribute + Options 三段式

## 6. 维护建议

- 每次 SDK 升级后，先核对 `component` 目录是否出现非 `static.d.ets` 文件
- 若ArkTS Dynamic组件文件出现，补充第 3 节“ArkTS Dynamic”的组件声明清单
- 若 `featureability.d.ts` 的 `@deprecated` 状态变化，更新第 1、2 节说明
- 若 `common.static.d.ets` 新增全局函数，更新第 4 节“全局导入的API”
- 在示例中优先使用当前声明中存在的接口名，避免历史接口名混入
