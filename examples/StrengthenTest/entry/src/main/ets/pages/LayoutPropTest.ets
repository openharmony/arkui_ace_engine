import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement'

import {
  Text,
  TextAttribute,
  Column,
  Component,
  Color,
  ColumnOptions,
  Stack,
  Alignment,
  Margin,
  Entry,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'

import hilog from '@ohos.hilog'

@Entry
@Component
export struct LayoutPropTest {

  build() {
    NavDestination() {
      Column({ space: 5 } as ColumnOptions) {
      // 设置子元素垂直方向间距为5
      Text('space'). width('90%')
      Column({ space: '15' } as ColumnOptions) {
        Column().backgroundColor('#7b68ee').width('100%').height(30)
        Column().backgroundColor('#ffc0cb').width('100%').height(30)
      }.width('90%').height(100).border({ width: 1 })

      Stack({ alignContent: Alignment.Bottom }) {
        Text('First child').backgroundColor('#7b68ee').width('90%').height('100%')
        Text('Second child').backgroundColor('#ffc0cb').width('70%').height('60%')
      }.width('90%').height(150).margin({ top: 5 } as Margin).border({ width: 1 })

    }. width('100%')
    }
    .title('布局属性组件功能')
  }
}

