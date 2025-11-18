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
import { 
  NavigationTitleModeRadio, 
  SysSymbolToggle,
  FontSizeToggle,
  EffectStrategyToggle,
  FontWeightToggle,
  FontColorToggle
} from '../CommonComponents'


@Entry
@Component
struct test1 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @State titleMode:NavigationTitleMode = NavigationTitleMode.Mini

  @State fontSize:number|string|Resource|null|undefined = 30

  @State fontColor: null|undefined|(Color|string|Resource)  = Color.Blue
  @State fontColorIndex1:number = 0
  @State text2:string = 'Color.Blue'

  @State fontWeight: null|undefined|number|string|FontWeight = 100

  @State icon1: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))

  @State icon2: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))
                                      .fontSize('50').fontColor(['#ff03ead1']).fontWeight(FontWeight.Bold)
  @State active:boolean = false
  @State status:ToolbarItemStatus = ToolbarItemStatus.NORMAL

  @State hideBackButton:boolean = false
  @State hideTitleBar:boolean = false
  @State hideToolBar:boolean = false
  @State effectStrategy:SymbolEffectStrategy = SymbolEffectStrategy.NONE

  @State NavBarPosition1:NavBarPosition = NavBarPosition.Start

  private myWindow: window.Window | null = null;
  createWindow() {
    try {
      window.createWindow({name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1200, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/hmSymbol/test2', ls)
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
    Column(){
      Column(){
        Navigation(this.pageInfos) {
          Column() {
          }
        }
        .title('Index页面')
        .border({width:1})
        .titleMode(this.titleMode)
        .backButtonIcon(this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight))
        .menus([
          {
            value: "1",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight),
          },
          {
            value: "2",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight),
          },
          {
            value: "3",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight),
          },
          {
            value: "4",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight),
          },
          {
            value: "5",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight),
          },
          {
            value: "6",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight),
          },
          {
            value: "7",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor]).fontWeight(this.fontWeight),
          }
        ])
        .hideBackButton(this.hideBackButton)
        .hideTitleBar(this.hideTitleBar)
        .hideToolBar(this.hideToolBar)
        .toolbarConfiguration([
          {
            value: "1",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor])
                        .fontWeight(this.fontWeight).effectStrategy(this.effectStrategy),
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
            value: "2",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor])
                        .fontWeight(this.fontWeight).effectStrategy(this.effectStrategy),
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
            value: "3",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor])
                        .fontWeight(this.fontWeight).effectStrategy(this.effectStrategy),
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
            value: "4",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor])
                        .fontWeight(this.fontWeight).effectStrategy(this.effectStrategy),
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
            value: "5",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor])
                        .fontWeight(this.fontWeight).effectStrategy(this.effectStrategy),
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
            value: "6",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor])
                        .fontWeight(this.fontWeight).effectStrategy(this.effectStrategy),
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
            value: "7",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor])
                        .fontWeight(this.fontWeight).effectStrategy(this.effectStrategy),
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
        .navBarPosition(this.NavBarPosition1)
      }.width('100%').backgroundColor(0xEFEFEF).padding(10).height('48%')

      Column({space:5}){
          NavigationTitleModeRadio({titleMode: this.titleMode})
          SysSymbolToggle({icon: this.icon1})
          FontSizeToggle({fontSize: this.fontSize})
          FontColorToggle({fontColor: this.fontColor})
          FontWeightToggle({fontWeight: this.fontWeight})
          Row() {
            Button('hideBackButton')
              .fontSize(10)
              .height(24)
              .padding(2)
              .margin(2)
              .onClick(() => {
                this.hideBackButton = true
              })
            Button('hideTitleBar')
              .fontSize(10)
              .height(24)
              .padding(2)
              .margin(2)
              .onClick(() => {
                this.hideTitleBar = true
              })
            Button('hideToolBar')
              .fontSize(10)
              .height(24)
              .padding(2)
              .margin(2)
              .onClick(() => {
                this.hideToolBar = true
              })
            Button('open subWindow')
              .fontSize(10)
              .height(24)
              .padding(2)
              .margin(2)
              .onClick(() => {
                this.createWindow();
              })
            Button('navBarPosition:End')
              .fontSize(10)
              .height(24)
              .padding(2)
              .margin(2)
              .onClick(() => {
                this.NavBarPosition1 =NavBarPosition.End
              })
          }
          EffectStrategyToggle({effectStrategy: this.effectStrategy})
        }.height('52%').width('100%').backgroundColor(0xEFEFEF)
    }

  }
}