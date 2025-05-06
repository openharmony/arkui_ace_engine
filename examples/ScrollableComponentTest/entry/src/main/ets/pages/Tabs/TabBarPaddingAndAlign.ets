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

// 通过设置barModifier参数设置tabBar的padding和align属性，可以使页签与tabs边界保持固定间距
import { CommonModifier } from '@kit.ArkUI';

@Entry
@Component
struct TabBarPaddingAndAlignExample {
  private controller: TabsController = new TabsController()
  @State tabBarModifier: CommonModifier = new CommonModifier()

  aboutToAppear(): void {
    // padding属性使tabBar与tabs上边界间距固定，align属性使页签向上对齐，不会居中显示
    this.tabBarModifier.padding({ top: 50 }).align(Alignment.Top).width(75)
  }

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, controller: this.controller, barModifier: this.tabBarModifier }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Pink)
        }.tabBar(SubTabBarStyle.of('Pink'))

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar(SubTabBarStyle.of('Green'))

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Blue)
        }.tabBar(SubTabBarStyle.of('Blue'))

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Yellow)
        }.tabBar(SubTabBarStyle.of('Yellow'))
      }
      .vertical(true)
      .height(500)
      .backgroundColor(0xf1f3f5)
      .barMode(BarMode.Scrollable)
    }
    .width('100%')
    .margin({ top: 5 })
    .padding('24vp')
  }
}