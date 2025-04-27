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

export default function CalendarPickerDialogBootcampTest() {
  describe('CalendarPickerDialogBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(10000);


        let ListItemGroup: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItemGroup[0].getBoundsCenter()
        let width2: Point = await ListItemGroup[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(2000);

        let atomDisplays: Component = await driver.findComponent(ON.text('弹窗'));
        await atomDisplays.click();
        await driver.delayMs(3000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)


        let ListItemGroup1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItemGroup1[0].getBoundsCenter()
        let width4: Point = await ListItemGroup1[2].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(2000);

        let scrollSearch: Component = await driver.findComponent(ON.text('日历选择器弹窗/CalendarpickerDialog'))
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


    it('ArkUI_CalendarPickerDialog_001', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_002', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_003', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_004', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_005', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_006', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_007', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.Style.ButtonStyleMode')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_008', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.Style.ButtonStyleMode')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_009', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.Style.ButtonStyleMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_010', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.Style.ButtonStyleMode')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_011', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.Style.ButtonStyleMode')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_012', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.Style.ButtonStyleMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_013', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_014', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_015', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_016', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_017', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_018', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_019', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_020', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_021', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_022', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_023', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_024', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_025', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.role.ButtonRole')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_026', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.role.ButtonRole')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_027', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.role.ButtonRole')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_028', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.role.ButtonRole')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_029', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontSize')
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

    it('ArkUI_CalendarPickerDialog_030', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontSize')
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

    it('ArkUI_CalendarPickerDialog_031', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontWeight')
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

    it('ArkUI_CalendarPickerDialog_032', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontWeight')
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

    it('ArkUI_CalendarPickerDialog_033', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_034', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_035', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_036', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_037', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_038', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_039', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_040', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_041', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_042', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })


    it('ArkUI_CalendarPickerDialog_043', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_044', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_045', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_046', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_047', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_048', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_049', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.acceptButtonStyle.borderRadius')
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

    it('ArkUI_CalendarPickerDialog_050', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.cancelButtonStyle.borderRadius')
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

    it('ArkUI_CalendarPickerDialog_051', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_052', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_053', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_054', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_055', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_056', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_057', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_058', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_059', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 8,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_060', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 9,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_061', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 10,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_062', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_063', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_064', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_065', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_066', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_067', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_068', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_069', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_070', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_071', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_072', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_073', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_074', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_075', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_076', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_077', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.radius')
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

    it('ArkUI_CalendarPickerDialog_078', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_079', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.type')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_080', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_081', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_082', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_083', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_084', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_085', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_086', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.offsetX')
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

    it('ArkUI_CalendarPickerDialog_087', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.offsetY')
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

    it('ArkUI_CalendarPickerDialog_088', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.fill')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_089', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow.shadowOptions.fill')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_090', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_091', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_092', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.start')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_093', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.start')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_094', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.start')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_095', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.start')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_096', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.start')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_097', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.start')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_098', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.end')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_099', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.end')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_0100', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.end')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_101', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.end')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_102', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.end')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_103', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.end')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_104', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.markToday')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.markToday'
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_105', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.markToday')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.markToday',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })


    it('ArkUI_CalendarPickerDialog_106', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.disabledDateRange')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.disabledDateRange',
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_107', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.disabledDateRange')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.disabledDateRange',
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_108', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.disabledDateRange')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.disabledDateRange',
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_109', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.disabledDateRange')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.disabledDateRange',
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_110', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.disabledDateRange')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.disabledDateRange',
        }
      })
      done();
    })

    it('ArkUI_CalendarPickerDialog_111', 0, async (done: Function) => {
      await Search('参数列表', 'CalendarDialogOptions.disabledDateRange')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'CalendarDialogOptions.disabledDateRange',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
  })
}