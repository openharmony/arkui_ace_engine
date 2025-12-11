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

import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct Index {
  controller: RichEditorController = new RichEditorController()
  private start: number = -1;
  private end: number = -1;
  @State message: string = '[-1, -1]';
  @State content: string = '';

  build() {
    Column() {
      RichEditor({ controller: this.controller })
        .width('100%')
        .height('50%')
        .borderWidth(2)
        .borderColor(Color.Black)
        .scrollBarColor(ColorMetrics.resourceColor('#2787D9'))
        .draggable(true)
        .onReady(() => {
          this.controller.addTextSpan('Hello World\n')
        })
        .onSelect((value: RichEditorSelection) => {
          this.start = value.selection[0];
          this.end = value.selection[1];
          this.message = '[' + this.start + ', ' + this.end + ']';
        })
        .aboutToIMEInput((value: RichEditorInsertValue) => {
          console.info('---------------------- aboutToIMEInput ----------------------');
          console.info('insertOffset:' + value.insertOffset);
          console.info('insertValue:' + value.insertValue);
          return true;
        })
        .onIMEInputComplete((value: RichEditorTextSpanResult) => {
          console.info('---------------------- onIMEInputComplete ---------------------');
          console.info('spanIndex:' + value.spanPosition.spanIndex);
          console.info('spanRange:[' + value.spanPosition.spanRange[0] + ',' + value.spanPosition.spanRange[1] + ']');
          console.info('offsetInSpan:[' + value.offsetInSpan[0] + ',' + value.offsetInSpan[1] + ']');
          console.info('value:' + value.value);
        })
        .aboutToDelete((value: RichEditorDeleteValue) => {
          console.info('---------------------- aboutToDelete --------------------------');
          console.info('offset:' + value.offset);
          console.info('direction:' + value.direction);
          console.info('length:' + value.length);
          value.richEditorDeleteSpans.forEach(item => {
            console.info('---------------------- item --------------------------');
            console.info('spanIndex:' + item.spanPosition.spanIndex);
            console.info('spanRange:[' + item.spanPosition.spanRange[0] + ',' + item.spanPosition.spanRange[1] + ']');
            console.info('offsetInSpan:[' + item.offsetInSpan[0] + ',' + item.offsetInSpan[1] + ']');
            if (typeof (item as RichEditorImageSpanResult)['imageStyle'] != 'undefined') {
              console.info('image:' + (item as RichEditorImageSpanResult).valueResourceStr);
            } else {
              console.info('text:' + (item as RichEditorTextSpanResult).value);
            }
          })
          return true;
        })
        .onDeleteComplete(() => {
          console.info('---------------------- onDeleteComplete ------------------------');
        })
        .placeholder('input...', {
          fontColor: Color.Gray,
          font: {
            size: 16,
            weight: FontWeight.Normal,
            family: 'HarmonyOS Sans',
            style: FontStyle.Normal
          }
        })
    }
    .height('100%')
    .width('100%')
  }
}