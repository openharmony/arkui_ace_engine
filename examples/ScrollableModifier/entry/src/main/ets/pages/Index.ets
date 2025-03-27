import router from '@ohos.router';

@Entry
@Component
struct Index {

  build() {
    Row() {
      Column() {
        Button('list')
          .onClick(() => {
            router.pushUrl({ url: 'pages/list' })
          })
        Button('Grid_AttributeModifier')
          .onClick(() => {
            router.pushUrl({ url: 'pages/Grid_AttributeModifier' })
          })
        Button('Grid_AttributeUpdater')
          .onClick(() => {
            router.pushUrl({ url: 'pages/Grid_AttributeUpdater' })
          })
        Button('GridTest')
          .onClick(() => {
            router.pushUrl({ url: 'pages/GridTest' })
          })

        Button('WaterFlow_AttributeModifier')
          .onClick(() => {
            router.pushUrl({ url: 'pages/WaterFlow_AttributeModifier' })
          })
        Button('WaterFlow_AttributeUpdater')
          .onClick(() => {
            router.pushUrl({ url: 'pages/WaterFlow_AttributeUpdater' })
          })
        Button('WaterFlowTest')
          .onClick(() => {
            router.pushUrl({ url: 'pages/WaterFlow_Test' })
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}