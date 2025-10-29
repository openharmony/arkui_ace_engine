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
import { pages }  from './pageTwo'

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
  @State navBarWidth: number = 240
  @State minNavBarWidth: number = 240
  @State maxNavBarWidth: number = 350
  @State flag1 : boolean = false
  @State flag2 : boolean = false
  @State top1: number = 0
  @State left1: number = 0
  @State bottom1: number = 0
  @State right1: number = 0
  @State backgroundColor1: string[] = ['#ffffff','#8bd4cc']
  @State index: number = 0
  scroller: Scroller = new Scroller()

  @State types: Array <SafeAreaType> = [SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD]
  @State edges: Array <SafeAreaEdge> = [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END]
  
  @Styles counterStyle() {
    .padding(3)
    .height(32)
  }

  @Styles buttonStyles() {
    .padding(4)
    .height(22)
    .margin(2)
  }

  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp({ names: name, values: this.pageInfos } as pages)
    }
  }
  
  @Builder NavigationTitle() {
    Column() {
      Text('Title')
        .fontColor('#182431')
        .fontSize(30)
        .lineHeight(41)
        .fontWeight(700)
      Text('subtitle')
        .fontColor('#182431')
        .fontSize(14)
        .lineHeight(19)
        .opacity(0.4)
        .margin({ top: 2, bottom: 20 })
    }.alignItems(HorizontalAlign.Start)
  }

  @Builder NavigationMenus() {
    Row() {
      Image('common/ic_public_add.svg')
        .width(24)
        .height(24)
      Image('common/ic_public_add.svg')
        .width(24)
        .height(24)
        .margin({ left: 24 })
      Image('common/ic_public_more.svg')
        .width(24)
        .height(24)
        .margin({ left: 24 })
    }
  }
  @Builder text1(){
    Text('text').height('350').width('240').border({width:1})
  }
  build() {
    Column() {
      if (this.flag1){
        this.text1()
      }
      Navigation(this.pageInfos) {
        Scroll(this.scroller){
          Column(){
            TextInput({ placeholder: 'search...' })
              .width('90%')
              .height(40)
              .backgroundColor('#FFFFFF')
              .margin({ top: 8 })

            List({ space: 8, initialIndex: 0 }) {
              ListItem(){
                Row() {
                  Button(this.hideTitleBar ? 'showTitleBar' : 'hideTitleBar')
                    .fontSize(12)
                    .buttonStyles()
                    .onClick(() => {
                      this.hideTitleBar = !this.hideTitleBar
                    })
                  Button(this.hideToolBar ? 'showToolBar' : 'hideToolBar')
                    .fontSize(12)
                    .buttonStyles()
                    .onClick(() => {
                      this.hideToolBar = !this.hideToolBar
                    })
                }
              }
              ListItem() {
                Row() {
                  Text('mode:').fontSize(12)
                  Text('Stack').fontSize(12).width(50).onClick(() => {
                    this.mode = NavigationMode.Stack
                  })
                  Text('Split').fontSize(12).width(50).onClick(() => {
                    this.mode = NavigationMode.Split
                  })
                  Text('Auto').fontSize(12).width(50).onClick(() => {
                    this.mode = NavigationMode.Auto
                  })
                }
              }
              ListItem() {
                Row() {
                  Text('width').fontSize(12)
                  Counter() {
                    Text(this.navBarWidth.toString())
                  }.counterStyle()
                  .onInc(() => {
                    this.navBarWidth++
                  })
                  .onDec(() => {
                    this.navBarWidth--
                  })
                }.width('50%')
              }
              ListItem() {
                Row() {
                  Text('minNavBarWidth:').fontSize(12)
                  Counter() {
                    Text(this.minNavBarWidth.toString())
                  }.counterStyle()
                  .onInc(() => {
                    this.minNavBarWidth++
                  })
                  .onDec(() => {
                    this.minNavBarWidth--
                  })
                }.width('50%')
              }
              ListItem() {
                Row() {
                  Text('maxNavBarWidth:').fontSize(12)
                  Counter() {
                    Text(this.maxNavBarWidth.toString())
                  }.counterStyle()
                  .onInc(() => {
                    this.maxNavBarWidth++
                  })
                  .onDec(() => {
                    this.maxNavBarWidth--
                  })
                }.width('50%')
              }
              ListItem() {
                Button(this.flag1 ? 'Navigation set no text in top' : 'Navigation set text in top')
                  .fontSize(12)
                  .buttonStyles()
                  .onClick(() => {
                    this.flag1 = !this.flag1
                  })
              }
              ListItem() {
                Button(this.flag2 ? 'Navigation set no text in bottom' : 'Navigation set text in bottom')
                  .fontSize(12)
                  .buttonStyles()
                  .onClick(() => {
                    this.flag2 = !this.flag2
                  })
              }
              ListItem() {
                Row() {
                  Text('top:').fontSize(12)
                  Counter() {
                    Text(this.top1.toString())
                  }.counterStyle()
                  .onInc(() => {
                    this.top1++
                  })
                  .onDec(() => {
                    this.top1--
                  })
                }.width('50%')
              }
              ListItem() {
                Row() {
                  Text('left:').fontSize(12)
                  Counter() {
                    Text(this.left1.toString())
                  }.counterStyle()
                  .onInc(() => {
                    this.left1++
                  })
                  .onDec(() => {
                    this.left1--
                  })
                }.width('50%')
              }
              ListItem() {
                Row() {
                  Text('bottom:').fontSize(12)
                  Counter() {
                    Text(this.bottom1.toString())
                  }.counterStyle()
                  .onInc(() => {
                    this.bottom1++
                  })
                  .onDec(() => {
                    this.bottom1--
                  })
                }.width('50%')
              }
              ListItem() {
                Row() {
                  Text('right:').fontSize(12)
                  Counter() {
                    Text(this.right1.toString())
                  }.counterStyle()
                  .onInc(() => {
                    this.right1++
                  })
                  .onDec(() => {
                    this.right1--
                  })
                }.width('50%')
              }
              ListItem() {
                Row() {
                  Button('change backgroundColor')
                    .fontSize(12)
                    .buttonStyles()
                    .onClick(() => {
                      this.index++
                      if (this.index > this.backgroundColor1.length - 1) {
                        this.index = 0
                      }
                    })
                  Button('pushPath', { stateEffect: true, type: ButtonType.Capsule })
                    .fontSize(12)
                    .buttonStyles()
                    .onClick(() => {
                      this.pageInfos.pushPath({ name: 'pageOne' })
                    })
                }
              }
              ListItem() {
                Column() {
                  Row() {
                    Button('SYSTEM')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        if (!this.types.some(item => item == SafeAreaType.SYSTEM)) {
                          this.types.push(SafeAreaType.SYSTEM)
                        }
                      })
                    Button('CUTOUT')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        if (!this.types.some(item => item == SafeAreaType.CUTOUT)) {
                          this.types.push(SafeAreaType.CUTOUT)
                        }
                      })
                    Button('KEYBOARD')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        if (!this.types.some(item => item == SafeAreaType.KEYBOARD)) {
                          this.types.push(SafeAreaType.KEYBOARD)
                        }
                      })
                  }
                }
              }
              ListItem() {
                Column() {
                  Row() {
                    Button('SYSTEM')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        this.types = this.types.filter(item => item != SafeAreaType.SYSTEM)
                      })
                    Button('CUTOUT')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        this.types = this.types.filter(item => item != SafeAreaType.CUTOUT,)
                      })
                    Button('KEYBOARD')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        this.types = this.types.filter(item => item != SafeAreaType.KEYBOARD)
                      })
                  }
                }
              }
              ListItem() {
                Column() {
                  Row() {
                    Button('TOP')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        if (!this.edges.some(item => item == SafeAreaEdge.TOP)) {
                          this.edges.push(SafeAreaEdge.TOP)
                        }
                      })
                    Button('BOTTOM')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        if (!this.edges.some(item => item == SafeAreaEdge.BOTTOM)) {
                          this.edges.push(SafeAreaEdge.BOTTOM)
                        }
                      })
                    Button('START')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        if (!this.edges.some(item => item == SafeAreaEdge.START)) {
                          this.edges.push(SafeAreaEdge.START)
                        }
                      })
                    Button('END')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        if (!this.edges.some(item => item == SafeAreaEdge.END)) {
                          this.edges.push(SafeAreaEdge.END)
                        }
                      })
                  }
                }
              }
              ListItem() {
                Column() {
                  Row() {
                    Button('TOP')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        this.edges = this.edges.filter(item => item != SafeAreaEdge.TOP)
                      })
                    Button('BOTTOM')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        this.edges = this.edges.filter(item => item != SafeAreaEdge.BOTTOM)

                      })
                    Button('START')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        this.edges = this.edges.filter(item => item != SafeAreaEdge.START)
                      })
                    Button('END')
                      .fontSize(12)
                      .buttonStyles()
                      .onClick(() => {
                        this.edges = this.edges.filter(item => item != SafeAreaEdge.END)
                      })
                  }
                }
              }
            }
            .width('100%')
            .height(500)
          }
        }
      }
      .mode(this.mode)
      .title(this.NavigationTitle)
      .menus(this.NavigationMenus)
      .titleMode(NavigationTitleMode.Full)
      .toolbarConfiguration([
        {
          value: 'add',
          icon: $r('app.media.344')
        },
        {
          value: 'app',
          icon: $r('app.media.354')
        },
        {
          value: 'collect',
          icon: $r('app.media.360')
        }
      ])
      
      .navDestination(this.PageMap)
      
      .hideTitleBar(this.hideTitleBar)
      .hideToolBar(this.hideToolBar)
      .navBarWidth(this.navBarWidth)
      .navBarWidthRange([this.minNavBarWidth,this.maxNavBarWidth])
      .expandSafeArea(this.types,this.edges)
      .margin({top:this.top1,left:this.left1,bottom:this.bottom1,right:this.right1})
      .backgroundColor(this.backgroundColor1[this.index])
      if (this.flag2){
        this.text1()
      }
    }.width('100%').height('100%').backgroundColor('#F1F3F5')
  }
}