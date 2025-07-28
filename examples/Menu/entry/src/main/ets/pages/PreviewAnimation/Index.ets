import router from '@ohos.router';
@Entry
@Component
struct Index {

  build() {
    Row() {
      Column() {
        Text('').fontSize(28).fontWeight(FontWeight.Bold)
        Button('InterfaceTest_001')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_001',
            })
          })
        Button('InterfaceTest_002')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_002',
            })
          })
        Button('InterfaceTest_003')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_003',
            })
          })
        Button('InterfaceTest_004')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_004',
            })
          })

        Button('ScenariosTest_001')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_001',
            })
          })
        Button('ScenariosTest_002')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_002',
            })
          })
        Button('ScenariosTest_003')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_003',
            })
          })
        Button('ScenariosTest_004')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_004',
            })
          })
        Button('ScenariosTest_005')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_005',
            })
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}