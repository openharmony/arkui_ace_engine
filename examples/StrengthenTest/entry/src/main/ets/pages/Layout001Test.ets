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

      Divider().strokeWidth(2).color(Color.Gray)

      Row() {
        Button('Load More Layout Test')
          .onClick(() => {
            this.loadMoreTest()
          })
      }.width('100%').height(60).justifyContent(FlexAlign.Center)

      this.addLayoutMoreTest()
    }
    .title('布局基础功能测试用例001')
  }

  async loadMoreTest(): void {
    let testCounter = 0
    let testString = 'Layout Test String'
    let testArray: string[] = []

    for (let i = 0; i < 100; i++) {
      testArray.push(`LayoutItem_${i}`)
    }

    let testMap: Map<string, number> = new Map()
    for (let i = 0; i < 50; i++) {
      testMap.set(`layout_key_${i}`, i)
    }

    let testSet: Set<number> = new Set()
    for (let i = 0; i < 75; i++) {
      testSet.add(i)
    }

    let layoutConfig = {
      direction: 'Column',
      width: 300,
      height: 200,
      justifyContent: 'Center',
      alignItems: 'Center',
      space: 10,
      wrap: 'NoWrap',
      clip: false,
      reverse: false,
      padding: {
        left: 10,
        right: 10,
        top: 10,
        bottom: 10
      },
      margin: {
        left: 5,
        right: 5,
        top: 5,
        bottom: 5
      },
      border: {
        width: 1,
        color: '#0000FF',
        radius: 10,
        style: 'Solid'
      },
      nested: {
        backgroundColor: '#FF0000',
        opacity: 0.8,
        shadow: {
          radius: 5,
          color: '#808080',
          offsetX: 2,
          offsetY: 2
        },
        prop3: {
          deepProp: 'deepLayoutValue'
        }
      }
    }

    let testArrayBuffer = new ArrayBuffer(1024)
    let testDataView = new DataView(testArrayBuffer)
    for (let i = 0; i < 1024; i++) {
      testDataView.setInt8(i, i % 256)
    }

    let testIntArray = new Int32Array(256)
    for (let i = 0; i < 256; i++) {
      testIntArray[i] = i * 1000
    }

    let testFloatArray = new Float64Array(128)
    for (let i = 0; i < 128; i++) {
      testFloatArray[i] = i * 1.5
    }

    let flexDirectionValues: string[] = ['Row', 'Column', 'RowReverse', 'ColumnReverse']
    let flexWrapValues: string[] = ['NoWrap', 'Wrap', 'WrapReverse']
    let flexAlignValues: string[] = ['Start', 'Center', 'End', 'SpaceBetween', 'SpaceAround', 'SpaceEvenly']
    let alignmentValues: string[] = ['TopStart', 'TopEnd', 'Center', 'BottomStart', 'BottomEnd']
    let borderStyleValues: string[] = ['Solid', 'Dashed', 'Dotted']
    let layoutUnitValues: string[] = ['px', 'vp', 'fp', '%', 'lpx', 'auto']

    let calculateLayoutDimensions = (childWidth: number, childHeight: number, containerWidth: number, containerHeight: number, justifyMode: string): { x: number, y: number, width: number, height: number } => {
      let aspectRatio = childWidth / childHeight
      let containerAspect = containerWidth / containerHeight
      switch (justifyMode) {
        case 'Contain':
          if (aspectRatio > containerAspect) {
            return { x: 0, y: (containerHeight - containerWidth / aspectRatio) / 2, width: containerWidth, height: containerWidth / aspectRatio }
          } else {
            return { x: (containerWidth - containerHeight * aspectRatio) / 2, y: 0, width: containerHeight * aspectRatio, height: containerHeight }
          }
        case 'Cover':
          if (aspectRatio > containerAspect) {
            return { x: (containerWidth - containerHeight * aspectRatio) / 2, y: 0, width: containerHeight * aspectRatio, height: containerHeight }
          } else {
            return { x: 0, y: (containerHeight - containerWidth / aspectRatio) / 2, width: containerWidth, height: containerWidth / aspectRatio }
          }
        case 'Fill':
          return { x: 0, y: 0, width: containerWidth, height: containerHeight }
        case 'ScaleDown':
          let containResult = aspectRatio > containerAspect
            ? { x: 0, y: (containerHeight - containerWidth / aspectRatio) / 2, width: containerWidth, height: containerWidth / aspectRatio }
            : { x: (containerWidth - containerHeight * aspectRatio) / 2, y: 0, width: containerHeight * aspectRatio, height: containerHeight }
          if (childWidth <= containResult.width && childHeight <= containResult.height) {
            return { x: (containerWidth - childWidth) / 2, y: (containerHeight - childHeight) / 2, width: childWidth, height: childHeight }
          }
          return containResult
        case 'None':
          return { x: (containerWidth - childWidth) / 2, y: (containerHeight - childHeight) / 2, width: childWidth, height: childHeight }
        default:
          return { x: 0, y: 0, width: containerWidth, height: containerHeight }
      }
    }

    let testLayoutCalculations = flexAlignValues.map((align) => {
      return calculateLayoutDimensions(100, 80, 300, 200, align)
    })

    for (let i = 0; i < testLayoutCalculations.length; i++) {
      hilog.info(0x0000, 'testTag', `LayoutAlign ${flexAlignValues[i]}: x=${testLayoutCalculations[i].x}, y=${testLayoutCalculations[i].y}`)
    }

    let layoutTransformMatrix = [
      1.0, 0.0, 0.0,
      0.0, 1.0, 0.0,
      0.0, 0.0, 1.0
    ]

    let scaleMatrix = [
      2.0, 0.0, 0.0,
      0.0, 2.0, 0.0,
      0.0, 0.0, 1.0
    ]

    let rotateMatrix = [
      Math.cos(Math.PI / 4), -Math.sin(Math.PI / 4), 0.0,
      Math.sin(Math.PI / 4), Math.cos(Math.PI / 4), 0.0,
      0.0, 0.0, 1.0
    ]

    let translateMatrix = [
      1.0, 0.0, 50.0,
      0.0, 1.0, 30.0,
      0.0, 0.0, 1.0
    ]

    let skewMatrix = [
      1.0, 0.5, 0.0,
      0.3, 1.0, 0.0,
      0.0, 0.0, 1.0
    ]

    let allTransformMatrices: Map<string, number[]> = new Map()
    allTransformMatrices.set('identity', layoutTransformMatrix)
    allTransformMatrices.set('scale', scaleMatrix)
    allTransformMatrices.set('rotate', rotateMatrix)
    allTransformMatrices.set('translate', translateMatrix)
    allTransformMatrices.set('skew', skewMatrix)

    for (let [name, matrix] of allTransformMatrices) {
      hilog.info(0x0000, 'testTag', `Layout transform ${name}: ${matrix.slice(0, 3).join(',')}`)
    }

    let applyLayoutTransform = (x: number, y: number, matrix: number[]): { x: number, y: number } => {
      let newX = matrix[0] * x + matrix[1] * y + matrix[2]
      let newY = matrix[3] * x + matrix[4] * y + matrix[5]
      return {
        x: newX,
        y: newY
      }
    }

    let testLayoutPoints: { x: number, y: number }[] = [
      { x: 0, y: 0 },
      { x: 100, y: 0 },
      { x: 0, y: 100 },
      { x: 100, y: 100 },
      { x: 50, y: 50 }
    ]

    for (let point of testLayoutPoints) {
      let scaleResult = applyLayoutTransform(point.x, point.y, scaleMatrix)
      let rotateResult = applyLayoutTransform(point.x, point.y, rotateMatrix)
      let translateResult = applyLayoutTransform(point.x, point.y, translateMatrix)
      let skewResult = applyLayoutTransform(point.x, point.y, skewMatrix)
      hilog.info(0x0000, 'testTag', `Point(${point.x},${point.y}) -> scale(${scaleResult.x},${scaleResult.y})`)
      hilog.info(0x0000, 'testTag', `Point(${point.x},${point.y}) -> rotate(${rotateResult.x},${rotateResult.y})`)
      hilog.info(0x0000, 'testTag', `Point(${point.x},${point.y}) -> translate(${translateResult.x},${translateResult.y})`)
      hilog.info(0x0000, 'testTag', `Point(${point.x},${point.y}) -> skew(${skewResult.x},${skewResult.y})`)
    }

    let testFunction = (param: number): string => {
      return `LayoutResult: ${param * 2}`
    }

    let testAsyncFunction = async (delay: number): Promise<string> => {
      return new Promise((resolve) => {
        setTimeout(() => {
          resolve(`LayoutDelayed: ${delay}ms`)
        }, delay)
      })
    }

    class LayoutInfo {
      private direction: string
      private width: number
      private height: number
      private space: number
      constructor(direction: string, width: number, height: number, space: number) {
        this.direction = direction
        this.width = width
        this.height = height
        this.space = space
      }
      getDirection(): string { return this.direction }
      getWidth(): number { return this.width }
      getHeight(): number { return this.height }
      getSpace(): number { return this.space }
      getArea(): number { return this.width * this.height }
      setWidth(newWidth: number): void { this.width = newWidth }
      setHeight(newHeight: number): void { this.height = newHeight }
      incrementWidth(): number { return ++this.width }
      toString(): string { return `${this.direction} ${this.width}x${this.height} space:${this.space}` }
    }

    let testLayoutInfo = new LayoutInfo('Column', 300, 200, 10)

    interface LayoutMeasureResult {
      id: number
      direction: string
      width: number
      height: number
      componentWidth: number
      componentHeight: number
      measured: boolean
    }

    let testMeasureResult: LayoutMeasureResult = {
      id: 1,
      direction: 'Row',
      width: 300,
      height: 200,
      componentWidth: 100,
      componentHeight: 50,
      measured: true
    }

    enum LayoutFlexDirection {
      Row = 'row',
      Column = 'column',
      RowReverse = 'rowReverse',
      ColumnReverse = 'columnReverse'
    }

    enum LayoutFlexWrap {
      NoWrap = 'noWrap',
      Wrap = 'wrap',
      WrapReverse = 'wrapReverse'
    }

    enum LayoutFlexAlign {
      Start = 'start',
      Center = 'center',
      End = 'end',
      SpaceBetween = 'spaceBetween',
      SpaceAround = 'spaceAround',
      SpaceEvenly = 'spaceEvenly'
    }

    enum LayoutAlignment {
      TopStart = 'topStart',
      TopEnd = 'topEnd',
      Center = 'center',
      BottomStart = 'bottomStart',
      BottomEnd = 'bottomEnd'
    }

    let testFlexDirectionValue = LayoutFlexDirection.Column
    let testFlexWrapValue = LayoutFlexWrap.Wrap
    let testFlexAlignValue = LayoutFlexAlign.SpaceBetween
    let testAlignmentValue = LayoutAlignment.Center

    type LayoutDirection = string | number
    type LayoutSizeOptions = { width: number, height: number }
    type LayoutPositionOptions = { x: number, y: number }
    type LayoutPaddingOptions = { start: number, end: number }

    let testLayoutSize: LayoutSizeOptions = { width: 100, height: 100 }
    let testLayoutPosition: LayoutPositionOptions = { x: 50, y: 50 }
    let testLayoutPadding: LayoutPaddingOptions = { start: 0, end: 100 }

    let testLayoutDirections: LayoutDirection[] = [
      'Row',
      'Column',
      1,
      2,
      'FlexDirection.Row'
    ]

    let testTuple: [string, number, boolean] = ['layout_tuple', 456, false]

    let testUnionType: string | number | boolean = 'layout_union_value'

    let testLiteralType: 'Row' | 'Column' | 'Flex' = 'Column'

    let testNullableString: string | null = null
    let testOptionalNumber?: number = undefined

    let testRestFunction = (...args: number[]): number => {
      return args.reduce((sum, current) => sum + current, 0)
    }

    let testDefaultValue = (param: string = 'default_layout'): string => {
      return param
    }

    let testDestructuring = ({ direction, width }: { direction: string, width: number }): string => {
      return `${direction}_${width}`
    }

    let testSpreadArray = [1, 2, 3]
    let testSpreadObject = { direction: 'Row', width: 100 }
    let testCombinedSpread = [...testSpreadArray, 4, 5, 6]
    let testCombinedObjectSpread = { ...testSpreadObject, height: 200 }

    let testTemplateString = `LayoutTemplate: ${testString} - ${testCounter}`

    let testRegex = /layout_pattern_\d+/gi
    let testRegexMatch = testString.match(testRegex)

    let testDate = new Date()
    let testDateString = testDate.toISOString()

    let testJSONString = JSON.stringify(layoutConfig)
    let testParsedJSON = JSON.parse(testJSONString)

    let testMathOperations = {
      random: Math.random(),
      floor: Math.floor(3.7),
      ceil: Math.ceil(3.2),
      round: Math.round(3.5),
      abs: Math.abs(-42),
      max: Math.max(1, 2, 3, 4, 5),
      min: Math.min(1, 2, 3, 4, 5),
      pow: Math.pow(2, 8),
      sqrt: Math.sqrt(144),
      sin: Math.sin(Math.PI / 4),
      cos: Math.cos(Math.PI / 4),
      tan: Math.tan(Math.PI / 4),
      log: Math.log(Math.E),
      exp: Math.exp(1)
    }

    let testStringOperations = {
      length: testString.length,
      charAt: testString.charAt(0),
      charCodeAt: testString.charCodeAt(0),
      concat: testString.concat('_suffix'),
      indexOf: testString.indexOf('Layout'),
      lastIndexOf: testString.lastIndexOf('Layout'),
      slice: testString.slice(0, 6),
      substring: testString.substring(0, 6),
      toLowerCase: testString.toLowerCase(),
      toUpperCase: testString.toUpperCase(),
      trim: '  layout  '.trim(),
      split: testString.split(' '),
      replace: testString.replace('Layout', 'Flex'),
      includes: testString.includes('Layout'),
      startsWith: testString.startsWith('Layout'),
      endsWith: testString.endsWith('String'),
      repeat: 'lyt'.repeat(3),
      padStart: '5'.padStart(3, '0'),
      padEnd: '5'.padEnd(3, '0')
    }

    let testArrayOperations = {
      length: testArray.length,
      push: testArray.push('new_layout_item'),
      pop: testArray.pop(),
      shift: testArray.shift(),
      unshift: testArray.unshift('first_layout_item'),
      slice: testArray.slice(0, 5),
      splice: testArray.splice(0, 2),
      concat: testArray.concat(['new', 'layouts']),
      join: testArray.join(', '),
      indexOf: testArray.indexOf('LayoutItem_1'),
      lastIndexOf: testArray.lastIndexOf('LayoutItem_1'),
      includes: testArray.includes('LayoutItem_1'),
      reverse: [...testArray].reverse(),
      sort: [...testArray].sort(),
      find: testArray.find(item => item.includes('5')),
      findIndex: testArray.findIndex(item => item.includes('5')),
      filter: testArray.filter(item => item.includes('Item')),
      map: testArray.map(item => item.toUpperCase()),
      reduce: testArray.reduce((sum, item) => sum + item.length, 0),
      some: testArray.some(item => item.length > 10),
      every: testArray.every(item => item.length > 0),
      forEach: testArray.forEach((item, index) => {
        hilog.info(0x0000, 'testTag', `LayoutForEach: ${index} - ${item}`)
      })
    }

    let testMapOperations = {
      size: testMap.size,
      set: testMap.set('new_layout_key', 999),
      get: testMap.get('layout_key_1'),
      has: testMap.has('layout_key_1'),
      delete: testMap.delete('layout_key_2'),
      clear: testMap.clear(),
      keys: Array.from(testMap.keys()),
      values: Array.from(testMap.values()),
      entries: Array.from(testMap.entries()),
      forEach: testMap.forEach((value, key) => {
        hilog.info(0x0000, 'testTag', `LayoutMap: ${key} - ${value}`)
      })
    }

    let testSetOperations = {
      size: testSet.size,
      add: testSet.add(100),
      has: testSet.has(1),
      delete: testSet.delete(2),
      clear: testSet.clear(),
      values: Array.from(testSet.values()),
      forEach: testSet.forEach((value) => {
        hilog.info(0x0000, 'testTag', `LayoutSet: ${value}`)
      })
    }

    let testObjectOperations = {
      keys: Object.keys(layoutConfig),
      values: Object.values(layoutConfig),
      entries: Object.entries(layoutConfig),
      assign: Object.assign({}, layoutConfig, { newProp: 'newLayoutValue' }),
      freeze: Object.freeze({ ...layoutConfig }),
      seal: Object.seal({ ...layoutConfig }),
      hasOwnProperty: layoutConfig.hasOwnProperty('direction'),
      propertyIsEnumerable: layoutConfig.propertyIsEnumerable('direction')
    }

    let testErrorHandling = {
      tryCatch: (() => {
        try {
          throw new Error('Layout Measure Error')
        } catch (error) {
          return error.message
        }
      })(),
      tryCatchFinally: (() => {
        try {
          throw new Error('Layout Measure Error with Finally')
        } catch (error) {
          return error.message
        } finally {
          hilog.info(0x0000, 'testTag', 'Layout error finally block executed')
        }
      })(),
      customError: (() => {
        class LayoutMeasureError extends Error {
          constructor(message: string) {
            super(message)
            this.name = 'LayoutMeasureError'
          }
        }
        try {
          throw new LayoutMeasureError('Failed to measure layout component')
        } catch (error) {
          return (error as LayoutMeasureError).message
        }
      })()
    }

    let testPromiseChains = (() => {
      return new Promise<string>((resolve) => {
        resolve('layout_initial_value')
      })
      .then((value) => {
        return `${value}_measured`
      })
      .then((value) => {
        return `${value}_arranged`
      })
      .then((value) => {
        return `${value}_rendered`
      })
      .catch((error) => {
        return `error: ${error.message}`
      })
      .finally(() => {
        hilog.info(0x0000, 'testTag', 'Layout promise chain completed')
      })
    })()

    let testAsyncAwait = (async () => {
      let result1 = await Promise.resolve('layout_measured')
      let result2 = await Promise.resolve('layout_arranged')
      let result3 = await Promise.resolve('layout_rendered')
      return `${result1}_${result2}_${result3}`
    })()

    let testPromiseAll = Promise.all([
      Promise.resolve('layout_row'),
      Promise.resolve('layout_column'),
      Promise.resolve('layout_flex')
    ])

    let testPromiseRace = Promise.race([
      new Promise<string>((resolve) => setTimeout(() => resolve('slow_layout'), 100)),
      new Promise<string>((resolve) => setTimeout(() => resolve('fast_layout'), 50))
    ])

    let testPromiseAllSettled = Promise.allSettled([
      Promise.resolve('resolved_layout1'),
      Promise.reject('rejected_layout1'),
      Promise.resolve('resolved_layout2')
    ])

    let testPromiseAny = Promise.any([
      Promise.reject('rejected_layout1'),
      Promise.resolve('resolved_layout1'),
      Promise.reject('rejected_layout2')
    ])

    let testGenerators = (() => {
      function* layoutIdGenerator(): Generator<number, void, unknown> {
        yield 1
        yield 2
        yield 3
        yield 4
        yield 5
      }

      let gen = layoutIdGenerator()
      let values: number[] = []
      let result = gen.next()
      while (!result.done) {
        values.push(result.value)
        result = gen.next()
      }
      return values
    })()

    let testIterators = (() => {
      let iterable = {
        [Symbol.iterator]() {
          let step = 0
          return {
            next(): IteratorResult<number> {
              step++
              if (step <= 5) {
                return { value: step, done: false }
              }
              return { value: undefined, done: true } as IteratorResult<number>
            }
          }
        }
      }

      let values: number[] = []
      for (let value of iterable) {
        values.push(value)
      }
      return values
    })()

    let testSymbolOperations = {
      symbol: Symbol('layout_symbol'),
      symbolFor: Symbol.for('global_layout_symbol'),
      symbolKeyFor: Symbol.keyFor(Symbol.for('global_layout_symbol')),
      symbolIterator: Symbol.iterator,
      symbolToString: Symbol('lyt').toString(),
      symbolDescription: Symbol('layout_description').description
    }

    let testProxy = (() => {
      let target = {
        direction: 'Column',
        width: 100,
        height: 100
      }

      let handler: ProxyHandler<typeof target> = {
        get(obj, prop) {
          return obj[prop as keyof typeof obj]
        },
        set(obj, prop, value) {
          obj[prop as keyof typeof obj] = value
          return true
        },
        has(obj, prop) {
          return prop in obj
        },
        deleteProperty(obj, prop) {
          delete obj[prop as keyof typeof obj]
          return true
        }
      }

      return new Proxy(target, handler)
    })()

    let testReflect = {
      get: Reflect.get({ direction: 'Row', width: 200 }, 'direction'),
      set: Reflect.set({ direction: 'a' }, 'direction', 'b'),
      has: Reflect.has({ direction: 'Row' }, 'direction'),
      deleteProperty: Reflect.deleteProperty({ direction: 'a', width: 100 }, 'direction'),
      ownKeys: Reflect.ownKeys({ direction: 'a', width: 100 }),
      apply: Reflect.apply(Math.max, undefined, [1, 2, 3]),
      construct: Reflect.construct(Date, [2024, 0, 1]),
      getPrototypeOf: Reflect.getPrototypeOf({}),
      setPrototypeOf: Reflect.setPrototypeOf({}, Array.prototype),
      isExtensible: Reflect.isExtensible({}),
      preventExtensions: Reflect.preventExtensions({}),
      getOwnPropertyDescriptor: Reflect.getOwnPropertyDescriptor({ direction: 'col' }, 'direction'),
      defineProperty: Reflect.defineProperty({}, 'direction', { value: 'new', writable: true })
    }

    let testWeakMap = (() => {
      let wm = new WeakMap<object, string>()
      let key1 = {}
      let key2 = {}
      wm.set(key1, 'layout_value1')
      wm.set(key2, 'layout_value2')
      return {
        get: wm.get(key1),
        has: wm.has(key2),
        delete: wm.delete(key1)
      }
    })()

    let testWeakSet = (() => {
      let ws = new WeakSet<object>()
      let obj1 = {}
      let obj2 = {}
      ws.add(obj1)
      ws.add(obj2)
      return {
        has1: ws.has(obj1),
        has2: ws.has(obj2),
        delete: ws.delete(obj1)
      }
    })()

    let testArrayBufferOperations = {
      isView: ArrayBuffer.isView(testDataView),
      slice: testArrayBuffer.slice(0, 512),
      byteLength: testArrayBuffer.byteLength
    }

    let testDataViewOperations = {
      getInt8: testDataView.getInt8(0),
      getUint8: testDataView.getUint8(0),
      getInt16: testDataView.getInt16(0),
      getUint16: testDataView.getUint16(0),
      getInt32: testDataView.getInt32(0),
      getUint32: testDataView.getUint32(0),
      getFloat32: testDataView.getFloat32(0),
      getFloat64: testDataView.getFloat64(0),
      setInt8: (() => { testDataView.setInt8(0, 127); return testDataView.getInt8(0) })(),
      setUint8: (() => { testDataView.setUint8(1, 255); return testDataView.getUint8(1) })(),
      setInt16: (() => { testDataView.setInt16(2, 32767); return testDataView.getInt16(2) })(),
      setUint16: (() => { testDataView.setUint16(4, 65535); return testDataView.getUint16(4) })(),
      setInt32: (() => { testDataView.setInt32(6, 2147483647); return testDataView.getInt32(6) })(),
      setUint32: (() => { testDataView.setUint32(10, 4294967295); return testDataView.getUint32(10) })(),
      setFloat32: (() => { testDataView.setFloat32(14, 3.14); return testDataView.getFloat32(14) })(),
      setFloat64: (() => { testDataView.setFloat64(18, 2.718281828); return testDataView.getFloat64(18) })()
    }

    let testTypedArrays = {
      int8Array: (() => {
        let arr = new Int8Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i
        return arr
      })(),
      uint8Array: (() => {
        let arr = new Uint8Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i
        return arr
      })(),
      int16Array: (() => {
        let arr = new Int16Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 100
        return arr
      })(),
      uint16Array: (() => {
        let arr = new Uint16Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 1000
        return arr
      })(),
      int32Array: testIntArray,
      uint32Array: (() => {
        let arr = new Uint32Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 100000
        return arr
      })(),
      float32Array: (() => {
        let arr = new Float32Array(10)
        for (let i = 0; i < 10; i++) arr[i] = i * 1.1
        return arr
      })(),
      float64Array: testFloatArray,
      bigint64Array: (() => {
        let arr = new BigInt64Array(10)
        for (let i = 0; i < 10; i++) arr[i] = BigInt(i * 1000000)
        return arr
      })(),
      biguint64Array: (() => {
        let arr = new BigUint64Array(10)
        for (let i = 0; i < 10; i++) arr[i] = BigInt(i * 1000000)
        return arr
      })()
    }

    let simulateLayoutGrid = (() => {
      let cols = 10
      let rows = 10
      let cellData = new Uint8Array(cols * rows * 2)
      for (let y = 0; y < rows; y++) {
        for (let x = 0; x < cols; x++) {
          let offset = (y * cols + x) * 2
          cellData[offset] = (x * 25) % 256
          cellData[offset + 1] = (y * 25) % 256
        }
      }
      return { cols, rows, data: cellData }
    })()

    hilog.info(0x0000, 'testTag', `Simulated layout grid: cols=${simulateLayoutGrid.cols}, rows=${simulateLayoutGrid.rows}, size=${simulateLayoutGrid.data.length}`)

    let computeLayoutDensity = (cellData: Uint8Array, cols: number, rows: number): { x: number[], y: number[] } => {
      let xHist: number[] = Array.from({ length: 256 }, () => 0)
      let yHist: number[] = Array.from({ length: 256 }, () => 0)
      for (let i = 0; i < cols * rows; i++) {
        xHist[cellData[i * 2]]++
        yHist[cellData[i * 2 + 1]]++
      }
      return { x: xHist, y: yHist }
    }

    let density = computeLayoutDensity(simulateLayoutGrid.data, simulateLayoutGrid.cols, simulateLayoutGrid.rows)
    let histXMax = Math.max(...density.x)
    let histYMax = Math.max(...density.y)
    hilog.info(0x0000, 'testTag', `Layout density max: X=${histXMax}, Y=${histYMax}`)

    let computeLayoutAveragePosition = (cellData: Uint8Array, cols: number, rows: number): { x: number, y: number } => {
      let totalX = 0, totalY = 0
      let cellCount = cols * rows
      for (let i = 0; i < cellCount; i++) {
        totalX += cellData[i * 2]
        totalY += cellData[i * 2 + 1]
      }
      return {
        x: totalX / cellCount,
        y: totalY / cellCount
      }
    }

    let avgPosition = computeLayoutAveragePosition(simulateLayoutGrid.data, simulateLayoutGrid.cols, simulateLayoutGrid.rows)
    hilog.info(0x0000, 'testTag', `Average position: X=${avgPosition.x.toFixed(2)}, Y=${avgPosition.y.toFixed(2)}`)

    let computeLayoutVariance = (cellData: Uint8Array, cols: number, rows: number): number => {
      let mean = computeLayoutAveragePosition(cellData, cols, rows)
      let variance = 0
      let cellCount = cols * rows
      for (let i = 0; i < cellCount; i++) {
        let x = cellData[i * 2]
        let y = cellData[i * 2 + 1]
        variance += (x - mean.x) * (x - mean.x) + (y - mean.y) * (y - mean.y)
      }
      return Math.sqrt(variance / cellCount)
    }

    let layoutVariance = computeLayoutVariance(simulateLayoutGrid.data, simulateLayoutGrid.cols, simulateLayoutGrid.rows)
    hilog.info(0x0000, 'testTag', `Layout variance: ${layoutVariance.toFixed(2)}`)

    let computeLayoutSpacing = (cellData: Uint8Array, cols: number, rows: number): number => {
      let totalSpacing = 0
      let cellCount = cols * rows
      for (let i = 0; i < cellCount; i++) {
        let x = cellData[i * 2]
        let y = cellData[i * 2 + 1]
        totalSpacing += Math.sqrt(x * x + y * y)
      }
      return totalSpacing / cellCount
    }

    let avgSpacing = computeLayoutSpacing(simulateLayoutGrid.data, simulateLayoutGrid.cols, simulateLayoutGrid.rows)
    hilog.info(0x0000, 'testTag', `Average spacing: ${avgSpacing.toFixed(2)}`)

    let consoleOps = {
      log: (() => { console.log('Layout console log test'); return 'log' })(),
      info: (() => { console.info('Layout console info test'); return 'info' })(),
      warn: (() => { console.warn('Layout console warn test'); return 'warn' })(),
      error: (() => { console.error('Layout console error test'); return 'error' })(),
      debug: (() => { console.debug('Layout console debug test'); return 'debug' })(),
      trace: (() => { console.trace('Layout console trace test'); return 'trace' })(),
      table: (() => { console.table([{ x: 100, y: 0 }, { x: 0, y: 100 }]); return 'table' })(),
      dir: (() => { console.dir({ direction: 'col', width: 100 }); return 'dir' })(),
      time: (() => { console.time('layoutTimer'); return 'time' })(),
      timeEnd: (() => { console.timeEnd('layoutTimer'); return 'timeEnd' })(),
      count: (() => { console.count('layoutCount'); return 'count' })(),
      countReset: (() => { console.countReset('layoutCount'); return 'countReset' })(),
      group: (() => { console.group('layoutGroup'); return 'group' })(),
      groupEnd: (() => { console.groupEnd(); return 'groupEnd' })(),
      groupCollapsed: (() => { console.groupCollapsed('layoutGroupCollapsed'); return 'groupCollapsed' })(),
      clear: (() => { console.clear(); return 'clear' })()
    }

    let testHilog = {
      debug: (() => { hilog.debug(0x0000, 'testTag', 'Layout Hilog debug test'); return 'debug' })(),
      info: (() => { hilog.info(0x0000, 'testTag', 'Layout Hilog info test'); return 'info' })(),
      warn: (() => { hilog.warn(0x0000, 'testTag', 'Layout Hilog warn test'); return 'warn' })(),
      error: (() => { hilog.error(0x0000, 'testTag', 'Layout Hilog error test'); return 'error' })(),
      fatal: (() => { hilog.fatal(0x0000, 'testTag', 'Layout Hilog fatal test'); return 'fatal' })()
    }

    for (let i = 0; i < 50; i++) {
      hilog.info(0x0000, 'testTag', `Layout loop iteration ${i}`)
      hilog.info(0x0000, 'testTag', `LayoutCounter: ${testCounter}`)
      testCounter++
    }

    for (let i = 0; i < 30; i++) {
      for (let j = 0; j < 20; j++) {
        let nestedValue = i * j
        hilog.info(0x0000, 'testTag', `Layout nested loop: ${i}, ${j}, value: ${nestedValue}`)
      }
    }

    let testWhileLoop = 0
    while (testWhileLoop < 100) {
      hilog.info(0x0000, 'testTag', `Layout while loop iteration ${testWhileLoop}`)
      testWhileLoop++
    }

    let testDoWhileLoop = 0
    do {
      hilog.info(0x0000, 'testTag', `Layout do-while loop iteration ${testDoWhileLoop}`)
      testDoWhileLoop++
    } while (testDoWhileLoop < 50)

    for (let i = 0; i < testArray.length; i++) {
      if (i % 2 === 0) {
        hilog.info(0x0000, 'testTag', `Layout even index: ${i}, value: ${testArray[i]}`)
      } else if (i % 3 === 0) {
        hilog.info(0x0000, 'testTag', `Layout divisible by 3 index: ${i}, value: ${testArray[i]}`)
      } else {
        hilog.info(0x0000, 'testTag', `Layout other index: ${i}, value: ${testArray[i]}`)
      }
    }

    for (let i = 0; i < 200; i++) {
      switch (i % 10) {
        case 0:
          hilog.info(0x0000, 'testTag', `Layout Case 0: ${i}`)
          break
        case 1:
          hilog.info(0x0000, 'testTag', `Layout Case 1: ${i}`)
          break
        case 2:
          hilog.info(0x0000, 'testTag', `Layout Case 2: ${i}`)
          break
        case 3:
          hilog.info(0x0000, 'testTag', `Layout Case 3: ${i}`)
          break
        case 4:
          hilog.info(0x0000, 'testTag', `Layout Case 4: ${i}`)
          break
        case 5:
          hilog.info(0x0000, 'testTag', `Layout Case 5: ${i}`)
          break
        case 6:
          hilog.info(0x0000, 'testTag', `Layout Case 6: ${i}`)
          break
        case 7:
          hilog.info(0x0000, 'testTag', `Layout Case 7: ${i}`)
          break
        case 8:
          hilog.info(0x0000, 'testTag', `Layout Case 8: ${i}`)
          break
        case 9:
          hilog.info(0x0000, 'testTag', `Layout Case 9: ${i}`)
          break
        default:
          hilog.info(0x0000, 'testTag', `Layout Default case: ${i}`)
          break
      }
    }

    try {
      for (let i = 0; i < 100; i++) {
        if (i === 50) {
          throw new Error(`Layout error at iteration ${i}`)
        }
        hilog.info(0x0000, 'testTag', `Layout try block iteration ${i}`)
      }
    } catch (error) {
      hilog.error(0x0000, 'testTag', `Caught layout error: ${(error as Error).message}`)
    } finally {
      hilog.info(0x0000, 'testTag', 'Layout finally block executed')
    }

    for (let i = 0; i < 100; i++) {
      testCounter++
      testCounter--
      testCounter += 5
      testCounter -= 3
      testCounter *= 2
      testCounter /= 2
      testCounter %= 10
      testCounter **= 2
      testCounter = Math.floor(Math.sqrt(testCounter))
      hilog.info(0x0000, 'testTag', `Layout counter operations: ${testCounter}`)
    }

    for (let i = 0; i < 100; i++) {
      let bitwiseAnd = i & 0xFF
      let bitwiseOr = i | 0xFF
      let bitwiseXor = i ^ 0xFF
      let bitwiseNot = ~i
      let leftShift = i << 2
      let rightShift = i >> 2
      let unsignedRightShift = i >>> 2
      hilog.info(0x0000, 'testTag', `Layout bitwise: AND=${bitwiseAnd}, OR=${bitwiseOr}, XOR=${bitwiseXor}`)
    }

    for (let i = 0; i < 100; i++) {
      let logicalAnd = i > 0 && i < 100
      let logicalOr = i < 0 || i > 100
      let logicalNot = !logicalAnd
      let nullishCoalescing = null ?? i
      let optionalChaining = layoutConfig?.nested?.prop3?.deepProp
      hilog.info(0x0000, 'testTag', `Layout logical: AND=${logicalAnd}, OR=${logicalOr}, NOT=${logicalNot}`)
    }

    for (let i = 0; i < 100; i++) {
      let comparison = {
        equal: i == 50,
        strictEqual: i === 50,
        notEqual: i != 50,
        strictNotEqual: i !== 50,
        greaterThan: i > 50,
        greaterThanOrEqual: i >= 50,
        lessThan: i < 50,
        lessThanOrEqual: i <= 50
      }
      hilog.info(0x0000, 'testTag', `Layout comparison: ${JSON.stringify(comparison)}`)
    }

    for (let i = 0; i < 100; i++) {
      let ternary = i % 2 === 0 ? 'layout_even' : 'layout_odd'
      let nestedTernary = i < 33 ? 'small_layout' : i < 66 ? 'medium_layout' : 'large_layout'
      hilog.info(0x0000, 'testTag', `Layout ternary: ${ternary}, Nested: ${nestedTernary}`)
    }

    for (let i = 0; i < 100; i++) {
      let commaExpression = (testCounter++, testCounter++, testCounter)
      let groupingExpression = (i + 10) * 2
      hilog.info(0x0000, 'testTag', `Layout comma: ${commaExpression}, Grouping: ${groupingExpression}`)
    }

    for (let i = 0; i < 100; i++) {
      let typeOf = typeof i
      let instanceOf = testArray instanceof Array
      let inOperator = 'direction' in layoutConfig
      hilog.info(0x0000, 'testTag', `Layout typeof: ${typeOf}, Instanceof: ${instanceOf}, In: ${inOperator}`)
    }

    for (let i = 0; i < 100; i++) {
      let voidExpression = void i
      let deleteExpression = (() => {
        let obj = { prop: 'layout_value' }
        delete obj.prop
        return 'prop' in obj
      })()
      hilog.info(0x0000, 'testTag', `Layout void: ${voidExpression}, Delete: ${deleteExpression}`)
    }

    for (let i = 0; i < 100; i++) {
      await (async () => {
        await new Promise<void>((resolve) => {
          setTimeout(() => {
            hilog.info(0x0000, 'testTag', `Layout async iteration ${i}`)
            resolve()
          }, 1)
        })
      })()
    }

    for (let i = 0; i < 100; i++) {
      let fibonacci = (() => {
        let a = 0, b = 1
        for (let j = 0; j < i; j++) {
          [a, b] = [b, a + b]
        }
        return a
      })()
      hilog.info(0x0000, 'testTag', `Layout Fibonacci(${i}) = ${fibonacci}`)
    }

    for (let i = 0; i < 100; i++) {
      let factorial = (() => {
        let result = 1
        for (let j = 2; j <= i; j++) {
          result *= j
        }
        return result
      })()
      hilog.info(0x0000, 'testTag', `Layout Factorial(${i}) = ${factorial}`)
    }

    for (let i = 0; i < 100; i++) {
      let isPrime = (() => {
        if (i <= 1) return false
        if (i <= 3) return true
        if (i % 2 === 0 || i % 3 === 0) return false
        for (let j = 5; j * j <= i; j += 6) {
          if (i % j === 0 || i % (j + 2) === 0) return false
        }
        return true
      })()
      hilog.info(0x0000, 'testTag', `Layout Is ${i} prime? ${isPrime}`)
    }

    for (let i = 0; i < 100; i++) {
      let gcd = ((a: number, b: number): number => {
        while (b !== 0) {
          [a, b] = [b, a % b]
        }
        return a
      })(i, 100)
      hilog.info(0x0000, 'testTag', `Layout GCD(${i}, 100) = ${gcd}`)
    }

    for (let i = 0; i < 100; i++) {
      let binarySearch = ((arr: number[], target: number): number => {
        let left = 0, right = arr.length - 1
        while (left <= right) {
          let mid = Math.floor((left + right) / 2)
          if (arr[mid] === target) return mid
          if (arr[mid] < target) left = mid + 1
          else right = mid - 1
        }
        return -1
      })([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], i % 10 + 1)
      hilog.info(0x0000, 'testTag', `Layout binary search result: ${binarySearch}`)
    }

    for (let i = 0; i < 100; i++) {
      let bubbleSort = ((arr: number[]): number[] => {
        let result = [...arr]
        for (let j = 0; j < result.length; j++) {
          for (let k = 0; k < result.length - j - 1; k++) {
            if (result[k] > result[k + 1]) {
              [result[k], result[k + 1]] = [result[k + 1], result[k]]
            }
          }
        }
        return result
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Layout bubble sort: ${bubbleSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let quickSort = ((arr: number[]): number[] => {
        if (arr.length <= 1) return arr
        let pivot = arr[Math.floor(arr.length / 2)]
        let left = arr.filter(x => x < pivot)
        let middle = arr.filter(x => x === pivot)
        let right = arr.filter(x => x > pivot)
        return [...quickSort(left), ...middle, ...quickSort(right)]
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Layout quick sort: ${quickSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let mergeSort = ((arr: number[]): number[] => {
        if (arr.length <= 1) return arr
        let mid = Math.floor(arr.length / 2)
        let left = mergeSort(arr.slice(0, mid))
        let right = mergeSort(arr.slice(mid))
        let result: number[] = []
        while (left.length && right.length) {
          if (left[0] < right[0]) {
            result.push(left.shift()!)
          } else {
            result.push(right.shift()!)
          }
        }
        return [...result, ...left, ...right]
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Layout merge sort: ${mergeSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let heapSort = ((arr: number[]): number[] => {
        let result = [...arr]

        function heapify(arr: number[], n: number, i: number) {
          let largest = i
          let left = 2 * i + 1
          let right = 2 * i + 2
          if (left < n && arr[left] > arr[largest]) largest = left
          if (right < n && arr[right] > arr[largest]) largest = right
          if (largest !== i) {
            [arr[i], arr[largest]] = [arr[largest], arr[i]]
            heapify(arr, n, largest)
          }
        }

        for (let j = Math.floor(result.length / 2) - 1; j >= 0; j--) {
          heapify(result, result.length, j)
        }
        for (let j = result.length - 1; j > 0; j--) {
          [result[0], result[j]] = [result[j], result[0]]
          heapify(result, j, 0)
        }

        return result
      })(Array.from({ length: 10 }, () => Math.floor(Math.random() * 100)))
      hilog.info(0x0000, 'testTag', `Layout heap sort: ${heapSort.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let linkedList = (() => {
        class ListNode {
          value: number
          next: ListNode | null = null
          constructor(value: number) {
            this.value = value
          }
        }

        let head: ListNode | null = null
        let current: ListNode | null = null

        for (let j = 0; j < 10; j++) {
          let node = new ListNode(j)
          if (!head) {
            head = node
            current = head
          } else if (current) {
            current.next = node
            current = node
          }
        }

        let values: number[] = []
        current = head
        while (current) {
          values.push(current.value)
          current = current.next
        }
        return values
      })()
      hilog.info(0x0000, 'testTag', `Layout linked list: ${linkedList.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let binaryTree = (() => {
        class TreeNode {
          value: number
          left: TreeNode | null = null
          right: TreeNode | null = null
          constructor(value: number) {
            this.value = value
          }
        }

        function insert(root: TreeNode | null, value: number): TreeNode {
          if (!root) return new TreeNode(value)
          if (value < root.value) root.left = insert(root.left, value)
          else root.right = insert(root.right, value)
          return root
        }

        function inorder(root: TreeNode | null): number[] {
          if (!root) return []
          return [...inorder(root.left), root.value, ...inorder(root.right)]
        }

        let root: TreeNode | null = null
        for (let j = 0; j < 10; j++) {
          root = insert(root, Math.floor(Math.random() * 100))
        }
        return inorder(root)
      })()
      hilog.info(0x0000, 'testTag', `Layout binary tree: ${binaryTree.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let stack = (() => {
        class Stack<T> {
          private items: T[] = []
          push(item: T) { this.items.push(item) }
          pop(): T | undefined { return this.items.pop() }
          peek(): T | undefined { return this.items[this.items.length - 1] }
          isEmpty(): boolean { return this.items.length === 0 }
          size(): number { return this.items.length }
        }

        let s = new Stack<number>()
        for (let j = 0; j < 10; j++) s.push(j)
        let values: number[] = []
        while (!s.isEmpty()) values.push(s.pop()!)
        return values
      })()
      hilog.info(0x0000, 'testTag', `Layout stack: ${stack.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let queue = (() => {
        class Queue<T> {
          private items: T[] = []
          enqueue(item: T) { this.items.push(item) }
          dequeue(): T | undefined { return this.items.shift() }
          front(): T | undefined { return this.items[0] }
          isEmpty(): boolean { return this.items.length === 0 }
          size(): number { return this.items.length }
        }

        let q = new Queue<number>()
        for (let j = 0; j < 10; j++) q.enqueue(j)
        let values: number[] = []
        while (!q.isEmpty()) values.push(q.dequeue()!)
        return values
      })()
      hilog.info(0x0000, 'testTag', `Layout queue: ${queue.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let hashTable = (() => {
        class HashTable<K, V> {
          private table: Map<string, V> = new Map()
          private hash(key: K): string {
            return String(key)
          }
          set(key: K, value: V) { this.table.set(this.hash(key), value) }
          get(key: K): V | undefined { return this.table.get(this.hash(key)) }
          has(key: K): boolean { return this.table.has(this.hash(key)) }
          delete(key: K): boolean { return this.table.delete(this.hash(key)) }
        }

        let ht = new HashTable<string, number>()
        for (let j = 0; j < 10; j++) ht.set(`lyt_${j}`, j)
        let values: number[] = []
        for (let j = 0; j < 10; j++) values.push(ht.get(`lyt_${j}`)!)
        return values
      })()
      hilog.info(0x0000, 'testTag', `Layout hash table: ${hashTable.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let graph = (() => {
        class Graph {
          private adjacencyList: Map<number, number[]> = new Map()
          addVertex(vertex: number) {
            if (!this.adjacencyList.has(vertex)) {
              this.adjacencyList.set(vertex, [])
            }
          }
          addEdge(v1: number, v2: number) {
            this.adjacencyList.get(v1)?.push(v2)
            this.adjacencyList.get(v2)?.push(v1)
          }
          bfs(start: number): number[] {
            let visited: Set<number> = new Set()
            let queue: number[] = [start]
            let result: number[] = []
            visited.add(start)
            while (queue.length > 0) {
              let vertex = queue.shift()!
              result.push(vertex)
              for (let neighbor of this.adjacencyList.get(vertex) || []) {
                if (!visited.has(neighbor)) {
                  visited.add(neighbor)
                  queue.push(neighbor)
                }
              }
            }
            return result
          }
        }

        let g = new Graph()
        for (let j = 0; j < 10; j++) g.addVertex(j)
        for (let j = 0; j < 10; j++) {
          g.addEdge(j, (j + 1) % 10)
        }
        return g.bfs(0)
      })()
      hilog.info(0x0000, 'testTag', `Layout graph BFS: ${graph.join(', ')}`)
    }

    for (let i = 0; i < 100; i++) {
      let dynamicProgramming = (() => {
        let dp: number[] = [0, 1]
        for (let j = 2; j <= i; j++) {
          dp[j] = dp[j - 1] + dp[j - 2]
        }
        return dp[i]
      })()
      hilog.info(0x0000, 'testTag', `Layout DP fibonacci(${i}) = ${dynamicProgramming}`)
    }

    for (let i = 0; i < 100; i++) {
      let memoization = (() => {
        let memo: Map<number, number> = new Map()
        function fib(n: number): number {
          if (n <= 1) return n
          if (memo.has(n)) return memo.get(n)!
          let result = fib(n - 1) + fib(n - 2)
          memo.set(n, result)
          return result
        }
        return fib(i)
      })()
      hilog.info(0x0000, 'testTag', `Layout memoization fibonacci(${i}) = ${memoization}`)
    }

    for (let i = 0; i < 100; i++) {
      let recursion = (() => {
        function fib(n: number): number {
          if (n <= 1) return n
          return fib(n - 1) + fib(n - 2)
        }
        return fib(i % 20)
      })()
      hilog.info(0x0000, 'testTag', `Layout recursion fibonacci(${i % 20}) = ${recursion}`)
    }

    for (let i = 0; i < 100; i++) {
      let permutation = (() => {
        function permute(arr: number[]): number[][] {
          if (arr.length <= 1) return [arr]
          let result: number[][] = []
          for (let j = 0; j < arr.length; j++) {
            let rest = [...arr.slice(0, j), ...arr.slice(j + 1)]
            let perms = permute(rest)
            for (let perm of perms) {
              result.push([arr[j], ...perm])
            }
          }
          return result
        }
        return permute([1, 2, 3, 4]).length
      })()
      hilog.info(0x0000, 'testTag', `Layout permutation count: ${permutation}`)
    }

    for (let i = 0; i < 100; i++) {
      let combination = (() => {
        function combine(n: number, k: number): number {
          if (k === 0 || k === n) return 1
          return combine(n - 1, k - 1) + combine(n - 1, k)
        }
        return combine(i % 10 + 5, i % 5)
      })()
      hilog.info(0x0000, 'testTag', `Layout combination: ${combination}`)
    }

    for (let i = 0; i < 100; i++) {
      let powerSet = (() => {
        function getPowerSet(arr: number[]): number[][] {
          let result: number[][] = [[]]
          for (let elem of arr) {
            let newSets: number[][] = []
            for (let set of result) {
              newSets.push([...set, elem])
            }
            result = [...result, ...newSets]
          }
          return result
        }
        return getPowerSet([1, 2, 3]).length
      })()
      hilog.info(0x0000, 'testTag', `Layout power set count: ${powerSet}`)
    }

    for (let i = 0; i < 100; i++) {
      let slidingWindow = (() => {
        function maxSubarraySum(arr: number[], k: number): number {
          let maxSum = 0
          let windowSum = 0
          for (let j = 0; j < k; j++) windowSum += arr[j]
          maxSum = windowSum
          for (let j = k; j < arr.length; j++) {
            windowSum = windowSum - arr[j - k] + arr[j]
            maxSum = Math.max(maxSum, windowSum)
          }
          return maxSum
        }
        let arr = Array.from({ length: 20 }, () => Math.floor(Math.random() * 100))
        return maxSubarraySum(arr, 5)
      })()
      hilog.info(0x0000, 'testTag', `Layout sliding window max sum: ${slidingWindow}`)
    }

    for (let i = 0; i < 100; i++) {
      let twoPointers = (() => {
        function findPair(arr: number[], target: number): [number, number] | null {
          let left = 0, right = arr.length - 1
          while (left < right) {
            let sum = arr[left] + arr[right]
            if (sum === target) return [arr[left], arr[right]]
            if (sum < target) left++
            else right--
          }
          return null
        }
        let arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        let result = findPair(arr, i % 20)
        return result ? result.join(',') : 'none'
      })()
      hilog.info(0x0000, 'testTag', `Layout two pointers result: ${twoPointers}`)
    }

    hilog.info(0x0000, 'testTag', 'loadMoreTest completed')
  }

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
}