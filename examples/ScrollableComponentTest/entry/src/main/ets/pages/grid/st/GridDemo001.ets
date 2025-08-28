import {
  memo,
  __memo_context_type,
  __memo_id_type
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
  ComputedBarAttribute,
  GridAttribute,
  ScrollState,
  ItemDragInfo,
  Row,
  OnScrollFrameBeginHandlerResult,
  OnScrollFrameBeginCallback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins
import {
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins
import hilog from '@ohos.hilog'

/**
 * 验证接口
 * scrollBar
 * columnsTemplate
 * columnsGap
 * GridItemStyle，GridItemOptions
 * enableScrollInteraction
 * onScrollStart
 * onScrollStop
 * onReachStart
 * onReachEnd
 * onScrollIndex
 * onScrollFrameBegin
 */
@Component
struct GridDemo001 {
  @State colorNumber1: number = 0xF9CF93;
  @State colorNumber2: number = 0xF9CF93;
  @State colorNumber3: number = 0xF9CF93;
  @State barState: BarState = BarState.On;
  @State columnsTem: string = '1fr';
  @State columnsGap: number = 0;
  @State gridItemStyle: GridItemStyle = GridItemStyle.NONE;
  @State enableScrollInteraction: boolean = true;

  build() {
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
          Button('repeat(auto-fill, 50)')
            .onClick((e: ClickEvent) => {
              this.columnsTem = 'repeat(auto-fill, 50)';
            })
        }

        Row(undefined) {
          Text('columnsGap')
            .fontSize(16)
        }

        Row(undefined) {
          Button('10')
            .onClick((e: ClickEvent) => {
              this.columnsGap = 10;
            })
          Button('0')
            .onClick((e: ClickEvent) => {
              this.columnsGap = 0;
            })
          Button('-10')
            .onClick((e: ClickEvent) => {
              this.columnsGap = -10;
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

        Grid(undefined, undefined) {
          GridItem({ style: this.gridItemStyle }) {
            Text('1')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(50)
          .backgroundColor(this.colorNumber1)

          GridItem({ style: this.gridItemStyle }) {
            Text('2')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(this.colorNumber2)
          .width('100%')
          .height(50)

          GridItem({ style: this.gridItemStyle }) {
            Text('3')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(this.colorNumber3)
          .width('100%')
          .height(50)

          GridItem({ style: this.gridItemStyle }) {
            Text('4')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Red)
          .width('100%')
          .height(50)

          GridItem({ style: this.gridItemStyle }) {
            Text('5')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Green)
          .width('100%')
          .height(50)

          GridItem(undefined) {
            Text('6')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(50)

          GridItem(undefined) {
            Text('7')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Gray)
          .width('100%')
          .height(50)

          GridItem(undefined) {
            Text('8')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(50)

          GridItem(undefined) {
            Text('9')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height(50)
        }
        .columnsTemplate(this.columnsTem)
        .columnsGap(this.columnsGap)
        .height(300)
        .width(300)
        .backgroundColor(0xF9CF93)
        .scrollBar(this.barState)
        .enableScrollInteraction(this.enableScrollInteraction)
        .clip(true)
        .onScrollStart(() => {
          hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onScrollStart');
        })
        .onScrollStop(() => {
          hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onScrollStop');
        })
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
        .onScrollFrameBegin((offset: number, state: ScrollState) => {
          hilog.info(0x0000, 'testTag', 'Grid onScrollFrameBegin state:' + state);
          hilog.info(0x0000, 'testTag', 'Grid onScrollFrameBegin offset:' + offset);
          return { offsetRemain: offset } as OnScrollFrameBeginHandlerResult;
        } as OnScrollFrameBeginCallback)
      }
    }
  }
}

export class ComExampleTrivialApplication extends UserView {
  getBuilder() {
    hilog.info(0x0000, 'testTag', 'getBuilder');
    let wrapper = @
    memo() =>
    {
      hilog.info(0x0000, 'testTag', 'GridDemo001');
      GridDemo001(undefined)
    }
    return wrapper;
  }
}