/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { TextModifier } from '@kit.ArkUI';

@Builder
export function SelectOptionTextModifierBuilder(name: string, param: Object) {
  SelectOptionTextModifierExample()
}

@Entry
@Component
struct SelectOptionTextModifierExample {
  pathStack: NavPathStack = new NavPathStack()
  @State text: string = 'TTTTTTTTTT'.repeat(3);
  @State index: number = 2;
  optiontextModifier: TextModifier = new TextModifier();
  selectedOptiontextModifier: TextModifier = new TextModifier();

  aboutToAppear(): void {
    this.optiontextModifier
      .maxLines(1)
      .fontSize(16)
      .textAlign(TextAlign.Start)
      .fontColor($r('app.color.option_text_modifier_color'))
      .fontWeight(FontWeight.Normal)
      .width(200)

    this.selectedOptiontextModifier
      .maxLines(1)
      .fontSize(18)
      .textAlign(TextAlign.Start)
      .fontColor($r('app.color.selected_option_text_modifier_color'))
      .fontWeight(FontWeight.Bold)
      .width(200)
  }

  build() {
    NavDestination() {
      Column() {
        Select([
          {
            value: 'A very long option text that should be truncated nicely'.repeat(3),
            icon: $r('app.media.app_icon')
          },
          { value: 'Option B', icon: $r('app.media.app_icon') },
          { value: 'Option C', icon: $r('app.media.app_icon') },
          { value: 'Option D', icon: $r('app.media.app_icon') }
        ])
          .selected(this.index)
          .value(this.text)
          .onSelect((index: number, text?: string) => {
            console.info('Select:' + index);
            this.index = index;
            if (text) {
              this.text = text;
            }
          })
          .optionTextModifier(this.optiontextModifier)
          .selectedOptionTextModifier(this.selectedOptiontextModifier)
          .width('90%')
          .margin({ top: 20, left: 30 })
          .borderRadius(12)
          .width(200)
          .padding(9)
          .backgroundColor(Color.White)
          .shadow({
            radius: 10,
            color: $r('app.color.shadow'),
            offsetX: 0,
            offsetY: 10
          })
      }
      .alignItems(HorizontalAlign.Start)
      .padding(10)
      .backgroundColor($r('app.color.background_color_5'))
      .width('100%')
      .height('100%')
    }
    .title('SelectModifier')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}