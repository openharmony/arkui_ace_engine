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
 * 测试目的：验证Swiper组件的onContentWillScroll回调功能在基础场景下的拦截机制和各种配置属性的影响
 * 建议测试前阅读代码了解各个场景具体操作和预期结果
 *
 * 0-初始化页面
 * 1、打开demo页面，页面包含：
 *    - 上方：单个Swiper组件（粉色背景，带导航箭头）
 *    - 下方：丰富的控制面板，包含实时显示区域和各种配置选项
 * 2、观察初始状态：
 *    - Swiper默认显示页面0，包含5个页面（'0', '1', '2', '3', '4'）
 *    - 拦截条件：currentIndex = 0, comingIndex = 0
 *    - 实时显示：willScrollCurrentIndex = 0, comingIndex = 0, offset = 0
 *    - 配置：loop = true, displayCount = 1, width = 300, height = 30%
 * 
 * 说明：
 * 1、Swiper为水平方向滚动，支持循环、多页显示等多种模式
 * 2、onContentWillScroll拦截逻辑：当 info.currentIndex == this.currentIndex && info.comingIndex == this.comingIndex
 *     时返回false阻止滚动
 * 3、页面提供了完整的Swiper配置控制，可以动态测试各种参数组合
 */

/**
 * 1-场景1：基础拦截功能测试
 * 验证onContentWillScroll回调的基本拦截能力
 *
 * 操作步骤：
 * 1、保持默认拦截条件：currentIndex = 0, comingIndex = 0
 * 2、在Swiper中从页面0向右滑动到页面1（应该正常）
 * 3、设置拦截条件：currentIndex = 0, comingIndex = 1
 * 4、再次从页面0向右滑动到页面1
 * 5、观察实时显示数据变化
 * 
 * 预期结果：
 * 1、默认条件下（0→0）不会拦截实际的滑动操作
 * 2、设置0→1拦截后，该方向的切换被阻止
 * 3、其他方向的切换（如0→4循环）正常执行
 * 4、实时显示正确反映滑动过程中的参数变化
 */

/**
 * 2-场景2：控制器操作拦截测试
 * 验证通过SwiperController调用时的拦截功能
 *
 * 操作步骤：
 * 1、设置拦截条件：currentIndex = 1, comingIndex = 2
 * 2、使用changeIndex按钮切换到页面1
 * 3、点击"showNext"按钮，尝试切换到页面2
 * 4、点击"showPrevious"按钮，尝试切换到页面0
 * 5、使用"changeIndex(2, true/false)"按钮直接切换到页面2
 * 
 * 预期结果：
 * 1、showNext操作正常执行
 * 2、showPrevious操作正常执行
 * 3、changeIndex操作正常执行
 */

/**
 * 3-场景3：循环模式拦截测试
 * 验证loop模式下的边界拦截功能
 *
 * 操作步骤：
 * 1、确保loop = true
 * 2、设置拦截条件：currentIndex = 4, comingIndex = 0（拦截末页到首页的循环）
 * 3、滑动到页面4
 * 4、向右滑动，尝试循环到页面0
 * 5、设置拦截条件：currentIndex = 0, comingIndex = 4（拦截首页到末页的循环）
 * 6、在页面0向左滑动，尝试循环到页面4
 * 
 * 预期结果：
 * 1、末页→首页的循环切换被拦截
 * 2、首页→末页的循环切换被拦截
 * 3、非循环方向的切换正常执行
 */

/**
 * 4-场景4：多页显示模式拦截测试
 * 验证displayCount > 1时的拦截功能
 *
 * 操作步骤：
 * 1、点击"displayCount++"设置为2
 * 2、点击"change swipeByGroup"测试分组滑动
 * 3、设置拦截条件：currentIndex = 0, comingIndex = 2
 * 4、观察分组滑动和单页滑动的区别
 * 
 * 预期结果：
 * 1、多页显示模式下拦截功能正常工作
 * 2、swipeByGroup模式影响切换行为但不影响拦截逻辑
 * 3、页面索引正确对应实际显示的页面
 */

