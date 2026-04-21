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

// 定义 autoHalfFold 的 Modifier 类
@Observed
class AutoHalfFoldModifier implements AttributeModifier<FolderStackAttribute> {
  private autoHalfFoldValue: boolean | undefined | null;
  constructor(value: boolean | undefined | null ) {
    this.autoHalfFoldValue = value;
  }
  applyNormalAttribute(instance: FolderStackAttribute): void {
    instance.autoHalfFold(this.autoHalfFoldValue);
  }
}

@Entry
@Component
struct FolderStackExample3 {
  @State private AutoHalfFoldModifier1: AutoHalfFoldModifier = new AutoHalfFoldModifier(true);
  @State private AutoHalfFoldModifier2: AutoHalfFoldModifier = new AutoHalfFoldModifier(false);
  @State private AutoHalfFoldModifier3: AutoHalfFoldModifier = new AutoHalfFoldModifier(undefined);
  @State private AutoHalfFoldModifier4: AutoHalfFoldModifier = new AutoHalfFoldModifier(null);

  @Builder
  private AutoHalfFoldWithExample(autoHalfFold: boolean | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      FolderStack({ upperItems: ['upperitemsId3'] }) {
        Column() {
          Text('video zone').height('100%').width('100%').textAlign(TextAlign.Center).fontSize(25)
        }.backgroundColor('rgb(0, 74, 175)').width('100%').height('100%').id('upperitemsId3')

        Column() {
          Text('video title')
            .width('100%')
            .height(50)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(25)
        }.width('100%').height('100%').justifyContent(FlexAlign.Start)

        Column() {
          Text('video bar')
            .width('100%')
            .height(50)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(25)
        }.width('100%').height('100%').justifyContent(FlexAlign.End)
      }
      .backgroundColor('rgb(39, 135, 217)')
      .autoHalfFold(autoHalfFold)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  private AutoHalfFoldModifierWithExample(modifier: AttributeModifier<FolderStackAttribute>, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      FolderStack({ upperItems: ['upperitemsId33'] }) {
        Column() {
          Text('video zone').height('100%').width('100%').textAlign(TextAlign.Center).fontSize(25)
        }.backgroundColor('rgb(0, 74, 175)').width('100%').height('100%').id('upperitemsId33')

        Column() {
          Text('video title')
            .width('100%')
            .height(50)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(25)
        }.width('100%').height('100%').justifyContent(FlexAlign.Start)

        Column() {
          Text('video bar')
            .width('100%')
            .height(50)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(25)
        }.width('100%').height('100%').justifyContent(FlexAlign.End)
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
        Text('autoHalfFold 设置是否开启自动旋转')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.AutoHalfFoldWithExample(true, 'autoHalfFold: true')
        this.AutoHalfFoldWithExample(false, 'autoHalfFold: false')
        this.AutoHalfFoldWithExample(undefined, 'autoHalfFold: undefined')
        this.AutoHalfFoldWithExample(null, 'autoHalfFold: null')

        Text('autoHalfFold Modifier 设置是否开启自动旋转')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.AutoHalfFoldModifierWithExample(this.AutoHalfFoldModifier1, 'autoHalfFold: true')
        this.AutoHalfFoldModifierWithExample(this.AutoHalfFoldModifier2, 'autoHalfFold: false')
        this.AutoHalfFoldModifierWithExample(this.AutoHalfFoldModifier3, 'autoHalfFold: undefined')
        this.AutoHalfFoldModifierWithExample(this.AutoHalfFoldModifier4, 'autoHalfFold: null')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}