/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { eq, neq, gt, ITestFile } from '../lib/testRunner';

declare function ObservedV2<T>(baseClass: T): T;

declare function Trace(target: object, propertyKey: string): void;

declare function Local(target: object, propertyKey: string): void;

declare function Param(proto: object, propertyKey: string): void;

declare function Once(proto: object, propertyKey: string): void;

declare function Event(target: object, propertyKey: string): void;

declare function Provider(aliasName?: string): (proto: object, varName: string) => void;

declare function Consumer(aliasName?: string): (proto: object, varName: string) => void;

declare function Monitor(key: string, ...keys: Array<string>): (target: object, propertyKey: string,
  descriptor: MonitorDescriptorImpl) => void;

declare function SyncMonitor(key: string, ...keys: Array<string>): (target: object, propertyKey: string,
  descriptor: MonitorDescriptorImpl) => void;

declare function Computed(target: object, propertyKey: string, descriptor: ComputedDescriptorImpl): void;

declare function Env(envKey: string): (proto: object, varName: string) => void;

interface IMonitorValue<T> {
  before: T;
  now: T;
  path: string;
}

interface IMonitor {
  dirty: Array<string>;

  value<T>(key?: string): IMonitorValue<T> | undefined;
}

class MonitorDescriptorImpl {
  value: (m: IMonitor) => void;

  constructor() {
    this.value = (_m: IMonitor): void => {
    };
  }
}

class ComputedDescriptorImpl {
  configurable: boolean = true;
  enumerable: boolean = true;
  get: () => number;

  constructor() {
    this.get = (): number => 7;
  }
}

class DecoratorCarrier {
  title: string = 'init';
  score: number = 1;
  theme: string = 'light';
  onDone: () => void = (): void => {
  };
  parentTheme: string | undefined = 'none';
  envValue: string = 'default';
}

class ObservedClassBase {
  value: number = 1;

  getValue(): number {
    return this.value;
  }
}

