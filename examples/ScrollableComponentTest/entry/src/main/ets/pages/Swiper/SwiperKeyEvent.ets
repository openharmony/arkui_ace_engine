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
 * 测试目的：验证Swiper组件在键盘操作中的走焦功能
 * 建议使用测试前阅读代码了解各个场景具体做了操作
 *
 * 说明：
 * 1、页面共10页，display count为4页，不使用组播。
 * 2、不设置prev/nextMargin。
 * 3、所有页面均可作为焦点。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击场景1按钮。
 * 3、使用hdc模拟键盘输入。
 *    uinput -K -d 2012 -u 2012     //up
 *    uinput -K -d 2013 -u 2013     //down
 *    uinput -K -d 2014 -u 2014     //left
 *    uinput -K -d 2015 -u 2015     //right
 *    uinput -K -d 2049 -u 2049     //tab
 * 4、点击tab激活焦点，激活后使用right翻页至最后，再使用left翻页至第一页，观察焦点状态。
 *
 * 预期结果：
 * 翻页过程中焦点锁定符合逻辑，翻页动画正常。
 */

/**
 * 2-场景2：
 * 设置部分页面不可被选中，翻页过程中焦点应跳过不可被选中页面。
 *
 * 说明：
 * 2-1：index为1、3、4、6的页面不可被选中。
 * 2-2：仅有index为0页面可选中。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击场景2-1按钮。
 * 3、使用hdc模拟键盘输入。
 * 4、点击tab激活焦点，激活后使用right翻页至最后，再使用left翻页至第一页，观察焦点状态。
 * 5、点击场景2-2按钮，重复上一步。
 *
 * 预期结果：
 * 2-1：翻页过程中焦点锁定符合逻辑，跳过不可被选中的页面，翻页动画正常。
 * 2-2：仅可翻页一次，翻页后会失焦。
 */

/**
 * 3-场景3：
 * 设置切换方式为组播，验证部分页面不可被选中情况下的走焦功能。
 *
 * 说明：
 * 3-1：使用组播，所有页面均可被选中。
 * 3-2：使用组播，index为1、3、4、6的页面不可被选中。
 * 3-3：使用组播，仅有index为0页面可选中。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击场景3-1按钮。
 * 3、使用hdc模拟键盘输入。
 * 4、点击tab激活焦点，激活后使用right翻页至最后，再使用left翻页至第一页，观察焦点状态。
 * 5、点击场景3-2按钮，重复上一步。
 * 5、点击场景3-3按钮，重复上一步。
 *
 * 预期结果：
 * 3-1：翻页过程中焦点锁定符合逻辑，翻页动画正常。
 * 3-2：翻页过程中焦点锁定符合逻辑，跳过不可被选中的页面，翻页动画正常。
 * 3-3：仅可翻页一次，翻页后会失焦。
 */

/**
 * 4-场景4：
 * 设置prevMargin，验证走焦功能。
 *
 * 说明：
 * 4-1：设置prevMargin(50,false)。
 * 4-2：设置prevMargin(50,true)。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击场景4-1按钮。
 * 3、使用hdc模拟键盘输入。
 * 4、点击tab激活焦点，激活后使用right翻页至最后，再使用left翻页至第一页，观察焦点状态。
 * 5、点击场景4-2按钮，重复上一步。
 *
 * 预期结果：
 * 4-1：翻页过程中焦点锁定符合逻辑，翻页动画正常。
 * 4-2：翻页过程中焦点锁定符合逻辑，翻页动画正常。
 */

