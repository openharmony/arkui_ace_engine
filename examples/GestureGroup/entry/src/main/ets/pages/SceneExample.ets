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

// [Start scene_example]
// xxx.ets
import { PromptAction } from '@kit.ArkUI';

@Entry
@Component
struct CombinedGestureDemo {
  @State isLongPress: boolean = false;
  promptAction: PromptAction = this.getUIContext().getPromptAction();

  build() {
    Swiper() {
      // 页面1
      Row()
        .width('100%')
        .height('100%')
        .backgroundColor(Color.Grey)
        .borderRadius(12)
        // 通过自定义手势判定回调，判断在长按手势未成功时，拒绝子组件的滑动手势，从而让父组件Swiper的滑动手势成功
        .onGestureRecognizerJudgeBegin(
          (event: BaseGestureEvent, current: GestureRecognizer, others: Array<GestureRecognizer>) => {
            if (current.getType() !== GestureControl.GestureType.PAN_GESTURE) {
              return GestureJudgeResult.CONTINUE;
            }
            ;
            if (this.isLongPress) {
              return GestureJudgeResult.CONTINUE;
            }
            ;
            return GestureJudgeResult.REJECT;
          })
        .gesture(
          // 绑定并行手势组，实现长按手势和滑动手势可以同时触发
          GestureGroup(GestureMode.Parallel,
            LongPressGesture()
              .onAction(() => {
                this.isLongPress = true;
                this.promptAction.showToast({ message: 'LongPress trigger' });
              })
              .onActionEnd(() => {
                this.isLongPress = false;
              })
            ,
            PanGesture()
              .onActionStart(() => {
                this.promptAction.showToast({ message: 'child pan start' });
              })
          )
        )
      // 页面2
      Row()
        .width('100%')
        .height('100%')
        .backgroundColor(Color.Pink)
        .borderRadius(12)
    }
    .borderWidth(2)
    .width('100%')
    .height(300)
    .padding(20)
  }
}
// [End scene_example]