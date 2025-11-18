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
import { SysSymbolToggle, FontSizeToggle, FontWeightToggle, SymbolEffectToggle, MultipleFontColorToggle, RenderingStrategyToggle } from '../common/CommonComponents'

@Component
export struct pageThreeTmp {
  @Consume('pageInfos') pageInfos: NavPathStack;

  @State fontSize:number|string|Resource|null|undefined = 30
  @State fontColor1: null|undefined|Color|string|Resource = Color.Blue
  @State fontColor2: null|undefined|Color|string|Resource = Color.Blue
  @State fontWeight: null|undefined|number|string|FontWeight = 100
  @State icon1: SymbolGlyphModifier= new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))
  @State renderingStrategy:SymbolRenderingStrategy = SymbolRenderingStrategy.SINGLE

  @State symbolEffect: SymbolEffect|ScaleSymbolEffect|HierarchicalSymbolEffect| AppearSymbolEffect|DisappearSymbolEffect|BounceSymbolEffect| ReplaceSymbolEffect|PulseSymbolEffect = new SymbolEffect()
  @State isActive:boolean = false
  @State triggerValue:number = -1
  build() {
    NavDestination() {
      Column({space:5}){
        SysSymbolToggle({icon: this.icon1})
        FontSizeToggle({fontSize: this.fontSize})
        RenderingStrategyToggle({renderingStrategy: this.renderingStrategy})
        MultipleFontColorToggle({fontColor1: this.fontColor1, fontColor2: this.fontColor2})
        FontWeightToggle({fontWeight: this.fontWeight})
        SymbolEffectToggle({symbolEffect: this.symbolEffect})
        Column() {
          Button(this.isActive ? '关闭-isActive' : '播放-isActive').onClick(() => {
            this.isActive = !this.isActive;
          })
          Blank()
        }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(50)

      }.width('100%').height('100%')
    }.title('NavDestination传入symbol设置symbolEffect属性测试（isActive）')
    .backgroundColor('#4198b7')
    .backButtonIcon(
      this.icon1
        .fontSize(this.fontSize)
        .fontColor([this.fontColor1,this.fontColor2])
        .fontWeight(this.fontWeight)
        .symbolEffect({symbolEffect:this.symbolEffect,isActive:this.isActive})
        .renderingStrategy(this.renderingStrategy)
    )
    .menus([
      {
        value: '1',
        symbolIcon: this.icon1,

      },
      {
        value: '2',
        symbolIcon: this.icon1,
      },
      {
        value: '3',
        symbolIcon: this.icon1,
      },
      {
        value: '4',
        symbolIcon: this.icon1,
      },
      {
        value: '5',
        symbolIcon: this.icon1,
      },
      {
        value: '6',
        symbolIcon: this.icon1,
      },
      {
        value: '7',
        symbolIcon: this.icon1,
      }
    ])
    .onBackPressed(() => {
      this.pageInfos.pop() // 弹出路由栈栈顶元素
      console.log('pop' + '返回值' + JSON.stringify(this.pageInfos.pop()))
      return true
    })
  }
}