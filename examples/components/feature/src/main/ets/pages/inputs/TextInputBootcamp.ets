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
import { ColorBlock, useEnabled } from 'common';


@Component
export struct TextInputBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false
  @State isShow: boolean = false
  @State text: string = ''
  @State enablebackgroundColor: boolean = false;
  @State ebackgroundColor: ResourceColor = 'rgb(255, 0, 0, 0.9)';
  @State enablecaretColor: boolean = false;
  @State ecaretColor: ResourceColor = 'rgb(255, 0, 0, 0.9)';

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
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      TextInput({ text: this.text })
        .onChange((value: string) => {
          this.text = value
        })
        .caretColor(useEnabled(this.enablebackgroundColor, this.ebackgroundColor))
        .selectedBackgroundColor(useEnabled(this.enablecaretColor, this.ecaretColor))
    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        ColorBlock({
          title: '光标颜色',
          isEnabled: this.enablebackgroundColor,
          color: this.ebackgroundColor
        })
        ColorBlock({
          title: '背景颜色',
          isEnabled: this.enablecaretColor,
          color: this.ecaretColor
        })
      }.width('100%')
      .height('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct TextInputBootcampPreviewer {
  build() {
    TextInputBootcamp({
      title: '单行文本框/TextInput'
    })
  }
}