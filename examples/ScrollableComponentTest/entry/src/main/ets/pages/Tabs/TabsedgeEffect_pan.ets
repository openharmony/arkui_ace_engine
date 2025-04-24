/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
 enum TabContentPosition {
  START,
  END,
  MIDDLE
}

class TabConentGestureModifier implements GestureModifier {
  private contentPosition: TabContentPosition = TabContentPosition.MIDDLE

  constructor(position: TabContentPosition) {
    this.contentPosition = position
  }

  applyGesture(event: UIGestureEvent): void {
    switch (this.contentPosition) {
      case TabContentPosition.START:
        event.addGesture(new PanGestureHandler({ direction: PanDirection.Right }))
        break;
      case TabContentPosition.END:
        event.addGesture(new PanGestureHandler({ direction: PanDirection.Left }))
        break;
      default:
        break;
    }
  }
}


@Entry
@Component
struct TabBarDemo {
  private controller: TabsController = new TabsController();
  @State currentIndex: number = 0;
  @State data: Array<string> = [];
  @State isReady: boolean = false;
  private panOptionStart: PanGestureOptions = new PanGestureOptions({ direction: PanDirection.Right })
  private panOptionEnd: PanGestureOptions = new PanGestureOptions({ direction: PanDirection.Left })

  aboutToAppear(): void {
    for (let i = 0; i < 10; i++) {
      this.data.push(`我是第${i}条数据`)
    }
  }

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
        .fontSize(this.currentIndex === index ? 24 : 16)
        .fontWeight(this.currentIndex === index ? 600 : 400)
        .height(50)
      // 根据是否当前显示的TabContent确定是否显示indicator
      if (this.currentIndex === index) {
        Image($r('app.media.startIcon'))
      }
    }.width('100%')
  }

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: $$this.currentIndex, controller: this.controller }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor('#6600CB87')
        }.tabBar(this.tabBuilder(0, 'Tab1'))
        // 通过自定义手势屏蔽TabContent边缘回弹效果
        // 使用ForEach创建TabContent时可以根据index确定TabConentGestureModifier参数
        .gestureModifier(new TabConentGestureModifier(TabContentPosition.START))
        // 也可以直接设置，TabConentGestureModifier主要用于ForEach生成TabContent的场景
        // .gesture(PanGesture(this.panOptionStart))

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Yellow)
        }.tabBar(this.tabBuilder(1, 'Tab2'))
        // 非ForEach统一生成TabContent此处也可以不设置
        .gestureModifier(new TabConentGestureModifier(TabContentPosition.MIDDLE))

        TabContent() {
          Grid() {
            ForEach(this.data, (item: string, index: number) => {
              GridItem() {
                Text(item).fontSize(16).width('100%').height(30).textAlign(TextAlign.Center)
              }
            }, (item: string, index: number) => index.toString())
          }
          .onAppear(() => {
            this.isReady = true;
          })
        }.tabBar(this.tabBuilder(2, 'Tab3'))
        .gestureModifier(new TabConentGestureModifier(TabContentPosition.END))
        // .gesture(PanGesture(this.panOptionEnd))
      }
      .onChange((index: number) => {
        this.currentIndex = index
      })
    }.width('100%')
  }
}