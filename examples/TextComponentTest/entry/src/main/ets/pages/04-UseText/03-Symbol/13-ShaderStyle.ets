/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct OnClickOnTouch {
  radialGradientOptions: RadialGradientOptions = {
    center: ['50%', '50%'],
    radius: '20%',
    colors: [[Color.Red, 0.0], [Color.Blue, 0.3], [Color.Green, 0.5]],
    repeating: true,
  };

  build() {
    Column() {
      Text('径向渐变')
        .fontSize(18)
        .fontColor(0xCCCCCC)
        .textAlign(TextAlign.Center)
      SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
        .fontSize(96)
        .shaderStyle([new RadialGradientStyle(this.radialGradientOptions)])
    }
  }
}