/**
 * 5-场景5：
 * 设置nextMargin，验证走焦功能。
 *
 * 说明：
 * 5-1：设置nextMargin(50,false)。
 * 5-2：设置nextMargin(50,true)。
 *
 * 操作步骤：
 * 0-初始化页面
 * 1、打开demo页面。
 * 2、点击场景5-1按钮。
 * 3、使用hdc模拟键盘输入。
 * 4、点击tab激活焦点，激活后使用right翻页至最后，再使用left翻页至第一页，观察焦点状态。
 * 5、点击场景5-2按钮，重复上一步。
 *
 * 预期结果：
 * 5-1：翻页过程中焦点锁定符合逻辑，翻页动画正常。
 * 5-2：翻页过程中焦点锁定符合逻辑，翻页动画正常。
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

class MyDataSource2 implements IDataSource {
  private list: boolean[] = [];


  constructor(list: boolean[]) {
    this.list = list;
  }


  totalCount(): number {
    return this.list.length;
  }


  getData(index: number): boolean {
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
  UpdateFocus(): MyDataSource2 {
    switch(this.focusFlag){
      case 0:
        return this.focus1
      case 1:
        return this.focus2
      case 2:
        return this.focus3
      default:
        return this.focus1
    }
  }
  private swiperController: SwiperController = new SwiperController();
  private data: MyDataSource = new MyDataSource([]);
  private focus1: MyDataSource2 = new MyDataSource2([]);
  private focus2: MyDataSource2 = new MyDataSource2([]);
  private focus3: MyDataSource2 = new MyDataSource2([]);
  @State focusFlag: number = 0
  @State previousMargin: number = 0
  @State previousIgnoreBlank: boolean = false
  @State nextMargin: number = 0
  @State nextIgnoreBlank: boolean = false
  @State displayCount: number = 4
  @State groupDisplay: boolean = false
  @State loop: boolean = false
  @State autoplay: boolean = false


  aboutToAppear(): void {
    let list1: number[] = [];
    let list2: boolean[] = [];
    let list3: boolean[] = [];
    let list4: boolean[] = [];
    for (let i = 0; i < 10; i++) {
      list1.push(i);
      list2.push(true)
      if (i == 1 || i == 3 || i == 4 || i == 6) {
        list3.push(false)
      } else {
        list3.push(true)
      }
      if (i > 0) {
        list4.push(false)
      } else {
        list4.push(true)
      }
    }
    this.data = new MyDataSource(list1);
    this.focus1 = new MyDataSource2(list2)
    this.focus2 = new MyDataSource2(list3)
    this.focus3 = new MyDataSource2(list4)
  }


  build() {
    Column() {
      Swiper(this.swiperController) {
        LazyForEach(this.data, (item: string,index:number) => {
          Text(item.toString())
            .focusable(this.UpdateFocus().getData(index))
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
      .indicator(false)
      .displayCount(this.displayCount,this.groupDisplay)

      Row({ space: 12 }) {
        Button('场景1')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 0;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = false;
            this.loop = false;
            this.autoplay = false;
          })
        Button('场景2-1')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 1;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = false;
            this.loop = false;
            this.autoplay = false;
          })
        Button('场景2-2')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 2;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = false;
            this.loop = false;
            this.autoplay = false;
          })
      }.margin(5)
      Row({ space: 12 }) {
        Button('场景3-1')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 0;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = true;
            this.loop = false;
            this.autoplay = false;
          })
        Button('场景3-2')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 1;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = true;
            this.loop = false;
            this.autoplay = false;
          })
        Button('场景3-3')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 2;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
              this.groupDisplay = true;
            this.loop = false;
            this.autoplay = false;
          })
      }.margin(5)
      Row({ space: 12 }) {
        Button('场景4-1')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 0;
            this.previousMargin = 50;
            this.previousIgnoreBlank = false;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = false;
            this.loop = false;
            this.autoplay = false;
          })
        Button('场景4-2')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 0;
            this.previousMargin = 50;
            this.previousIgnoreBlank = true;
            this.nextMargin = 0;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = false;
            this.loop = false;
            this.autoplay = false;
          })
        Button('场景5-1')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 0;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 50;
            this.nextIgnoreBlank = false;
            this.displayCount = 4;
            this.groupDisplay = false;
            this.loop = false;
            this.autoplay = false;
          })
        Button('场景5-2')
          .onClick((event:ClickEvent) => {
            this.focusFlag = 0;
            this.previousMargin = 0;
            this.previousIgnoreBlank = false;
            this.nextMargin = 50;
            this.nextIgnoreBlank = true;
            this.displayCount = 4;
            this.groupDisplay = false;
            this.loop = false;
            this.autoplay = false;
          })
      }.margin(5)
    }
    .height('100%')
    .width('100%')
  }
}