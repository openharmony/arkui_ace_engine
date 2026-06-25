'use static'

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import {
  Component,
  Column,
  ColumnOptions,
  Row,
  RowOptions,
  Text,
  Blank,
  Button,
  ButtonOptions,
  ButtonType,
  ButtonStyleMode,
  SymbolGlyph,
  BuilderParam,
  Builder,
  PropRef,
  Require,
  $r,
  Resource,
  ResourceStr,
  HorizontalAlign,
  VerticalAlign,
  TextOverflow
} from '@kit.ArkUI'

@Component
export struct CompletedRoutableCard {
  @PropRef
  symbol: Resource = $r('sys.symbol.label');
  @PropRef
  @Require
  title: string;
  @PropRef
  description?: ResourceStr;

  build(): void {
    Card({ verticalAlign: VerticalAlign.Top }) {
      Button({ type: ButtonType.Circle }) {
        SymbolGlyph(this.symbol)
          .fontColor(['#fff'])
          .fontSize(16)
      }
      .borderRadius(14)

      Column({ space: 8 } as ColumnOptions) {
        Text(this.title)
          .fontColor($r('sys.color.font_primary'))

        if (this.description) {
          Text(this.description)
            .fontColor($r('sys.color.font_secondary'))
            .fontSize($r('sys.float.Body_S'))
        }
      }
      .alignItems(HorizontalAlign.Start)
      .layoutWeight(1)
    }
  }
}

@Component
export struct Card {
  @PropRef
  verticalAlign: VerticalAlign = VerticalAlign.Center;
  @BuilderParam
  content: () => void;

  build(): void {
    Row({ space: 12 } as RowOptions) {
      this.content()
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
  @PropRef
  icon: Resource = $r('sys.symbol.label');
  @PropRef
  @Require
  title: ResourceStr;

  build(): void {
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

      Button({ type: ButtonType.Normal, buttonStyle: ButtonStyleMode.TEXTUAL } as ButtonOptions) {
        SymbolGlyph($r('sys.symbol.chevron_right'))
          .fontSize(18)
          .fontColor([$r('sys.color.font_secondary')])
      }
    }
  }
}

@Component
export struct ComponentCard {
  @PropRef
  title?: ResourceStr;
  @BuilderParam content: () => void;
  @PropRef
  description?: ResourceStr;

  build(): void {
    Column({ space: 8 } as ColumnOptions) {
      if (this.title) {
        Text(this.title)
          .fontSize(14)
          .fontColor('#666')
      }
      Row({ space: 12 } as RowOptions) {
        this.content();
      }

      if (this.description) {
        Text(this.description)
          .backgroundColor('#eee')
          .borderRadius(4)
          .padding(4)
          .fontSize(12)
          .fontColor('#999')
          .width('100%')
      }
    }
    .alignItems(HorizontalAlign.Start)
    .backgroundColor('#fff')
    .borderRadius(12)
    .padding(12)
    .width('100%')
  }
}