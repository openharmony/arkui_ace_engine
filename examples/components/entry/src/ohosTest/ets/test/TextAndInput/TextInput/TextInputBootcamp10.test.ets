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

import { describe, beforeAll, it } from '@ohos/hypium';
import { abilityDelegatorRegistry, Driver } from '@kit.TestKit';
import {
    buttonClick,
    getToggle, radioClick, searchToggle,
    Slide,
    sliderDrag,
    titleSearch,
    ToggleClick
} from '../../../utils';
import { textInputBeforeAll } from './TextInput.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TextInputBootcampTest10() {
  describe('TextInputBootcampTest10', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      textInputBeforeAll(done, delegator, driver);
    })

  })
}