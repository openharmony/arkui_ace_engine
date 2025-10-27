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
    new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')),
    new SymbolGlyphModifier($r('sys.symbol.trash_circle')),
    new SymbolGlyphModifier($r('sys.symbol.ohos_trash')),
    new SymbolGlyphModifier($r('sys.symbol.picture')),
    new SymbolGlyphModifier($r('sys.symbol.ohos_lungs')),
  ]
  @State iconIndex1:number = 0
  @State text1:string = 'ohos_folder_badge_plus'

  @State icon2: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')).fontSize('50')
                                      .fontColor(['#ff03ead1']).fontWeight(FontWeight.Bold)
  @State active:boolean = false
  @State status:ToolbarItemStatus = ToolbarItemStatus.NORMAL

  @State symbolEffect: SymbolEffect|ScaleSymbolEffect|HierarchicalSymbolEffect| 
                      AppearSymbolEffect|DisappearSymbolEffect|BounceSymbolEffect| 
                      ReplaceSymbolEffect|PulseSymbolEffect = new SymbolEffect()
  @State symbolEffectIndex:number = 0
  @State symbolEffectText1:string = 'SymbolEffect'
  @State isActive:boolean = false
  @State triggerValue:number = -1
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
        .backButtonIcon(this.icon1[this.iconIndex1].fontSize(this.fontSize)
                        .fontColor(this.fontColor).fontWeight(this.fontWeight)
                        .symbolEffect({
                          symbolEffect:new HierarchicalSymbolEffect(),
                          isActive:this.isActive,triggerValue:this.triggerValue
                        }))
        .menus([
          {
            value: "1",
            symbolIcon: this.icon1[this.iconIndex1],

          },
          {
            value: "2",
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "3",
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "4",
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "5",
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "6",
            symbolIcon: this.icon1[this.iconIndex1],
          },
          {
            value: "7",
            symbolIcon: this.icon1[this.iconIndex1],
          }
        ])
        .toolbarConfiguration([
          {
            value: "1",
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
          Row() {
            Text('style:')
            Blank()
            Column({space:5}){
              Row(){
                Radio({ value: 'Radio1', group: 'radioGroup1' }).checked(true)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.titleMode = NavigationTitleMode.Free
                  })
                Text('NavigationTitleMode.Free')
              }

              Row(){
                Radio({ value: 'Radio2', group: 'radioGroup1' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.titleMode = NavigationTitleMode.Mini
                  })
                Text('NavigationTitleMode.Mini')
              }

              Row(){
                Radio({ value: 'Radio3', group: 'radioGroup1' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.titleMode = NavigationTitleMode.Full
                  })
                Text('NavigationTitleMode.Full')
              }
            }
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(130)
          Column() {
            Text('图标为: sys.symbol' + this.text1).fontSize(10)
            Blank()
            Button('切换图标').onClick(() => {
              this.iconIndex1++

              if (this.iconIndex1 > 4) {
                this.iconIndex1 = 0
              }

              if (this.iconIndex1 == 0) {
                this.text1 = 'ohos_folder_badge_plus'
              }
              if(this.iconIndex1 == 1){
                this.text1 = 'trash_circle'
              }
              if(this.iconIndex1 == 2){
                this.text1 = 'ohos_trash'
              }
              if(this.iconIndex1 == 3){
                this.text1 = 'picture'
              }
              if(this.iconIndex1 == 4){
                this.text1 = 'ohos_lungs'
              }
            })
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(60)
          Row() {
            Text('fontSize:')
            Blank()
            Column({space:5}){
              Row(){
                Radio({ value: 'Radio1', group: 'radioGroup2' }).checked(true)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = 30
                  })
                Text('30')
              }

              Row(){
                Radio({ value: 'Radio2', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = -30
                  })
                Text('-30')
              }

              Row(){
                Radio({ value: 'Radio3', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = 30
                  })
                Text("$r('app.integer.integer_30')")
              }
              Row(){
                Radio({ value: 'Radio4', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = '30px'
                  })
                Text("30px")
              }
              Row(){
                Radio({ value: 'Radio5', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = '30lpx'
                  })
                Text("30lpx")
              }
              Row(){
                Radio({ value: 'Radio6', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = '30fp'
                  })
                Text("30fp")
              }
              Row(){
                Radio({ value: 'Radio7', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = '30vp'
                  })
                Text("30vp")
              }
              Row(){
                Radio({ value: 'Radio8', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = null
                  })
                Text("null")
              }
              Row(){
                Radio({ value: 'Radio9', group: 'radioGroup2' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.fontSize = undefined
                  })
                Text("undefined")
              }
            }.alignItems(HorizontalAlign.Start)
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(405)
          Column() {
            Text('fontColor为:' + this.text2).fontSize(10)
            Blank()
            Button('fontColor').onClick(() => {
              this.fontColorIndex1++
              if (this.fontColorIndex1 > 6){
                this.fontColorIndex1 = 0
              }
              if (this.fontColorIndex1 == 0 ) {
                this.fontColor = [Color.Blue]
                this.text2 = 'Color.Blue'
              }
              if (this.fontColorIndex1 == 1 ) {
                this.fontColor = ['#fc0303']
                this.text2 = '#fc0303'
              }
              if (this.fontColorIndex1 == 2 ) {
                this.fontColor = [0xFF0000]
                this.text2 = '0xFF0000'
              }
              if (this.fontColorIndex1 == 3 ) {
                this.fontColor = ['rgb(2, 184, 17)']
                this.text2 = 'rgb(2, 184, 17)'
              }
              if (this.fontColorIndex1 == 4 ) {
                this.fontColor = [$r('app.color.start_window_background')]
                this.text2 = "$r('app.color.Pink')"
              }
              if (this.fontColorIndex1 == 5 ) {
                this.fontColor = ['abcd']
                this.text2 = "abcd"
              }
              if (this.fontColorIndex1 == 6 ) {
                this.fontColor = undefined
                this.text2 = 'undefined'
              }
              if (this.fontColorIndex1 == 6 ) {
                this.fontColor = null
                this.text2 = 'null'
              }

            })
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(60)
          Column() {
            Text('fontWeight为:' + this.text3).fontSize(10)
            Blank()
            Button('fontWeight').onClick(() => {
              this.fontWeightIndex1++
              if (this.fontWeightIndex1 > 7){
                this.fontWeightIndex1 = 0
              }
              if (this.fontWeightIndex1 == 0 ) {
                this.fontWeight = 100
                this.text3 = '100'
              }
              if (this.fontWeightIndex1 == 1 ) {
                this.fontWeight = 500
                this.text3 = '500'
              }
              if (this.fontWeightIndex1 == 2 ) {
                this.fontWeight = 900
                this.text3 = '900'
              }
              if (this.fontWeightIndex1 == 3 ) {
                this.fontWeight = FontWeight.Lighter
                this.text3 = 'FontWeight.Lighter'
              }
              if (this.fontWeightIndex1 == 4 ) {
                this.fontWeight = FontWeight.Bolder
                this.text3 = 'FontWeight.Bolder'
              }
              if (this.fontWeightIndex1 == 5 ) {
                this.fontWeight = '100'
                this.text3 = '"100"'
              }
              if (this.fontWeightIndex1 == 6 ) {
                this.fontWeight = null
                this.text3 = "null"
              }
              if (this.fontWeightIndex1 == 7 ) {
                this.fontWeight = undefined
                this.text3 = 'undefined'
              }

            })
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(60)
          Column() {
            Text('symbolEffect:' + this.symbolEffectText1).fontSize(10)
            Blank()
            Button('symbolEffect').onClick(() => {
              this.symbolEffectIndex++
              if (this.symbolEffectIndex > 7){
                this.symbolEffectIndex = 0
              }
              if (this.symbolEffectIndex == 0 ) {
                this.symbolEffect = new SymbolEffect()
                this.symbolEffectText1 = 'SymbolEffect'
              }
              if (this.symbolEffectIndex == 1 ) {
                this.symbolEffect = new ScaleSymbolEffect(EffectScope.WHOLE)
                this.symbolEffectText1 = 'ScaleSymbolEffect'
              }
              if (this.symbolEffectIndex == 2 ) {
                this.symbolEffect = new HierarchicalSymbolEffect(EffectFillStyle.ITERATIVE)
                this.symbolEffectText1 = 'HierarchicalSymbolEffect'
              }
              if (this.symbolEffectIndex == 3 ) {
                this.symbolEffect = new AppearSymbolEffect()
                this.symbolEffectText1 = 'AppearSymbolEffect'
              }
              if (this.symbolEffectIndex == 4 ) {
                this.symbolEffect = new DisappearSymbolEffect()
                this.symbolEffectText1 = 'DisappearSymbolEffect'
              }
              if (this.symbolEffectIndex == 5 ) {
                this.symbolEffect = new BounceSymbolEffect()
                this.symbolEffectText1 = 'BounceSymbolEffect'
              }
              if (this.symbolEffectIndex == 6 ) {
                this.symbolEffect = new ReplaceSymbolEffect()
                this.symbolEffectText1 = "ReplaceSymbolEffect"
              }
              if (this.symbolEffectIndex == 7 ) {
                this.symbolEffect = new PulseSymbolEffect()
                this.symbolEffectText1 = 'PulseSymbolEffect'
              }
            })
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(60)
          Column() {
            Button(this.isActive ? '关闭-isActive' : '播放-isActive').onClick(() => {
              this.isActive = !this.isActive;
            })
            Blank()
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(50)

          Row() {
            Text('triggerValue:')
            Blank()
            Toggle({ type: ToggleType.Switch, isOn: false })
              .selectedColor('#007DFF')
              .switchPointColor('#FFFFFF')
              .onChange((isOn: boolean) => {
                if (isOn) {
                  this.triggerValue = 1
                }else{
                  this.triggerValue = -1
                }
              })
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(50)

        }.width('100%').backgroundColor(0xEFEFEF).padding(10)
      }.height(250)
    }

  }
}