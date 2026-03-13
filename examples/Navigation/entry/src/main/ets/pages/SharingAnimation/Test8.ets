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
struct NavigationDemo8 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOne8()
    } else if (name === 'pageTwo') {
      pageTwo8()
    }
  }

  @State disableAnimation: boolean = false

  build() {
    Navigation(this.pageInfos) {
      Column() {

        Button('全局是否禁用转场动画，disableAnimation: ' + this.disableAnimation)
          .margin(20)
          .onClick(()=>{
            this.disableAnimation = !this.disableAnimation
            this.pageInfos.disableAnimation(this.disableAnimation)
          })

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
struct pageOne8 {
  @Consume('pageInfos') pageInfos: NavPathStack;

  build() {
    NavDestination() {
      Scroll(){
        Column({space:20}) {
          Button('跳转PageTwo-pushPath-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPath({ name: 'pageTwo' }, false)
              })
            })

          Button('跳转PageTwo-pushPath-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPath({ name: 'pageTwo' }, true)
              })
            })

          Button('跳转PageTwo-pushPath-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPath({ name: 'pageTwo' })
              })
            })

          Button('跳转PageTwo-pushPathByName-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPathByName( 'pageTwo' ,null, false)
              })
            })

          Button('跳转PageTwo-pushPathByName-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPathByName( 'pageTwo' ,null, true)
              })
            })

          Button('跳转PageTwo-pushPathByName-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPathByName( 'pageTwo',null)
              })
            })

          Button('跳转PageTwo-replacePath-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePath( { name: 'pageTwo' }, false)
              })
            })

          Button('跳转PageTwo-replacePath-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePath( { name: 'pageTwo' }, true)
              })
            })

          Button('跳转PageTwo-replacePath-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePath( { name: 'pageTwo' })
              })
            })

          Button('跳转PageTwo-replacePathByName-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePathByName( 'pageTwo' ,null, false)
              })
            })

          Button('跳转PageTwo-replacePathByName-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePathByName( 'pageTwo' ,null, true)
              })
            })

          Button('跳转PageTwo-replacePathByName-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePathByName( 'pageTwo' ,null)
              })
            })

          Button('Pop-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pop(false)
              })
            })

          Button('Pop-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pop(true)
              })
            })

          Button('Pop-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pop()
              })
            })

          Button('回退到第一个pageTwo页面,popToName-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToName( 'pageTwo', false)
              })
            })

          Button('回退到第一个pageTwo页面,popToName-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToName( 'pageTwo', true)
              })
            })

          Button('回退到第一个pageTwo页面,popToName-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToName( 'pageTwo')
              })
            })

          Button('回退到索引为1的页面,popToIndex-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToIndex( 1, false)
              })
            })

          Button('回退到索引为1的页面,popToIndex-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToIndex( 1, true)
              })
            })

          Button('回退到索引为1的页面,popToIndex-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToIndex( 1)
              })
            })

          Button('将第一个名为pageTwo页面移到栈顶,moveToTop-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveToTop( 'pageTwo', false)
              })
            })

          Button('将第一个名为pageTwo页面移到栈顶,moveToTop-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveToTop( 'pageTwo', true)
              })
            })

          Button('将第一个名为pageTwo页面移到栈顶,moveToTop-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveToTop( 'pageTwo')
              })
            })

          Button('将索引为1的页面移到栈顶,popToIndex-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveIndexToTop( 1, false)
              })
            })

          Button('将索引为1的页面移到栈顶,popToIndex-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveIndexToTop( 1, true)
              })
            })

          Button('将索引为1的页面移到栈顶,popToIndex-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveIndexToTop( 1)
              })
            })


          Button('清除栈中所有页面,clear-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.clear(false)
              })
            })

          Button('清除栈中所有页面,clear-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.clear(true)
              })
            })

          Button('清除栈中所有页面,clear-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.clear()
              })
            })

        }
      }.height(300).borderWidth(1).margin({bottom:20}).padding({top:20,bottom:20})

      Image($r('app.media.1')).geometryTransition('picture')
        .borderWidth(2)
        .width(200)
        .height(300)
    }
    .title('pageOne')
    // 3.通过transition控制其1000ms后下树
    .transition(TransitionEffect.opacity(0.99).animation({ duration: 1000 }))
    .onBackPressed(() => {
      this.pageInfos.pop()
      return true
    })
  }
}

