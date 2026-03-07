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

@Builder
export function RatingLevel3Builder(name: string, param: Object) {
  RatingLevel3Example()
}

@Entry
@Component
struct RatingLevel3Example {
  pathStack: NavPathStack = new NavPathStack()
  @State rating: number = 3
  @State rating2: number = 4
  @State rating3: number = 2
  @State rating4: number = 5
  @State rating5: number = 1

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          Text('Rating 基础示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Text('默认评分')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Rating({ rating: this.rating })
            .onChange((value: number) => {
              this.rating = value
            })

          Text('自定义星级')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Rating({ rating: this.rating2 })
            .stepSize(0.5)
            .stars(5)
            .onChange((value: number) => {
              this.rating2 = value
            })

          Text('不同星级数量')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Rating({ rating: 3 })
              .stars(3)
            Rating({ rating: 4 })
              .stars(4)
            Rating({ rating: 5 })
              .stars(5)
          }

          Text('自定义星星样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Rating({ rating: this.rating3 })
            .starStyle({
              backgroundUri: '/common/star_grey.png',
              foregroundUri: '/common/star_yellow.png'
            })
            .onChange((value: number) => {
              this.rating3 = value
            })

          Text('不同尺寸')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Rating({ rating: 4 })
              .width(100)
            Rating({ rating: 3 })
              .width(150)
            Rating({ rating: 5 })
              .width(200)
          }

          Text('禁用状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Rating({ rating: 3 })
              .enabled(false)
            Rating({ rating: 5 })
              .enabled(false)
          }

          Text('带标签')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Row({ space: 10 }) {
              Rating({ rating: this.rating4 })
                .onChange((value: number) => {
                  this.rating4 = value
                })
              Text(`${this.rating4} 星`)
                .fontSize(16)
            }
            Row({ space: 10 }) {
              Rating({ rating: this.rating5 })
                .stepSize(0.5)
                .onChange((value: number) => {
                  this.rating5 = value
                })
              Text(`${this.rating5} 分`)
                .fontSize(16)
            }
          }

          Text('半星评分')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Rating({ rating: 3.5 })
            .stepSize(0.5)
            .starStyle({
              backgroundUri: '/common/star_grey.png',
              foregroundUri: '/common/star_yellow.png'
            })

          Text('垂直排列')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 15 }) {
            Row({ space: 10 }) {
              Text('服务态度:')
              Rating({ rating: 4 })
                .starStyle({
                  backgroundUri: '/common/star_grey.png',
                  foregroundUri: '/common/star_yellow.png'
                })
            }
            Row({ space: 10 }) {
              Text('产品质量:')
              Rating({ rating: 5 })
                .starStyle({
                  backgroundUri: '/common/star_grey.png',
                  foregroundUri: '/common/star_yellow.png'
                })
            }
            Row({ space: 10 }) {
              Text('物流速度:')
              Rating({ rating: 3 })
                .starStyle({
                  backgroundUri: '/common/star_grey.png',
                  foregroundUri: '/common/star_yellow.png'
                })
            }
          }

          Text('不同样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Rating({ rating: 4 })
              .starStyle({
                backgroundUri: '/common/star_grey.png',
                foregroundUri: '/common/star_red.png'
              })
            Rating({ rating: 3 })
              .starStyle({
                backgroundUri: '/common/star_grey.png',
                foregroundUri: '/common/star_green.png'
              })
            Rating({ rating: 5 })
              .starStyle({
                backgroundUri: '/common/star_grey.png',
                foregroundUri: '/common/star_blue.png'
              })
          }
        }
        .padding(20)
      }
    }
    .title('RatingLevel3')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
