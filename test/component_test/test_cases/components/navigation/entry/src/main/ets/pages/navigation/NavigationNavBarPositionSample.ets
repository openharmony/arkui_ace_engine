/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import navigationNavBarPositionTest from '../MyTest/NavigationNavBarPositionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct NavigationNavBarPositionSample {
  aboutToAppear(): void {
    loadComponentTestEntry(navigationNavBarPositionTest)
  }

  @State navBarPosition: NavBarPosition = NavBarPosition.Start
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

  build() {
    Column() {
      Navigation() {
        TextInput({ placeholder: 'search...' })
          .width('90%')
          .height(40)
          .backgroundColor('#FFFFFF')
          .margin({ top: 8 })

        List({ space: 12, initialIndex: 0 }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('80%')
                .height(72)
                .backgroundColor(Color.Pink)
                .borderRadius(24)
                .fontSize(16)
                .fontWeight(500)
                .textAlign(TextAlign.Center)
            }
          }, (item: number) => item.toString())
        }
        .height(324)
        .width('100%')
        .margin({ top: 12, left: '10%' })
      }
      .title('hello')
      .height(300)
      .toolbarConfiguration([{ value: 'hello', icon: $r('sys.media.ohos_ic_public_drawer_open_filled') }])
      .navBarWidth(200)
      .mode(NavigationMode.Split)
      .navBarPosition(this.navBarPosition)
      .id('navigationNavBarPosition')

      Button('NavigationNavBarPosition')
        .onClick(() => {
          this.navBarPosition = NavBarPosition.End
        })
    }
  }
}