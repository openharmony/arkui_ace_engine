import { Index } from "app/pages/index-entry"
import { UserView, UserViewBuilder } from "@koalaui/arkts-arkui"

export class ComExampleShoppingApplication extends UserView {
    constructor(params: String) {
        super()
    }
    getBuilder(): UserViewBuilder {
        /** @memo */
        let wrapper = () => { Index() }
        return wrapper
    }
}
