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

import { Colors } from '@kit.ArkUI'
import { Tool } from '../Index'


@Component
export struct MyButton {
  text: string = ''
  onClickFunction: (event: ClickEvent) => void = ()=>{}
  backGdColor = '#ccc'

  build() {
    Button() {
      Text(this.text)
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
    }
    .width('100%')
    .type(ButtonType.Capsule)
    .margin({ top: 4 })
    .onClick(this.onClickFunction)
    .backgroundColor(this.backGdColor)
  }
}

@Entry({ routeName: 'newInstanceTest' })
@Component
struct forcedNewInstance {
  @Provide('stack') stack: NavPathStack = new NavPathStack()

  aboutToAppear(): void {
    this.getUIContext().getUIObserver().on('routerPageUpdate', (info) => {
      console.log('[router] observerInfo: ' + JSON.stringify(info))
    })
  }

  @Builder
  pageMap(name: string) {
    if (name.substring(0, 7) == 'pageOne') {
      PageOne()
    } else if (name.substring(0, 7) == 'pageTwo') {
      PageTwo()
    }
  }

  @State mode:NavigationMode = NavigationMode.Auto

  build() {
    Navigation(this.stack) {
      Text('空白过渡页面')
    }.navDestination(this.pageMap)
    .mode(NavigationMode.Auto)
    .onAppear(() => {
      this.stack.pushDestination({ name: 'pageTwo'})
    })
  }
}

@Component
export struct PageOne {
  @Consume('stack') stack: NavPathStack
  @State stackSize: number = -1
  @State stackArray: Array<string> = []

  name: string = 'PAGE_ONE'

  build() {
    NavDestination() {
      Column() {
        Text('当前栈信息: ')
          .fontSize(35)
          .fontWeight(FontWeight.Bold)
        Text(JSON.stringify(this.stackArray))
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
      }
      MyButton({
        text: 'push new_instance pageTwo',
        onClickFunction: () => {
          this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
        }
      })

      MyButton({
        text: 'push pageOne',
        onClickFunction: () => {
          this.stack.pushDestination({ name: 'pageOne' })
        }
      })

      MyButton({
        text: 'push pageTwo',
        onClickFunction: () => {
          this.stack.pushDestination({ name: 'pageTwo'  })
        }
      })

      MyButton({
        text: 'push new_instance pageOne',
        onClickFunction: () => {
          this.stack.pushDestination({ name: 'pageOne' }, { launchMode: LaunchMode.NEW_INSTANCE})
        }
      })

      MyButton({
        text: 'pop*2 + push pageTwo',
        onClickFunction: () => {
          this.stack.pop()
          this.stack.pop()
          this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
        }
      })

      MyButton({
        text: 'pop*2 + push pageTwo,pageOne',
        onClickFunction: () => {
          this.stack.pop()
          this.stack.pop()
          this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
          this.stack.pushPath({ name: 'pageOne' }, { launchMode: LaunchMode.NEW_INSTANCE })
        }
      })

      MyButton({
        text: 'clear + push pageTwo',
        onClickFunction: () => {
          this.stack.clear()
          this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
        }
      })

    }.title('Page One')
    .onWillShow(() => {
      console.log('[new_instance][life] ' +'Page One' + ' onWillShow')
    })
    .onShown(() => {
      console.log('[new_instance][life] ' + 'Page One' + ' onShown')
      this.stackSize = this.stack.size()

    })
    .onWillHide(() => {
      console.log('[new_instance][life] ' + 'Page One' + ' onWillHide')
    })
    .onHidden(() => {
      console.log('[new_instance][life] ' + 'Page One' + ' onHidden')
    })
    .onWillAppear(() => {
      console.log('[new_instance][life] ' + 'Page One' + ' onWillAppear')
    })
    .onAppear(() => {
      console.log('[new_instance][life] ' + 'Page One' + ' onAppear')
    })
    .onWillDisappear(() => {
      console.log('[new_instance][life] ' + 'Page One' + ' onWillDisappear')
    })
    .onDisAppear(() => {
      console.log('[new_instance][life] ' + 'Page One' + ' onDisAppear')
    })
  }
}

@Component
export struct PageTwo {
  @Consume('stack') stack: NavPathStack
  @State stackSize: number = -1
  @State stackArray: Array<string> = []
  color: Color = (Tool.count) % 2 == 0 ? Color.Pink : Color.Gray
  @State name: string = 'PAGE_TWO'
  @State mode: NavigationMode = NavigationMode.Auto
  private scroller: Scroller = new Scroller()

