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
import { pageOneTmp } from './pageOne'
import { pageTwoTmp } from './pageTwo'
import { pageThreeTmp } from './pageThree'
// import { pages }  from './pageThree'

@Entry
@Component
struct test1 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @State text : String = ''
  @State number : number = 0
  @State mode: NavigationMode = NavigationMode.Auto
  @State navBarWidth: number = 240
  @State minNavBarWidth: number = 240
  @State maxNavBarWidth: number = 350
  @State hideTitleBar: boolean = false
  @State hideToolBar: boolean = false

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp()
    } else if (name === 'pageThree') {
      pageThreeTmp()
    }
  }

  @Builder NavigationTitle() {
    Column() {
      Text('Title')
        .fontColor('#182431')
        .fontSize(30)
        .lineHeight(41)
        .fontWeight(700)
      Text('subtitle')
        .fontColor('#182431')
        .fontSize(14)
        .lineHeight(19)
        .opacity(0.4)
        .margin({ top: 2, bottom: 20 })
    }.alignItems(HorizontalAlign.Start)
  }

  @Builder NavigationMenus() {
    Row() {
      Image('common/ic_public_add.svg')
        .width(24)
        .height(24)
      Image('common/ic_public_add.svg')
        .width(24)
        .height(24)
        .margin({ left: 24 })
      Image('common/ic_public_more.svg')
        .width(24)
        .height(24)
        .margin({ left: 24 })
    }
  }

  build() {
    Scroll() {
      Column() {
        Navigation(this.pageInfos) {
          Column() {
          }
        }
        .title('NavIndex')
        .navDestination(this.PageMap)
        .border({ width: 1 })
        .height(500)
        .mode(this.mode)
        .hideTitleBar(this.hideTitleBar)
        .hideToolBar(this.hideToolBar)
        .navBarWidth(this.navBarWidth)
        .navBarWidthRange([this.minNavBarWidth, this.maxNavBarWidth])
        Scroll() {
          Column() {
            Button('pushPageOne', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'pageOne' }) //将name指定的NavDestination页面信息入栈
              })
            Button('pushPageTwo', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'pageTwo' }) //将name指定的NavDestination页面信息入栈
              })
            Button('pushPageThree', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.pushPath({ name: 'pageThree' }) //将name指定的NavDestination页面信息入栈
              })
            Button('清除全部页面')
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.pageInfos.clear() //将name指定的NavDestination页面信息入栈
              })
            Row() {
              Text('显示模式:')
              Text('单栏').width(50).onClick(() => {
                this.mode = NavigationMode.Stack
              })
              Text('双栏').width(50).onClick(() => {
                this.mode = NavigationMode.Split
              })
              Text('自适应').width(50).onClick(() => {
                this.mode = NavigationMode.Auto
              })
            }

            Row() {
              Text('导航栏宽度')
              Counter() {
                Text(this.navBarWidth.toString())
              }.margin({ right: 20 })
              .onInc(() => {
                this.navBarWidth++
              })
              .onDec(() => {
                this.navBarWidth--
              })
              // .offset({ x:-30 })
            }.height(50).width('50%')

            Row() {
              Text('minNavBarWidth:')
              Counter() {
                Text(this.minNavBarWidth.toString())
              }.margin({ right: 20 })
              .onInc(() => {
                this.minNavBarWidth++
              })
              .onDec(() => {
                this.minNavBarWidth--
              })
              // .offset({ x:-30 })
            }.height(50).width('50%')

            Row() {
              Text('maxNavBarWidth:')
              Counter() {
                Text(this.maxNavBarWidth.toString())
              }.margin({ right: 20 })
              .onInc(() => {
                this.maxNavBarWidth++
              })
              .onDec(() => {
                this.maxNavBarWidth--
              })

              // .offset({ x:-30 })
            }.height(50).width('50%')
          }
        }.height(250)
      }
    }
  }
}