import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Text,
  TextAttribute,
  Column,
  ColumnAttribute,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  FlexAlign,
  Row ,
  RowAttribute,
  Divider,
  List,
  ListItem,
  TextAlign,
  DividerAttribute,
  ListItemAttribute,
  Padding,
  Margin,
  Color,
  CommonMethod,
  Flex,
  FlexAttribute,
  FlexWrap,
  FlexDirection,
  Stack,
  StackAttribute,
  Alignment,
  HorizontalAlign,
  Flex,
  FlexAttribute,
  FlexDirection,
  ItemAlign,
  LengthMetrics,
  FlexSpaceOptions,
  VerticalAlign,
  GridCol,
  GridRow,
  GridColAttribute,
  GridRowAttribute,
  BorderOptions,
  LengthMetrics,
  LocalizedPadding,
  LocalizedMargin,
  $r,
  PixelRoundPolicy,
  PixelRoundCalcPolicy,
  Position,
  Blank,
  EdgeStyles,
  BorderStyle,
  EdgeWidths,
  BorderRadiuses,
  EdgeColors,
  LocalizedEdgeColors,
  LocalizedEdgeWidths,
  LocalizedBorderRadiuses,
  Direction,
  Resource,
  ColumnOptions,
  Entry,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Entry
@Component
export struct Layout002Test {

