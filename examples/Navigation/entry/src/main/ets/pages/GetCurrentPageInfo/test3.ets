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
import { pageOneTmp } from './pageOne'
import { pageTwoTmp } from './pageTwo'

@Component
struct pageThreeTmp {
  private pathStack: NavPathStack | null = null;
  @State text: string = "none";
  @State text2: string = "none";
  @State lifeCycle: string = "";


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
    .id("A03")
  }
}

@Entry
@Component
struct test3 {
  @Provide stack: NavPathStack = new NavPathStack();
  @Provide stack2: NavPathStack = new NavPathStack();
  @State text: string = ''
  @State text2: string = ''
  @State lifeCycle: string = "";
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
        Scroll(){
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

            NavRouter() {
              Row() {
                Row()
                  .width(30)
                  .height(30)
                  .borderRadius(30)
                  .margin({ left: 3, right: 10 })
                  .backgroundColor(Color.Pink)
                Text(`pageFour`)
                  .fontSize(22)
                  .fontWeight(500)
                  .textAlign(TextAlign.Center)
              }
              .width('90%')
              .height(60)

              NavDestination() {
                Column() {
                  Text('pageFour')
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
              .title('pageFour')
              .onReady((ctx: NavDestinationContext) => {
                this.lifeCycle += "<onReady>";
                try {
                  this.text2 = JSON.stringify(ctx.pathInfo)
                  console.log(`testTag onReady: info: ${JSON.stringify(ctx.pathInfo)}  stack: ${JSON.stringify(ctx.pathStack)}`)
                } catch (e) {
                  console.log(`testTag onReady catch exception: ${JSON.stringify(e)}`)
                }
              })
              .id("C03")
            }
            .margin({ top: 10, bottom: 10 })
            .borderRadius(20)
            .mode(NavRouteMode.PUSH_WITH_RECREATE)
            .onStateChange((isActivated: boolean) => {
            })

            Navigation(this.stack2){
              Column(){
                Button('childrenPushPathOne', { stateEffect: true, type: ButtonType.Capsule })
                  .width('80%')
                  .height(40)
                  .margin(20)
                  .onClick(() => {
                    let p = new MyParam();
                    p.text = "from children navigation"
                    this.stack2.pushPath({ name: 'pageOne', param: p})
                  })
              }
            }.navDestination(this.PageMap).title("children")
            .id("D03")

          }
          .width('100%')
          .height('100%')
        }.width('100%').height(750)
      }
      .width('100%')
      .height('100%')
      .navDestination(this.PageMap)
      .title("NavIndex")
      .id("B03")
    }
  }
}