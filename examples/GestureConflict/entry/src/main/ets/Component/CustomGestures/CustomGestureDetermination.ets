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
// [Start custom_gestures]
import { PromptAction } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  scroller: Scroller = new Scroller();
  promptAction: PromptAction = this.getUIContext().getPromptAction();

  build() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        /*
        请将$r('app.string.Drag_instructions')替换为实际资源文件，在本示例中该资源文件的value值为"包括上下两层组件，上层组件绑定长按手势，
        下层组件绑定拖拽。其中上层组件下半区域绑定手势拦截，使该区域响应下层拖拽手势。"
         */
        Text($r('app.string.Drag_instructions')).width('100%').fontSize(20).fontColor('0xffdd00')
        Stack({ alignContent: Alignment.Center }) {
          Column() {
            // 模拟上半区和下半区
            Stack().width('200vp').height('100vp').backgroundColor(Color.Gray)
            Stack().width('200vp').height('100vp').backgroundColor(Color.Blue)
          }.width('200vp').height('200vp')

          // Stack的下半区是绑定了滑动手势的图像区域。
          // $r('sys.media.ohos_app_icon') 需要替换为开发者所需的资源文件
          Image($r('sys.media.ohos_app_icon'))
            .draggable(true)
            .onDragStart(() => {
              // 请将$r('app.string.Allow_dragging_prompt')替换为实际资源文件，在本示例中该资源文件的value值为"Drag 下半区蓝色区域，Image响应"
              this.promptAction.showToast({ message: $r('app.string.Allow_dragging_prompt') });
            })
            .width('200vp').height('200vp')
          // Stack的上半区是绑定了长按手势的浮动区域。
          Stack() {
          }
          .width('200vp')
          .height('200vp')
          .hitTestBehavior(HitTestMode.Transparent)
          .gesture(GestureGroup(GestureMode.Parallel,
            LongPressGesture()
              .onAction((event: GestureEvent) => {
                /*
                请将$r('app.string.Stop_dragging_prompt')替换为实际资源文件，在本示例中
                该资源文件的value值为"LongPressGesture 长按上半区 红色区域，红色区域响应"
                 */
                this.promptAction.showToast({ message: $r('app.string.Stop_dragging_prompt') });
              })
              .tag('longpress')
          ))
          .onGestureJudgeBegin((gestureInfo: GestureInfo, event: BaseGestureEvent) => {
            // 如果是长按类型手势，判断点击的位置是否在上半区
            if (gestureInfo.type == GestureControl.GestureType.LONG_PRESS_GESTURE) {
              if (event.fingerList.length > 0 && event.fingerList[0].localY < 100) {
                return GestureJudgeResult.CONTINUE;
              } else {
                return GestureJudgeResult.REJECT;
              }
            };
            return GestureJudgeResult.CONTINUE;
          })
        }.width('100%')
      }.width('100%')
    }
  }
}

// [End custom_gestures]