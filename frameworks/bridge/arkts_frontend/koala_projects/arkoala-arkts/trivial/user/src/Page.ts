import { Page1 } from "app/page1"
import { UserView, UserViewBuilder } from "@koalaui/arkts-arkui"

export class ComExampleTrivialApplication extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        console.log(`ComExampleTrivialApplication`)
        /** @memo */
        let wrapper = () => {
            Page1()
        }
        return wrapper
    }
}