// pageTwo.ets
@Component
struct pageTwo8 {
  @Consume('pageInfos') pageInfos: NavPathStack;

  build() {
    NavDestination() {


      Scroll(){
        Column({space:20}) {
          Button('跳转pageOne-pushPath-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPath({ name: 'pageOne' }, false)
              })
            })

          Button('跳转pageOne-pushPath-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPath({ name: 'pageOne' }, true)
              })
            })

          Button('跳转pageOne-pushPath-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPath({ name: 'pageOne' })
              })
            })

          Button('跳转pageOne-pushPathByName-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPathByName( 'pageOne' ,null, false)
              })
            })

          Button('跳转pageOne-pushPathByName-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPathByName( 'pageOne' ,null, true)
              })
            })

          Button('跳转pageOne-pushPathByName-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pushPathByName( 'pageOne',null)
              })
            })

          Button('跳转pageOne-replacePath-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePath( { name: 'pageOne' }, false)
              })
            })

          Button('跳转pageOne-replacePath-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePath( { name: 'pageOne' }, true)
              })
            })

          Button('跳转pageOne-replacePath-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePath( { name: 'pageOne' })
              })
            })

          Button('跳转pageOne-replacePathByName-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePathByName( 'pageOne' ,null, false)
              })
            })

          Button('跳转pageOne-replacePathByName-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePathByName( 'pageOne' ,null, true)
              })
            })

          Button('跳转pageOne-replacePathByName-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              // 1.转场操作放到动画闭包中
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.replacePathByName( 'pageOne' ,null)
              })
            })

          Button('Pop-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pop(false)
              })
            })

          Button('Pop-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pop(true)
              })
            })

          Button('Pop-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.pop()
              })
            })

          Button('回退到第一个pageOne页面,popToName-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToName( 'pageOne', false)
              })
            })

          Button('回退到第一个pageOne页面,popToName-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToName( 'pageOne', true)
              })
            })

          Button('回退到第一个pageOne页面,popToName-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToName( 'pageOne')
              })
            })

          Button('回退到索引为1的页面,popToIndex-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToIndex( 1, false)
              })
            })

          Button('回退到索引为1的页面,popToIndex-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToIndex( 1, true)
              })
            })

          Button('回退到索引为1的页面,popToIndex-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.popToIndex( 1)
              })
            })

          Button('将第一个名为pageOne页面移到栈顶,moveToTop-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveToTop( 'pageOne', false)
              })
            })

          Button('将第一个名为pageOne页面移到栈顶,moveToTop-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveToTop( 'pageOne', true)
              })
            })

          Button('将第一个名为pageOne页面移到栈顶,moveToTop-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveToTop( 'pageOne')
              })
            })

          Button('将索引为1的页面移到栈顶,popToIndex-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveIndexToTop( 1, false)
              })
            })

          Button('将索引为1的页面移到栈顶,popToIndex-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveIndexToTop( 1, true)
              })
            })

          Button('将索引为1的页面移到栈顶,popToIndex-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.moveIndexToTop( 1)
              })
            })


          Button('清除栈中所有页面,clear-animated:false', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.clear(false)
              })
            })

          Button('清除栈中所有页面,clear-animated:true', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.clear(true)
              })
            })

          Button('清除栈中所有页面,clear-不设置animated', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .onClick(() => {
              animateTo({ duration: 1000 }, () => {
                this.pageInfos.clear()
              })
            })

        }
      }.height(300).borderWidth(1).margin({bottom:20}).padding({top:20,bottom:20})

        Image($r('app.media.2'))
          .border({ color: Color.Red, width: 2 })
          .width(300).height(200)
          .geometryTransition('picture')


    }
    .title('pageTwo')
    .transition(TransitionEffect.opacity(0.99).animation({ duration: 1000 }))
    .onBackPressed(() => {
      this.pageInfos.pop()
      return true
    })
  }
}