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
// import { pageOneTmp } from './pageOne'
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import { NavigationTitleModeRadio } from '../common/CommonComponents'


@Entry
@Component
struct test1 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @State titleMode:NavigationTitleMode = NavigationTitleMode.Mini

  @State fontSize:number|string|Resource|null|undefined = 30

  @State fontColor: null|undefined|(Color|string|Resource)[] = [Color.Blue]
  @State fontColorIndex1:number = 0
  @State text2:string = 'Color.Blue'

  @State fontWeight: null|undefined|number|string|FontWeight = 100
  @State fontWeightIndex1:number = 0
  @State text3:string = '100'

  @State icon1: SymbolGlyphModifier[]= [
    new SymbolGlyphModifier($r('app.integer.integer_30')),
  ]
  @State iconIndex1:number = 0
  @State text1:string = 'ohos_folder_badge_plus'

  @State icon2: SymbolGlyphModifier = new SymbolGlyphModifier($r('app.integer.integer_30'))
  @State active:boolean = false
  @State status:ToolbarItemStatus = ToolbarItemStatus.NORMAL
  build() {
    Column(){
      Column(){
        Navigation(this.pageInfos) {
          Column() {

          }
        }
        .title('NavIndex')
        .height(500).border({width:1})
        .titleMode(this.titleMode)
        .backButtonIcon(this.icon1[this.iconIndex1].fontSize(this.fontSize).fontColor(this.fontColor).fontWeight(this.fontWeight))
        .menus([
          {
            value: "1",
            icon:'/image/1.jpg',
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "2",
            icon:'/image/1.jpg',
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "3",
            icon:'/image/1.jpg',
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "4",
            icon:'/image/1.jpg',
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "5",
            icon:'/image/1.jpg',
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "6",
            icon:'/image/1.jpg',
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "7",
            icon:'/image/1.jpg',
            symbolIcon: this.icon1[this.iconIndex1],
          }
        ])
        .toolbarConfiguration([
          {
            value: "1",
            icon: $r('app.media.startIcon'),
            symbolIcon: this.icon1[this.iconIndex1],
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
            icon: $r('app.media.startIcon'),
            symbolIcon: this.icon1[this.iconIndex1],
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
            icon: $r('app.media.startIcon'),
            symbolIcon: this.icon1[this.iconIndex1],
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
            icon: $r('app.media.startIcon'),
            symbolIcon: this.icon1[this.iconIndex1],
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
            icon: $r('app.media.startIcon'),
            symbolIcon: this.icon1[this.iconIndex1],
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
            icon: $r('app.media.startIcon'),
            symbolIcon: this.icon1[this.iconIndex1],
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
            icon: $r('app.media.startIcon'),
            symbolIcon: this.icon1[this.iconIndex1],
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
      }.width('100%').backgroundColor(0xEFEFEF).padding(10)


      Scroll(){
        Column({space:5}){
          NavigationTitleModeRadio({titleMode: this.titleMode})
        }.width('100%').backgroundColor(0xEFEFEF).padding(10)
      }.height(250)
    }

  }
}