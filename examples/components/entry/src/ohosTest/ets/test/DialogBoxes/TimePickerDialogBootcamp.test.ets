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
export default function TimePickerDialogBootcampTest() {
  describe('TimePickerDialogBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);

        let ListItemGroup :Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width:Point = await ListItemGroup[0].getBoundsCenter()
        let width2:Point = await ListItemGroup[5].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(2000);

        let atomDisplays:Component = await driver.findComponent(ON.text('弹窗'));
        await atomDisplays.click();
        await driver.delayMs(3000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)


        let ListItemGroup1 :Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3:Point = await ListItemGroup1[0].getBoundsCenter()
        let width4:Point = await ListItemGroup1[2].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(2000);

        let scrollSearch:Component = await driver.findComponent(ON.text('时间选择器弹窗/TimePickerDialog'))
        await scrollSearch.click()
        await driver.delayMs(2000);

        let Buttons:Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(2000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    it('ArkUI_TimePickerDialog_001', 0, async (done: Function) => {
      await Search('参数列表', 'useMilitaryTime')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_002', 0, async (done: Function) => {
      await Search('参数列表', 'useMilitaryTime')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_003', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_004', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_005', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_006', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_007', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_008', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_009', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.font.size')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_010', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.font.weight')
      await radioClick({
        radioClickObj: 0,
      })

      done();
    })

    it('ArkUI_TimePickerDialog_011', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.font.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_TimePickerDialog_012', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_013', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_014', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_015', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_016', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_017', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_018', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.font.size')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_019', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.font.weight')
      await radioClick({
        radioClickObj: 0,
      })

      done();
    })

    it('ArkUI_TimePickerDialog_020', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.font.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_TimePickerDialog_021', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 0,
      })

      done();
    })

    it('ArkUI_TimePickerDialog_022', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();
    })

    it('ArkUI_TimePickerDialog_023', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();
    })

    it('ArkUI_TimePickerDialog_024', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();
    })

    it('ArkUI_TimePickerDialog_025', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();
    })

    it('ArkUI_TimePickerDialog_026', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_TimePickerDialog_027', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.font.size')
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

    it('ArkUI_TimePickerDialog_028', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.font.weight')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_029', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.font.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_030', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_031', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_032', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_033', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_034', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_035', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_036', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.style')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_037', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.style')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_038', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.style')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_039', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.style')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_040', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.style')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_042', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.style')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_043', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_044', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_045', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_046', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_047', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_048', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_049', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_050', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_051', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_052', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_053', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_054', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_055', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.role')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_TimePickerDialog_056', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.role')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_057', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.role')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_058', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.role')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_059', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontSize')
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

    it('ArkUI_TimePickerDialog_060', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontSize')
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

    it('ArkUI_TimePickerDialog_061', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontWeight')
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

    it('ArkUI_TimePickerDialog_062', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontWeight')
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

    it('ArkUI_TimePickerDialog_063', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_064', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_065', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_066', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_067', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_068', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_069', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_070', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_071', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_072', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_073', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_074', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_075', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_076', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_077', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_078', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_079', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.borderRadius')
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

    it('ArkUI_TimePickerDialog_080', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.borderRadius')
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

    it('ArkUI_TimePickerDialog_081', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_082', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_083', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it('ArkUI_TimePickerDialog_084', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_085', 0, async (done: Function) => {
      await Search('参数列表', 'offset.dx')
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

    it('ArkUI_TimePickerDialog_086', 0, async (done: Function) => {
      await Search('参数列表', 'offset.dy')
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

    it('ArkUI_TimePickerDialog_087', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.x')
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

    it('ArkUI_TimePickerDialog_088', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.y')
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

    it('ArkUI_TimePickerDialog_089', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_TimePickerDialog_090', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_091', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_TimePickerDialog_092', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_093', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })

    it('ArkUI_TimePickerDialog_094', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })

    it('ArkUI_TimePickerDialog_095', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })

    it('ArkUI_TimePickerDialog_096', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })

    it('ArkUI_TimePickerDialog_097', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })

    it('ArkUI_TimePickerDialog_098', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_099', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_TimePickerDialog_100', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_101', 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_TimePickerDialog_102', 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_103', 0, async (done: Function) => {
      await Search('参数列表', 'dateTimeOptions.hour')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_TimePickerDialog_104', 0, async (done: Function) => {
      await Search('参数列表', 'dateTimeOptions.hour')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_105', 0, async (done: Function) => {
      await Search('参数列表', 'dateTimeOptions.minute')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'dateTimeOptions.minute'
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_106', 0, async (done: Function) => {
      await Search('参数列表', 'dateTimeOptions.minute')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'dateTimeOptions.minute',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_107', 0, async (done: Function) => {
      await Search('参数列表', 'hapticFeedback')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hapticFeedback',
        }
      })
      done();
    })

    it('ArkUI_TimePickerDialog_108', 0, async (done: Function) => {
      await Search('参数列表', 'hapticFeedback')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hapticFeedback',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
  })
}