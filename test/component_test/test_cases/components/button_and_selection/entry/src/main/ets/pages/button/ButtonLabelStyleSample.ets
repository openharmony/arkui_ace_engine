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
import buttonLabelStyleTest from '../MyTest/ButtonLabelStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct ButtonLabelStyleSample {
  @State labelStyOverFlow: TextOverflow = TextOverflow.Ellipsis
  @State labelStyFlowHeight: TextHeightAdaptivePolicy = TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST
  @State labelStyFlowNum: number | string = 100
  @State labelStyNum: number | string = 20
  @State labelStyFlowStyle: FontStyle = FontStyle.Normal

  aboutToAppear(): void {
    loadComponentTestEntry(buttonLabelStyleTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Flex() {
      Column() {
        Button('ButtonLabelStyle1').labelStyle({ overflow: TextOverflow.None }).id('buttonLabelStyle1').width(100);
        Button('ButtonLabelStyle2').labelStyle({ overflow: TextOverflow.Clip }).id('buttonLabelStyle2').width(100);
        Button('ButtonLabelStyle3').labelStyle({ overflow: this.labelStyOverFlow }).id('buttonLabelStyle3').width(100);
        Button('ButtonLabelStyle4').labelStyle({
          maxLines: 3,
          minFontSize: 5,
          maxFontSize: 5
        }).id('buttonLabelStyle4').width(50);
        Button('ButtonLabelStyle5').labelStyle({
          maxLines: 3,
          minFontSize: '5px',
          maxFontSize: '10px'
        }).id('buttonLabelStyle5').width(50);
        Button('ButtonLabelStyle6').labelStyle({
          maxLines: 3,
          minFontSize: $r('app.string.minFont_size'),
          maxFontSize: $r('app.string.maxFont_size')
        }).id('buttonLabelStyle6').width(50);
        Button('ButtonLabelStyle7').labelStyle({
          maxLines: 3,
          minFontSize: -1,
          maxFontSize: 5,
          heightAdaptivePolicy: TextHeightAdaptivePolicy.MAX_LINES_FIRST
        }).id('buttonLabelStyle7').width(100);
        Button('ButtonLabelStyle8').labelStyle({
          heightAdaptivePolicy: this.labelStyFlowHeight
        }).id('buttonLabelStyle8').onClick(() => {
          this.labelStyOverFlow = TextOverflow.MARQUEE;
          this.labelStyFlowHeight = TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST;
        }).width(100);
      }

      Column() {
        Button('ButtonLabelStyle9').labelStyle({
          font: {
            weight: FontWeight.Lighter
          }
        }).id('buttonLabelStyle9').width(200);
        Button('ButtonLabelStyle10').labelStyle({
          font: {
            weight: FontWeight.Normal
          }
        }).id('buttonLabelStyle10').width(200);
        Button('ButtonLabelStyle11').labelStyle({
          font: {
            weight: FontWeight.Regular
          }
        }).id('buttonLabelStyle11').width(200);
        Button('ButtonLabelStyle12').labelStyle({
          font: {
            weight: FontWeight.Medium
          }
        }).id('buttonLabelStyle12').width(200);
        Button('ButtonLabelStyle13').labelStyle({
          font: {
            weight: FontWeight.Bold,
            size: $r('app.string.size')
          }
        }).id('buttonLabelStyle13').width(200);
        Button('ButtonLabelStyle14').labelStyle({
          font: {
            weight: FontWeight.Bolder,
            size: '10',
            family: 'Arial',
            style: this.labelStyFlowStyle
          }
        }).id('buttonLabelStyle14').width(200);
        Button('ButtonLabelStyle15').labelStyle({
          font: {
            weight: this.labelStyFlowNum,
            size: this.labelStyNum,
            family: 'TESTFONT'
          }
        }).id('buttonLabelStyle15').onClick(() => {
          this.labelStyFlowNum = '200';
          this.labelStyNum = '40';
          this.labelStyFlowStyle = FontStyle.Italic;
        }).width(200);
      }
    }
  }
}