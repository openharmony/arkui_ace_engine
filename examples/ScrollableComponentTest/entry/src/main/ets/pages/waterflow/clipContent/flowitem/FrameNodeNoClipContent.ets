/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { FlowItemFrameNodeController } from './FrameNodeController'

@ComponentV2
export struct FlowItemFrameNodeNoClipContentTest {
  @Local scrollRange: string = 'idx:--';
  private controller: FlowItemFrameNodeController = new FlowItemFrameNodeController(false);

  aboutToAppear(): void {
    this.controller.setRangeCallback((range: string) => {
      this.scrollRange = range;
    });
  }

  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Top }) {
        NodeContainer(this.controller)
          .width('100%')
          .height('100%')

        Row({ space: 6 }) {
          Button('Reload').onClick(() => {
            this.controller.reload();
          })
          Button('jump10').onClick(() => {
            this.controller.scrollToIndex(10);
          })
          Text(this.scrollRange).fontSize(12)
        }
        .height(50)
        .padding({ left: 12, right: 12 })
      }
      .width('100%')
      .height('100%')
      .background('#DCDCDC')
      .safeAreaPadding({ top: $r('sys.float.ohos_id_navigation_bar_height') })
    }.title('FlowItemFrameNodeNoClipContent', {
      backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
      barStyle: BarStyle.STACK,
    })
  }
}
