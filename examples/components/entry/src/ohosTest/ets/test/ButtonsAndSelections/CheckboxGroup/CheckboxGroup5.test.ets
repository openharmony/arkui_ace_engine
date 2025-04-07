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
import { Driver, ON } from '@kit.TestKit';
import { buttonClick,
  JsonType, KeyStruct, radioClick,
  Slide, sliderDrag,
  titleSearch,
  Search,
  ToggleClick } from '../../../utils';
import { CheckboxGroupStart } from './CheckboxGroup';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function CheckboxGroup5() {
  describe('CheckboxGroup5', () => {

    beforeAll(async (done: Function) => {
      await CheckboxGroupStart(done)
    })

    //focusable
    it('ArkUI_CheckboxGroup_Comp_0461', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_CheckboxGroup_Comp_0462', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // defaultFocus
    it('ArkUI_CheckboxGroup_Comp_0463', 0, async (done: Function) => {
      //设置当前组件是否为当前页面上的默认焦点，仅在初次创建的页面第一次进入时生效。
      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_CheckboxGroup_Comp_0464', 0, async (done: Function) => {

      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

  })
}