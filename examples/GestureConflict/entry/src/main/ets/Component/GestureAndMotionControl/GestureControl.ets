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
@Entry
@Component
struct GestureControlGroup {
  scroller: Scroller = new Scroller();
  scroller2: Scroller = new Scroller();
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
  private childRecognizer: GestureRecognizer = new GestureRecognizer();
  private currentRecognizer: GestureRecognizer = new GestureRecognizer();
  private lastOffset: number = 0;

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      Scroll(this.scroller) { // 外部滚动容器
        Column() {
          Text('Scroll Area')
            .width('90%')
            .height(150)
            .backgroundColor(0xFFFFFF)
            .borderRadius(15)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .margin({ top: 10 })
          Scroll(this.scroller2) { // 内部滚动容器
            Column() {
              Text('Scroll Area2')
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
                }, (item: string) => item)
              }.width('100%')
            }
          }
          .id('inner')
          .width('100%')
          .height(800)
        }.width('100%')
      }
      .id('outer')
      .height(600)
      .scrollable(ScrollDirection.Vertical) // 滚动方向纵向
      .scrollBar(BarState.On) // 滚动条常驻显示
      .scrollBarColor(Color.Gray) // 滚动条颜色
      .scrollBarWidth(10) // 滚动条宽度
      .edgeEffect(EdgeEffect.None)


      // [Start gesture_simultaneously]
      .shouldBuiltInRecognizerParallelWith((current: GestureRecognizer, others: Array<GestureRecognizer>) => {
        for (let i = 0; i < others.length; i++) {
          let target = others[i].getEventTargetInfo();
          if (target.getId() == 'inner' && others[i].isBuiltIn() && others[i].getType() == GestureControl.GestureType.PAN_GESTURE) { // 找到将要组成并行手势的识别器
            this.currentRecognizer = current; // 保存当前组件的识别器
            this.childRecognizer = others[i]; // 保存将要组成并行手势的识别器
            return others[i]; // 返回和当前手势将要组成并行手势的识别器
          };
        };
        return undefined;
      })
      //  [End gesture_simultaneously]


      // [Start gesture_openingclosing]
      .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer,
        others: Array<GestureRecognizer>) => { // 在识别器即将要成功时，根据当前组件状态，设置识别器使能状态
        let target = current.getEventTargetInfo();
        if (target && target.getId() == 'outer' && current.isBuiltIn() && current.getType() == GestureControl.GestureType.PAN_GESTURE) {
          for (let i = 0; i < others.length; i++) {
            let target = others[i].getEventTargetInfo() as ScrollableTargetInfo;
            if (target instanceof ScrollableTargetInfo && target.getId() == 'inner') { // 找到响应链上对应并行的识别器
              let panEvent = event as PanGestureEvent;
              this.childRecognizer.setEnabled(true);
              this.currentRecognizer.setEnabled(false);
              if (target.isEnd()) { // 根据当前组件状态以及移动方向动态控制识别器使能状态
                if (panEvent && panEvent.offsetY < 0) {
                  this.childRecognizer.setEnabled(false);
                  this.currentRecognizer.setEnabled(true);
                };
              } else if (target.isBegin()) {
                if (panEvent.offsetY > 0) {
                  this.childRecognizer.setEnabled(false);
                  this.currentRecognizer.setEnabled(true);
                };
              };
            };
          };
        };
        return GestureJudgeResult.CONTINUE;
      })
      //  [End gesture_openingclosing]

      // [Start listening_gestures]
      .parallelGesture( // 绑定一个Pan手势作为动态控制器
        PanGesture()
          .onActionUpdate((event: GestureEvent)=>{
            if (this.childRecognizer.getState() != GestureRecognizerState.SUCCESSFUL ||
              this.currentRecognizer.getState() != GestureRecognizerState.SUCCESSFUL) { // 如果识别器状态不是SUCCESSFUL，则不做控制
              return;
            };
            let target = this.childRecognizer.getEventTargetInfo() as ScrollableTargetInfo;
            let currentTarget = this.currentRecognizer.getEventTargetInfo() as ScrollableTargetInfo;
            if (target instanceof ScrollableTargetInfo && currentTarget instanceof ScrollableTargetInfo) {
              this.childRecognizer.setEnabled(true);
              this.currentRecognizer.setEnabled(false);
              if (target.isEnd()) { // 在移动过程中实时根据当前组件状态，控制识别器的开闭状态
                if ((event.offsetY - this.lastOffset) < 0) {
                  this.childRecognizer.setEnabled(false);
                  if (currentTarget.isEnd()) {
                    this.currentRecognizer.setEnabled(false);
                  } else {
                    this.currentRecognizer.setEnabled(true);
                  };
                };
              } else if (target.isBegin()) {
                if ((event.offsetY - this.lastOffset) > 0) {
                  this.childRecognizer.setEnabled(false);
                  if (currentTarget.isBegin()) {
                    this.currentRecognizer.setEnabled(false);
                  } else {
                    this.currentRecognizer.setEnabled(true);
                  };
                };
              };
            };
            this.lastOffset = event.offsetY;
          })
      )
      //  [End listening_gestures]

    }.width('100%').height('100%').backgroundColor(0xDCDCDC)
  }
}