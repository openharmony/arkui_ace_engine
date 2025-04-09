
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';

const TAG = 'MarqueeBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export async function AlphabetIndexerStart(done:Function){

  await delegator.startAbility({
    bundleName: 'cn.ohos.components',
    abilityName: 'EntryAbility'
  });

  await driver.delayMs(6000);
  console.info(TAG + 'AlphabetIndexerBootcamp001' + ' begin');

  let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
  let width: Point = await ListItems[0].getBoundsCenter()
  let width2: Point = await ListItems[6].getBoundsCenter()
  await driver.swipe(width.x, width2.y, width.x, width.y, 500)
  await driver.delayMs(4000);

  let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
  await atomDisplays.click();
  await driver.delayMs(1000);

  let scrollSearch: Component = await driver.findComponent(ON.text('索引条/AlphabetIndexer'))
  await scrollSearch.click()
  await driver.delayMs(1000);

  let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
  await Buttons[1].click()
  await driver.delayMs(1000);

  console.info(`beforeAll end`);

  done()
}
