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
  BarState,
  GridItemAttribute,
  Color,
  GridItemStyle,
  GridDirection,
  GridAttribute,
  ScrollState,
  Row
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
 * multiSelectable
 * selectable
 * selected
 * onSelect
 * rowsTemplate
 * rowsGap
 */
@Component
struct GridDemo002 {
  @State colorNumber1: number = 0xF9CF93;
  @State colorNumber2: number = 0xF9CF93;
  @State colorNumber3: number = 0xF9CF93;
  @State selectable: boolean = true;
  @State selected: boolean = false;
  @State multiSelectable: boolean = false;
  @State rowsTem: string = '1fr';
  @State rowsGap: number = 0;

  build() {
    Column(undefined) {
      Column(undefined) {
        Row(undefined) {
          Text('rowsTemplate')
            .fontSize(16)
        }

        Row(undefined) {
          Button('1fr')
            .onClick((e: ClickEvent) => {
              this.rowsTem = '1fr';
            })
          Button('1fr 1fr')
            .onClick((e: ClickEvent) => {
              this.rowsTem = '1fr 1fr';
            })
          Button('1fr 1fr 2fr')
            .onClick((e: ClickEvent) => {
              this.rowsTem = '1fr 1fr 2fr';
            })
          Button('repeat(auto-fill, 50)')
            .onClick((e: ClickEvent) => {
              this.rowsTem = 'repeat(auto-fill, 50)';
            })
        }

        Row(undefined) {
          Text('rowsGap')
            .fontSize(16)
        }

        Row(undefined) {
          Button('10')
            .onClick((e: ClickEvent) => {
              this.rowsGap = 10;
            })
          Button('0')
            .onClick((e: ClickEvent) => {
              this.rowsGap = 0;
            })
          Button('-10')
            .onClick((e: ClickEvent) => {
              this.rowsGap = -10;
            })
        }

        Row(undefined) {
          Text('multiSelectable')
            .fontSize(16)
        }

        Row(undefined) {
          Button('true')
            .onClick((e: ClickEvent) => {
              this.multiSelectable = true;
            })
          Button('false')
            .onClick((e: ClickEvent) => {
              this.multiSelectable = false;
            })
        }

        Row(undefined) {
          Text('selectable')
            .fontSize(16)
        }

        Row(undefined) {
          Button('true')
            .onClick((e: ClickEvent) => {
              this.selectable = true;
            })
          Button('false')
            .onClick((e: ClickEvent) => {
              this.selectable = false;
            })
        }

        Row(undefined) {
          Text('selected')
            .fontSize(16)
        }

        Row(undefined) {
          Button('true')
            .onClick((e: ClickEvent) => {
              this.selected = true;
            })
          Button('false')
            .onClick((e: ClickEvent) => {
              this.selected = false;
            })
        }

        Grid(undefined, undefined) {
          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('1')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .selectable(this.selectable)
          .selected(this.selected)
          .width('100%')
          .height('100%')
          .backgroundColor(this.colorNumber1)
          .onSelect((parameter: boolean) => {
            hilog.info(0x0000, 'testTag', 'XXX' + 'Grid onSelect1: ' + parameter);
            if (parameter) {
              this.colorNumber1 = 0x6B8E23;
            } else {
              this.colorNumber1 = 0x6A5ACD;
            }
          })

          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('2')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(this.colorNumber2)
          .width('100%')
          .height('100%')

          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('3')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(this.colorNumber3)

          GridItem({ style: GridItemStyle.PLAIN }) {
            Text('4')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Red)
          .width('100%')
          .height('100%')

          GridItem({ style: GridItemStyle.NONE }) {
            Text('5')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Green)
          .width('100%')
          .height('100%')

          GridItem(undefined) {
            Text('6')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height('100%')

          GridItem(undefined) {
            Text('7')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .backgroundColor(Color.Gray)
          .width('100%')
          .height('100%')

          GridItem(undefined) {
            Text('8')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height('100%')

          GridItem(undefined) {
            Text('9')
              .fontSize(16)
              .backgroundColor(0xF9CF93)
          }
          .width('100%')
          .height('100%')
        }
        .columnsTemplate('1fr 1fr 1fr')
        .columnsGap(5)
        .rowsTemplate(this.rowsTem)
        .rowsGap(this.rowsGap)
        .height(300)
        .width(300)
        .backgroundColor(0xF9CF93)
        .multiSelectable(this.multiSelectable)
        .scrollBar(BarState.On)
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
      hilog.info(0x0000, 'testTag', 'GridDemo002');
      GridDemo002(undefined)
    }
    return wrapper;
  }
}