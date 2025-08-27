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

import { SymbolGlyphModifier, TextModifier, ThemeControl } from '@kit.ArkUI';

@Builder
export function SelectLevel2Builder(name: string, param: Object) {
  SelectLevel2Example()
}

ThemeControl.setDefaultTheme(null);

interface CasesObject2 {
  avoidance?: AvoidanceMode | undefined | null
  menuAlignType?: MenuAlignType | undefined,
  optionHeight?: number | undefined,
  position?: Position | undefined,
  offset?: Offset | undefined,
  optionWidth?: number | undefined
  menuOutline?: MenuOutlineOptions | undefined
  textModifier?: Optional<TextModifier>
  arrowModifier?: Optional<SymbolGlyphModifier>
  optionTextModifier?: Optional<TextModifier>
  selectedOptionTextModifier?: Optional<TextModifier>
}

@Entry
@Component
struct SelectLevel2Example {
  pathStack: NavPathStack = new NavPathStack()
  @State noneValueOne: number = 200
  @State noneValueOney: number = 200
  @State noneValueOnew: number = 100
  @State noneValueOne0: number = 250
  @State avoidance1: AvoidanceMode | undefined | null = undefined
  @State MenuAlignType1: MenuAlignType | undefined = undefined
  @State index: number = 0
  private testCases: CasesObject2[] = [
    {
      //0
      avoidance: undefined,
      menuAlignType: undefined,
      optionHeight: undefined,
      optionWidth: undefined,
      position: undefined,
      menuOutline: undefined,
      textModifier: undefined,
      arrowModifier: undefined,
      optionTextModifier: undefined,
      selectedOptionTextModifier: undefined
    },
    {
      //1
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.END,
      optionHeight: 488,
      optionWidth: 100,
      position: { x: 200, y: 240 },
      menuOutline: {
        width: 5,
        color: Color.Green
      },
      textModifier: new TextModifier().fontColor(Color.Red),
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.ohos_star')).fontSize(16)
        .fontColor([Color.Green])
        .fontWeight(FontWeight.Bolder)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      optionTextModifier: new TextModifier().fontColor(Color.Red),
      selectedOptionTextModifier: new TextModifier().fontColor(Color.Yellow)
    },
    {
      //2
      avoidance: AvoidanceMode.COVER_TARGET,
      menuAlignType: MenuAlignType.END,
      optionHeight: 488,
      optionWidth: 100,
      position: { x: 200, y: 240 },
      menuOutline: {
        width: '5px',
        color: 0XFFEFD5
      },
      textModifier: new TextModifier().fontStyle(FontStyle.Italic),
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.arrow_up_house')).fontSize('60px')
        .fontColor([Color.Blue])
        .fontWeight('lighter')
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      optionTextModifier: new TextModifier().fontStyle(FontStyle.Italic),
      selectedOptionTextModifier: new TextModifier().fontColor(0XFFEFD5).fontStyle(FontStyle.Italic)
    },
    {
      //3
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.CENTER,
      optionHeight: 250,
      optionWidth: 260,
      position: { x: 200, y: 240 },
      menuOutline: {
        width: '6vp',
        color: 6200067
      },
      textModifier: new TextModifier().fontSize(20),
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.cross_store')).fontSize($r('app.float.float_80'))
        .fontColor([6256767, 0XFFFFFF00, '#088F9F'])
        .fontWeight(FontWeight.Bolder)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      optionTextModifier: new TextModifier().fontSize(20),
      selectedOptionTextModifier: new TextModifier().fontColor(0XFFFFFF00).fontSize(16)
    },
    {
      //4
      avoidance: undefined,
      menuAlignType: MenuAlignType.START,
      optionHeight: 550,
      optionWidth: 160,
      position: { x: 200, y: 550 },
      menuOutline: {
        width: '3fp',
        color: '#808000'
      },
      textModifier: new TextModifier().fontWeight(FontWeight.Bolder),
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')).fontSize($r('sys.float.dialog_font_size'))
        .fontColor(['#FFC0D9D9', 'rgb(128, 128, 0)'])
        .fontWeight(FontWeight.Lighter)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      optionTextModifier: new TextModifier().fontWeight(FontWeight.Bolder),
      selectedOptionTextModifier: new TextModifier().fontColor('rgb(0,255,0)')
    },
    {
      //5
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.CENTER,
      optionHeight: 550,
      optionWidth: 260,
      position: { x: 200, y: 650 },
      menuOutline: {
        width: '5lpx',
        color: 'rgb(138,43,226)'
      },
      textModifier: new TextModifier().fontFamily('huawen').fontSize(24),
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.blur_bar'))
        .fontColor([$r('sys.color.ohos_id_text_overlay_menu_border_color')])
        .fontWeight('medium')
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      optionTextModifier: new TextModifier().fontFamily('huawen').fontSize(24),
      selectedOptionTextModifier: new TextModifier().fontColor('rgba(138,43,226,0.2)')
    },
    {
      //6
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.CENTER,
      optionHeight: 150,
      optionWidth: 100,
      position: { x: 150, y: 650 },
      menuOutline: {
        width: '5%',
        color: 'rgba(0,128,0,0.3)'
      },
      textModifier: new TextModifier().fontWeight('lighter'),
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.arrow_left_circle')).fontSize($r('app.string.Size100'))
        .fontColor([Color.Green])
        .fontWeight(undefined)
        .renderingStrategy(SymbolRenderingStrategy.SINGLE),
      optionTextModifier: new TextModifier().fontWeight('lighter'),
      selectedOptionTextModifier: new TextModifier().fontColor($r('app.color.Color_pink'))
    },
    {
      //7
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.START,
      optionHeight: 550,
      optionWidth: 260,
      position: { x: 2, y: 650 },
      menuOutline: {
        width: $r('app.float.float_2'),
        color: $r('sys.color.multi_color_aux_05')
      },
      textModifier: new TextModifier().fontColor(Color.Blue),
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.ad_circle_slash'))
        .fontColor([Color.Green])
        .fontWeight(250)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      optionTextModifier: new TextModifier().fontColor(Color.Blue),
      selectedOptionTextModifier: new TextModifier().fontColor($r('sys.color.ohos_id_color_alert'))
    },
    {
      //8
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.START,
      optionHeight: 550,
      optionWidth: 100,
      position: { x: 2, y: 350 },
      menuOutline: {
        width: 4,
        color: $r('app.color.Color_red')
      },
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.ohos_star')).fontSize('100fp')
        .fontColor([Color.Red])
        .fontWeight(FontWeight.Regular)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      selectedOptionTextModifier: new TextModifier().fontColor($r('app.color.Color_red'))
    },
    {
      //9
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.CENTER,
      optionHeight: 550,
      optionWidth: 300,
      position: { x: 2, y: 350 },
      menuOutline: {
        width: {
          left: 1,
          right: $r('app.float.float_2'),
          top: 3,
          bottom: 4
        },
        color: Color.Green
      },
      arrowModifier: new SymbolGlyphModifier($r('sys.symbol.a_5k_rectangle')).fontSize(20)
        .fontColor([Color.Green])
        .fontWeight(800)
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
      selectedOptionTextModifier: new TextModifier().fontSize(22).fontColor('#FFFF7E00')
    },
    {
      //10
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.START,
      optionHeight: 550,
      optionWidth: 300,
      position: { x: 2, y: 120 },
      menuOutline: {
        width: 4,
        color: {
          left: Color.Orange,
          right: '#808000',
          top: '#228B22',
          bottom: 0XFF4500
        }
      },
      arrowModifier: undefined,
      optionTextModifier: new TextModifier().fontSize(25).fontColor('#FFFF7E00'),
      selectedOptionTextModifier: new TextModifier().fontColor(Color.Green)
        .fontStyle(FontStyle.Italic)
        .fontWeight(FontWeight.Medium)
    },
    {
      //11
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.START,
      optionHeight: 550,
      optionWidth: 300,
      position: { x: 110, y: 300 },
      menuOutline: {
        width: {
          left: '8fp',
          right: '3vp',
          top: '20px',
          bottom: '26lpx'
        },
        color: {
          left: $r('sys.color.multi_color_aux_05'),
          right: '#808000',
          top: 'rgb(138,43,226)',
          bottom: $r('app.string.Color4169E1')
        }
      },
      textModifier: new TextModifier().fontSize(25).fontColor('#FFFF7E00'),
      selectedOptionTextModifier: new TextModifier().fontColor(Color.Blue).fontWeight(FontWeight.Lighter)
    },
    {
      //12
      avoidance: AvoidanceMode.AVOID_AROUND_TARGET,
      menuAlignType: MenuAlignType.START,
      optionHeight: 550,
      optionWidth: 300,
      position: { x: 110, y: 400 },
      textModifier: new TextModifier().fontColor('#8B008B'),
      selectedOptionTextModifier: new TextModifier().fontSize(22).fontColor('#9400D3').textShadow({
        radius: 10,
        color: Color.Black,
        offsetX: 1,
        offsetY: 1
      })
    }
  ]
  font = this.getUIContext().getFont();

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Divider()
        Row({ space: 5 }) {
          Text(`${this.index} /`)
            .fontSize(15)
            .focusable(false)
          Text(`${this.testCases.length - 1}`)
            .fontSize(15)
            .key(`totalTest`)
            .focusable(false)
          Text('Test++')
            .fontSize(15)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .focusable(false)
            .onClick(() => {
              this.index++
              if (this.index >= this.testCases.length) {
                this.index = 0
              }
            })
          Text('Test--')
            .fontSize(15)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .focusable(false)
            .onClick(() => {
              this.index--
              if (this.index < 0) {
                this.index = this.testCases.length - 1
              }
            })
        }

        Select([{ value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' },
          { value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' },
          { value: '选项1' }, { value: '选项2' }, { value: '选项3' }, { value: '选项4' }, { value: '选项5' }])
          .selected(1)
          .value('点击弹出菜单')
          .key('2Select2')
          .avoidance(this.testCases[this.index].avoidance)
          .position(this.testCases[this.index].position)
          .menuAlign(this.testCases[this.index].menuAlignType, this.testCases[this.index].offset)
          .optionWidth(this.testCases[this.index].optionWidth)
          .optionHeight(this.testCases[this.index].optionHeight)
          .menuOutline(this.testCases[this.index].menuOutline)
          .textModifier(this.testCases[this.index].textModifier)
          .arrowModifier(this.testCases[this.index].arrowModifier)
          .optionTextModifier(this.testCases[this.index].optionTextModifier)
          .selectedOptionTextModifier(this.testCases[this.index].selectedOptionTextModifier)
      }
      .height('80%')
    }
    .title('SelectLevel2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}