@Entry
@Component
struct OnContentWillScrollNormal {
  private swiperController: SwiperController = new SwiperController()
  @State data: number[] = [0, 1, 2, 3, 4]
  @State idx: number = 0
  @State willScrollCurrentIndex: number = 0
  @State willScrollComingIndex: number = 0
  @State willScrollOffset: number = 0
  @State changeIndex: number = 0
  @State currentIndex: number = 0
  @State comingIndex: number = 0
  @State swiperWidth: Length = 300
  @State swiperHeight: Length = '30%'
  @State preMargin: number = 0
  @State nextMargin: number = 0
  @State itemSpace: number = 0
  @State swiperClip: boolean = true
  @State cachedCount: number = 1
  @State displayCount: number = 1
  @State loop: boolean = true
  @State swipeByGroup: boolean = false
  @State prevIgnoreBlank: boolean = false
  @State nextIgnoreBlank: boolean = false
  @State direct: Direction = Direction.Ltr

  build() {
    Column({ space: 5 }) {
      Swiper(this.swiperController) {
        ForEach(this.data, (item: string) => {
          OnContentWillScrollComponent({ txt: item.toString() })
        }, (item: string) => item)
      }
      .borderWidth(1)
      .backgroundColor(Color.Pink)
      .index(this.idx)
      .loop(this.loop)
      .width(this.swiperWidth)
      .height(this.swiperHeight)
      .prevMargin(this.preMargin, this.prevIgnoreBlank)
      .nextMargin(this.nextMargin, this.nextIgnoreBlank)
      .itemSpace(this.itemSpace)
      .displayCount(this.displayCount, this.swipeByGroup)
      .direction(this.direct)
      .displayArrow({
        // 设置导航点箭头样式
        showBackground: true,
        isSidebarMiddle: true,
        backgroundSize: 24,
        backgroundColor: Color.White,
        arrowSize: 18,
        arrowColor: Color.Blue
      }, false)
      .onContentWillScroll((result: SwiperContentWillScrollResult) => {
        this.willScrollCurrentIndex = result.currentIndex
        this.willScrollComingIndex = result.comingIndex
        this.willScrollOffset = result.offset

        if (result.currentIndex == this.currentIndex && result.comingIndex == this.comingIndex) {
          return false;
        }

        return true
      })

      Scroll() {
        Column({ space: 12 }) {
          Text('will scroll currentIndex: ' + this.willScrollCurrentIndex + ', comingIndex: ' +
          this.willScrollComingIndex + ', offset: ' + this.willScrollOffset)
            .margin(5)

          Button('change loop')
            .onClick(() => {
              this.loop = !this.loop
            })
            .margin(5)
            .fontSize(15)

          Button('total count = 10')
            .onClick(() => {
              this.data = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            })
            .margin(5)
            .fontSize(15)

          Button('total count = 5')
            .onClick(() => {
              this.data = [0, 1, 2, 3, 4]
            })
            .margin(5)
            .fontSize(15)

          Text('width: ' + this.swiperWidth.toString())
            .margin(5)
          Row() {
            Button('width = 300')
              .onClick(() => {
                this.swiperWidth = 300
              })
              .margin(5)
              .fontSize(15)

            Button('width = 90%')
              .onClick(() => {
                this.swiperWidth = '90%'
              })
              .margin(5)
              .fontSize(15)
          }

          Text('index: ' + this.idx)
            .margin(5)
          Row() {
            Button('index=1')
              .onClick(() => {
                this.idx = 1
              })
              .margin(5)
              .fontSize(15)

            Button('index++')
              .onClick(() => {
                this.idx++
              })
              .margin(5)
              .fontSize(15)

            Button('index--')
              .onClick(() => {
                this.idx--
              })
              .margin(5)
              .fontSize(15)
          }

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

          Text('itemSpace: ' + this.itemSpace + 'prevMargin: ' + this.preMargin + ', nextMargin: ' + this.nextMargin +
            ', prevIgnoreBlank: ' +
            (this.prevIgnoreBlank ? 'true' : 'false') + ', nextIgnoreBlank: ' +
            (this.nextIgnoreBlank ? 'true' : 'false'))
          Row() {
            Button('change prevIgnoreBlank')
              .onClick(() => {
                this.prevIgnoreBlank = !this.prevIgnoreBlank
              })
              .margin(5)
              .fontSize(15)

            Button('change nextIgnoreBlank')
              .onClick(() => {
                this.nextIgnoreBlank = !this.nextIgnoreBlank
              })
              .margin(5)
              .fontSize(15)

          }

          Row() {
            Button('prevMargin++')
              .onClick(() => {
                this.preMargin += 10
              })
              .margin(5)
              .fontSize(12)

            Button('nextMargin++')
              .onClick(() => {
                this.nextMargin += 10
              })
              .margin(5)
              .fontSize(12)

            Button('itemSpace++')
              .onClick(() => {
                this.itemSpace += 10
              })
              .margin(5)
              .fontSize(12)
          }

          Row() {
            Button('prevMargin--')
              .onClick(() => {
                this.preMargin -= 10
              })
              .margin(5)
              .fontSize(12)

            Button('nextMargin--')
              .onClick(() => {
                this.nextMargin -= 10
              })
              .margin(5)
              .fontSize(12)

            Button('itemSpace--')
              .onClick(() => {
                this.itemSpace -= 10
              })
              .margin(5)
              .fontSize(12)
          }


          Text('change index: ' + this.changeIndex)
            .margin(5)
          Row() {

            Button('changeIndex++')
              .onClick(() => {
                this.changeIndex++
              })
              .margin(5)
              .fontSize(15)

            Button('changeIndex--')
              .onClick(() => {
                this.changeIndex--
              })
              .margin(5)
              .fontSize(15)
          }


          Row() {
            Button('showNext')
              .onClick(() => {
                this.swiperController.showNext()
              })
              .margin(5)
              .fontSize(15)
            Button('showPrevious')
              .onClick(() => {
                this.swiperController.showPrevious()
              })
              .fontSize(15)
              .margin(5)
          }.margin(5)

          Row() {
            Button('changeIndex(' + this.changeIndex + ', false)')
              .onClick(() => {
                this.swiperController.changeIndex(this.changeIndex, false)
              })
              .fontSize(15)
              .margin(5)

            Button('changeIndex(' + this.changeIndex + ', true)')
              .onClick(() => {
                this.swiperController.changeIndex(this.changeIndex, true)
              })
              .fontSize(15)
              .margin(5)
          }

          Text('displayCount:' + this.displayCount + ', swipeByGroup:' + this.swipeByGroup)
          Button('change swipeByGroup')
            .onClick(() => {
              this.swipeByGroup = !this.swipeByGroup
            })
            .margin(5)
            .fontSize(15)
          Row() {
            Button('displayCount++')
              .onClick(() => {
                this.displayCount++
              })
              .margin(5)
              .fontSize(15)

            Button('displayCount--')
              .onClick(() => {
                this.displayCount--
              })
              .margin(5)
              .fontSize(15)
          }

          Row() {
            Button('RTL')
              .onClick(() => {
                this.direct = Direction.Rtl
              })
              .margin(5)
              .fontSize(15)

            Button('LTR')
              .onClick(() => {
                this.direct = Direction.Ltr
              })
              .margin(5)
              .fontSize(15)
          }

        }.margin(5)
      }
      .height('60%')
    }
    .width('100%')
    .margin({ top: 5 })
  }
}

@Component
struct OnContentWillScrollComponent {
  txt: string = ''

  aboutToAppear(): void {
    console.info('aboutToAppear index:' + this.txt)
  }

  aboutToDisappear(): void {
    console.info('aboutToDisappear index:' + this.txt)
  }

  build() {
    Column() {
      Text(this.txt)
        .width('100%')
        .height('100%')
        .textAlign(TextAlign.Center)
        .fontSize(15)
        .backgroundColor(0xAFEEEE)
        .borderWidth(1)
    }
    .width(100)
    .height(200)
  }
}
