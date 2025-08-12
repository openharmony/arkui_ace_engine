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
struct Index_ContainerSpan {
  @State messageResponseRegion: string = '标记是否点到热区'

  build() {
    Scroll() {

      Column() {
        Column() {
          Text(' 测试点 Hyperlink create ')
          Hyperlink($r('app.string.TextInputPlaceholder'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Column() {
            Text(' 测试点 Hyperlink color ')
            Hyperlink($r('app.string.TextInputPlaceholder'))
              .color($r('app.color.ModeColor'))
          }.borderWidth(1)

          Blank().borderWidth(5).height(1)


          Column() {
            Text(' 测试点 Text responseRegion ')
            Text(' 浅色 左半边，深色 全部 ')
            Hyperlink($r('app.string.TextInputPlaceholder'))
              .borderWidth(2)
              .borderColor(Color.Red)
              .height(100)
              .width(300)
              .onClick(() => {
                this.messageResponseRegion = '已经点到热区，点一下 点击复位 '
              })
              .responseRegion({
                x: 0,
                y: 0,
                width: $r('app.string.TextResponseRegionWidth'),
                height: '100%'
              })
            Text(this.messageResponseRegion)
            Button('点击复位')
              .onClick(() => {
                this.messageResponseRegion = '标记是否点到热区'
              })
          }.borderWidth(1)

        }

      }
    }
  }
}