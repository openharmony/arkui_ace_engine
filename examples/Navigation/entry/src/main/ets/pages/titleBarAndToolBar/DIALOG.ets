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
import window from '@ohos.window';
import base from '@ohos.base';
import { SysSymbolToggle, FontSizeToggle, FontWeightToggle,EffectStrategyToggle, FontColorToggle } from '../common/CommonComponents'

@Component
export struct DIALOG {
  @Consume('pageInfos') pageInfos: NavPathStack;

  @State fontSize:number|string|Resource|null|undefined = 30

  @State fontColor: null|undefined|(Color|string|Resource)  = Color.Blue

  @State fontWeight: null|undefined|number|string|FontWeight   = 100

  @State icon1: SymbolGlyphModifier= new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))

  @State effectStrategy:SymbolEffectStrategy = SymbolEffectStrategy.NONE
  @State hideTitleBar:boolean = false

  private myWindow: window.Window | null = null;
  createWindow() {
    try {
      window.createWindow({name: 'testWindow', windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/test2', ls)
              .then(() => {
                console.log(`testTag success to loadContent`)
              }).catch((e: base.BusinessError) => {
              console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
            })
          }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
          });
        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }

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
            Row() {
              Button('开启子窗口')
                .fontSize(10)
                .margin(2)
                .padding(2)
                .height(24)
                .onClick(() => {
                  this.createWindow();
                })
              Button('hideTitleBar')
                .fontSize(10)
                .margin(2)
                .padding(2)
                .height(24)
                .onClick(() => {
                  this.hideTitleBar = true
                })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10})
          }.width('100%').backgroundColor(0xEFEFEF).padding(10)
        }.height('90%')
      }.width('100%').height('100%')
    }.title('NavDestination传入symbol设置fontSize、fontColor、fontWeight、effectStrategy属性测试')
    .backgroundColor('#4198b7')
    .backButtonIcon(this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight).effectStrategy(this.effectStrategy))
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
    .hideTitleBar(this.hideTitleBar)
    .mode(NavDestinationMode.DIALOG)
    .onBackPressed(() => {
      this.pageInfos.pop()
      console.log('pop' + '返回值' + JSON.stringify(this.pageInfos.pop()))
      return true
    })
  }
}