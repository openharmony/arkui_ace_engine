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
import { SysSymbolToggle, FontSizeToggle, FontWeightToggle, MultipleFontColorToggle, RenderingStrategyToggle } from '../common/CommonComponents'

@Component
export struct pageTwoTmp {
  @Consume('pageInfos') pageInfos: NavPathStack;

  @State fontSize:number|string|Resource|null|undefined = 30

  @State fontColor1: null|undefined|Color|string|Resource = Color.Blue
  @State fontColor2: null|undefined|Color|string|Resource = Color.Blue
  @State fontWeight: null|undefined|number|string|FontWeight = 100
  @State icon1: SymbolGlyphModifier= new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))
  @State renderingStrategy:SymbolRenderingStrategy = SymbolRenderingStrategy.SINGLE
  build() {
    NavDestination() {
      Column() {
        Scroll(){
          Column({space:5}){
            SysSymbolToggle({icon: this.icon1})
            FontSizeToggle({fontSize: this.fontSize})
            RenderingStrategyToggle({renderingStrategy: this.renderingStrategy})
            MultipleFontColorToggle({fontColor1: this.fontColor1, fontColor2: this.fontColor2})
            FontWeightToggle({fontWeight: this.fontWeight})
          }.width('100%').backgroundColor(0xEFEFEF).padding(10)
        }.height('90%')
      }.width('100%').height('100%')
    }.title('NavDestination传入symbol设置fontSize、fontColor、fontWeight、renderingStrategy属性测试')
    .backgroundColor('#4198b7')
    .backButtonIcon(this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy))
    .menus([
      {
        value: '1',
        symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy),

      },
      {
        value: '2',
        symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy),
      },
      {
        value: '3',
        symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy),
      },
      {
        value: '4',
        symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy),
      },
      {
        value: '5',
        symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy),
      },
      {
        value: '6',
        symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy),
      },
      {
        value: '7',
        symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy),
      }
    ])
    .onBackPressed(() => {
      this.pageInfos.pop() // 弹出路由栈栈顶元素
      console.log('pop' + '返回值' + JSON.stringify(this.pageInfos.pop()))
      return true
    })
  }
}