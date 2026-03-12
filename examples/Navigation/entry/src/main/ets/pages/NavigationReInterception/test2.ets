/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { BTmp } from './B'
import { CTmp } from './C'

class a{
  num = 1
}
@Entry
@Component
struct NavigationExample {
  pageInfos: NavPathStack = new NavPathStack()
  @State disableAnimation: boolean = false;
  @StorageLink('mode') mode: NavigationMode = NavigationMode.Stack
  @State text1:string = ''
  @State text2:string = ''
  @State mode2:NavigationMode =NavigationMode.Auto

  @Builder
  PageMap(name: string) {
    if (name === 'A') {
      ATmp()
    }
    if (name === 'B') {
      BTmp()
    }
    else if (name === 'C') {
      CTmp()
    }
  }

  build() {
    Column(){
      Navigation(this.pageInfos) {
        Column() {
        }
      }.title('主页面').navDestination(this.PageMap).mode(this.mode).height('30%')
      // Row(){
      //   Button('单栏').onClick(() => {
      //     this.mode = NavigationMode.Stack
      //   })
      //   Button('双栏').onClick(() => {
      //     this.mode = NavigationMode.Split
      //   })
      // }
      Scroll(){
        Column(){
          Text('返回信息:' + this.text1)
          Text('获取栈中所有NavDestination页面的名称:' + this.text2)
          Button(`push A`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'A'})
            })
          Button(`push B`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
            })
          Button(`getAllPathName`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.text2 = JSON.stringify(this.pageInfos.getAllPathName())
            })
          Button(`pushPath到B页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pushPath({name:'B'})
                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`pushPathByName到B页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pushPathByName('B',null)
                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`pushPathByName到B页面(携带onPop)`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pushPathByName('B',a,(popInfo:PopInfo) => {
                    console.info(popInfo.info.name)
                  })
                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`pushDestination到B页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pushDestination({name: 'B' })
                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`pushDestinationByName到B页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pushDestinationByName('B',null)
                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`pushDestinationByName到B页面(携带onPop)`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pushDestinationByName('B',a,(popInfo:PopInfo) => {
                    console.info(popInfo.info.name)
                  })

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`replacePath到B页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.replacePath({name:'B'})

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`replacePathByName到B页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.replacePathByName('B',null)

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`removeByIndexes删除当前页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.removeByIndexes([0])

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`removeByName删除当前页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.removeByName('A')

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`pop`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pop()

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`popToName到A`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.popToName('A')

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`popToIndex到0`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.popToIndex(0)

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`moveToTop B`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.moveToTop('B')
                }

              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }

            })
          Button(`moveIndexToTop`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.pushPath({name:'B'})
                  this.pageInfos.pushPath({name:'C'})
                  this.pageInfos.moveIndexToTop(1)

                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })
          Button(`clear`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                modeChange: (mode: NavigationMode) => {
                  this.pageInfos.clear()
                }
              });
              if (this.mode == NavigationMode.Stack) {
                this.mode = NavigationMode.Split
              }else if (this.mode == NavigationMode.Split){
                this.mode = NavigationMode.Stack
              }
            })


        }
      }.height(450)
    }
  }
}

// PageOne.ets
class TmpClass{
  count:number=10
}

@Component
export struct ATmp {
  pageInfos: NavPathStack = new NavPathStack();
  @State isChange: boolean = false;
  @State text2: string = '';

  build() {
    NavDestination() {
      Scroll(){
        Column() {

        }.width('100%').height('100%')
      }
    }.title('A页面')
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}