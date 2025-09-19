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

@Entry
@Component
struct OnClickOnTouch {
  @State textStr1: string = '';
  @State textStr2: string = '';

  build() {
    Row() {
      Column() {
        Text('This is a text component.')
          .fontSize(30)
          .onClick(() => {
            console.info('Text onClick is triggering');
            this.textStr1 = 'Text onClick is triggering';
          })
          .onTouch(() => {
            console.info('Text onTouch is triggering');
            this.textStr2 = 'Text onTouch is triggering';
          })
        Text('onClick：' + this.textStr1)
          .fontSize(20)
        Text('onTouch：' + this.textStr2)
          .fontSize(20)
      }.width('100%')
    }
    .height('100%')
  }
}