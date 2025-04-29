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
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textTextShadowTest from '../MyTest/TextTextShadowTest'

@Entry
@Component
struct TextTextShadowSample {
  @State textShadowType1: ShadowOptions | Array<ShadowOptions> =
    [{
      radius: $r('app.integer.number'),
      type: ShadowType.BLUR,
      color: $r('sys.color.ohos_id_color_text_tertiary'),
      offsetX: 30,
      offsetY: 30
    },
      {
        radius: $r('app.integer.number'),
        type: ShadowType.BLUR,
        color: "#FF4500",
        offsetX: $r('app.integer.offset_radius2'),
        offsetY: $r('app.integer.offset_radius2')
      }]
  @State textShadowType2: ShadowOptions | Array<ShadowOptions> =
    [{
      radius: $r('app.integer.number'),
      type: ShadowType.BLUR,
      color: 0xffffff,
      offsetX: $r('app.integer.offset_radius1'),
      offsetY: $r('app.integer.offset_radius1'),
      fill: false
    }]

  aboutToAppear(): void {
    loadComponentTestEntry(textTextShadowTest)
  }

  build() {
    Column({ space: 8 }) {
      Text('textShadow').textShadow(this.textShadowType1)
        .id('textTextShadow1')
      Button('TextTextShadow1')
        .onClick(() => {
          this.textShadowType1 = [{
            radius: 10,
            type: ShadowType.COLOR,
            color: Color.Red,
            offsetX: 10,
            offsetY: 10
          },
            {
              radius: 30,
              type: ShadowType.COLOR,
              color: ColoringStrategy.PRIMARY,
              offsetX: 30,
              offsetY: 30
            }]
        })
      Text('textShadow').textShadow(this.textShadowType2)
        .id('textTextShadow2')
      Button('TextTextShadow2')
        .onClick(() => {
          this.textShadowType2 = [{
            radius: 10,
            type: ShadowType.COLOR,
            color: ColoringStrategy.INVERT,
            offsetX: 30,
            offsetY: 30,
            fill: true
          }]
        })
      Text('textShadow').textShadow([{ radius: 10, color: ColoringStrategy.AVERAGE }])
        .id('textTextShadow3')
    }
  }
}