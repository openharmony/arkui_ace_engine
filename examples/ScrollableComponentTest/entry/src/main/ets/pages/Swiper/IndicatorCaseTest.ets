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
 * 测试目的：测试indicator不同样式的交互场景
 * 建议使用测试前阅读代码了解各个场景具体做了操作
 *
 * 说明：
 * 1、页面共10页，display count为3页，不使用组播。
 * 2、不设置prev/nextMargin。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击第一排各个导航点样式按钮。
 * 3、检查各个导航点UI，以及自动播放动画。
 *
 * 预期结果：
 * 各个导航点UI样式正常，翻页动画正常。
 */

/**
 * 2-交互测试：
 * 针对点状导航点（默认导航点）的交互场景进行测试。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击点状导航点（默认导航点）按钮。
 * 3、触屏点击导航点区域左右两侧，检查点击翻页情况。
 * 4、触屏长按导航点，检查长按拖拽翻页情况。
 * 5、使用鼠标点击导航点，检查跳转情况。
 *
 * 预期结果：
 * 触屏点击可以正常翻页，不设置循环的场景下会在边界停下。
 * 长按进入悬停状态后将暂停自动播放功能，拖拽可正常翻页。
 * 鼠标悬停不会暂停自动播放，可以正常跳页。
 */

/**
 * 3-循环场景：
 * 设置loop为true，测试默认导航点的交互情况。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击点状导航点（默认导航点）按钮。
 * 3、触屏点击导航点区域左右两侧，检查点击翻页情况。
 * 4、触屏长按导航点，检查长按拖拽翻页情况。
 * 5、使用鼠标点击导航点，检查跳转情况。
 *
 * 预期结果：
 * 触屏点击可以正常翻页，不会在边界停下，可以翻到下一页。
 * 长按进入悬停状态后将暂停自动播放功能，拖拽可正常翻页。
 * 鼠标悬停不会暂停自动播放，可以正常跳页。
 */

/**
 * 4-组播场景：
 * 设置组播，测试默认导航点的交互情况。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击点状导航点（默认导航点）按钮。
 * 3、触屏点击导航点区域左右两侧，检查点击翻页情况。
 * 4、触屏长按导航点，检查长按拖拽翻页情况。
 * 5、使用鼠标点击导航点，检查跳转情况。
 *
 * 预期结果：
 * 触屏点击可以正常翻页，不会在边界停下，可以翻到下一页。
 * 长按进入悬停状态后将暂停自动播放功能，拖拽可正常翻页。
 * 鼠标悬停不会暂停自动播放，可以正常跳页。
 */
class MyDataSource implements IDataSource {
  private list: number[] = [];


  constructor(list: number[]) {
    this.list = list;
  }


  totalCount(): number {
    return this.list.length;
  }


  getData(index: number): number {
    return this.list[index];
  }


  registerDataChangeListener(listener: DataChangeListener): void {
  }


  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct Index {
  UpdateIndicator(): DotIndicator | DigitIndicator | boolean {
    switch(this.indicatorController){
      case 0:
        return true;
      case 1:
        return new DotIndicator();
      case 2:
        return new DigitIndicator();
      case 3:
        return false;
      default:
        return true;
    }
  }

  private swiperController: SwiperController = new SwiperController();
  private data: MyDataSource = new MyDataSource([]);
  @State previousMargin: number = 0
  @State previousIgnoreBlank: boolean = false
  @State nextMargin: number = 0
  @State nextIgnoreBlank: boolean = false
  @State displayCount: number = 3
  @State groupDisplay: boolean = false
  @State loop: boolean = false
  @State autoplay: boolean = true
  @State indicatorController: number = 0


  aboutToAppear(): void {
    let list: number[] = [];
    for (let i = 0; i < 10; i++) {
      list.push(i);
    }
    this.data = new MyDataSource(list);
  }


  build() {
    Column() {
      Swiper(this.swiperController) {
        LazyForEach(this.data, (item: string,index:number) => {
          Text(item.toString())
            .tabIndex(index)
            .width('90%')
            .height(500)
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }, (item: string) => item)
      }
      .loop(this.loop)
      .autoPlay(this.autoplay)
      .nextMargin(this.nextMargin,this.nextIgnoreBlank)
      .prevMargin(this.previousMargin,this.previousIgnoreBlank)
      .indicator(this.UpdateIndicator())
      .displayCount(this.displayCount,this.groupDisplay)

      Row({ space: 12 }) {
        Button('默认导航点')
          .onClick((event:ClickEvent) => {
            this.indicatorController = 0;
          })
        Button('点状导航点')
          .onClick((event:ClickEvent) => {
            this.indicatorController = 1;
          })
        Button('数字导航点')
          .onClick((event:ClickEvent) => {
            this.indicatorController = 2;
          })
        Button('无导航点')
          .onClick((event:ClickEvent) => {
            this.indicatorController = 3;
          })
      }.margin(5)
      Row({ space: 12 }) {
        Button('循环场景')
          .onClick((event:ClickEvent) => {
            this.loop = true;
            this.indicatorController = 0;
          })
        Button('组播场景')
          .onClick((event:ClickEvent) => {
            this.groupDisplay = true;
            this.indicatorController = 0;
          })
      }.margin(5)
    }
    .height('100%')
    .width('100%')
  }
}