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

import {CommonModifier} from "@ohos.arkui.modifier"
// import { SearchModifier} from '@ohos.arkui.modifier';
// xxx.ets

class SearchModifier implements AttributeModifier<SearchAttribute> {
  fontSize: number = 16
  halfleading: (boolean | undefined | null)[] = [false , true, undefined, null];
  halfleadingStr: string[] = ['false' , 'true', 'undefined', 'null'];
  halfleadingIndex: number = 0
  lineheightTest: number = -1
  heightTest: number = 80
  applyNormalAttribute(instance: SearchAttribute): void {
    instance.width(280)
      .halfLeading(this.halfleading[this.halfleadingIndex])
      .height(this.heightTest)
      .minFontScale(0.8)
      .maxFontScale(32)
      .lineHeight(this.lineheightTest)


  }
}

class TextInputModifier implements AttributeModifier<TextInputAttribute> {
  fontSize: number = 16
  halfleading: (boolean | undefined | null)[] = [false , true, undefined, null];
  halfleadingStr: string[] = ['false' , 'true', 'undefined', 'null'];
  halfleadingIndex: number = 0
  lineheightTest: number = -1
  heightTest: number = 80
  applyNormalAttribute(instance: TextInputAttribute): void {
    instance.width(280).height(150)
      .halfLeading(this.halfleading[this.halfleadingIndex])
      .height(this.heightTest)
      .lineHeight(this.lineheightTest)
      .minFontScale(0)
      .maxFontScale(32)
  }
}
class TextAreaModifier implements AttributeModifier<TextAreaAttribute> {
  fontSize: number = 16
  halfleading: (boolean | undefined | null)[] = [false , true, undefined, null];
  halfleadingStr: string[] = ['false' , 'true', 'undefined', 'null'];
  halfleadingIndex: number = 0
  lineheightTest: number = -1
  heightTest: number = 80
  applyNormalAttribute(instance: TextAreaAttribute): void {
    instance.width(280).height(150)
      .halfLeading(this.halfleading[this.halfleadingIndex])
      .lineHeight(this.lineheightTest)
      .height(this.heightTest)
      .minFontScale(0)
      .maxFontScale(32)
      // .maxLines(1)
      // .ellipsisMode(EllipsisMode.CENTER)
      // .textOverflow(TextOverflow.Ellipsis)

  }
}
@Entry
@Component
struct attributeDemo {
  // @State modifier1 :SearchModifier = new SearchModifier().minFontScale(1).maxFontScale(1)
  @State SearchModifier: SearchModifier = new SearchModifier()
  @State TextAreaModifier: TextAreaModifier = new TextAreaModifier()
  @State TextInputModifier: TextInputModifier = new TextInputModifier()
  build() {

    Column() {

      Search({ placeholder: 'Search组件，请输入。。。' })
        // .attributeModifier(this.modifier1)
        .attributeModifier(this.SearchModifier)
        .margin(15)
        .borderWidth(1)
      TextInput({ placeholder: 'TextInput组件，请输入。。。' })
        .attributeModifier(this.TextInputModifier)
        .margin(15)
        .borderWidth(1)
      TextArea({ placeholder: 'TextArea组件，请输入。。。' })
        .attributeModifier(this.TextAreaModifier)
        .margin(15)
        .borderWidth(1)

      Column() {
        Row() {
          Button('Search行高+：' + this.SearchModifier.lineheightTest)
            .width('40%').fontSize('13vp')
            .onClick(() => {
              this.SearchModifier.lineheightTest += 10
            }).margin(2)

          Button('Search行高-：' + this.SearchModifier.lineheightTest)
            .width('40%')
            .fontSize('13vp')
            .onClick(() => {
              this.SearchModifier.lineheightTest -= 10
            }).margin(2)
        }
        Row() {
          Button('SearchHalfleading：' + this.SearchModifier.halfleadingStr[this.SearchModifier.halfleadingIndex]).onClick(() => {
            this.SearchModifier.halfleadingIndex ++
            if (this.SearchModifier.halfleadingIndex > (this.SearchModifier.halfleadingStr.length - 1)) {
              this.SearchModifier.halfleadingIndex = 0
            }
          }).width(150)


        }
        Row() {
          Button('TextInput行高+：' + this.TextInputModifier.lineheightTest)
            .width('40%').fontSize('13vp')
            .onClick(() => {
              this.TextInputModifier.lineheightTest += 10
            }).margin(2)

          Button('TextInput行高-：' + this.TextInputModifier.lineheightTest)
            .width('40%')
            .fontSize('13vp')
            .onClick(() => {
              this.TextInputModifier.lineheightTest -= 10
            }).margin(2)
        }
        Row() {
          Button('TextInputHalfleading:' + this.TextInputModifier.halfleadingStr[this.TextInputModifier.halfleadingIndex]).onClick(() => {
            this.TextInputModifier.halfleadingIndex ++
            if (this.TextInputModifier.halfleadingIndex > (this.TextInputModifier.halfleadingStr.length - 1)) {
              this.TextInputModifier.halfleadingIndex = 0
            }
          }).width(150)


        }
        Row() {
          Button('TextArea行高+：' + this.TextAreaModifier.lineheightTest)
            .width('40%').fontSize('13vp')
            .onClick(() => {
              this.TextAreaModifier.lineheightTest += 10
            }).margin(2)

          Button('TextArea行高-：' + this.TextAreaModifier.lineheightTest)
            .width('40%')
            .fontSize('13vp')
            .onClick(() => {
              this.TextAreaModifier.lineheightTest -= 10
            }).margin(2)
        }
        Row() {
          Button('TextAreaHalfleading:' + this.TextAreaModifier.halfleadingStr[this.TextAreaModifier.halfleadingIndex]).onClick(() => {
            this.TextAreaModifier.halfleadingIndex ++
            if (this.TextAreaModifier.halfleadingIndex > (this.TextAreaModifier.halfleadingStr.length - 1)) {
              this.TextAreaModifier.halfleadingIndex = 0
            }
          }).width(150)


        }

      }
      .height('100%').width('100%')

    }
  }
}
