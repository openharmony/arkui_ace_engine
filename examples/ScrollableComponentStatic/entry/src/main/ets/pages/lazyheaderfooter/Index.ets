'use static'

import {
  Entry,
  Component,
  Builder,
  Column,
  ColumnOptions,
  Button,
  ButtonType,
  Text,
  FontWeight,
  HorizontalAlign,
  ResourceColor,
} from '@ohos.arkui.component'

@Entry
@Component
struct Index {
  @Builder
  EntryButton(label: string, url: string, color: ResourceColor): void {
    Button({ type: ButtonType.Normal }) {
      Text(label)
        .fontSize(18)
        .fontColor('#ffffffff')
    }
      .width('80%')
      .height(56)
      .backgroundColor(color)
      .onClick(() => {
        this.getUIContext().getRouter().pushUrl({ url: url })
      })
  }

  build(): void {
    Column({ space: 20 } as ColumnOptions) {
      Text('Lazy Header/Footer Samples')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 40, bottom: 20 })

      this.EntryButton('Scroll', 'pages/lazyheaderfooter/ScrollSample', '#4A90E2')
      this.EntryButton('List', 'pages/lazyheaderfooter/ListSample', '#7ED321')
      this.EntryButton('WaterFlow', 'pages/lazyheaderfooter/WaterFlowSample', '#F5A623')
      this.EntryButton('GridDirect (诊断)', 'pages/lazyheaderfooter/GridDirect', '#E0529C')
    }
    .width('100%')
    .height('100%')
    .alignItems(HorizontalAlign.Center)
  }
}
