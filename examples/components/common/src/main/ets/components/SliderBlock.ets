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

@Component
export struct SliderBlock {
  @Prop title: string;
  @Prop step: number = 1;
  @Link isEnabled: boolean;
  @Link value: number;
  @Prop min: number = 0;
  @Prop max: number = 100;
  @StorageLink('Block') listSliderTagsTemp: Array<BlockTag> = [];
  @State listSliderTags: Array<BlockTag> = [];

  build() {
    Column({ space: 0 }) {
      Block({ title: this.title, isEnabled: $isEnabled }) {
        Row({ space: 0 }) {
          Text(`${this.value}`)
            .fontSize(16)
            .width(28)
          Slider({
            value: this.value,
            min: this.min,
            max: this.max,
            step: this.step,
            style: SliderStyle.OutSet
          })
            .showSteps(false)
            .enabled(this.isEnabled)
            .showSteps(true)
            .width('80%')
            .onChange((value: number, mode: SliderChangeMode) => {
              this.value = Math.floor(value)
              if (mode.toString() === '2') {
                setTimeout(() => {
                  let time = formatDate(new Date(Date.now()))
                  this.listSliderTagsTemp.push(new BlockTag(time, tagDesRule(this.title, value.toString())))
                  console.log('Block  =====>>>>>' + JSON.stringify(this.listSliderTagsTemp));
                  if (AppStorage.get('Block')) {
                    this.listSliderTags = this.listSliderTags.concat(this.listSliderTagsTemp);
                    this.listSliderTagsTemp = [];
                    AppStorage.setOrCreate('Block', this.listSliderTags);
                    console.log('get Block Slider ==' + JSON.stringify(this.listSliderTags));
                    console.log('get Block Slider length ==>> ' + this.listSliderTags.length);
                  } else {
                    if (this.listSliderTagsTemp) {
                      this.listSliderTags = this.listSliderTags.concat(this.listSliderTagsTemp);
                    }
                    console.log('Block Slider ==' + JSON.stringify(this.listSliderTags));
                    console.log('Block Slider length ==>> ' + this.listSliderTags.length);
                    AppStorage.setOrCreate('Block', this.listSliderTags);
                    if (this.listSliderTags) {
                      this.listSliderTagsTemp = [];
                    }
                  }
                }, 200)
              }
            })
        }
        .margin({ left: 16 })
        .width('100%')
      }
    }
  }
}

@Preview
@Component
struct SliderBlockPreview {
  @State isEnabled: boolean = true
  @State value: number = 1;

  build() {
    SliderBlock({
      title: 'SliderBlock',
      isEnabled: $isEnabled,
      value: $value,
      min: 0,
      max: 100
    })
  }
}