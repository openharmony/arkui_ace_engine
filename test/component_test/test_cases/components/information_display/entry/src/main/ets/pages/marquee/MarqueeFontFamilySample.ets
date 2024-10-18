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
import font from '@ohos.font';
import marqueeFontFamilyTest from '../MyTest/MarqueeFontFamilyTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct MarqueeFontFamilySample {
  @State buttonString: string | Resource = 'iconFont'
  @State start: boolean = true
  private fromStart: boolean = true
  private step: number = 50
  private loop: number = Number.POSITIVE_INFINITY
  private src: string = "Running Marquee starts rolling"

  aboutToAppear() {
    font.registerFont({
      familyName: 'iconFont',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(marqueeFontFamilyTest)
  }

  build() {
    Column({ space: 8 }) {
      Marquee({
        start: this.start,
        step: this.step,
        loop: this.loop,
        fromStart: this.fromStart,
        src: this.src
      }).fontFamily(this.buttonString).width(200).id('marqueeFontFamily')
      Button('MarqueeFontFamily')
        .onClick(() => {
          this.buttonString = "Arial"
        })
    }
  }
}