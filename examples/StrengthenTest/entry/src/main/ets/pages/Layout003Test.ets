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

      Text('Column 基础布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 10 } as ColumnOptions) {
        Text('Column 子元素1').width('80%').height(50).backgroundColor('#FF6B6B')
        Text('Column 子元素2').width('80%').height(50).backgroundColor('#4ECDC4')
        Text('Column 子元素3').width('80%').height(50).backgroundColor('#45B7D1')
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Row 基础布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 10 }) {
        Text('Row 子元素1').width('30%').height(50).backgroundColor('#FF6B6B')
        Text('Row 子元素2').width('30%').height(50).backgroundColor('#4ECDC4')
        Text('Row 子元素3').width('30%').height(50).backgroundColor('#45B7D1')
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Flex 水平布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Row }) {
        Text('Flex Row 1').width(80).height(40).backgroundColor('#FF6B6B')
        Text('Flex Row 2').width(80).height(40).backgroundColor('#4ECDC4')
        Text('Flex Row 3').width(80).height(40).backgroundColor('#45B7D1')
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Flex 垂直布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Column }) {
        Text('Flex Column 1').width('80%').height(40).backgroundColor('#FF6B6B')
        Text('Flex Column 2').width('80%').height(40).backgroundColor('#4ECDC4')
        Text('Flex Column 3').width('80%').height(40).backgroundColor('#45B7D1')
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Flex justifyContent 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Start }) {
        Text('Start').width(60).height(40).backgroundColor('#FF6B6B')
        Text('Start').width(60).height(40).backgroundColor('#4ECDC4')
      }.width('90%').height(60).padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Center }) {
        Text('Center').width(60).height(40).backgroundColor('#FF6B6B')
        Text('Center').width(60).height(40).backgroundColor('#4ECDC4')
      }.width('90%').height(60).padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.End }) {
        Text('End').width(60).height(40).backgroundColor('#FF6B6B')
        Text('End').width(60).height(40).backgroundColor('#4ECDC4')
      }.width('90%').height(60).padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
        Text('SpaceBetween').width(60).height(40).backgroundColor('#FF6B6B')
        Text('SpaceBetween').width(60).height(40).backgroundColor('#4ECDC4')
      }.width('90%').height(60).padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
        Text('SpaceAround').width(60).height(40).backgroundColor('#FF6B6B')
        Text('SpaceAround').width(60).height(40).backgroundColor('#4ECDC4')
      }.width('90%').height(60).padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceEvenly }) {
        Text('SpaceEvenly').width(60).height(40).backgroundColor('#FF6B6B')
        Text('SpaceEvenly').width(60).height(40).backgroundColor('#4ECDC4')
      }.width('90%').height(60).padding(10).backgroundColor('#F0F8FF')

      Text('Flex alignItems 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Start }) {
        Text('Start').width(60).height(40).backgroundColor('#FF6B6B')
        Text('Start').width(60).height(60).backgroundColor('#4ECDC4')
        Text('Start').width(60).height(80).backgroundColor('#45B7D1')
      }.width('90%').height(100).padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
        Text('Center').width(60).height(40).backgroundColor('#FF6B6B')
        Text('Center').width(60).height(60).backgroundColor('#4ECDC4')
        Text('Center').width(60).height(80).backgroundColor('#45B7D1')
      }.width('90%').height(100).padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.End }) {
        Text('End').width(60).height(40).backgroundColor('#FF6B6B')
        Text('End').width(60).height(60).backgroundColor('#4ECDC4')
        Text('End').width(60).height(80).backgroundColor('#45B7D1')
      }.width('90%').height(100).padding(10).backgroundColor('#F0F8FF')

      Text('Flex wrap 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ wrap: FlexWrap.Wrap }) {
        Text('Wrap 1').width(120).height(40).backgroundColor('#FF6B6B')
        Text('Wrap 2').width(120).height(40).backgroundColor('#4ECDC4')
        Text('Wrap 3').width(120).height(40).backgroundColor('#45B7D1')
        Text('Wrap 4').width(120).height(40).backgroundColor('#96CEB4')
        Text('Wrap 5').width(120).height(40).backgroundColor('#FFEEAD')
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Flex({ wrap: FlexWrap.NoWrap }) {
        Text('NoWrap 1').width(120).height(40).backgroundColor('#FF6B6B')
        Text('NoWrap 2').width(120).height(40).backgroundColor('#4ECDC4')
        Text('NoWrap 3').width(120).height(40).backgroundColor('#45B7D1')
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Stack 基础布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Stack({ alignContent: Alignment.TopStart }) {
        Text('Stack 底层').width('100%').height('100%').backgroundColor('#FF6B6B')
        Text('Stack 中层').width('70%').height('70%').backgroundColor('#4ECDC4')
        Text('Stack 顶层').width('40%').height('40%').backgroundColor('#45B7D1')
      }.width('90%').height(150).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.Center }) {
        Text('Center 1').width(80).height(80).backgroundColor('#FF6B6B')
        Text('Center 2').width(60).height(60).backgroundColor('#4ECDC4')
        Text('Center 3').width(40).height(40).backgroundColor('#45B7D1')
      }.width('90%').height(150).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.BottomEnd }) {
        Text('BottomEnd 1').width(80).height(80).backgroundColor('#FF6B6B')
        Text('BottomEnd 2').width(60).height(60).backgroundColor('#4ECDC4')
        Text('BottomEnd 3').width(40).height(40).backgroundColor('#45B7D1')
      }.width('90%').height(150).padding(10).backgroundColor('#F0F8FF')

      Text('GridRow 基础布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      GridRow({
        columns: 4,
        gutterX: 10,
        gutterY: 10
      } as GridRowAttribute) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8], (item: number) => {
          GridCol({ span: 1 } as GridColAttribute) {
            Text(`Grid ${item}`)
              .width('100%')
              .height(60)
              .backgroundColor(item % 2 === 0 ? '#FF6B6B' : '#4ECDC4')
              .textAlign(TextAlign.Center)
          }
        })
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('GridRow 不同 span').fontSize(9).fontColor(0xCCCCCC).width('90%')
      GridRow({
        columns: 4,
        gutterX: 10,
        gutterY: 10
      } as GridRowAttribute) {
        GridCol({ span: 2 } as GridColAttribute) {
          Text('Span 2').width('100%').height(60).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        }
        GridCol({ span: 1 } as GridColAttribute) {
          Text('Span 1').width('100%').height(60).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        }
        GridCol({ span: 1 } as GridColAttribute) {
          Text('Span 1').width('100%').height(60).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
        }
        GridCol({ span: 3 } as GridColAttribute) {
          Text('Span 3').width('100%').height(60).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
        }
        GridCol({ span: 1 } as GridColAttribute) {
          Text('Span 1').width('100%').height(60).backgroundColor('#FFEEAD').textAlign(TextAlign.Center)
        }
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Column 嵌套 Row').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 5 } ) {
        Text('第一行').width('100%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Row({ space: 10 }) {
          Text('左').width('45%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
          Text('右').width('45%').height(40).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
        }.width('100%')
        Text('第三行').width('100%').height(40).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Row 嵌套 Column').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 10 }) {
        Column({ space: 5 } ) {
          Text('上').width('100%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
          Text('下').width('100%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        }.width('30%')
        Column({ space: 5 } ) {
          Text('中上').width('100%').height(40).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
          Text('中下').width('100%').height(40).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
        }.width('30%')
        Column({ space: 5 } ) {
          Text('右').width('100%').height(80).backgroundColor('#FFEEAD').textAlign(TextAlign.Center)
        }.width('30%')
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Flex 嵌套布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Column }) {
        Flex({ direction: FlexDirection.Row }) {
          Text('Flex 嵌套 1').width(80).height(40).backgroundColor('#FF6B6B')
          Text('Flex 嵌套 2').width(80).height(40).backgroundColor('#4ECDC4')
        }
        Flex({ direction: FlexDirection.Row }) {
          Text('Flex 嵌套 3').width(80).height(40).backgroundColor('#45B7D1')
          Text('Flex 嵌套 4').width(80).height(40).backgroundColor('#96CEB4')
        }
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Divider 分隔线测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 10 } ) {
        Text('分隔线上方').width('100%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Divider().strokeWidth(2).color('#000000')
        Text('分隔线下方').width('100%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Divider().strokeWidth(4).color('#FF0000')
        Text('分隔线下方2').width('100%').height(40).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Padding 和 Margin 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 10 } ) {
        Text('Padding 10').width('80%').height(40).backgroundColor('#FF6B6B').padding(10).textAlign(TextAlign.Center)
        Text('Padding 20').width('80%').height(40).backgroundColor('#4ECDC4').padding(20).textAlign(TextAlign.Center)
        Text('Margin 10').width('80%').height(40).backgroundColor('#45B7D1').margin(10).textAlign(TextAlign.Center)
        Text('Margin 20').width('80%').height(40).backgroundColor('#96CEB4').margin(20).textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Flex displayPriority 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Row }) {
        Text('Priority 1').width(100).height(40).backgroundColor('#FF6B6B').displayPriority(1).textAlign(TextAlign.Center)
        Text('Priority 2').width(100).height(40).backgroundColor('#4ECDC4').displayPriority(2).textAlign(TextAlign.Center)
        Text('Priority 3').width(100).height(40).backgroundColor('#45B7D1').displayPriority(3).textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Column alignItems 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 10, alignItems: HorizontalAlign.Start } ) {
        Text('Start').width('60%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Start').width('60%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Column({ space: 10, alignItems: HorizontalAlign.Center } ) {
        Text('Center').width('60%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Center').width('60%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Column({ space: 10, alignItems: HorizontalAlign.End } ) {
        Text('End').width('60%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('End').width('60%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Row verticalAlign 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 10, verticalAlign: VerticalAlign.Top }) {
        Text('Top').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Top').width(60).height(60).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Row({ space: 10, verticalAlign: VerticalAlign.Center }) {
        Text('Center').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Center').width(60).height(60).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Row({ space: 10, verticalAlign: VerticalAlign.Bottom }) {
        Text('Bottom').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Bottom').width(60).height(60).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Text('Flex 复杂布局测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Column }) {
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceBetween }) {
          Text('左上').width(80).height(50).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
          Text('右上').width(80).height(50).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        }
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Center }) {
          Text('中').width(100).height(50).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
        }
        Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
          Text('左下').width(80).height(50).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
          Text('右下').width(80).height(50).backgroundColor('#FFEEAD').textAlign(TextAlign.Center)
        }
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Column justifyContent 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 10, justifyContent: FlexAlign.Start } ) {
        Text('Start').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Start').width('80%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Column({ space: 10, justifyContent: FlexAlign.Center } ) {
        Text('Center').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Center').width('80%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F0FF')

      Column({ space: 10, justifyContent: FlexAlign.End } ) {
        Text('End').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('End').width('80%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Column({ space: 10, justifyContent: FlexAlign.SpaceBetween } ) {
        Text('SpaceBetween').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('SpaceBetween').width('80%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Column({ space: 10, justifyContent: FlexAlign.SpaceAround } ) {
        Text('SpaceAround').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('SpaceAround').width('80%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Column({ space: 10, justifyContent: FlexAlign.SpaceEvenly } ) {
        Text('SpaceEvenly').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('SpaceEvenly').width('80%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(120).padding(10).backgroundColor('#F0F8FF')

      Text('Row justifyContent 测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 10, justifyContent: FlexAlign.Start }) {
        Text('Start').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Start').width(60).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Row({ space: 10, justifyContent: FlexAlign.Center }) {
        Text('Center').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('Center').width(60).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Row({ space: 10, justifyContent: FlexAlign.End }) {
        Text('End').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('End').width(60).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Row({ space: 10, justifyContent: FlexAlign.SpaceBetween }) {
        Text('SpaceBetween').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('SpaceBetween').width(60).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Row({ space: 10, justifyContent: FlexAlign.SpaceAround }) {
        Text('SpaceAround').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('SpaceAround').width(60).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Row({ space: 10, justifyContent: FlexAlign.SpaceEvenly }) {
        Text('SpaceEvenly').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('SpaceEvenly').width(60).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Stack 不同对齐方式').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Stack({ alignContent: Alignment.TopStart }) {
        Text('TopStart').width(100).height(60).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.TopCenter }) {
        Text('TopCenter').width(100).height(60).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.TopEnd }) {
        Text('TopEnd').width(100).height(60).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.Start }) {
        Text('Start').width(100).height(60).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.Center }) {
        Text('Center').width(100).height(60).backgroundColor('#FFEEAD').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.End }) {
        Text('End').width(100).height(60).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.BottomStart }) {
        Text('BottomStart').width(100).height(60).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.BottomCenter }) {
        Text('BottomCenter').width(100).height(60).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Stack({ alignContent: Alignment.BottomEnd }) {
        Text('BottomEnd').width(100).height(60).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
      }.width('90%').height(80).padding(10).backgroundColor('#F0F8FF')

      Text('Flex 反向布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.RowReverse }) {
        Text('1').width(60).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('2').width(60).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('3').width(60).height(40).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Flex({ direction: FlexDirection.ColumnReverse }) {
        Text('1').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('2').width('80%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('3').width('80%').height(40).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('GridRow 响应式布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      GridRow({
        columns: {
          xs: 2,
          sm: 3,
          md: 4,
          lg: 5,
          xl: 6
        },
        gutterX: 10,
        gutterY: 10
      } as GridRowAttribute) {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], (item: number) => {
          GridCol({
            span: {
              xs: 1,
              sm: 1,
              md: 1,
              lg: 1,
              xl: 1
            }
          } as GridColAttribute) {
            Text(`Item ${item}`)
              .width('100%')
              .height(50)
              .backgroundColor(item % 2 === 0 ? '#FF6B6B' : '#4ECDC4')
              .textAlign(TextAlign.Center)
          }
        })
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Flex 复杂嵌套').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Column }) {
        Flex({ direction: FlexDirection.Row }) {
          Column({ space: 5 } ) {
            Text('嵌套1').width('100%').height(30).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
            Text('嵌套2').width('100%').height(30).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
          }.width('40%')
          Column({ space: 5 } ) {
            Text('嵌套3').width('100%').height(30).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
            Text('嵌套4').width('100%').height(30).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
          }.width('40%')
        }
        Flex({ direction: FlexDirection.Row }) {
          Text('底部').width('80%').height(40).backgroundColor('#FFEEAD').textAlign(TextAlign.Center)
        }
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Column 权重布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column() {
        Text('权重1').width('80%').layoutWeight(1).height(0).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('权重2').width('80%').layoutWeight(2).height(0).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('权重3').width('80%').layoutWeight(1).height(0).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').height(150).padding(10).backgroundColor('#F0F8FF')

      Text('Row 权重布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row() {
        Text('权重1').layoutWeight(1).width(0).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('权重2').layoutWeight(2).width(0).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('权重3').layoutWeight(1).width(0).height(40).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Flex 权重布局').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Row }) {
        Text('权重1').layoutWeight(1).width(0).height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('权重2').layoutWeight(2).width(0).height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('权重3').layoutWeight(1).width(0).height(40).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('边框测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 10 } ) {
        Text('边框1').width('80%').height(40).border({ width: 2, color: '#FF0000' } as BorderOptions).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('边框2').width('80%').height(40).border({ width: 4, color: '#00FF00', radius: 10 } as BorderOptions).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('边框3').width('80%').height(40).border({ width: 2, color: '#0000FF', style: BorderStyle.Dashed } as BorderOptions).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('圆角测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 10 }) {
        Text('圆角5').width(80).height(40).borderRadius(5).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        Text('圆角10').width(80).height(40).borderRadius(10).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('圆角20').width(80).height(40).borderRadius(20).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
        Text('圆形').width(80).height(80).borderRadius(40).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('Text 对齐测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Column({ space: 10 } ) {
        Text('左对齐').width('100%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Start)
        Text('居中对齐').width('100%').height(40).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
        Text('右对齐').width('100%').height(40).backgroundColor('#45B7D1').textAlign(TextAlign.End)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('背景色测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 10 }) {
        Text('红色').width(80).height(40).backgroundColor('#FF0000').textAlign(TextAlign.Center)
        Text('绿色').width(80).height(40).backgroundColor('#00FF00').textAlign(TextAlign.Center)
        Text('蓝色').width(80).height(40).backgroundColor('#0000FF').textAlign(TextAlign.Center)
        Text('黄色').width(80).height(40).backgroundColor('#FFFF00').textAlign(TextAlign.Center)
      }.width('90%').padding(10).backgroundColor('#F0F8FF')

      Text('混合布局测试').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Column }) {
        Row({ space: 10 }) {
          Column({ space: 5 } ) {
            Text('1').width('100%').height(30).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
            Text('2').width('100%').height(30).backgroundColor('#4ECDC4').textAlign(TextAlign.Center)
          }.width('30%')
          Flex({ direction: FlexDirection.Column }) {
            Text('3').width('100%').height(30).backgroundColor('#45B7D1').textAlign(TextAlign.Center)
            Text('4').width('100%').height(30).backgroundColor('#96CEB4').textAlign(TextAlign.Center)
          }.width('30%')
          Stack({ alignContent: Alignment.Center }) {
            Text('5').width(60).height(60).backgroundColor('#FFEEAD').textAlign(TextAlign.Center)
          }.width('30%').height(70)
        }
        Divider().strokeWidth(2).color('#000000')
        Flex({ direction: FlexDirection.Row }) {
          Text('底部').width('80%').height(40).backgroundColor('#FF6B6B').textAlign(TextAlign.Center)
        }
      }.width('90%').padding(10).backgroundColor('#F0F8FF')
    }.width('100%').margin({ top: 5 } as Margin)
    }
    .title('布局基础功能测试用例003')
  }
}