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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';

@Component
export struct SymbolGlyphBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFontColor1: boolean = false;
  @State fontColor1: ResourceColor | undefined = undefined;
  @State enableFontColor2: boolean = false;
  @State fontColor2: ResourceColor | undefined = undefined;
  @State enableFontColor3: boolean = false;
  @State fontColor3: ResourceColor | undefined = undefined;
  @State enableFontSize: boolean = false;
  @State fontSize: number | undefined = undefined;
  @State enableFontWeight: boolean = false;
  @State fontWeight: FontWeight | number | string = FontWeight.Normal;
  @State enableRenderingStrategy: boolean = false;
  @State renderingStrategy: SymbolRenderingStrategy = SymbolRenderingStrategy.SINGLE
  @State enableEffectStrategy: boolean = false;
  @State effectStrategy: SymbolEffectStrategy = SymbolEffectStrategy.NONE
  @State enableSymbolEffectIsActive: boolean = false;
  @State symbolEffectIsActive: boolean = false;
  @State enableSymbolEffectTriggerValue: boolean = false;
  @State symbolEffectTriggerValue: number = -1;
  @State replace: boolean = true




  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row({ space: 10 }) {
      Column() {
        SymbolGlyph(($r('sys.symbol.ohos_folder_badge_plus')))
          .width(50)
          .height(50)
          .fontColor([useEnabled(this.enableFontColor1, this.fontColor1),
            useEnabled(this.enableFontColor2, this.fontColor2),
            useEnabled(this.enableFontColor3, this.fontColor3)])
          .fontSize(useEnabled(this.enableFontSize, this.fontSize))
          .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
          .renderingStrategy(useEnabled(this.enableRenderingStrategy, this.renderingStrategy))
          .effectStrategy(useEnabled(this.enableEffectStrategy, this.effectStrategy))

      }

      if (this.enableSymbolEffectIsActive) {
        Column() {
          SymbolGlyph($r('sys.symbol.ohos_wifi'))
            .fontSize(96)
            .symbolEffect(new HierarchicalSymbolEffect(EffectFillStyle.ITERATIVE),
              useEnabled(this.enableSymbolEffectIsActive, this.symbolEffectIsActive))
          Button(this.symbolEffectIsActive ? '关闭' : '播放').onClick(() => {
            this.symbolEffectIsActive = !this.symbolEffectIsActive;
          })
        }.margin({ right: 20 })
      }
      if (this.enableSymbolEffectTriggerValue) {
        Column() {
          SymbolGlyph(true ? $r('sys.symbol.checkmark_circle') : $r('sys.symbol.repeat_1'))
            .fontSize(96)
            .symbolEffect(new ReplaceSymbolEffect(EffectScope.WHOLE),
              useEnabled(this.enableSymbolEffectTriggerValue, this.symbolEffectTriggerValue))
          Button('trigger').onClick(() => {
            this.replace = !this.replace;
            this.symbolEffectTriggerValue = this.symbolEffectTriggerValue + 1;
          })
        }.margin({ left: 30, top: 50 })

      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        ColorBlock({
          title: 'fontColor1',
          isEnabled: this.enableFontColor1,
          color: this.fontColor1
        })

        ColorBlock({
          title: 'fontColor2',
          isEnabled: this.enableFontColor2,
          color: this.fontColor2
        })

        ColorBlock({
          title: 'fontColor3',
          isEnabled: this.enableFontColor3,
          color: this.fontColor3
        })

        SliderBlock({
          title: 'fontSize',
          isEnabled: this.enableFontSize,
          value: this.fontSize,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'fontWeight',
          isEnabled: this.enableFontWeight,
          value: this.fontWeight,
          dataSource: [
            { label: '100', value: 100 },
            { label: '200', value: 200 },
            { label: '300', value: 300 },
            { label: '400', value: 400 },
            { label: '500', value: 500 },
            { label: '600', value: 600 },
            { label: '700', value: 700 },
            { label: '800', value: 800 },
            { label: '900', value: 900 },
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title: 'renderingStrategy',
          isEnabled: this.enableRenderingStrategy,
          value: this.renderingStrategy,
          dataSource: [
            { label: 'SINGLE', value: SymbolRenderingStrategy.SINGLE },
            { label: 'MULTIPLE_COLOR', value: SymbolRenderingStrategy.MULTIPLE_COLOR },
            { label: 'MULTIPLE_OPACITY', value: SymbolRenderingStrategy.MULTIPLE_OPACITY },
          ]
        })

        RadioBlock({
          title: 'effectStrategy',
          isEnabled: this.enableEffectStrategy,
          value: this.effectStrategy,
          dataSource: [
            { label: 'NONE', value: SymbolEffectStrategy.NONE },
            { label: 'SCALE', value: SymbolEffectStrategy.SCALE },
            { label: 'HIERARCHICAL', value: SymbolEffectStrategy.HIERARCHICAL },
          ]
        })

        RadioBlock({
          title: 'symbolEffect.isActive',
          isEnabled: this.enableSymbolEffectIsActive,
          value: this.symbolEffectIsActive,
          dataSource: [
            { label: 'true', value: true},
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'symbolEffect.triggerValue',
          isEnabled: this.enableSymbolEffectTriggerValue,
          value: this.symbolEffectTriggerValue,
          min: -1,
          max: 10
        })

      }
    }
  }
}

@Preview
@Component
struct SymbolGlyphBootcampPreviewer {
  build() {
    SymbolGlyphBootcamp({
      title: 'SymbolGlyph'
    })
  }
}