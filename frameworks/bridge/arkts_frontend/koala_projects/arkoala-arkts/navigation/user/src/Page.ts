import { NavigationPage } from "app/navigation"
import { UserView, UserViewBuilder } from "@koalaui/arkts-arkui"

export class ComExampleNavigationApplication extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        /** @memo */
        let wrapper = () => {
            NavigationPage()
        }
        return wrapper
    }
}
