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

enum Mode {
  ONE = '1',
  TWO = '2',
};

@Component
export struct SliderBlock {
  @Prop title: string;
  @Prop step: number = 1;
  @Link isEnabled: boolean;
  @Link value: number;
  @Prop min: number = 0;
  @Prop max: number = 100;
  @State listSliderTagsTemp: Array<BlockTag> = [];
  @StorageLink('Block') listSliderTags: Array<BlockTag> = [];

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
              this.value = value
              if (mode.toString() === Mode.TWO) {
                setTimeout(() => {
                  let time = formatDate(new Date(Date.now()))
                  this.listSliderTagsTemp.push(new BlockTag(time, tagDesRule(this.title, value.toString())))
                  if (AppStorage.get('Block')) {
                    this.listSliderTags = this.listSliderTags.concat(this.listSliderTagsTemp);
                    this.listSliderTagsTemp = [];
                  } else {
                    if (this.listSliderTagsTemp) {
                      this.listSliderTags = this.listSliderTags.concat(this.listSliderTagsTemp);
                    }
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