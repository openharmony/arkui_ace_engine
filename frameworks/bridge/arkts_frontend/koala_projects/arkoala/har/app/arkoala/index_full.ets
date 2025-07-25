import UIAbility from '@ohos.app.ability.UIAbility';

// todo
// import { checkLoader } from "./loader.js"

import { __setPageLoader, __getModuleInfo, startArkoala, wrapOnWindowStageCreate } from "./bundle.js"

interface ModuleInfo {
  bundleName: string;
  moduleName: string;
}

async function loadPage(page: string) {
  let info: ModuleInfo = __getModuleInfo();
  let url: string = `@bundle:${info.bundleName}/${info.moduleName}/ets/${page}`;
  await import(url);
}

__setPageLoader(loadPage);

export * from "./bundle.js"

export class ArkoalaAbility extends UIAbility {
    constructor() {
        super()
        wrapOnWindowStageCreate(this)
    }
}

// todo
// checkLoader()
