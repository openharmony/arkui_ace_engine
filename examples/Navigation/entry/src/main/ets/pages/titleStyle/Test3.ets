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
@Entry
@Component
struct Index71553 {
  @State titleModeValue: NavigationTitleMode[] = [
    NavigationTitleMode.Free,
    NavigationTitleMode.Mini,
    NavigationTitleMode.Full
  ]
  @State titleModeValueIndex: number = 0
  @State titleModeValueStr: string[] = ['NavigationTitleMode.Free', 'NavigationTitleMode.Mini', 'NavigationTitleMode.Full']
  @State modeValue: NavigationMode[] = [NavigationMode.Stack,  NavigationMode.Split,  NavigationMode.Auto]
  @State modeValueIndex: number = 0
  @State modeValueStr: string[] = ['NavigationMode.Stack', 'NavigationMode.Split', 'NavigationMode.Auto']
  @State barStyleValue: BarStyle[] = [BarStyle.STANDARD, BarStyle.STACK]
  @State barStyleIndex: number = 0
  @State barStyleStr: string[] = ['BarStyle.STANDARD', 'BarStyle.STACK']
  @State hideBackButtonValue:boolean = false
  private arr: number[] = [0, 1]
  @State titleValue: (ResourceStr | NavigationCommonTitle) [] = [
    '主标题', '主标题主标题主标题主标题主标题主标题', '主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串' +
    '主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串',
    {main:'主标题', sub:'副标题'}, {main:'主标题主标题主标题主标题主标题主标题', sub:'副标题副标题副标题副标题副标题副标题'},
    {main:'主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串' +
      '主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串',
      sub:'副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串' +
      '副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串副标题超长字符串'},
    'سۆزلىگقۇبۇل',
    'سۆزلىسۆسۆزلىسۆزلىسۆزلىگقۇبۇلسۆزلىگقۇبۇل',
    'ۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇل' +
      'زلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگق' +
      'سۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆ',
    {main:'سۆزلىگقۇبۇل', sub:'سۆزلىگقۇبۇل'},
    {main:'سۆزلىسۆزلىسۆزلىگقۇبۇلسۆزلىگقۇبۇل', sub:'سۆزلىسۆزلىسۆزلىگقۇبۇلسۆزلىگقۇبۇل'},
    {
      main:'زلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇل' +
        'سۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆ' +
        'سۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆ' +
        'زلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇل' ,
      sub:'زلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇل' +
        'سۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆ' +
        'سۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆ' +
        'زلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇلسۆزلىگقۇبۇل'
    },
    'བོད་ཀྱ','བོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱ', 'བོད་ཀྱབོད་ཀྱབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིག' +
    'བོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིག', {main:'བོད་ཀྱ', sub:'བོད་ཀྱ'},
    {main:'བོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱ', sub:'བོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱབོད་ཀྱ'},
    {main:'བོད་ཀྱབོད་ཀྱབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིག' +
      'བོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིག',
      sub:'བོད་ཀྱབོད་ཀྱབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིག' +
        'བོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིགབོད་ཀྱི་སྐད་ཡིག'},
  ]
  @State titleValueStr: string[] = ['主标题-中文-短文本', '主标题-中文-中文本', '主标题-中文-长文本',
    '主副标题-中文-短文本','主副标题-中文-中文本', '主副标题-中文-长文本',
    '主标题-维吾尔语-短文本', '主标题-维吾尔语-中文本','主标题-维吾尔语-长文本',
    '主副标题-维吾尔语-短文本', '主副标题-维吾尔语-中文本','主副标题-维吾尔语-长文本',
    '主标题-藏语-短文本', '主标题-藏语-中文本', '主标题-藏语-长文本',
    '主副标题-藏语-短文本', '主副标题-藏语-中文本','主副标题-藏语-长文本']
  @State titleValueIndex: number = 0
  @State edgesValue: SafeAreaEdge[][] = [
    [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END],
    [ SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END]
  ]
  @State edgesValueStr: string[] = ['expand to unsafe area','safe area remove TOP']
  @State edgesValueIndex: number = 0
  @State navBarPositionValue:NavBarPosition[] = [NavBarPosition.Start, NavBarPosition.End]
  @State navBarPositionValueStr:string[] = ['NavBarPosition.Start', 'NavBarPosition.End']
  @State navBarPositionValueIndex:number = 0
  build() {
    Navigation() {
      Column({ space: 10 }) {
        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(150)
                .textAlign(TextAlign.Center)
                .backgroundColor(Color.Orange)
            }
          }, (item: string) => item)
        }
        .scrollBar(BarState.Off)
        .width('90%')
        .height('30%')
        Column({ space: 5 }) {
          Button('title:' + this.titleValueStr[this.titleValueIndex])
            .onClick(() => {
              this.titleValueIndex++
              if (this.titleValueIndex > this.titleValueStr.length - 1) {
                this.titleValueIndex = 0
              }
            })
          Button('titleMode:' + this.titleModeValueStr[this.titleModeValueIndex])
            .onClick(() => {
              this.titleModeValueIndex++
              if (this.titleModeValueIndex > this.titleModeValue.length - 1) {
                this.titleModeValueIndex = 0
              }
            })
          Button('mode:' + this.modeValueStr[this.modeValueIndex])
            .onClick(() => {
              this.modeValueIndex++
              if (this.modeValueIndex > this.modeValue.length - 1) {
                this.modeValueIndex = 0
              }
            })
          Button('barStyle:' + this.barStyleStr[this.barStyleIndex])
            .onClick(() => {
              this.barStyleIndex++
              if (this.barStyleIndex > this.barStyleValue.length - 1) {
                this.barStyleIndex = 0
              }
            })
          Button('hideBackButton:' + this.hideBackButtonValue)
            .onClick(() => {
              this.hideBackButtonValue = !this.hideBackButtonValue
            })
          Button('expandSafeArea:' + this.edgesValueStr[this.edgesValueIndex])
            .onClick(() => {
              this.edgesValueIndex++
              if (this.edgesValueIndex > this.edgesValue.length - 1) {
                this.edgesValueIndex = 0
              }
            })
          Button('navBarPosition:' + this.navBarPositionValueStr[this.navBarPositionValueIndex])
            .onClick(() => {
              this.navBarPositionValueIndex++
              if (this.navBarPositionValueIndex > this.navBarPositionValue.length - 1) {
                this.navBarPositionValueIndex = 0
              }
            })
          }
      }.height('100%')
    }
    .title(this.titleValue[this.titleValueIndex], {backgroundColor:Color.Pink,
      barStyle:this.barStyleValue[this.barStyleIndex]})
    .titleMode(this.titleModeValue[this.titleModeValueIndex])
    .mode(this.modeValue[this.modeValueIndex])
    .hideBackButton(this.hideBackButtonValue)
    .navBarWidthRange(['150vp','432vp'])
    .minContentWidth('50vp')
    .borderWidth(1)
    .expandSafeArea([SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD],
      this.edgesValue[this.edgesValueIndex])
    .navBarPosition(this.navBarPositionValue[this.navBarPositionValueIndex])
    .backgroundColor('#ffd5e5fa')
  }
}