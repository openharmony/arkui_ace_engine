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
import router from '@ohos.router';
import { MyParam } from "./common"
import { CustomTransition } from './CustomNavigationUtils'
import { pageOneTmp } from './pageOne'
import { pageTwoTmp } from './pageTwo'
let durationOne: number = 1000


@Component
struct pageThreeTmp {
  private pathStack: NavPathStack | null = null;
  @State text: string = "none";
  @State text2: string = "none";
  @State lifeCycle: string = "";
  @State opacity1: number = 1
  aboutToAppear() {
    CustomTransition.getInstance().registerNavParam('pageOne', (isPush: boolean, onFinish: () => void,isexit:boolean, isPop: boolean) => {
      if (isexit && isPop == false) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else if (isPush && isPop == false) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else if (isPop) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      }
    })
  }

  build() {
    NavDestination() {
      Column() {
        Button('pushPath', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(20)
          .margin(10)
          .onClick(() => {
            let p = new MyParam();
            p.text = "from pageThree"
            this.pathStack?.pushPath({ name: 'pageTwo' , param: p})
          })
        Button('pop', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(20)
          .margin(10)
          .onClick(() => {
            this.pathStack?.pop();
          })
        Button('clear', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(20)
          .margin(10)
          .onClick(() => {
            this.pathStack?.clear()
          })
        Text(this.text)
        Text(this.text2)
        Text(this.lifeCycle)
      }
      .width('100%')
      .height('100%')
    }
    .onShown(()=>{
      this.lifeCycle += "<onShown>"
    })
    .onHidden(()=>{
      this.lifeCycle += "<onHidden>"
    })
    .onAppear(() => {
      this.lifeCycle += "<onAppear>";
    })
    .onDisAppear(() => {
      this.lifeCycle += "<onDisAppear>";
    })
    .title('pageThree')
    .onReady((ctx: NavDestinationContext) => {
      this.lifeCycle += "<onReady>";
      try {
        this.text = (ctx.pathInfo.param as MyParam).text;
        this.text2 = JSON.stringify(ctx.pathInfo)
        this.pathStack = ctx.pathStack;
        console.log(`testTag onReady: info: ${JSON.stringify(ctx.pathInfo)}  stack: ${JSON.stringify(ctx.pathStack)}`)
      } catch (e) {
        console.log(`testTag onReady catch exception: ${JSON.stringify(e)}`)
      }
    })
    .id('A05')
  }
}

@Entry
@Component
struct test5 {
  private stack: NavPathStack = new NavPathStack();
  @State opacity1: number = 1
  @State text1: string = ''
  aboutToAppear() {
    CustomTransition.getInstance().registerNavParam('pageOne', (isPush: boolean, onFinish: () => void,isexit:boolean, isPop: boolean) => {
      if (isexit && isPop == false) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else if (isPush && isPop == false) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else if (isPop) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      }
    })
  }
  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp()
    }else if (name === 'pageThree') {
      pageThreeTmp()
    }
  }

  build() {
    Column() {
      Button("back to Main page", { stateEffect: true, type: ButtonType.Capsule })
        .onClick(() => {
          router.back();
        })
      Navigation(this.stack) {
        Column() {
          Button('pushPathOne', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(20)
            .margin(10)
            .onClick(() => {
              let p = new MyParam();
              p.text = "from mainPage"
              this.stack.pushPath({ name: 'pageOne', param: p})
            })
          Button('pushPathTwo', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(20)
            .margin(10)
            .onClick(() => {
              let p = new MyParam();
              p.text = "from mainPage"
              this.stack.pushPath({ name: 'pageTwo', param: p})
            })
          Button('pushPathThree', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(20)
            .margin(10)
            .onClick(() => {
              let p = new MyParam();
              p.text = "from mainPage"
              this.stack.pushPath({ name: 'pageThree', param: p})
            })
          Text(this.text1)
        }
        .width('100%')
        .height('100%')
      }
      .customNavContentTransition((from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => {
        this.text1 = NavigationOperation[operation] + ''
        if (from.mode === NavDestinationMode.DIALOG || to.mode === NavDestinationMode.DIALOG) {
          console.log("Dialog navDestination do system transition animation.")
          return undefined
        }
        // 其他页面做自定义动画
        let customAnimation: NavigationAnimatedTransition
        customAnimation = {
          onTransitionEnd: () => {

          },
          timeout: 500,
          transition: (transitionContext) => {
            let onFinish: () => void = () => {
              transitionContext.finishTransition()
            }
            // from页面的自定义动画
            let fromAnimatedFunc: (isPush: boolean, onFinish: () => void,isexit: boolean, isPop: boolean) => void
            fromAnimatedFunc = CustomTransition.getInstance().getNavParam(transitionContext.from.name)
            if (fromAnimatedFunc != undefined && operation === NavigationOperation.PUSH) {
              fromAnimatedFunc(operation === NavigationOperation.PUSH, onFinish,false,false)
            }

            // to页面的自定义动画
            let toAnimatedFunc: (isPush: boolean, onFinish: () => void,isexit: boolean, isPop: boolean) => void
            toAnimatedFunc = CustomTransition.getInstance().getNavParam(transitionContext.to.name)
            if (toAnimatedFunc != undefined && operation == NavigationOperation.PUSH) {
              toAnimatedFunc(operation == NavigationOperation.PUSH, onFinish,true,false)
            }
          }

        }
        return customAnimation
      })
      .width('100%')
      .height('100%')
      .navDestination(this.PageMap)
      .title("NavIndex")
    }
  }
}