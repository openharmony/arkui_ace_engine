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
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';

const fontSizeList:(string|number|Resource|null|undefined)[] = [
  30, -30, 30, '30px', '30lpx', '30fp', '30vp', null, undefined, 0
]

const fontSizeTextList:(string)[] = [
  'fontSize30',
  'fontSize-30',
  'fontSizeResourceInteger',
  'fontSize30px',
  'fontSize30lpx',
  'fontSize30fp',
  'fontSize30vp',
  'fontSizeNull',
  'fontSizeUndefined',
  'fontSize0'
]

@Component
export struct FontSizeToggle {
  @Link fontSize: number|string|Resource|null|undefined

  build() {
    Flex({wrap: FlexWrap.Wrap}) {
      ForEach(fontSizeTextList, (text:string, index) => {
        Button(text)
          .key(text)
          .fontSize(10)
          .margin(2)
          .padding(2)
          .height(24)
          .onClick(() => {
            this.fontSize = fontSizeList[index]
          })
      })
    }
  }
}


//切换图标
@Component
export struct SysSymbolToggle {
  @State symbolTextList:string[] = [
    'ohos_folder_badge_plus',
    'trash_circle',
    'ohos_trash',
    'picture',
    'ohos_lungs'
  ]
  @State symbolList: SymbolGlyphModifier[]= [
    new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')),
    new SymbolGlyphModifier($r('sys.symbol.trash_circle')),
    new SymbolGlyphModifier($r('sys.symbol.ohos_trash')),
    new SymbolGlyphModifier($r('sys.symbol.picture')),
    new SymbolGlyphModifier($r('sys.symbol.ohos_lungs')),
  ]
  @Link icon:SymbolGlyphModifier

  build() {
    Flex({wrap: FlexWrap.Wrap}) {
      ForEach(this.symbolTextList, (text: string, index) => {
        Button(text)
          .key(text)
          .fontSize(10)
          .margin(2)
          .padding(2)
          .height(24)
          .onClick(() => {
            this.icon = this.symbolList[index]
          })
      })
    }
  }
}

const fontWeightList:(null|undefined|number|string|FontWeight)[] = [
  0, 100, 500, 900, FontWeight.Lighter, FontWeight.Bolder, '100', null, undefined
]

const fontWeightTextList:(string)[] = [
  'fontWeight0',
  'fontWeight100',
  'fontWeight500',
  'fontWeight900',
  'fontWeightLighter',
  'fontWeightBolder',
  'fontWeightString100',
  'fontWeightNull',
  'fontWeightUndefined'
]

// 切换fontWeight
@Component
export struct FontWeightToggle {
  @Link fontWeight:null|undefined|number|string|FontWeight

  build() {
    Flex({wrap: FlexWrap.Wrap}) {
      ForEach(fontWeightTextList, (text: string, index) => {
        Button(text)
          .key(text)
          .fontSize(10)
          .margin(2)
          .padding(2)
          .height(24)
          .onClick(() => {
            this.fontWeight = fontWeightList[index]
          })
      })
    }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10})
  }
}

// NavigationTitleMode切换
@Component
export struct NavigationTitleModeRadio {
  @Link titleMode:NavigationTitleMode

  build() {
    Column() {
      Row({space:5}){
        Text('NavigationTitleMode:').fontSize(10)
        Row(){
          Radio({ value: 'Radio1', group: 'radioGroup1' }).checked(false)
            .key('NavigationTitleModeFree')
            .width(12)
            .height(12)
            .radioStyle({
              checkedBackgroundColor: Color.Pink,
            })
            .onChange((isChecked: boolean) => {
              this.titleMode = NavigationTitleMode.Free
            })
          Text('Free').fontSize(10)
        }

        Row(){
          Radio({ value: 'Radio2', group: 'radioGroup1' }).checked(true)
            .key('NavigationTitleModeMini')
            .width(12)
            .height(12)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .onChange((isChecked: boolean) => {
              this.titleMode = NavigationTitleMode.Mini
            })
          Text('Mini').fontSize(10)
        }

        Row(){
          Radio({ value: 'Radio3', group: 'radioGroup1' }).checked(false)
            .key('NavigationTitleModeFull')
            .width(12)
            .height(12)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .onChange((isChecked: boolean) => {
              this.titleMode = NavigationTitleMode.Full
            })
          Text('Full').fontSize(10)
        }
      }
    }.backgroundColor(0xFFFFFF).width('100%')
  }
}