  build() {
    NavDestination() {
      Scroll(this.scroller){
        Column(){
          Column() {
            Text('当前栈信息: (索引:名称)')
              .fontSize(35)
              .fontWeight(FontWeight.Bold)
            Text(JSON.stringify(this.stackArray))
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
          }
          //不使用New Instance
          Column() {
            Column() {
              Text('不使用New Instance')
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .textAlign(TextAlign.Start)
                .position({top: 7, left: 7})
            }.margin(5)
            Scroll(this.scroller) {
              Column(){
                MyButton({
                  text: 'push pageOne',
                  onClickFunction: () => {
                    this.stack.pushDestination({ name: 'pageOne' })
                  }
                })
                MyButton({
                  text: 'push pageTwo',
                  onClickFunction: () => {
                    this.stack.pushDestination({ name: 'pageTwo' })
                  }
                })

                MyButton({
                  text: 'push pageTwo*3',
                  onClickFunction: () => {
                    this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
                    this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
                    this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
                  }
                })

                MyButton({
                  text: 'pop*2,push pageTwo',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pop()
                    this.stack.pushDestination({ name: 'pageTwo' })
                  }
                })

                MyButton({
                  text: 'push pageTwo*2',
                  onClickFunction: () => {
                    this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
                    this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
                  }
                })

                MyButton({
                  text: 'pop + pageTwo*2',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pushDestination({ name: 'pageTwo' })
                    this.stack.pushDestination({ name: 'pageTwo' })
                  }
                })


                MyButton({
                  text: 'pop + push pageTwo',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pushPath({ name: 'pageTwo' })
                  }
                })

                MyButton({
                  text: '清空栈 + push pageTwo',
                  onClickFunction: () => {
                    this.stack.clear()
                    this.stack.pushDestination({ name: 'pageTwo' })
                  }
                })
                MyButton({
                  text: 'push pageTwo + pop',
                  onClickFunction: () => {
                    this.stack.pushPath({ name: 'pageTwo' })
                    this.stack.pop()
                  }
                })

                MyButton({
                  text: 'popToName pageTwo',
                  onClickFunction: () => {
                    this.stack.popToName('pageTwo')
                  }
                })
                MyButton({
                  text: 'pop + push pageTwo',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pushPath({ name: 'pageTwo' })
                  }
                })

              }
            }.height('275vp').scrollBar(BarState.On)

          }.backgroundColor('#598')
          .width('100%')
          .height('275vp')
          .margin(15)
          // 使用New Instance
          Column() {
            Column() {
              Text('使用New Instance')
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .textAlign(TextAlign.Start)
                .position({top: 7, left: 7})
            }

            Scroll(this.scroller){
              Column(){
                MyButton({
                  text: 'push 新实例 pageTwo',
                  onClickFunction: () => {
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
                  }
                })
                MyButton({
                  text: 'push 新实例 pageTwo*5',
                  onClickFunction: () => {
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})

                  }
                })

                MyButton({
                  text: 'pop*2 + push 新实例 pageTwo',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pop()
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
                  }
                })

                MyButton({
                  text: 'pop + push 新实例 pageTwo',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
                  }
                })

                MyButton({
                  text: 'pop + push 新实例 two *2',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ }, { launchMode: LaunchMode.NEW_INSTANCE})
                    this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ }, { launchMode: LaunchMode.NEW_INSTANCE})
                  }
                })

                MyButton({
                  text: 'pop + push 新实例 (无动画)',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE, animated: false })
                  }
                })

                MyButton({
                  text: '清空栈 + push 新实例 Two',
                  onClickFunction: () => {
                    this.stack.clear()
                    this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
                  }
                })

                MyButton({
                  text: 'push 新实例 Two + pop',
                  onClickFunction: () => {
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                    this.stack.pop()

                  }
                })
                MyButton({
                  text: 'pop*2,push pageTwo*2',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pop()
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                  }
                })
                MyButton({
                  text: 'pop*2 + push 新实例 Two*2',
                  onClickFunction: () => {
                    this.stack.pop()
                    this.stack.pop()
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                  }
                })

                MyButton({
                  text: 'push 新实例 Two*2 + pop*2',
                  onClickFunction: () => {
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                    this.stack.pop()
                    this.stack.pop()

                  }
                })

                MyButton({
                  text: 'popToname pageTwo + push 新实例 Two',
                  onClickFunction: () => {
                    this.stack.popToName('pageTwo')
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                  }
                })
                MyButton({
                  text: 'replace pageTwo + push 新实例 Two',
                  onClickFunction: () => {
                    this.stack.replacePath({name: 'pageTwo',  param: null},{ launchMode: LaunchMode.NEW_INSTANCE })
                    this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                  }
                })
                MyButton({
                  text: 'push*100,popToName,push*10',
                  onClickFunction: () => {
                    let i:number
                    for(i=1;i<=100;i++)
                    {
                      this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                    }
                    this.stack.popToName('pageTwo')
                    for(i=1;i<=10;i++)
                    {
                      this.stack.pushPath({ name: 'pageTwo' },{ launchMode: LaunchMode.NEW_INSTANCE })
                    }
                  }
                })

              }
            }.height('350vp').scrollBar(BarState.On)

          }.backgroundColor('#aff')
          .width('100%')
          .height('350vp')
        }

      }.height('100%')
      .scrollBar(BarState.On)
      .scrollable(ScrollDirection.Vertical)

    }.title(this.name).backgroundColor(this.color)
    .onReady((ctx: NavDestinationContext) => {
      this.stack = ctx.pathStack
      this.name = ctx.pathInfo.name
      let allName = this.stack.getAllPathName()
      this.stackArray = []
      for (let i = 0; i < allName.length ; i++) {
        this.stackArray.push(i + ':' + allName[i])
      }
    })
    .onWillShow(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillShow')
    })
    .onShown(() => {
      console.log('[new_instance][life] ' + this.name + ' onShown')
      this.stackSize = this.stack.size()

    })
    .onWillHide(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillHide')
    })
    .onHidden(() => {
      console.log('[new_instance][life] ' + this.name + ' onHidden')
    })
    .onWillAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillAppear')
    })
    .onAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onAppear')
    })
    .onWillDisappear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillDisappear')
    })
    .onDisAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onDisAppear')
    })

  }
}

