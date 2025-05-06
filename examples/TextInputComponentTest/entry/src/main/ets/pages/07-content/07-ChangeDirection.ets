/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct Ets_7_7_changeDirection {
  build() {
    Column() {
      Text('规格 改变direction从Ltr到Rtl，文本位置左右镜像').fontColor(Color.Blue)

      Text('pass条件：\n 1、前两个输入框与黑色边框左对齐，后两个输入框与黑色边框右对齐').fontColor(Color.Red).padding(10)

      Row() {
        Search({ value: '输入框内容填充' })
          .type(SearchType.NORMAL)
          .cancelButton({ style: CancelButtonStyle.CONSTANT })
          .width('100%')
          .direction(Direction.Auto)
      }

      Row() {
        Search({ value: '输入框内容填充' })
          .type(SearchType.NORMAL)
          .cancelButton({ style: CancelButtonStyle.CONSTANT })
          .width('100%')
          .direction(Direction.Ltr)
      }

      Row() {
        Search({ value: '输入框内容填充' })
          .type(SearchType.NORMAL)
          .cancelButton({ style: CancelButtonStyle.CONSTANT })
          .width('100%')
          .direction(Direction.Rtl)
      }

      Row() {
        Search({ value: 'أدخل محتويات المربع' })
          .type(SearchType.NORMAL)
          .cancelButton({ style: CancelButtonStyle.CONSTANT })
          .width('100%')
          .direction(Direction.Auto)
      }

      Row()
        .width('100%')
        .height(20)
        .backgroundColor(Color.Black)
        .border({
          width: {
            start: LengthMetrics.vp(36),
            end: LengthMetrics.vp(36),
          },
          color: Color.Red
        })
    }
  }
}