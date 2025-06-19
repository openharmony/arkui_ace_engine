import UIAbility from '@ohos.app.ability.UIAbility';

import { __setPageLoader, __getModuleInfo, startArkoala, wrapOnWindowStageCreate } from "./bundle.js"

async function loadPage(page: string) {
}

__setPageLoader(loadPage);

export * from "./bundle.js"

export class ArkoalaAbility extends UIAbility {
    constructor() {
        super()
        wrapOnWindowStageCreate(this)
    }
}
