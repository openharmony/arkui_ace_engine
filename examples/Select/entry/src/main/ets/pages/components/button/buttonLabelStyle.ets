/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
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

@Builder
export function ButtonLabelStyleBuilder(name: string, param: Object) {
  ButtonLabelStyleExample()
}

@Entry
@Component
struct ButtonLabelStyleExample {
  pathStack: NavPathStack = new NavPathStack()
  @State txt: string = 'overflowTextOverLengthTextOverflow.Clip';
  @State widthShortSize: number = 210;

  build() {
    NavDestination() {
      Row() {
        Column() {
          Button(this.txt)
            .width(this.widthShortSize)
            .height(100)
            .backgroundColor($r('app.color.background_color_6'))
            .labelStyle({
              overflow: TextOverflow.Clip,
              maxLines: 1,
              minFontSize: 20,
              maxFontSize: 20,
              font: {
                size: 20,
                weight: FontWeight.Bolder,
                family: 'cursive',
                style: FontStyle.Italic
              }
            })
            .fontSize(40)
        }
        .width('100%')
      }
      .height('100%')
    }
    .title('ButtonLabelStyle')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}