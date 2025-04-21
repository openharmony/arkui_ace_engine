/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct MoveTextToTarContentNeedHideHandle {
  @State scale1: number = 1
  @State opacity1: number = 1

  @Styles
  listCard(){
    .backgroundColor(Color.White)
    .height(72)
    .width('100%')
  }

  @Builder
  ListTest(i: number) {
    WaterFlow() {
      ForEach(new Array(i).fill(1), (item: number, index) => {
        FlowItem() {
          Text('item' + index)
            .fontSize(16)
            .copyOption(CopyOptions.InApp)
        }.listCard()
      }, (item: string) => item)
    }
    .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true })
    .hitTestBehavior(HitTestMode.Transparent)
    .layoutWeight(1)
    .nestedScroll({
      scrollForward: NestedScrollMode.PARENT_FIRST,
      scrollBackward: NestedScrollMode.SELF_FIRST
    })

  }

  @Builder
  CustomList(i: number) {
    Column() {
      this.ListTest(i)
    }
    .height('100%')
    .width('100%')
    .parallelGesture(
      PanGesture(new PanGestureOptions({ direction: PanDirection.Vertical }))
        .onActionStart(() => {

        })
        .onActionUpdate(() => {
          console.log('1111')
        })
        .onActionEnd(() => {

        })
    )
  }

  build() {
    Scroll() {
      Column() {
        Text('==========操作==========\n0' +
          '1、点击【Tab2】，展示Tab2\n' +
          '2、双击item0，展示两个完整手柄、完整高亮区、菜单\n' +
          '3、上划隐藏item0\n' +
          '==========期望==========\n' +
          '1、隐藏一半item0，展示两个一半高度手柄、一半高度高亮区，菜单\n' +
          '2、隐藏全部item0，隐藏所有手柄、高亮、菜单')
        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            this.CustomList(1)
          }.tabBar('Tab1')

          TabContent() {
            this.CustomList(20)
          }.tabBar('Tab2')
        }
        .height('100%')
      }.width('100%')
    }
    .height('100%')
    .backgroundColor('#DCDCDC')
    .width('100%')
    .height('100%')
    .scale({ x: this.scale1 })
    .opacity(this.opacity1)
    .height('100%')
    .width('100%')
  }
}