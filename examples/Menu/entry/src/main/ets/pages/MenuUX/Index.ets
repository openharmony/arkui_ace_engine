import router from '@ohos.router'
@Entry
@Component
struct Index {

  build() {
    Row() {
      Column() {
        Button('【补充demo】预览组件包含search')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/Preview_Search',
            })
          })
        Button('enabled 不设置')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/enabledNull',
            })
          })
        Button('enabled true')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/enabledTrue',
            })
          })
        Button('enabled false')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/enabledFalse',
            })
          })
        Button('enabled 混合使用')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/enabled',
            })
          })
        Button('preview NONE 默认值')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewNONE',
            })
          })
        Button('preview为IMAGE true')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewIMAGE1',
            })
          })
        Button('preview为IMAGE false')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewIMAGE2',
            })
          })
        Button('RightClick IMAGE')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewClickIMAGE',
            })
          })
        Button('CustomBuilder menu菜单')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewCustomBuilder',
            })
          })
        Button('CustomBuilder 按键')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewCustomBuilder2',
            })
          })
        Button('CustomBuilder Text文本')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewCustomBuilder3',
            })
          })
        Button('CustomBuilder Image图片')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewCustomBuilder4',
            })
          })
        Button('preview IMAGE 拖拽')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewIMAGEDrag',
            })
          })
        Button('CustomBuilder 拖拽')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewBurDrag',
            })
          })
        Button('preview IMAGE Text文本选中')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewIMAGESet',
            })
          })
        Button('CustomBuilder Text文本选中')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/previewBurSet',
            })
          })
        Button('button绑定menu')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/MenuUX/btnMenu',
            })
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}