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
import progressStyleCapsuleStyleOptionsTest from '../MyTest/ProgressStyleCapsuleStyleOptionsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressStyleCapsuleStyleOptionsSample {
  aboutToAppear(): void {
    loadComponentTestEntry(progressStyleCapsuleStyleOptionsTest)
  }

  @State style: CapsuleStyleOptions = {
    borderColor: Color.Green,
    borderWidth: 10,
    content: 'hello',
    font: {
      size: 5,
      weight: 300,
      family: 'Arial',
      style: FontStyle.Normal
    },
    fontColor: Color.Orange,
    enableScanEffect: false,
    enableSmoothEffect: true,
    showDefaultPercentage: true
  }

  build() {
    Column() {
      Progress({ value: 100, total: 100, type: ProgressType.Capsule })
        .height(10)
        .width(200)
        .color(Color.Blue)
        .value(60)
        .width(100)
        .style(this.style)
        .margin(20)
        .id('progressStyleCapsuleStyleOptions')
      Button('ProgressStyleCapsuleStyleOptions1')
        .onClick(() => {
          this.style = {
            borderColor: 0x0000ff,
            borderWidth: '10px',
            content: 'hello',
            font: {
              size: '5px',
              weight: FontWeight.Lighter,
              family: $rawfile('TESTFONT.TTF'),
              style: FontStyle.Italic
            },
            fontColor: 0x666666,
            enableScanEffect: false,
            enableSmoothEffect: true,
            showDefaultPercentage: true
          }
        })
        .margin(10)
      Button('ProgressStyleCapsuleStyleOptions2')
        .onClick(() => {
          this.style = {
            borderColor: '#0000ff',
            borderWidth: $r("app.string.border_width_length"),
            content: 'test',
            font: {
              size: $r("app.string.font_size_progress"),
              weight: '5px',
              family: 'Arial',
              style: FontStyle.Italic
            },
            fontColor: '#fff888',
            enableScanEffect: false,
            enableSmoothEffect: false,
            showDefaultPercentage: true
          }
        })
      Button('ProgressStyleCapsuleStyleOptions3')
        .onClick(() => {
          this.style = {
            borderColor: $r('app.color.borderColor'),
            borderWidth: 10,
            font: {
              size: 5,
              weight: 500,
              family: 'Arial',
              style: FontStyle.Italic
            },
            fontColor: Color.Pink,
            enableScanEffect: true,
            enableSmoothEffect: true,
            showDefaultPercentage: false
          }
        })
    }
  }
}