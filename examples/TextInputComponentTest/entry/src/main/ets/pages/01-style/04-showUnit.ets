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
struct struct_01_style_04_showUnit {
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
        Column() {
          Text('规格：TextInput.showUnit 默认undefined，不创建自定义控件').fontColor(Color.Blue)
          TextInput({ text: '没有设置 showUnit ' })
          TextInput({ text: ' .showUnit(undefined) ' }).showUnit(undefined)
          TextInput({ text: ' .showUnit() ' }).showUnit()
        }.borderWidth(2)

        Column() {
          Text('规格：TextInput设置内联模式&showUnit，获焦后，不显示自定义控件').fontColor(Color.Blue)
          TextInput({ text: ' 设置内联模式&showUnit ' }).showUnit(this.itemEnd()).style(TextInputStyle.Inline)
          TextInput({ text: ' 设置默认模式&showUnit' }).showUnit(this.itemEnd()).style(TextInputStyle.Default)
        }.borderWidth(2)

        Column() {
          Text('规格：密码模式，showUnit不生效').fontColor(Color.Blue)
          TextInput({ text: ' 设置内联模式&showUnit ' }).showUnit(this.itemEnd()).style(TextInputStyle.Inline)
          TextInput({ text: ' 设置默认模式&showUnit' }).showUnit(this.itemEnd()).style(TextInputStyle.Default)
        }.borderWidth(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}