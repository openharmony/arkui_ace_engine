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
export function SelectMenuOutlineBuilder(name: string, param: Object) {
  SelectMenuOutline()
}

@Entry
@Component
struct SelectMenuOutline {
  pathStack: NavPathStack = new NavPathStack()
  @State private selectOutlineWidthIndex: number = 0;
  @State private selectOutlineColorIndex: number = 0;
  @State private text: string = 'SelectTest';
  @State private index: number = 2;
  private outlineWidthArr: (Dimension | EdgeOutlineWidths | undefined) [] =
    ['1vp', '3vp', '1px', '3px', undefined];
  private outlineColorArr: (ResourceColor | EdgeColors | undefined)[] =
    [Color.Transparent, Color.Red, undefined];
  private arrowPosition: ArrowPosition = ArrowPosition.END;
  private space: number = 8;

  @Builder
  testComponent() {
    Column({ space: 20 }) {
      Select([{ value: 'aaa', icon: $r("app.media.startIcon") },
        { value: 'bbb', icon: $r("app.media.startIcon") },
        { value: 'ccc', icon: $r("app.media.startIcon") },
        { value: 'ddd', icon: $r("app.media.startIcon") }])
        .selected(this.index)
        .value(this.text)
        .font({ size: 16, weight: 500 })
        .fontColor($r('sys.color.font_primary'))
        .selectedOptionFont({ size: 16, weight: 400 })
        .optionFont({ size: 16, weight: 400 })
        .space(this.space)
        .arrowPosition(this.arrowPosition)
        .menuAlign(MenuAlignType.START, { dx: 0, dy: 0 })
        .optionWidth(200)
        .optionHeight(300)
        .onSelect((index: number, text: string) => {
          this.index = index;
          if (text) {
            this.text = text;
          }
        })
        .menuOutline({
          width: this.outlineWidthArr[this.selectOutlineWidthIndex],
          color: this.outlineColorArr[this.selectOutlineColorIndex]
        })
    }
  }

  private updateIndex(index: number, length: number): number {
    let tmp: number = (index + 1) % length;
    return tmp;
  }

  @Builder
  operateButton() {
    Column({ space: 10 }) {
      Button(`updateSelectOutlineColor: ${this.outlineColorArr[this.selectOutlineColorIndex]}`)
        .width('100%')
        .onClick(() => {
          this.selectOutlineColorIndex = this.updateIndex(this.selectOutlineColorIndex, this.outlineColorArr.length);
        })
      Button(`updateSelectOutlineWidth: ${this.outlineWidthArr[this.selectOutlineWidthIndex]}`)
        .width('100%')
        .onClick(() => {
          this.selectOutlineWidthIndex = this.updateIndex(this.selectOutlineWidthIndex, this.outlineWidthArr.length);
        })
    }
    .margin({
      top: $r('sys.float.padding_level36')
    })
  }

  build() {
    NavDestination() {
      Column() {
        this.testComponent()
        this.operateButton()
      }
    }
    .title('SelectMenuOutline')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}