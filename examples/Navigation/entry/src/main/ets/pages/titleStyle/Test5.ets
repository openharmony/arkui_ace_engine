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
@Component
struct TestResourceColor5 {

  build() {
    NavDestination() {

    }
    .width('100%')
    .height('100%')
    .title('test resource color', {backgroundColor: $r('sys.color.ohos_id_color_toolbar_bg')})
  }
}

@Component
struct OnlyColor5 {
  @State useColor1: boolean = true;

  build() {
    NavDestination() {
      Stack({alignContent: Alignment.Center}) {
        Button('switch color')
          .onClick(() => {
            this.useColor1 = !this.useColor1;
          })
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
    .title('test only color', {backgroundColor: this.useColor1 ? Color.Red : Color.Blue})
  }
}

@Component
struct OnlyBlur5 {
  @State useBlur1: boolean = true;

  build() {
    NavDestination() {
      Stack({alignContent: Alignment.Center}) {
        Button('switch blur')
          .onClick(() => {
            this.useBlur1 = !this.useBlur1;
          })
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
    .backgroundImage($r('app.media.background'))
    .title('test only blur', {
      backgroundBlurStyle: this.useBlur1 ? BlurStyle.COMPONENT_THIN : BlurStyle.COMPONENT_THICK
    })
  }
}

@Component
struct ColorAndBlur5 {
  @State useColor1: boolean = true;
  @State useBlur1: boolean = true;

  build() {
    NavDestination() {
      Column() {
        Stack({alignContent: Alignment.Center}) {
          Button('switch color')
            .onClick(() => {
              this.useColor1 = !this.useColor1;
            })
        }
        .width('100%')
        .layoutWeight(1)
        Stack({alignContent: Alignment.Center}) {
          Button('switch blur')
            .onClick(() => {
              this.useBlur1 = !this.useBlur1;
            })
        }
        .width('100%')
        .layoutWeight(1)
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
    .backgroundImage($r('app.media.background'))
    .title('test color and blur', {
      backgroundColor: this.useColor1 ? '#99990000' : '#99000099',
      backgroundBlurStyle: this.useBlur1 ? BlurStyle.COMPONENT_THIN : BlurStyle.COMPONENT_THICK
    })
  }
}



@Entry
@Component
struct Index71555 {
  @State titleModeValue: NavigationTitleMode[] = [
    NavigationTitleMode.Free,
    NavigationTitleMode.Mini,
    NavigationTitleMode.Full
  ]
  @State titleModeValueIndex: number = 0
  @State titleModeValueStr: string[] = [
    'NavigationTitleMode.Free',
    'NavigationTitleMode.Mini',
    'NavigationTitleMode.Full'
  ]

  @State modeValue: NavigationMode[] = [
    NavigationMode.Stack,
    NavigationMode.Split,
    NavigationMode.Auto
  ]
  @State modeValueIndex: number = 0
  @State modeValueStr: string[] = ['NavigationMode.Stack', 'NavigationMode.Split', 'NavigationMode.Auto']

  @State barStyleValue: BarStyle[] = [ BarStyle.STANDARD, BarStyle.STACK]
  @State barStyleIndex: number = 1
  @State barStyleStr: string[] = ['BarStyle.STANDARD', 'BarStyle.STACK']

  @State hideBackButtonValue:boolean = false


  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

  @State titleValue: (ResourceStr | NavigationCommonTitle) [] = [
    '主标题',
    '主标题主标题主标题主标题主标题主标题',
    '主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串主标题超长字符串' +
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
    '主副标题-中文-短文本','主副标题-中文-中文本', '主标题-中文-长文本',
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


  @State backgroundColorValue:ResourceColor = Color.Pink

  @Builder
  PageBuilder(name: string) {
    if (name === 'resourceColor') {
      TestResourceColor5()
    } else if (name === 'color') {
      OnlyColor5()
    } else if (name === 'blur') {
      OnlyBlur5()
    } else {
      ColorAndBlur5()
    }
  }

  private stack: NavPathStack = new NavPathStack();

  build() {
    Navigation(this.stack) {
      Column({ space: 10 }) {
        if (this.barStyleIndex === 1) {
          Button('resourceColor')
            .onClick(() => {
              this.stack.pushPath({name: 'resourceColor'})
            })
        }
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
        .width('90%')
        .height('20%')

        Scroll(){
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

            Row({space:5}){
              Button('resourceColor')
                .onClick(() => {
                  this.stack.pushPath({name: 'resourceColor'})
                })
              Button('only color')
                .onClick(() => {
                  this.stack.pushPath({name: 'color'})
                })
            }

            Row({space:5}){
              Button('only blur')
                .onClick(() => {
                  this.stack.pushPath({name: 'blur'})
                })
              Button('color and blur')
                .onClick(() => {
                  this.stack.pushPath({name: 'colorAndBlur'})
                })
            }
            Button('title backgroundColor Transparent')
              .onClick(() => {
                this.backgroundColorValue = Color.Transparent
              })

          }.height('100%')
        }.height('80%')
      }.height('100%')

    }
    .menus([{value:'menus'}])
    .title(this.titleValue[this.titleValueIndex],{
      backgroundColor:this.backgroundColorValue,
      backgroundBlurStyle:BlurStyle.Thin, 
      barStyle:this.barStyleValue[this.barStyleIndex]
    })
    .titleMode(this.titleModeValue[this.titleModeValueIndex])
    .mode(this.modeValue[this.modeValueIndex])
    .hideBackButton(this.hideBackButtonValue)
    .navBarWidthRange(['150vp','432vp'])
    .minContentWidth('50vp')
    .borderWidth(1)
    .expandSafeArea([SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD],
      this.edgesValue[this.edgesValueIndex])
    .navBarPosition(this.navBarPositionValue[this.navBarPositionValueIndex])
    .navDestination(this.PageBuilder)
    .backgroundColor('#ffd5e5fa')

  }
}