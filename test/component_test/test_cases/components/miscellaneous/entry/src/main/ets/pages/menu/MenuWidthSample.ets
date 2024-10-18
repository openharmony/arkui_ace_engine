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
import menuWidthTest from '../MyTest/MenuWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MenuWidthSample {
  @State widthType: Length = 220

  aboutToAppear(): void {
    loadComponentTestEntry(menuWidthTest)
  }

  build() {
    Column() {
      Menu() {
        MenuItem({ content: "width" })
      }.width(this.widthType).id('menuWidth1')

      Menu() {
        MenuItem({ content: "width" })
      }.width($r('app.string.menu_width')).id('menuWidth2')

      Button('MenuWidth')
        .onClick(() => {
          this.widthType = '200px'
        })
    }
  }
}