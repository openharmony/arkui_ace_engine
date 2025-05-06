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
struct hyperlink {
  @State type: CancelButtonStyle = CancelButtonStyle.INVISIBLE
  @State text1: string = '123456789test001'

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Column() {
          Text('操作：分别对图片Hyperlink和纯文本Hyperlink长按拖拽').fontColor(Color.Blue)
          Text('Pass条件：两个Hyperlink均可展示，且默认可拖起').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        Column() {
          Hyperlink($r('app.string.website')) {
            Image($r('app.media.startIcon'))
              .width(200)
              .height(100)
          }
        }

        Column() {
          Hyperlink($r('app.string.website'), 'Go to the developer website') {
          }
          .color(Color.Blue)
        }
      }.width('100%')
    }
  }
}