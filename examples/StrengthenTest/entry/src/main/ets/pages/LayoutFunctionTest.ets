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
  Entry,
  ColumnOptions,
  SizeOptions,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Entry
@Component
export struct LayoutFunctionTest {
  build() {
    NavDestination() {
      Column({ space: 5 } as ColumnOptions) {
      // 设置子元素垂直方向间距为5
      Text('space'). width('90%')
      Column({ space: '15' } as ColumnOptions) {
        Column().backgroundColor('#7b68ee').width('100%').height(30)
        Column().backgroundColor('#ffc0cb').width('100%').height(30)
      }.width('90%').height(100).border({ width: 1 })

      // 设置子元素水平方向对齐方式
      Text('alignItems(Start)'). width('90%')
      Column(undefined) {
        Column().backgroundColor('#7b68ee').width('50%').height(30)
        Column().backgroundColor('#ffc0cb').width('50%').height(30)
      }.alignItems(HorizontalAlign.Start).width('90%').border({ width: 1 })

      Text('alignItems(End)'). width('90%')
      Column(undefined) {
        Column().width('50%').height(30).backgroundColor('#7b68ee')
        Column().width('50%').height(30).backgroundColor('#ffc0cb')
      }.alignItems(HorizontalAlign.End). width('90%').border({ width: 1 })

      Text('alignItems(Center)'). width('90%')
      Column(undefined) {
        Column().width('50%').height(30).backgroundColor('#7b68ee')
        Column().width('50%').height(30).backgroundColor('#ffc0cb')
      }.alignItems(HorizontalAlign.Center). width('90%').border({ width: 1 })

      // 设置子元素垂直方向的对齐方式
      Text('justifyContent(Center)'). width('90%')
      Column(undefined) {
        Column().width('90%').height(30).backgroundColor('#7b68ee')
        Column().width('90%').height(30).backgroundColor('#ffc0cb')
      }.justifyContent(FlexAlign.Center).height(100).border({ width: 1 })

      Text('justifyContent(End)'). width('90%')
      Column(undefined) {
        Column().width('90%').height(30).backgroundColor('#7b68ee')
        Column().width('90%').height(30).backgroundColor('#ffc0cb')
      }.height(100).justifyContent(FlexAlign.End).border({ width: 1 })

      Text('justifyContent(End) reverse'). width('90%')
      Column(undefined) {
        Column().width('90%').height(30).backgroundColor('#7b68ee')
        Column().width('90%').height(30).backgroundColor('#ffc0cb')
      }.height(100).justifyContent(FlexAlign.End).reverse(true).border({ width: 1 })
    }. width('100%')
    }
    .title('布局组件基础功能测试用例')
  }
}