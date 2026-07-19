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

// [Start key_event_intercept]
import { KeyCode } from '@kit.InputKit';

@Entry
@Component
struct PreImeEventExample {
  @State buttonText: string = '';
  @State buttonType: string = '';
  @State columnText: string = '';
  @State columnType: string = '';

  build() {
    Column() {
      Search({
        placeholder: 'Search...'
      })
        .width('80%')
        .height('40vp')
        .border({ radius: '20vp' })
        .onKeyPreIme((event: KeyEvent) => {
          if (event.keyCode == KeyCode.KEYCODE_DPAD_LEFT) {
            return true;
          }
          return false;
        })
    }
  }
}
// [End key_event_intercept]

@Builder
export function PreIme() {
  NavDestination() {
    Column({ space: 12 }) {
      PreImeEventExample()
    }
    .width('100%')
    .height('100%')
    .padding({ left: 12, right: 12 })
  }
  .backgroundColor('#f1f2f3')
  // 请将$r('app.string.Device_OnKeyPreIme_title')替换为实际资源文件，在本示例中该资源文件的value值为"屏蔽按键事件"
  .title($r('app.string.Device_OnKeyPreIme_title'))
}