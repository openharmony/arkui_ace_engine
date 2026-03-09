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

    }
    }
    .title('布局基础功能测试用例001')
  }
}