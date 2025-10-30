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
import { pageOneTmp } from './pageOne'
import { pageTwoTmp } from './pageTwo'
import { pageThreeTmp } from './pageThree'
import { pageFourTmp } from './pageFour'
import { pageFiveTmp } from './page5'
import { pageSixTmp } from './page6'
import { pageSevenTmp } from './page7'
import { pageEightTmp } from './page8'
import { pageNineTmp } from './page9'
import { pageTenTmp } from './page10'
import { pageElevenTmp } from './page11'
import { pageTwelveTmp } from './page12'
import { pageThirteenTmp } from './page13'
import { DIALOG } from './DIALOG'

@Entry
@Component
struct test1 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @State titleMode:NavigationTitleMode = NavigationTitleMode.Mini
  @State fontSize:number|string|Resource|null|undefined = 30
  @State fontColor: null|undefined|(Color|string|Resource)[] = [Color.Blue]
  @State fontWeight: null|undefined|number|string|FontWeight = 100
  @State icon1: SymbolGlyphModifier= new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')).fontSize(this.fontSize).fontColor(this.fontColor).fontWeight(this.fontWeight)
  @State icon2: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')).fontSize('50').fontColor(['#ff03ead1']).fontWeight(FontWeight.Bold)
  @State active:boolean = false
  @State status:ToolbarItemStatus = ToolbarItemStatus.NORMAL

  @State hideBackButton:boolean = false
  @State hideTitleBar:boolean = false
  @State hideToolBar:boolean = false

  @Styles buttonStyles () {
    .height(30)
  }

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOneTmp()
    }else if(name === 'pageTwo'){
      pageTwoTmp()
    }else if(name === 'pageThree'){
      pageThreeTmp()
    }else if(name === 'pageFour'){
      pageFourTmp()
    }else if(name === 'pageFive'){
      pageFiveTmp()
    }else if(name === 'pageSix'){
      pageSixTmp()
    }else if(name === 'pageSeven'){
      pageSevenTmp()
    }else if(name === 'pageEight'){
      pageEightTmp()
    }else if(name === 'pageNine'){
      pageNineTmp()
    }else if(name === 'pageTen'){
      pageTenTmp()
    }else if(name === 'pageEleven'){
      pageElevenTmp()
    }else if(name === 'pageTwelve'){
      pageTwelveTmp()
    }else if(name === 'pageThirteen'){
      pageThirteenTmp()
    }else if(name === 'DIALOG'){
      DIALOG()
    }
  }
  

  build() {
    Column(){
      Column(){
        Navigation(this.pageInfos) {
          Scroll(){
            Column({space: 5}) {
              Button('push PageOne')
                .fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageOne'})
                })
              Button('push PageTwo').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageTwo'})
                })
              Button('push PageThree').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageThree'})
                })
              Button('push Page4').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageFour'})
                })
              Button('push Page5').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageFive'})
                })
              Button('push Page6').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageSix'})
                })
              Button('push Page7').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageSeven'})
                })
              Button('push Page8').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageEight'})
                })
              Button('push Page9').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageNine'})
                })
              Button('push Page10').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageTen'})
                })
              Button('push Page11').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageEleven'})
                })
              Button('push Page12').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageTwelve'})
                })
              Button('push Page13').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'pageThirteen'})
                })
              Button('push DIALOG').fontSize(12)
                .buttonStyles()
                .onClick(() => {
                  this.pageInfos.pushPath({name:'DIALOG'})
                })
            }.width('100%').backgroundColor(0xEFEFEF).padding(10)
          }.height('90%')

        }
        .navDestination(this.PageMap)
        .title('NavIndex')
        .border({width:1})
        .titleMode(this.titleMode)
        .backButtonIcon(this.icon1)
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
        .hideBackButton(this.hideBackButton)
        .hideTitleBar(this.hideTitleBar)
        .hideToolBar(this.hideToolBar)
        .toolbarConfiguration([
          {
            value: '1',
            symbolIcon: this.icon1,
            action:() => {
              if(this.active){
                this.status = ToolbarItemStatus.NORMAL
              }else{
                this.status = ToolbarItemStatus.ACTIVE
              }
              this.active = !this.active
            },
            status:this.status,
            activeSymbolIcon:this.icon2
          },
          {
            value: '2',
            symbolIcon: this.icon1,
            action:() => {
              if(this.active){
                this.status = ToolbarItemStatus.NORMAL
              }else{
                this.status = ToolbarItemStatus.ACTIVE
              }
              this.active = !this.active
            },
            status:this.status,
            activeSymbolIcon:this.icon2
          },
          {
            value: '3',
            symbolIcon: this.icon1,
            action:() => {
              if(this.active){
                this.status = ToolbarItemStatus.NORMAL
              }else{
                this.status = ToolbarItemStatus.ACTIVE
              }
              this.active = !this.active
            },
            status:this.status,
            activeSymbolIcon:this.icon2
          },
          {
            value: '4',
            symbolIcon: this.icon1,
            action:() => {
              if(this.active){
                this.status = ToolbarItemStatus.NORMAL
              }else{
                this.status = ToolbarItemStatus.ACTIVE
              }
              this.active = !this.active
            },
            status:this.status,
            activeSymbolIcon:this.icon2
          },
          {
            value: '5',
            symbolIcon: this.icon1,
            action:() => {
              if(this.active){
                this.status = ToolbarItemStatus.NORMAL
              }else{
                this.status = ToolbarItemStatus.ACTIVE
              }
              this.active = !this.active
            },
            status:this.status,
            activeSymbolIcon:this.icon2
          },
          {
            value: '6',
            symbolIcon: this.icon1,
            action:() => {
              if(this.active){
                this.status = ToolbarItemStatus.NORMAL
              }else{
                this.status = ToolbarItemStatus.ACTIVE
              }
              this.active = !this.active
            },
            status:this.status,
            activeSymbolIcon:this.icon2
          },
          {
            value: '7',
            symbolIcon: this.icon1,
            action:() => {
              if(this.active){
                this.status = ToolbarItemStatus.NORMAL
              }else{
                this.status = ToolbarItemStatus.ACTIVE
              }
              this.active = !this.active
            },
            status:this.status,
            activeSymbolIcon:this.icon2
          }
        ])
        .height('100%')
      }.width('100%').backgroundColor(0xEFEFEF).padding(10)
    }
  }
}