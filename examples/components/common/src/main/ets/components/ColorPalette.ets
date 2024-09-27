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
import { BlockTag } from '../model/BlockTag';
import { tagDesRule } from '../utils';
import { formatDate } from '../utils/timeUtil';

@Component
export struct ColorPalette {
  @Prop color: ResourceColor | undefined = undefined;
  @Prop colors: ResourceColor[] =
    ['#0A59F7', '#646AFD', '#FE7062', '#E9E8ED', '#1C1C1C', $r('sys.color.ohos_id_color_text_primary_contrary')];
  @Prop isEnabled: boolean = false;
  onChange?: (color: ResourceColor) => void;
  @Prop title: string = '';
  @State listColorBlockTags: Array<BlockTag> = [];
  @State listColorBlockTagsTemp: Array<BlockTag> = [];

  build() {
    Row() {
      ForEach(this.colors, (color: ResourceColor, index: number) => {
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
            let time = formatDate(new Date(Date.now()))
            this.listColorBlockTagsTemp.push(new BlockTag(time, tagDesRule(this.title, (color).toString())))
            console.log('Block  =====>>>>>' + JSON.stringify(this.listColorBlockTagsTemp));
            setTimeout(() => {
              if (AppStorage.get('Block')) {
                let block = AppStorage.get('Block') as Array<BlockTag>;
                this.listColorBlockTags = block.concat(this.listColorBlockTagsTemp);
                this.listColorBlockTagsTemp = [];
                AppStorage.setOrCreate('Block', this.listColorBlockTags);
                console.log('get Block this.listBlockTags ==' + JSON.stringify(this.listColorBlockTagsTemp));
                console.log('get Block this.listBlockTags length ==>> ' + this.listColorBlockTags.length);
              } else {
                if (this.listColorBlockTagsTemp) {
                  this.listColorBlockTags = this.listColorBlockTags.concat(this.listColorBlockTagsTemp);
                }
                console.log('Block this.listBlockTags ==' + JSON.stringify(this.listColorBlockTags));
                console.log('Block this.listBlockTags length ==>> ' + this.listColorBlockTags.length);
                AppStorage.setOrCreate('Block', this.listColorBlockTags);
                if (this.listColorBlockTags) {
                  this.listColorBlockTagsTemp = [];
                }
              }
            }, 200)
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