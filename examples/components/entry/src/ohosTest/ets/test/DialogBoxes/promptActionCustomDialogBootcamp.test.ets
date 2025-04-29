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

export default function promptActionCustomDialogBootcampTest() {
  describe('promptActionCustomDialogBootcampTest', () => {
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
        await driver.delayMs(3000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)


        let ListItemGroup1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItemGroup1[0].getBoundsCenter()
        let width4: Point = await ListItemGroup1[2].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(2000);

        let scrollSearch: Component = await driver.findComponent(ON.text('promptActionCustomDialog'))
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


    it('ArkUI_promptActionCustomDialog_001', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_002', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_003', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_004', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_005', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_006', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_007', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderRadiusTopLeft')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_008', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderRadiusTopRight')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_009', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderRadiusBottomLeft')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_010', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderRadiusBottomRight')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_011', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderBorderWidthTop')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_012', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderBorderWidthLeft')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_013', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderBorderWidthBottom')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_014', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderBorderWidthRight')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_015', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorTop')
      await buttonClick({
        buttonClickObj: 0
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_016', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorTop')
      await buttonClick({
        buttonClickObj: 1
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_017', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorTop')
      await buttonClick({
        buttonClickObj: 2
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_018', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorTop')
      await buttonClick({
        buttonClickObj: 3
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_019', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorTop')
      await buttonClick({
        buttonClickObj: 4
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_020', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorTop')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_021', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorLeft')
      await buttonClick({
        buttonClickObj: 0
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_022', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorLeft')
      await buttonClick({
        buttonClickObj: 1
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_023', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorLeft')
      await buttonClick({
        buttonClickObj: 2
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_024', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorLeft')
      await buttonClick({
        buttonClickObj: 3
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_025', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorLeft')
      await buttonClick({
        buttonClickObj: 4
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_026', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorLeft')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_027', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorBottom')
      await buttonClick({
        buttonClickObj: 0
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_028', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorBottom')
      await buttonClick({
        buttonClickObj: 1
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_029', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorBottom')
      await buttonClick({
        buttonClickObj: 2
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_030', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorBottom')
      await buttonClick({
        buttonClickObj: 3
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_031', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorBottom')
      await buttonClick({
        buttonClickObj: 4
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_032', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorBottom')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_033', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorRight')
      await buttonClick({
        buttonClickObj: 0
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_034', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorRight')
      await buttonClick({
        buttonClickObj: 1
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_035', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorRight')
      await buttonClick({
        buttonClickObj: 2
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_036', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorRight')
      await buttonClick({
        buttonClickObj: 3
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_037', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorRight')
      await buttonClick({
        buttonClickObj: 4
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_038', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderColorRight')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_039', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleTop')
      await radioClick({
        radioClickObj: 0,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_040', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleTop')
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_041', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleTop')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_042', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleLeft')
      await radioClick({
        radioClickObj: 0,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_043', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleLeft')
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_044', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleLeft')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_045', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleBottom')
      await radioClick({
        radioClickObj: 0,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_046', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleBottom')
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_047', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleBottom')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_048', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleRight')
      await radioClick({
        radioClickObj: 0,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_049', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleRight')
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_050', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.borderStyleRight')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_051', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.width')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_052', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.height')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })


    it('ArkUI_promptActionCustomDialog_053', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_054', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_055', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_056', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_057', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_058', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_059', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_060', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_061', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_062', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_063', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_064', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.backgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })


    it('ArkUI_promptActionCustomDialog_065', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.shadow')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_066', 0, async (done: Function) => {
      await Search('参数列表', 'shadowStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'shadowStyle'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_067', 0, async (done: Function) => {
      await Search('参数列表', 'shadowStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'shadowStyle'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_068', 0, async (done: Function) => {
      await Search('参数列表', 'shadowStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'shadowStyle'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_069', 0, async (done: Function) => {
      await Search('参数列表', 'shadowStyle')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'shadowStyle'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_070', 0, async (done: Function) => {
      await Search('参数列表', 'shadowStyle')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'shadowStyle'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_071', 0, async (done: Function) => {
      await Search('参数列表', 'shadowStyle')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'shadowStyle',
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_072', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.shadow')
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_073', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.radius')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_074', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.type')
      await radioClick({
        radioClickObj: 0
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_075', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.type')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_076', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'shadowOptions.color'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_077', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'shadowOptions.color'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_078', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'shadowOptions.color'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_079', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.color')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'shadowOptions.color'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_080', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.color')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'shadowOptions.color'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_081', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'shadowOptions.color'
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_082', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.offsetX')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'shadowOptions.offsetX'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'shadowOptions.offsetX',
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_083', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.offsetY')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'shadowOptions.offsetY'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'shadowOptions.offsetY',
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })

    it('ArkUI_promptActionCustomDialog_084', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.fill')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'shadowOptions.fill'
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_085', 0, async (done: Function) => {
      await Search('参数列表', 'shadowOptions.fill')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'shadowOptions.fill',
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })

    it('ArkUI_promptActionCustomDialog_086', 0, async (done: Function) => {
      await Search('参数列表', 'CustomDialogOptions.shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'CustomDialogOptions.shadow',
          toggleClickType: ToggleClick.Close
        }
      })

      done()
    })
  })
}