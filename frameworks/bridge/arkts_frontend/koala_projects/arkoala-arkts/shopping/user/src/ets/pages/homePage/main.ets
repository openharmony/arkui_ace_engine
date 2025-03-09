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

import { NavDataModel, SearchTextModel, SwiperModel, TitleBarModel } from '../../model/homeModel'
import { navData, findSearchTextData, swiperData, titleBarData } from '../../data/homeData'
import { Core1 } from './core1'
import { Boutique } from './boutique'
import { GoodsList } from './goodsList'
import { BaseRouteParam, SearchParam } from '../../model/routeModel'
@Component
export struct MainPage {
  @State navData: Array<NavDataModel> = navData
  @State searchData: Array<SearchTextModel> = findSearchTextData
  @State tabsIndex: number = 0
  @State swiperData: Array<SwiperModel> = swiperData
  controller: TabsController = new TabsController()
  @State titleBarData: Array<TitleBarModel> = titleBarData
  @State ListIndex: number = 0
  @Prop num: number
  @Prop ratio: number
  @Consume('pathInfos') pathInfos: NavPathStack

  isPerf: boolean = true

  onPageShow() {
    console.log('shopping onPageShow()')
  }

  onPageHide() {
    console.log('shopping onPageHide()')
  }

  @Builder
  build2() {
    const count = 1500
    let perfData = new Array<number>(count)
    for (let i = 0; i < count; i++) perfData[i] = i
    let now = Date.now()
    console.log(`Measuring...`)
    ForEach(perfData, (item: number, index: number) => {
        Stack().width(100).height(100).backgroundColor(Color.Red).margin(5)
    }, (item: number, index: number) => String(item))
    let passed = Date.now() - now
    console.log(`Passed ${passed}ms, ${passed / count}ms per iteration`)
  }

  build() {
    console.log('build')
    if (this.isPerf) {
      const count = 100
      let perfData = new Array<number>(count)
      for (let i = 0; i < count; i++) perfData[i] = i
      let now = Date.now()
      console.log(`Measuring...`)
      ForEach(perfData, (item: number, index: number) => {
        this.buildReal()
      }, (item: number, index: number) => String(item))
      let passed = Date.now() - now
      console.log(`Passed ${passed}ms, ${passed / count}ms per iteration`)
    } else {
      this.buildReal()
    }
  }

  @Builder
  buildReal() {
    Column() {
      Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
        Column() {
          Image('/resources/icon/scan.png')
            .width(30 * this.ratio)
            .aspectRatio(1)
            .objectFit(ImageFit.Contain)
        }
        .padding({ top: 5, bottom: 5 } as Padding)
        Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
          Image('/resources/icon/search.png')
            .width(25 * (this.ratio + 0.2))
            .aspectRatio(1)
            .objectFit(ImageFit.Contain)

          Swiper() {
            ForEach(this.searchData, (item: SearchTextModel, index: number) => {
              Column() {
                Text(item.searchText)
                  .fontSize(14 * (this.ratio + 0.2))
                  .lineHeight(23 * (this.ratio + 0.2))
              }
              .height(25 * (this.ratio + 0.2))
              .width('100%')
              .alignItems(HorizontalAlign.Start)
              .onClick((e?: ClickEvent) => {
                let searchParam : SearchParam = {
                  message: item.searchText,
                  num: this.num,
                  ratio: this.ratio
                }
                this.pathInfos.pushPath(new NavPathInfo('searchPage', searchParam))
              })
            }, (item: SearchTextModel, index: number) => JSON.stringify(item))
          }
          .width('65%')
          .autoPlay(true)
          .loop(true)
          .vertical(true)
          .indicator(false)
          .interval(2000)

          Image('/resources/icon/camera.png')
            .width(25 * (this.ratio + 0.2))
            .aspectRatio(1)
            .objectFit(ImageFit.Contain)
        }
        .border({ width: 2, color: Color.Orange, radius: 20 } as BorderOptions)
        .width('70%')
        .padding(5)

        Column() {
          Image('/resources/icon/barcode.png')
            .width(30 * this.ratio)
            .aspectRatio(1)
            .objectFit(ImageFit.Contain)
        }
        .padding({ top: 5, bottom: 5 } as Padding)
      }
      .padding(5)

