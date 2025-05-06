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
struct showPasswordPage {
  @State text: string =
    'A simple day in my life begins with a cup of coffee and a glimpse of the sunrise. I walk to the park, enjoying the fresh air and the sounds of nature.'

  build() {
    Row() {
      Column() {
        Text() {
          Span('规格: \n')
          Span('测试showPassword \n')
        }.draggable(true).copyOption(CopyOptions.InApp)

        Text('设置密码的显隐状态。需要组合密码模式才能生效，非密码输入模式不生效。默认值为false').fontSize(10)
        Text('由于小眼睛图标内置更新密码模式的状态，建议在onSecurityStateChange上增加状态同步').fontSize(10)
        Text('获焦，失焦，点击，长按无变化').fontSize(10)
        Text('设置showPassword为true').fontSize(12)
        TextInput({ text: this.text })
          .width('95%')
          .height(40)
          .margin(20)
          .type(InputType.Password)
          .maxLength(9)
          .showPassword(true)
        Text('设置showPassword为false').fontSize(12)
        TextInput({ text: this.text })
          .width('95%')
          .height(40)
          .margin(20)
          .type(InputType.Password)
          .maxLength(9)
          .showPassword(false)
      }.width('100%')
    }
  }
}