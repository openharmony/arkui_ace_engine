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
export default function BindPopupBootcampTest() {
  describe('BindPopupBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(10000);



        let ListItemGroup :Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width:Point = await ListItemGroup[0].getBoundsCenter()
        let width2:Point = await ListItemGroup[4].getBoundsCenter()
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
        
        let scrollSearch:Component = await driver.findComponent(ON.text('气泡/bindPopup'))
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



    it('ArkUI_BindPopup_001', 0, async (done: Function) => {
      await Search('参数列表','show.buttons')
      await radioClick({
        radioClickObj: 0

      })
      done();
    })

    it('ArkUI_BindPopup_002', 0, async (done: Function) => {
      await Search('参数列表','show.buttons')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_BindPopup_003', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.arrowOffset')
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

    it('ArkUI_BindPopup_004', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.showInSubWindow')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_BindPopup_005', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.showInSubWindow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_006', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.maskType')
      await radioClick({
        radioClickObj: 0,
      })

      await Search('参数列表', 'popupOptions.mask.boolean')
      await radioClick({
        radioClickObj: 0
      })
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      await Search('参数列表','popupOptions.maskType')
      await radioClick({
        radioClickObj: 1,
      })

      await Search('参数列表', 'popupOptions.mask.color')
      await buttonClick({
        buttonClickObj: 0
      })
      await buttonClick({
        buttonClickObj: 1,
      })
      await buttonClick({
        buttonClickObj: 2,
      })
      await buttonClick({
        buttonClickObj: 3,
      })
      await buttonClick({
        buttonClickObj: 4,
      })
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      await Search('参数列表','popupOptions.maskType')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_007', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.textColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_BindPopup_008', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.textColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_BindPopup_009', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.textColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_BindPopup_010', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.textColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_BindPopup_011', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.textColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_BindPopup_012', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.textColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_013', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.size')
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

    it('ArkUI_BindPopup_014', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.weight')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_BindPopup_015', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.weight')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it('ArkUI_BindPopup_016', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.weight')
      await radioClick({
        radioClickObj: 2,

      })
      done();
    })

    it('ArkUI_BindPopup_017', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.weight')
      await radioClick({
        radioClickObj: 3,

      })
      done();
    })

    it('ArkUI_BindPopup_018', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.weight')
      await radioClick({
        radioClickObj: 4,

      })
      done();
    })

    it('ArkUI_BindPopup_019', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_BindPopup_020', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.style')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_BindPopup_021', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.messageOptions.font.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_BindPopup_022', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.targetSpace')
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

    it('ArkUI_BindPopup_023', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_BindPopup_024', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_BindPopup_025', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })

    it('ArkUI_BindPopup_026', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })

    it('ArkUI_BindPopup_027', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })

    it('ArkUI_BindPopup_028', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })

    it('ArkUI_BindPopup_029', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })

    it('ArkUI_BindPopup_030', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })

    it('ArkUI_BindPopup_031', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })

    it('ArkUI_BindPopup_032', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.placement')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_033', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.offsetX')
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

    it('ArkUI_BindPopup_034', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.offsetY')
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

    it('ArkUI_BindPopup_035', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.enableArrow')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_BindPopup_036', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.enableArrow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_037', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.popupColor')
      await buttonClick({
        buttonClickObj: 0,

      })
      done();
    })

    it('ArkUI_BindPopup_038', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.popupColor')
      await buttonClick({
        buttonClickObj: 1,

      })
      done();
    })

    it('ArkUI_BindPopup_039', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.popupColor')
      await buttonClick({
        buttonClickObj: 2,

      })
      done();
    })

    it('ArkUI_BindPopup_040', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.popupColor')
      await buttonClick({
        buttonClickObj: 3,

      })
      done();
    })

    it('ArkUI_BindPopup_041', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.popupColor')
      await buttonClick({
        buttonClickObj: 4,

      })
      done();
    })

    it('ArkUI_BindPopup_042', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.popupColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_043', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.autoCancel')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_BindPopup_044', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.autoCancel')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_045', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.width')
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

    it('ArkUI_BindPopup_046', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.arrowPointPosition')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_BindPopup_047', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.arrowPointPosition')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it('ArkUI_BindPopup_048', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.arrowPointPosition')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_BindPopup_049', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })



    it('ArkUI_BindPopup_050', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })

    it('ArkUI_BindPopup_051', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })

    it('ArkUI_BindPopup_052', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 2,

      })
      done();
    })

    it('ArkUI_BindPopup_053', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 3,

      })
      done();
    })

    it('ArkUI_BindPopup_054', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 4,

      })
      done();
    })

    it('ArkUI_BindPopup_055', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowStyle')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }

      })
      done();
    })

    it('ArkUI_BindPopup_056', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_BindPopup_057', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.radius')
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

    it('ArkUI_BindPopup_058', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.type')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_BindPopup_059', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.type')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_060', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    it('ArkUI_BindPopup_061', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    it('ArkUI_BindPopup_062', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    it('ArkUI_BindPopup_063', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    it('ArkUI_BindPopup_064', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    it('ArkUI_BindPopup_065', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.color')
      await buttonClick({
        buttonClickObj: 5,
      })
      done();
    })

    it('ArkUI_BindPopup_066', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.offsetX')
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

    it('ArkUI_BindPopup_067', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.offsetY')
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

    it('ArkUI_BindPopup_068', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.fill')
      await radioClick({
        radioClickObj: 0
      })

      done();
    })

    it('ArkUI_BindPopup_069', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow.shadowOptions.fill')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })

    it('ArkUI_BindPopup_070', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.shadow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_071', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it('ArkUI_BindPopup_072', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it('ArkUI_BindPopup_073', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    it('ArkUI_BindPopup_074', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    it('ArkUI_BindPopup_075', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    it('ArkUI_BindPopup_076', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })

    it('ArkUI_BindPopup_077', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })

    it('ArkUI_BindPopup_078', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })

    it('ArkUI_BindPopup_079', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
      })
      done();
    })

    it('ArkUI_BindPopup_080', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
      })
      done();
    })

    it('ArkUI_BindPopup_081', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
      })
      done();
    })

    it('ArkUI_BindPopup_082', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.BackgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_BindPopup_083', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.opacity')
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

    it('ArkUI_BindPopup_084', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.translateX')
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

    it('ArkUI_BindPopup_085', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.translateY')
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

    it('ArkUI_BindPopup_086', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.translateZ')
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

    it('ArkUI_BindPopup_087', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.scaleX')
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

    it('ArkUI_BindPopup_088', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.scaleY')
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

    it('ArkUI_BindPopup_089', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.scaleZ')
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

    it('ArkUI_BindPopup_090', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.scale.centerX')
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

    it('ArkUI_BindPopup_091', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.scale.centerY')
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

    it('ArkUI_BindPopup_092', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.RotateX')
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

    it('ArkUI_BindPopup_093', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.RotateY')
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

    it('ArkUI_BindPopup_094', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.Rotate.CenterX')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'popupOptions.transition.Rotate.CenterX'
        }
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'popupOptions.transition.Rotate.CenterX'
        }
      })
      done();
    })

    it('ArkUI_BindPopup_095', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.Rotate.CenterY')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'popupOptions.transition.Rotate.CenterY'
        }
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'popupOptions.transition.Rotate.CenterY'
        }
      })
      done();
    })

    it('ArkUI_BindPopup_096', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.move')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupOptions.transition.move'
        }
      })
      done();
    })

    it('ArkUI_BindPopup_097', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.move')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupOptions.transition.move'
        }
      })
      done();
    })

    it('ArkUI_BindPopup_098', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.move')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupOptions.transition.move'
        }
      })
      done();
    })

    it('ArkUI_BindPopup_099', 0, async (done: Function) => {
      await Search('参数列表','popupOptions.transition.move')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupOptions.transition.move',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
  })
}