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
export struct SliderOpacityBlock {
  @Prop title: string;
  @Prop step: number = 0.1;
  @Link isEnabled: boolean;
  @Link value: number;
  @Prop min: number = 0;
  @Prop max: number = 1;
  @State listSliderOpacityTagsTemp: Array<BlockTag> = [];
  @State listSliderOpacityTags: Array<BlockTag> = [];

  build() {
    Column({ space: 0 }) {
      Block({ title: this.title, isEnabled: $isEnabled }) {
        Row({ space: 0 }) {
          Text(`${this.value}`)
            .fontSize(16)
            .width(24)
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
              this.value = parseFloat(value.toFixed(1));
              console.log(`SliderOpacityBlock onChange: ${this.value}`);
              if (mode.toString() === '2') {
                let time = formatDate(new Date(Date.now()))
                this.listSliderOpacityTagsTemp.push(new BlockTag(time, tagDesRule(this.title, this.value.toString())))
                console.log('Block  =====>>>>>' + JSON.stringify(this.listSliderOpacityTagsTemp));
                setTimeout(() => {
                  if (AppStorage.get('Block')) {
                    let block = AppStorage.get('Block') as Array<BlockTag>;
                    this.listSliderOpacityTags = block.concat(this.listSliderOpacityTagsTemp);
                    this.listSliderOpacityTagsTemp = [];
                    AppStorage.setOrCreate('Block', this.listSliderOpacityTags);
                    console.log('get Block SliderOpacity ==' + JSON.stringify(this.listSliderOpacityTags));
                    console.log('get Block SliderOpacity length ==>> ' + this.listSliderOpacityTags.length);
                  } else {
                    if (this.listSliderOpacityTagsTemp) {
                      this.listSliderOpacityTags = this.listSliderOpacityTags.concat(this.listSliderOpacityTagsTemp);
                    }
                    console.log('Block SliderOpacity ==' + JSON.stringify(this.listSliderOpacityTags));
                    console.log('Block SliderOpacity length ==>> ' + this.listSliderOpacityTags.length);
                    AppStorage.setOrCreate('Block', this.listSliderOpacityTags);
                    if (this.listSliderOpacityTags) {
                      this.listSliderOpacityTagsTemp = [];
                    }
                  }
                }, 200)
              }
            })
        }.width('100%')
        .margin({ left: 16 })
      }
    }
  }
}
