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

/**
 * 测试目的：验证Swiper嵌套List组件时的onContentWillScroll回调功能和滚动拦截机制
 * 建议测试前阅读代码了解各个场景具体操作和预期结果
 *
 * 0-初始化页面
 * 1、打开demo页面，页面包含：
 *    - 上方：垂直Swiper组件，每页包含一个List容器
 *    - 下方：实时显示区域和拦截条件控制按钮
 * 2、观察初始状态：
 *    - Swiper默认显示页面0
 *    - 每个List页面包含14个ListItem（0-13）
 *    - 拦截条件：currentIndex = 0, comingIndex = 0
 *    - 实时显示：willScrollCurrentIndex = 0, comingIndex = 0, offset = 0
 * 
 * 说明：
 * 1、Swiper包含5个页面（通过LazyForEach动态生成），垂直方向滚动
 * 2、每个Swiper页面包含一个List组件，List中有14个ListItem
 * 3、List嵌套滚动模式：NestedScrollMode.SELF_FIRST（List优先处理滚动）
 * 4、onContentWillScroll拦截逻辑：当 info.currentIndex == this.currentIndex && info.comingIndex == this.comingIndex
 *     时返回false阻止滚动
 */

 /**
 * 1-场景1：基础拦截功能测试
 * 验证onContentWillScroll回调能够正确拦截特定页面切换
 *
 * 操作步骤：
 * 1、设置拦截条件：保持默认 currentIndex = 0, comingIndex = 0
 * 2、在任意Swiper中尝试从页面0滑动到页面0（无实际滑动）
 * 3、在任意Swiper中从页面1滑动到页面0
 * 4、观察实时显示数据变化
 * 
 * 预期结果：
 * 1、页面0到页面0的切换被拦截（实际无意义，但验证回调触发）
 * 2、其他页面切换正常执行
 * 3、实时显示正确反映滑动过程中的参数变化
 */

/**
 * 2-场景2：从页面1到页面2的拦截测试
 * 验证拦截正常页面切换的功能
 *
 * 操作步骤：
 * 1、重置拦截条件：currentIndex = 1, comingIndex = 2
 * 2、在Swiper中滑动到页面1
 * 3、从页面1向下滑动，尝试切换到页面2
 * 4、观察Swiper是否被阻止切换
 * 5、尝试从页面1向上滑动到页面0（应该正常）
 * 
 * 预期结果：
 * 1、页面1→2的切换被拦截，Swiper停留在页面1
 * 2、页面1→0的切换正常执行
 * 3、实时显示中可以看到willScrollComingIndex在滑动过程中变为2，但切换被阻止
 */

/**
 * 3-场景3：从页面1到页面2的拦截测试
 * 验证拦截正常页面切换的功能
 *
 * 操作步骤：
 * 1、重置拦截条件：currentIndex = 2, comingIndex = 1
 * 2、在Swiper中滑动到页面2
 * 3、从页面1向下滑动，尝试切换到页面1
 * 4、观察Swiper是否被阻止切换
 * 5、尝试从页面1向上滑动到页面2（应该正常）
 * 
 * 预期结果：
 * 1、页面2→1的切换被拦截，Swiper停留在页面2
 * 2、页面1→2的切换正常执行
 * 3、实时显示中可以看到willScrollComingIndex在滑动过程中变为2，但切换被阻止
 */

class SwiperNestListMyDataSource implements IDataSource {
  private list: number[] = []

  constructor(list: number[]) {
    this.list = list
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): number {
    return this.list[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct OnContentWillScrollNestList {
  private swiperController: SwiperController = new SwiperController()
  private data: SwiperNestListMyDataSource = new SwiperNestListMyDataSource([])
  @State text: number = 0
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
  @State currentIndex: number = 0
  @State comingIndex: number = 0
  @State swiperWidth: Length = 300
  @State swiperHeight: Length = '30%'
  @State willScrollCurrentIndex: number = 0
  @State willScrollComingIndex: number = 0
  @State willScrollOffset: number = 0

  aboutToAppear(): void {
    let list: number[] = []
    for (let i = 0; i <= 4; i++) {
      list.push(i);
    }
    this.data = new SwiperNestListMyDataSource(list)
  }

  build() {
    Column({ space: 5 }) {
      Swiper(this.swiperController) {
        LazyForEach(this.data, (item: string) => {
          List({ space: 5, initialIndex: 0 }) {
            ForEach(this.arr, (item: number) => {
              ListItem() {
                Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                  Text('' + item)
                    .width('100%')
                    .height(20)
                    .fontSize(16)
                    .textAlign(TextAlign.Center)
                    .borderRadius(10)
                    .backgroundColor(0xFFFFFF)
                }

              }
            }, (item: string) => item)
          }
          .borderWidth(1)
          .nestedScroll({ scrollForward: NestedScrollMode.SELF_FIRST, scrollBackward: NestedScrollMode.SELF_FIRST })
          .edgeEffect(EdgeEffect.None)
          .width('30%')
          .height('30%')
          .alignRules({
            bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
            left: { anchor: '__container__', align: HorizontalAlign.Start }
          })

        }, (item: string) => item)

      }
      .backgroundColor(Color.Pink)
      .vertical(true)
      .width(this.swiperWidth)
      .height(this.swiperHeight)
      .onContentWillScroll((info: SwiperContentWillScrollResult) => {
        this.willScrollCurrentIndex = info.currentIndex
        this.willScrollComingIndex = info.comingIndex
        this.willScrollOffset = info.offset

        if (info.currentIndex == this.currentIndex && info.comingIndex == this.comingIndex) {
          return false;
        }

        return true
      })

      Scroll() {
        Column({ space: 12 }) {
          Text('will scroll currentIndex: ' + this.willScrollCurrentIndex + ', comingIndex: ' +
          this.willScrollComingIndex + ', offset: ' + this.willScrollOffset)
            .margin(5)

          Text('拦截条件: ' + this.currentIndex + ' 到 ' + this.comingIndex)
            .margin(5)

          Row() {
            Button('currentIndex++')
              .onClick(() => {
                this.currentIndex++
              })
              .margin(5)
              .fontSize(15)

            Button('currentIndex--')
              .onClick(() => {
                this.currentIndex--
              })
              .margin(5)
              .fontSize(15)
          }

          Row() {
            Button('comingIndex++')
              .onClick(() => {
                this.comingIndex++
              })
              .margin(5)
              .fontSize(15)

            Button('comingIndex--')
              .onClick(() => {
                this.comingIndex--
              })
              .margin(5)
              .fontSize(15)
          }
        }.margin(5)
      }
      .height('60%')
    }
  }
}

