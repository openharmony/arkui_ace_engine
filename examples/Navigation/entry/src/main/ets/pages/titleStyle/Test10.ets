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
import { NavigationTitleModeRadio } from '../CommonComponents'

@Entry
@Component
struct test10 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @State titleMode:NavigationTitleMode = NavigationTitleMode.Mini

  @State fontSize:number|string|Resource|null|undefined = 30

  @State fontColor: null|undefined|(Color|string|Resource)[] = [Color.Blue]
  @State fontColorIndex1:number = 0
  @State text2:string = 'Color.Blue'

  @State fontWeight: null|undefined|number|string|FontWeight = 100
  @State fontWeightIndex1:number = 0
  @State text3:string = '100'

  @State icon2: undefined = undefined
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
        .backButtonIcon(undefined)
        .menus([
          {
            value: '1',
            symbolIcon: undefined,

          },
          {
            value: '2',
            symbolIcon: undefined,
          },
          {
            value: '3',
            symbolIcon: undefined,
          },
          {
            value: '4',
            symbolIcon: undefined,
          },
          {
            value: '5',
            symbolIcon: undefined,
          },
          {
            value: '6',
            symbolIcon: undefined,
          },
          {
            value: '7',
            symbolIcon: undefined,
          }
        ])
        .toolbarConfiguration([
          {
            value: '1',
            symbolIcon: undefined,
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
            symbolIcon: undefined,
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
            symbolIcon: undefined,
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
            symbolIcon: undefined,
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
            symbolIcon: undefined,
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
            symbolIcon: undefined,
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
            symbolIcon: undefined,
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