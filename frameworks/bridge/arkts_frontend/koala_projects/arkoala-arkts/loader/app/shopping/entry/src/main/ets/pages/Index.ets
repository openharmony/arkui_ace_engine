/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

//import mediaQuery from '@ohos.mediaquery';
import { TabTitleModel } from '../model/homeModel'
import { tabTitleData } from '../data/homeData'
import { MainPage } from './homePage/main'
import { VisitPage } from './homePage/visitPage'
import { Information } from './homePage/informance'
import { Detail } from './detailPage/detail'
import { SearchPage } from  './search/searchPage'
//import mediaquery from '@ohos.mediaquery';
import { SearchParam } from '../model/routeModel'

@Entry
@Component
struct Index {
    @State device: string = ''
    @State tabsIndex: number = 0
    @State tabTittleData: Array<TabTitleModel> = tabTitleData
    @State idx: number = 0
    controller: TabsController = new TabsController()
    @State opacity1: number = 1
    @State width1: number = 100
    @State ratio: number = 1
    @Provide('pathInfos') pathInfos : NavPathStack = new NavPathStack()
    //listener = mediaQuery.matchMediaSync('(orientation:landscape)')

    aboutToAppear() {
        //this.listener.on('change', this.onPortrait)
    }
    /*
      async onPortrait(mediaQueryResult:mediaquery.MediaQueryResult) {
        let result = mediaQueryResult.matches
        if (result) {
          this.width1 = 45
        } else {
          this.width1 = 100
        }
      }
    */
    @Builder
    shoppingRouter(name: string, param: Object) {
        if (name === 'detailPage') {
            Detail()
        } else if (name === 'searchPage') {
            // Arkoala: original Shopping passed param to SearchPage
            // But it does not good.
            SearchPage()
        }
    }

    build() {
        Stack() {
            Navigation(this.pathInfos) {
                Column() {
                    Column() {
                        Tabs({ barPosition: BarPosition.Start, controller: this.controller, index: this.tabsIndex }) {
                            TabContent() {
                                MainPage({ num: this.width1, ratio: this.ratio })
                            }.tabBar({ text: this.tabTittleData[0].title })

                            TabContent() {
                                VisitPage({ ratio: this.ratio })
                            }.tabBar({ text: this.tabTittleData[0].title })

                            TabContent() {
                                Information({ ratio: this.ratio })
                            }.tabBar({ text: this.tabTittleData[0].title })
                        }
                        .barWidth(400)
                            .barHeight(0)
                            .scrollable(false)
                            .animationDuration(200)
                            .height('92%')

                        Column() {
                            Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
                                ForEach(this.tabTittleData, (item: TabTitleModel) => {
                                    Flex({
                                        direction: FlexDirection.Column,
                                        justifyContent: FlexAlign.Center,
                                        alignItems: ItemAlign.Center
                                    }) {
                                        Image(this.tabsIndex == item.id ? item.selectedUri : item.uri)
                                            .width(25 * this.ratio)
                                            .aspectRatio(1)
                                            .objectFit(ImageFit.Contain)
                                        Text(item.title)
                                            .fontSize(15 * this.ratio)
                                            .margin(1)
                                            .fontColor(this.tabsIndex == item.id ? Color.Orange : Color.Black)
                                    }
                                    .width('20%')
                                        .onClick((e?: ClickEvent) => {
                                            this.tabsIndex = item.id
                                            this.controller.changeIndex(item.id)
                                        })
                                },  (item: TabTitleModel) => JSON.stringify(item))
                            }
                            .height('8%')
                        }
                        .width('100%')
                    }
                    .width(`${this.width1}%`)
                    .backgroundColor(Color.White)
                }
                .width('100%')
                .backgroundColor('#10000000')
            }
            .mode(NavigationMode.Stack)
            .hideTitleBar(true)
            .navDestination(this.shoppingRouter)
        }
        .margin({top:50, bottom: 50} as Padding)
    }

    // pageTransition() {
    //     PageTransitionEnter({ duration: 0, curve: Curve.Linear, delay: 0 })
    //         .onEnter((type: RouteType, progress: number) => {
    //             this.opacity1 = 1
    //         })
    //     PageTransitionExit({ duration: 0, curve: Curve.Linear, delay: 0 })
    //         .onExit((type: RouteType, progress: number) => {
    //             this.opacity1 = 1
    //         })
    // }
}
