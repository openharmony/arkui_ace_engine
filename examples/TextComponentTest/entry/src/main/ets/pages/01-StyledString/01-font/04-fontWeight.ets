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
import { LengthMetrics, LengthUnit } from '@kit.ArkUI'

@Entry
@Component
struct struct_01_StyledString_01_StyledStringValue_01_TextStyle_fontWeight {
  @State message: string = '运动45分钟';
  @State start: number = 0
  @State end: number = 5
  @State showValue1: string = ''
  controller1: TextController = new TextController()
  mutableStyledString1: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontWeight: 900 })
  }]);
  @State showValue2: string = ''
  controller2: TextController = new TextController()
  mutableStyledString2: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontWeight: FontWeight.Bolder })
  }]);
  @State showValue3: string = ''
  controller3: TextController = new TextController()
  mutableStyledString3: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontWeight: 'bolder' })
  }]);

  aboutToAppear(): void {
    setTimeout(() => {
      let styles1 = this.mutableStyledString1.getStyles(this.start, this.end)
      let fontAttr1 = styles1[0].styledValue as TextStyle;
      console.info('StyledString fontWeight:' + fontAttr1.fontWeight)
      this.showValue1 = 'getStyles 的值是 ' + fontAttr1.fontWeight?.toString()

      let styles2 = this.mutableStyledString2.getStyles(this.start, this.end)
      let fontAttr2 = styles2[0].styledValue as TextStyle;
      console.info('StyledString fontWeight:' + fontAttr2.fontWeight)
      this.showValue2 = 'getStyles 的值是 ' + fontAttr2.fontWeight?.toString()

      let styles3 = this.mutableStyledString3.getStyles(this.start, this.end)
      let fontAttr3 = styles3[0].styledValue as TextStyle;
      console.info('StyledString fontWeight:' + fontAttr3.fontWeight)
      this.showValue3 = 'getStyles 的值是 ' + fontAttr3.fontWeight?.toString()

    }, 100)
  }

  build() {
    Column() {
      Column() {
        Text('测试 TextStyle fontSize number  类型')
        Text('pass条件：fontWeight 的值是 8 ')
        Text(undefined, { controller: this.controller1 })
        Text(this.showValue1)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle fontSize FontWeight  类型')
        Text('pass条件：fontWeight 的值是 8 ')
        Text(undefined, { controller: this.controller2 })
        Text(this.showValue2)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle fontSize FontWeight  类型')
        Text('pass条件：fontWeight 的值是 8 ')
        Text(undefined, { controller: this.controller3 })
        Text(this.showValue3)
      }.borderWidth(1)

    }
    .height('100%')
    .width('100%')
  }
}