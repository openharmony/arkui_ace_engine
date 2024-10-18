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
import marqueeFontWeightTest_two from '../MyTest/MarqueeFontWeightTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MarqueeFontWeightSample_two {
  @State buttonFontWeight: number | FontWeight | string = FontWeight.Regular
  @State buttonString: number | FontWeight | string = FontWeight.Medium
  @State start: boolean = true
  private fromStart: boolean = true
  private step: number = 50
  private loop: number = Number.POSITIVE_INFINITY
  private src: string = "Running Marquee starts rolling"

  aboutToAppear(): void {
    loadComponentTestEntry(marqueeFontWeightTest_two)
  }

  build() {
    Column({ space: 20 }) {
      Marquee({
        start: this.start,
        step: this.step,
        loop: this.loop,
        fromStart: this.fromStart,
        src: this.src
      }).fontWeight(this.buttonString).width(200).id('marqueeFontWeight4')
      Button('MarqueeFontWeight1')
        .onClick(() => {
          this.buttonString = "lighter"
        })
      Marquee({
        start: this.start,
        step: this.step,
        loop: this.loop,
        fromStart: this.fromStart,
        src: this.src
      }).fontWeight(this.buttonFontWeight).width(200).id('marqueeFontWeight5')
      Button('MarqueeFontWeight2')
        .onClick(() => {
          this.buttonFontWeight = FontWeight.Bolder
        })
    }
  }
}