import { Case1 } from "../build/generated/pages/case1" 
import { Case2 } from "../build/generated/pages/case2" 
import { UserView, UserViewBuilder } from "@koalaui/arkts-arkui"

export class EtsHarness extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        switch (this.params) {
            case "Case1": {
                /** @memo */
                const wrapper = () => { Case1() }
                return wrapper
            }
            case "Case2": {
                /** @memo */
                const wrapper = () => { Case2() }
                return wrapper
            }
            default: {
                throw new Error("No test case provided!")
            }
        }
    }
}
