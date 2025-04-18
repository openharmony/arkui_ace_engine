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

export default function TextPickerDialogBootcampTest() {
  describe('TextPickerDialogBootcampTest', () => {
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

        let scrollSearch:Component = await driver.findComponent(ON.text('文本选择器弹窗/TextpickerDialog'))
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


    it('ArkUI_TextPickerDialog_001', 0, async (done: Function) => {
      await Search('参数列表', 'defaultPickerItemHeight')
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


    it('ArkUI_TextPickerDialog_002', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 0
      })

      done();
    })

    it('ArkUI_TextPickerDialog_003', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 1
      })

      done();
    })

    it('ArkUI_TextPickerDialog_004', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 2
      })

      done();
    })

    it('ArkUI_TextPickerDialog_005', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 3
      })

      done();
    })

    it('ArkUI_TextPickerDialog_006', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 4
      })

      done();
    })

    it('ArkUI_TextPickerDialog_007', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_TextPickerDialog_008', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.font.size')
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

    it('ArkUI_TextPickerDialog_009', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.font.weight')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_TextPickerDialog_010', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.font.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_011', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 0
      })

      done();
    })

    it('ArkUI_TextPickerDialog_012', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 1
      })

      done();
    })

    it('ArkUI_TextPickerDialog_013', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 2
      })

      done();
    })

    it('ArkUI_TextPickerDialog_014', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 3
      })

      done();
    })

    it('ArkUI_TextPickerDialog_015', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 4
      })

      done();
    })

    it('ArkUI_TextPickerDialog_016', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_TextPickerDialog_017', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.font.size')
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

    it('ArkUI_TextPickerDialog_018', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.font.weight')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_019', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.font.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_020', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 0
      })

      done();
    })

    it('ArkUI_TextPickerDialog_021', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 1
      })

      done();
    })

    it('ArkUI_TextPickerDialog_022', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 2
      })

      done();
    })

    it('ArkUI_TextPickerDialog_023', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 3
      })

      done();
    })

    it('ArkUI_TextPickerDialog_024', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 4
      })

      done();
    })

    it('ArkUI_TextPickerDialog_025', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_026', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_027', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.font.weight')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_028', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.font.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_029', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_030', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_031', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.type')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_032', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_033', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_034', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.type')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_035', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.style')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_036', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.style')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_037', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.style')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_038', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.style')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_039', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.style')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_040', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.style')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_041', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_042', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_043', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_044', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_045', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_046', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_047', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_048', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_049', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_050', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_051', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_052', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_053', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.role')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_054', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.role')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_055', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.role')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_056', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.role')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_057', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_058', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_059', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_060', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_061', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_062', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_063', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_064', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_065', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_066', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_067', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_068', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_069', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_070', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_071', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_072', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_073', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_074', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_075', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_076', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_077', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_078', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_079', 0, async (done: Function) => {
      await Search('参数列表', 'canLoop')
      await radioClick({
        radioClickObj: 0,
      })

      done();
    })

    it('ArkUI_TextPickerDialog_080', 0, async (done: Function) => {
      await Search('参数列表', 'canLoop')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_TextPickerDialog_081', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_082', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_083', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 2,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_084', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_085', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_086', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_087', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_088', 0, async (done: Function) => {
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

    it('ArkUI_TextPickerDialog_089', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_090', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_091', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_TextPickerDialog_092', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_093', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 0,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_094', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 1,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_095', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 2,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_096', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 3,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_097', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 4,

      })
      done();
    })

    it('ArkUI_TextPickerDialog_098', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_099', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'backgroundBlurStyle'
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_100', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'backgroundBlurStyle'
        }
      })
      done();
    })

    it('ArkUI_TextPickerDialog_101', 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'shadow'
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_102', 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'shadow',
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_103', 0, async (done: Function) => {
      await Search('参数列表', 'hapticFeedback')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hapticFeedback',
        }

      })
      done();
    })

    it('ArkUI_TextPickerDialog_104', 0, async (done: Function) => {
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