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
export default function CustomDialogBootcampTest() {
  describe('CustomDialogBootcampTest', () => {
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
        await driver.delayMs(2000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)

        let ListItemGroup1 :Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3:Point = await ListItemGroup1[0].getBoundsCenter()
        let width4:Point = await ListItemGroup1[2].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(2000);

        let scrollSearch:Component = await driver.findComponent(ON.text('自定义弹窗/CustomDialog'))
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


    it("ArkUI_CustomDialog_0001", 0, async (done: Function) => {
      await Search('参数列表', 'autoCancel')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it("ArkUI_CustomDialog_0002", 0, async (done: Function) => {
      await Search('参数列表', 'autoCancel')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it("ArkUI_CustomDialog_0003", 0, async (done: Function) => {
      await Search('参数列表', 'duration')
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

    it("ArkUI_CustomDialog_0004", 0, async (done: Function) => {
      await Search('参数列表', 'tempo')
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

    it("ArkUI_CustomDialog_0005", 0, async (done: Function) => {
      await Search('参数列表', 'delay')
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

    it("ArkUI_CustomDialog_0006", 0, async (done: Function) => {
      await Search('参数列表', 'iterations')
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

    it("ArkUI_CustomDialog_0007", 0, async (done: Function) => {
      await Search('参数列表', 'playMode')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0008", 0, async (done: Function) => {
      await Search('参数列表', 'playMode')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it("ArkUI_CustomDialog_0009", 0, async (done: Function) => {
      await Search('参数列表', 'playMode')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it("ArkUI_CustomDialog_0010", 0, async (done: Function) => {
      await Search('参数列表', 'playMode')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0011", 0, async (done: Function) => {
      await Search('参数列表', 'finishCallbackType')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0012", 0, async (done: Function) => {
      await Search('参数列表', 'finishCallbackType')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0013", 0, async (done: Function) => {
      await Search('参数列表', 'expectedFrameRateRange.min')
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

    it("ArkUI_CustomDialog_0014", 0, async (done: Function) => {
      await Search('参数列表', 'expectedFrameRateRange.max')
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

    it("ArkUI_CustomDialog_0015", 0, async (done: Function) => {
      await Search('参数列表', 'expectedFrameRateRange.min')
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

    it("ArkUI_CustomDialog_0016", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0017", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it("ArkUI_CustomDialog_0018", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it("ArkUI_CustomDialog_0019", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    it("ArkUI_CustomDialog_0020", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    it("ArkUI_CustomDialog_0021", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })

    it("ArkUI_CustomDialog_0022", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })

    it("ArkUI_CustomDialog_0023", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })

    it("ArkUI_CustomDialog_0024", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 8,
      })
      done();
    })

    it("ArkUI_CustomDialog_0025", 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0026", 0, async (done: Function) => {
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

    it("ArkUI_CustomDialog_0027", 0, async (done: Function) => {
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

    it("ArkUI_CustomDialog_0028", 0, async (done: Function) => {
      await Search('参数列表', 'customStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0029", 0, async (done: Function) => {
      await Search('参数列表', 'customStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0030", 0, async (done: Function) => {
      await Search('参数列表', 'isModal')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0031", 0, async (done: Function) => {
      await Search('参数列表', 'isModal')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0032", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 0,

      })
      done();
    })

    it("ArkUI_CustomDialog_0033", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 1,

      })
      done();
    })

    it("ArkUI_CustomDialog_0034", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 2,

      })
      done();
    })

    it("ArkUI_CustomDialog_0035", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 3,

      })
      done();
    })

    it("ArkUI_CustomDialog_0036", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 4,

      })
      done();
    })

    it("ArkUI_CustomDialog_0037", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it("ArkUI_CustomDialog_0038", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it("ArkUI_CustomDialog_0039", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it("ArkUI_CustomDialog_0040", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,

      })
      done();
    })

    it("ArkUI_CustomDialog_0041", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,

      })
      done();
    })

    it("ArkUI_CustomDialog_0042", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,

      })
      done();
    })

    it("ArkUI_CustomDialog_0043", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,

      })
      done();
    })

    it("ArkUI_CustomDialog_0044", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,

      })
      done();
    })

    it("ArkUI_CustomDialog_0045", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,

      })
      done();
    })

    it("ArkUI_CustomDialog_0046", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,

      })
      done();
    })

    it("ArkUI_CustomDialog_0047", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,

      })
      done();
    })

    it("ArkUI_CustomDialog_0048", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,

      })
      done();
    })

    it("ArkUI_CustomDialog_0049", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,

      })
      done();
    })

    it("ArkUI_CustomDialog_0050", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it("ArkUI_CustomDialog_0051", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.topLeft')
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

    it("ArkUI_CustomDialog_0052", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.topRight')
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

    it("ArkUI_CustomDialog_0053", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.bottomLeft')
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

    it("ArkUI_CustomDialog_0054", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.bottomRight')
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

    it("ArkUI_CustomDialog_0055", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0056", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it("ArkUI_CustomDialog_0057", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it("ArkUI_CustomDialog_0058", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    it("ArkUI_CustomDialog_0059", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    it("ArkUI_CustomDialog_0060", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0061", 0, async (done: Function) => {
      await Search('参数列表', 'borderWidth')
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

    it("ArkUI_CustomDialog_0062", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0063", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it("ArkUI_CustomDialog_0064", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it("ArkUI_CustomDialog_0065", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it("ArkUI_CustomDialog_0066", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it("ArkUI_CustomDialog_0067", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0068", 0, async (done: Function) => {
      await Search('参数列表', 'maskColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it("ArkUI_CustomDialog_0069", 0, async (done: Function) => {
      await Search('参数列表', 'maskColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it("ArkUI_CustomDialog_0070", 0, async (done: Function) => {
      await Search('参数列表', 'maskColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it("ArkUI_CustomDialog_0071", 0, async (done: Function) => {
      await Search('参数列表', 'maskColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it("ArkUI_CustomDialog_0072", 0, async (done: Function) => {
      await Search('参数列表', 'maskColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it("ArkUI_CustomDialog_0073", 0, async (done: Function) => {
      await Search('参数列表', 'maskColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0074", 0, async (done: Function) => {
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it("ArkUI_CustomDialog_0075", 0, async (done: Function) => {
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it("ArkUI_CustomDialog_0076", 0, async (done: Function) => {
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 2,

      })
      done();
    })

    it("ArkUI_CustomDialog_0077", 0, async (done: Function) => {
      await Search('参数列表', 'width')
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

    it("ArkUI_CustomDialog_0078", 0, async (done: Function) => {
      await Search('参数列表', 'height')
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

    it("ArkUI_CustomDialog_0079", 0, async (done: Function) => {
      await Search('参数列表', 'gridCount')
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

    it("ArkUI_CustomDialog_0080", 0, async (done: Function) => {
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

    it("ArkUI_CustomDialog_0081", 0, async (done: Function) => {
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

    it("ArkUI_CustomDialog_0082", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'maskRect.width',
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0083", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'maskRect.width',
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0084", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'maskRect.width',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0085", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'maskRect.height',
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0086", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'maskRect.height',
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0087", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'maskRect.height',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0088", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0089", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0090", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0091", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0092", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0093", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0094", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0095", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0096", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0097", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0098", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0099", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickObj: 'curve'
        }
      })
      done();
    })

    it("ArkUI_CustomDialog_0100", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

  })
}