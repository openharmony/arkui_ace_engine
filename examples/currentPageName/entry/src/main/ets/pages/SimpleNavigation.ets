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



@Builder
export function PageOneBuilder(name: string, param: Object) {
  PageOneComponent()
}

@Component
struct PageOneComponent {
  private stack: NavPathStack | null = null;
  @State eventStr: string = "";

  build() {
    NavDestination() {
      Column() {
        Text("event: " + this.eventStr)

        Button('pushPath', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            if (this.stack) {
              this.stack.pushPath({ name: "test/pageTwo" });
            }
          })
        Button('pop', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.stack?.pop()
          })
      }
      .width('100%')
      .height('100%')
    }
    .title('pageOne')
    .onAppear(() => {
      this.eventStr += "<onAppear>";
    })
    .onDisAppear(() => {
      this.eventStr += "<onDisAppear>";
    })
    .onShown(() => {
      this.eventStr += "<onShown>";
    })
    .onHidden(() => {
      this.eventStr += "<onHidden>";
    })
    .onWillAppear(() => {
      this.eventStr += "<onWillAppear>";
    })
    .onWillDisappear(() => {
      this.eventStr += "<onWillDisappear>";
    })
    .onWillShow(() => {
      this.eventStr += "<onWillShow>";
    })
    .onWillHide(() => {
      this.eventStr += "<onWillHide>";
    })
    // onReady会在onAppear之前调用
    .onReady((ctx: NavDestinationContext) => {
      try {
        this.eventStr += "<onReady>";
        this.stack = ctx.pathStack;
      } catch (e) {
        console.log(`testTag onReady catch exception: ${JSON.stringify(e)}`)
      }
    })
  }
}

@Entry
@Component
struct NavigationExample3 {
  private stack: NavPathStack = new NavPathStack();

  build() {
    Navigation(this.stack) {
      Stack({ alignContent: Alignment.Center }) {
        Button('pushPath', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.stack.pushPath({ name: "test/pageOne" })
          })
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
    .title('Navigation')
  }
}