@Component
export struct RenderingStrategyToggle {
  @Link renderingStrategy:SymbolRenderingStrategy
  @State renderingStrategyList: SymbolRenderingStrategy[] = [
    SymbolRenderingStrategy.SINGLE,
    SymbolRenderingStrategy.MULTIPLE_COLOR,
    SymbolRenderingStrategy.MULTIPLE_OPACITY
  ]
  @State renderingStrategyText: string[] = [
    'SymbolRenderingStrategy.SINGLE',
    'SymbolRenderingStrategy.MULTIPLE_COLOR',
    'SymbolRenderingStrategy.MULTIPLE_OPACITY'
  ]
  build() {
    Flex({wrap: FlexWrap.Wrap}) {
      ForEach(this.renderingStrategyText, (text: string, index) => {
        Button(text)
          .key(text)
          .fontSize(10)
          .margin(2)
          .padding(2)
          .height(24)
          .onClick(() => {
            this.renderingStrategy = this.renderingStrategyList[index]
          })
      })
    }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10})
  }
}

// 切换fontColor
@Component
export struct FontColorToggle {
  @Link fontColor: null|undefined|Color|string|Resource

  @State colorList: (null|undefined|Color|string|Resource) [] = [
    Color.Blue, '#fc0303', 0xFF0000, 'rgb(2, 184, 17)', $r('app.color.start_window_background'), 'abcd', undefined, null
  ]
  @State colorTextList: (null|undefined|Color|string|Resource) [] = [
    'fontColorColorBlue',
    'fontColor#fc0303',
    'fontColor0xFF0000',
    'fontColorRgb',
    'fontColorResourceColor',
    'fontColor-abcd',
    'fontColorUndefined',
    'fontColorNull'
  ]

  build() {
    Flex({wrap: FlexWrap.Wrap}) {
      ForEach(this.colorTextList, (text: string, index) => {
        Button(text)
          .fontSize(10)
          .margin(2)
          .padding(2)
          .height(24)
          .onClick(() => {
            this.fontColor = this.colorList[index]
          })
      })
    }
  }
}

@Component
export struct EffectStrategyToggle {
  @Link effectStrategy:SymbolEffectStrategy

  @State list: SymbolEffectStrategy[]= [
    SymbolEffectStrategy.NONE,
    SymbolEffectStrategy.SCALE,
    SymbolEffectStrategy.HIERARCHICAL
  ]

  @State textList: string[]= [
    'SymbolEffectStrategy.NONE',
    'SymbolEffectStrategy.SCALE',
    'SymbolEffectStrategy.HIERARCHICAL'
  ]

  build() {
    Flex({wrap: FlexWrap.Wrap}) {
      ForEach(this.textList, (text:string, index) => {
        Button(text)
          .key(text)
          .fontSize(10)
          .margin(2)
          .padding(2)
          .height(24)
          .onClick(() => {
            this.effectStrategy = this.list[index]
          })
      })
    }
  }
}

