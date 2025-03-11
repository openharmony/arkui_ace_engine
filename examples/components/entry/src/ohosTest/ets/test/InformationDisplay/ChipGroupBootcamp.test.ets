import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  titleSearch,
  searchToggle,
  getToggle,
  searchParentBlock
} from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'ChipGroupBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function ChipGroupBootcampTest() {
  describe('ChipGroupBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done:Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'ChipGroupBootcampTest' + ' begin');

        let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
        let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
        await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
        await driver.delayMs(1000);


        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[2].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('操作块群组/ChipGroup'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    // options.itemStyle.size
    it('ArkUI_ChipGroup_001', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.size')
      // options.itemStyle.size无法获取
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_ChipGroup_002', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.size')
      // options.itemStyle.size无法获取
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })
    // options.itemStyle.backgroundColor
    it('ArkUI_ChipGroup_003', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.backgroundColor')
      // options.itemStyle.backgroundColor无法获取
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_ChipGroup_004', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.backgroundColor')
      // options.itemStyle.backgroundColor无法获取
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })

    it('ArkUI_ChipGroup_005', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.backgroundColor')
      // options.itemStyle.backgroundColor无法获取
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })

    it('ArkUI_ChipGroup_006', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.backgroundColor')
      // options.itemStyle.backgroundColor无法获取
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })

    it('ArkUI_ChipGroup_007', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.backgroundColor')
      // options.itemStyle.backgroundColor无法获取
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })

    it('ArkUI_ChipGroup_008', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.backgroundColor')
      // options.itemStyle.backgroundColor无法获取
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // options.itemStyle.fontColor
    it('ArkUI_ChipGroup_009', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.fontColor')
      // options.itemStyle.fontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_ChipGroup_010', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.fontColor')
      // options.itemStyle.fontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })

    it('ArkUI_ChipGroup_011', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.fontColor')
      // options.itemStyle.fontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })

    it('ArkUI_ChipGroup_012', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.fontColor')
      // options.itemStyle.fontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })

    it('ArkUI_ChipGroup_013', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.fontColor')
      // options.itemStyle.fontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })

    it('ArkUI_ChipGroup_014', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.fontColor')
      // options.itemStyle.fontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // options.itemStyle.selectedFontColor
    it('ArkUI_ChipGroup_015', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedFontColor')
      // options.itemStyle.selectedFontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_ChipGroup_016', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedFontColor')
      // options.itemStyle.selectedFontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })

    it('ArkUI_ChipGroup_017', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedFontColor')
      // options.itemStyle.selectedFontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })

    it('ArkUI_ChipGroup_018', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedFontColor')
      // options.itemStyle.selectedFontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })

    it('ArkUI_ChipGroup_019', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedFontColor')
      // options.itemStyle.selectedFontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })

    it('ArkUI_ChipGroup_020', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedFontColor')
      // options.itemStyle.selectedFontColor 属性无法获取
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // options.itemStyle.selectedBackgroundColor
    it('ArkUI_ChipGroup_021', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedBackgroundColor')
      // options.itemStyle.selectedBackgroundColor 属性无法获取
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_ChipGroup_022', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedBackgroundColor')
      // options.itemStyle.selectedBackgroundColor 属性无法获取
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })

    it('ArkUI_ChipGroup_023', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedBackgroundColor')
      // options.itemStyle.selectedBackgroundColor 属性无法获取
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })

    it('ArkUI_ChipGroup_024', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedBackgroundColor')
      // options.itemStyle.selectedBackgroundColor 属性无法获取
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })

    it('ArkUI_ChipGroup_025', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedBackgroundColor')
      // options.itemStyle.selectedBackgroundColor 属性无法获取
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })

    it('ArkUI_ChipGroup_026', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.itemStyle.selectedBackgroundColor')
      // options.itemStyle.selectedBackgroundColor 属性无法获取
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // options.selectedIndexes
    it('ArkUI_ChipGroup_027', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.selectedIndexes')
      // options.selectedIndexes无法获取
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_ChipGroup_028', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.selectedIndexes')
      // options.selectedIndexes无法获取
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })

    it('ArkUI_ChipGroup_029', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.selectedIndexes')
      // options.selectedIndexes无法获取
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // options.multiple
    it('ArkUI_ChipGroup_030', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.multiple')
      // options.multiple 无法获取
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_ChipGroup_031', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.multiple')
      // options.multiple 无法获取
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // options.chipGroupSpace.itemSpace
    it('ArkUI_ChipGroup_032', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.chipGroupSpace.itemSpace')
      // options.chipGroupSpace.itemSpace 无法获取
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

    // options.chipGroupSpace.startSpace
    it('ArkUI_ChipGroup_033', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.chipGroupSpace.startSpace')
      // options.chipGroupSpace.startSpace 无法获取
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

    // options.chipGroupSpace.endSpace
    it('ArkUI_ChipGroup_034', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.chipGroupSpace.endSpace')
      // options.chipGroupSpace.endSpace 无法获取
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

    // options.chipGroupSpace.top
    it('ArkUI_ChipGroup_035', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.ChipGroupPadding.top')
      // options.chipGroupSpace.top 无法获取
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

    // options.chipGroupSpace.bottom
    it('ArkUI_ChipGroup_036', 0, async  (done:Function) => {
      await titleSearch('参数列表', 'options.ChipGroupPadding.bottom')
      // options.chipGroupSpace.bottom 无法获取
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
    

  })
}