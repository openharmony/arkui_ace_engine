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
  ComputedBarAttribute,
  GridAttribute,
  ScrollState,
  OnScrollFrameBeginHandlerResult,
  OnScrollFrameBeginCallback,
  Entry
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import router from '@ohos.router'

@Entry
@Component
struct GridExample {
  irregularIndexes: Array<number> = new Array<number>()
  layoutOptions2: GridLayoutOptions = {
    regularSize: [1, 1],
    irregularIndexes: this.irregularIndexes,

  } as GridLayoutOptions
  @State colorNumber1: number = 0xF9CF93;
  @State colorNumber2: number = 0xF9CF93;
  @State colorNumber3: number = 0xF9CF93;
  @State text: string = 'drag'
  arrGridItem: Array<string> = new Array<string>('0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11');

  changeIndex(index1: number, index2: number) { //交换数组位置
    let temp: string;
    temp = this.arrGridItem[index1];
    this.arrGridItem[index1] = this.arrGridItem[index2];
    this.arrGridItem[index2] = temp;
  }

  build() {
    Column(undefined) {
      Column(undefined) {
        Grid() {
          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('1')
              .fontSize(16)
              .focusable(true)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(100)
          .selectable(true)
          .selected(true)
          .backgroundColor(this.colorNumber1)
          .onSelect((parameter: boolean) =>{
            hilog.info(0x0000, 'testTag',  'Grid onSelect1: ' + parameter);
            if (parameter) {
              this.colorNumber1 = 0x6B8E23
            }else{
              this.colorNumber1 = 0x6A5ACD
            }
          })

          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('2')
              .fontSize(16)
              .focusable(true)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(this.colorNumber2)
          .selectable(true)
          .selected(false)
          .width('100%')
          .height(100)
          .onSelect((parameter: boolean) =>{
            hilog.info(0x0000, 'testTag',  'Grid onSelect2: ' + parameter);
            if (parameter) {
              this.colorNumber2 = 0x00FFFF
            }else{
              this.colorNumber2 = 0x00FF7F
            }
          })

          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('3')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(100)
          .backgroundColor(this.colorNumber3)
          .selectable(false)
          .selected(true)
          .onSelect((parameter: boolean) =>{
            hilog.info(0x0000, 'testTag',  'Grid onSelect3: ' + parameter);
            if (parameter) {
              this.colorNumber3 = 0x6A5ACD
            }else{
              this.colorNumber3 = 0x00FF7F
            }
          })

          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('4')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(100)
          .backgroundColor(Color.Red)

          GridItem({ style: GridItemStyle.NONE }) {
            Text('5')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Green)
          .width('100%')
          .height(100)

          GridItem(undefined) {
            Text('6')
              .fontSize(16)
          }
          .backgroundColor(0xF9CF93)
          .width('100%')
          .height(100)
          .border({width:1})

          GridItem(undefined) {
            Text('7')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Brown)
          .width('100%')
          .height(100)

          GridItem(undefined) {
            Text('8')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(100)
          .backgroundColor(0x6A5ACD)

          GridItem(undefined) {
            Text('9')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(0xF9CF93)
          .width('100%')
          .height('100%')
          .border({width:1})
        }
        .columnsTemplate('1fr 1fr 1fr')
        .columnsGap('10')
        .padding('4vp')
        .editMode(true)
        // .rowsTemplate('1fr 1fr 1fr')
        .clip(true) 
        .rowsGap(20)
        .height(300)
        .width('90%')
        .backgroundColor(Color.Gray)
        .multiSelectable(true)
        .scrollBar(BarState.On)
        .enableScrollInteraction(true)
        .onScrollStart(() => {
          hilog.info(0x0000, 'testTag','Grid onScrollStart');
        })
        .onScrollStop(() => {
          hilog.info(0x0000, 'testTag','Grid onScrollStop');
        })
        .onReachStart(() => {
          hilog.info(0x0000, 'testTag','Grid onReachStart');
        })
        .onReachEnd(() => {
          hilog.info(0x0000, 'testTag','Grid onReachEnd');
        })
        .onScrollIndex((first: number, last: number) => {
          hilog.info(0x0000, 'testTag','Grid onScrollIndex');
          hilog.info(0x0000, 'testTag','Grid onScrollIndex first:' + first);
          hilog.info(0x0000, 'testTag','Grid onScrollIndex last:' + last);
        })
        .onScrollFrameBegin((offset: number, state: ScrollState) => {
          hilog.info(0x0000, 'testTag', 'Grid onScrollFrameBegin state:' + state);
          hilog.info(0x0000, 'testTag', 'Grid onScrollFrameBegin offset:' + offset);
          return { offsetRemain: offset } as OnScrollFrameBeginHandlerResult
        } as OnScrollFrameBeginCallback)
      }
    }
  }
}