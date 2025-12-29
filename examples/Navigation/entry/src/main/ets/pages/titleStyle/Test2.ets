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
import { BusinessError } from '@ohos.base';
import { NavigationTitleModeRadio, SysSymbolToggle, FontSizeToggle, RenderingStrategyToggle, FontWeightToggle, MultipleFontColorToggle } from '../common/CommonComponents'

@Entry
@Component
struct test2 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @State titleMode:NavigationTitleMode = NavigationTitleMode.Mini

  @State fontSize:number|string|Resource|null|undefined = 30

  @State fontColor1: null|undefined|Color|string|Resource = Color.Blue
  @State fontColor2: null|undefined|Color|string|Resource = Color.Blue

  @State fontWeight: null|undefined|number|string|FontWeight = 100

  @State icon1: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))

  @State icon2: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')).fontSize('50').fontColor(['#ff03ead1']).fontWeight(FontWeight.Bold)
  @State active:boolean = false
  @State status:ToolbarItemStatus = ToolbarItemStatus.NORMAL

  @State renderingStrategy:SymbolRenderingStrategy = SymbolRenderingStrategy.SINGLE

  @State navigationMode:NavigationMode = NavigationMode.Auto

  private curWindow: window.Window | null = null;
  closeWindow() {
    console.log(`testTag prepare to close Window`)
    try {
      this.curWindow = window.findWindow('testWindow');
      if (!this.curWindow) {
        console.log(`testTag failed to findWindow`);
        return;
      }
      this.curWindow.destroyWindow().then(() => {
        console.log(`testTag success to destroy curWindow`);
      }).catch((err: BusinessError) => {
        console.log(`failed to destroy curWindow`)
      })
    } catch (e) {
      console.log(`testTag catch exception when find Window: ${JSON.stringify(e)}`)
    }
  }

  build() {
    Column(){
      Column(){
        Navigation(this.pageInfos) {
          Column() {

          }
        }
        .title('NavIndex')
        .border({width:1})
        .titleMode(this.titleMode)
        .backButtonIcon(this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight).renderingStrategy(this.renderingStrategy))
        .menus([
          {
            value: "1",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),

          },
          {
            value: "2",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
          },
          {
            value: "3",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
          },
          {
            value: "4",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
          },
          {
            value: "5",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
          },
          {
            value: "6",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
          },
          {
            value: "7",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
          }
        ])
        .toolbarConfiguration([
          {
            value: "1",
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
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
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
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
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
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
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
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
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
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
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
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
            symbolIcon: this.icon1.fontSize(this.fontSize).fontColor([this.fontColor1,this.fontColor2]).fontWeight(this.fontWeight),
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
        .mode(this.navigationMode)
      }.width('100%').backgroundColor(0xEFEFEF).padding(10).height('40%')

      Column({space:5}){
        NavigationTitleModeRadio({titleMode: this.titleMode})
        SysSymbolToggle({icon: this.icon1})
        FontSizeToggle({fontSize: this.fontSize})
        RenderingStrategyToggle({renderingStrategy: this.renderingStrategy})
        MultipleFontColorToggle({
          fontColor1: this.fontColor1,
          fontColor2: this.fontColor2
        })
        FontWeightToggle({fontWeight: this.fontWeight})
        Row() {
          Button('close Window')
            .fontSize(10)
            .margin(2)
            .padding(2)
            .height(24)
            .onClick(() => {
              this.closeWindow();
            })
          Button('mode:Split')
            .fontSize(10)
            .margin(2)
            .padding(2)
            .height(24)
            .onClick(() => {
              this.navigationMode = NavigationMode.Split
            })
          Button('mode:Stack')
            .fontSize(10)
            .margin(2)
            .padding(2)
            .height(24)
            .onClick(() => {
              this.navigationMode = NavigationMode.Stack
            })
        }
      }.width('100%').height('60%').backgroundColor(0xEFEFEF)
    }

  }
}