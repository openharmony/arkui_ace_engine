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

@Component
export struct CompletedRoutableCard {
  @Prop
  symbol: Resource = $r('sys.symbol.label');
  @Prop
  @Require
  title: string;
  @Prop
  @Require
  description: string;

  build() {
    Card({ verticalAlign: VerticalAlign.Top }) {
      Button({ type: ButtonType.Circle }) {
        SymbolGlyph(this.symbol)
          .fontColor(['#fff'])
          .fontSize(16)
      }
      .borderRadius(14)

      Column({ space: 8 }) {
        Text(this.title)
          .fontColor($r('sys.color.font_primary'))

        Text(this.description)
          .fontColor($r('sys.color.font_secondary'))
          .fontSize($r('sys.float.Body_S'))
      }
      .alignItems(HorizontalAlign.Start)
      .layoutWeight(1)
    }
  }
}

@Component
export struct Card {
  @Prop
  verticalAlign: VerticalAlign = VerticalAlign.Center;
  @BuilderParam
  content: () => void;

  build() {
    Row({ space: 12 }) {
      this.content();
    }
    .alignItems(this.verticalAlign)
    .backgroundColor('#fff')
    .borderRadius(12)
    .padding(12)
    .width('100%')
  }
}

@Component
export struct RoutableCard {
  @Prop
  icon: Resource = $r('sys.symbol.label');
  @Prop
  @Require
  title: ResourceStr;

  build() {
    Card() {
      Button({ type: ButtonType.Circle }) {
        SymbolGlyph(this.icon)
          .fontColor(['#fff'])
          .fontSize(16)
      }
      .borderRadius(14)

      Text(this.title)
        .fontColor($r('sys.color.font_primary'))
        .minFontSize(12)
        .maxFontSize(16)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })

      Blank()

      Button({ type: ButtonType.Normal, buttonStyle: ButtonStyleMode.TEXTUAL }) {
        SymbolGlyph($r('sys.symbol.chevron_right'))
          .fontSize(18)
          .fontColor([$r('sys.color.font_secondary')])
      }
    }
  }
}