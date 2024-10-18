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
import navigationToolbarConfigurationTest from '../MyTest/NavigationToolbarConfigurationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct NavigationToolbarConfigurationSample {
  aboutToAppear(): void {
    loadComponentTestEntry(navigationToolbarConfigurationTest)
  }

  @State toolbarConfiguration1: Array<ToolbarItem> = [{
    value: 'hello',
    icon: $r('sys.media.ohos_ic_public_drawer_open_filled'),
    action: () => this.NavigationTitle(),
    status: ToolbarItemStatus.NORMAL,
    activeIcon: $r('sys.media.ohos_ic_public_location')
  }]
  @State toolbarConfiguration2: NavigationToolbarOptions =
    { backgroundColor: Color.Yellow, backgroundBlurStyle: BlurStyle.Thin }

  @Builder
  NavigationTitle() {
    Column() {
      Text('free')
        .fontSize(30)
        .fontWeight(500)
    }
  }

  build() {
    Column() {
      Navigation() {
      }
      .height(200)
      .width('100%')
      .margin(20)
      .title('title')
      .toolbarConfiguration(this.toolbarConfiguration1, this.toolbarConfiguration2)
      .id('navigationToolbarConfiguration1')

      Button('NavigationToolbarConfiguration1')
        .onClick(() => {
          this.toolbarConfiguration1 = [{
            value: 'hello',
            icon: $r('sys.media.ohos_ic_public_drawer_open_filled'),
            action: () => this.NavigationTitle(),
            status: ToolbarItemStatus.DISABLED,
            activeIcon: $r('sys.media.ohos_ic_public_location')
          }]
          this.toolbarConfiguration2 =
            { backgroundColor: $r("app.color.navigation_color"), backgroundBlurStyle: BlurStyle.Thick }
        })
        .margin(20)
      Button('NavigationToolbarConfiguration2')
        .onClick(() => {
          this.toolbarConfiguration1 = [{
            value: 'hello',
            icon: $r('sys.media.ohos_ic_public_drawer_open_filled'),
            action: () => this.NavigationTitle(),
            status: ToolbarItemStatus.ACTIVE,
            activeIcon: $r('sys.media.ohos_ic_public_location')
          }]
          this.toolbarConfiguration2 = { backgroundColor: 0x0000ff, backgroundBlurStyle: BlurStyle.Regular }
        })
        .margin(20)
      Navigation() {
      }
      .height(100)
      .margin(20)
      .title('hello')
      .toolbarConfiguration(this.NavigationTitle())
      .id('navigationToolbarConfiguration2')
    }
  }
}