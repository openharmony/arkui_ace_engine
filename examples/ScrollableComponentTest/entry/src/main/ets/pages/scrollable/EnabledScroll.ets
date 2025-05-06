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

import { promptAction } from '@kit.ArkUI'

@Entry
@Component
struct EnabledScroll {

  /*用例描述
   1、在外层Scroll上启用了手势的Enabled属性，在滑动过程中，如果Enable属性被设置为false，会导致手势不会给滚动组件传递DragEnd事件，
    使得滚动组件没有时机去执行离手逻辑（重置自身的滚动状态）。
   2、由于滚动组件错误的认为自身还处于滚动状态，因此后续的第一次点击事件会被滚动组件消费以结束自身的滚动状态。
   3、后续通过适配手势的PanEnd回调（Enable属性为false会给滚动组件触发一次）修复了上述的问题，本测试用例即对该适配功能进行看护。
  */
  /* 关键结构
   |-> Scroll (添加手势识别器)
    |-> Scroll (内部绑定点击事件)
  */
  /*测试步骤
   1、滑动内部Scroll到底部
   2、点击两次内部Scroll的Item
  */
  /*预期结果
   2、触发两次点击事件，弹出两次toast弹窗
  */

  scroller1: Scroller = new Scroller()
  scroller2: Scroller = new Scroller()
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  private childRecognizer: GestureRecognizer = new GestureRecognizer()
  private currentRecognizer: GestureRecognizer = new GestureRecognizer()
  private lastOffset: number = 0

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      Scroll(this.scroller1) { // 外部滚动容器
        Column() {
          Text('Outside Scroll')
            .width('90%')
            .height(150)
            .backgroundColor(0xFFFFFF)
            .borderRadius(15)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .margin({ top: 10 })
          Scroll(this.scroller2) { // 内部滚动容器
            Column() {
              Text('Inside Scroll')
                .width('90%')
                .height(150)
                .backgroundColor(0xFFFFFF)
                .borderRadius(15)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .margin({ top: 10 })
              Column() {
                ForEach(this.arr, (item: number) => {
                  Text(item.toString())
                    .width('90%')
                    .height(150)
                    .backgroundColor(0xFFFFFF)
                    .borderRadius(15)
                    .fontSize(16)
                    .textAlign(TextAlign.Center)
                    .margin({ top: 10 })
                    .onClick(() => {
                      promptAction.showToast({
                        message: '点击内部Item：' + item // 测试点：抛滑内部
                      })
                    })
                }, (item: string) => item)
              }
              .width('100%')
            }
          }
          .id('inner')
          .width('100%')
          .height(800)
        }
        .width('100%')
      }
      .id('outer')
      .height(600)
      .scrollable(ScrollDirection.Vertical) // 滚动方向纵向
      .scrollBar(BarState.On) // 滚动条常驻显示
      .scrollBarColor(Color.Gray) // 滚动条颜色
      .scrollBarWidth(10) // 滚动条宽度
      .edgeEffect(EdgeEffect.None)
      .shouldBuiltInRecognizerParallelWith((current: GestureRecognizer, others: Array<GestureRecognizer>) => {
          for (let i = 0; i < others.length; i++) {
            let target = others[i].getEventTargetInfo();
            if (target) {
              // 找到将要组成并行手势的识别器
              if (target.getId() == 'inner' && others[i].isBuiltIn() && others[i].getType() == GestureControl.GestureType.PAN_GESTURE) { 
                // 保存当前组件的识别器
                this.currentRecognizer = current;
                // 保存将要组成并行手势的识别器
                this.childRecognizer = others[i];
                // 返回将要组成并行手势的识别器
                return others[i]; 
              }
            }
          }
          return undefined;
        })
        .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer,
            others: Array<GestureRecognizer>) => {
          // 在识别器即将要成功时，根据当前组件状态，设置识别器使能状态
          if (current) {
            let target = current.getEventTargetInfo();
            if (target) {
              if (target.getId() == 'outer' && current.isBuiltIn() &&
                current.getType() == GestureControl.GestureType.PAN_GESTURE) {
                if (others) {
                  for (let i = 0; i < others.length; i++) {
                    let target = others[i].getEventTargetInfo() as ScrollableTargetInfo;
                    // 找到响应链上对应并行的识别器
                    if (target instanceof ScrollableTargetInfo && target.getId() == 'inner') {
                      let panEvent = event as PanGestureEvent;
                      // 根据当前组件状态以及移动方向动态控制识别器使能状态
                      if (target.isEnd()) {
                        if (panEvent && panEvent.offsetY < 0) {
                          this.childRecognizer.setEnabled(false)
                          this.currentRecognizer.setEnabled(true)
                        } else {
                          this.childRecognizer.setEnabled(true)
                          this.currentRecognizer.setEnabled(false)
                        }
                      } else if (target.isBegin()) {
                        if (panEvent.offsetY > 0) {
                          this.childRecognizer.setEnabled(false)
                          this.currentRecognizer.setEnabled(true)
                        } else {
                          this.childRecognizer.setEnabled(true)
                          this.currentRecognizer.setEnabled(false)
                        }
                      } else {
                        this.childRecognizer.setEnabled(true)
                        this.currentRecognizer.setEnabled(false)
                      }
                    }
                  }
                }
              }
            }
          }
          return GestureJudgeResult.CONTINUE;
        })
        // 绑定一个Pan手势作为动态控制器
        .parallelGesture(
          PanGesture()
            .onActionUpdate((event: GestureEvent) => {
              // 如果识别器状态不是SUCCESSFUL，则不做控制
              if (this.childRecognizer.getState() != GestureRecognizerState.SUCCESSFUL || 
                  this.currentRecognizer.getState() != GestureRecognizerState.SUCCESSFUL) {
                return;
              }
              let target = this.childRecognizer.getEventTargetInfo() as ScrollableTargetInfo;
              let currentTarget = this.currentRecognizer.getEventTargetInfo() as ScrollableTargetInfo;
              if (target instanceof ScrollableTargetInfo && currentTarget instanceof ScrollableTargetInfo) {
                // 在移动过程中实时根据当前组件状态，控制识别器的开闭状态
                if (target.isEnd()) {
                  if ((event.offsetY - this.lastOffset) < 0) {
                    this.childRecognizer.setEnabled(false)
                    if (currentTarget.isEnd()) {
                      this.currentRecognizer.setEnabled(false)
                    } else {
                      this.currentRecognizer.setEnabled(true)
                    }
                  } else {
                    this.childRecognizer.setEnabled(true)
                    this.currentRecognizer.setEnabled(false)
                  }
                } else if (target.isBegin()) {
                  if ((event.offsetY - this.lastOffset) > 0) {
                    this.childRecognizer.setEnabled(false)
                    if (currentTarget.isBegin()) {
                      this.currentRecognizer.setEnabled(false)
                    } else {
                      this.currentRecognizer.setEnabled(true)
                    }
                  } else {
                    this.childRecognizer.setEnabled(true)
                    this.currentRecognizer.setEnabled(false)
                  }
                } else {
                  this.childRecognizer.setEnabled(true)
                  this.currentRecognizer.setEnabled(false)
                }
              }
              this.lastOffset = event.offsetY
            })
        )
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
  }
}