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

import { BusinessError, Callback } from '@ohos.base';
import { JSON } from '@kit.ArkTS';
import observer from '@ohos.arkui.observer';

class DerivedNavPathStack extends NavPathStack {

  getParent(): NavPathStack | null {
    console.log('reached DerivedNavPathStack\'s getParent');
    return super.getParent();
  }

}


@Entry
@Component
struct Index114323 {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  derivedStack2: DerivedNavPathStack = new DerivedNavPathStack();
  faStack: NavPathStack = new NavPathStack();
  @Builder
  pageMap(name: string) {
    if (name === 'pageOne') {
      PageOne()
    } else if (name === 'pageTwo') {
      PageTwo()
    } else if (name === 'pageThree') {
      PageThree()
    }
  }

  build() {
    Column({ space: 10 }) {
      Button('parent Navigation push pageOne')
        .onClick(() => {
          this.faStack.pushPath({name:'pageOne'})
        })

      Button('child Navigation getParent&clean Navigation stack')
        .onClick(() => {
          let stack = this.derivedStack.getParent()
          if(stack) {
            stack.clear()
            console.log('getParent return :' + JSON.stringify(this.derivedStack.getParent()))
          } else {
            console.log('getParent return :' + this.derivedStack.getParent())
          }
        })

      Navigation(this.faStack) {
        Navigation(this.derivedStack) {
          Column({space:10}){

          }.width('100%')
        }
        .height('70%')
        .title('child Navigation')
        .backgroundColor('#ffb0cdb0')
        .navDestination(this.pageMap)
      }
      .height('35%')
      .title('parent Navigation')
      .backgroundColor(Color.Pink)
      .navDestination(this.pageMap)

      Button('no parent Navigation getParent')
        .onClick(() => {
          let stack = this.derivedStack2.getParent()
          if(stack) {
            stack.clear()
            console.log('getParent return :' + JSON.stringify(this.derivedStack2.getParent()))
          } else {
            console.log('getParent return :' + this.derivedStack2.getParent())
          }
        })
      Navigation(this.derivedStack2) {
      }
      .height('35%')
      .title('no parent Navigation')
      .backgroundColor(Color.Pink)
      .navDestination(this.pageMap)

    }
  }
}

@Component
struct PageOne {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  curStringifyParam: string = '';
  build() {
    NavDestination() {
      Column({space:10}) {
      }
    }
    .title('pageOne')
    .backgroundColor(Color.Pink)
    .onReady((context: NavDestinationContext) => {
      console.log('PageOne onReady');
      this.derivedStack = context.pathStack as DerivedNavPathStack;
    })
    .onBackPressed(() => {
      console.log(`pageOne on backpress`)
      this.derivedStack?.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log('pageOne onWillAppear')
    })
    .onAppear(()=>{
      console.log('pageOne onAppear')
    })
    .onWillShow(()=>{
      console.log('pageOne onWillShow')
    })
    .onShown(()=>{
      console.log('pageOne onShown')
    })
    .onWillHide(()=>{
      console.log('pageOne onWillHide')
    })
    .onHidden(()=>{
      console.log('pageOne onHidden')
    })
    .onWillDisappear(()=>{
      console.log('pageOne onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('pageOne onDisAppear')
    })

  }
}


@Component
struct PageTwo {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  curStringifyParam: string = '';
  build() {
    NavDestination() {
      Column({space:10}) {
      }
    }
    .title('pageTwo')
    .backgroundColor(Color.Pink)
    .onReady((context: NavDestinationContext) => {
      console.log('PageTwo onReady');
      this.derivedStack = context.pathStack as DerivedNavPathStack;
    })
    .onBackPressed(() => {
      console.log(`PageTwo on backpress`)
      this.derivedStack?.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log('PageTwo onWillAppear')
    })
    .onAppear(()=>{
      console.log('PageTwo onAppear')
    })
    .onWillShow(()=>{
      console.log('PageTwo onWillShow')
    })
    .onShown(()=>{
      console.log('PageTwo onShown')
    })
    .onWillHide(()=>{
      console.log('PageTwo onWillHide')
    })
    .onHidden(()=>{
      console.log('PageTwo onHidden')
    })
    .onWillDisappear(()=>{
      console.log('PageTwo onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('PageTwo onDisAppear')
    })
  }
}

@Component
struct PageThree {
  derivedStack: DerivedNavPathStack = new DerivedNavPathStack();
  curStringifyParam: string = '';
  build() {
    NavDestination() {
      Column({space:10}) {
      }
    }
    .title('pageThree')
    .backgroundColor(Color.Pink)
    .onReady((context: NavDestinationContext) => {
      console.log(' PageThree onReady');
      this.derivedStack = context.pathStack as DerivedNavPathStack;
    })
    .onBackPressed(() => {
      console.log(`pageThree on backpress`)
      this.derivedStack?.pop()
      return true
    })
    .onWillAppear(()=>{
      console.log('pageThree onWillAppear')
    })
    .onAppear(()=>{
      console.log('pageThree onAppear')
    })
    .onWillShow(()=>{
      console.log('pageThree onWillShow')
    })
    .onShown(()=>{
      console.log('pageThree onShown')
    })
    .onWillHide(()=>{
      console.log('pageThree onWillHide')
    })
    .onHidden(()=>{
      console.log('pageThree onHidden')
    })
    .onWillDisappear(()=>{
      console.log('pageThree onWillDisappear')
    })
    .onDisAppear(()=>{
      console.log('pageThree onDisAppear')
    })
  }
}