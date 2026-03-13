/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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
import Napi from 'libentry.so';
import { NodeContent } from '@kit.ArkUI';


@Extend(Text)
function style(textAlign: TextAlign) {
  .textAlign(textAlign)
  .fontSize(12)
  .border({ width: 1 })
  .padding(10)
  .width('100%')
}

@Entry
@Component
struct CheckboxTest {
  @State status: number = Visibility.Visible;
  @State nodeId: number = -1;
  @State nodeStatus: string = '';
  @State curNodeType: string = '';
  @State attributeType: string = '';
  @State attributeTypeId: number = -1;
  @State attributeValue: string = '-1';
  @State resultValue: string = '-1';
  @State curAttrStatus: number = 0;
  @State result: string = '...';
  private nodeContentDemo = new NodeContent();

  nativeCallback = (data: string) => {
    this.result = data;
  }

  aboutToAppear() {
    Napi.initCheckboxDemo(this.nodeContentDemo);
  }

  build() {
    Column() {
      Row() {
        Button($r('app.string.return_node'))
          .width(100)
          .height(30)
          .fontSize(15)
          .fontColor(Color.Black)
          .backgroundColor(Color.White)
          .borderColor(Color.Black)
          .borderWidth(3)
          .onClick(() => {
            this.getUIContext().getRouter().back();
          })
        Text($r('app.string.native_checkbox_example'))
          .fontSize(20)
          .height(30)
          .margin({left: 20})
          .fontWeight(FontWeight.Bold)
      }

      Column() {
        ContentSlot(this.nodeContentDemo)
      }
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .width('90%')
      .height('60%')
      .margin({ top: 30 })
      .border({ width: 1 })
    }.alignItems(HorizontalAlign.Center).width('100%').height('100%')
  }
}
