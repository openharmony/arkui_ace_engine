import {
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  UserView,
  WaterFlow,
  LazyVGridLayout,
  GridLayoutOptions,
  ForEach,
  BarState,
  GridItemAttribute,
  Color,
  GridItemStyle,
  GridDirection,
  ComputedBarAttribute,
  GridAttribute,
  ScrollState,
  OnScrollFrameBeginHandlerResult,
  OnScrollFrameBeginCallback,
  Entry,
  Scroller,
  ColumnOptions,
  ForEach,
  OnScrollCallback,
  ClickEvent,
  ScrollState,
  TextAlign,
  LengthMetrics
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'


@Entry
@Component
struct LazyVGridLayoutSample1 {
  private arr:Array<number> = [];
  build() {
    Column() {
      WaterFlow() {
        LazyVGridLayout() {
          ForEach(this.arr, (item:number)=>{
            Text('item' + item.toString())
              .height(64)
              .width('100%')
              .borderRadius(5)
              .backgroundColor(Color.White)
              .textAlign(TextAlign.Center)
          })
        }
        .columnsTemplate('1fr 1fr')
        .rowsGap(LengthMetrics.vp(10))
        .columnsGap(LengthMetrics.vp(10))
      }.padding(10)
    }
    .width('100%').height('100%')
    .backgroundColor('#DCDCDC')
  }

  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.arr.push(i);
    }
  }
}