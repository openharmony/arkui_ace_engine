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

import { Block } from './Block';
import { IconPalette } from './IconPalette';

@Component
export struct IconBlock {
  @Prop title: string;
  @Link isEnabled: boolean;
  @Link icon: ResourceStr;
  @StorageLink('Block') listIconBlockTags: Array<BlockTag> = [];
  @State listIconBlockTagsTemp: Array<BlockTag> = [];
  build() {
    Block({
      title: this.title,
      isEnabled: $isEnabled
    }) {
      IconPalette({
        icon: this.icon,
        title: this.title,
        onChange: (icon,index) => {
          this.icon = icon;
          if (this.isEnabled) {
            let time = formatDate(new Date(Date.now()))
            this.listIconBlockTagsTemp.push(new BlockTag(time, tagDesRule(this.title, (index + 1).toString())))
            setTimeout(() => {
              if (AppStorage.get('Block')) {
                this.listIconBlockTags = this.listIconBlockTags.concat(this.listIconBlockTagsTemp);
                this.listIconBlockTagsTemp = [];
              } else {
                if (this.listIconBlockTagsTemp) {
                  this.listIconBlockTags = this.listIconBlockTags.concat(this.listIconBlockTagsTemp);
                }
                if (this.listIconBlockTags) {
                  this.listIconBlockTagsTemp = [];
                }
              }
            }, 200)
          }
        },
        isEnabled: this.isEnabled,
      })
    }
  }
}

@Preview
@Component
struct IconBlockPreview {
  @State isEnabled: boolean = true
  @State icon: ResourceStr = '#fd5d77'

  build() {
    IconBlock({
      title: '标题',
      isEnabled: $isEnabled,
      icon: $icon
    })
  }
}