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

import { describe, beforeAll, it } from '@ohos/hypium'
import { Driver, } from '@kit.TestKit';
import { buttonClick, radioClick, Search, searchParentBlock, ToggleClick } from '../../../utils';
import { AlertDialogStart } from './AlertDialog';


const driver = Driver.create();

export default function AlertDialog1() {
  describe('AlertDialog1', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await AlertDialogStart(done)
    })
    /**
     * 测试组件twoButton的secondaryButton.backgroundColor支持设置Button背景颜色为1号色
     */
    it('ArkUI_AlertDialog_121', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'secondaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.backgroundColor支持设置Button背景颜色为2号色
     */
    it('ArkUI_AlertDialog_122', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'secondaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.backgroundColor支持设置Button背景颜色为3号色
     */
    it('ArkUI_AlertDialog_123', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'secondaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.backgroundColor支持设置Button背景颜色为4号色
     */
    it('ArkUI_AlertDialog_124', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'secondaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.backgroundColor支持设置Button背景颜色为5号色
     */
    it('ArkUI_AlertDialog_125', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'secondaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.backgroundColor支持设置Button背景颜色为6号色
     */
    it('ArkUI_AlertDialog_126', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'secondaryButton.backgroundColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    //twoButton的相关属性测试完毕，关闭twoButton Toggle,无需断言
    it('ArkUI_AlertDialog_127', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('twoButton', false, '参数列表')
      done()
    })

    /**
     * 测试组件threeButton的buttons.enabled设置点击Button是否响应为可以响应
     */
    it('ArkUI_AlertDialog_128', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('threeButton', true, '参数列表')
      await Search('参数列表', 'buttons.enabled')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'buttons.enabled'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.enabled设置点击Button是否响应为可以不响应
     */
    it('ArkUI_AlertDialog_129', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.enabled')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttons.enabled',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.defaultFocus设置Button是否是默认焦点为是默认焦点
     */
    it('ArkUI_AlertDialog_130', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.defaultFocus')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'buttons.defaultFocus'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.defaultFocus设置Button是否是默认焦点为不是默认焦点
     */
    it('ArkUI_AlertDialog_131', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.defaultFocus')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttons.defaultFocus',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.style设置Button的风格样式为DEFAULT
     */
    it('ArkUI_AlertDialog_132', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.style')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'buttons.style'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.style设置Button的风格样式为HIGHLIGHT
     */
    it('ArkUI_AlertDialog_133', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttons.style',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.fontColor支持设置Button文本颜色为1号色
     */
    it('ArkUI_AlertDialog_134', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'buttons.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.fontColor支持设置Button文本颜色为2号色
     */
    it('ArkUI_AlertDialog_135', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttons.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.fontColor支持设置Button文本颜色为3号色
     */
    it('ArkUI_AlertDialog_136', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'buttons.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.fontColor支持设置Button文本颜色为4号色
     */
    it('ArkUI_AlertDialog_137', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'buttons.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.fontColor支持设置Button文本颜色为5号色
     */
    it('ArkUI_AlertDialog_138', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'buttons.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.fontColor支持设置Button文本颜色为6号色
     */
    it('ArkUI_AlertDialog_139', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'buttons.fontColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.backgroundColor支持设置Button背景颜色为1号色
     */
    it('ArkUI_AlertDialog_140', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'buttons.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.backgroundColor支持设置Button背景颜色为2号色
     */
    it('ArkUI_AlertDialog_141', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttons.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.backgroundColor支持设置Button背景颜色为3号色
     */
    it('ArkUI_AlertDialog_142', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'buttons.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.backgroundColor支持设置Button背景颜色为4号色
     */
    it('ArkUI_AlertDialog_143', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'buttons.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.backgroundColor支持设置Button背景颜色为5号色
     */
    it('ArkUI_AlertDialog_144', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'buttons.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件threeButton的buttons.backgroundColor支持设置Button背景颜色为6号色
     */
    it('ArkUI_AlertDialog_145', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'buttons.backgroundColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    //threeButton的相关属性测试完毕，关闭threeButton Toggle,无需断言
    it('ArkUI_AlertDialog_146', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('threeButton', false, '参数列表')
      done();
    })

    /**
     * 测试组件buttonDirection支持按钮排布方向默认值为AUTO
     */
    it('ArkUI_AlertDialog_147', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttonDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'buttonDirection',
        }
      })
      done();
    })

    /**
     * 测试组件buttonDirection支持按钮排布方向默认值为HIGHLIGHT
     */
    it('ArkUI_AlertDialog_148', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttonDirection')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttonDirection',
        }
      })
      done();
    })

    /**
     * 测试组件buttonDirection支持按钮排布方向默认值为VERTICAL
     */
    it('ArkUI_AlertDialog_149', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttonDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'buttonDirection',
        }
      })
      done();
    })

  })

}