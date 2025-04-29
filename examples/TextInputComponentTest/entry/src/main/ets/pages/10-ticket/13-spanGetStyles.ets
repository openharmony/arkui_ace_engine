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

class AtSpan extends UserDataSpan {
  constructor(name: string, age: number) {
    super()
    this.name = name
    this.age = age
  }

  public name: string
  public age: number
}

@Entry
@Component
struct SpanGetStylesPages {
  controller: TextController = new TextController()
  @State text: string = '占位占位占位'
  styleString: MutableStyledString = new MutableStyledString('styleString', [{
    start: 0,
    length: 2,
    styledKey: StyledStringKey.USER_DATA,
    styledValue: new AtSpan('Alice', 30)
  }, {
    start: 0,
    length: 2,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])

  build() {
    Scroll() {
      Column({ space: 20 }) {

        Column() {
          Text('操作步骤：').fontColor(Color.Black)
          Text('1、点击get an span').fontColor(Color.Black)
          Text('2、点击replace string').fontColor(Color.Black)
          Text('3、点击get an span').fontColor(Color.Black)
          Text('Pass条件：步骤三之后，显示length = xx').fontColor(Color.Red)

          Text(undefined, { controller: this.controller })
          Button('get an span')
            .onClick(() => {
              let arr = this.styleString.getStyles(0, this.styleString.length)
              this.text = 'length = ' + arr.length
            })

          Button('replace string')
            .onClick(() => {
              this.styleString.replaceString(1, 6, '已经替换==')
              this.controller.setStyledString(this.styleString)
              this.text = 'replace string'
            })

          Text(this.text)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('95%')

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)

      }.width('100%')
    }
  }
}