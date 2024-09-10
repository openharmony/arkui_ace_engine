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
import panelCustomHeightTest from '../MyTest/PanelCustomHeightTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PanelCustomHeightSample {
  @State panelCustomHeight: Dimension | PanelHeight = "50px"

  aboutToAppear(): void {
    loadComponentTestEntry(panelCustomHeightTest)
  }

  build() {
    Column() {
      Panel(true) {
        Column() {
          Text('Today Calendar')
          Divider()
          Text('1. afternoon 4:00 The project meeting')
        }
      }
      .customHeight(this.panelCustomHeight)
      .height(120)
      .width(500)
      .id('panelCustomHeight1')

      Panel(true) {
        Column() {
          Text('Today Calendar')
          Divider()
          Text('1. afternoon 4:00 The project meeting')
        }
      }
      .customHeight("50fp")
      .height(120)
      .width(500)
      .id('panelCustomHeight2')

      Panel(true) {
        Column() {
          Text('Today Calendar')
          Divider()
          Text('1. afternoon 4:00 The project meeting')
        }
      }
      .customHeight('50vp')
      .height(120)
      .width(500)
      .id('panelCustomHeight3')

      Button('PanelCustomHeight1')
        .onClick(() => {
          this.panelCustomHeight = $r('app.string.length')
        })
      Button('PanelCustomHeight2')
        .onClick(() => {
          this.panelCustomHeight = PanelHeight.WRAP_CONTENT
        })
      Button('PanelCustomHeight3')
        .onClick(() => {
          this.panelCustomHeight = "50lpx"
        })
      Button('PanelCustomHeight4')
        .onClick(() => {
          this.panelCustomHeight = "50%"
        })
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }
}