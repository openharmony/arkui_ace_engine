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
struct TextInputExample5_2 {
  @State copyOption: CopyOptions[] = [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2
  @State text: string = ''
  @State type: InputType[] = [InputType.Normal, InputType.Number, InputType.Password, InputType.Email, InputType.PhoneNumber, InputType.NUMBER_PASSWORD, InputType.USER_NAME, InputType.NEW_PASSWORD]
  @State typeStr: string[] = ['Normal', 'Number', 'Password', 'Email', 'PhoneNumber', 'NUMBER_PASSWORD', 'SCREEN_LOCK_PASSWORD', 'USER_NAME', 'NEW_PASSWORD']
  @State inputIndex: number = 0
  @State enable: boolean = true
  @State color: string[] = ['rgba(0,0,0,0)','rgba(0,0,0,0.4)', 'rgba(243, 11, 11, 1)', 'rgba(11, 234, 33, 0.98)', 'rgba(7, 122, 245, 0.98)', 'rgba(0,0,0,1)']
  @State colorStr: string[] = ['透明', '透明60%', '红', '绿', '蓝', '黑']
  @State colorIndex: number = 5
  @State selectedBackgroundColor: number = 1
  controller: TextInputController = new TextInputController()
  build() {
    Column(){
      TextInput({ text: this.text, placeholder: 'input your word...', controller: this.controller })
        .placeholderFont({ size: 14, weight: 400 })
        .type(this.type[this.inputIndex])
        .copyOption(this.copyOption[this.index])
        .fontColor(this.color[this.colorIndex])
        .selectedBackgroundColor(this.color[this.selectedBackgroundColor])
        .enabled(this.enable)
        .draggable(true)
        .width(400)
        .height(40)
        .margin(20)
        .onChange((value: string) => {
          this.text = value
        }).width('80%')

      TextArea({placeholder:'TextArea'}).height(100).width('80%')

      Row() {
        Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
          this.index ++
          if (this.index > (this.copyOptionStr.length - 1)) {
            this.index = 0
          }
        })
        Button('type:' + this.typeStr[this.inputIndex]).onClick(() => {
          this.inputIndex ++
          if (this.inputIndex > (this.type.length - 1)) {
            this.inputIndex = 0
          }
        })
      }.margin({top:20})
     Row() {
       Button('字体颜色:' + this.colorStr[this.colorIndex]).onClick(() => {
         this.colorIndex ++
         if (this.colorIndex > (this.colorStr.length - 1)) {
           this.colorIndex = 0
         }
       })
       Button('底板颜色:' + this.colorStr[this.selectedBackgroundColor]).onClick(() => {
         this.selectedBackgroundColor ++
         if (this.selectedBackgroundColor > (this.colorStr.length - 1)) {
           this.selectedBackgroundColor = 0
         }
       })
     }
      Button('enabled:' + this.enable).onClick((event: ClickEvent) => {
        this.enable = !this.enable
      })

    }.alignItems(HorizontalAlign.Center).width('100%')
  }
}