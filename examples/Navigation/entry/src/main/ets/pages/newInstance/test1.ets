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

import observer from '@ohos.arkui.observer'
import { router } from '@kit.ArkUI';

@Entry
@Component
struct test1{
  @Provide pageInfos:NavPathStack = new NavPathStack()
  @State height1:string = '100%'
  @State mode:NavigationMode = NavigationMode.Stack
  @State launchMode:LaunchMode = LaunchMode.STANDARD

  navDesUpdateCallback(info: NavDestinationInfo) {
    console.log(`testTag navDesUpdateCallback, info: ${JSON.stringify(info)}`);
    console.log(`testTag id, info: ${JSON.stringify(info.navigationId)}, name:${JSON.stringify(info.name)},navDestinationId:${JSON.stringify(info.navDestinationId)}`);
  }
  observerOn(){
    observer.on('navDestinationUpdate', this.navDesUpdateCallback);
  }
  observerOff(){
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
  }


  @Builder
  PageMap(name: string){
    if (name === 'pageOne') {
      pageOne()
    }else if (name === 'pageTwo'){
      pageTwo()
    }else if (name === 'pageThree'){
      pageThree()
    }
  }

  build() {
    Column(){
      Navigation(this.pageInfos){
        Scroll(){
          Column({space:5}){
            Text('text1')
            Button('pushPath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
                this.pageInfos.pushPath({name:'pageOne'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('pushPath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
                this.pageInfos.pushPath({name:'pageTwo'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('pushPath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
                this.pageInfos.pushPath({name:'pageThree'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

            Button('pushDestination pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
                this.pageInfos.pushDestination({name:'pageOne'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('pushDestination pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
                this.pageInfos.pushDestination({name:'pageTwo'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('pushDestination pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
                this.pageInfos.pushDestination({name:'pageThree'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

            Button('replacePath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              this.pageInfos.replacePath({name:'pageOne'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('replacePath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              this.pageInfos.replacePath({name:'pageTwo'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('replacePath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              this.pageInfos.replacePath({name:'pageThree'}, { launchMode:this.launchMode })
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)



            Button('router到pageOne页面', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              router.pushUrl({url:'pages/34-ssasdadsadsa/pageOne'})
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('router到pageTwo页面', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              router.pushUrl({url:'pages/34-ssasdadsadsa/pageTwo'})
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
            Button('router.clear', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              router.clear()
            }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

            Row() {
              Text('launchMode:')
              Blank()
              Column({space:5}){
                Row(){
                  Radio({ value: 'Radio1', group: 'radioGroup' }).checked(true)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.launchMode = LaunchMode.STANDARD
                    })
                  Text('STANDARD')
                }
                Row(){
                  Radio({ value: 'Radio2', group: 'radioGroup' }).checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.launchMode = LaunchMode.MOVE_TO_TOP_SINGLETON
                    })
                  Text('MOVE_TO_TOP_SINGLETON')
                }
                Row(){
                  Radio({ value: 'Radio3', group: 'radioGroup' }).checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.launchMode = LaunchMode.POP_TO_SINGLETON
                    })
                  Text('POP_TO_SINGLETON')
                }
                Row(){
                  Radio({ value: 'Radio4', group: 'radioGroup' }).checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.launchMode = LaunchMode.NEW_INSTANCE
                    })
                  Text('NEW_INSTANCE')
                }

              }.alignItems(HorizontalAlign.Start)
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(180)
            Row() {
              Text('Navigation是否全屏:')
              Blank()
              Toggle({ type: ToggleType.Switch, isOn: true })
                .selectedColor('#007DFF')
                .switchPointColor('#FFFFFF')
                .onChange((isOn: boolean) => {
                  if (isOn) {
                    this.height1 = '100%'
                  }else{
                    this.height1 = '50%'
                  }
                })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(50)

            Row({space:5}){
              Text('无感监听')
              Button('observerOn')
                .onClick(() => {
                  this.observerOn()
                })

              Button('observerOff')
                .onClick(() => {
                  this.observerOff()
                })
            }
          }.width('100%').backgroundColor(0xEFEFEF).padding(10)
        }
        .height('100%')
      }
      .navDestination(this.PageMap)
      .mode(this.mode)
      .height(this.height1)
      .border({width:1})
    }

  }
}

@Component
export struct pageOne{
  @Consume('pageInfos') pageInfos: NavPathStack
  @State launchMode:LaunchMode = LaunchMode.STANDARD
  @State count:number = 0

  build() {
    NavDestination(){
      Scroll(){
        Column({space:5}){
          Button('add count:' + this.count).onClick((event: ClickEvent) => {
            this.count += 1
          })
          Button('pop', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pop()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('clear', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.clear()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('pushPath pageOne111', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pop()
            this.pageInfos.pushPath({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('pushPath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushPath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushPath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('pushDestination pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushDestination pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushDestination pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('replacePath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('replacePath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('replacePath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('popToIndex 0', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.popToIndex(0)
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('router到pageOne页面', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            router.pushUrl({url:'pages/34-ssasdadsadsa/pageOne'})
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('router到pageTwo页面', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            router.pushUrl({url:'pages/34-ssasdadsadsa/pageTwo'})
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('router.clear', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            router.clear()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Row() {
            Text('launchMode:')
            Blank()
            Column({space:5}){
              Row(){
                Radio({ value: 'Radio1', group: 'radioGroup' }).checked(true)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.STANDARD
                  })
                Text('STANDARD')
              }
              Row(){
                Radio({ value: 'Radio2', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.MOVE_TO_TOP_SINGLETON
                  })
                Text('MOVE_TO_TOP_SINGLETON')
              }
              Row(){
                Radio({ value: 'Radio3', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.POP_TO_SINGLETON
                  })
                Text('POP_TO_SINGLETON')
              }
              Row(){
                Radio({ value: 'Radio4', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.NEW_INSTANCE
                  })
                Text('NEW_INSTANCE')
              }

            }.alignItems(HorizontalAlign.Start)
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(180)

        }.width('100%').backgroundColor(0xEFEFEF).padding(10)
      }
      .height('100%')
    }
    .title('pageOne')
    .onBackPressed(() => {
      this.pageInfos.pop() // 弹出路由栈栈顶元素
      return true
    })
    .onAppear(() => {
      console.log('testTag pageOne onAppear')
    })
    .onDisAppear(() => {
      console.log('testTag pageOne onDisAppear')
    })
    .onShown(() => {
      console.log('testTag pageOne onShown')
    })
    .onHidden(() => {
      console.log('testTag pageOne onHidden')
    })
    .onWillAppear(() => {
      console.log('testTag pageOne onWillAppear')
    })
    .onWillShow(() => {
      console.log('testTag pageOne onWillShow')
    })
    .onWillHide(() => {
      console.log('testTag pageOne onWillHide')
    })
    .onWillDisappear(() => {
      console.log('testTag pageOne onWillDisappear')
    })

  }
}

@Component
export struct pageTwo{
  @Consume('pageInfos') pageInfos: NavPathStack
  @State launchMode:LaunchMode = LaunchMode.STANDARD
  @State count:number = 0

  build() {
    NavDestination(){
      Scroll(){
        Column({space:5}){
          Button('add count:' + this.count).onClick((event: ClickEvent) => {
            this.count += 1
          })
          Button('pop', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pop()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('clear', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.clear()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('pushPath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushPath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushPath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('pushDestination pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushDestination pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushDestination pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('replacePath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('replacePath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('replacePath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('popToIndex 0', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.popToIndex(0)
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('router到pageOne页面', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            router.pushUrl({url:'pages/34-ssasdadsadsa/pageOne'})
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('router到pageTwo页面', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            router.pushUrl({url:'pages/34-ssasdadsadsa/pageTwo'})
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('router.clear', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            router.clear()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Row() {
            Text('launchMode:')
            Blank()
            Column({space:5}){
              Row(){
                Radio({ value: 'Radio1', group: 'radioGroup' }).checked(true)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.STANDARD
                  })
                Text('STANDARD')
              }
              Row(){
                Radio({ value: 'Radio2', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.MOVE_TO_TOP_SINGLETON
                  })
                Text('MOVE_TO_TOP_SINGLETON')
              }
              Row(){
                Radio({ value: 'Radio3', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.POP_TO_SINGLETON
                  })
                Text('POP_TO_SINGLETON')
              }
              Row(){
                Radio({ value: 'Radio4', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.NEW_INSTANCE
                  })
                Text('NEW_INSTANCE')
              }

            }.alignItems(HorizontalAlign.Start)
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(180)

        }.width('100%').backgroundColor(0xEFEFEF).padding(10)
      }
      .height('100%')
    }
    .title('pageTwo')
    .onBackPressed(() => {
      this.pageInfos.pop() // 弹出路由栈栈顶元素
      return true
    })
    .onAppear(() => {
      console.log('testTag pageTwo onAppear')
    })
    .onDisAppear(() => {
      console.log('testTag pageTwo onDisAppear')
    })
    .onShown(() => {
      console.log('testTag pageTwo onShown')
    })
    .onHidden(() => {
      console.log('testTag pageTwo onHidden')
    })
    .onWillAppear(() => {
      console.log('testTag pageTwo onWillAppear')
    })
    .onWillShow(() => {
      console.log('testTag pageTwo onWillShow')
    })
    .onWillHide(() => {
      console.log('testTag pageTwo onWillHide')
    })
    .onWillDisappear(() => {
      console.log('testTag pageTwo onWillDisappear')
    })
  }
}

@Component
export struct pageThree{
  @Consume('pageInfos') pageInfos: NavPathStack
  @State launchMode:LaunchMode = LaunchMode.STANDARD
  @State count:number = 0

  build() {
    NavDestination(){
      Scroll(){
        Column({space:5}){
          Button('add count:' + this.count).onClick((event: ClickEvent) => {
            this.count += 1
          })
          Button('pop', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pop()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('clear', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.clear()
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('pushPath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushPath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushPath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushPath({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('pushDestination pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushDestination pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('pushDestination pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.pushDestination({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('replacePath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageOne'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('replacePath pageTwo', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageTwo'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)
          Button('replacePath pageThree', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.replacePath({name:'pageThree'}, { launchMode:this.launchMode })
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Button('popToIndex 0', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
            this.pageInfos.popToIndex(0)
          }).width('90%').margin({ top: 14, bottom: 14}).borderRadius(8)

          Row() {
            Text('launchMode:')
            Blank()
            Column({space:5}){
              Row(){
                Radio({ value: 'Radio1', group: 'radioGroup' }).checked(true)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.STANDARD
                  })
                Text('STANDARD')
              }
              Row(){
                Radio({ value: 'Radio2', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.MOVE_TO_TOP_SINGLETON
                  })
                Text('MOVE_TO_TOP_SINGLETON')
              }
              Row(){
                Radio({ value: 'Radio3', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.POP_TO_SINGLETON
                  })
                Text('POP_TO_SINGLETON')
              }
              Row(){
                Radio({ value: 'Radio4', group: 'radioGroup' }).checked(false)
                  .radioStyle({
                    checkedBackgroundColor: Color.Pink
                  })
                  .height(30)
                  .width(30)
                  .onChange((isChecked: boolean) => {
                    this.launchMode = LaunchMode.NEW_INSTANCE
                  })
                Text('NEW_INSTANCE')
              }

            }.alignItems(HorizontalAlign.Start)
          }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(180)

        }.width('100%').backgroundColor(0xEFEFEF).padding(10)
      }
      .height('100%')
    }
    .title('pageThree')
    .onBackPressed(() => {
      this.pageInfos.pop() // 弹出路由栈栈顶元素
      return true
    })
    .onAppear(() => {
      console.log('pageThree onAppear')
    })
    .onDisAppear(() => {
      console.log('pageThree onDisAppear')
    })
    .onShown(() => {
      console.log('pageThree onShown')
    })
    .onHidden(() => {
      console.log('pageThree onHidden')
    })
    .onWillAppear(() => {
      console.log('pageThree onWillAppear')
    })
    .onWillShow(() => {
      console.log('pageThree onWillShow')
    })
    .onWillHide(() => {
      console.log('pageThree onWillHide')
    })
    .onWillDisappear(() => {
      console.log('pageThree onWillDisappear')
    })
  }
}