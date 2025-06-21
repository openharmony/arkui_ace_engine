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
        // 宽度80 ,高度80 ,上下开始结束的外边距40、20、30、10(蓝色区域），上下开始结束的内边距分别为5、15、10、20（白色区域）
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
    }.width('100%').margin({ top: 5 } as Margin)
    }
    .title('布局基础功能测试用例002')
  }
}