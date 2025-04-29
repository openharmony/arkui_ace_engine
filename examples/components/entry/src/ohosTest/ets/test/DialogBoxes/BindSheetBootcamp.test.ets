import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  Search,
  ToggleClick
} from '../../utils';
import { Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function BindSheetBootcampTest() {
  describe('BindSheetBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);

        let ListItemGroup: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItemGroup[0].getBoundsCenter()
        let width2: Point = await ListItemGroup[5].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(2000);

        let atomDisplays: Component = await driver.findComponent(ON.text('弹窗'));
        await atomDisplays.click();
        await driver.delayMs(2000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)


        let ListItemGroup1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItemGroup1[0].getBoundsCenter()
        let width4: Point = await ListItemGroup1[5].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(2000);

        let scrollSearch: Component = await driver.findComponent(ON.text('半模态/BindSheet'))
        await scrollSearch.click()
        await driver.delayMs(2000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(2000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })


    it('ArkUI_BindSheet_001', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.height')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_002', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.height')
      await radioClick({
        radioClickObj: 1
      })

      done();
    })

    it('ArkUI_BindSheet_003', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.height')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_004', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.detents')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_005', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.detents')
      await radioClick({
        radioClickObj: 1
      })

      done();
    })

    it('ArkUI_BindSheet_006', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.detents')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_007', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.preferType')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_008', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.preferType')
      await radioClick({
        radioClickObj: 1
      })

      done();
    })

    it('ArkUI_BindSheet_009', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.preferType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_010', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.showClose')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_011', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.showClose')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_012', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.dragBar')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_013', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.dragBar')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_014', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_015', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 1
      })

      done();
    })

    it('ArkUI_BindSheet_016', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 2
      })

      done();
    })

    it('ArkUI_BindSheet_017', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 3
      })

      done();
    })

    it('ArkUI_BindSheet_018', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 4
      })

      done();
    })

    it('ArkUI_BindSheet_019', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 5
      })

      done();
    })

    it('ArkUI_BindSheet_020', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 6
      })

      done();
    })

    it('ArkUI_BindSheet_021', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 7
      })

      done();
    })

    it('ArkUI_BindSheet_022', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 8
      })

      done();
    })

    it('ArkUI_BindSheet_023', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 9
      })

      done();
    })

    it('ArkUI_BindSheet_024', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 10
      })

      done();
    })

    it('ArkUI_BindSheet_025', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 11
      })

      done();
    })

    it('ArkUI_BindSheet_026', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.blurStyle')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_027', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.maskColor')
      await buttonClick({
        buttonClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_028', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.maskColor')
      await buttonClick({
        buttonClickObj: 1
      })

      done();
    })

    it('ArkUI_BindSheet_029', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.maskColor')
      await buttonClick({
        buttonClickObj: 2
      })

      done();
    })

    it('ArkUI_BindSheet_030', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.maskColor')
      await buttonClick({
        buttonClickObj: 3
      })

      done();
    })

    it('ArkUI_BindSheet_031', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.maskColor')
      await buttonClick({
        buttonClickObj: 4
      })

      done();
    })

    it('ArkUI_BindSheet_032', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.maskColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_033', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.title.title')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_034', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.title.title')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_035', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.title.subtitle')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_036', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.title.subtitle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_037', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.enableOutsideInteractive')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindSheet_038', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.enableOutsideInteractive')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_039', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderWidth')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindSheet_040', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderColor')
      await buttonClick({
        buttonClickObj: 0,
      })

      done();
    })

    it('ArkUI_BindSheet_041', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderColor')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();
    })

    it('ArkUI_BindSheet_042', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderColor')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();
    })

    it('ArkUI_BindSheet_043', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderColor')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();
    })

    it('ArkUI_BindSheet_044', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderColor')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();
    })

    it('ArkUI_BindSheet_045', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_046', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderStyle')
      await radioClick({
        radioClickObj: 0,
      })

      done();
    })

    it('ArkUI_BindSheet_047', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderStyle')
      await radioClick({
        radioClickObj: 1,
      })

      done();
    })

    it('ArkUI_BindSheet_048', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.borderStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_049', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.width')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_050', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.shadow')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'sheetOptions.shadow'
        }
      })

      done();
    })

    it('ArkUI_BindSheet_051', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'sheetOptions.shadow'
        }
      })

      done();
    })

    it('ArkUI_BindSheet_052', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.shadow')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'sheetOptions.shadow'
        }
      })

      done();
    })

    it('ArkUI_BindSheet_053', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.shadow')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'sheetOptions.shadow'
        }
      })

      done();
    })

    it('ArkUI_BindSheet_054', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.shadow')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'sheetOptions.shadow'
        }
      })

      done();
    })

    it('ArkUI_BindSheet_055', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.shadow')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'sheetOptions.shadow',
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindSheet_056', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.mode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'sheetOptions.mode',
        }
      })

      done();
    })

    it('ArkUI_BindSheet_057', 0, async (done: Function) => {
      await Search('参数列表', 'sheetOptions.mode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'sheetOptions.mode',
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
  })
}