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

import { describe, beforeAll, it } from '@ohos/hypium';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
  Search
} from '../../../utils';
import { FoldSplitContainerStart } from './FoldSplitContainer';
import { Driver, ON } from '@kit.TestKit';

const driver = Driver.create();

export default function FoldSplitContainer5() {
  describe('FoldSplitContainer5', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
    })

    //linearGradient.color1
    it('ArkUI_FoldSplitContainer_Comp_0134', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0135', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0136', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 2,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0137', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 3,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0138', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 4,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0139', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number1
    it('ArkUI_FoldSplitContainer_Comp_0140', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.number1', '通用属性2')

      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // linearGradient.color2
    it('ArkUI_FoldSplitContainer_Comp_0141', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0142', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0143', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 2,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0144', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 3,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0145', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 4,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0146', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number2
    it('ArkUI_FoldSplitContainer_Comp_0147', 0, async (done: Function) => {
      await titleSearch('基础属性', 'linearGradient.number2', '通用属性2')
      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })
    // linearGradient.repeating
    it('ArkUI_FoldSplitContainer_Comp_0148', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0149', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性2')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })
  })
}