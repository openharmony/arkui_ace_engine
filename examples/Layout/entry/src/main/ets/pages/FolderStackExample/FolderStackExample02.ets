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

// 定义 enableAnimation 的 Modifier 类
@Observed
class EnableAnimationModifier implements AttributeModifier<FolderStackAttribute> {
  private enableAnimationValue: boolean | undefined | null;
  constructor(value: boolean | undefined | null ) {
    this.enableAnimationValue = value;
  }
  applyNormalAttribute(instance: FolderStackAttribute): void {
    instance.enableAnimation(this.enableAnimationValue);
  }
}

@Entry
@Component
struct FolderStackExample2 {
  @State private EnableAnimationModifier1: EnableAnimationModifier = new EnableAnimationModifier(true);
  @State private EnableAnimationModifier2: EnableAnimationModifier = new EnableAnimationModifier(false);
  @State private EnableAnimationModifier3: EnableAnimationModifier = new EnableAnimationModifier(undefined);
  @State private EnableAnimationModifier4: EnableAnimationModifier = new EnableAnimationModifier(null);

  @Builder
  private EnableAnimationWithExample(enableAnimation: boolean | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      FolderStack({ upperItems: ['upperitemsId22'] }) {
        Column() {
          Text('video zone').height('100%').width('100%').textAlign(TextAlign.Center).fontSize(25)
        }.backgroundColor('rgb(0, 74, 175)').width('100%').height('100%').id('upperitemsId22')

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
      .enableAnimation(enableAnimation)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  private EnableAnimationModifierWithExample(modifier: AttributeModifier<FolderStackAttribute>, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      FolderStack({ upperItems: ['upperitemsId2'] }) {
        Column() {
          Text('video zone').height('100%').width('100%').textAlign(TextAlign.Center).fontSize(25)
        }.backgroundColor('rgb(0, 74, 175)').width('100%').height('100%').id('upperitemsId2')

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
        Text('enableAnimation 设置是否使用默认动效')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.EnableAnimationWithExample(true, 'enableAnimation: true')
        this.EnableAnimationWithExample(false, 'enableAnimation: false')
        this.EnableAnimationWithExample(undefined, 'enableAnimation: undefined')
        this.EnableAnimationWithExample(null, 'enableAnimation: null')

        Text('enableAnimation Modifier 设置是否使用默认动效')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.EnableAnimationModifierWithExample(this.EnableAnimationModifier1, 'enableAnimation: true')
        this.EnableAnimationModifierWithExample(this.EnableAnimationModifier2, 'enableAnimation: false')
        this.EnableAnimationModifierWithExample(this.EnableAnimationModifier3, 'enableAnimation: undefined')
        this.EnableAnimationModifierWithExample(this.EnableAnimationModifier4, 'enableAnimation: null')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}