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
  Entry,
  SizeOptions,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Entry
@Component
export struct MultiComponentTest {
  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Bottom  }) {
      Text('First child').backgroundColor('#7b68ee').width('90%').height('100%')
      Text('Second child').backgroundColor('#ffc0cb').width('70%').height('60%')
    }.width('100%').height(150).margin({ top: 5 } as Margin)
    }
    .title('一多组布局属性组件功能')
  }
}