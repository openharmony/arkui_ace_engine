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
struct DecorationStyle {
  mutableStyledString: MutableStyledString = new MutableStyledString('运动35分钟', [
    {
      start: 0,
      length: 4,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle({ type: TextDecorationType.LineThrough, color: Color.Red, thicknessScale: 3 })
    },
    {
      start: 4,
      length: 2,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle(
        {
          type: TextDecorationType.Underline,
        },
        {
          // 开启多装饰线
          enableMultiType: true
        }
      )
    },
    {
      start: 4,
      length: 2,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle(
        {
          type: TextDecorationType.LineThrough,
        },
        {
          // 开启多装饰线
          enableMultiType: true
        }
      )
    },
  ]);
  controller: TextController = new TextController();

  async onPageShow() {
    this.controller.setStyledString(this.mutableStyledString);
  }

  build() {
    Column() {
      // 显示属性字符串
      Text(undefined, { controller: this.controller })
    }
    .width('100%')
  }
}