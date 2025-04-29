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
struct struct_02_layout_01_border {
  build() {
    Scroll() {
      Column() {
        Column({ space: 5 }) {
          Text('规格：TextInput 未指定输入框宽度时，输入框宽度按照maxWidth撑满').fontColor(Color.Blue)
          Text('pass条件：输入框的边框线与外层Column的边框线重叠 \n')
          Column() {
            TextInput({ placeholder: '观察边框线' })
              .border({
                color: Color.Blue,
                width: 1,
                radius: 0,
                style: BorderStyle.Solid
              })
          }
          .width('95%')
          .border({
            color: Color.Black,
            width: 1,
            radius: 0,
            style: BorderStyle.Solid
          })

        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：TextInput 未指定输入框高度时，textInput高度按照默认高度').fontColor(Color.Blue)
          Text('pass条件：两个输入框高度一致 \n')
          Row() {
            TextInput({ placeholder: '未指定输入框高度' })
              .border({
                color: Color.Red,
                width: 1,
                radius: 0,
                style: BorderStyle.Solid
              })
              .width('50%')
            TextInput({ placeholder: '设置了 height("40vp")' })
              .height('40vp')
              .border({
                color: Color.Black,
                width: 1,
                radius: 0,
                style: BorderStyle.Solid
              })
              .width('50%')
          }
        }

        Column({ space: 5 }) {
          Text('规格：TextInput 默认padding，left 16vp, right 16vp, top 8vp, button 8vp').fontColor(Color.Blue)
          Text('pass条件：两个输入框大小一致 \n')

          Row() {
            TextInput({ placeholder: '默认' })
              .border({
                color: Color.Red,
                width: 1,
                radius: 0,
                style: BorderStyle.Solid
              })
          }
          .width('50%')
          .border({
            color: Color.Red,
            width: 1,
            radius: 0,
            style: BorderStyle.Solid
          })

          Row() {
            TextInput({ placeholder: '设置了padding' })
              .padding({
                left: '16vp',
                right: '16vp',
                top: '8vp',
                bottom: '8vp'
              })
              .border({
                color: Color.Red,
                width: 1,
                radius: 0,
                style: BorderStyle.Solid
              })
          }
          .width('50%')
          .border({
            color: Color.Red,
            width: 1,
            radius: 0,
            style: BorderStyle.Solid
          })

        }

      }
    }
    .height('100%')
    .width('100%')
  }
}