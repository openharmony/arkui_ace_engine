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

import I18n from '@ohos.i18n';
import window from '@ohos.window';
import base from '@ohos.base';

@Entry
@Component
struct test1{
  @Provide pageInfos:NavPathStack = new NavPathStack()
  @State mode:NavigationMode = NavigationMode.Stack
  @State launchMode:LaunchMode = LaunchMode.STANDARD

  @State height1:string = '100%'
  @State width1:string = '100%'
  @State navBarWidth:number = 240
  @State minContentWidth:number = 360
  @State min:number = 240
  @State max:number = 400

  @State navBarPosition:NavBarPosition = NavBarPosition.Start

  private myWindow: window.Window | null = null;

  createWindow() {
    try {
      window.createWindow({name: 'testWindow', windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow?.resize(1000, 2200);
          this.myWindow?.moveWindowTo(50, 200);
          let ls = new LocalStorage();
          console.log('loadContent before')
          this.myWindow?.loadContent('pages/37-ssasdadsadsa/WindowTwo', ls)
            .then(() => {
              console.log(`testTag success to loadContent`)
            }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
          })
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)

          }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
          });
        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }

  @Builder
  PageMap(name: string){
    if (name === 'pageOne') {
      pageOne()
    }
  }

  build() {
    Column(){
      Navigation(this.pageInfos){
        Scroll(){
          Column({space:5}){
            Row() {
              Text('mode:').fontSize(15)
              Blank()
              Column({space:5}){
                Row(){
                  Radio({ value: 'Radio1', group: 'radioGroup' }).checked(true)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(15)
                    .width(15)
                    .onChange((isChecked: boolean) => {
                      this.mode = NavigationMode.Stack
                    })
                  Text('Stack').fontSize(15)
                }
                Row(){
                  Radio({ value: 'Radio2', group: 'radioGroup' }).checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(15)
                    .width(15)
                    .onChange((isChecked: boolean) => {
                      this.mode = NavigationMode.Split
                    })
                  Text('Split').fontSize(15)
                }
                Row(){
                  Radio({ value: 'Radio3', group: 'radioGroup' }).checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(15)
                    .width(15)
                    .onChange((isChecked: boolean) => {
                      this.mode = NavigationMode.Auto
                    })
                  Text('Auto').fontSize(15)
                }
              }.alignItems(HorizontalAlign.Start)
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(80)


            Row() {
              Text('Navigation宽高是否为50%:').fontSize(15)
              Blank()
              Toggle({ type: ToggleType.Switch, isOn: false })
                .selectedColor('#007DFF')
                .switchPointColor('#FFFFFF')
                .onChange((isOn: boolean) => {
                  if (isOn) {
                    this.height1 = '50%'
                    this.width1 = '50%'

                  }else{
                    this.height1 = '100%'
                    this.width1 = '100%'

                  }
                })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(30)

            Row() {
              Text('navBarWidth:').fontSize(15)
              Blank()
              Counter() {
                Text(this.navBarWidth.toString())
              }
              .onInc(() => {
                this.navBarWidth += 10
              })
              .onDec(() => {
                this.navBarWidth -= 10
              })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(30)

            Row() {
              Text('minContentWidth:').fontSize(15)
              Blank()
              Counter() {
                Text(this.minContentWidth.toString())
              }
              .onInc(() => {
                this.minContentWidth += 10
              })
              .onDec(() => {
                this.minContentWidth -= 10
              })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(30)

            Row() {
              Text('导航栏最小宽度:').fontSize(15)
              Blank()
              Counter() {
                Text(this.min.toString())
              }
              .onInc(() => {
                this.min += 10
              })
              .onDec(() => {
                this.min -= 10
              })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(30)
            Row() {
              Text('导航栏最大宽度:').fontSize(15)
              Blank()
              Counter() {
                Text(this.max.toString())
              }
              .onInc(() => {
                this.max += 10
              })
              .onDec(() => {
                this.max -= 10
              })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(30)

            Button('设置维吾尔语', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              I18n.System.setAppPreferredLanguage('ar-EG');
            }).width('90%').borderRadius(8)
            Button('设置中文', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              I18n.System.setAppPreferredLanguage('zh');
            }).width('90%').borderRadius(8)

            Button('pushPath pageOne', { type: ButtonType.Normal, stateEffect: true }).onClick((event: ClickEvent) => {
              this.pageInfos.pushPath({name:'pageOne'})
            }).width('90%').borderRadius(8)

            Row() {
              Text('导航栏位置是否为start').fontSize(15)
              Blank()
              Toggle({ type: ToggleType.Switch, isOn: true })
                .selectedColor('#007DFF')
                .switchPointColor('#FFFFFF')
                .onChange((isOn: boolean) => {
                  if (isOn) {
                    this.navBarPosition =NavBarPosition.Start
                  }else{
                    this.navBarPosition =NavBarPosition.End
                  }
                })
            }.backgroundColor(0xFFFFFF).width('100%').padding({left:10,right:10}).borderRadius(15).height(30)

            SideBarContainer(SideBarContainerType.Embed) {
              Column() {


              }.width('100%')
              .justifyContent(FlexAlign.SpaceEvenly)
              .backgroundColor('#19000000')

              Column() {
                Text('SideBarContainer content text1').fontSize(25)
                Text('SideBarContainer content text2').fontSize(25)
              }
              .margin({ top: 50, left: 20, right: 30 })
            }
            .controlButton({
              icons: {
                hidden: $r('app.media.icon'),
                shown: $r('app.media.icon'),
                switching: $r('app.media.icon')
              }
            })
            .sideBarWidth(150)
            .minSideBarWidth(50)
            .maxSideBarWidth(300)
            .minContentWidth(0)

            Button('开启子窗口')
              .onClick(() => {
                this.createWindow();
              })

          }.width('100%').backgroundColor(0xEFEFEF).padding(10)
        }
        .height('100%')
      }
      .mode(this.mode)
      .navBarWidth(this.navBarWidth)
      .minContentWidth(this.minContentWidth)
      .navBarWidthRange([this.min,this.max])
      .height(this.height1)
      .border({width:1})
      .navBarPosition(this.navBarPosition)
      .navDestination(this.PageMap)
    }
  }
}

@Component
export struct pageOne{
  @Consume('pageInfos') pageInfos: NavPathStack
  @State launchMode:LaunchMode = LaunchMode.STANDARD

  build() {
    NavDestination(){
      Scroll(){
        SideBarContainer(SideBarContainerType.Embed) {
          Column() {


          }.width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
          .backgroundColor('#19000000')

          Column() {
            Text('SideBarContainer content text1').fontSize(25)
            Text('SideBarContainer content text2').fontSize(25)
          }
          .margin({ top: 50, left: 20, right: 30 })
        }
        .controlButton({
          icons: {
            hidden: $r('app.media.icon'),
            shown: $r('app.media.icon'),
            switching: $r('app.media.icon')
          }
        })
        .sideBarWidth(150)
        .minSideBarWidth(50)
        .maxSideBarWidth(300)
        .minContentWidth(0)
      }
    }
    .title('pageOne')
  }
}