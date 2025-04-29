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

// 测试代码路径
import buttonFontWeightTest from '../MyTest/ButtonFontWeightTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ButtonFontWeightSample {
  @State fontWeightEnum: FontWeight = FontWeight.Regular
  @State fontWeightTest: number | string = 200

  aboutToAppear(): void {
    loadComponentTestEntry(buttonFontWeightTest)
  }

  build() {
    Column() {
      Button('ButtonFontWeight1').fontWeight(FontWeight.Lighter).id('buttonFontWeight1');
      Button('ButtonFontWeight2').fontWeight(FontWeight.Normal).id('buttonFontWeight2');
      Button('ButtonFontWeight3').fontWeight(this.fontWeightEnum).id('buttonFontWeight3');
      Button('ButtonFontWeight4').fontWeight(FontWeight.Bold).id('buttonFontWeight4');
      Button('ButtonFontWeight5').fontWeight(FontWeight.Bolder).id('buttonFontWeight5');
      Button('ButtonFontWeight6').fontWeight(this.fontWeightTest).id('buttonFontWeight6').onClick(() => {
        this.fontWeightEnum = FontWeight.Medium
        this.fontWeightTest = '700'
      });
    }
  }
}