      Scroll() {
        Column() {
          Row() {
            List() {
              ForEach(this.navData, (item: NavDataModel, index: number) => {
                ListItem() {
                  Text(item.navData)
                    .fontColor(item.navData == '首页' ? Color.Blue : Color.Black)
                    .fontWeight(item.navData == '首页' ? FontWeight.Bold : FontWeight.Normal)
                    .fontSize(19 * this.ratio)
                    .margin({ left: 5, right: 8 } as Margin)
                    .lineHeight(30 * this.ratio)
                }
                .height(30 * this.ratio)
              }, (item: NavDataModel, index: number) => JSON.stringify(item))
            }
            .height(30 * this.ratio)
            .width('85%')
            .listDirection(Axis.Horizontal)

            Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
              Image('/resources/icon/nav_classification.png')
                .width(20 * this.ratio)
                .aspectRatio(1)
                .objectFit(ImageFit.Contain)
              Text('分类')
                .fontSize(15 * this.ratio)
            }
            .height(30 * this.ratio)
            .width('15%')
          }
          .margin({ bottom: 0, left: 5, right: 5 } as Margin)

          Swiper() {
            ForEach(this.swiperData, (item: SwiperModel, index: number) => {
              Image(item.img)
                .width('100%')
                .height('100%')
                .objectFit(ImageFit.Contain)
                .border({ radius: 10 * this.ratio } as BorderOptions)
                .onClick((e?: ClickEvent)=>{
                  let params : BaseRouteParam = {
                    num: this.num,
                    ratio: this.ratio
                  }
                  this.pathInfos.pushPath(new NavPathInfo('detailPage', params))
                })

            }, (item: SwiperModel, index: number) => JSON.stringify(item))
          }
          .autoPlay(true)
          .loop(true)
          .width('93%')
          .aspectRatio(2.6)

          Column() {
            Core1({ ratio: this.ratio })
          }

          Column() {
            Boutique({ ratio: this.ratio })
          }
          .margin({ top: 10 } as Margin)

          Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
            ForEach(this.titleBarData, (item: TitleBarModel, index: number) => {
              Column() {
                Text(item.title)
                  .fontSize(15 * this.ratio)
                  .margin(3)
                  .fontColor(this.tabsIndex == item.id ? Color.Orange : Color.Black)
              }
              .width('20%')
              .padding({ top: 5, bottom: 5 } as Padding)
              .onClick((e?: ClickEvent) => {
                this.tabsIndex = item.id
                this.controller.changeIndex(item.id)
              })
            }, (item: TitleBarModel, index: number) => JSON.stringify(item))
          }
          .height('7%')
          .zIndex(2)
          .backgroundColor(Color.White)

          Column() {
            Tabs({ controller: this.controller }) {
              TabContent() {
                GoodsList({ ListIndex: $ListIndex, ratio: $ratio })
              }.tabBar('全部')

              TabContent() {
                GoodsList({ ListIndex: $ListIndex, ratio: $ratio })
              }.tabBar('直播')

              TabContent() {
                GoodsList({ ListIndex: $ListIndex, ratio: $ratio })
              }.tabBar('便宜好货')

              TabContent() {
                GoodsList({ ListIndex: $ListIndex, ratio: $ratio })
              }.tabBar('洋淘')
            }
            .barWidth(0)
            .barHeight(0)
            .height('93%')
            .scrollable(false)
          }
          .width('100%')
        }
      }
      .width('100%')
      .scrollBar(BarState.Off)
    }
  }
}
