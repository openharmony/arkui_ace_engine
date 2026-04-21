/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// 定义 alignContent 的 Modifier 类
@Observed
class AlignContentModifier implements AttributeModifier<FolderStackAttribute> {
  private alignContentValue: Alignment | undefined | null;
  constructor(value: Alignment | undefined | null) {
    this.alignContentValue = value;
  }
  applyNormalAttribute(instance: FolderStackAttribute): void {
    instance.alignContent(this.alignContentValue);
  }
}

@Entry
@Component
struct FolderStackExample1 {
  @State private AlignContentModifier1: AlignContentModifier = new AlignContentModifier(Alignment.TopStart);
  @State private AlignContentModifier2: AlignContentModifier = new AlignContentModifier(Alignment.Top);
  @State private AlignContentModifier3: AlignContentModifier = new AlignContentModifier(Alignment.TopEnd);
  @State private AlignContentModifier4: AlignContentModifier = new AlignContentModifier(Alignment.Start);
  @State private AlignContentModifier5: AlignContentModifier = new AlignContentModifier(Alignment.Center);
  @State private AlignContentModifier6: AlignContentModifier = new AlignContentModifier(Alignment.End);
  @State private AlignContentModifier7: AlignContentModifier = new AlignContentModifier(Alignment.BottomStart);
  @State private AlignContentModifier8: AlignContentModifier = new AlignContentModifier(Alignment.Bottom);
  @State private AlignContentModifier9: AlignContentModifier = new AlignContentModifier(Alignment.BottomEnd);
  @State private AlignContentModifier10: AlignContentModifier = new AlignContentModifier(undefined);
  @State private AlignContentModifier11: AlignContentModifier = new AlignContentModifier(null);
  @Builder
  private AlignContentWithExample(alignContent: Alignment | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      FolderStack({ upperItems: ['upperitemsId1'] }) {
        Column() {
          Text('video zone').height(100).width(100).textAlign(TextAlign.Center).fontSize(25)
        }.backgroundColor('rgb(0, 74, 175)').id('upperitemsId1')

        Column() {
          Text('video title')
            .width('100%')
            .height(20)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(15)
        }
      }
      .backgroundColor('rgb(39, 135, 217)')
      .alignContent(alignContent)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  private AlignContentModifierWithExample(modifier: AttributeModifier<FolderStackAttribute>, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      FolderStack({ upperItems: ['upperitemsId11'] }) {
        Column() {
          Text('video zone').height(100).width(100).textAlign(TextAlign.Center).fontSize(25)
        }.backgroundColor('rgb(0, 74, 175)').id('upperitemsId11')

        Column() {
          Text('video title')
            .width('100%')
            .height(20)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(15)
        }
      }
      .backgroundColor('rgb(39, 135, 217)')
      .attributeModifier(modifier)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column() {
        Text('alignContent 设置子组件在容器内的对齐方式')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.AlignContentWithExample(Alignment.TopStart, 'alignContent: TopStart')
        this.AlignContentWithExample(Alignment.Top, 'alignContent: Top')
        this.AlignContentWithExample(Alignment.TopEnd, 'alignContent: TopEnd')
        this.AlignContentWithExample(Alignment.Start, 'alignContent: Start')
        this.AlignContentWithExample(Alignment.Center, 'alignContent: Center')
        this.AlignContentWithExample(Alignment.End, 'alignContent: End')
        this.AlignContentWithExample(Alignment.BottomStart, 'alignContent: BottomStart')
        this.AlignContentWithExample(Alignment.Bottom, 'alignContent: Bottom')
        this.AlignContentWithExample(Alignment.BottomEnd, 'alignContent: BottomEnd')
        this.AlignContentWithExample(undefined, 'alignContent: undefined')
        this.AlignContentWithExample(null, 'alignContent: null')

        Text('alignContent Modifier 设置子组件在容器内的对齐方式')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.AlignContentModifierWithExample(this.AlignContentModifier1, 'TopStart')
        this.AlignContentModifierWithExample(this.AlignContentModifier2, 'Top')
        this.AlignContentModifierWithExample(this.AlignContentModifier3, 'TopEnd')
        this.AlignContentModifierWithExample(this.AlignContentModifier4, 'Start')
        this.AlignContentModifierWithExample(this.AlignContentModifier5, 'Center')
        this.AlignContentModifierWithExample(this.AlignContentModifier6, 'End')
        this.AlignContentModifierWithExample(this.AlignContentModifier7, 'TopStart')
        this.AlignContentModifierWithExample(this.AlignContentModifier8, 'TopStart')
        this.AlignContentModifierWithExample(this.AlignContentModifier9, 'TopStart')
        this.AlignContentModifierWithExample(this.AlignContentModifier10, 'undefined')
        this.AlignContentModifierWithExample(this.AlignContentModifier11, 'null')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}