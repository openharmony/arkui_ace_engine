/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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

// xxx.ets
@Entry
@Component
struct TabsExample {
  @State currentIndex: number = 0;
  private controller: TabsController = new TabsController();
  private data: number[] = [];

  aboutToAppear(): void {
    for (let i = 0; i < 10; i++) {
      this.data.push(i);
    }
  }

  @State isOnContentDidScrollIndex: number = 0
  @State text: string = ''
  @State isOnContentDidScroll: Array<OnTabsContentDidScrollCallback | undefined> = [
    ((selectedIndex: number, index: number, position: number, mainAxisLength: number) => {
      // 监听Swiper页面滑动事件，在该回调中可以实现自定义导航点切换动画等
      console.info("ygl onContentDidScroll selectedIndex: " + selectedIndex + ", index: " + index +
        ", position: " + position + ", mainAxisLength: " + mainAxisLength);
      this.text = "onContentDidScroll: \n"
        + "selectedIndex: " + selectedIndex + ';\n'
        + "index: " + index + ';\n'
        + "position: " + position + ';\n'
        + "mainAxisLength: " + mainAxisLength
    }),
    undefined]

  @Builder
  tabBuilder(title: string, targetIndex: number) {
    Column() {
      Text(title).fontColor(this.currentIndex === targetIndex ? '#FF0000' : '#6B6B6B')
    }.width('100%')
    .height(50)
    .justifyContent(FlexAlign.Center)
  }

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.End, controller: this.controller, index: this.currentIndex }) {
        ForEach(this.data, (item: string) => {
          TabContent() {
            Column() {
              Text('' + item)
            }.width('100%').height('100%').backgroundColor('#00CB87').justifyContent(FlexAlign.Center)
          }.tabBar(this.tabBuilder('P' + item, parseInt(item)))
        }, (item: string) => item)
      }
      .barWidth(360)
      .barHeight(60)
      .animationDuration(4000)
      .onChange((index: number) => {
        this.currentIndex = index;
      })
      .width(360)
      .height(360)
      .backgroundColor('#F1F3F5')
      .onContentDidScroll(this.isOnContentDidScroll[this.isOnContentDidScrollIndex])


      Button('onContentDidScroll:' + this.isOnContentDidScroll[this.isOnContentDidScrollIndex])
        .margin({ bottom: '12vp' })
        .onClick((event?: ClickEvent) => {
          this.isOnContentDidScrollIndex++
          if (this.isOnContentDidScrollIndex > this.isOnContentDidScroll.length - 1) {
            this.isOnContentDidScrollIndex = 0
          }
        })
      // Text('onContentDidScroll: ' + this.text)

    }.width('100%')
  }
}
