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
import { SysSymbolToggle, FontSizeToggle, FontWeightToggle,EffectStrategyToggle, FontColorToggle } from '../common/CommonComponents'

@Entry
@Component
export struct pageFiveTmp {
  @Consume('pageInfos') pageInfos: NavPathStack;

  @State fontSize:number|string|Resource|null|undefined = 30
  @State fontColor: null|undefined|(Color|string|Resource)  = Color.Blue
  @State fontWeight: null|undefined|number|string|FontWeight   = 100
  @State icon1: SymbolGlyphModifier= new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))
  @State effectStrategy:SymbolEffectStrategy = SymbolEffectStrategy.NONE

  build() {
    NavDestination() {
      Column() {
        Scroll(){
          Column({space:5}){
            SysSymbolToggle({icon: this.icon1})
            FontSizeToggle({fontSize: this.fontSize})
            FontColorToggle({fontColor: this.fontColor})
            FontWeightToggle({fontWeight: this.fontWeight})
            EffectStrategyToggle({effectStrategy: this.effectStrategy})
          }.width('100%').backgroundColor(0xEFEFEF).padding(10)
        }.height('90%')
      }.width('100%').height('100%')
    }.title('标题栏同时设置icon和symbolIcon')
    .backgroundColor('#4198b7')
    .backButtonIcon(this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight).effectStrategy(this.effectStrategy))
    .menus([
      {
        value: '1',
        icon:'/image/1.jpg',
        symbolIcon: this.icon1,
      },
      {
        value: '2',
        icon:'/image/1.jpg',
        symbolIcon: this.icon1,
      },
      {
        value: '3',
        icon:'/image/1.jpg',
        symbolIcon: this.icon1,
      },
      {
        value: '4',
        icon:'/image/1.jpg',
        symbolIcon: this.icon1,
      },
      {
        value: '5',
        icon:'/image/1.jpg',
        symbolIcon: this.icon1,
      },
      {
        value: '6',
        icon:'/image/1.jpg',
        symbolIcon: this.icon1,
      },
      {
        value: '7',
        icon:'/image/1.jpg',
        symbolIcon: this.icon1,
      }
    ])
    .onBackPressed(() => {
      this.pageInfos.pop()
      console.log('pop' + '返回值' + JSON.stringify(this.pageInfos.pop()))
      return true
    })
  }
}