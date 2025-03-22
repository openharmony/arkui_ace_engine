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
import { Component, Driver, ON } from '@kit.TestKit';
import {
  buttonClick,
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  titleSearch,
  searchParentBlock
} from '../../../utils';
import { ListStart } from './List';


const driver = Driver.create();

export default function List4() {
  describe('List4', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await ListStart(done)

    })

    it('ArkUI_List_Comp_0214', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })

    it('ArkUI_List_Comp_0215', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })

    it('ArkUI_List_Comp_0216', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0217', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_List_Comp_0218', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_List_Comp_0219', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件transform
     */
    it('ArkUI_List_Comp_0220', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_List_Comp_0221', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件clip
     */
    it('ArkUI_List_Comp_0222', 0, async (done: Function) => {
      await searchParentBlock('clip', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_List_Comp_0223', 0, async (done: Function) => {
      await searchParentBlock('clip', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'List',
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
    it('ArkUI_List_Comp_0224', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_List_Comp_0225', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0226', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0227', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件mask
     */
    it('ArkUI_List_Comp_0228', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_List_Comp_0229', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0230', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0231', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_List_Comp_0232', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_List_Comp_0233', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_List_Comp_0234', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_List_Comp_0235', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0236', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件maskShape
     */
    it('ArkUI_List_Comp_0237', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_List_Comp_0238', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0239', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0240', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件blur
     */
    it('ArkUI_List_Comp_0241', 0, async (done: Function) => {
      await Search('基础属性', 'blur.value', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blur', JsonType.value),
        ],
        assertEqual: 0
      })

      done();
    })
    it('ArkUI_List_Comp_0242', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0243', 0, async (done: Function) => {
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
    it('ArkUI_List_Comp_0244', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.radius', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_List_Comp_0245', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    it('ArkUI_List_Comp_0246', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_List_Comp_0247', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_List_Comp_0248', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_List_Comp_0249', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_List_Comp_0250', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_List_Comp_0251', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_List_Comp_0252', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    it('ArkUI_List_Comp_0253', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetX', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_List_Comp_0254', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetY', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_List_Comp_0255', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_List_Comp_0256', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'List',
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
    it('ArkUI_List_Comp_0257', 0, async (done: Function) => {
      await searchParentBlock('grayscale', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
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
    it('ArkUI_List_Comp_0258', 0, async (done: Function) => {
      await searchParentBlock('brightness', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
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
    it('ArkUI_List_Comp_0259', 0, async (done: Function) => {
      await searchParentBlock('saturate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
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
    it('ArkUI_List_Comp_0260', 0, async (done: Function) => {
      await searchParentBlock('contrast', false, '基础属性', '通用属性2')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
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
    it('ArkUI_List_Comp_0261', 0, async (done: Function) => {
      await searchParentBlock('invert', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
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
    it('ArkUI_List_Comp_0262', 0, async (done: Function) => {
      await searchParentBlock('sepia', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
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
    it('ArkUI_List_Comp_0263', 0, async (done: Function) => {
      await searchParentBlock('hueRotate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
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
    it('ArkUI_List_Comp_0264', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_List_Comp_0265', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_List_Comp_0266', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_List_Comp_0267', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_List_Comp_0268', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_List_Comp_0269', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'List',
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
    it('ArkUI_List_Comp_0270', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.value', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '0.00px'
      })

      done();
    })
    it('ArkUI_List_Comp_0271', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
    it('ArkUI_List_Comp_0272', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'List',
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
    it('ArkUI_List_Comp_0273', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'List',
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
    it('ArkUI_List_Comp_0274', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
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
    it('ArkUI_List_Comp_0275', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'List',
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
    it('ArkUI_List_Comp_0276', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'List',
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
    it('ArkUI_List_Comp_0277', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'List',
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
    it('ArkUI_List_Comp_0278', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'List',
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
    it('ArkUI_List_Comp_0279', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'List',
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
    it('ArkUI_List_Comp_0280', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
        id: 'List',
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
    it('ArkUI_List_Comp_0281', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
        id: 'List',
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
    it('ArkUI_List_Comp_0282', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'List',
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
    it('ArkUI_List_Comp_0283', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_List_Comp_0284', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'false'
      })

      done();

    })
    // blendMode
    it('ArkUI_List_Comp_0285', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_List_Comp_0286', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 1
      })

      done();

    })
    it('ArkUI_List_Comp_0287', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 2
      })

      done();

    })
    it('ArkUI_List_Comp_0288', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 3
      })

      done();

    })
    it('ArkUI_List_Comp_0289', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 4
      })

      done();

    })
    it('ArkUI_List_Comp_0290', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 5
      })

      done();

    })
    it('ArkUI_List_Comp_0291', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 6
      })

      done();

    })
    it('ArkUI_List_Comp_0292', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 7
      })

      done();

    })
    it('ArkUI_List_Comp_0293', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 8,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 8
      })

      done();

    })
    it('ArkUI_List_Comp_0294', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 9,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 9
      })

      done();

    })
    it('ArkUI_List_Comp_0295', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 10,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 10
      })

      done();

    })
    it('ArkUI_List_Comp_0296', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 11,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 11
      })

      done();

    })
    it('ArkUI_List_Comp_0297', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 12,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 12
      })

      done();

    })
    it('ArkUI_List_Comp_0298', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 13,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 13
      })

      done();

    })
    it('ArkUI_List_Comp_0299', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 14,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 14
      })

      done();

    })
    it('ArkUI_List_Comp_0300', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 15,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 15
      })

      done();

    })
    it('ArkUI_List_Comp_0301', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 16,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 16
      })

      done();

    })
    it('ArkUI_List_Comp_0302', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 17,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 17
      })

      done();

    })
    it('ArkUI_List_Comp_0303', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 18,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 18
      })

      done();

    })
    it('ArkUI_List_Comp_0304', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 19,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 19
      })

      done();

    })
    it('ArkUI_List_Comp_0305', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 20,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 20
      })

      done();

    })
    it('ArkUI_List_Comp_0306', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 21,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 21
      })

      done();

    })
    it('ArkUI_List_Comp_0307', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 22,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 22
      })

      done();

    })
    it('ArkUI_List_Comp_0308', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 23,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 23
      })

      done();

    })

    it('ArkUI_List_Comp_0309', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 24,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 24
      })

      done();

    })
    it('ArkUI_List_Comp_0310', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 25,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 25
      })

      done();

    })

  })
}




