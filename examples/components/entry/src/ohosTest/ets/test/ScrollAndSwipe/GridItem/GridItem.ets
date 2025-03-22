import { abilityDelegatorRegistry, Driver,Component,ON} from '@kit.TestKit';
import {Point } from '@ohos.UiTest';

const TAG = 'GridItemBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export async function GridItemStart(done:Function) {
  await delegator.startAbility({
    bundleName: 'cn.ohos.components',
    abilityName: 'EntryAbility'
  });

  await driver.delayMs(3500);
  console.info(TAG + 'GridItemBootcamp001' + ' begin');

  let atomDisplays: Component = await driver.findComponent(ON.text('滚动与滑动'));
  await atomDisplays.click();
  await driver.delayMs(4000);

  let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
  let width: Point = await ListItems[0].getBoundsCenter()
  let width2: Point = await ListItems[4].getBoundsCenter()
  await driver.swipe(width.x, width2.y, width.x, width.y, 500)
  await driver.delayMs(2500);


  let scrollSearch: Component = await driver.findComponent(ON.text('网格选项/GridItem'))
  await scrollSearch.click()
  await driver.delayMs(1000);

  let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
  await Buttons[1].click()
  await driver.delayMs(1000);


  console.info(`beforeAll end`);
  done();
}