export class V2DecoratorsTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  public testCoreBasics(): void {
    const Wrapped = ObservedV2(ObservedClassBase);
    const obj = new Wrapped();
    eq(obj.getValue(), 1, 'observed');
    const h = new DecoratorCarrier();
    Trace(h, 'title');
    Local(h, 'theme');
    Param(h, 'score');
    Once(h, 'score');
    Event(h, 'onDone');
    Provider('app')(h, 'theme');
    Consumer('app')(h, 'parentTheme');
    const e = Env('system.arkui.breakpoint');
    e(h, 'envValue');
    eq(h.theme, 'light', 'core');
  }

  public testMonitorCase001(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('profile.name')(h, 'm001', d);
    eq(typeof d.value, 'function', 'm001');
    eq(h.title, 'init', 'mhost001');
  }

  public testMonitorCase002(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('profile.age')(h, 'm002', d);
    eq(typeof d.value, 'function', 'm002');
    eq(h.title, 'init', 'mhost002');
  }

  public testMonitorCase003(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('profile.level')(h, 'm003', d);
    eq(typeof d.value, 'function', 'm003');
    eq(h.title, 'init', 'mhost003');
  }

  public testMonitorCase004(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('settings.theme')(h, 'm004', d);
    eq(typeof d.value, 'function', 'm004');
    eq(h.title, 'init', 'mhost004');
  }

  public testMonitorCase005(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('settings.locale')(h, 'm005', d);
    eq(typeof d.value, 'function', 'm005');
    eq(h.title, 'init', 'mhost005');
  }

  public testMonitorCase006(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('network.type')(h, 'm006', d);
    eq(typeof d.value, 'function', 'm006');
    eq(h.title, 'init', 'mhost006');
  }

  public testMonitorCase007(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('network.signal')(h, 'm007', d);
    eq(typeof d.value, 'function', 'm007');
    eq(h.title, 'init', 'mhost007');
  }

  public testMonitorCase008(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('page.route')(h, 'm008', d);
    eq(typeof d.value, 'function', 'm008');
    eq(h.title, 'init', 'mhost008');
  }

  public testMonitorCase009(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('page.visible')(h, 'm009', d);
    eq(typeof d.value, 'function', 'm009');
    eq(h.title, 'init', 'mhost009');
  }

  public testMonitorCase010(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(h, 'm010', d);
    eq(typeof d.value, 'function', 'm010');
    eq(h.title, 'init', 'mhost010');
  }

  public testMonitorCase011(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('dialog.reason')(h, 'm011', d);
    eq(typeof d.value, 'function', 'm011');
    eq(h.title, 'init', 'mhost011');
  }

  public testMonitorCase012(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('list.count')(h, 'm012', d);
    eq(typeof d.value, 'function', 'm012');
    eq(h.title, 'init', 'mhost012');
  }

  public testMonitorCase013(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('list.offset')(h, 'm013', d);
    eq(typeof d.value, 'function', 'm013');
    eq(h.title, 'init', 'mhost013');
  }

  public testMonitorCase014(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('form.valid')(h, 'm014', d);
    eq(typeof d.value, 'function', 'm014');
    eq(h.title, 'init', 'mhost014');
  }

  public testMonitorCase015(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('form.progress')(h, 'm015', d);
    eq(typeof d.value, 'function', 'm015');
    eq(h.title, 'init', 'mhost015');
  }

  public testMonitorCase016(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('cache.size')(h, 'm016', d);
    eq(typeof d.value, 'function', 'm016');
    eq(h.title, 'init', 'mhost016');
  }

  public testMonitorCase017(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('cache.scope')(h, 'm017', d);
    eq(typeof d.value, 'function', 'm017');
    eq(h.title, 'init', 'mhost017');
  }

  public testMonitorCase018(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('user.id')(h, 'm018', d);
    eq(typeof d.value, 'function', 'm018');
    eq(h.title, 'init', 'mhost018');
  }

  public testMonitorCase019(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('user.email')(h, 'm019', d);
    eq(typeof d.value, 'function', 'm019');
    eq(h.title, 'init', 'mhost019');
  }

  public testMonitorCase020(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('task.total')(h, 'm020', d);
    eq(typeof d.value, 'function', 'm020');
    eq(h.title, 'init', 'mhost020');
  }

  public testMonitorCase021(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    Monitor('profile.name')(h, 'm021', d);
    eq(typeof d.value, 'function', 'm021');
    eq(h.title, 'init', 'mhost021');
  }

  public testSyncMonitorCase081(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('profile.*')(h, 's081', d);
    eq(typeof d.value, 'function', 's081');
    eq(h.envValue, 'default', 'shost081');
  }

  public testSyncMonitorCase082(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('settings.*')(h, 's082', d);
    eq(typeof d.value, 'function', 's082');
    eq(h.envValue, 'default', 'shost082');
  }

  public testSyncMonitorCase083(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('network.*')(h, 's083', d);
    eq(typeof d.value, 'function', 's083');
    eq(h.envValue, 'default', 'shost083');
  }

  public testSyncMonitorCase084(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('page.*')(h, 's084', d);
    eq(typeof d.value, 'function', 's084');
    eq(h.envValue, 'default', 'shost084');
  }

  public testSyncMonitorCase085(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('dialog.*')(h, 's085', d);
    eq(typeof d.value, 'function', 's085');
    eq(h.envValue, 'default', 'shost085');
  }

  public testSyncMonitorCase086(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('list.*')(h, 's086', d);
    eq(typeof d.value, 'function', 's086');
    eq(h.envValue, 'default', 'shost086');
  }

  public testSyncMonitorCase087(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('form.*')(h, 's087', d);
    eq(typeof d.value, 'function', 's087');
    eq(h.envValue, 'default', 'shost087');
  }

  public testSyncMonitorCase088(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('cache.*')(h, 's088', d);
    eq(typeof d.value, 'function', 's088');
    eq(h.envValue, 'default', 'shost088');
  }

  public testSyncMonitorCase089(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('task.*')(h, 's089', d);
    eq(typeof d.value, 'function', 's089');
    eq(h.envValue, 'default', 'shost089');
  }

  public testSyncMonitorCase090(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('metrics.*')(h, 's090', d);
    eq(typeof d.value, 'function', 's090');
    eq(h.envValue, 'default', 'shost090');
  }

  public testSyncMonitorCase091(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('profile.*')(h, 's091', d);
    eq(typeof d.value, 'function', 's091');
    eq(h.envValue, 'default', 'shost091');
  }

  public testSyncMonitorCase092(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('settings.*')(h, 's092', d);
    eq(typeof d.value, 'function', 's092');
    eq(h.envValue, 'default', 'shost092');
  }

  public testSyncMonitorCase093(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('network.*')(h, 's093', d);
    eq(typeof d.value, 'function', 's093');
    eq(h.envValue, 'default', 'shost093');
  }

  public testSyncMonitorCase094(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('page.*')(h, 's094', d);
    eq(typeof d.value, 'function', 's094');
    eq(h.envValue, 'default', 'shost094');
  }

  public testSyncMonitorCase095(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('dialog.*')(h, 's095', d);
    eq(typeof d.value, 'function', 's095');
    eq(h.envValue, 'default', 'shost095');
  }

  public testSyncMonitorCase096(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('list.*')(h, 's096', d);
    eq(typeof d.value, 'function', 's096');
    eq(h.envValue, 'default', 'shost096');
  }

  public testSyncMonitorCase097(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('form.*')(h, 's097', d);
    eq(typeof d.value, 'function', 's097');
    eq(h.envValue, 'default', 'shost097');
  }

  public testSyncMonitorCase098(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('cache.*')(h, 's098', d);
    eq(typeof d.value, 'function', 's098');
    eq(h.envValue, 'default', 'shost098');
  }

  public testSyncMonitorCase099(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('task.*')(h, 's099', d);
    eq(typeof d.value, 'function', 's099');
    eq(h.envValue, 'default', 'shost099');
  }

  public testSyncMonitorCase100(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('metrics.*')(h, 's100', d);
    eq(typeof d.value, 'function', 's100');
    eq(h.envValue, 'default', 'shost100');
  }

  public testSyncMonitorCase101(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('profile.*')(h, 's101', d);
    eq(typeof d.value, 'function', 's101');
    eq(h.envValue, 'default', 'shost101');
  }

  public testSyncMonitorCase102(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('settings.*')(h, 's102', d);
    eq(typeof d.value, 'function', 's102');
    eq(h.envValue, 'default', 'shost102');
  }

  public testSyncMonitorCase103(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('network.*')(h, 's103', d);
    eq(typeof d.value, 'function', 's103');
    eq(h.envValue, 'default', 'shost103');
  }

  public testSyncMonitorCase104(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('page.*')(h, 's104', d);
    eq(typeof d.value, 'function', 's104');
    eq(h.envValue, 'default', 'shost104');
  }

  public testSyncMonitorCase105(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('dialog.*')(h, 's105', d);
    eq(typeof d.value, 'function', 's105');
    eq(h.envValue, 'default', 'shost105');
  }

  public testSyncMonitorCase106(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('list.*')(h, 's106', d);
    eq(typeof d.value, 'function', 's106');
    eq(h.envValue, 'default', 'shost106');
  }

  public testSyncMonitorCase107(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('form.*')(h, 's107', d);
    eq(typeof d.value, 'function', 's107');
    eq(h.envValue, 'default', 'shost107');
  }

  public testSyncMonitorCase108(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('cache.*')(h, 's108', d);
    eq(typeof d.value, 'function', 's108');
    eq(h.envValue, 'default', 'shost108');
  }

  public testSyncMonitorCase109(): void {
    const h = new DecoratorCarrier();
    const d = new MonitorDescriptorImpl();
    SyncMonitor('task.*')(h, 's109', d);
    eq(typeof d.value, 'function', 's109');
    eq(h.envValue, 'default', 'shost109');
  }

  public testComputedCase181(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_181_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp181');
  }

  public testComputedCase182(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_182_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp182');
  }

  public testComputedCase183(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_183_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp183');
  }

  public testComputedCase184(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_184_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp184');
  }

  public testComputedCase185(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_185_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp185');
  }

  public testComputedCase186(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_186_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp186');
  }

  public testComputedCase187(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_187_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp187');
  }

  public testComputedCase188(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_188_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp188');
  }

  public testComputedCase189(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_189_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp189');
  }

  public testComputedCase190(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_190_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp190');
  }

  public testComputedCase191(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_191_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp191');
  }

  public testComputedCase192(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_192_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp192');
  }

  public testComputedCase193(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_193_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp193');
  }

  public testComputedCase194(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_194_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp194');
  }

  public testComputedCase195(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_195_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp195');
  }

  public testComputedCase196(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_196_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp196');
  }

  public testComputedCase197(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_197_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp197');
  }

  public testComputedCase198(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_198_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp198');
  }

  public testComputedCase199(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_199_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp199');
  }

  public testComputedCase200(): void {
    const h = new DecoratorCarrier();
    let t = 0;
    for (let n = 0; n < 5; n++) {
      const d = new ComputedDescriptorImpl();
      Computed(h, 'cc_200_' + n, d);
      t += d.get();
    }
    eq(t, 35, 'comp200');
  }

  public testExpansionCase0001(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0001', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0002(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0002', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0003(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0003', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0004(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0004', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0005(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0005', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0006(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0006', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0007(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0007', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0008(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0008', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0009(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0009', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0010(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0010', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0011(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0011', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0012(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0012', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0013(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0013', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0014(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0014', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0015(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0015', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0016(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0016', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0017(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0017', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0018(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0018', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0019(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0019', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0020(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0020', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0021(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0021', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0022(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0022', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0023(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0023', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0024(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0024', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0025(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0025', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0026(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0026', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0027(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0027', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0028(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0028', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0029(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0029', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0030(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0030', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0031(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0031', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0032(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0032', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0033(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0033', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0034(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0034', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0035(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0035', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0036(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0036', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0037(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0037', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0038(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0038', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0039(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0039', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0040(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0040', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0041(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0041', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0042(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0042', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0043(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0043', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0044(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0044', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0045(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0045', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0046(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0046', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0047(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0047', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0048(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0048', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0049(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0049', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0050(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0050', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0051(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0051', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0052(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0052', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0053(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0053', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0054(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0054', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0055(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0055', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0056(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0056', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0057(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0057', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0058(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0058', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0059(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0059', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0060(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0060', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0061(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0061', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0062(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0062', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0063(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0063', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0064(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0064', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0065(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0065', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0066(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0066', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0067(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0067', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0068(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0068', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0069(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0069', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0070(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0070', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0071(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0071', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0072(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0072', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0073(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0073', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0074(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0074', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0075(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0075', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0076(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0076', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0077(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0077', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0078(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0078', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0079(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0079', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0080(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0080', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0081(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0081', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0082(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0082', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0083(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0083', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0084(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0084', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0085(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0085', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0086(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0086', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0087(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0087', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0088(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0088', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0089(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0089', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0090(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0090', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0091(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0091', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0092(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0092', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0093(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0093', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0094(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0094', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0095(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0095', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0096(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0096', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0097(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0097', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0098(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0098', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0099(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0099', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0100(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0100', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0101(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0101', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0102(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0102', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0103(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0103', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0104(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0104', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0105(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0105', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0106(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0106', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0107(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0107', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0108(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0108', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0109(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0109', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0110(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0110', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0111(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0111', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0112(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0112', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0113(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0113', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0114(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0114', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0115(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0115', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0116(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0116', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0117(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0117', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0118(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0118', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0119(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0119', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0120(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0120', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0121(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0121', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0122(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0122', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0123(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0123', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0124(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0124', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0125(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0125', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0126(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0126', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0127(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0127', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0128(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0128', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0129(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0129', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0130(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0130', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0131(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0131', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0132(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.age')(host, 'exp_0132', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0133(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.level')(host, 'exp_0133', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0134(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.theme')(host, 'exp_0134', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0135(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('settings.locale')(host, 'exp_0135', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0136(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.type')(host, 'exp_0136', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0137(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('network.signal')(host, 'exp_0137', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0138(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.route')(host, 'exp_0138', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0139(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('page.visible')(host, 'exp_0139', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0140(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('dialog.opened')(host, 'exp_0140', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testExpansionCase0141(): void {
    const host = new DecoratorCarrier();
    const monitorDesc = new MonitorDescriptorImpl();
    Monitor('profile.name')(host, 'exp_0141', monitorDesc);
    eq(typeof monitorDesc.value, 'function', 'exp monitor function');
    eq(host.theme, 'light', 'exp host theme');
    eq(host.score, 1, 'exp host score');
  }

  public testFinalSummary(): void {
    const groups = 260;
    gt(groups, 200, 'groups');
    neq(groups, 0, 'nonzero');
    eq(groups, 260, 'exact');
  }
}
