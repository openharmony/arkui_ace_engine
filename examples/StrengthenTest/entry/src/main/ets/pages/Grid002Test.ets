import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Text,
  TextAttribute,
  Column,
  Component,
  ButtonAttribute,
  ClickEvent,
  UserView,
  Grid,
  GridItem,
  ForEach,
  TextAlign,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

/**
 * 验证接口
 * ColumnStart
 * columnEnd
 * rowStart
 * rowEnd
 */
@Component
export struct Grid002Test {

  @State numbers: string[] = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"];

  build() {
    NavDestination() {
      Column(undefined) {
        Column() {
          Grid() {
            GridItem() {
              Text('4')
                .fontSize(16)
                .backgroundColor(0xFAEEE0)
                .width('100%')
                .height('100%')
                .textAlign(TextAlign.Center)
            }.rowStart(1).rowEnd(2).columnStart(1).columnEnd(2) // 同时设置合理的行列号

            ForEach(this.numbers, (item: string) => {
              GridItem() {
                Text(item)
                  .fontSize(16)
                  .backgroundColor(0xF9CF93)
                  .width('100%')
                  .height('100%')
                  .textAlign(TextAlign.Center)
              }
            }, (item: string) => item)

            GridItem() {
              Text('5')
                .fontSize(16)
                .backgroundColor(0xDBD0C0)
                .width('100%')
                .height('100%')
                .textAlign(TextAlign.Center)
            }.columnStart(1).columnEnd(4) // 只设置列号，不会从第1列开始布局
          }
          .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
          .rowsTemplate('1fr 1fr 1fr 1fr 1fr')
          .width('90%').height(300)
        }.width('100%')
      }
    }
    .title('Grid基础功能用例002')
  }
}