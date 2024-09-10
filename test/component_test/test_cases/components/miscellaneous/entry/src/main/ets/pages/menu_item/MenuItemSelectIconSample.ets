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
// 测试代码路径
import menuItemSelectIconTest from '../MyTest/MenuItemSelectIconTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MenuItemSelectIcon {
  private iconStr: ResourceStr = $r("app.media.app_icon")
  @State selectIcon: boolean | ResourceStr = false

  aboutToAppear(): void {
    loadComponentTestEntry(menuItemSelectIconTest)
  }

  build() {
    Column() {
      Menu() {
        MenuItem({ content: "菜单选项", startIcon: this.iconStr }).selectIcon(this.selectIcon)
          .id('menuItemSelectIcon1')
        MenuItem({ content: "菜单选项", startIcon: this.iconStr })
          .selectIcon("../../../resources/base/media/icon.png")
          .id('menuItemSelectIcon2')
      }

      Button('MenuItemSelectIcon1').onClick(() => {
        this.selectIcon = !this.selectIcon
      })
      Button('MenuItemSelectIcon2').onClick(() => {
        this.selectIcon = $r("sys.media.ohos_app_icon")
      })
    }
  }
}