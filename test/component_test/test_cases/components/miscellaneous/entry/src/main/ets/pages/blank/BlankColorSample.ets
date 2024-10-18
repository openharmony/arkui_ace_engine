/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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
import blankColorTest from '../MyTest/BlankColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BlankColorSample {
  @State blankColor: ResourceColor = 'rgb(255, 100, 255)'

  aboutToAppear(): void {
    loadComponentTestEntry(blankColorTest)
  }

  build() {
    Column() {
      Row() {
        Text('BlankColor1')
        Blank().color(Color.Yellow)
          .id('blankColor1')
      }.width('100%')

      Row() {
        Text('BlankColor2')
        Blank().color(0xffff0000)
          .id('blankColor2')
      }.width('100%')

      Row() {
        Text('BlankColor3')
        Blank().color(this.blankColor)
          .id('blankColor3')
      }.width('100%')

      Button('BlankColor').onClick(() => {
        this.blankColor = $r('sys.color.ohos_fa_connected')
      })
    }
  }
}