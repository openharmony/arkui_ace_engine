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
import textTimerTextShadowTest from '../MyTest/TextTimerTextShadowTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextTimerTextShadowSample {
  aboutToAppear(): void {
    loadComponentTestEntry(textTimerTextShadowTest)
  }

  @State textShadow1: ShadowOptions | Array<ShadowOptions> = [{
    radius: $r("app.string.text_timer_radius"),
    type: ShadowType.BLUR,
    color: "#FF0000",
    offsetX: $r("app.string.text_timer_offsetX1"),
    offsetY: $r("app.string.text_timer_offsetY1")
  },
    {
      radius: $r("app.string.text_timer_radius"),
      type: ShadowType.BLUR,
      color: "#0000FF",
      offsetX: $r("app.string.text_timer_offsetX2"),
      offsetY: $r("app.string.text_timer_offsetY2")
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
    color: $r("app.color.text_timer_color1"),
    offsetX: 10,
    offsetY: 10
  },
    {
      radius: 10,
      type: ShadowType.COLOR,
      color: $r("app.color.text_timer_color2"),
      offsetX: 30,
      offsetY: 30
    }]
  @State textShadow4: ShadowOptions | Array<ShadowOptions> = {
    radius: $r("app.string.text_timer_radius"),
    type: ShadowType.BLUR,
    color: "#00FF00",
    offsetX: $r("app.string.text_timer_offsetX1"),
    offsetY: $r("app.string.text_timer_offsetY1")
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
    color: $r("app.color.text_timer_color1"),
    offsetX: 50,
    offsetY: 50
  }

  build() {
    Column({ space: 50 }) {
      TextTimer().textShadow(this.textShadow1).id('textTimerTextShadow1')
      Button('TextTimerTextShadow1')
        .onClick(() => {
          this.textShadow1 = this.textShadow2
        })
      TextTimer().textShadow(this.textShadow3).id('textTimerTextShadow2')
      TextTimer().textShadow(this.textShadow4).id('textTimerTextShadow3')
      Button('TextTimerTextShadow2')
        .onClick(() => {
          this.textShadow4 = this.textShadow5
        })
      TextTimer().textShadow(this.textShadow6).id('textTimerTextShadow4')
    }
  }
}