/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct struct_01_style_10_cancelButton {
  @Builder
  itemEnd() {
    Select([{ value: 'KB' },
      { value: 'MB' },
      { value: 'GB' },
      { value: 'TB', }])
      .height('48vp')
      .borderRadius(0)
      .selected(2)
      .align(Alignment.Center)
      .value('MB')
      .font({ size: 20, weight: 500 })
      .fontColor('#182431')
      .selectedOptionFont({ size: 20, weight: 400 })
      .optionFont({ size: 20, weight: 400 })
      .backgroundColor(Color.Transparent)
      .responseRegion({
        height: '40vp',
        width: '80%',
        x: '10%',
        y: '6vp'
      })
      .onSelect((index: number) => {
        console.info('Select:' + index);
      })
  }

  build() {
    Scroll() {
      Column() {
        Column({ space: 5 }) {
          Text('规格：TextInput内联模式下不支持cancelButton ').fontColor(Color.Blue)
          TextInput({ text: ` 内联模式 设置 cancelButton` }).style(TextInputStyle.Inline).cancelButton({
            style: CancelButtonStyle.INPUT
          })
          TextInput({ text: ` TextInputStyle.Default 设置 cancelButton` }).style(TextInputStyle.Default)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：TextInput.cancelButton 默认值取 {style: CancelButtonStyle.INPUT}').fontColor(Color.Blue)
          TextInput({ text: ` 不设置 cancelButton ` })
          TextInput({ text: ` cancelButton 设置 {style: CancelButtonStyle.INPUT}` }).cancelButton({
            style: CancelButtonStyle.INPUT
          })
          TextInput({ text: ` cancelButton 设置  undefined` }).cancelButton(undefined)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：TextInput.cancelButton 密码模式下，icon显示在小眼睛左侧').fontColor(Color.Blue)
          TextInput({ text: ` cancelButton 设置 {style: CancelButtonStyle.INPUT}` })
            .type(InputType.Password)
            .cancelButton({
              style: CancelButtonStyle.CONSTANT,
              icon: {
                size: 45,
                src: $r('app.media.startIcon'),
                color: Color.Blue
              }
            })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格： cancelButton的icon显示在showUnit控件 左侧').fontColor(Color.Blue)
          TextInput({ text: ` cancelButton 设置 {style: CancelButtonStyle.INPUT}` })
            .cancelButton({
              style: CancelButtonStyle.CONSTANT,
              icon: {
                size: 45,
                src: $r('app.media.startIcon'),
                color: Color.Blue
              }
            })
            .showUnderline(true)
            .showUnit(this.itemEnd())
          Blank().height(20)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格： cancelButton 显示与隐藏不改变下划线的长度').fontColor(Color.Blue)
          TextInput({ text: ` 设置 {style: CancelButtonStyle.INVISIBLE}` })
            .cancelButton({
              style: CancelButtonStyle.INVISIBLE,
              icon: {
                size: 45,
                src: $r('app.media.startIcon'),
                color: Color.Blue
              }
            })
            .showUnderline(true)

          TextInput({ text: ` 设置 {style: CancelButtonStyle.INPUT}` })
            .cancelButton({
              style: CancelButtonStyle.INPUT,
              icon: {
                size: 45,
                src: $r('app.media.startIcon'),
                color: Color.Blue
              }
            })
            .showUnderline(true)

          TextInput({ text: ` 设置 {style: CancelButtonStyle.CONSTANT}` })
            .cancelButton({
              style: CancelButtonStyle.CONSTANT,
              icon: {
                size: 45,
                src: $r('app.media.startIcon'),
                color: Color.Blue
              }
            })
            .showUnderline(true)
          Blank().height(20)
        }.borderWidth(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}