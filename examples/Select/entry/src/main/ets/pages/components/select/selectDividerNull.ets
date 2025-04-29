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

@Builder
export function SelectDividerNullBuilder(name: string, param: Object) {
  SelectDividerNullExample()
}

@Entry
@Component
struct SelectDividerNullExample {
  pathStack: NavPathStack = new NavPathStack()
  @State text: string = 'TTTTT';
  @State index: number = -1;
  @State arrowPosition: ArrowPosition = ArrowPosition.END;

  build() {
    NavDestination() {
      Column() {
        Text('Set divider to null for a dropdown without a divider style.')
          .fontSize('16fp')
          .fontWeight(FontWeight.Bolder)
          .padding({ top: 250, bottom: 20 })
        Select([{ value: 'aaa', icon: $r('app.media.app_icon') },
          { value: 'bbb', icon: $r('app.media.app_icon') },
          { value: 'ccc', icon: $r('app.media.app_icon') },
          { value: 'ddd', icon: $r('app.media.app_icon') }])
          .selected(this.index)
          .value(this.text)
          .font({ size: 16, weight: 500 })
          .fontColor($r('app.color.select_font_color'))
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .divider(null)
          .onSelect((index: number, text?: string | undefined) => {
            console.info('Select:' + index);
            this.index = index;
            if (text) {
              this.text = text;
            }
          })
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#45FFE0E0')
    }
    .title('SelectDividerNull')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}