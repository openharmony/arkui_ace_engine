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


export default function ActionSheetBootcampTest() {
  describe('ActionSheetBootcampTest', () => {
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

        let scrollSearch: Component = await driver.findComponent(ON.text('列表选择弹窗/ActionSheet'))
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

    it('ArkUI_ActionSheet_001', 0, async (done: Function) => {
      await Search('参数列表', 'autoCancel')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_ActionSheet_002', 0, async (done: Function) => {
      await Search('参数列表', 'autoCancel')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it('ArkUI_ActionSheet_003', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it('ArkUI_ActionSheet_004', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it('ArkUI_ActionSheet_005', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })

    it('ArkUI_ActionSheet_006', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })

    it('ArkUI_ActionSheet_007', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })

    it('ArkUI_ActionSheet_008', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })

    it('ArkUI_ActionSheet_009', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })

    it('ArkUI_ActionSheet_010', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })

    it('ArkUI_ActionSheet_011', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })

    it('ArkUI_ActionSheet_012', 0, async (done: Function) => {
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_013", 0, async (done: Function) => {
      await Search('参数列表', 'offset.dx')
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

    it("ArkUI_ActionSheet_014", 0, async (done: Function) => {
      await Search('参数列表', 'offset.dy')
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

    it("ArkUI_ActionSheet_015", 0, async (done: Function) => {
      await Search('参数列表', 'isModal')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_016", 0, async (done: Function) => {
      await Search('参数列表', 'isModal')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_017", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_018", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_019", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })

    it("ArkUI_ActionSheet_020", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })

    it("ArkUI_ActionSheet_021", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })

    it("ArkUI_ActionSheet_022", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_023", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_024", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_025", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })

    it("ArkUI_ActionSheet_026", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })

    it("ArkUI_ActionSheet_027", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })

    it("ArkUI_ActionSheet_028", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })

    it("ArkUI_ActionSheet_029", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })

    it("ArkUI_ActionSheet_030", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })

    it("ArkUI_ActionSheet_031", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })

    it("ArkUI_ActionSheet_032", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })

    it("ArkUI_ActionSheet_033", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })

    it("ArkUI_ActionSheet_034", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })

    it("ArkUI_ActionSheet_035", 0, async (done: Function) => {
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_036", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.topLeft')
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

    it("ArkUI_ActionSheet_037", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.topRight')
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

    it("ArkUI_ActionSheet_038", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.bottomLeft')
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

    it("ArkUI_ActionSheet_039", 0, async (done: Function) => {
      await Search('参数列表', 'cornerRadius.bottomRight')
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

    it("ArkUI_ActionSheet_040", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_041", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_042", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })

    it("ArkUI_ActionSheet_043", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })

    it("ArkUI_ActionSheet_044", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })

    it("ArkUI_ActionSheet_045", 0, async (done: Function) => {
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_046", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_047", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_048", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })

    it("ArkUI_ActionSheet_049", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })

    it("ArkUI_ActionSheet_050", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })

    it("ArkUI_ActionSheet_051", 0, async (done: Function) => {
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_052", 0, async (done: Function) => {
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_053", 0, async (done: Function) => {
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_054", 0, async (done: Function) => {
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_055", 0, async (done: Function) => {
      await Search('参数列表', 'width')
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

    it("ArkUI_ActionSheet_056", 0, async (done: Function) => {
      await Search('参数列表', 'height')
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

    it("ArkUI_ActionSheet_057", 0, async (done: Function) => {
      await Search('参数列表', 'showInSubWindow')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_058", 0, async (done: Function) => {
      await Search('参数列表', 'showInSubWindow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_059", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.x')
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

    it("ArkUI_ActionSheet_060", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.y')
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

    it("ArkUI_ActionSheet_061", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_062", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_063", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_064", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_065", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_066", 0, async (done: Function) => {
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_067", 0, async (done: Function) => {
      await Search('参数列表', 'confirm.enabled')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_ActionSheet_068", 0, async (done: Function) => {
      await Search('参数列表', 'confirm.enabled')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    it("ArkUI_ActionSheet_069", 0, async (done: Function) => {
      await Search('参数列表', 'confirm.defaultFocus')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_ActionSheet_070", 0, async (done: Function) => {
      await Search('参数列表', 'confirm.defaultFocus')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_071", 0, async (done: Function) => {
      await Search('参数列表', 'confirm.style')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    it("ArkUI_ActionSheet_072", 0, async (done: Function) => {
      await Search('参数列表', 'confirm.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_073", 0, async (done: Function) => {
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

    it("ArkUI_ActionSheet_074", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    it("ArkUI_ActionSheet_075", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    it("ArkUI_ActionSheet_076", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })

    it("ArkUI_ActionSheet_077", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })

    it("ArkUI_ActionSheet_078", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })

    it("ArkUI_ActionSheet_079", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })

    it("ArkUI_ActionSheet_080", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })

    it("ArkUI_ActionSheet_081", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })

    it("ArkUI_ActionSheet_082", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })

    it("ArkUI_ActionSheet_083", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })

    it("ArkUI_ActionSheet_084", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })

    it("ArkUI_ActionSheet_085", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })

    it("ArkUI_ActionSheet_086", 0, async (done: Function) => {
      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_087", 0, async (done: Function) => {
      await Search('参数列表', 'scale.x')
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

    it("ArkUI_ActionSheet_088", 0, async (done: Function) => {
      await Search('参数列表', 'scale.y')
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

    it("ArkUI_ActionSheet_089", 0, async (done: Function) => {
      await Search('参数列表', 'SuffixIcon')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'SuffixIcon',
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_090", 0, async (done: Function) => {
      await Search('参数列表', 'SuffixIcon')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'SuffixIcon',
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_091", 0, async (done: Function) => {
      await Search('参数列表', 'SuffixIcon')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'SuffixIcon',
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_092", 0, async (done: Function) => {
      await Search('参数列表', 'SuffixIcon')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'SuffixIcon',
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_093", 0, async (done: Function) => {
      await Search('参数列表', 'SuffixIcon')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'SuffixIcon',
        }
      })
      done();
    })

    it("ArkUI_ActionSheet_094", 0, async (done: Function) => {
      await Search('参数列表', 'SuffixIcon')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'SuffixIcon',
        }
      })
      done();
    })
  })
}