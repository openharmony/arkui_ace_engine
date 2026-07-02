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
// [Start key_distribute_event]
import { hilog } from '@kit.PerformanceAnalysisKit';

const TAG = '[Sample_Eventproject]';
const DOMAIN = 0xF811;
const BUNDLE = 'Eventproject_';

@Entry
@Component
struct Index {
  build() {
    Row() {
      Row() {
        Button('button1')
          .id('button1')
          .margin({ left: 70, right: 30 })
          .onKeyEvent((event) => {
            hilog.info(DOMAIN, TAG, BUNDLE + 'button1');
            return true;
          })
        Button('button2')
          .id('button2')
          .onKeyEvent((event) => {
            hilog.info(DOMAIN, TAG, BUNDLE + 'button2');
            return true;
          })
      }
      .width('100%')
      .height('100%')
      .id('Row1')
      .onKeyEventDispatch((event) => {
        let context = this.getUIContext();
        context.getFocusController().requestFocus('button1');
        return context.dispatchKeyEvent('button1', event);
      })

    }
    .height('100%')
    .width('100%')
    .onKeyEventDispatch((event) => {
      if (event.type == KeyType.Down) {
        let context = this.getUIContext();
        context.getFocusController().requestFocus('Row1');
        return context.dispatchKeyEvent('Row1', event);
      }
      return true;
    })
  }
}

// [End key_distribute_event]

@Builder
export function OnKeyDistributeEvent() {
  NavDestination() {
    Column({ space: 12 }) {
      Index()
    }
    .width('100%')
    .height('100%')
    .padding({ left: 12, right: 12 })
  }
  .backgroundColor('#f1f2f3')
  // 请将$r('app.string.OnKeyDistributeEvent_title')替换为实际资源文件，在本示例中该资源文件的value值为"分发按键事件"
  .title($r('app.string.OnKeyDistributeEvent_title'))
}