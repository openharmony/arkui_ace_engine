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

export const navId1: string = "navigationId1";
export const navId2: string = 'navigationId2';

@Component
export struct pageOneDialog {
  private stack: NavPathStack | null = null;
  private prevNum: number = 0;
  @Prop str: string = '';

  build() {
    NavDestination() {
      Column({space:5}) {
        Button(this.str + ' push pageTwo')
          .onClick(() => {
            if (this.stack) {
              this.stack.pushPath({name: "pageTwo", param: this.prevNum + 1});
            }
          })

        Button(this.str + ' removeByIndexes 0')
          .onClick(() => {
            if (this.stack) {
              this.stack.removeByIndexes([0]);
            }
          })

        Button(this.str + ' replacePathByName pageThree')
          .onClick(() => {
            this.stack?.replacePathByName( "pageThree", this.prevNum + 1)
          })
      }
      .width('100%')
      .height('100%')
    }
    .mode(NavDestinationMode.DIALOG)
    .backgroundColor('#ffaed8ee')
    .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM])
    .title('pageOne')
    .onAppear(() => {
      console.log(`testTag pageOne onAppear`)
    })
    .onDisAppear(() => {
      console.log(`testTag pageOne onDisAppear`)
    })
    .onShown(() => {
      console.log(`testTag pageOne onShown`)
    })
    .onHidden(() => {
      console.log(`testTag pageOne onHidden`)
    })
    .onBackPressed(() => {
      console.log(`testTag pageOne on backpress`)
      this.stack?.pop()
      return true
    })
    .onReady((ctx: NavDestinationContext) => {
      try {
        console.log(`testTag pageOne onReady`)
        this.prevNum = ctx?.pathInfo?.param as number;
        this.stack = ctx.pathStack;
      } catch (e) {
        console.log(`testTag onReady catch exception: ${JSON.stringify(e)}`)
      }
    })

  }
}

@Component
export struct pageTwoDialog {
  private stack: NavPathStack | null = null;
  private prevNum: number = 0;
  @Prop str: string = '';


  build() {
    NavDestination() {
      Column({space:5}) {
        Button(this.str + 'push pageOne')
          .onClick(() => {
            if (this.stack) {
              this.stack.pushPath({name: "pageOne", param: this.prevNum + 1});
            }
          })

        Button(this.str + ' replacePathByName pageOne')
          .onClick(() => {
            this.stack?.replacePathByName( "pageOne", this.prevNum + 1)
          })

        Button(this.str + ' replacePathByName pageThree')
          .onClick(() => {
            this.stack?.replacePathByName( "pageThree", this.prevNum + 1)
          })

        Row({space:5}){
          Button(this.str +' clear')
            .onClick(() => {
              this.stack?.clear()
            })

          Button(this.str +' pop')
            .onClick(() => {
              if (this.stack) {
                this.stack.pop();
              }
            })
        }

        Button(this.str +' push pageThree')
          .onClick(() => {
            this.stack?.pushPath({name: "pageThree", param: this.prevNum + 1});
          })

      }
      .width('100%')
      .height('100%')
    }
    .mode(NavDestinationMode.DIALOG)
    .title('pageTwo')
    .backgroundColor('#ffaed8ee')
    .onAppear(() => {
      console.log(`testTag pageTwo onAppear`)
    })
    .onDisAppear(() => {
      console.log(`testTag pageTwo onDisAppear`)
    })
    .onShown(() => {
      console.log(`testTag pageTwo onShown`)
    })
    .onHidden(() => {
      console.log(`testTag pageTwo onHidden`)
    })
    .onBackPressed(() => {
      console.log(`testTag pageTwo on backpress`)
      this.stack?.pop()
      return true
    })
    .onReady((ctx: NavDestinationContext) => {
      try {
        console.log(`testTag pageTwo onReady`)
        this.prevNum = ctx?.pathInfo?.param as number;
        this.stack = ctx.pathStack;
      } catch (e) {
        console.log(`testTag onReady catch exception: ${JSON.stringify(e)}`)
      }
    })

  }
}

@Component
export struct pageThreeDialog {
  private stack: NavPathStack | null = null;
  private prevNum: number = 0;
  @Prop str: string = '';

  build() {
    NavDestination() {
     Column({space:5}){
      Button(this.str +' pop')
        .onClick(() => {
          if (this.stack) {
            this.stack.pop();
          }
        })

      }
      .width('100%')
      .height('100%')
    }
    .title('pageThree')
    .backgroundColor('#ffaed8ee')
    .onAppear(() => {
      console.log(`testTag pageThree onAppear`)
    })
    .onDisAppear(() => {
      console.log(`testTag pageThree onDisAppear`)
    })
    .onShown(() => {
      console.log(`testTag pageThree onShown`)
    })
    .onHidden(() => {
      console.log(`testTag pageThree onHidden`)
    })
    .onBackPressed(() => {
      console.log(`testTag pageThree on backpress`)
      this.stack?.pop()
      return true
    })
    .onReady((ctx: NavDestinationContext) => {
      try {
        console.log(`testTag pageThree onReady`)
        this.prevNum = ctx?.pathInfo?.param as number;
        this.stack = ctx.pathStack;
      } catch (e) {
        console.log(`testTag onReady catch exception: ${JSON.stringify(e)}`)
      }
    })
  }
}



@Component
export struct custom {
  build() {
    Row() {
      Button('query info')
        .margin(5)
        .onClick(() => {
          let info = this.queryNavDestinationInfo();
          console.log('123'+ JSON.stringify(info))
        })
    }.width('100%').justifyContent(FlexAlign.Center)
  }
}