// 切换fontColor
@Component
export struct MultipleFontColorToggle {
  @Link fontColor1: null|undefined|Color|string|Resource
  @Link fontColor2: null|undefined|Color|string|Resource
  @State fontColorIndex1:number = 0
  @State fontColorIndex2:number = 0
  @State fontColoText1:string = 'Color.Blue'
  @State fontColoText2:string = 'Color.Blue'
  build() {
    Column() {
      Row() {
        Text('fontColor1为:' + this.fontColoText1).fontSize(10)
        Blank()
        Text('fontColor2为:' + this.fontColoText2).fontSize(10)
      }.width('100%')
      Row() {
        Button('fontColor1').fontSize(10).padding(3).height(26).onClick(() => {
          this.fontColorIndex1++
          if (this.fontColorIndex1 > 7){
            this.fontColorIndex1 = 0
          }
          if (this.fontColorIndex1 == 0 ) {
            this.fontColor1 = Color.Blue
            this.fontColoText1 = 'Color.Blue'
          }
          if (this.fontColorIndex1 == 1 ) {
            this.fontColor1 = '#fc0303'
            this.fontColoText1 = '#fc0303'
          }
          if (this.fontColorIndex1 == 2 ) {
            this.fontColor1 = 0xFF0000
            this.fontColoText1 = '0xFF0000'
          }
          if (this.fontColorIndex1 == 3 ) {
            this.fontColor1 = 'rgb(2, 184, 17)'
            this.fontColoText1 = 'rgb(2, 184, 17)'
          }
          if (this.fontColorIndex1 == 4 ) {
            this.fontColor1 = $r('app.color.start_window_background')
            this.fontColoText1 = '$r(app.color.start_window_background)'
          }
          if (this.fontColorIndex1 == 5 ) {
            this.fontColor1 = 'abcd'
            this.fontColoText1 = 'abcd'
          }
          if (this.fontColorIndex1 == 6 ) {
            this.fontColor1 = undefined
            this.fontColoText1 = 'undefined'
          }
          if (this.fontColorIndex1 == 7 ) {
            this.fontColor1 = null
            this.fontColoText1 = 'null'
          }
        })
        Blank()
        Button('fontColor2').fontSize(10).padding(3).height(26).onClick(() => {
          this.fontColorIndex2++
          if (this.fontColorIndex2 > 7){
            this.fontColorIndex2 = 0
          }
          if (this.fontColorIndex2 == 0 ) {
            this.fontColor2 = Color.Blue
            this.fontColoText2 = 'Color.Blue'
          }
          if (this.fontColorIndex2 == 1 ) {
            this.fontColor2 = '#fc0303'
            this.fontColoText2 = '#fc0303'
          }
          if (this.fontColorIndex2 == 2 ) {
            this.fontColor2 = 0xFF0000
            this.fontColoText2 = '0xFF0000'
          }
          if (this.fontColorIndex2 == 3 ) {
            this.fontColor2 = 'rgb(2, 184, 17)'
            this.fontColoText2 = 'rgb(2, 184, 17)'
          }
          if (this.fontColorIndex2 == 4 ) {
            this.fontColor2 = $r('app.color.start_window_background')
            this.fontColoText2 = '$r(app.color.start_window_background)'
          }
          if (this.fontColorIndex2 == 5 ) {
            this.fontColor2 = 'abcd'
            this.fontColoText2 = 'abcd'
          }
          if (this.fontColorIndex2 == 6 ) {
            this.fontColor2 = undefined
            this.fontColoText2 = 'undefined'
          }
          if (this.fontColorIndex2 == 7 ) {
            this.fontColor2 = null
            this.fontColoText2 = 'null'
          }
        })
      }
      .width('100%')
    }
    .backgroundColor(0xFFFFFF)
    .width('100%')
    .padding({left:10,right:10})
  }
}

@Component
export struct SymbolEffectToggle {
  @State textList:string[] = [
    'SymbolEffect',
    'ScaleSymbolEffect',
    'HierarchicalSymbolEffect',
    'AppearSymbolEffect',
    'DisappearSymbolEffect',
    'BounceSymbolEffect',
    'ReplaceSymbolEffect',
    'PulseSymbolEffect'
  ]

  @State valueList: (SymbolEffect|ScaleSymbolEffect|HierarchicalSymbolEffect| 
                    AppearSymbolEffect|DisappearSymbolEffect|BounceSymbolEffect| 
                    ReplaceSymbolEffect|PulseSymbolEffect)[] = [
    new SymbolEffect(),
    new ScaleSymbolEffect(EffectScope.WHOLE),
    new HierarchicalSymbolEffect(EffectFillStyle.ITERATIVE),
    new AppearSymbolEffect(),
    new DisappearSymbolEffect(),
    new BounceSymbolEffect(),
    new ReplaceSymbolEffect(),
    new PulseSymbolEffect()
  ]

  @Link symbolEffect: SymbolEffect|ScaleSymbolEffect|HierarchicalSymbolEffect| 
                      AppearSymbolEffect|DisappearSymbolEffect|BounceSymbolEffect| 
                      ReplaceSymbolEffect|PulseSymbolEffect
  build() {
    Flex() {
      ForEach(this.textList, (text:string, index) => {
        Button(text)
          .fontSize(10)
          .margin(2)
          .padding(2)
          .height(24)
          .onClick(() => {
            this.symbolEffect = this.valueList[index]
          })
      })
    }
  }
}

@Component
export struct PrimaryButton {
  @Prop text: string
  onClickFunction: (event: ClickEvent) => void = () => {}
  lineHeight: number = 22
  fontSize: number = 16

  build() {
    Button() {
      Text(this.text)
        .lineHeight(this.lineHeight)
        .fontColor(Color.White)
        .fontSize(this.fontSize)
    }
    .borderRadius(0)
    .onClick(this.onClickFunction)
    .padding(4)
    .margin(5)
  }
}
