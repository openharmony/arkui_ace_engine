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
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  Grid,
  GridItem,
  GridLayoutOptions,
  EdgeEffect,
  BarState,
  GridItemAttribute,
  Color,
  GridItemStyle,
  GridDirection,
  GridAttribute,
  ScrollState,
  Row,
  ForEach,
  Scroller,
  TextAlign,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

/**
 * 验证接口
 * scrollBar
 * columnsTemplate
 * columnsGap
 * GridItemStyle，GridItemOptions
 * enableScrollInteraction
 * onReachStart
 * onReachEnd
 * onScrollIndex
 */
@Component
export struct Grid001Test {
  @State colorNumber1: number = 0xF9CF93;
  @State colorNumber2: number = 0xF9CF93;
  @State colorNumber3: number = 0xF9CF93;
  @State barState: BarState = BarState.On;
  @State columnsTem: string = '1fr';
  @State gridItemStyle: GridItemStyle = GridItemStyle.NONE;
  @State enableScrollInteraction: boolean = true;
  scroller: Scroller = new Scroller()
  @State numbers: Array<string> = ['0', '1', '2', '3', '4', '5', '6','7', '8', '9', '10', '11', '12', '13', '14', '15'];

  build() {
    NavDestination() {
      Column(undefined) {
        Column(undefined) {
          Row(undefined) {
            Text('scrollBar')
              .fontSize(16)
          }

          Row(undefined) {
            Button('BarState.ON')
              .onClick((e: ClickEvent) => {
                this.barState = BarState.On;
              })
            Button('BarState.OFF')
              .onClick((e: ClickEvent) => {
                this.barState = BarState.Off;
              })
            Button('BarState.AUTO')
              .onClick((e: ClickEvent) => {
                this.barState = BarState.Auto;
              })
          }

          Row(undefined) {
            Text('columnsTemplate')
              .fontSize(16)
          }

          Row(undefined) {
            Button('1fr')
              .onClick((e: ClickEvent) => {
                this.columnsTem = '1fr';
              })
            Button('1fr 1fr')
              .onClick((e: ClickEvent) => {
                this.columnsTem = '1fr 1fr';
              })
            Button('1fr 1fr 2fr')
              .onClick((e: ClickEvent) => {
                this.columnsTem = '1fr 1fr 2fr';
              })
          }

          Row(undefined) {
            Text('GridItemStyle')
              .fontSize(16)
          }

          Row(undefined) {
            Button('PLAIN')
              .onClick((e: ClickEvent) => {
                this.gridItemStyle = GridItemStyle.PLAIN;
              })
            Button('NONE')
              .onClick((e: ClickEvent) => {
                this.gridItemStyle = GridItemStyle.NONE;
              })
          }

          Row(undefined) {
            Text('enableScrollInteraction')
              .fontSize(16)
          }

          Row(undefined) {
            Button('true')
              .onClick((e: ClickEvent) => {
                this.enableScrollInteraction = true;
              })
            Button('false')
              .onClick((e: ClickEvent) => {
                this.enableScrollInteraction = false;
              })
          }

          Grid(this.scroller) {
            ForEach(this.numbers, (day: string) => {
              GridItem({ style: this.gridItemStyle }) {
                Text(day)
                  .fontSize(16)
                  .backgroundColor(Color.Red)
                  .width('100%')
                  .height(40)
                  .textAlign(TextAlign.Center)
              }
            })
          }
          .columnsTemplate(this.columnsTem)
          .columnsGap(5)
          .rowsGap(5)
          .height(300)
          .width(300)
          .backgroundColor(0xF9CF93)
          .scrollBar(this.barState)
          .enableScrollInteraction(this.enableScrollInteraction)
          .clip(true)
          .onReachStart(() => {
            hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onReachStart');
          })
          .onReachEnd(() => {
            hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onReachEnd');
          })
          .onScrollIndex((first: number, last: number) => {
            hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onScrollIndex');
            hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onScrollIndex first:' + first);
            hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onScrollIndex last:' + last);
          })
        }
      }
    }
    .title('Grid基础功能用例001')
  }
}