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
struct struct_01_style_02_style {
  @State text: string = ''

  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格：style 异常值取 TextInputStyle.Default').fontColor(Color.Blue)
          TextInput({ placeholder: '.style(TextInputStyle.Default)' }).style(TextInputStyle.Default)
          TextInput({ placeholder: '未设置style' })
          TextInput({ placeholder: '.style(undefined)' }).style(undefined)

          Column({ space: 5 }) {
            Text('规格：内联模式第一次获焦时不弹手柄，后续单击操作允许弹手柄').fontColor(Color.Blue)
            TextInput({ text: `文本框点击两次，第三次点击光标` }).style(TextContentStyle.INLINE)
            TextInput({ text: `文本框点击两次，第三次点击光标` }).style(TextInputStyle.Inline)
          }.borderWidth(2)

          Column({ space: 5 }) {
            Text('规格：TextInput 内联模式，全选多行文本，显示空行连接线（2vp）').fontColor(Color.Blue)
            TextInput({ text: `ABC CDE，点击全选` }).style(TextInputStyle.Inline)
          }.borderWidth(2)

          Column() {
            Text('规格1 默认普通模式or设置异常值状态下').fontColor(Color.Blue)
            Text('pass条件: 三个文本框，都执行以下三个步骤 \n').fontColor(Color.Red)
            Text('步骤1：点击文本框，键盘拉起显示光标 \n')
            Text('步骤2：收起键盘，长按文本框，键盘拉起显示光标 \n')
            Text('步骤3：关闭键盘或者点击其他文本框时，当前文本框光标消失。 \n')
            Column() {
              TextInput({ placeholder: 'TextInput: 未设置style' })
              TextInput({ placeholder: 'TextInput: 设置 .style(TextInputStyle.Default)' })
                .style(TextInputStyle.Default)
              TextInput({ placeholder: 'TextInput: 设置 .style(111)' })
                .style(111)
            }
          }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

          Column() {
            Text('规格2 普通模式获焦显示光标并拉起键盘，失焦隐藏光标，点击或长按可获焦').fontColor(Color.Blue)
            Text('pass条件: 三个文本框，都执行以下三个步骤 \n').fontColor(Color.Red)
            Text('步骤1：点击文本框，键盘拉起显示光标 \n')
            Text('步骤2：收起键盘，长按文本框，键盘拉起显示光标 \n')
            Text('步骤3：关闭键盘或者点击其他文本框时，当前文本框光标消失。 \n')

            Text('下面是 TextInput，设置TextContentStyle.DEFAULT')
            TextInput({ placeholder: 'TextInput: 普通模式', text: this.text })
              .style(TextContentStyle.DEFAULT)
            Text('下面是 TextArea，设置TextContentStyle.DEFAULT')
            TextArea({ placeholder: 'TextArea: 普通模式', text: this.text })
              .style(TextContentStyle.DEFAULT)
          }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)


          Column() {
            Text('规格3 内联模式获焦变为圆角矩形方框').fontColor(Color.Blue)
            Text('pass条件:  点击文本框变成圆角矩形方框 \n').fontColor(Color.Red)

            Text('下面是 TextInput')
            TextInput({ placeholder: 'TextInput: 内联模式', text: this.text })
              .style(TextContentStyle.INLINE)
            Text('下面是 TextArea')
            TextArea({ placeholder: 'TextArea: 内联模式', text: this.text })
              .style(TextContentStyle.INLINE)
          }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        }.borderWidth(2)
      }
    }
    .height('100%')
    .width('100%')
  }
}