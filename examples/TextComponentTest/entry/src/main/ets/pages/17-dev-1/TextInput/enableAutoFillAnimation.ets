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

/* 0. 点击 'enableAutoFillAnimation' 按钮使 enableAutoFillAnimation==true
 * 1. 进入'设置'->设置锁屏密码
 * 2. 进入'设置'->进入 '密码保险箱'->使用锁屏密码解锁
 * 3. '密码保险箱'中添加一个账户
 * 4. 点击输入框->弹出键盘可以看见 '🗝︎ 密码保险箱',点击该字样后并使用锁屏密码解锁选择刚刚添加的账户后方可自动填充
 * */

@Component
struct TextInputEnableAutoFillAnimation1 {
  @State enableAutoFillAnimation: boolean = true;

  build() {
    Column() {
      Button(`enableAutoFillAnimation==${this.enableAutoFillAnimation ? "true" : "false"}`).onClick(() => {
        this.enableAutoFillAnimation = !this.enableAutoFillAnimation;
      })
      Text("请输入用户名：")
      TextInput()
        .type(InputType.USER_NAME)
        .width("100%")
        .margin(20)
        .cancelButton({
          style: CancelButtonStyle.INPUT,
          icon: {
            color: Color.Black
          }
        })
      Text("请输入密码：")
      TextInput({ placeholder: 'input your word...' })
        .width("100%")
        .margin(20)
        .type(InputType.Password)
        .enableAutoFillAnimation(this.enableAutoFillAnimation)

      Text("强密码：")
      TextInput()
        .width("70%")
        .margin(20)
        .type(InputType.NEW_PASSWORD)
        .enableAutoFillAnimation(this.enableAutoFillAnimation)
    }
    .width('100%')
  }
}

@Component
export struct TextInputEnableAutoFillAnimation {
  build() {
    NavDestination() {
      TextInputEnableAutoFillAnimation1()
    }.hideBackButton(true)
  }
}