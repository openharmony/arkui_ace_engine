/*
 * Copyright (c) 2025 Hunan OpenValley Digital Industry Development Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { describe, beforeAll, it } from '@ohos/hypium'
import {  Driver, ON } from '@kit.TestKit';
import { buttonClick,
  JsonType, KeyStruct, radioClick,
  Slide, sliderDrag,
  titleSearch,
  Search,
  ToggleClick } from '../../../utils';
import { ToggleStart } from './Toggle';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function Toggle5() {
  describe('Toggle5', () => {

    beforeAll(async (done: Function) => {
      await ToggleStart(done)
    })

    // linearGradient.number2
    it('ArkUI_Toggle_Comp_0350', 0, async (done: Function) => {
      await titleSearch('基础属性', 'linearGradient.number2', '通用属性3')
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
    it('ArkUI_Toggle_Comp_0351', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Toggle',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    it('ArkUI_Toggle_Comp_0352', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Toggle',
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