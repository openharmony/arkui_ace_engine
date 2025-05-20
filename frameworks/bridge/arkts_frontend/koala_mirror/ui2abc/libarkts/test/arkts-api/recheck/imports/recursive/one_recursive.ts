import { Two } from "./two_recursive"

export interface One {
    two(): Two {
        throw new Error("")
    }
}

