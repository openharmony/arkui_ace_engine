/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, SliderBlock, useEnabled } from 'common';
import promptAction from '@ohos.promptAction';

@Component
export struct ToastBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableMessage: boolean = false;
  @State compMessage: string = 'Harmony Sans';
  @State enableDuration: boolean = false;
  @State compDuration: number = 1500;
  @State enableBottom: boolean = false;
  @State compBottom: number = 80;
  @State compBackGroundColor:ResourceColor = Color.Transparent;
  @State compMargin: number = 15;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor(this.compBackGroundColor)
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Button('显示Toast')
        .onClick(() => {
          try {
            promptAction.showToast({
              message: useEnabled(this.enableMessage, this.compMessage, 'text'),
              duration: useEnabled(this.enableDuration, this.compDuration),
              bottom: useEnabled(this.enableBottom, this.compBottom)
            });
          } catch (error) {

          }
        }).margin(this.compMargin)
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '文本数量',
          isEnabled: this.enableMessage,
          value: this.compMessage,
          dataSource: [
            { label: '单行', value: 'text'},
            { label: '多行', value: 'The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.'},
            { label: '多', value: 'The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.'},
            { label: '超多', value: 'The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.'}
          ]
        })
        SliderBlock({
          title: '文本显示时间(ms)',
          isEnabled: this.enableDuration,
          value: this.compDuration,
          min: 1500,
          max: 10000
        })
        SliderBlock({
          title: '距底部位置',
          isEnabled: this.enableBottom,
          value: this.compBottom,
          min: 80,
          max: 400
        })
      }.width('100%')
      .height('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct ToastBootcampPreviewer {
  build() {
    ToastBootcamp({
      title: '即时反馈/Toast'
    })
  }
}
