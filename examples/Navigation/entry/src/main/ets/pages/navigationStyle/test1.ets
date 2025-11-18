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

import { pageOneTmp } from './pageOne'
import { pageTwoTmp } from './pageTwo'

class A {
  text: string = ''
  num: number = 0
}

@Entry
@Component
struct NavigationExample {
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  @State currentIndex: number = 0
  @State hideTitleBar: boolean = false
  @State hideToolBar: boolean = false
  @State mode: NavigationMode = NavigationMode.Auto
  @State titleMode: NavigationTitleMode = NavigationTitleMode.Free
  @State navBarWidth: number = 240
  @State minNavBarWidth: number = 240
  @State maxNavBarWidth: number = 350
  @State value: BlurStyle = BlurStyle.NONE
  @State value2: BlurStyle = BlurStyle.NONE
  @State NavBarPosition1: NavBarPosition = NavBarPosition.Start
  @State height2: number = 50
  @State height1: number = 100
  @State width1: number = 100
  @State backgroundColor1: Color[] = [Color.Gray,Color.Red,Color.Pink,Color.Brown]
  @State index: number = 2

  @Styles buttonStyles() {
    .padding({top: 0, left: 5, right: 5, bottom: 0})
    .height(24)
    .margin({bottom: 4, left: 1, right: 1})
  }


  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp()
    }
  }


  @Builder NavigationTitle() {
    Column() {
      Text('Title')
        .fontColor('#182431')
        .fontSize(30)
        .lineHeight(41)
        .fontWeight(700)
    }.alignItems(HorizontalAlign.Start)
    .backgroundColor(Color.Pink)

    .height(this.height1).width(this.width1)

  }

  @Builder NavigationMenus() {
    Row() {
      Image($r('app.media.background'))
        .width(24)
        .height(24)
      Image($r('app.media.foreground'))
        .width(24)
        .height(24)
        .margin({ left: 24 })
      Image($r('app.media.startIcon'))
        .width(24)
        .height(24)
        .margin({ left: 24 })
    }.backgroundColor('#5e86ff')

  }
  @Builder toolbarConfiguration(){
    Row(){
      Column(){
        Text('add')
      }.width('50%')
      Column(){
        Text('app')
      }.width('50%')
      Column(){}
    }
    .height(this.height2)
    .backgroundImage($r('app.media.background'))
  }
  build() {
    Column() {
      Navigation(this.pageInfos) {
        Row() {
          Column() {
            Button(this.hideTitleBar ? 'showTitleBar' : 'hideTitleBar')
              .fontSize(10)
              .buttonStyles()
              .margin({top: 8, bottom: 2})
              .onClick(() => {
                this.hideTitleBar = !this.hideTitleBar
              })

            Button(this.hideToolBar ? 'showToolBar' : 'hideToolBar')
              .fontSize(10)
              .buttonStyles()
              .onClick(() => {
                this.hideToolBar = !this.hideToolBar
              })
            Row() {
              Button('Stack')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.mode = NavigationMode.Stack
                })
              Button('Split')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.mode = NavigationMode.Split
                })
              Button('Auto')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.mode = NavigationMode.Auto
                })
            }.width('100%').justifyContent(FlexAlign.Start)
            Row() {
              Button('Free')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.titleMode = NavigationTitleMode.Free
                })
              Button('Mini')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.titleMode = NavigationTitleMode.Mini
                })
              Button('Full')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.titleMode = NavigationTitleMode.Full
                })
            }.width('100%').justifyContent(FlexAlign.Start)
            Counter() {
              Text(this.navBarWidth.toString())
            }
            .padding(3)
            .height(32)
            .onInc(() => {
              this.navBarWidth++
            })
            .onDec(() => {
              this.navBarWidth--
            })
            Text('minNavBarWidth:').fontSize(11)
            Counter() {
              Text(this.minNavBarWidth.toString())
            }
            .padding(3)
            .height(32)
            .onInc(() => {
              this.minNavBarWidth++
            })
            .onDec(() => {
              this.minNavBarWidth--
            })

            Text('maxNavBarWidth:').fontSize(11)
            Counter() {
              Text(this.maxNavBarWidth.toString())
            }
            .padding(3)
            .height(32)
            .onInc(() => {
              this.maxNavBarWidth++
            })
            .onDec(() => {
              this.maxNavBarWidth--
            })


            Counter() {
              Text(this.height1.toString())
            }
            .padding(3)
            .height(32)
            .onInc(() => {
              this.height1++
            })
            .onDec(() => {
              this.height1--
            })

            Counter() {
              Text(this.width1.toString())
            }
            .padding(3)
            .height(32)
            .onInc(() => {
              this.width1 += 10
            })
            .onDec(() => {
              this.width1 -= 10
            })

            Counter() {
              Text(this.height2.toString())
            }
            .padding(3)
            .height(32)
            .onInc(() => {
              this.height2++
            })
            .onDec(() => {
              this.height2--
            })

            Button('toggle backgroundColor')
              .fontSize(10)
              .buttonStyles()
              .onClick((event: ClickEvent) => {
                this.index++
                if (this.index > (this.backgroundColor1.length - 1)) {
                  this.index = 0
                }
              })

            Row({ space: 10 }) {
              Button('Start')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.NavBarPosition1 = NavBarPosition.Start
                })
              Button('End')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.NavBarPosition1 = NavBarPosition.End
                })
            }
          }
          .width('50%').alignItems(HorizontalAlign.Start)
          Column() {
            Column(){
              Row({ space: 5 }) {
                Button('Thin')
                  .fontSize(10)
                  .buttonStyles()
                  .onClick(() => {
                    this.value = BlurStyle.Thin
                  })
                Button('Regular')
                  .fontSize(10)
                  .buttonStyles()
                  .onClick(() => {
                    this.value = BlurStyle.Regular
                  })
              }
              Row({ space: 5 }) {
                Button('Thick')
                  .fontSize(10)
                  .buttonStyles()
                  .onClick(() => {
                    this.value = BlurStyle.Thick
                  })
                Button('NONE')
                  .fontSize(10)
                  .buttonStyles()
                  .onClick(() => {
                    this.value = BlurStyle.NONE
                  })
              }
              Button('BACKGROUND_THIN')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.BACKGROUND_THIN
                })
              Button('BACKGROUND_REGULAR')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.BACKGROUND_REGULAR
                })
              Button('BACKGROUND_THICK')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.BACKGROUND_THICK
                })
              Button('BACKGROUND_ULTRA_THICK')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.BACKGROUND_ULTRA_THICK
                })

              Button('COMPONENT_ULTRA_THIN')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.COMPONENT_ULTRA_THIN
                })
              Button('COMPONENT_THIN')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.COMPONENT_THIN
                })
              Button('COMPONENT_REGULAR')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.COMPONENT_REGULAR
                })
              Button('COMPONENT_THICK')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.COMPONENT_THICK
                })
              Button('COMPONENT_ULTRA_THICK')
                .fontSize(10)
                .buttonStyles()
                .onClick(() => {
                  this.value = BlurStyle.COMPONENT_ULTRA_THICK
                })
            }
          }
          .width('50%')
        }
        .width('100%')
        .alignItems(VerticalAlign.Top)
      }
      .mode(this.mode)
      .title(this.NavigationTitle, {backgroundBlurStyle:this.value})
      .menus(this.NavigationMenus)
      .hideTitleBar(this.hideTitleBar)
      .hideToolBar(true)
      .titleMode(this.titleMode)
      .navBarWidth(this.navBarWidth)
      .navBarWidthRange([this.minNavBarWidth,this.maxNavBarWidth])
      .navDestination(this.PageMap)
      .toolbarConfiguration(this.toolbarConfiguration)
      .navBarPosition(this.NavBarPosition1)
      .onTitleModeChange((titleModel: NavigationTitleMode) => {
        console.info('titleMode' + titleModel)
      })

      .backgroundBlurStyle(this.value2)
      .backgroundColor(this.backgroundColor1[this.index])
      .height(650)
      .width('100%')
      Button('pushOne', { stateEffect: true, type: ButtonType.Capsule })
        .width('80%')
        .height(30)
        .margin({bottom: 5})
        .onClick(() => {
          this.pageInfos.pushPath({ name: 'pageOne' })
        })
      Button('pushTwo', { stateEffect: true, type: ButtonType.Capsule })
        .width('80%')
        .height(30)
        .onClick(() => {
          this.pageInfos.pushPath({ name: 'pageTwo' })
        })
    }
    .justifyContent(FlexAlign.Start)
    .width('100%')
    .height('100%')
  }
}