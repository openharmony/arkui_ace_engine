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
 * 测试目的：验证Swiper、Indicator、controller之间的两两连接状态，其中showPrevious和showNext按键代表controller
 * 建议使用测试前阅读代码了解各个场景具体做了操作
 *
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 3、滑动Swiper，点击和长按拖动Indicator。
 * 
 * 说明：
 * 1、Swiper1和导航点1绑定，受controller1控制。
 * 2、Swiper2和导航点2绑定，受controller2控制。
 * 
 * 连接状态描述：
 * Swiper1 -- controller1 -- Indicator1
 * Swiper2 -- controller2 -- Indicator2
 */

/**
 * 1-场景1：
 * Indicator1和Swiper1绑定，受controller2控制。
 * Indicator2和Swiper2绑定，受controller1控制。
 *
 * 连接状态描述：
 * 此场景实际进行了两步：
 * 第一步：
 * Swiper2 -- controller1 -- Indicator1
 * Swiper1 -- controller2 -- Indicator2
 * 第二步：
 * Swiper2 -- controller1 -- Indicator2
 * Swiper1 -- controller2 -- Indicator1
 *
 * 此场景等同于场景4+场景5，如若此场景不通过，可尝试用5+4调换顺序来判断是Indicator问题还是Swiper问题。
 *
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景1按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 4、滑动Swiper，点击和长按拖动Indicator。
 * 
 * 预期结果：
 * Indicator1和Swiper1绑定，受controller2控制。
 * Indicator2和Swiper2绑定，受controller1控制。
 */

/**
 * 2-场景2：
 * Indicator2不变，切换Indicator1。变化后应只有indicator1生效，两个分支场景只是控制它的controller不同。
 * 
 * 连接状态描述：
 * 场景2-1：
 * Swiper1 -- controller1 -- null
 * Swiper2 -- controller2 -- Indicator1 （此时indicator2的连接被顶掉了）
 * 场景2-2：
 * Swiper1 -- controller1 -- Indicator1
 * Swiper2 -- controller2 -- null 
 *
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景2-1按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 4、滑动Swiper，点击和长按拖动Indicator。
 * 5、点击场景2-2按钮，重复以上两步。
 * 
 * 场景2-1：
 * 1、Indicator1受controller2控制。
 * 2、Indicator2不再受controller2控制。
 * 3、Swiper2不再受Indicator2控制，Swiper2变化时Indicator2无动画。
 * 
 * 场景2-2：
 * 1、Indicator1受controller1控制。
 * 2、Indicator2不再受controller2控制。
 * 3、Swiper2不再受Indicator2控制，Swiper2变化时Indicator2无动画。
 */

/**
 * 3-场景3：
 * Swiper2不变，切换Swiper1。变化后应只有Swiper1生效，两个分支场景下控制它的controller和Indicator都不同。
 *
 * 连接状态描述：
 * 场景3-1：
 * null -- controller1 -- Indicator1
 * Swiper1 -- controller2 -- Indicator2 （此时Swiper2的连接被顶掉了）
 * 场景3-2：
 * Swiper1 -- controller1 -- Indicator1
 * null -- controller2 -- Indicator2 
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景3-1按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 4、滑动Swiper，点击和长按拖动Indicator。
 * 5、点击场景3-2按钮，重复以上两步。
 * 
 * 场景3-1：
 * 1、Swiper1受controller2和Indicator2控制,Swiper1和Indicator1解绑。
 * 2、Swiper2不再受controller2和Indicator2控制。
 * 
 * 场景3-2：
 * 1、Swiper1受controller1和Indicator1控制，Swiper1和Indicator1重新绑定。
 * 2、Swiper2和Indicator2解绑；Swiper2不再受controller2和Indicator2控制。
 */

/**
 * 4-场景4：
 * Indicator不变，Swiper1和Swiper2绑定的controller互换。
 * 
 * 连接状态描述：
 * Swiper2 -- controller1 -- Indicator1
 * Swiper1 -- controller2 -- Indicator2
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景4按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 4、滑动Swiper，点击和长按拖动Indicator。
 * 
 * 预期结果：
 * Swiper1和Indicator2绑定，受controller2控制。
 * Swiper2和Indicator1绑定，受controller1控制。
 */

/**
 * 5-场景5：
 * Swiper不变，Indicator1和Indicator2绑定的controller互换。
 * 
 * 连接状态描述：
 * Swiper1 -- controller1 -- Indicator2
 * Swiper2 -- controller2 -- Indicator1
 *
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景5按钮。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 4、滑动Swiper，点击和长按拖动Indicator。
 * 
 * 预期结果：
 * Swiper1和Indicator2绑定，受controller1控制。
 * Swiper2和Indicator1绑定，受controller2控制。
 */

/**
 * 6-场景6：
 * 数字导航点切换
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景6-1按钮 切换导航点样式。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 2、点击场景6-2按钮 切换导航点样式。
 * 
 * 说明：
 * 1、场景6-1，导航点1更新。
 * 2、场景6-2，导航点2更新。
 * 原则：相同controller控制不同导航点时，以最后一次更新的为准。
 */

