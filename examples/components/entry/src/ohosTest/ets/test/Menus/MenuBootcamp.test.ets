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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, ON, Component } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';

const TAG = 'MenuBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function MenuBootcampTest() {
  describe('MenuBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      // 无法取到属性值进行断言

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(3500);
        console.info(TAG + 'MenuBootcamp001' + ' begin');

        let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        console.info(TAG + 'ListItemGroup' + ListItemGroup.toString());
        let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
        let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
        await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
        await driver.delayMs(3500);

        let atomDisplays: Component = await driver.findComponent(ON.text('菜单'));
        await atomDisplays.click();
        await driver.delayMs(4500);


        let scrollSearch: Component = await driver.findComponent(ON.text('菜单/Menu'))
        await scrollSearch.click()
        await driver.delayMs(2500);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })


    /**
     * 测试组件font.size支持统一设置Menu中所有文本的尺寸
     */
    it('ArkUI_Menu_001', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.size')
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

    /**
     * 测试组件font.weight支持统一设置Menu中所有文本的字体粗细为Lighter
     */
    it('ArkUI_Menu_002', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.weight')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件font.weight支持统一设置Menu中所有文本的字体粗细为Normal
     */
    it('ArkUI_Menu_003', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.weight')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件font.weight支持统一设置Menu中所有文本的字体粗细为Regular
     */
    it('ArkUI_Menu_004', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.weight')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件font.weight支持统一设置Menu中所有文本的字体粗细为Medium
     */
    it('ArkUI_Menu_005', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.weight')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件font.weight支持统一设置Menu中所有文本的字体粗细为Bold
     */
    it('ArkUI_Menu_006', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.weight')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件font.weight支持统一设置Menu中所有文本的字体粗细为Bolder
     */
    it('ArkUI_Menu_007', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件font.style支持统一设置Menu中所有文本的字体样式为Normal
     */
    it('ArkUI_Menu_008', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.style')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件font.style支持统一设置Menu中所有文本的字体样式为Italic
     */
    it('ArkUI_Menu_009', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'font.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件fontColor支持统一设置Menu中所有文本的字体颜色1号色
     */
    it('ArkUI_Menu_010', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件fontColor支持统一设置Menu中所有文本的字体颜色2号色
     */
    it('ArkUI_Menu_011', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件fontColor支持统一设置Menu中所有文本的字体颜色3号色
     */
    it('ArkUI_Menu_012', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件fontColor支持统一设置Menu中所有文本的字体颜色4号色
     */
    it('ArkUI_Menu_013', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件fontColor支持统一设置Menu中所有文本的字体颜色5号色
     */
    it('ArkUI_Menu_014', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件fontColor支持统一设置Menu中所有文本的字体颜色6号色
     */
    it('ArkUI_Menu_015', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件radius支持设置Menu边框圆角半径
     */
    it('ArkUI_Menu_016', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'radius')
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
     * 测试组件menuItemDivider.color支持设置menuItem分割线颜色1号色
     */
    it('ArkUI_Menu_017', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.color')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件menuItemDivider.color支持设置menuItem分割线颜色2号色
     */
    it('ArkUI_Menu_018', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.color')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件menuItemDivider.color支持设置menuItem分割线颜色3号色
     */
    it('ArkUI_Menu_019', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.color')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件menuItemDivider.color支持设置menuItem分割线颜色4号色
     */
    it('ArkUI_Menu_020', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.color')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件menuItemDivider.color支持设置menuItem分割线颜色5号色
     */
    it('ArkUI_Menu_021', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.color')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件menuItemDivider.color支持设置menuItem分割线颜色6号色
     */
    it('ArkUI_Menu_022', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件menuItemDivider.strokeWidth支持设置menuItem分割线线条宽度
     */
    it('ArkUI_Menu_023', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.strokeWidth')
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
     * 测试组件menuItemDivider.startMargin支持设置分割线与menuItem侧边起端的距离
     */
    it('ArkUI_Menu_024', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.startMargin')
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
     * 测试组件menuItemDivider.endMargin支持设置分割线与menuItem侧边起端的距离
     */
    it('ArkUI_Menu_025', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemDivider.endMargin')
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
     * 测试组件menuItemGroupDivider.strokeWidth支持设置menuItemGroup分割线线宽
     */
    it('ArkUI_Menu_026', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.strokeWidth')
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
     * 测试组件menuItemGroupDivider.color支持设置menuItemGroup分割线颜色1号色
     */
    it('ArkUI_Menu_027', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.color')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件menuItemGroupDivider.color支持设置menuItemGroup分割线颜色2号色
     */
    it('ArkUI_Menu_028', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.color')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件menuItemGroupDivider.color支持设置menuItemGroup分割线颜色3号色
     */
    it('ArkUI_Menu_029', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.color')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件menuItemGroupDivider.color支持设置menuItemGroup分割线颜色4号色
     */
    it('ArkUI_Menu_030', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.color')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件menuItemGroupDivider.color支持设置menuItemGroup分割线颜色5号色
     */
    it('ArkUI_Menu_031', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.color')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件menuItemGroupDivider.color支持设置menuItemGroup分割线颜色6号色
     */
    it('ArkUI_Menu_032', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     *  测试组件menuItemGroupDivider.startMargin支持设置上下分割线与menuItemGroup侧边起端的距离
     */
    it('ArkUI_Menu_033', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.startMargin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
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
     * 测试组件menuItemGroupDivider.endMargin支持设置上下分割线与menuItemGroup侧边起端的距离
     */
    it('ArkUI_Menu_034', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'menuItemGroupDivider.endMargin')
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
     * 测试组件SubMenuExpandingMode支持设置Menu子菜单展开样式为SIDE_EXPAND
     */
    it('ArkUI_Menu_035', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SubMenuExpandingMode')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件SubMenuExpandingMode支持设置Menu子菜单展开样式为EMBEDDED_EXPAND
     */
    it('ArkUI_Menu_036', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SubMenuExpandingMode')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件SubMenuExpandingMode支持设置Menu子菜单展开样式为STACK_EXPAND
     */
    it('ArkUI_Menu_037', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'SubMenuExpandingMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件direction支持设置设置容器元素内主轴方向上的布局为Auto且获取属性正确
     */
    it('ArkUI_Menu_038', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'direction')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件direction支持设置设置容器元素内主轴方向上的布局为Rtl且获取属性正确
     */
    it('ArkUI_Menu_039', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'direction')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })


    /**
     * 测试组件direction支持设置设置容器元素内主轴方向上的布局为Ltr且获取属性正确
     */
    it('ArkUI_Menu_040', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'direction')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })


    /**
     * 测试组件菜单项1选中
     */
    it('ArkUI_Menu_041', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项1是否选中')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件菜单项1不选中
     */
    it('ArkUI_Menu_042', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项1是否选中')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件菜单项2选中
     */
    it('ArkUI_Menu_043', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项2是否选中')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件菜单项2不选中
     */
    it('ArkUI_Menu_044', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项2是否选中')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件菜单项3选中
     */
    it('ArkUI_Menu_045', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项3是否选中')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: '菜单项3是否选中'
        }
      })
      done();
    })

    /**
     * 测试组件菜单项3不选中
     */
    it('ArkUI_Menu_046', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项3是否选中')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: '菜单项3是否选中',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件菜单项4选中
     */
    it('ArkUI_Menu_047', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项4是否选中')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: '菜单项4是否选中'
        }
      })
      done();
    })

    /**
     * 测试组件菜单项4不选中
     */
    it('ArkUI_Menu_048', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '菜单项4是否选中')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: '菜单项4是否选中',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试显示前缀图标
     */
    it('ArkUI_Menu_049', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标'
        }
      })
      done();
    })

    /**
     * 测试不显示前缀图标
     */
    it('ArkUI_Menu_050', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', '是否显示前缀图标')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: '是否显示前缀图标',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Menu_Comp_0001', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_Menu_Comp_0002', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_Menu_Comp_0003', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_Menu_Comp_0004', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_Menu_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_Menu_Comp_0006', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_Menu_Comp_0007', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_Menu_Comp_0008', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_Menu_Comp_0009', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_Menu_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启position
     */
    it('ArkUI_Menu_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_Menu_Comp_0012', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_Menu_Comp_0013', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_Menu_Comp_0014', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.right且获取属性正确
     */
    it('ArkUI_Menu_Comp_0015', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试关闭position
     */
    it('ArkUI_Menu_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启markAnchor
     */
    it('ArkUI_Menu_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_Menu_Comp_0018', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_Menu_Comp_0019', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试关闭markAnchor
     */
    it('ArkUI_Menu_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
  })
}