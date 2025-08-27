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
  TextAlign,
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
export struct Layout003Test {
  build() {
    NavDestination() {
      Column({ space: 5 } as ColumnOptions) {
      Text('flexGrow').fontSize(9).fontColor(0xCCCCCC).width('90%')
      // flexGrow()表示剩余空间分配给该元素的比例
      Flex(undefined) {
        Text('flexGrow(2)')
          .flexGrow(2) // 父容器分配给该Text的宽度为剩余宽度的2/3
          .height(100)
          .backgroundColor('#ffb6c1')
          .textAlign(TextAlign.Center)
        Text('flexGrow(1)')
          .flexGrow(1) // 父容器分配给该Text的宽度为剩余宽度的1/3
          .height(100)
          .backgroundColor('#dc1434')
          .textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Text('flexShrink').fontSize(9).fontColor(0xCCCCCC).width('90%')
      // flexShrink()表示该元素的压缩比例，基于超出的总尺寸进行计算
      // 第一个text压缩比例是0,另外两个都是1,因此放不下时等比例压缩后两个,第一个不压缩
      Flex({ direction: FlexDirection.Row }) {
        Text('flexShrink(0)')
          .flexShrink(0)
          .width('50%')
          .height(100)
          .backgroundColor('#ffb6c1')
          .textAlign(TextAlign.Center)
        Text('default flexShrink') // 默认值为1
          .width('40%')
          .height(100)
          .backgroundColor('#dc1434')
          .textAlign(TextAlign.Center)
        Text('flexShrink(1)')
          .flexShrink(1)
          .width('40%')
          .height(100)
          .backgroundColor('#FF00FF')
          .textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Text('flexBasis').fontSize(9).fontColor(0xCCCCCC).width('90%')
      // 基于主轴的基准尺寸
      // flexBasis()值可以是字符串'auto',表示基准尺寸是元素本来的大小,也可以是长度设置，相当于.width()/.height()
      Flex() {
        Text('flexBasis(100)')
          .flexBasis(100) // 这里表示宽度为100vp
          .height(100)
          .backgroundColor('#ffb6c1')
          .textAlign(TextAlign.Center)
        Text(`flexBasis('auto')`)
          .flexBasis('auto') // 这里表示宽度保持原本设置的60%的宽度
          .width('60%')
          .height(100)
          .backgroundColor('#dc1434')
          .textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Text('alignSelf').fontSize(9).fontColor(0xCCCCCC).width('90%')
      // alignSelf会覆盖Flex布局容器中的alignItems设置
      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
        Text('alignSelf Auto')
          .alignSelf(ItemAlign.Auto)
          .width('15%')
          .height(70)
          .backgroundColor('#DB7093')
          .textAlign(TextAlign.Center)
        Text('alignSelf Start')
          .alignSelf(ItemAlign.Start)
          .width('15%')
          .height(70)
          .backgroundColor('#DA70D6')
          .textAlign(TextAlign.Center)
        Text('alignSelf Center')
          .alignSelf(ItemAlign.Center)
          .width('15%')
          .height(70)
          .backgroundColor('#8A2BE2')
          .textAlign(TextAlign.Center)
        Text('alignSelf End')
          .alignSelf(ItemAlign.End)
          .width('15%')
          .height(70)
          .backgroundColor('#0000FF')
          .textAlign(TextAlign.Center)
        Text('no alignSelf,height:100%')
          .width('15%')
          .height('100%')
          .backgroundColor('#1E90FF')
          .textAlign(TextAlign.Center)
        Text('alignSelf Baseline')
          .alignSelf(ItemAlign.Baseline)
          .width('15%')
          .height('100%')
          .backgroundColor('#87CEEB')
          .textAlign(TextAlign.Center)
        Text('alignSelf Stretch')
          .alignSelf(ItemAlign.Stretch)
          .width('15%')
          .height('100%')
          .backgroundColor('#7FFFAA')
          .textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')
    }.width('100%').margin({ top: 5 } as Margin)
    }
    .title('布局基础功能测试用例003')
  }
}