  build() {
    NavDestination() {
      Column({ space: 10 } as ColumnOptions) {
        Text('margin and padding:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Row() {
            Row().size({ width: '100%', height: '100%' }).backgroundColor('#7b68ee')
          }
          .width(80)
          .height(80)
          .padding({
            top: LengthMetrics.vp(5),
            bottom: LengthMetrics.vp(15),
            start: LengthMetrics.vp(10),
            end: LengthMetrics.vp(20)
          } as LocalizedPadding)
          .margin({
            top: LengthMetrics.vp(40),
            bottom: LengthMetrics.vp(20),
            start: LengthMetrics.vp(30),
            end: LengthMetrics.vp(10)
          } as LocalizedMargin)
          .backgroundColor('#dc1434')
          .direction(Direction.Ltr)
        }.backgroundColor('#ffc0cb')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Column layout with different alignments:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Column() {
          Text('Start').width(80).height(40).backgroundColor('#FF5733')
          Text('Center').width(80).height(40).backgroundColor('#33FF57')
          Text('End').width(80).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#f0f0f0')
        .alignItems(HorizontalAlign.Start)

        Column() {
          Text('Start').width(80).height(40).backgroundColor('#FF5733')
          Text('Center').width(80).height(40).backgroundColor('#33FF57')
          Text('End').width(80).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#e0e0e0')
        .alignItems(HorizontalAlign.Center)

        Column() {
          Text('Start').width(80).height(40).backgroundColor('#FF5733')
          Text('Center').width(80).height(40).backgroundColor('#33FF57')
          Text('End').width(80).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#d0d0d0')
        .alignItems(HorizontalAlign.End)

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Row layout with different alignments:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('Top').width(80).height(40).backgroundColor('#FF5733')
          Text('Center').width(80).height(40).backgroundColor('#33FF57')
          Text('Bottom').width(80).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(100)
        .backgroundColor('#f0f0f0')
        .alignItems(VerticalAlign.Top)

        Row() {
          Text('Top').width(80).height(40).backgroundColor('#FF5733')
          Text('Center').width(80).height(40).backgroundColor('#33FF57')
          Text('Bottom').width(80).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(100)
        .backgroundColor('#e0e0e0')
        .alignItems(VerticalAlign.Center)

        Row() {
          Text('Top').width(80).height(40).backgroundColor('#FF5733')
          Text('Center').width(80).height(40).backgroundColor('#33FF57')
          Text('Bottom').width(80).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(100)
        .backgroundColor('#d0d0d0')
        .alignItems(VerticalAlign.Bottom)

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Flex layout with different directions:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Flex({ direction: FlexDirection.Row }) {
          Text('Item 1').width(60).height(40).backgroundColor('#FF5733')
          Text('Item 2').width(60).height(40).backgroundColor('#33FF57')
          Text('Item 3').width(60).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(60)
        .backgroundColor('#f0f0f0')

        Flex({ direction: FlexDirection.Column }) {
          Text('Item 1').width(60).height(40).backgroundColor('#FF5733')
          Text('Item 2').width(60).height(40).backgroundColor('#33FF57')
          Text('Item 3').width(60).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#e0e0e0')

        Flex({ direction: FlexDirection.RowReverse }) {
          Text('Item 1').width(60).height(40).backgroundColor('#FF5733')
          Text('Item 2').width(60).height(40).backgroundColor('#33FF57')
          Text('Item 3').width(60).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(60)
        .backgroundColor('#d0d0d0')

        Flex({ direction: FlexDirection.ColumnReverse }) {
          Text('Item 1').width(60).height(40).backgroundColor('#FF5733')
          Text('Item 2').width(60).height(40).backgroundColor('#33FF57')
          Text('Item 3').width(60).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#c0c0c0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Flex layout with wrap:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Flex({ wrap: FlexWrap.Wrap }) {
          Text('Item 1').width(80).height(40).backgroundColor('#FF5733')
          Text('Item 2').width(80).height(40).backgroundColor('#33FF57')
          Text('Item 3').width(80).height(40).backgroundColor('#3357FF')
          Text('Item 4').width(80).height(40).backgroundColor('#F3FF33')
          Text('Item 5').width(80).height(40).backgroundColor('#FF33F3')
        }
        .width('100%')
        .height(120)
        .backgroundColor('#f0f0f0')

        Flex({ wrap: FlexWrap.NoWrap }) {
          Text('Item 1').width(80).height(40).backgroundColor('#FF5733')
          Text('Item 2').width(80).height(40).backgroundColor('#33FF57')
          Text('Item 3').width(80).height(40).backgroundColor('#3357FF')
          Text('Item 4').width(80).height(40).backgroundColor('#F3FF33')
          Text('Item 5').width(80).height(40).backgroundColor('#FF33F3')
        }
        .width('100%')
        .height(60)
        .backgroundColor('#e0e0e0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Stack layout:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Stack({ alignContent: Alignment.TopStart }) {
          Text('Bottom').width(150).height(150).backgroundColor('#FF5733')
          Text('Middle').width(100).height(100).backgroundColor('#33FF57')
          Text('Top').width(50).height(50).backgroundColor('#3357FF')
        }
        .width(200)
        .height(200)
        .backgroundColor('#f0f0f0')

        Stack({ alignContent: Alignment.Center }) {
          Text('Bottom').width(150).height(150).backgroundColor('#FF5733')
          Text('Middle').width(100).height(100).backgroundColor('#33FF57')
          Text('Top').width(50).height(50).backgroundColor('#3357FF')
        }
        .width(200)
        .height(200)
        .backgroundColor('#e0e0e0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Border and borderRadius:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('Border').width(80).height(50).backgroundColor('#FF5733')
            .border({
              width: { left: 2, right: 2, top: 2, bottom: 2 } as EdgeWidths,
              color: { left: 0x000000, right: 0x000000, top: 0x000000, bottom: 0x000000 } as EdgeColors,
              radius: { topLeft: 5, topRight: 5, bottomLeft: 5, bottomRight: 5 } as BorderRadiuses,
              style: BorderStyle.Solid
            } as BorderOptions)

          Text('Radius').width(80).height(50).backgroundColor('#33FF57')
            .borderRadius(10)
        }
        .width('100%')
        .height(70)
        .backgroundColor('#f0f0f0')

        Row() {
          Text('Dashed').width(80).height(50).backgroundColor('#3357FF')
            .border({
              width: 2,
              color: 0x000000,
              radius: 8,
              style: BorderStyle.Dashed
            } as BorderOptions)

          Text('Dotted').width(80).height(50).backgroundColor('#F3FF33')
            .border({
              width: 2,
              color: 0x000000,
              radius: 8,
              style: BorderStyle.Dotted
            } as BorderOptions)
        }
        .width('100%')
        .height(70)
        .backgroundColor('#e0e0e0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Size and position:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Stack() {
          Text('Full').width('100%').height('100%').backgroundColor('#FF5733').opacity(0.3)
          Text('50%').width('50%').height('50%').backgroundColor('#33FF57').opacity(0.5)
          Text('25%').width('25%').height('25%').backgroundColor('#3357FF').opacity(0.7)
        }
        .width(200)
        .height(200)
        .backgroundColor('#f0f0f0')

        Row() {
          Text('Absolute').width(60).height(40).backgroundColor('#FF5733')
            .position({ x: 10, y: 10 } as Position)
          Text('Relative').width(60).height(40).backgroundColor('#33FF57')
        }
        .width(200)
        .height(80)
        .backgroundColor('#e0e0e0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Nested layouts:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Column() {
          Row() {
            Text('R1C1').width(60).height(40).backgroundColor('#FF5733')
            Text('R1C2').width(60).height(40).backgroundColor('#33FF57')
          }
          Row() {
            Text('R2C1').width(60).height(40).backgroundColor('#3357FF')
            Text('R2C2').width(60).height(40).backgroundColor('#F3FF33')
          }
        }
        .width('100%')
        .height(100)
        .backgroundColor('#f0f0f0')

        Flex({ direction: FlexDirection.Column }) {
          Column() {
            Text('C1').width(60).height(40).backgroundColor('#FF5733')
          }
          Row() {
            Text('R1').width(60).height(40).backgroundColor('#33FF57')
            Text('R2').width(60).height(40).backgroundColor('#3357FF')
          }
          Column() {
            Text('C2').width(60).height(40).backgroundColor('#F3FF33')
          }
        }
        .width('100%')
        .height(150)
        .backgroundColor('#e0e0e0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Flex justify content:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Flex({ justifyContent: FlexAlign.Start }) {
          Text('1').width(40).height(30).backgroundColor('#FF5733')
          Text('2').width(40).height(30).backgroundColor('#33FF57')
          Text('3').width(40).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(40)
        .backgroundColor('#f0f0f0')

        Flex({ justifyContent: FlexAlign.Center }) {
          Text('1').width(40).height(30).backgroundColor('#FF5733')
          Text('2').width(40).height(30).backgroundColor('#33FF57')
          Text('3').width(40).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(40)
        .backgroundColor('#e0e0e0')

        Flex({ justifyContent: FlexAlign.End }) {
          Text('1').width(40).height(30).backgroundColor('#FF5733')
          Text('2').width(40).height(30).backgroundColor('#33FF57')
          Text('3').width(40).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(40)
        .backgroundColor('#d0d0d0')

        Flex({ justifyContent: FlexAlign.SpaceBetween }) {
          Text('1').width(40).height(30).backgroundColor('#FF5733')
          Text('2').width(40).height(30).backgroundColor('#33FF57')
          Text('3').width(40).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(40)
        .backgroundColor('#c0c0c0')

        Flex({ justifyContent: FlexAlign.SpaceAround }) {
          Text('1').width(40).height(30).backgroundColor('#FF5733')
          Text('2').width(40).height(30).backgroundColor('#33FF57')
          Text('3').width(40).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(40)
        .backgroundColor('#b0b0b0')

        Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
          Text('1').width(40).height(30).backgroundColor('#FF5733')
          Text('2').width(40).height(30).backgroundColor('#33FF57')
          Text('3').width(40).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(40)
        .backgroundColor('#a0a0a0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Column justify content:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Column() {
          Text('1').width(60).height(30).backgroundColor('#FF5733')
          Text('2').width(60).height(30).backgroundColor('#33FF57')
          Text('3').width(60).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#f0f0f0')
        .justifyContent(FlexAlign.Start)

        Column() {
          Text('1').width(60).height(30).backgroundColor('#FF5733')
          Text('2').width(60).height(30).backgroundColor('#33FF57')
          Text('3').width(60).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#e0e0e0')
        .justifyContent(FlexAlign.Center)

        Column() {
          Text('1').width(60).height(30).backgroundColor('#FF5733')
          Text('2').width(60).height(30).backgroundColor('#33FF57')
          Text('3').width(60).height(30).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#d0d0d0')
        .justifyContent(FlexAlign.SpaceBetween)

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Direction test:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('LTR').width(60).height(40).backgroundColor('#FF5733')
          Text('LTR').width(60).height(40).backgroundColor('#33FF57')
          Text('LTR').width(60).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(60)
        .backgroundColor('#f0f0f0')
        .direction(Direction.Ltr)

        Row() {
          Text('RTL').width(60).height(40).backgroundColor('#FF5733')
          Text('RTL').width(60).height(40).backgroundColor('#33FF57')
          Text('RTL').width(60).height(40).backgroundColor('#3357FF')
        }
        .width('100%')
        .height(60)
        .backgroundColor('#e0e0e0')
        .direction(Direction.Rtl)

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Blank component:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('Left').width(60).height(40).backgroundColor('#FF5733')
          Blank().width(20)
          Text('Right').width(60).height(40).backgroundColor('#33FF57')
        }
        .width('100%')
        .height(60)
        .backgroundColor('#f0f0f0')

        Column() {
          Text('Top').width(60).height(40).backgroundColor('#3357FF')
          Blank().height(20)
          Text('Bottom').width(60).height(40).backgroundColor('#F3FF33')
        }
        .width('100%')
        .height(120)
        .backgroundColor('#e0e0e0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('GridRow and GridCol:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        GridRow({
          columns: 4,
          gutter: { x: 10, y: 10 } as LengthMetrics
        } as GridRowAttribute) {
          ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
            GridCol({ span: 1 } as GridColAttribute) {
              Text(`Item ${item}`)
                .width('100%')
                .height(50)
                .backgroundColor(item % 2 === 0 ? '#FF5733' : '#33FF57')
                .textAlign(TextAlign.Center)
            }
          })
        }
        .width('100%')
        .height(150)
        .backgroundColor('#f0f0f0')

        GridRow({
          columns: 3,
          gutter: { x: 10, y: 10 } as LengthMetrics
        } as GridRowAttribute) {
          GridCol({ span: 2 } as GridColAttribute) {
            Text('Span 2')
              .width('100%')
              .height(50)
              .backgroundColor('#3357FF')
              .textAlign(TextAlign.Center)
          }
          GridCol({ span: 1 } as GridColAttribute) {
            Text('Span 1')
              .width('100%')
              .height(50)
              .backgroundColor('#F3FF33')
              .textAlign(TextAlign.Center)
          }
        }
        .width('100%')
        .height(80)
        .backgroundColor('#e0e0e0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('List and ListItem:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        List({ space: 10 }) {
          ForEach([1, 2, 3, 4, 5], (item: number) => {
            ListItem() {
              Text(`List Item ${item}`)
                .width('100%')
                .height(50)
                .backgroundColor(item % 2 === 0 ? '#FF5733' : '#33FF57')
                .textAlign(TextAlign.Center)
            }
            .width('100%')
          })
        }
        .width('100%')
        .height(300)
        .backgroundColor('#f0f0f0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Button with different states:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Button('Normal')
            .width(100)
            .height(40)
            .backgroundColor('#FF5733')
            .onClick(() => {
              hilog.info(0x0000, 'Layout002Test', 'Normal button clicked')
            })

          Button('Disabled')
            .width(100)
            .height(40)
            .backgroundColor('#CCCCCC')
            .enabled(false)
        }
        .width('100%')
        .height(60)
        .backgroundColor('#f0f0f0')

        Divider().strokeWidth(2).color(0xCCCCCC)

        Text('Complex nested layout:').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Column() {
          Row() {
            Column() {
              Text('C1').width(40).height(30).backgroundColor('#FF5733')
              Text('C2').width(40).height(30).backgroundColor('#33FF57')
            }
            .width(50)
            .height(80)
            .backgroundColor('#f0f0f0')

            Stack() {
              Text('S1').width(40).height(30).backgroundColor('#3357FF')
              Text('S2').width(30).height(20).backgroundColor('#F3FF33')
            }
            .width(50)
            .height(80)
            .backgroundColor('#e0e0e0')

            Flex({ direction: FlexDirection.Column }) {
              Text('F1').width(40).height(30).backgroundColor('#FF33F3')
              Text('F2').width(40).height(30).backgroundColor('#33FFF3')
            }
            .width(50)
            .height(80)
            .backgroundColor('#d0d0d0')
          }
          .width('100%')
          .height(100)
          .backgroundColor('#c0c0c0')
        }
        .width('100%')
        .height(120)
        .backgroundColor('#b0b0b0')

      }.width('100%').margin({ top: 5 } as Margin)
    }
    .title('布局基础功能测试用例002')
  }
}