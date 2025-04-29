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
import textClockTextShadowOptionsTest from '../MyTest/TextClockTextShadowOptionsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextClockTextShadowOptionsSample {
  @State textShadow1: ShadowOptions | Array<ShadowOptions> =
    [{
      radius: $r("app.string.data_panel_number"),
      type: ShadowType.BLUR,
      color: "#800080",
      offsetX: $r('app.string.data_panel_offset_radius1'),
      offsetY: $r('app.string.data_panel_offset_radius1')
    },
      {
        radius: $r("app.string.data_panel_number"),
        type: ShadowType.BLUR,
        color: "#FF4500",
        offsetX: $r('app.string.data_panel_offset_radius2'),
        offsetY: $r('app.string.data_panel_offset_radius2')
      }]
  @State textShadow2: ShadowOptions | Array<ShadowOptions> = [{
    radius: 10,
    type: ShadowType.COLOR,
    color: Color.Red,
    offsetX: 10,
    offsetY: 10
  },
    {
      radius: 10,
      type: ShadowType.COLOR,
      color: Color.Yellow,
      offsetX: 30,
      offsetY: 30
    }]
  @State textShadow3: ShadowOptions | Array<ShadowOptions> = [{
    radius: 10,
    type: ShadowType.COLOR,
    color: $r('sys.color.ohos_id_color_text_hyperlink'),
    offsetX: 10,
    offsetY: 10
  },
    {
      radius: 10,
      type: ShadowType.COLOR,
      color: $r('sys.color.ohos_id_color_text_tertiary'),
      offsetX: 30,
      offsetY: 30
    }]
  @State textShadow4: ShadowOptions | Array<ShadowOptions> =
    {
      radius: $r("app.string.data_panel_number"),
      type: ShadowType.BLUR,
      color: "#800080",
      offsetX: $r('app.string.data_panel_offset_radius1'),
      offsetY: $r('app.string.data_panel_offset_radius1')
    }
  @State textShadow5: ShadowOptions | Array<ShadowOptions> = {
    radius: 10,
    type: ShadowType.COLOR,
    color: Color.Blue,
    offsetX: 30,
    offsetY: 30
  }
  @State textShadow6: ShadowOptions | Array<ShadowOptions> = {
    radius: 10,
    type: ShadowType.COLOR,
    color: $r('app.color.data_panel_resource_color2'),
    offsetX: 30,
    offsetY: 30
  }

  aboutToAppear(): void {
    loadComponentTestEntry(textClockTextShadowOptionsTest)
  }

  build() {
    Column({ space: 8 }) {
      TextClock()
        .id('textClockTextShadowOptions1')
        .textShadow(this.textShadow1)
      TextClock()
        .id('textClockTextShadowOptions2')
        .textShadow(this.textShadow3)
      TextClock()
        .id('textClockTextShadowOptions3')
        .textShadow(this.textShadow4)

      Button('TextClockTextShadowOptions1')
        .onClick(() => {
          this.textShadow1 = this.textShadow6
        })
      Button('TextClockTextShadowOptions2')
        .onClick(() => {
          this.textShadow1 = this.textShadow2
        })
      Button('TextClockTextShadowOptions3')
        .onClick(() => {
          this.textShadow1 = this.textShadow5
        })
    }
  }
}