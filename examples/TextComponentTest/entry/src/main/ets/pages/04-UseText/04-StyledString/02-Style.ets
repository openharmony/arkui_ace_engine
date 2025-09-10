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

import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct styled_string_demo2 {
  textStyleAttrs: TextStyle =
    new TextStyle({ fontWeight: FontWeight.Bolder, fontSize: LengthMetrics.vp(24),
      fontStyle: FontStyle.Italic, strokeWidth: LengthMetrics.px(5), strokeColor: Color.Green });
  mutableStyledString: MutableStyledString = new MutableStyledString('运动45分钟 目标达成', [
    {
      start: 2,
      length: 2,
      styledKey: StyledStringKey.FONT,
      styledValue: this.textStyleAttrs
    },
    {
      start: 7,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Orange, fontSize: LengthMetrics.vp(12),
        superscript: SuperscriptStyle.SUPERSCRIPT })
    }
  ]);
  controller: TextController = new TextController();

  async onPageShow() {
    this.controller.setStyledString(this.mutableStyledString);
  }

  build() {
    Column() {
      // 显示属性字符串
      Text(undefined, { controller: this.controller })
        .margin({ top: 10 })
    }
    .width('100%')
  }
}