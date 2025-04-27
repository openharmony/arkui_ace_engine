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
struct ShowPasswordIconStruct {
  @State text: string = 'TextInput: Hello world'
  @State passwordState: boolean = false

  build() {
    Column({ space: 20 }) {
      Text() {
        Span('规格:\n')
        Span('1、默认值为true，设置密码输入模式时，输入框末尾的图标显示 \n')
        Span('2、输入框末尾的图标显示时，点击图标切换为对应的密码展示或密码隐藏图标 \n')
      }.draggable(true).copyOption(CopyOptions.InApp)

      Text('默认值为true，设置密码输入模式时，输入框末尾的图标显示')
      Row() {
        TextInput({ placeholder: 'TextInput: not set', text: this.text })
          .width('50%')
          .type(InputType.Password)
        TextInput({ placeholder: 'TextInput: set default', text: this.text })
          .width('50%')
          .type(InputType.Password)
          .showPasswordIcon(true)
      }

      Text('设置false，设置密码输入模式时，输入框末尾的图标不显示')
      TextInput({ placeholder: 'TextInput: set false', text: this.text })
        .width('50%')
        .type(InputType.Password)
        .showPasswordIcon(false)

      Text('输入框末尾的图标显示时，点击图标切换为对应的密码展示或密码隐藏图标')
      TextInput({ placeholder: 'TextInput', text: this.text })
        .type(InputType.Password)
        .showPasswordIcon(true)
        .showPassword(this.passwordState)
        .onSecurityStateChange(((isShowPassword: boolean) => {
          // 更新密码显示状态
          this.passwordState = isShowPassword
        }))
    }.width('100%')
  }
}