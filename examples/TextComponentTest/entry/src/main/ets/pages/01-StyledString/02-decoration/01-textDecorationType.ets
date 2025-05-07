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
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({ type: TextDecorationType.Underline })
  }]);
  @State showValue2: string = ''
  controller2: TextController = new TextController()
  mutableStyledString2: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({ type: TextDecorationType.LineThrough })
  }]);
  @State showValue3: string = ''
  controller3: TextController = new TextController()
  mutableStyledString3: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({ type: TextDecorationType.Overline })
  }]);
  @State showValue4: string = ''
  controller4: TextController = new TextController()
  mutableStyledString4: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({ type: TextDecorationType.None })
  }]);

  aboutToAppear(): void {
    setTimeout(() => {
      let styles1 = this.mutableStyledString1.getStyles(this.start, this.end)
      let attr1 = styles1[0].styledValue as DecorationStyle;
      console.info('StyledString TextDecorationType:' + attr1.type)
      this.showValue1 = 'getStyles 的值是 ' + attr1.type?.toString()

      let styles2 = this.mutableStyledString2.getStyles(this.start, this.end)
      let attr2 = styles2[0].styledValue as DecorationStyle;
      console.info('StyledString TextDecorationType:' + attr2.type)
      this.showValue2 = 'getStyles 的值是 ' + attr2.type?.toString()

      let styles3 = this.mutableStyledString3.getStyles(this.start, this.end)
      let attr3 = styles3[0].styledValue as DecorationStyle;
      console.info('StyledString TextDecorationType:' + attr3.type)
      this.showValue3 = 'getStyles 的值是 ' + attr3.type?.toString()

      let styles4 = this.mutableStyledString4.getStyles(this.start, this.end)
      let attr4 = styles4[0].styledValue as DecorationStyle;
      console.info('StyledString TextDecorationType:' + attr4.type)
      this.showValue3 = 'getStyles 的值是 ' + attr4.type?.toString()

    }, 100)
  }

  build() {
    Column() {
      Column() {
        Text('测试 TextStyle DecorationStyle TextDecorationType Underline 枚举值')
        Text('pass条件：type 的值是 1 ')
        Text(undefined, { controller: this.controller1 })
        Text(this.showValue1)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle DecorationStyle TextDecorationType LineThrough 枚举值')
        Text('pass条件：type 的值是 3 ')
        Text(undefined, { controller: this.controller2 })
        Text(this.showValue2)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle DecorationStyle TextDecorationType LineThrough 枚举值')
        Text('pass条件：type 的值是 2 ')
        Text(undefined, { controller: this.controller3 })
        Text(this.showValue3)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle DecorationStyle TextDecorationType LineThrough 枚举值')
        Text('pass条件：type 的值是 0 ')
        Text(undefined, { controller: this.controller4 })
        Text(this.showValue4)
      }.borderWidth(1)

    }
    .height('100%')
    .width('100%')
  }
}