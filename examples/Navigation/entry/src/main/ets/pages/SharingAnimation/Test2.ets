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
@Entry
@Component
struct NavigationDemo2 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOne222()
    } else if (name === 'pageTwo') {
      pageTwo222()
    }
  }

  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('NavPathStack-跳转到PageOne', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageOne' })
          })
        NavRouter({ name: "pageTwo" }) {
          Button('NavRouter-跳转到PageTwo', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(20)
        }
      }
    }
    .title("Navigation")
    .navDestination(this.PageMap)

  }
}


// pageOne.ets
@Component
struct pageOne222 {
  @Consume('pageInfos') pageInfos: NavPathStack;

  build() {
    NavDestination() {
      Column({space:30}) {
        Button('跳转PageTwo，跳转动画：500ms，下树：800ms', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .onClick(() => {
            // 1.转场操作放到动画闭包中
            animateTo({ duration: 500 }, () => {
              // 2.关系系统的转场动画
              this.pageInfos.pushPath({ name: 'pageTwo' }, false)
            })
          })

        Button('Pop，跳转动画：1000ms', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .onClick(() => {
            animateTo({ duration: 1000 }, () => {
              this.pageInfos.pop(false)
            })
          })

        Image($r('app.media.1')).geometryTransition('picture')
          .borderWidth(2)
          .width(200)
          .height(400)
      }
    }
    .title('pageOne')
    .transition(TransitionEffect.opacity(0.99).animation({ duration: 800 }))
    .onBackPressed(() => {
      animateTo({ duration: 1000 }, () => {
        this.pageInfos.pop(false)
      })
      return true
    })
  }
}

// pageTwo.ets
@Component
struct pageTwo222 {
  @Consume('pageInfos') pageInfos: NavPathStack;

  build() {
    NavDestination() {
      Column({space:30}) {
        Button('跳转PageOne，跳转动画：1000ms，下树：1000ms', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .onClick(() => {
            animateTo({ duration: 1000 }, () => {
              this.pageInfos.pushPath({ name: 'pageOne' }, false)
            })
          })
        Button('Pop 跳转动画：1000ms', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .onClick(() => {
            animateTo({ duration: 500 }, () => {
              this.pageInfos.pop(false)
            })
          })

        Image($r('app.media.2'))
          .border({ color: Color.Red, width: 2 })
          .width(300).height(200)
          .geometryTransition('picture')

      }
    }
    .title('pageTwo')
    .transition(TransitionEffect.opacity(0.99).animation({ duration: 1000 }))
    .onBackPressed(() => {
      animateTo({ duration: 500 }, () => {
        this.pageInfos.pop(false)
      })
      return true
    })
  }
}