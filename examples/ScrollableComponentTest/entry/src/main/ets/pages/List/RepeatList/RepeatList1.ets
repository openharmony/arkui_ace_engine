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

import { LengthMetrics } from '@kit.ArkUI';

@ObservedV2
class Repeat001Clazz {
  @Trace 
  public message: string = '';

  constructor(message: string) {
    this.message = message;
  }
}

@Entry
@ComponentV2
struct RepeatList1 {

  /*用例描述
   1、本用例测试了List下放置Repeat，而Repeat中真实数据源数量小于预期数据源数量的场景，关注的重点为List滑动到底部时的默认表现是否正常
   2、测试点包括了快速拖动滚动条到底部，scrollToIndex方法，IsAtEnd事件，底部边缘效果edgeEffect
  */
  /* 关键结构
   |-> List
    |-> Repeat
  */

  @Local simpleList: Array<Repeat001Clazz> = [];
  @Local selectOptions: SelectOption[] = [];
  @Local selectIdx: number = 0;
  private flag: boolean = false;
  private scroller: ListScroller = new ListScroller()
  @Local isSmooth: boolean = false;
  @Local align_: ScrollAlign = ScrollAlign.START;
  @Local extralOffset: number = 0;
  @Local repeatNum: number = 70;

  //向Repeat的数据源中添加数据，本用例初始化时真实数据源（50）小于预期数据源（70）
  aboutToAppear(): void {
    for(let i = 0; i < 50; i++) {
    this.simpleList.push(new Repeat001Clazz(`item_${i}`));
  }
}

build() {
  Column({ space: 10 }) {
    Text('virtualScroll each()&template() 1t')
      .fontSize(15)
      .fontColor(Color.Gray)

    Select(this.selectOptions)
      .selected(this.selectIdx)
      .value(this.selectIdx.toString())
      .key('selectIdx')
      .onSelect((index: number) => {
        this.selectIdx = index;
      })
    Row({ space: 5 }) {
      Button('Reduce virtualNum:' + this.repeatNum)
        .onClick(() => {
          this.repeatNum = 50;
        })
      Button('Add virtualNum:' + this.repeatNum)
        .onClick(() => {
          this.repeatNum = 70;
        })
      Button('isAtEnd')
        .onClick(() => {
          console.info('isAtEnd:' + this.scroller.isAtEnd())
        })
    }
    Row({ space: 5 }) {
      Button('对齐方式: ' + this.align_)
        .fontSize(10)
        .onClick(() => {
          if (this.align_ == ScrollAlign.START) {
            this.align_ = ScrollAlign.CENTER
          } else if (this.align_ == ScrollAlign.CENTER) {
            this.align_ = ScrollAlign.END
          } else if (this.align_ == ScrollAlign.END) {
            this.align_ = ScrollAlign.AUTO
          } else {
            this.align_ = ScrollAlign.START
          }
        })
      Button('动画：' + this.isSmooth.toString())
        .fontSize(10)
        .onClick(() => {
          this.isSmooth = !this.isSmooth
        })
      Button('extralOffset：' + this.extralOffset)
        .fontSize(10)
        .onClick(() => {
          this.extralOffset += -100
        })
      Button('ScrollTo')
        .fontSize(10)
        .onClick(() => {
          // 测试点：List执行ScrollToIndex跳转到大于真实数据长度位置时是否异常
          // 预期结果：不触发跳转，且不白屏
          this.scroller.scrollToIndex(
            60, this.isSmooth, this.align_, { extraOffset: LengthMetrics.px(this.extralOffset) })
        })
    }

    List({ space: 10, scroller: this.scroller }) {
      Repeat<Repeat001Clazz>(this.simpleList)
        .each((obj: RepeatItem<Repeat001Clazz>) => {
          ListItem() {
            Text(`[each] index${obj.index}: ${obj.item.message}`)
              .fontSize(25)
          }
            .backgroundColor(Color.Red)
        })
        .key((item: Repeat001Clazz, index: number) => {
          return item.message;
        })
        // 设置Repeat的预期数据数量
        .virtualScroll({ totalCount: this.repeatNum })
        .templateId(() => 'a')
        .template('a', (ri) => {
          Text(`[a] index${ri.index}: ${ri.item.message}`)
            .fontSize(25)
        }, { cachedCount: 3 })
    }
      // 测试点：开启框选，测试该场景下List的鼠标框选功能是否正常
      .multiSelectable(true)
      // 测试点：测试该场景下onScrollIndex的参数值是否正确
      .onScrollIndex((start: number, end: number, center: number) => {
        console.log('RepeatList1 ------------- onScrollIndex start: ' + start + ' end: ' + end + ' center: ' + center)
        // 测试点：在向下滑动的过程中模拟新增数据的效果，验证该过程效果是否正常（测试其他测试点时需注释下方if逻辑）
        if (end >= 39 && !this.flag) {
          this.flag = true;
          console.log('RepeatList1 -------------  add index to 70')
          for (let i = 50; i < 70; i++) {
            this.simpleList.push(new Repeat001Clazz(`item_${i}`));
          }
        }
      })
      // 测试点：List滑动到底部时OnReachEnd事件是否触发
      // 预期结果：不触发List的OnReachEnd事件
      .onReachEnd(() => {
        console.log('RepeatList1 ------------- onReachEnd')
      })
      // 测试点：List滑动到底部时边缘效果是否触发
      // 预期结果：不触发List的底部边缘效果
      .edgeEffect(EdgeEffect.Spring)
      .cachedCount(2)
      .border({ width: 1 })
      .width('95%')
      .height('40%')
  }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
}
}