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
  Entry,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Entry
@Component
export struct Layout001Test {

  addLayoutMoreTest() {
    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Direction Column Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column }) {
        Text('Item1').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('Item2').width('100%').height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('Item3').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Direction Row Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row }) {
        Text('Item1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('Item2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('Item3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Wrap Wrap Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
          Text('Wrap' + item)
            .width(80).height(50)
            .backgroundColor(Color.Orange)
            .margin(5)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Justify Space Around Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
        Text('Around1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('Around2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('Around3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row Space Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 20 }) {
        Text('R1').width(70).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('R2').width(70).height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        Text('R3').width(70).height(50).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column Space Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 15 }) {
        Text('C1').width('100%').height(50).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
        Text('C2').width('100%').height(50).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        Text('C3').width('100%').height(50).backgroundColor(Color.Brown).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack Default Alignment Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack() {
        Text('S1').width(120).height(70).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('S2').width(100).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('S3').width(80).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width(140).height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack Alignment Top Start Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack({ alignContent: Alignment.TopStart }) {
        Text('TS1').width(100100).height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('TS2').width(80).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('TS3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width(120).height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow Columns 5 Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 5, gutterX: 8, gutterY: 8 }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], (item: number) => {
          GridCol() {
            Text('G' + item)
              .width('100%').height(45)
              .backgroundColor(Color.Lime)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List No Space Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List() {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text('NoSpace ' + item)
              .width('100%').height(50)
              .backgroundColor(Color.Gray)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(300)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Padding Top Bottom Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Padding TB')
        .width(160).height(80)
        .padding({ top: 15, bottom: 15 } as LocalizedPadding)
        .backgroundColor(Color.White)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Padding Left Right Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Padding LR')
        .width(160).height(80)
        .padding({ left: 20, right: 20 } as LocalizedPadding)
        .backgroundColor(Color.Black)
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Margin Top Only Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Margin Top')
        .width(140).height(70)
        .margin({ top: 30 } as LocalizedMargin)
        .backgroundColor(Color.Red)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Border Width Different Sides Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Diff Border')
        .width(180).height(100)
        .borderWidth({ left: 2, right: 4, top: 6, bottom: 8 } as EdgeWidths)
        .borderColor(Color.Blue)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Border Radius Different Corners Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Diff Radius')
        .width(180).height(100)
        .borderRadius({ topLeft: 5, topRight: 10, bottomLeft: 15, bottomRight: 20 } as BorderRadiuses)
        .backgroundColor(Color.Yellow)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Item Align Baseline Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Baseline }) {
        Text('Base1').width(80).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('Base2').width(80).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('Base3').width(80).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row Default Vertical Align Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row() {
        Text('Def1').width(70).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('Def2').width(70).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('Def3').width(70).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column Default Horizontal Align Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Text('Def1').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('Def2').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('Def3').width(120).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Nested Flex Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column }) {
        Flex({ direction: FlexDirection.Row }) {
          Text('NF1').width(60).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('NF2').width(60).height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%')
        Flex({ direction: FlexDirection.Row }) {
          Text('NF3').width(60).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('NF4').width(60).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%')
      }.width('100%').height(120)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Nested Row Column Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row() {
        Column() {
          Text('NR1').width('100%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('NR2').width('100%').height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width(80)
        Column() {
          Text('NR3').width('100%').height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('NR4').width('100%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width(80)
      }.width('100%').height(120)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Blank with Color Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row() {
        Text('Left').width(80).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank().color(Color.Green)
        Text('Right').width(80).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Position with Negative Values Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack() {
        Text('Base')
          .width(200).height(200)
          .backgroundColor(Color.Gray)
          .fontSize(30)
          .textAlign(TextAlign.Center)
        Text('Neg')
          .width(80).height(40)
          .backgroundColor(Color.Red)
          .fontSize(16)
          .textAlign(TextAlign.Center)
          .position({ x: -20, y: -10 } as Position)
      }.width(220).height(220)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Multiple Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
        ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
          Text('M' + item)
            .width(50).height(40)
            .backgroundColor(Color.Orange)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(60)
    }).width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List with Long Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List({ space: 10 }) {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text('Long List Item Number ' + item + ' for testing')
              .width('100%').height(60)
              .backgroundColor(Color.Pink)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(350)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Span Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 3, gutterX: 10, gutterY: 10 }) {
        GridCol() {
          Text('Span1').width('100%').height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }
        GridCol({ span: 2 }) {
          Text('Span2').width('100%').height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }
        GridCol({ span: 2 }) {
          Text('Span3').width('100%').height(60).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('Span4').width('100%').height(60).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }
      }.width('100%').height(180)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Different Widths Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row }) {
        Text('W1').width(40).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('W2').width(80).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('W3').width(120).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Percentage Width Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row() {
        Text('30%').width('30%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('40%').width('40%').height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('30%').width('30%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Percentage Height Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Text('30%').width('100%').height('30%').backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('40%').width('100%').height('40%').backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('30%').width('100%').height('30%').backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack with Many Layers Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack({ alignContent: Alignment.Center }) {
        Text('Layer1').width(200).height(200).backgroundColor(Color.Red).fontSize(30).textAlign(TextAlign.Center)
        Text('Layer2').width(180).height(180).backgroundColor(Color.Orange).fontSize(25).textAlign(TextAlign.Center)
        Text('Layer3').width(160).height(160).backgroundColor(Color.Yellow).fontSize(20).textAlign(TextAlign.Center)
        Text('Layer4').width(140).height(140).backgroundColor(Color.Green).fontSize(18).textAlign(TextAlign.Center)
        Text('Layer5').width(120).height(120).backgroundColor(Color.Cyan).fontSize(16).textAlign(TextAlign.Center)
      }.width(220).height(220)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Border with Hex Color Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Hex Border')
        .width(180).height(100)
        .borderWidth(6)
        .borderColor('#FF00FF')
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Background with Hex Color Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Hex BG')
        .width(180).height(100)
        .backgroundColor('#00FFFF')
        .fontColor('#000000')
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Column with Space Between Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.SpaceBetween }) {
        Text('SB1').width('100%').height(40).backgroundColor(Color.Red).ariaLabel('Item 1').textAlign(TextAlign.Center)
        Text('SB2').width('100%').height(40).backgroundColor(Color.Green).ariaLabel('Item 2').textAlign(TextAlign.Center)
        Text('SB3').width('100%').height(40).backgroundColor(Color.Blue).ariaLabel('Item 3').textAlign(TextAlign.Center)
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Column with Space Evenly Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.SpaceEvenly }) {
        Text('SE1').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('SE2').width('100%').height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('SE3').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Column with Space Around Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.SpaceAround }) {
        Text('SA1').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('SA2').width('100%').height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('SA3').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Multiple Spaces Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 15 }) {
        Text('MS1').width(60).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('MS2').width(60).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('MS3').width(60).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        Text('MS4').width(60).height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Multiple Spaces Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 12 }) {
        Text('MS1').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('MS2').width('100%').height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('MS3').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        Text('MS4').width('100%').height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Large Gutter Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 3, gutterX: 20, gutterY: 20 }) {
        ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
          GridCol() {
            Text('LG' + item)
              .width('100%').height(60)
              .backgroundColor(Color.Purple)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(250)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List with Small Space Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List({ space: 5 }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
          ListItem() {
            Text('SmallSpace ' + item)
              .width('100%').height(45)
              .backgroundColor(Color.Orange)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(400)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Padding All Sides Large Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Large Padding')
        .width(160).height(80)
        .padding(30)
        .backgroundColor(Color.Cyan)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Margin All Sides Large Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Large Margin')
        .width(140).height(70)
        .margin(25)
        .backgroundColor(Color.Magenta)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Border Width Large Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Large Border')
        .width(180).height(100)
        .borderWidth(15)
        .borderColor(Color.Black)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Border Radius Large Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Text('Large Radius')
        .width(180).height(100)
        .borderRadius(40)
        .backgroundColor(Color.Yellow)
        .textAlign(TextAlign.Center)
        .fontSize(18)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Small Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
          Text('S' + item)
            .width(40).height(30)
            .backgroundColor(Color.Gray)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(50)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Small Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 8 }) {
        ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
          Text('RS' + item)
            .width(50).height(35)
            .backgroundColor(Color.Red)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(50)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Small Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 8 }) {
        ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
          Text('CS' + item)
            .width('100%').height(30)
            .backgroundColor(Color.Green)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(250)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack with Small Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack({ alignContent: Alignment.Center }) {
        Text('SS1').width(80).height(60).backgroundColor(Color.Red).fontSize(20).textAlign(TextAlign.Center)
        Text('SS2').width(60).height(50).backgroundColor(Color.Green).fontSize(16).textAlign(TextAlign.Center)
        Text('SS3').width(40).height(40).backgroundColor(Color.Blue).fontSize(14).textAlign(TextAlign.Center)
      }.width(100).height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Small Cells Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 4, gutterX: 5, gutterY: 5 }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], (item: number) => {
          GridCol() {
            Text('SC' + item)
              .width('100%').height(35)
              .backgroundColor(Color.Orange)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List with Small Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List({ space: 8 }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], (item: number) => {
          ListItem() {
            Text('SmallItem ' + item)
              .width('100%').height(35)
              .backgroundColor(Color.Pink)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(400)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Large Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
        ForEach([1, 2, 3], (item: number) => {
          Text('L' + item)
            .width(100).height(80)
            .backgroundColor(Color.Blue)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Large Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 20 }) {
        ForEach([1, 2, 3], (item: number) => {
          Text('RL' + item)
            .width(100).height(80)
            .backgroundColor(Color.Yellow)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Large Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 20 }) {
        ForEach([1, 2, 3], (item: number) => {
          Text('CL' + item)
            .width('100%').height(80)
            .backgroundColor(Color.Purple)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(300)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack with Large Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack({ alignContent: Alignment.Center }) {
        Text('SL1').width(200).height(150).backgroundColor(Color.Red).fontSize(35).textAlign(TextAlign.Center)
        Text('SL2').width(160).height(120).backgroundColor(Color.Orange).fontSize(28).textAlign(TextAlign.Center)
        Text('SL3').width(120).height(90).backgroundColor(Color.Yellow).fontSize(22).textAlign(TextAlign.Center)
      }.width(220).height(180)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Large Cells Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 2, gutterX: 15, gutterY: 15 }) {
        ForEach([1, 2, 3, 4], (item: number) => {
          GridCol() {
            Text('LC' + item)
              .width('100%').height(100)
              .backgroundColor(Color.Teal)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(280)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List with Large Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List({ space: 15 }) {
        ForEach([1, 2, 3, 4, 5], (item: number) => {
          ListItem() {
            Text('LargeItem ' + item)
              .width('100%').height(80)
              .backgroundColor(Color.Brown)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(450)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex Wrap with Many Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceAround }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], (item: number) => {
          Text('WrapMany' + item)
            .width(70).height(45)
            .backgroundColor(Color.Lime)
            .margin(5)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(250)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex NoWrap with Many Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ wrap: FlexWrap.NoWrap }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
          Text('NoWrap' + item)
            .width(60).height(40)
            .backgroundColor(Color.Olive)
            .margin(3)
            .textAlign(TextAlign.Center)
        })
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Nested Stack Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack({ alignContent: Alignment.Center }) {
        Stack({ alignContent: Alignment.Center }) {
          Text('Inner1').width(100).height(80).backgroundColor(Color.Red).fontSize(20).textAlign(TextAlign.Center)
          Text('Inner2').width(80).height(60).backgroundColor(Color.Green).fontSize(16).textAlign(TextAlign.Center)
        }.width(120).height(100)
        Text('Outer').width(140).height(120).backgroundColor(Color.Blue).fontSize(25).textAlign(TextAlign.Center)
      }.width(160).height(140)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Deep Nested Layout Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Row() {
          Column() {
            Text('D1').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
            Text('D2').width('100%').height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
          }.width(80)
          Column() {
            Text('D3').width('100%').height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
            Text('D4').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          }.width(80)
        }.width('100%')
        Row() {
          Column() {
            Text('D5').width('100%').height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
            Text('D6').width('100%').height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
          }.width(80)
          Column() {
            Text('D7').width('100%').height(40).backgroundColor(Color.Orange).textAlign(TextAlign.Center)
            Text('D8').width('100%').height(40).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
          }.width(80)
        }.width('100%')
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Blank Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row }) {
        Text('Left').width(80).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('Right').width(80).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Blank Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Text('Top').width('100%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('Bottom').width('100%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Border with Different Styles Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 15 }) {
        Text('Solid')
          .width(80).height(60)
          .borderStyle(BorderStyle.Solid)
          .borderWidth(4)
          .borderColor(Color.Red)
          .textAlign(TextAlign.Center)
        Text('Dashed')
          .width(80).height(60)
          .borderStyle(BorderStyle.Dashed)
          .borderWidth(4)
          .borderColor(Color.Green)
          .textAlign(TextAlign.Center)
        Text('Dotted')
          .width(80).height(60)
          .borderStyle(BorderStyle.Dotted)
          .borderWidth(4)
          .borderColor(Color.Blue)
          .textAlign(TextAlign.Center)
      }.width('100%').height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Offset Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 3, gutterX: 10, gutterY: 10 }) {
        GridCol() {
          Text('Offset1').width('100%').height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }
        GridCol({ offset: 1 }) {
          Text('Offset2').width('100%').height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('Offset3').width('100%').height(60).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('Offset4').width('100%').height(60).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }
      }.width('100%').height(180)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Different Alignments Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Start }) {
          Text('Start').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(60).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(70)
        Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
          Text('Center').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Center').width(60).height(60).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(70)
        Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.End }) {
          Text('End').width(60).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('End').width(60).height(60).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(70)
      }.width('100%').height(250)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Different Vertical Aligns Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Row({ verticalAlign: VerticalAlign.Top }) {
          Text('Top').width(70).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Top').width(70).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(70)
        Row({ verticalAlign: VerticalAlign.Center }) {
          Text('Center').width(70).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Center').width(70).height(60).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(70)
        Row({ verticalAlign: VerticalAlign.Bottom }) {
          Text('Bottom').width(70).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('Bottom').width(70).height(60).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(70)
      }.width('100%').height(250)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Different Horizontal Aligns Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Column({ alignItems: HorizontalAlign.Start }) {
          Text('Start').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Column({ alignItems: HorizontalAlign.Center }) {
          Text('Center').width(100).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Center').width(150).height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Column({ alignItems: HorizontalAlign.End }) {
          Text('End').width(100).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('End').width(150).height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(100)
      }.width('100%').height(350)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack with Different Alignments Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 10 }) {
        Stack({ alignContent: Alignment.TopStart }) {
          Text('TS').width(80).height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }.width(100).height(80)
        Stack({ alignContent: Alignment.Center }) {
          Text('C').width(80).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width(100).height(80)
        Stack({ alignContent: Alignment.BottomEnd }) {
          Text('BE').width(80).height(60).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width(100).height(80)
      }.width('100%').height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Complex Nested Layout Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column }) {
        Row() {
          Stack({ alignContent: Alignment.Center }) {
            Text('S1').width(60).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          }.width(80).height(70)
          Column() {
            Text('C1').width('100%').height(30).backgroundColor(Color.Green).textAlign(TextAlign.Center)
            Text('C2').width('100%').height(30).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          }.width(80).height(70)
        }.width('100%')
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
          Text('F1').width(80).height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
          Text('F2').width(80).height(50).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('F3').width(80).height(50).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%')
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List with Nested Layout Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List({ space: 10 }) {
        ListItem() {
          Row() {
            Text('Item1').width(100).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
            Text('Detail1').width('100%').height(50).backgroundColor(Color.Orange).textAlign(TextAlign.Center)
          }.width('100%')
        }
        ListItem() {
          Row() {
            Text('Item2').width(100).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
            Text('Detail2').width('100%').height(50).backgroundColor(Color.Lime).textAlign(TextAlign.Center)
          }.width('100%')
        }
        ListItem() {
          Row() {
            Text('Item3').width(100).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
            Text('Detail3').width('100%').height(50).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
          }.width('100%')
        }
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Complex Span Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 4, gutterX: 10, gutterY: 10 }) {
        GridCol() {
          Text('C1').width('100%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }
        GridCol({ span: 2 }) {
          Text('C2').width('100%').height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('C3').width('100%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }
        GridCol({ span: 3 }) {
          Text('C4').width('100%').height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('C5').width('100%').height(50).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
        }
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Color Variations Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
        Text('Red').width(70).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('Green').width(70).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('Blue').width(70).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        Text('Yellow').width(70).height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        Text('Pink').width(70).height(50).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Border with Color Variations Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 10 }) {
        Text('Red').width(70).height(50).borderWidth(4).borderColor(Color.Red).textAlign(TextAlign.Center)
        Text('Green').width(70).height(50).borderWidth(4).borderColor(Color.Green).textAlign(TextAlign.Center)
        Text('Blue').width(70).height(50).borderWidth(4).所以borderColor(Color.Blue).textAlign(TextAlign.Center)
        Text('Yellow').width(70).height(50).borderWidth(4).borderColor(Color.Yellow).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Different Heights Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Start }) {
        Text('H30').width(60).height(30).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('H50').width(60).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('H70').width(60).height(70).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        Text('H90').width(60).height(90).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
      }.width('100%').height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Different Widths Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start }) {
        Text('W50').width(50).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('W100').width(100).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('W150').width(150).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        Text('W200').width(200).height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Different Heights Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ verticalAlign: VerticalAlign.Top }) {
        Text('RH30').width(60).height(30).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('RH50').width(60).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('RH70').width(60).height(70).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        Text('RH90').width(60).height(90).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
      }.width('100%').height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Different Widths Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ alignItems: HorizontalAlign.Start }) {
        Text('CW50').width(50).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('CW100').width(100).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('CW150').width(150).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        Text('CW200').width(200).height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack with Different Sizes Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack({ alignContent: Alignment.BottomStart }) {
        Text('S200x150').width(200).height(150).backgroundColor(Color.Red).fontSize(20).textAlign(TextAlign.Center)
        Text('S150x120').width(150).height(120).backgroundColor(Color.Green).fontSize(18).textAlign(TextAlign.Center)
        Text('S100x90').width(100).height(90).backgroundColor(Color.Blue).fontSize(16).textAlign(TextAlign.Center)
        Text('S50x60').width(50).height(60).backgroundColor(Color.Yellow).fontSize(14).textAlign(TextAlign.Center)
      }.width(220).height(180)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Different Cell Heights Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 3, gutterX: 10, gutterY: 10 }) {
        GridCol() {
          Text('H40').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('H60').width('100%').height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('H80').width('100%').height(80).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('H50').width('100%').height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('H70').width('100%').height(70).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('H90').width('100%').height(90).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }
      }.width('100%').height(280)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List with Different Item Heights Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List({ space: 10 }) {
        ListItem() {
          Text('Height 40').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }
        ListItem() {
          Text('Height 60').width('100%').height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }
        ListItem() {
          Text('Height 80').width('100%').height(80).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }
        ListItem() {
          Text('Height 50').width('100%').height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }
        ListItem() {
          Text('Height 70').width('100%').height(70).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
        }
      }.width('100%').height(400)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Mixed Content Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
        Text('Text').width(80).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('Text2').width(80).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Blank()
        Text('Text3').width(80).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Mixed Content Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row() {
        Text('RText').width(70).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('RText2').width(70).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Blank()
        Text('RText3').width(70).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Mixed Content Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Text('CText').width('100%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('CText2').width('100%').height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Blank()
        Text('CText3').width('100%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Border Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
        Text('B1').width(70).height(50).borderWidth(3).borderColor(Color.Red).backgroundColor(Color.White).textAlign(TextAlign.Center)
        Text('B2').width(70).height(50).borderWidth(3).borderColor(Color.Green).backgroundColor(Color.White).textAlign(TextAlign.Center)
        Text('B3').width(70).height(50).borderWidth(3).borderColor(Color.Blue).backgroundColor(Color.White).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Border Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 10 }) {
        Text('RB1').width(70).height(50).borderWidth(3).borderColor(Color.Red).backgroundColor(Color.White).textAlign(TextAlign.Center)
        Text('RB2').width(70).height(50).borderWidth(3).borderColor(Color.Green).backgroundColor(Color.White).textAlign(TextAlign.Center)
        Text('RB3').width(70).height(50).borderWidth(3).borderColor(Color.Blue).backgroundColor(Color.White).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Border Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Text('CB1').width('100%').height(50).borderWidth(3).borderColor(Color.Red).backgroundColor(Color.White).textAlign(TextAlign.Center)
        Text('CB2').width('100%').height(50).borderWidth(3).borderColor(Color.Green).backgroundColor(Color.White).textAlign(TextAlign.Center)
        Text('CB3').width('100%').height(50).borderWidth(3).borderColor(Color.Blue).backgroundColor(Color.White).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Radius Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
        Text('R1').width(70).height(50).borderRadius(10).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('R2').width(70).height(50).borderRadius(15).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('R3').width(70).height(50).borderRadius(20).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Radius Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 10 }) {
        Text('RR1').width(70).height(50).borderRadius(10).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('RR2').width(70).height(50).borderRadius(15).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('RR3').width(70).height(50).borderRadius(20).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(70)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Radius Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Text('CR1').width('100%').height(50).borderRadius(10).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('CR2').width('100%').height(50).borderRadius(15).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('CR3').width('100%').height(50).borderRadius(20).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Padding Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
        Text('P1').width(70).height(50).padding(10).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('P2').width(70).height(50).padding(15).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('P3').width(70).height(50).padding(20).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Padding Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 10 }) {
        Text('RP1').width(70).height(50).padding(10).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('RP2').width(70).height(50).padding(15).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('RP3').width(70).height(50).padding(20).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Padding Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Text('CP1').width('100%').height(50).padding(10).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('CP2').width('100%').height(50).padding(15).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('CP3').width('100%').height(50).padding(20).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Margin Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
        Text('M1').width(70).height(50).margin(5).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('M2').width(70).height(50).margin(10).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('M3').width(70).height(50).margin(15).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Margin Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 10 }) {
        Text('RM1').width(70).height(50).margin(5).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('RM2').width(70).height(50).margin(10).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('RM3').width(70).height(50).margin(15).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(80)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Margin Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Text('CM1').width('100%').height(50).margin(5).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Text('CM2').width('100%').height(50).margin(10).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Text('CM3').width('100%').height(50).margin(15).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Complex Layout Combination Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
          Stack({ alignContent: Alignment.Center }) {
            Text('Stack').width(60).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          }.width(80).height(70)
          Column() {
            Text('Col1').width('100%').height(30).backgroundColor(Color.Green).textAlign(TextAlign.Center)
            Text('Col2').width('100%').height(30).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          }.width(80).height(70)
          Row() {
            Text('Row1').width(40).height(35).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
            Text('Row2').width(40).height(35).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          }.width(80).height(70)
        }.width('100%')
        List({ space: 5 }) {
          ListItem() {
            Text('ListItem1').width('100%').height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
          }
          ListItem() {
            Text('ListItem2').width('100%').height(40).backgroundColor(Color.Orange).textAlign(TextAlign.Center)
          }
        }.width('100%').height(100)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Full Span Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 3, gutterX: 10, gutterY: 10 }) {
        GridCol() {
          Text('C1').width('100%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('C2').width('100%').height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }
        GridCol() {
          Text('C3').width('100%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }
        GridCol({ span: 3 }) {
          Text('Full Span').width('100%').height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Empty Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
        Text('Item1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('Item2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Blank()
        Text('Item3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with Empty Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row() {
        Text('RItem1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('RItem2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Blank()
        Text('RItem3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(60)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with Empty Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Text('CItem1').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        Blank()
        Text('CItem2').width('100%').height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        Blank()
        Text('CItem3').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack with Position Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Stack() {
        Text('Base').width(200).height(200).backgroundColor(Color.Gray).fontSize(30).textAlign(TextAlign.Center)
        Text('Pos1').width(60).height(40).backgroundColor(Color.Red).fontSize(14).textAlign(TextAlign.Center).position({ x: 10, y: 10 } as Position)
        Text('Pos2').width(60).height(40).backgroundColor(Color.Green).fontSize(14).textAlign(TextAlign.Center).position({ x: 130, y: 10 } as Position)
        Text('Pos3').width(60).height(40).backgroundColor(Color.Blue).fontSize(14).textAlign(TextAlign.Center).position({ x: 10, y: 150 } as Position)
        Text('Pos4').width(60).height(40).backgroundColor(Color.Yellow).fontSize(14).textAlign(TextAlign.Center).position({ x: 130, y: 150 } as Position)
      }.width(220).height(220)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with Percentage Width and Height Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Flex({ direction: FlexDirection.Column }) {
        Flex({ direction: FlexDirection.Row }) {
          Text('25%').width('25%').height('100%').backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('50%').width('50%').height('100%').backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('25%').width('25%').height('100%').backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height('50%')
        Flex({ direction: FlexDirection.Row }) {
          Text('33%').width('33%').height('100%').backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
          Text('34%').width('34%').height('100%').backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('33%').width('33%').height('100%').backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height('50%')
      }.width('100%').height(150)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('List with Many Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      List({ space: 8 }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15], (item: number) => {
          ListItem() {
            Text('ManyItem ' + item)
              .width('100%').height(40)
              .backgroundColor(item % 2 === 0 ? Color.Gray : Color.LightGray)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(400)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('GridRow with Many Columns Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      GridRow({ columns: 5, gutterX: 8, gutterY: 8 }) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15], (item: number) => {
          GridCol() {
            Text('GC' + item)
              .width('100%').height(45)
              .backgroundColor(item % 2 === 0 ? Color.Orange : Color.Yellow)
              .textAlign(TextAlign.Center)
          }
        })
      }.width('100%').height(200)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with All Justify Content Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Start }) {
          Text('Start').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(50)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Center }) {
          Text('Center').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Center').width(60).height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(50)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.End }) {
          Text('End').width(60).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('End').width(60).height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(50)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
          Text('Between').width(60).height(40).backgroundColor(Color.Orange).textAlign(TextAlign.Center)
          Text('Between').width(60).height(40).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
        }.width('100%').height(50)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
          Text('Around').width(60).height(40).backgroundColor(Color.Brown).textAlign(TextAlign.Center)
          Text('Around').width(60).height(40).backgroundColor(Color.Gray).textAlign(TextAlign.Center)
        }.width('100%').height(50)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceEvenly }) {
          Text('Evenly').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Evenly').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(50)
      }.width('100%').height(380)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with All Align Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start }) {
          Text('Start').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
          Text('Center').width(100).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Center').width(150).height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.End }) {
          Text('End').width(100).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('End').width(150).height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Stretch }) {
          Text('Stretch').width(100).height(40).backgroundColor(Color.Orange).textAlign(TextAlign.Center)
          Text('Stretch').width(150).height(40).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
        }.width('100%').height(100)
      }.width('100%').height(450)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Row with All Vertical Align Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Row({ verticalAlign: VerticalAlign.Top }) {
          Text('Top').width(70).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Top').width(70).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(70)
        Row({ verticalAlign: VerticalAlign.Center }) {
          Text('Center').width(70).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Center').width(70).height(60).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(70)
        Row({ verticalAlign: VerticalAlign.Bottom }) {
          Text('Bottom').width(70).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('Bottom').width(70).height(60).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(70)
      }.width('100%').height(250)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Column with All Horizontal Align Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Column({ alignItems: HorizontalAlign.Start }) {
          Text('Start').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Column({ alignItems: HorizontalAlign.Center }) {
          Text('Center').width(100).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Center').width(150).height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Column({ alignItems: HorizontalAlign.End }) {
          Text('End').width(100).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('End').width(150).height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(100)
      }.width('100%').height(350)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Stack with All Alignments Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Row({ space: 10 }) {
        Stack({ alignContent: Alignment.TopStart }) {
          Text('TS').width(70).height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
        }.width(90).height(80)
        Stack({ alignContent: Alignment.TopEnd }) {
          Text('TE').width(100).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width(120).height(80)
        Stack({ alignContent: Alignment.Center }) {
          Text('C').width(80).height(60).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width(100).height(80)
        Stack({ alignContent: Alignment.BottomStart }) {
          Text('BS').width(70).height(60).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width(90).height(80)
        Stack({ alignContent: Alignment.BottomEnd }) {
          Text('BE').width(100).height(60).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
        }.width(120).height(80)
      }.width('100%').height(100)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with All Directions Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Flex({ direction: FlexDirection.Row }) {
          Text('Row1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Row2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
        }.width('100%').height(50)
        Flex({ direction: FlexDirection.Column }) {
          Text('Col1').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          Text('Col2').width('100%').height(40).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
        }.width('100%').height(100)
        Flex({ direction: FlexDirection.RowReverse }) {
          Text('RowRev1').width(60).height(40).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('RowRev2').width(60).height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
        }.width('100%').height(50)
        Flex({ direction: FlexDirection.ColumnReverse }) {
          Text('ColRev1').width('100%').height(40).backgroundColor(Color.Orange).textAlign(TextAlign.Center)
          Text('ColRev2').width('100%').height(40).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
        }.width('100%').height(100)
      }.width('100%').height(350)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Flex with All Wrap Modes Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column({ space: 10 }) {
        Flex({ wrap: FlexWrap.NoWrap }) {
          ForEach([1, 2, 3, 4, 5], (item: number) => {
            Text('NW' + item).width(70).height(40).backgroundColor(Color.Red).margin(3).textAlign(TextAlign.Center)
          })
        }.width('100%').height(50)
        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
            Text('W' + item).width(70).height(40).backgroundColor(Color.Green).margin(3).textAlign(TextAlign.Center)
          })
        }.width('100%').height(100)
        Flex({ wrap: FlexWrap.WrapReverse }) {
          ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
            Text('WR' + item).width(70).height(40).backgroundColor(Color.Blue).margin(3).textAlign(TextAlign.Center)
          })
        }.width('100%').height(100)
      }.width('100%').height(280)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)

    Divider().strokeWidth(2).color(Color.Gray)

    Column(undefined) {
      Text('Complete Layout Test Suite').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
      Column() {
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
          Stack({ alignContent: Alignment.Center }) {
            Text('S').width(50).height(45).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          }.width(70).height(65)
          Column() {
            Text('C1').width('100%').height(25).backgroundColor(Color.Green).textAlign(TextAlign.Center)
            Text('C2').width('100%').height(25).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          }.width(70).height(65)
          Row() {
            Text('R1').width(35).height(30).backgroundColor(Color.Yellow).textAlign(TextAlign.Center).textAlign(TextAlign.Center)
            Text('R2').width(35).height(30).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          }.width(70).height(65)
        }.width('100%')
        GridRow({ columns: 3, gutterX: 8, gutterY: 8 }) {
          ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
            GridCol() {
              Text('G' + item).width('100%').height(40).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
            }
          })
        }.width('100%').height(100)
        List({ space: 5 }) {
          ListItem() {
            Text('L1').width('100%').height(35).backgroundColor(Color.Orange).textAlign(TextAlign.Center)
          }
          ListItem() {
            Text('L2').width('100%').height(35).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
          }
        }.width('100%').height(90)
      }.width('100%').height(280)
    }.width('100%').margin({ top: 20 } as LocalizedMargin)
  }

  build() {
    NavDestination() {
      Column(undefined) {
      Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
        // 线段
        Text('dashed')
          .borderStyle(BorderStyle.Dashed).borderWidth(5).borderColor(0xAFEEEE).borderRadius(10)
          .width(70).height(70).textAlign(TextAlign.Center).fontSize(16)
        //实线1
        Text('Solid')
          .borderStyle(BorderStyle.Solid).borderColor(Color.Pink)
          .borderRadius(2)
          .borderWidth(2)
          .width(70).height(70).textAlign(TextAlign.Center).fontSize(16)
        //点线1
        Text('dotted1')
          .borderStyle(BorderStyle.Dotted).borderWidth(5).borderColor('#ff000000').borderRadius(10)
          .width(70).height(70).textAlign(TextAlign.Center).fontSize(16)
      }.width('100%').height(150)

      Text('.border')
        .fontSize(50)
        .width(300)
        .height(300)
        .borderWidth({ left: 3, right: 6, top: 10, bottom: 15 } as EdgeWidths )
        .borderColor($r('app.color.background'))
        .borderRadius({ topLeft: 10, topRight: 20, bottomLeft: 40, bottomRight: 80 } as BorderRadiuses )
        .textAlign(TextAlign.Center)

      Divider().strokeWidth(2).color(Color.Gray)

      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
        Text('padding test')
          .width(120).height(60)
          .padding(20)
          .backgroundColor(Color.Orange)
          .textAlign(TextAlign.Center)
        Text('margin test')
          .width(120).height(60)
          .margin({ left: 10, right: 10, top: 10, bottom: 10 } as LocalizedMargin)
          .backgroundColor(Color.Green)
          .textAlign(TextAlign.Center)
      }.width('100%').height(100)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Wrap Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceAround }) {
          ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
            Text('Item' + item)
              .width(80).height(50)
              .backgroundColor(Color.Blue)
              .margin(5)
              .textAlign(TextAlign.Center)
          })
        }.width('100%').height(200)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Row Layout Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Row({ space: 10 }) {
          Text('Row1').width(80).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Row2').width(80).height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
          Text('Row3').width(80).height(50).backgroundColor(Color.Cyan).textAlign(TextAlign.Center)
        }.width('100%').height(70)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Column Layout Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Column({ space: 10 }) {
          Text('Col1').width('100%').height(50).backgroundColor(Color.Pink).textAlign(TextAlign.Center)
          Text('Col2').width('100%').height(50).backgroundColor(Color.Purple).textAlign(TextAlign.Center)
          Text('Col3').width('100%').height(50).backgroundColor(Color.Brown).textAlign(TextAlign.Center)
        }.width('100%').height(200)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Stack Layout Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Stack({ alignContent: Alignment.Center }) {
          Text('Bottom').width(200).height(200).backgroundColor(Color.Gray).fontSize(30).textAlign(TextAlign.Center)
          Text('Middle').width(150).height(150).backgroundColor(Color.White).fontSize(25).textAlign(TextAlign.Center)
          Text('Top').width(100).height(100).backgroundColor(Color.Red).fontSize(20).textAlign(TextAlign.Center)
        }.width(220).height(220)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('GridRow/GridCol Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        GridRow({ columns: 3, gutterX: 10, gutterY: 10 }) {
          ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
            GridCol() {
              Text('Grid' + item)
                .width('100%').height(60)
                .backgroundColor(Color.Orange)
                .textAlign(TextAlign.Center)
            }
          })
        }.width('100%').height(250)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Align Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start }) {
          Text('Start').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Start').width(200).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Justify Content Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Center }) {
          Text('Center').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Center').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Center').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(60)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Blank Component Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Column(undefined) {
          Text('Top').width('100%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Blank().color(Color.Gray)
          Text('Bottom').width('100%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Position Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Stack() {
          Text('Base')
            .width(200).height(200)
            .backgroundColor(Color.Gray)
            .fontSize(30)
            .textAlign(TextAlign.Center)
          Text('Absolute')
            .width(80).height(40)
            .backgroundColor(Color.Red)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .position({ x: 60, y: 80 } as Position)
        }.width(220).height(220)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('List Component Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        List({ space: 10 }) {
          ForEach([1, 2, 3, 4, 5], (item: number) => {
            ListItem() {
              Text('List Item ' + item)
                .width('100%').height(50)
                .backgroundColor(Color.Orange)
                .textAlign(TextAlign.Center)
            }
          })
        }.width('100%').height(300)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Space Between Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
          Text('Item1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Item2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Item3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(60)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Space Evenly Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceEvenly }) {
          Text('Item1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Item2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Item3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(60)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Row Align Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Row({ verticalAlign: VerticalAlign.Top }) {
          Text('Top').width(60).height(30).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Top').width(60).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Top').width(60).height(70).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(80)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Column Align Items Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Column({ alignItems: HorizontalAlign.Center }) {
          Text('Center').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Center').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Center').width(200).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Nested Layout Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Column(undefined) {
          Row({ space: 10 }) {
            Text('R1').width(50).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
            Text('R2').width(50).height(50).backgroundColor(Color.Yellow).textAlign(TextAlign.Center)
          }.width('100%')
          Row({ space: 10 }) {
            Text('R3').width(50).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
            Text('R4').width(50).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
          }.width('100%')
        }.width('100%').height(120)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Border Edge Colors Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Edge Colors')
          .width(200).height(100)
          .borderWidth(5)
          .borderColor({ left: Color.Red, right: Color.Green, top: Color.Blue, bottom: Color.Yellow } as EdgeColors)
          .textAlign(TextAlign.Center)
          .fontSize(20)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Direction Column Reverse Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.ColumnReverse }) {
          Text('Item1').width('100%').height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Item2').width('100%').height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Item3').width('100%').height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Direction Row Reverse Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.RowReverse }) {
          Text('Item1').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Item2').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Item3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(60)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Stack Alignment Bottom Start Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Stack({ alignContent: Alignment.BottomStart }) {
          Text('Item1').width(100).height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Item2').width(80).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Item3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width(120).height(100)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Stack Alignment Top End Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Stack({ alignContent: Alignment.TopEnd }) {
          Text('Item1').width(100).height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Item2').width(80).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Item3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width(120).height(100)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('GridRow Columns 4 Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        GridRow({ columns: 4, gutterX: 5, gutterY: 5 }) {
          ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
            GridCol() {
              Text('G' + item)
                .width('100%').height(50)
                .backgroundColor(Color.Purple)
                .textAlign(TextAlign.Center)
            }
          })
        }.width('100%').height(180)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Padding All Sides Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Padding 20')
          .width(150).height(80)
          .padding(20)
          .backgroundColor(Color.Cyan)
          .textAlign(TextAlign.Center)
          .fontSize(18)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Margin All Sides Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Margin 15')
          .width(150).height(80)
          .margin(15)
          .backgroundColor(Color.Magenta)
          .textAlign(TextAlign.Center)
          .fontSize(18)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Item Align Stretch Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Stretch }) {
          Text('Stretch').width(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Stretch').width(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Stretch').width(60).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(100)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Row Horizontal Align Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Row() {
          Text('Left').width(80).height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Blank()
          Text('Right').width(80).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(60)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Column Vertical Align Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Column() {
          Text('Top').width('100%').height(50).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Blank()
          Text('Bottom').width('100%').height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('List Space Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        List({ space: 20 }) {
          ForEach([1, 2, 3], (item: number) => {
            ListItem() {
              Text('Space ' + item)
                .width('100%').height(60)
                .backgroundColor(Color.Orange)
                .textAlign(TextAlign.Center)
            }
          })
        }.width('100%').height(250)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Wrap No Wrap Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ wrap: FlexWrap.NoWrap }) {
          ForEach([1, 2, 3, 4, 5], (item: number) => {
            Text('NW' + item)
              .width(80).height(50)
              .backgroundColor(Color.Gray)
              .margin(5)
              .textAlign(TextAlign.Center)
          })
        }.width('100%').height(70)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Wrap Wrap Reverse Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ wrap: FlexWrap.WrapReverse }) {
          ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
            Text('WR' + item)
              .width(80).height(50)
              .backgroundColor(Color.Brown)
              .margin(5)
              .textAlign(TextAlign.Center)
          })
        }.width('100%').height(180)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Stack Alignment Center Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Stack({ alignContent: Alignment.Center }) {
          Text('C1').width(120).height(70).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('C2').width(100).height(60).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('C3').width(80).height(50).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width(140).height(100)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Row Vertical Align Center Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Row({ verticalAlign: VerticalAlign.Center }) {
          Text('Center').width(60).height(30).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Center').width(60).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Center').width(60).height(70).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(80)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Column Horizontal Align Start Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Column({ alignItems: HorizontalAlign.Start }) {
          Text('Start').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Start').width(200).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Column Horizontal Align End Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Column({ alignItems: HorizontalAlign.End }) {
          Text('End').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('End').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('End').width(200).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Justify Content Start Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Start }) {
          Text('Start').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Start').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Start').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(60)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Justify Content End Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.End }) {
          Text('End').width(60).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('End').width(60).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('End').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(60)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Border Width All Sides Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Border 10')
          .width(180).height(100)
          .borderWidth(10)
          .borderColor(Color.Black)
          .textAlign(TextAlign.Center)
          .fontSize(18)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Border Radius All Corners Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Radius 25')
          .width(180).height(100)
          .borderRadius(25)
          .backgroundColor(Color.Yellow)
          .textAlign(TextAlign.Center)
          .fontSize(18)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('GridRow Columns 2 Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        GridRow({ columns: 2, gutterX: 15, gutterY: 15 }) {
          ForEach([1, 2, 3, 4], (item: number) => {
            GridCol() {
              Text('Grid' + item)
                .width('100%').height(70)
                .backgroundColor(Color.Teal)
                .textAlign(TextAlign.Center)
            }
          })
        }.width('100%').height(200)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Align Items End Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.End }) {
          Text('End').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('End').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('End').width(200).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Flex Align Items Center Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
          Text('Center').width(100).height(40).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Center').width(150).height(40).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Center').width(200).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(150)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Stack Alignment Bottom End Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Stack({ alignContent: Alignment.BottomEnd }) {
          Text('BE1').width(100).height(60).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('BE2').width(80).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('BE3').width(60).height(40).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width(120).height(100)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Row Vertical Align Bottom Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Row({ verticalAlign: VerticalAlign.Bottom }) {
          Text('Bottom').width(60).height(30).backgroundColor(Color.Red).textAlign(TextAlign.Center)
          Text('Bottom').width(60).height(50).backgroundColor(Color.Green).textAlign(TextAlign.Center)
          Text('Bottom').width(60).height(70).backgroundColor(Color.Blue).textAlign(TextAlign.Center)
        }.width('100%').height(80)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Border Style Dotted Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Dotted Border')
          .width(180).height(100)
          .borderStyle(BorderStyle.Dotted)
          .borderWidth(8)
          .borderColor(Color.Purple)
          .textAlign(TextAlign.Center)
          .fontSize(18)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Border Style Solid Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Solid Border')
          .width(180).height(100)
          .borderStyle(BorderStyle.Solid)
          .borderWidth(8)
          .borderColor(Color.Orange)
          .textAlign(TextAlign.Center)
          .fontSize(18)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      Divider().strokeWidth(2).color(Color.Gray)

      Column(undefined) {
        Text('Border Style Dashed Test').fontSize(20).margin({ bottom: 10 } as LocalizedMargin)
        Text('Dashed Border')
          .width(180).height(100)
          .borderStyle(BorderStyle.Dashed)
          .borderWidth(8)
          .borderColor(Color.Pink)
          .textAlign(TextAlign.Center)
          .fontSize(18)
      }.width('100%').margin({ top: 20 } as LocalizedMargin)

      this.addLayoutMoreTest()

    }
    }
    .title('布局基础功能测试用例001')
  }
}