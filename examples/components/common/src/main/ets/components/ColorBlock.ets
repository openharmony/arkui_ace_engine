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

import { Block } from './Block'
import { ColorPalette } from './ColorPalette';
import { BlockTag } from '../model/BlockTag';
import { formatDate } from '../utils/timeUtil';
import { tagDesRule } from '../utils';
import { ColorMetrics } from '@kit.ArkUI';


@Component
export struct ColorBlock {
  @Prop title: string;
  @Link isEnabled: boolean;
  @Link color: ResourceColor;
  @StorageLink('Block') listColorBlockTags: Array<BlockTag> = [];
  @State listColorBlockTagsTemp: Array<BlockTag> = [];

  build() {
    Block({
      title: this.title,
      isEnabled: $isEnabled
    }) {
      ColorPalette({
        color: this.color,
        title: this.title,
        onChange: (color) => {
          this.color = color;
          const colors = ColorMetrics.resourceColor(color);
          if (colors.red === 255 && colors.green === 255 && colors.blue === 255 && colors.alpha === 255) {
            color = '#FFFFFF'
          }
          if (this.isEnabled) {
            let time = formatDate(new Date(Date.now()))
            this.listColorBlockTagsTemp.push(new BlockTag(time, tagDesRule(this.title, (color).toString())))
            setTimeout(() => {
              if (AppStorage.get('Block')) {
                this.listColorBlockTags = this.listColorBlockTags.concat(this.listColorBlockTagsTemp);
                this.listColorBlockTagsTemp = [];
              } else {
                if (this.listColorBlockTagsTemp) {
                  this.listColorBlockTags = this.listColorBlockTags.concat(this.listColorBlockTagsTemp);
                }
                if (this.listColorBlockTags) {
                  this.listColorBlockTagsTemp = [];
                }
              }
            }, 200)
          }
        },
        isEnabled: this.isEnabled
      })
    }
  }
}


@Preview
@Component
struct ColorBlockPreview {
  @State isEnabled: boolean = true
  @State color: ResourceColor = '#fd5d77'

  build() {
    ColorBlock({
      title: '标题',
      isEnabled: $isEnabled,
      color: $color
    })
  }
}