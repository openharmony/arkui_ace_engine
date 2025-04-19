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
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  ToggleClick
} from '../../../utils';
import { searchBeforeAll } from './Search.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SearchBootcampTest5() {
  describe('SearchBootcampTest5', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      searchBeforeAll(done, delegator, driver);
    })
    it('ArkUI_Search_Comp_0201', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Search_Comp_0202', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.angle', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '360.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_Search_Comp_0203', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_Search_Comp_0204', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_Search_Comp_0205', 0, async (done: Function) => {
      // 读取不到属性值
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerZ', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0206', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.perspective', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Search_Comp_0207', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件translate
     */
    it('ArkUI_Search_Comp_0208', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Search_Comp_0209', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Search_Comp_0210', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Search_Comp_0211', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Search_Comp_0212', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件scale
     */
    it('ArkUI_Search_Comp_0213', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Search_Comp_0214', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '300.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })

    it('ArkUI_Search_Comp_0215', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '300.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })

    it('ArkUI_Search_Comp_0216', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Search_Comp_0217', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_Search_Comp_0218', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_Search_Comp_0219', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件transform
     */
    it('ArkUI_Search_Comp_0220', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Search_Comp_0221', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件clip
     */
    it('ArkUI_Search_Comp_0222', 0, async (done: Function) => {
      await searchParentBlock('clip', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_Search_Comp_0223', 0, async (done: Function) => {
      await searchParentBlock('clip', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })
    /**
     * 测试组件clipShape
     */
    it('ArkUI_Search_Comp_0224', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Search_Comp_0225', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      await searchParentBlock('clipShape.width', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0226', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      await searchParentBlock('clipShape.height', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0227', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件mask
     */
    it('ArkUI_Search_Comp_0228', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Search_Comp_0229', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.value', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0230', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', false, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0231', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_Search_Comp_0232', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_Search_Comp_0233', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_Search_Comp_0234', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_Search_Comp_0235', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0236', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件maskShape
     */
    it('ArkUI_Search_Comp_0237', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Search_Comp_0238', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      await searchParentBlock('maskShape.width', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0239', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      await searchParentBlock('maskShape.height', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_Search_Comp_0240', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件blur
     */
    it('ArkUI_Search_Comp_0241', 0, async (done: Function) => {
      await Search('基础属性', 'blur.value', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blur', JsonType.value),
        ],
        assertEqual: 0
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blur', JsonType.value),
        ],
        assertEqual: 0
      })

      done();
    })
    it('ArkUI_Search_Comp_0242', 0, async (done: Function) => {
      await Search('基础属性', 'blur.options.grayscale.number1', '通用属性2');
      // 读取不到
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    it('ArkUI_Search_Comp_0243', 0, async (done: Function) => {
      // 读取不到
      await Search('基础属性', 'blur.options.grayscale.number2', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    /**
     * 测试组件shadow
     */
    it('ArkUI_Search_Comp_0244', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.radius', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_Search_Comp_0245', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    it('ArkUI_Search_Comp_0246', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_Search_Comp_0247', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Search_Comp_0248', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Search_Comp_0249', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Search_Comp_0250', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Search_Comp_0251', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Search_Comp_0252', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    it('ArkUI_Search_Comp_0253', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetX', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_Search_Comp_0254', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetY', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_Search_Comp_0255', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_Search_Comp_0256', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    /**
     * 测试组件grayscale
     */
    it('ArkUI_Search_Comp_0257', 0, async (done: Function) => {
      await searchParentBlock('grayscale', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件brightness
     */
    it('ArkUI_Search_Comp_0258', 0, async (done: Function) => {
      await searchParentBlock('brightness', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 2
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件saturate
     */
    it('ArkUI_Search_Comp_0259', 0, async (done: Function) => {
      await searchParentBlock('saturate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value)
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件contrast
     */
    it('ArkUI_Search_Comp_0260', 0, async (done: Function) => {
      await searchParentBlock('contrast', false, '基础属性', '通用属性2')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value)
        ],
        assertEqual: 10
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件invert
     */
    it('ArkUI_Search_Comp_0261', 0, async (done: Function) => {
      await searchParentBlock('invert', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件sepia
     */
    it('ArkUI_Search_Comp_0262', 0, async (done: Function) => {
      await searchParentBlock('sepia', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件hueRotate
     */
    it('ArkUI_Search_Comp_0263', 0, async (done: Function) => {
      await searchParentBlock('hueRotate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value)
        ],
        assertEqual: 180
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value)
        ],
        assertEqual: 180
      })

      done();
    })
    /**
     * 测试组件colorBlend
     */
    it('ArkUI_Search_Comp_0264', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Search_Comp_0265', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Search_Comp_0266', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Search_Comp_0267', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Search_Comp_0268', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Search_Comp_0269', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件linearGradientBlur
     */
    it('ArkUI_Search_Comp_0270', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.value', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '60.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '0.00px'
      })

      done();
    })
    it('ArkUI_Search_Comp_0271', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.100000,0.000000', '0.200000,1.000000']
      })

      done();

    })
    it('ArkUI_Search_Comp_0272', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.100000,0.330000', '0.200000,0.660000', '0.300000,1.000000']
      })

      done();

    })
    it('ArkUI_Search_Comp_0273', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.400000,0.250000', '0.300000,0.500000', '0.200000,0.750000', '0.100000,1.000000']
      })

      done();

    })
    it('ArkUI_Search_Comp_0274', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    it('ArkUI_Search_Comp_0275', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    it('ArkUI_Search_Comp_0276', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT'
      })

      done();

    })
    it('ArkUI_Search_Comp_0277', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'BOTTOM'
      })

      done();

    })
    it('ArkUI_Search_Comp_0278', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT_TOP'
      })

      done();

    })
    it('ArkUI_Search_Comp_0279', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT_BOTTOM'
      })

      done();

    })
    it('ArkUI_Search_Comp_0280', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT_TOP'
      })

      done();

    })
    it('ArkUI_Search_Comp_0281', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT_BOTTOM'
      })

      done();

    })
    it('ArkUI_Search_Comp_0282', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    // renderGroup
    it('ArkUI_Search_Comp_0283', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_Search_Comp_0284', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'false'
      })

      done();

    })
    // blendMode
    it('ArkUI_Search_Comp_0285', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_Search_Comp_0286', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 1
      })

      done();

    })
    it('ArkUI_Search_Comp_0287', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 2
      })

      done();

    })
    it('ArkUI_Search_Comp_0288', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 3
      })

      done();

    })
    it('ArkUI_Search_Comp_0289', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 4
      })

      done();

    })
    it('ArkUI_Search_Comp_0290', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 5
      })

      done();

    })

  })
}