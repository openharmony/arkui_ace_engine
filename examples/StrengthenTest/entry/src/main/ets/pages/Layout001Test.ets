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

    }
    }
    .title('布局基础功能测试用例001')
  }
}