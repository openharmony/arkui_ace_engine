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
struct Index {
  @State value1: string = ''
  @State text1: string = '离离原上草，一岁一枯荣。野火烧不尽，春风吹又生。远芳侵古道，晴翠接荒城。 又送王孙去，萋萋满别情。'
  @State text2: string = 'OpenHarmony'
  textInputcontroller1: TextInputController = new TextInputController()
  textInputcontroller2: TextInputController = new TextInputController()
  textAreacontroller1: TextAreaController = new TextAreaController()
  textAreacontroller2: TextAreaController = new TextAreaController()
  searchController1: SearchController = new SearchController()
  searchController2: SearchController = new SearchController()
  aboutToAppear() {
    setTimeout(() => {
      this.textInputcontroller1.setTextSelection(5, 10);
    }, 10);
  }

  build() {
    Scroll() {
      Column() {
        Text('该示例实现了TextInput组件监听onWillChange和onChange的用法')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Text('该示例同时监听了onWillInsert、onWillDelete、onDidInsert、onDidDelete以便观察回调顺序')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        TextInput({ text: this.text1, placeholder: '设置showError', controller: this.textInputcontroller1 })
          .margin({ top: 10, bottom: 30 })
          .defaultFocus(true)
          .cancelButton({ style: CancelButtonStyle.CONSTANT })
          .onWillInsert(
            (info: InsertValue) => {
              console.log('onWillInsert Triggered:' + info.insertValue);
              return true;
            }
          )

          .onWillDelete(
            (info: DeleteValue) => {
              console.log('onWillDelete Triggered:' + info.deleteValue);
              return true;
            }
          )

          .onDidInsert((info: InsertValue) => {
            console.log('onDidInsert Triggered:' + info.insertValue);
          })

          .onDidDelete((info: DeleteValue) => {
            console.log('onDidDelete Triggered:' + info.deleteValue);
          })

          .onChange((value: string, previewText?: PreviewText, options?: TextChangeOptions) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onChange Triggered:' + value);
            console.log('onChange old content:' + options?.oldContent);
            console.log('onChange new ontent:' + value);
            console.log('onChange old previewText value:' + options?.oldPreviewText?.value);
            console.log('onChange old previewText offset:' + options?.oldPreviewText?.offset);
            console.log('onChange new previewText value:' + previewText?.value);
            console.log('onChange new previewText offset:' + previewText?.offset);
            console.log('onChange rangeBefore:' + options?.rangeBefore.start + '   ' + options?.rangeBefore.end);
            console.log('onChange rangeAfter:' + options?.rangeAfter.start + '   ' + options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
          })

          .onWillChange((value: EditableTextChangeValue) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onWillChange Triggered');
            console.log('onWillChange old content:' + value.options?.oldContent);
            console.log('onWillChange new content:' + value.content);
            console.log('onWillChange new content length:' + value.content.length);
            console.log('onWillChange old previewText value:' + value.options?.oldPreviewText?.value);
            console.log('onWillChange old previewText offset:' + value.options?.oldPreviewText?.offset);
            console.log('onWillChange new previewText value:' + value.previewText?.value);
            console.log('onWillChange new previewText offset:' + value.previewText?.offset);
            console.log('onWillChange rangeBefore:' + value.options?.rangeBefore.start + '   ' + value.options?.rangeBefore.end);
            console.log('onWillChange rangeAfter:' + value.options?.rangeAfter.start + '   ' + value.options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            return true;
          })

        Text('该示例实现了TextArea组件监听onWillChange和onChange的用法')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Text('该示例同时监听了onWillInsert、onWillDelete、onDidInsert、onDidDelete以便观察回调顺序')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        TextArea({
          text: this.text1,
          controller: this.textAreacontroller1
        })
          .margin({ top: 10, bottom: 30 })

          .onWillInsert(
            (info: InsertValue) => {
              console.log('onWillInsert Triggered:' + info.insertValue);
              return true;
            }
          )

          .onWillDelete(
            (info: DeleteValue) => {
              console.log('onWillDelete Triggered:' + info.deleteValue);
              return true;
            }
          )

          .onDidInsert((info: InsertValue) => {
            console.log('onDidInsert Triggered:' + info.insertValue);
          })

          .onDidDelete((info: DeleteValue) => {
            console.log('onDidDelete Triggered:' + info.deleteValue);
          })

          .onChange((value: string, previewText?: PreviewText, options?: TextChangeOptions) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onChange Triggered:' + value);
            console.log('onChange old content:' + options?.oldContent);
            console.log('onChange new ontent:' + value);
            console.log('onChange old previewText value:' + options?.oldPreviewText?.value);
            console.log('onChange old previewText offset:' + options?.oldPreviewText?.offset);
            console.log('onChange new previewText value:' + previewText?.value);
            console.log('onChange new previewText offset:' + previewText?.offset);
            console.log('onChange rangeBefore:' + options?.rangeBefore.start + '   ' + options?.rangeBefore.end);
            console.log('onChange rangeAfter:' + options?.rangeAfter.start + '   ' + options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
          })
          .onWillChange((value: EditableTextChangeValue) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onWillChange Triggered');
            console.log('onWillChange old content:' + value.options?.oldContent);
            console.log('onWillChange new content:' + value.content);
            console.log('onWillChange new content length:' + value.content.length);
            console.log('onWillChange old previewText value:' + value.options?.oldPreviewText?.value);
            console.log('onWillChange old previewText offset:' + value.options?.oldPreviewText?.offset);
            console.log('onWillChange new previewText value:' + value.previewText?.value);
            console.log('onWillChange new previewText offset:' + value.previewText?.offset);
            console.log('onWillChange rangeBefore:' + value.options?.rangeBefore.start + '   ' + value.options?.rangeBefore.end);
            console.log('onWillChange rangeAfter:' + value.options?.rangeAfter.start + '   ' + value.options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            return true;
          })

        Text('该示例实现了Search组件监听onWillChange和onChange的用法')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Text('该示例同时监听了onWillInsert、onWillDelete、onDidInsert、onDidDelete以便观察回调顺序')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Search({ value: this.text1, controller: this.searchController1 })
          .margin({ top: 10, bottom: 30 })
          .onWillInsert(
            (info: InsertValue) => {
              console.log('onWillInsert Triggered:' + info.insertValue);
              return true;
            }
          )

          .onWillDelete(
            (info: DeleteValue) => {
              console.log('onWillDelete Triggered:' + info.deleteValue);
              return true;
            }
          )

          .onDidInsert((info: InsertValue) => {
            console.log('onDidInsert Triggered:' + info.insertValue);
          })

          .onDidDelete((info: DeleteValue) => {
            console.log('onDidDelete Triggered:' + info.deleteValue);
          })

          .onWillChange((value: EditableTextChangeValue) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onWillChange Triggered');
            console.log('onWillChange old content:' + value.options?.oldContent);
            console.log('onWillChange new content:' + value.content);
            console.log('onWillChange new content length:' + value.content.length);
            console.log('onWillChange old previewText value:' + value.options?.oldPreviewText?.value);
            console.log('onWillChange old previewText offset:' + value.options?.oldPreviewText?.offset);
            console.log('onWillChange new previewText value:' + value.previewText?.value);
            console.log('onWillChange new previewText offset:' + value.previewText?.offset);
            console.log('onWillChange rangeBefore:' + value.options?.rangeBefore.start + '   ' + value.options?.rangeBefore.end);
            console.log('onWillChange rangeAfter:' + value.options?.rangeAfter.start + '   ' + value.options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            return true;
          })
          .onChange((value: string, previewText?: PreviewText, options?: TextChangeOptions) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onChange Triggered:' + value);
            console.log('onChange old content:' + options?.oldContent);
            console.log('onChange new ontent:' + value);
            console.log('onChange old previewText value:' + options?.oldPreviewText?.value);
            console.log('onChange old previewText offset:' + options?.oldPreviewText?.offset);
            console.log('onChange new previewText value:' + previewText?.value);
            console.log('onChange new previewText offset:' + previewText?.offset);
            console.log('onChange rangeBefore:' + options?.rangeBefore.start + '   ' + options?.rangeBefore.end);
            console.log('onChange rangeAfter:' + options?.rangeAfter.start + '   ' + options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
          })

        Text('该示例实现了TextInput组件使用OnWillChange来拦截输入的功能')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Text('该示例同时监听了onWillInsert、onWillDelete、onDidInsert、onDidDelete以便观察上屏被拦截后的回调顺序')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        TextInput({ text: this.text2, controller: this.textInputcontroller2 })
          .margin({ top: 10, bottom: 30 })
          .cancelButton({ style: CancelButtonStyle.CONSTANT })
          .onWillInsert(
            (info: InsertValue) => {
              console.log('onWillInsert Triggered:' + info.insertValue);
              return true;
            }
          )

          .onWillDelete(
            (info: DeleteValue) => {
              console.log('onWillDelete Triggered:' + info.deleteValue);
              return true;
            }
          )

          .onDidInsert((info: InsertValue) => {
            console.log('onDidInsert Triggered:' + info.insertValue);
          })

          .onDidDelete((info: DeleteValue) => {
            console.log('onDidDelete Triggered:' + info.deleteValue);
          })

          .onChange((value: string, previewText?: PreviewText, options?: TextChangeOptions) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onChange Triggered:' + value);
            console.log('onChange old content:' + options?.oldContent);
            console.log('onChange new ontent:' + value);
            console.log('onChange old previewText value:' + options?.oldPreviewText?.value);
            console.log('onChange old previewText offset:' + options?.oldPreviewText?.offset);
            console.log('onChange new previewText value:' + previewText?.value);
            console.log('onChange new previewText offset:' + previewText?.offset);
            console.log('onChange rangeBefore:' + options?.rangeBefore.start + '   ' + options?.rangeBefore.end);
            console.log('onChange rangeAfter:' + options?.rangeAfter.start + '   ' + options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
          })

          .onWillChange((value: EditableTextChangeValue) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onWillChange Triggered');
            console.log('onWillChange old content:' + value.options?.oldContent);
            console.log('onWillChange new content:' + value.content);
            console.log('onWillChange new content length:' + value.content.length);
            console.log('onWillChange old previewText value:' + value.options?.oldPreviewText?.value);
            console.log('onWillChange old previewText offset:' + value.options?.oldPreviewText?.offset);
            console.log('onWillChange new previewText value:' + value.previewText?.value);
            console.log('onWillChange new previewText offset:' + value.previewText?.offset);
            console.log('onWillChange rangeBefore:' + value.options?.rangeBefore.start + '   ' + value.options?.rangeBefore.end);
            console.log('onWillChange rangeAfter:' + value.options?.rangeAfter.start + '   ' + value.options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            return false;
          })

        Text('该示例实现了TextArea组件使用OnWillChange来拦截输入的功能')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Text('该示例同时监听了onWillInsert、onWillDelete、onDidInsert、onDidDelete以便观察上屏被拦截后的回调顺序')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        TextArea({
          text: this.text2,
          controller: this.textAreacontroller2
        })
          .margin({ top: 10, bottom: 30 })

          .onWillInsert(
            (info: InsertValue) => {
              console.log('onWillInsert Triggered:' + info.insertValue);
              return true;
            }
          )

          .onWillDelete(
            (info: DeleteValue) => {
              console.log('onWillDelete Triggered:' + info.deleteValue);
              return true;
            }
          )

          .onDidInsert((info: InsertValue) => {
            console.log('onDidInsert Triggered:' + info.insertValue);
          })

          .onDidDelete((info: DeleteValue) => {
            console.log('onDidDelete Triggered:' + info.deleteValue);
          })

          .onChange((value: string, previewText?: PreviewText, options?: TextChangeOptions) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onChange Triggered:' + value);
            console.log('onChange old content:' + options?.oldContent);
            console.log('onChange new ontent:' + value);
            console.log('onChange old previewText value:' + options?.oldPreviewText?.value);
            console.log('onChange old previewText offset:' + options?.oldPreviewText?.offset);
            console.log('onChange new previewText value:' + previewText?.value);
            console.log('onChange new previewText offset:' + previewText?.offset);
            console.log('onChange rangeBefore:' + options?.rangeBefore.start + '   ' + options?.rangeBefore.end);
            console.log('onChange rangeAfter:' + options?.rangeAfter.start + '   ' + options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
          })
          .onWillChange((value: EditableTextChangeValue) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onWillChange Triggered');
            console.log('onWillChange old content:' + value.options?.oldContent);
            console.log('onWillChange new content:' + value.content);
            console.log('onWillChange new content length:' + value.content.length);
            console.log('onWillChange old previewText value:' + value.options?.oldPreviewText?.value);
            console.log('onWillChange old previewText offset:' + value.options?.oldPreviewText?.offset);
            console.log('onWillChange new previewText value:' + value.previewText?.value);
            console.log('onWillChange new previewText offset:' + value.previewText?.offset);
            console.log('onWillChange rangeBefore:' + value.options?.rangeBefore.start + '   ' + value.options?.rangeBefore.end);
            console.log('onWillChange rangeAfter:' + value.options?.rangeAfter.start + '   ' + value.options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            return false;
          })


        Text('该示例实现了Search组件使用OnWillChange来拦截输入的功能')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Text('该示例同时监听了onWillInsert、onWillDelete、onDidInsert、onDidDelete以便观察上屏被拦截后的回调顺序')
          .margin({ top: 10, bottom: 10 })
          .fontColor(Color.Blue)
        Search({ value: this.text2, controller: this.searchController2 })
          .margin({ top: 10, bottom: 30 })
          .onWillInsert(
            (info: InsertValue) => {
              console.log('onWillInsert Triggered:' + info.insertValue);
              return true;
            }
          )

          .onWillDelete(
            (info: DeleteValue) => {
              console.log('onWillDelete Triggered:' + info.deleteValue);
              return true;
            }
          )

          .onDidInsert((info: InsertValue) => {
            console.log('onDidInsert Triggered:' + info.insertValue);
          })

          .onDidDelete((info: DeleteValue) => {
            console.log('onDidDelete Triggered:' + info.deleteValue);
          })

          .onWillChange((value: EditableTextChangeValue) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onWillChange Triggered');
            console.log('onWillChange old content:' + value.options?.oldContent);
            console.log('onWillChange new content:' + value.content);
            console.log('onWillChange new content length:' + value.content.length);
            console.log('onWillChange old previewText value:' + value.options?.oldPreviewText?.value);
            console.log('onWillChange old previewText offset:' + value.options?.oldPreviewText?.offset);
            console.log('onWillChange new previewText value:' + value.previewText?.value);
            console.log('onWillChange new previewText offset:' + value.previewText?.offset);
            console.log('onWillChange rangeBefore:' + value.options?.rangeBefore.start + '   ' + value.options?.rangeBefore.end);
            console.log('onWillChange rangeAfter:' + value.options?.rangeAfter.start + '   ' + value.options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            return false;
          })
          .onChange((value: string, previewText?: PreviewText, options?: TextChangeOptions) => {
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
            console.log('onChange Triggered:' + value);
            console.log('onChange old content:' + options?.oldContent);
            console.log('onChange new ontent:' + value);
            console.log('onChange old previewText value:' + options?.oldPreviewText?.value);
            console.log('onChange old previewText offset:' + options?.oldPreviewText?.offset);
            console.log('onChange new previewText value:' + previewText?.value);
            console.log('onChange new previewText offset:' + previewText?.offset);
            console.log('onChange rangeBefore:' + options?.rangeBefore.start + '   ' + options?.rangeBefore.end);
            console.log('onChange rangeAfter:' + options?.rangeAfter.start + '   ' + options?.rangeAfter.end);
            console.log('+++++++++++++++++++++++++++++++++++++++++++++++++++++++');
          })

      }
      .width(400)
        .height('auto')
    }
    .height('100%')
  }

}