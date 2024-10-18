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
import navigationTitleTest from '../MyTest/NavigationTitleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct NavigationTitleSample {
  aboutToAppear(): void {
    loadComponentTestEntry(navigationTitleTest)
  }

  @State titleValue: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle = 'state'
  @State ss: BlurStyle = BlurStyle.Thin

  @Builder
  NavigationTitle() {
    Column() {
      Text('Hi')
        .id('title2')
        .fontSize(30)
        .fontWeight(500)
    }
  }

  @Builder
  NavigationTitle2() {
    Column() {
      Text('hello')
        .fontSize(30)
    }
  }

  build() {
    Column() {
      Navigation() {
      }
      .height(100)
      .width('100%')
      .margin(10)
      .title(this.titleValue)
      .id('navigationTitle1')

      Button('NavigationTitle1')
        .onClick(() => {
          this.titleValue = { main: 'nihao', sub: 'world' }
        }).margin(10)
      Button('NavigationTitle2')
        .onClick(() => {
          this.titleValue = $r("app.string.navigation_title")
        })
      Navigation() {
      }
      .title(this.NavigationTitle())
      .margin(10)
      .height(50)
      .id('navigationTitle2')

      Navigation() {
      }
      .title({ builder: this.NavigationTitle2(), height: TitleHeight.MainOnly },
        { backgroundColor: 0x0000ff, backgroundBlurStyle: BlurStyle.Thick })
      .margin(10)
      .height(50)
      .id('navigationTitle3')

      Navigation() {
      }
      .title({ builder: this.NavigationTitle2(), height: TitleHeight.MainWithSub },
        { backgroundColor: Color.Green, backgroundBlurStyle: BlurStyle.Thin })
      .margin(10)
      .height(100)
      .id('navigationTitle4')

      Navigation() {
      }
      .title({ builder: this.NavigationTitle2(), height: 50 })
      .margin(10)
      .height(100)
      .id('navigationTitle5')

    }
  }
}