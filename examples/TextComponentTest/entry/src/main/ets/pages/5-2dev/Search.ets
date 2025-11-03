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
struct Search5_2 {
  @State copyOption: CopyOptions[] = [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2
  @State text: string = ''
  controller: SearchController = new SearchController()
  @State maxLength: number = 6
  @State enable: boolean = true
  @State color: string[] = ['rgba(0,0,0,0)','rgba(0,0,0,0.4)', 'rgba(243, 11, 11, 1)', 'rgba(11, 234, 33, 0.98)', 'rgba(7, 122, 245, 0.98)', 'rgba(0,0,0,1)']
  @State colorStr: string[] = ['透明', '透明60%', '红', '绿', '蓝', '黑']
  @State colorIndex: number = 4

  build() {
    Column(){
      Search({ value: this.text, placeholder:'placeholder...', controller: this.controller})
        .copyOption(this.copyOption[this.index])
        .enabled(this.enable)
        .draggable(true)
        .fontColor(this.color[this.colorIndex])
        .onChange((value: string) => {
          this.text = value
        }).width('80%').margin(20)

      TextArea({placeholder:'TextArea'}).height(100).width('80%')

      Row() {
        Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
          this.index ++
          if (this.index > (this.copyOptionStr.length - 1)) {
            this.index = 0
          }
        })
        Button('enabled:' + this.enable).onClick((event: ClickEvent) => {
          this.enable = !this.enable
        })
      }.margin({top:20})

      Row() {
        Button('字体颜色:' + this.colorStr[this.colorIndex]).onClick(() => {
          this.colorIndex ++
          if (this.colorIndex > (this.colorStr.length - 1)) {
            this.colorIndex = 0
          }
        })
      }

    }.alignItems(HorizontalAlign.Center).width('100%')
  }
}