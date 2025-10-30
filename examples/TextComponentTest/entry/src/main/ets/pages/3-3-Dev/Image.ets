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
struct ImageExample3_3 {
  @State copyOption: CopyOptions[] =
    [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 0
  @State text: string = 'SR000IH5KG【基础能力】文本输入类基础能力增强'

  build() {
    Column() {
      Text('同一格式图片jpg')
      Row() {
        Image($r('app.media.no0')).copyOption(this.copyOption[this.index]).height(100).width(100)
        Image($r('app.media.no0')).copyOption(this.copyOption[this.index]).height(100).width(100)
        Image($r('app.media.no0')).copyOption(this.copyOption[this.index]).height(100).width(100)
      }.border({ width: 1 })

      Text('不同一格式图片jpg、png、bmp')
      Row() {
        Image($r('app.media.no1')).copyOption(this.copyOption[this.index]).height(100).width(100)
        Image($r('app.media.no0')).copyOption(this.copyOption[this.index]).height(100).width(100)
        Image($r('app.media.no9')).copyOption(this.copyOption[this.index]).height(100).width(100)
      }.border({ width: 1 })

      Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
        this.index++
        if (this.index > (this.copyOptionStr.length - 1)) {
          this.index = 0
        }
      }).margin({ top: 20 })
    }.alignItems(HorizontalAlign.Center).width('100%')
  }
}