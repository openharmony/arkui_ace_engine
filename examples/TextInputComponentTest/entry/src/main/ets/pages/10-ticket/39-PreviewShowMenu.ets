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
struct struct_10_39_preview_show_menu {
  @State text: string = ''

  build() {
    Column() {
      Text('步骤：1、开启预上屏 2、输入文字 3、点击清除按钮 4、长按文本框').fontColor(Color.Blue)
      Text('pass条件：出现菜单').fontColor(Color.Blue)

      TextInput()
        .cancelButton({ style: CancelButtonStyle.CONSTANT })
        .enablePreviewText(true)
    }
    .width('100%')
    .height('100%')
  }
}