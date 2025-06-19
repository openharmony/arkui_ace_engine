import { Index } from "app/Index"
import { UserView, UserViewBuilder } from "@koalaui/arkts-arkui"

export class ComExampleCats extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        /** @memo */
        let wrapper = () => {
            Index()
        }
        return wrapper
    }
}
