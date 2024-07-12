/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
export struct ColorPalette {
  @Prop color: ResourceColor | undefined = undefined;
  @Prop colors: ResourceColor[] =
    ['#0A59F7', '#646AFD', '#FE7062', '#E9E8ED', '#1C1C1C', $r('sys.color.ohos_id_color_text_primary_contrary')];
  @Prop isEnabled: boolean = false;
  onChange?: (color: ResourceColor) => void;

  build() {
    Row({ space: 12 }) {
      ForEach(this.colors, (color: ResourceColor) => {
        Button() {
          Circle({ width: 24, height: 24 })
            .fill(color)
            .borderRadius(12)
            .shadow(ShadowStyle.OUTER_DEFAULT_XS)
            .scale({
              x: this.color === color ? 1.25 : 1,
              y: this.color === color ? 1.25 : 1,
            })
            .border({
              width: 2,
              color: '#fff'
            })
            .animation({ curve: Curve.Sharp, duration: 150 })
        }
        .type(ButtonType.Circle)
        .backgroundColor(Color.Transparent)
        .width(32)
        .height(32)
        .onClick(() => {
          if (this.isEnabled) {
            this.onChange?.(color);
          }
        })
      })
    }
    .enabled(this.isEnabled)
    .width('100%')
    .grayscale(this.isEnabled ? 0 : 1)
  }
}

@Preview
@Component
struct ColorPalettePreview {
  build() {
    ColorPalette({})
  }
}