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

import { ThemeControl } from '@kit.ArkUI';

@Builder
export function SliderLevel10Builder(name: string, param: Object) {
  Slider_Level1_0()
}

ThemeControl.setDefaultTheme(null);

@Entry
@Component
struct Slider_Level1_0 {
  pathStack: NavPathStack = new NavPathStack()
  @State arr: string[] = ['0', '1', '2', '3', '4']
  @State outSetValueOne: number = 40
  @State currentIndex: number = 0
  @State show: boolean = false
  sliderArray: number[] = [0, 0, 0, 0]
  private controller: TabsController = new TabsController()

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 10 }) {
          Text('测试Slider和List的滑动事件会不会互相影响')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          List({ space: 20, initialIndex: 0 }) {
            ForEach(this.arr, (item: string) => {
              ListItem() {
                Slider({
                  value: this.outSetValueOne,
                  min: 0,
                  max: 100,
                  style: SliderStyle.OutSet
                })
                  .showTips(true)
                  .onChange((value: number, mode: SliderChangeMode) => {
                    this.outSetValueOne = value
                    console.info('value:' + value + 'mode:' + mode.toString())
                  })
                  .key('slider1')
                // toFixed(0)将滑动条返回值处理为整数精度
              }
              .width('80%')
              .border({ width: 2, color: Color.Green })
            }, (item: string) => item)
          }
          .listDirection(Axis.Horizontal)
          .height(100)
          .width('80%')
          .borderWidth(2)
          .alignListItem(ListItemAlign.Center)
          .scrollBar(BarState.Off)

          Text('测试Slider组件在Tabs中滑动会不会引起冲突')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Tabs({ barPosition: BarPosition.Start, controller: this.controller }) {
            TabContent() {
              Column() {
                Slider({
                  value: this.outSetValueOne,
                  min: 0,
                  max: 100,
                  style: SliderStyle.OutSet
                })
                  .showTips(true)
                  .width('80%')
                  .backgroundColor(Color.Yellow)
                  .onChange((value: number, mode: SliderChangeMode) => {
                    this.outSetValueOne = value
                    if (value > 50) {
                      this.controller.changeIndex(1)
                    } else {
                      this.controller.changeIndex(0)
                    }
                    console.info('value:' + value + 'mode:' + mode.toString())
                  })
              }
              .width('100%').height('100%').backgroundColor(Color.Pink)
            }.tabBar(new SubTabBarStyle('Pink'))

            TabContent() {
              Column().width('100%').height('100%').backgroundColor(Color.Yellow)
            }.tabBar(new SubTabBarStyle('Yellow'))

            TabContent() {
              Column().width('100%').height('100%').backgroundColor(Color.Blue)
            }.tabBar(new SubTabBarStyle('Blue'))

            TabContent() {
              Column().width('100%').height('100%').backgroundColor(Color.Green)
            }.tabBar(new SubTabBarStyle('Green'))
          }
          .vertical(false)
          .scrollable(true)
          .barMode(BarMode.Fixed)
          .onChange((index: number) => {
            console.info(index.toString())
          })
          .width('100%')
          .height(100)
          .backgroundColor(0xF1F3F5)

          Text('测试用ForEach生成Slider组件').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          ForEach(this.sliderArray, (item: number) => {
            Slider()
          })
          Text('测试if控制Slider组件的显示情况以及slider组件自适应父组件逻辑')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          if (this.show) {
            Column() {
              Slider()
                .key('slider2')
                .backgroundColor(Color.Yellow)
            }
            .width('80%')
            .height(70)
            .borderWidth(2)

          }
          Button('showSlider')
            .onClick(() => {
              this.show = !this.show
            })
        }
        .width('100%')
        .borderWidth(2)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
    }
    .title('SliderLevel10')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}