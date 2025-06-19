import { TestWrapper } from "app/TestWrapper"
import { UserView, UserViewBuilder } from "@koalaui/arkts-arkui"

export class ViewTestApp extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        /** @memo */
        let wrapper = () => {
            TestWrapper()
        }
        return wrapper
    }
}

