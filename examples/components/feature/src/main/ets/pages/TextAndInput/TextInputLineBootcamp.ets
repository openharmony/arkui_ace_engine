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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock } from 'common';

@Component
export struct TextInputLineBootcamp {
  @Provide('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableInputType: boolean = false;
  @State inputType: InputType = InputType.Password
  @State enableShowUnderLine: boolean = true;
  @State text: string = ''
  @State cancelStyle: CancelButtonStyle | null = CancelButtonStyle.CONSTANT;
  private scrollerForScroll: Scroller = new Scroller();

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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Scroll(this.scrollerForScroll) {
      Column() {
        TextInput({ text: this.text, placeholder: 'input your word...', })
          .cancelButton({
            style: this.cancelStyle,
          })
          .showUnderline(this.enableShowUnderLine)
          .type(this.inputType)
      }.width('100%').height('100%')
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '文本框类型',
          isEnabled: this.enableInputType,
          value: this.inputType,
          dataSource: [
            { label: '下划线', value: InputType.Normal },
            { label: '加密', value: InputType.Password }]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct TextInputLineBootcampPreviewer {
  build() {
    TextInputLineBootcamp({
      title: '下划线文本/TextInputLine'
    })
  }
}