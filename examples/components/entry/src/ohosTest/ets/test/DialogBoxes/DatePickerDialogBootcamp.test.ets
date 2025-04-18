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
export default function DatePickerDialogBootcampTest() {
  describe('DatePickerDialogBootcampTest', () => {
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

        let scrollSearch:Component = await driver.findComponent(ON.text('日期选择器弹窗/DatepickerDialog'))
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

    it('ArkUI_DatePickerDialog_0001', 0, async (done: Function) => {
      await Search('参数列表', 'lunar')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0002', 0, async (done: Function) => {
      await Search('参数列表', 'lunar')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0003', 0, async (done: Function) => {
      await Search('参数列表', 'lunarSwitch')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0004', 0, async (done: Function) => {
      await Search('参数列表', 'lunarSwitch')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0005', 0, async (done: Function) => {
      await Search('参数列表', 'showTime')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0006', 0, async (done: Function) => {
      await Search('参数列表', 'showTime')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0007', 0, async (done: Function) => {
      await Search('参数列表', 'useMilitaryTime')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0008', 0, async (done: Function) => {
      await Search('参数列表', 'useMilitaryTime')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0009', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0010', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0011', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0012', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0013', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0014', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0015', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.fontSize')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0016', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.fontSize')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0017', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.fontSize')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0018', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.fontWeight')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0019', 0, async (done: Function) => {
      await Search('参数列表', 'disappearTextStyle.fontWeight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0020', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0021', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0022', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0023', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0024', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0025', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0026', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.fontSize')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0027', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.fontSize')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0028', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.fontSize')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0029', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.fontWeight')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0030', 0, async (done: Function) => {
      await Search('参数列表', 'textStyle.fontWeight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0031', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0032', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0033', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0034', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0035', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0036', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0037', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.fontSize')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0038', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.fontSize')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0039', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.fontSize')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0040', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.fontWeight')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0041', 0, async (done: Function) => {
      await Search('参数列表', 'selectedTextStyle.fontWeight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0042', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0043', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0044', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0045', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0046', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0047', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0048', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonType')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0049', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonType')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0050', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0051', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonType')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0052', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonType')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0053', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0054', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0055', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0056', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0057', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0058', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0059', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0060', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0061', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0062', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0063', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0064', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0065', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButtonStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0066', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.role')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0067', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.role')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0068', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.role')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0069', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.role')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0070', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.size')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0071', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.size')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0072', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.size')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0073', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.size')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0074', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.fontWeight')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0075', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.fontWeight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0076', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.fontWeight')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0077', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.fontWeight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0078', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0079', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0080', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.fontStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0081', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0082', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0083', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0084', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0085', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0086', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0087', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0088', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0089', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0090', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0091', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0092', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0093', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0094', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.borderRadius')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0095', 0, async (done: Function) => {
      await Search('参数列表', 'acceptButton.borderRadius')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0096', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.borderRadius')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0097', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.borderRadius')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0098', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0099', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0100', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0101', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0102', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0103', 0, async (done: Function) => {
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

    it('ArkUI_DatePickerDialog_0104', 0, async (done: Function) => {
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

    it('ArkUI_DatePickerDialog_0105', 0, async (done: Function) => {
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

    it('ArkUI_DatePickerDialog_0106', 0, async (done: Function) => {
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

    it('ArkUI_DatePickerDialog_0107', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0108', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0109', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0110', 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0111', 0, async (done: Function) => {
      await Search('参数列表', 'dialogBackgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0112', 0, async (done: Function) => {
      await Search('参数列表', 'dialogBackgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0113', 0, async (done: Function) => {
      await Search('参数列表', 'dialogBackgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0114', 0, async (done: Function) => {
      await Search('参数列表', 'dialogBackgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0115', 0, async (done: Function) => {
      await Search('参数列表', 'dialogBackgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0116', 0, async (done: Function) => {
      await Search('参数列表', 'dialogBackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0117', 0, async (done: Function) => {
      await Search('参数列表', 'DialogBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0118', 0, async (done: Function) => {
      await Search('参数列表', 'DialogBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0119', 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0120', 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0121', 0, async (done: Function) => {
      await Search('参数列表', 'hourFormat')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hourFormat'
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0122', 0, async (done: Function) => {
      await Search('参数列表', 'hourFormat')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hourFormat',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0123', 0, async (done: Function) => {
      await Search('参数列表', 'minuteFormat')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'minuteFormat'
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0124', 0, async (done: Function) => {
      await Search('参数列表', 'minuteFormat')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'minuteFormat',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0125', 0, async (done: Function) => {
      await Search('参数列表', 'hapticFeedback')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hapticFeedback'
        }
      })
      done();
    })

    it('ArkUI_DatePickerDialog_0126', 0, async (done: Function) => {
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