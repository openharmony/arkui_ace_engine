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
import menuRadiusTest from '../MyTest/MenuRadiusTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MenuRadiusSample {
  @State radiusDimensionType: Dimension = '30px'
  @State radiusBorderRadiusesType: BorderRadiuses = {
    topLeft: 50,
    topRight: 50,
    bottomLeft: 50,
    bottomRight: 50
  }

  aboutToAppear(): void {
    loadComponentTestEntry(menuRadiusTest)
  }

  build() {
    Row() {
      Column() {
        Menu() {
          MenuItem({ content: "menu dimension change" })
        }.radius(this.radiusDimensionType).id('menuRadius1')

        Menu() {
          MenuItem({ content: "menu dimension lpx" })
        }.radius('30lpx').id('menuRadius2')

        Menu() {
          MenuItem({ content: "menu dimension %" })
        }.radius('10%').id('menuRadius3')

        Menu() {
          MenuItem({ content: "menu dimension resource" })
        }.radius($r('app.string.length')).id('menuRadius4')
      }

      Column() {
        Menu() {
          MenuItem({ content: "menu radiuses string" })
        }
        .radius({
          topLeft: "10px",
          topRight: "10px",
          bottomLeft: "10px",
          bottomRight: "10px"
        })
        .id('menuRadius5')

        Menu() {
          MenuItem({ content: "menu radiuses change" })
        }.radius(this.radiusBorderRadiusesType).id('menuRadius6')

        Button('MenuRadius1')
          .onClick(() => {
            this.radiusDimensionType = '100vp'
          })
        Button('MenuRadius2')
          .onClick(() => {
            this.radiusDimensionType = '10fp'
          })
        Button('MenuRadius3')
          .onClick(() => {
            this.radiusBorderRadiusesType = {
              topLeft: $r('app.string.length'),
              topRight: $r('app.string.length'),
              bottomLeft: $r('app.string.length'),
              bottomRight: $r('app.string.length')
            }
          })
      }
    }
  }
}