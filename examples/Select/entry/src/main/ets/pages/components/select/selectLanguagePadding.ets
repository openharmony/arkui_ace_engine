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

import { SymbolGlyphModifier } from '@ohos.arkui.modifier'

@Builder
export function SelectLanguagePaddingBuilder(name: string, param: Object) {
  SelectLanguagePaddingExample()
}

@Component
struct SelectLanguagePaddingExample {
  pathStack: NavPathStack = new NavPathStack()
  @State text: string = 'This system offers high-performance hardware and efficient software for enhanced computing.'
  @State index: number = 2
  @State space: number = 8
  @State arrowPosition: ArrowPosition = ArrowPosition.END
  @State symbolModifier1: SymbolGlyphModifier =
    new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')).fontColor([Color.Green]);
  @State symbolModifier2: SymbolGlyphModifier =
    new SymbolGlyphModifier($r('sys.symbol.ohos_star')).fontColor([Color.Red]);
  @State symbolModifier3: SymbolGlyphModifier =
    new SymbolGlyphModifier($r('sys.symbol.ohos_trash')).fontColor([Color.Gray]);
  @State symbolModifier4: SymbolGlyphModifier =
    new SymbolGlyphModifier($r('sys.symbol.exposure')).fontColor([Color.Gray]);

  build() {
    NavDestination() {
      Column() {
        Text('场景：Select的左右间距，在切换语言的时候，变化情况')
          .margin({ top: 100, bottom: 100 })
        Select([{ value: '菜单1', icon: $r('app.media.app_icon'), symbolIcon: this.symbolModifier1 },
          { value: '菜单2', icon: $r('app.media.app_icon'), symbolIcon: this.symbolModifier2 },
          { value: '菜单3', icon: $r('app.media.app_icon'), symbolIcon: undefined },
          { value: '菜单4', icon: $r('app.media.app_icon') }])
          .selected(this.index)
          .value(this.text)
          .font({ size: 16, weight: 500 })
          .fontColor($r('app.color.select_font_color'))
          .selectedOptionFont({ size: 16, weight: 400 })
          .optionFont({ size: 16, weight: 400 })
          .space(this.space)
          .arrowPosition(this.arrowPosition)
          .menuAlign(MenuAlignType.CENTER, { dx: 0, dy: 0 })
          .optionWidth(200)
          .optionHeight(300)
          .onSelect((index: number, text?: string | undefined) => {
            console.info('Select:' + index)
            this.index = index;
            if (text) {
              this.text = text;
            }
          })
      }.width('100%')
    }
    .title('SelectLanguagePadding')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { SelectLanguagePaddingExample };