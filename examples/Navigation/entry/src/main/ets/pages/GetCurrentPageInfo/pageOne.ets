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
// pageOne.ets
import { MyParam } from "./common"
import { CustomTransition } from './CustomNavigationUtils'
let durationOne: number = 1000

export class pages {
  names: string = ""
  values: NavPathStack | null = null
}

@Component
export struct pageOneTmp {
  private pathStack: NavPathStack | null = null;
  @State lifeCycle: string = "";
  @State text :string = ''
  @State text2 :string = ''
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
            p.text = "from pageOne"
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
    .title('pageOne')
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
    .id("A07")
  }
}