/**
 * 7-场景7：
 * "内置" 和 "绑定"，进行切换
 *
 * 点击场景7按钮，导航点样式会按照以下顺序依次变化：
 * 1、使用内置导航点，与原先导航点脱离绑定
 * 2、与Indicator1绑定
 * 3、与Indicator2绑定
 * 4、使用内置导航点，与原先导航点脱离绑定
 * 5、无导航点
 * 6、内置导航点，且导航点为数字样式导航点
 * 
 * 操作步骤：
 * 1、打开demo页面。
 * 2、点击场景7按钮 切换导航点样式。
 * 3、点击showNext1,showPrevious1,showNext2,showPrevious2。
 * 
 * 预期结果：
 * 导航点类型正确切换，丢失绑定的时候单独导航点状态刷新。
 */


class MyDataSource1 implements IDataSource {
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
struct Index111 {

  UpdateIndicaotr(): IndicatorComponentController | DotIndicator | DigitIndicator | boolean {
    switch (this.swiper2_controller) {
      case 0:
        return new DotIndicator();
      case 1:
        return this.indicatorController1;
      case 2:
        return this.indicatorController2;
      case 3:
        return true;
      case 4:
        return false;
      case 5:
        return new DigitIndicator();
      default:
        return false;
    }
  }
  @State count: number = 5;
  private indicatorController1: IndicatorComponentController = new IndicatorComponentController()
  private indicatorController2: IndicatorComponentController = new IndicatorComponentController()
  private data: MyDataSource1 = new MyDataSource1([])
  @State isDigIndicator1: boolean = false;
  @State isDigIndicator2: boolean = false;
  private swiperController1: SwiperController = new SwiperController()
  private swiperController2: SwiperController = new SwiperController()
  @State swiper1_controller: number = 1
  @State swiper2_controller: number = 2
  @State indicator1_controller: number = 1
  @State indicator2_controller: number = 2

  aboutToAppear(): void {
    let list: number[] = []
    for (let i = 0; i < 9; i++) {
      list.push(i);
    }
    this.data = new MyDataSource1(list)
  }

  build() {
    Column() {
      Row() {
        Button('showNext1')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController1.showNext()

          })
        Button('showPrevious1')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController1.showPrevious()
          })
        Button('showNext2')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController2.showNext()

          })
        Button('showPrevious2')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicatorController2.showPrevious()
          })
      }

      Swiper(this.swiperController1) {
        LazyForEach(this.data, (item: string) => {
          Text(item.toString())
            .width('90%')
            .height(160)
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }, (item: string) => item)
      }
      .margin(10)
      .loop(false)
      .indicator(this.swiper1_controller == 1 ? this.indicatorController1 : this.indicatorController2)
      .vertical(false)

      Swiper(this.swiperController2) {
        LazyForEach(this.data, (item: string) => {
          Text(item.toString())
            .width('90%')
            .height(160)
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }, (item: string) => item)
      }
      .margin(10)
      .loop(false)
      .indicator(this.UpdateIndicaotr())
      .vertical(false)

      IndicatorComponent(this.indicator1_controller == 1 ? this.indicatorController1 : this.indicatorController2)
        .style(this.isDigIndicator1 ? new DigitIndicator() :
          new DotIndicator()
        )
        .loop(false)
        .count(this.count)
        .vertical(false)

      IndicatorComponent(this.indicator2_controller == 1 ? this.indicatorController1 : this.indicatorController2)
        .style(this.isDigIndicator2 ? new DigitIndicator() :
          new DotIndicator()
        )
        .loop(false)
        .count(this.count)
        .vertical(false)
      Row() {
        Button('场景1')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 2;
            this.swiper2_controller = 1;
            this.indicator1_controller = 2;
            this.indicator2_controller = 1;
          })
        Button('场景2-1')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicator1_controller = 2;
          })
        Button('场景2-2')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicator1_controller = 1;
          })
        Button('场景3-1')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 2;
          })
        Button('场景3-2')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 1;
          })
      }

      Row() {
        Button('场景4')
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper1_controller = 2;
            this.swiper2_controller = 1;
          })
        Button('场景5')
          .margin({ top: 5 })
          .onClick(() => {
            this.indicator1_controller = 2;
            this.indicator2_controller = 1;
          })
        Button('场景6 - 1')
          .margin({ top: 5 })
          .onClick(() => {
            this.isDigIndicator1 = !this.isDigIndicator1;
          })
        Button('场景6 - 2')
          .margin({ top: 5 })
          .onClick(() => {
            this.isDigIndicator2 = !this.isDigIndicator2;
          })
      }
      Row(){
        Button('场景7 swiper2_controller = ' + this.swiper2_controller)
          .margin({ top: 5 })
          .onClick(() => {
            this.swiper2_controller = (this.swiper2_controller + 1) % 6;
          })
      }
    }
    .width('100%')
  }
}