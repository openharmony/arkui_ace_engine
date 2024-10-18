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
import navigationMenusTest from '../MyTest/NavigationMenusTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct NavigationMenusSample {
  @State menus: Array<NavigationMenuItem> | CustomBuilder = this.NavigationMenus()

  aboutToAppear(): void {
    loadComponentTestEntry(navigationMenusTest)
  }

  @Builder
  NavigationMenus() {
    Row() {
      Image($r('sys.media.ohos_ic_public_text'))
        .width(24)
        .height(24)
      Image($r('sys.media.ohos_ic_public_minus'))
        .width(24)
        .height(24)
        .margin({ left: 24 })
      Image($r('sys.media.ohos_app_icon'))
        .width(24)
        .height(24)
        .margin({ left: 24 })
      Text('Exit')
    }
  }

  build() {
    Column() {
      Navigation() {
      }
      .title('hello')
      .menus(this.NavigationMenus())
      .height(100)
      .margin(10)
      .id('navigationMenus1')

      Navigation() {
      }
      .title('world')
      .height(100)
      .margin(10)
      .menus([{ value: "menu", icon: '../../../resources/base/media/test_image.png', action: () => this.NavigationMenus() }])
      .id('navigationMenus2')
    }
  }
}