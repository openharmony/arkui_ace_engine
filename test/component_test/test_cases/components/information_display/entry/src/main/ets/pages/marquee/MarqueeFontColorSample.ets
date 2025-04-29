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
import marqueeFontColorTest from '../MyTest/MarqueeFontColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MarqueeFontColorSample {
  @State colorResource: ResourceColor = "#FFF000"
  @State start: boolean = true
  private fromStart: boolean = true
  private step: number = 50
  private loop: number = Number.POSITIVE_INFINITY
  private src: string = "Running Marquee starts rolling"

  aboutToAppear(): void {
    loadComponentTestEntry(marqueeFontColorTest)
  }

  build() {
    Column({ space: 40 }) {
      Marquee({
        start: this.start,
        step: this.step,
        loop: this.loop,
        fromStart: this.fromStart,
        src: this.src
      }).fontColor(0x66FF66).width(200).id('marqueeFontColor1')
      Marquee({
        start: this.start,
        step: this.step,
        loop: this.loop,
        fromStart: this.fromStart,
        src: this.src
      }).fontColor(Color.Red).width(200).id('marqueeFontColor2')
      Marquee({
        start: this.start,
        step: this.step,
        loop: this.loop,
        fromStart: this.fromStart,
        src: this.src
      }).fontColor(this.colorResource).width(200).id('marqueeFontColor3')
      Button('MarqueeFontColor')
        .onClick(() => {
          this.colorResource = $r("app.color.marquee_font_color")
        })
    }
  }
}