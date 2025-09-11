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
struct HtmlSpanStringDemo {
  @State html: string =
    '<p>This is <b>b</b> <strong>strong</strong> <em>em</em> <i>i</i> <u>u</u> <del>del</del> <s>s</s> <span style =   "foreground-color:blue"> <a href=\'https://www.example.com\'>www.example</a> </span> <span   style="background-color: red;">red span</span> <sup>superscript</sup> and <sub>subscript</sub></p>';
  @State spanString: StyledString | undefined = undefined;
  @State resultText: string = ''; // 保存结果文本的状态
  controller: TextController = new TextController;

  build() {
    Column() {
      // 显示转换后的spanString
      Text(undefined, { controller: this.controller }).height(100)

      // TextArea显示每个步骤的结果
      TextArea({ text: this.html })
        .width('100%')
        .height(100)
        .margin(5)

      // 按钮1:将HTML转换为SpanString
      Button('Converted HTML to SpanString').onClick(async () => {
        this.spanString = await StyledString.fromHtml(this.html);
        this.controller.setStyledString(this.spanString);
        this.resultText = 'Converted HTML to SpanString successfully.';
      }).margin(5)

      // 按钮2:将SpanString转换为HTML
      Button('Converted SpanString to HTML').onClick(() => {
        if (this.spanString) {
          // 将spanString转换为HTML并替换当前的HTML状态
          const newHtml = StyledString.toHtml(this.spanString);
          if (newHtml !== this.html) { // 通过检查内容是否已经相同来防止重复
            this.html = newHtml;
          }
          this.resultText = 'Converted SpanString to HTML successfully.';
        } else {
          this.resultText = 'SpanString is undefined.';
        }
      }).margin(5)

      // 按钮3:将HTML转换回SpanString
      Button('Converted HTML back to SpanString').onClick(async () => {
        this.spanString = await StyledString.fromHtml(this.html);
        this.controller.setStyledString(this.spanString);
        this.resultText = 'Converted HTML back to SpanString successfully.';
      }).margin(5)

      // 重置：重置HTML和SpanString
      Button('Reset').onClick(() => {
        this.html =
          '<p>This is <b>b</b> <strong>strong</strong> <em>em</em> <i>i</i> <u>u</u> <del>del</del> <s>s</s> <span   style = "foreground-color:blue"> <a href=\'https://www.example.com\'>www.example</a> </span> <span   style="background-color: red;">red span</span> <sup>superscript</sup> and <sub>subscript</sub></p>';
        this.spanString = undefined;
        this.controller.setStyledString(new StyledString('')); // 使用空的StyledString实例
        this.resultText = 'Reset HTML and SpanString successfully.';
      }).margin(5)
    }.width('100%').padding(20)
  }
}